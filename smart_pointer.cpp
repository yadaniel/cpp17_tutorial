#include <iostream>
#include <iomanip>
#include <memory>
#include <limits>

// types
typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef float       f32;
typedef double      f64;
typedef long double f128;

template <typename T>
void print_type_info(std::string n) {
    n.resize(6, '.');   // returns void, fill char
    std::cout << n << ", size=" << std::setw(2) << sizeof(T) << ", char=" << typeid(T).name();
    if constexpr (std::is_same<T,i8>() || std::is_same<T,u8>()) {
        // work around non-printable chars and interpret values numerically
        std::cout << ", min=" << static_cast<i16>(std::numeric_limits<T>::min());
        std::cout << ", max=" << static_cast<i16>(std::numeric_limits<T>::max());
    } else {
        std::cout << ", min=" << std::numeric_limits<T>::min();
        std::cout << ", max=" << std::numeric_limits<T>::max();
    }
    std::cout << std::endl;
}

void print_type_sizes() {
    using namespace std;
    print_type_info<bool>("bool");
    print_type_info<i8>("i8");  // no macro-free way to convert T to string
    print_type_info<i16>("i16");
    print_type_info<i32>("i32");
    print_type_info<i64>("i64");
    print_type_info<u8>("u8");
    print_type_info<u16>("u16");
    print_type_info<u32>("u32");
    print_type_info<u64>("u64");
    print_type_info<f32>("f32");
    print_type_info<f64>("f64");
    print_type_info<f128>("f128");
}

// shared_ptr, unique_ptr, weak_ptr
//
//

struct S {
    inline static u16 cnt = 0;
    u16 id;
    S() : id(cnt++) {}
    ~S() {
        std::cout << "~S()" << std::endl;
    }
    void f() {
        std::cout << "f called on " << id << std::endl;
    }
};

// shared_ptr usage examples
//
//
void shared_ptr_usage() {
    std::shared_ptr<S> p1, p2;
    if(!p1) {
        std::cout << "not set"  << std::endl;
    }
    std::cout << p1.use_count() << std::endl;    // 0
    p1 = std::make_shared<S>();
    std::cout << p1.use_count() << std::endl;    // 1
    p2 = p1;
    std::cout << p1.use_count() << std::endl;    // 2
    std::cout << p2.use_count() << std::endl;    // 2
    S * s = p1.get();   // get raw pointer, count not decremented
    std::cout << p1.use_count() << std::endl;    // 2
    p1->f();
    p2->f();
    if(p1) {
        std::cout << "set"  << std::endl;
    }
    //
    S * s0 = new S();
    S * s1 = new S{};
    S * s2 = new S;
    delete s0;
    delete s1;
    s0 = s1 = nullptr;
    delete s0;          // ok, no double delete
    // delete nullptr;  // not compiling
    //
    S * s3 = new S{};
    std::shared_ptr<S> p3(s3);      // memory leak when S() throws an exception
    // std::shared_ptr<S> p4(s3);   // double delete
    std::shared_ptr<S> p4 = std::make_shared<S>();  // no memory leak when S() throws an exception
    p3->f();    // use -> for access to object API, use . for access to shared_ptr API
    p4->f();
}

void shared_ptr_usage2() {
    // manage array of type S
    std::shared_ptr<S> p(new S[10], [](S*ps) {
        delete [] ps;
    });
}

void use_shared_ptr(std::shared_ptr<S> p) {
    std::cout << p.use_count() << std::endl;    // 2
    p.reset();
    std::cout << p.use_count() << std::endl;    // 0
}
void shared_ptr_usage3() {
    std::shared_ptr<S> p = std::make_shared<S>();
    std::cout << p.use_count() << std::endl;    // 1
    use_shared_ptr(p);                          // use and reset
    std::cout << p.use_count() << std::endl;    // 1
}

// unique_ptr usage examples
//
//

void unique_ptr_usage() {
    std::unique_ptr<S> p(new S);
    if(p) {
        std::cout << "set" << std::endl;
    }
    p->f();
    p.release();
    if(!p) {
        std::cout << "not set" << std::endl;
    }
}

// weak_ptr usage examples
//
// TODO


int main() {
    print_type_sizes();
    shared_ptr_usage();
    shared_ptr_usage2();
    shared_ptr_usage3();
    unique_ptr_usage();
    return 0;
}

