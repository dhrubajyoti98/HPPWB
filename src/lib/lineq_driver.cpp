/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 3 , 2021

This file contains the code for the Linear Equation benchmark using the 
Gauss-Seidel Method in a N=1000 dimensional system.

*/ 

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include<omp.h>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

double calcError(double* x1, double* x2, int DIM)
{
	double sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<DIM;i++)
		sum=sum+pow(x1[i]-x2[i],2);
	
	return sqrt(sum);
}

double lineq_timer(gsl_rng* h)
{
	double start_time=omp_get_wtime();

	int DIM=(int)atof(getenv("DIM"));

	double* x=new double[DIM];
	double* xnew=new double[DIM];

	double* B=new double[DIM];
	double** A=new double*[DIM];
	for(int i=0;i<DIM;i++)
		A[i]=new double[DIM];

	for(int i=0;i<DIM;i++)
	{
		double sum=0;
		B[i]=gsl_ran_flat(h,0,1);
		x[i]=gsl_ran_flat(h,0,1);
		for(int j=0;j<DIM;j++)
		{
			if(i==j)
				continue;
			else
			{
				A[i][j]=gsl_ran_flat(h,0,1);
				sum=sum+fabs(A[i][j]);
			} 
		}
		A[i][i]=sum+0.5;
	}

	int ITER_COUNT=1, MAX_ITER=(int)atof(getenv("MAX_ITER"));
	double err=pow(10,-1), err_tol=pow(10,-(int)atof(getenv("ERR_TOL")));
	
	while(ITER_COUNT<=MAX_ITER && err > err_tol)
	{
		//printf("IterCount=%d, Err=%lf\n",ITER_COUNT,err);
		for(int i=0;i<DIM;i++)
		{
			double sum1=0, sum2=0;

			#pragma omp parallel for reduction(+:sum1)
			for(int j=0;j<=i-1;j++)
				sum1=sum1+A[i][j]*x[j];		

			#pragma omp parallel for reduction(+:sum2)
			for(int j=i+1;j<DIM;j++)
				sum2=sum2+A[i][j]*x[j];

			xnew[i]=(1.0/A[i][i])*(B[i]-sum1-sum2);
		}
		err=calcError(xnew,x,DIM);

		for(int i=0;i<DIM;i++)
			x[i]=xnew[i];
		
		ITER_COUNT++;
	}

	// for(int i=0;i<DIM;i++)
	// 	printf("%lf\n",x[i]);
	
	for(int i=0;i<DIM;i++)
		delete[] A[i];
	delete[] A;
	delete[] B;
	delete[] x;
	delete[] xnew;

	double end_time=omp_get_wtime();
    return (end_time-start_time);
}

//Testing Code
// int main(int argc, char* argv[])
// {
// 	gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
// 	gsl_rng_set(h,time(NULL));
// 	srand48(time(NULL));

// 	double t=0;
// 	int COUNT=1;
// 	for(int n=1;n<=COUNT;n++)
// 	{
// 		printf("Sample=%d\n",n);
// 		t=t+lineq_timer(h);
// 	}

// 	printf("t=%lf\n",t/COUNT);
// 	return 0;
// }

