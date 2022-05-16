# Deno FFI

ffi 支援 i8,i16,...,u8,u16,...,usize,f32,f64,void,pointer (const uint8_t *) 與 global static.

* https://deno.land/manual/runtime/ffi_api
    * https://deno.com/blog/v1.13#experimental-ffi-replaces-native-plugin-system
    * https://deno.com/blog/v1.15#ffi-improvements
    * https://deno.com/blog/v1.17#updates-to-the-ffi-api
    * https://deno.com/blog/v1.20#ffi-api-supports-read-only-global-statics

* https://deno.land/x/sqlite3@0.4.2/src/ffi.ts

* https://medium.com/deno-the-complete-reference/
    * [Calling C functions from Deno — Part 1 Passing primitive types](https://medium.com/deno-the-complete-reference/foreign-function-interface-calling-c-functions-from-deno-357ec4f5f793)
    * [Calling C functions from Deno: Part 2 — Pass buffers](https://medium.com/deno-the-complete-reference/calling-c-functions-from-deno-part-2-pass-buffers-ad168a3b6cc7)
    * [Calling C functions from Windows DLL in Deno — Part 1 Primitive types](https://medium.com/deno-the-complete-reference/calling-c-functions-from-windows-dll-in-deno-part-1-primitive-types-b4812ea327f5)
    * [Calling C functions from Windows DLL in Deno — Part 2 Buffers](https://medium.com/deno-the-complete-reference/calling-c-functions-from-windows-dll-in-deno-part-2-buffers-131226acd3d2)


## example

* [Calling C functions from Deno: Part 2 — Pass buffers](https://medium.com/deno-the-complete-reference/calling-c-functions-from-deno-part-2-pass-buffers-ad168a3b6cc7)

denoFfiTest.cc

```cpp
#include <stdio.h>
extern "C" char* toAndFroBuffer(void* buf) {
  printf("RECEIVED IN C SPACE => %s\n", (char*) buf);
  return (char*) "Hello back from C space";
}
```

compile

```
$ g++ -c denoFfiTest.cc
$ g++ -dynamiclib -fPIC -o denoFfiTest.dylib denoFfiTest.o
```


```js
const libName = "denoFfiTest.dylib";
const dylib = Deno.dlopen(libName, {
  "toAndFroBuffer": { parameters: ["pointer"], result: "pointer" },
});
const buffer = new TextEncoder().encode("Hello coming from Deno space");
const ret = dylib.symbols.toAndFroBuffer(buffer);
const dataView = new Deno.UnsafePointerView(ret);
console.log("RECEIVED IN DENO SPACE => ", dataView.getCString());
```

run

```
> deno run --allow-all --unstable app.ts 
RECEIVED IN C SPACE => Hello coming from Deno space
RECEIVED IN DENO SPACE =>  Hello back from C space
```