#line 1 "mixed-intro-example-three-loops.cpp2"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <span>
#include <memory>

auto print(auto const& thing) -> void { 
    std::cout << ">> " << thing << "\n";
}

auto decorate_and_print(auto& thing) -> void { 
    thing = "[" + thing + "]";
    print(thing);
}

auto main() -> int {
    auto words = std::vector<std::string>
        { "hello", "big", "world" };

    std::span<std::string> view{ words };

    auto i = std::make_unique<int>(0);
    while (*i < view.size()) {
        print( view[*i] );
        ++*i;
    }

    do {
        std::cout << std::setw(4) << "**";
    } while (--*i > 0);

    std::cout << "\n";
    for (auto& word : words) {
        decorate_and_print(word);
    }
}
