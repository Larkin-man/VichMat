#include <stdio.h>
#include <math.h>

//----------------------------------------------------------
//----------------------------------------------------------
//class containing vector operations
class VECTOR
{
	double x1;
	double x2;

	friend VECTOR DisplToPoint(double);
	friend double Func(double);
	friend double OneDimensionalDescent(VECTOR, VECTOR);
	friend VECTOR KvaziNewtonDirectConst(VECTOR, VECTOR);
	friend VECTOR SearchMin(VECTOR);

public:
	VECTOR() {}            //Конструкторы и деструктор класса
	VECTOR(double k1, double k2)
	{
		x1 = k1;
		x2 = k2;
	}
	~VECTOR() {}

	void Grad(VECTOR Xk)     //Ф-ция для вычисления градиента
	{
		x1 = 16*Xk.x1+4*Xk.x2;
		x2 = 4*Xk.x1+10*Xk.x2;
	}

	double Norm()          // Ф-ция для вычисления нормы вектора
	{
		return(sqrt(x1*x1+x2*x2));
	}

	void VectAdd(VECTOR Xk, double displ, VECTOR Pk)    // Ф-ция для вычисления
	{								  // координат точки xk+1
		x1 = Xk.x1+displ*Pk.x1;
		x2 = Xk.x2+displ*Pk.x2;
	}

	void VectPrint()                       //Ф-ция для вывода на экран вектора
	{
		printf("[%.20f;%.20f]", x1, x2);
	}

	void VectInit(VECTOR Xk)
	{
		x1 = Xk.x1;
		x2 = Xk.x2;
	}

	void VectSub(VECTOR a, VECTOR b)
	{
		x1 = a.x1-b.x1;
		x2 = a.x2-b.x2;
	}
};
//----------------------------------------------------------
//----------------------------------------------------------