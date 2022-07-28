// from -- https://stackoverflow.com/questions/56118941/do-we-have-c20-ranges-library-in-gcc-9

#include <vector>
#include <ranges>
#include <iostream>

int main()
{
  std::vector<int> ints{0,1,2,3,4,5,6};
  auto even = [](int i){ return 0 == i % 2; };
  auto square = [](int i) { return i * i; };

  for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
    std::cout << i << ' ';
  }
}