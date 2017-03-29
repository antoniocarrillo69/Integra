 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de captura de condiciones iniciales                                              //
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
#ifndef VDCondicionInicialH
#define VDCondicionInicialH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCondicionInicial : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TListBox *ListBoxCondicionInicial;
        TStaticText *NombreVariable;
        TEdit *EditaValorVariable;
        TButton *Button1;
        TStaticText *StaticText2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ListBoxCondicionInicialClick(TObject *Sender);
        void __fastcall EditaValorVariableKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TCondicionInicial(TComponent* Owner);
        bool Estado;
        bool Capturando;
};
//---------------------------------------------------------------------------
extern PACKAGE TCondicionInicial *CondicionInicial;
//---------------------------------------------------------------------------
#endif

