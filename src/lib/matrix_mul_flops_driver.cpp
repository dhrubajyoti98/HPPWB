/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 6 , 2021

This file contains the code for SGEMM benchmark
for calculating the FLOPS.
*/

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath> 

#include<omp.h>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

double matrix_mul_flops_timer(gsl_rng* h)
{
    double N=100;
    int niter=10;
    int size=(int)N;

    double alpha=gsl_rng_uniform(h);
    double beta=gsl_rng_uniform(h);

    double A[size][size], B[size][size], C[size][size], D[size][size];
    
    #pragma omp parallel for collapse(2)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            A[i][j]=gsl_rng_uniform(h);
            B[i][j]=gsl_rng_uniform(h);
            C[i][j]=gsl_rng_uniform(h);
        }
    }

    double start_time=omp_get_wtime();
    for(int n=1;n<=niter;n++)
    {
        printf("Iter%d\n",n);
        #pragma omp parallel for collapse(2)
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                D[i][j]=beta*C[i][j];
                #pragma omp simd
                for(int k=0;k<size;k++)
                    D[i][j]=D[i][j]+alpha*A[i][k]*B[k][j];
            }
        }   
    }
    double end_time=omp_get_wtime();

    double flops64=(int)(2*N*N*(N+1)*niter)/(end_time-start_time);
    return flops64/(pow(10,9));
}

//Testing Code
int main(int argc, char* argv[])
{
    gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(h,time(NULL));
    srand48(time(NULL));

    printf("Avg FLOPS64=%lf GFLOPS\n",matrix_mul_flops_timer(h));
    return 0;
}