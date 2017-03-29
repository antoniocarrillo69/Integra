//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana de Trabajo                                                                       //
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
#include <Buttons.hpp>
#include "Ctrl_estructura.hpp"

//---------------------------------------------------------------------------
class TVentanaTrabajo : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *BarraEstados;
        TMainMenu *MainMenu1;
        TMenuItem *MenuArchivos;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuArchivosCerrar;
        TTimer *Timer;
        TMenuItem *Ventana1;
        TMenuItem *N1;
        TMenuItem *About1;
        TPanel *Panel1;
        TSpeedButton *IconoNuevoSistema;
        TSpeedButton *IconoBorraSistema;
        TSpeedButton *IconoDuplicaSistema;
        TSpeedButton *IconoRenombraSistema;
        TSpeedButton *IconoImprimeSistema;
        TPanel *Panel2;
        TPageControl *PageControl2;
        TTabSheet *Systems;
        TSpeedButton *IconoGeneraEjecutable;
        TSpeedButton *IconoGrabarProyecto;
        TMenuItem *MenuSystems;
        TMenuItem *Save1;
        TMenuItem *SaveAs1;
        TMenuItem *N4;
        TMenuItem *New1;
        TMenuItem *Delete1;
        TMenuItem *Rename1;
        TMenuItem *Duplicate;
        TMenuItem *Print1;
        TMenuItem *Print2;
        TSaveDialog *SaveDialog1;
        TMenuItem *Funciones1;
        TMenuItem *Edit1;
        TMenuItem *Cut1;
        TMenuItem *Copy1;
        TMenuItem *Paste1;
        TMenuItem *Delete2;
        TMenuItem *Selectall1;
        TMenuItem *Undo1;
        TMenuItem *N2;
        TMenuItem *CopyAll1;
        TMenuItem *Make1;
        TMenuItem *MakeandSendEmail1;
        TMenuItem *MakeandSave1;
        TMenuItem *MakeandExecute1;
        TMenuItem *MakeOnlyCodeC1;
        TPanel *Panel3;
        TPageControl *BarraEdicion;
        TTabSheet *TabSheet1;
        TRichEdit *EditorEcuaciones;
        TTabSheet *TabSheet2;
        TRichEdit *EditorDescripcion;
        TTabSheet *TabSheet3;
        TRichEdit *EditorDescripcionProyecto;
        TTabSheet *CodigoEnC;
        TRichEdit *EditorCodigoC;
        TListBox *ListaSistemas;
        TMenuItem *Run1;
        TMenuItem *Exist1;
        TOpenDialog *OpenDialog2;
        void __fastcall MenuArchivosCerrarClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall Ventana1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall IconoNuevoSistemaClick(TObject *Sender);
        void __fastcall ListaSistemasClick(TObject *Sender);
        void __fastcall IconoBorraSistemaClick(TObject *Sender);
        void __fastcall IconoDuplicaSistemaClick(TObject *Sender);
        void __fastcall IconoRenombraSistemaClick(TObject *Sender);
        void __fastcall IconoImprimeSistemaClick(TObject *Sender);
        void __fastcall IconoGrabarProyectoClick(TObject *Sender);
        void __fastcall Print2Click(TObject *Sender);
        void __fastcall SaveAs1Click(TObject *Sender);
        void __fastcall Funciones1Click(TObject *Sender);
        void __fastcall Cut1Click(TObject *Sender);
        void __fastcall Copy1Click(TObject *Sender);
        void __fastcall Selectall1Click(TObject *Sender);
        void __fastcall Delete2Click(TObject *Sender);
        void __fastcall Paste1Click(TObject *Sender);
        void __fastcall BarraEdicionEnter(TObject *Sender);
        void __fastcall EditorDescripcionEnter(TObject *Sender);
        void __fastcall EditorDescripcionProyectoEnter(TObject *Sender);
        void __fastcall EditorCodigoCEnter(TObject *Sender);
        void __fastcall Undo1Click(TObject *Sender);
        void __fastcall CopyAll1Click(TObject *Sender);
        void __fastcall MakeandSendEmail1Click(TObject *Sender);
        void __fastcall MakeandSave1Click(TObject *Sender);
        void __fastcall MakeandExecute1Click(TObject *Sender);
        void __fastcall MakeOnlyCodeC1Click(TObject *Sender);
        void __fastcall Exist1Click(TObject *Sender);
private:	// User declarations
        bool                   Sw_calculo_en_proceso;
        bool                   Sw_cerrar_ventana;
        int                    Sistema_activo;
        int                    VentanaActiva;
        char                   ArchivoCPP[MAXPATH];
        char                   ArchivoHPP[MAXPATH];
        Ctrl_estructura       *Ctrl;
        

        void __fastcall        OnHint(TObject *Sender);
public:		// User declarations

        __fastcall             TVentanaTrabajo(TComponent* Owner);

                               // Asigna nuevo nombre al proyecto
        void                   Nombre_proyecto(const char *proy)
                               {
                                  Ctrl->Cambia_nombre_proyecto(proy);
                                  Actualiza_titulo_ventana();
                               }
                               // Actualiza el titulo de la ventana
        void                   Actualiza_titulo_ventana(void)
                               {
                                  Caption = Ctrl->Retorna_nombre_proyecto();
                               }
                               // Actuzliza el contenido del sistema
        void                   Actualiza_sistema(const int sis);
                               // Revisa si se modificarón los datos del proyecto
        void                   Revisa_modificacion_sistema(const int sis);
                               // Carga el proyecto indicado por NOMBRE
        void                   Carga_proyecto(const char *arch);
                               // Carga el contenido del sistema
        void                   Carga_sistema(const int sis);
                               // Genera el codigo del proyecto
        int                    Genera_CPP(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TVentanaTrabajo *VentanaTrabajo;
//---------------------------------------------------------------------------
#endif
