/*
 * DLinkedList.c
 *
 *  Created on: 2023. 5. 30.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>

#include "DLinkedList.h"

void ListInit(List *plist)
{
	plist->head = (Node*) calloc(sizeof(Node), 1);
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
	/*
	 * [질의]
	 * 1. plist 의 맴버인 cur, before 는 왜 초기화를 안 해주는거지?
	 * 2. plist의 맴버인 head를 초기화하는건 ok, head->next까지 해야하는 이유는?
	 * 		A : 해당  List 는 head가 더미고 head->next 부터가 진짜 시작이다.
	 * 		그래서 기본적으로 head, head->next 를 가지고 있게된다.
	 * 		initialization의 의미대로 가장 기본이 되는 모양은 갖춰주는 것.
	 */
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
	plist->before = plist->head;
	plist->cur = plist->head->next;

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
	Node *pred = plist->head;
	newNode->data = data;

	while(pred->next != NULL && plist->comp(data, pred->next->data) != 0) {
		pred = pred->next;
	}

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

	free(rpos);
	(plist->numOfData)--;

	return rdata;
}

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}
