
#include <iostream>

#include "image.h"

#include "scm_globals.h"
#include "imgOperaciones.h"

//CPU
#include "SCM.h"

//GPU
#include "SCM_GPU.cuh"

using namespace std;


int main() {

	/////////////////////// Imagen entrada  //////////////////////////

	Image imagenTest("test.txt");
	imagenTest.createMat();

	Mat imagenGray = imageGray(imagenTest.imagenMat);
	Mat imagenEscala = imageResize(imagenGray,100,100);


	//Image imagenTest("BD/img.jpg",1);
	//Mat imagenGray = imageGray(imagenTest.imagenMat);



	//imagenTest.showPixelMat_1C();

	//namedWindow("ENTRADA", 1);
	//imshow("ENTRADA", imagenEscala);
	//waitKey(0);


	/////////////////////////////////////////////////////////////////
	/////////////////////////////// CPU /////////////////////////////
	/////////////////////////////////////////////////////////////////

	SCM scmImagen(&imagenTest, 256);

	scmImagen.createSCM(OFFSETS_DEFAULT, 1, SCM_DIRECTION_45);

	scmImagen.showFileSCM();


	//cin.get();

	/////////////////////////////////////////////////////////////////
	/////////////////////////////// GPU /////////////////////////////
	/////////////////////////////////////////////////////////////////

	SCM_GPU scmImagen_GPU(&imagenTest, 256);

	scmImagen_GPU.createSCM(OFFSETS_DEFAULT, 1, SCM_DIRECTION_45);

	scmImagen_GPU.showFileSCM();


	cin.get();

	return 0;
}


