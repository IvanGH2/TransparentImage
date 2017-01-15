//---------------------------------------------------------------------------

#ifndef transimageH
#define transimageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <ExtDlgs.hpp>


#define INVERT_COLORS      //comment this line to disable color inversion
#define MOVE_REGION         //comment this line to  disable region movement

/*define macros for extracting the red, green and blue components from 15 and 16 bit bitmaps */
#define GETBLUECOL(COL)((BYTE)(COL & 0x1F))
#define GETGREENCOL16(COL)((BYTE)((COL >> 5) & 0x3F))
#define GETREDCOL16(COL)((BYTE)((COL >> 11) & 0x1F))
#define GETREDCOL15(COL)((BYTE)((COL >> 10) & 0x1F))
#define GETGREENCOL15(COL)((BYTE)((COL >> 5) & 0x1F))

enum TShapes  { shNone, shEllipse, shRect, shRoundRect };
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *TrackBar1;
        TButton *Button1;
        TColorDialog *ColorDialog1;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TButton *Button2;
        TOpenPictureDialog *OpenPicture1;
		TStaticText *StaticText5;
        TShape *Shape1;
        TStaticText *StaticText6;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TCheckBox *CheckBox1;
        TImage *Image1;
        TSpeedButton *SpeedButton4;
        TCheckBox *CheckBox2;
        TTrackBar *TrackBar2;
        TTrackBar *TrackBar3;
        TStaticText *StaticText9;
        TStaticText *StaticText10;
        TCheckBox *CheckBox3;
		TStatusBar *StatusBar1;


		void __fastcall XMoveRegion(TObject *Sender);
		void __fastcall YMoveRegion(TObject *Sender);
		void __fastcall AlphaChange(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Image2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Image2MouseMove(TObject *Sender,
       TShiftState Shift, int X, int Y);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
       
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
		void __fastcall CheckBox2Click(TObject *Sender);
		void __fastcall CheckBox3Click(TObject *Sender);

private:	// User declarations
         const unsigned int drawPosLeft;
		 const unsigned int drawPosTop;
		 const unsigned int drawPosRight;
		 const unsigned int drawPosBottom;

		 BITMAP bs;
		 Graphics::TBitmap* bmp;
		 HRGN hRgn;
		 TPoint sp,ep;
		 bool leftMouseDown;
		 TShapes shShape;
		 RGBQUAD *rgbqn;
         BYTE maxr,maxg,maxb;
         BYTE red,green,blue;
         int shift,shiftgreen;
         int colors;
		 int bmprgnw,bmprgnh;
		 bool moving;

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall DrawTransImage();
        void __fastcall ShowError(int);
        void __fastcall GetColors(TColor Color);
        void __fastcall ShowBmpInfo(AnsiString& str, int w, int h);
        void __fastcall GetBmpInfo();
        void __fastcall CreateClipRgn();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
