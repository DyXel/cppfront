#ifndef CPP2_TESTING_H
#define CPP2_TESTING_H

namespace cpp2::testing {

using test_function = void(void);

class session {
public:
	session() {
		std::cout << "Creating test session!\n";
	}

	static inline session& the() {
		static session instance;
		return instance;
	}

	void register_test(test_function* tf) {
		tests_.push_back(tf);
	}

	void run(int const argc, char** argv) {
		std::cout << "Running test session!\n";
		int test_count = 0;
		for(auto test : tests_) {
			std::cout << "Running test " << test_count++ << "!\n";
			test();
		}
	}
private:
	std::vector<test_function*> tests_;
};

struct auto_reg {
	auto_reg(test_function* tf) {
		std::cout << "Registering test func: " << tf << '\n';
		session::the().register_test(tf);
	}
};

}

#endif
