#include <iostream>
#include <functional>
#include <cmath>

// value
void fx(int i) {
    std::cout << "value" << std::endl;
}

// pointer
void fx(int * p) {
    std::cout << "pointer" << std::endl;
}

// lvalue reference
void fx(int & r) {
    std::cout << "lvalue ref" << std::endl;
}

/*
// rvalue reference
void fx(int && l) {
    std::cout << "rvalue ref" << std::endl;
}
*/

void test1() {
    int i = 0;
    // calling pointer (compiler sees all 4 overloads)
    std::nullptr_t null;
    fx(null);
    fx(nullptr);
    fx(&i);

    // compiler sees all 4 overloads and cannot select
    // fx(i);      // value, lvalue?
    // fx(int(i)); // value, rvalue?
    // fx(0);  // pointer, value, rvalue ref?

    // when int& overload commented out, then value called
    // when int overload commented out, then lvalue ref called
    // fx(i);  // comment out overloads

    // when int&& overload commented out, then value called
    // when int overload commented out, then rvalue ref called
    fx(0);  // comment out overloads

}

////////////////////////////////////////////////////////////////////////////////////////////////


auto sep = [](std::string msg, int n) -> void {
    // const std::string frame(static_cast<int>(std::ceil((80-2-msg.size())/2.0)), '*');
    const std::string frame((n-2-msg.size())/2, '*');
    std::cout << frame << " " << msg << " " << frame;
    if(msg.size() % n == 1) {
        std::cout << '*';
    }
    std::cout << std::endl;
};

// functional
std::function<int(int, int)> f = [](int x, int y) -> int { return x+y; };

void test_sep() {
    sep("A", 80);
    sep("AA", 80);
    sep("AAA", 80);
    sep("AAAA", 80);
    sep("A", 100);
    sep("AA", 100);
    sep("AAA", 100);
    sep("AAAA", 100);
    sep("A", 120);
    sep("AA", 120);
    sep("AAA", 120);
    sep("AAAA", 120);
}

void q(int * p) {
    std::cout << "pointer" << std::endl;
}

void test2() {
    q(0);           // when no int overload, then compiler calls pointer
    q(nullptr);     // explicit, calls pointer even when int overload defined
}

int main() {
    // test_sep();
    sep("TEST 1", 120);
    test1();
    sep("TEST 2", 120);
    test2();
    return 0;
}

