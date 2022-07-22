# generator / yield

* [In-depth understanding of Generators](https://cdn.jsdelivr.net/gh/b0xt/sobyte-images/2022/05/15/33fab37fc19e45d5a27e5c212fee7c2e.png) (有深入實作原理)

```js
function* example() {
  yield 1;
  yield 2;
  yield 3;
}
var iter = example();
iter.next();
```

展開後變成

```js
var marked0$0 = [example].map(regeneratorRuntime.mark);
function example() {
  return regeneratorRuntime.wrap(
    function example$(context$1$0) {
      while (1)
        switch ((context$1$0.prev = context$1$0.next)) {
          case 0:
            context$1$0.next = 2;
            return 1;

          case 2:
            context$1$0.next = 4;
            return 2;

          case 4:
            context$1$0.next = 6;
            return 3;

          case 6:
          case 'end':
            return context$1$0.stop();
        }
    },
    marked0$0[0],
    this
  );
}
var iter = example();
iter.next();
```

其背後還有一堆實作

```js
runtime.mark = function(genFun) {
  if (Object.setPrototypeOf) {
    Object.setPrototypeOf(genFun, GeneratorFunctionPrototype);
  } else {
    genFun.__proto__ = GeneratorFunctionPrototype;
  }
  genFun.prototype = Object.create(Gp);
  return genFun;
};

runtime.wrap = function(innerFn, outerFn, self, tryLocsList) {
  // If outerFn provided, then outerFn.prototype instanceof Generator.
  var generator = Object.create((outerFn || Generator).prototype);
  var context = new Context(tryLocsList || []);

  // The ._invoke method unifies the implementations of the .next,
  // .throw, and .return methods.
  generator._invoke = makeInvokeMethod(innerFn, self, context);

  return generator;
};

// Helper for defining the .next, .throw, and .return methods of the
// Iterator interface in terms of a single ._invoke method.
function defineIteratorMethods(prototype) {
  ['next', 'throw', 'return'].forEach(function(method) {
    prototype[method] = function(arg) {
      return this._invoke(method, arg);
    };
  });
}

function makeInvokeMethod(innerFn, self, context) {
  var state = GenStateSuspendedStart;

  return function invoke(method, arg) {
    ...

  }
}

var record = tryCatch(innerFn, self, context);

function tryCatch(fn, obj, arg) {
  try {
    return { type: 'normal', arg: fn.call(obj, arg) };
  } catch (err) {
    return { type: 'throw', arg: err };
  }
}

var record = tryCatch(innerFn, self, context);
if (record.type === "normal") {
  // If an exception is thrown from innerFn, we leave state ===
  // GenStateExecuting and loop back for another invocation.
  state = context.done
    ? GenStateCompleted
    : GenStateSuspendedYield;

  var info = {
    value: record.arg,
    done: context.done
  };
```


## 參考

* https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/yield

