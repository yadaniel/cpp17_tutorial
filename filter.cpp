#include <iostream>
#include <cstdlib>
#include <ctime>        // not really needed
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <functional>   // function<rettype(argtype1)>
#include <algorithm>    // copy_if (functional analog to filter), copy_n (take), fill, for_each, transform (map)

using namespace std;

void test1() {
    vector<uint8_t> vec(100);  // set size and capacity, elements default initialized
    cout << "size=" << vec.size() << ", capacity=" << vec.capacity() << endl;
    for(auto v: vec) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;

    // change elements
    for(auto & v: vec) {
        v = 1;
    }
    for(auto v: vec) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;

    // change elements to random
    srand(time(nullptr));
    for(auto & v: vec) {
        v = rand() % 100;
    }
    for(auto v: vec) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;

    // filter out elements ... back_inserter
    vector<uint8_t> vec1;
    copy_if(vec.begin(), vec.end(), back_inserter(vec1), [](uint8_t v) {
        return v > 50;
    });
    cout << "copy_if ... ";
    for(auto v: vec1) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;
    vec1.clear();

    // filter out elements ... front_inserter
    // vector<uint8_t> vec2;    // no front_inserter
    // queue<uint8_t> q;        // no front_inserter
    list<uint8_t> lst;
    copy_if(vec.begin(), vec.end(), front_inserter(lst), [](uint8_t v) {
        return v > 50;
    });
    cout << "copy_if ... ";
    for(auto v: lst) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;
}

void test2() {
    vector<uint8_t> vec(10, 0xFF);    // set size and capacity, elements initialized with 0xFF
    srand(time(nullptr));
    for(auto & v: vec) {
        v = rand() % 100;
    }

    // copy_n
    vector<uint8_t> vec1;
    copy_n(vec.begin(), 5, back_inserter(vec1));
    cout << "original ... ";
    for(auto v: vec) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl << "copy_n ... ";
    for(auto v: vec1) {
        cout << static_cast<uint16_t>(v) << ", ";
    }
    cout << endl;
}

void test3() {
    vector<uint8_t> vec(10);
    uint8_t cnt = 0;
    generate(vec.begin(), vec.end(), [&cnt]() -> uint8_t {
        return cnt++;
    });

    // for_each
    cout << "original ... ";
    for_each(vec.begin(), vec.end(), [](uint8_t v) {
        cout << static_cast<uint16_t>(v) << ", " ;
    });
    cout << endl;

    // transform
    vector<uint8_t> vec1(vec.size());
    transform(vec.begin(), vec.end(), vec1.begin(), [](uint8_t v) {
        return  v % 2;
    });

    // for_each
    cout << "transformed ... ";
    for_each(vec1.begin(), vec1.end(), [](uint8_t v) {
        cout << static_cast<uint16_t>(v) << ", " ;
    });
    cout << endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}

