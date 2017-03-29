 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de captura de par�metros del metodos de integraci�n                             //
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
#ifndef VDMetodosIntrgracionH
#define VDMetodosIntrgracionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Controlador.hpp"
//---------------------------------------------------------------------------
class TConfiguracionMetodosIntegracion : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TComboBox *ListaMetodosNumericos;
        TStaticText *StaticText1;
        TGroupBox *GroupBox1;
        TStaticText *StaticText2;
        TEdit *Edit1;
        TStaticText *StaticText3;
        TEdit *Edit2;
        TStaticText *StaticText4;
        TEdit *Edit3;
        TStaticText *StaticText5;
        TEdit *Edit4;
        TStaticText *StaticText6;
        TEdit *Edit5;
        TStaticText *StaticText7;
        TEdit *Edit6;
        TButton *Button1;
        TGroupBox *GroupBox2;
        TEdit *Edit7;
        TStaticText *StaticText8;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ListaMetodosNumericosChange(TObject *Sender);
private:	// User declarations
        Controlador           *Ctrl;
public:		// User declarations
        __fastcall TConfiguracionMetodosIntegracion(TComponent* Owner);
        void Pasa_puntero_controlador(Controlador *ptr)
             {
                 Ctrl = ptr;
             }
        void Actualiza_valores(void);
        bool Estado;
};
//---------------------------------------------------------------------------
extern PACKAGE TConfiguracionMetodosIntegracion *ConfiguracionMetodosIntegracion;
//---------------------------------------------------------------------------
#endif

