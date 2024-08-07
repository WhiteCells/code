// #include <iostream>
// #include <vector>

// template<class T>
// class Vector : public std::vector<T> {
// public:
//     Vector(const std::initializer_list<T> &init_list)
//         : std::vector<T>(init_list) {
//     }
//     Vector<T> &operator+(const Vector<T> &other) {
//         this->insert(this->end(), other.begin(), other.end());
//         return *this;
//     }
// };

// int main(int argc, char const *argv[]) {
//     Vector<int> v1 {1, 2, 3};
//     Vector<int> v2 {2, 3, 3};
//     Vector<int> v3 = v1 + v2;

//     for (const auto &v : v3) {
//         std::cout << v << " ";
//     }
//     return 0;
// }

#include <vector>
#include <iostream>

void push_back_Example() {
    std::vector<int> vec {1, 2, 3};
    vec.push_back(1);
}

void back_Example() {
    std::vector<int> vec {1, 2, 3};
    std::cout << vec.back() << std::endl;
}

int main(int argc, char *argv[]) {
    back_Example();
    return 0;
}