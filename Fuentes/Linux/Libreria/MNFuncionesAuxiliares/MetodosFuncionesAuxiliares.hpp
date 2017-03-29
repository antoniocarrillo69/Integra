//////////////////////////////////////////////////////////////////////////////////////////////
// Métodos de graficación de funciones auxiliares                                           //
// Revisión: 16 de Octubre del 2001                                                         //
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
