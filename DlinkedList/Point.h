/*
 * Point.h
 *
 *  Created on: 2023. 6. 4.
 *      Author: jhhwang
 */

#ifndef DLINKEDLIST_POINT_H_
#define DLINKEDLIST_POINT_H_

typedef struct _point
{
	int x;
	int y;
	int z;
} Point;

void set_point(Point *point, int x, int y, int z);

void show_point(Point *point);

int compare_point(Point *p1, Point *p2);

#endif /* DLINKEDLIST_POINT_H_ */
