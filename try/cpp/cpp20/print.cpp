/* from -- https://en.cppreference.com/w/cpp/concepts/same_as
wsl> g++-10 -std=c++20 -Wall print.cpp
wsl> ./a.out
Example: 3.14 : 42 : [a-Z]
*/
#include <concepts>
#include <iostream>
 
template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);
 
template<typename T>
concept IsPrintable = std::integral<T> || std::floating_point<T> ||
    IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;
 
void println(IsPrintable auto const ... arguments)
{
    (std::wcout << ... << arguments) << '\n';
}
 
int main() { println("Example : ", 3.14, " : ", 42, " : [", 'a', L'-', L"Z]"); }

