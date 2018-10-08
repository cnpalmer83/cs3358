#include <iostream>
#include <cstdlib>
#include "something.h"
//#include "something.cpp"
using namespace std;

int main(int argc, char* argv[])
{
   something<char> obj;
   something<int> obj2;
   something<string> obj3;

   obj.setSomething('M');
   obj2.setSomething(3);
   obj3.setSomething(" Inc.");

   cout << obj2.getSomething();
   cout << obj.getSomething();
   cout << obj3.getSomething() << endl;

   return EXIT_SUCCESS;
}
// TO COMPILE:
// $g++ test.cpp
// (Notice that something.cpp is not specified)
// $./a.out

// PROGRAM OUTPUT:
// 3M Inc.
