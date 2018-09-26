// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2018
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity)
      : used(0), current_index(used), capacity(initial_capacity)
   {
      if (capacity < 1)
         capacity = DEFAULT_CAPACITY;
      data = new value_type[capacity];
      current_index = used;
   }

   sequence::sequence(const sequence& source)
      : used(source.used), current_index(source.current_index), capacity(source.capacity)
   {
      data = new value_type[source.capacity];
      for (size_type i = 0; i < used; ++i)
         data[i] = source.data[i];
   }

   sequence::~sequence()
   {
      delete [] data;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      //   void resize(size_type new_capacity)
      //    Pre:  new_capacity > 0
      //    Post: The sequence's current capacity is changed to new_capacity
      //      (but not less that the number of items already on the sequence).
      //      The insert/attach functions will work efficiently (without
      //      allocating new memory) until this new capacity is reached.
      //    Note: If new_capacity is less than used, it will be made equal to
      //      to used (in order to preserve existing data). Thereafter, if Pre
      //      is not met, new_capacity will be adjusted to 1.
      if (new_capacity < 1)
         new_capacity = 1;
      if (new_capacity < used)
         new_capacity = used;
      if (new_capacity == used)
         new_capacity = new_capacity + 1;
      capacity = new_capacity;
      value_type *newData = new value_type[capacity];
      for (size_type i = 0; i < used; ++i)
         newData[i] = data[i];
      delete [] data;
      data = newData;
   }

   void sequence::start()
   {
      current_index = 0;
   }

   void sequence::advance()
   {
      if (is_item())
         ++current_index;
   }

   void sequence::insert(const value_type& entry)
   {
      if (used == capacity)
         resize(capacity * 1.25);
      if (!is_item())
         start();
      copy(&data[current_index], &data[used], &data[current_index + 1]);
      data[current_index] = entry;
      ++used;
   }

   void sequence::attach(const value_type& entry)
   {
      if (used == capacity)
         resize(capacity * 1.25);
      advance();
      copy(&data[current_index], &data[used], &data[current_index + 1]);
      data[current_index] = entry;
      ++used;
   }

   void sequence::remove_current()
   {
      //    Pre:  is_item returns true.
      //    Post: The current item has been removed from the sequence, and
      //      the item after this (if there is one) is now the new current
      //      item. If the current item was already the last item in the
      //      sequence, then there is no longer any current item.
      if (is_item())
      {
         if (current_index == used)
            start();
         else
            copy(&data[current_index + 1], &data[used], &data[current_index]);
         --used;
      }
   }

   sequence& sequence::operator=(const sequence& source)
   {
      if (this != &source)
      {
         value_type* newData = new value_type[source.capacity];
         for (size_type i = 0; i < source.used; ++i)
         {
            newData[i] = source.data[i];
         }
         delete [] data;
         data = newData;
         used = source.size();
         current_index = source.current_index;
         capacity = source.capacity;
      }
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }

   bool sequence::is_item() const
   {
      if (current_index < used)
         return true;
      else
         return false;
   }

   sequence::value_type sequence::current() const
   {
      //   value_type current() const
      //    Pre:  is_item() returns true.
      //    Post: The item returned is the current item in the sequence.
      return data[current_index];
   }
}
