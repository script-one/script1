class Person {
    var name;
    var age;

    Person(var name, var age) {
        this.name = name;
        this.age = age;
    }

    @override
    String toString() {
        return this.name+' '+this.age.toString();
    }
}

void main() {
    print(Person);
    var p=new Person('ccc', 52);
    print(p);
    print(p.toString());
}
