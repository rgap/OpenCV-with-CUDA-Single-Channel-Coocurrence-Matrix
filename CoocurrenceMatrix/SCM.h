#ifndef SCM_H
#define SCM_H

#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

#include "image.h"

using namespace std;
using namespace cv;

class SCM {

private:

	Image* imagen;	

    int direction;
    int distance;

	double * descriptores;

public:

	int * matrizSCM;

	int arraySize;

	int cols;
    int rows;

	int numNiveles;

	int delta_j;
	int delta_i;

	SCM();

	SCM(Image *imagen, int numNiveles);

	int * createSCM(int* offsets, int distance, int direction);

	void showFileSCM();

	void showSCM();

	void calcDescriptores();

	void showDescriptores();

	double *getDescriptores();

	void NormalizarSCM();

	~SCM();

};

#endif // SCM_H

