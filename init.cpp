#include <iostream>

class A {
public:
protected:
private:
};

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct S {
    void print() const {
        std::cout << "x:" << x << ", y:" << y << ", z=" << z << std::endl;
    }
    u16 x;
    u16 y;
    u16 z;
};

void test1() {
    // A a1 {};
    // A a2 = A();
    //
    uint8_t u8 {};  // gcc warns shadowed typedef
    u8 = 0b11110000;
    u32 hex32 {0xFFFF0000};
    //
    S s1 {100,200,300};
    S s2 {10,20};
    S s3 {1};
    S s4 {};
    s1.print();
    s2.print();
    s3.print();
    s4.print();
}

int main() {
    test1();
    return 0;
}

