#include <iostream>
#include <limits>

// default int
enum class X1 {A,B,C};

// define underlying base
enum class X2 : uint8_t {A,B,C};

int main() {
    // std::cout << std::numeric_limits<X2>::min() << std::endl;    // not defined
    // std::cout << std::numeric_limits<uint16_t>::min() << std::endl;

    auto x1 = X1::A;
    auto x2 = X2::A;

    decltype (x1) x1a;
    decltype (x2) x2a;

    std::cout << typeid(x1).name() << std::endl;
    std::cout << typeid(decltype(x1)).name() << std::endl;

    std::cout << typeid(x2).name() << std::endl;
    std::cout << typeid(decltype(x2)).name() << std::endl;

    std::cout << typeid(1).name() << std::endl;
    std::cout << typeid(int).name() << std::endl;

    return 0;
}

