# Cajson

Cajson is a programming language inspired by C and JavaScript. 

Programming language can be devided into strong typed and weak typed.

Strong typed language, such as C / C++ / C# / Java are hard to write but run fast.

Weak typed language, such as Python / JavaScript are easy to write but run slow.

Cajson try to extend weak typed syntax by set default value, so that compiler may inferred variable type automatically.

If the type information is enough, Cajson will run as fast as C.

## run

1. convert *.cj to *.js
2. use deno to run *.js

```
$ ./cj prog/hello.cj -o out/hello.js
$ deno run out/hello.js
hello cj
```

## test

```
$ ./cj2js.sh
++ ./run.sh hello
hello cj
++ ./run.sh while
sum(10)= 55
++ ./run.sh sum
sum(10)= 55
++ ./run.sh fn
inc(2)= 3
add(2,3)= 5
++ ./run.sh for
5
4
3
2
1
5
4
3
2
1
1
3
5
7
9
1
3
4
5
++ ./run.sh if
max(3 5)= 5
++ ./run.sh array
mean([1 2 3 4 5])= 3
++ ./run.sh matrix
a= [ [ 1, 2 ], [ 4, 5 ] ]
b= [ [ 1, 1 ], [ 1, 1 ] ]
++ ./run.sh mt
[ "一隻", "狗", "追", "一隻", "貓" ]
```




