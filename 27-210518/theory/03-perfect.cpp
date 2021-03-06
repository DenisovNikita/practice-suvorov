#include <iostream>
#include <memory>
#include <utility>
#include <string>

void foo(int a, std::string b, int &c, std::unique_ptr<int> d, std::string &&e) {
    std::cout << a << " " << b << " " << c << " " << *d << " " << e << "\n";
    c++;
    e += "_spoiled";
}

// Подгоняем под вызов.
void call_foo(int &&a, std::string &b, int &c, std::unique_ptr<int> &&d, std::string &&e) {
    std::cout << "foo() started\n";
    foo(
        static_cast<int&&>(a),
        static_cast<std::string&>(b),
        static_cast<int&>(c),
        static_cast<std::unique_ptr<int>&&>(d),
        static_cast<std::string&&>(e)
    );
    std::cout << "foo() ended\n";
}

int main() {
    int x = 30;
    std::unique_ptr<int> y = std::make_unique<int>(40);
    std::string b("wow");
    std::string s("hello");
    call_foo(10, b, x, std::move(y), std::move(s));
    std::cout << "x=" << x << "\n";
    std::cout << "s=" << s << "\n";
}
