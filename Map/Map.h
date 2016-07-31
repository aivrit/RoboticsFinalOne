#ifndef MAP_H_
#define MAP_H_

#include "../Consts.h"
#include "../MapLoader/lodepng.h"
#include "../MapLoader/MapInit.h"

class Map {
private:
	int HeightMap;
	int WidthMap;
	char** _mapMatrix;
	float resolution;
public:
	Map(char** matrix, int HeightMap, int WidthMap, float resolution);
	Map(Map* mapToCopy);
	void setMapValueFromRealLocation(double x, double y, char value);
	void setMapValue(int row, int col, char value);
	void printMap();
	char getMapValueFromRealLocation(double x, double y);
	char getMapValue(int row, int col);
	int getColFromXPos(double x);
	int getRowFromYPos(double y);
	int getMapHeight();
	int getMapWidth();
	float getMapResolution();
};

#endif
