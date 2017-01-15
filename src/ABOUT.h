//----------------------------------------------------------------------------
#ifndef aboutH
#define aboutH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TOKRightDlg : public TForm
{
__published:
	TBevel *Bevel1;
        TSpeedButton *SpeedButton1;
        TMemo *Memo1;
        void __fastcall SpeedButton1Click(TObject *Sender);
private:
public:
	virtual __fastcall TOKRightDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKRightDlg *OKRightDlg;
//----------------------------------------------------------------------------
#endif    
