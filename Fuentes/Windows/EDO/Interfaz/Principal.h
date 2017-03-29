//////////////////////////////////////////////////////////////////////////////////////////////
// Ventana Principal                                                                        //
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
        TMenuItem *MenuArchivos;
        TMenuItem *MenuArchivosSalir;
        TPanel *PanelIconos;
        TSpeedButton *IconoNewProyect;
        TStatusBar *BarraEstadoPrincipal;
        TMenuItem *Help1;
        TMenuItem *General1;
        TMenuItem *N1;
        TMenuItem *LaboratoriodeDinmicanoLinealUNAM1;
        TMenuItem *N2;
        TMenuItem *Aboutof1;
        TSpeedButton *IconoLoadProyect;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TMenuItem *Proyect1;
        TMenuItem *NewProyect1;
        TMenuItem *Load1;
        TMenuItem *Edit1;
        TMenuItem *Userrequest1;
        TMenuItem *ConfiguserEmail1;
        TSpeedButton *IconoRenombrarProyecto;
        TSpeedButton *IconoDuplicarProyecto;
        TSpeedButton *IconoBorrarProyecto;
        TSpeedButton *IconoEjecutaEXE;
        TMenuItem *Rename1;
        TMenuItem *Duplicate1;
        TMenuItem *Delete1;
        TMenuItem *N3;
        TMenuItem *ReloadUserrequest1;
        TMenuItem *Usuario0;
        TMenuItem *Usuario1;
        TMenuItem *Usuario2;
        TOpenDialog *OpenDialog2;
        void __fastcall MenuArchivosSalirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall General1Click(TObject *Sender);
        void __fastcall LaboratoriodeDinmicanoLinealUNAM1Click(
          TObject *Sender);
        void __fastcall Aboutof1Click(TObject *Sender);
        void __fastcall IconoNewProyectClick(TObject *Sender);
        void __fastcall IconoLoadProyectClick(TObject *Sender);
        void __fastcall Userrequest1Click(TObject *Sender);
        void __fastcall ConfiguserEmail1Click(TObject *Sender);
        void __fastcall IconoRenombrarProyectoClick(TObject *Sender);
        void __fastcall IconoDuplicarProyectoClick(TObject *Sender);
        void __fastcall IconoBorrarProyectoClick(TObject *Sender);
        void __fastcall Usuario0Click(TObject *Sender);
        void __fastcall Usuario1Click(TObject *Sender);
        void __fastcall Usuario2Click(TObject *Sender);
        void __fastcall IconoEjecutaEXEClick(TObject *Sender);
private:	// User declarations
        // Controla la visualizacion de Hint en la barra de estado
        void __fastcall OnHint(TObject *Sender);
        int  Usuario;

public:		// User declarations
        __fastcall TVentanaPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVentanaPrincipal *VentanaPrincipal;
//---------------------------------------------------------------------------
#endif
