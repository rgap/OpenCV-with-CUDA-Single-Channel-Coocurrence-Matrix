#include "image.h"

#include <iostream>
#include <fstream>

using namespace std;

Image::Image(int rows, int cols) {
	this->rows = rows;
    this->cols = cols;
	arraySize = rows*cols;

	this->fileImage = "-";

	initializePixelMat();

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

Pixel **Image::getSegmentos(int numDivsRows, int numDivsCols){
	return 0;
}

void Image::recortarImagen(Pixel *segmento,int inicioRow,int finRow,int inicioCol,int finCol){

	int i,j;
	for (i = inicioRow; i < finRow; ++i){
		for (j = inicioCol; j < finCol; ++j){
			segmento[i*finCol+j].canal_0 = pixelMat[i*cols+j].canal_0;
			segmento[i*finCol+j].canal_1 = pixelMat[i*cols+j].canal_1;
			segmento[i*finCol+j].canal_2 = pixelMat[i*cols+j].canal_2;
		}
	}
}

void Image::showPixelMat_1C() {

    int i,j;

    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j)
			cout<<pixelMat[i*cols+j].canal_0<<'\t';
        cout<<endl;
    }
	cout<<endl;
}

void Image::initializePixelMat(){
	//Asignar memoria
    pixelMat = new Pixel[arraySize];
}

void Image::createMat(){

	imagenMat = Mat::zeros(rows,cols, CV_8UC3);

	int i,j;
	for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
			imagenMat.at<Vec3b>(i,j)[0]=pixelMat[i*cols+j].canal_0;
			imagenMat.at<Vec3b>(i,j)[1]=pixelMat[i*cols+j].canal_1;
			imagenMat.at<Vec3b>(i,j)[2]=pixelMat[i*cols+j].canal_2;

		}
    }
}


Image::~Image() {

	//this->imagenMat.release();

    //delete []pixelMat;
	//delete []fileImage;
}
