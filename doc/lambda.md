# lambda

Python lambda 中的 block 不允許多個 statement，只允許有一個 exp

JavaScript/Dart 則可允許多個 statement

但要符合所有語言，應該取共同特性，也就是限縮到 Python 的 lambda 限制上，只允許有一個 exp。

這樣，對於 map, class 就得有下列限制


```
map = {
    key: exp,
    ....
}
```

exp 中只能放 lambda ，不能放整個函數。

```
class id {
    function *
}
```
