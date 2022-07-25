# C++

* https://www.geeksforgeeks.org/features-of-c-20/
* [Effective Modern C++](https://moodle.ufsc.br/pluginfile.php/2377667/mod_resource/content/0/Effective_Modern_C__.pdf)

* [山姆大叔談 C++](https://ithelp.ithome.com.tw/users/20120425/ironman/2507)

* [DAY 3：只能死一次，不能鞭屍，談 std::unique_ptr<T>，卷一](https://ithelp.ithome.com.tw/articles/10213866)

「Modern C++」的精神之一便是：

不再使用 RAW Pointer，不再使用 new/delete，全面改用 Smart Pointer 及輔具來管理物件。（不知道怎麼挑，就用 std::unique_ptr 吧）

* [DAY 6：Smart Pointer std::shared_ptr<T>，卷二](https://ithelp.ithome.com.tw/articles/10214337)
為什麼需要 std::make_shared？
「Modern C++」有一個寬鬆的要求：盡可能不要直接使用 new/delete 來建構物件或使用記憶體。遇到 new/delete 應該改用 std::make_unique 或者 std::make_shared 來取代。《Effective Modern C++》Item 21 有說明理由。

* [DAY 7：Modern C++ 要角，老語言回春的關鍵，談 auto/decltype，卷一](https://ithelp.ithome.com.tw/articles/10214472)

* [DAY 8：Modern C++ 要角，老語言回春的關鍵，談 auto/decltype，卷二](https://ithelp.ithome.com.tw/articles/10214680)

傳入一個型別、值或運算式（expression）給 decltype 即可獲得該傳入的東西其型別為何。舉幾個例子：

> decltype(1.0 + 1) the_double = 0.0;

C++14 進一步定義了 decltype(auto)，可用於函數的回傳型別定義，如此一來，便可確定函數定義與實際回傳型別吻合：

* [DAY 16：Structured Bindings](https://ithelp.ithome.com.tw/articles/10217358)

```cpp
struct TeaShopOwner {
    int         id;
    std::string name;
};

std::vector<TeaShopOwner> owners {{1, "COCO"}, {2, "1Shit"}};

// OLD
for (const auto& owner : owners) {
    printf("Owner id = %d\n", owner.id);
}

// Using Structured Binding
for (const auto& [id, _] : owners) {
    printf("Owner id = %d\n", id);
}
```

