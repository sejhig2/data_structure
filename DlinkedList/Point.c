/*
 * Point.c
 *
 *  Created on: 2023. 6. 4.
 *      Author: jhhwang
 */
#include "Point.h"
#include <stdio.h>
#include "DLinkedList.h"

void set_point(Point *point, int x, int y, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

void show_point(Point *point)
{
	printf("[x:%d \t y:%d \t z:%d]\n", point->x, point->y, point->z);
}

int compare_point(Point *p1, Point *p2)
{
	if (p1->x == p2->x) {
		printf("same x position \n");
		return TRUE;
	} else {
		return FALSE;
	}
}
