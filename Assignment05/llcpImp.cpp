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
   // Case for empty list
   // Case for 1 node
   // Case for 2 nodes
   // Case for 3 nodes

   // Case for 4+ nodes

   // Initialize all pointers and bool variables
   Node* preKey = 0;
   Node* key = headPtr;
   Node* preCur = key;
   Node* cur = preCur->link;

   bool finished = (key->link == 0);
   bool curEnd = (cur->link = 0);
   bool match = (key->data == cur->data);
   bool pair = match;                              // initial test of first 2 nodes
   if (pair)
   {
      preKey = key;
      key = key->link;
      preCur = key;
      cur = preCur->link;
   }

   while (!finished)
   {
      if (preKey != 0)
         pair = (preKey->data == key->data);
      finished = (key->link == 0);

      if (finished)
      {
         switch (pair)
         {
            case 1:
               break;
            case 0:
               Node* newNodePtr = new Node;
               newNodePtr->data = key->data;
               newNodePtr->link = 0;
               key->link = newNodePtr;
               break;
         }
         return;
      }

      else
      {
         if (preKey != 0)
            pair = (preKey->data == key->data);
         match = (key->data == cur->data);
         curEnd = false;                           // dealt with in curEnd loop

         while (!curEnd)
         {
            match = (key->data == cur->data);
            curEnd = (cur->link == 0);

            if (!curEnd)
            {
               if (match)                          // !curEnd, match
               {
                  switch (pair) {
                     case 1:
                        preCur->link = cur->link;
                        delete cur;
                        cur = preCur->link;
                        break;
                     case 0:
                        temp = cur->link;
                        cur->link = key->link;
                        key->link = cur;
                        preCur->link = temp;
                        preKey = key;
                        key = key->link;
                        cur = temp;
                        temp = 0;
                        break;
                  }
               }
               else                                // !curEnd, !match
               {
                  preCur = cur;
                  cur = cur->link;
                  /*
                  switch (pair) {                  // TODO: remove switch if not needed.
                     case 1:                       //       both cases should only require ++cur
                     case 0:                       //       but left behind just in case.
                  }
                  */
               }
            }

            else
            {
               if (match)                          // curEnd, match
               {
                  switch (pair) {
                     case 1:
                        preKey = key;
                        key = key->link;
                        preCur->link = 0;
                        preCur = key;
                        delete cur;
                        cur = preCur->link;        // 0 if key has moved to end of list
                        break;
                     case 0:
                        preCur->link = 0;
                        cur->link = key->link;
                        key->link = cur;
                        preKey = key;
                        key = key->link;
                        preCur = key;
                        cur = cur->link;
                        break;
                  }
               }
               else                                // curEnd, !match
               {
                  switch (pair) {
                     case 1:
                        preKey = key;
                        key = key->link;
                        precur = key;
                        cur = precur->link;
                        break;
                     case 0:
                        Node* newNode = new Node;
                        newNode->data = key->data;
                        newNode->link = key->link;
                        key->link = newNode;
                        preKey = key;
                        key = key->link;
                        preCur = key;
                        cur = preCur->link;
                        newNode = 0;
                  }
               }
            }
            pair = (preKey->data == key->data);    // Maybe don't need this....
         }


      }
   }
}
