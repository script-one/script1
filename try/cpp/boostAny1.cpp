#include <boost/any.hpp>
#include <iostream>

using namespace std; 

int main()
{
  boost::any a = 1;
  a = 3.14;
  cout << "a=" << boost::any_cast<double>(a) << endl;
  a = true;
  cout << "a=" << boost::any_cast<bool>(a) << endl;
}
