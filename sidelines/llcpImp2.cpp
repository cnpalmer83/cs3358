#include <iostream>
#include <cstdlib>
#include "llcpInt.h"
using namespace std;

int FindListLength(Node* headPtr)
{
   int length = 0;

   while (headPtr != 0)
   {
      ++length;
      headPtr = headPtr->link;
   }

   return length;
}

bool IsSortedUp(Node* headPtr)
{
   if (headPtr == 0 || headPtr->link == 0) // empty or 1-node
      return true;
   while (headPtr->link != 0) // not at last node
   {
      if (headPtr->link->data < headPtr->data)
         return false;
      headPtr = headPtr->link;
   }
   return true;
}

void InsertAsHead(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = headPtr;
   headPtr = newNodePtr;
}

void InsertAsTail(Node*& headPtr, int value)
{
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = 0;
   if (headPtr == 0)
      headPtr = newNodePtr;
   else
   {
      Node *cursor = headPtr;

      while (cursor->link != 0) // not at last node
         cursor = cursor->link;
      cursor->link = newNodePtr;
   }
}

void InsertSortedUp(Node*& headPtr, int value)
{
   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data < value)
   {
      precursor = cursor;
      cursor = cursor->link;
   }

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   newNodePtr->link = cursor;
   if (cursor == headPtr)
      headPtr = newNodePtr;
   else
      precursor->link = newNodePtr;

   ///////////////////////////////////////////////////////////
   /* using-only-cursor (no precursor) version
   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   //newNodePtr->link = 0;
   //if (headPtr == 0)
   //   headPtr = newNodePtr;
   //else if (headPtr->data >= value)
   //{
   //   newNodePtr->link = headPtr;
   //   headPtr = newNodePtr;
   //}
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   //else if (headPtr->link == 0)
   //   head->link = newNodePtr;
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      //if (cursor->link != 0)
      //   newNodePtr->link = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }

   ////////////////// commented lines removed //////////////////

   Node *newNodePtr = new Node;
   newNodePtr->data = value;
   if (headPtr == 0 || headPtr->data >= value)
   {
      newNodePtr->link = headPtr;
      headPtr = newNodePtr;
   }
   else
   {
      Node *cursor = headPtr;
      while (cursor->link != 0 && cursor->link->data < value)
         cursor = cursor->link;
      newNodePtr->link = cursor->link;
      cursor->link = newNodePtr;
   }
   */
   ///////////////////////////////////////////////////////////
}

bool DelFirstTargetNode(Node*& headPtr, int target)
{
   Node *precursor = 0,
        *cursor = headPtr;

   while (cursor != 0 && cursor->data != target)
   {
      precursor = cursor;
      cursor = cursor->link;
   }
   if (cursor == 0)
   {
      cout << target << " not found." << endl;
      return false;
   }
   if (cursor == headPtr) //OR precursor == 0
      headPtr = headPtr->link;
   else
      precursor->link = cursor->link;
   delete cursor;
   return true;
}

bool DelNodeBefore1stMatch(Node*& headPtr, int target)
{
   if (headPtr == 0 || headPtr->link == 0 || headPtr->data == target) return false;
   Node *cur = headPtr->link, *pre = headPtr, *prepre = 0;
   while (cur != 0 && cur->data != target)
   {
      prepre = pre;
      pre = cur;
      cur = cur->link;
   }
   if (cur == 0) return false;
   if (cur == headPtr->link)
   {
      headPtr = cur;
      delete pre;
   }
   else
   {
      prepre->link = cur;
      delete pre;
   }
   return true;
}

void ShowAll(ostream& outs, Node* headPtr)
{
   while (headPtr != 0)
   {
      outs << headPtr->data << "  ";
      headPtr = headPtr->link;
   }
   outs << endl;
}

void FindMinMax(Node* headPtr, int& minValue, int& maxValue)
{
   if (headPtr == 0)
   {
      cerr << "FindMinMax() attempted on empty list" << endl;
      cerr << "Minimum and maximum values not set" << endl;
   }
   else
   {
      minValue = maxValue = headPtr->data;
      while (headPtr->link != 0)
      {
         headPtr = headPtr->link;
         if (headPtr->data < minValue)
            minValue = headPtr->data;
         else if (headPtr->data > maxValue)
            maxValue = headPtr->data;
      }
   }
}

double FindAverage(Node* headPtr)
{
   if (headPtr == 0)
   {
      cerr << "FindAverage() attempted on empty list" << endl;
      cerr << "An arbitrary zero value is returned" << endl;
      return 0.0;
   }
   else
   {
      int sum = 0,
          count = 0;

      while (headPtr != 0)
      {
         ++count;
         sum += headPtr->data;
         headPtr = headPtr->link;
      }

      return double(sum) / count;
   }
}

void ListClear(Node*& headPtr, int noMsg)
{
   int count = 0;

   Node *cursor = headPtr;
   while (headPtr != 0)
   {
      headPtr = headPtr->link;
      delete cursor;
      cursor = headPtr;
      ++count;
   }
   if (noMsg) return;
   clog << "Dynamic memory for " << count << " nodes freed"
        << endl;
}

// definition of MakeDistinctPairs of Assignment 5 Part 1
void MakeDistinctPairs(Node*& headPtr)
{
   Node* key = headPtr;
   Node* cur = headPtr;
   Node* preCur = 0;
   Node* preKey = 0;
   Node* temp = 0;
   bool keyEnd = false;
   bool curEnd = false;
   bool pair = false;
   bool match = false;
   int length = 0;

   while (cur != 0)                  // Get length for proper entry
   {
      ++length;
      cur = cur->link;
   }

   if (length == 0)                                // Case for empty list
      return;
   if (length == 1)                                // Case for single node
   {
      Node* newNode = new Node;
      newNode->data = key->data;
      newNode->link = 0;
      key->link = newNode;
      return;
   }
   if (length == 2)                                // Case for exactly two nodes
   {
      cur = cur->link;                             // If both nodes match, do nothing.
      if (key->data != cur->data)                  // Otherwise, make each node a pair.
      {
         Node* newNodeKey = new Node;
         Node* newNodeCur = new Node;
         newNodeKey->data = key->data;
         newNodeCur->data = cur->data;
         newNodeKey->link = cur;
         newNodeCur->link = 0;
         key->link = newNodeKey;
         cur->link = newNodeCur;
      }
      return;
   }
                                                   // List is 3 or more nodes
   preKey = headPtr;                               // Stage pointer variables
   key = preKey->link;
   preCur = key;
   cur = preCur->link;
   curEnd = (cur->link == 0);

   while (!keyEnd)                                 // Process the list
   //while (cin.get() != 1)
   {
/*
      cout << "--------------------------------------------\n";
      cout << "preKeyPtr, keyPtr, preCurPtr, curPtr: "
           << preKey->data << " " << key->data << " " << preCur->data << " " << cur->data << endl;
      cout << headPtr->data << "--" << headPtr->link->data << "--" << headPtr->link->link->data << "--"
           << headPtr->link->link->link->data << "--" << endl;
      cout << "BEFORE\n";
      cout << "keyEnd, curEnd, match, pair: "
           << keyEnd << " " << curEnd << " " << match << " " << pair
           << " -- key->link == cur: " << (key->link == cur) << endl << endl;
*/
      cout << "===========================================" << endl;
      cout << "Top of loop";
      keyEnd = (key->link == 0);
      //keyEnd = (curEnd && key->link == cur);
      curEnd = (cur->link == 0);                   // Set flags for logic control
      match  = (key == cur);
      pair   = (preKey == key);

      //cout << "AFTER\n";
      cout << endl << "keyEnd, curEnd, match, pair: "
           << keyEnd << " " << curEnd << " " << match << " " << pair
           << " -- key->link == cur: " << (key->link == cur) << endl;

      if (keyEnd)                                  // 3 nodes or final operation
      {
         if (match && pair)
         {
            cout << "Entering condition A" << endl;
            key->link = 0;
            delete cur;
            cur = 0;
         }
         cout << "Entering condition C" << endl;
         if (!match && pair)
         {
            Node* newNodeCur = new Node;
            newNodeCur->data = cur->data;
            newNodeCur->link = 0;
            cur->link = newNodeCur;
         }
         if (!match && !pair)
         {
            cout << "Entering condition D" << endl;
            Node* newNodeKey = new Node;
            Node* newNodeCur = new Node;
            newNodeKey->data = key->data;
            newNodeCur->data = cur->data;
            newNodeKey->link = cur;
            newNodeCur->link = 0;
            key->link = newNodeKey;
            cur->link = newNodeCur;

            if (length == 3)
            {
               Node* newNodePreKey = new Node;
               newNodePreKey->data = preKey->data;
               newNodePreKey->link = preKey->link;
               preKey->link = newNodePreKey;
            }
         }
         return;
      }
      if (curEnd)                                  // cur resets after this operation
      {
         if (match && pair)
         {
            cout << "Entering condition E" << endl;
            preKey = key;
            key = key->link;
            preCur->link = 0;
            preCur = key;
            delete cur;
            cur = preCur->link;
         }
         if (match && !pair)
         {
            cout << "Entering condition F" << endl;
            temp = key->link;
            cur->link = temp;
            key->link = cur;
            preCur->link = 0;
            preKey = key;
            key = key->link;
            preCur = key;
            cur = preCur->link;
            temp = 0;
         }
         if (!match && pair)
         {
            cout << "Entering condition G" << endl;
            preKey = key;
            key = key->link;
            preCur = key;
            cur = preCur->link;
         }
         if (!match && !pair)                      // Condition H: 0 1 0 0
         {
            cout << "Entering condition H" << endl;
            if (preKey == headPtr)
            {
               cout << "H.1" << endl;
               Node* newNodePreKey = new Node;
               newNodePreKey->data = preKey->data;
               newNodePreKey->link = preKey->link;
               preKey->link = newNodePreKey;
               preKey = preKey->link;
               newNodePreKey = 0;
               preCur = key;
               cur = preCur->link;
            }
            else
            {
               if (key->link == preCur)
               {
                  preKey = key;
                  key = key->link;
               }
               else
               {
                  cout << "H.2" << endl;
                  Node* newNodeKey = new Node;
                  newNodeKey->data = key->data;
                  newNodeKey->link = key->link;
                  key->link = newNodeKey;
                  preKey = key;
                  key = key->link;
                  preCur = key;                       // Latest fix (still losing last node)
                  cur = preCur->link;
               }
            }
         }
      }
      else                                         // Not keyEnd or curEnd
      {
         if (match && pair)                        // Condition I: 0 0 1 1
         {
            cout << "Entering condition I" << endl;
            temp = cur;
            cur = cur->link;
            preCur->link = cur;
            delete temp;
            temp = 0;
         }
         if (match && !pair)                       // Condition J: 0 0 1 0
         {
            cout << "Entering condition J" << endl;
            if (key->link == cur)
            {
               preKey = key;
               key = key->link;
               preCur = cur;
               cur = cur->link;
            }
            else
            {
               temp = cur->link;
               cur->link = key->link;
               key->link = cur;
               preCur->link = temp;
               preKey = key;
               key = key->link;
               cur = temp;
               temp = 0;
            }
         }
         if (!match)                               // Condition K & L: 0 0 0 1
         {                                         //                  0 0 0 0
            cout << "Entering condition K or L" << endl;
            preCur = cur;
            cur = cur->link;
         }
      }

      temp = headPtr;
      while (temp != 0)
      {
         cout << temp->data << " ";
         temp = temp->link;
      }
      cout << endl << "preKeyPtr, keyPtr, preCurPtr, curPtr: "
           << preKey->data << " " << key->data << " " << preCur->data << " " << cur->data << endl;
      cout << "End of loop" << endl;

      //keyEnd = (curEnd && key->link == cur);
   }
}
