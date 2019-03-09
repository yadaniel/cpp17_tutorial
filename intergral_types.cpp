#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

void using_assert() {
    const uint8_t C = 0xFF;

    // assert is evaluated at runtime
    assert(C == 255);
    assert(C == 0xFF);
    assert(C == 0377);
    assert(C == 0b11111111);

    // helper function for compiler implementation
    // __assert(__FILE__, line, "message");   // print filename (char*), line(int) and message(char*)

    // static_assert is evaluated at compile time
    static_assert(C == 0xFF);
}

[[nodiscard]]
uint16_t test1() {
    // results of mathematical expression on unsigned types are "modulo corrected"
    // thus the result is always defined (in range of the type)
    uint8_t u8; // 0 ... 255
    u8 = 255;
    u8 += 1;    // well defined
    assert(u8 == 0);    // wrap around to 0
    u8 -= 1;    // well defined
    assert(u8 == 0xFF);

    // results of mathematical expression on signed types are not "modulo corrected"
    int8_t i8;  // -128 ... 127
    // overflow
    i8 = 127;
    i8 += 1;    // undefined behaviour because the result is not in range of int8_t
    assert(i8 == -128);     // gcc and clang choose to implement that 0b0111_1111 -> 0b1000_0000, thus assert holds here
    // underflow
    i8 = -128;  // 0b1000_0000
    i8 -= 1;    // undefined behaviour because the result is not in range of int8_t
    assert(i8 == 127);  // gcc and clang choose to implement that 0b1000_0000 -> 0b0111_1111, thus assert holds here
    // transition from negative to positive
    i8 = -1;    // 0b1111_1111
    i8 += 1;    // defined behaviour because the results remains in range of int8_t

    return 0;
}

void test2() {
    // using signed and unsigned types in same expression
}

int main() {
    using_assert();
    (void)test1();  // explicit ignore [[nodiscard]] attributed return value
    test2();
    return 0;
}

