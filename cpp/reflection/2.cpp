#include <iostream>
#include <string>
#include <tuple>
#include <utility>

// 用于存储字段名称和值
template <typename... Members>
class Reflectable {
public:
    template <std::size_t N>
    auto& get() {
        return std::get<N>(members_);
    }

    static constexpr std::size_t size() {
        return sizeof...(Members);
    }

protected:
    std::tuple<Members...> members_;
};

class MyClass : public Reflectable<int, std::string> {
public:
    MyClass() {
        members_ = std::make_tuple(10, "example");
    }
};

template <typename T>
void print_fields(T& obj) {
    constexpr std::size_t N = T::size();
    print_impl(obj, std::make_index_sequence<N>{});
}

template <typename T, std::size_t... I>
void print_impl(T& obj, std::index_sequence<I...>) {
    ((std::cout << "Field " << I << ": " << obj.template get<I>() << std::endl), ...);
}

int main() {
    MyClass obj;
    print_fields(obj);
    return 0;
}