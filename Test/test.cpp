#include <iostream>
#include <cstdlib>
#include "something.h"
namespace nameTest = someKindOfLongNamespaceForNoReason;
using namespace std;

int main(int argc, char* argv[])
{
   nameTest::something<char> obj;
   nameTest::something<int> obj2;
   nameTest::something<string> obj3;

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
