//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int numF = 4;
int posA = 1;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
  Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BitBtn3Click(TObject *Sender)
{
   if(posA >= 1 && posA < numF){
      switch(posA){
         case 1:
               posA++;
               Image1->Picture = Image3->Picture;
               Image2->Picture = Image4->Picture;
               break;
        case 2:
               posA++;
               Image1->Picture = Image5->Picture;
               Image2->Picture = Image6->Picture;
               break;
        case 3:
               posA++;
               Image1->Picture = Image7->Picture;
               Image2->Picture = Image8->Picture;
               break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn2Click(TObject *Sender)
{
      if(posA <= 4 && posA > 1){
      switch(posA){
         case 4:
               posA--;
               Image1->Picture = Image5->Picture;
               Image2->Picture = Image6->Picture;
               break;
        case 3:
               posA--;
               Image1->Picture = Image3->Picture;
               Image2->Picture = Image4->Picture;
               break;
        case 2:
               posA--;
               Image1->Picture = Image9->Picture;
               Image2->Picture = Image10->Picture;
               break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn4Click(TObject *Sender)
{
  Form2->Close();
  Form1->BitBtn1->Click();
}
//---------------------------------------------------------------------------
