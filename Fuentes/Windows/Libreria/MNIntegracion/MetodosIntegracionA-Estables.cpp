//////////////////////////////////////////////////////////////////////////////////////////////
// M�todos de Integraci�n de ecuaciones diferenciales ordinarias                            //
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

///////////////////////////////////////////////
//#error Revisar en los metodos multipasos que pasara cuando se cambian las condiciones iniciales (esto no afecta a metodos de un paso)
///////////////////////////////////////////////


#include "MetodosIntegracion.hpp"

#ifndef __PROGRAMACION_BORLAND__
#else
   #include "winuser.h"
   #include "Dialogs.hpp"
#endif


//////////////////////////////////////////////////////////////
//   CLASE DE METODOS NUMERICOS DE INTEGRACION NUMERICA     //
//////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//                                                                 //
//                 M�todos de integraci�n n�merica                 //
//                          de paso fijo                           //
//                                                                 //
//                                                                 //
// Trapezium                (A-stable Secant iterations)           //
// Regresive Euler          (A-stable Secant iterations)           //
//                                                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//                M�todo del Trapecio con Iteracion por Secante                   //
////////////////////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Trapecio_iteraciones_secante(void)
{
   int k, j, sw, sw1;
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

//   // Actualiza el paso de integraci�n
//   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
//   if(!Integracion_positiva) Paso_integracion *= -1.0;

   // Si el reporte esta activo
   if (Reporte_activo) Detalle_reporte(-1);
   if (Visualiza_integracion) {
      // Dibuja la gr�fica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
   
   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          aux2[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * Paso_integracion * 0.5);
          aux3[i] = aux2[i];
          
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      j = 0;
      sw = 0;
      do {
         // Actualiza valores
         t = At_Tiempo[Sistema_actual] + Paso_integracion;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = aux3[i];

         // Se obtiene una aproximaci�n para c�lculo de la derivada
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             for(k = 0; k < Numero_ecuaciones[Sistema_actual]; k++) X[k] = aux3[k];
             X[i] = aux3[k] - Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5];
             // Calculo con la ecuacion diferencial
             aux5[i] = ( this->*funcion[Sistema_actual][i] )();
             // Controla los errores en el calculo matematico
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
             X[i] = aux3[k] + Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5];
             // Calculo con la ecuacion diferencial
             aux6[i] = ( this->*funcion[Sistema_actual][i] )();
             // Controla los errores en el calculo matematico
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         
         sw1 = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calculo de la derivada usando tres puntos
             aux7[i] = ((aux6[i] - aux5[i]) / (Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5] * 2.0));
             if (fabsl(aux7[i]) < 1.0e5) {
                aux8[i] = aux3[i] - ((aux3[i] - (aux4[i] * Paso_integracion * 0.5) - aux1[i]) / (1.0 - (aux7[i] * Paso_integracion * 0.5)));
                if (fabsl(aux8[i] - aux3[i]) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) sw1 = 1;
             } else sw1 = 1;
         }

         if (sw1) {
            j ++;
            // Actualizo posici�n
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) aux3[i] = aux8[i];
            // Si supera el m�ximo se acepta esta, pero no cumplio con la tolerencia
            if (j > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4] || fabsl(aux8[i]) > MAX_VALOR[Sistema_actual]) {
               sw = 1;
               for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) aux8[i] = aux2[i];
            }
         } else sw = 1;
      } while (!sw);
      

      // Obtiene la siguiente condici�n inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] = aux8[i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el numero de iteraciones
      Numero_iteraciones ++;
      // Actualiza el tiempo
#ifdef _INTEGRAR_TIEMPO_EXACTO_
      if (Ultima_integracion) { 
         At_Tiempo[Sistema_actual] += Paso_integracion;
         Tiempo_integracion += fabsl(Paso_integracion);
       } else {
         At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
         Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
      }
#else      
      At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
      Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
#endif

      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(-1);
      if (Visualiza_integracion) {
         // Dibuja la gr�fica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gr�fica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteraci�n
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir alg�n m�todo para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el ultimo valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso_integracion)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso_integracion = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso_integracion *= -1.0;
         Ultima_integracion = true;
      }
#endif      

      // Acciones a realizar despu�s de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gr�fica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}





////////////////////////////////////////////////////////////////////////////////////
//               M�todo de Euler Regresivo con Iteracion por Secante              //
////////////////////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Euler_iteraciones_secante(void)
{
   int k, j, sw, sw1;
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

//   // Actualiza el paso de integraci�n
//   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
//   if(!Integracion_positiva) Paso_integracion = - fabsl(Paso_integracion);
   
   // Si el reporte esta activo
   if (Reporte_activo) Detalle_reporte(-1);
   if (Visualiza_integracion) {
      // Dibuja la gr�fica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
   
   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////
      // Actualiza valores
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          aux2[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * Paso_integracion * 0.5);
          aux3[i] = At_Condicion[Sistema_actual][i];
          
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      j = 0;
      sw = 0;
      do {
         // Actualiza valores
         t = At_Tiempo[Sistema_actual] + Paso_integracion;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = aux3[i];

         // Se obtiene una aproximaci�n para c�lculo de la derivada
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             for(k = 0; k < Numero_ecuaciones[Sistema_actual]; k++) X[k] = aux3[k];
             X[i] = aux3[k] - Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5];
             // Calculo con la ecuacion diferencial
             aux5[i] = ( this->*funcion[Sistema_actual][i] )();
             // Controla los errores en el calculo matematico
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
             X[i] = aux3[k] + Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5];
             // Calculo con la ecuacion diferencial
             aux6[i] = ( this->*funcion[Sistema_actual][i] )();
             // Controla los errores en el calculo matematico
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         sw1 = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calculo de la derivada usando tres puntos
             aux7[i] = ((aux6[i] - aux5[i]) / (Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][5] * 2.0));
             if (fabsl(aux7[i]) < 1.0e5) {
                aux8[i] = aux3[i] - ((aux3[i] - (aux4[i] * Paso_integracion) - At_Condicion[Sistema_actual][i]) / (1.0 - (aux7[i] * Paso_integracion)));
                if (fabsl(aux8[i] - aux3[i]) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) sw1 = 1;
             } else sw1 = 1;
         }

         if (sw1) {
            j ++;
            // Actualizo posici�n
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) aux3[i] = aux8[i];
            // Si supera el m�ximo se acepta esta, pero no cumplio con la tolerencia
            if (j > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4] || fabsl(aux8[i]) > MAX_VALOR[Sistema_actual]) {
               sw = 1;
               for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) aux8[i] = aux2[i];
            }
         } else sw = 1;
      } while (!sw);
      

      // Obtiene la siguiente condici�n inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] = aux8[i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el numero de iteraciones
      Numero_iteraciones ++;
      // Actualiza el tiempo
#ifdef _INTEGRAR_TIEMPO_EXACTO_
      if (Ultima_integracion) { 
         At_Tiempo[Sistema_actual] += Paso_integracion;
         Tiempo_integracion += fabsl(Paso_integracion);
       } else {
         At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
         Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
      }
#else      
      At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
      Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
#endif
      
      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(-1);
      if (Visualiza_integracion) {
         // Dibuja la gr�fica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gr�fica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteraci�n
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir alg�n m�todo para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el ultimo valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso_integracion)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso_integracion = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso_integracion *= -1.0;
         Ultima_integracion = true;
      }
#endif      

      // Acciones a realizar despu�s de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gr�fica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}




