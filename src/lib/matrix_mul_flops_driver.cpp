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
    long long int N=1000;
    int niter=100;

    double alpha=gsl_rng_uniform(h);
    double beta=gsl_rng_uniform(h);

    double A[N][N], B[N][N], C[N][N], D[N][N];
    
    #pragma omp parallel for collapse(2)
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=gsl_rng_uniform(h);
            B[i][j]=gsl_rng_uniform(h);
            C[i][j]=gsl_rng_uniform(h);
        }
    }

    double start_time=omp_get_wtime();
    for(int n=1;n<=niter;n++)
    {
        #pragma omp parallel for collapse(2) schedule(static)
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                double val=0;

                #pragma omp parallel for reduction(+:val)
                for(int k=0;k<N;k++)
                    val=val+(A[i][k]*B[k][j]);

                D[i][j]=alpha*val+beta*C[i][j];
            }
        }   
    }
    double end_time=omp_get_wtime();

    double flops64=(2*N*N*(N+1)*niter)/(end_time-start_time);
    return flops64;
}

//Testing Code
int main(int argc, char* argv[])
{
    gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(h,time(NULL));
    srand48(time(NULL));

    printf("FLOPS64=%lf GFLOPS\n",matrix_mul_flops_timer(h)/pow(10,9));
    return 0;
}