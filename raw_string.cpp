#include <iostream>
#include <string>

int main() {
    std::string s1("foo\\bar");
    std::string s2(R"(foo\bar)");
    std::string s3(R"DELIM(foo\bar)DELIM");
    std::string s4(R"FOO(foo\bar)FOO");
    if(s1 == s2) {
        if (s3 == s4) {
            if (s1 == s3) {
                std::cout << "equal" << std::endl;
            }
        }
    }
    return 0;
}

