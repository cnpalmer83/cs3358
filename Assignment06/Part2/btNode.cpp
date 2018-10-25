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
bool bst_insert(btNode* bst_root, int insInt)
{
   btNode newNode = new btNode;
   newNode->data  = insInt;
   newNode->left  = 0;
   newNode->right = 0;

   if (bst_root == 0)                              // tree is empty, insInt is now the root.
   {
      bst_root = newNode;
      return true;
   }
   else
   {
      btNode* cur    = bst_root;
      btNode* parent = bst_root;
      while (cur->left != 0 && cur->right != 0)    // cursor is not a leaf, keep traversing
      {
         if (insInt == cur->data)
         {
            // TODO: handle matching condition
         }
         if (insInt < cur->data)
         {
            // TODO: traverse left
         }
         else
         {
            // TODO: insInt > cur->data.  traverse right
         }
         // TODO: traverse finished.  insert newNode here.
         return true;                              // newNode successfully inserted
      }
      return false;                                // Insert failed
   }
}
// write definition for bst_remove here

// write definition for bst_remove_max here
