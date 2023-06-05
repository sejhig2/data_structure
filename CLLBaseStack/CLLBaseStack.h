/*
 * CLLBaseStack.h
 *
 *  Created on: 2023. 6. 5.
 *      Author: jhhwang
 */

#ifndef SRC_CLLBASESTACK_CLLBASESTACK_H_
#define SRC_CLLBASESTACK_CLLBASESTACK_H_

#include "../CLinkedList/CLinkedList.h"

typedef struct _listStack
{
	List *plist;
} ListStack;

typedef ListStack Stack;

void StackInit(Stack *pstack);
int SIsEmpty(Stack *pstack);

void SPush(Stack *pstack, Data data);
Data SPop(Stack *pstack);
Data SPeek(Stack *pstack);

#endif /* SRC_CLLBASESTACK_CLLBASESTACK_H_ */
