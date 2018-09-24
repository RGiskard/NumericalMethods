#include<iostream>
#include<cmath>
#include <vector>
typedef double (*fun)(double);
using namespace std;
double fx(double x)
{
	return x*x;
}	
double simpson38(fun fx, double a,double b,int n)
{   
	double h,sum=0,integral;
	vector<double> x,y;
	h=(b-a)/n;                        //get the width of the subintervals
	for (int i=0;i<n+1;i++)
	{                        //loop to evaluate x0,...xn and y0,...yn
		double val1=a+i*h;            //and store them in arrays
		x.push_back(val1);
		double val2=fx(x[i]);
		y.push_back(val2);
	}
	for (int i=1;i<n;i++)
	{
		if (i%3==0)
			sum=sum+2*y[i];
		else
			sum=sum+3*y[i];
	}
	return 3.0*h/8.0*(y[0]+y[n]+sum); 
}
int main()
{
	cout<<simpson38(fx,0,1,6)<<endl;
	return 0;
}	
