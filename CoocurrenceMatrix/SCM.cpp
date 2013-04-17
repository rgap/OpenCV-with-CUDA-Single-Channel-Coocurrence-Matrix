#include "SCM.h"
#include <iostream>
#include <fstream>



using namespace std;

SCM::SCM(Image *imagen, int numNiveles) {

	this->imagen = imagen;
	this->numNiveles = numNiveles;

	rows = numNiveles;
    cols = numNiveles;

	arraySize = rows*cols;

	//AsignarMemoria
    matrizSCM = new int[arraySize];

    //Inicializar con 0
    for (int i = 0; i < arraySize; ++i)
		matrizSCM[i] = 0;

}

int * SCM::createSCM(int* offsets, int distance, int direction) {

	this->distance = distance;
	this->direction = direction;
	
	this->delta_j = offsets[(this->direction)*this->distance];
    this->delta_i = offsets[(this->direction + 1)*this->distance];
	
	int posx,posy,i,j;

	//Inicializar con 0
    for (int i = 0; i < arraySize; ++i)
		matrizSCM[i] = 0;

    for (i = 0; i < imagen->rows; ++i) {
        for (j = 0; j < imagen->cols; ++j) {

            if ( (j + delta_j) < imagen->cols && (i + delta_i) < imagen->rows && 
				((j + delta_j) >= 0) && ((i + delta_i) >= 0) )
			{
                posx = imagen->pixelMat[i*imagen->cols+j].canal_0;
				posy = imagen->pixelMat[(i + delta_i)*imagen->cols+(j + delta_j)].canal_0;

                matrizSCM[posx*cols+posy]++;
                matrizSCM[posy*cols+posx]++;

            }

        }
    }

    return matrizSCM;
}

void SCM::calcDescriptores(){

	double ASM = 0; //angular second moment, uniformity
	double contrast = 0;
	double correlation = 0;
	double variance = 0; //sum of squares
    double homogeneity = 0; //inverse difference moment
	double entropy = 0;

    double dissimilarity = 0;
    double mean = 0;

	double energy = 0;
	double standardDesv = 0;

	int i,j;

    for (i = 0; i < rows; ++i) {
        for ( j = 0; j < cols; ++j) {
            homogeneity += (matrizSCM[i*cols+j] / (1 + (i - j)*(i - j)) );

            contrast += matrizSCM[i*cols+j] * (i - j)*(i - j);

            dissimilarity += matrizSCM[i*cols+j] * abs(i - j);

            ASM += matrizSCM[i*cols+j] * matrizSCM[i*cols+j];

            if (matrizSCM[i*cols+j] != 0)
                entropy -= ( matrizSCM[i*cols+j] * log((float)matrizSCM[i*cols+j]) );

            mean += i * matrizSCM[i*cols+j];
        }
    }

    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j)
            variance += matrizSCM[i*cols+j] * (i - mean)*(i - mean);

    for (i = 0; i < rows; ++i)
        for (j = 0; j < cols; ++j)
            correlation += matrizSCM[i*cols+j]*(i - mean)*(j - mean) / sqrt(variance * variance);

	energy = sqrt(ASM);

	standardDesv = sqrt(variance);

    descriptores = new double[10];

	descriptores[0] = ASM;
	descriptores[1] = contrast;
	descriptores[2] = correlation;
	descriptores[3] = variance;
    descriptores[4] = homogeneity;
	descriptores[5] = entropy;

    descriptores[6] = dissimilarity;
    descriptores[7] = mean;

	descriptores[8] = energy;
	descriptores[9] = standardDesv;

}

void SCM::showDescriptores(){
	cout<<"ASM = "<<descriptores[0]<<endl;
	cout<<"contrast = "<<descriptores[1]<<endl;
	cout<<"correlation = "<<descriptores[2]<<endl;
	cout<<"variance = "<<descriptores[3]<<endl;
	cout<<"homogeneity = "<<descriptores[4]<<endl;
	cout<<"entropy = "<<descriptores[5]<<endl;
	cout<<"dissimilarity = "<<descriptores[6]<<endl;
	cout<<"mean = "<<descriptores[7]<<endl;
	cout<<"energy = "<<descriptores[8]<<endl;
	cout<<"standardDesv = "<<descriptores[9]<<endl;
}

double *SCM::getDescriptores(){
	return descriptores;
}

void SCM::showSCM(){

	for (int i = 0; i < arraySize; ++i) {
		if(i%cols==0) cout<<endl;
		
		cout<<matrizSCM[i]<<'\t';
	}
	cout<<"TERMINO\n";
}

void SCM::showFileSCM(){

	ofstream ficheroSCM("SCM.txt");

	for (int i = 0; i < arraySize; ++i) {
		if(i%cols==0) ficheroSCM<<endl;

		ficheroSCM<<matrizSCM[i]<<'\t';
		
	}
	//cout<<"TERMINO\n";
	ficheroSCM.close();
}



void SCM::NormalizarSCM() {
    int total = 0,i;
    for (i = 0; i < arraySize; ++i)
		total += matrizSCM[i];

    for (i = 0; i < arraySize; ++i)
		matrizSCM[i] = matrizSCM[i] / total;
}


SCM::~SCM(){
	//delete[] matrizSCM;
	//free(matrizSCM);
	//delete[] imagen;
	//delete[] descriptores;
	//free(descriptores);
}

