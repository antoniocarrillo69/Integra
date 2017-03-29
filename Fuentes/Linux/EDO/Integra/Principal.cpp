 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana Principal                                                                        //
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

#include <vcl.h>
#include <vcl\Registry.hpp>
#include <Printers.hpp>
#include "Ayuda.h"
#include "Acecade.h"
#include "ACX-WebBrowser.h"
#include "LMensaje.h"
#include "Controlador.hpp"
#include "VentanaVisualizacion.h"
#pragma hdrstop

#include "Principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVentanaPrincipal *VentanaPrincipal;
// Variables globales
const char *TRAYECTORIA_ARCHIVOS    = ".\\";
const char *TituloAplicacion        = "Integra Windows 1.0";
const char *VERSION                 = "Version: 1.0.2 b";
const char *DERECHOS_AUTOR          = "Copyright:  1997 - 2003";
const char *FECHA_DERECHOS_AUTOR    = "México, D.F. Otoño del 2003";
const char *REGISTRO_AUTOR          = "SEP-INDAUTOR: 167025";
const char *COMPANIA                = "Laboratorio de Dinámica no Lineal, UNAM, México D.F.";
const char *E_MAIL                  = "E-mail: dinamica@www.dynamics.unam.edu";
const char *WWW                     = "http://www.dynamics.unam.edu/integra";



void *Ventana_activa;
// Variable de control de tareas
int TAREA_POR_REALIZAR = 0;

// Variables locales
const char *VP_TXT01                = "Do you wish to end the program?";
const char *VP_TXT02                = "Load File ...";
const char *CLAVE_REGISTRO          = "Laboratorio de Dinamica no Lineal\\INTEGRA 1.0";


// Constructor de la aplicación
__fastcall TVentanaPrincipal::TVentanaPrincipal(TComponent* Owner) : TForm(Owner)
{
   Caption = TituloAplicacion;
   Application->Title = Caption;
   int top = 30, left = 30;

   try {
      TRegistry &regkey = * new TRegistry();
      bool keygood = regkey.OpenKey(CLAVE_REGISTRO,false);
      if (keygood) {
         top = regkey.ReadInteger("Top");
         left = regkey.ReadInteger("Left");
      }
   } catch (...) {};
   Top = top, Left = left;

   try {
      // Carga el icono de la aplicación
      Application->Icon->LoadFromFile("BIFURCA.ICO");
   } catch (...) {};
   
   // Tiempo maximo de muestra de Hits
   Application->HintHidePause = 10000;

   // Pantalla de presentación
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
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
      }
   } catch (...) {};

   CanClose = false;
   if (MessageBox(Handle,VP_TXT01,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
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
// Definición de acciones de los Iconos
///////////////////////////////////////////////////////////////////////////////////////////////////

// Abre una nueva ventana de trabajo de integra
void __fastcall TVentanaPrincipal::IconoVentanaIntegraClick(TObject *Sender)
{
   TVentanaTrabajo *vent = new TVentanaTrabajo(this);
   if (vent) {
       vent->Show();
   }
}


// Abre caja de dialogo para seleccionar el sistema activo
void __fastcall TVentanaPrincipal::IconoSistemasClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_SISTEMAS;       
}

// Abre caja de dialogo para cambiar los parametros del sistema activo
void __fastcall TVentanaPrincipal::IconoParametrosClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_PARAMETROS;       
}

// Cambia el tipo de ventana activa al de ejes en 2D
void __fastcall TVentanaPrincipal::IconoEjes2DClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_EJES_2D;       
}

// Abre caja de dialogo para cambiar las dimensiones de la ventana
void __fastcall TVentanaPrincipal::IconoDimensionVentanaClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_DIMENSIONES;       
}

// Abre caja de dialogo para cambiar al metodo numerico de integración activo
void __fastcall TVentanaPrincipal::IconoMetodosIntegracionClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_METODOSNUMERICOS;       
}

// Abre caja de dialogo para cambiar el escenario grafico
void __fastcall TVentanaPrincipal::IconoEscenarioGraficoClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_ESCENARIOGRAFICO;       
}

// Dibuja el campo vectorial
void __fastcall TVentanaPrincipal::IconoCampoVectorialClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_CAMPOVECTORIAL;       
}

// Abre caja de dialogo para cambiar la condición inicial
void __fastcall TVentanaPrincipal::IconoCondicionInicialClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_CONDICIONESINICIALES;       
}

// Integra en tiempo negativo
void __fastcall TVentanaPrincipal::IntegraTiempoNegativoClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_INTEGRATIEMPONEGATIVO;       
}

// Integra en tiempo positivo
void __fastcall TVentanaPrincipal::IntegraTiempoPositivoClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_INTEGRATIEMPOPOSITIVO;       
}

// Limpia la ventana de trabajo
void __fastcall TVentanaPrincipal::IconoLimpiaVentanaTrabajoClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_LIMPIARVENTANA;       
}

// Cambia el grafico de puntos a lineas y vice versa
void __fastcall TVentanaPrincipal::IconoGraficaPuntosLineasClick(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_GRFICAPUNTOSLINEAS;       
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Definición de acciones del Menu
///////////////////////////////////////////////////////////////////////////////////////////////////

// Menu->Archivos->Descripción del Proyecto
void __fastcall TVentanaPrincipal::DescripciondelProyecto1Click(TObject *Sender)
{
   TLMensajeForm *vent = new TLMensajeForm(this);
   if (vent) {
      char ARCHIVO[200], xarchivo[200];
      vent->Caption = "Proyect Description";
      Base_Metodos_Numericos *Ctrl = new Base_Metodos_Numericos;
      Ctrl->Inicializa();
      sprintf(ARCHIVO,"%s%02d",Ctrl->Retorna_nombre_proyecto(),0);
      int i = 0, lg = strlen(ARCHIVO) -1;
      while (ARCHIVO[lg] != '\\') {
         xarchivo[i] = ARCHIVO[lg];
         i++, lg --;
      }
      xarchivo[i] = 0;
      strrev(xarchivo);
      if (access(xarchivo,04) == 0) {
         vent->Editor->Lines->LoadFromFile(xarchivo);
      } else {
         if (access(ARCHIVO,04) == 0) {
            vent->Editor->Lines->LoadFromFile(ARCHIVO);
         } else vent->Editor->Lines->Append("No have description for this proyect.");
      }
      vent->ShowModal();
      delete vent;
      delete Ctrl;
   }
}


// Manu->Archivos->Edita archivo ASCII
void __fastcall TVentanaPrincipal::MenuArchivosEditaArchivosClick(TObject *Sender)
{
/*
   TEditorForm *editor = new TEditorForm(this);
   if (editor) {
      editor->Abrir_archivo("", false);
   }
*/   
}

// Manu->Archivos->Imprime archivo en formato BMP
void __fastcall TVentanaPrincipal::MenuArchivosPrintFileBMPFormatClick(TObject *Sender)
{
   OpenPictureDialog->Title = VP_TXT02;
   if (OpenPictureDialog->Execute()) {
      Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
      Bitmap->LoadFromFile(OpenPictureDialog->FileName);
      Printer()->BeginDoc();
      Printer()->Canvas->TextOut(100,210,Application->Title);
      Printer()->Canvas->StretchDraw(Rect(100,500,Printer()->PageWidth-100,Printer()->PageWidth+200),Bitmap);
      Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 300),COMPANIA);
      Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 390),E_MAIL);
      Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 480),WWW);
      Printer()->EndDoc();
      delete Bitmap;
   }
}

// Manu->Archivos-> Configura impresora
void __fastcall TVentanaPrincipal::MenuArchivosPrinterSetupClick(TObject *Sender)
{
   PrinterSetupDialog->Execute();        
}


// Manu->Archivos->->Salir
void __fastcall TVentanaPrincipal::MenuArchivosSalirClick(TObject *Sender)
{
   Close();        
}

// Manu->Ayuda->Ayuda General ...
void __fastcall TVentanaPrincipal::General1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,"C:\\Integra\\Help\\Integra.hlp");
      Ayuda->Show();
   }
}

// Manu->Ayuda->WWW del Laboratorio de inámica no Lineal
void __fastcall TVentanaPrincipal::LaboratoriodeDinmicanoLinealUNAM1Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros(WWW);
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








