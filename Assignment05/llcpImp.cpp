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
   if (headPtr == 0)                                           // Case for empty list
      return;
   if (headPtr->link == 0)                                     // Case for 1 node
   {
      Node* newNode = new Node;
      newNode->data = headPtr->data;
      newNode->link = 0;
      headPtr->link = newNode;
      return;
   }

   Node* leadKey = headPtr;
   Node* tailKey = headPtr;
   Node* preCur  = headPtr;
   Node* cur     = leadKey->link;
   Node* temp    = 0;
   //Node* test = headPtr;                                                   //REMOVE WHEN WORKING
   int keyData   = leadKey->data;

   while (leadKey != 0)
   {
      keyData = leadKey->data;
      while (cur != 0)
      {
         cout << "cur loop entered\n";                                     //REMOVE WHEN WORKING
         if (leadKey == tailKey)                               // There is no pair
         {
            if (cur->data == keyData && cur->link != 0)        // match and cur not at end
            {
               temp = cur->link;
               cur->link = leadKey->link;
               leadKey->link = cur;
               cur = temp;
               preCur->link = cur;
               leadKey = leadKey->link;
               temp = 0;
            }
            else if (cur->data == keyData && cur->link == 0)   // match and cur at the end
            {
               cur->link = leadKey->link;
               leadKey->link = cur;
               preCur->link = 0;
               leadKey = leadKey->link;
               cur = 0;
            }
            else                                               // no match, increment cur if not at end
            {
               if (cur->link != 0)
               {
                  cout << "no pair or match, increment cur\n";                        //REMOVE WHEN WORKING
                  preCur = cur;
                  cur = cur->link;
               }
               else
               {
                  cout << "no pair or match, create node and attach key to it\n";     //REMOVE WHEN WORKING
                  Node* newNode = new Node;
                  newNode->data = leadKey->data;
                  newNode->link = leadKey->link;
                  leadKey->link = newNode;
                  leadKey = leadKey->link;
                  if (leadKey->link == cur && cur->link == 0)
                  {
                     if (cur->data == keyData)
                        delete cur;
                     else
                     {
                        Node* newNode = new Node;
                        newNode->data = cur->data;
                        newNode->link = 0;
                        leadKey->link = newNode;
                        return;
                     }
                  }
               }
            }
         }
         else                                                  // There is a pair
         {
            if (cur->data == keyData && cur->link != 0)        // match and cur not at end
            {
               temp = cur->link;
               delete cur;
               cur = temp;
               preCur->link = cur;
               temp = 0;
            }
            else if (cur->data == keyData && cur->link == 0)   // match and cur at the end
            {
               delete cur;
               cur = 0;
            }
            else  // There is no match
            {
               if (cur->link != 0)
               {
                  cout << "is a pair but no match, cur incrememnted\n";
                  preCur = cur;
                  cur = cur->link;
               }
               else
               {
                  Node* newNode = new Node;
                  newNode->data = cur->data;
                  newNode->link = 0;
                  cur->link = newNode;
                  preCur = cur;
                  cur = cur->link;
                  cout << (cur->link == 0) << endl;
               }
            }
         }
      }
      if (leadKey->link == 0)
         leadKey = 0;
      else
      {
         cout << "key incremented\n";                          //REMOVE WHEN WORKING
         leadKey = leadKey->link;
         tailKey = leadKey;
         preCur = leadKey;
         cur = preCur->link;
      }
      cout << "key->link is cur: " << (leadKey->link == cur) << endl;
      cout << "cur->link is 0  : " << (cur->link == 0) << endl;
      /*
      if (leadKey->link == cur && cur->link == 0)
      {
         if (leadKey == tailKey && cur->data != keyData) // no match/pair exists, make final node at tail
         {
            cout << "1\n";
            Node* newNode = new Node;
            newNode->data = cur->data;
            newNode->link = cur->link;
            cur->link = newNode;
            return;
         }
         //else if (leadKey == tailKey && cur->data == keyData) // new pair, do nothing
         else if (leadKey != tailKey && cur->data != keyData) // make final node on tail
         {
            cout << "2\n";
            Node* newNode = new Node;
            newNode->data = cur->data;
            newNode->link = cur->link;
            cur->link = newNode;
            return;
         }
         else if (leadKey != tailKey && cur->data == keyData) // delete cur
         {
            cout << "3\n";
            delete cur;
            return;
         }
         return;
      }
      */
   }
}
