/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 1 , 2021

This file contains the code for the ODE benchmark. This uses the ODE system defined in
Equation 1 of the paper "Ispolatov, I. et al. Chaos in high-dimensional dissipative dynamical systems.
Sci. Rep. 5, 12506; doi: 10.1038/srep12506 (2015)".

Using DIM=150

*/

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

#include<omp.h>

double f(int i, double*** a, double** b, double x[], int DIM)
{
    double val1=0, val2=0;

    #pragma omp parallel for reduction(+:val1,val2)
    for(int j=0;j<DIM;j++)
    {
        val1=val1+b[i][j]*x[j];
        for(int k=0;k<DIM;k++)
            val2=val2+a[i][j][k]*(x[j]*x[k]);
    }
    return val1+val2-pow(x[i],3);
}

void stepForward(double x[], double*** a, double** b, int DIM, double dt)
{
    double temp[DIM], val;
    double M[4][DIM];

    for(int i=0;i<DIM;i++)
        temp[i]=x[i];

    for(int k=0;k<4;k++)
    {
        #pragma omp parallel for
        for(int i=0;i<DIM;i++)
            M[k][i]=dt*f(i,a,b,temp,DIM);

        if(k<=2)
        {
            val=(k==0||k==1)?0.5:1.00;
            for(int i=0;i<DIM;i++)
                temp[i]=x[i]+val*M[k][i];
        }
    }

    for(int i=0;i<DIM;i++)
        x[i]=x[i]+(1/6.0)*(M[0][i]+M[3][i]+2*(M[1][i]+M[2][i]));
}

void initParameter(double*** a, double** b, gsl_rng* h, int DIM)
{
    for(int i=0;i<DIM;i++)
    {
        for(int j=0;j<DIM;j++)
        {
            b[i][j]=gsl_ran_gaussian(h,1);
            for(int k=0;k<DIM;k++)
            {
                a[i][j][k]=gsl_ran_gaussian(h,1);
            }
        }
    }
}
void initState(int DIM, double x1[], gsl_rng* h)
{
    for(int i=0;i<DIM;i++)
    {
        x1[i]=gsl_ran_gaussian(h,DIM);
    }
}

double ode_timer(gsl_rng* h)
{
    double start_time=omp_get_wtime();

    int DIM=150, T=10000;

    double x[DIM];
    initState(DIM,x,h);

    double*** a=new double**[DIM];
    double** b=new double*[DIM];
    for(int i=0;i<DIM;i++)
    {     
        b[i]=new double[DIM];
        a[i]=new double*[DIM];
        for(int j=0;j<DIM;j++)
            a[i][j]=new double[DIM];
    }

    initParameter(a,b,h,DIM);

    double dt=0.1/(DIM*DIM);

    for(int n=1;n<=T;n++)
        stepForward(x,a,b,DIM,dt);

    for(int i=0;i<DIM;i++)
    {   
        delete[] b[i];
        for(int j=0;j<DIM;j++)
            delete[] a[i][j];    
    }
    delete[] b;
    delete[] a;

    double end_time=omp_get_wtime();
    return (end_time-start_time);
}

//Testing Code
// int main(int argc, char* argv[])
// {
//     gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
//     gsl_rng_set(h,time(NULL));
//     srand48(time(NULL));
    
//     double t=0;
//     for(int n=1;n<=5;n++)
//         t=t+ode_timer(h);

//     printf("Avg=%lf\n",t/5);
//     return 0;
// }