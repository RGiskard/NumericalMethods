#include<iostream>
#include<cmath>
#include <vector>
typedef double (*fun)(double);
using namespace std;
double fx(double x)
{
	return x*x;
}	
double trapezoidal(fun fx, double a,double b,int n)
{
	double h,sum=0,integral;       
	vector<double> x,y;    
	h=(b-a)/n;                //get the width of the subintervals
	for (int i=0;i<=n;i++)            
	{                         //loop to evaluate x0,...xn and y0,...yn
		double val1=a+i*h;            //and store them in arrays
		x.push_back(val1);
		double val2=fx(x[i]);
		y.push_back(val2);
	}
	for (int i=1;i<n;i++)            //loop to evaluate h*(y1+...+yn-1)
	{
		sum=sum+h*y[i];
	}
	return h/2.0*(y[0]+y[n])+sum;        //h/2*[y0+yn+2(y1+y2+y3+...yn-1)]
}
int main()
{
	cout<<trapezoidal(fx,0,1,20)<<endl;
	return 0;
}	
