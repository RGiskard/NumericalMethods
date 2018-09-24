
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "gnuplot.h"
#include <algorithm>
using namespace std;

///Lagrange
/*Funcion que calcula los polinomios coeficientes de lagrange*/
float Lk(float* X,float x,int k,int n)
{
    float num=1,den=1;
    for(int i=0;i<n;i++)
        if(i!=k)
        {
            num*=x-X[i];
            den*=X[k]-X[i];
        }
    return num/den;
}

float lagrange(float* X,float* Y,int n,float x)
{
    float Yk=0;
    for(int i=0;i<n;i++)
        Yk+=Y[i]*Lk(X,x,i,n);
        //cout<<Yk<<" ";
    return Yk;
}

void graficar(float* X,float* Y,int n,float a, float b)
{
    FILE * Arch;
    Arch=fopen("datos.dat","w+");
    float r;
    for(float i=a;i<=b;i+=0.01)
    {
        r=lagrange(X,Y,n,i);
        fprintf(Arch,"%f %f %d  \n",i,r,1);
    }

    for(float j=a;j<=b;j+=0.01)
        fprintf(Arch,"%f %f %d \n",j,sin(j),40);
    for(int k=0;k<n;k++)
        fprintf(Arch,"%f %f %d  \n",X[k],Y[k],25);
    fclose(Arch);

}
///Newton
void print_m(float **m,int n)
{
    printf("\nTabla de diferencias dividivas\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
            printf("%3.1f ",m[i][j]);
        printf("\n");
    }
}

void newton(float *x,float *y,int n,int a,int b)
{
    FILE * Arch;
    Arch=fopen("datos.dat","w+");
    //tabla diferencias divididas
    float ** dif_div=new float *[n]();
    for(int i=0;i<n;i++)
        dif_div[i]=new float[n+1]();

    for(int j=0;j<n;j++)
    {
        dif_div[j][0]=x[j];
        dif_div[j][1]=y[j];
    }

   int inc=1;
   for(int c=2;c<n+1;c++)
   {
       for(int f=c-1;f<n;f++)
       {
         dif_div[f][c]=(dif_div[f][c-1]-dif_div[f-1][c-1])/(dif_div[f][0]-dif_div[f-inc][0]);
         cout<<dif_div[f][c]<<" ";
       }
       inc++;
    }
    print_m(dif_div,n);
    /*Llenado de la tabla de diferencias divididas*/
    float *r=new float [n];
    for(int s=0;s<n;s++)
    {
        if(dif_div[s][s+1]!=0)
            r[s]=dif_div[s][s+1];
    }

    float res;
    float temp=1;
    for(float num=a;num<=b;num+=0.1)
    {
        res=r[0];
        for(unsigned int i=1;i<sizeof(r);i++)
        {
            for(unsigned int j=0;j<i;j++)
                temp*=(num-x[j]);
            temp=temp*r[i];
            res+=temp;
            temp=1;
        }
        fprintf(Arch,"%f %f %d\n",num,res,10);
        res=0;
        fprintf(Arch,"%f %f %d \n",num,sin(num),40);
    }
    for(int j=0;j<n;j++)
        fprintf(Arch,"%f %f %d\n",x[j],y[j],15);
    fclose(Arch);
    cout<<"Coeficientes"<<endl;
    for(int i=0;i<n;i++)
        cout<<r[i]<<" ";
    cout<<endl;

}

int main()
{
    float pi=M_PI;
/*
    cout<<"ingrese el numero de puntos"<<endl;
    int n;
    cin>>n;

    float* x;
    float* y;
    x=new float[n];
    y=new float[n];

    cout<<"ingrese los puntos"<<endl;
    float p,q;
    for(int i=0;i<n;i++)
    {
        cin>>p>>q;
        x[i]=p;
        y[i]=q;
        //y[i]=2*cos((pi/2)*q);
    }

    cout<<"ingrese el intervalo a graficar"<<endl;
    float a,b;
    cin>>a>>b;
    graficar(x,y,n,a,b);
    Gnuplot plot;
    plot("plot 'datos.dat' using 1:2:3 with points pointtype 7 palette ");
    system("pause");

    return 0;*/

    int tam=40;
    float *x=new float[tam];
    float *y=new float[tam];
    double inicio=0.0;

    /*for(int i=0;i<tam;i++)
    {
        x[i]=inicio;
        y[i]=sin(inicio);
        inicio+=0.3;
    }*/
    for(int i=0;i<tam;i++)
        {
            x[i]=inicio;
            y[i]=sin(inicio);
            inicio+=0.5;
        }

    newton(x,y,tam,-1,tam*0.5);


/*
    int tam=3;
    float *x=new float[tam];
    x[0]=1;
    x[1]=3;
    x[2]=5;

   float *y=new float[tam];
   y[0]=2;
   y[1]=4;
   y[2]=2;

   newton(x,y,tam,1,5);*/
    /*int tam=3;
       float *x=new float[tam];
       x[0]=1.0;
       x[1]=2.0;
       x[2]=4.0;

      float *y=new float[tam];
      y[0]=1.0;
      y[1]=3.0;
      y[2]=2.0;

      newton(x,y,tam,1,5);*/

    Gnuplot plot;
    plot("plot 'datos.dat' using 1:2:3 with points pointtype 7 palette ");
    system("pause");
}
