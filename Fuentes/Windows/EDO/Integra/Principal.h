 //////////////////////////////////////////////////////////////////////////////////////////////
 // Ventana principal                                                                        //
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


#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TVentanaPrincipal : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MenuPrincipal;
        TMenuItem *MenuFile;
        TMenuItem *MenuArchivosSalir;
        TPanel *PanelIconos;
        TSpeedButton *IconoVentanaIntegra;
        TStatusBar *BarraEstadoPrincipal;
        TMenuItem *MenuHelp;
        TMenuItem *General1;
        TMenuItem *N1;
        TMenuItem *LaboratoriodeDinmicanoLinealUNAM1;
        TMenuItem *N2;
        TMenuItem *Aboutof1;
        TMenuItem *N3;
        TMenuItem *MenuArchivosEditaArchivos;
        TMenuItem *N4;
        TMenuItem *MenuArchivosPrintFileBMPFormat;
        TMenuItem *MenuArchivosPrinterSetup;
        TPrinterSetupDialog *PrinterSetupDialog;
        TOpenPictureDialog *OpenPictureDialog;
        TSpeedButton *IconoSistemas;
        TSpeedButton *IntegraTiempoNegativo;
        TSpeedButton *IntegraTiempoPositivo;
        TSpeedButton *IconoParametros;
        TSpeedButton *IconoDimensionVentana;
        TSpeedButton *IconoMetodosIntegracion;
        TSpeedButton *IconoEscenarioGrafico;
        TSpeedButton *IconoCampoVectorial;
        TSpeedButton *IconoCondicionInicial;
        TSpeedButton *IconoEjes2D;
        TSpeedButton *IconoLimpiaVentanaTrabajo;
        TSpeedButton *IconoGraficaPuntosLineas;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TMenuItem *N5;
        TMenuItem *DescripciondelProyecto1;
        TMenuItem *MenuEdit;
        TMenuItem *MenuEditCopy;
        TMenuItem *MenuEditPaste;
        void __fastcall MenuArchivosSalirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall General1Click(TObject *Sender);
        void __fastcall Aboutof1Click(TObject *Sender);
        void __fastcall MenuArchivosEditaArchivosClick(TObject *Sender);
        void __fastcall MenuArchivosPrintFileBMPFormatClick(
          TObject *Sender);
        void __fastcall MenuArchivosPrinterSetupClick(TObject *Sender);
        void __fastcall LaboratoriodeDinmicanoLinealUNAM1Click(
          TObject *Sender);
        void __fastcall IconoVentanaIntegraClick(TObject *Sender);
        void __fastcall IconoSistemasClick(TObject *Sender);
        void __fastcall IconoParametrosClick(TObject *Sender);
        void __fastcall IconoEjes2DClick(TObject *Sender);
        void __fastcall IconoDimensionVentanaClick(TObject *Sender);
        void __fastcall IconoMetodosIntegracionClick(TObject *Sender);
        void __fastcall IconoEscenarioGraficoClick(TObject *Sender);
        void __fastcall IconoCampoVectorialClick(TObject *Sender);
        void __fastcall IconoCondicionInicialClick(TObject *Sender);
        void __fastcall IntegraTiempoNegativoClick(TObject *Sender);
        void __fastcall IntegraTiempoPositivoClick(TObject *Sender);
        void __fastcall IconoLimpiaVentanaTrabajoClick(TObject *Sender);
        void __fastcall IconoGraficaPuntosLineasClick(TObject *Sender);
        void __fastcall DescripciondelProyecto1Click(TObject *Sender);
private:	// User declarations
        // Controla la visualizacion de Hint en la barra de estado
        void __fastcall OnHint(TObject *Sender);
public:		// User declarations
        __fastcall TVentanaPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVentanaPrincipal *VentanaPrincipal;
//---------------------------------------------------------------------------
#endif
