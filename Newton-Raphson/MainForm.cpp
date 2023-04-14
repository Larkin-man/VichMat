#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	increase=3;
	kvadrat=3;
	min[0]=0;
	min[1]=0;
	ur=0;
	sprintf (minimum, "Аналит.минимум f(%.2f, %.2f)=(5x^2+4y^2+3xy+12)=%.2f",
		min[0], min[1],function(min[0], min[1]));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Offset[0]=-min[0]*increase+Grafik->Width/2;
	Offset[1]=min[1]*increase+Grafik->Height/2;
	Label1->Caption=minimum;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Print()
{
	Grafik->Repaint();
	Grafik->Canvas->Pen->Width=1;
	Grafik->Canvas->Pen->Color=clLtGray;
	for(int i=0; i<Grafik->Width; i+=50)
	{
		sprintf(buffer,"%.1f",(i-Offset[0])/increase);
		Grafik->Canvas->TextOutA(i,Grafik->Height-15,buffer);
		for(int j=0; j<Grafik->Height; j+=30)
		{
			Grafik->Canvas->MoveTo(i+15,j);
			Grafik->Canvas->LineTo(i+15,j+15);
		}
	}
	for(int i=0; i<Grafik->Height; i=i+50)
	{
		sprintf(buffer,"%.1f",-(i-Offset[1])/increase);
		Grafik->Canvas->TextOutA(Grafik->Width-30,i,buffer);
		for(int j=0; j<Grafik->Width; j=j+30)
		{
			Grafik->Canvas->MoveTo(j,i+15);
			Grafik->Canvas->LineTo(j+15,i+15);
		}
	}
	Grafik->Canvas->Pen->Width=1;
	Grafik->Canvas->Pen->Color=clBlack;
	Grafik->Canvas->Rectangle(1,1,Grafik->Width,Grafik->Height);

	double step=1,z,D,start,end;
	for(double i=min[0]*increase; i<=min[0]*increase+350; i+=step)
	{
		z=function(i,min[1]);
		if(ur==0)
		{
			if((D=284*(-192+16*z))<0) D=0;

			start=-sqrt(D)/142.;
			end=sqrt(D)/142.;
		}
		else
		{
			if(z<0)z=0;
			start=-sqrt(sqrt(z/9.))-1;
			end=sqrt(sqrt(z/9.))-1;
		}

		Grafik->Canvas->MoveTo(increase*start+Offset[0],-increase*uravnenie(start,z,true)+Offset[1]);
		for(double j=start+1./increase; j<end; j=j+1./increase)
		Grafik->Canvas->LineTo(increase*j+Offset[0],-increase*uravnenie(j,z,true)+Offset[1]);
		Grafik->Canvas->LineTo(increase*end+Offset[0],-increase*uravnenie(end,z,true)+Offset[1]);

		for(double j=end-1./increase; j>start; j=j-1./increase)
		Grafik->Canvas->LineTo(increase*j+Offset[0],-increase*uravnenie(j,z,false)+Offset[1]);
		Grafik->Canvas->LineTo(increase*start+Offset[0],-increase*uravnenie(start,z,false)+Offset[1]);
		step++;
	}

}

void __fastcall TForm1::AddDot(double x[], bool move)
{
	if(increase*x[0]+Offset[0]<0 || increase*x[0]+Offset[0]>700 || -increase*x[1]+Offset[1]<0 || -increase*x[1]+Offset[1]>500)
	return;

	double z,D,ot,d0;
	Grafik->Canvas->Pen->Color=clRed;
	Grafik->Canvas->Pen->Width=1;

	if(move)
		Grafik->Canvas->MoveTo(increase*x[0]+Offset[0],-increase*x[1]+Offset[1]);
	else
		Grafik->Canvas->LineTo(increase*x[0]+Offset[0],-increase*x[1]+Offset[1]);
	Grafik->Canvas->Rectangle(increase*x[0]+Offset[0]-kvadrat,-increase*x[1]+Offset[1]-kvadrat,increase*x[0]+Offset[0]+kvadrat,-increase*x[1]+Offset[1]+kvadrat);
	Grafik->Canvas->MoveTo(increase*x[0]+Offset[0],-increase*x[1]+Offset[1]);
}


void __fastcall TForm1::NewtonRafson(TObject *sender)
{
	int i=0;
	double start[2],dk[2]={0,0};
	if((eps=atof(Edit3->Text.c_str()))<=0) eps=0.0001;
	if(!Edit3->Text.IsEmpty()) Edit3->Text=eps;
	if(!Edit1->Text.IsEmpty()) Edit1->Text=(curent[0]=atof(Edit1->Text.c_str()));
	if(!Edit2->Text.IsEmpty()) Edit2->Text=(curent[1]=atof(Edit2->Text.c_str()));

	Label4->Visible=true;
	Label5->Visible=false;
	Label7->Visible=false;
	Label8->Visible=false;
	Edit3->Visible=true;
	Edit4->Visible=false;
	Edit6->Visible=false;
	Edit8->Visible=false;

	for(int j=1; j<Form2->StringGrid1->RowCount; j++)
	Form2->StringGrid1->Rows[j]->Clear();
	Form2->StringGrid1->RowCount=2;

	Print();
	AddDot(curent,true);

	do
	{
		Form2->StringGrid1->Cols[0]->Add(++i);
		Form2->StringGrid1->Cols[1]->Add(curent[0]);
		Form2->StringGrid1->Cols[2]->Add(curent[1]);
		Form2->StringGrid1->Cols[3]->Add(function(curent[0],curent[1]));
		Form2->StringGrid1->Cols[4]->Add(tk);
		Form2->StringGrid1->Cols[5]->Add(dk[0]);
		Form2->StringGrid1->Cols[6]->Add(dk[1]);

		start[0]=curent[0];
		start[1]=curent[1];
		dk[0]=-HgradF(start[0],start[1])[0];
		dk[1]=-HgradF(start[0],start[1])[1];
		tk=minimizaciya(start[0],start[1],dk[0],dk[1]);

		curent[0]=start[0]+tk*dk[0];
		curent[1]=start[1]+tk*dk[1];
		AddDot(curent,false);
		Form2->StringGrid1->RowCount++;
	}while(sqrt(pow(function(curent[0],curent[1])-function(start[0],start[1]),2)) > eps
			|| sqrt(pow(curent[0]-start[0],2)+pow(curent[1]-start[1],2)) > eps);
	sprintf (buffer, ". Расчитанный минимум f(%.2f, %.2f)=%.2f.", curent[0], curent[1], function(curent[0], curent[1]));
	Label1->Caption = AnsiString(minimum)+buffer;
	Form2->StringGrid1->RowCount--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BestProb(TObject *sender)
{
	int i=0;
	double dk[2]={1,0};
	betta = 0.5;
	R = 0.01;

	if((N=atoi(Edit4->Text.c_str()))<1)N=50; if(!Edit4->Text.IsEmpty()) Edit4->Text=N;
	if((M=atoi(Edit8->Text.c_str()))<1)M=50; if(!Edit8->Text.IsEmpty()) Edit8->Text=M;
	if((tk=atof(Edit6->Text.c_str()))<=0)tk=1; if(!Edit6->Text.IsEmpty()) Edit6->Text=tk;
	if(!Edit1->Text.IsEmpty()) Edit1->Text=(curent[0]=atof(Edit1->Text.c_str()));
	if(!Edit2->Text.IsEmpty()) Edit2->Text=(curent[1]=atof(Edit2->Text.c_str()));


	Label4->Visible=false;
	Label5->Visible=true;
	Label7->Visible=true;
	Label8->Visible=true;
	Edit3->Visible=false;
	Edit4->Visible=true;
	Edit6->Visible=true;
	Edit8->Visible=true;

	for(int j=1; j<Form2->StringGrid1->RowCount; j++)
	Form2->StringGrid1->Rows[j]->Clear();
	Form2->StringGrid1->RowCount=2;

	Print();
	AddDot(curent,true);
	do
	{
		Form2->StringGrid1->Cols[0]->Add(++i);
		Form2->StringGrid1->Cols[1]->Add(curent[0]);
		Form2->StringGrid1->Cols[2]->Add(curent[1]);
		Form2->StringGrid1->Cols[3]->Add(function(curent[0],curent[1]));
		Form2->StringGrid1->Cols[4]->Add(tk);
		Form2->StringGrid1->Cols[5]->Add(dk[0]);
		Form2->StringGrid1->Cols[6]->Add(dk[1]);
		for(int j=0; j<M; j++)
		{
			dk[0]=((rand()%100/100.>.5)?(1):(-1))*(rand()%100)/100.;
			dk[1]=((rand()%100/100.>.5)?(1):(-1))*sqrt(1-dk[0]*dk[0]);
			if(j==0 || function(min[0],min[1])>function(curent[0]+tk*dk[0],curent[1]+tk*dk[1]))
			{
				min[0]=curent[0]+tk*dk[0];
				min[1]=curent[1]+tk*dk[1];
			}
		}

		if(function(min[0],min[1])>=function(curent[0],curent[1]))
			tk*=betta;
		else
		{
			curent[0]=min[0];
			curent[1]=min[1];
			AddDot(curent,false);
		}
		Form2->StringGrid1->RowCount++;
	}while(tk>R && i<N);
	sprintf (buffer, ". Расчитанный минимум f(%.2f, %.2f)=%.2f.", curent[0], curent[1], function(curent[0], curent[1]));
	Label1->Caption = AnsiString(minimum)+buffer;
	Form2->StringGrid1->RowCount--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(ur==0)
	{
		min[0]=-1;
		min[1]=1;
		ur=1;
		sprintf (minimum, "Функция f(%.2f, %.2f)=(9(x+1)^4+6(y-1)^4)=%.2f",
			min[0], min[1],function(min[0], min[1]));
	}
	else
	{
		min[0]=0;
		min[1]=0;
		ur=0;
		sprintf (minimum, "Функция f(%.2f, %.2f)=(5x^2+4y^2+3xy+12)=%.2f",
			min[0], min[1],function(min[0], min[1]));
	}
	FormCreate(Sender);
	if(RadioButton1->Checked)
		NewtonRafson(Sender);
	else if(RadioButton2->Checked)
		BestProb(Sender);
	else
	Print();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Form1->Close();
}
//---------------------------------------------------------------------------

