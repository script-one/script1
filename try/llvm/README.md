# LLVM

## 參考文獻

* [Mapping High Level Constructs to LLVM IR](https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/a-quick-primer/index.html)
* [Getting Started with LLVM Core Libraries（中文版）](https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh_CN/latest/index.html)
    * [第3章 工具和设计 -- 使用独立工具](https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh_CN/latest/ch03.html#id4)
    * [第5章 LLVM中间表示](https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh_CN/latest/ch05.html#)
* [從 LLVM IR 來看編譯器最佳化都在做些什麼](https://medium.com/starbugs/see-what-compiler-optimization-do-from-llvm-ir-dfd3774292cb)
* [三段式LLVM编译器](https://www.cnblogs.com/wujianming-110117/p/15614228.html)
* [LLVM学习笔记 1-54](https://blog.csdn.net/wuhui_gdnt/category_6778926.html)
    * [LLVM - 学习笔记一](https://blog.csdn.net/qq_36287943/article/details/109626082)

## Install

```
$ sudo apt install llvm
$ sudo apt install clang
```

## Use

hello.c

```
wsl> clang -S hello.c -emit-llvm        // generate hello.ll

wsl> lli hello.ll                       // interpret hello.ll
Hello!

wsl> llc hello.ll                       // compile hello.ll into hello.s

wsl> gcc hello.s -o hello               // assemble hello.s into hello

wsl> ./hello                            // run hello
Hello!
```
