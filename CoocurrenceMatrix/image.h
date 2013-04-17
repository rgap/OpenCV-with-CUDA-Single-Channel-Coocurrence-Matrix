#ifndef IMAGE_H
#define IMAGE_H

#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

#include "pixel.h"

using namespace cv;

class Image {

private:

	char* fileImage;

public:

	Mat imagenMat;

	Pixel *pixelMat;

	int arraySize;

	int rows;
	int cols;


	Image(int rows, int cols);

	Image(char* fileImage,int flag);

	Image(char* fileTest);

	Pixel **getSegmentos(int numDivsRows, int numDivsCols);

	void recortarImagen(Pixel *segmento,int inicioRow,int finRow,int inicioCol,int finCol);

	void showPixelMat_1C();

	void initializePixelMat();

	void createMat();

	~Image();

};


#endif // IMAGE_H
