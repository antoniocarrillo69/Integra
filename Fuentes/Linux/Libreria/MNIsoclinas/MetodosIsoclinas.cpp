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


#include "MetodosIsoclinas.hpp"
#include <math.h>



//////////////////////////////////////////////////////////////////////////
//                Grafica isoclinas del sistema actual                  //
//////////////////////////////////////////////////////////////////////////

// Métodos numéricos para el cálculo de Isoclinas
// (0) Calculo correctamente
// (1) No calcula campo vectorial si se tiene como un escenario al tiempo
int  Metodos_Numericos_Isoclinas::Calcula_isoclinas(const long double valor)
{
   if (Numero_ecuaciones[Sistema_actual] > 2) return 1; // (1) Isoclinas solo se calculan en sistemas de dos ecuaciones diferenciales

   long double c_ini[2],c[NUMERO_ECUACIONES],incx, incy; 
   int xi,i; 
   long double p0,p1,q0,q1,p,q, Valor_isoclina = valor;


   // Inicializa variables
   Suspende_Calculo = false;
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = 0.0, c[i] = 0,0;
   At_Tiempo[Sistema_actual] = t = Ac_Tiempo[Sistema_actual]; // Fija valor para el tiempo

   /////////////////////////////////////////////////////////////
   // Ceroclinas tomando como fijo el eje Y
   incx = (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) / (Numero_puntos * 0.01);
   incy = (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) / (Numero_puntos * 0.5);

   for(c_ini[0] = Dimensiones[Sistema_actual].Yi; c_ini[0] <= Dimensiones[Sistema_actual].Yf; c_ini[0] += incy) {
      X[1] = c_ini[0];
      for(c_ini[1] = Dimensiones[Sistema_actual].Xi; c_ini[1] <= Dimensiones[Sistema_actual].Xf; c_ini[1] += incx) {
         for(xi = 0; xi < 2; xi++) {
            p0 = c_ini[1];
            p1 = c_ini[1] + incx;
            X[0] = p0;
            if (Valor_isoclina != 0.0) {
               q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
               if (q != 0.0)  q0 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
               else q0 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
            } else q0 = ( this->*funcion[Sistema_actual][xi] )();
            if(ERROR_MATEMATICO) {
               ERROR_MATEMATICO = 0;
               continue;
            }
            // Controla el desbordamiento numerico
            if(fabsl(q0) > MAX_VALOR[Sistema_actual]) continue;
            X[0] = p1;
            if (Valor_isoclina != 0.0) {
               q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
               if (q != 0.0)  q1 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
               else q1 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
            } else q1 = ( this->*funcion[Sistema_actual][xi] )();
            if(ERROR_MATEMATICO) {
               ERROR_MATEMATICO = 0;
               continue;
            }
            // Controla el desbordamiento numerico
            if(fabsl(q1) > MAX_VALOR[Sistema_actual]) continue;
            for(i = 2; i < Max_iter; i++) {
               if((q1-q0) == 0.0) break;
               p = p1 - (q1*((p1-p0)/(q1-q0)));
               // Controla divergencia
               if(fabs(p-p1) > (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi)) break;
               if(fabs(p-p1) < Tolerancia) {
                  c[0] = p, c[1] = c_ini[0];
                  Dibuja_punto(c,At_Tiempo[Sistema_actual],Color_Isoclina);
                  break;
               }
               p0 = p1, q0 = q1, p1 = p;
               X[0] = p;
               if (Valor_isoclina != 0.0) {
                  q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
                  if (q != 0.0)  q1 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
                  else q1 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
               } else q1 = ( this->*funcion[Sistema_actual][xi] )();
               // Controla el desbordamiento numerico
               if(ERROR_MATEMATICO) {
                  ERROR_MATEMATICO = 0;
                  continue;
               }
               if(fabsl(q1) > MAX_VALOR[Sistema_actual]) break;
            }
         }
      }
      // Cancela la graficacion de ceroclinas
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
      Application->ProcessMessages();
#endif      
      if(Suspende_Calculo) return 0;
   }
   /////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////
   // Ceroclinas tomando como fijo el eje X
   incy = (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) / (Numero_puntos*0.01);
   incx = (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) / (Numero_puntos*0.5);


   for(c_ini[1] = Dimensiones[Sistema_actual].Xi; c_ini[1] <= Dimensiones[Sistema_actual].Xf; c_ini[1] += incx) {
      X[0] = c_ini[1];
      for(c_ini[0] = Dimensiones[Sistema_actual].Yi; c_ini[0] <= Dimensiones[Sistema_actual].Yf; c_ini[0] += incy) {
         for(xi = 0; xi < 2; xi++) {
            p0 = c_ini[0];
            p1 = c_ini[0] + incy;
            X[1] = p0;
            if (Valor_isoclina != 0.0) {
               q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
               if (q != 0.0)  q0 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
               else q0 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
            } else q0 = ( this->*funcion[Sistema_actual][xi] )();   
            if(ERROR_MATEMATICO) {
               ERROR_MATEMATICO = 0;
               continue;
            }
            // Controla el desbordamiento numerico
            if(fabsl(q0) > MAX_VALOR[Sistema_actual]) continue;
            X[1] = p1;
            if (Valor_isoclina != 0.0) {
               q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
               if (q != 0.0)  q1 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
               else q1 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
            } else q1 = ( this->*funcion[Sistema_actual][xi] )();
            if(ERROR_MATEMATICO) {
               ERROR_MATEMATICO = 0;
               continue;
            }
            // Controla el desbordamiento numerico
            if(fabs(q1) > MAX_VALOR[Sistema_actual]) continue;
            for(i = 2; i < Max_iter; i++) {
               if((q1-q0) == 0.0) break;
               p = p1 -(q1*((p1-p0)/(q1-q0)));
               // Controla divergencia
               if(fabs(p-p1) > (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi)) break;
               // Controla el desbordamiento numerico
               if(fabs(p-p1) < Tolerancia) {
                  c[1] = p, c[0] = c_ini[1];
                  Dibuja_punto(c,At_Tiempo[Sistema_actual],Color_Isoclina);
                  break;
               }
               p0 = p1, q0 = q1, p1 = p;
               X[1] = p;
               if (Valor_isoclina != 0.0) {
                  q = ( this->*funcion[Sistema_actual][(xi == 0 ? 1 : 0)] )();
                  if (q != 0.0)  q1 = (( this->*funcion[Sistema_actual][xi] )() / q) - Valor_isoclina;
                  else q1 = ( this->*funcion[Sistema_actual][xi] )()  - Valor_isoclina;
               } else q1 = ( this->*funcion[Sistema_actual][xi] )();
               if(ERROR_MATEMATICO) {
                  ERROR_MATEMATICO = 0;
                  continue;
               }
               // Controla el desbordamiento numerico
               if(fabsl(q1) > MAX_VALOR[Sistema_actual]) break;
            }
         }
      }
      // Cancela la graficacion de ceroclinas
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
      Application->ProcessMessages();
#endif      
      if(Suspende_Calculo) return 0;
   }
   /////////////////////////////////////////////////////////////

   // Indica que se visualize el error matematico
   return 0; // (0) Calculo correctamente
}


