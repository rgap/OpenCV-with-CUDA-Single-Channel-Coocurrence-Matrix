#ifndef SCM_GPU_H
#define SCM_GPU_H

#pragma once

//CUDA
#include <cuda.h>

#include "image.h"

using namespace std;
using namespace cv;


class SCM_GPU{

private:

	Image* imagen;

	Pixel* pixelMat_h;
	Pixel* pixelMat_d;

	int direction;
	int distance;

	//Variables GPU

	int Grid_Dim_x;
	int Grid_Dim_y;

	int Block_Dim_x;
	int Block_Dim_y;

	dim3 Grid;
	dim3 Block;

public:

	int * matrizSCM_h;
	int * matrizSCM_d;

	int arraySize;

	int cols;
	int rows;

	int numNiveles;

	int delta_i;
	int delta_j;

	SCM_GPU(Image *imagen, int numNiveles);

	void createSCM(int* offsets, int distance, int direction);

	void inicializar_MemDevice();

	void inicializar_VarsGPU();

	void copiar_DeviceHost();

	void showFileSCM();

	~SCM_GPU();
};


#endif  // SCM_GPU_H