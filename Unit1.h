//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TPanel *Panel2;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TBitBtn *BitBtn5;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TLabel *Label4;
        TPanel *Panel3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TPanel *Panel4;
        TButton *Button1;
        TLabel *Label5;
        TShape *Shape1;
        TTimer *Timer1;
        TLabel *Label6;
        TButton *Button2;
        TPanel *Panel5;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *Panel6;
        TRadioButton *RadioButton9;
        TRadioButton *RadioButton10;
        TPanel *Panel8;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton11;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TPanel *Panel7;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton12;
        TEdit *Edit2;
        TBitBtn *BitBtn6;
        TPanel *Panel9;
        TRadioButton *RadioButton13;
        TRadioButton *RadioButton14;
        TButton *Button6;
        TLabel *Label12;
        TEdit *Edit3;
        TPanel *Panel10;
        TRadioButton *RadioButton15;
        TRadioButton *RadioButton16;
        TLabel *Label13;
        TPanel *Panel11;
        TLabel *Label15;
        TRadioButton *RadioButton17;
        TRadioButton *RadioButton18;
        TRadioButton *RadioButton19;
        TBitBtn *BitBtn7;
        TButton *Button7;
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall RadioButton13Click(TObject *Sender);
        void __fastcall RadioButton14Click(TObject *Sender);
        void __fastcall RadioButton15Click(TObject *Sender);
        void __fastcall RadioButton16Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall TForm1::ClickImage(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
