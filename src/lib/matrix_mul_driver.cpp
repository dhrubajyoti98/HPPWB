/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 6 , 2021

This file contains the code for the matrix-multiplication benchmark.

*/

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath> 

#include<omp.h>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

double matrix_mul_timer(gsl_rng* h)
{
    double start_time=omp_get_wtime();

    int N=10000;
    double** C=new double*[N];
    double** A=new double*[N];
    double** B=new double*[N];

    for(int i=0;i<N;i++)
    {
        A[i]=new double[N];
        B[i]=new double[N];
        C[i]=new double[N];
    }

    #pragma omp parallel for collapse(2)
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=gsl_rng_uniform(h);
            B[i][j]=gsl_rng_uniform(h);
            C[i][j]=0;
        }
    }

    #pragma omp parallel for collapse(3)
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            for(int k=0;k<N;k++)
                C[i][j]=C[i][j]+A[i][k]*B[k][j];
        }
    }

    for(int i=0;i<N;i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    double end_time=omp_get_wtime();
    return (end_time-start_time);
}

//Testing Code
// int main(int argc, char* argv[])
// {
//     double t=0;
//     gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
//     gsl_rng_set(h,time(NULL));
//     srand48(time(NULL));

//     int NUM=10;

//     for(int COUNT=1;COUNT<=NUM;COUNT++)
//         t=t+matrix_mul_timer(h);

//     printf("Avg=%lf\n",t/NUM);
//     return 0;
// }