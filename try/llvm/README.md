# LLVM

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
