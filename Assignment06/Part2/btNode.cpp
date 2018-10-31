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

void bst_insert(btNode*& bst_root, const int& insInt)
{
   if (bst_root == 0)                                       // Condition 1: Tree is empty, insInt
   {                                                        //              assigned to root.
      btNode* newNodePtr = new btNode;
      newNodePtr->data   = insInt;
      newNodePtr->left   = 0;
      newNodePtr->right  = 0;
      bst_root = newNodePtr;
      return;
   }
   else                                                     // Case for non-empty tree.
   {
      btNode* cur = bst_root;
      while (true)                                          // Traverse until insert point found.
      {
         if (insInt < cur->data)                            // insInt < data, check for insert condition.
         {
            if (cur->left == 0)                             // If left child vacant, fill with new node.
            {
               cur->left = new btNode;
               cur->left->data = insInt;
               cur->left->left = 0;
               cur->left->right = 0;
               return;
            }
            else                                            // Else, traverse left.
               cur = cur->left;
         }

         else if (insInt > cur->data)                       // insInt > data, check for insert condition.
         {
            if (cur->right == 0)                            // If right child vacant, fill with new node.
            {
               cur->right = new btNode;
               cur->right->data = insInt;
               cur->right->left = 0;
               cur->right->right = 0;
               return;
            }
            else                                            // Else, traverse right.
               cur = cur->right;
         }

         else                                               // insInt == data implied
         {
            cur->data = insInt;                             // Overwrite existing data with insInt.
            return;
         }
      }
   }
}

bool bst_remove(btNode*& bst_root, const int& remInt)
{
   if (bst_root == 0)                                       // Base case (tree is empty)
      return false;
   else if (remInt < bst_root->data)                        // remInt < data (traverse left)
      return bst_remove(bst_root->left, remInt);
   else if (remInt > bst_root->data)                        // remInt > data (traverse right)
      return bst_remove(bst_root->right, remInt);
   else if (bst_root->left == 0 || bst_root->right == 0)    // remInt found and 0 or 1 child exists
   {
      btNode* temp = bst_root;
      if (bst_root->left != 0)                              // Case for left child
         bst_root = bst_root->left;
      else if (bst_root->right != 0)                        // Case for right child
         bst_root = bst_root->right;
      else                                                  // Case for no children
         bst_root = 0;

      delete temp;
      return true;
   }
   else                                                     // Case for two children
   {
      bst_remove_max(bst_root->left, bst_root->data);
      return true;
   }
}

void bst_remove_max(btNode*& bst_root, int& removed)
{
   if (bst_root->right == 0)                                // Base case (max value of tree found)
   {
      if (bst_root->left != 0)                              // Condition 1: max value has left child
      {
         btNode* temp = bst_root;
         removed = bst_root->data;
         bst_root = bst_root->left;
         delete temp;
      }
      else                                                  // Condition 2: max value has no children
      {
         removed = bst_root->data;
         delete bst_root;
         bst_root = 0;
      }
      return;
   }
   else                                                     // Recursive search for max until found
      bst_remove_max(bst_root->right, removed);
}
