#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<double>> Matrix;

Matrix gaussSeidel(Matrix &A,Matrix &b,Matrix &X0,int Nmax)
{
	Matrix X;
	int n=A.size();
	for(int m=0;m<Nmax;m++)
	{
		X=X0;
		for(int i=0;i<n;i++)
		{
			double s=0;
			for(int k=0;k<n;k++)
			{
				s+=A[i][k]*X[i][k];
			}
			X0[i][0]=(b[i][0]-s+A[i][i]*X[i][0])/A[i][i];
			x[i] = x0[i];
		}	
	}
	return X0;
}	

int main() 
{
	/*Definición de la matrix cuadrada*/
	Matrix M;
	double f1[] = {4,-1,0};
	std::vector<double> fila1 (f1, f1 + sizeof(f1) / sizeof(double) );
	double f2[] = {-1,4,-1};
	std::vector<double> fila2 (f2, f2 + sizeof(f2) / sizeof(double) );
	double f3[] = {0,-1,4};
	std::vector<double> fila3 (f3, f3 + sizeof(f3) / sizeof(double) );
	M.push_back(fila1);
	M.push_back(fila2);
	M.push_back(fila3);
	/*Definición de la matrix columna*/
	Matrix R;
	double f01[] = {2};
	std::vector<double> fila01 (f01, f01 + sizeof(f01) / sizeof(double) );
	double f02[] = {6};
	std::vector<double> fila02 (f02, f02 + sizeof(f02) / sizeof(double) );
	double f03[] = {2};
	std::vector<double> fila03 (f03, f03 + sizeof(f03) / sizeof(double) );
	R.push_back(fila01);
	R.push_back(fila02);
	R.push_back(fila03);
	
	/*Definición de la matrix columna para la aproximacion inicial*/
	Matrix Aprox;
	double f001[] = {0};
	std::vector<double> fila001 (f001, f001 + sizeof(f001) / sizeof(double) );
	double f002[] = {0};
	std::vector<double> fila002 (f002, f002 + sizeof(f002) / sizeof(double) );
	double f003[] = {0};
	std::vector<double> fila003 (f003, f003 + sizeof(f003) / sizeof(double) );
	Aprox.push_back(fila001);
	Aprox.push_back(fila002);
	Aprox.push_back(fila003);
	Matrix Respuesta=jacobi(M,R,Aprox,5);
	/*Impresion de la matri Respuesta*/
	cout<<Respuesta[0][0]<<endl;
	cout<<Respuesta[1][0]<<endl;
	cout<<Respuesta[2][0]<<endl;
	return 0;
}

