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

   // Metodo n�merico tipo 1
   if (Ctrl->Retorna_tipo_parametros_metodo_integracion(ListaMetodosNumericos->ItemIndex) == 1) {
       StaticText2->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(1,0);
       StaticText3->Caption = Ctrl->Retorna_nombre_parametro_metodo_integracion(1,1);
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,0));
       Edit1->Text = xcad;
       sprintf(xcad,"%1.9Le",Ctrl->Retorna_valor_parametro_metodo_integracion(ListaMetodosNumericos->ItemIndex,1));
       Edit2->Text = xcad;
   }
   // Metodo n�merico tipo 2
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
   // Metodo n�merico tipo 3
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
   // Cota para el c�lculo
   sprintf(xcad,"%1.9Le",Ctrl->Retorna_cota_evitar_overflow());
   Edit7->Text = xcad;
}


void __fastcall TConfiguracionMetodosIntegracion::ListaMetodosNumericosChange(TObject *Sender)
{
   Actualiza_valores();     
}

