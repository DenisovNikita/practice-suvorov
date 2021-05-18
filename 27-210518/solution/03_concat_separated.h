#ifndef CONCAT_SEPARATED_H
#define CONCAT_SEPARATED_H

#include <sstream>
#include <string>
#include <string_View>
#include <tuple>
#include <utility>

namespace cls_27 {
#if 1  // Recursive solution (C++11)
namespace impl {
void append_separated(bool, std::stringstream &, std::string_view) {
}

template<typename Arg, typename ...Args>
void append_separated(bool first, std::stringstream &s, std::string_view sep, const Arg &arg, const Args &...args) {
    if (!first) s << sep;
    s << arg;
    append_separated(/*first=*/false, s, sep, args...);
}
}  // namespace impl

template<typename ...Args>
std::string concat_separated(std::string_view sep, const Args &...args) {
    std::stringstream s;
    impl::append_separated(/*first=*/true, s, sep, args...);
    return s.str();
}
#else  // Fold expression solution (C++17)
template<typename ...Args>
std::string concat_separated(std::string_view sep, const Args &...args) {
    std::stringstream s;
    bool first = true;
    auto print = [&](const auto &arg) {
        if (!first) s << sep;
        first = false;
        s << arg;
    };
    (print(args), ...);
    return s.str();
}
#endif

template<typename ...Args>
std::string concat_separated(std::string_view sep, const std::tuple<Args...> &t) {
    return std::apply(
        static_cast<std::string(*)(std::string_view, const Args&...)>(concat_separated),
        std::tuple_cat(std::tuple{sep}, t)
    );
}
}  // namespace cls_27

#endif  // CONCAT_SEPARATED_H
