
dynamic add(a,b) {
    return a+b;
}

dynamic main() {
    print('hello');
    print('add(2,3)='+add(2,3).toString());
    print('add(2.1,3)='+add(2.1,3).toString());
    print('add(hello,world)='+add('hello','world').toString());
}
