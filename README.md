# Script1

Script1 is a programming language that can be translated into JavaScript / Python and Dart. 

Programmer have to learn so many languages to build program run at different platform. Why cann't we use only one language ?

That's why we build s1, a tool to translate script1 into JavaScript / Python and Dart. 

If you write code in script1, you may use s1 to translate your code into JavaScript for web, Python for machine learning, and Dart for mobile app.

## run

1. convert *.s1 to *.js
2. use deno to run *.js

```
$ ./s1 prog/hello.s1 -o out/hello.js
$ deno run out/hello.js
hello script1
```

## test

```js
$ ./js_test.sh
++ ./js_run.sh hello
// source file: prog/hello.s1
import '../sys/s1.js'

let name='script1'                                 // (1) 
print('hello',name)                                // (2) 

hello script1
++ ./js_run.sh while
// source file: prog/while.s1
import '../sys/s1.js'

let sum=function (n) {                             // (1)
  let i=1                                          // (2)
  let s=0                                          // (3)
  while (i<=n)    {                                // (4)
    s=(s+i)                                        // (5)
    i=(i+1)                                        // (6)
  }                                                // (4)
                                                   // (4)
  return s                                         // (8)
}                                                  // (1)
print('sum(10)=',sum(10))                          // (11)

sum(10)= 55
++ ./js_run.sh sum
// source file: prog/sum.s1
import '../sys/s1.js'

let sum=function (n) {                             // (1)
  let s=0                                          // (2)
  for (let i=1;i<=n;i++) s=(s+i)                   // (3)
                                                   // (3)
  return s                                         // (4)
}                                                  // (1)
print('sum(10)=',sum(10))                          // (7)

sum(10)= 55
++ ./js_run.sh fn
// source file: prog/fn.s1
import '../sys/s1.js'

let inc=function (x) {                             // (1)
  return (x+1)                                     // (1)
}                                                  // (1)
let add=function (x,y) {                           // (3)
  return (x+y)                                     // (3)
}                                                  // (3)
print('inc(2)=',inc(2))                            // (5)
print('add(2,3)=',add(2,3))                        // (6)

inc(2)= 3
add(2,3)= 5
++ ./js_run.sh for
Error at line=15, pos=175. C halt at file=./src/parse.c line=315, tk=239(? 

++ ./js_run.sh if
// source file: prog/if.s1
import '../sys/s1.js'

let max=function (x,y) {                           // (1)
  if (x>y) return x                                // (1)
 else return y                                     // (1)
                                                   // (1)
}                                                  // (1)
print('max(3 5)=',max(3,5))                        // (3)

max(3 5)= 5
++ ./js_run.sh array
// source file: prog/array.s1
import '../sys/s1.js'

function mean(a) {                                 // (1)
  let s=0                                          // (2)
  for (let i in a) s=(s+a[i])                      // (3)
                                                   // (3)
  return (s/a.length)                              // (4)
}                                                  // (1)
print('mean([1 2 3 4 5])=',mean([1,2,3,4,5]))      // (7)

mean([1 2 3 4 5])= 3
++ ./js_run.sh matrix
// source file: prog/matrix.s1
import '../sys/s1.js'

let a=[[1,2],[4,5]]                                // (1)
let b=[[1,1],[1,1]]                                // (2)
print('a=',a)                                      // (4)
print('b=',b)                                      // (5)

a= [ [ 1, 2 ], [ 4, 5 ] ]
b= [ [ 1, 1 ], [ 1, 1 ] ]
++ ./js_run.sh mt
// source file: prog/mt.s1
import '../sys/s1.js'

let e2c={dog:'??,cat:'鞎?,a:'銝??,the:'?',chase:'餈?,bite:'??} // (1)      
let translate=function (ewords) {                  // (3)
  let cwords=[]                                    // (4)
  for (let e of ewords)    {                       // (5)
    cwords.push(e2c[e])                            // (6)
  }                                                // (5)
                                                   // (5)
  return cwords                                    // (8)
}                                                  // (3)
let c=translate(['a','dog','chase','a','cat'])     // (11)
print(c)                                           // (12)

[ "一隻", "狗", "追", "一隻", "貓" ]
++ ./js_run.sh global
// source file: prog/global.s1
import '../sys/s1.js'

global.print('hello 雿末!')                      // (1)
let x=3                                            // (3)
global.x=5                                         // (5)
print('x=',x)                                      // (7) 
print('@x=',global.x)                              // (8)

hello 你好!
x= 3
@x= 5
++ ./js_run.sh obj
// source file: prog/obj.s1
import '../sys/s1.js'

let ccc={name:'ccc',age:52,str:function () {       // (4)
  return ('name='+(this.name+(' age='+this.age)))  // (5)
}}                                                 // (1)
print(ccc.str())                                   // (9)

name=ccc age=52
++ ./js_run.sh import
// source file: prog/import.s1
import '../sys/s1.js'

import * as H from 'https://deno.land/std/hash/mod.ts' // (1)
function hash(text) {                              // (3)
  let h1=H.createHash('sha256')                    // (4)
  h1.update(text)                                  // (5)
  return str(h1)                                   // (6)
}                                                  // (3)
print('hash(hello)=',hash('hello'))                // (9)

hash(hello)= 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
++ ./js_run.sh sha256
// source file: prog/sha256.s1
import '../sys/s1.js'

import * as H from 'https://deno.land/std/hash/mod.ts' // (1)
function hash(text) {                              // (3)
  let h1=H.createHash('sha256')                    // (4)
  h1.update(text)                                  // (5)
  return str(h1)                                   // (6)
}                                                  // (3)
let record={nonce:0,data:'john => mary $2.7'}      // (9)
let json=JSON.stringify(record,null,2)             // (14)
print('json=',json)                                // (15) 
let digest=hash(json)                              // (17)
print('digest=',digest)                            // (18)

json= {
  "nonce": 0,
  "data": "john => mary $2.7"
}
digest= cde91f9fdaf2ad6d01d07bb2836f3f6640556232660faa3731c47ebf86683cb8
++ ./js_run.sh try
// source file: prog/try.s1
import '../sys/s1.js'

try  {                                             // (1)
  throw Error('Error')                             // (2)
}                                                  // (1)
 catch (error) {                                   // (3)
  print(error)                                     // (4)
}                                                  // (3)
                                                   // (1)

Error: Error
    at file:///C:/ccc111/code/C/script1/out/try.js:5:9
++ ./js_run.sh sqlite
// source file: prog/sqlite.s1
import '../sys/s1.js'

import * as sqlite from 'https://deno.land/x/sqlite/mod.ts' // (1)
let db=new sqlite.DB('test.db')                    // (4)
db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)') // (5)
let names=['Peter Parker','Clark Kent','Bruce Wayne'] // (7)
for (let name of names) db.query('INSERT INTO people (name) VALUES (?)',[name]) // (11)
                                                   // (10)
for (let r of db.query('SELECT id, name FROM people')) print(r[0],r[1]) // (15)
                                                   // (14)
db.close()                                         // (18)

1 Peter Parker
2 Clark Kent
3 Bruce Wayne
++ ./js_run.sh map
// source file: prog/map.s1
import '../sys/s1.js'

let ccc={name:'ccc',age:52}                        // (1)
print(ccc)                                         // (2)
let e2c={dog:'??,cat:'鞎?,a:'銝??,the:'?',chase:'餈?,bite:'??} // (4)      
print(e2c)                                         // (5)

{ name: "ccc", age: 52 }
{ dog: "狗", cat: "貓", a: "一隻", the: "這隻", chase: "追", bite: "吃" }
++ ./js_run.sh class
// source file: prog/class.s1
import '../sys/s1.js'

class Person {                                     // (2)
  constructor(name,age)   {                        // (2)
    this.name=name                                 // (3)
    this.age=age                                   // (4)
  }
                                                   // (6)
  __str()   {                                      // (6)
    return (this.name+(' '+this.age))              // (7)
  }
}                                                  // (1)
print(Person)                                      // (11)
let p=new Person('ccc',52)                         // (13)
print(str(p))                                      // (14)
print(p)                                           // (15)

[Function: Person]
ccc 52
Person { name: "ccc", age: 52 }
```




