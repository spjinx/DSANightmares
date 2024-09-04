#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_FA2023_A5P2
{
   // Default constructor: Initializes numItems to 0
   cnPtrQueue::cnPtrQueue() : numItems(0){}

   // Checks if the queue is empty
   // Returns true if both inStack and outStack are empty, false otherwise
   bool cnPtrQueue::empty() const
   {
      return(inStack.empty() && outStack.empty());
   }

   // Returns the current size of the queue
   cnPtrQueue::size_type cnPtrQueue::size() const{
         return numItems;
   }

   // Returns a pointer to the front of the queue
   CNode* cnPtrQueue::front()
   {
      // Assert that at least one of the stacks is not empty
      assert(!inStack.empty() || !outStack.empty());

      // If outStack is empty, transfer all elements from inStack to outStack
      if (outStack.empty()) {
         while (!inStack.empty()) {
            outStack.push(inStack.top());
         inStack.pop();
         }
      }
      // Return the top element of outStack (FIFO)
      return outStack.top();
   }

   // Adds a new item to the back of the queue
   void cnPtrQueue::push(CNode* cnPtr)
   {
      inStack.push(cnPtr);
      ++numItems;
   }

   // Removes the front item from the queue
   void cnPtrQueue::pop()
   {
      assert(!inStack.empty() || !outStack.empty());

      if (outStack.empty() ) {
         while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
         }
      }
      outStack.pop();
   -- numItems;
   }
}