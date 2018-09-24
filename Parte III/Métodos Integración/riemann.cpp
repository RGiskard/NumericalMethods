#include <iostream>
#include <stdlib.h> 
#include <math.h>
typedef double (*fun)(double);
using namespace std;
double fx(double x)
{
	return x*x;
}	
double riemann(fun fx, double a,double b,int N)
{
	double dX=fabs(a-b)/N;
	double sum(0.0);
	double x=a;
	while(x<=b)
	{
		sum+=fx(x)*dX;
		x+=dX;
	}
	return sum;
}	


int main()
{
	cout<<riemann(fx,0,1,20)<<endl;
	return 0;
}	
