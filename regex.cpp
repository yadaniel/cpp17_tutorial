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
        // std::regex pattern(R"(\w+)=(\d+)",
        // std::regex pattern(R"([a-z]+)=([0-9]+)",     // regex error OR mismatched () exception
        std::regex pattern("([a-z]+)=([0-9]+)",
                           std::regex::awk |         // works
                           // std::regex::grep |
                           // std::regex::egrep |       // works
                           // std::regex::basic |
                           // std::regex::extended |    // works
                           std::regex::icase
                           // std::regex::multiline |   // not compiling
                           // std::regex::optimized     // not compiling
                          );

        std::cmatch m1, m2;
        bool b1 = std::regex_match("x=123", m1, pattern);
        bool b2 = std::regex_search("x=123", m2, pattern);
        std::cout << std::boolalpha << "match=" << b1 << ", search=" << b2 << std::endl;

        if(b1) {
            std::cout << "b1" << std::endl;
            std::cout << m1[0] << std::endl;
            std::cout << m1[1] << std::endl;
            std::cout << m1[2] << std::endl;
        }

        if(b2) {
            std::cout << "b2" << std::endl;
            std::cout << m2[0] << std::endl;
            std::cout << m2[1] << std::endl;
            std::cout << m2[2] << std::endl;
        }

        std::smatch m3, m4;
        std::string line{"x=123"};
        bool b3 = std::regex_match(line, m3, pattern);
        bool b4 = std::regex_search(line, m4, pattern);
        std::cout << std::boolalpha << "match=" << b3 << ", search=" << b3 << std::endl;

        if(b3) {
            std::cout << "b3" << std::endl;
            std::cout << m3[0] << std::endl;
            std::cout << m3[1] << std::endl;
            std::cout << m3[2] << std::endl;
        }

        if(b4) {
            std::cout << "b4" << std::endl;
            std::cout << m4[0] << std::endl;
            std::cout << m4[1] << std::endl;
            std::cout << m4[2] << std::endl;
        }


        //
        std::cout << std::boolalpha;    // ok, set stream flag before << true and false
        std::cout << "true=" << true << ", false=" << false << std::endl;

    } catch(std::exception & exc) {
        std::cout << "catched: " << exc.what() << std::endl;
    }
}

void test2() {
    std::string text = "x=1, y=10, z=100";
    std::regex pattern("[a-z]+=[0-9]+");
    std::sregex_iterator next(text.begin(), text.end(), pattern);
    std::sregex_iterator end;
    while(next != end) {
        std::smatch m {*next};
        std::cout << m.str() << std::endl;
        next++;
    }
}

void test3() {
    std::string text = "x=1, y=10, z=100";
    std::regex pattern("([a-z]+)=([0-9]+)");
    std::sregex_iterator next(text.begin(), text.end(), pattern);
    std::sregex_iterator end;
    while(next != end) {
        std::smatch m {*next};
        std::cout << m.str() << std::endl;
        std::cout << m.str(0) << std::endl;
        std::cout << m.str(1) << std::endl;
        std::cout << m.str(2) << std::endl;
        if(m.str(3) == "") {
            std::cout << "non existing group 3 is empty" << std::endl;
        }
        try {
            std::cout << m.str(3) << std::endl;
        } catch (...) {
            std::cout << "no group 3" << std::endl;
        }
        next++;
    }
}

void test4() {
    const char * text = "x=1, y=10, z=100";
    int len = strlen(text);
    std::regex pattern("([a-z]+)=([0-9]+)");
    std::cregex_iterator next(&text[0], &text[len], pattern);
    std::cregex_iterator end;
    while(next != end) {
        std::cmatch m {*next};
        std::cout << m.str() << std::endl;
        std::cout << m.str(0) << std::endl;
        std::cout << m.str(1) << std::endl;
        std::cout << m.str(2) << std::endl;
        if(m.str(3) == "") {
            std::cout << "non existing group 3 is empty" << std::endl;
        }
        try {
            std::cout << m.str(3) << std::endl;
        } catch (...) {
            std::cout << "no group 3" << std::endl;
        }
        next++;
    }
}

int main() {
    // test1();
    // test2();
    // test3();
    test4();
    // assert_example(10);
    return 0;
}

