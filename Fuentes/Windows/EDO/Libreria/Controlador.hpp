//////////////////////////////////////////////////////////////////////////////////////////////
// Control del sistema                                                                      //
// Revisi�n: 16 de Abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001-2002                                                                  //
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



#ifndef __Controlador__
#define __Controlador__


#include "MetodosNumericos.hpp"


#define INTEGRA_POSITIVAMENTE     1
#define INTEGRA_NEGATIVAMENTE     0



/////////////////////////////////////////////////////////////
//                                                         //
//   Controlador del sistema Bifurca                       //
//                                                         //
/////////////////////////////////////////////////////////////

class Controlador: public Metodos_Numericos
{
   private:

                    // Limpia la ventana de trabajo
      void          Limpiar(void) 
                    {
                       Guarda_posicion = false;
                       Base_Ventana_Graficacion::Limpiar();
                       Poner_cursor();
                    }

   public:


      /////////////////////////////////////////////////////////////////////////////////////////////
      // Varias
      /////////////////////////////////////////////////////////////////////////////////////////////
   

      void          Inicializa(void)
                    {
                       Metodos_Numericos::Inicializa();
                    }

      void          Activa_visualizacion_cursor()
                    {
                       Actualiza_condicion_inicial();
                       Establecer_visualizar_cursor(true);
                       Poner_cursor();
                    }
                    
      
      /////////////////////////////////////////////////////////////////////////////////////////////
      // Sistemas
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Establece el sistema activo
      void          Establece_sistema_activo(const int sistema)
                    {
                       Establece_numero_sistema_actual(sistema);
                       Establece_Dimensiones(Dimensiones[Sistema_actual]);
                       Actualiza_escenario();
                    }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // Calcular
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Integra en tiempo positivo
      void          Integra_tiempo_positivo(void)
                    {
                       Integra_numericamente(INTEGRA_POSITIVAMENTE);
                       Guarda_posicion = true;
                       Poner_cursor();
                    }

                    // Integra en tiempo negativo
      void          Integra_tiempo_negativo(void)
                    {
                       Integra_numericamente(INTEGRA_NEGATIVAMENTE);
                       Guarda_posicion = true;
                       Poner_cursor();
                    }


                    // Mapeo del per�odo en tiempo positivo
      void          Mapeo_periodo_tiempo_positivo(const int veces)
                    {
                       Mapeo_periodo(INTEGRA_POSITIVAMENTE, veces);
                       Guarda_posicion = true;
                       Poner_cursor();
                    }

                    // Mapeo del per�odo en tiempo negativo
      void          Mapeo_periodo_tiempo_negativo(const int veces)
                    {
                       Mapeo_periodo(INTEGRA_NEGATIVAMENTE,veces);
                       Guarda_posicion = true;
                       Poner_cursor();
                    }
                    
       int          Dibuja_campo_vectorial(void)
                    {
                       int res = Metodos_Numericos_Campo_Vectorial::Dibuja_campo_vectorial();
                       Poner_cursor();
                       return res;
                    }             

       int          Dibuja_campo_direccional(void)
                    {
                       int res = Metodos_Numericos_Campo_Vectorial::Dibuja_campo_direccional();
                       Poner_cursor();
                       return res;
                    }             

       int          Dibuja_isoclina(const long double val)
                    {
                       int res = Metodos_Numericos_Isoclinas::Calcula_isoclinas(val);
                       Poner_cursor();
                       return res;
                    }             

       int          Calculo_equilibrios(void)
                    {
                       int res = Metodos_Numericos_Calculo_Equilibrios::Calculo_equilibrios();
                       Poner_cursor();
                       return res;
                    }               

      /////////////////////////////////////////////////////////////////////////////////////////////
      // Par�metros
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Retorna a los parametros originales del sistema
      void          Parametros_originales(void)
                    {
                       Sistemas::Parametros(Sistema_actual);
                       Sistemas::Limpiar_variables(Sistema_actual);
                       Limpiar_ventana_sin_conservar_condicion_inicial();
                    }

                    // Limpia los parametros usados como variables
      void          Parametros_limpiar_variables(void)
                    {
                       Sistemas::Limpiar_variables(Sistema_actual);
                       Limpiar_ventana_sin_conservar_condicion_inicial();
                    }

      /////////////////////////////////////////////////////////////////////////////////////////////
      // Cursor
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Cursor al origen
      void          Cursor_al_origen(void)
                    {
                       Condiciones_iniciales_al_origen();
                       Poner_cursor();
                    }

                    // Cursor al centro de la ventana
      void          Cursor_al_centro_ventana(void)
                    {
                       Condiciones_iniciales_al_centro_ventana();
                       Poner_cursor();
                    }

                    // Incrementa la condicion inicial
      void          Condicion_inicial(const int x, const int y, const int z);

      /////////////////////////////////////////////////////////////////////////////////////////////
      // Ventana
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Retorna las dimensiones del sistema actual
      void          Establece_dimensiones_sistema(Dimension_Ventana dim, const long double todos, const long double factor);
   
                    // Limpia la ventana conservando la condici�n inicial
      void          Limpiar_ventana_conservado_condicion_inicial(void)
                    {
                       Limpiar();
                       Dibuja();
                       Guarda_posicion = true;
                    }

                    // Limpia la ventana sin conservar la condici�n inicial
      void          Limpiar_ventana_sin_conservar_condicion_inicial(void)
                    {
                       Limpiar();
                       Dibuja();
                    }

                    // Establece el tipo de ventana activo
      void          Establece_tipo_ventana(const int tp)
                    {
                       // Activa el nuevo tipo de ventana
                       Tipo_ventana_activa(tp);
                       // Limpia el �rea de visualizaci�n
                       Limpiar();
                       // Dibuja los ejes coordenados
                       Dibuja();
                       // Visualiza el cursor
                       Poner_cursor();
                    }

                    // Actualiza el escenario Grafico
      void          Actualiza_escenario(void);

      /////////////////////////////////////////////////////////////////////////////////////////////
      // Ventana
      /////////////////////////////////////////////////////////////////////////////////////////////

                    // Imprime el estado del proyecto
      void          Imprime_estado(const int tr);
                    // Graba la configuraci�n del sistema con el nombre indicado
      void          Graba_configuracion(const char *xarch);
                    // Lee la configuraci�n del sistema con el nombre indicado
                    // Si tp es (-1) restaura la configuraci�n de todos los sistemas
                    //          (n)  restaura la configuraci�n del sistema n
                    // si RS es (99) restaura toda la configuraci�n
                    //          (1)  par�metros
                    //          (2)  condiciones iniciales
                    //          (3)  m�todos num�ricos
                    //          (4)  dimensiones
                    //          (5)  escenarios
      int           Lee_configuracion(const char *archivo, const int tp, const int rs);

};



#endif
