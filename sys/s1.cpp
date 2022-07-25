// ref -- 山姆大叔談 C++: https://ithelp.ithome.com.tw/articles/10213368
//        C++ Best Practices: https://github.com/cpp-best-practices/cppbestpractices
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;

void log(auto a, string b="", string c="", string d="", string e="", string f="", string g="", string h="") {
  cout << a << b << c << d << e << f << g << h;
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

// 以下 ForEach/Map/Filter/Reduce 程式碼參考
// -- https://pgon.dev/blog/posts/building-map-filter-and-reduce-in-c-with-templates-and-iterators/

template <typename IteratorType>
using ItemType = typename std::iterator_traits<typename IteratorType::iterator>::value_type;

template <typename IteratorType>
void ForEach(IteratorType &items, std::function<void(ItemType<IteratorType> &item)> forEachCb)
{
    for (typename IteratorType::iterator ptr = items.begin(); ptr != items.end(); ++ptr)
        forEachCb(*ptr);
}

template <typename IteratorType>
IteratorType Map(IteratorType &items, std::function<ItemType<IteratorType>(ItemType<IteratorType> &item)> mapCb)
{
    IteratorType mappedIterator;
    ForEach<IteratorType>(items, [&mappedIterator, &mapCb](auto &item) { mappedIterator.push_back(mapCb(item)); });
    return mappedIterator;
}

template <typename IteratorType>
IteratorType Filter(IteratorType &items, std::function<bool(ItemType<IteratorType> &item)> filterCb)
{
    IteratorType filteredIterator;
    ForEach<IteratorType>(items, [&filteredIterator, &filterCb](auto &item) { if (filterCb(item)) filteredIterator.push_back(item); });
    return filteredIterator;
}

template <typename IteratorType, typename MemoType>
MemoType Reduce(IteratorType &items, std::function<MemoType(ItemType<IteratorType> &item, MemoType &memo)> reduceCb, const MemoType &start)
{
    MemoType memo = start;
    ForEach<IteratorType>(items, [&memo, &reduceCb](auto &item) { memo = reduceCb(item, memo); });
    return memo;
}
