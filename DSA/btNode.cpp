#include "btNode.h"

void bst_insert(btNode*& bst_root, int insInt) {
   btNode* newNode = new btNode;
   newNode->data = insInt;
   newNode->left = newNode->right = nullptr;

   if (bst_root == nullptr) {
      bst_root = newNode;
      return;
   }

   btNode* current = bst_root;
   btNode* parent = nullptr;
   while (current != nullptr) {
      parent = current;
      if (insInt < current->data) {
         current = current->left;
      } else if (insInt > current->data) {
         current = current->right;
      } else { // Node w same val
         delete newNode; // Clean up, no insert
         return;
      }
   }

   if (insInt < parent->data) {
      parent->left = newNode;
   } else {
      parent->right = newNode;
   }
}

bool bst_remove(btNode*& bst_root, int remInt) {
   if (bst_root == nullptr){return false;}

   btNode* current = bst_root;
   btNode* parent = nullptr;
   bool isLC = false;

   // Find node to remove
   while (current != nullptr && current->data != remInt) {
      parent = current;
      if (remInt < current->data) {
         isLC = true;
         current = current->left;
      } else {
         isLC = false;
         current = current->right;
      }
   }

   if (current == nullptr) {
      return false; // Value not found
   }

   // C1: Node w/ 2 children
   if (current->left != nullptr && current->right != nullptr) {
      // find prev (maximum in left subtree)
      btNode* prev = current->left;
      btNode* prevTop = current;
      while (prev->right != nullptr) {
         prevTop = prev;
         prev = prev->right;
      }

      // Copy prev data to current node
      current->data = prev->data;

      // Remove prev
      if (prevTop == current) {
         prevTop->left = prev->left;
      } else {
         prevTop->right = prev->left;
      }
      delete prev;
   }

   // C2: Node w/ 1 child/null child
   else {
      btNode* child = (current->left != nullptr) ? current->left : current->right;
      if (parent == nullptr) {
            bst_root = child; // Root begone
      } else {
         if (isLC) {
               parent->left = child;
         } else {
               parent->right = child;
         }
      }
      delete current;
   }

   return true;
}

void bst_remove_max(btNode*& bst_root, int& remInt) {
   if (bst_root == nullptr) return;

   btNode* current = bst_root;
   btNode* parent = nullptr;
   while (current->right != nullptr) {
      parent = current;
      current = current->right;
   }

   remInt = current->data;

   if (parent == nullptr) { 
      // Root is  max
      bst_root = bst_root->left;
   } else {
      parent->right = current->left;
   }

   delete current;
}


void portToArrayInOrder(btNode* bst_root, int* portArray)
{
   if (bst_root == 0) return;
   int portIndex = 0;
   portToArrayInOrderAux(bst_root, portArray, portIndex);
}

void portToArrayInOrderAux(btNode* bst_root, int* portArray, int& portIndex)
{
   if (bst_root == 0) return;
   portToArrayInOrderAux(bst_root->left, portArray, portIndex);
   portArray[portIndex++] = bst_root->data;
   portToArrayInOrderAux(bst_root->right, portArray, portIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}
