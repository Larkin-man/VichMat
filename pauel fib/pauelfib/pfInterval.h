//----------------------------------------------------------
//----------------------------------------------------------
class INTERVAL
{
	double d_left;
	double d_right;

	friend INTERVAL Swann1();
	friend INTERVAL Fibonacci2(INTERVAL);
	friend double Pauell(INTERVAL);
	friend double OneDimensionalDescent(VECTOR, VECTOR);

public:
	INTERVAL() {}
	INTERVAL(double d1, double d2)
	{
		d_left = d1;
		d_right = d2;
	}
	~INTERVAL() {}
};
//----------------------------------------------------------
//----------------------------------------------------------