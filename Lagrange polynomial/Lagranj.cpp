//******���������������� ��������� ��������******//

#include<stdio.h>
#include<conio.h> 
#include<string.h>
#include<iostream.h>

int i,j;	//�������� �����
float *X=NULL;	//���� ������������
float *Y=NULL;	//�������� ������� f(x)
int n;	//���������� ����� (�������)
float x;	//����� ��� ������� ����� ����� f(x)
float L=0;	//���������������� ���������
float *P=NULL;	//����������� �����������
	
void main()
{
	clrscr();
	char num[50]={NULL}; //��������� �����
	
	//�������� ������
	printf("Vvedi kol-vo mnogochlenov: ");
	scanf("%d",&n);
	X = new float[n];
	Y = new float[n];
	P = new float[n]; 

	int nCount=11; //���� ������� X � ������
	printf("\nVvedite X:");
	for (i=0;i<n;i++)
	{
		gotoxy(i+nCount+1,3);
		scanf("%s",num);
		nCount+=strlen(num);
		X[i]=atof(num);
	}
	nCount=11;
	//���� ������� Y � ������
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
