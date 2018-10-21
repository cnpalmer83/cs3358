#include <iostream>
#include <cstdlib>
#include <array>
using namespace std;

typedef std::size_t size_type;
int recursionTest(const int a[], int n);

int main(int argc, char* argv[])
{
   int a[5] = {-2, -6, -5, -5, -15};
   int b[5] = {0, 4, 6, 3, 10};
   int c[1] = {0};
   //int b[0];

   cout << recursionTest(a, 5) << endl;
   cout << recursionTest(b, 5) << endl;
   cout << recursionTest(c, 1) << endl;
   //cout << recursionTest(b, 5) << endl;
   //cout << recursionTest(a, 5);
   //cout << recursionTest(b, 0);

   return EXIT_SUCCESS;
}

int recursionTest(const int a[], int n)
{
   if (n == 0)
      return -999;
   if (n == 1 && a[0] >= 0)
      return -999;
   if (n == 1 && a[0] < 0)
      return 0;
   //else
   //{
      int min = recursionTest(a, n-1);
      if (a[0] <= a[min+1])
         return 0;
      //if (a[n-1] < min && a[n-1] >= 0)
      //   return -999;
         //return a[n-1];
      else
      {
         //cout << "a[min + 1]: " << a[min + 1] << " ~";
         if (a[min + 1] >= 0)
            return -999;
         else
            //return (a[min + 1] >= 0) ? -999 : min+1;
            return a[min+1];
         //return 1+min;
      }
   //}



   //cout << "index [" << n-1 << "] (n-1) has integer " << a[n-1] << endl;
   //return recursionTest(a, n - 1);
}
