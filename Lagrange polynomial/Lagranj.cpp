//******Интерполяционный многочлен Лагранжа******//

#include<stdio.h>
#include<conio.h> 
#include<string.h>
#include<iostream.h>

int i,j;	//Счетчики цикла
float *X=NULL;	//Узлы интерполяции
float *Y=NULL;	//Значение функции f(x)
int n;	//Количество узлов (степень)
float x;	//Точка для которой нужно найти f(x)
float L=0;	//Интерполяционный многочлен
float *P=NULL;	//Лагранжевый коэффициент
	
void main()
{
	clrscr();
	char num[50]={NULL}; //Введенное число
	
	//Создание матриц
	printf("Vvedi kol-vo mnogochlenov: ");
	scanf("%d",&n);
	X = new float[n];
	Y = new float[n];
	P = new float[n]; 

	int nCount=11; //Ввод Вектора X в строку
	printf("\nVvedite X:");
	for (i=0;i<n;i++)
	{
		gotoxy(i+nCount+1,3);
		scanf("%s",num);
		nCount+=strlen(num);
		X[i]=atof(num);
	}
	nCount=11;
	//Ввод Вектора Y в строку
	printf("Vvedite Y:");
	for (i=0;i<n;i++)
	{
		gotoxy(i+nCount+1,4);
		scanf("%s",num);
		nCount+=strlen(num);
		Y[i]=atof(num);
	}
		
	printf("\nVvedite x: ");
	scanf("%f",&x);

	for (i=0;i<n;i++)
	{
		P[i]=1;
		for (j=0;j<n;j++)
		{
			if(j==i) continue;
			P[i]*=(x-X[j])/(X[i]-X[j]);
		}
		P[i]*=Y[i];
		L+=P[i];
		//printf("\nP[%d]=%f ",i,P[i]);
	}
	printf("\nV tochke X=%f: Y=%f ",x,L);

	delete []X;
	delete []Y;
	delete []P;
	getch();
}
