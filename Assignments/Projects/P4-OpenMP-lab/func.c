/* File Name: func.c */
/* Student Name: Jason Less */
/* Student ID Number: 404-640-158 */

#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
    
    double calcTemp = 1/((double)(n));
    double dxr = xr;
    double dyr = yr;
    
    #pragma omp parallel for num_threads(27) private(i) firstprivate(n, weights, calcTemp, arrayX, dxr, arrayY, dyr)
	for(i = 0; i < n; i++){
		weights[i] = calcTemp;
		arrayX[i] = dxr;
		arrayY[i] = dyr;
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;

    int reduceMultiplication, reduceMultiplicationOne, reduceMultiplicationTwo, reduceMultiplicationThree, reduceIndexFunctionCall, reduceArrayFunctionCall;
    double probTemp;
    double onesTemp = (double) Ones;
    
    #pragma omp parallel for num_threads(27) private(i) firstprivate(n, arrayX, seed, arrayY)
   	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
   	}

    #pragma omp parallel for num_threads(27) private(i, j, index_X, index_Y, \
    reduceMultiplication, reduceMultiplicationOne, reduceMultiplicationTwo, \
    reduceMultiplicationThree, reduceIndexFunctionCall, reduceArrayFunctionCall, probTemp) \
    firstprivate(n, Ones, arrayX, objxy, arrayY, index, Y, Z, iter, max_size, array, probability, \
    onesTemp)
    
   	for(i = 0; i<n; i++)
    {
        reduceMultiplication = i * Ones;
   		for(j = 0; j < Ones; j++)
        {
            reduceMultiplicationOne = j * 2;
            reduceMultiplicationTwo = reduceMultiplication + j;
            
   			index_X = round(arrayX[i]) + objxy[reduceMultiplicationOne + 1];
   			index_Y = round(arrayY[i]) + objxy[reduceMultiplicationOne];
   			reduceIndexFunctionCall = fabs(index_X*Y*Z + index_Y*Z + iter);
            index[reduceMultiplicationTwo] = (reduceIndexFunctionCall >= max_size) ? 0 : reduceIndexFunctionCall;
   		}
        
        probTemp = 0;
        
   		for(j = 0; j < Ones; j++)
        {
            reduceMultiplicationThree = reduceMultiplication + j;
            reduceArrayFunctionCall = array[index[reduceMultiplicationThree]];
   			probTemp += (pow((reduceArrayFunctionCall - 100),2) -
   							  pow((reduceArrayFunctionCall-228),2))/50.0;
   		}
        probability[i] = probTemp / onesTemp;
   	}
}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
    
    double weight1;

    #pragma omp parallel for num_threads(27) private(i, weight1) firstprivate(n, weights, probability) reduction(+:sumWeights)
	for(i = 0; i < n; i++)
    {
        weight1 = weights[i] * exp(probability[i]);
        weights[i] = weight1;
        sumWeights += weight1;
    }

    #pragma omp parallel for num_threads(27) private(i, weight1) firstprivate(n, weights, sumWeights)
	for(i = 0; i < n; i++)
    {
        weight1 = weights[i];
   		weight1 = weight1/sumWeights;
        weights[i] = weight1;
    }
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;
    
    double weight2;

    #pragma omp parallel for num_threads(27) private(i, weight2) firstprivate(n, arrayX, weights, arrayY) reduction(+:estimate_x, estimate_y)
	for(i = 0; i < n; i++){
        weight2 = weights[i];
   		estimate_x += arrayX[i] * weight2;
   		estimate_y += arrayY[i] * weight2;
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;

    double uCalcTemp = (double) n;
    
    #pragma omp parallel for num_threads(27) private(i) firstprivate(n, u, u1, uCalcTemp)
	for(i = 0; i < n; i++){
        u[i] = u1 + i/uCalcTemp;
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;

    double weightCalc = 1/((double)(n));
    
    #pragma omp parallel for num_threads(27) private(i, j) firstprivate(n, cfd, u, x_j, arrayX, y_j, arrayY)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}

    #pragma omp parallel for num_threads(27) private(i) firstprivate(n, arrayX, x_j, arrayY, y_j, weights, weightCalc)
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = weightCalc;
	}
}
