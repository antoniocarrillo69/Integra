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
#include <vcl.h>
#pragma hdrstop

#include "VDMetodosIntegracion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfiguracionMetodosIntegracion *ConfiguracionMetodosIntegracion;
//---------------------------------------------------------------------------

__fastcall TConfiguracionMetodosIntegracion::TConfiguracionMetodosIntegracion(TComponent* Owner) : TForm(Owner)
{
   Estado = false;
}


void __fastcall TConfiguracionMetodosIntegracion::Button1Click(TObject *Sender)
{
   Estado = true;
   Close();        
}


void TConfiguracionMetodosIntegracion::Actualiza_valores(void)
{
   char xcad[200];
   StaticText4->Visible = false;
   Edit3->Visible = false;
   StaticText5->Visible = false;
   Edit4->Visible = false;
   StaticText6->Visible = false;
   Edit5->Visible = false;

   // Metodo númerico tipo 1
   if (Ctrl->Retorna_tipo_parametros_metodo_integracion(ListaMetodosNumericos->ItemIndex) == 1) {
       StaticText2->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(1,0);
       StaticText3->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(1,1);
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,0));
       Edit1->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,1));
       Edit2->Text = xcad;
   }
   // Metodo númerico tipo 2
   if (Ctrl->Retorna_tipo_parametros_metodo_integracion(ListaMetodosNumericos->ItemIndex) == 2) {
       StaticText2->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(2,0);
       StaticText3->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(2,1);
       StaticText4->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(2,2);
       StaticText5->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(2,3);
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,0));
       Edit1->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,1));
       Edit2->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,2));
       Edit3->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,3));
       Edit4->Text = xcad;
       StaticText4->Visible = true;
       StaticText5->Visible = true;
       Edit3->Visible = true;
       Edit4->Visible = true;
   }
   // Metodo númerico tipo 3
   if (Ctrl->Retorna_tipo_parametros_metodo_integracion(ListaMetodosNumericos->ItemIndex) == 3) {
       StaticText2->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(3,0);
       StaticText3->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(3,1);
       StaticText4->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(3,2);
       StaticText5->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(3,3);
       StaticText6->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(3,4);
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,0));
       Edit1->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,1));
       Edit2->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,2));
       Edit3->Text = xcad;
       sprintf(xcad,"%3Lf",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,3));
       Edit4->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,4));
       Edit5->Text = xcad;
       StaticText4->Visible = true;
       StaticText5->Visible = true;
       StaticText6->Visible = true;
       Edit3->Visible = true;
       Edit4->Visible = true;
       Edit5->Visible = true;
   }
   // Cota para el cálculo
   sprintf(xcad,"%1.9Le",Ctrl->Retorna_cota_evitar_overflow());
   Edit7->Text = xcad;
}


void __fastcall TConfiguracionMetodosIntegracion::ListaMetodosNumericosChange(TObject *Sender)
{
   Actualiza_valores();     
}

