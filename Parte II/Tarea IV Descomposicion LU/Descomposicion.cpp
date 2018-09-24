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
	
	Matrix<T> identidad()
	{
		Matrix<T> M;
		Int64 n=this->getnumCols();
		for(Int64 i=1;i<=n;i++)
		{
			for(Int64 j=1;j<=n;j++)
			{
				if(i==j)
					M[i][j]=1;
				else
					M[i][j]=0;
			}
		}
		return M;
	}
	
	Matrix<T>  escalonar(Matrix<T>& MM)
	{
		Matrix<T> M=*this;
		Int64 n=M.size();
		T m;
		for(Int64 j=1;j<n;j++)
		{
			for(Int64 i=j+1;i<=n;i++)
			{
				m=(M[i][j]/M[j][j]);
				for(Int64 k=1;k<n+1;k++)
					M[i][k]-=m*M[j][k];
				MM[i][j] = m;	
			}	
		}
		return M;
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
Matrix<T> DescomposicionLU(Matrix<T> &A,Matrix<T> &b){
	Int64 n = A.size();
	Matrix<T> L=A.identidad();
	Matrix<T> U=A.escalonar(L);
	Matrix<T> x,y;
	cout<<"Matriz A"<<endl;
	A.disp();
	cout<<"------------"<<endl;
	cout<<"Matriz U"<<endl;
	U.disp();
	cout<<"------------"<<endl;
	cout<<"Matriz L"<<endl;
	L.disp();
	
	return y;
}






int main() {
	Matrix<double> A,M1,M2;
	A[1][1]=4;  A[1][2]=-2; A[1][3]=1;
	A[2][1]=20; A[2][2]=-7; A[2][3]=12;
	A[3][1]=-8; A[3][2]=13; A[3][3]=17;
	//
	Matrix<double> b;
	b[1][1]=11;b[2][1]=70;b[3][1]=17;
	//
	DescomposicionLU(A,b);
	return 0;
}

