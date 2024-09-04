#include "nodes_LLoLL.h"
#include "cnPtrQueue.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2023_A5P2
{
	
   // do breadth-first traversal and print data
   void ShowAll_BF(PNode* pListHead, ostream& outs)
   {
      // empty list
      if (pListHead == 0) return;
      // queue of CNode pointers
      CNode* cursor = 0;
      // queue of CNode pointers
      cnPtrQueue queue;

      // list point to pListHead, load
      while (pListHead != 0) {
         if (pListHead->data != 0) {
            // load queue with CNode pointers
            queue.push(pListHead->data);
         }
         // move to next PNode
         pListHead = pListHead->link;
      }

      // not empty, display queue
      while (!queue.empty() ) {
         cursor = queue.front();
         queue.pop();
         // display data
         outs << cursor->data << "  ";
      if (cursor->link != 0) {
         // load queue with CNode pointers
            queue.push(cursor->link);
         }
      }

   }
   
   void Destroy_cList(CNode*& cListHead)
   {
      int count = 0;
      CNode* cNodePtr = cListHead;
      while (cListHead != 0)
      {
         cListHead = cListHead->link;
         delete cNodePtr;
         cNodePtr = cListHead;
         ++count;
      }
      cout << "Dynamic memory for " << count << " CNodes freed"
           << endl;
   }

   void Destroy_pList(PNode*& pListHead)
   {
      int count = 0;
      PNode* pNodePtr = pListHead;
      while (pListHead != 0)
      {
         pListHead = pListHead->link;
         Destroy_cList(pNodePtr->data);
         delete pNodePtr;
         pNodePtr = pListHead;
         ++count;
      }
      cout << "Dynamic memory for " << count << " PNodes freed"
           << endl;
   }

   // do depth-first traversal and print data
   void ShowAll_DF(PNode* pListHead, ostream& outs)
   {
      while (pListHead != 0)
      {
         CNode* cListHead = pListHead->data;
         while (cListHead != 0)
         {
            outs << cListHead->data << "  ";
            cListHead = cListHead->link;
         }
         pListHead = pListHead->link;
      }
   }
}
