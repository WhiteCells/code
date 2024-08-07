#include <iterator>
#include <iostream>
#include <vector>

/*
<iterator>
  template<typename _InputIterator, typename _Distance>
    __attribute__((__always_inline__))
    inline _GLIBCXX17_CONSTEXPR void
    advance(_InputIterator& __i, _Distance __n)
    {
      // concept requirements -- taken care of in __advance
      typename iterator_traits<_InputIterator>::difference_type __d = __n;
      std::__advance(__i, __d, std::__iterator_category(__i));
    }
迭代器移动指定的数量
 */

void foo() {
    std::vector<int> v {1, 2, 3};
    auto it1 = v.begin();
    std::cout << "it1 value: " << *it1 << std::endl;

    std::advance(it1, 1);
    std::cout << *it1 << std::endl;

    std::advance(it1, -1);
    std::cout << *it1 << std::endl;
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}