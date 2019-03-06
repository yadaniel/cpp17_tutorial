#include <iostream>
#include <iomanip>
#include <limits>
#include <tuple>

// container
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <string>
#include <bitset>

// container adapter
#include <stack>
#include <queue>

// pseudo container
// vector<bool> is overloaded template to store bool as 1bit

using namespace std;

// typedef string = basis_string<char>
// typedef wstring = basis_string<wchar>



void test_vector_bool() {
    vector<bool> vb;
}

void test_string() {
    string s;
    wstring ws;
}

void test_deque() {
}

void test_map() {
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

void test_hex() {
    cout << 0xff << endl;                       // 255
    cout << hex << 0xff << endl;                // 0xff
    cout << hex << uppercase << 0xff << endl;   // 0xFF
}

int main() {
    test_vector_bool();
    test_deque();
    test_string();
    test_queue();
    test_stack();
    test_map();
    test_bitset();
    test_hex();
    return 0;
}

