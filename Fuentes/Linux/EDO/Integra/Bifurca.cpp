// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Direcci�n: Amsterdam 312 col. Hip�dromo Condesa
// Tel�fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr�mite 1999-2000
// Revisi�n  1.1-A

#include <vcl.h>
#pragma hdrstop
USEFORM("Acecade.cpp", VAcercaDe);
USEFORM("..\Libreria\Formas\VDColoresSistema.cpp", ColoresSistema);
USEFORM("..\Libreria\Formas\VDCondicionInicial.cpp", CondicionInicial);
USEFORM("..\Libreria\Formas\VDDimensiones.cpp", Dimensiones);
USEFORM("..\Libreria\Formas\VDEquilibrios.cpp", FormaParametrosEquilibrios);
USEFORM("..\Libreria\Formas\VDEscenarios.cpp", Escenarios);
USEFORM("..\Libreria\Formas\VDIncrementoPasoCursor.cpp", IncrementoPasoCursor);
USEFORM("..\Libreria\Formas\VDMetodosIntegracion.cpp", ConfiguracionMetodosIntegracion);
USEFORM("..\Libreria\Formas\VDParametros.cpp", Parametros);
USEFORM("..\Libreria\Formas\VDPasoCursor.cpp", PasoCursor);
USEFORM("..\Libreria\Formas\VDPeriodoTrayectoriaCerrada.cpp", PeriodoTrayectoriaCerrada);
USEFORM("..\Libreria\Formas\VDSistemas.cpp", SeleccionSistemas);
USEFORM("..\Libreria\Formas\VentanaVisualizacion.cpp", VentanaTrabajo);
USEFORM("..\Libreria\Formas\VDCampoVectorial.cpp", CampoVectorial);
USEFORM("..\..\Libreria\FORMAS\Lmensaje.cpp", LMensajeForm);
USEFORM("..\..\Libreria\FORMAS\Ayuda.cpp", AyudaForm);
USEFORM("..\..\Libreria\FORMAS\EnviarCorreo.cpp", FormaEnviarCorreo);
USEFORM("..\..\Libreria\FORMAS\ACX-WebBrowser.cpp", FormaWebBrowzer);
USEFORM("Principal.cpp", VentanaPrincipal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TVentanaPrincipal), &VentanaPrincipal);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
