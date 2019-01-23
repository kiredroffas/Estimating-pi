/* Erik Safford
   Programming Assignment 4 - Estimating Pi
   CS 330
   December 2018 
   
   Build this program with: gcc -o '___' estimatePi.c 
   Run the executable '___'                            */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288 /* pi */
#endif

long double trapezoidRule(long double a, long double b, int n); //Prototypes
long double simpsonOneThirdRule(long double a, long double b, int n);
long double simpsonThreeEighthsRule(long double a, long double b, int n);
long double booleRule(long double a, long double b, int n);

//This definite integral numerically estimates pi
//pi = 4*arctan1 = integral from 0 to 1, (4/(1 + x^2)) dx
long double f(long double x) {
  return 4.0L/(1.0L + x*x);
}

//Estimate pi using Trapezoid Rule, return error
// (1/2)h * [ f(x0) + f(x1) ]
long double trapezoidRule(long double a, long double b, int n) {
  long double approximation = 0;
  long double h = (b - a)/n;
  long double x0 = 0;
  long double x1 = h;

  for(int i=0;i < n;i++) {
    approximation = approximation + ( (0.5*h) * (f(x0) + f(x1)) );
    x0 = x1;
    x1 += h; 
  }
  
  long double TRerror = fabsl(M_PI - approximation);
  return(TRerror); 
}

//Estimate pi using Simpson's One Third Rule, return error
// (1/3)h * [ f(x0) + 4*f(x1) + f(x2) ]
long double simpsonOneThirdRule(long double a, long double b, int n) {
  long double approximation = 0;
  long double h = (b - a)/n;
  long double x0 = 0;
  long double x1 = h;
  long double x2 = h + h;
  int loops = n/2; //Loop half the number of n (i.e. n=12 -> loop 6 times)

  for(int i=0;i < loops;i++) {
    approximation = approximation + ((h/3) * (f(x0) + (4 * f(x1)) + f(x2)));
    x0 += 2*h;
    x1 += 2*h;
    x2 += 2*h;
  }

  long double SOTerror = fabsl(M_PI - approximation);
  return(SOTerror);
}

//Estimate pi using Simpson's Three Eighths Rule, return error
// (3/8)h * [ f(x0) + 3*f(x1) + 3*f(x2) + f(x3) ]
long double simpsonThreeEighthsRule(long double a, long double b, int n) {
  long double approximation = 0;
  long double h = (b-a)/n;
  long double x0 = 0;
  long double x1 = h;
  long double x2 = h*2;
  long double x3 = h*3;
  
  for(int i=0;i < n;i+=3) {
    approximation += (3*h/8) * ( f(x0) + (3*f(x1)) + (3*f(x2)) + f(x3) );  
    x0 += h*3;
    x1 += h*3;
    x2 += h*3;
    x3 += h*3;
  } 

  long double STEerror = fabsl(M_PI - approximation);
  return(STEerror);
}

//Estimate pi using Boole's Rule, return error
// (2/45)h * [ 7*f(x0) + 32*f(x1) + 12*f(x2) + 32*f(x3) + 7*f(x4) ]
long double booleRule(long double a, long double b, int n) {
  long double approximation = 0;
  long double h = (b-a)/n;
  long double x0 = 0;
  long double x1 = h;
  long double x2 = h*2;
  long double x3 = h*3;
  long double x4 = h*4;

  for(int i=0;i < n;i+=4) {
    approximation += (2*h/45) * ( 7*f(x0) + 32*f(x1) + 12*f(x2) + 32*f(x3) + 7*f(x4) );
    x0 += h*4;
    x1 += h*4;
    x2 += h*4;
    x3 += h*4;
    x4 += h*4;
  }

  long double BRerror = fabsl(M_PI - approximation);
  return(BRerror);
}

int main() {  	

  long double a = 0;  //pi = 4*arctan1 = integral from 0(a) to 1(b), (4/(1 + x^2)) dx
  long double b = 1;


  for(int n=12;n < 786433;n*=2) { //Values of n start at 12 and double until 786432

    //Calculate errors using Trapezoid Rule, Simpson's 1/3 Rule, Simpson's 3/8 Rule, and Boole's Rule	    
    long double tRuleError = trapezoidRule(a,b,n);
    long double sOneThirdError = simpsonOneThirdRule(a,b,n); 
    long double sThreeEighthsError = simpsonThreeEighthsRule(a,b,n);
    long double booleRuleError = booleRule(a,b,n);
    printf("%d %0.10Le %0.10Le %0.10Le %0.10Le\n",n,tRuleError,sOneThirdError,sThreeEighthsError,booleRuleError);
  }
  return 0;
}
