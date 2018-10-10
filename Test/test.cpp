/*
   This program demonstrates template classes and some of the quirks
   that comes with the process.  A simple namespace demo is also
   included.  I discovered through other applications that it may also
   be useful to determine an object's primitive type that is defined at
   runtime for a template class.  This is experimented with using typeid()
   in the getInput method, but should probably be reserved for debugging
   purposes as it may create undesired outcomes and runtime overhead.

   TEMPLATING:
   As expected, the header file is included with the driver program.
   Unfortunately, the header file must also include the implementation.
   This can be done in two ways:
      1. Implementation can be explicitly defined in the header file
         below the class definition.  Congratulations, you've now revealed
         everything about your class to the end-user.
      2. You can #include the implementation file at the end of the
         definition as is done here.  You've now retained some aspects
         of encapsulation while taking advantages of the portability
         of template classes.

   Another quirk missing from this example involves class methods with a
   class return type.  If a method exists with a 'something<T>' return type,
   the implementation must be preceeded with the key word 'typename'. Example:

   template <class T>
   typename something<T>::value_type something<T>::someFunction()
   {
      T someValue;
      // do something
      return someValue;
   }

   Maybe I'll include the "why" along with an actual example at a later date.
   For now, this is just the way it is!

   Finally, compiling template classes differs from static class types. You will
   not be able to compile the class implementation and client files together...
   it won't work and you will pull your hair out combing through syntatically
   correct code looking for the problem.  You only need to compile the client!
   In simplest terms...

   $g++ test.cpp                    // This will compile this program
   $g++ something.cpp test.cpp      // This will NOT compile this program

   NAMESPACE:
   Namespace is a great tool for avoiding name conflicts in programs that
   utilize many libraries.  Suppose another library is included in this example
   that also has a class named 'something.'  Namespace allows us to parameterize
   the type to avoid compile time errors that will occure if the compiler thinks
   it is trying to define the same class twice (when they are actually different
   classes with the same name).
*/

#include <iostream>
#include <cstdlib>
#include <typeinfo>    // to determine Item primitive type in getInput
#include "something.h"
namespace nameTest = someKindOfLongNamespaceForNoReason;
using namespace std;
using namespace nameTest;

template <class T>
void getInput(nameTest::something<T> src);


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

   getInput(obj1);
   getInput(obj2);
   getInput(obj3);


   return EXIT_SUCCESS;
}
template <class T>
void getInput(nameTest::something<T> src)
{
   if (typeid(T) == typeid(int))
      cout << "Obj2 is of type int and takes valid integers" << endl;
   if (typeid(T) == typeid(char))
      cout << "Obj1 is of type char and takes valid chars" << endl;
   if (typeid(T) == typeid(string))
      cout << "Obj3 is of type string and takes valid strings" << endl;
   /*
   if (typeid(T).name() == typeid(int).name())
      cout << "Obj2 is an integer" << endl;
   if (typeid(T).name() == typeid(char).name())
      cout << "Obj1 is a character" << endl;
   if (typeid(T).name() == typeid(string).name())
      cout << "Obj3 is a string" << endl;
   */

}

// TO COMPILE:
// $g++ test.cpp
// (Notice that something.cpp is not specified)
// $./a.out
