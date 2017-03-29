//////////////////////////////////////////////////////////////////////////////////////////////
// M�todos de graficaci�n de funciones auxiliares                                           //
// Revisi�n: 16 de Octubre del 2001                                                         //
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


#ifndef __MetodosFuncionesAuxiliares__
#define __MetodosFuncionesAuxiliares__


#include "BaseMetodosNumericos.hpp"
#include "../Libreria/Cadenas.hpp"



class Metodos_Numericos_FuncionesAuxiliares: virtual public Base_Metodos_Numericos
{
   public:

      int            NUMERO_PUNTOS;
      char           xcad[1000];
      
                     // Inicializa la clase
      virtual void   Inicializa(void)
                     {
                        NUMERO_PUNTOS = 5000;
                     }

                     // Grafica la funcion pasada como parametro
      void           Grafica_funcion_auxiliar(const char *exp, Dimension_Ventana vtn);

      void           Establece_puntos_graficar_funcion_auxiliar(const int num)
                     {
                         NUMERO_PUNTOS = num;
                     }

      int            Retorna_puntos_graficar_funcion_auxiliar(void)
                     {
                         return (NUMERO_PUNTOS);
                     }

      int            Retorna_numero_funcion_auxiliar_definida(void)
                     {
                        return (Numero_funciones_auxiliares[Sistema_actual]);
                     }
                     
      char          *Retorna_funcion_auxiliar_definida(const int i)
                     {
                        strcpy(xcad,"");
                        if(i <= Numero_funciones_auxiliares[Sistema_actual]) strcpy(xcad,Funciones_auxiliares[Sistema_actual][i-1]);
                        return xcad;
                     }

};


#endif
