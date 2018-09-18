#include "IntSet.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
   IntSet is1;
   is1.add(1);
   is1.add(2);
   is1.add(3);

   IntSet is2;

   is2.add(1);
   is2.add(4);
   is2.add(5);

   cout << "sets 1 and 2 before subtract:" << endl;
   is1.DumpData(cout);
   cout << endl;
   is2.DumpData(cout);
   cout << endl;

   is1.subtract(is2);

   cout << "sets 1 and 2 after subtract:" << endl;

   is1.DumpData(cout);
   cout << endl;
   is2.DumpData(cout);
   cout << endl;

   return 0;
}
