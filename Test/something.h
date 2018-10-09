#ifndef SOMETHING_H
#define SOMETHING_H

namespace someKindOfLongNamespaceForNoReason
{
   template <class T>
   class something
   {
   public:
      something();
      void setSomething(const T& src);
      T getSomething();
   private:
      T someData;
   };
}

#include "something.cpp"

#endif
