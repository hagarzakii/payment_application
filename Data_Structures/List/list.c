#include"../../Libraries/libraries.h"
#include"list.h"

void createList(List *pl)
{
	pl->head = NULL;
	pl->size = 0;
}

int listFull(List *pl)
{
	return 0;
}

int listEmpty(List *pl)
{
	return (pl->size==0);
}

int insertList(listEntry item , List *pl)
{
	ListNode *p , *q ;
	int i;
	if(p = (ListNode*)malloc(sizeof(ListNode))){
	p->entry = item;
	p->next = NULL;
	int pos =pl->size;
	if(pos == 0)
	{
		p->next = pl->head;
		pl->head = p;
	}
	else
	{
		for(i = 0 , q=pl->head ; i <pos-1 ; i++)
		{
			q = q->next;
		}
		p->next = q->next;
		q->next = p;
	}
	pl->size ++;
	return 1;
	}
	else{
		return 0;
	}
}

void deleteList(int pos ,listEntry *pitem , List *pl)
{
	ListNode *tmp , *q ;
	int i ;
	if(pos == 0)
	{
		*pitem = pl->head->entry;
		tmp = pl->head->next;
		free(pl->head);
		pl->head = tmp;
	}
	else{
	q = pl->head;
	for(i = 0 ; i < pos-1  ; i++)
	{
		q = q->next;
	}
	*pitem = q->next->entry;
    tmp = q->next->next;
	free(q->next);
	q->next = tmp;
	}
	pl->size --;
}

void destroyList(List *pl)
{
	ListNode *q;
	while(pl->head)
	{
		q = pl-> head->next;
		free(pl->head);
		pl->head = q;
	}
	pl->size = 0;
}

void retrieveList(int pos ,listEntry *pitem , List *pl)
{
	ListNode *q ;
	q = pl->head;
	for(int i = 0 ; i < pos ; i ++)
	{
		q=q->next;
	}
	*pitem = q->entry;
}

int listSize(List *pl)
{
	return pl->size ;
}

void replaceList(int pos ,listEntry item , List *pl)
{
	ListNode *q ;
	q = pl->head;
	for(int i = 0 ; i < pos ; i ++)
	{
		q=q->next;
	}
	 q->entry = item;
}

void traverseList(List*pl , void (*pf)(listEntry item))
{
	ListNode *p = pl->head;
	while(p){
		(*pf)(p->entry);
		p = p->next;
	}
}