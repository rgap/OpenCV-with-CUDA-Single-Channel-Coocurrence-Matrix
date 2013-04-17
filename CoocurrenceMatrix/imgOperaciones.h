#include "image.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <math.h>

static void YCbCrToRGB(Image* imYCbCr, Image* imRGB){

	int i,j;
	double Y,Cb,Cr;

	int cols=imYCbCr->cols, rows=imYCbCr->rows;

    for(i=0; i < imYCbCr->rows; i++){
        for(j=0; j < imYCbCr->cols; j++){
			Y = imYCbCr->pixelMat[i*cols+j].canal_0;
            Cb = imYCbCr->pixelMat[i*cols+j].canal_1;
            Cr = imYCbCr->pixelMat[i*cols+j].canal_2;

            Cb -= 128;
            Cr -= 128;

			imRGB->pixelMat[i*cols+j].canal_0 = 1 * Y + 0 * Cb + 1.4 * Cr;
			imRGB->pixelMat[i*cols+j].canal_1 = 1 * Y - 0.343 * Cb - 0.711 *Cr;
			imRGB->pixelMat[i*cols+j].canal_2 = 1* Y + 1.765 * Cb + 0* Cr;
		}
	}
}

static void RGBtoYCbCr(Image* imRGB, Image* imYCbCr){

	int i,j;
	double R,G,B;

	int cols=imYCbCr->cols, rows=imYCbCr->rows;

    for(i=0; i < imRGB->rows; i++){
        for(j=0; j < imRGB->cols; j++){
            R = imRGB->pixelMat[i*cols+j].canal_0;
            G = imRGB->pixelMat[i*cols+j].canal_1;
            B = imRGB->pixelMat[i*cols+j].canal_2;

			imYCbCr->pixelMat[i*cols+j].canal_0 = floor(0.299    *R + 0.587  *G  + 0.114  *B);
			imYCbCr->pixelMat[i*cols+j].canal_1 = floor(-0.1687   *R - 0.3313 *G  + 0.5    *B + 128);
			imYCbCr->pixelMat[i*cols+j].canal_2 = floor(0.5      *R - 0.4187 *G  - 0.0813 *B + 128);
        }
    }
}

Mat imageResize(Mat imagen, int x, int y) {
	Mat imagenNueva;
	resize(imagen,imagenNueva,Size(),x,y,INTER_LINEAR);
    return imagenNueva;
}

Mat imageGray(Mat imagen) {
	Mat imagenNueva;
	cvtColor(imagen, imagenNueva, CV_BGR2GRAY);
    return imagenNueva;
}
