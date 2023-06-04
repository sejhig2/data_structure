/*
 * DLinkedList.c
 *
 *  Created on: 2023. 6. 4.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>

#include  "DLinkedList.h"

void ListInit(List *plist)
{
	plist->head = (Node*) calloc(sizeof(Node), 1);
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

int LCount(List *plist)
{
	return plist->numOfData;
}

int LFirst(List *plist, LData *pdata)
{
	if (plist->head->next == NULL) {
		return FALSE;
	}

	plist->cur = plist->head->next;
	plist->before = plist->head;
	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List *plist, LData *pdata)
{
	if (plist->cur->next == NULL) {
		return FALSE;
	}
	plist->before = plist->cur;
	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;

	return TRUE;
}

void FInsert(List *plist, LData data)
{
	Node *newNode = (Node*) calloc(sizeof(Node), 1);
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;

}
void SInsert(List *plist, LData data)
{
	Node *newNode = (Node*) calloc(sizeof(Node), 1);
	newNode->data = data;
	Node *pred = plist->head;

	while((pred->next != NULL) && (plist->comp(data, pred->next->data)) != 0) {
		pred = pred->next;
	};

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;

}

void LInsert(List *plist, LData data)
{
	if (plist->comp == NULL) {
		FInsert(plist, data);
	} else {
		SInsert(plist, data);
	}
}

LData LRemove(List *plist)
{
	Node *rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	(plist->numOfData)--;
	free(rpos);

	return rdata;

}

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}

