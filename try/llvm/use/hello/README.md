# LLVM

## Install

```
$ sudo apt install llvm
$ sudo apt install clang
```

## Compile C into .ll file in Linux

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

## Compile C into .ll file in MacOS

1. gen LLVM IR
    - `-S` generate .ll(Human-readable)

        `$ clang -S hello.c -emit-llvm        // generate hello.ll`
    - `-c` generate .bc(Bitcode)

        `$ clang -c hello.c -emit-llvm        // generate hello.bc`

2. compile

    `$ gcc -S hello.ll -o hello.s         // compile hello.ll into hello.s`

3. assemble

    `$ gcc hello.s -o hello               // assemble hello.s into hello`

4. run

    `$ ./hello                         // console output: Hello!
`
