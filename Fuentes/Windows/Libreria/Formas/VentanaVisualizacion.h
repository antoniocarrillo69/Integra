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
#ifndef VentanaVisualizacionH
#define VentanaVisualizacionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "Controlador.hpp"
#include <NMsmtp.hpp>
#include <Psock.hpp>


#define  P_SISTEMAS                 1
#define  P_PARAMETROS               2
#define  P_EJES_2D                  3
#define  P_DIMENSIONES              4
#define  P_METODOSNUMERICOS         5
#define  P_ESCENARIOGRAFICO         6
#define  P_CAMPOVECTORIAL           7
#define  P_CAMPODIRECCIONAL         8
#define  P_CONDICIONESINICIALES     9
#define  P_INTEGRATIEMPONEGATIVO    10
#define  P_INTEGRATIEMPOPOSITIVO    11
#define  P_LIMPIARVENTANA           12
#define  P_GRFICAPUNTOSLINEAS       13


#define NUM_MAX_DIM_ZOOM      10


//---------------------------------------------------------------------------
class TVentanaTrabajo : public TForm 
{
__published:	// IDE-managed Components
        TStatusBar *BarraEstados;
        TMainMenu *MainMenu1;
        TMenuItem *MenuArchivos;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuArchivosCerrar;
        TTimer *TimeTareas;
        TMenuItem *Ventana1;
        TMenuItem *N1;
        TMenuItem *About1;
        TMenuItem *N2;
        TMenuItem *SaveWindowBMPFormat1;
        TMenuItem *Print1;
        TSavePictureDialog *SaveDialog;
        TPanel *Marco;
        TPaintBox *VVentanaTrabajo;
        TMenuItem *Sistemas1;
        TMenuItem *ReporteEstado1;
        TMenuItem *Descripcin1;
        TMenuItem *Biblioteca1;
        TMenuItem *Calcular1;
        TMenuItem *CampoVectorial1;
        TMenuItem *FuncionesAuxiliares1;
        TMenuItem *MCeroclinas;
        TMenuItem *MapeodePoincare1;
        TMenuItem *Bifurcaciones1;
        TMenuItem *N5;
        TMenuItem *IntegraTNegativo1;
        TMenuItem *IntegraTPositivo1;
        TMenuItem *Parametros1;
        TMenuItem *Originales1;
        TMenuItem *Modificar1;
        TMenuItem *Cursor1;
        TMenuItem *IncrementodelCursor1;
        TMenuItem *PasodelCursor1;
        TMenuItem *Moveralorigen1;
        TMenuItem *Movera1;
        TMenuItem *Ventana2;
        TMenuItem *Ver1;
        TMenuItem *Coordenadascursor1;
        TMenuItem *Nombredeejes1;
        TMenuItem *Colores1;
        TMenuItem *Tipodeescenario1;
        TMenuItem *CoordenadasPolares;
        TMenuItem *Caja3D;
        TMenuItem *Caja2D;
        TMenuItem *Ejes3D;
        TMenuItem *Ejes2D;
        TMenuItem *N6;
        TMenuItem *LimpiarconsPosicion1;
        TMenuItem *LimpiarsinConsPosicion1;
        TMenuItem *Dimensiones1;
        TMenuItem *MetodosNumericos1;
        TMenuItem *Bifurcaciones2;
        TMenuItem *Integracin1;
        TMenuItem *Escenario1;
        TMenuItem *EscenarioRotaciones;
        TMenuItem *AcercarAlejar1;
        TMenuItem *Moverorigen1;
        TMenuItem *EscenarioGrafico;
        TMenuItem *GraficarconPuntosolineas1;
        TMenuItem *N3;
        TMenuItem *CampoVectorial2;
        TMenuItem *CalcularCeroclinas;
        TMenuItem *CalcularIsoclinas;
        TMenuItem *PuntosaGraficar1;
        TMenuItem *Graficar1;
        TMenuItem *Puntos1;
        TMenuItem *FuncionAuxuliar11;
        TMenuItem *FuncionAuxuliar21;
        TMenuItem *FuncionAuxuliar31;
        TMenuItem *FuncionAuxuliar41;
        TMenuItem *FuncionAuxuliar51;
        TMenuItem *FuncionAuxuliar61;
        TMenuItem *FuncionAuxuliar71;
        TMenuItem *FuncionAuxuliar81;
        TMenuItem *FuncionAuxuliar91;
        TMenuItem *FuncionAuxuliarSeparador;
        TMenuItem *DetenerClculo1;
        TMenuItem *FuncionesValidas1;
        TMenuItem *DirectionalField1;
        TMenuItem *GrabarConfiguracin1;
        TMenuItem *LeerConfiguracin1;
        TMenuItem *N8;
        TMenuItem *MenuArchivosGrabarIntegraciones;
        TSaveDialog *SaveDialogReport;
        TMenuItem *N9;
        TMenuItem *MenuVentanaBorrarultimaintegracin;
        TSaveDialog *SaveDialogConfiguracion;
        TOpenDialog *OpenDialogConfiguracion;
        TMenuItem *N10;
        TMenuItem *CopyConfiguration1;
        TMenuItem *PastConfiguration1;
        TMenuItem *ReportedeEstado1;
        TMenuItem *RestauraConfiguracinProyecto1;
        TMenuItem *N11;
        TMenuItem *GraduarEjesCoordenados1;
        TTimer *TimerActivaDesactivaMenus;
        TMenuItem *Equilibriums1;
        TMenuItem *Equilibriums2;
        TMenuItem *Ejes2DM;
        TMenuItem *N12;
        TMenuItem *PeriodofTrajectoryClosed1;
        TMenuItem *PeridMap1;
        TMenuItem *ForwardPeriodMap1;
        TMenuItem *BackwardPeriodMap2;
        TMenuItem *ForwardTrajectory1;
        TMenuItem *BackwardsTrajectory1;
        TMenuItem *Period1;
        TMenuItem *ActivaRecuperaciondeestadoantesdecalcular1;
        TMenuItem *N4;
        TMenuItem *ParametrosClear;
        TPopupMenu *PopupMenu1;
        TMenuItem *Colorofintegration1;
        TColorDialog *ColorDialog;
        TMenuItem *SetInitCondandIntegrate1;
        TMenuItem *Ventana2D;
        TMenuItem *N7;
        TMenuItem *MovetoMiddlePointofWindow1;
        TTimer *TimerVisualizaBarraEstados;
        TMenuItem *N13;
        TMenuItem *Caja3DM;
        TMenuItem *MenuVentanaZoomOut;
        TMenuItem *OriginalDimension1;
        TMenuItem *CursoTemporal;
        TMenuItem *CursoTemporalNormal;
        TMenuItem *CursoTemporalSimultaneous;
        void __fastcall MenuArchivosCerrarClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall TimeTareasTimer(TObject *Sender);
        void __fastcall Ventana1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall SaveWindowBMPFormat1Click(TObject *Sender);
        void __fastcall Print1Click(TObject *Sender);
        void __fastcall VVentanaTrabajoPaint(TObject *Sender);
        void __fastcall LimpiarsinConsPosicion1Click(TObject *Sender);
        void __fastcall LimpiarconsPosicion1Click(TObject *Sender);
        void __fastcall IntegraTPositivo1Click(TObject *Sender);
        void __fastcall IntegraTNegativo1Click(TObject *Sender);
        void __fastcall Moveralorigen1Click(TObject *Sender);
        void __fastcall Originales1Click(TObject *Sender);
        void __fastcall Biblioteca1Click(TObject *Sender);
        void __fastcall CalcularIsoclinasClick(TObject *Sender);
        void __fastcall CampoVectorial1Click(TObject *Sender);
        void __fastcall GraficarconPuntosolineas1Click(TObject *Sender);
        void __fastcall Ejes2DClick(TObject *Sender);
        void __fastcall Caja2DClick(TObject *Sender);
        void __fastcall Integracin1Click(TObject *Sender);
        void __fastcall Modificar1Click(TObject *Sender);
        void __fastcall Movera1Click(TObject *Sender);
        void __fastcall PasodelCursor1Click(TObject *Sender);
        void __fastcall IncrementodelCursor1Click(TObject *Sender);
        void __fastcall Dimensiones1Click(TObject *Sender);
        void __fastcall CampoVectorial2Click(TObject *Sender);
        void __fastcall Descripcin1Click(TObject *Sender);
        void __fastcall ReporteEstado1Click(TObject *Sender);
        void __fastcall Colores1Click(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Ejes3DClick(TObject *Sender);
        void __fastcall Caja3DClick(TObject *Sender);
        void __fastcall CoordenadasPolaresClick(TObject *Sender);
        void __fastcall CalcularCeroclinasClick(TObject *Sender);
        void __fastcall PuntosaGraficar1Click(TObject *Sender);
        void __fastcall Graficar1Click(TObject *Sender);
        void __fastcall Puntos1Click(TObject *Sender);
        void __fastcall Nombredeejes1Click(TObject *Sender);
        void __fastcall Coordenadascursor1Click(TObject *Sender);
        void __fastcall FuncionAuxuliar11Click(TObject *Sender);
        void __fastcall FuncionAuxuliar21Click(TObject *Sender);
        void __fastcall FuncionAuxuliar31Click(TObject *Sender);
        void __fastcall FuncionAuxuliar41Click(TObject *Sender);
        void __fastcall FuncionAuxuliar51Click(TObject *Sender);
        void __fastcall FuncionAuxuliar61Click(TObject *Sender);
        void __fastcall FuncionAuxuliar71Click(TObject *Sender);
        void __fastcall FuncionAuxuliar81Click(TObject *Sender);
        void __fastcall FuncionAuxuliar91Click(TObject *Sender);
        void __fastcall DetenerClculo1Click(TObject *Sender);
        void __fastcall FuncionesValidas1Click(TObject *Sender);
        void __fastcall DirectionalField1Click(TObject *Sender);
        void __fastcall MenuArchivosGrabarIntegracionesClick(TObject *Sender);
        void __fastcall MenuVentanaBorrarultimaintegracinClick(TObject *Sender);
        void __fastcall GrabarConfiguracin1Click(TObject *Sender);
        void __fastcall LeerConfiguracin1Click(TObject *Sender);
        void __fastcall CopyConfiguration1Click(TObject *Sender);
        void __fastcall PastConfiguration1Click(TObject *Sender);
        void __fastcall ReportedeEstado1Click(TObject *Sender);
        void __fastcall RestauraConfiguracinProyecto1Click(
          TObject *Sender);
        void __fastcall EscenarioRotacionesClick(TObject *Sender);
        void __fastcall TimerActivaDesactivaMenusTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Equilibriums1Click(TObject *Sender);
        void __fastcall Equilibriums2Click(TObject *Sender);
        void __fastcall Ejes2DMClick(TObject *Sender);
        void __fastcall PeriodMapForward1Click(TObject *Sender);
        void __fastcall BackwardPeriodMap1Click(TObject *Sender);
        void __fastcall ForwardTrajectory1Click(TObject *Sender);
        void __fastcall BackwardsTrajectory1Click(TObject *Sender);
        void __fastcall Period1Click(TObject *Sender);
        void __fastcall ActivaRecuperaciondeestadoantesdecalcular1Click(
          TObject *Sender);
        void __fastcall ParametrosClearClick(TObject *Sender);
        void __fastcall Colorofintegration1Click(TObject *Sender);
        void __fastcall VVentanaTrabajoMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VVentanaTrabajoMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VVentanaTrabajoMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall VVentanaTrabajoDblClick(TObject *Sender);
        void __fastcall Ventana2DClick(TObject *Sender);
        void __fastcall MovetoMiddlePointofWindow1Click(TObject *Sender);
        void __fastcall TimerVisualizaBarraEstadosTimer(TObject *Sender);
        void __fastcall Caja3DMClick(TObject *Sender);
        void __fastcall MenuVentanaZoomOutClick(TObject *Sender);
        void __fastcall OriginalDimension1Click(TObject *Sender);
        void __fastcall CursoTemporalNormalClick(TObject *Sender);
        void __fastcall CursoTemporalSimultaneousClick(TObject *Sender);
        void __fastcall EscenarioGraficoClick(TObject *Sender);
private:	// User declarations
        bool                   Sw_calculo_en_proceso;
        bool                   Sw_cerrar_ventana;
        bool                   Sw_cancela_calculo;
        bool                   Sw_activo_visualizacion_cursor;
        bool                   Sw_visualizacion_condiciones_iniciales;
        bool                   Sw_graba_ventana_antes_de_integrar;
        bool                   Genera_reporte_integracion;
        bool                   Rotando_ejes;
        char                   Funcion_auxiliar[1000];
        char                   Archivo_temporal[MAXPATH];
        char                   Archivo_integraciones[MAXPATH];
        int                    Veces_mapeo_periodo;
        long double            Periodo_trayectoria_cerrada;
        long double            Tiempo_trayectoria_cerrada;
        long double            Paso_trayectoria_cerrada;
        long double            Tiempo_sin_checar_trayectoria_cerrada;
        long double            Tolerancia_trayectoria_cerrada;
        long double            Valor_isoclina;
        
        // Variables necesarias para dibujar recuadro de selecccion de una area 
        Definicion_Ventana     Vt1, Vt2, xVt;
        Dimension_Ventana      Vs;
        bool                   Ventana_seleccionada;
        bool                   Sw_Dibuja_rectangulo;
        bool                   Sw_Dibuja_rectangulo_ant;
        bool                   Sw_Recuadro_activo;
        bool                   Sw_Doble_click;
        bool                   Sw_VisualizaTextoBarraEstados;
        int                    Ind_zoom;
        Dimension_Ventana      Dim_zoom[NUM_MAX_DIM_ZOOM];
        Dimension_Ventana      Dim_orig;
        int                    Puntos_ventana_X;
        int                    Puntos_ventana_Y;
        bool                   Zoom_manteniendo_aspecto;

        C_2D                   Escala1; // Escala del gráfico
        Dimension_Ventana      Dim_Vtn;


        void __fastcall        OnHint(TObject *Sender);
        void                   Ctrl_tareas(const int tp);
        void                   Control_funciones_auxliares(const char *cad);
        void                   Activa_menu_funciones_auxiliares(void);
        void                   Graba_ventana(void);
        void                   Borra_Archivos_ventana(void);

public:		// User declarations
        __fastcall TVentanaTrabajo(TComponent* Owner);
        void                   Titulo_ventana(void);

        // Controlador de INTEGRA
        Controlador           *Ctrl;

};
//---------------------------------------------------------------------------
extern PACKAGE TVentanaTrabajo *VentanaTrabajo;
//---------------------------------------------------------------------------
#endif
