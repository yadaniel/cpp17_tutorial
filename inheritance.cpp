#include <iostream>

class A {
public:
    explicit A();           // explicit has no effect without arguments
    virtual void f() = 0;   // abstract function
    virtual void q() { ans = 0.0; }     // virtual function
    virtual int n() { return 0; }       // virtual function
    double add(double x);                   // normal function
    double sub(double x) noexcept;          // normal function, no exceptions
protected:
    uint32_t mode;
private:
    double ans;
};

A::A() : ans(0.0), mode(0) {
}

double A::add(double x) {
    ans += x;
    return ans;
}

double A::sub(double x) noexcept {
    // if(ans == 0) { throw 1; }
    ans -= x;
    return ans;
}

class B : public A {
public:
    explicit B(uint32_t, uint32_t);     // explicit has no effect with more than 1 argument
    void f() override;
    void q() override;
    // int n() override final { return 1; }
    double calc(double x, double y) { return x + y; }
    // double calc(int x, int y) = delete;
    double calc(uint32_t x, uint32_t y) = delete;
};

B::B(uint32_t x, uint32_t y) : A() {
}

void B::f() {
    mode = 1;
}

void B::q() {
    mode = 2;
}

class C : public B {
public:
    C() : B(1, 1) {}
    int n() override { return 2; }  // can be overriden when not final in B
};

void test1() {
    C c;
    // std::cout << c.calc(1, 2) << std::endl;
    std::cout << c.calc(1.0f, 2.0f) << std::endl;
    // std::cout << c.calc(1UL, 2UL) << std::endl;
    // std::cout << c.calc(1L, 2L) << std::endl;
    std::cout << c.calc(1.0, 2.0) << std::endl;
}

void test2() {
    C * pc = new C();
    std::cout << pc->add(10) << std::endl;
    std::cout << pc->sub(5) << std::endl;
}

int main() {
    test1();
    test2();
    return 0;
}

