 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de captura de parámetros del cálculo de equilibrios                              //
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
#ifndef VDEquilibriosH
#define VDEquilibriosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormaParametrosEquilibrios : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TEdit *Edit1;
        TEdit *Edit2;
        TGroupBox *GroupBox2;
        TStaticText *StaticText3;
        TEdit *Edit3;
        TBitBtn *FormaCapturaParametrosEquilibrios;
        TStaticText *StaticText4;
        TStaticText *StaticText5;
        TEdit *Edit4;
        TEdit *Edit5;
        void __fastcall FormaCapturaParametrosEquilibriosClick(
          TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormaParametrosEquilibrios(TComponent* Owner);
        bool Estado;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormaParametrosEquilibrios *FormaParametrosEquilibrios;
//---------------------------------------------------------------------------
#endif
