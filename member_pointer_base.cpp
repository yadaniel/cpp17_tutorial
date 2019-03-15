#include <iostream>

class A1 {
public:
    void afoo() {}
    void abar() {}
    int a_pub1;
    int a_pub2;
protected:
    int a_prot;
private:
    int a_priv;
};

class A2 {
public:
    void afoo() {}
    void abar() {}
    int a_pub1;
    int a_pub2;
protected:
    int a_prot;
private:
    int a_priv;
};

class B : public A1, public A2 {
public:
    void bfoo() {}
    void bbar() {}
    int b_pub1;
    int b_pub2;
protected:
    int b_prot;
private:
    int b_priv;
};

using BInt = int B::*;
using BMethod = void (B::*)();

void test() {
    B b1, b2;
    int * pi1 = &b1.A1::a_pub1;  // pointer to concrete int variable of object instance b
    int * pi2 = &b1.A2::a_pub1;  // pointer to concrete int variable of object instance b

    BInt bInt;
    BMethod bMethod;

    bInt = &B::b_pub1;      // object instance is missing
    b1.*bInt = 0;           // object instance supplied ... b1.b_pub1 changed
    bInt = &B::b_pub2;      // object instance is missing
    b2.*bInt = 0;           // object instance supplied ... b2.b_pub2 changed

    bMethod = &B::bfoo;     // object instance is missing
    (b1.*bMethod)();        // object instance supplied ... b1.bfoo called
    bMethod = &B::bbar;
    (b2.*bMethod)();        // object instance supplied ... b2.bbar called

    // now for base
    bInt = &A1::a_pub1;
    b1.*bInt = 100;     // this works, a_pub1 is part of B
    bInt = &A2::a_pub2;
    b1.*bInt = 100;     // this works, a_pub2 is part of B

    bMethod = &A1::afoo; // this works, a_afoo is part of B
    (b1.*bMethod)();
    bMethod = &A2::abar; // this works, a_abar is part of B
    (b1.*bMethod)();
}

int main() {
    test();
    return 0;
}

