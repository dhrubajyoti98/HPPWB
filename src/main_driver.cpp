/*
HPPWB High Performance Physics Workstation Benchmark v0.1.0
author: dhrubajyoti biswas, email: dhrubajyoti98@gmail.com
date: Dec 3 , 2021

This file contains the code for the main driver part.
*/ 

#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

#include "include/direct_integral_driver.hpp"
#include "include/matrix_mul_flops_driver.hpp"
#include "include/mc_integral_driver.hpp"
#include "include/ode_driver.hpp"
#include "include/lineq_driver.hpp"

int main(int argc, char* argv[])
{
    gsl_rng* h=gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(h,time(NULL));
    srand48(time(NULL));

    int RUN_COUNTER;
    int NUM_RUNS=(int)atof(argv[1]);

    double d_integral_time=0, m_integral_time=0;
    double lineq_time=0, ode_time=0;
    double total_time=0;
    double flops=0;

    for(RUN_COUNTER=1;RUN_COUNTER<=NUM_RUNS;RUN_COUNTER++)
    {
        printf("Running Sample %03d of %d.\n",RUN_COUNTER,NUM_RUNS);

        // printf("Running DGEMM...\n");

        // printf("Direct Integral-Trapezoidal Rule, Evaluating Pi...\n");
        // d_integral_time+=direct_integral_timer();

        // printf("Monte-Carlo Integral, Evaluating Pi...\n");
        // m_integral_time+=mc_integral_timer(h);

        // printf("Solving Linear Equations using Gauss-Seidel Method...\n");
        // lineq_time+=lineq_timer(h);

        // printf("Solving a high-dimensional ODE using RK4...\n");
        // ode_time+=ode_timer(h);

        // printf("\n");
        // total_time+=(d_integral_time+m_integral_time+lineq_time+ode_time);
    }

    printf("--------------------------Results-for-%03d-PASSES--------------------------\n",NUM_RUNS);
    printf("| DGEMM                              | %14.4lf Avg. MFLOPS        |\n",flops);
    printf("| Monte-Carlo Integral               | %14.4lf seconds/pass       |\n",m_integral_time);
    printf("| Trapezoidal Integral               | %14.4lf seconds/pass       |\n",d_integral_time);
    printf("| ODE Solver                         | %14.4lf seconds/pass       |\n",ode_time);
    printf("| Gauss Seidel Iteration             | %14.4lf seconds/pass       |\n",lineq_time);
    printf("--------------------------------------------------------------------------\n");

    return 0;
}
