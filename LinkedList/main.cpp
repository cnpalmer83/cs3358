/*
   This fucking linked list doesn't work because of my failed attempt
   to implement templates.  Want it to work?  Remove the templates.
*/


#include <cstdlib>
#include "linkedlist.h"
#include "linkedlist.cpp"
using namespace std;

int main (int argc, char** argv) {

   LinkedList intList;
   intList.AddNode(3);
   intList.AddNode(4);
   intList.AddNode(5);

   intList.PrintList();

   return 0;
}
