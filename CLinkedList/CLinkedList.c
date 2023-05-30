/*
 * CLinkedList.c
 *
 *  Created on: 2023. 5. 30.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>

#include "CLinkedList.h"

void ListInit(List *plist)
{
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

int LCount(List *plist)
{
	return plist->numOfData;
}

void LInsert(List *plist, LData data)
{
	Node *newNode = (Node*) calloc(sizeof(Node), 1);
	newNode->data = data;

	if (plist->tail == NULL) {
		plist->tail = newNode;
		// tail->next : head
		newNode->next = newNode;
		// 원형 리스트에서 newNode 하나 밖에 없기 때문에 next는 자기 자신이다.
	} else {
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
		plist->tail = newNode; // newNode 를 tail에 추가하기 위한 코드.
	}
}

void LInsertFront(List *plist, LData data)
{
	Node *newNode = (Node*) calloc(sizeof(Node), 1);
	newNode->data = data;

	if (plist->tail == NULL) {
		plist->tail = newNode;
		newNode->next = newNode;
	} else {
		newNode->next = plist->tail->next;
		plist->tail->next = newNode;
	}
}

int LFirst(List *plist, LData *pdata)
{
	if (plist->tail == NULL) {
		return FALSE;
	}

	plist->before = plist->tail;
	plist->cur = plist->tail->next;

	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List *plist, LData *pdata)
{
	if (plist->tail == NULL) {
		return FALSE;
	}

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;

	return TRUE;
}

LData LRemove(List *plist)
{
	Node *rpos = plist->cur;
	LData rdata = plist->cur->data;

	if (plist->tail == NULL) {
		if (plist->tail == plist->tail->next) {
			plist->tail = NULL;
		} else {
			plist->tail = plist->before;
		}
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	free(rpos);
	return rdata;
}

