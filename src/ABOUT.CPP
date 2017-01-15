//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "about.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TOKRightDlg *OKRightDlg;
//--------------------------------------------------------------------- 
__fastcall TOKRightDlg::TOKRightDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TOKRightDlg::SpeedButton1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

