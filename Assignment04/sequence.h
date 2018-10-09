// FILE: sequence.h

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstdlib>  // provides size_t

namespace CS3358_FA2018_A04_sequenceOfItem
{
   template <class Item>
   class sequence
   {
   public:
      // TYPEDEFS and MEMBER CONSTANTS
      typedef Item value_type;
      typedef size_t size_type;
      static const size_type CAPACITY = 10;
      // CONSTRUCTOR
      sequence();
      // MODIFICATION MEMBER FUNCTIONS
      void start();
      void end();
      void advance();
      void move_back();
      void add(const Item& entry);
      void remove_current();
      // CONSTANT MEMBER FUNCTIONS
      size_type size() const;
      bool is_item() const;
      Item current() const;

   private:
      Item data[CAPACITY];
      size_type used;
      size_type current_index;
   };
}
#include "sequence.cpp"

#endif
