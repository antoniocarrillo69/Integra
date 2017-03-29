//////////////////////////////////////////////////////////////////////////////////////////////
// Acerca de ...                                                                            //
// Revisi�n: 10 de Abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001                                                                       //
//                                                                                          //
// An�lisis y Dise�o:                                                                       //
//                                                                                          //
// Autor     Dr. Humberto Carrillo Calvet                                                   //
// E-mail:   carr@servidor.unam.mx                                                          //
// P�gina:   http://www.dynamics.unam.edu/hcc                                               //
//                                                                                          //
// Autor:    Luis Alonso Nava Fernandez                                                     //
// E-mail:   nava@athena.fciencias.unam.mx                                                  //
// P�gina:   http://www.dynamics.unam.edu/lanf                                              //
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





#include <vcl\vcl.h>
#include "Acecade.h"
#include "ACX-WebBrowser.h"
#include "EnviarCorreo.h"
#pragma hdrstop

extern const char *WWW;
extern const char *VERSION;
extern const char *DERECHOS_AUTOR;
extern const char *FECHA_DERECHOS_AUTOR;
extern const char *REGISTRO_AUTOR;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVAcercaDe::TVAcercaDe(TComponent* Owner) : TForm(Owner)
{
   // Nombre de la aplicaci�n
   Label10->Caption = Application->Title;
   // Fecha de generacion de la versi�n
   FechaGeneracion->Caption = __DATE__;
   // Versi�n del sistema
   Label13->Caption = VERSION;
   // Derechos de Autor
   Label20->Caption = DERECHOS_AUTOR;
   Label1->Caption = REGISTRO_AUTOR;
   Label2->Caption = FECHA_DERECHOS_AUTOR;
   
   
}
//---------------------------------------------------------------------------


// P�gina de Humberto Carrillo
void __fastcall TVAcercaDe::Label5Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/hcc");
       vent->Show();
   }
}


// P�gina de Antonio Carrillo
void __fastcall TVAcercaDe::Label16Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/acl");
       vent->Show();
   }
}

// P�gina de Luis Nava
void __fastcall TVAcercaDe::Label4Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/");
       vent->Show();     
   }
}


// P�gina del Laboratorio
void __fastcall TVAcercaDe::Label10Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros(WWW);
       vent->Show();
   }
}

// Correo del Laboratorio
void __fastcall TVAcercaDe::Label3Click(TObject *Sender)
{
   TFormaEnviarCorreo *vent = new TFormaEnviarCorreo(this);
   if (vent) {
       vent->Parametros("UserMail@dinamica1.fciencias.unam.mx","dinamica@www.dynamics.unam.edu",Application->Title.c_str());
       vent->ShowModal();
   }
}




