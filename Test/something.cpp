#include "something.h"

template <class T>
something<T>::something() {}

template <class T>
void something<T>::setSomething(const T& src)
{
   someData = src;
}

template <class T>
T something<T>::getSomething()
{
   return someData;
}
