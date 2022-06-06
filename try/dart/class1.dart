class Person {
    String name = '';
    int age = 0;

    Person(String name, int age) {
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
