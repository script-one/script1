# web assembly

```
$ wat2wasm simple.wat -o simple.wasm
$ wat2wasm simple.wat -v
```

* https://webassembly.github.io/wabt/demo/wasm2wat/
* https://deno.land/manual@v1.8.3/getting_started/webassembly
* https://www.mirkosertic.de/blog/2018/01/object-oriented-webassembly/

## 簡介


* https://developer.mozilla.org/en-US/docs/WebAssembly/Understanding_the_text_format
* https://webassembly.github.io/spec/core/text/index.html
* https://en.wikipedia.org/wiki/S-expression
* https://www.tutorialspoint.com/webassembly/webassembly_text_format.htm

## 工具

* https://github.com/appcypher/awesome-wasm-runtimes
* https://github.com/WAVM/WAVM
    * WAVM uses LLVM to compile WebAssembly code to machine code with close to native performance.
* https://www.wasm.builders/gunjan_0307/compiling-javascript-to-wasm-34lk

## 範例

ex1a

```wast
(module
(func (param i32) (param i32) (local i32) (result i64) get_local 0
get_local 1
get_local 2
)
)
```

ex1b

```
(module
(func
(param $a i32)
(param $b i32)
(local $c i32)
(result i64) get_local $a get_local $b get_local $c
)
)
```

ex2:

```
(func (param $a i32) (param $b i32)
get_local $a
get_local $b
i32.add
)
```

ex3:

https://github.com/funcdef/fdvm

```
(module
    (func $log (import "env" "log") (param i32))
    (func $main
        i32.const 42
        (call $log)
    )
    (start $main)
)
$fdvm example.wasm
42
```