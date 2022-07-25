#include <iostream>
using namespace std;
int main() {
    cout << "Hello" << "你好" << endl;
}
/*
本程式在 windows 下會出現亂碼，但在 Linux 下則不會

$ g++ chinese.cpp
$ ./a
Hello雿末
$ wsl
wsl> g++ chinese.cpp
wsl> ./a
-bash: ./a: No such file or directory
wsl> ./a.out
Hello你好
*/