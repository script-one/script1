# Script1

Script1 is a programming language that can be translated into JavaScript / Python and Dart. 

Programmer have to learn so many languages to build program run at different platform. Why cann't we use only one language ?

That's why we build s1, a tool to translate script1 into JavaScript / Python and Dart. 

If you write code in script1, you may use s1 to translate your code into JavaScript for web, Python for machine learning, and Dart for mobile app.

## Install

1. Install deno + python + dart
2. run install.sh once before compile & run

## compile & run

### S1 => JavaScript

* convert *.s1 to *.js
* use deno to run *.js

```
$ ./s1 -m hello.s1 -o hello.js
$ deno run hello.js
hello script1
```

### S1 => Python

* convert *.s1 to *.py
* use python to run *.py

```
$ ./s1 -m hello.s1 -o hello.py
$ python hello.py
hello script1
```

### S1 => Dart

* convert *.s1 to *.dart
* use dart to run *.dart

```
$ ./s1 -m hello.s1 -o hello.dart
$ dart hello.dart
hello script1 
```

## test

```js
$ ./test.sh
++ set -e      
++ ./install.sh
+++ set -e
+++ export S1HOME=/c/ccc111/script1
+++ S1HOME=/c/ccc111/script1
+++ export PYTHONPATH=/c/ccc111/script1/sys/
+++ PYTHONPATH=/c/ccc111/script1/sys/       
+++ dart pub get
Resolving dependencies...
Got dependencies!
++ ./runs1.sh hello
== JavaScript ==
hello script1
== Python ==
hello script1
== Dart ==
hello script1      
++ ./runs1.sh while
== JavaScript ==
sum(10)= 55
== Python ==
sum(10)= 55
== Dart ==
sum(10)= 55      
++ ./runs1.sh sum
== JavaScript ==
sum(10)= 55
== Python ==
sum(10)= 55
== Dart ==
sum(10)= 55      
++ ./runs1.sh fn
== JavaScript ==
inc(2)= 3
add(2,3)= 5
== Python ==
inc(2)= 3
add(2,3)= 5
== Dart ==
inc(2)= 3      
add(2,3)= 5
++ ./runs1.sh for
== JavaScript ==
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
== Python ==
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
== Dart ==
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
++ ./runs1.sh if
== JavaScript ==
max(3,5)= 5
min(3,5)= 3
== Python ==
max(3,5)= 5
min(3,5)= 3
== Dart ==
max(3,5)= 5      
min(3,5)= 3
++ ./runs1.sh matrix
== JavaScript ==
a= [ [ 1, 2 ], [ 4, 5 ] ]
b= [ [ 1, 1 ], [ 1, 1 ] ]
== Python ==
a= [[1, 2], [4, 5]]
b= [[1, 1], [1, 1]]
== Dart ==
a= [[1, 2], [4, 5]]      
b= [[1, 1], [1, 1]]
++ ./runs1.sh map
== JavaScript ==
{ name: "ccc", age: 52 }
{ dog: "狗", cat: "貓", a: "一隻", the: "這隻", chase: "追", bite: "吃" }
== Python ==
{'name': 'ccc', 'age': 52}
{'dog': '狗', 'cat': '貓', 'a': '一隻', 'the': '這隻', 'chase': '追', 'bite': '吃'}
== Dart ==
{name: ccc, age: 52}       
{dog: 狗, cat: 貓, a: 一隻, the: 這隻, chase: 追, bite: 吃}
++ ./runs1.sh mt
== JavaScript ==
[ "一隻", "狗", "追", "一隻", "貓" ]
== Python ==
['一隻', '狗', '追', '一隻', '貓']
== Dart ==
[一隻, 狗, 追, 一隻, 貓]       
++ ./runs1.sh class
== JavaScript ==
[Function: Person]
ccc 52
Person { name: "ccc", age: 52 }
== Python ==
<class '__main__.Person'>
<__main__.Person object at 0x000002F489B79730>
<__main__.Person object at 0x000002F489B79730>
== Dart ==
Person       
ccc 52
ccc 52
++ ./runs1.sh global
== JavaScript ==
hello 你好!
x= 3
@x= 5
== Python ==
  File "C:\ccc111\script1\out\global.py", line 9
    global.x=5                                         # (5) 
          ^
SyntaxError: invalid syntax
== Dart ==
hello 你好!       
x= 3
@x= 5
++ ./runs1.sh cond
== JavaScript ==
max(3,5)= 5
== Python ==
max(3,5)= 5
== Dart ==
max(3,5)= 5      
++ ./runs1.sh try
== JavaScript ==
Error: Error
    at error (file:///C:/ccc111/script1/sys/js/base.js:39:12)
    at file:///C:/ccc111/script1/out/try.js:6:11
== Python ==
  File "C:\ccc111\script1\out\try.py", line 8
    throw error('Error')                           # (2) 
          ^
SyntaxError: invalid syntax
== Dart ==
Exception: Error       
++ ./runs1.sh lambda
== JavaScript ==
a= [ 1, 2, 3 ]
b= [ 1, 4, 9 ]
c= [ 2, 3, 4 ]
== Python ==
a= [1, 2, 3]
b= [1, 4, 9]
c= [2, 3, 4]
== Dart ==
a= [1, 2, 3]      
b= [1, 4, 9]
c= [2, 3, 4]
++ ./runs1.sh lambda
== JavaScript ==
a= [ 1, 2, 3 ]
b= [ 1, 4, 9 ]
c= [ 2, 3, 4 ]
== Python ==
a= [1, 2, 3]
b= [1, 4, 9]
c= [2, 3, 4]
== Dart ==
a= [1, 2, 3]      
b= [1, 4, 9]
c= [2, 3, 4]
++ ./runs1.sh lambda
== JavaScript ==
a= [ 1, 2, 3 ]
b= [ 1, 4, 9 ]
c= [ 2, 3, 4 ]
== Python ==
a= [1, 2, 3]
b= [1, 4, 9]
c= [2, 3, 4]
== Dart ==
a= [1, 2, 3]      
b= [1, 4, 9]
c= [2, 3, 4]
++ ./runs1.sh lambda
== JavaScript ==
a= [ 1, 2, 3 ]
b= [ 1, 4, 9 ]
c= [ 2, 3, 4 ]
== Python ==
a= [1, 2, 3]
b= [1, 4, 9]
c= [2, 3, 4]
== Dart ==
a= [1, 2, 3]      
b= [1, 4, 9]
c= [2, 3, 4]
++ ./libs1.sh obj
++ ./libs1.sh calculus
++ ./libs1.sh rnd
++ ./libs1.sh vector
++ ./libs1.sh file
++ ./libs1.sh guid
++ ./libs1.sh obj
++ ./runs1.sh _calllib
== JavaScript ==
rUnif(5,10)= 6.697968082249961
rInt()= 19
guid()= a6cf33ff-7e16-f4b5-70c4-79a8bb9b850f
diff(sin, PI/4)= 0.7067531099743674
dot([1,2,3], [1,1,1])= 6
obj2= { name: "snoopy", age: 3 }
== Python ==
rUnif(5,10)= 9.66511391381389
rInt()= 12
guid()= 81827462-2658-a50d-a304-21efbd3823df
diff(sin, PI/4)= 0.7067531099742563
dot([1,2,3], [1,1,1])= 6
obj2= {'name': 'snoopy', 'age': 3}
== Dart ==
rUnif(5,10)= 9.617655440706228      
rInt()= 11      
guid()= 973ad15f-c0f5-a648-173f-4bec4bc9ed02
diff(sin, PI/4)= 0.7067531099742563
dot([1,2,3], [1,1,1])= 6
obj2= {name: snoopy, age: 3}      
++ ./runjs.sh _copy
a= [ "a", 2 ]
b= [ "b1", [ "a", 2 ] ]
d= [ "b", [ "a", 1 ] ]
++ ./runjs.sh _math
sin(PI/4)= 0.7071067811865475
random()= 0.501383436341361
ln(E)= 1
++ ./runjs.sh _sha256
json= {
  "nonce": 0,
  "data": "john => mary $2.7"
}
digest= cde91f9fdaf2ad6d01d07bb2836f3f6640556232660faa3731c47ebf86683cb8
++ ./runjs.sh _datetime
2022-07-23T07:49:19.114Z
Sat Jul 23 2022 15:49:19 GMT+0800 (台北標準時間)
++ ./runjs.sh _regexp
[ "52", "166", "60" ]
[ "age:52", "height:166", "weight:60" ]
++ ./runjs.sh _fs
{
    "name":"snoopy",
    "age":3
}

{ name: "snoopy", age: 3 }
++ ./runjs.sh _sqlite
1 Peter Parker
2 Clark Kent
3 Bruce Wayne
++ ./runjs.sh _console
user: ccc
user= ccc
++ ./runjs.sh _server
start at : http://127.0.0.1:3001
```




