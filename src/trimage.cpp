//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("trimage.res");
USEFORM("transimage.cpp", Form1);
USEFORM("about.cpp", OKRightDlg);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TOKRightDlg), &OKRightDlg);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
