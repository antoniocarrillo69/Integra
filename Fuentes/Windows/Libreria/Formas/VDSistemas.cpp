 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de selección de sistema                                                          //
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
#include <io.h>
#pragma hdrstop

#include "VDSistemas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSeleccionSistemas *SeleccionSistemas;
//---------------------------------------------------------------------------
__fastcall TSeleccionSistemas::TSeleccionSistemas(TComponent* Owner) : TForm(Owner)
{
   Estado = false;
}


void __fastcall TSeleccionSistemas::Button1Click(TObject *Sender)
{
   Estado = true;
   Close();        
}


void __fastcall TSeleccionSistemas::ListBoxSistemasClick(TObject *Sender)
{
   for (int i = 0; i < ListBoxSistemas->Items->Count; i++) {
       if (ListBoxSistemas->Selected[i]) Actualiza_configuracion(i);
   }
}


void TSeleccionSistemas::Actualiza_configuracion(const int i)
{
   char xcad[200], ARCHIVO[100];
   Memo1->Visible = false;
   Memo2->Visible = false;
   // Limpia los memos
   Memo1->Lines->Clear();
   Memo2->Lines->Clear();
   // Inserta las ecuaciones del sistema
   sprintf(xcad,"System: %s",Ctrl->Retorna_nombre_sistema(i));
   Memo1->Lines->Append(xcad);
   Memo1->Lines->Append("");
   Memo1->Lines->Append("Equations:");
   if (Ctrl->Retorna_tipo_ecuacion(i)) {
      Memo1->Lines->Append(" Original:");
      sprintf(xcad,"   %s",Ctrl->Retorna_ecuacion_original(i));
      Memo1->Lines->Append(xcad);
      Memo1->Lines->Append(" System:");
   }
   for (int xi = 0; xi < Ctrl->Retorna_numero_ecuaciones_sistema(i); xi++) {
      sprintf(xcad,"   %s",Ctrl->Retorna_ecuacion_sistema(i,xi));
      Memo1->Lines->Append(xcad);
   }
   Memo1->Lines->Append("");
   Memo1->Lines->Append("Parameters:");
   for (int xi = 0; xi < Ctrl->Numero_parametros_sistema(i); xi++) {
      sprintf(xcad,"   %s = %1.10Lf",Ctrl->Retorna_nombre_parametro(i,xi), Ctrl->Retorna_valor_parametro(i,xi));
      Memo1->Lines->Append(xcad);
   }
   // Carga la descripción del sistema
   sprintf(ARCHIVO,"%s%02d",Ctrl->Retorna_nombre_proyecto(),i+1);
   if (access(ARCHIVO,04) == 0) {
      Memo2->Lines->LoadFromFile(ARCHIVO);
   } else Memo2->Lines->Append("No have description for this system.");

   Memo1->Visible = true;
   Memo2->Visible = true;
   // Indica el sistema activo el la lista de sistemas
   ListBoxSistemas->ItemIndex = i;
}

