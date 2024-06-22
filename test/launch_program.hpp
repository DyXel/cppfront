#ifndef LAUNCH_PROGRAM_HPP
#define LAUNCH_PROGRAM_HPP
#include <filesystem>
#include <string>
#include <vector>

struct launch_result
{
	int exit_status;
	std::string output;
};

auto launch_program(
	std::filesystem::path const& work_dir,
	std::filesystem::path const& exe,
	std::vector<std::string> const& args
) -> launch_result;

#ifdef LAUNCH_PROGRAM_IMPLEMENTATION
#ifdef _WIN32
#define _WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <array>
#include <iostream>

auto launch_program(
	std::filesystem::path const& work_dir,
	std::filesystem::path const& exe,
	std::vector<std::string> const& args
) -> launch_result {
	auto make_pipe_handle_pair = []() -> std::pair<HANDLE, HANDLE> {
		SECURITY_ATTRIBUTES saAttr{sizeof(SECURITY_ATTRIBUTES), nullptr, true};
		HANDLE read_end = nullptr;
		HANDLE write_end = nullptr;
		if(!CreatePipe(&read_end, &write_end, &saAttr, 0)) { return {}; }
		if(!SetHandleInformation(read_end, HANDLE_FLAG_INHERIT, 0)) {
			CloseHandle(write_end);
			CloseHandle(read_end);
			return {};
		}
		return {read_end, write_end};
	};

	auto [stdout_read, stdout_write] = make_pipe_handle_pair();
	auto [stderr_read, stderr_write] = make_pipe_handle_pair();

	PROCESS_INFORMATION piProcInfo;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	STARTUPINFOA siStartInfo;
	ZeroMemory(&siStartInfo, sizeof(siStartInfo));
	siStartInfo.cb = sizeof(siStartInfo);
	siStartInfo.hStdOutput = stdout_write;
	siStartInfo.hStdError = stderr_write;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	std::string cl_args = exe.string();
	for(const auto& arg : args) { cl_args.append(1, ' ').append(arg); }

	if(
		!CreateProcessA(
			exe.string().c_str(),
			cl_args.data(),
			nullptr,
			nullptr,
			true,
			0,
			nullptr,
			work_dir.string().c_str(),
			&siStartInfo,
			&piProcInfo
		)
	) {

		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);

		CloseHandle(stdout_write);
		CloseHandle(stdout_read);

		CloseHandle(stderr_write);
		CloseHandle(stderr_read);

		return {-1, {}};
	}

	CloseHandle(piProcInfo.hThread);

	CloseHandle(stdout_write);
	CloseHandle(stderr_write);

	auto read_from_pipe = [](HANDLE read_end) {
		std::array<char, 4096> buff;
		std::string out;

		while(true) {
			DWORD bytes_read;
			if(
				!ReadFile(
					read_end,
					buff.data(),
					static_cast<DWORD>(buff.size()),
					&bytes_read,
					nullptr
				) || bytes_read == 0
			) { break; }
			out.append(buff.data(), bytes_read);
		}

		CloseHandle(read_end);
		return out;
	};

	std::string output = read_from_pipe(stdout_read);
	output += read_from_pipe(stderr_read);

	DWORD exitCode{};
	GetExitCodeProcess(piProcInfo.hProcess, &exitCode);
	CloseHandle(piProcInfo.hProcess);

	return {static_cast<int>(exitCode), output};
}
#else // POSIX
#include <array>
#include <stdio.h>

auto launch_program(
	std::filesystem::path const& work_dir,
	std::filesystem::path const& exe,
	std::vector<std::string> const& args
) -> launch_result {
	auto const prev_work_dir = std::filesystem::current_path();
	std::filesystem::current_path(work_dir);

	std::string cl_args = exe.string();
	for(const auto& arg : args) { cl_args.append(1, ' ').append(arg); }
	cl_args += " 2>&1";

	auto const fd = popen(cl_args.c_str(), "r");
	if(fd == nullptr) {
		std::filesystem::current_path(prev_work_dir);
		return {-1, {}};
	}

	std::string output;
	{
		std::array<char, 4096> buff;
		while (
				fgets(
					buff.data(),
					static_cast<int>(buff.size()),
					fd
				) != nullptr
			) {
			output += buff.data();
		}
	}

	std::filesystem::current_path(prev_work_dir);
	return {pclose(fd), output};
}

#endif // _WIN32
#endif // LAUNCH_PROGRAM_IMPLEMENTATION
#endif // LAUNCH_PROGRAM_HPP
