#include "s1.cpp"

int main() {
    log("hello ", "world!\n");
    for (auto i:range(2,7)) {
        cout << i << endl;
    }
    for (auto i:drange(0.0, 1.0, 0.1)) {
        cout << i << endl;
    }
    vector<int> a{ 10, 20, 30 };
    vector<int> b(a.begin(), a.end());
    for (auto i:b) {
        cout << i << endl;
    }

    // lambda
    auto add = [] (int x, int y) { return x + y; };
    cout << add(3,5) << endl;

    // map/filter/reduce
    // https://stackoverflow.com/questions/40901615/how-to-replicate-map-filter-and-reduce-behaviors-in-c-using-stl
    list<char> chars {'a', 'b', 'c', 'd'};
    vector<int> nums { 1, 2, 3, 4, 5 };
    string word { "Hello" };

    each<list<char>>(chars, [](char &chr){ cout << chr << endl; });
    each<vector<int>>(nums, [](int &num) { cout << num << endl; });
    each<string>(word,[](char &letter) { cout << letter << endl; });

    // auto mappedWord = map<string>(word, [](char &chr) { return static_cast<char>(chr + 1); });
    auto mappedWord = map<string>(word, [](char &chr) { return chr + 1; });
    cout << "map(word)=" << mappedWord << endl;

    auto mappedNums = map<vector<int>>(nums, [](int &x) { return x*x; });
    each<vector<int>>(mappedNums, [](int &x) { cout << x << endl; });

}
