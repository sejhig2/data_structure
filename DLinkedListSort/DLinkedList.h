/*
 * DLinkedList.h
 *
 *  Created on: 2023. 5. 30.
 *      Author: jhhwang
 */

#ifndef DLINKEDLISTSORT_DLINKEDLIST_H_
#define DLINKEDLISTSORT_DLINKEDLIST_H_

#define TRUE 1
#define FALSE 0
typedef int LData;

typedef struct _node
{
	LData data;
	struct _node *next;
} Node;

typedef struct _linkedList
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
LData LRemove(List *plist);

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2));

#endif /* DLINKEDLISTSORT_DLINKEDLIST_H_ */
