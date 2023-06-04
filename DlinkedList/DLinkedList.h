/*
 * DLinkedList.h
 *
 *  Created on: 2023. 6. 4.
 *      Author: jhhwang
 */

#ifndef DLINKEDLIST_DLINKEDLIST_H_
#define DLINKEDLIST_DLINKEDLIST_H_

#define TRUE (1)
#define FALSE (0)

#include "Point.h"

//typedef int LData;
typedef Point LData;

typedef struct _node
{
	struct _node *next;
	LData data;
} Node;

typedef struct linkedlist
{
	Node *head;
	Node *cur;
	Node *before;
	int numOfData;
	int (*comp)(LData d1, LData d2);
} LinkedList;

typedef LinkedList List;

void ListInit(List *plist);
int LCount(List *plist);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

void LInsert(List *plist, LData data);
LData LRemove(List *plis);

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2));

#endif /* DLINKEDLIST_DLINKEDLIST_H_ */
