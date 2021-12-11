/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 1 , 2021

This file contains the code for the monte-carlo integral benchmark. The integral which is 
evaluated is the following \int_{0}^{1} \frac{4}{1+x^2} dx = \pi using the Monte Carlo Estimator

*/

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath> 

#include<omp.h>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

double f(double x)
{
    return 4.0/(1+pow(x,2));
}

double mc_integral_timer(gsl_rng* h)
{
    double start_time=omp_get_wtime();
    double computed_VALUE=0;

    int AVG_LENGTH=5000;

    #pragma omp parallel for reduction(+:computed_VALUE)
    for(int n=1;n<=AVG_LENGTH;n++)
    {
        int SAMP_LENGTH=5000;
        double VALUE=0;
        
        for(int m=1;m<=SAMP_LENGTH;m++)
            VALUE=VALUE+(1.0/SAMP_LENGTH)*f(gsl_rng_uniform(h));

        computed_VALUE=computed_VALUE+(VALUE/AVG_LENGTH);
    }

    printf("%0.5lf\n",computed_VALUE);
    double end_time=omp_get_wtime();
    return (end_time-start_time);
}

// Testing Code
// int main(int argc, char* argv[])
// {
//     gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
//     gsl_rng_set(h,time(NULL));
//     srand48(time(NULL));

//     double t=0,pi=0,cpi;
//     for(int i=1;i<=100;i++)
//         t=t+mc_integral_timer(h);
//     printf("Avg=%lf\n",t/100);
//     return 0;
// } 
