#include <iostream>

using namespace std;

// make base class template and pass derived class into it
// thus the derived class is known inside the base class
// inside the method the object is casted back to derived
template <typename T>
class X {
private:
    int cnt = 0;
public:
    void foo() {
        cout << "X.foo() enter [" << cnt << "]" << endl;
        T * derived = static_cast<T*>(this);
        derived->foo();
        cout << "X.foo() exit  [" << cnt << "]" << endl;
        cnt += 1;
    }
};

class Y : public X<Y> {
public:
    void foo() {
        cout << "Y.foo()" << endl;
    }
};

void test() {
    Y y;            // the instance of derived class
    X<Y> * py = &y; // derived class instance through pointer to base
    X<Y> & ry = y;  // derived class instance through reference to base
    py->foo();      // dispatch on base type calls method from derived type
    ry.foo();       // dispatch on base type calls method from derived type
}

int main() {
    test();
    return 0;
}

