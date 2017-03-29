 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de captura de parámetros del metodos de integración                             //
 // Revisión: 8 de Enero del 2003                                                            //
 //                                                                                          //
 // Copyright (C) 1997-2003                                                                  //
 //                                                                                          //
 // Análisis y Diseño:                                                                       //
 //                                                                                          //
 // Autor     Dr. Humberto Carrillo Calvet                                                   //
 // E-mail:   carr@servidor.unam.mx                                                          //
 // Página:   http://www.dynamics.unam.edu/hcc                                               //
 //                                                                                          //
 // Autor:    Antonio Carrillo Ledesma                                                       //
 // E-mail:   acl@www.dynamics.unam.edu                                                      //
 // Página:   http://www.dynamics.unam.edu/acl                                               //
 //                                                                                          //
 // Programación:                                                                            //
 //                                                                                          //
 // Autor:    Antonio Carrillo Ledesma                                                       //
 // E-mail:   acl@www.dynamics.unam.edu                                                      //
 // Página:   http://www.dynamics.unam.edu/acl                                               //
 //                                                                                          //
 // Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
 // bajo los términos de la Licencia Pública General de GNU según es                         //
 // publicada por la Free Software Foundation, bien de la versión 2 de                       //
 // dicha Licencia o bien (según su elección) de cualquier versión                           //
 // posterior.                                                                               //
 //                                                                                          //
 // Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
 // NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
 // garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
 // Licencia Pública General de GNU para más detalles.                                       //
 //                                                                                          //
 // Debería haber recibido una copia de la Licencia Pública General junto                    //
 // con este programa. Si no ha sido así, escriba a la Free Software                         //
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

