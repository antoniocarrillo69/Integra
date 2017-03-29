//////////////////////////////////////////////////////////////////////////////////////////////
// M�todos de Isoclinas                                                                     //
// Revisi�n: 9 de Noviembre del 2001                                                        //
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


#ifndef __MetodosIsoclinas__
#define __MetodosIsoclinas__


#include "BaseMetodosNumericos.hpp"


// M�todos num�ricos para el c�lculo de Isoclinas
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
