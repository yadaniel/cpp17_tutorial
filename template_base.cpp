#include <iostream>

using namespace std;

class A1 {
public:
    void foo() {
        cout << "A1.foo()" << endl;
    }
    static void Foo() {
        cout << "A1::Foo()" << endl;
    }
};

class A2 {
public:
    void foo() {
        cout << "A2.foo()" << endl;
    }
    static void Foo() {
        cout << "A2::Foo()" << endl;
    }
};

template <typename T>
class B : public T {
private:
    int cnt = 0;                // separate for each instance
    int static inline Cnt = 0;  // separate for each specialization
public:
    void foo() {
        cout << "B.foo() enter [" << cnt << "]" << endl;
        T::foo();
        cout << "B.foo() exit  [" << cnt << "]" << endl;
        cnt += 1;
    }
    static void Foo() {
        cout << "B.Foo() enter [" << Cnt << "]" << endl;
        T::Foo();
        cout << "B.Foo() exit  [" << Cnt << "]" << endl;
        Cnt += 1;
    }
};

template <typename T>
void user_of_class_B(B<T> & b) {
    b.foo();
    b.Foo();
}

// CXXFLAGS=-Wunused-result make
// nodiscard attribute will not be ignored
[[nodiscard]]
int test() {
    B<A1> b1;
    b1.foo();
    b1.Foo();
    A1 * pb1 = &b1;
    pb1->foo();  // A1.foo()
    //
    B<A2> b2;
    b2.foo();
    b2.Foo();
    A2 * pb2 = &b2;
    pb2->foo();  // A2.foo()
    //
    // b1,b2 derive from different bases, but present to it's users common interface
    user_of_class_B(b1);
    user_of_class_B(b2);

    return 0;
}

int main() {
    (void)test();  // nodiscard attribute will be now ignored
    return 0;
}

