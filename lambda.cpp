#include <iostream>

// capture rules
// [=] means capture all variables by value
// [&] means capture all variables by reference
// [var1] means capture variable var1 by value
// [&var1] means capture variable var1 by reference
// mixed forms
// [&var1,=] means capture var1 by reference, all other variables by value
// [var1,&] means capture var1 by value, all other variables by reference
// [var1,&var2] means capture var1 by value, var by reference

void test1() {
    auto f0 = []() {};   // shortest possible lambda
    auto f1 = [](int x, int y) {
        return x+y;
    };
    auto f2 = [](int x, int y) -> int { return x+y; };

    int r = 1;
    int s = 10;
    auto f3 = [](int x, int y) {
        return x
               // + r
               // + s
               + y;
    };
    auto f4 = [r,s](int x, int y) {
        return x
               + r
               + s
               + y;
    };
    auto f5 = [=](int x, int y) {
        return x
               + r
               + s
               + y;
    };
    auto f6 = [&](int x, int y) {
        return x
               + r
               + s
               + y;
    };
    auto f7 = [&](int x, int y) {
        r *= 10;
        s *= 100;
        return x
               + r
               + s
               + y;
    };
    std::cout << "r=" << r << ", s=" << s << std::endl;
    f7(1,2);
    std::cout << "r=" << r << ", s=" << s << std::endl;
}

typedef void(*ftype)();     // old-style function pointer
using fType = void(*)();    // new-style function pointer

template<typename T1, typename T2, int X>
void F(T1 t1, T2 t2) {
    for(int i=0; i<X; i++) {
        std::cout << ".";
    }
}

// TODO: not working
// template <typename T1>
// using F_double_10 = F<T1, double, 10>;

template <typename T1, typename T2, uint16_t N>
struct S {
    T1 t1;
    T2 t2;
    uint8_t val[N];
};

template <typename T>
using SI100 = S<T,bool,100>;


void test2() {
    F<int, int, 10>(1,1);
    F<decltype(1),decltype(1),10>(1,1);
    F<decltype(1.0),decltype(1),10>(1.0,1);
}

void test3() = delete;  // disallow definition of test3 function
void test3();           // declaration is not disallowed
// void test3() {}      // error

int main() {
    test1();
    test2();
    return 0;
}

