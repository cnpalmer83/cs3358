#include <cstdlib>
#include <iostream>
#include "linkedlist.h"
using namespace std;

LinkedList::LinkedList()
{
	head = nullptr;
	curr = nullptr;
	temp = nullptr;
}

void LinkedList::AddNode(int addData)
{
	nodePtr n = new Node;
	n->next = nullptr;
	n->data = addData;

	if (head != nullptr)
	{
		curr = head;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr->next = n;
	}

	else
	{
		head = n;
	}
}

void LinkedList::DeleteNode(int delData)
{
	nodePtr delPtr = nullptr;
	temp = head;
	curr = head;

	while (curr != nullptr && curr->data != delData)
	{
		temp = curr;
		curr = curr->next;
	}

	if (curr == nullptr)
	{
		cout << delData << " not in list\n";
		delete delPtr;
	}

	else
	{
		delPtr = curr;
		curr = curr->next;
		temp->next = curr;
		delete delPtr;
		cout << "The value " << delData << " was deleted\n";
	}
}

void LinkedList::PrintList()
{
	curr = head;
	while (curr != nullptr)
	{
		cout << curr->data << endl;
		curr = curr->next;
	}
}
