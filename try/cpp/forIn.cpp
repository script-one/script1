#include <iostream> 
#include <string> 
#include <vector>
#include <map>
using namespace std; 

int main() { 
    int x[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // Range-based for loop to iterate through the array.
    for( int y : x ) { // Access by value using a copy declared as a specific type.
                       // Not preferred.
        cout << y << " ";
    }
    cout << endl;

    // Iterating over whole array
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    for (auto i : v)
        std::cout << i << ' ';
      
    std::cout << '\n';

    // Printing keys and values of a map
    std::map <int, int> MAP({{1, 1}, {2, 2}, {3, 3}});
    for (auto i : MAP)
        std::cout << '{' << i.first << ", " << i.second << "}\n";
}
