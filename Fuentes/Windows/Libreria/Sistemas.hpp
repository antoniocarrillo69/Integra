//////////////////////////////////////////////////////////////////////////////////////////////
// Definici�n de sistemas                                                                   //
// Revisi�n: 6 de Abril del 2001                                                            //
//                                                                                          //
// Copyright (C) 2001                                                                       //
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


#ifndef __SISTEMAS__
#define __SISTEMAS__


#include <string.h>
#include "Def_Usuario.hpp"

#define NUMERO_METODOS_NUMERICOS                             56   // Indica el n�mero de m�todos num�ricos en el sistema
#define NUMERO_MAXIMO_PARAMETROS_METODOS_INTEGRACION          6   // Indica el n�mero de par�metros en los m�todos num�ricos de integraci�n



class Sistemas: public Definicion_Usuario
{
   protected:

                         // Indica si esta activa la visualizacion simultanea
      bool               Visualizacion_simultanea[NUMERO_SISTEMAS];
                         // Indica los escenarios activos en la visualizacion simultanea
      int                Escenarios_visualizar[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
                         // Indica el numero de escenarios activos a visualuizar simultaneamente
      int                Numero_escenarios_visualizar[NUMERO_SISTEMAS];

      
                         // Indica el n�mero de par�metros del campo vectorial
      long double        Parametros_campo_vectorial[NUMERO_SISTEMAS][4];
                         // Factor para el campo direccional
      long double        Factor_direccional[NUMERO_SISTEMAS];
                         // Factor para el campo vectorial
      long double        Factor_vectorial[NUMERO_SISTEMAS];
                         // Indica si se muestra la cabeza del vector
      bool               Muestra_cabeza_vector[NUMERO_SISTEMAS];

      
      int                MAX_VALOR[NUMERO_SISTEMAS];
      long double        Ac_Condicion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
      long double        Ac_Tiempo[NUMERO_SISTEMAS];
      bool               Grafica_puntos[NUMERO_SISTEMAS];

      
                         // Parametros de los m�todos n�mericos
      long double        Parametros_metodo[NUMERO_SISTEMAS][NUMERO_METODOS_NUMERICOS][NUMERO_MAXIMO_PARAMETROS_METODOS_INTEGRACION];
                         // N�mero de par�metros del metodo numerico de integracion
      int                Tipo_parametros_metodo_integracion[NUMERO_METODOS_NUMERICOS];


                         // Dimensiones de la ventana de trabajo por cada sistema
      Dimension_Ventana  Dimensiones[NUMERO_SISTEMAS];

      
                         // Indica el paso del cursor
      C_3D               Paso_cursor[NUMERO_SISTEMAS];
                         // Indica el inclremento al paso del cursor
      C_3D               Incremento_paso_cursor[NUMERO_SISTEMAS];
      
      
   

   public:
   
                         // Retorna el nombre del sistema activo
      void               Nombre_sistema_activo(char *nombre)
                         {
                            strcpy(nombre,Nombre_sistema[Sistema_actual]);
                         }

                         // Retorna las dimensiones del sistema actual
      void               Retorna_dimensiones_sistema(Dimension_Ventana &dim)
                         {
                            dim = Dimensiones[Sistema_actual];
                         }
                         // Fija modo de visualizaci�n simultanea
      void               Fija_visualizacion_simultanea(const bool tv)
                         {
                            Visualizacion_simultanea[Sistema_actual] = tv;
                         }
                         // Fija en numero de escenarios a visualizar simultaneamente
      void               Fija_numero_escenarios_visualizar(const int num);

                         // Retorna el numero de escenarios a visualizar simultaneamente
      int                Retorna_numero_escenarios_visualizar(void)
                         {
                            return (Numero_escenarios_visualizar[Sistema_actual]);
                         }
                         // Fija los escenarios a visualizar simultaneamente
      void               Fija_escenarios_visualizar(const int num[]);
      
                         // Retorna los escenarios a visualizar simultaneamente
      int                Retorna_escenarios_visualizar(const int num)
                         {
                            return (Escenarios_visualizar[Sistema_actual][num]);
                         }
                         // Retorna el tipo de ecuaci�n del sistema actual
      int                Retorna_tipo_ecuacion(void)
                         {
                            return (Tipo_ecuacion[Sistema_actual]);
                         }
                         // Retorna el tipo de ecuaci�n del sistema i
      int                Retorna_tipo_ecuacion(const int i)
                         {
                            return (Tipo_ecuacion[i]);
                         }
};


#endif
