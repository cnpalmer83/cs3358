#ifndef BAG_H
#define BAG_H

namespace c_palmer_bag1
{
   class Bag
   {
   public:
      // TYPEDEFS and MEMBER CONSTANTS
      typedef int value_type;
      typedef std::size_t size_type;
      static const size_type CAPACITY = 30;

      // CONSTRUCTOR
      Bag() { used = 0; }

      // CONSTANT MEMBER FUNCTIONS
      size_type size() const;                         // returns number of items in bag
      size_type count(const value_type& target);      // returns number of copies of specific item in bag

      // MODIFICATION MEMBER FUNCTIONS
      void insert(const value_type& entry);           // places new item in bag
      bool erase_one(const value_type& target);       // returns true if specific item is in bag and erased (else false)
      size_type erase(const value_type& target);      // deletes all items in bag and returns number of items deleted
      void operator +=(const Bag& addend);

   private:
      value_type data[CAPACITY];                      // An array to store items
      size_type used;                                 // How much of the array is used
   };

   // NONMEMBER FUNCTIONS for the Bag class
   Bag operator +(const Bag& b1, const Bag& b2);   // overloads '+' to allow adding of type bag
   
} // END NAMESPACE GROUPING

#endif // BAG_H
