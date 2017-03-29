//////////////////////////////////////////////////////////////////////////////////////////////
// Métodos de Isoclinas                                                                     //
// Revisión: 9 de Noviembre del 2001                                                        //
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


#ifndef __MetodosIsoclinas__
#define __MetodosIsoclinas__


#include "BaseMetodosNumericos.hpp"


// Métodos numéricos para el cálculo de Isoclinas
class Metodos_Numericos_Isoclinas: virtual public Base_Metodos_Numericos
{
   private:
  
      // Numero de puntos a graficar para funciones auxiliares
      int            Numero_puntos;
      long double    Tolerancia;
      int            Max_iter;

      
   protected:
                     // Calcula la isoclina indicada
      int            Calcula_isoclinas(const long double valor);

      
   
   public:

                     // Inicializa la clase
      virtual void   Inicializa(void)
                     {
                       Numero_puntos = 5000;
                       Tolerancia = 1e-5;
                       Max_iter = 10000;
                     }

                     // Establece la cantidad de puntos a graficar
      void           Establece_puntos_graficar_isoclinas(const int num)
                     {
                         Numero_puntos = num;
                     }

                     // Retorna la cantidad de puntos a graficar
      int            Retorna_puntos_graficar_isoclinas(void)
                     {
                         return (Numero_puntos);
                     }
};


#endif
