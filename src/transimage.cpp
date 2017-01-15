//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "about.h"
#include "transimage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
		: TForm(Owner)
		, drawPosLeft(300)
		, drawPosTop(88)
		, drawPosRight(550)
		, drawPosBottom(338)
{
        bmp=new Graphics::TBitmap;
	bmp->Width=250;
        bmp->Height=250;
	rgbqn=new RGBQUAD[256];    //RGBQUAD array for paletted bitmaps (4 & 8 bit)
	GetBmpInfo();
        ColorDialog1->Color=clWhite;
        GetColors(clWhite); //initialize the glass color to white
        shShape=shNone;
	Canvas->Brush->Style=bsClear;
	DoubleBuffered = true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::DrawTransImage()
{

     BYTE* cptr;
     WORD* Wptr;
     register int i,j;
    //
      //clip output to a rect region 250*250 in size so even for large images we don't draw the whole image
   // hRgn hRgn=CreateRectRgn(300,88,550,350);
   //  SelectClipRgn(Canvas->Handle,hRgn);
	 if(moving)
		Canvas->Draw(drawPosLeft, drawPosTop, Image1->Picture->Bitmap);

	 switch(bs.bmBitsPixel) {
      case 4://pf4bit:
      case 8://pf8bit:
	   DRAW48BPP:

          if(!GetDIBColorTable(Image1->Picture->Bitmap->Canvas->Handle,0,colors,rgbqn))
                ShowError(GetLastError());

        for(register int k=0;k<colors;++k)  {
         if  (rgbqn[k].rgbRed <= maxr)
                if(rgbqn[k].rgbRed + TrackBar1->Position > maxr  )
                   rgbqn[k].rgbRed = maxr;
                else
                   rgbqn[k].rgbRed+=TrackBar1->Position;
        else
                if(rgbqn[k].rgbRed - TrackBar1->Position > maxr  )
                   rgbqn[k].rgbRed -= TrackBar1->Position;
                else
                   rgbqn[k].rgbRed = maxr;

        if  (rgbqn[k].rgbGreen <= maxg)
                if(rgbqn[k].rgbGreen + TrackBar1->Position > maxg  )
                   rgbqn[k].rgbGreen = maxg;
                else
                   rgbqn[k].rgbGreen+=TrackBar1->Position;
        else
                if(rgbqn[k].rgbGreen - TrackBar1->Position > maxg  )
                   rgbqn[k].rgbGreen -= TrackBar1->Position;
                else
                   rgbqn[k].rgbGreen = maxg;

        if  (rgbqn[k].rgbBlue <= maxb)
                if(rgbqn[k].rgbBlue + TrackBar1->Position > maxb  )
                   rgbqn[k].rgbBlue = maxb;
                else
                   rgbqn[k].rgbBlue+=TrackBar1->Position;
        else
                if(rgbqn[k].rgbBlue - TrackBar1->Position > maxb  )
                   rgbqn[k].rgbBlue -= TrackBar1->Position;
                else
                   rgbqn[k].rgbBlue = maxb;
           }

        bmp->Assign(Image1->Picture->Bitmap);
		//BitBlt(bmp->Canvas->Handle,0,0,250,250, Image1->Canvas->Handle,0,0,SRCCOPY);
	   SetDIBColorTable(bmp->Canvas->Handle,0,colors,rgbqn) ;
	   break;
       case 24://pf24bit:

        bmp->Assign(Image1->Picture->Bitmap);
        //BitBlt((HDC)bmp->Canvas->Handle,0,0,bmp->Width,bmp->Height, Image1->Picture->Bitmap->Canvas->Handle,0,0,SRCCOPY);
        for( register i=0; i<bmp->Height;++i)   {
        cptr=(BYTE*) bmp->ScanLine[i];
        for( register  j=0;j<bmp->Width;++j)    {          //blue
                if  (*cptr <= maxb)
                if(*cptr + TrackBar1->Position > maxb  )
                   *cptr = maxb;
                else
                   *cptr +=TrackBar1->Position;
        else
                if(*cptr - TrackBar1->Position > maxb  )
                   *cptr -= TrackBar1->Position;
                else
                   *cptr = maxb;
        cptr++;
        if  (*cptr <= maxg)                             //green
                if(*cptr + TrackBar1->Position > maxg  )
                   *cptr = maxg;
                else
                   *cptr +=TrackBar1->Position;
        else
                if(*cptr - TrackBar1->Position > maxg  )
                   *cptr -= TrackBar1->Position;
                else
                   *cptr = maxg;
        cptr++;
        if  (*cptr <= maxr)            //red
                if(*cptr + TrackBar1->Position > maxr  )
                   *cptr = maxr;
                else
                   *cptr += TrackBar1->Position;
        else
				if(*cptr - TrackBar1->Position > maxr  )
                   *cptr -= TrackBar1->Position;
                else
				   *cptr = maxr;
         cptr++;
               // bmp->PixelFormat == pf24bit ? cptr++: cptr += 2;
        }
	   }
       break;
       case 15://pf15bit:
	   case 16://pf16bit:
		bmp->Assign(Image1->Picture->Bitmap);
		//BitBlt(bmp->Canvas->Handle,0,0,bmp->Width,bmp->Height, Image1->Picture->Bitmap->Canvas->Handle,0,0,SRCCOPY);
        for( register i=0; i<bmp->Height;++i)   {
        BYTE rc,bc,gc;
        Wptr=(WORD*) bmp->ScanLine[i];

		for( register  j=0;j<bmp->Width;++j)    {

				 bc = GETBLUECOL(*Wptr);
				 if(bs.bmBitsPixel == 16) {
				 gc = GETGREENCOL16(*Wptr);
				 rc = GETREDCOL16(*Wptr);
				} else  {
				 gc = GETGREENCOL15(*Wptr);
				 rc = GETREDCOL15(*Wptr);
                 }

				if (bc <= maxb){
                if(bc + TrackBar1->Position > maxb  )
                   bc = maxb;
                else
                   bc +=TrackBar1->Position;
				}else {
                if(bc - TrackBar1->Position > maxb  )
                   bc -= TrackBar1->Position;
                else
				   bc = maxb;
				}

		if  (gc <= maxg){                             //green
                if(gc + TrackBar1->Position > maxg  )
                   gc = maxg;
                else
                   gc +=TrackBar1->Position;
		}else {
                if(gc - TrackBar1->Position > maxg  )
                   gc -= TrackBar1->Position;
                else
                   gc = maxg;
		}
        if  (rc <= maxr)            //red
                if(rc + TrackBar1->Position > maxr  )
                   rc = maxr;
                else
                   rc += TrackBar1->Position;
        else
                if(rc - TrackBar1->Position > maxr  )
                   rc -= TrackBar1->Position;
                else
                   rc = maxr;

		bs.bmBitsPixel == 16 ? *Wptr = bc | gc << 5 | rc << 11 : *Wptr = bc | gc << 5 | rc << 10;
        Wptr++;
                }
		   }
        break;
        }

		SHAPE:
         //on win2x i XP you can  achive  transparency of shapes by changing Canvas's brush property  instead of defining regions
         //aparently brush is used differently on win9x so I use regions to make this work on every OS
         // Image2->Canvas->Brush->Bitmap=bmp;       if using brush instead of regions
		CreateClipRgn();
        END:
		 Canvas->Draw(drawPosLeft,drawPosTop,bmp);
		 #if defined(INVERT_COLORS)
		 if(CheckBox2->Checked){
			InvertRgn(Canvas->Handle,hRgn);
		}
		#endif
        moving=false;
        DeleteObject(hRgn);
}
void __fastcall TForm1::ShowError(int error)          //if an error ocurred show it
{
        LPVOID lpMsgBuf;
        FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
        );
        MessageBox( NULL, (LPTSTR)lpMsgBuf, "TransImage - Error code", MB_OK|MB_ICONINFORMATION );
        LocalFree( lpMsgBuf );

}

void __fastcall TForm1::AlphaChange(TObject *Sender)
{
		DrawTransImage();
		/** for slow computers, otherwise graphics will flicker
		static unsigned int elapsed=0;
		if(GetTickCount()- elapsed > 100) {
        //Image2->Repaint();
		DrawTransImage();
		elapsed=GetTickCount();
		}    */
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    if(bmp)
		delete bmp;

    if(rgbqn)
		delete [] rgbqn;
}
void __fastcall TForm1::GetColors(TColor Color)
{
	 maxg = GetGValue(Color) >> shiftgreen;
	 maxr = GetRValue(Color) >> shift;
	 maxb = GetBValue(Color) >> shift;
     Shape1->Brush->Color = Color;
}
void __fastcall TForm1::ShowBmpInfo(AnsiString& str, int w, int h)
{
               Label2->Caption= str;
               Label3->Caption= IntToStr(w);
               Label4->Caption= IntToStr(h);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
                if(ColorDialog1->Execute())
                        GetColors(ColorDialog1->Color);   //refresh the color
                DrawTransImage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
      if(SpeedButton1->Down)
                shShape=shEllipse;

         if(SpeedButton2->Down)
                 SpeedButton1->Down=false;
          if(SpeedButton3->Down)
                 SpeedButton2->Down=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetBmpInfo()
{
	 GetObject(Image1->Picture->Bitmap->Handle, sizeof(BITMAP),&bs);
     switch(bs.bmBitsPixel) {
     case 16:
     shift = 3;
     shiftgreen=2;
     TrackBar1->Max=63;
     //bmp->PixelFormat=pf16bit;
     Image1->Picture->Bitmap->PixelFormat=pf16bit;
     //Image2->Picture->Bitmap->PixelFormat=pf16bit;
     ShowBmpInfo((AnsiString)"16 bit bitmap", bs.bmWidth,bs.bmHeight);
     break;
     case 15:
     shift = 3;
     shiftgreen=3;
     TrackBar1->Max=32;
     Image1->Picture->Bitmap->PixelFormat=pf15bit;
     //bmp->PixelFormat=pf15bit;
     ShowBmpInfo((AnsiString)"15 bit bitmap", bs.bmWidth,bs.bmHeight);
     break;
     case 24:
     shift = 0;
     shiftgreen=0;
     TrackBar1->Max=255;

     ShowBmpInfo((AnsiString)"24 bit bitmap", bs.bmWidth,bs.bmHeight);
     break;
     case 4:
     colors = 16;
     shift = 0;
     shiftgreen=0;
     TrackBar1->Max=255;
     ShowBmpInfo((AnsiString)"4 bit bitmap", bs.bmWidth,bs.bmHeight);
     break;
     case 8:
     colors = 256;
     shift = 0;
     shiftgreen=0;
     TrackBar1->Max=255;
     ShowBmpInfo((AnsiString)"8 bit bitmap", bs.bmWidth,bs.bmHeight);
     break;
     default:
	 ShowBmpInfo((AnsiString)"Unsupported file format" + IntToStr(bs.bmBitsPixel) + "bit bitmap" , bs.bmWidth,bs.bmHeight);
       }
     bmp->Width= Image1->Picture->Bitmap->Width;
     bmp->Height=Image1->Picture->Bitmap->Height;
	 bmp->PixelFormat=Image1->Picture->Bitmap->PixelFormat;
	 bmp->Width > 250 ? bmprgnw = 250: bmprgnw = bmp->Width;
	 bmp->Height > 250 ? bmprgnh = 250: bmprgnh = bmp->Height;
     GetColors(ColorDialog1->Color); //refresh the color to indicate the format change
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(OpenPicture1->Execute()){
		AnsiString fileExt =  StrRScan(OpenPicture1->FileName.c_str(),'.');
		if(AnsiSameText(fileExt,".jpg") ||  AnsiSameText(fileExt,".jpeg")){     //jpeg images have to be converted to bitmaps
			TJPEGImage* jpg=new TJPEGImage;
			jpg->LoadFromFile(OpenPicture1->FileName);
			Image1->Picture->Bitmap->Assign(jpg);
			delete jpg;
	}else if(AnsiSameText(fileExt,".bmp")){      //bitmap so we don't have to convert
		Image1->Picture->Bitmap->LoadFromFile(OpenPicture1->FileName);
	}else{
		 Application->MessageBoxA("Unsupported picture format", "Trans Image error", MB_OK | MB_ICONERROR);
	}
    GetBmpInfo();
    Canvas->Brush->Color=Form1->Color;
	Canvas->Rectangle(drawPosLeft-2, drawPosTop-2,552,350);

    HRGN rrgn;
	  //clip output to a rect region 250*250 in size so even for large images we don't draw the whole image
    rrgn=CreateRectRgn(drawPosLeft, drawPosTop,550,340);
    SelectClipRgn(Canvas->Handle,rrgn);
    DeleteObject(rrgn);
    Canvas->Brush->Style=bsClear;
	Canvas->Draw(drawPosLeft, drawPosTop,Image1->Picture->Bitmap);
                }
}

void __fastcall TForm1::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
		if(Button == mbLeft){
		if(drawPosLeft < X && X < drawPosRight ){
		if(Y > drawPosTop && Y <  drawPosBottom) {
		leftMouseDown=true;
		Canvas->Pen->Style=psDot;
		Canvas->Pen->Width = 1;
		sp.x = X;
		sp.y = Y;
		}}}

}
void __fastcall TForm1::Image2MouseMove(TObject *Sender,
       TShiftState Shift, int X, int Y)
{
        if(leftMouseDown) {
       // leftMouseDown=true;
		 if(drawPosLeft < X && X < drawPosRight &&  Y > drawPosTop && Y <  drawPosBottom)
         {
		   HRGN rrgn=CreateRectRgn(drawPosLeft,drawPosTop,drawPosRight,drawPosBottom+2);
           SelectClipRgn(Canvas->Handle,rrgn);
           DeleteObject(rrgn);
		   Canvas->Draw(drawPosLeft,drawPosTop,Image1->Picture->Bitmap);

		Canvas->MoveTo(sp.x,sp.y);
		Canvas->LineTo(X,Y);
        }
        else
        leftMouseDown=false;
      }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
	if(leftMouseDown)      {
		if(drawPosLeft < X && X < drawPosRight &&  Y > drawPosTop && Y <  drawPosBottom)
      		 {
                ep.x=X;
                ep.y=Y;
		Canvas->Brush->Style = bsClear;
                switch(shShape) {
                case shEllipse:
		Canvas->Rectangle(sp.x,sp.y,ep.x,ep.y);
                Canvas->Ellipse(sp.x,sp.y,ep.x,ep.y);
                break;
                case shRect:
                Canvas->Rectangle(sp.x,sp.y,ep.x,ep.y);
                break;
                case shRoundRect:
                Canvas->RoundRect(sp.x,sp.y,ep.x,ep.y,10,10);
                }
                //DeleteObject(hRgn);
                leftMouseDown=false;           }
       else
		leftMouseDown=false;
                }
        DrawTransImage();

}

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
         if(SpeedButton3->Down)
                shShape=shRoundRect;

         if(SpeedButton1->Down)
                 SpeedButton1->Down=false;
          if(SpeedButton2->Down)
                 SpeedButton2->Down=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
        if(CheckBox1->Checked)  {
        OnMouseDown= &Image2MouseDown;
        OnMouseMove= &Image2MouseMove;
        OnMouseUp= &Image2MouseUp;
        SpeedButton1->Enabled=true;
        SpeedButton2->Enabled=true;
        SpeedButton3->Enabled=true;
        TrackBar2->Enabled=true;
        TrackBar3->Enabled=true;
        if(SpeedButton1->Down)
                shShape=shEllipse;
         if(SpeedButton2->Down)
                shShape=shRect;
          if(SpeedButton3->Down)
                shShape=shRoundRect;
     
	   } else {
        OnMouseDown= 0;
        OnMouseMove= 0;
        OnMouseUp= 0;
        shShape=shNone;
        SpeedButton1->Enabled=false;
        SpeedButton2->Enabled=false;
        SpeedButton3->Enabled=false;
        TrackBar2->Enabled=false;
        TrackBar3->Enabled=false;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
      if(SpeedButton2->Down)
                shShape=shRect;

      if(SpeedButton1->Down)
                 SpeedButton1->Down=false;
      if(SpeedButton3->Down)
                 SpeedButton3->Down=false;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
	HRGN rrgn;
      //clip output to a rectangular region 250*250 in size so even for large images we don't draw the whole image
	rrgn=CreateRectRgn(drawPosLeft-2,drawPosTop-2,drawPosRight+2, drawPosBottom+2);
        SelectClipRgn(Canvas->Handle,rrgn);
        DeleteObject(rrgn);
        Canvas->Pen->Style=psDash;
	Canvas->Draw(drawPosLeft, drawPosTop,Image1->Picture->Bitmap);
	Canvas->Rectangle(drawPosLeft-2,drawPosTop-2,drawPosRight+2, drawPosBottom+2); //rectangle used for outlining shapes (ellipse, round rect,rect)

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
        OKRightDlg->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
        DrawTransImage();
}

void __fastcall TForm1::XMoveRegion(TObject *Sender)
{
	   #if defined(MOVE_REGION)
	   static int oldposx = 100;
	   if((sp.x+TrackBar2->Position-100 > drawPosLeft ||  sp.x+TrackBar2->Position-100 < drawPosRight ) &&
	   (ep.x+TrackBar2->Position-100 < drawPosRight ||  ep.x+TrackBar2->Position-100 > drawPosLeft))     {
	   sp.x+=TrackBar2->Position - oldposx;
	   ep.x+=TrackBar2->Position - oldposx;
	   moving = true;
	   DrawTransImage();
        }
	   oldposx = TrackBar2->Position;
		#endif
}
//---------------------------------------------------------------------------

void __fastcall TForm1::YMoveRegion(TObject *Sender)
{
	 #if defined(MOVE_REGION)
	   static int oldposy=100;
	   if((sp.y+TrackBar3->Position-100  > drawPosTop+2 || sp.y+TrackBar3->Position-100  < drawPosBottom+2)
		&&  (ep.y +TrackBar3->Position-100 < drawPosRight || ep.y +TrackBar3->Position-100 > drawPosTop+2))    {
       sp.y+=TrackBar3->Position-oldposy;
	   ep.y+=TrackBar3->Position-oldposy;
	   moving = true;
	   DrawTransImage();
	  /* static unsigned int elapsed=0;
		if(GetTickCount()-elapsed > 100) {
        moving=true;
        DrawTransImage();
        elapsed=GetTickCount();
		}   */
        }
	   oldposy=TrackBar3->Position;
	#endif
}

void __fastcall TForm1::CreateClipRgn()
{
    switch(shShape) {
		case shEllipse:
		hRgn = CreateEllipticRgn(sp.x,sp.y,ep.x,ep.y);
		break;
		case shRect:
		hRgn = CreateRectRgn(sp.x,sp.y,ep.x,ep.y);
		break;
		case shRoundRect:
		hRgn = CreateRoundRectRgn(sp.x,sp.y,ep.x,ep.y,10,10);
		break;
		case shNone:
		hRgn=CreateRectRgn(drawPosLeft,drawPosTop,550,350);
		}
	SelectClipRgn(Canvas->Handle,hRgn);
}
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
	BYTE* cptr;
        BYTE* bptr;
	 //   hRgn hRgn;
     unsigned factor;
	 Graphics::TBitmap* bmp8bit;
	 if (CheckBox3->Checked) {
	  switch(bs.bmBitsPixel) {
     //switch(bmp->PixelFormat) {
      case 4://pf4bit:
      case 8://pf8bit:
      if(!GetDIBColorTable(Image1->Picture->Bitmap->Canvas->Handle,0,colors,rgbqn))
                ShowError(GetLastError());
        for( int k=0;k<colors;++k)  {
            factor = rgbqn[k].rgbRed * 0.3 + rgbqn[k].rgbGreen * 0.59 + rgbqn[k].rgbBlue * 0.11;
            rgbqn[k].rgbRed = factor;
            rgbqn[k].rgbGreen = factor;
            rgbqn[k].rgbBlue = factor;
                        }
        bmp->Assign(Image1->Picture->Bitmap);
        SetDIBColorTable(bmp->Canvas->Handle,0,colors,rgbqn) ;
        break;
        case 24:
        bmp->Assign(Image1->Picture->Bitmap);
		//BitBlt((HDC)bmp->Canvas->Handle,0,0,bmp->Width,bmp->Height, Image1->Picture->Bitmap->Canvas->Handle,0,0,SRCCOPY);
        for( register i=0; i<bmp->Height;++i)   {
        cptr= (BYTE*) bmp->ScanLine[i];
        bptr = cptr;
        for( register  j=0;j<bmp->Width;++j)    {
        factor = *cptr * 0.11;
        cptr++;
        factor += *cptr * 0.59;
        cptr++;
        factor += *cptr * 0.30;
        *bptr =  factor;  //correct the blue comp
        bptr++;
        *bptr =  factor; //correct the green comp
        bptr++;
        *bptr =  factor;  //correct the red comp
        cptr++;     //move the pointer to the next RGB pixel
        bptr++;
        }
        }
		bmp8bit = new Graphics::TBitmap();
		if (bmp8bit){
			bmp8bit->PixelFormat = pf8bit;
			bmp8bit->Assign(bmp);
			bmp->Assign(bmp8bit);
			delete bmp8bit;
        }
        break;
		}
        CreateClipRgn();
		Canvas->Draw(drawPosLeft, drawPosTop, bmp);
	   }
	   else{
		DrawTransImage();
	   }
}
//---------------------------------------------------------------------------


