#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>
#include "lodepng.h"
#include "math.h"
#include "../Consts.h"
#include "../Map/Map.h"
#include "../ConfigurationManager.h"

Map CreateMap(ConfigurationManager config);
void printMap(char** map, unsigned int height, unsigned int width);
char** initializeMatrix2(unsigned int height,unsigned int width, char sign);

#endif /* PNGUTIL_H_ */
