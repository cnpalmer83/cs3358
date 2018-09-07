#include <iostream>
#include <cstdlib>
#include "bag1.h"
#include "bag.cpp"
using namespace std;
using namespace c_palmer_bag1;

// PROTOTYPES //
void get_ages(Bag& age);
void check_ages(Bag& age);


int main()
{
   Bag ages;

   //get_ages(ages);
   //check_ages(ages);
   cout << "May your family live long and prosper." << endl;
   return EXIT_SUCCESS;
}


void get_ages(Bag& age)
{
   int user_input;

   cout << "Type the ages in your family." << endl;
   cout << "Type a negative number when you are done:" << endl;
   cin >> user_input;

   while (user_input >= 0)
   {
      if (age.size() < age.CAPACITY)
         age.insert(user_input);
      else
         cout << "I have no more room for that age." << endl;
      cin >> user_input;
   }
}  // END GET_AGES()


void check_ages(Bag& age)
{
   int user_input;

   cout << "Type those ages again.  Press return after each age:" << endl;
   while (age.size() > 0)
   {
      cin >> user_input;
      if (age.erase_one(user_input))
         cout << "Yes, I've found that age and removed it." << endl;
      else
         cout << "No, that age does not exist in the bag!" << endl;
   }
}  // END CHECK_AGES()
