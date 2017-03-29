//////////////////////////////////////////////////////////////////////////////////////////////
// Venatan de trabajo                                                                       //
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




//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\Registry.hpp>
#include <Printers.hpp>
#include <dos.h>
#include "Ayuda.h"
#include "Acecade.h"
#include "EnviarCorreo.h"
#pragma hdrstop

#include "VentanaVisualizacion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVentanaTrabajo *VentanaTrabajo;


// Indica si esta activo el borrar los fuentes generados
#define __BORRA_FUENTES__
// Indica si esta activo el enviar por correo los datos capturados por el usuario
#define __MANDA_CORREO__


// Variables globales
extern void *Ventana_activa;
extern char *COMPANIA;
extern char *E_MAIL;
extern const char *TituloAplicacion;
extern const char *CLAVE_REGISTRO;
extern const char *Errores_a_s[];

#define AYUDAINTERFAZ    "C:\\Integra\\Help\\Interfaz.hlp"
#define AYUDAFUNCIONES   "C:\\Integra\\Help\\Funciones.hlp"
#define SOLICITUDDATOS   "C:\\Integra\\Help\\Solicitud.txt"
#define ARCHIVOSOLICITUD "C:\\Integra\\Solitictud.txt" 
#define SEPARADOR        "C:\\Integra\\Help\\Separador.txt" 
#define DIRECCIONEMAIL   "dinamica@dinamica1.fciencias.unam.mx"


#ifdef _IDIOMA_ESPANOL_
   #define V_TXT01 "Do you wish to close this window?"
   #define V_TXT02 "Save as ..."
   #define V_TXT03 "Do you wish to save this proyect?"
   #define V_TXT04 "No Name"
   #define V_TXT05 "New System"
   #define V_TXT06 "Name:"
   #define V_TXT07 "Too many systems in the proyect"
   #define V_TXT08 "The name of the system already exists"
   #define V_TXT09 "Do yo delete the system?"
   #define V_TXT10 "Duplicate System"
   #define V_TXT11 "New Name:"
   #define V_TXT12 "Rename system"
   #define V_TXT13 "Proyect whit same name"

   #define V_TXT14 "Check Proyect:"  
   #define V_TXT15 "System OK"
   #define V_TXT16 "There are not defined systems"
   #define V_TXT17 "The system has not equations"
   #define V_TXT18 ""
   #define V_TXT19 "There must exist at least one diferential equations"
   #define V_TXT20 "The maximun number of equations was exceeded"
   #define V_TXT21 "The maximun number of parameters was exceeded"
   #define V_TXT22 "There are duplicated expresions"
   #define V_TXT23 "Possibly there was a error in the expression analysis"
   #define V_TXT24 "C++ file was not generated"
   #define V_TXT25 "C++ file was generated correctly"
   #define V_TXT26 "E-mail"
   #define V_TXT27 "Request user in:" 

   
#else
   #define V_TXT01 "Do you wish to close this window?"
   #define V_TXT02 "Save as ..."
   #define V_TXT03 "Do you wish to save this proyect?"
   #define V_TXT04 "No Name"
   #define V_TXT05 "New System"
   #define V_TXT06 "Name:"
   #define V_TXT07 "Too many systems in the proyect"
   #define V_TXT08 "The name of the system already exists"
   #define V_TXT09 "Do yo delete the system?"
   #define V_TXT10 "Duplicate System"
   #define V_TXT11 "New Name:"
   #define V_TXT12 "Rename system"
   #define V_TXT13 "Proyect whit same name"
   #define V_TXT14 "Check Proyect:"  
   #define V_TXT15 "System OK"
   #define V_TXT16 "There are not defined systems"
   #define V_TXT17 "The system has not equations"
   #define V_TXT18 ""
   #define V_TXT19 "There must exist at least one diferential equations"
   #define V_TXT20 "The maximun number of equations was exceeded"
   #define V_TXT21 "The maximun number of parameters was exceeded"
   #define V_TXT22 "There are duplicated expresions"
   #define V_TXT23 "Possibly there was a error in the expression analysis"
   #define V_TXT24 "C++ file was not generated"
   #define V_TXT25 "C++ file was generated correctly"
   #define V_TXT26 "E-mail"
   #define V_TXT27 "Request user in:" 
#endif

//---------------------------------------------------------------------------


// Constructor de la clase
__fastcall TVentanaTrabajo::TVentanaTrabajo(TComponent* Owner) : TForm(Owner)
{
   Ctrl = new Ctrl_estructura;
   if (!Ctrl) Free();
   // Controla si esta activo algun calculo
   Sw_calculo_en_proceso = false;
   Sw_cerrar_ventana = false;
   Sistema_activo = 0;
}


// Al activar la ventana
void __fastcall TVentanaTrabajo::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
}

// Al solicitar cerrar la ventana
void __fastcall TVentanaTrabajo::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;
   if (MessageBox(Handle,V_TXT01,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
       Sw_cerrar_ventana = true;
   }
}

// Al no ser la ventana la activa
void __fastcall TVentanaTrabajo::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
}

// OnHint
void  __fastcall TVentanaTrabajo::OnHint(TObject *Sender)
{
   BarraEstados->SimpleText = Application->Hint;
}

// Revisa cada segundo si se ha solicitado el cierre de la ventana
void __fastcall TVentanaTrabajo::TimerTimer(TObject *Sender)
{
   // Almacena la ventana activa
   if (Focused()) {
      Ventana_activa = this;
   }   
   // Controla que no este calculando para cerrar la ventana
   if (Sw_cerrar_ventana && !Sw_calculo_en_proceso) {
      Timer->Enabled = false;
      // Revisa si sera grabado el proyecto
      if (Ctrl->Proyecto_modificado()) {
         if (MessageBox(Handle,V_TXT03,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
             Ctrl->Graba_proyecto();
         }
      }
      delete Ctrl;
      // Libera la ventana activa
      Ventana_activa = NULL;
      Free();
   }
}


//////////////////////////////////////////////////////////////////////////////////////////////
// Opciones del Menu
//////////////////////////////////////////////////////////////////////////////////////////////

// Cerrar ventana de trabajo
void __fastcall TVentanaTrabajo::MenuArchivosCerrarClick(TObject *Sender)
{
   Close();
}


// Grabar como ...
void __fastcall TVentanaTrabajo::SaveAs1Click(TObject *Sender)
{
   if (SaveDialog1->Execute()) {
      Nombre_proyecto(SaveDialog1->FileName.c_str());
      Ctrl->Graba_proyecto();
   }
}

// imprime el proyecto
void __fastcall TVentanaTrabajo::Print2Click(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   // Revisa si sera grabado el proyecto
   if (Ctrl->Proyecto_modificado()) {
      if (MessageBox(Handle,V_TXT03,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Graba_proyecto();
      }
   }
   Ctrl->Imprime_proyecto();
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,"ARCH_PRN.$$$");
      Ayuda->Show();
   }
   unlink("ARCH_PRN.$$$");
}




// Ventana de ayuda
void __fastcall TVentanaTrabajo::Ventana1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,AYUDAINTERFAZ);
      Ayuda->Show();
   }
}

// Ventana de ayuda
void __fastcall TVentanaTrabajo::Funciones1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,AYUDAFUNCIONES);
      Ayuda->Show();
   }
}


// Acerca de ...
void __fastcall TVentanaTrabajo::About1Click(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}




///////////////////////////////////////////////////////////////////////////////////////////////
// Iconos de Acción
///////////////////////////////////////////////////////////////////////////////////////////////

// Icono de Nuevo sistema
void __fastcall TVentanaTrabajo::IconoNuevoSistemaClick(TObject *Sender)
{
   if (Ctrl->Numero_sistemas()) Actualiza_sistema(Sistema_activo);
   AnsiString sist = V_TXT04;
   if (InputQuery(V_TXT05,V_TXT06, sist)) {
      char xnombre[400];
      memccpy(xnombre,sist.c_str(),0,LG_MAX_NOM_SISTEMA);
      int st = Ctrl->Nuevo_sistema(xnombre);
      if (!st)  {
         ListaSistemas->Items->Add(sist);
         EditorEcuaciones->Lines->Clear();
         EditorDescripcion->Lines->Clear();
         ListaSistemas->ItemIndex = Ctrl->Numero_sistemas() - 1;
      }
      if (st == 1) ShowMessage(V_TXT07);
      if (st == 2) ShowMessage(V_TXT08);
   }
   Sistema_activo = Ctrl->Numero_sistemas()- 1;
   EditorEcuaciones->ReadOnly = false;
   EditorDescripcion->ReadOnly = false;
}

// Icono de borrar sistema activo
void __fastcall TVentanaTrabajo::IconoBorraSistemaClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   if (MessageBox(Handle,V_TXT09,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      Ctrl->Borra_sistema(Sistema_activo);
      Ctrl->Actualiza_estructura_proyecto();
      ListaSistemas->Items->Delete(Sistema_activo);
      ListaSistemas->ItemIndex = 0;
      Sistema_activo = 0;
      Carga_sistema(Sistema_activo);
   }
}

// Icono que duplica el sistema activo
void __fastcall TVentanaTrabajo::IconoDuplicaSistemaClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   AnsiString nombre = V_TXT04;
   if (InputQuery(V_TXT10,V_TXT11, nombre)) {
      char xnombre[400];
      memccpy(xnombre,nombre.c_str(),0,LG_MAX_NOM_SISTEMA);
      if (Ctrl->Nuevo_sistema(xnombre)) return;
      if (!Ctrl->Duplica_sistema(Sistema_activo, xnombre, Ctrl->Numero_sistemas()-1)) {
         ListaSistemas->Items->Add(nombre);
         ListaSistemas->ItemIndex = Ctrl->Numero_sistemas() - 1;
         Sistema_activo = Ctrl->Numero_sistemas() - 1;
         Carga_sistema(Sistema_activo);
      }
   }
}

//  Icono que Renombra el sistema activo
void __fastcall TVentanaTrabajo::IconoRenombraSistemaClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   AnsiString nombre = Ctrl->Retorna_nombre_sistema(Sistema_activo);
   if (InputQuery(V_TXT12,V_TXT11, nombre)) {
      char xnombre[400];
      memccpy(xnombre,nombre.c_str(),0,LG_MAX_NOM_SISTEMA);
      if (!Ctrl->Valida_nombre_sistema(xnombre)) {
         ShowMessage(V_TXT13);
         return;
      }
      Ctrl->Cambia_nombre_sistema(Sistema_activo, xnombre);
      ListaSistemas->Items->Strings[Sistema_activo] = nombre;
   }
}

// Icono Imprime Sistema Activo
void __fastcall TVentanaTrabajo::IconoImprimeSistemaClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   // Revisa si sera grabado el proyecto
   if (Ctrl->Proyecto_modificado()) {
      if (MessageBox(Handle,V_TXT03,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Graba_proyecto();
      }
   }
   Ctrl->Imprime_sistema(Sistema_activo);
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,"ARCH_PRN.$$$");
      Ayuda->Show();
   }
   unlink("ARCH_PRN.$$$");
}

// Genera archivo CPP y HPP y envia por correo la solicitud completa de generación del EXE
void __fastcall TVentanaTrabajo::MakeandSendEmail1Click(TObject *Sender)
{
   if (!Genera_CPP()) {
      // Envia el archivo por correo
      TFormaEnviarCorreo *vent = new TFormaEnviarCorreo(this);
      if (vent) {
          AnsiString email;
          try {
             TRegistry &regkey = * new TRegistry();
             bool keygood = regkey.OpenKey(CLAVE_REGISTRO,false);
             if (keygood) email = regkey.ReadString(V_TXT26);
          } catch (...) {};
          vent->Parametros(email.c_str(),DIRECCIONEMAIL,Application->Title.c_str());
          // Fija el numero de archivos a enviar
          vent->Fija_numero_archivos(1);
          vent->Asigna_nombre_archivo(1,ARCHIVOSOLICITUD);
          vent->Editor->Lines->LoadFromFile(SOLICITUDDATOS);
          // Muestra la ventana del mensaje
          vent->ShowModal();
          delete vent;
      }   
      unlink(ArchivoCPP);
      unlink(ArchivoHPP);
   }
}

// Genera archivo CPP y HPP y muestra la solicitud completa de generación del EXE
void __fastcall TVentanaTrabajo::MakeandSave1Click(TObject *Sender)
{
   if (!Genera_CPP()) {
      // Ventana con el archivo de solicitud conjuntamente con el código fuente
      TAyudaForm *TODO = new TAyudaForm(this);
      if (TODO) {
         TODO->Abrir_archivo(TituloAplicacion,ARCHIVOSOLICITUD);
         TODO->Show();
      }
      unlink(ArchivoCPP);
      unlink(ArchivoHPP);
   }
}

// Genera archivo CPP y HPP y ejecuta el archivo EXE
void __fastcall TVentanaTrabajo::MakeandExecute1Click(TObject *Sender)
{
   if (!Genera_CPP()) {
      unlink(ArchivoCPP);
      unlink(ArchivoHPP);
   }
}

// Genera archivo CPP y HPP y muestra el código en C++ generado
void __fastcall TVentanaTrabajo::MakeOnlyCodeC1Click(TObject *Sender)
{
   if (!Genera_CPP()) {
      // Ventana del código CPP
      TAyudaForm *CPP = new TAyudaForm(this);
      if (CPP) {
         CPP->Abrir_archivo(TituloAplicacion,ArchivoCPP);
         CPP->Show();
      }
      // Ventana del código HPP
      TAyudaForm *HPP = new TAyudaForm(this);
      if (HPP) {
         HPP->Abrir_archivo(TituloAplicacion,ArchivoHPP);
         HPP->Show();
      }
   }
}



// Icono de grabar proyecto
void __fastcall TVentanaTrabajo::IconoGrabarProyectoClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   // Revisa si sera grabado el proyecto
   Ctrl->Graba_proyecto();
   Ctrl->Proyecto_modificado(false);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Control de lista de sistemas
///////////////////////////////////////////////////////////////////////////////////////////////


void __fastcall TVentanaTrabajo::ListaSistemasClick(TObject *Sender)
{
   if (!Ctrl->Numero_sistemas()) return;
   Actualiza_sistema(Sistema_activo);
   for (int i = 0; i < ListaSistemas->Items->Count; i++) {
       if (ListaSistemas->Selected[i]) Sistema_activo = i;
   }
   Carga_sistema(Sistema_activo);
}


// Actuzliza el contenido del sistema
void TVentanaTrabajo::Actualiza_sistema(const int sis)
{
   int i;
   Revisa_modificacion_sistema(sis);
   // Borra las ecuaciones del sistema dado
   Ctrl->Borra_ecuaciones(sis);
   // Borra la descripción del sistema dado
   Ctrl->Borra_descripcion(sis);
   // Borra la descripción del proyecto
   Ctrl->Borra_descripcion_proyecto();
   // Borra el codigo en C
   Ctrl->Borra_codigo_en_C();
   // Actualiza la descripcion del proyecto
   if (EditorDescripcionProyecto->Lines->Count) {
      if (!Ctrl->Crea_espacio_descripcion_proyecto(EditorDescripcionProyecto->Lines->Count)) return;
      for (i = 0; i < EditorDescripcionProyecto->Lines->Count; i++) {
         Ctrl->Almacena_descripcion_proyecto(EditorDescripcionProyecto->Lines->Strings[i].c_str());
      }
   }
   // Actualiza la descripcion del sistema
   if (EditorDescripcion->Lines->Count) {
      if (!Ctrl->Crea_espacio_descripcion_sistema(sis,EditorDescripcion->Lines->Count)) return;
      for (i = 0; i < EditorDescripcion->Lines->Count; i++) {
         Ctrl->Almacena_descripcion_sistema(sis,EditorDescripcion->Lines->Strings[i].c_str());
      }
   }
   // Actualiza las ecuaciones del sistema
   if (EditorEcuaciones->Lines->Count) {
      if (!Ctrl->Crea_espacio_ecuaciones_sistema(sis,EditorEcuaciones->Lines->Count)) return;
      for (i = 0; i < EditorEcuaciones->Lines->Count; i++) {
         Ctrl->Almacena_ecuaciones_sistema(sis,EditorEcuaciones->Lines->Strings[i].c_str());
      }
   }
   // Actualiza el codigo en C ++
   if (EditorCodigoC->Lines->Count) {
      if (!Ctrl->Crea_espacio_codigo_en_C(EditorCodigoC->Lines->Count)) return;
      for (i = 0; i < EditorCodigoC->Lines->Count; i++) {
         Ctrl->Almacena_codigo_en_C(EditorCodigoC->Lines->Strings[i].c_str());
      }
   }
}

// Revisa si se modificarón los datos del proyecto
void TVentanaTrabajo::Revisa_modificacion_sistema(const int sis)
{
   if (!Ctrl->Numero_sistemas()) return;
   int i;
   // Revisa si se modifico la descripción del proyecto
   if (EditorDescripcionProyecto->Lines->Count == Ctrl->Numero_lineas_descripcion_proyecto()) {
      for (i = 0; i < EditorDescripcionProyecto->Lines->Count; i++) {
         AnsiString txt1(EditorDescripcionProyecto->Lines->Strings[i]);
         if (strcmp(txt1.c_str(),Ctrl->Retorna_cadena_descripcion_proyecto(i))) Ctrl->Proyecto_modificado(true);
      }
   } else Ctrl->Proyecto_modificado(true);

   // Revisa si se modifico la descripción del sistema
   if (EditorDescripcion->Lines->Count == Ctrl->Numero_lineas_descripcion_sistema(sis)) {
      for (i = 0; i < EditorDescripcion->Lines->Count; i++) {
         AnsiString txt1(EditorDescripcion->Lines->Strings[i]);
         if (strcmp(txt1.c_str(),Ctrl->Retorna_cadena_descripcion_sistema(sis,i))) Ctrl->Proyecto_modificado(true);
      }
   } else Ctrl->Proyecto_modificado(true);

   // Revisa si se modifico las ecuaciones del sistema
   if (EditorEcuaciones->Lines->Count == Ctrl->Numero_lineas_ecuaciones_sistema(sis)) {
      for (i = 0; i < EditorEcuaciones->Lines->Count; i++) {
         AnsiString txt1(EditorEcuaciones->Lines->Strings[i]);
         if (strcmp(txt1.c_str(),Ctrl->Retorna_cadena_ecuaciones_sistema(sis,i))) Ctrl->Proyecto_modificado(true);
      }
   } else Ctrl->Proyecto_modificado(true);

   // Revisa si se modifico el codigo en C++
   if (EditorCodigoC->Lines->Count == Ctrl->Numero_lineas_codigo_en_C()) {
      for (i = 0; i < EditorCodigoC->Lines->Count; i++) {
         AnsiString txt1(EditorCodigoC->Lines->Strings[i]);
         if (strcmp(txt1.c_str(),Ctrl->Retorna_cadena_codigo_en_C(i))) Ctrl->Proyecto_modificado(true);
      }
   } else Ctrl->Proyecto_modificado(true);
}


// Carga el contenido del sistema
void TVentanaTrabajo::Carga_sistema(const int sis)
{
   int i;
   // Carga la descripcion del proyecto
   EditorDescripcionProyecto->Lines->Clear();
   for (i = 0; i < Ctrl->Numero_lineas_descripcion_proyecto(); i++) {
      EditorDescripcionProyecto->Lines->Add(Ctrl->Retorna_cadena_descripcion_proyecto(i));
   }
   // Carga la descripcion del sistema
   EditorDescripcion->Lines->Clear();
   for (i = 0; i < Ctrl->Numero_lineas_descripcion_sistema(sis); i++) {
      EditorDescripcion->Lines->Add(Ctrl->Retorna_cadena_descripcion_sistema(sis,i));
   }
   // Carga las ecuaciones del sistema
   EditorEcuaciones->Lines->Clear();
   for (i = 0; i < Ctrl->Numero_lineas_ecuaciones_sistema(sis); i++) {
      EditorEcuaciones->Lines->Add(Ctrl->Retorna_cadena_ecuaciones_sistema(sis,i));
   }
   // Carga el codigo en C
   EditorCodigoC->Lines->Clear();
   for (i = 0; i < Ctrl->Numero_lineas_codigo_en_C(); i++) {
      EditorCodigoC->Lines->Add(Ctrl->Retorna_cadena_codigo_en_C(i));
   }
}

// Carga el proyecto indicado por NOMBRE
void TVentanaTrabajo::Carga_proyecto(const char *arch)
{
   ListaSistemas->Items->Clear();
   Ctrl->Lee_proyecto(arch);
   for (int i = 0; i < Ctrl->Numero_sistemas(); i++) {
      ListaSistemas->Items->Add(Ctrl->Retorna_nombre_sistema(i));
   }
   ListaSistemas->ItemIndex = 0;
   Sistema_activo = 0;
   Carga_sistema(Sistema_activo);
   Actualiza_titulo_ventana();
   EditorEcuaciones->ReadOnly = false;
   EditorDescripcion->ReadOnly = false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//#error
// Permitir copiar un sistema al buffer de trabajo
// Permitir pegar del bufer de trabajo un sistema
//////////////////////////////////////////////////////////////////////////////////////////////////

// Deshace los cambio
void __fastcall TVentanaTrabajo::Undo1Click(TObject *Sender)
{
   if (VentanaActiva == 1) SendMessage(EditorEcuaciones->Handle,WM_UNDO,0,0);
   if (VentanaActiva == 2) SendMessage(EditorDescripcion->Handle,WM_UNDO,0,0);
   if (VentanaActiva == 3) SendMessage(EditorDescripcionProyecto->Handle,WM_UNDO,0,0);
   if (VentanaActiva == 4) SendMessage(EditorCodigoC->Handle,WM_UNDO,0,0);
}

// Corta el texto marcado
void __fastcall TVentanaTrabajo::Cut1Click(TObject *Sender)
{
   if (VentanaActiva == 1) EditorEcuaciones->CutToClipboard();
   if (VentanaActiva == 2) EditorDescripcion->CutToClipboard();
   if (VentanaActiva == 3) EditorDescripcionProyecto->CutToClipboard();
   if (VentanaActiva == 4) EditorCodigoC->CutToClipboard();
}

// Copia el texto marcado
void __fastcall TVentanaTrabajo::Copy1Click(TObject *Sender)
{
   if (VentanaActiva == 1) EditorEcuaciones->CopyToClipboard();
   if (VentanaActiva == 2) EditorDescripcion->CopyToClipboard();
   if (VentanaActiva == 3) EditorDescripcionProyecto->CopyToClipboard();
   if (VentanaActiva == 4) EditorCodigoC->CopyToClipboard();
}

// Borra el texto marcado
void __fastcall TVentanaTrabajo::Delete2Click(TObject *Sender)
{
   if (VentanaActiva == 1) EditorEcuaciones->CutToClipboard();
   if (VentanaActiva == 2) EditorDescripcion->CutToClipboard();
   if (VentanaActiva == 3) EditorDescripcionProyecto->CutToClipboard();
   if (VentanaActiva == 4) EditorCodigoC->CutToClipboard();
}

// Pega el texto copiado
void __fastcall TVentanaTrabajo::Paste1Click(TObject *Sender)
{
   if (VentanaActiva == 1) EditorEcuaciones->PasteFromClipboard();      
   if (VentanaActiva == 2) EditorDescripcion->PasteFromClipboard();      
   if (VentanaActiva == 3) EditorDescripcionProyecto->PasteFromClipboard();      
   if (VentanaActiva == 4) EditorCodigoC->PasteFromClipboard();      
}

// Selecciona todo el texto
void __fastcall TVentanaTrabajo::Selectall1Click(TObject *Sender)
{
   if (VentanaActiva == 1) EditorEcuaciones->SelectAll();        
   if (VentanaActiva == 2) EditorDescripcion->SelectAll();        
   if (VentanaActiva == 3) EditorDescripcionProyecto->SelectAll();        
   if (VentanaActiva == 4) EditorCodigoC->SelectAll();        
}

// Copia todo el texto
void __fastcall TVentanaTrabajo::CopyAll1Click(TObject *Sender)
{
   if (VentanaActiva == 1) {
       EditorEcuaciones->SelectAll();        
       EditorEcuaciones->CopyToClipboard();        
   }
   if (VentanaActiva == 2) {
       EditorDescripcion->SelectAll();        
       EditorDescripcion->CopyToClipboard();        
   }
   if (VentanaActiva == 3) {
       EditorDescripcionProyecto->SelectAll();        
       EditorDescripcionProyecto->CopyToClipboard();        
   }
   if (VentanaActiva == 4) {
       EditorCodigoC->SelectAll();        
       EditorCodigoC->CopyToClipboard();        
   }
}

// Activa la ventana de edición de Sistema de Ecuaciones
void __fastcall TVentanaTrabajo::BarraEdicionEnter(TObject *Sender)
{
   VentanaActiva = 1;        
}

// Activa la ventana de edición de la Descripción del sistema
void __fastcall TVentanaTrabajo::EditorDescripcionEnter(TObject *Sender)
{
   VentanaActiva = 2;        
}

// Activa la ventana de edición de la Descripción del Proyecto
void __fastcall TVentanaTrabajo::EditorDescripcionProyectoEnter(TObject *Sender)
{
   VentanaActiva = 3;        
}

// Activa la ventana de edición del Codigo en C
void __fastcall TVentanaTrabajo::EditorCodigoCEnter(TObject *Sender)
{
   VentanaActiva = 4;        
}



// Genera Archivo C++
int TVentanaTrabajo::Genera_CPP(void)
{
   char xcad[MAXPATH], arch1[MAXPATH], arch2[MAXPATH];
   int err, i, lg, st = 0;
   if (!Ctrl->Numero_sistemas()) return -1;
   Actualiza_sistema(Sistema_activo);
   // Revisa si sera grabado el proyecto
   if (Ctrl->Proyecto_modificado()) {
      if (MessageBox(Handle,V_TXT03,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Graba_proyecto();
      }
   }
   // Asigna los nombres de archivos CPP y HPP
   strcpy(xcad,Ctrl->Retorna_nombre_proyecto());
   lg = strlen(xcad);
   // Archivo CPP
   xcad[lg-3] = 'c';
   xcad[lg-2] = 'p';
   xcad[lg-1] = 'p';
   strcpy(ArchivoCPP, xcad);
    // Archivo HPP
   xcad[lg-3] = 'h';
   strcpy(ArchivoHPP, xcad);

   
   // Abre y muestra la ventana de estado
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,"");
      Ayuda->EditorAyuda->Lines->Add(V_TXT14);  
      Ayuda->EditorAyuda->Lines->Add(" ");  
      // Revisa si estan correctos los sistemas
      for (i = 0; i < Ctrl->Numero_sistemas(); i++) {
         strcpy(xcad,"   ");
         strcat(xcad,Ctrl->Retorna_nombre_sistema(i));
         Ayuda->EditorAyuda->Lines->Add(xcad);
         strcpy(xcad,"      ");
         err = Ctrl->Revisa_sistema(i);
         if (err) st = 1;
         switch(err) {
            case 0:
               strcat(xcad,V_TXT15);
               break;
            case 1:
               strcat(xcad,V_TXT16);
               break;
            case 2:
               strcat(xcad,V_TXT17);
               break;
            case 3:
// No asignado            
//               strcat(xcad,V_TXT18);
               break;
            case 4:
               strcat(xcad,V_TXT19);
               break;
            case 5:
               strcat(xcad,V_TXT20);
               break;
            case 6:
               strcat(xcad,V_TXT21);
               break;
            case 7:  
               strcat(xcad,V_TXT22);
               break;
            case 8:  
               strcat(xcad,V_TXT23);
               break;
            default:
               strcat(xcad,Errores_a_s[err-9]);
         }
         Ayuda->EditorAyuda->Lines->Add(xcad);
         Ayuda->EditorAyuda->Lines->Add(" ");
      }
      Ayuda->EditorAyuda->Lines->Add(" ");

      // Muestra el estado del proyecto
      Ayuda->Show();
      // Si no hay errores genera los archivos
      if (!st) {
         // Genera archivos CPP, HPP, D00,...,D99
         Ctrl->Generar();
         Ctrl->Imprime_proyecto();
         Manipulador_archivos  ma;
         ma.Copia_archivo(SOLICITUDDATOS, ARCHIVOSOLICITUD);
         ma.Concatena_archivo(SEPARADOR, ARCHIVOSOLICITUD);
         ma.Concatena_archivo("ARCH_PRN.$$$", ARCHIVOSOLICITUD);
         ma.Concatena_archivo(SEPARADOR, ARCHIVOSOLICITUD);
         ma.Concatena_archivo(ArchivoCPP, ARCHIVOSOLICITUD);
         ma.Concatena_archivo(SEPARADOR, ARCHIVOSOLICITUD);
         ma.Concatena_archivo(ArchivoHPP, ARCHIVOSOLICITUD);
         ma.Concatena_archivo(SEPARADOR, ARCHIVOSOLICITUD);
         // Borra el archivo del reporte del proyecto
         unlink("ARCH_PRN.$$$");
         Ayuda->EditorAyuda->Lines->Add(V_TXT27);
         Ayuda->EditorAyuda->Lines->Add(ARCHIVOSOLICITUD);
         Ayuda->EditorAyuda->Lines->Add("");
         Ayuda->EditorAyuda->Lines->Add(V_TXT25);
      } else Ayuda->EditorAyuda->Lines->Add(V_TXT24);
   }   
   return st;
}


// Ejecuta archivo del proyecto existente
void __fastcall TVentanaTrabajo::Exist1Click(TObject *Sender)
{
   // Selecciona el archivo a ejecutar
   if (OpenDialog2->Execute()) {
      // Ejecuta el archivo seleccionado
      system(OpenDialog2->FileName.c_str());
   }     
}

