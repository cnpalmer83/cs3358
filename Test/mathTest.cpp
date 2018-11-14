#include <iostream>
#include <cstdlib>
using namespace std;

void getChildIndex(int n);
void getParentIndex(int n);

int main(int argc, char* argv[])
{
   cout << "Parent      = (n - 1) / 2" << endl;
   cout << "Left Child  = 2n + 1" << endl;
   cout << "Right Child = 2n + 2" << endl << endl;

   cout << "n = 1: " << endl;
   getChildIndex(1);
   getParentIndex(1);
   cout << endl;

   cout << "n = 3: " << endl;
   getChildIndex(3);
   getParentIndex(3);
   cout << endl;

   cout << "n = 4: " << endl;
   getChildIndex(4);
   getParentIndex(4);
   cout << endl;

   cout << "n = 5: " << endl;
   getChildIndex(5);
   getParentIndex(5);
   cout << endl;

   return EXIT_SUCCESS;
}

void getChildIndex(int n)
{
   cout << "Left: " << 2*n + 1 << "   " << "Right: " << 2*n + 2 << endl;
   return;
}

void getParentIndex(int n)
{
   cout << "Parent: " << (n - 1) / 2 << endl;
   return;
}
