//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
	StringGrid1->RowCount=2;
	StringGrid1->Cols[0]->Add("#");
	StringGrid1->Cols[1]->Add("x");
	StringGrid1->Cols[2]->Add("y");
	StringGrid1->Cols[3]->Add("f(x,y)");
	StringGrid1->Cols[4]->Add("Величина шага");
	StringGrid1->Cols[5]->Add("dk1");
	StringGrid1->Cols[6]->Add("dk2");
}
//---------------------------------------------------------------------------
 