#include <math.h>
#include <conio.h>
#include <iostream.h>
#include <stdio.h>
#include "pfMatrix.h"
#include "pfInterval.h"

//----------------------------------------------------------
//----------------------------------------------------------
//global variables & class objects
VECTOR X0;
VECTOR Point;
int Iteration = 1;      //счетчик итераций
MATRIX MatrixA(1, 0, 0, 1);
VECTOR VectorX(10, 10);
//----------------------------------------------------------
//----------------------------------------------------------
//functions
VECTOR DisplToPoint(double d_point)
{
	VECTOR v_point;
	v_point.x1 = X0.x1 + d_point * Point.x1;
	v_point.x2 = X0.x2 + d_point * Point.x2;
	return(v_point);
}
//----------------------------------------------------------
//----------------------------------------------------------
double Func(double d_point)  //8x12 + 4x1x2 + 5x22
{
	VECTOR x;
	x = DisplToPoint(d_point);
	return(8 * x.x1 * x.x1 + 4 * x.x1 * x.x2 + 5 * x.x2 * x.x2);
}
//----------------------------------------------------------
//----------------------------------------------------------
//swenn method
INTERVAL Swann1()
{
	double d_step = 0.01;      //начальный шаг

	if(Func(d_step) > Func(0))
		d_step = -d_step;

	double d_point = 0;
	do
	{
		d_point += d_step;
		d_step *= 2;
	} while (Func(d_point) > Func(d_point + d_step));
	INTERVAL int1;           //объект для сохранения начального интервала локализации
					//минимума
	if((d_point + d_step)<(d_point-d_step/2))
	{
		int1.d_left = d_point + d_step;  //a
		int1.d_right = d_point - d_step/2; //b
	}
	else
	{
		int1.d_left = d_point - d_step/2; //a
		int1.d_right = d_point + d_step;  //b
	}

	return(int1);
}
//----------------------------------------------------------
//----------------------------------------------------------
//fib2 method
INTERVAL Fibonacci2(INTERVAL int1)
{
	double Ln = 0.0001;
	double L1 = fabs(int1.d_right-int1.d_left);
	double Fn = L1 / Ln;
	double n = log(Fn*2.236)/log(1.618)-1;

	double Fnm1 = pow(1.618, (int)n)/2.236;
	double Fnp1 = Fn + Fnm1;
	double E = L1/Fnp1;	//погрешность локализации минимума

	int count = 1;            //счетчик итераций
	double L2 = Fnm1/Fn * L1+pow(-1, (int)n) * E/Fn;

	double displX1 = int1.d_left + L2;
	double displX2;


	INTERVAL intk(int1.d_left, int1.d_right);  //инициализация дополнительного объекта для
											// хранения рабочего интервала
	while((count! = (int)n)&&(count! = 6))
	{
		if(fabs(intk.d_right-intk.d_left) <= E)   //Проверка КОП данного метода
		{
			intk.d_left = intk.d_right = (intk.d_left + intk.d_right)/2;
			return(intk);
		}

		displX2 = intk.d_left + intk.d_right - displX1;

		if(displX1 < displX2)           //Сокращение ТИЛ
			if(Func(displX1) < Func(displX2))  //1
				intk.d_right = displX2;
		else                //2
		{
			intk.d_left = displX1;
			displX1 = displX2;
		}
		else
		if(Func(displX1) < Func(displX2))  //3
			intk.d_left = displX2;
		else                //4
		{
			intk.d_right = displX1;
			displX1 = displX2;
		}

		count++;
	}
	return(intk);
}
//----------------------------------------------------------
//----------------------------------------------------------
//pauell method
double Pauell(INTERVAL int1)
{
	int k = 1;      //счетчик итераций
	double E = 0.000001;     //погрешность локализации минимума

	double displA, displB, displC;     //абсолютные смещения симметричных точек А, В и С
	displA = int1.d_left;
	displC = int1.d_right;
	displB = (displA + displC)/2;

	double displD, Fa, Fb, Fc, Fd, displX;  //Смещение апроксимирующего минимума и значекния
	while(1)                       //целевой ф-ции в точках А, В, С и D
	{
		Fa = Func(displA);
		Fb = Func(displB);
		Fc = Func(displC);
		if(k == 1)
		{
			displD = 0.5*(Fa*(displB*displB-displC*displC)+Fb*(displC*displC-displA*displA)+Fc*(displA*displA-displB*displB));
			displD/ = (Fa*(displB-displC)+Fb*(displC-displA)+Fc*(displA-displB));
		}
		else
			displD = (displA+displB)/2+1/2*(Fa-Fb)*(displB-displC)*(displC-displA)/(Fa*(displB-displC)+Fb*(displC-displA)+Fc*(displA-displB));

			Fd = Func(displD);

		if((fabs((displD-displB)/displB) <= E)&&(fabs((Fd-Fb)/Fb) <= E))    //проверка КОП
		{
			displX = (displB+displD)/2;
			break;
		}

		if(displB<displD)      //Сокращение ТИЛ
			if(Fb<Fd)        //1
				displC = displD;
		else          //2
		{
			displA = displB;
			displB = displD;
		}
		else
		if(Fb<Fd)        //3
			displA = displD;
		else          //4
		{
			displC = displB;
			displB = displD;
		}

   k++;
	}

	return displX;
}
//----------------------------------------------------------
//----------------------------------------------------------
double OneDimensionalDescent(VECTOR Xk, VECTOR Pk)
{
	X0.x1 = Xk.x1;
	X0.x2 = Xk.x2;
	Point.x1 = Pk.x1;
	Point.x2 = Pk.x2;

	INTERVAL intI = Swann1();

	INTERVAL int2 = Fibonacci2(intI);
	double d_point;	 //смещение минимума целевой ф-ции от Xk по направлению Pk
	if(int2.d_left == int2.d_right)
		d_point = int2.d_left;
	else
		d_point = Pauell(int2);

	return(d_point);
}
//----------------------------------------------------------
//----------------------------------------------------------
//
VECTOR KvaziNewtonDirectConst(VECTOR Xk, VECTOR Xkm1)
{         //km1 - означает индекс k-1, в остальном обозначения эквивалентны приведенным в схеме
									//метода
	VECTOR dXkm1, GRADk, GRADkm1, GAMMAkm1, Skm1, Pk;
	GRADk.Grad(Xk);

	if((Iteration%2) == 0)
	{
		dXkm1.VectSub(Xk, Xkm1);
		GRADkm1.Grad(Xkm1);
		GAMMAkm1.VectSub(GRADk, GRADkm1);

		Skm1.x1 = MatrixA.m[0][0]*GAMMAkm1.x1+MatrixA.m[0][1]*GAMMAkm1.x2;
		Skm1.x2 = MatrixA.m[1][0]*GAMMAkm1.x1+MatrixA.m[1][1]*GAMMAkm1.x2;

		double zn2, zn1 = dXkm1.x1*GAMMAkm1.x1+dXkm1.x2*GAMMAkm1.x2;
		MATRIX Ak, mat1, mat2;
		mat1.m[0][0] = (dXkm1.x1*dXkm1.x1)/zn1;
		mat1.m[0][1] = (dXkm1.x1*dXkm1.x2)/zn1;
		mat1.m[1][0] = (dXkm1.x1*dXkm1.x2)/zn1;
		mat1.m[1][1] = (dXkm1.x2*dXkm1.x2)/zn1;

		zn2 = Skm1.x1*GAMMAkm1.x1+Skm1.x2*GAMMAkm1.x2;
		mat2.m[0][0] = (Skm1.x1*Skm1.x1)/zn2;
		mat2.m[0][1] = (Skm1.x1*Skm1.x2)/zn2;
		mat2.m[1][0] = (Skm1.x1*Skm1.x2)/zn2;
		mat2.m[1][1] = (Skm1.x2*Skm1.x2)/zn2;

		for(int j, i = 0;i<N;i++)
		for(j = 0;j<N;j++)
		Ak.m[i][j] = MatrixA.m[i][j]+mat1.m[i][j]-mat2.m[i][j];

		Pk.x1 = -(Ak.m[0][0]*GRADk.x1+Ak.m[0][1]*GRADk.x2);
		Pk.x2 = -(Ak.m[1][0]*GRADk.x1+Ak.m[1][1]*GRADk.x2);

		MatrixA.MatrInit(Ak);
	}
	else
	{
		Pk.x1 = -GRADk.x1;
		Pk.x2 = -GRADk.x2;
	}

	return(Pk);
}
//----------------------------------------------------------
//----------------------------------------------------------

VECTOR SearchMin(VECTOR Xk)
{
	VECTOR Pk = KvaziNewtonDirectConst(Xk, VectorX);
	double d_point = OneDimensionalDescent(Xk, Pk);
	VECTOR Xkp1;
	Xkp1.VectAdd(Xk, d_point, Pk);
	VectorX.VectInit(Xk);
	return(Xkp1);
}
//----------------------------------------------------------
//----------------------------------------------------------

int main(void)
{
	double E = 0.000001;	 //погрешность локализации минимума
	VECTOR vectorPointer, vectorPointer1, vP(10, 10);
	cout<<"Davidona-Fletchera-Pauella method";
	do
	{
		vectorPointer1 = SearchMin(vP);
		Iteration++;
		vectorPointer.Grad(vectorPointer1);

		cout<<endl<<endl<<"Iteration: "<<(Iteration-1);
		cout<<endl<<"Point : "<<(Iteration-1);
		vP.VectPrint();
		cout<<endl<<"Point : "<<Iteration;
		vectorPointer1.VectPrint();
		cout<<endl<<"Gradient: ";
		vectorPointer.VectPrint();
		printf("\nNorm of gradient: %.20f\n", vectorPointer.Norm());
		getch();

		if(vectorPointer.Norm() <= E)
		{
			cout<<endl<<endl<<"Minimum: ";
			vectorPointer1.VectPrint();
			cout<<endl<<endl;
			break;
		}

		vP.VectInit(vectorPointer1);
	} while(1);

	getch();
	return 0;
}
//----------------------------------------------------------
//----------------------------------------------------------