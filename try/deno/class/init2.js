let Person = class {
    static __init(name, age) {
        let p = new Person()
        p.name = name
        p.age = age
        return p
    }
}

let p2 =Person.__init("ccc", 52);
console.log(p2)
