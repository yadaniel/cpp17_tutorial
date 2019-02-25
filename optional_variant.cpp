#include <optional>
#include <variant>
#include <iostream>
#include <string>

namespace X::Y::Z {

std::optional<uint8_t> hasValue(std::string input) {
    if(input == "0" || input == "a") {
        return 0;   // implicit
    }
    if(input == "1" || input == "b") {
        return std::make_optional(1);   // explicit
    }
    if(input == "2" || input == "c") {
        return std::make_optional<uint8_t>(2);   // explicit
    }
    if(input == "3" || input == "d") {
        return std::optional<uint8_t>(3);   // explicit
    } else {
        return std::nullopt;    // explicit
    }
    return {};              // implicit
}

std::variant<uint8_t, uint8_t*> result(std::string input) {
    static uint8_t value = 100;
    if(input == "value") {
        return value;
    } else {
        return &value;
    }
}

}

int test_optional() {
    using namespace std;
    using namespace X::Y::Z;

    string input;
    cin >> input;

    // optional can be tested implicit
    if(hasValue(input)) {
        cout << "value returned" << endl;
    } else {
        cout << "optional returned" << endl;
    }

    // optional can be tested explicit
    if(hasValue(input).has_value()) {
        cout << "value returned" << endl;
    } else {
        cout << "optional returned" << endl;
    }

    return 0;
}

int test_variant() {
    using namespace std;
    using namespace X::Y::Z;

    string input;
    cin >> input;

    std::variant<uint8_t,uint8_t*> res = result(input);
    if(input == "value") {
        uint8_t x = std::get<0>(res);
        cout << "uint8_t ... " << static_cast<uint16_t>(x) << endl;
    } else {
        uint8_t* px = std::get<1>(res);
        cout << "uint8_t * ... " << static_cast<uint16_t>(*px) << endl;
    }

    // exception
    try {
        // static_case<uint16_t>(val) needed to print number and not char
        cout << "uint8_t ... " << static_cast<uint16_t>(std::get<0>(res)) << endl;  // get<0>
        cout << "uint8_t ... " << static_cast<uint16_t>(std::get<uint8_t>(res)) << endl;    // get<type>
        cout << "uint8_t * ... " << std::get<1>(res) << endl;
        cout << "uint8_t * ... " << std::get<uint8_t*>(res) << endl;
    } catch(std::bad_variant_access&) {
        cout << "bad_variant_access exception" << endl;
    }

    return 0;
}

int main() {
    test_optional();
    test_variant();
}
