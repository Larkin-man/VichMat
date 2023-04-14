//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>

int ur=0;
double function(double x, double y)
{

	if(ur==0) return 5*x*x+3*x*y+4*y*y+12.;
	else return 9*(x+1)*(x+1)*(x+1)*(x+1)+6*(y-1)*(y-1)*(y-1)*(y-1);
};

double *HgradF(double x, double y)
{
	double temp[2];
	if(ur==0)
	{
		temp[0]=151*x/71;
		temp[1]=151*y/71;
	}
	else
	{
		temp[0]=36*(x+1)/108;
		temp[1]=24*(y-1)/72;
	}
	return temp;
};

double minimizaciya(double x, double y,double koef1,double koef2)
{
	double A=-10, B=10, EPS=0.01;
	double t[2]={B-(B-A)/((sqrt(5)+1)/2),A+(B-A)/((sqrt(5)+1)/2)};
	double fun[2]={function(x+t[0]*koef1,y+t[0]*koef2),function(x+t[1]*koef1,y+t[1]*koef2)};

	do
	{
		if(fun[0]<=fun[1])
		{
			B=t[1];
			t[1]=t[0];
			t[0]=B-(B-A)/((sqrt(5)+1)/2);
			fun[1]=fun[0];
			fun[0]=function(x+t[0]*koef1,y+t[0]*koef2);
		}
		else
		{
			A=t[0];
			t[0]=t[1];
			t[1]=A+(B-A)/((sqrt(5)+1)/2);
			fun[0]=fun[1];
			fun[1]=function(x+t[1]*koef1,y+t[1]*koef2);
		}
		if(sqrt(pow(A-B,2))<EPS)
			break;
	}while(true);

	return t[fun[0]>fun[1]];
}


double uravnenie(double x, double z, bool znak)
{
	if(ur==0)
	{
		double D=pow(3*x,2)-16*(5*x*x+12-z);
		if(D<=0) return (-3*x/8.);
		if(znak) return (-3*x+sqrt(D))/8.;
		else return (-3*x-sqrt(D))/8.;
	}
	else
	{
		double temp=z-9*(x+1)*(x+1)*(x+1)*(x+1);
		if(temp<0) return 0;
		return ((znak)?(1):(-1))*sqrt(sqrt((temp)/6.))+1;
	}
	return 0;
}
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Grafik;
	TPanel *Panel1;
	TLabel *Label1;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit4;
	TLabel *Label5;
	TEdit *Edit6;
	TLabel *Label7;
	TEdit *Edit8;
	TLabel *Label8;
	TButton *Button3;
	TLabel *Label6;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label12;
	TLabel *Label11;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Print();
	void __fastcall AddDot(double x[], bool move);
	void __fastcall NewtonRafson(TObject *sender);
	void __fastcall BestProb(TObject *sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	//void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	double min[2],Offset[2],increase;
	double kvadrat;
	char buffer[256];
	char minimum[256];
	double curent[2],tk,betta,R,eps;
	int N,M;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
