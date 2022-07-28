// ref -- 山姆大叔談 C++: https://ithelp.ithome.com.tw/articles/10213368
//        C++ Best Practices: https://github.com/cpp-best-practices/cppbestpractices
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <any>
#include <sstream>
#include <algorithm>
#include <functional>
#include <concepts>
using namespace std;

// variadic template : 參考 A Tour Of C++: 7.4 節
template<typename T, typename... Tail>
void log(T head, Tail... tail)
{
    cout << head << ' ';
    if constexpr(sizeof...(tail)>0) {
        log(tail...);
    } else {
        cout << endl;
    }
}

// 摺疊運算式 C++17: 參考 參考 A Tour Of C++: 7.4.1 節
/*
template<typename... T>
void log(T&&...args)
{
    (cout <<... << args) << '\n';
}
*/
/*
void log(auto a, string b="", string c="", string d="", string e="", string f="", string g="", string h="") {
  cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << " " << h << endl;
}
*/

// #define str(x) to_string(x)
#define str(x) ({ string s = stringstream() << x; s; })

#define len(x) x.size()

/*
template <typename T> string join(vector<T> v, string spliter) {
    string s;
    for (const T &x : v) {
        s += x;
        s += spliter;
    }
    return s;
}
*/

template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

template<typename T>
concept IsPrintable = std::integral<T> || std::floating_point<T> ||
    IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;

void println(IsPrintable auto const ... arguments)
{
    (std::wcout << ... << arguments) << '\n';
}

string join(IsPrintable auto v, string spliter) {
    stringstream ss;
    for (const any &x : v) {
        ss << x;
        ss << spliter;
    }
    string s;
    ss >> s;
    return s;
}

vector<int> range(int from, int to, int step=1) {
    vector<int> r;
    for (int i = from; i < to; i+=step)
        r.push_back(i);
    return r;
}

double epsilon = 0.0000001;
vector<double> drange(double from, double to, double step=1.0) {
    vector<double> r;
    for (double i = from; i < to-epsilon; i+=step)
        r.push_back(i);
    return r;
}

#define push(a, x) (a).push_back(x)

// 以下 each/map/Filter/Reduce 程式碼參考
// -- https://pgon.dev/blog/posts/building-map-filter-and-reduce-in-c-with-templates-and-iterators/

template <typename IteratorType>
using ItemType = typename std::iterator_traits<typename IteratorType::iterator>::value_type;

template <typename IteratorType>
void each(IteratorType &items, std::function<void(ItemType<IteratorType> &item)> forEachCb)
{
    for (typename IteratorType::iterator ptr = items.begin(); ptr != items.end(); ++ptr)
        forEachCb(*ptr);
}

template <typename IteratorType>
IteratorType map1(IteratorType &items, std::function<ItemType<IteratorType>(ItemType<IteratorType> &item)> mapCb)
{
    IteratorType mappedIterator;
    each<IteratorType>(items, [&mappedIterator, &mapCb](auto &item) { mappedIterator.push_back(mapCb(item)); });
    return mappedIterator;
}

template <typename IteratorType>
IteratorType filter(IteratorType &items, std::function<bool(ItemType<IteratorType> &item)> filterCb)
{
    IteratorType filteredIterator;
    each<IteratorType>(items, [&filteredIterator, &filterCb](auto &item) { if (filterCb(item)) filteredIterator.push_back(item); });
    return filteredIterator;
}

template <typename IteratorType, typename MemoType>
MemoType reduce(IteratorType &items, std::function<MemoType(ItemType<IteratorType> &item, MemoType &memo)> reduceCb, const MemoType &start)
{
    MemoType memo = start;
    each<IteratorType>(items, [&memo, &reduceCb](auto &item) { memo = reduceCb(item, memo); });
    return memo;
}
