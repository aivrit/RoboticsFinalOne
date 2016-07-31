/*
 * AStar.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "AStar.h"

AStar::AStar(Map* map) {
	heigth = map->getMapHeight();
	width = map->getMapWidth();
	pointsMap = new Point**[map->getMapHeight()];

	for (int y=0; y<map->getMapHeight(); y++) {
	  pointsMap[y] = new Point*[map->getMapWidth()];
	}

	 // Goes all over the map matrix and constructs a points matrix from it
	 for ( int row = 0; row < map->getMapHeight(); row++ )
	 {
		 for ( int col = 0; col < map->getMapWidth(); col++ )
		 {
			 pointsMap[row][col] = new Point(row, col, map->getMapValue(row, col) != BLOCK_CELL);
		 }
	 }
}

// TODO: do it someday
AStar::~AStar() {
}

vector<Location*> AStar::findPath(int rowStart, int colStart, int rowEnd, int colEnd)
{
    vector<Location*> path;

    // Define points to work with
    Point *start = pointsMap[rowStart][colStart];
    Point *end = pointsMap[rowEnd][colEnd];
    Point *current;
    Point *child;

    // Define the open and the close list
    list<Point*> openList;
    list<Point*> closedList;
    list<Point*>::iterator i;

    unsigned int n = 0;

    // Add the start point to the openList
    openList.push_back(start);
    start->opened = true;

    while (n == 0 || (current != end && n < heigth * width))
    {
        // Look for the smallest F value in the openList and make it the current point
        for (i = openList.begin(); i != openList.end(); ++ i)
        {
            if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
            {
                current = (*i);
            }
        }

        // Stop if we reached the end
        if (current == end)
        {
            break;
        }

        // Remove the current point from the openList
        openList.remove(current);
        current->opened = false;

        // Add the current point to the closedList
        closedList.push_back(current);
        current->closed = true;

        // Get all current's adjacent walkable points
        for (int x = -1; x < 2; x ++)
        {
            for (int y = -1; y < 2; y ++)
            {
                // If it's current point then pass
                if (x == 0 && y == 0)
                {
                    continue;
                }

                // Get this point
                child = pointsMap[current->getX() + x][current->getY() + y];

                // If it's closed or not walkable then pass
                if (child->closed || !child->walkable)
                {
                    continue;
                }

                // If we are at a corner
                if (x != 0 && y != 0)
                {
                    // if the next horizontal point is not walkable or in the closed list then pass
                    if (!pointsMap[current->getX()][current->getY() + y]->walkable || pointsMap[current->getX()][current->getY() + y]->closed)
                    {
                        continue;
                    }

                    // if the next vertical point is not walkable or in the closed list then pass
                    if (!pointsMap[current->getX() + x][current->getY()]->walkable || pointsMap[current->getX() + x][current->getY()]->closed)
                    {
                        continue;
                    }
                }

                // If it's already in the openList
                if (child->opened)
                {
                    // If it has a wroste g score than the one that pass through the current point
                    // then its path is improved when it's parent is the current point
                    if (child->getGScore() > child->getGScore(current))
                    {
                        // Change its parent and g score
                        child->setParent(current);
                        child->computeScores(end);
                    }
                }
                else
                {
                    // Add it to the openList with current point as parent
                    openList.push_back(child);
                    child->opened = true;

                    // Compute it's g, h and f score
                    child->setParent(current);
                    child->computeScores(end);
                }
            }
        }

        n ++;
    }

    // Reset
    for (i = openList.begin(); i != openList.end(); ++ i)
    {
        (*i)->opened = false;
    }
    for (i = closedList.begin(); i != closedList.end(); ++ i)
    {
        (*i)->closed = false;
    }

    // Resolve the path starting from the end point
    while (current->hasParent() && current != start)
    {
        path.push_back(current->getLocation());
        current = current->getParent();
        n ++;
    }

    vector<Location*> fromStart;
    for (int i = path.size() - 1; i >= 0; i--)
    {
    	fromStart.push_back(path[i]);
    }

    return fromStart;
}

