let Person = class {
    constructor(name, age) {
        this.name = name
        this.age = age
    }

    static __init(name, age) {
        return new Person(name, age)
    }
}

let p = new Person("ccc", 52);
console.log(p)

let p2 =Person.__init("ccc", 52);
console.log(p2)
