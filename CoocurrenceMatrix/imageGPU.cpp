#include "ImageGPU.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <cassert>
#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;


///////////////////////////////////// Constructors /////////////////////////////////////

ImageGPU::ImageGPU(int rows, int cols) {
	this->rows = rows;
    this->cols = cols;
	arraySize = rows*cols;

	this->fileImage = "-";

	initializePixelMat();


	//Memoria en device

	Pixel *imagen_d;
	int *matrizSCM_d;

	//////////////  IMAGEN

	size_t size_imagen = arraySize*sizeof(Pixel);

	cudaMalloc((void**)&imagen_d, size_imagen);//Memoria en device
}



ImageGPU::ImageGPU( int _width, int _height )
{
	width = _width;
	height = _height;
	depth = 8;
	channels = 3;
	/*	pixels = new PixelRGB[ width * height ];
	datagray = new PixelGray[ width * height ];*/


	
}



Image::Image(char* fileTest) {
	ifstream ficheroImagen(fileTest);

	ficheroImagen>>rows;
    ficheroImagen>>cols;
	arraySize = rows*cols;

	this->fileImage = fileTest;

	initializePixelMat();

	int i,j;
	for(i = 0; i < arraySize; ++i){
		ficheroImagen>>pixelMat[i].canal_0;
		pixelMat[i].canal_1 = 0;
		pixelMat[i].canal_2 = 0;
	}

}

Image::Image(char* fileImage,int flag) {

	imagenMat = imread(fileImage,flag);

	rows = imagenMat.rows;
    cols = imagenMat.cols;
	arraySize = rows*cols;

	this->fileImage = fileImage;

	initializePixelMat();

	int i,j;
	for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
			pixelMat[i*cols+j].canal_0=imagenMat.at<Vec3b>(i,j)[2];
			pixelMat[i*cols+j].canal_1=imagenMat.at<Vec3b>(i,j)[1];
			pixelMat[i*cols+j].canal_2=imagenMat.at<Vec3b>(i,j)[0];
		}
    }

}


////////////////////////////////////// Destructor //////////////////////////////////////

ImageGPU::~ImageGPU()
{
	cudaFree( pixels );
	cudaFree( datagray );
}

/////////////////////////////////////// Functions //////////////////////////////////////

PixelRGB*& ImageGPU::getPixelRGB()
{
	return pixels;
}
PixelGray*& ImageGPU::getPixelsGray()
{
	return datagray;
}




//////////////////////////////////////// Methods ///////////////////////////////////////






void ImageGPU::copyFromCPURGB( Image& img )
{

	cudaMemcpy( pixels, img.getPixelRGB(), width * height * sizeof( PixelRGB ) , cudaMemcpyHostToDevice);
}

void ImageGPU::copyToCPURGB( Image& img )
{
	cudaMemcpy( img.getPixelRGB(), pixels,  width * height * sizeof( PixelRGB ) , cudaMemcpyDeviceToHost);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////				cpu   gray                     //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageGPU::copyFromCPUGray( Image& img )
{

	cudaMemcpy( datagray, img.getPixelsGray(), width * height * sizeof( PixelGray ) , cudaMemcpyHostToDevice);
}

void ImageGPU::copyToCPUGray( Image& img )
{
	cudaMemcpy( img.getPixelsGray(), datagray,  width * height * sizeof( PixelGray ) , cudaMemcpyDeviceToHost);
}
