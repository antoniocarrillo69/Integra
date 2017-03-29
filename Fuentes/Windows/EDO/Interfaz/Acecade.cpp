//////////////////////////////////////////////////////////////////////////////////////////////
// Acerca de ...                                                                            //
// Revisión: 10 de Abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001                                                                       //
//                                                                                          //
// Análisis y Diseño:                                                                       //
//                                                                                          //
// Autor     Dr. Humberto Carrillo Calvet                                                   //
// E-mail:   carr@servidor.unam.mx                                                          //
// Página:   http://www.dynamics.unam.edu/hcc                                               //
//                                                                                          //
// Autor:    Luis Alonso Nava Fernandez                                                     //
// E-mail:   nava@athena.fciencias.unam.mx                                                  //
// Página:   http://www.dynamics.unam.edu/lanf                                              //
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
   // Nombre de la aplicación
   Label10->Caption = Application->Title;
   // Fecha de generacion de la versión
   FechaGeneracion->Caption = __DATE__;
   // Versión del sistema
   Label13->Caption = VERSION;
   // Derechos de Autor
   Label20->Caption = DERECHOS_AUTOR;
   Label1->Caption = REGISTRO_AUTOR;
   Label2->Caption = FECHA_DERECHOS_AUTOR;
   
   
}
//---------------------------------------------------------------------------


// Página de Humberto Carrillo
void __fastcall TVAcercaDe::Label5Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/hcc");
       vent->Show();
   }
}


// Página de Antonio Carrillo
void __fastcall TVAcercaDe::Label16Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/acl");
       vent->Show();
   }
}

// Página de Luis Nava
void __fastcall TVAcercaDe::Label4Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://www.dynamics.unam.edu/");
       vent->Show();     
   }
}


// Página del Laboratorio
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




