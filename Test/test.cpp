#include <iostream>
#include <cstdlib>
#include <typeinfo>    // to determine Item primitive type
#include "something.h"
namespace nameTest = someKindOfLongNamespaceForNoReason;
using namespace std;
using namespace nameTest;

template <class T>
void show_list(nameTest::something<T> src);


int main(int argc, char* argv[])
{
   nameTest::something<char> obj1;
   nameTest::something<int> obj2;
   nameTest::something<string> obj3;

   obj1.setSomething('M');
   obj2.setSomething(3);
   obj3.setSomething(" Inc.");

   cout << obj2.getSomething();
   cout << obj1.getSomething();
   cout << obj3.getSomething() << endl;

   show_list(obj1);
   show_list(obj2);
   show_list(obj3);


   return EXIT_SUCCESS;
}
template <class T>
void show_list(nameTest::something<T> src)
{
   if (typeid(T).name() == typeid(int).name())
      cout << "Obj2 is an integer" << endl;
   if (typeid(T).name() == typeid(char).name())
      cout << "Obj1 is a character" << endl;
   if (typeid(T).name() == typeid(string).name())
      cout << "Obj3 is a string" << endl;

}

// TO COMPILE:
// $g++ test.cpp
// (Notice that something.cpp is not specified)
// $./a.out

// PROGRAM OUTPUT:
// 3M Inc.
