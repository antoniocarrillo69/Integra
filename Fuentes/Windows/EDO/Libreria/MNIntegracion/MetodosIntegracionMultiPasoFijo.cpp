//////////////////////////////////////////////////////////////////////////////////////////////
// Métodos de Integración de ecuaciones diferenciales ordinarias                            //
// Revisión: 16 de Abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001-2002                                                                  //
//                                                                                          //
// Análisis y Diseño:                                                                       //
//                                                                                          //
// Autor     Dr. Humberto Carrillo Calvet                                                   //
// E-mail:   carr@servidor.unam.mx                                                          //
// Página:   http://www.dynamics.unam.edu/hcc                                               //
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
//                 Métodos de integración númerica                 //
//                          de paso fijo                           //
//                                                                 //
//                                                                 //
// Adams-Bashforth          (2 steps)                              //
// Adams-Bashforth          (3 steps)                              //
// Milne                    (3 steps)                              //
// Adams-Bashforth          (4 steps)                              //
// Adams-Bashforth          (5 steps)                              //
//                                                                 //
// Predictor-Corrector                                             //
//                                                                 //
// Adams-Bashforth-Moulton    (3 order)                            //
// Milne-Simpson              (3 order)                            //
// Adams-Bashforth-Moulton    (4 order)                            //
// Adams-Bashforth-Moulton I  (5 order)                            //
// Adams-Bashforth-Moulton II (5 order)                            //
// Adams-Bashforth-Moulton    (6 order)                            //
// Adams-Bashforth-Moulton    (7 order)                            //
//                                                                 //
/////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-2Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Adams_Bashforth_2pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeros pasos
   if (Genera_n_pasos(1,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 1;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion);

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[2][i] = paso[1][i] + ( ((3.0 * aux2[i]) - (aux1[i])) *  (Paso_integracion / 2.0) );
          At_Condicion[Sistema_actual][i] = paso[2][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(1);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      // Acciones a realizar después de integrar
      Despues_integrar(0);

   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-3Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Adams_Bashforth_3pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(2,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 2;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 2.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[3][i] = paso[2][i] + ( ((23.0 * aux3[i]) - (16.0 * aux2[i]) + (5.0 * aux1[i]) ) *  (Paso_integracion / 12.0) );
          At_Condicion[Sistema_actual][i] = paso[3][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(2);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//                       Método Milne-3Pasos                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Milne_3pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(3,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 3;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 3.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[4][i] = paso[0][i] + ( ((2.0 * aux3[i]) - (aux2[i]) + (2.0 * aux1[i]) ) *  ((4.0 * Paso_integracion) / 3.0) );
          At_Condicion[Sistema_actual][i] = paso[4][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(3);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-4Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Adams_Bashforth_4pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(3,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 3;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 3.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[4][i] = paso[3][i] + ( ((55.0 * aux4[i]) - (59.0 * aux3[i]) + (37.0 * aux2[i]) - (9.0 * aux1[i]) ) *  (Paso_integracion / 24.0) );
          At_Condicion[Sistema_actual][i] = paso[4][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(3);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}



//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-5Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Adams_Bashforth_5pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(4,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 4;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 4.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[4];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[5][i] = paso[4][i] + ((( (1901.0 * aux5[i]) - (2774.0 * aux4[i]) + (2616.0 * aux3[i]) - (1274.0 * aux2[i]) + (251.0 * aux1[i])) ) *  (Paso_integracion / 720.0));
          At_Condicion[Sistema_actual][i] = paso[5][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[5][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(4);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}



//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-6Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Adams_Bashforth_6pasos(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(5,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
      Numero_iteraciones++;
      Detalle_reporte(5);
   }

   // Actualiza valores de los 5 primeros pasos
   Numero_iteraciones = 5;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 5.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[4];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      t = tiempo[5];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[6][i] = paso[5][i] + ((( (4277.0 * aux6[i]) - (7923.0 * aux5[i]) + (9982.0 * aux4[i]) - (7298.0 * aux3[i]) + (2877.0 * aux2[i]) - (475.0 * aux1[i])) ) *  (Paso_integracion / 1440.0));
          At_Condicion[Sistema_actual][i] = paso[6][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[5][i];
          paso[5][i] = paso[6][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(5);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                Método Adams-Bashforth-7Pasos                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Adams_Bashforth_7pasos(void)
{
   // Actualiza valores para calcular los seis primeros pasos 
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(6,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
      Numero_iteraciones++;
      Detalle_reporte(5);
      Numero_iteraciones++;
      Detalle_reporte(6);
   }

   // Actualiza valores de los 6 primeros pasos
   Numero_iteraciones = 6;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 6.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[4];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      t = tiempo[5];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[6];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[6][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux7[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[7][i] = paso[6][i] + ((((198721.0 * aux7[i]) - (447288.0 * aux6[i]) + (705549.0 * aux5[i]) - (688256.0 * aux4[i]) + (407139.0 * aux3[i]) - (134472.0 * aux2[i]) + (19087.0 * aux1[i])) ) *  (Paso_integracion / 60480.0));
          At_Condicion[Sistema_actual][i] = paso[7][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[5][i];
          paso[5][i] = paso[6][i];
          paso[6][i] = paso[7][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  = tiempo[6];
      tiempo[6]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(6);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}




//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 3 orden   //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM3(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(2,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 2;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 2.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      

      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[3][i] = paso[2][i] + ( ((23.0 * aux3[i]) - (16.0 * aux2[i]) + (5.0 * aux1[i]) ) *  (Paso_integracion / 12.0) );
      }
      t = tiempo[2] + Paso_integracion;
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[4][i] = paso[2][i] + ( ((5.0 * aux4[i]) + (8.0 * aux3[i]) - (aux2[i]) ) *  (Paso_integracion / 12.0) );
          At_Condicion[Sistema_actual][i] = paso[4][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[4][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(2);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//     Método Predictor-Corrector de Milne-Simpson de 3 orden       //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Predictor_corrector_MS3(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo_inicial = tiempo[0] = Tiempo_actual;
   
   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(3,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 3;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 3.0);
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[4][i] = paso[0][i] + (( ((2.0 * aux3[i]) - (aux2[i]) + (2.0 * aux1[i]) ) *  (Paso_integracion / 3.0) * 4.0) );
      }

      t = tiempo[3] + Paso_integracion;
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];

      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[5][i] = paso[2][i] + ( ((aux4[i]) + (4.0 * aux3[i]) + (aux2[i]) ) *  (Paso_integracion / 3.0) );
          At_Condicion[Sistema_actual][i] = paso[5][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[5][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(3);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 4 orden   //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Predictor_corrector_ABM4(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(3,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
   }

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 3;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 3.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      t = tiempo[0];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[1];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[2];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      t = tiempo[3];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      

      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[4][i] = paso[3][i] + ( ((55.0 * aux4[i]) - (59.0 * aux3[i]) + (37.0 * aux2[i]) - (9.0 * aux1[i]) ) *  (Paso_integracion / 24.0) );
      }
      t = tiempo[3] + Paso_integracion;
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[5][i] = paso[3][i] + ( ((9.0 * aux5[i]) + (19.0 * aux4[i]) - (5.0 * aux3[i]) + (aux2[i]) ) *  (Paso_integracion / 24.0) );
          At_Condicion[Sistema_actual][i] = paso[5][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[5][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(3);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton I de 5 orden //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Predictor_corrector_ABM5(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(4,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
   } 

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 4;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 4.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      t = tiempo[0];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      t = tiempo[1];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      t = tiempo[2];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      t = tiempo[3];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      t = tiempo[4];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[5][i] = paso[4][i] + ((( (1901.0 * aux5[i]) - (2774.0 * aux4[i]) + (2616.0 * aux3[i]) - (1274.0 * aux2[i]) + (251.0 * aux1[i])) ) *  (Paso_integracion / 720.0));
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      t = tiempo[4] + Paso_integracion;
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[6][i] = paso[4][i] + ( ((251.0 * aux6[i]) + (646.0 * aux5[i]) - (264.0 * aux4[i]) + (106.0 * aux3[i]) - (19.0 * aux2[i]) ) *  (Paso_integracion / 720.0) );
          At_Condicion[Sistema_actual][i] = paso[6][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[6][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(4);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}



//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton II de        //
//                         5 orden                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM5a(void)
{
   // Actualiza valores para calcular los dos primeros pasos del método usando Runge-Kutta 4
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Cálcula los dos primeroa pasos
   if (Genera_n_pasos(4,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
   } 

   // Actualiza valores de los 2 primeros pasos
   Numero_iteraciones = 4;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 4.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      t = tiempo[0];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      t = tiempo[1];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      t = tiempo[2];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      t = tiempo[3];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      t = tiempo[4];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[5][i] = paso[4][i] + ( ((1901.0 * aux5[i]) - (2774.0 * aux4[i]) + (2616.0 * aux3[i]) - (1274.0 * aux2[i]) + (251.0 * aux1[i]) ) *  (Paso_integracion / 720.0) );
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      t = tiempo[4] + Paso_integracion;
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[6][i] = paso[4][i] + ( ((475.0 * aux6[i]) + (1427.0 * aux5[i]) - (798.0 * aux4[i]) + (482.0 * aux3[i]) - (173.0 * aux2[i]) + (27.0 * aux1[i]) ) *  (Paso_integracion / 1440.0) );
          At_Condicion[Sistema_actual][i] = paso[6][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[6][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(4);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 6 orden   //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM6(void)
{
   // Actualiza valores para calcular los cinco primeros pasos
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Cálcula los cinco primeros pasos
   if (Genera_n_pasos(5,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
      Numero_iteraciones++;
      Detalle_reporte(5);
   } 

   // Actualiza valores de los 5 primeros pasos
   Numero_iteraciones = 5;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 5.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      t = tiempo[0];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      t = tiempo[1];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      t = tiempo[2];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      t = tiempo[3];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      t = tiempo[4];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      t = tiempo[5];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

///////////////////////////////////
      
      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[6][i] = paso[5][i] + ( ((4277.0 * aux6[i]) - (7923.0 * aux5[i]) + (9982.0 * aux4[i]) - (7298.0 * aux3[i]) + (2877.0 * aux2[i]) - (475.0 * aux1[i]) ) *  (Paso_integracion / 1440.0) );
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[6][i];
      t = tiempo[5] + Paso_integracion;
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux7[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[7][i] = paso[5][i] + ( ((19087.0 * aux7[i]) + (65112.0 * aux6[i]) - (46461.0 * aux5[i]) + (37504.0 * aux4[i]) - (20211.0 * aux3[i]) + (6312.0 * aux2[i]) - (863.0 * aux1[i]) ) *  (Paso_integracion / 60480.0) );
          At_Condicion[Sistema_actual][i] = paso[7][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[5][i];
          paso[5][i] = paso[7][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(5);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 7 orden   //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM7(void)
{
   // Actualiza valores para calcular los seis primeros pasos
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   Paso_integracion = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);

   // Cálcula los seis primeros pasos
   if (Genera_n_pasos(6,Paso_integracion)) return;
   if (Reporte_activo) {
      Detalle_reporte(0);
      Numero_iteraciones++;
      Detalle_reporte(1);
      Numero_iteraciones++;
      Detalle_reporte(2);
      Numero_iteraciones++;
      Detalle_reporte(3);
      Numero_iteraciones++;
      Detalle_reporte(4);
      Numero_iteraciones++;
      Detalle_reporte(5);
      Numero_iteraciones++;
      Detalle_reporte(6);
   } 

   // Actualiza valores de los 6 primeros pasos
   Numero_iteraciones = 6;
   
   // Inicializa las variables
   Tiempo_integracion = fabsl(Paso_integracion * 6.0);

   // Loop del metodo numerico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[0][i];
      t = tiempo[0];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[1][i];
      t = tiempo[1];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[2][i];
      t = tiempo[2];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[3][i];
      t = tiempo[3];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux4[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[4][i];
      t = tiempo[4];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux5[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[5][i];
      t = tiempo[5];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux6[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[6][i];
      t = tiempo[6];
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux7[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
///////////////////////////////////
      
      // Obtiene la siguiente condición inicial para corregir
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[7][i] = paso[6][i] + ( ((198721.0 * aux7[i]) - (447288.0 * aux6[i]) + (705549.0 * aux5[i]) - (688256.0 * aux4[i]) + (407139.0 * aux3[i]) - (134472.0 * aux2[i]) + (19087.0 * aux1[i]) ) *  (Paso_integracion / 60480.0) );
      }

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[7][i];
      t = tiempo[6] + Paso_integracion;
      // Calcula el nuevo valor inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calculo con la ecuacion diferencial
          aux8[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Corrige la nueva condición inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          paso[8][i] = paso[6][i] + ( ((36799.0 * aux8[i]) + (139849.0 * aux7[i]) - (121797.0 * aux6[i]) + (123133.0 * aux5[i]) - (88547.0 * aux4[i]) + (41499.0 * aux3[i]) - (11351.0 * aux2[i]) + (1375.0 * aux1[i]) ) *  (Paso_integracion / 120960.0) );
          At_Condicion[Sistema_actual][i] = paso[8][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[5][i];
          paso[5][i] = paso[6][i];
          paso[6][i] = paso[8][i];

          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      if(!Integracion_positiva) Paso_integracion = -fabsl(Paso_integracion);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  = tiempo[6];
      tiempo[6]  += Paso_integracion;

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
      if (Reporte_activo) Detalle_reporte(6);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini, At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
      }
      
      #ifdef _SUSPENDE_INTEGRACION_
      // Revisa si es necesario detener la iteración
      if (!(Numero_iteraciones % NUMERO_ITERACIONES_REVISAR)) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para procesar mensajes pendientes del sistema
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
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

