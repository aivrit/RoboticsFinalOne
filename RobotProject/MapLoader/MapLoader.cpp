#include "MapLoader.h"

Map CreateMap(ConfigurationManager config)
{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned int x, y;

	const char* path = config.getMapPath();
	unsigned error = lodepng::decode(image, width, height, path);
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
	}

	// Get parameters
	double gridResoultion = config.getGridResolutionCM();
	double mapResoultion = config.getMapResolutionCM();
	int divider = ceil(gridResoultion/mapResoultion); // Numbers of pixels for 1 cell in matrix

	// Create map as png pixels
	char** map = initializeMatrix2(height + (divider - 1) * 2,width + (divider - 1) * 2,  FREE_CELL);
	unsigned char color;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
			{
				// There is an obstacle in the map
				color = FREE_CELL;
			}
			else
			{
				// There is no obstacle
				color = BLOCK_CELL;
			}
			map[y + divider - 1][x + divider - 1] = color;

		}
	}

	// Create map as config cm size
	int newMapHieght = height/divider;
	int newMapWidth = width/divider;

	// Now it will build a mapBlow that will represents the resolution of the gridex
	// (for example: one cell in map is 2.5 cm, and in the mapBlow is 10 cm)
	char** mapBlow = initializeMatrix2(newMapHieght, newMapWidth, FREE_CELL);
	unsigned i,j;
	int mapBlowY = 0, mapBlowX = 0;
	bool hasObstacle = false;

	// Starts from divider -1 because "map" has SecurityWall
	for (y = divider - 1; y < height; y += divider)
	{
		for (x = divider - 1; x < width; x += divider)
		{
			for (i = 0; i < divider && !hasObstacle; i++)
			{
				for (j = 0; j < divider && !hasObstacle; j++)
				{
					if (map[y + i][x + j] == BLOCK_CELL)
					{
						hasObstacle = true;
					}
				}
			}

			// Checks if it has encontered an obstacle in one of the cells that it checked
			// it checks a subMatrix of (DIVIDERxDIVIDER) for every cell in the mapBlow
			if (hasObstacle)
			{
				mapBlow[mapBlowY][mapBlowX] = BLOCK_CELL;
			}

			hasObstacle = false;
			mapBlowX++;
		}

		mapBlowX = 0;
		mapBlowY++;
	}

	// ReSize obstacle
	double* robotSize =  config.getRobotSize();
	int sizeH = ceil(((robotSize[0] / gridResoultion) - 1) / 2);
	int sizeW = ceil(((robotSize[1] / gridResoultion) - 1) / 2);

	// Resizes the obstacles in the map so the robot will be represented in one cell
	char** newMap = initializeMatrix2(newMapHieght + sizeH*2, newMapWidth + sizeW*2, FREE_CELL);
	for (int i = 0; i < newMapHieght; i++)
	{
		for (int j = 0; j < newMapWidth; j++)
		{
			if (mapBlow[i][j] == BLOCK_CELL)
			{
				for (int iNewMap = i - 1; iNewMap <= i + sizeH + 2; iNewMap++)
				{
					for (int jNewMap = j - 1; jNewMap <= j + sizeW + 2; jNewMap++)
					{
						if (i > 0 && j > 0){
							newMap[iNewMap][jNewMap] = BLOCK_CELL;
						}
					}
				}
			}
		}
	}

	// Initialize final map with wall block of size 1.
	char** finalMap = initializeMatrix2(newMapHieght + 2, newMapWidth + 2, BLOCK_CELL);
	for (int i=1; i < newMapHieght + 1; i++)
	{
		for (int j=1; j< newMapWidth + 1; j++)
		{
			finalMap[i][j] = newMap[sizeH + i - 1][sizeW + j -1];
		}
	}


	return Map(finalMap, newMapHieght + 2, newMapWidth  + 2, gridResoultion / 100);
}

void printMap(char** map, unsigned int height, unsigned int width) {

	unsigned x, y;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			std::cout << map[y][x];
		}
		std::cout << std::endl;
	}

	std::cout << "----------------------------" << std::endl;
}

char** initializeMatrix2(unsigned int height,unsigned int width, char sign) {

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
