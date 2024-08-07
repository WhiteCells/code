#include <iterator>
#include <iostream>
#include <vector>

/*
<iterator>
  template<typename _InputIterator>
    _GLIBCXX_NODISCARD __attribute__((__always_inline__))
    inline _GLIBCXX17_CONSTEXPR
    typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
      // concept requirements -- taken care of in __distance
      return std::__distance(__first, __last,
			     std::__iterator_category(__first));
    }
第一个迭代器到第二个迭代器的距离
 */

void foo() {
    std::vector<int> v {1, 2, 3};
    std::vector<int>::iterator it1 = v.begin();
    std::cout << "it1 value: " << *it1 << std::endl;
    // std::vector<int>::iterator it2 = v.end() - 1;
    std::vector<int>::iterator it2 = v.begin();
    std::cout << "it2 value: " << *it2 << std::endl;
    std::cout << std::distance(it1, it2) << std::endl;
    std::cout << std::distance(it2, it1) << std::endl;
}

int main(int argc, char *argv[]) {
    foo();
    return 0;
}