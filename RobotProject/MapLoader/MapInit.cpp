#include "MapInit.h"

char** initializeMatrix(unsigned int height,unsigned int width, char sign) {

	unsigned x, y;

	char** map = new char*[height];

		for (y=0; y<height; y++) {
			map[y] = new char[width];
		}

		for (y = 0; y < height; y++)
			for (x = 0; x < width; x++) {
				map[y][x] = sign;
			}

		return map;
}

