#include <iostream>

class X {
public:
    int x = 0;
    int y = 1;
    int z = 2;
    // X() : z(3), y(z), x(y) {}   // warning here, members are initialized in order of their declaration -> x, y, z
    X() : x(10), y(20), z(30) {}

    operator std::string() {
        return std::string("");
    }

    // data
    int q;

    // method
    void foo(std::string msg) {
        std::cout << "foo: " << msg << std::endl;
    }

    // static data
    static int Q;

    // static method
    static void Foo(std::string msg) {
        std::cout << "Foo: " << msg << std::endl;
    }
};
int X::Q;   // initialization of static data

void test() {
    X x;

    // call on object
    // no difference between non-static and static data and/or methods
    x.foo("foo1");
    x.q = 100;
    x.Foo("Foo1");

    // call on object with type name
    // no difference between non-static and static data and/or methods
    x.X::foo("foo2");
    x.X::q = 1000;
    x.X::Foo("Foo2");

    // call on type name
    X::Foo("Foo3 static");

    // note: C# style is different
    // obj::static_data
    // obj::static_method
    // obj.non_static_data
    // obj.non_static_method
    // ClassName(){} non-static data initialization constructor
    // static ClassName() {} static data initialization constructor
    // because of single inheritance only one base -> base.member syntax to access shadowed members
    // the access to shadowed member in C++ is done with full base type name and :: (see diamond.cpp)
}

int main() {
    test();
    return 0;
}

