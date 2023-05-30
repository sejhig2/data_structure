/*
 * CLinkedList.h
 *
 *  Created on: 2023. 5. 30.
 *      Author: jhhwang
 */

#ifndef CLINKEDLIST_CLINKEDLIST_H_
#define CLINKEDLIST_CLINKEDLIST_H_

#define TRUE 1
#define FALSE 0

#include "Employee.h"
//typedef int LData;

typedef Employee *LData;
typedef struct _node
{
	LData data;
	struct _node *next;
} Node;

typedef struct _CLL
{
	Node *tail;
	Node *cur;
	Node *before;
	int numOfData;
} CList;

typedef CList List;

void ListInit(List *plist);
int LCount(List *plist);

void LInsert(List *plist, LData data);
void LInsertFront(List *plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List *plist);

#endif /* CLINKEDLIST_CLINKEDLIST_H_ */
