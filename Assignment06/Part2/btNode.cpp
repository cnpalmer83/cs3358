#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
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

// write definition for bst_insert here
bool bst_insert(btNode* bst_root, const int& insInt)
{
   btNode* cur;                                          // placeholder for node insertion
   bool insertLeft;
   bool inPosition;

   bst_root == 0 ? (cur = 0) : (cur = bst_root);         // check for an empty tree

   if (cur == 0)                                         // if tree empty, cur placeholder is set
      inPosition = true;

   while (!inPosition)                                   // else, iterate tree until cur is positioned
   {
      if (cur->data == insInt)                           // if insInt == existing data, override data
      {                                                  // and return true (no new node created)
         cur->data = insInt;
         return true;
      }
      else if (insInt < cur->data)
      {
         if (cur->left == 0)                             // if insInt < cur->data and there is a left
         {                                               // child, go left. Otherwise, cur in position.
            inPosition = true;
            insertLeft = true;
         }
         else
            cur = cur->left;
      }
      else                                               // if insInt > cur->data and there is a right
         if (cur->right == 0)                            // child, go right. Otherwise, cur in position.
         {
            inPosition = true;
            insertLeft = false;
         }
         else
            cur = cur->right;
   }

   btNode newNode = new btNode;
   newNode->data  = insInt;
   newNode->left  = 0;
   newNode->right = 0;

   if (cur == 0)                                         // make newNode root if tree is empty
      bst_root = newNode;
   else                                                  // Otherwise, insert as appropriate cur child.
      insertLeft ? (newNode = cur->left) : (newNode = cur->right);

}
// write definition for bst_remove here
bool bst_remove(btNode* bst_root, const int& remInt)
{

}
// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& removed)
{
   
}
