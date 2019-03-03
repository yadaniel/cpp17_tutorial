#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct X {
    // pointer for functions
    typedef void (*F1)();   // old style
    using F2 = void(*)();   // new style

    // pointers for methods
    typedef void (X::*F3)();    // old style
    using F4 = void (X::*)();   // new style

    // pointer for members
    typedef int (X::*M1);       // old style
    using M2 = int (X::*);      // new style

    // more usefull chaining method pointer
    using Action = const X & (X::*)() const;
    using Apply = X & (X::*)(int);

    // and some methods with Action type
    const X & foo() const {
        cout << "foo" << endl;
        return *this;
    }

    const X & bar() const {
        cout << "bar" << endl;
        return *this;
    }

    // and some methods with Apply type
    X & add(int val) {
        value += val;
        return *this;
    }

    X & mult(int val) {
        value *= val;
        return *this;
    }

    // some members with M2 type
    int p = 1;
    int q = 10;
    int value = 0;

    vector<Action> actions;
    vector<tuple<Apply,int>> applies;

    void run_actions() const {
        for(auto action: actions) {
            (this->*action)();
        }
    }

    void run_applies() {
        for(auto [apply,val]: applies) {
            // do side-effects on this to modify the state for the next chained call
            (this->*apply)(val);
        }
    }
};

void test1() {
    X x, * px = &x;
    x.foo().bar().foo().bar();

    // simple usage
    X::Action a = &X::foo;
    (x.*a)();
    (px->*a)();

    x.actions.push_back(&X::foo);
    x.actions.push_back(&X::bar);
    x.actions.push_back(&X::foo);
    x.actions.push_back(&X::bar);
    x.run_actions();
}

void test2() {
    X x, * px = &x;
    x.add(10).mult(2).add(100).mult(3);
    cout << "value=" << x.value << endl;

    x.value = 0;    // reset value
    // x.applies.push_back(tuple<X::Apply,int>(&X::add, 10));
    // x.applies.push_back(tuple<X::Apply,int>(&X::mult, 2));
    // x.applies.push_back(tuple<X::Apply,int>(&X::add, 100));
    // x.applies.push_back(tuple<X::Apply,int>(&X::mult, 3));
    x.applies.push_back(tuple(&X::add, 10));
    x.applies.push_back(tuple(&X::mult, 2));
    x.applies.push_back(tuple(&X::add, 100));
    x.applies.push_back(tuple(&X::mult, 3));
    x.run_applies();
    cout << "value=" << x.value << endl;
}

int main() {
    // test1();
    test2();
    return 0;
}

