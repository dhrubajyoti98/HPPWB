/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 1 , 2021

This file contains the code for the direct integral benchmark. The integral which is 
evaluated is the following \int_{0}^{1} \frac{4}{1+x^2} dx = \pi using the Trapezoidal method.

*/

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath> 
#include<omp.h>

double g(double x)
{
    return 4.0/(1+pow(x,2));
}

double direct_integral_timer()
{
    double start_time=omp_get_wtime();

    double actual_VALUE=M_PI;
    double computed_VALUE=0;

    int COUNT=100000;
    double h=1.0/COUNT;

    #pragma omp parallel for reduction(+:computed_VALUE)
    for(int n=0;n<COUNT;n++)
        computed_VALUE=computed_VALUE+0.5*h*(g(n*h)+g((n+1)*h));

    //printf("%lf\n",computed_VALUE);
    double end_time=omp_get_wtime();
    
    return (end_time-start_time);
}

// Testing_Code
// int main(int argc, char* argv[])
// {
//     double t=0;
//     for(int i=1;i<=10000;i++)
//         t=t+direct_integral_timer();
//     printf("Avg=%lf\n",t/10000);
//     return 0;
// } 
