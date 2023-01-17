#include <iostream.h>
#include "pfVector.h"


//----------------------------------------------------------
//----------------------------------------------------------
//class for matrix operations(in addition to vector class)
const int N = 2;   //Size of matrix

class MATRIX
{
	double m[2][2];

	friend VECTOR KvaziNewtonDirectConst(VECTOR, VECTOR);
	friend VECTOR SearchMin(VECTOR);

public:
	MATRIX()
	{
		int j;
		for(int i = 0;i<N;i++)
			for(j = 0;j<N;j++)
				m[i][j] = 0;
	}
	MATRIX(double m00, double m01, double m10, double m11)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[1][0] = m10;
		m[1][1] = m11;
	}
	~MATRIX() {}

	void MatrPrint()
	{
		for(int i = 0;i<N;i++)
		{
			cout<<endl<<"| ";
			for(int j = 0;j<N;j++)
				cout<<m[i][j];
			cout<<"|";
		}
	}

	void MatrInit(MATRIX M)
	{
		m[0][0] = M.m[0][0];
		m[0][1] = M.m[0][1];
		m[1][0] = M.m[1][0];
		m[1][1] = M.m[1][1];
	}
};
//----------------------------------------------------------
//----------------------------------------------------------
