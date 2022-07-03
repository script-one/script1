void main() { 
    person('ccc', 52, 'teacher');
    person('george', 8);

}

person([name, age, job="none"]) { 
    print('name:'+name+' age='+age.toString()+' job='+job);
}