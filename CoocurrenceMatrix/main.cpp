#include <iostream>
#include "SCM.h"
#include "spaceConversion.h"
#include "imgOperaciones.h"

using namespace std;

void main(){

	/*
	//Prueba imagen

	Image imagenTest("test1.txt");

	imagenTest.createMat();

	Mat imagenGray = imageGray(imagenTest.imagenMat);
	
	Mat imagenEscala = imageResize(imagenGray,100,100);

	namedWindow("ENTRADA", 1);
	imshow("ENTRADA", imagenEscala);

	waitKey(0);

	imagenTest.showPixelMat_1C();
	


	SCM matrizSCM(&imagenTest, OFFSETS_DEFAULT, 1, SCM_DIRECTION_0);

    matrizSCM.createSCM(NIVEL_GRISES);

	matrizSCM.showFileSCM();

	matrizSCM.calcDescriptores();

	matrizSCM.showDescriptores();

	*/
	
	Image imagenTest("BD/img.jpg",1);

	Mat imagenGray = imageGray(imagenTest.imagenMat);

	namedWindow("ENTRADA", 1);
	imshow("ENTRADA", imagenGray);

	waitKey(0);
	


	SCM matrizSCM(&imagenTest, OFFSETS_DEFAULT, 1, SCM_DIRECTION_0);

    matrizSCM.createSCM(NIVEL_GRISES);

	matrizSCM.showFileSCM();

	matrizSCM.calcDescriptores();

	matrizSCM.showDescriptores();

	waitKey(0);




	cin.get();
}


