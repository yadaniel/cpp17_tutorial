#include <iostream>
#include <iomanip>
#include <limits>
#include <tuple>

// container
#include <vector>
#include <deque>
#include <list>
#include <set>      // set, multiset
#include <map>      // map, multimap
#include <string>   // string, wstring, basic_string
#include <bitset>   // bitset<int N>

// container adapter
#include <stack>
#include <queue>

using namespace std;

void test_vector_bool() {
    // vector<bool> is overloaded template to store bool as 1bit
    vector<bool> vb;
}

void test_string() {
    // typedef string = basis_string<char>
    // typedef wstring = basis_string<wchar>
    string s;
    wstring ws;

    // string conversion
    string strVal = std::to_string(12345);
    int intVal = std::stoi(strVal);
}

void test_vector() {
    // push_back, pop_back
    vector<int> v{0};
    v.reserve(100);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    cout << "vector: size=" << v.size() << ", capacity=" << v.capacity() << endl;
}

void test_deque() {
    // push_front, push_back
    // pop_front, pop_back
    // deque works with blocks of elements
    deque<int> dq;
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);
    dq.push_front(2);
    dq.push_front(1);
    dq.push_front(0);
    cout << "deque: ";
    for(int& v: dq) {
        cout << v << ", ";
    }
    cout << endl;
    //
    dq.pop_front();    // returns void
    dq.pop_back();     // returns void
}

void test_list() {
    // push_back, push_front
    // pop_back, pop_front
    // list works with prev, next pointers (memory overhead)
    list<int> lst;
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);
    lst.push_front(2);
    lst.push_front(1);
    lst.push_front(0);
    cout << "list: ";
    for(int& v: lst) {
        cout << v << ", ";
    }
    cout << endl;
    //
    lst.pop_front();    // returns void
    lst.pop_back();     // returns void
}

void test_set() {
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(1);
    s.insert(1);
    s.insert(1);
    cout << "set: ";
    for(auto x: s) {
        cout << x << ", ";
    }
    cout << endl;
    for(int i=0; i<=5; i++) {
        cout << "count(" << i << ")=" << s.count(i) << endl;
    }

    // multiset
    multiset<int> ms;
    ms.insert(1);
    ms.insert(2);
    ms.insert(3);
    ms.insert(4);
    ms.insert(5);
    ms.insert(1);
    ms.insert(1);
    ms.insert(1);
    cout << "multiset: ";
    for(auto x: ms) {
        cout << x << ", ";
    }
    cout << endl;
    for(int i=0; i<=5; i++) {
        cout << "count(" << i << ")=" << ms.count(i) << endl;
    }
}

void test_map() {
    std::map<uint16_t, std::string> m;
    m[1] = "1";
    m[2] = "2";
    m[3] = "3";
    m[4] = "4";
    m[5] = "5";
    for(auto & [key,value] : m) {
        cout << "map[" << key << "] = " << value << endl;
    }
}

void test_queue() {
}

void test_stack() {
}

void test_bitset() {
    bitset<32> bset1;   // default zero initialized
    bitset<32> bset2(0xFF00FF00);
    // bitset<8> bset3(string("1111_0000"));    // throws std::invalid_argument
    bitset<8> bset3(string("11110000"));
    // bitset<8> bset4(string("F"));    // throws std::invalid_argument

    bset1.set(0);   // index
    bset1[1] = 1;
    bset1[2] = 1;
    bset1[2] = 0;
    bset1.set(31);
    bset1.reset(31);
    // bset1.set(32);  // throws std::out_of_range

    cout << bset1 << endl;
    cout << bset2 << endl;
    cout << bset3 << endl;

    bset1 = 0xF00F;
    bset2 = 0xFFFF;
    cout << "0xF00F & 0xFFFF = " << (bset1 & bset2) << endl;
    cout << uppercase << hex << (bset1 & bset2).to_ulong() << endl;

}

void undefined() {
    vector<int> v{0,1,2,3,4,5,6,7,8,9};
    typedef vector<int>::iterator Iter;
    using I = vector<int>::iterator;

    I n = v.end();
    Iter m = v.end();

    n++;    // undefined behaviour
    m++;    // undefined behaviour

    // changing container invalidates iterator (possible reallocation)
    int * p = &v[9];
    cout << *p << endl;
    for(int i=10; i<1000; i++) {
        v.push_back(i);
    }
    int buffer[10] = {};
    int * q = new int[100];
    cout << *p << endl;     // undefined behaviour
    delete [] q;
}

void test_hex() {
    cout << 0xff << endl;                       // 255
    cout << hex << 0xff << endl;                // 0xff
    cout << hex << uppercase << 0xff << endl;   // 0xFF
}

int main() {
    // test_vector_bool();
    // test_vector();
    // test_deque();
    // test_string();
    // test_queue();
    // test_list();
    // test_stack();
    // test_set();
    test_map();
    // test_bitset();
    // test_hex();
    // undefined();
    return 0;
}

