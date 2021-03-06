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
   if (headPtr == 0)                                        // Case for empty list
      return;
   if (headPtr->link == 0)                                  // Case for 1 node list
   {
      Node* newNodePtr = new Node;
      newNodePtr->data = headPtr->data;
      newNodePtr->link = 0;
      headPtr->link = newNodePtr;
      return;
   }
   else                                                     // Case for 2 or more nodes
   {
      Node* preKey = 0;                                     // Stage pointers for comparison
      Node* temp = 0;                                       // of first two nodes
      Node* key = headPtr;
      Node* preTarget = headPtr;
      Node* target = headPtr->link;
      bool keyEndOfList = false;
      bool pair = false;
      bool targetEndOfList = (target->link == 0);
      bool match = (key->data == target->data);             // First evaluation

      cout << "Loop pre-condition case: ";
      switch (targetEndOfList)
      {
         case 1:
            cout << "A" << endl;                                       // exactly two nodes
            if (!match)                                     // the two nodes are not a pair
            {
                                                            // Do nothing if two nodes already match
               Node* newNodePtr1 = new Node;
               Node* newNodePtr2 = new Node;
               newNodePtr1->data = key->data;
               newNodePtr2->data = target->data;
               newNodePtr1->link = target;
               newNodePtr2->link = 0;
               key->link = newNodePtr1;
               target->link = newNodePtr2;
            }
            return;
         case 0:
            cout << "B" << endl;                                          // more than two nodes
            if (match)                                      // first two nodes are the same
            {

               // Just increment pointers
               pair = true;
               preKey = key;
               preTarget = target;
               key = target;
               target = target->link;
            }
            else                                            // first two nodes are not the same
            {
               preTarget = target;
               target = target->link;
            }
            break;
      }
      cout << "Before while loop" << endl;
      cout << "keyEnd, targetEnd, match, pair = "
           << keyEndOfList << " " << targetEndOfList << " " << match << " " << pair << endl;
      while (!keyEndOfList)
      {
         //cout << "In while loop (top)" << endl;
         targetEndOfList = (target->link == 0);          // Set targetEndOfList flag
         match = (key->data == target->data);            // Set match flag

         cout << "Start loop" << endl;
         cout << "keyEnd, targetEnd, match, pair = "
              << keyEndOfList << " " << targetEndOfList << " " << match << " " << pair << endl;
         cout << "Entering case: ";

         if (targetEndOfList)
         {
            switch (pair)
            {
            case 1:
               if (match)
               {
                  cout << "1" << endl;
                  // targetEndOfList AND pair AND match.
                  if (key->link == target)
                  {
                     delete target;
                     key->link = 0;
                     target = 0;
                  }
                  else
                  {
                     key = key->link;
                     delete target;
                     (key->link == 0) ? target = 0 : target = key->link;
                  }
               }
               else
               {
                  cout << "2" << endl;
                  // targetEndOfList AND pair but no match
                  if (key->link == target)
                  {
                     match = (key->data == target->data);
                     if (match)
                     {
                        delete target;
                        target = 0;
                        cout << "Target deleted at tail" << endl;
                     }
                     else
                     {
                        Node* newNodePtr = new Node;
                        newNodePtr->data = target->data;
                        newNodePtr->link = 0;
                        target->link = newNodePtr;
                        key = newNodePtr;
                     }
                  }
                  else
                  {
                     key = key->link;
                     preTarget = key;
                     target = key->link;
                     pair = false;
                  }
               }
               break;
            case 0:
               if (match)
               {
                  cout << "3" << endl;
                  // targetEndOfList AND no pair exists AND there is a match.
                  if (key->link == target)
                     key = target;
                  else
                  {
                     preTarget->link = 0;
                     target->link = key->link;
                     key->link = target;
                     key = key->link;
                     target = key->link;
                  }
                  pair = true;
               }
               else
               {
                  cout << "4" << endl;
                  // targetEndOfList AND no pair exists AND there is NOT a match.
                  Node* newNodePtr = new Node;
                  newNodePtr->data = key->data;
                  newNodePtr->link = key->link;
                  key->link = newNodePtr;
                  key = key->link;
                  target = key->link;
                  pair = true;
               }
               break;
            }
         }
         else if (!targetEndOfList)
         {
            switch (pair)
            {
            case 1:
               if (match)
               {
                  cout << "5" << endl;
                  // !targetEndOfList AND pair AND match.
                  temp = target;
                  target = target->link;
                  preTarget->link = target;
                  delete temp;
                  temp = 0;
               }
               else
               {
                  cout << "6" << endl;
                  // !targetEndOfList AND pair but no match
                  preTarget = target;
                  target = target->link;
               }
               break;
            case 0:
               if (match)
               {
                  cout << "7" << endl;
                  // !targetEndOfList AND no pair exists AND there is a match.
                  if (key->link == target)
                  {
                     key = target;
                     preKey = preTarget;
                     target = target->link;
                     preTarget = key;
                  }
                  else
                  {
                     preKey = key;
                     temp = target;
                     target = target->link;
                     key = temp;
                     preTarget->link = target;
                     key->link = preKey->link;
                     preKey->link = key;
                     /*
                     temp = target->link;
                     target->link = key->link;
                     key->link = target;
                     preTarget->link = temp;
                     target = temp;
                     temp = 0;
                     key = key->link;
                     */
                  }
                  pair = true;
               }
               else
               {
                  cout << "8" << endl;
                  // !targetEndOfList AND no pair exists AND there is NOT a match.
                  preTarget = target;
                  target = target->link;
               }
               break;
            }
         }
         // TODO: ensure all flags properly set, especially keyEndOfList
         //       pair should have been set in one of the 8 possible conditions above
         keyEndOfList = (key->link == 0);
         cout << "End loop" << endl;
         cout << "keyEnd, targetEnd, match, pair = "
              << keyEndOfList << " " << targetEndOfList << " " << match << " " << pair << endl;
         cout << "-----------------------------------------" << endl;
      }
      cout << "<><><><><><><><><><><><>END OF TEST<><><><><><><><><><><><>" << endl;
   }
}
