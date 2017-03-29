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
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "VDCondicionInicial.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCondicionInicial *CondicionInicial;
//---------------------------------------------------------------------------
__fastcall TCondicionInicial::TCondicionInicial(TComponent* Owner) : TForm(Owner)
{
   Estado = false;
   Capturando = false;
}


void __fastcall TCondicionInicial::Button1Click(TObject *Sender)
{
   if (Capturando) {
      char xcad[100], xcad1[100];
      AnsiString txt1(NombreVariable->Caption);
      memccpy(xcad1,txt1.c_str(),0,99);
      AnsiString txt2(EditaValorVariable->Text);
      sprintf(xcad,"%s = %1.9f",xcad1,atof(txt2.c_str()));
      for (int i = 0; i < ListBoxCondicionInicial->Items->Count; i++) {
          if (ListBoxCondicionInicial->Selected[i]) ListBoxCondicionInicial->Items->Strings[i] = xcad; 
      }    
   }
   Estado = true;
   Close();        
}


void __fastcall TCondicionInicial::ListBoxCondicionInicialClick(TObject *Sender)
{
   Capturando = true;
   unsigned int i1, i2;
   int i;
   for (i = 0; i < ListBoxCondicionInicial->Items->Count; i++) {
       if (ListBoxCondicionInicial->Selected[i]) {
           char xcad[100], xcad1[100];
           // Nombre del parámetro
           AnsiString txt1(ListBoxCondicionInicial->Items->Strings[i]);
           memccpy(xcad1,txt1.c_str(),0,99);
           i1 = 0;
           while(xcad1[i1] != ' ') {
               xcad[i1] = xcad1[i1];
               i1++;
           }
           xcad[i1] = ':';
           xcad[i1+1] = 0;
           NombreVariable->Caption = xcad;
           while(xcad1[i1] != '=') i1++;
           i1++;
           // Valor del parámetro
           for (i2 = 0; i1 < strlen(xcad1); i2++, i1++) { 
               xcad[i2] = xcad1[i1];
           }
           xcad[i2] = 0;
           EditaValorVariable->Text = xcad;
           // Se hace visible el nombre y valor del parámetro
           NombreVariable->Visible = true;
           EditaValorVariable->Visible = true;     
           break;
       }
   }
}

void __fastcall TCondicionInicial::EditaValorVariableKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      Key = 0;
      PostMessage(Handle, WM_NEXTDLGCTL,0,0);
      char xcad[100], xcad1[100];
      AnsiString txt1(NombreVariable->Caption);
      memccpy(xcad1,txt1.c_str(),0,99);
      AnsiString txt2(EditaValorVariable->Text);
      sprintf(xcad,"%s = %1.9f",xcad1,atof(txt2.c_str()));
      for (int i = 0; i < ListBoxCondicionInicial->Items->Count; i++) {
          if (ListBoxCondicionInicial->Selected[i]) ListBoxCondicionInicial->Items->Strings[i] = xcad; 
      }    
      NombreVariable->Visible = false;
      EditaValorVariable->Visible = false;     
      Capturando = false;
   }
}

