#include <iostream>
#include <unordered_map>
#include <math.h>
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
		
		Matrix<T> permutar(Matrix<T>& MM)
		{
			Matrix<T> M=*this;
			Int64 n=M.size();
			T m;
			for(Int64 i=1;i<=n;i++)
			{ 
				Int64 indexMax=M.maxcols(i);
				M.swapRows(indexMax,i);
				MM.swapRows(indexMax,i);
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
		
		Matrix<T> operator*(Matrix<T>MM)
		{
			Matrix<T> prod;
			for(Int64 i=1; i<=getnumRows(); i++)
				for(Int64 j=1; j<=MM.getnumCols();j++)
					for(Int64 k = 1; k<=MM.getnumRows();k++)
						prod[i][j] += m_estructura[i][k]*MM[k][j];
			
			return prod;
		}
		
		Matrix<T> operator +(Matrix<T> MM)
		{
			Matrix<T> R;
			for(Int64 i = 1; i<=getnumRows() ; i++)
				for(Int64 j = 1; j<=getnumCols(); j++)
					R[i][j] = m_estructura[i][j] + MM[i][j];
			return R;
		}
		
		Matrix<T> operator *(T value)
		{
			Matrix<T> R=*this;
			for(Int64 i = 1; i<=getnumRows() ; i++)
				for(Int64 j = 1; j<=getnumCols(); j++)
					R[i][j] = R[i][j]*value;
			return R;
		}
		
		/*Debera de tener la misma cantida de filas para la matriz aumentada*/
		Matrix<T> operator|(Matrix<T> MM)
		{
			Matrix<T> R=*this;
			for(Int64 i=1;i<=MM.getnumRows();i++)
			{
				Int64 index=getnumCols()+1;
				for(Int64 j=1;j<=MM.getnumCols();j++)
				{
					R[i][index]=MM[i][j];	
					index++;
				}
			}
			return R;
		}
		
		void swapRows(Int64 i,Int64 j)
		{
			swap(m_estructura[i],m_estructura[j]);
		}
		/*Dado un valor para empezar analiza hasta el último de la fila y devuelve el índice del mayor*/
		Int64 maxcols(Int64 i)
		{
			Int64 index=i;
			for(Int64 j=i;j<=getnumRows();j++)
			{
				if(fabs(m_estructura[j][i])>fabs(m_estructura[i][i]))
					index=j;
			}
			return index;
		}
};


/*Funciones Auxiliares para los diferentes métodos*/
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
			s+=m1[i][j]*R[j][1];
		R[i][1] = (m1[i][cols]-s)/m1[i][i];
	}
	return R;
}

/*Sustitucion progresiva*/
template<typename T>
Matrix<T> sustitucionProgresiva(Matrix<T> &m1)
{
	Matrix<T> R;
	Int64 rows=m1.getnumRows();
	Int64 cols=m1.getnumCols();
	for(Int64 i = 1; i<=rows;i++)
	{
		T s = 0;
		for(Int64 j = 1;j<i;j++)
		{
			s+=m1[i][j]*R[j][1];
		}
		R[i][1] = (m1[i][cols]-s)/m1[i][i];
	}
	
	return R;
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



/*METODO DE JACOBI */
template<typename T>
Matrix<T> jacobi(Matrix<T> &A,Matrix<T> &b,Matrix<T> &X0,Int64 Nmax)
{
	Matrix<T> X;
	Int64 n=A.size();
	for(Int64 m=0;m<Nmax;m++)
	{
		X=X0;
		for(Int64 i=1;i<=n;i++)
		{
			double s=0;
			for(Int64 k=1;k<=n;k++)
				s+=A[i][k]*X[k][1];
			X0[i][1]=(b[i][1]-s+A[i][i]*X[i][1])/A[i][i];
		}	
	}
	return X0;
}	

/*METODO GAUSS SEIDEL*/
template<typename T>
Matrix<T> gaussSeidel(Matrix<T> &A,Matrix<T> &b,Matrix<T> &X0,Int64 Nmax)
{
	Matrix<T> X;
	Int64 n=A.size();
	for(Int64 m=0;m<Nmax;m++)
	{
		X=X0;
		for(Int64 i=1;i<=n;i++)
		{
			T s=0;
			for(Int64 k=1;k<=n;k++)
				s+=A[i][k]*X[k][1];
			X0[i][1]=(b[i][1]-s+A[i][i]*X[i][1])/A[i][i];
			X[i] = X0[i];
		}
	}
	return X0;
}	
/*ELIMINACION GAUSIANA*/
template<typename T>
Matrix<T> EliminacionGaussiana(Matrix<T> A,Matrix<T>b){
	//Matriz Aumentada
	Int64 n=A.size();
	Matrix<T> Ab=A|b;
	for(Int64 j=1;j<n;j++)
	{
		T m;
		for(Int64 i=j+1;i<=n;i++)
		{
			m=-(Ab[i][j]/Ab[j][j]);
			for(Int64 k=1;k<=n+1;k++)
				Ab[i][k]=Ab[i][k]+m*Ab[j][k];
		}	
	}
	return sustitucionRegresiva(Ab);
}

/*Eliminacion Gausiana con pivoteo*/
template<typename T>
Matrix<T> EliminacionGaussianaPivot(Matrix<T> A,Matrix<T>b){
	//Matriz Aumentada
	Int64 n=A.size();
	Matrix<T> Ab=A|b;
	for(Int64 j=1;j<n;j++)
	{
		T m;
		A.swapRows(A.maxcols(j),j);
		for(Int64 i=j+1;i<=n;i++)
		{
			m=-(Ab[i][j]/Ab[j][j]);
			for(Int64 k=1;k<=n+1;k++)
				Ab[i][k]=Ab[i][k]+m*Ab[j][k];
		}	
	}
	return sustitucionRegresiva(Ab);
}

/*Descomposicion PLU*/
template<typename T>
Matrix<T> DescomposicionLU(Matrix<T> &A,Matrix<T> &b){
	Int64 n = A.size();
	Matrix<T> L=A.identidad();
	Matrix<T> U=A.escalonar(L);
	Matrix<T> x,y;
	cout<<"Matriz A"<<endl;
	A.disp();
	cout<<"------------"<<endl;
	cout<<"Matriz L"<<endl;
	L.disp();
	cout<<"------------"<<endl;
	cout<<"Matriz U"<<endl;
	U.disp();
	cout<<"------------"<<endl;
	Matrix<T> Lb=L|b;
	y=sustitucionProgresiva(Lb);
	cout<<"------------"<<endl;
	cout<<"Matriz Y"<<endl;
	y.disp();
	Matrix<T> Uy=U|y;
	x=sustitucionRegresiva(Uy);
	cout<<"------------"<<endl;
	cout<<"Matriz X"<<endl;
	x.disp();
	return x;
}

template<typename T>
Matrix<T> DescomposicionPLU(Matrix<T> &A,Matrix<T> &b){
	Matrix<T> P  = A.identidad();
	Matrix<T> PA = A.permutar(P);
	Matrix<T> L  = A.nullMatrix();
	Matrix<T> U  = PA.escalonar(L);
	cout<<"Matriz P"<<endl;
	P.disp();
	cout<<"Matriz A"<<endl;
	A.disp();
	cout<<"Matriz L"<<endl;
	L=L+L.identidad();
	L.disp();
	cout<<"Matriz U"<<endl;
	U.disp();
	Matrix<T> x,y;
	cout<<"------------"<<endl;
	Matrix<T> Lpb=L|P*b;
	y=sustitucionProgresiva(Lpb);
	cout<<"Matriz Y"<<endl;
	y.disp();
	Matrix<T> Uy=U|y;
	x=sustitucionRegresiva(Uy);
	cout<<"------------"<<endl;
	cout<<"Matriz X"<<endl;
	x.disp();
	
	return U;
}

Matrix<double> newtowMatrix(Matrix<fun> &F,Matrix<fun> J,Matrix<double> X0,Int64 max)
{
	Matrix<double> X;
	for(Int64 n=0;n<max;n++){
		for(Int64 i=1;i<=X0.getnumRows();i++)
		{
			//Matrix<double> JI=(eval(J,X0[1][1],X0[1][1])).inverza();
			Matrix<double> JE=eval(J,X0[1][1],X0[1][1]);
			Matrix<double> FE=eval(F,X0[1][1],X0[1][1]);
			Matrix<double> P=EliminacionGaussianaPivot(JE,FE);
			X[i][1]=X0[i][1]-P[i][1];//-((eval(J,X0[1][1],X0[2][1])).inverza());
		}	
		X0=X;
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
	Matrix<double> A,b,X0;

	A[1][1]=5;A[1][2]=2;A[1][3]=-1;
	A[2][1]=-1;A[2][2]=7;A[2][3]=1;
	A[3][1]=2;A[3][2]=1;A[3][3]=-6;

	b[1][1]=6;b[2][1]=16;b[3][1]=-14;
	X0[1][1]=0;X0[2][1]=0;X0[3][1]=0;
	
//	jacobi(A,b,X0,15).disp();
//	gaussSeidel(A,b,X0,15).disp();
//	EliminacionGaussiana(A,b).disp();
//	EliminacionGaussianaPivot(A,b).disp();
//	DescomposicionLU(A,b);
//	DescomposicionPLU(A,b);
	Matrix<fun> F;
	F[1][1]=f1;
	F[2][1]=f2;
	Matrix<fun> J;
	J[1][1]=df1x;J[1][2]=df1y;
	J[2][1]=df2x;J[2][2]=df2y;
	Matrix<double> X;
	X[1][1]=1;
	X[2][1]=1;
	Matrix<double> P=newtowMatrix(F,J,X,5);
	P.disp();
	return 0;
}

