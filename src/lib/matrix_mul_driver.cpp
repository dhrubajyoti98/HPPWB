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

    int N=1000;
    double** C=new double*[N];
    double** A=new double*[N];
    double** B=new double*[N];

    for(int i=0;i<N;i++)
    {
        A[i]=new double[N];
        B[i]=new double[N];
        C[i]=new double[N];
    }

    #pramga omp parallel for
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

    double end_time=omp_get_wtime();
    return (end_time-start_time);
}