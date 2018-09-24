#include<iostream>
#include<cmath>
#include <vector>
typedef double (*fun)(double);
using namespace std;
double fx(double x)
{
	return x*x;
}	
double simpson13(fun fx, double a,double b,int n)
{    
	double h,sum=0;
	vector<double> x,y;
	h=(b-a)/n;                        //Establecemos los subintervalos
	for (int i=0;i<n+1;i++)
	{                        //bucle para evaluar x0,...xn and y0,...yn
		double val1=a+i*h;            //almacenamos en arrays
		x.push_back(val1);
		double val2=fx(x[i]);
		y.push_back(val2);
	}
	for (int i=1;i<n;i+=2)
		sum=sum+4.0*y[i];                //bucle para evaluar 4*(y1+y3+y5+...+yn-1)
	for (int i=2;i<n-1;i+=2)
		sum=sum+2.0*y[i];                /*bucle para evaluar 4*(y1+y3+y5+...+yn-1)+
		2*(y2+y4+y6+...+yn-2)*/ 
	return h/3.0*(y[0]+y[n]+sum); //h/3*[y0+yn+4*(y1+y3+y5+...+yn-1)+2*(y2+y4+y6+...+yn-2)]
	} 
int main()
{
	cout<<simpson13(fx,0,1,6)<<endl;
	return 0;
}	
