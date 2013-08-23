//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string.h>
#include <stdio.h>
#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
/*Diseñado por Kevin Hernández - Universidad del Táchira - Venezuela*/
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
void dialogBox(int x, int y, int width, int height, char titulo[50], char text[300], const TColor);
void panDefecto();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
   Form1->Width = 380;
   Form1->Height = 471;
   Label1->Height = 80;
   Label1->Visible = true;
   Label1->Width = 230;
   Label1->Left = 72;
   Label1->Top = 24;
   Panel1->Visible = true;
   Panel1->Height = 289;
   Panel1->Width = 241;
   Panel1->Left = 64;
   Panel1->Top = 104;
   Panel2->Height = 297;
   Panel2->Width = 240;
   Panel2->Left = 64;
   Panel2->Top = 104;
   Panel5->Height = 289;
   Panel5->Width = 217;
   Panel5->Left = 77;
   Panel5->Top = 104;
   Panel7->Height = 369;
   Panel7->Width = 241;
   Panel7->Left = 64;
   Panel7->Top = 104;
   Panel11->Height = 209;
   Panel11->Width = 241;
   Panel11->Left = 64;
   Panel11->Top = 104;
   Form1->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

class box{
private:
       TImage *tab;
       int i;
       int j;
       int wich;
       bool visual;
public: box(){
          i = 0;
          j = 0;
          wich = 0;
          tab = new TImage(Form1);
          tab->Parent = Form1;
        }
        ~box(){
          delete tab;
        }
        box(int i, int j, int wich, bool visual){
           this->visual = visual;
           this->i = i;
           this->j = j;
           this->wich = wich;
           if(visual){
              tab = new TImage(Form1);
              tab->Parent = Form1;
              tab->Top = 16+33*i;
              tab->Left = 16+33*j;
              tab->BringToFront();
              tab->Visible = true;
              tab->OnClick = Form1->ClickImage;
           }else
              tab = NULL;
           inCol(this->wich);
        }
        void inCol(int wich){
            this->wich = wich;
            //1 negro, 2 blanco, 3 standby, 0 vacio
            if(visual){
              if(!this->wich)
                 tab->Picture = Form1->Image1->Picture;
              else if( this->wich==1)
                 tab->Picture = Form1->Image2->Picture;
              else if( this->wich==2)
                 tab->Picture = Form1->Image3->Picture;
              else if( this->wich==3)
                 tab->Picture = Form1->Image4->Picture;
            }
        }
        void voltea(){
           if( this->wich==1)
               this->wich = 2;
           else if( this->wich==2)
               this->wich = 1;
           else
              return;
           inCol( this->wich);
        }
        int getWich(){
            return  this->wich;
        }
        void convertirNoGrafico(){
           visual = false;
           tab->Visible = false;
        }
};
//---------------------------------------------------------------------------
class tablero{
private:
       TShape *fondo;
       box ***spaces;
       bool visual;
       int x;
       int y;

public:
         int numBlack;
         int numWhite;
        tablero(){
            numBlack = 2;
            numWhite = 2;
        }
        ~tablero(){
          delete fondo;
          for(int i=0;i<x;i++)
               for(int j=0;j<y;j++)
                   delete spaces[i][j];
        }
        tablero(int x, int y, bool visual){
            int i, j;
            this->x = x;
            this->y = y;
            this->visual = visual;
            if(visual){
               fondo = new TShape(Form1);
               fondo->Parent = Form1;
               fondo->Left = 11.8;
               fondo->Top = 11.8;
               fondo->Height = x*33.8;
               fondo->Width = y*33.8;
               fondo->Shape = stRectangle;
               fondo->Pen->Width = 4;
               fondo->Pen->Color = clWhite;
               fondo->Brush->Color = clBlack;
            }
            numBlack = 2;
            numWhite = 2;
            spaces = new box**[x];
            for(i=0;i<x;i++)
               spaces[i] = new box*[y];

            for(i=0;i<x;i++)
               for(j=0;j<y;j++)
            spaces[i][j] = new box(i, j, 0, visual);

        }

        TShape *getFondo(){
                return fondo;
        }
        box *getBox(int i, int j){
              return spaces[i][j];
        }
        int getNumBlack(){
           return numBlack;
        }
        int getNumWhite(){
           return numWhite;
        }
        void cambiarFondo(const TColor color){
            fondo->Brush->Color = color;
        }
        int getX(){
                return x;
        }
        int getY(){
                return y;
        }
};
//---------------------------------------------------------------------------
class pan{
      private:
            TShape *fondo;
            TImage *pers;
            TLabel *punt;
            TLabel *name;
            int turno;
            int puntos;
      public:
            pan(int x, int y, int turno, AnsiString nameTL, bool down){
                 puntos = 2;
                 this->turno = turno;
                 fondo = new TShape(Form1);
                 pers = new TImage(Form1);
                 punt = new TLabel(Form1);
                 name = new TLabel(Form1);
                 fondo->Parent = Form1;
                 pers->Parent = Form1;
                 punt->Parent = Form1;
                 name->Parent = Form1;
                 fondo->Shape = stRectangle;

                 pers->Picture = turno==1?Form1->Image2->Picture:Form1->Image3->Picture;
                 punt->Caption = puntos;
                 //nameTL.SetLength(8);
                 name->Caption = nameTL;
                 
                 fondo->Left = x;
                 pers->Left = x + 17;
                 punt->Left = x + 20;
                 fondo->Top = y;
                 pers->Top = y + 19;
                 punt->Top = y + 62;
                 name->Font->Size = 18;
                 if(down){
                    //Poner el nombre abajo
                    name->Left = x - (nameTL.Length()<=8?12:15)*nameTL.Length();
                    name->Top = y + 56;
                 }else{
                    //Poner el nombre arriba
                    name->Left = x + 65;
                    name->Top = y;
                 }
                 fondo->Height = 88;
                 fondo->Width = 65;
                 fondo->Pen->Width = 4;
                 fondo->Pen->Color = clWhite;
                 fondo->Brush->Color = clBlack;
                 punt->Font->Color = clWhite;
                 name->Font->Color = clBlack;
                 name->Color = clWhite;

            }
            ~pan(){
                delete fondo;
                delete pers;
                delete punt;
                delete name;
            }
            void change(int puntos){
                this->puntos = puntos;
                punt->Caption = puntos;
            }
            int getTurno(){
                return turno;
            }
            void colorFondo(const TColor color){
                 punt->Color = color;
                 fondo->Brush->Color = color;
            }
            int getPuntos(){
                return puntos;
            }
            AnsiString getNombre(){
               return name->Caption;
            }

};
//---------------------------------------------------------------------------
class player{
protected:
        int ficha;  //1 negro, 2 blanco
        char name[25];
public:
        player(int ficha, char *name){
             this->ficha = ficha;
             strcpy(this->name,name);
        }
        char* getName(){
             return name;
        }
        int getFicha(){
             return ficha;
        }
};
//---------------------------------------------------------------------------
class human:public player{
public:
        human(int ficha, char *name):player(ficha, name){}

};
//---------------------------------------------------------------------------
class robot:public player{
public:
        robot(int ficha, char *name):player(ficha, name){}
};
//---------------------------------------------------------------------------
class posicion{
     private:
            int i;
            int j;
            int num;
            posicion *link;

     public:
            posicion(int i, int j){
                this->i = i;
                this->j = j;
                link = NULL;
            }
             posicion(){
                this->i = 0;
                this->j = 0;
                link = NULL;
            }
            /*~posicion(){
                delete link;
            }*/
            posicion* getLink(){
                return link;
            }
            void setLink(posicion *link){
                this->link = link;
            }
            int getI(){
                return i;
            }
            int getJ(){
                return j;
            }
            void setI(int i){
                this->i = i;
            }
            void setJ(int j){
                this->j = j;
            }
            int getNum(){
                return num;
            }
            void setNum(int num){
                this->num = num;
            }
};
//---------------------------------------------------------------------------
class listaPos{
private:
		posicion *cab;
                int numPos;
public:
		listaPos(){
                    cab = NULL;
                    numPos = -1;
                }
                /*~listaPos(){
                   delete cab;
                }*/
		void push(int i, int j){
                    	posicion *newElement;
	                newElement = new posicion(i,j);
	                if(newElement){
	                	newElement->setLink(cab);
	                	cab = newElement;
                                numPos++;
                                newElement->setNum(numPos);
                        }
                }
		posicion* getPosicion(int num){
                posicion *elem;
                int n = 1;
                elem = new posicion;
                if(num <= numPos && num >= 0)
                  if(!num)
                    (*elem) = (*cab);
                  else{
                    (*elem) = (*cab);
                    while(n<=num){
                      elem = elem->getLink();
                      n++;
                    }
                  }
                return elem;
                }
                int getnumPos(){
                   return numPos+1;
                }

};
//---------------------------------------------------------------------------

class game{
private:
        tablero *tablero1;
        int **tab;       //Aqui se guardan los valores numericos del tablero actual
        int **matrizEva; //Matriz usada para la funcion de evaluación de piezas estables (Caracteristica 3)
        //int **tabAux;    //Tablero aux
        int modoJuego;   //Modalidad del juego 0 HvsR, 1 RvsR, 2 HvsH
        pan *panPlayer1;     //Pizarron 1
        pan *panPlayer2;     //Pizarron 2
        player *player1;   //Humano||Robot
        player *player2;     //Robot||Humano
        listaPos listaP; //Lista de posiciones del tablero actual
        int turno; //1 negro, 2 blanco, negro comienza el negro;
        
public:
        game(){
            turno = 1;
        }
//###################################################################################################################################
        tablero* getTablero(){
                return tablero1;
        }
//###################################################################################################################################
        pan* getPanPlayer1(){
                return panPlayer1;
        }
//###################################################################################################################################
        pan* getPanPlayer2(){
                return panPlayer2;
        }
//###################################################################################################################################
        void setPanPlayer1(pan *panPlayer1){
                this->panPlayer1 = panPlayer1;
        }
//###################################################################################################################################
        void setPanPlayer2(pan *panPlayer2){
                this->panPlayer2 = panPlayer2;
        }
//###################################################################################################################################
        void iniPlayer1(int ficha, char* nombre, int modoJuego){
                if(!modoJuego || modoJuego == 2)
                    player1 = new human(ficha, nombre);
                else if(modoJuego == 1)
                    player1 = new robot(ficha, nombre);
        }
//###################################################################################################################################
        void iniPlayer2(int ficha, char* nombre, int modoJuego){
                if(!modoJuego || modoJuego == 1)
                   player2 = new robot(ficha,nombre);
                else if(modoJuego == 2)
                   player2 = new human(ficha,nombre);
        }
//###################################################################################################################################
        player* getPlayer1(){
                return player1;
        }
//###################################################################################################################################
        player* getPlayer2(){
                return player2;
        }
//###################################################################################################################################
        void abrirMatriz(int x, int y){
        //Método que abre alguno de los archivos con la matriz necesaria para determinar la función de evaluación de las piezas estables (Se guarda en matrizEva)
         FILE *fp;
          int  i = 0, j = 0, k = 0, f=0, c=0;
          char ch[5], *charAux = "_matEsta_";
                sprintf( ch, "%d", x ); //Convierte x a cadena
                strcat(charAux, ch);  //Concatena cadena a _matEsta_
                strcat(charAux, ".dat"); //Concatena .dat a _matEstan_
                fp = fopen(charAux,"rb");
        	if(!fp){
	             return;
        	}
	        while(i < x)
	            fread(matrizEva[i++],sizeof(int),y,fp);
                fclose(fp);
        }
 //###################################################################################################################################
        void contar(){
                panPlayer1->change((player1->getFicha()==1)?tablero1->getNumBlack():tablero1->getNumWhite());
                panPlayer2->change((player2->getFicha()==1)?tablero1->getNumBlack():tablero1->getNumWhite());
        }
 //###################################################################################################################################
        void inicio(int x, int y, int modoJuego){
                 this->modoJuego = modoJuego;
                 int h, k, m = 2;
                 h = (x/2)-1;
                 k = (y/2)-1;
                 tablero1 = new tablero(x,y,true);
                  for(int j = 0;j<2;j++) {
                       for(int i = 0;i<2;i++){
                          tablero1->getBox(h,k++)->inCol(m);
                           m = m==2?1:2;
                       }
                        k = (y/2)-1;
                        h++;
                        m = 1;
                 }
            if(!modoJuego || modoJuego == 1){
                 matrizEva = new int*[x];
                 tab = new int*[x];
                 for(int i=0;i<x;i++){
                    tab[i] = new int[y];
                    matrizEva[i] = new int[y];
                 }
                 abrirMatriz(x,y);
            }
            jugPos(turno,turno==1?2:1,true);
        }
 //###################################################################################################################################
        void copiarTablero(){
        //Copia el tablero actual en la matriz tab
          for(int i=0;i<tablero1->getX();i++)
               for(int j=0;j<tablero1->getY();j++)
          tab[i][j] = tablero1->getBox(i,j)->getWich();
        }
//###################################################################################################################################
        int FuncionEval(int** tablero, int ficha, int fichaContraria){
        int  factor1 = 2, factor2 = 3, factor3 = 2;
        factor1 = ((tablero1->getNumBlack()+tablero1->getNumWhite()) > (tablero1->getX()*tablero1->getY()-tablero1->getX()*2)) ? 3:2;
        factor2 = ((tablero1->getNumBlack()+tablero1->getNumWhite()) > (tablero1->getX()*tablero1->getY()-tablero1->getX()*2)) ? 2:3;
        factor3 = ((tablero1->getNumBlack()+tablero1->getNumWhite()) > (tablero1->getX()*tablero1->getY()-tablero1->getX()*2)) ? 3:2; /**/

        return factor1*funE1_CF(tablero, ficha, fichaContraria) + factor2*funE2_MO(tablero, ficha, fichaContraria) +
               factor3*funE3_PE(tablero, ficha, fichaContraria)/**/                                                     ;
        }
//###################################################################################################################################
        int funE1_CF(int** tablero, int ficha, int fichaContraria){
        //Función de evaluación 1, número de fichas que se tendrá en un movimiento
        int f = 0, fc = 0, c;
           for(int i=0;i<tablero1->getX();i++)
              for(int j=0;j<tablero1->getY();j++)
               if(tablero[i][j] == ficha)
                f++;
               else if(tablero[i][j] == fichaContraria)
                fc++;
             return (f-fc);
        }
//###################################################################################################################################
        int funE2_MO(int** tablero, int ficha, int fichaContraria){
         //Funcion Evaluación 2, Movilidad (los espacios en donde ficha puede poner)
           return posiblesJugadas(tablero,ficha, fichaContraria).getnumPos()  //Se usa el método "posiblesJugadas" que retorna una lista con la cantidad de posibles jugadas
                  - posiblesJugadas(tablero,fichaContraria, ficha).getnumPos();
        }
//###################################################################################################################################
        int funE3_PE(int** tablero, int ficha, int fichaContraria){
        //Funcion Evaluación 3, piezas estables
        int n = 0, m = 0;;
        for(int i=0;i<tablero1->getX();i++)
              for(int j=0;j<tablero1->getY();j++)
              if(tablero[i][j] == ficha)
               n += matrizEva[i][j];
              else if(tablero[i][j] == fichaContraria)
               m += matrizEva[i][j];/* */
        return n-m;
        }
//###################################################################################################################################        void turkPiensa(int ficha, int fichaContraria){
       void robotPiensa(int ficha, int fichaContraria){
             int nivelRecursion = (tablero1->getX()==8||tablero1->getX()==10) ? 5:4;;  //nivel recursión varia según tamaño del tablero
             int alpha = 10000;
             int beta = -10000;
             int cont = 0;
             int aux = -50000;
             int mejorEva = -10000;
             posicion mejorPosicion;
             if(tablero1->getNumBlack()==2&&tablero1->getNumWhite()==2) // ini (CASO A)
                mejorPosicion = *listaP.getPosicion(rand()%3);
             else if(listaP.getnumPos()==1){  //si solo hay una jugada (CASO B)
                mejorPosicion = (*listaP.getPosicion(cont));
             }else if(listaP.getnumPos()!=0){ //caso general (CASO C)
                copiarTablero(); // Copia el tablero actual a una matriz entera tab
                //Form1->Edit2->Text =  Form1->Edit2->Text + "-" + listaP.getnumPos();
                for(int i = 0; i < listaP.getnumPos(); i++){
                    aux = MinMax(generarMovimiento(tab,*listaP.getPosicion(i),ficha,fichaContraria), ficha, fichaContraria, nivelRecursion-1,  alpha,  beta);
                    //Form1->Edit2->Text = Form1->Edit2->Text + " " + aux  ;
                    if(aux > mejorEva){
                       mejorPosicion = *listaP.getPosicion(i);
                       mejorEva = aux;
                    }
                }
             }
            jugada(mejorPosicion.getI(), mejorPosicion.getJ(), ficha, fichaContraria);
       }
//###################################################################################################################################        void turkPiensa(int ficha, int fichaContraria){
       int MinMax(int** tablero, int max, int min, int limite, int alpha, int beta){
            return MaxMove(tablero, max, min, limite, alpha, beta);
       }
//###################################################################################################################################        void turkPiensa(int ficha, int fichaContraria){
       int MaxMove(int** tablero, int max, int min, int limite, int alpha, int beta){
            int aux = -50000;
            int mejorEva = -10000;
            if(finalJuegoTablero(tablero)||limite<=0)
                 return FuncionEval(tablero, max, min);
            else{
                 listaPos listaMovimientos;
                 listaMovimientos = posiblesJugadas(tablero, min, max);
                 if(listaMovimientos.getnumPos()>0){
                      for(int i = 0; i < listaMovimientos.getnumPos(); i++){
                         aux = MinMove(generarMovimiento(tablero,*listaMovimientos.getPosicion(i),min,max), max, min, limite-1,  alpha,  beta);
                          if(aux > mejorEva){
                             mejorEva = aux;
                             alpha = mejorEva;
                          }
                          //Eliminar el resto de movimientos
                          if(beta > alpha)
                            return mejorEva;
                      }
                      return mejorEva;
                 }else
                      MaxMove(tablero, max, min, limite-1,  alpha,  beta);
            }
       }
//###################################################################################################################################        void turkPiensa(int ficha, int fichaContraria){
       int MinMove(int** tablero, int max, int min, int limite, int alpha, int beta){
            int aux = 50000;
            int mejorEva =10000;
            if(finalJuegoTablero(tablero)||limite<=0)
                 return FuncionEval(tablero, min, max);
            else{
                 listaPos listaMovimientos;
                 listaMovimientos = posiblesJugadas(tablero, max, min);
                 if(listaMovimientos.getnumPos()>0){
                     for(int i = 0; i < listaMovimientos.getnumPos(); i++){
                         aux = MaxMove(generarMovimiento(tablero,*listaMovimientos.getPosicion(i),max,min), max, min, limite-1,  alpha,  beta);
                          if(aux < mejorEva){
                             mejorEva = aux;
                             beta = mejorEva;
                          }
                          if(beta < alpha)
                             return mejorEva; 
                     }
                     return mejorEva;
                 }else
                     return MinMove(tablero, max, min, limite-1,  alpha,  beta);
            }
       }
//###################################################################################################################################
       bool finalJuegoTablero(int** tablero){
             if(!posiblesJugadas(tablero, 1, 2).getnumPos()&&!posiblesJugadas(tablero, 2, 1).getnumPos())
                     return true;
             return false;
       }

//###################################################################################################################################
      listaPos posiblesJugadas(int **tab, int ficha, int fichaContraria){
        listaPos lis;
        //Función que indica donde puede poner una pieza el robot
        int c = 0, y, x;
        for(int i = 0; i < tablero1->getX(); i++)
           for(int j = 0; j < tablero1->getY(); j++)
              if(tab[i][j]==3)
                 tab[i][j]=0;

         for(int i = 0; i < tablero1->getX(); i++)
             for(int j = 0; j < tablero1->getY(); j++)
                 if(tab[i][j]==ficha){
                        /*Verificar los ocho lados para poner la marca*/
                    if(j>0&&tab[i][j-1]==fichaContraria)
                       for(y = j-1; y>=0; y--){
                          if(tab[i][y]==fichaContraria){
                             c++;
                          }else if(tab[i][y]==0){
                             if(c>0){
                               tab[i][y] = 3;
                               lis.push(i,y);
                             }
                             c = 0;
                             break;
                          }else
                             break;
                        }
                    if(j<tablero1->getY()-1&&tab[i][j+1]==fichaContraria)
                        for(y = j+1; y<tablero1->getY(); y++){
                          if(tab[i][y]==fichaContraria){
                              c++;
                          }else if(tab[i][y]==0){
                             if(c>0){
                               tab[i][y] = 3;
                               lis.push(i,y);
                             }
                             c = 0;
                             break;
                          }else
                              break;
                      }
                     if(i>0&&tablero1->getBox(i-1,j)->getWich()==fichaContraria)
                       for(x = i-1; x >= 0; x--){
                         if(tab[x][j]==fichaContraria){
                             c++;
                         }else if(tab[x][j]==0){
                             if(c>0){
                               tab[x][j] = 3;
                               lis.push(x,j);
                             }
                             c = 0;
                             break;
                         }else
                             break;
                     }
                     if(i<tablero1->getX()-1&&tab[i+1][j]==fichaContraria)
                      for(x = i+1; x < tablero1->getY(); x++){
                         if(tab[x][j]==fichaContraria){
                             c++;
                         }else if(tab[x][j]==0){
                            if(c>0){
                              tab[x][j] = 3;
                              lis.push(x,j);
                            }
                            c = 0;
                            break;
                         }else
                             break;
                       }
                        x = i-1; y = j-1;
                        if(i>0&&j>0&&tab[x][y]==fichaContraria)
                          while(x>=0&&y>=0){
                            if(tab[x][y]==fichaContraria){
                              c++;
                            }else if(tab[x][y]==0){
                              if(c>0){
                                tab[x][y] = 3;
                                lis.push(x,y);
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x--;y--;
                         }
                         x = i+1; y = j+1;
                         if(j<tablero1->getY()-1&&i<tablero1->getX()-1&&tab[x][y]==fichaContraria)
                          while(x<tablero1->getX()&&y<tablero1->getY()){
                            if(tab[x][y]==fichaContraria){
                              c++;
                            }else if(tab[x][y]==0){
                              if(c>0){
                                tab[x][y] = 3;
                                lis.push(x,y);
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x++;y++;
                         }
                          x = i+1; y = j-1;
                          if(j>0&&i<tablero1->getX()-1&&tab[x][y]==fichaContraria)
                          while(x<tablero1->getX()&&y>=0){
                            if(tab[x][y]==fichaContraria){
                              c++;
                            }else if(tab[x][y]==0){
                              if(c>0){
                                tab[x][y] = 3;
                                lis.push(x,y);
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x++;y--;
                         }
                       x = i-1; y = j+1;
                       if(i>0&&j<tablero1->getY()-1&&tab[x][y]==fichaContraria)
                          while(x>=0&&y<tablero1->getY()){
                            if(tab[x][y]==fichaContraria){
                              c++;
                            }else if(tab[x][y]==0){
                              if(c>0){
                                tab[x][y] = 3;
                                lis.push(x,y);
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x--;y++;
                         }
                   }
                return lis;
        }
//###################################################################################################################################
        void jugada(){
           if(!modoJuego){
              if(turno == player2->getFicha()){
                  robotPiensa(player2->getFicha(),player1->getFicha());
                  setTurno(player1->getFicha());
                  if(!jugPos(turno,turno==1?2:1,true)){
                      if(!jugPos(turno==1?2:1,turno,false))
                         finalJuego();//Final del juego
                  }
                  contar();
               }
           }else if(modoJuego == 1){
               if(jugPos(turno,turno==1?2:1,true)){
                  robotPiensa(turno,turno==1?2:1);
                  setTurno(turno==1?2:1);
                  contar();
               }else{
                   if(!jugPos(turno==1?2:1,turno,false))
                      finalJuego();
                   else
                       setTurno(turno==1?2:1);
               }
           }
        }
//###################################################################################################################################
        int** generarMovimiento(int** tabl, posicion pos, int ficha, int fichaContraria){
               int c = 0, y, x, cc = 0, n=0;
               int **tabAux;
               tabAux = new int*[tablero1->getX()];
                for(int j=0;j<tablero1->getY();j++)
                       tabAux[j] = new int[tablero1->getY()];

               /*Se copia el tablero que se envia al tablero que jugara*/
               for(int i=0;i<tablero1->getX();i++)
                   for(int j=0;j<tablero1->getY();j++)
                       tabAux[i][j] = tabl[i][j];

            if(tabAux[pos.getI()][pos.getJ()]==3||tabAux[pos.getI()][pos.getJ()]==0){
                  //[X][0][0][0][0][0][0][X]<-  4
                  if(pos.getJ()>0)
                  if(tabAux[pos.getI()][pos.getJ()-1]==fichaContraria){
                      for(y = pos.getJ()-1; y>=0; y--){
                           if(tabAux[pos.getI()][y]==fichaContraria){
                              c++;
                          }else if(tabAux[pos.getI()][y]==0||tabAux[pos.getI()][y]==3){
                              c = 0;
                              break;
                          }else{
                              n++;
                              break;
                          }
                     }
                     y = pos.getJ()-1;
                     while(cc<c&&n==1){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[pos.getI()][y--] = ficha;
                           cc++;
                      }
                      }//Cuarto caso
                   //->[X][0][0][0][0][0][0][X]   5
                  if(pos.getJ()<tablero1->getY()-1)
                  if(tabAux[pos.getI()][pos.getJ()+1]==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(y = pos.getJ()+1; y<tablero1->getY(); y++){
                           if(tabAux[pos.getI()][y]==fichaContraria){
                              c++;
                          }else if(tabAux[pos.getI()][y]==0||tabAux[pos.getI()][y]==3){
                              c = 0;
                              break;
                          }else{
                              n++;
                              break;
                          }
                      }
                      y = pos.getJ()+1;
                     while(cc<c&&n==1){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[pos.getI()][y++] = ficha;
                           cc++;
                     }
                  }//Quinto caso

                  /*
                  [X]
                  [0]      2
                  [X]
                  ^
                  */
                  if(pos.getI()>0)
                  if(tabAux[pos.getI()-1][pos.getJ()]==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(x = pos.getI()-1; x >= 0; x--){
                           if(tabAux[x][pos.getJ()]==fichaContraria){
                               c++;
                           }else if(tabAux[x][pos.getJ()]==0||tabAux[x][pos.getJ()]==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                      }
                      x = pos.getI()-1;
                     while(cc<c&&n==1){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x--][pos.getJ()] = ficha;
                           cc++;
                     }

                  }//Caso dos
                  /*
                  [X]
                  [0]      7
                  [X]
                   v
                  */
                  if(pos.getI()<tablero1->getX()-1)
                  if(tabAux[pos.getI()+1][pos.getJ()]==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(x = pos.getI()+1; x < tablero1->getY(); x++){
                           if(tabAux[x][pos.getJ()]==fichaContraria){
                               c++;
                           }else if(tabAux[x][pos.getJ()]==0||tabAux[x][pos.getJ()]==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                     }
                      x = pos.getI()+1;
                      while(cc<c&&n==1){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x++][pos.getJ()] = ficha;
                           cc++;
                     }
                  }//Séptimo caso
                 /*Diagonal arriba izquierda 3*/
                 if(pos.getI()>0&&pos.getJ()>0)
                 if(tabAux[pos.getI()-1][pos.getJ()-1]==fichaContraria){
                    cc = 0; c = 0; n = 0; x = pos.getI()-1; y = pos.getJ()-1;
                    while(x>=0&&y>=0){
                          if(tabAux[x][y]==fichaContraria){
                               c++;
                          }else if(tabAux[x][y]==0||tabAux[x][y]==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                          x--;y--;
                    }
                      x = pos.getI()-1; y = pos.getJ()-1;
                      while(cc<c&&n==1&&(x>=0&&y>=0)){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x--][y--] = ficha;
                           cc++;
                      }
                    }//tercer caso
                  /*Diagonal abajo derecha 8 */
                  if(pos.getJ()<tablero1->getY()-1&&pos.getI()<tablero1->getX()-1)
                  if(tabAux[pos.getI()+1][pos.getJ()+1]==fichaContraria){
                    cc = 0; c = 0; n = 0; x = pos.getI()+1; y = pos.getJ()+1;
                     while(x<tablero1->getX()&&y<tablero1->getY()){
                          if(tabAux[x][y]==fichaContraria){
                               c++;
                         }else if(tabAux[x][y]==0||tabAux[x][y]==3){
                              c = 0;
                              break;
                          }else{
                               n++;
                               break;
                          }
                          x++;y++;
                     }
                      x = pos.getI()+1; y = pos.getJ()+1;
                       while(cc<c&&n==1&&(x<tablero1->getX()&&y<tablero1->getY())){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x++][y++] = ficha;
                           cc++;
                     }
                  }//Octavo caso
                 /*Diagonal abajo izquierda 6*/
                 if(pos.getJ()>0&&pos.getI()<tablero1->getX()-1)
                 if(tabAux[pos.getI()+1][pos.getJ()-1]==fichaContraria){
                    cc = 0; c = 0; n = 0; x = pos.getI()+1; y = pos.getJ()-1;
                    while(x<tablero1->getX()&&y>=0){
                          if(tabAux[x][y]==fichaContraria){
                               c++;
                          }else if(tabAux[x][y]==0||tabAux[x][y]==3){
                               c = 0;
                               break;
                           }else{
                              n++;
                              break;
                           }
                          x++;y--;
                     }
                       x = pos.getI()+1; y = pos.getJ()-1;
                      while(cc<c&&n==1&&(x<tablero1->getX()-1&&y>=0)){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x++][y--]=ficha;
                           cc++;
                      }
                   }//Sexto caso
                 /*Diagonal arriba derecha 3*/
                 if(pos.getI()>0&&pos.getJ()<tablero1->getY()-1)
                 if(tabAux[pos.getI()-1][pos.getJ()+1]==fichaContraria){
                    cc = 0; c = 0; n = 0; x = pos.getI()-1; y = pos.getJ()+1;
                    while(x>=0&&y<tablero1->getY()){
                          if(tabAux[x][y]==fichaContraria){
                               c++;
                          }else if(tabAux[x][y]==0||tabAux[x][y]==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                           x--;y++;
                     }
                      x = pos.getI()-1; y = pos.getJ()+1;
                      while(cc<c&&n==1&&(x>=0&&y<tablero1->getY())){
                           tabAux[pos.getI()][pos.getJ()]=ficha;
                           tabAux[x--][y++]=ficha;
                           cc++;
                     }
                 }//Tercer caso
              //return tabAux;
            }//ya se ha jugado en esa posicion
            return tabAux;
        }
//###################################################################################################################################
        bool jugPos(int ficha, int fichaContraria, bool ponerMarca){
        listaPos lis;
        //Función que indica donde se puede poner una pieza y si no se puede retorna false
        bool jug = false;
        int c = 0, y, x;
        for(int i = 0; i < tablero1->getX(); i++)
                for(int j = 0; j < tablero1->getY(); j++)
                  if(tablero1->getBox(i,j)->getWich()==3)
                      tablero1->getBox(i,j)->inCol(0);

              for(int i = 0; i < tablero1->getX(); i++)
                for(int j = 0; j < tablero1->getY(); j++)
                   if(tablero1->getBox(i,j)->getWich()==ficha){
                        /*Verificar los ocho lados para poner la marca*/
                      if(j>0&&tablero1->getBox(i,j-1)->getWich()==fichaContraria)
                        for(y = j-1; y>=0; y--){
                          if(tablero1->getBox(i,y)->getWich()==fichaContraria){
                             c++;
                          }else if(tablero1->getBox(i,y)->getWich()==0){
                             if(c>0){
                               if(ponerMarca)
                                 tablero1->getBox(i,y)->inCol(3);
                               lis.push(i,y);
                               jug = true;
                             }
                             c = 0;
                             break;
                          }else
                             break;
                        }
                      if(j<tablero1->getY()-1&&tablero1->getBox(i,j+1)->getWich()==fichaContraria)
                         for(y = j+1; y<tablero1->getY(); y++){
                           if(tablero1->getBox(i,y)->getWich()==fichaContraria){
                              c++;
                           }else if(tablero1->getBox(i,y)->getWich()==0){
                             if(c>0){
                               if(ponerMarca)
                                 tablero1->getBox(i,y)->inCol(3);
                               lis.push(i,y);
                               jug = true;
                             }
                             c = 0;
                             break;
                           }else
                              break;

                         }
                     if(i>0&&tablero1->getBox(i-1,j)->getWich()==fichaContraria)
                       for(x = i-1; x >= 0; x--){
                         if(tablero1->getBox(x,j)->getWich()==fichaContraria){
                             c++;
                         }else if(tablero1->getBox(x,j)->getWich()==0){
                             if(c>0){
                               if(ponerMarca)
                                  tablero1->getBox(x,j)->inCol(3);
                               lis.push(x,j);
                               jug = true;
                             }
                             c = 0;
                             break;
                         }else
                             break;
                     }
                     if(i<tablero1->getX()-1&&tablero1->getBox(i+1,j)->getWich()==fichaContraria)
                      for(x = i+1; x < tablero1->getY(); x++){
                         if(tablero1->getBox(x,j)->getWich()==fichaContraria){
                             c++;
                         }else if(tablero1->getBox(x,j)->getWich()==0){
                            if(c>0){
                              if(ponerMarca)
                                 tablero1->getBox(x,j)->inCol(3);
                              lis.push(x,j);
                              jug = true;
                            }
                            c = 0;
                            break;
                         }else
                             break;
                       }
                        x = i-1; y = j-1;
                        if(i>0&&j>0&&tablero1->getBox(x,y)->getWich()==fichaContraria)
                          while(x>=0&&y>=0){
                            if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                              c++;
                            }else if(tablero1->getBox(x,y)->getWich()==0){
                              if(c>0){
                                if(ponerMarca)
                                   tablero1->getBox(x,y)->inCol(3);
                                lis.push(x,y);
                                jug = true;
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x--;y--;
                         }
                         x = i+1; y = j+1;
                         if(j<tablero1->getY()-1&&i<tablero1->getX()-1&&tablero1->getBox(x,y)->getWich()==fichaContraria)
                          while(x<tablero1->getX()&&y<tablero1->getY()){
                            if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                              c++;
                            }else if(tablero1->getBox(x,y)->getWich()==0){
                              if(c>0){
                                if(ponerMarca)
                                   tablero1->getBox(x,y)->inCol(3);
                                lis.push(x,y);
                                jug = true;
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x++;y++;
                         }
                          x = i+1; y = j-1;
                          if(j>0&&i<tablero1->getX()-1&&tablero1->getBox(x,y)->getWich()==fichaContraria)
                          while(x<tablero1->getX()&&y>=0){
                            if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                              c++;
                            }else if(tablero1->getBox(x,y)->getWich()==0){
                              if(c>0){
                                if(ponerMarca)
                                   tablero1->getBox(x,y)->inCol(3);
                                lis.push(x,y);
                                jug = true;
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x++;y--;
                         }
                          x = i-1; y = j+1;
                       if(i>0&&j<tablero1->getY()-1&&tablero1->getBox(x,y)->getWich()==fichaContraria)
                          while(x>=0&&y<tablero1->getY()){
                            if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                              c++;
                            }else if(tablero1->getBox(x,y)->getWich()==0){
                              if(c>0){
                                if(ponerMarca)
                                   tablero1->getBox(x,y)->inCol(3);
                                lis.push(x,y);
                                jug = true;
                              }
                              c = 0;
                              break;
                            }else
                              break;
                            x--;y++;
                         }
                   }
                 listaP = lis;
                return jug;
        }
//###################################################################################################################################
        void jugada(int i, int j, int ficha, int fichaContraria){
            int c = 0, y, x, cc = 0, n=0, punt = 0;
            bool jugo = false;
            if(tablero1->getBox(i,j)->getWich()==3){
                  //[X][0][0][0][0][0][0][X]<-  4
                  if(j>0&&tablero1->getBox(i,j-1)->getWich()==fichaContraria){
                      for(y = j-1; y>=0; y--){
                           if(tablero1->getBox(i,y)->getWich()==fichaContraria){
                              c++;
                          }else if(tablero1->getBox(i,y)->getWich()==0||tablero1->getBox(i,y)->getWich()==3){
                              c = 0;
                              break;
                          }else{
                              n++;
                              break;
                          }
                     }
                     y = j-1;
                     if(n){
                        punt+=c;
                     }
                     while(cc<c&&n==1){
                           tablero1->getBox(i,y--)->voltea();
                           cc++;
                      }
                      }//Cuarto caso
                   //->[X][0][0][0][0][0][0][X]   5
                  if(j<tablero1->getY()-1&&tablero1->getBox(i,j+1)->getWich()==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(y = j+1; y<tablero1->getY(); y++){
                          if(tablero1->getBox(i,y)->getWich()==fichaContraria){
                               c++;
                           }else if(tablero1->getBox(i,y)->getWich()==0||tablero1->getBox(i,y)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                      }
                      y = j+1;
                     if(n){
                        punt+=c;
                     }
                     while(cc<c&&n==1){
                           tablero1->getBox(i,y++)->voltea();
                           cc++;
                     }
                  }//Quinto caso
                  /*
                  [X]
                  [0]      2
                  [X]
                  ^
                  */
                  if(i>0&&tablero1->getBox(i-1,j)->getWich()==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(x = i-1; x >= 0; x--){
                           if(tablero1->getBox(x,j)->getWich()==fichaContraria){
                               c++;
                           }else if(tablero1->getBox(x,j)->getWich()==0||tablero1->getBox(x,j)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                      }
                      x = i-1;
                     if(n){
                        punt+=c;
                     }
                     while(cc<c&&n==1){
                           tablero1->getBox(x--,j)->voltea();
                           cc++;
                     }
                  }//Caso dos
                  /*
                  [X]
                  [0]      7
                  [X]
                   v
                  */
                  if(i<tablero1->getX()-1&&tablero1->getBox(i+1,j)->getWich()==fichaContraria){
                     cc = 0; c = 0; n = 0;
                     for(x = i+1; x < tablero1->getY(); x++){
                           if(tablero1->getBox(x,j)->getWich()==fichaContraria){
                               c++;
                           }else if(tablero1->getBox(x,j)->getWich()==0||tablero1->getBox(x,j)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                     }
                      x = i+1;
                     if(n){
                        punt+=c;
                     }
                      while(cc<c&&n==1){
                           tablero1->getBox(x++,j)->voltea();
                           cc++;
                     }
                  }//Séptimo caso
                 /*Diagonal arriba izquierda 3*/
                 if(i>0&&j>0&&tablero1->getBox(i-1,j-1)->getWich()==fichaContraria){
                    cc = 0; c = 0; n = 0; x = i-1; y = j-1;
                    while(x>=0&&y>=0){
                          if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                               c++;
                          }else if(tablero1->getBox(x,y)->getWich()==0||tablero1->getBox(x,y)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                          x--;y--;
                    }
                      x = i-1; y = j-1;
                     if(n){
                        punt+=c;
                     }
                      while(cc<c&&n==1&&(x>=0&&y>=0)){
                           tablero1->getBox(x--,y--)->voltea();
                           cc++;
                      }
                    }//tercer caso
                  /*Diagonal abajo derecha 8 */
                  if(j<tablero1->getY()-1&&i<tablero1->getX()-1&&tablero1->getBox(i+1,j+1)->getWich()==fichaContraria){
                    cc = 0; c = 0; n = 0; x = i+1; y = j+1;
                     while(x<tablero1->getX()&&y<tablero1->getY()){
                          if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                               c++;
                         }else if(tablero1->getBox(x,y)->getWich()==0||tablero1->getBox(x,y)->getWich()==3){
                              c = 0;
                              break;
                          }else{
                               n++;
                               break;
                          }
                          x++;y++;
                     }
                      x = i+1; y = j+1;
                     if(n){
                        punt+=c;
                     }
                       while(cc<c&&n==1&&(x<tablero1->getX()&&y<tablero1->getY())){
                           tablero1->getBox(x++,y++)->voltea();
                           cc++;
                     }
                  }//Octavo caso
                 /*Diagonal abajo izquierda 6*/
                 if(j>0&&i<tablero1->getX()-1&&tablero1->getBox(i+1,j-1)->getWich()==fichaContraria){
                    cc = 0; c = 0; n = 0; x = i+1; y = j-1;
                    while(x<tablero1->getX()&&y>=0){
                          if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                               c++;
                          }else if(tablero1->getBox(x,y)->getWich()==0||tablero1->getBox(x,y)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                              n++;
                              break;
                           }
                          x++;y--;
                     }
                       x = i+1; y = j-1;
                     if(n){
                        punt+=c;
                     }
                      while(cc<c&&n==1&&(x<tablero1->getX()&&y>=0)){
                           tablero1->getBox(x++,y--)->voltea();
                           cc++;
                      }
                   }//Sexto caso
                 /*Diagonal arriba derecha 3*/
                 if(i>0&&j<tablero1->getY()-1&&tablero1->getBox(i-1,j+1)->getWich()==fichaContraria){
                    cc = 0; c = 0; n = 0; x = i-1; y = j+1;
                    while(x>=0&&y<tablero1->getY()){
                          if(tablero1->getBox(x,y)->getWich()==fichaContraria){
                               c++;
                          }else if(tablero1->getBox(x,y)->getWich()==0||tablero1->getBox(x,y)->getWich()==3){
                               c = 0;
                               break;
                           }else{
                               n++;
                               break;
                           }
                           x--;y++;
                     }
                      x = i-1; y = j+1;
                     if(n){
                        punt+=c;
                     }
                      while(cc<c&&n==1&&(x>=0&&y<tablero1->getY())){
                           tablero1->getBox(x--,y++)->voltea();
                           cc++;
                     }
                 }//Tercer caso
                 if(punt > 0){
                     tablero1->getBox(i,j)->inCol(ficha);
                     ficha==1?tablero1->numBlack+=(punt+1):tablero1->numWhite+=(punt+1);
                     ficha==1?tablero1->numWhite-=punt:tablero1->numBlack-=punt;
                 }
            }//ya se ha jugado en esa posicion
        }
//###################################################################################################################################
       void finalJuego(){
           Form1->Timer1->Enabled = false;
           tablero1->cambiarFondo(clRed);
           int pos, difpoint;
           char points[3];
           char data[300];
           pos = 11.8 + (tablero1->getX()*33.8);
           contar();
           if(panPlayer1->getPuntos() == panPlayer2->getPuntos())
             strcpy(data, "¡Ha habido un empate!") ;
           else{
             strcpy(data, "\nHa ganado ");
             difpoint = (panPlayer2->getPuntos()>panPlayer1->getPuntos())?panPlayer2->getPuntos()-panPlayer1->getPuntos():panPlayer1->getPuntos()-panPlayer2->getPuntos();
             itoa(difpoint, points, 10);
             strcat(strcat(strcat(strcat(strcat(data, (panPlayer2->getPuntos()>panPlayer1->getPuntos())?panPlayer2->getNombre().c_str():panPlayer1->getNombre().c_str()), " con "), points), " puntos de \nventaja sobre "), (panPlayer2->getPuntos()<panPlayer1->getPuntos())?panPlayer2->getNombre().c_str():panPlayer1->getNombre().c_str());
           }
           setTurno(-1);
           Form1->Button2->Left = pos/2 - Form1->Button2->Width/2;
           Form1->Button2->Top = pos;
           Form1->Button2->Visible = true;
           dialogBox(pos/16, pos/3, (pos - 11.8) - pos/16, 110,"¡Final del juego!" ,data, 0x00313131);
       }
//###################################################################################################################################
       void backToMenu(){
       //Poner valores por defecto y reabrir el panel 1
        delete panPlayer1;
        delete panPlayer2;
        delete player1;
        delete player2;
        delete tablero1;
        delete tab;
        delete matrizEva;
        turno = 1;
        panDefecto();
        Form1->Label1->Visible = true;
        Form1->Panel1->Visible = true;
        Form1->Button2->Visible = false;
       }
//###################################################################################################################################
        void setTurno(int turno){
               this->turno = turno;
               if(turno < 0){
                   (panPlayer2->getPuntos()>panPlayer1->getPuntos())?panPlayer2->colorFondo(0x0035802B):panPlayer1->colorFondo(0x0035802B);
                   (panPlayer2->getPuntos()<panPlayer1->getPuntos())?panPlayer2->colorFondo(clRed):panPlayer1->colorFondo(clRed);
               }else if(panPlayer1->getTurno() == turno){
                   panPlayer2->colorFondo(clBlack);
                   panPlayer1->colorFondo(0x003F442B);
               }else{
                   panPlayer1->colorFondo(clBlack);
                   panPlayer2->colorFondo(0x003F442B);
               }                         
        }
//###################################################################################################################################
        int getTurno(){
                return turno;
        }
//###################################################################################################################################
        int getModoJuego(){
             return modoJuego;
        }
};
game juego;
//---------------------------------------------------------------------------
void __fastcall TForm1::ClickImage(TObject *Sender)
{
    TImage *aux;
     int i = 0, j = 0;
     aux = (TImage*)Sender;
           i = (aux->Top-16)/33;
           j = (aux->Left-16)/33;
     if(!juego.getModoJuego()){ // Humano vs Robot
        if(juego.getTurno() == juego.getPlayer1()->getFicha() && juego.getTablero()->getBox(i,j)->getWich()==3){
           juego.jugada(i,j,juego.getPlayer1()->getFicha(),juego.getPlayer2()->getFicha());
           juego.setTurno(juego.getPlayer2()->getFicha());
           juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true);
        }else if(juego.getTurno() == juego.getPlayer1()->getFicha() && !juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true)){
           juego.setTurno(juego.getTurno()==1?2:1);
           if(!juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true))
              juego.finalJuego();//final del juego
           else
              juego.jugada();
        }
     }else if(juego.getModoJuego() == 2){//Humano vs humano
        bool pass = !juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true);
        if(!pass){
           if(juego.getPlayer1()->getFicha() == juego.getTurno() && juego.getTablero()->getBox(i,j)->getWich()==3){
              juego.jugada(i,j,juego.getPlayer1()->getFicha(),juego.getPlayer2()->getFicha());
              juego.setTurno(juego.getPlayer2()->getFicha());
              juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true);
           }else if(juego.getPlayer2()->getFicha() == juego.getTurno() && juego.getTablero()->getBox(i,j)->getWich()==3){
              juego.jugada(i,j,juego.getPlayer2()->getFicha(),juego.getPlayer1()->getFicha());
              juego.setTurno(juego.getPlayer1()->getFicha());
              juego.jugPos(juego.getTurno(),juego.getTurno()==1?2:1,true);
           }
        }else{
           if(!juego.jugPos(juego.getTurno()==1?2:1,juego.getTurno(),true))
              juego.finalJuego();
           else
              juego.setTurno(juego.getTurno()==1?2:1);
        }
        juego.contar();
     }
}
void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
        Form1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    //Abrir menú para modos de juego
    Form2->Close();
    Panel1->Visible = false;
    Panel5->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
int x, y, h = 0;   // posición de los tableros de puntuaciones
if(Edit1->Text==""||!(RadioButton1->Checked||RadioButton2->Checked||RadioButton3->Checked)||!(RadioButton4->Checked||RadioButton5->Checked))
   dialogBox(25, 160, 300, 95, "Aviso","Debe ingresar su nombre,\nel tamaño del tablero y el color de la ficha", 0x000C2901);
else{
    Panel2->Visible = false;
    Label1->Visible = false;
     if(RadioButton1->Checked){
         h = 8;
         Form1->Width = 299;
         x = 267;
         Form1->Height = 422;
         y = 283;

     }else if(RadioButton2->Checked){
         h = 10;
         Form1->Width = 365;
         x = 333;
         Form1->Height = 491;
         y = 350;
     }else if(RadioButton3->Checked){
         h = 12;
         Form1->Width = 433;
         x = 403;
         Form1->Height = 560;
         y = 417;
     }
     juego.iniPlayer1(RadioButton4->Checked?1:2, (char*)Edit1->Text.c_str(), 0);
     juego.iniPlayer2(RadioButton4->Checked?2:1, "Robot1", 0);
     juego.inicio(h,h,0);
     //Se crean los paneles de puntuaciones
     juego.setPanPlayer1(new pan(juego.getTablero()->getFondo()->Left, juego.getTablero()->getFondo()->Top + y, RadioButton4->Checked?1:2, Form1->Edit1->Text, false)); //false para colocar el nombre arriba
     juego.setPanPlayer2(new pan(juego.getTablero()->getFondo()->Left + x-62, juego.getTablero()->getFondo()->Top + y, RadioButton4->Checked?2:1, "Robot1", true)); //true para ponerlo abajo
     juego.setTurno(juego.getTurno());
     juego.contar();
     Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
}
void dialogBox(int x, int y, int width, int height, char titulo[50], char text[300], const TColor color){
    Form1->Panel4->Visible = true;
    Form1->Panel4->BringToFront();
    Form1->Panel4->Left = x;
    Form1->Shape1->Left = 0;
    Form1->Panel4->Top = y;
    Form1->Shape1->Top = 0;
    Form1->Panel4->Height =  height;
    Form1->Shape1->Height = height;
    Form1->Panel4->Width = width;
    Form1->Shape1->Width = width;
    Form1->Shape1->Brush->Color = color;
    Form1->Shape1->Pen->Width = 4;
    Form1->Shape1->Pen->Color = clWhite;
    Form1->Label6->Caption = (AnsiString)titulo;
    Form1->Label6->Left = width/2 - Form1->Label6->Width/2;
    Form1->Label6->Top = 10;
    Form1->Label6->Color = clWhite;
    Form1->Label6->Font->Color = clBlack;
    Form1->Label6->Font->Size = 4;
    Form1->Label5->Caption = (AnsiString)text;
    Form1->Label5->Left = 5;
    Form1->Label5->Top = 25;
    Form1->Label5->Color = color;
    Form1->Label5->Font->Color = clWhite;
    Form1->Label5->Font->Size = 4;
    Form1->Button1->Left = width/2 - Form1->Button1->Width/2;
    Form1->Button1->Top = height - 35;
    Form1->Button1->Caption = "Aceptar";
    Form1->Panel4->Visible = true;
    Form1->Shape1->SendToBack();
}
//---------------------------------------------------------------------------
void panDefecto(){
//Pone los paneles por defecto
Form1->Width = 380;
Form1->Height = 471;
       Form1->Edit1->Text = "";
       Form1->RadioButton1->Checked = false;
       Form1->RadioButton2->Checked = false;
       Form1->RadioButton3->Checked = false;
       Form1->RadioButton4->Checked = false;
       Form1->RadioButton5->Checked = false;
       Form1->RadioButton8->Checked = false;
       Form1->RadioButton9->Checked = false;
       Form1->RadioButton10->Checked = false;
       Form1->RadioButton11->Checked = false;
       Form1->RadioButton17->Checked = false;
       Form1->RadioButton18->Checked = false;
       Form1->RadioButton19->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
dialogBox(25, 160, 320, 110,"Acerca de" ,"Programado por Kevin Hernández\nUniversidad Nacional Experimental del Táchira\nEstructura de datos - Sección 2 - 2012-2" , 0x000C2901);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  juego.jugada();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Panel4->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
   Form2->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 juego.backToMenu();
 Panel4->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    Panel1->Visible = true;
    Panel5->Visible = false;
    Panel4->Visible = false;
    Edit1->Text = "";
    RadioButton8->Checked = false;
    RadioButton9->Checked = false;
    RadioButton10->Checked = false;
    RadioButton11->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
if( (RadioButton9->Checked||RadioButton10->Checked) && (RadioButton8->Checked||RadioButton11->Checked)){
    Panel5->Visible = false;
    if((RadioButton9->Checked&&RadioButton8->Checked) || (RadioButton10->Checked&&RadioButton11->Checked))
       //Humano vs robot
       Panel2->Visible = true;
    else if(RadioButton9->Checked&&RadioButton11->Checked){
        //Humano vs humano
       Form1->Height = 520;
       Panel7->Visible = true;
    }else if(RadioButton10->Checked&&RadioButton8->Checked){
        Panel11->Visible = true;
        //Robot vs robot
    }
}else
 dialogBox(25, 165, 300, 95, "Aviso","   Debe seleccionar una modalidad de juego\n correcta", 0x000C2901);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
       Panel5->Visible = true;
       Panel2->Visible = false;
       Edit1->Text = "";
       RadioButton1->Checked = false;
       RadioButton2->Checked = false;
       RadioButton3->Checked = false;
       RadioButton4->Checked = false;
       RadioButton5->Checked = false;
       RadioButton8->Checked = false;
       RadioButton9->Checked = false;
       RadioButton10->Checked = false;
       RadioButton11->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
       Panel5->Visible = true;
       Panel7->Visible = false;
       Form1->Height = 471;
       Edit2->Text = "";
       Edit3->Text = "";
       RadioButton6->Checked = false;
       RadioButton7->Checked = false;
       RadioButton12->Checked = false;
       RadioButton13->Checked = false;
       RadioButton14->Checked = false;
       RadioButton15->Checked = false;
       RadioButton16->Checked = false;
       RadioButton8->Checked = false;
       RadioButton9->Checked = false;
       RadioButton10->Checked = false;
       RadioButton11->Checked = false;
}
//---------------------------------------------------------------------------
/*->Cambiar las selecciones en el panel de humano vs humano<-*/
void __fastcall TForm1::RadioButton13Click(TObject *Sender)
{
 if(RadioButton15->Checked){
    RadioButton15->Checked = false;
    RadioButton16->Checked = true;
 }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton14Click(TObject *Sender)
{
   if(RadioButton16->Checked){
    RadioButton16->Checked = false;
    RadioButton15->Checked = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton15Click(TObject *Sender)
{
 if(RadioButton13->Checked){
    RadioButton13->Checked = false;
    RadioButton14->Checked = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton16Click(TObject *Sender)
{
 if(RadioButton14->Checked){
    RadioButton14->Checked = false;
    RadioButton13->Checked = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
       Panel5->Visible = true;
       Panel11->Visible = false;

       RadioButton17->Checked = false;
       RadioButton18->Checked = false;
       RadioButton19->Checked = false;

       RadioButton8->Checked = false;
       RadioButton9->Checked = false;
       RadioButton10->Checked = false;
       RadioButton11->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn6Click(TObject *Sender)
{
      int x, y, h = 0;   // posición de los tableros de puntuaciones
if(Edit2->Text==""||Edit3->Text==""||!(RadioButton6->Checked||RadioButton7->Checked||RadioButton12->Checked)||!(RadioButton13->Checked||RadioButton14->Checked)||!(RadioButton15->Checked||RadioButton16->Checked))
   dialogBox(25, 170, 300, 95, "Aviso","Debe ingresar ambos nombre,\nel tamaño del tablero y el color de las fichas", 0x000C2901);

else{
    Panel7->Visible = false;
    Label1->Visible = false;
     if(RadioButton6->Checked){
         h = 8;
         Form1->Width = 299;
         x = 267;
         Form1->Height = 422;
         y = 283;

     }else if(RadioButton7->Checked){
         h = 10;
         Form1->Width = 365;
         x = 333;
         Form1->Height = 491;
         y = 350;
     }else if(RadioButton12->Checked){
         h = 12;
         Form1->Width = 433;
         x = 403;
         Form1->Height = 560;
         y = 417;
     }
     juego.iniPlayer1(RadioButton13->Checked?1:2, (char*)Edit2->Text.c_str(), 2);
     juego.iniPlayer2(RadioButton13->Checked?2:1, (char*)Edit3->Text.c_str(), 2);
     juego.inicio(h,h,2);
     //Se crean los paneles de puntuaciones
     juego.setPanPlayer1(new pan(juego.getTablero()->getFondo()->Left, juego.getTablero()->getFondo()->Top + y, RadioButton13->Checked?1:2, Edit2->Text, false)); //false para colocar el nombre arriba
     juego.setPanPlayer2(new pan(juego.getTablero()->getFondo()->Left + x-62, juego.getTablero()->getFondo()->Top + y, RadioButton13->Checked?2:1, Edit3->Text, true)); //true para ponerlo abajo
     juego.setTurno(juego.getTurno());
     juego.contar();
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn7Click(TObject *Sender)
{
           int x, y, h = 0;   // posición de los tableros de puntuaciones
if(!(RadioButton17->Checked||RadioButton18->Checked||RadioButton19->Checked))
   dialogBox(25, 170, 300, 95, "Aviso","Debe ingresar el tamaño del tablero", 0x000C2901);

else{
    Panel11->Visible = false;
    Label1->Visible = false;
     if(RadioButton17->Checked){
         h = 8;
         Form1->Width = 299;
         x = 267;
         Form1->Height = 422;
         y = 283;

     }else if(RadioButton18->Checked){
         h = 10;
         Form1->Width = 365;
         x = 333;
         Form1->Height = 491;
         y = 350;
     }else if(RadioButton19->Checked){
         h = 12;
         Form1->Width = 433;
         x = 403;
         Form1->Height = 560;
         y = 417;
     }
     juego.iniPlayer1(1, "Robot1", 1); //Fichas negras
     juego.iniPlayer2(2, "Robot2", 1); //Fichas blancas
     juego.inicio(h,h,1);
     //Se crean los paneles de puntuaciones
     juego.setPanPlayer1(new pan(juego.getTablero()->getFondo()->Left, juego.getTablero()->getFondo()->Top + y, 1, "Robot1", false)); //false para colocar el nombre arriba
     juego.setPanPlayer2(new pan(juego.getTablero()->getFondo()->Left + x-62, juego.getTablero()->getFondo()->Top + y, 2, "Robot2", true)); //true para ponerlo abajo
     juego.setTurno(juego.getTurno());
     juego.contar();
     Timer1->Enabled = true;
     }
}
//---------------------------------------------------------------------------

