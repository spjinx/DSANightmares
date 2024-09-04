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
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <new>
using namespace std;

namespace CS3358_FA2023
{
    // === CONSTRUCTORS and DESTRUCTOR ===
   
   // Constructor with given capacity. Initializes a dynamic array of given size.
   sequence::sequence(size_t initial_capacity) : used(0), current_index(0), capacity(initial_capacity)
   {
      // Check PRE
      if(initial_capacity < 1){
      capacity = 1;}

      // DynSeqArray
      data = new value_type[capacity];
   }

   // Copy constructor. Initializes sequence from another sequence.
   sequence::sequence(const sequence& source) : used(source.used), current_index(source.current_index), capacity(source.capacity)
   {
      // dynArray
      data = new value_type[capacity];

      // copy
      for (size_t i = 0; i < used; ++i) 
      {
         data[i] = source.data[i];
      }
   }

   // Destruction
   sequence::~sequence()
   {
      // Begone!
      delete [] data;
      data = NULL;
   }


   // MODIFICATION MEMBER FUNCTIONS

   // Inflate
   void sequence::resize(size_t new_capacity)
   {
      // Valid! Resize
      if(new_capacity < 1){
         new_capacity = 1;}
      if(new_capacity < used) {
         capacity = used;}
      else {
         capacity = new_capacity;}

      // dynA, to new place
      value_type *temp_data = new value_type[capacity];
      for (size_t i = 0; i < used; ++i) {
         temp_data[i] = data[i];
      }

      // Goodbye!
      delete [] data;
      data = temp_data;
   }

   // Sets the current item to the first item in the sequence = 0.
   void sequence::start()
   {
      current_index = 0;
   }

   // Advances to the next item in the sequence.
   void sequence::advance()
   {
      // Assert can be used to protect.
      assert(is_item());
      current_index = current_index + 1;
   }

   // Inserts a new item before the current item, or at the start if no current item.
   void sequence::insert(const value_type& entry)
   {
      if(used == capacity){resize(size_t (1.5 * capacity) + 1);}

      if(!is_item()) {
         current_index = 0;
         for(size_t i = used + 1; i> current_index; --i){
            data[i] = data[i - 1];
         }

         data[current_index] = entry;
         ++used;

      } else {

         // Insert if existing item present
         for(size_t i = used + 1; i > current_index; --i){
            data[i] = data[i - 1];
         }

         data[current_index] = entry;
         ++used;
      }

   }

   // Appends a new item after the current item, or at the end if no current item.
   void sequence::attach(const value_type& entry)
   {
      // Checks
      if(used == capacity){
         resize(size_t (1.5 * capacity) + 1);
      }

      if(!is_item()){
         //Attatch
         data[current_index] = entry;
         used++;
      } else {
         //Append
         current_index = current_index + 1;
         for (size_t i = used + 1; i > current_index; --i) {
            data[i] = data[i-1];
         }

         data[current_index] = entry; // current_index + 1 = entry
         ++used;
      }
   }
   
   // Removes the current item from the sequence.
   void sequence::remove_current()
   {
      assert(is_item());

      // Valid current item. Remove current and shift items to the left.
      for (size_t i = current_index; i < used - 1; ++i) {
         data[i] = data[i + 1];
      }

      --used;
   }

   // Assignment operator. Assign sequence to other sequence
   sequence& sequence::operator=(const sequence& source)
   {
      // failsafe
      if (this == &source) return *this;

      value_type *temp_data = new value_type[source.capacity];

      for (size_t i = 0; i < source.used; ++i) {
         temp_data[i] = source.data[i];
      }

      // remove
      delete [] data;

      // replace
      data = temp_data;
      capacity = source.capacity;
      used = source.used;
      current_index = source.current_index;

      return *this;
   }


   // CONSTANT MEMBER FUNCTIONS

   // returns the number of items in the sequence
   sequence::size_type sequence::size() const
   {
      return used;
   }

   // checks if there's a valid item at current_index.
   bool sequence::is_item() const
   {
      return (current_index != used);
   }

   // return item in sequence at current_index.
   sequence::value_type sequence::current() const
   {
      // Assert can be used to protect.
      assert(is_item());

      return data[current_index];
   }
}