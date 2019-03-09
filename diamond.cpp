#include <iostream>
#include <iomanip>

using namespace std;

// classical diamond
class A {
public:
    uint16_t u8 = 1;
};

class B1 : public A {
};

class B2 : public A {
};

class C : public B1, public B2 {
};

[[nodiscard]]   // warns when applied to function returning void
int test1() {
    C c;
    cout << c.B1::u8 << endl;
    cout << c.B2::u8 << endl;
    return 0;
}

// diamond plus base
class D : public B1, public B2 {};    // remove warning
// class D : public B1, public B2, public A {};    // warns that base A is inaccessible
// class D : public B1, public B2, protected A {};    // warns that base A is inaccessible
// class D : public B1, public B2, private A {};    // warns that base A is inaccessible

void test2() {
    D d;
    cout << d.B1::u8 << endl;
    cout << d.B2::u8 << endl;
    // cout << d.A::u8 << endl; // error
}

// access syntax
class E : public A {
public:
    uint16_t u8 = 2;
};

void test3() {
    // E e {u8 = 1; };
    E e {};
    cout << e.A::u8 << endl;
    cout << e.u8 << endl;
}

//

int main() {
    (void)test1();  // cast to void because of [[nodiscard]] attribute
    test2();
    test3();
    return 0;
}

