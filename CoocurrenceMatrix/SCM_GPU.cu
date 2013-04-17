
#include "SCM_GPU.cuh"

#include <iostream>
#include <fstream>
#include <math.h>


#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "cuPrintf.cu"

#if __CUDA_ARCH__ < 200 	//Compute capability 1.x architectures
#define CUPRINTF cuPrintf 
#else						//Compute capability 2.x architectures
#define CUPRINTF(fmt, ...) printf("[%d, %d]:\t" fmt, \
								blockIdx.y*gridDim.x+blockIdx.x,\
								threadIdx.z*blockDim.x*blockDim.y+threadIdx.y*blockDim.x+threadIdx.x,\
								__VA_ARGS__)
#endif


SCM_GPU::SCM_GPU(Image *imagen, int numNiveles){

	this->imagen = imagen;
	this->pixelMat_h = imagen->pixelMat;

	this->numNiveles = numNiveles;

	rows = numNiveles;
    cols = numNiveles;

	arraySize = rows*cols;
	
	//AsignarMemoria
    matrizSCM_h = new int[arraySize];

    //Inicializar con 0
    for (int i = 0; i < arraySize; ++i)
		matrizSCM_h[i] = 0;

	//Inicializar memoria device
	inicializar_MemDevice();

	//Inicializar variables GPU
	inicializar_VarsGPU();

}

void SCM_GPU::inicializar_MemDevice(){

	//////////// Memoria de imagen en device //////////////////

	size_t size_imagen = imagen->arraySize*sizeof(Pixel);

	cudaMalloc((void**)&pixelMat_d, size_imagen);

	cudaMemcpy(pixelMat_d,pixelMat_h,size_imagen,cudaMemcpyHostToDevice);


	//////////// Memoria de SCM en device //////////////////

	size_t size_matrizSCM = arraySize*sizeof(int);

	cudaMalloc((void**)&matrizSCM_d, size_matrizSCM);

	cudaMemcpy(matrizSCM_d,matrizSCM_h,size_matrizSCM,cudaMemcpyHostToDevice);
}

void SCM_GPU::inicializar_VarsGPU(){

	int numThreads = 32;

	Grid_Dim_x=imagen->rows, Grid_Dim_y=imagen->cols;	//Grid structure values

	Block_Dim_x=numThreads, Block_Dim_y=numThreads;	//Block structure values


	Grid = dim3( ceil(Grid_Dim_x*1.0/numThreads), ceil(Grid_Dim_y*1.0/numThreads) );		//Grid structure

	Block = dim3(Block_Dim_x,Block_Dim_x);	//Block structure, threads/block limited by specific device
}


__global__ 
void createSCM_kernel(Pixel*pixelMat,int imgRows,int imgCols,
					  int*matrizSCM, int numNiveles, int delta_i,int delta_j)
					  
{

	int i = blockIdx.y*blockDim.y+threadIdx.y;
	int j = blockIdx.x*blockDim.x+threadIdx.x;
	
    int cols = numNiveles;

	int posx,posy;

	//CUPRINTF("i = %d  \n",i);
	//CUPRINTF("j = %d  \n",j);

    if ( (j + delta_j) < imgCols && (i + delta_i) < imgRows && 
		((j + delta_j) >= 0) && ((i + delta_i) >= 0) )
	{
        posx = pixelMat[i*imgCols+j].canal_0;
		posy = pixelMat[(i + delta_i)*imgCols+(j + delta_j)].canal_0;

		atomicAdd(&matrizSCM[posx*cols+posy], 1);
		
        atomicAdd(&matrizSCM[posy*cols+posx], 1);

    }
	__syncthreads();
}


void SCM_GPU::createSCM(int* offsets, int distance, int direction){

	this->distance = distance;
	this->direction = direction;
	
	this->delta_j = offsets[(this->direction)*this->distance];
    this->delta_i = offsets[(this->direction + 1)*this->distance];
	
	int posx,posy,i,j;

	//Inicializar con 0
    for (int i = 0; i < arraySize; ++i)
		matrizSCM_h[i] = 0;


	//Ejecutar kernel
	createSCM_kernel<<<Grid,Block>>>(pixelMat_d,imagen->rows,imagen->cols,
									 matrizSCM_d,numNiveles,delta_i,delta_j);

	cudaThreadSynchronize();


	copiar_DeviceHost();
}


void SCM_GPU::copiar_DeviceHost(){

	/////////////////// Variables del device al host ///////////////////////// 

	// Retrieve result from device to host in the host memory
	//cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind)
	cudaMemcpy(matrizSCM_h,matrizSCM_d,sizeof(int)*arraySize,cudaMemcpyDeviceToHost);
}


void SCM_GPU::showFileSCM(){

	ofstream ficheroSCM("SCM_GPU.txt");

	for (int i = 0; i < arraySize; ++i) {
		if(i%cols==0) ficheroSCM<<endl;

		ficheroSCM<<matrizSCM_h[i]<<'\t';
		
	}
	//cout<<"TERMINO\n";
	ficheroSCM.close();
}


SCM_GPU::~SCM_GPU() {

	// liberar memoria en el device y host 
	//free(imagen_h);
	//cudaFree(imagen_d);
	free(matrizSCM_h);
	cudaFree(matrizSCM_d);
}