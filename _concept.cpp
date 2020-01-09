#include <iostream>
#include <cassert>
#include <string>
#include <type_traits>

// clang++ -std=c++2a -Xclang -fconcepts-ts concept.cpp
// g++ -std=c++17 -fconcepts concept.cpp
// g++ -std=c++1z -fconcepts concept.cpp

// template <class T, class U>
// concept Derived = std::is_base_of<U, T>::value;

// template <typename T>
// concept Hashable = requires(T a) {
//     {
//         std::hash<T> {}(a)
//     } -> std::size_t;
// };

template <typename T>
concept bool Xable1 {
};


template <typename T>
concept bool Xable2 {
    {}
};

template <typename T>
concept bool Xable3 {
    true
};

template <typename T>
concept bool Xable4 {
    false
};

// following is compiling with g++ 7.4.0
// it does not compile with clang++ 5.0.1

template<typename T>
concept bool EqualityComparable = requires(T a, T b) {
    {
        a == b
    } -> bool;
};

template<typename T>
concept bool Stringable = requires(T a) {
    {
        a.to_string()
    } -> std::string;
};

template<typename T>
concept bool Hashable = requires(T a) {
    {
        a.to_hash()
    } -> std::string;
};

template<typename T>
concept bool HasStringFunc = requires(T a) {
    {
        to_string(a)
    } -> std::string;

};

// option 1

template <EqualityComparable T>
class X1 {
// public:
// compiles with and without public
    bool operator==(const X1 & other) {
        return true;
    }
};

template <EqualityComparable T>
requires Stringable<T>
class X2 {
};

template <EqualityComparable T>
requires Stringable<T> && Hashable<T>
class X3 {
};

// option 2

template <typename T>
requires EqualityComparable<T>
class X4 {
};

template <typename T>
requires EqualityComparable<T> && Stringable<T> && Hashable<T>
class X5 {
};

template <typename T>
requires EqualityComparable<T> && (Stringable<T> || Hashable<T>)
class X6 {
};

// function template
template <typename T>
requires (sizeof(T) >= 4)
void f(T t) {}

// tests

void test() {
    X1<uint32_t> x1;
    // f(true); // constraints not satisfied
    f(1);
}

// main

int main() {
    std::cout << "main" << std::endl;
    assert(__cpp_concepts >= 201500);   // check compiled with -fconcepts
    assert(__cplusplus >= 201500);      //check compiled with --std=c++1z
    return 0;
}

