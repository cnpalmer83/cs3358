#include <iostream>
#include <cstdlib>
#include <algorithm>    // Provides copy function
#include <cassert>      // Provides assert function
#include "bag1.h"

namespace c_palmer_bag1
{
   const Bag::size_type Bag::CAPACITY;

   Bag::size_type Bag::erase(const value_type& target)
   {
      // SELF-TEST EXERCISE
   }

   Bag::size_type Bag::count(const value_type& target) const
   {
      size_type answer;
      size_type i;
      answer = 0;

      for (i = 0; i < used; ++i)
      {
         if (target == data[i])
            ++answer;
      }
      return answer;
   } // END COUNT()

   void Bag::insert(const value_type& entry)
   {
      assert(size() < CAPACITY);                // ??? Library facilities used: cassert ???
      data[used] = entry;
      ++used;
   } // END INSERT()

   bool Bag::erase_one(const value_type& target)
   // Postcondition: If target was in the bag, then one copy has been removed;
   // otherwise the bag is unchanged. A true return value indicates that one
   // copy was removed; false indicates that nothing was removed.
   {
      size_type index;     // The location of target in the data array
      index = 0;

      while ((index < used) && (data[index] != target))
         ++index;

      if (index == used)
         return false;     // target not in the bag.

      // If program reaches this point, target is in the bag (data[index]).  Decrement 'used'
      // and copy last item in the bag to the new hole in the array (data[index]).
      --used;
      data[index] = data[used];
      return true;
   } // END ERASE_ONE()

   void Bag::operator +=(const Bag& addend)
   // Precondition: size() + addend.size() <= CAPACITY
   // Postcondition: Each item in addend has been added to this bag
   // Library facilities used: algorithm, cassert
   {
      assert(size() + addend.size() <= CAPACITY);                 // Make sure there's room for everything
      copy(addend.data, addend.data + addend.used, data + used);  // Perform the copy procedure
      used += addend.used;                                        // Update used counter
   }

   Bag operator +(const Bag& b1, const Bag& b2)
   // Library facilities used: cassert
   {
      Bag answer;

      assert(b1.size() + b2.size() <= Bag::CAPACITY);

      answer += b1;
      answer += b2;
      return answer;
   }

} // END NAMESPACE GROUPING
