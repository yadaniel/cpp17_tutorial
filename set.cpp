#include <set>
#include <iostream>
#include <iomanip>
#include <cassert>

// requires gcc8
// #include <filesystem>

struct X {
    int v1;
    int v2;
    int v3;
};

struct XCmp {

    // needed for test2 (ordering within set)
    // inline int operator()(const X & fst, const X& snd) const {
    inline bool operator()(const X & fst, const X& snd) const {
        // std::cout << "." << std::boolalpha << (fst.v1 == snd.v1) << std::endl;
        // bool operator()(const X & fst, const X& snd) {
        // bool operator()(X & fst, X& snd) const {
        // warning => the specified comparator type does not provide a const call operator [-Wuser-defined-warnings]

        // Compare = std::less<Key>
        // operator must return bool ... true => include into set, false => do not include into set ... no further ordering (use std::sort)
        if(fst.v1 == snd.v1) {
            if(fst.v2 == snd.v2) {
                if(fst.v3 == snd.v3) {
                    return false;
                }
            }
        }
        return true;

        // if(fst.v1 == snd.v1) {
        //     if(fst.v2 == snd.v2) {
        //         if(fst.v3 == snd.v3) {
        //             // all equal, do not include into set
        //             // return 0;
        //             return false;
        //         } else {
        //             // decide on v3
        //             // return (fst.v3 < snd.v3) ? -1 : 1;
        //             return true;
        //         }
        //     } else {
        //         // decide on v2
        //         // return (fst.v2 < snd.v2) ? -1 : 1;
        //         return true;
        //     }
        // } else {
        //     // decide on v1
        //     // return (fst.v1 < snd.v1) ? -1 : 1;
        //     return true;
        // }

    }

};

// operator== is not used by std::set. Elements a and b are considered equal if !(a < b) && !(b < a)
// needed for test1
inline bool operator<(const X & fst, const X& snd) {
    // std::cout << "," << std::endl;
    return fst.v1 < snd.v1;
}

void test1() {
    std::set<X> xs;
    X x1 {1,2,3};
    X x2 {1,2,3};
    X x3 {1,2,3};
    X x4 {1,2,3};

    xs.insert(x1);
    xs.insert(x2);
    xs.insert(x3);
    xs.insert(x4);

    std::cout << "size = " << xs.size() << std::endl;
    assert(xs.size() == 1);
}

void test2() {
    std::set<X, XCmp> xs;
    X x1 {.v1=1, .v2=2, .v3=3};
    X x2 {.v1=1, .v2=2, .v3=3};
    X x3 {.v1=1, .v2=2, .v3=3};
    X x4 {.v1=1, .v2=2, .v3=3};

    xs.insert(x1);
    xs.insert(x2);
    xs.insert(x3);
    xs.insert(x4);

    std::cout << "size = " << xs.size() << std::endl;
    assert(xs.size() == 1);
}

void test3() {
    std::set<int> xs;

    for(int i=0; i<10; i++) {
        xs.insert(1);
    }
    xs.insert(1);
    xs.insert(1);
    xs.insert(1);
    xs.insert(1);

    std::cout << "size = " << xs.size() << std::endl;
    assert(xs.size() == 1);
}

void test4() {
    std::set<X, XCmp> xs;
    X x1 {.v1=1, .v2=2, .v3=3};
    X x2 {.v1=1, .v2=2, .v3=3};
    X x3 {.v1=2, .v2=1, .v3=3};
    X x4 {.v1=2, .v2=2, .v3=3};
    X x5 {.v1=3, .v2=2, .v3=3};
    X x6 {.v1=3, .v2=1, .v3=3};
    X x7 {.v1=4, .v2=2, .v3=1};
    X x8 {.v1=4, .v2=2, .v3=3};
    X x9 {.v1=5, .v2=2, .v3=3};
    X x10 {.v1=5, .v2=2, .v3=1};
    // size must be 9

    xs.insert(x1);
    xs.insert(x2);
    xs.insert(x3);
    xs.insert(x4);
    xs.insert(x5);
    xs.insert(x6);
    xs.insert(x7);
    xs.insert(x8);
    xs.insert(x9);
    xs.insert(x10);

    std::cout << "size = " << xs.size() << std::endl;
    assert(xs.size() == 9);

    for(auto x: xs) {
        std::cout << x.v1 << "," << x.v2 << "," << x.v3 << std::endl;
    }
}

void test5() {
    std::set<X, XCmp> xs;
    X x10 {.v1=1, .v2=2, .v3=3};
    X x9 {.v1=1, .v2=2, .v3=3};
    X x8 {.v1=2, .v2=1, .v3=3};
    X x7 {.v1=2, .v2=2, .v3=3};
    X x6 {.v1=3, .v2=2, .v3=3};
    X x5 {.v1=3, .v2=1, .v3=3};
    X x4 {.v1=4, .v2=2, .v3=1};
    X x3 {.v1=4, .v2=2, .v3=3};
    X x2 {.v1=5, .v2=2, .v3=3};
    X x1 {.v1=5, .v2=2, .v3=1};
    // size must be 9

    xs.insert(x1);
    xs.insert(x2);
    xs.insert(x3);
    xs.insert(x4);
    xs.insert(x5);
    xs.insert(x6);
    xs.insert(x7);
    xs.insert(x8);
    xs.insert(x9);
    xs.insert(x10);

    std::cout << "size = " << xs.size() << std::endl;
    assert(xs.size() == 9);

    for(auto x: xs) {
        std::cout << x.v1 << "," << x.v2 << "," << x.v3 << std::endl;
    }
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return EXIT_SUCCESS;
}

