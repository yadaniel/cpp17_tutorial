#include <iostream>
#include <iomanip>
#include <cassert>
#include <typeinfo>     // typeid

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
    // rule1: when signed and unsigned types of the same rank are used together, then signed values are casted to unsigned (unsigned wins)
    // rule2: when ranks are different, then values of the lower rank are casted to higher ranked type, if all values can be represented
    // if higher ranked type cannot represent all values of lower ranked type, then unsigned version of the higher ranked type is used

    // rule1
    // u16 = 1;
    // i16 = -1;
    // step1: u16 and i16 of the same rank => -1 casted to uint16_t => 0xFFFF
    // step2: 0xFFFF + 0x0001 => 0x10000
    // step3: 0x10000 & 0xFFFF => 0x0000 ... modulo conversion

    cout << string(35,'*') << " type letters " << string(35,'*') << endl;
    cout << "uint8_t => " << typeid(uint8_t).name() << endl;    // h
    cout << "uint16_t => " << typeid(uint16_t).name() << endl;  // t
    cout << "uint32_t => " << typeid(uint32_t).name() << endl;  // j
    cout << "uint64_t => " << typeid(uint64_t).name() << endl;  // m
    cout << "int8_t => " << typeid(int8_t).name() << endl;      // a
    cout << "int16_t => " << typeid(int16_t).name() << endl;    // s
    cout << "int32_t => " << typeid(int32_t).name() << endl;    // i
    cout << "int64_t => " << typeid(int64_t).name() << endl;    // l
    cout << string(84, '*') << endl;

    {
        // rule1
        uint8_t u8 {1};
        int8_t i8 {-2};
        uint8_t res1 = i8 + u8;
        int8_t res2 = i8 + u8;
        cout << static_cast<uint16_t>(res1) << "..." << static_cast<uint16_t>(res2) << "..." << static_cast<uint16_t>(i8 + u8) << endl;  // 255...65535...65535
        cout << typeid(decltype(i8 + u8)).name() << endl; // i
        cout << typeid(res1).name() << endl; // h
        cout << typeid(res2).name() << endl; // a
    }

    {
        // rule1
        uint16_t u16 {1};
        int16_t i16 {-2};
        uint16_t res1 = i16 + u16;
        int16_t res2 = i16 + u16;
        cout << res1 << "..." << res2 << "..." << i16 + u16 << endl;  // 65535 ... -1 ... -1
        cout << typeid(decltype(i16 + u16)).name() << endl; // i
        cout << typeid(res1).name() << endl; // t
        cout << typeid(res2).name() << endl; // s
    }

    {
        // rule1
        uint32_t u32 {1};
        int32_t i32 {-2};
        uint32_t res1 = i32 + u32;
        int32_t res2 = i32 + u32;
        cout << res1 << "..." << res2 << "..." << i32 + u32 << endl;    // 4294967295...-1...4294967295
        cout << typeid(decltype(i32 + u32)).name() << endl; // j
        cout << typeid(res1).name() << endl; // j
        cout << typeid(res2).name() << endl; // i
    }

    {
        // rule1
        uint64_t u64 {1};
        int64_t i64 {-2};
        uint64_t res1 = i64 + u64;
        int64_t res2 = i64 + u64;
        cout << res1 << "..." << res2 << "..." << i64 + u64 << endl;    // 18446744073709551615...-1...18446744073709551615
        cout << typeid(decltype(i64 + u64)).name() << endl; // m
        cout << typeid(res1).name() << endl; // m
        cout << typeid(res2).name() << endl; // l
    }

    // C++ does not define "typeof"
    // typeof is GCC extension, use decltype defined in c++17
    // decltype is compile-time construct
    // typeid is run-time construct
}

int main() {
    using_assert();
    (void)test1();  // explicit ignore [[nodiscard]] attributed return value
    test2();
    return 0;
}

