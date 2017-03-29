//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana Principal                                                                        //
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


#include <vcl.h>
#include <vcl\Registry.hpp>
#include <Printers.hpp>
#include <dir.h>
#include "Ayuda.h"
#include "Acecade.h"
#include "VentanaVisualizacion.h"
#include "ACX-WebBrowser.h"
#include "Man_arch.hpp"
#pragma hdrstop

#include "Principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TVentanaPrincipal *VentanaPrincipal;
// Variables globales
const char *CLAVE_REGISTRO          = "Laboratorio de Dinamica no Lineal\\Bifurcations Interactive Analyzer 1.0";
const char *TRAYECTORIA_ARCHIVOS    = ".\\";
const char *TituloAplicacion        = "Interfaz of INTEGRA 1.0";
const char *VERSION                 = "Version: 1.0.1 b";
const char *DERECHOS_AUTOR          = "Copyright:  1997 - 2003";
const char *FECHA_DERECHOS_AUTOR    = "México, D.F. Otoño del 2003";
const char *REGISTRO_AUTOR          = "SEP-INDAUTOR: 167025";
const char *COMPANIA                = "Laboratorio de Dinámica no Lineal, UNAM";
const char *E_MAIL                  = "E-mail: dinamica@www.dynamics.unam.edu";
const char *WWW                     = "http://www.dynamics.unam.edu/integra/";
void *Ventana_activa;

#define SOLICITUDINVESTIGADOR "C:\\Integra\\Help\\SolicitudInvestigador.txt"
#define SOLICITUDPROFESOR "C:\\Integra\\Help\\SolicitudProfesor.txt"
#define SOLICITUDESTUDIANTE "C:\\Integra\\Help\\SolicitudEstudiante.txt"
#define SOLICITUDDATOS "C:\\Integra\\Help\\Solicitud.txt"
#define AYUDAINTERFAZ  "C:\\Integra\\Help\\Interfaz.hlp"
#define DIRECCIONLDNL  "http://Dinamica1.fciencias.unam.mx"

#ifdef _IDIOMA_ESPANOL_
   #define VPTXT01 "Do you wish to end the program?"
   #define VPTXT02 "E-mail"
   #define VPTXT03 "Config user E-mail"
   #define VPTXT04 "General help"
   #define VPTXT05 "New Name:"
   #define VPTXT06 "Rename system"
   #define VPTXT07 "Duplicate System"
#else
   #define VPTXT01 "Do you wish to end the program?"
   #define VPTXT02 "E-mail"
   #define VPTXT03 "Config user E-mail"
   #define VPTXT04 "General help"
   #define VPTXT05 "New Name:"
   #define VPTXT06 "Rename system"
   #define VPTXT07 "Duplicate System"
#endif


// Constructor de la aplicación
__fastcall TVentanaPrincipal::TVentanaPrincipal(TComponent* Owner) : TForm(Owner)
{
   Caption = TituloAplicacion;
   Application->Title = Caption;
   int top = 30, left = 30; 
   Usuario = 2; // (2) Estudiante, (1) Maestro, (0) Investigador

   try {
      TRegistry &regkey = * new TRegistry();
      bool keygood = regkey.OpenKey(CLAVE_REGISTRO,false);
      if (keygood) {
         top = regkey.ReadInteger("Top");
         left = regkey.ReadInteger("Left");
         Usuario = regkey.ReadInteger("Usuario");
      }
   } catch (...) {};
   Top = top, Left = left;

   try {
      // Carga el icono de la aplicación
      Application->Icon->LoadFromFile("INTERFAZ.ICO");
   } catch (...) {};
   // Tiempo maximo de muestra de Hits
   Application->HintHidePause = 10000;

   // Muestra la ventana de presentación
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
   if (Usuario == 0) Usuario0->Checked = true;
   if (Usuario == 1) Usuario1->Checked = true;
   if (Usuario == 2) Usuario2->Checked = true;
}


// Controla la visualizacion de Hint en la barra de estado
void __fastcall TVentanaPrincipal::OnHint(TObject *Sender)
{
   BarraEstadoPrincipal->SimpleText = Application->Hint;
}

// Al solicitar cerrar el programa
void __fastcall TVentanaPrincipal::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   try {
      // Graba la configuracion de la ventana
      TRegistry &regkey = * new TRegistry();
      bool keygood = regkey.OpenKey(CLAVE_REGISTRO,true);
      if (keygood) {
         regkey.WriteInteger("Top", Top);
         regkey.WriteInteger("Left", Left);
         regkey.WriteInteger("Usuario", Usuario);
      }
   } catch (...) {};

   CanClose = false;
   if (MessageBox(Handle,VPTXT01,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      CanClose = true;
      exit(EXIT_SUCCESS);
   }
}

// Al activar la ventana
void __fastcall TVentanaPrincipal::FormActivate(TObject *Sender)
{
   Application->OnHint = &OnHint;        
}

// Al crearse la forma
void __fastcall TVentanaPrincipal::FormCreate(TObject *Sender)
{
   // Asigna la rutina de visualizacion de la barra de estado
   Application->OnHint = &OnHint;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Definición de acciones del Menu
///////////////////////////////////////////////////////////////////////////////////////////////////


// Manu->Archivos->->Salir
void __fastcall TVentanaPrincipal::MenuArchivosSalirClick(TObject *Sender)
{
   Close();        
}

void __fastcall TVentanaPrincipal::Usuario0Click(TObject *Sender)
{
   Manipulador_archivos  ma;
   Usuario = 0;
   Usuario0->Checked = true;
   Usuario1->Checked = false;
   Usuario2->Checked = false;
   ma.Copia_archivo(SOLICITUDINVESTIGADOR, SOLICITUDDATOS);
}


void __fastcall TVentanaPrincipal::Usuario1Click(TObject *Sender)
{
   Manipulador_archivos  ma;
   Usuario = 1;
   Usuario0->Checked = false;
   Usuario1->Checked = true;
   Usuario2->Checked = false;
   ma.Copia_archivo(SOLICITUDPROFESOR, SOLICITUDDATOS);
}


void __fastcall TVentanaPrincipal::Usuario2Click(TObject *Sender)
{
   Manipulador_archivos  ma;
   Usuario = 2;
   Usuario0->Checked = false;
   Usuario1->Checked = false;
   Usuario2->Checked = true;
   ma.Copia_archivo(SOLICITUDESTUDIANTE, SOLICITUDDATOS);
}



// Edita la solicitud de datos del usuario 
void __fastcall TVentanaPrincipal::Userrequest1Click(TObject *Sender)
{
//////////////////////////////////////////////////////////////////////////// 
// #error Hay que poner un editor sensillo y no TEditorForm
//   TEditorForm *editor = new TEditorForm(this);
//   if (editor) {
//      editor->Abrir_archivo(SOLICITUDDATOS, false);
//   }
//////////////////////////////////////////////////////////////////////////// 
}

// Configura la direccion de correo del usuario
void __fastcall TVentanaPrincipal::ConfiguserEmail1Click(TObject *Sender)
{
   try {
      AnsiString email;
      TRegistry &regkey = * new TRegistry();
      bool keygood = regkey.OpenKey(CLAVE_REGISTRO,false);
      if (keygood) email = regkey.ReadString(VPTXT02);
      if (InputQuery(VPTXT03,VPTXT02, email)) {
         TRegistry &regkey = * new TRegistry();
         bool keygood = regkey.OpenKey(CLAVE_REGISTRO,true);
         if (keygood) {
            regkey.WriteString(VPTXT02,email);
         }
      }
   } catch (...) {};
}


// Crea un nuevo proyecto
void __fastcall TVentanaPrincipal::IconoNewProyectClick(TObject *Sender)
{
   SaveDialog1->Title = "NEW PROYECT";
   if (SaveDialog1->Execute()) {
      TVentanaTrabajo *ventana = new TVentanaTrabajo(this);
      if (ventana) {
         ventana->Nombre_proyecto(SaveDialog1->FileName.c_str());
         ventana->Show();
      }
   }
}

// Cargar proyecto
void __fastcall TVentanaPrincipal::IconoLoadProyectClick(TObject *Sender)
{
   OpenDialog1->Title = "LOAD PROYECT";
   if (OpenDialog1->Execute()) {
      TVentanaTrabajo *ventana = new TVentanaTrabajo(this);
      if (ventana) {
         // Si existe lo carga en caso contrario lo crea
         if (!access(OpenDialog1->FileName.c_str(),06)) ventana->Carga_proyecto(OpenDialog1->FileName.c_str());
          else ventana->Nombre_proyecto(OpenDialog1->FileName.c_str());
         ventana->Show();
      }
   }
}

// Renombrar proyecto
void __fastcall TVentanaPrincipal::IconoRenombrarProyectoClick(TObject *Sender)
{
   OpenDialog1->Title = "RENAME PROYECT";
   if (OpenDialog1->Execute()) {
      TVentanaTrabajo *ventana = new TVentanaTrabajo(this);
      if (ventana) {
         AnsiString nombre = OpenDialog1->FileName;
         if (InputQuery(VPTXT07,VPTXT05, nombre)) {
            if (!access(nombre.c_str(),06)) {
               char xnom[MAXPATH];
               Manipulador_archivos ma;
               ma.Cambia_ext_path(nombre.c_str(), "pry", xnom);
               ma.Renombra_archivo(OpenDialog1->FileName.c_str(),xnom);
/////////////////////////////////////////////////////
//#error preguntar si se renombra tambien exe y descripción
/////////////////////////////////////////////////////            
            }
         }   
      }      
   }
}

// Duplicar proyecto
void __fastcall TVentanaPrincipal::IconoDuplicarProyectoClick(TObject *Sender)
{
   OpenDialog1->Title = "DUPLICATE PROYECT";
   if (OpenDialog1->Execute()) {
      TVentanaTrabajo *ventana = new TVentanaTrabajo(this);
      if (ventana) {
         AnsiString nombre = OpenDialog1->FileName;
         if (InputQuery(VPTXT06,VPTXT05, nombre)) {
            if (!access(nombre.c_str(),06)) {
               char xnom[MAXPATH];
               Manipulador_archivos ma;
               ma.Cambia_ext_path(nombre.c_str(), "pry", xnom);
               ma.Copia_archivo(OpenDialog1->FileName.c_str(),xnom);
            }
         }
      }
   }
}

// Borrar proyecto
void __fastcall TVentanaPrincipal::IconoBorrarProyectoClick(TObject *Sender)
{
   OpenDialog1->Title = "DELETE PROYECT";
   if (OpenDialog1->Execute()) {
      TVentanaTrabajo *ventana = new TVentanaTrabajo(this);
      if (ventana) {
         if (!access(OpenDialog1->FileName.c_str(),06)) {
            Manipulador_archivos ma;
            ma.Remueve_archivo(OpenDialog1->FileName.c_str(),0);
/////////////////////////////////////////////////////
//#error preguntar si se borra tambien exe y descripción
/////////////////////////////////////////////////////            
         }
      }
   }
}


// Ejecuta archivo del proyecto existente
void __fastcall TVentanaPrincipal::IconoEjecutaEXEClick(TObject *Sender)
{
   // Selecciona el archivo a ejecutar
   if (OpenDialog2->Execute()) {
      // Ejecuta el archivo seleccionado
      system(OpenDialog2->FileName.c_str());
   }     
}



// Manu->Ayuda->Ayuda General ...
void __fastcall TVentanaPrincipal::General1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(VPTXT04,AYUDAINTERFAZ);
      Ayuda->Show();
   }
}


// Manu->Ayuda->WWW del Laboratorio
void __fastcall TVentanaPrincipal::LaboratoriodeDinmicanoLinealUNAM1Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros(DIRECCIONLDNL);
       vent->Show();
   }
}

// Manu->Ayuda->Acerca de ...
void __fastcall TVentanaPrincipal::Aboutof1Click(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}





