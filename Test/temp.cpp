#include "temp.h"

namespace nameTest
{
   template <class Item>
   temp<Item>::temp() {}

   template <class Item>
   void temp<Item>::setData(const Item& src)
   {
      data = src;
   }

   template <class Item>
   Item temp<Item>::getData()
   {
      return data;
   }
}
