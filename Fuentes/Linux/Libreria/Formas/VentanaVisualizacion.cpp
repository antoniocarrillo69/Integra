 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana de Visualización                                                                 //
 // Revisión: 8 de Noviembre del 2003                                                        //
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
#include <Printers.hpp>
#include <dos.h>
#include <io.h>
#include "Ayuda.h"
#include "Acecade.h"
#include "VDSistemas.h"
#include "VDParametros.h"
#include "VDCondicionInicial.h"
#include "VDIncrementoPasoCursor.h"
#include "VDPasoCursor.h"
#include "VDDimensiones.h"
#include "VDCampoVectorial.h"
#include "VDMetodosIntegracion.h"
#include "VDMetodosIntegracion.h"
#include "VDEscenarios.h"
#include "VDColoresSistema.h"
#include "VDEquilibrios.h"
#include "LMensaje.h"
#include "Editor.h"
#include "VDPeriodoTrayectoriaCerrada.h"
#include "Evaexpc.hpp"
#pragma hdrstop


#include "VentanaVisualizacion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVentanaTrabajo *VentanaTrabajo;


// Variables globales
extern const char *TituloAplicacion;
extern void *Ventana_activa;
extern char *COMPANIA;
extern char *E_MAIL;
extern char *WWW;
// Variable de control de tareas
extern int   TAREA_POR_REALIZAR;

// Variables locales
const char *V_TXT01 = "Do you wish to close this window?";
const char *V_TXT02 = "Save as ...";
const char *V_TXT03 = "Para rotar los ejes coordenados use las flechas horizontales y verticales, para terminar use la tecla [Esc]";
const char *V_TXT04 = "¿Desea ver el archivo de iteraciones?";
const char *V_TXT05   = "Do you wish to zoom?";

// Definicion de acciones 
#define LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL                  1
#define LIMPIA_VENTANA_CONSERVANDO_CONDICION_INICIAL                    2
#define INTEGRAR_TIEMPO_POSITIVO                                        3
#define INTEGRAR_TIEMPO_NEGATIVO                                        4
#define PARAMETROS_ORIGINALES                                           6
#define PARAMETROS_LIMPIAR_USADOS_VARIABLES                             7
#define CAMPO_VECTORIAL                                                 8
#define CAMPO_DIRECCIONAL                                               9
#define MAPEO_PERIODO_TIEMPO_POSITIVO                                   10
#define MAPEO_PERIODO_TIEMPO_NEGATIVO                                   11
#define PERIODO_TRAYECTORIA_CERRADA_TIEMPO_POSITIVO                     12
#define PERIODO_TRAYECTORIA_CERRADA_TIEMPO_NEGATIVO                     13



#define AYUDAINTEGRA                     "C:\\Integra\\Help\\Integra.hlp"
#define AYUDAFUNCIONES                   "C:\\Integra\\Help\\Funciones.hlp"
#define ARCHIVO_CONFIGURACION            "C:\\TMP_CFG"
#define ARCHIVO_CONFIGURACION_ORIGINAL   "C:\\TMP_CFGORG"
#define ARCHIVO_TEMPORAL                 "C:\\TMP_WIN"
#define ARCHIVO_IMPRESION                "PRN_IMG.BMP"
#define ARCHIVO_IMPRESION_TMP            "ARCH_PRN.$$$"

#ifdef _IDIOMA_ESPANOL_
   #define VVTXT01 "This system have no parameters"
   #define VVTXT02 "No Ver &Nombres de Ejes"
   #define VVTXT03 "Ver &Nombres de Ejes"
   #define VVTXT04 "No Ver &Condiciones Iniciales"
   #define VVTXT05 "Ver &Condiciones Iniciales"
   #define VVTXT06 "No Activo"
   #define VVTXT07 "Tiempo"
   #define VVTXT08 "Graficar Usando Lineas"
   #define VVTXT09 "Graficar Usando Puntos"
   #define VVTXT10 "Save as ..."
   #define VVTXT11 "Load ..."
   #define VVTXT12 "Repor of State"
   #define VVTXT13 "Save &Integrations ..."
   #define VVTXT14 "No Save &Integrations ..."
   #define VVTXT15 "No se calcula en escenarios con el tiempo como una componente"
   #define VVTXT16 "System Description"
   #define VVTXT17 "No have description for this system."
   #define VVTXT18 "El cálculo de ceroclina es para sistemas de 2 ecuaciones"
   #define VVTXT19 "Calculo de Isoclina"
   #define VVTXT20 "Valor a calcular:"
   #define VVTXT21 "El cálculo de isoclinas es para sistemas de 2 ecuaciones"
   #define VVTXT22 "Puntos a graficar en la Función auxiliar"
   #define VVTXT23 "Number of Points:"
   #define VVTXT24 "Función auxiliar a calcular"
   #define VVTXT25 "Función:"
   #define VVTXT26 "Escenarios a gráficar simultaneamente"
   #define VVTXT27 "Escenarios:"
   #define VVTXT28 "Equilibrios:"
   #define VVTXT29 "Period Map:"
   #define VVTXT30 "Repeat:"
   
#else 
   #define VVTXT01 "The System have no Parameters"
   #define VVTXT02 "No See &Name of Axis"
   #define VVTXT03 "See &Name of Axis"
   #define VVTXT04 "No See &Initial Conditions"
   #define VVTXT05 "See &Initial Conditions"
   #define VVTXT06 "No Active"
   #define VVTXT07 "Time"
   #define VVTXT08 "&Draw use lines"
   #define VVTXT09 "&Draw use dots"
   #define VVTXT10 "Save as ..."
   #define VVTXT11 "Load ..."
   #define VVTXT12 "Repor of State"
   #define VVTXT13 "Save &Integrations ..."
   #define VVTXT14 "No Save &Integrations ..."
   #define VVTXT15 "No se calcula en escenarios con el tiempo como una componente"
   #define VVTXT16 "System Description"
   #define VVTXT17 "No have description for this system."
   #define VVTXT18 "El cálculo de ceroclina es para sistemas de 2 ecuaciones"
   #define VVTXT19 "Calculo de Isoclina"
   #define VVTXT20 "Valor a calcular:"
   #define VVTXT21 "El cálculo de isoclinas es para sistemas de 2 ecuaciones"
   #define VVTXT22 "Puntos a graficar en la Función auxiliar"
   #define VVTXT23 "Number of Points:"
   #define VVTXT24 "Función auxiliar a calcular"
   #define VVTXT25 "Función:"
   #define VVTXT26 "Escenarios a gráficar simultaneamente"
   #define VVTXT27 "Escenarios:"
   #define VVTXT28 "Equilibriums:"
   #define VVTXT29 "Period Map:"
   #define VVTXT30 "Repeat:"
#endif

//---------------------------------------------------------------------------


// Constructor de la clase
__fastcall TVentanaTrabajo::TVentanaTrabajo(TComponent* Owner) : TForm(Owner)
{
   Ctrl = new Controlador;
   if (!Ctrl) Free();
   // Solocitud de un nombre unico para soporte de archivos de última integración
   char xfile[MAXPATH];
   tmpnam(xfile);
   strcpy(Archivo_temporal,ARCHIVO_TEMPORAL);
   strcat(Archivo_temporal,xfile);
   Ctrl->Asigna_puntero_ventana_Visualizacion(VVentanaTrabajo);
   Ctrl->Inicializa();
   Titulo_ventana();
   // Al cambiar el sistema se activa los menus de las funciones activas existentes
   Activa_menu_funciones_auxiliares();
   
   // Controla si esta activo algun calculo
   Sw_calculo_en_proceso = false;
   Sw_cerrar_ventana = false;
   Sw_cancela_calculo = false;
   Sw_activo_visualizacion_cursor = true;
   Sw_visualizacion_condiciones_iniciales = true;
   Genera_reporte_integracion = false;
   Sw_graba_ventana_antes_de_integrar = false;
   Rotando_ejes = false;
   strcpy(Funcion_auxiliar,"F(t)=(sinl(t),cosl(t))");
   // Borra posibles archivos de las ventana de pixeles
   Ctrl->Borra_archivo_ventana_pixeles(Archivo_temporal);
   // Graba la configuración original para su posible restauración
   Ctrl->Graba_configuracion(ARCHIVO_CONFIGURACION_ORIGINAL);
   TimeTareas->Enabled = true;
   Veces_mapeo_periodo = 100;
   Tiempo_trayectoria_cerrada = 1000.0;
   Paso_trayectoria_cerrada = 0.001;
   Tiempo_sin_checar_trayectoria_cerrada = 0.1;
   Tolerancia_trayectoria_cerrada = 1e-5;
   Valor_isoclina = 1.0;

   // Zooms
   Zoom_manteniendo_aspecto = false;
   // Controla si esta activo algun calculo
   Sw_calculo_en_proceso = false;
   Sw_cerrar_ventana = false;
   // Inicializa el indicador de recuadro
   Sw_Dibuja_rectangulo = false;
   Ventana_seleccionada = false;
   Sw_Doble_click = false;
   Sw_Recuadro_activo = true;
   Sw_VisualizaTextoBarraEstados = true;
   // Dimenciones de la ventana
   Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
   // Dimensiones originales
   Dim_orig = Dim_Vtn;
   // Indice de zooms
   Ind_zoom = 0;
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
       Sw_cancela_calculo = true;
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
void __fastcall TVentanaTrabajo::TimeTareasTimer(TObject *Sender)
{
   // Activa la visualización del cursor
   if (Sw_activo_visualizacion_cursor) {
      Sw_activo_visualizacion_cursor = false;
      Ctrl->Activa_visualizacion_cursor();
   }
   // Almacena la ventana activa
   if (Focused()) {
      Ventana_activa = this;
   }   
   // Revisa si es la ventana activa 
   if (Ventana_activa == this) {
       switch (TAREA_POR_REALIZAR) {
          case P_SISTEMAS:
             TAREA_POR_REALIZAR = 0;
             Biblioteca1Click(this);
             break;
          case P_PARAMETROS:
             TAREA_POR_REALIZAR = 0;
             Modificar1Click(this);
             break;
          case P_EJES_2D:
             TAREA_POR_REALIZAR = 0;
             Ejes2DClick(this);
             break;
          case P_DIMENSIONES:
             TAREA_POR_REALIZAR = 0;
             Dimensiones1Click(this);
             break;
          case P_METODOSNUMERICOS:
             TAREA_POR_REALIZAR = 0;
             Integracin1Click(this);
             break;
          case P_ESCENARIOGRAFICO:
             TAREA_POR_REALIZAR = 0;
             EscenarioGraficoClick(this);
             break;
          case P_CAMPOVECTORIAL:
             TAREA_POR_REALIZAR = 0;
             Ctrl_tareas(CAMPO_VECTORIAL);
             break;
          case P_CAMPODIRECCIONAL:
             TAREA_POR_REALIZAR = 0;
             Ctrl_tareas(CAMPO_DIRECCIONAL);
             break;
          case P_CONDICIONESINICIALES:
             TAREA_POR_REALIZAR = 0;
             Movera1Click(this);
             break;
          case P_INTEGRATIEMPONEGATIVO:
             TAREA_POR_REALIZAR = 0;
             Ctrl_tareas(INTEGRAR_TIEMPO_NEGATIVO);
             break;
          case P_INTEGRATIEMPOPOSITIVO:
             TAREA_POR_REALIZAR = 0;
             Ctrl_tareas(INTEGRAR_TIEMPO_POSITIVO);
             break;
          case P_LIMPIARVENTANA:
             TAREA_POR_REALIZAR = 0;
             Ctrl_tareas(LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL);
             break;
          case P_GRFICAPUNTOSLINEAS:
             TAREA_POR_REALIZAR = 0;
             GraficarconPuntosolineas1Click(this);
             break;
       }
   }

   // Se ordena cancelar el cálculo al solicitar cerrar ventana
   if (Sw_cerrar_ventana) Ctrl->Detiene_calculo(); 
   // Controla que no este calculando para cerrar la ventana
   if (Sw_cerrar_ventana && !Sw_calculo_en_proceso) {
      Ventana_activa = NULL;
      Ctrl->Finaliza_reporte();
//#error deberia borrar todos los archivos temporales si los hay      
      Ctrl->Borra_archivo_ventana_pixeles(Archivo_temporal);
//#error Estos dos archivos se deben de borrar al terminar el programa      
//      unlink(ARCHIVO_CONFIGURACION);
//      unlink(ARCHIVO_CONFIGURACION_ORIGINAL);
      Ctrl->Destruye();
      delete Ctrl;
      Ctrl = NULL;
      Free();
   }
}

// Visualiza la condición inicial
void __fastcall TVentanaTrabajo::TimerVisualizaBarraEstadosTimer(TObject *Sender)
{
   if (!Sw_VisualizaTextoBarraEstados) return;
   // Visualiza la condición inicial
   char xcad[300];
   if (Rotando_ejes) {
      BarraEstados->SimpleText = V_TXT03;
    } else {
      if (!Sw_calculo_en_proceso) {
         if (Sw_visualizacion_condiciones_iniciales) {
            Ctrl->Condiciones_iniciales_texto(xcad);
         }
      } else sprintf(xcad,"Calculating: %+1.8Le Time, %d Iterations, to stop use Ctrl-Alt-S",Ctrl->Reporta_tiempo_integrado(),Ctrl->Reporta_numero_iteraciones());
      BarraEstados->SimpleText = xcad;
   }
}

// Actualiza los elementos del menu visibles
void __fastcall TVentanaTrabajo::TimerActivaDesactivaMenusTimer(TObject *Sender)
{
   // Revisa segun el tipo de escenario activo lo que se activara o desactivara
   EscenarioRotaciones->Enabled = false;
   // Ejes coordenados en tres dimensiones
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_3D) {
      Ejes3D->Enabled = false;
      Ejes3D->Checked = true;
      EscenarioRotaciones->Enabled = true;
      CalcularCeroclinas->Enabled = false;
      CalcularIsoclinas->Enabled = false;
    } else {
      Ejes3D->Enabled = true;
      Ejes3D->Checked = false;
   } 
   // Ejes coordenados en dos dimensiones
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2D) {
      Ejes2D->Enabled = false;
      Ejes2D->Checked = true;
      CalcularCeroclinas->Enabled = true;
      CalcularIsoclinas->Enabled = true;
    } else {
      Ejes2D->Enabled = true;
      Ejes2D->Checked = false;
   }
   // Ejes coordenados en dos dimensiones
   if (Ctrl->Retorna_tipo_ventana() == VENTANA_2D) {
      Ventana2D->Enabled = false;
      Ventana2D->Checked = true;
      CalcularCeroclinas->Enabled = true;
      CalcularIsoclinas->Enabled = true;
    } else {
      Ventana2D->Enabled = true;
      Ventana2D->Checked = false;
   }
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2DM) {
      Ejes2DM->Enabled = false;
      Ejes2DM->Checked = true;
      CalcularCeroclinas->Enabled = true;
      CalcularIsoclinas->Enabled = true;
    } else {
      Ejes2DM->Enabled = true;
      Ejes2DM->Checked = false;
   }
   // Ejes en forma de caja en tres dimensiones
   if (Ctrl->Retorna_tipo_ventana() == EJES_CAJA_3D) {
      Caja3D->Enabled = false;
      Caja3D->Checked = true;
      EscenarioRotaciones->Enabled = true;
      CalcularCeroclinas->Enabled = false;
      CalcularIsoclinas->Enabled = false;
    } else {
      Caja3D->Enabled = true;
      Caja3D->Checked = false;
   }
   // Ejes en forma de caja modificada en tres dimensiones
   if (Ctrl->Retorna_tipo_ventana() == EJES_CAJA_3DM) {
      Caja3DM->Enabled = false;
      Caja3DM->Checked = true;
      EscenarioRotaciones->Enabled = true;
      CalcularCeroclinas->Enabled = false;
      CalcularIsoclinas->Enabled = false;
    } else {
      Caja3DM->Enabled = true;
      Caja3DM->Checked = false;
   }
   // Ejes en forma de caja en dos dimensiones
   if (Ctrl->Retorna_tipo_ventana() == EJES_CAJA_2D) {
      Caja2D->Enabled = false;
      Caja2D->Checked = true;
      CalcularCeroclinas->Enabled = true;
      CalcularIsoclinas->Enabled = true;
    } else {
      Caja2D->Enabled = true;
      Caja2D->Checked = false;
   }
   // Ejes en coordenadas polares 
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADAS_POLARES) {
      CoordenadasPolares->Enabled = false;
      CoordenadasPolares->Checked = true;
      CalcularCeroclinas->Enabled = false;
      CalcularIsoclinas->Enabled = false;
      EscenarioGrafico->Enabled = false;
    } else {
      CoordenadasPolares->Enabled = true;
      CoordenadasPolares->Checked = false;
      EscenarioGrafico->Enabled = true;
   }

   // Revisa que tipo de ecuación fue capturada en la interfaz
   if (Ctrl->Retorna_tipo_ecuacion() == 1) {
      // Dependiendo del tipo de ecuación capturada en la interfaz activa o desactiva:
      EscenarioGrafico->Enabled = false;
      Ejes3D->Enabled = false;
      Caja3D->Enabled = false;
   }
}


// Acciones que se realizarán al usar una tecla
void __fastcall TVentanaTrabajo::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
   switch(Key) {
      case 27: // Esc
         Rotando_ejes = false;
         break;
      case 70: // Integra en tiempo positivo  
         Ctrl_tareas(INTEGRAR_TIEMPO_POSITIVO);              
         break;
      case 66: // Integra en tiempo negativo
         Ctrl_tareas(INTEGRAR_TIEMPO_NEGATIVO);        
         break;
      case 67: // Limpia la ventana  
         Ctrl_tareas(LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL);
         break;
      case 80: // Convierte la grafica de puntos a lineas y vice versa  
         GraficarconPuntosolineas1Click(this);
         break;
      case 83: // Detiene el calculo
         DetenerClculo1Click(this);
         break;
      case 107: // Incrementa el paso del cursor  (+)
         Ctrl->Incrementa_paso_cursor();
         break;
      case 109: // Decrementa el paso del cursor  (-)
         Ctrl->Decrementa_paso_cursor();
         break;
   }
}

// Acciones que se realizarán al usar teclas de movimiento
void __fastcall TVentanaTrabajo::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   switch(Key) {
      case 27: // Esc
         Rotando_ejes = false;
         break;
      case 38: // Flecha arriba
         if (!Rotando_ejes) Ctrl->Condicion_inicial(0,1, 0);
          else Ctrl->Rotar_ejes_3D(0.01,0.0);
         break;
      case 40: // Flecha abajo
         if (!Rotando_ejes) Ctrl->Condicion_inicial(0, -1, 0);
          else Ctrl->Rotar_ejes_3D(-0.01,0.0);
         break;
      case 37: // Flecha izquierda
         if (!Rotando_ejes) Ctrl->Condicion_inicial(-1, 0, 0);
          else Ctrl->Rotar_ejes_3D(0.0,0.01);
         break;
      case 39: // Flecha derecha
         if (!Rotando_ejes) Ctrl->Condicion_inicial(1, 0, 0);
          else Ctrl->Rotar_ejes_3D(0.0,-0.01);
         break;
      case 34: // Pagina abajo
         Ctrl->Condicion_inicial(0, 0, 1);
         break;
      case 33: // Pagina arriba
         Ctrl->Condicion_inicial(0, 0, -1);
         break;
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Opciones del Menu
//////////////////////////////////////////////////////////////////////////////////////////////

// Graba la ventana en formato BMP
void __fastcall TVentanaTrabajo::SaveWindowBMPFormat1Click(TObject *Sender)
{
   Sw_cancela_calculo  = true;
   TRect   xRect = Rect(0,0,VVentanaTrabajo->ClientWidth,VVentanaTrabajo->ClientHeight);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VVentanaTrabajo->ClientWidth;
   Bitmap->Height = VVentanaTrabajo->ClientHeight;
   Bitmap->Canvas->CopyRect(xRect, VVentanaTrabajo->Canvas, xRect);
   Bitmap->IgnorePalette = true;
   SaveDialog->Title = V_TXT02;
   if (SaveDialog->Execute()) Bitmap->SaveToFile(SaveDialog->FileName);           
   delete Bitmap;
}

// Imprime archivo
void __fastcall TVentanaTrabajo::Print1Click(TObject *Sender)
{
   Sw_cancela_calculo  = true;
   TRect   xRect = Rect(0,0,VVentanaTrabajo->ClientWidth,VVentanaTrabajo->ClientHeight);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VVentanaTrabajo->ClientWidth;
   Bitmap->Height = VVentanaTrabajo->ClientHeight;
   Bitmap->Canvas->CopyRect(xRect, VVentanaTrabajo->Canvas, xRect);
   Bitmap->SaveToFile(ARCHIVO_IMPRESION);
   delete Bitmap;
   Bitmap = new Graphics::TBitmap;
   Bitmap->LoadFromFile(ARCHIVO_IMPRESION);
   Printer()->BeginDoc();
   Printer()->Canvas->TextOut(100,210,Application->Title);
   Printer()->Canvas->TextOut(100,300,Caption);
   Printer()->Canvas->StretchDraw(Rect(100,500,Printer()->PageWidth-100,Printer()->PageWidth+200),Bitmap);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 300),COMPANIA);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 390),E_MAIL);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth + 480),WWW);
   Printer()->EndDoc();
   delete Bitmap;
   unlink(ARCHIVO_IMPRESION);
}

// Graba el estado del proyecto
void __fastcall TVentanaTrabajo::GrabarConfiguracin1Click(TObject *Sender)
{
   SaveDialogConfiguracion->Title = VVTXT10;
   if (SaveDialogConfiguracion->Execute()) {
      Ctrl->Graba_configuracion(SaveDialogConfiguracion->FileName.c_str());
   }
}

// Lee el estado del proyecto
void __fastcall TVentanaTrabajo::LeerConfiguracin1Click(TObject *Sender)
{
   OpenDialogConfiguracion->Title = VVTXT11;
   if (OpenDialogConfiguracion->Execute()) {
      Ctrl->Lee_configuracion(OpenDialogConfiguracion->FileName.c_str(),-1,99);
   }
}

// Restaura la configuración original del proyecto
void __fastcall TVentanaTrabajo::RestauraConfiguracinProyecto1Click(TObject *Sender)
{
   Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION_ORIGINAL,-1,99);
}

// Muestra el reporte de estado del proyecto
void __fastcall TVentanaTrabajo::ReportedeEstado1Click(TObject *Sender)
{
   TAyudaForm *vent = new TAyudaForm(this);
   if (vent) {
      Ctrl->Imprime_estado(0);
      vent->Abrir_archivo(VVTXT12,ARCHIVO_IMPRESION_TMP);
      vent->ShowModal();
      delete vent;
      unlink(ARCHIVO_IMPRESION_TMP);
   }
}

// Graba la integración numerica
void __fastcall TVentanaTrabajo::MenuArchivosGrabarIntegracionesClick(TObject *Sender)
{
   if (Genera_reporte_integracion) {
      // Desactiva la generación del reporte
      MenuArchivosGrabarIntegraciones->Caption = VVTXT13;
      Genera_reporte_integracion = false;
      Ctrl->Finaliza_reporte();
      // Pregunta si desea ver el archivo de integraciones
      if (MessageBox(Handle,V_TXT04,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         // Ver el archivo de integraciones
         TAyudaForm *vent = new TAyudaForm(this);
         if (vent) {
            vent->Abrir_archivo(VVTXT13,Archivo_integraciones);
            vent->ShowModal();
            delete vent;
         }
      }
    } else {
      // Activa la generación del reporte
      SaveDialogReport->Title = V_TXT02;
      if (SaveDialogReport->Execute()) {
         strcpy(Archivo_integraciones, SaveDialogReport->FileName.c_str());
         MenuArchivosGrabarIntegraciones->Caption = VVTXT14;
         Genera_reporte_integracion = true;
         Ctrl->Inicializa_reporte(Archivo_integraciones);
      }
   }
}


// Cerrar ventana de trabajo
void __fastcall TVentanaTrabajo::MenuArchivosCerrarClick(TObject *Sender)
{
   Close();     
}

// Al solicitar revisualizar la ventana
void __fastcall TVentanaTrabajo::VVentanaTrabajoPaint(TObject *Sender)
{
   Ctrl->Grafica();
}

// Control de tareas
void TVentanaTrabajo::Ctrl_tareas(const int tp)
{
   if(!Ctrl) return;
   switch (tp) {
      ///////////////////////////////////////////////////////////////////
      // Menu Calcular
      ///////////////////////////////////////////////////////////////////
      case INTEGRAR_TIEMPO_POSITIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Integra_tiempo_positivo();
         Sw_calculo_en_proceso = false;
         break;
      case INTEGRAR_TIEMPO_NEGATIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Integra_tiempo_negativo();
         Sw_calculo_en_proceso = false;
         break;
      case MAPEO_PERIODO_TIEMPO_POSITIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Mapeo_periodo_tiempo_positivo(Veces_mapeo_periodo);
         Sw_calculo_en_proceso = false;
         break;
      case MAPEO_PERIODO_TIEMPO_NEGATIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Mapeo_periodo_tiempo_negativo(Veces_mapeo_periodo);
         Sw_calculo_en_proceso = false;
         break;
      case PERIODO_TRAYECTORIA_CERRADA_TIEMPO_POSITIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Calculo_periodo_trayectoria_cerrada(Tiempo_trayectoria_cerrada, Paso_trayectoria_cerrada, Tiempo_sin_checar_trayectoria_cerrada, Tolerancia_trayectoria_cerrada,Periodo_trayectoria_cerrada);
         Sw_calculo_en_proceso = false;
         break;
      case PERIODO_TRAYECTORIA_CERRADA_TIEMPO_NEGATIVO:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         Ctrl->Calculo_periodo_trayectoria_cerrada(Tiempo_trayectoria_cerrada, -Paso_trayectoria_cerrada, Tiempo_sin_checar_trayectoria_cerrada, Tolerancia_trayectoria_cerrada,Periodo_trayectoria_cerrada);
         Sw_calculo_en_proceso = false;
         break;
      case CAMPO_VECTORIAL:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         if (Ctrl->Dibuja_campo_vectorial()) ShowMessage(VVTXT15);
         Sw_calculo_en_proceso = false;     
         break;
      case CAMPO_DIRECCIONAL:
         Sw_calculo_en_proceso = true;
         Graba_ventana();
         if (Ctrl->Dibuja_campo_direccional()) ShowMessage(VVTXT15);     
         Sw_calculo_en_proceso = false;
         break;
      ///////////////////////////////////////////////////////////////////
      // Menu Parámetros
      ///////////////////////////////////////////////////////////////////
      case PARAMETROS_ORIGINALES:
         Borra_Archivos_ventana();
         Ctrl->Parametros_originales();
         Ctrl->Fija_Guardar_posicion_integracion(false);
         break;
      case PARAMETROS_LIMPIAR_USADOS_VARIABLES:
         Borra_Archivos_ventana();
         Ctrl->Parametros_limpiar_variables();
         Ctrl->Fija_Guardar_posicion_integracion(false);
         break;
      ///////////////////////////////////////////////////////////////////
      // Menu Ventana
      ///////////////////////////////////////////////////////////////////
      case LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL:
         Ctrl->Limpiar_ventana_sin_conservar_condicion_inicial();
         Borra_Archivos_ventana();
         break;   
      case LIMPIA_VENTANA_CONSERVANDO_CONDICION_INICIAL:
         Borra_Archivos_ventana();
         Ctrl->Limpiar_ventana_conservado_condicion_inicial();
         break;
   }
}

// Genera el titulo de la ventana con el nombre del sistema activo
void TVentanaTrabajo::Titulo_ventana(void)
{
   char nombre[1000], xcad[1000];
   Ctrl->Nombre_sistema_activo(nombre);
   sprintf(xcad,"System: %s",nombre);
   Caption = xcad;
   Ctrl->Actualiza_escenario();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Sistemas

// Menu->Sistemas->Selecionar sistema
void __fastcall TVentanaTrabajo::Biblioteca1Click(TObject *Sender)
{
/////////////////////////////////////////////////////////////////////////////////////////
// Al modificar esta función tambien hacerlo en los demas escenario de Bifurca
/////////////////////////////////////////////////////////////////////////////////////////
   TSeleccionSistemas *vent = new TSeleccionSistemas(this);
   if (vent) {
      // Pasa parámetros
      if (Ctrl->Retorna_numero_sistemas()) {
         vent->ListBoxSistemas->Items->Clear();
         for (int i = 0; i < Ctrl->Retorna_numero_sistemas(); i ++) {
             vent->ListBoxSistemas->Items->Add(Ctrl->Retorna_nombre_sistema(i));
         }
         vent->Pasa_puntero(Ctrl);
         vent->Actualiza_configuracion(Ctrl->Retorna_numero_sistema_actual());
      } 
      vent->ShowModal();
      if (vent->Estado) {
         for (int i = 0; i < vent->ListBoxSistemas->Items->Count; i++) {
             if (vent->ListBoxSistemas->Selected[i]) Ctrl->Establece_sistema_activo(i);
         }
         Titulo_ventana();
      }
      delete vent;
   }
   Borra_Archivos_ventana();
   // Actualiza las dimensiones de la venatana
   Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
   Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   // Dimensiones originales
   Dim_orig = Dim_Vtn;
   // Indice de zooms
   Ind_zoom = 0;
   // Posiciona el cursor al origen
   Ctrl->Cursor_al_centro_ventana();
   // Al cambiar el sistema se activa los menus de las funciones activas existentes
   Activa_menu_funciones_auxiliares();
   
}

// Menu->Sistemas->Descripción del sistema
void __fastcall TVentanaTrabajo::Descripcin1Click(TObject *Sender)
{
   TLMensajeForm *vent = new TLMensajeForm(this);
   if (vent) {
      char ARCHIVO[200], xarchivo[200];
      vent->Caption = VVTXT16;
      sprintf(ARCHIVO,"%s%02d",Ctrl->Retorna_nombre_proyecto(),Ctrl->Retorna_numero_sistema_actual()+1);
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
         } else vent->Editor->Lines->Append(VVTXT17);
      }
      vent->ShowModal();
      delete vent;
   }
}

// Menu->Sistemas->Reporte de Estado
void __fastcall TVentanaTrabajo::ReporteEstado1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ctrl->Imprime_estado(1);
      Ayuda->Abrir_archivo(VVTXT12,ARCHIVO_IMPRESION_TMP);
      Ayuda->ShowModal();
      unlink(ARCHIVO_IMPRESION_TMP);
      delete Ayuda;
   }
}

// Menu->Sistema->Copia la configuracion del sistema
void __fastcall TVentanaTrabajo::CopyConfiguration1Click(TObject *Sender)
{
   // Graba configuración del sistema
   Ctrl->Graba_configuracion(ARCHIVO_CONFIGURACION);
}

// Menu->Sistema->Pega la configuracion del sistema
void __fastcall TVentanaTrabajo::PastConfiguration1Click(TObject *Sender)
{
   // Pega la configuración del sistema
   if (MessageBox(Handle,"Do you wish to paste all configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),99);
   } else {
      if (MessageBox(Handle,"Do you wish to paste parameters configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),1);
      }
      if (MessageBox(Handle,"Do you wish to paste initial conditions configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),2);
      }
      if (MessageBox(Handle,"Do you wish to paste numerical methods configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),3);
      }
      if (MessageBox(Handle,"Do you wish to paste dimensions configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),4);
      }
      if (MessageBox(Handle,"Do you wish to paste scenerys configuration?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
         Ctrl->Lee_configuracion(ARCHIVO_CONFIGURACION,Ctrl->Retorna_numero_sistema_actual(),5);
      }
   }
   Ctrl->Limpiar_ventana_conservado_condicion_inicial();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Calcular

// Menu->Calcular->Integrar en tiempo positivo
void __fastcall TVentanaTrabajo::IntegraTPositivo1Click(TObject *Sender)
{
   Ctrl_tareas(INTEGRAR_TIEMPO_POSITIVO);        
}

// Menu->Calcular->Integrar en tiempo negativo
void __fastcall TVentanaTrabajo::IntegraTNegativo1Click(TObject *Sender)
{
   Ctrl_tareas(INTEGRAR_TIEMPO_NEGATIVO);        
}

// Menu->Calcular->Detener calculo
void __fastcall TVentanaTrabajo::DetenerClculo1Click(TObject *Sender)
{
   Ctrl->Detiene_calculo();        
}

// Menu->Calcular->Equilibrios
void __fastcall TVentanaTrabajo::Equilibriums1Click(TObject *Sender)
{
   // Calculo de equilibrios
   Sw_calculo_en_proceso = true;
   Graba_ventana();
   BarraEstados->SimpleText = "Calculating...";
   if (Ctrl->Calculo_equilibrios()) {
      TAyudaForm *Ayuda = new TAyudaForm(this);
      if (Ayuda) {
         Ayuda->Abrir_archivo(VVTXT28,ARCHIVO_IMPRESION_TMP);
         Ayuda->ShowModal();
         unlink(ARCHIVO_IMPRESION_TMP);
         delete Ayuda;
      }
   }
   Sw_calculo_en_proceso = false;
}

// Menu->Calcular->Mapeo período tiempo positivo
void __fastcall TVentanaTrabajo::PeriodMapForward1Click(TObject *Sender)
{
   char input[80];
   AnsiString Valor = (AnsiString) Veces_mapeo_periodo;

   Graba_ventana();
   if (InputQuery(VVTXT29,VVTXT30, Valor)) {
       memccpy(input,Valor.c_str(),0,79);
       Veces_mapeo_periodo = atoi(input);
       Ctrl_tareas(MAPEO_PERIODO_TIEMPO_POSITIVO);        
   }
}

// Menu->Calcular->Mapeo período tiempo negativo
void __fastcall TVentanaTrabajo::BackwardPeriodMap1Click(TObject *Sender)
{
   char input[80];
   AnsiString Valor = (AnsiString) Veces_mapeo_periodo;

   Graba_ventana();
   if (InputQuery(VVTXT29,VVTXT30, Valor)) {
       memccpy(input,Valor.c_str(),0,79);
       Veces_mapeo_periodo = atoi(input);
       Ctrl_tareas(MAPEO_PERIODO_TIEMPO_POSITIVO);
   }
}

// Menu->Calcular->Período de una Trayectoria Cerrada en tiempo positivo
void __fastcall TVentanaTrabajo::ForwardTrajectory1Click(TObject *Sender)
{
   char xcad[100];
   BarraEstados->SimpleText = "Calculating...";
   Ctrl_tareas(PERIODO_TRAYECTORIA_CERRADA_TIEMPO_POSITIVO);

   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
         Ayuda->EditorAyuda->Lines->Add("Period of Closed Trajectory:");
         sprintf(xcad,"%+1.16Le",Periodo_trayectoria_cerrada);
         Ayuda->EditorAyuda->Lines->Add(xcad);
         Ayuda->ShowModal();
         delete Ayuda;
   }
//   Tiempo_trayectoria_cerrada = 1000.0;
//   Paso_trayectoria_cerrada = 0.001;
//   Tiempo_sin_checar_trayectoria_cerrada = 0.1;
//   Tolerancia_trayectoria_cerrada = 1e-5;
   BarraEstados->SimpleText = " ";
}

// Menu->Calcular->Período de una Trayectoria Cerrada en tiempo negativo
void __fastcall TVentanaTrabajo::BackwardsTrajectory1Click(TObject *Sender)
{
   char xcad[100];
   BarraEstados->SimpleText = "Calculating...";
   Ctrl_tareas(PERIODO_TRAYECTORIA_CERRADA_TIEMPO_NEGATIVO);
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
         Ayuda->EditorAyuda->Lines->Add("Period of Closed Trajectory:");
         sprintf(xcad,"%+1.16Le",Periodo_trayectoria_cerrada);
         Ayuda->EditorAyuda->Lines->Add(xcad);
         Ayuda->ShowModal();
         delete Ayuda;
   }
   BarraEstados->SimpleText = " ";
}


// Menu->Calcular->Isoclinas->Ceroclinas
void __fastcall TVentanaTrabajo::CalcularCeroclinasClick(TObject *Sender)
{
   Sw_calculo_en_proceso = true;
   Graba_ventana();
   if (Ctrl->Dibuja_isoclina(0.0)) ShowMessage(VVTXT18);     
   Sw_calculo_en_proceso = false;
}

// Menu->Calcular->Isoclinas->Isoclinas
void __fastcall TVentanaTrabajo::CalcularIsoclinasClick(TObject *Sender)
{
   char xcad[100], input[80], *endptr;
   sprintf(xcad,"%Le",Valor_isoclina);
   AnsiString Valor = xcad;

   Graba_ventana();
   if (InputQuery(VVTXT19,VVTXT20, Valor)) {
       memccpy(input,Valor.c_str(),0,79);
       Valor_isoclina = _strtold(input, &endptr);
       Sw_calculo_en_proceso = true;
       if (Ctrl->Dibuja_isoclina(Valor_isoclina)) ShowMessage(VVTXT21);     
       Sw_calculo_en_proceso = false;
   }
}

// Menu->Calcular->Isoclinas->Puntos a graficar
void __fastcall TVentanaTrabajo::PuntosaGraficar1Click(TObject *Sender)
{
   char xcad[100];
   int pts;
   itoa(Ctrl->Retorna_puntos_graficar_isoclinas(), xcad, 10);
   AnsiString puntos = xcad;

   if (InputQuery(VVTXT22,VVTXT23, puntos)) {
       pts = atoi(puntos.c_str());
       if (pts > 0) Ctrl->Establece_puntos_graficar_isoclinas(pts);
   }
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar11Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(1));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar21Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(2));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar31Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(3));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar41Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(4));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar51Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(5));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar61Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(6));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar71Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(7));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar81Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(8));
}

// Menu->Calcular->Funciones Auxiliares->Graficar funciones auxiares definidas por el usuario
void __fastcall TVentanaTrabajo::FuncionAuxuliar91Click(TObject *Sender)
{
   Control_funciones_auxliares(Ctrl->Retorna_funcion_auxiliar_definida(9));
}

// Menu->Calcular->Funciones Auxiliares->Graficar
void __fastcall TVentanaTrabajo::Graficar1Click(TObject *Sender)
{
   AnsiString Fun = Funcion_auxiliar;
   char xexp[2010];
   // Captura de la función auxiliar
   if (InputQuery(VVTXT24,VVTXT25, Fun)) {
      // Función auxiliar capturada por el usuario
      strcpy(Funcion_auxiliar,Fun.c_str());
      // Validación inicial
      if (!(Funcion_auxiliar[0] == 'F' && Funcion_auxiliar[1] == '(' && (Funcion_auxiliar[2] == 't' || Funcion_auxiliar[2] == 'x' || Funcion_auxiliar[2] == 'y') && Funcion_auxiliar[3] == ')' && Funcion_auxiliar[4] == '=')) {
         MessageBox(Handle,"The function is defined as F(t)=(...,...), F(x)=... or F(y)=...",VVTXT24,MB_OK + MB_ICONINFORMATION);
         return;
      }
      // Analiza la expresion en busca de errores de sintaxis
      strcpy(xexp,Funcion_auxiliar);
      Analizador_sintactico *As = new Analizador_sintactico;
      if (xexp[3] == 'x' || xexp[3] == 'y') {
         // Cambia el F(x)= por X=
         xexp[0] = xexp[1] = xexp[2] = 32, xexp[3] = 'X';
         // Valida la expresion
         As->Analiza_expresion_tipo_01(xexp);
       } else {
         // Cambia el F(x)= por X=P
         xexp[0] = xexp[1] = 32;
         xexp[2] = 'X';
         xexp[3] = '=';
         xexp[4] = 'P';
         // Valida la expresion
         As->Analiza_expresion_tipo_01(xexp);
      }
      // Si hay errores muestra estos 
      if(As->Numero_errores()) {
         TLMensajeForm *vtn = new TLMensajeForm(this);
         vtn->Caption = "Warnings and Errors ...";
         // Introduce la expresión a graficar
         vtn->Editor->Lines->Add(Funcion_auxiliar);
         // Introduce los errores encontrados en la expresión a graficar
         for (int i = 0; i < As->Numero_errores(); i++) vtn->Editor->Lines->Add(As->Retorna_error(i));
         vtn->ShowModal();
         delete vtn;
       } else {      
         // Grafica la función auxiliar
         Control_funciones_auxliares(Funcion_auxiliar);
      }
   }
}


// Gráfica la Funcion Auxiliar
void TVentanaTrabajo::Control_funciones_auxliares(const char *cad)
{
/////////////////////////////////////////////////////////////////////////////////////////
// Al modificar esta función tambien hacerlo en los demas escenario de Bifurca
/////////////////////////////////////////////////////////////////////////////////////////
   if (!cad[0]) return;
   Cadenas cd;
   char xcad[100], xfun[1000];
   unsigned int posini, pos;
   strcpy(xfun, cad);
   strcpy(Funcion_auxiliar,cad);

   Dimension_Ventana vtn;
   Ctrl->Retorna_dimensiones_sistema(vtn);
   // Ajusta las dimensiones de la ventana
   if (cd.Busca_caracter(xfun,'|', pos)) {
       posini = pos;
       char xcad1[100], xcad2[1000];
       cd.Substr(xfun, (pos+1), 100, xcad1);
       if (cd.Busca_caracter(xcad1,'|', pos)) {
           cd.Substr(xcad1, (pos+1), 100, xcad2);
           xcad1[pos] = 0;
           if (xfun[2] == 'x' || xfun[2] == 'X') {
               vtn.Xi = atof(xcad1); // Valor inicial
               vtn.Xf = atof(xcad2); // Valor final
            } else {
               vtn.Yi = atof(xcad1); // Valor inicial
               vtn.Yf = atof(xcad2); // Valor final
           }
       }
       // Expresión a gráficar
       xfun[posini] = 0;
   }
   
   // Remplaza los parametros existentes dentro de la expresión
   for (int i = 0; i < Ctrl->Numero_parametros_sistema(); i ++) {
      sprintf(xcad,"%1.10Lf",Ctrl->Retorna_valor_parametro(i));
      cd.Busca_remplaza_expresion(xfun, Ctrl->Retorna_nombre_parametro(i), xcad);
   }
   
   Sw_calculo_en_proceso = true;
   Ctrl->Grafica_funcion_auxiliar(xfun, vtn);
   Sw_calculo_en_proceso = false;
}


// Menu->Calcular->Funciones Auxiliares->Puntos a graficar
void __fastcall TVentanaTrabajo::Puntos1Click(TObject *Sender)
{
   char xcad[100];
   int pts;
   itoa(Ctrl->Retorna_puntos_graficar_funcion_auxiliar(), xcad, 10);
   AnsiString puntos = xcad;

   if (InputQuery(VVTXT22,VVTXT23, puntos)) {
       pts = atoi(puntos.c_str());
       if (pts > 0) Ctrl->Establece_puntos_graficar_funcion_auxiliar(pts);
   }
}

// Activa menus de las funciones auxiliares activas
void TVentanaTrabajo::Activa_menu_funciones_auxiliares(void)
{
   // Al cambiar el sistema se activa los menus de las funciones activas existentes
   FuncionAuxuliar11->Visible = false;
   FuncionAuxuliar21->Visible = false;
   FuncionAuxuliar31->Visible = false;
   FuncionAuxuliar41->Visible = false;
   FuncionAuxuliar51->Visible = false;
   FuncionAuxuliar61->Visible = false;
   FuncionAuxuliar71->Visible = false;
   FuncionAuxuliar81->Visible = false;
   FuncionAuxuliar91->Visible = false;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 1) FuncionAuxuliarSeparador->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 1) FuncionAuxuliar11->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 2) FuncionAuxuliar21->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 3) FuncionAuxuliar31->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 4) FuncionAuxuliar41->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 5) FuncionAuxuliar51->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 6) FuncionAuxuliar61->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 7) FuncionAuxuliar71->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 8) FuncionAuxuliar81->Visible = true;
   if (Ctrl->Retorna_numero_funcion_auxiliar_definida() >= 9) FuncionAuxuliar91->Visible = true;
}



// Menu->Calcular->Campo Vectorial
void __fastcall TVentanaTrabajo::CampoVectorial1Click(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_CAMPOVECTORIAL;       
}

// Menu->Calcular->Campo Direccional
void __fastcall TVentanaTrabajo::DirectionalField1Click(TObject *Sender)
{
   TAREA_POR_REALIZAR = P_CAMPODIRECCIONAL;       
}

// Menu->Calcular->Borra la última integración
void __fastcall TVentanaTrabajo::MenuVentanaBorrarultimaintegracinClick(TObject *Sender)
{
   // Limpia la ventana de trabajo
   Ctrl->Limpiar_ventana_sin_conservar_condicion_inicial();
   // Lee la ultima ventana generada 
//#error Debe poder leer las ultimas n integraciones
   Ctrl->Lee_ventana_pixeles(Archivo_temporal);
   // Activa el menú de borrar la última integración
   Borra_Archivos_ventana();
}

// Indica que graba la ventana de pixeles
void TVentanaTrabajo::Graba_ventana(void)
{
//#error Debe poder grabar las ultimas n integraciones
   if (Sw_graba_ventana_antes_de_integrar) {
      // Desactiva el menú de borrar la última integración
      MenuVentanaBorrarultimaintegracin->Enabled = true;
      // Graba la ventana antes de integrar
      Ctrl->Graba_ventana_pixeles(Archivo_temporal);
   }
}


void TVentanaTrabajo::Borra_Archivos_ventana(void)
{
//#error Debe poder borrar las ultimas n integraciones o todas si así se precisa
   // Activa el menú de borrar la última integración
   MenuVentanaBorrarultimaintegracin->Enabled = false;
   // Borra los archivos donde se grabo la ventana de pixeles
   Ctrl->Borra_archivo_ventana_pixeles(Archivo_temporal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Parámetros

// Menu->Parámetros->Modificar
void __fastcall TVentanaTrabajo::Modificar1Click(TObject *Sender)
{
/////////////////////////////////////////////////////////////////////////////////////////
// Al modificar esta función tambien hacerlo en los demas escenario de Bifurca
/////////////////////////////////////////////////////////////////////////////////////////
   // Limpia parámetros que son usados como variables
   Ctrl_tareas(PARAMETROS_LIMPIAR_USADOS_VARIABLES);        
   // Edición de parámetros
   TParametros *vent = new TParametros(this);
   if (vent) {
      // Pasa parámetros
      if (Ctrl->Numero_parametros_sistema()) {
         char xcad[200];
         vent->StaticText1->Visible = true;
         vent->ListBoxParametros->Items->Clear();
         for (int i = 0; i < Ctrl->Numero_parametros_sistema(); i ++) {
            sprintf(xcad,"%s = %1.10Lf",Ctrl->Retorna_nombre_parametro(i),Ctrl->Retorna_valor_parametro(i));
            vent->ListBoxParametros->Items->Add(xcad);
         }
         vent->ListBoxParametros->Visible = true;
      } else  vent->Panel1->Caption = VVTXT01;
      vent->ShowModal();
      if (vent->Estado) {
         // Retorna parámetros
         if (Ctrl->Numero_parametros_sistema()) {
             unsigned int i1, i2;
             char xcad[100], xcad1[100];
             for (int i = 0; i < Ctrl->Numero_parametros_sistema(); i ++) {
                AnsiString txt1(vent->ListBoxParametros->Items->Strings[i]);
                memccpy(xcad1,txt1.c_str(),0,99);
                // Valor del parámetro
                i1 = 0;
                while(xcad1[i1] != '=') i1++;
                i1++;
                for (i2 = 0; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
                xcad[i2] = 0;
                Ctrl->Establece_valor_parametro(i,atof(xcad));
             }
         }
      }
      delete vent;
   }
   Ctrl->Fija_Guardar_posicion_integracion(false);
}

// Menu->Parámetros->Parámetros originales
void __fastcall TVentanaTrabajo::Originales1Click(TObject *Sender)
{
   Ctrl_tareas(PARAMETROS_ORIGINALES);
}


// Menu->Parámetros->Limpiar Parámetros que se usan como variables
void __fastcall TVentanaTrabajo::ParametrosClearClick(TObject *Sender)
{
   Ctrl_tareas(PARAMETROS_LIMPIAR_USADOS_VARIABLES);        
}
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Cursor

// Menu->Cursor->Condicion Inicial
void __fastcall TVentanaTrabajo::Movera1Click(TObject *Sender)
{
   TCondicionInicial *vent = new TCondicionInicial(this);
   if (vent) {
      // Pasa parámetros
      int i, xi;
      char xcad[200], xcad1[200];
      unsigned int i1, i2;
      vent->ListBoxCondicionInicial->Visible = false;
      vent->ListBoxCondicionInicial->Items->Clear();
      for (i = 0; i < Ctrl->Retorna_numero_ecuaciones_sistema(); i ++) {
         xi = 0;
         memccpy(xcad1,Ctrl->Retorna_ecuacion_sistema(i),0,199);
         while(xcad1[xi] != '\'') xi++;
         xcad1[xi] = 0;
         sprintf(xcad,"%s = %1.10Lf",xcad1,Ctrl->Retorna_condiciones_iniciales(i));
         vent->ListBoxCondicionInicial->Items->Add(xcad);
      }
      sprintf(xcad,"Time = %1.10Lf",Ctrl->Retorna_condiciones_iniciales(i));
      vent->ListBoxCondicionInicial->Items->Add(xcad);
      vent->ListBoxCondicionInicial->Visible = true;
      vent->ShowModal();
      if (vent->Estado) {
         // Retorna parámetros
         for (i = 0; i <= Ctrl->Retorna_numero_ecuaciones_sistema(); i ++) {
            AnsiString txt1(vent->ListBoxCondicionInicial->Items->Strings[i]);
            memccpy(xcad1,txt1.c_str(),0,99);
            // Valor del parámetro
            i1 = 0;
            while(xcad1[i1] != '=') i1++;
            i1++;
            for (i2 = 0; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
            xcad[i2] = 0;
            Ctrl->Establece_condiciones_iniciales(i,atof(xcad));
         }
      }
      delete vent;
   }
}

// Menu->Cursor->Mover al origen la condicion inicial
void __fastcall TVentanaTrabajo::Moveralorigen1Click(TObject *Sender)
{
   Ctrl->Cursor_al_origen();
}

void __fastcall TVentanaTrabajo::MovetoMiddlePointofWindow1Click(TObject *Sender)
{
   Ctrl->Cursor_al_centro_ventana();
}


// Menu->Cursor->Configurar el paso del cursor
void __fastcall TVentanaTrabajo::PasodelCursor1Click(TObject *Sender)
{
   TPasoCursor *vent = new TPasoCursor(this);
   if (vent) {
      C_3D paso;
      char xcad[100];
      Ctrl->Retorna_paso_cursor(paso);
      // Envia valores a la ventana
      sprintf(xcad,"%1.10Lf",paso.x);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",paso.y);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",paso.z);
      vent->Edit3->Text = (AnsiString) xcad;
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         paso.x = atof(txt1.c_str());
         AnsiString txt2(vent->Edit2->Text);
         paso.y = atof(txt2.c_str());
         AnsiString txt3(vent->Edit3->Text);
         paso.z = atof(txt3.c_str());
         // Actualiza los valores
         Ctrl->Establece_paso_cursor(paso);
      }
      // Destruye la ventana
      delete vent;
   }
}

// Menu->Cursor->Configurar el inclemento del paso del cursor
void __fastcall TVentanaTrabajo::IncrementodelCursor1Click(TObject *Sender)
{
   TIncrementoPasoCursor *vent = new TIncrementoPasoCursor(this);
   if (vent) {
      C_3D paso;
      char xcad[100];
      Ctrl->Retorna_incremento_paso_cursor(paso);
      // Envia valores a la ventana
      sprintf(xcad,"%1.10Lf",paso.x);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",paso.y);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",paso.z);
      vent->Edit3->Text = (AnsiString) xcad;
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         paso.x = atof(txt1.c_str());
         AnsiString txt2(vent->Edit2->Text);
         paso.y = atof(txt2.c_str());
         AnsiString txt3(vent->Edit3->Text);
         paso.z = atof(txt3.c_str());
         // Actualiza los valores
         Ctrl->Establece_incremento_paso_cursor(paso);
      }
      // Destruye la ventana
      delete vent;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Ventana

// Menu->Ventana->Configurar las dimensiones de la ventana de trabajo
void __fastcall TVentanaTrabajo::Dimensiones1Click(TObject *Sender)
{
   TDimensiones *vent = new TDimensiones(this);
   if (vent) {
      Dimension_Ventana  dim;
      long double todos, factor;
      char xcad[100];
      Ctrl->Retorna_dimensiones_sistema(dim);
      // Envia valores a la ventana
      sprintf(xcad,"%1.10Lf",dim.Xi);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",dim.Xf);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",dim.Yi);
      vent->Edit3->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",dim.Yf);
      vent->Edit4->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",dim.Zi);
      vent->Edit5->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",dim.Zf);
      vent->Edit6->Text = (AnsiString) xcad;
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         dim.Xi = atof(txt1.c_str());
         AnsiString txt2(vent->Edit2->Text);
         dim.Xf = atof(txt2.c_str());
         AnsiString txt3(vent->Edit3->Text);
         dim.Yi = atof(txt3.c_str());
         AnsiString txt4(vent->Edit4->Text);
         dim.Yf = atof(txt4.c_str());
         AnsiString txt5(vent->Edit5->Text);
         dim.Zi = atof(txt5.c_str());
         AnsiString txt6(vent->Edit6->Text);
         dim.Zf = atof(txt6.c_str());
         AnsiString txt7(vent->Edit7->Text);
         todos  = atof(txt7.c_str());
         AnsiString txt8(vent->Edit8->Text);
         factor = atof(txt8.c_str());
         // Actualiza los valores
         Ctrl->Establece_dimensiones_sistema(dim, todos, factor);
      }
      // Destruye la ventana
      delete vent;
   }
   // Actualiza las dimensiones de la venatana
   Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
   Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
}

void __fastcall TVentanaTrabajo::OriginalDimension1Click(TObject *Sender)
{
   Dim_Vtn = Dim_orig;
   Ctrl->Establece_dimensiones_sistema(Dim_Vtn, 0.0, 0.0);
   Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   Ind_zoom = 0;
   MenuVentanaZoomOut->Enabled = false;
}


// Menu->Ventana->Zoom out
void __fastcall TVentanaTrabajo::MenuVentanaZoomOutClick(TObject *Sender)
{
   Ctrl->Detiene_calculo();        
   // Almacena las dimensiones actuales
   if (Ind_zoom > 0) {
      Ind_zoom --;
      Dim_Vtn = Dim_zoom[Ind_zoom];
      Ctrl->Establece_dimensiones_sistema(Dim_Vtn, 0.0, 0.0);
      // Calcula la escala de la ventana de visualizacion
      Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
      Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
      if (Ind_zoom < 1) MenuVentanaZoomOut->Enabled = false;
   }
}



// Menu->Ventana->Limpiar sin conservar condicion inicial
void __fastcall TVentanaTrabajo::LimpiarsinConsPosicion1Click(TObject *Sender)
{
   Ctrl_tareas(LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL);
}

// Menu->Ventana->Limpiar conservando condicion inicial
void __fastcall TVentanaTrabajo::LimpiarconsPosicion1Click(TObject *Sender)
{
   Ctrl_tareas(LIMPIA_VENTANA_CONSERVANDO_CONDICION_INICIAL);
}

// Menu->Ventana->Establece el tipo de ventana a ejes coordenados 2D
void __fastcall TVentanaTrabajo::Ejes2DClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_COORDENADOS_2D);
}

// Menu->Ventana->Establece el tipo de ventana a ejes coordenados 2D Modificados 
void __fastcall TVentanaTrabajo::Ejes2DMClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_COORDENADOS_2DM);
}

// Menu->Ventana->Establece el tipo de ventana a ejes caja 2D
void __fastcall TVentanaTrabajo::Caja2DClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_CAJA_2D);
}

// Menu->Ventana->Establece el tipo de ventana a ventana completa 2D
void __fastcall TVentanaTrabajo::Ventana2DClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(VENTANA_2D);
}


// Menu->Ventana->Establece el tipo de ventana a ejes coordenados 3D
void __fastcall TVentanaTrabajo::Ejes3DClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_COORDENADOS_3D);
}


// Menu->Ventana->Establece el tipo de ventana a ejes caja 3D
void __fastcall TVentanaTrabajo::Caja3DClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_CAJA_3D);
}

// Menu->Ventana->Establece el tipo de ventana a ejes caja modificada 3D
void __fastcall TVentanaTrabajo::Caja3DMClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_CAJA_3DM);
}


// Menu->Ventana->Establece el tipo de ventana a ejes en coordenadoas polares
void __fastcall TVentanaTrabajo::CoordenadasPolaresClick(TObject *Sender)
{
   Ctrl->Establece_tipo_ventana(EJES_COORDENADAS_POLARES);
}

// Menu->Ventana->Configurar los colores del sistema
void __fastcall TVentanaTrabajo::Colores1Click(TObject *Sender)
{
   TColoresSistema *vent = new TColoresSistema(this);
   TColor c1,c2,c3,c4,c5,c6,c7,c8;
   if (vent) {
       Ctrl->Retorna_colores(c1, c2, c3, c4, c5, c6, c7, c8);
      vent->Panel2->Color = c6;
      vent->Panel3->Color = c7;
      vent->Panel4->Color = c8;
      vent->Panel5->Color = c4;
      vent->Panel6->Color = c5;
      vent->Panel7->Color = c3;
      vent->Panel8->Color = c2;
      vent->Panel9->Color = c1;
      vent->ShowModal();
      if (vent->Estado) {
         c6 = vent->Panel2->Color;
         c7 = vent->Panel3->Color;
         c8 = vent->Panel4->Color;
         c4 = vent->Panel5->Color;
         c5 = vent->Panel6->Color;
         c3 = vent->Panel7->Color;
         c2 = vent->Panel8->Color;
         c1 = vent->Panel9->Color;
         Ctrl->Fija_colores(c1, c2, c3, c4, c5, c6, c7, c8);
         delete vent;
         Ctrl->Dibuja();
      }
   }
}

// Menu->Ventana->Mustra u oculta los nombres de los ejes
void __fastcall TVentanaTrabajo::Nombredeejes1Click(TObject *Sender)
{
   Ctrl->Establece_Visualiza_nombre_eje(!Ctrl->Retorna_visualiza_nombre_eje());
   if (Ctrl->Retorna_visualiza_nombre_eje()) Nombredeejes1->Caption = VVTXT02;
    else Nombredeejes1->Caption = VVTXT03;
   Ctrl->Grafica(); 
}

// Menu->Ventana->Mustra u oculta las condiciones Iniciales
void __fastcall TVentanaTrabajo::Coordenadascursor1Click(TObject *Sender)
{
   Sw_visualizacion_condiciones_iniciales = !Sw_visualizacion_condiciones_iniciales;
   if (Sw_visualizacion_condiciones_iniciales) Coordenadascursor1->Caption = VVTXT04;
    else Coordenadascursor1->Caption = VVTXT05;
   BarraEstados->SimpleText = ""; 
}

// Menu->Ventana->Activa Recuperacion de Estado Antes de Calcular
void __fastcall TVentanaTrabajo::ActivaRecuperaciondeestadoantesdecalcular1Click(TObject *Sender)
{
// #error Modificer el elemento del menu segun el estado existente
   Sw_graba_ventana_antes_de_integrar = !Sw_graba_ventana_antes_de_integrar;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Métodos Numéricos

// Menu->Métodos Numéricos->Configurar los métodos numéricos de integración
void __fastcall TVentanaTrabajo::Integracin1Click(TObject *Sender)
{
   TConfiguracionMetodosIntegracion *vent = new TConfiguracionMetodosIntegracion(this);
   if (vent) {
      vent->ListaMetodosNumericos->Items->Clear();
      for (int i = 0; i < NUMERO_METODOS_NUMERICOS; i++) {
          vent->ListaMetodosNumericos->Items->Add(Ctrl->Retorna_nombre_metodo_integracion(i));
      }
      vent->ListaMetodosNumericos->ItemIndex = Ctrl->Retorna_metodo_numerico_integracion();
      vent->Pasa_puntero_controlador(Ctrl);
      vent->Actualiza_valores();
      vent->ShowModal();
      if (vent->Estado) {
         int met;
         met = vent->ListaMetodosNumericos->ItemIndex;
         Ctrl->Establece_metodo_numerico_integracion(met);
         AnsiString txt1(vent->Edit1->Text);
         Ctrl->Establece_valor_parametro_metodo_integracion(met, 0,atof(txt1.c_str()));
         AnsiString txt2(vent->Edit2->Text);
         Ctrl->Establece_valor_parametro_metodo_integracion(met, 1,atof(txt2.c_str()));
         if (Ctrl->Retorna_tipo_parametros_metodo_integracion(met) == 2 || Ctrl->Retorna_tipo_parametros_metodo_integracion(met) == 3) {
            AnsiString txt3(vent->Edit3->Text);
            Ctrl->Establece_valor_parametro_metodo_integracion(met, 2,atof(txt3.c_str()));
            AnsiString txt4(vent->Edit4->Text);
            Ctrl->Establece_valor_parametro_metodo_integracion(met, 3,atof(txt4.c_str()));
         }   
         if (Ctrl->Retorna_tipo_parametros_metodo_integracion(met) == 3) {
            AnsiString txt5(vent->Edit5->Text);
            Ctrl->Establece_valor_parametro_metodo_integracion(met, 4,atof(txt5.c_str()));
         }
         AnsiString txt6(vent->Edit7->Text);
         Ctrl->Fija_cota_evitar_overflow(fabsl(atof(txt6.c_str())));
      }
      delete vent;
   }
}

// Menu->Métodos Numéricos->Configurar el Campo Vectorial en 2D
void __fastcall TVentanaTrabajo::CampoVectorial2Click(TObject *Sender)
{
   TCampoVectorial *vent = new TCampoVectorial(this);
   if (vent) {
      char xcad[100];
      long double numx, numy, tamx, tamy, ftH, ftNH;
      Ctrl->Retorna_configuracion_campo_vectorial(numx,numy,tamx,tamy);
      // Envia valores a la ventana
      sprintf(xcad,"%1.10Lf",numx);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",numy);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",tamx);
      vent->Edit3->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",tamy);
      vent->Edit4->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",Ctrl->Retorna_factor_ajuste_no_homogeneo());
      vent->Edit5->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",Ctrl->Retorna_factor_ajuste_homogeneo());
      vent->Edit6->Text = (AnsiString) xcad;
      vent->CheckBox1->Checked = Ctrl->Retorna_muestra_cabeza_vector();
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         numx = atof(txt1.c_str());
         AnsiString txt2(vent->Edit2->Text);
         numy = atof(txt2.c_str());
         AnsiString txt3(vent->Edit3->Text);
         tamx = atof(txt3.c_str());
         AnsiString txt4(vent->Edit4->Text);
         tamy = atof(txt4.c_str());
         AnsiString txt5(vent->Edit5->Text);
         ftNH = atof(txt5.c_str());
         AnsiString txt6(vent->Edit6->Text);
         ftH  = atof(txt6.c_str());
         if (ftNH <= 0.0) ftNH = 1.0;
         // Actualiza los valores
         Ctrl->Establece_configuracion_campo_vectorial(numx,numy,tamx,tamy,ftNH,ftH);
         Ctrl->Fija_muestra_cabeza_vector(vent->CheckBox1->Checked);
      }
      // Destruye la ventana
      delete vent;
   }
}


// Menu->Métodos Numéricos->Configurar el calculo de equilibrios
void __fastcall TVentanaTrabajo::Equilibriums2Click(TObject *Sender)
{
   TFormaParametrosEquilibrios *vent = new TFormaParametrosEquilibrios(this);
   if (vent) {
      char xcad[100];
      int num;
      long double max,min, pas, tiem;
      Ctrl->Retorna_configura_calculo_equilibrios(num,min,max,pas,tiem);
      // Envia valores a la ventana
      sprintf(xcad,"%1.10Lf",min);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",max);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%d",num);
      vent->Edit3->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",tiem);
      vent->Edit4->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",pas);
      vent->Edit5->Text = (AnsiString) xcad;
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         min = atof(txt1.c_str());
         AnsiString txt2(vent->Edit2->Text);
         max = atof(txt2.c_str());
         AnsiString txt3(vent->Edit3->Text);
         num = atoi(txt3.c_str());
         AnsiString txt4(vent->Edit4->Text);
         tiem = atof(txt4.c_str());
         AnsiString txt5(vent->Edit5->Text);
         pas = atof(txt5.c_str());
         Ctrl->Fija_configura_calculo_equilibrios(num,min,max,pas,tiem);
      }
      // Destruye la ventana
      delete vent;
   }
}


// Menu->Métodos Numéricos->Configurar el cálculo del período de taryectorias cerradas
void __fastcall TVentanaTrabajo::Period1Click(TObject *Sender)
{
   TPeriodoTrayectoriaCerrada *vent = new TPeriodoTrayectoriaCerrada(this);
   if (vent) {
      char xcad[100];
      // Envia valores a la ventana
      sprintf(xcad,"%3.10Lf", Tiempo_trayectoria_cerrada);
      vent->Edit1->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",Paso_trayectoria_cerrada);
      vent->Edit3->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",Tiempo_sin_checar_trayectoria_cerrada);
      vent->Edit2->Text = (AnsiString) xcad;
      sprintf(xcad,"%1.10Lf",Tolerancia_trayectoria_cerrada);
      vent->Edit4->Text = (AnsiString) xcad;
      // Muestra la ventana de captura
      vent->ShowModal();
      if (vent->Estado) {
         // Recupera valores de la ventana
         AnsiString txt1(vent->Edit1->Text);
         Tiempo_trayectoria_cerrada = atof(txt1.c_str());
         AnsiString txt2(vent->Edit3->Text);
         Paso_trayectoria_cerrada = atof(txt2.c_str());
         AnsiString txt3(vent->Edit2->Text);
         Tiempo_sin_checar_trayectoria_cerrada = atof(txt3.c_str());
         AnsiString txt4(vent->Edit4->Text);
         Tolerancia_trayectoria_cerrada = atof(txt4.c_str());
      }
      // Destruye la ventana
      delete vent;
   }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Escenario

// Menu->Escenario->Selección del escenario grafico Normal
void __fastcall TVentanaTrabajo::EscenarioGraficoClick(TObject *Sender)
{
   TEscenarios *vent = new TEscenarios(this);
   if (vent) {
      char xcad[100];
      vent->ListaHorizontal->Items->Clear();
      vent->ListaVertical->Items->Clear();
      vent->ListaTercerEje->Items->Clear();
      vent->ListaTercerEje->Items->Add(VVTXT06);
      for (int i = 0; i < Ctrl->Retorna_numero_ecuaciones_sistema(); i++) {
          Ctrl->Retorna_variable_ecuacion_sistema_activo(i+1,xcad);
          vent->ListaHorizontal->Items->Add(xcad);
          vent->ListaVertical->Items->Add(xcad);
          vent->ListaTercerEje->Items->Add(xcad);
      }
      vent->ListaHorizontal->Items->Add(VVTXT07);
      vent->ListaVertical->Items->Add(VVTXT07);
      vent->ListaTercerEje->Items->Add(VVTXT07);
      vent->ListaHorizontal->ItemIndex = Ctrl->Retorna_esenario_activo(1)-1;
      vent->ListaVertical->ItemIndex = Ctrl->Retorna_esenario_activo(2)-1;
      vent->ListaTercerEje->ItemIndex = Ctrl->Retorna_esenario_activo(3);
      vent->ShowModal();
      if (vent->Estado) {
         Ctrl->Fija_visualizacion_simultanea(false);
         Ctrl->Establece_esenario_activo(1,vent->ListaHorizontal->ItemIndex + 1);
         Ctrl->Establece_esenario_activo(2,vent->ListaVertical->ItemIndex + 1);
         Ctrl->Establece_esenario_activo(3,vent->ListaTercerEje->ItemIndex);
         Ctrl->Actualiza_escenario();
      }
      delete vent;
   }
   Borra_Archivos_ventana();
}


// Menu->Escenario->Curso Temporal->Normal
void __fastcall TVentanaTrabajo::CursoTemporalNormalClick(TObject *Sender)
{
   TEscenarios *vent = new TEscenarios(this);
   if (vent) {
      char xcad[100];
      vent->ListaHorizontal->Items->Clear();
      vent->ListaVertical->Items->Clear();
      vent->ListaTercerEje->Items->Clear();
      vent->ListaTercerEje->Items->Add(VVTXT06);
      for (int i = 0; i < Ctrl->Retorna_numero_ecuaciones_sistema(); i++) {
          Ctrl->Retorna_variable_ecuacion_sistema_activo(i+1,xcad);
          vent->ListaHorizontal->Items->Add(xcad);
          vent->ListaVertical->Items->Add(xcad);
          vent->ListaTercerEje->Items->Add(xcad);
      }
      vent->ListaHorizontal->Items->Add(VVTXT07);
      vent->ListaTercerEje->Items->Add(VVTXT07);
      vent->ListaHorizontal->ItemIndex = Ctrl->Retorna_numero_ecuaciones_sistema();
      vent->ListaVertical->ItemIndex = Ctrl->Retorna_esenario_activo(1)-1;
      vent->ListaTercerEje->ItemIndex = 0;
      vent->ListaTercerEje->Enabled = false;
      vent->ListaHorizontal->Enabled = false;
      vent->ShowModal();
      if (vent->Estado) {
         Ctrl->Fija_visualizacion_simultanea(false);
         Ctrl->Establece_esenario_activo(1,vent->ListaHorizontal->ItemIndex + 1);
         Ctrl->Establece_esenario_activo(2,vent->ListaVertical->ItemIndex + 1);
         Ctrl->Establece_esenario_activo(3,vent->ListaTercerEje->ItemIndex);
         Ctrl->Actualiza_escenario();
      }
      delete vent;
   }
   Borra_Archivos_ventana();
   // Actualiza la dimension del tiempo para empezar en cero
   Dimension_Ventana  dim;
   long double todos = 0.0, factor = 0.0;
   Ctrl->Retorna_dimensiones_sistema(dim);
   dim.Xi = 0.0;
   Ctrl->Establece_dimensiones_sistema(dim, todos, factor);
   Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
   Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   // Fija el escenario de ejes coordenados en 2D modificados
   Ctrl->Establece_tipo_ventana(EJES_COORDENADOS_2DM);
}

// Menu->Escenario->Curso Temporal->Simultaneos
void __fastcall TVentanaTrabajo::CursoTemporalSimultaneousClick(
      TObject *Sender)
{
   AnsiString escenarios = (AnsiString) "1,2";

   if (InputQuery(VVTXT26,VVTXT27, escenarios)) {
      int Arr[NUMERO_ECUACIONES], num_elem, i, xi;
      char xcad[1000], xcad1[1000];
      memccpy(xcad, escenarios.c_str(),0,999);
      for (i = 0; i < Ctrl->Retorna_numero_ecuaciones_sistema(); i++) Arr[i] = 0;
      num_elem = 0;
      i = 0, xi = 0;
      Cadenas cd;
      cd.Expander_Cadena_numerica_entera(escenarios.c_str(),xcad);
      while(xcad[i]) {
         if (xcad[i] != ',') xcad1[xi] = xcad[i], xi++;
          else {
            xcad1[xi] = 0;
            Arr[num_elem] = atoi(xcad1);
            num_elem++;
            xi = 0;
         }
         i++;
      }
      xcad1[xi] = 0;
      Arr[num_elem] = atoi(xcad1);
      num_elem++;
      Ctrl->Fija_numero_escenarios_visualizar(num_elem);
      Ctrl->Fija_escenarios_visualizar(Arr);
      // Actualiza la dimension del tiempo para empezar en cero
      Dimension_Ventana  dim;
      long double todos = 0.0, factor = 0.0;
      Ctrl->Retorna_dimensiones_sistema(dim);
      dim.Xi = 0.0;
      Ctrl->Establece_dimensiones_sistema(dim, todos, factor);
      Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
      Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
      Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
      // Actualiza el escenario actual
      Ctrl->Actualiza_escenario();
      Ctrl->Condiciones_iniciales_al_origen();
   }
   Borra_Archivos_ventana();
//   Ctrl_tareas(LIMPIA_VENTANA_SIN_CONSERVAR_CONDICION_INICIAL);
//   Ctrl->Condiciones_iniciales_al_origen();
}


// Activa la rotación de ejes coordenados
void __fastcall TVentanaTrabajo::EscenarioRotacionesClick(TObject *Sender)
{
   Rotando_ejes = true;
}

  
// Menu->Escenario->Cambia la graficación de puntos a lineas y viceversa
void __fastcall TVentanaTrabajo::GraficarconPuntosolineas1Click(TObject *Sender)
{
   Ctrl->Establece_grafica_puntos_o_lineas(!Ctrl->Retorna_grafica_puntos_o_lineas());
   if (Ctrl->Retorna_grafica_puntos_o_lineas()) GraficarconPuntosolineas1->Caption = VVTXT08;
    else GraficarconPuntosolineas1->Caption = VVTXT09;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Ayuda

// Menu->Ayuda->Ventana de ayuda
void __fastcall TVentanaTrabajo::Ventana1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,AYUDAINTEGRA);
      Ayuda->ShowModal();
      delete Ayuda;
   }
}

// Menu->Ayuda->Funciones validas
void __fastcall TVentanaTrabajo::FuncionesValidas1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo(TituloAplicacion,AYUDAFUNCIONES);
      Ayuda->ShowModal();
      delete Ayuda;
   }
}


// Menu->Ayuda->Acerca de ...
void __fastcall TVentanaTrabajo::About1Click(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}


// Pop Menu->Configura el color de la integración
void __fastcall TVentanaTrabajo::Colorofintegration1Click(TObject *Sender)
{
   ColorDialog->Color = Ctrl->Retorna_color_integracion(); 
   if (ColorDialog->Execute()) Ctrl->Fija_color_integracion(ColorDialog->Color); 
}




void __fastcall TVentanaTrabajo::VVentanaTrabajoMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2D || Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2DM || Ctrl->Retorna_tipo_ventana() == EJES_CAJA_2D || Ctrl->Retorna_tipo_ventana() == VENTANA_2D || Ctrl->Retorna_tipo_ventana() == EJES_COORDENADAS_POLARES) {
      if (Sw_Doble_click) return;
      if (Sw_Recuadro_activo) {
         if (Button == mbLeft) {
            Vt2.Xf = Vt1.Xf = Vt2.Xi = Vt1.Xi = X;
            Vt2.Yf = Vt1.Yf = Vt2.Yi = Vt1.Yi = Y;
            Sw_Dibuja_rectangulo = true;
            Sw_Dibuja_rectangulo_ant = false;
            Ventana_seleccionada = false;
            Sw_VisualizaTextoBarraEstados = false;
         }
      }
   }
}

void __fastcall TVentanaTrabajo::VVentanaTrabajoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   if (!Sw_calculo_en_proceso) Sw_Doble_click = false;
   if (Sw_Recuadro_activo) {
      if (Sw_Dibuja_rectangulo) {
         TPenMode mode;

         mode = VVentanaTrabajo->Canvas->Pen->Mode;
         VVentanaTrabajo->Canvas->Pen->Mode = pmNot;
      
         if (Sw_Dibuja_rectangulo_ant) {
            VVentanaTrabajo->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VVentanaTrabajo->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
            VVentanaTrabajo->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VVentanaTrabajo->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VVentanaTrabajo->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VVentanaTrabajo->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VVentanaTrabajo->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VVentanaTrabajo->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         }
         VVentanaTrabajo->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VVentanaTrabajo->Canvas->LineTo(X,Vt1.Yi);
         VVentanaTrabajo->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VVentanaTrabajo->Canvas->LineTo(Vt1.Xi,Y);
         VVentanaTrabajo->Canvas->MoveTo(X,Y);
         VVentanaTrabajo->Canvas->LineTo(Vt1.Xi,Y);
         VVentanaTrabajo->Canvas->MoveTo(X,Y);
         VVentanaTrabajo->Canvas->LineTo(X,Vt1.Yi);
      
         Vt2.Xf = X;
         Vt2.Yf = Y;
         VVentanaTrabajo->Canvas->Pen->Mode = mode;
         Sw_Dibuja_rectangulo_ant = true;

         // Ajusta a que xVt tenga el inicio y el final de la ventana
         xVt.Xi = Vt1.Xi, xVt.Xf = Vt2.Xf, xVt.Yi = Vt1.Yi, xVt.Yf = Vt2.Yf;
         int  xtmp;
         if (xVt.Xi > xVt.Xf) xtmp = xVt.Xi, xVt.Xi = xVt.Xf, xVt.Xf = xtmp;
         if (xVt.Yi > xVt.Yf) xtmp = xVt.Yi, xVt.Yi = xVt.Yf, xVt.Yf = xtmp;
         // Ajusta los valores a la longitud de la ventana
         if (xVt.Xi < 0) xVt.Xi = 0;
         if (xVt.Yi < 0) xVt.Yi = 0;
         if (xVt.Xf > VVentanaTrabajo->Width) xVt.Xf = VVentanaTrabajo->Width;
         if (xVt.Yf > VVentanaTrabajo->Height) xVt.Yf = VVentanaTrabajo->Height;
         // Visualiza los valores de la region seleccionada segun la dimención de la ventana
         Vs.Xi = xVt.Xi / Escala1.X + Dim_Vtn.Xi;
         Vs.Yi = ((VVentanaTrabajo->Height - xVt.Yi) / Escala1.Y) + Dim_Vtn.Yi;
         Vs.Xf = xVt.Xf / Escala1.X + Dim_Vtn.Xi;
         Vs.Yf = ((VVentanaTrabajo->Height - xVt.Yf) / Escala1.Y) + Dim_Vtn.Yi;
         char xcad[300];
         Ctrl->Ajusta_dimension_escala(Vs);
         sprintf(xcad,"(%3.5Lf, %3.5Lf, %3.5Lf, %3.5Lf)",Vs.Xi,Vs.Yf,Vs.Xf,Vs.Yi);
         BarraEstados->SimpleText = (AnsiString) xcad;
      } else {
         Vs.Xf = X, Vs.Yf = Y;
         Vs.Xi = Vs.Xf / Escala1.X + Dim_Vtn.Xi;
         Vs.Yi = (-(Vs.Yf - VVentanaTrabajo->Height) / Escala1.Y) + Dim_Vtn.Yi;
         Ctrl->Ajusta_dimension_escala(Vs);
      }    
   }
}

void __fastcall TVentanaTrabajo::VVentanaTrabajoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Doble_click) return;
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         TPenMode mode;
         mode = VVentanaTrabajo->Canvas->Pen->Mode;
         VVentanaTrabajo->Canvas->Pen->Mode = pmNot;
         VVentanaTrabajo->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VVentanaTrabajo->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VVentanaTrabajo->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VVentanaTrabajo->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VVentanaTrabajo->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VVentanaTrabajo->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VVentanaTrabajo->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VVentanaTrabajo->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VVentanaTrabajo->Canvas->Pen->Mode = mode;
         Vt1.Xf = X;
         Vt1.Xf = Y;
         Sw_Dibuja_rectangulo = false;
         Sw_Dibuja_rectangulo_ant = false;
         BarraEstados->SimpleText = (AnsiString) " ";
         Ventana_seleccionada = true;
         // Revisa si realmente se solicito el zoom
         if (abs(Vt2.Xf - Vt2.Xi) > 5 && abs(Vt2.Yf - Vt2.Yi) > 5) {
            // Pregunta si se desea hacer el zoom
            if (MessageBox(Handle,V_TXT05,TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
               // Almacena las dimensiones actuales
               Dim_zoom[Ind_zoom] = Dim_Vtn;
               if ((Ind_zoom + 1) < NUM_MAX_DIM_ZOOM) Ind_zoom ++;
               MenuVentanaZoomOut->Enabled = true;

               long double incx = fabsl(Vs.Xf - Vs.Xi);
               long double incy = fabsl(Vs.Yf - Vs.Yi);
               long double inc  = (incx > incy ? incx : incy);
               // Actualiza las dimensiones de las ventanas de trabajo
               Ctrl->Retorna_dimensiones_sistema(Dim_Vtn);
               Dim_Vtn.Xi = Vs.Xi;
               Dim_Vtn.Yi = Vs.Yf;
               Dim_Vtn.Xf = Vs.Xf;
               Dim_Vtn.Yf = Vs.Yi;
               if (Zoom_manteniendo_aspecto) {
                  Dim_Vtn.Xf = Vs.Xi + inc;
                  Dim_Vtn.Yf = Vs.Yf + inc;
               }
               Ctrl->Establece_dimensiones_sistema(Dim_Vtn, 0.0, 0.0);
               // Calcula la escala de la ventana de visualización
               Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
               Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
            }
         }
      }
   }
   Sw_VisualizaTextoBarraEstados = true;
}

void __fastcall TVentanaTrabajo::FormResize(TObject *Sender)
{
   // Calcula la escala de la ventana de visualizacion
   Escala1.X = VVentanaTrabajo->Width / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = VVentanaTrabajo->Height / (Dim_Vtn.Yf - Dim_Vtn.Yi);
}


// Integra con condición inicial seleccionada por el mouse
void __fastcall TVentanaTrabajo::VVentanaTrabajoDblClick(TObject *Sender)
{
   if (Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2D || Ctrl->Retorna_tipo_ventana() == EJES_COORDENADOS_2DM || Ctrl->Retorna_tipo_ventana() == EJES_CAJA_2D || Ctrl->Retorna_tipo_ventana() == VENTANA_2D || Ctrl->Retorna_tipo_ventana() == EJES_COORDENADAS_POLARES) {
      Sw_Doble_click = true;
      // Actualiza la condición inicial
      Ctrl->Establece_condiciones_iniciales(Ctrl->Retorna_esenario_activo(1) - 1,Vs.Xi);
      Ctrl->Establece_condiciones_iniciales(Ctrl->Retorna_esenario_activo(2) - 1,Vs.Yi);
      // Integra en tiempo positivo  
      Ctrl_tareas(INTEGRAR_TIEMPO_POSITIVO); 
      Sw_Dibuja_rectangulo = false;
   }
}









