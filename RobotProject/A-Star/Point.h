#include <iostream>
#include "Position.h"
#include <stdlib.h>

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point();
	Point(int x, int y, bool w);
	int y, x, g, h, f;
	bool closed, opened, walkable;
	Point* parent;
	Position* getPosition();
	Point* getParent();
	void setParent(Point *p);
	int getX();
	int getY();
	float getXf();
	float getYf();
	int getGScore(Point *p);
	int getHScore(Point *p);
	int getGScore();
	int getHScore();
	int getFScore();
	void computeScores(Point *end);
	bool hasParent();
	int myAbs(int x);
};

#endif /* POINT_H_ */
