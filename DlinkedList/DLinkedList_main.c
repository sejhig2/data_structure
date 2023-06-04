/*
 * DLinkedList_main.c
 *
 *  Created on: 2023. 6. 4.
 *      Author: jhhwang
 */

#include <stdio.h>
#include <stdlib.h>

#include "DLinkedList.h"
#include "Point.h"

/*
 *
 int WhoIsBigger(LData d1, LData d2)
 {
 return d1 > d2 ? 1 : 0;
 }
 */

int main(void)
{

	List list = { 0 };
	Point *insert_point = { 0 };
	Point find_point = { 5, 5, 5 };

	int i = 0;

	ListInit(&list);
	insert_point = (Point*) calloc(sizeof(Point), 1);

	for (i = 0; i < 30; i++) {
		set_point(insert_point, i, i + 1, i + 2);
		LInsert(&list, *insert_point);
	}

	if (LFirst(&list, insert_point) == TRUE) {
		show_point(insert_point);
		while(LNext(&list, insert_point)) {
			show_point(insert_point);
		}
	}

	if (LFirst(&list, insert_point) == TRUE) {
		if (compare_point(insert_point, &find_point) == TRUE) {
			printf("removed : ");
			show_point(insert_point);
			LRemove(&list);
		}
		while(LNext(&list, insert_point) == TRUE) {
			if (compare_point(insert_point, &find_point) == TRUE) {
				printf("removed : ");
				show_point(insert_point);
				LRemove(&list);
			}
		}
	}

	if (LFirst(&list, insert_point) == TRUE) {
		show_point(insert_point);
		while(LNext(&list, insert_point)) {
			show_point(insert_point);
		}
	}

	return 0;
}
