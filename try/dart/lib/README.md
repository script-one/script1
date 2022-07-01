# dart library

* https://juejin.cn/post/6844903649617936392

Part与import有什么区别

可见性：
如果说在A库中import了B库，A库对B库是不可见的，也就是说B库是无法知道A库的存在的。而part的作用是将一个库拆分成较小的组件。两个或多个part共同构成了一个库，它们彼此之间是知道互相的存在的。

作用域：import不会完全共享作用域，而part之间是完全共享的。如果说在A库中import了B库，B库import了C库，A库是没有办法直接使用C库的对象的。而B,C若是A的part，那么三者共享所有对象。并且包含所有导入。

作者：Vadaski
链接：https://juejin.cn/post/6844903649617936392
来源：稀土掘金
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。