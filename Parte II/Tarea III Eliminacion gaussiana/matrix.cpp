#include <iostream>
#include <unordered_map>
using namespace std;
typedef unsigned int Int64;
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
			for(Int64 i=1;i<=m_estructura.size();i++)
			{
				for(Int64 j=1;j<=m_estructura[i].size();j++)
					cout<<m_estructura[i][j]<<" ";
				cout<<endl;
			}	
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
		for(Int64 j = i;j<=rows;j++)
		{
			s+=m1[i][j]*m1[j][cols];
		}
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
	//Ab.disp();
	sustitucionRegresiva(Ab).disp();
}

int main() {
	Matrix<double> M;
	M[1][1]=2; M[1][2]=-1; M[1][3]=3;
	M[2][1]=2; M[2][2]=2; M[2][3]=3;
	M[3][1]=-2; M[3][2]=3; M[3][3]=0;
	/*Matriz columna*/
	Matrix<double> B;
	B[1][1]=5;
	B[2][1]=7;
	B[3][1]=-3;
	EliminacionGaussiana(M,B);
	return 0;
}

