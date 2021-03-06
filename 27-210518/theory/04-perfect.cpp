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
// reference collapsing.
using TA = int;           // TA&& == int&&
using TB = std::string&;  // TB&& == std::string&
using TC = int&;          // TC&& == int&
using TD = std::unique_ptr<int>;  // TD&& == std::unique_ptr<int>&&
using TE = std::string;   // TE&& == std::string&&

void call_foo(TA &&a, TB &&b, TC &&c, TD &&d, TE &&e) {
    std::cout << "foo() started\n";
    foo(
        static_cast<TA&&>(a),
        static_cast<TB&&>(b),
        static_cast<TC&&>(c),
        static_cast<TD&&>(d),
        static_cast<TE&&>(e)
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
