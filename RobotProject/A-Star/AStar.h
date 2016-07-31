#ifndef ASTAR_H_
#define ASTAR_H_

#include <vector>
#include "../Map/Map.h"
#include "../Consts.h"
#include "Point.h"
#include <list>

using namespace std;

class AStar {
private:
	Point*** pointsMap;
	int heigth;
	int width;
public:
	AStar(Map* map);
	virtual ~AStar();
	vector<Location*> findPath(int rowStart, int colStart, int rowEnd, int colEnd);

};

#endif /* ASTAR_H_ */
