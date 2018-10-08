#ifndef TEMP_H
#define TEMP_H

namespace nameTest
{
   template <class Item>
   class temp
   {
   public:
      temp();
      void setData(const Item& src);
      Item getData();
   private:
      Item data;
   };
}

#include "test.cpp"
#endif
