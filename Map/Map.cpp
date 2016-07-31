#include <fstream>
#include <iostream>
#include <math.h>
#include "Map.h"

using namespace std;

Map::Map(char** matrix, int height, int width, float resolution)
{
	HeightMap = height;
	WidthMap = width;
	_mapMatrix = matrix;
	this->resolution = resolution;
}

Map::Map(Map* mapToCopy)
{
	HeightMap = mapToCopy->getMapHeight();
	WidthMap = mapToCopy->getMapWidth();
	this->resolution = mapToCopy->getMapResolution();

	_mapMatrix = initializeMatrix(HeightMap, WidthMap, FREE_CELL);

	for (int i = 0; i < mapToCopy->getMapHeight(); i++)
	{
		for (int j = 0; j < mapToCopy->getMapWidth(); j++)
		{
			_mapMatrix[i][j] = mapToCopy->getMapValue(i, j);
		}
	}
}

void Map::setMapValueFromRealLocation(double x, double y, char value)
{
	setMapValue(getRowFromYPos(y), getColFromXPos(x), value);
}

void Map::setMapValue(int row, int col, char value)
{
	if (!(col < 0 || col >= WidthMap || row < 0 || row >= HeightMap))
	{
		if (_mapMatrix[row][col] != BLOCK_CELL)
			{
			if (row == HeightMap - 3 || row == HeightMap - 4)
					{
						if (col == 56 || col == 55 || col == 57)
						{
							if (value == BLOCK_CELL)
								cout << "hello" << endl;
						}
					}
				_mapMatrix[row][col] = value;
			}
	}
}

void Map::printMap()
{
	for (int i= 0; i < HeightMap ; i++)
	{
		for (int j= 0; j < WidthMap; j++)
		{
			cout << _mapMatrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

char Map::getMapValueFromRealLocation(double x, double y)
{
	int col = getColFromXPos(x);
	int row = getRowFromYPos(y);

	if (col < 0 || col >= WidthMap || row < 0 || row >= HeightMap)
	{
		return BLOCK_CELL;
	}

	return _mapMatrix[row][col];
}

char Map::getMapValue(int row, int col)
{
	return _mapMatrix[row][col];
}

int Map::getColFromXPos(double x)
{
	return ceil(x);
}

int Map::getRowFromYPos(double y)
{
	return ceil(-y);
}

int Map::getMapHeight()
{
	return HeightMap;
}

int Map::getMapWidth()
{
	return WidthMap;
}

float Map::getMapResolution()
{
	return resolution;
}

