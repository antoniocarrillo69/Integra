 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de seleci�n de los colores usados en el sistema                                  //
 // Revisi�n: 8 de Enero del 2003                                                            //
 //                                                                                          //
 // Copyright (C) 1997-2003                                                                  //
 //                                                                                          //
 // An�lisis y Dise�o:                                                                       //
 //                                                                                          //
 // Autor     Dr. Humberto Carrillo Calvet                                                   //
 // E-mail:   carr@servidor.unam.mx                                                          //
 // P�gina:   http://www.dynamics.unam.edu/hcc                                               //
 //                                                                                          //
 // Autor:    Antonio Carrillo Ledesma                                                       //
 // E-mail:   acl@www.dynamics.unam.edu                                                      //
 // P�gina:   http://www.dynamics.unam.edu/acl                                               //
 //                                                                                          //
 // Programaci�n:                                                                            //
 //                                                                                          //
 // Autor:    Antonio Carrillo Ledesma                                                       //
 // E-mail:   acl@www.dynamics.unam.edu                                                      //
 // P�gina:   http://www.dynamics.unam.edu/acl                                               //
 //                                                                                          //
 // Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
 // bajo los t�rminos de la Licencia P�blica General de GNU seg�n es                         //
 // publicada por la Free Software Foundation, bien de la versi�n 2 de                       //
 // dicha Licencia o bien (seg�n su elecci�n) de cualquier versi�n                           //
 // posterior.                                                                               //
 //                                                                                          //
 // Este programa se distribuye con la esperanza de que sea �til, pero SIN                   //
 // NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita o sin                      //
 // garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. V�ase la                        //
 // Licencia P�blica General de GNU para m�s detalles.                                       //
 //                                                                                          //
 // Deber�a haber recibido una copia de la Licencia P�blica General junto                    //
 // con este programa. Si no ha sido as�, escriba a la Free Software                         //
 // Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
 //                                                                                          //
 //                                                                                          //
 //////////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------
#ifndef VDColoresSistemaH
#define VDColoresSistemaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TColoresSistema : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TGroupBox *GroupBox2;
        TStaticText *StaticText4;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TColorDialog *ColorDialog;
        TGroupBox *GroupBox3;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TPanel *Panel8;
        TPanel *Panel9;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Panel2Click(TObject *Sender);
        void __fastcall Panel3Click(TObject *Sender);
        void __fastcall Panel4Click(TObject *Sender);
        void __fastcall Panel5Click(TObject *Sender);
        void __fastcall Panel6Click(TObject *Sender);
        void __fastcall Panel7Click(TObject *Sender);
        void __fastcall Panel8Click(TObject *Sender);
        void __fastcall Panel9Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TColoresSistema(TComponent* Owner);
        bool Estado;
};
//---------------------------------------------------------------------------
extern PACKAGE TColoresSistema *ColoresSistema;
//---------------------------------------------------------------------------
#endif

