#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
   string str1 = "Chad";
   string str2 = "chad";

   cout << str1[0] << endl;
   cout << str2[0] << endl;

   if (str1 == str2)
      cout << "strings match" << endl;
   else
      cout << "strings don't match" << endl;

   str2 = "dahC";

   if (str1 == str2)
      cout << "strings match" << endl;
   else
      cout << "strings don't match" << endl;

   return 0;
}
