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
         capacity = 1;
      data = new value_type[capacity];
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
      if (new_capacity < 1)                                          // Resize to 1 if new_capacity < 1
         new_capacity = 1;                                           // (invalid). Resize to used if
      if (new_capacity < used)                                       // new_capacity too small to store
         new_capacity = used;                                        // all elements. Otherwise, resize to
      capacity = new_capacity;                                       // specified new_capacity.
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

   void sequence::insert(const value_type& entry)                    // Resize by ~+25% if insufficient
   {                                                                 // elements exist for new entry.
      if (used == capacity)                                          // Insert entry before current_index
      {                                                              // or first element if end of list.
         size_type newSize = capacity * 1.25;
         (newSize == capacity) ? resize(capacity + 1) : resize(newSize);
      }
      if (!is_item())
         start();
      copy(&data[current_index], &data[used], &data[current_index + 1]);
      data[current_index] = entry;
      ++used;
   }

   void sequence::attach(const value_type& entry)                    // Resize by ~+25% if insufficient
   {                                                                 // elements exist for new entry.
      if (used == capacity)                                          // Insert entry after current_index
      {                                                              // or last element if end of list.
         size_type newSize = capacity * 1.25;
         (newSize == capacity) ? resize(capacity + 1) : resize(newSize);
      }
      advance();
      copy(&data[current_index], &data[used], &data[current_index + 1]);
      data[current_index] = entry;
      ++used;
   }

   void sequence::remove_current()                                   // If item exists at current_index,
   {                                                                 // remove it. Resize list to used if
      if (!is_item())                                                // capacity > 25% larger than used.
         return;
      copy(&data[current_index + 1], &data[used], &data[current_index]);
      --used;
      if (capacity > used * 1.25)
         resize(used);
   }

   sequence& sequence::operator=(const sequence& source)
   {
      if (this != &source)
      {
         value_type* newData = new value_type[source.capacity];
         for (size_type i = 0; i < source.used; ++i)                 // Allocate new list and fill with
            newData[i] = source.data[i];                             // elements in source list. Point
         delete [] data;                                             // *data to new list. Define the
         data = newData;                                             // remaining variables to equal
         used = source.size();                                       // source variable values.
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
      if (is_item())
         return data[current_index];
      else
         return data[used];
   }
}
