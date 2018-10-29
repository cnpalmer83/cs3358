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
void bst_insert(btNode*& bst_root, const int& insInt)
{
   if (bst_root == 0)
   {
      btNode* newNodePtr = new btNode;
      newNodePtr->data   = insInt;
      newNodePtr->left   = 0;
      newNodePtr->right  = 0;
      bst_root = newNodePtr;
      return;
   }
   else
   {
      btNode* cur = bst_root;
      while (true)
      {
         if (insInt < cur->data)
         {
            if (cur->left == 0)
            {
               cur->left = new btNode;
               cur->left->data = insInt;
               cur->left->left = 0;
               cur->left->right = 0;
               return;
            }
            else
               cur = cur->left;
         }

         else if (insInt > cur->data)
         {
            if (cur->right == 0)
            {
               cur->right = new btNode;
               cur->right->data = insInt;
               cur->right->left = 0;
               cur->right->right = 0;
               return;
            }
            else
               cur = cur->right;
         }

         else //(insInt == cur->data)
         {
            cur->data = insInt;
            return;
         }
      }
   }
}
// write definition for bst_remove here
bool bst_remove(btNode*& bst_root, const int& remInt)
{
   if (bst_root == 0)
      return false;
   else if (remInt < bst_root->data)
      bst_remove(bst_root->left, remInt);
   else if (remInt > bst_root->data)
      bst_remove(bst_root->right, remInt);
   else                                                  // remInt == bst_root->data
   {
      /*
      if (bst_root->left != 0 && bst_root->right != 0)
         bst_remove_max(bst_root->left, bst_root);
      else
      {
         btNode* temp = bst_root;
         if (bst_root->left == 0)   // there is a right child
            bst_root = bst_root->right;
         if (bst_root->right == 0)  // there is a left child
            bst_root = bst_root->left;
         else
            bst_root = 0;
         delete temp;
      }
      return true;
   */

      if (bst_root->left == 0 || bst_root->right == 0)   // one or no children present
      {
         // NOTE: remove node with one or no children
         btNode* temp = bst_root;
         if (bst_root->left != 0)                        // there is a left child
            bst_root = bst_root->left;
         else if (bst_root->right != 0)                       // there is a right child
            bst_root = bst_root->right;
         else                                            // there are no children
            bst_root = 0;

         delete temp;
         return true;
      }
      else                                               // node to remove has 2 children
      {
         // NOTE: remove node with 2 children
         bst_remove_max(bst_root->left, bst_root->data);
         return true;
      }
   }
   //return true;

}
// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& removed)
{
   if (bst_root->right == 0)
   {
      if (bst_root->left != 0)
      {
         btNode* temp = bst_root;
         removed = bst_root->data;
         bst_root = bst_root->left;
         delete temp;
      }
      else
      {
         removed = bst_root->data;
         delete bst_root;
         bst_root = 0;
      }
      return;
   }
   else
      bst_remove_max(bst_root->right, removed);
}
