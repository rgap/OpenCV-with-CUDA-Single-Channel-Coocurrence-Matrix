#ifndef IMAGEGPU_H
#define IMAGEGPU_H

#include "Pixel.h"

#include <iostream>

using namespace std;

class ImageGPU
{
public:

	char* fileImage;

public:

	Pixel *pixelMat;

	int arraySize;

	int rows;
	int cols;

	ImageGPU(int rows, int cols);

	ImageGPU(char* fileImage,int flag);

	ImageGPU(char* fileTest);
};

#endif