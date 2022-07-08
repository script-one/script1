#include <iostream> 
#include <string> 
using namespace std; 

int main() { 
    string str1; 
    string str2("caterpillar"); 
    string str3(str2); 

    // assign: 指定字串 
    str1 = str1.assign(str2, 0, 5); 
    cout << "str1: " << str1 << endl; 
    str1 = str1.assign("caterpillar", 5, 6); 
    cout << "str1: " << str1 << endl; 

    str1 = ""; 

    // append: 字串串接 
    str1 = str1.append(str2, 0, 5); 
    str1 = str1.append(str3, 5, 6); 
    cout << "str1: " << str1 << endl; 

    // find: 尋找字串位置 
    cout << "尋找str1中的第一個pill: " 
         << str1.find("pill", 0) << endl; 

    // insert: 插入字串 
    cout << "在str1插入字串***: " 
         << str1.insert(5, "***") << endl; 

    cout << "str1長度: " << str1.length() << endl; 
 
    return 0; 
}