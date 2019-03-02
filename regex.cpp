#include <iostream>
#include <iomanip>
#include <cassert>
#include <regex>

// std::nullptr_t, nullptr
// overloading on int and pointer type now possible
// 0 calls int overload, nullptr call pointer overload

// noexcept is an improved version of throw(), which is depricated from c++11
void f1() noexcept; // calls std::terminate() when thrown, may or may not unwind the stack
void f2() throw();  // calls std::unexpected() when thrown, default handler will then call std::terminate()
void f3() noexcept(true);   // alternative syntax
void f4() noexcept(false);  // same when omitted

// alignment
alignas(4) char buffer1[10*sizeof(float)];
alignas(sizeof(float)) char buffer2[10*sizeof(float)];
alignas(double) char buffer3[10*sizeof(double)];
static_assert(alignof(buffer1) == 4);   // does not require cassert
static_assert(alignof(buffer2) == 4);
static_assert(alignof(buffer3) == 8);

void assert_example(int x) {
    assert(x == 10);
    int i{};
    std::cout << alignof(i) << std::endl;
}

void test1() {
    try {
        // std::regex pattern(R"(\w+)=(\d+)",
        // gcc will throw "Unexpected escape character"
        // clang will throw "An empty regex is not allowed in the POSIX grammar"
        std::regex pattern(R"(\\w+)=(\\d+)",
                           std::regex::grep |
                           std::regex::icase
                           // std::regex::multiline |
                           // std::regex::optimized
                          );

        std::cmatch m1, m2;
        bool b1 = std::regex_match("x=123", m1, pattern);
        bool b2 = std::regex_search("x=123", m2, pattern);

        std::cout << std::boolalpha;    // ok, set stream flag before << b1 and b2
        std::cout << "match=" << b1 << ", search=" << b2 << std::endl;
    } catch(std::exception & exc) {
        std::cout << "catched: " << exc.what() << std::endl;
    }
}

int main() {
    test1();
    assert_example(10);
    return 0;
}

