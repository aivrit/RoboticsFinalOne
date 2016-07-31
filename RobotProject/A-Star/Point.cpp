/*
 * Point.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "Point.h"
#include "math.h"

Point::Point()
{
    parent = NULL;
    closed = false;
    opened = false;
    walkable = false;

    x = y = f = g = h = 0;
}

Point::Point(int x, int y, bool w)
{
    this->walkable = w;
    this->x = x;
    this->y = y;

    parent = NULL;
	closed = false;
	opened = false;

	f = g = h = 0;
}

Location* Point::getLocation()
{
    return new Location(x, y);
}

Point* Point::getParent()
{
    return parent;
}

void Point::setParent(Point *p)
{
    parent = p;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

float Point::getXf()
{
    return (float)x;
}

float Point::getYf()
{
    return (float)y;
}

int Point::getGScore(Point *p)
{
    return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}

int Point::getHScore(Point *p)
{
	return (myAbs(p->x - x) + myAbs(p->y - y)) * 10;
}

int Point::myAbs(int x)
{
	if (x >= 0)
	{
		return x;
	}

	return -x;
}

int Point::getGScore()
{
    return g;
}

int Point::getHScore()
{
    return h;
}

int Point::getFScore()
{
    return f;
}

void Point::computeScores(Point *end)
{
    g = getGScore(parent);
    h = getHScore(end);
    f = g + h;
}

bool Point::hasParent()
{
    return parent != NULL;
}

