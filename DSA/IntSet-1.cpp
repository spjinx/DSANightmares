// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

// Resizes the internal data array to the given capacity.
void IntSet::resize(int new_capacity)
{
   capacity = (new_capacity <= 0) ? DEFAULT_CAPACITY : (new_capacity < used) ? used : new_capacity;

   int* new_data = new int[capacity];

   for(int index = 0; index < used; ++index) {
      new_data[index] = data[index];
   }

   delete [] data;
   data = new_data;
}

// Constructor that initializes the set with a given capacity.
IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0)
{ 
   //Capacity is a private int so it needs to be yoinked, hence : capacity in init
   capacity = (initial_capacity <= 0) ? DEFAULT_CAPACITY : capacity;
   data = new int[capacity];
}

// Copy constructor that creates a new set from an existing one.
IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used)
{
   data = new int[capacity];

   for(int i = 0; i < capacity; ++i){
      data[i] = src.data[i];
   }
}

// Destructor that deallocates the internal data array.
IntSet::~IntSet()
{
   delete [] data;
   data = NULL;
}

// Overloaded assignment operator to assign one set to another.
// Handles self-assignment (if !this != &rhs)
// Gets rid of old, crusty memory
IntSet& IntSet::operator=(const IntSet& rhs)
{
   if (this != &rhs){

      int* temp_data = new int[rhs.capacity];

      for (int i = 0; i < rhs.used; ++i) {
         temp_data[i] = rhs.data[i];
      }

      delete [] data;

      data = temp_data;
      capacity = rhs.capacity;
      used = rhs.used;
   }
   return *this;
}

// Returns the number of elements in the set.
int IntSet::size() const
{
   return used;
}

// Checks if the set is empty.
// Set used to 0

bool IntSet::isEmpty() const
{
   return used == 0;
}

// Checks if the set contains a specific integer.
bool IntSet::contains(int anInt) const
{
   for(int i = 0; (i < used) && (used > 0); ++i){
      if(data[i] == anInt) return true;
   }
   return false;
}

// Checks if the current set is a subset of another set.
// If the current set is empty, it is considered a subset of any set, 
//    so it returns true.
// If the current set is not empty, 
//    it checks every element of the current set to see if it is contained in otherIntSet. 
//    If there is even one element of the current set that is not in otherIntSet, 
//    it immediately returns false, indicating that the current set is not a 
//    subset of otherIntSet.
// If all elements of the current set are found in otherIntSet, 
//    the method will return true, indicating that the current set is indeed a subset 
//    of otherIntSet.
bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   if(isEmpty()){
      return true;
   } else {

   for(int i = 0; i < used; i++){
      if(!otherIntSet.contains(data[i]))
         return false;
      }
      return true;
   }
}

// Dumps the data of the set to an output stream.
void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

// Returns a new set that is the union of the current set and another set.
IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   IntSet unionIntSet = (*this);

   int sizeOtherInt = otherIntSet.size();

   for (int i = 0; i < sizeOtherInt; ++i) {
      if(!unionIntSet.contains(otherIntSet.data[i]))
         unionIntSet.add(otherIntSet.data[i]);
   }
   return unionIntSet;
}

// Returns a new set that is the intersection of the current set and another set.
IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet interSet = (*this);

   int sizeOtherInt = otherIntSet.size();

   for (int i = 0; i < sizeOtherInt; i++) {
      if(!otherIntSet.contains(data[i])){
         interSet.remove(data[i]);
      }
   }
   return interSet;
}

// Returns a new set that is the subtraction of another set from the current set.
IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   IntSet subSet = (*this);
   int sizeOtherInt = otherIntSet.size();

   for(int i = 0; i < sizeOtherInt; ++i){
      if(subSet.contains(otherIntSet.data[i])){
         subSet.remove(otherIntSet.data[i]);
      }
   }
   return subSet;
}

// Resets the set to be empty.
// Observes invariant?
void IntSet::reset()
{
   used = 0;
}

// Adds an integer to the set if it's not already present.
bool IntSet::add(int anInt)
{
   if(!contains(anInt)){
      if(used >= capacity){
         resize(int(capacity * 1.5) + 1); // as per special requirements
      }
      
      data[used] = anInt;
      ++used;
      return true;
   }
   return false;
}

// Removes an integer from the set if it's present. Shift by 1.
bool IntSet::remove(int anInt)
{
   if(contains(anInt)){
      for(int i = 0; i < used; ++i){
         if(data[i] == anInt) {
            for(int j = i; j < used - 1; ++j) {
               data[j] = data[j + 1];
            }
            --used;
            return true; 
         }
      }
   }
   return false;
}

// Checks if two sets are empty, then equal.
bool operator==(const IntSet& is1, const IntSet& is2) {
   if (is1.IntSet::isEmpty() && is2.IntSet::isEmpty()){
      return true;
   } else if(is1.IntSet::isSubsetOf(is2) && is2.IntSet::isSubsetOf(is1)){
      return true;
   }
   return false;
}
