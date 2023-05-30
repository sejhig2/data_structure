/*
 * Point.h
 *
 *  Created on: 2023. 5. 30.
 *      Author: jhhwang
 */

#ifndef DLINKEDLISTSORT_POINT_H_
#define DLINKEDLISTSORT_POINT_H_

typedef struct _point
{
	int xpos;
	int ypos;
} Point;

void SetPointPos(Point *ppos, int xpos, int ypos);
void ShowPointPos(Point *ppos);
int PointComp(Point *pos1, Point *pos2);

#endif /* DLINKEDLISTSORT_POINT_H_ */
