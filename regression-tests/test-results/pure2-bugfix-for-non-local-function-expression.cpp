
#define CPP2_USE_MODULES         Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"


#line 9 "pure2-bugfix-for-non-local-function-expression.cpp2"
class t;
    

//=== Cpp2 type definitions and function declarations ===========================

//  Clang note: When using Clang as the Cpp1 compiler, the following uses of an unnamed function
//  require Clang 13 or higher; Clang 12 complains "lambda expression in an unevaluated operand"
//  Standalone Cpp1 repro: https://godbolt.org/z/dznnYTvc6

#line 5 "pure2-bugfix-for-non-local-function-expression.cpp2"
template<typename T> concept v = []() -> bool { return true;  }(); 

using u = std::type_identity_t<decltype([]() -> void{})>;

class t: public std::type_identity_t<decltype([]() -> void{})> {

};

auto main() -> int;


//=== Cpp2 function definitions =================================================


#line 13 "pure2-bugfix-for-non-local-function-expression.cpp2"
auto main() -> int{}

