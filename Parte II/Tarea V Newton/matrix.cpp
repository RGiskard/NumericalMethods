#include <iostream>
#include <unordered_map>
using namespace std;
typedef unsigned int Int64;
typedef float (*fun)(float, float);
template<typename T> 
class Matrix
{
	typedef unordered_map<Int64,T> Fila;
	typedef unordered_map<Int64,Fila> Estructura;
	private:
		Estructura m_estructura;
	public:
		Matrix()
			:m_estructura(){}
		Fila & operator[](Int64 index)
		{
			return m_estructura[index];
		}
		Int64 size()
		{
			return m_estructura.size();
		}
		/*Sólo se podrán mostrar en caso ya se hayan ingresado los datos
		a la matrix*/
		Int64 getnumRows()
		{
			return m_estructura.size();
		}	
		Int64 getnumCols()
		{
			return m_estructura[1].size();
		}
		void disp()
		{
			for(Int64 i=1;i<=getnumRows();i++)
			{
				for(Int64 j=1;j<=getnumCols();j++)
					cout<<m_estructura[i][j]<<" ";
				cout<<endl;
			}	
		}	
		
		Matrix<T> nullMatrix()
		{
			Matrix<T> M;
			for(Int64 i=1;i<=getnumRows();i++)
				for(Int64 j=1;j<=getnumCols();j++)
					M[i][j]=0;
			return M;
		}
		
		Matrix<T> identidad()
		{
			Matrix<T> M;
			Int64 n=this->getnumCols();
			for(Int64 i=1;i<=n;i++)
				for(Int64 j=1;j<=n;j++)
				{
					if(i==j)
						M[i][j]=1;
					else
						M[i][j]=0;
				}
			return M;
		}
		
		Matrix<T>  escalonar(Matrix<T>& MM)
		{
			Matrix<T> M=*this;
			Int64 n=M.size();
			T m;
			for(Int64 j=1;j<n;j++)
				for(Int64 i=j+1;i<=n;i++)
				{
					m=(M[i][j]/M[j][j]);
					for(Int64 k=1;k<n+1;k++)
						M[i][k]-=m*M[j][k];
						MM[i][j] = m;	
				}	
			return M;
		}
		
		Matrix<T> inverza()
		{
			return identidad();
		}
		
		Matrix<T> operator*(Matrix<T>&MM)
		{
			Matrix<T> prod;
			for(Int64 i=1; i<=getnumRows(); i++)
				for(Int64 j=1; j<=MM.getnumCols();j++)
					for(Int64 k = 1; k<=MM.getnumRows();k++)
						prod[i][j] += m_estructura[i][k]*MM[k][j];
			
			return prod;
		}
		
		Matrix<T> operator +(Matrix<T> &MM)
		{
			Matrix<T> R;
			for(Int64 i = 1; i<=getnumRows() ; i++)
				for(Int64 j = 1; j<=getnumCols(); j++)
					R[i][j] = m_estructura[i][j] + MM[i][j];
			return R;
		}
		
		
		
};

template<typename T>
Matrix<T> sustitucionRegresiva(Matrix<T> &m1)
{
	Matrix<T> R;
	Int64 rows=m1.getnumRows();
	Int64 cols=m1.getnumCols();
	for(Int64 i=rows;i>=1;--i)
	{
		T s=0;
		for(Int64 j = i+1;j<=rows;j++)
			s+=m1[i][j]*m1[j][cols];
		R[i][1] = (m1[i][cols]-s)/m1[i][i];
	}
	return R;
}

/*Para el ingresar datos, utilizaremos los indices i j k que empezaran desde 1*/
template<typename T>
Matrix<T> matrizAumentada(Matrix<T> m1,Matrix<T> m2)
{
	Int64 index=m1.getnumCols()+1;
	Matrix<T> R=m1;
	for(Int64 i=1;i<=m1.getnumRows();i++)
		R[i][index]=m2[i][1];
	return R;
}

template<typename T>
void EliminacionGaussiana(Matrix<T> A,Matrix<T>b){
	//Matriz Aumentada
	Int64 n=A.size();
	Matrix<T> Ab=matrizAumentada(A,b);
	T m;
	for(Int64 j=1;j<n;j++)
	{
		for(Int64 i=j+1;i<=n;i++)
		{
			m=-(Ab[i][j]/Ab[j][j]);
			for(Int64 k=1;k<=n+1;k++)
				Ab[i][k]=Ab[i][k]+m*Ab[j][k];
		}	
	}
	Ab.disp();
	sustitucionRegresiva(Ab).disp();
}

/*Evaluar una matriz de funciones devolviendo floats*/
Matrix<double> eval(Matrix<fun> &matriz,double x,double y)
{
	Matrix<double> R;
	for(Int64 i=1;i<=matriz.getnumRows();i++)
		for(Int64 j=1;j<=matriz.getnumCols();j++)
			R[i][j]=(matriz[i][j])(x,y);
	return R;
}

Matrix<double> newtowMatrix(Matrix<fun> &F,Matrix<fun> J,Matrix<double> &B,Matrix<double> X0,Int64 max)
{
	Matrix<double> X;
	for(Int64 n=0;n<max;n++)
		for(Int64 i=1;i<=B.getnumRows();i++)
		{
			Matrix<double> JI=(eval(J,X0[1][1],X0[1][1])).inverza();
			Matrix<double> FE=eval(F,X0[1][1],X0[1][1]);
			Matrix<double> P=JI*FE;
			X[i][1]=B[i][1]-P[i][1];//-((eval(J,X0[1][1],X0[2][1])).inverza());
		}	
	return X;
}	


float f1(float x,float y){
	return x*x+y*y-1;
}
float f2(float x,float y){
	return x-y;
}

float df1x(float x,float y){
	return 2*x;
}

float df1y(float x,float y){
	return 2*y;
}

float df2x(float x,float y){
	return 1;
}
float df2y(float x,float y){
	return -1;
}


int main() {
	/*Matrix<double> M;
	M[1][1]=2;  M[1][2]=-1; M[1][3]=3;
	M[2][1]=2;  M[2][2]=2;  M[2][3]=3;
	M[3][1]=-2; M[3][2]=3;  M[3][3]=0;*/
	/*Matriz columna*/
	/*Matrix<double> B;
	B[1][1]=5;
	B[2][1]=7;
	B[3][1]=-3;
	EliminacionGaussiana(M,B);*/

	//typedef float (*)(float, float) fun;
	Matrix<fun> F;
	Matrix<fun> J;
	J[1][1]=df1x;	J[1][2]=df1y;
	J[2][1]=df2x;	J[2][2]=df2y;
	F[1][1]=f1;
	F[1][2]=f2;
	eval(J,1,1).disp();
	return 0;
}

