#include <iostream>
#include <iomanip>
#include <cassert>
#include <typeinfo>     // typeid
#include <climits>
#include <type_traits>

// interger promotion rules
// default argument promotion rules for functions with unprototyped arguments (function with ellispis)

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
    // integer promotion rule:
    //        integer types smaller than int (short, char) are promoted when an operation is performed on them.
    //        If all values of smaller type can be represented in int, then the value of smaller type is converted to int.
    //        Otherwise the value of the smaller type is converted to unsigned int.
    // arithmetic conversion rule:
    //        conversion takes place after integer promotion has been applied
    //        the types of promoted values of the operands must yield common type for the operation result
    //        if both operands have same type, then no further conversion is required
    //        if both operands are of the same integer type (all signed or all unsigned, but with different ranks), then the operand with the type of lesser integer rank is converted to the type of the operand with greater rank.
    //        if the operand that has unsigned integer type has rank greater than or equal to the rank of the type of the other (signed) operand, then the operand with signed integer type is converted to the type of the operand with unsigned integer type.
    //        if the type of the operand with signed integer type can represent all of the values of the type of the operand with unsigned integer type, then the operand with unsigned integer type is converted to the type of the operand with signed integer type,
    //        if the type of the operand with signed integer type cannot represent all of the values of the type of the operand with unsgiend integer type, then both operands are converted to the unsigned integer type corresponding to the type of the operand with signed integer type.
    //        TODO: lookup the defintion of type rank

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
        uint8_t u8 {1};
        int8_t i8 {-2};
        uint8_t res1 = i8 + u8;     // i8,u8 promoted to int, then casted to uint8_t
        int8_t res2 = i8 + u8;      // i8,u8 promoted to int, then casted to int8_t
        cout << static_cast<uint16_t>(res1) << "..." << static_cast<uint16_t>(res2)
             << "..." << static_cast<uint16_t>(i8 + u8) << endl;  // 255...65535...65535
        cout << typeid(decltype(i8 + u8)).name() << endl; // i
        cout << typeid(res1).name() << endl; // h
        cout << typeid(res2).name() << endl; // a
    }

    {
        uint16_t u16 {1};
        int16_t i16 {-2};
        uint16_t res1 = i16 + u16;  // i16,u16 promoted to int, then casted to uint16_t
        int16_t res2 = i16 + u16;   // i16,u16 promoted to int, then casted to int16_t
        cout << res1 << "..." << res2 << "..." << i16 + u16 << endl;  // 65535 ... -1 ... -1
        cout << typeid(decltype(i16 + u16)).name() << endl; // i
        cout << typeid(res1).name() << endl; // t
        cout << typeid(res2).name() << endl; // s
    }

    {
        uint32_t u32 {1};
        int32_t i32 {-2};
        uint32_t res1 = i32 + u32;  // u32 NOT promoted to int, i32 promoted to unsigned int
        int32_t res2 = i32 + u32;   // u32 NOT promoted to int, i32 promoted to unsigned int
        cout << res1 << "..." << res2 << "..." << i32 + u32 << endl;    // 4294967295...-1...4294967295
        cout << typeid(decltype(i32 + u32)).name() << endl; // j
        cout << typeid(res1).name() << endl; // j
        cout << typeid(res2).name() << endl; // i
    }

    {
        uint64_t u64 {1};
        int64_t i64 {-2};
        uint64_t res1 = i64 + u64;  // u64 NOT promoted to int, u64 promoted to unsigned long long
        int64_t res2 = i64 + u64;   // u64 NOT promoted to int, u64 promoted to unsigned long long
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

template<typename T>
void type(std::string t) {

    int size = ((t.size() / 10) + 1) * 10;
    t.resize(size, ' ');

    if constexpr(std::is_same<T,int8_t>() || std::is_same<T,uint8_t>()) {
        cout << t << typeid(T).name() << ", "
             << "min=" << static_cast<int16_t>(std::numeric_limits<T>::min()) << ", "
             << "max=" << static_cast<int16_t>(std::numeric_limits<T>::max()) <<  endl;
    } else {
        cout << t << typeid(T).name() << ", "
             << "min=" << std::numeric_limits<T>::min() << ", "
             << "max=" << std::numeric_limits<T>::max() <<  endl;
    }
}

void test3() {
    type<int8_t>(string("int8_t"));
    type<int16_t>(string("int16_t"));
    type<int32_t>(string("int32_t"));
    type<int64_t>(string("int64_t"));
    type<uint8_t>(string("uint8_t"));
    type<uint16_t>(string("uint16_t"));
    type<uint32_t>(string("uint32_t"));
    type<uint64_t>(string("uint64_t"));

    // show types of expressions
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;

    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;

    type<decltype(u8)>(string("decltype(u8)"));         // uint8_t
    type<decltype(!u8)>(string("decltype(!u8)"));       // bool
    type<decltype(~u8)>(string("decltype(~u8)"));       // int
    type<decltype(+u8)>(string("decltype(+u8)"));       // int
    type<decltype(-u8)>(string("decltype(-u8)"));       // int
    type<decltype(u8+0)>(string("decltype(u8+0)"));     // int
    type<decltype(u8-0)>(string("decltype(u8-0)"));     // int
    type<decltype(u8*1)>(string("decltype(u8*1)"));     // int
    type<decltype(u8/1)>(string("decltype(u8/1)"));     // int
    type<decltype(u8>>0)>(string("decltype(u8>>0)"));   // int
    type<decltype(u8<<0)>(string("decltype(u8<<0)"));   // int
    type<decltype(u8 & 0xFF)>(string("decltype(u8 & 0xFF)"));   // int
    type<decltype(u8 | 0x00)>(string("decltype(u8 | 0x00)"));   // int
    type<decltype(u8 ^ 0x00)>(string("decltype(u8 ^ 0x00)"));   // int
    // type<decltype(u8 && 0xFF)>(string("decltype(u8 && 0xFF)"));   // bool ... compiler warning
    // type<decltype(u8 || 0x00)>(string("decltype(u8 || 0x00)"));   // bool ... compiler warning
    type<decltype(u8 && true)>(string("decltype(u8 && true)"));   // bool
    type<decltype(u8 || false)>(string("decltype(u8 || false)"));   // bool
    type<decltype(u8+0ul)>(string("decltype(u8+0ul)")); // unsigned long long
    type<decltype(u8-0ul)>(string("decltype(u8-0ul)")); // unsigned long long
    type<decltype(u8*1ul)>(string("decltype(u8*1ul)")); // unsigned long long
    type<decltype(u8/1ul)>(string("decltype(u8/1ul)")); // unsigned long long
    type<decltype(u8>>0ul)>(string("decltype(u8>>0ul)")); // int
    type<decltype(u8<<0ul)>(string("decltype(u8<<0ul)")); // int

    // note: when calling printf("%f", 32.0f) or printf("%x", 'x')
    // the double and integer promotion happens before printf is called
    // thus it is not possible to pass float and char unpromoted to printf function
}

void test4() {
    // make_unsigned
    using _uint8_t = std::make_unsigned<int8_t>::type;
    using _uint16_t = std::make_unsigned<int16_t>::type;
    using _uint32_t = std::make_unsigned<int32_t>::type;
    using _uint64_t = std::make_unsigned<int64_t>::type;
    static_assert(std::is_same<_uint8_t, uint8_t>());
    static_assert(std::is_same<_uint16_t, uint16_t>());
    static_assert(std::is_same<_uint32_t, uint32_t>());
    static_assert(std::is_same<_uint64_t, uint64_t>());
    // make_signed
    using _int8_t = std::make_signed<uint8_t>::type;
    using _int16_t = std::make_signed<uint16_t>::type;
    using _int32_t = std::make_signed<uint32_t>::type;
    using _int64_t = std::make_signed<uint64_t>::type;
    static_assert(std::is_same<_int8_t, int8_t>());
    static_assert(std::is_same<_int16_t, int16_t>());
    static_assert(std::is_same<_int32_t, int32_t>());
    static_assert(std::is_same<_int64_t, int64_t>());
    // is_unsigned
    static_assert(std::is_unsigned<uint8_t>());
    static_assert(std::is_unsigned<uint16_t>());
    static_assert(std::is_unsigned<uint32_t>());
    static_assert(std::is_unsigned<uint64_t>());
    // is_signed
    static_assert(std::is_signed<int8_t>());
    static_assert(std::is_signed<int16_t>());
    static_assert(std::is_signed<int32_t>());
    static_assert(std::is_signed<int64_t>());

    // ...
    static_assert(std::is_unsigned<bool>());    // bool is unsigned
    // static_assert(std::is_signed<bool>());
    // static_assert(std::is_unsigned<float>());
    // static_assert(std::is_unsigned<double>());
    // static_assert(std::is_unsigned<long double>());
    static_assert(std::is_signed<float>());         // float is signed
    static_assert(std::is_signed<double>());        // double is signed
    static_assert(std::is_signed<long double>());   // long double is signed

    // is_integral
    static_assert(std::is_integral<uint8_t>());
    static_assert(std::is_integral<uint16_t>());
    static_assert(std::is_integral<uint32_t>());
    static_assert(std::is_integral<uint64_t>());
    static_assert(std::is_integral<int8_t>());
    static_assert(std::is_integral<int16_t>());
    static_assert(std::is_integral<int32_t>());
    static_assert(std::is_integral<int64_t>());
    static_assert(std::is_integral<bool>());        // bool is integral
    // static_assert(std::is_integral<float>());
    // static_assert(std::is_integral<double>());
    // static_assert(std::is_integral<long double>());
    static_assert(std::is_floating_point<float>());
    static_assert(std::is_floating_point<double>());
    static_assert(std::is_floating_point<long double>());

    // TODO: is_arithmetic
    // TODO: is_fundamental

    // show at runtime
    cout << "is uint32_t unsigned? -> " << std::is_unsigned<uint32_t>::value << endl;

}

void test5() {
    cout << "test5" << endl;

    // as static asserts ... uint8_t and ints of different rank
    static_assert(is_same<decltype(uint8_t(0)+int8_t(0)),int32_t>());
    static_assert(is_same<decltype(uint8_t(0)+int16_t(0)),int32_t>());
    static_assert(is_same<decltype(uint8_t(0)+int32_t(0)),int32_t>());
    static_assert(is_same<decltype(uint8_t(0)+int64_t(0)),int64_t>());
    // as static asserts ... uint8_t and uints of different rank
    static_assert(is_same<decltype(uint8_t(0)+uint8_t(0)),int32_t>());
    static_assert(is_same<decltype(uint8_t(0)+uint16_t(0)),int32_t>());
    static_assert(is_same<decltype(uint8_t(0)+uint32_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint8_t(0)+uint64_t(0)),uint64_t>());

    // as static asserts ... uint16_t and ints of different rank
    static_assert(is_same<decltype(uint16_t(0)+int8_t(0)),int32_t>());
    static_assert(is_same<decltype(uint16_t(0)+int16_t(0)),int32_t>());
    static_assert(is_same<decltype(uint16_t(0)+int32_t(0)),int32_t>());
    static_assert(is_same<decltype(uint16_t(0)+int64_t(0)),int64_t>());
    // as static asserts ... uint16_t and uints of different rank
    static_assert(is_same<decltype(uint16_t(0)+uint8_t(0)),int32_t>());
    static_assert(is_same<decltype(uint16_t(0)+uint16_t(0)),int32_t>());
    static_assert(is_same<decltype(uint16_t(0)+uint32_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint16_t(0)+uint64_t(0)),uint64_t>());

    // as static asserts ... uint32_t and ints of different rank
    static_assert(is_same<decltype(uint32_t(0)+int8_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+int16_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+int32_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+int64_t(0)),int64_t>());
    // as static asserts ... uint32_t and uints of different rank
    static_assert(is_same<decltype(uint32_t(0)+uint8_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+uint16_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+uint32_t(0)),uint32_t>());
    static_assert(is_same<decltype(uint32_t(0)+uint64_t(0)),uint64_t>());

    // as static asserts ... uint64_t and ints of different rank
    static_assert(is_same<decltype(uint64_t(0)+int8_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+int16_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+int32_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+int64_t(0)),uint64_t>());
    // as static asserts ... uint64_t and uints of different rank
    static_assert(is_same<decltype(uint64_t(0)+uint8_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+uint16_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+uint32_t(0)),uint64_t>());
    static_assert(is_same<decltype(uint64_t(0)+uint64_t(0)),uint64_t>());

    // float
    static_assert(is_same<decltype(float(0)+uint8_t(0)),float>());
    static_assert(is_same<decltype(float(0)+uint16_t(0)),float>());
    static_assert(is_same<decltype(float(0)+uint32_t(0)),float>());
    static_assert(is_same<decltype(float(0)+uint64_t(0)),float>());
    static_assert(is_same<decltype(float(0)+int8_t(0)),float>());
    static_assert(is_same<decltype(float(0)+int16_t(0)),float>());
    static_assert(is_same<decltype(float(0)+int32_t(0)),float>());
    static_assert(is_same<decltype(float(0)+int64_t(0)),float>());
    static_assert(is_same<decltype(float(0)+float(0)),float>());
    static_assert(is_same<decltype(float(0)+double(0)),double>());
    static_assert(is_same<decltype(float(0)+(long double)0),long double>());
    // double
    static_assert(is_same<decltype(double(0)+uint8_t(0)),double>());
    static_assert(is_same<decltype(double(0)+uint16_t(0)),double>());
    static_assert(is_same<decltype(double(0)+uint32_t(0)),double>());
    static_assert(is_same<decltype(double(0)+uint64_t(0)),double>());
    static_assert(is_same<decltype(double(0)+int8_t(0)),double>());
    static_assert(is_same<decltype(double(0)+int16_t(0)),double>());
    static_assert(is_same<decltype(double(0)+int32_t(0)),double>());
    static_assert(is_same<decltype(double(0)+int64_t(0)),double>());
    static_assert(is_same<decltype(double(0)+double(0)),double>());
    static_assert(is_same<decltype(double(0)+(long double)0),long double>());
    // long double
    static_assert(is_same<decltype((long double)0+uint8_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+uint16_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+uint32_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+uint64_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+int8_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+int16_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+int32_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+int64_t(0)),long double>());
    static_assert(is_same<decltype((long double)0+(long double)0),long double>());

}

int main() {
    using_assert();
    (void)test1();  // explicit ignore [[nodiscard]] attributed return value
    // test2();
    test3();
    test4();
    test5();
    return 0;
}

