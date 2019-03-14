#include <iostream>

using namespace std;

// implicit
class X {
private:
    int _i;
    double _d;
public:
    X() : _i(0), _d(0.0) {}
    X(int i) : _i(i), _d(0.0) {}
    X(double d) : _i(0), _d(d) {}
    operator int() {
        return _i;
    }
    operator double() {
        return _d;
    }
};

// explicit
class A {
private:
    int _i = 0;
    int _d = 0.0;
public:
    explicit A() {}
    explicit A(int i) : _i(i) {}
    explicit A(double d) : _d(d) {}
    operator int() {
        return _i;
    }
    operator double() {
        return _d;
    }
};

void takeX(X x) {
    cout << int(x) << ":" << double(x) << endl;
}

void takeA(A a) {
    cout << int(a) << ":" << double(a) << endl;
}

void test1() {
    X x;
    X xi(1);
    X xd(1.0);
    X xi1 = 1;
    X xd1 = 1.0;
    takeX(x);
    takeX(2);
    takeX(2.0);

    A a;
    A ai(1);
    A ad(1.0);
    // A ai1 = 1;       // not possible because A can be constructed only explicitly from int
    // A ad1 = 1.0;     // not possible because A can be constructed only explicitly from double
    takeA(a);
    // takeA(2);        // not possible because A can be constructed only explicitly from int
    // takeA(2.0);      // not possible because A can be constructed only explicitly from double
}

int main() {
    test1();
    return 0;
}

