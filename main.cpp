#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <variant>
#include <memory>   // g++ needs it for shared_ptr and unique_ptr

enum class eTestResult {eFAILED, ePASSED};

class A {
public:
    virtual ~A() {} // gcc, clang warn when virtual dtor is missing
    void f() {}
    virtual void vf() {}
    virtual void avf() = 0;
    virtual void avf2() = 0;
};

class B : public A {
public:
    void vf(uint8_t) {} // clang warns overloaded function hidden
    void vf() override {}        // clang warning disappers when virtual function gets overloaded
    void avf() override {}
    void avf2() override final {}
};

class C : public B {
public:
    void avf() override {}
    // void avf2() override {}  // cannot override final virtual function
};


// attributes

[[nodiscard]]
eTestResult test1() {
    A * pc = new C();
    delete pc;
    //
    auto c1 = std::make_unique<C>();
    std::unique_ptr<C> c2 = std::make_unique<C>();
    //
    auto s1 = std::shared_ptr<C>();
    std::shared_ptr<C> s2 = std::make_shared<C>();
    return eTestResult::ePASSED;
}

// write comma separated
[[noreturn, maybe_unused]]
void stop1() {
    while(true);
}
// write in sequence
[[noreturn]][[maybe_unused]]
void stop2() {
    while(true);
}
// write after function name
void stop3 [[noreturn,maybe_unused]] ()  {
    while(true) {}
}
void stop4 [[noreturn]][[maybe_unused]] ()  {
    while(true) {}
}

[[deprecated]]
void _old_f1() {}

[[deprecated("use _new_f2()")]]
void _old_f2() {}

[[]]    // empty attribute OK
void foo() {}

void bar(uint8_t val) {
    switch(val) {
    case 0:
        [[fallthrough]];
    case 1:
    case 2:
    case 3:
        ;
    case 4:
    case 5:
        break;
    // [[likely]]
    default:
        ;
    }
}


int main() {
    if(test1() == eTestResult::ePASSED) {
    }
    // _old_f1();
    // _old_f2();
    return EXIT_SUCCESS;
}



