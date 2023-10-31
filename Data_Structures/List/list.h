#ifndef DATASTRUCTURES_LIST
#define DATASTRUCTURES_LIST

#include"../../Libraries/data.h"

typedef struct listNode {
	listEntry entry;
	struct listNode *next;
}ListNode;

typedef struct List{
	ListNode *head;
	int size;
}List;

void createList(List *pl);
int listFull(List *pl);
int listEmpty(List *pl);
int listSize(List *pl);
void destroyList(List *pl);
int insertList(int pos,listEntry item , List *pl);
void deleteList(int p ,listEntry *pitem , List *pl);
void retrieveList(int p ,listEntry *pitem , List *pl);
void replaceList(int p ,listEntry item , List *pl);
void traverseList(List*ps , void (*pf)(listEntry item));

#endif