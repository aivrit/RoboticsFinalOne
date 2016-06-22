/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>


//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}
void decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename) {


	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
	unsigned char color;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				color = 0;
			else
				color = 255;
			navImage[y * width * 4 + x * 4 + 0] = color;
			navImage[y * width * 4 + x * 4 + 1] = color;
			navImage[y * width * 4 + x * 4 + 2] = color;
			navImage[y * width * 4 + x * 4 + 3] = 255;
		}

	encodeOneStep("newMap.png", navImage, width, height);
}
void setPixelColor(std::vector<unsigned char> &image, int height, int width, int color)
{
	image[height * width * 4 + width * 4 + 0] = color;
	image[height * width * 4 + width * 4 + 1] = color;
	image[height * width * 4 + width * 4 + 2] = color;
	image[height * width * 4 + width * 4 + 3] = 255;
}
void blowMap(const char* filename, double mapResolution, double robotSize)

{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned x, y;
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
	}

	double blowPixelFactor = (robotSize / mapResolution) / 4;
	std::vector<unsigned char> navImage;
	navImage.resize(width * height * 4);
		for (y = 0; y < height; y++)
			for (x = 0; x < width; x++) {
				if (image[y * width * 4 + x * 4 + 0]
						|| image[y * width * 4 + x * 4 + 1]
						|| image[y * width * 4 + x * 4 + 2])
				{
					setPixelColor(navImage, y, x, 255);
				}
			}
		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				if (!(image[y * width * 4 + x * 4 + 0]
						|| image[y * width * 4 + x * 4 + 1]
						|| image[y * width * 4 + x * 4 + 2]))
				{
					for (int i = -blowPixelFactor; i < blowPixelFactor; i++)
					{
						for (int j = -blowPixelFactor; j < blowPixelFactor; j++)
						{
							setPixelColor(navImage, y+i, x+j, 0);
						}
					}
				}
			}
		}

		encodeOneStep("newMap.png", navImage, width, height);
}

void thickenMap(const char* filename, int thickenSizeCM) {

	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	int x, y;
	int i, j;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
		<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> newImage; //the raw pixels

	newImage.resize(width * height * 4);

	// Initializing thick map
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			newImage[y * width * 4 + x * 4 + 0] = 255;
			newImage[y * width * 4 + x * 4 + 1] = 255;
			newImage[y * width * 4 + x * 4 + 2] = 255;
			newImage[y * width * 4 + x * 4 + 3] = 255;
		}

	// thickening map
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (!(image[y * width * 4 + x * 4 + 0]
			            || image[y * width * 4 + x * 4 + 1]
			                     || image[y * width * 4 + x * 4 + 2])){
				for (i = y - thickenSizeCM; i <= y + thickenSizeCM; i++){
					for (j = x - thickenSizeCM; j <= x + thickenSizeCM; j++){
						if ((i>=0)&&(j>=0)&&(i<height)&&(j<width)){
							newImage[i * width * 4 + j * 4 + 0] = 0;
							newImage[i * width * 4 + j * 4 + 1] = 0;
							newImage[i * width * 4 + j * 4 + 2] = 0;
						}
					}
				}
			}
		}

	// saving pic
	encodeOneStep("newMap.png", newImage, width, height);
}
