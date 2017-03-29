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
// Predictor-Corrector      (V.S. Adams-Bashforth-Moulton 3 order) //
// Predictor-Corrector      (V.S. Adams-Bashforth-Moulton 4 order) //
// Predictor-Corrector I    (V.S. Adams-Bashforth-Moulton 5 order) //
// Predictor-Corrector II   (V.S. Adams-Bashforth-Moulton 5 order) //
// Predictor-Corrector      (V.S. Adams-Bashforth-Moulton 6 order) //
// Predictor-Corrector      (V.S. Adams-Bashforth-Moulton 7 order) //
//                                                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 3 orden   //
//                       Paso Variable                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM3PV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   if (Reporte_activo) Detalle_reporte(0);
   
   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[2][i];
            tiempo[0] = tiempo[2];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(2,Paso)) return;
            rk = 0, rep = 1;
         }

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
             paso[3][i] = paso[2][i] + ( ((23.0 * aux3[i]) - (16.0 * aux2[i]) + (5.0 * aux1[i]) ) *  (Paso / 12.0) );
         }

         t = tiempo[2] + Paso;
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
             paso[4][i] = paso[2][i] + ( ((5.0 * aux4[i]) + (8.0 * aux3[i]) - (aux2[i]) ) *  (Paso / 12.0) );
         }

        
         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[4][i] - paso[3][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;

          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
            Numero_iteraciones++;
            Detalle_reporte(1);
            Numero_iteraciones++;
            Detalle_reporte(2);
         } else Numero_iteraciones += 2;
         Tiempo_integracion += fabsl(Paso * 2.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
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

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[2];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      if(!Integracion_positiva) Paso = -fabsl(Paso);
      


      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(2);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 4.0) Paso = 4.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         if(!Integracion_positiva) Paso = - fabsl(Paso);
         sw2 = 1;
      } 
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 3.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion) / 3.0);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 4 orden   //
//                       Paso Variable                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM4PV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - Paso;
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;
   
   if (Reporte_activo) Detalle_reporte(0);

   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[3][i];
            tiempo[0] = tiempo[3];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(3,Paso)) return;
            rk = 0, rep = 1;
         }

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
             paso[4][i] = paso[3][i] + ( ((55.0 * aux4[i]) - (59.0 * aux3[i]) + (37.0 * aux2[i]) - (9.0 * aux1[i]) ) *  (Paso / 24.0) );
         }

         t = tiempo[3] + Paso;
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
             paso[5][i] = paso[3][i] + ( ((9.0 * aux5[i]) + (19.0 * aux4[i]) - (5.0 * aux3[i]) + (aux2[i]) ) *  (Paso / 24.0) );
         }

        
         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[5][i] - paso[4][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;
          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
            Numero_iteraciones++;
            Detalle_reporte(1);
            Numero_iteraciones++;
            Detalle_reporte(2);
            Numero_iteraciones++;
            Detalle_reporte(3);
         } else Numero_iteraciones += 3;
         Tiempo_integracion += fabsl(Paso * 3.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
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

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[3];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      

      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(3);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 4.0) Paso = 4.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         if(!Integracion_positiva) Paso = - fabsl(Paso);
         sw2 = 1;
      } 
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 4.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion)) / 4.0;
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}




//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton I de 5 orden //
//                       Paso Variable                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM5PV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - Paso;
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   if (Reporte_activo) Detalle_reporte(0);

   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[4][i];
            tiempo[0] = tiempo[4];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(4,Paso)) return;
            rk = 0, rep = 1;
         }

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

         
         // Obtiene la siguiente condición inicial para corregir
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             paso[5][i] = paso[4][i] + ((( (1901.0 * aux5[i]) - (2774.0 * aux4[i]) + (2616.0 * aux3[i]) - (1274.0 * aux2[i]) + (251.0 * aux1[i])) ) *  (Paso / 720.0));
         }

         t = tiempo[4] + Paso;
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

         // Corrige la nueva condición inicial
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
             paso[6][i] = paso[4][i] + ( ((251.0 * aux6[i]) + (646.0 * aux5[i]) - (264.0 * aux4[i]) + (106.0 * aux3[i]) - (19.0 * aux2[i]) ) *  (Paso / 720.0) );
         }

         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[6][i] - paso[5][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;
         
          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
            Numero_iteraciones++;
            Detalle_reporte(1);
            Numero_iteraciones++;
            Detalle_reporte(2);
            Numero_iteraciones++;
            Detalle_reporte(3);
            Numero_iteraciones++;
            Detalle_reporte(4);
         } else Numero_iteraciones += 4;
         Tiempo_integracion += fabsl(Paso * 4.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for (i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
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

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[4];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(4);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 4.0) Paso = 4.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         sw2 = 1;
         if(!Integracion_positiva) Paso = -fabsl(Paso);
      } 
      
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 5.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion) / 5.0);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}



//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton II de 5      //
//              orden Paso Variable                                 //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM5aPV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - Paso;
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   if (Reporte_activo) Detalle_reporte(0);

   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[4][i];
            tiempo[0] = tiempo[4];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(4,Paso)) return;
            rk = 0, rep = 1;
         }

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

         
         // Obtiene la siguiente condición inicial para corregir
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             paso[5][i] = paso[4][i] + ((( (1901.0 * aux5[i]) - (2774.0 * aux4[i]) + (2616.0 * aux3[i]) - (1274.0 * aux2[i]) + (251.0 * aux1[i])) ) *  (Paso / 720.0));
         }

         t = tiempo[4] + Paso;
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

         // Corrige la nueva condición inicial
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
             paso[6][i] = paso[4][i] + ( ((475.0 * aux6[i]) + (1427.0 * aux5[i]) - (798.0 * aux4[i]) + (482.0 * aux3[i]) - (173.0 * aux2[i]) + (27.0 * aux1[i]) ) *  (Paso / 1440.0) );
         }

         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[6][i] - paso[5][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;
         
          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
            Numero_iteraciones++;
            Detalle_reporte(1);
            Numero_iteraciones++;
            Detalle_reporte(2);
            Numero_iteraciones++;
            Detalle_reporte(3);
            Numero_iteraciones++;
            Detalle_reporte(4);
         } else Numero_iteraciones += 4;
         Tiempo_integracion += fabsl(Paso * 4.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for (i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
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

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[4];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(4);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 4.0) Paso = 4.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         sw2 = 1;
         if(!Integracion_positiva) Paso = -fabsl(Paso);
      } 
      
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 5.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion) / 5.0);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 6 orden   //
//                       Paso Variable                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM6PV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - Paso;
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   if (Reporte_activo) Detalle_reporte(0);

   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[5][i];
            tiempo[0] = tiempo[5];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(5,Paso)) return;
            rk = 0, rep = 1;
         }

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

         
         // Obtiene la siguiente condición inicial para corregir
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             paso[6][i] = paso[5][i] + ((( (4277.0 * aux6[i]) - (7923.0 * aux5[i]) + (9982.0 * aux4[i]) - (7298.0 * aux3[i]) + (2877.0 * aux2[i]) - (475.0 * aux1[i])) ) *  (Paso / 1440.0));
         }

         t = tiempo[5] + Paso;
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

         // Corrige la nueva condición inicial
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
             paso[7][i] = paso[5][i] + ( ((19087.0 * aux7[i]) + (65112.0 * aux6[i]) - (46461.0 * aux5[i]) + (37504.0 * aux4[i]) - (20211.0 * aux3[i]) + (6312.0 * aux2[i]) - (863.0 * aux1[i]) ) *  (Paso / 60480.0) );
         }

         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[7][i] - paso[6][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;
         
          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
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
         } else Numero_iteraciones += 5;
         Tiempo_integracion += fabsl(Paso * 5.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for (i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          At_Condicion[Sistema_actual][i] = paso[7][i];

          paso[0][i] = paso[1][i];
          paso[1][i] = paso[2][i];
          paso[2][i] = paso[3][i];
          paso[3][i] = paso[4][i];
          paso[4][i] = paso[6][i];
          paso[5][i] = paso[7][i];
          
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[5];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(5);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 5.0) Paso = 5.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         sw2 = 1;
         if(!Integracion_positiva) Paso = -fabsl(Paso);
      } 
      
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 6.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion) / 6.0);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}


//////////////////////////////////////////////////////////////////////
//                                                                  //
//  Método Predictor-Corrector Adams-Bashforth-Moulton de 7 orden   //
//                       Paso Variable                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Predictor_corrector_ABM7PV(void)
{
   int sw, sw1, sw2, rep, rk;
   long double delta, xdelta, q;

   // Inicializa las variables
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - Paso;
   Paso_integracion = Paso_maximo = Paso_minimo = fabsl(Paso);

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = c_ini[i];
   tiempo[0] = Tiempo_actual;

   if (Reporte_activo) Detalle_reporte(0);

   sw1 = 0, sw2 = 0, rk = 1;
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
////////////////////////////////////////////////////////////////////////////      
      // Acciones a realizar antes de integrar
      Antes_integrar(0);
      // Revisar como recalculo las nuevas condiciones iniciales
///////////////////////////////////////////////////////////////////////////

      do {
         // Actualiza valores
         if (sw2) {
            // Toma los valores del último paso cálculado
            for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) paso[0][i] = paso[6][i];
            tiempo[0] = tiempo[6];
            sw2 = 0, rk = 1, sw1 = 0;
         }

         if (rk) {
            if (Genera_n_pasos(6,Paso)) return;
            rk = 0, rep = 1;
         }

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


         
         // Obtiene la siguiente condición inicial para corregir
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             paso[7][i] = paso[6][i] + ((( (198721.0 * aux7[i]) - (447288.0 * aux6[i]) + (705549.0 * aux5[i]) - (688256.0 * aux4[i]) + (407139.0 * aux3[i]) - (134472.0 * aux2[i]) + (19087.0 * aux1[i])) ) *  (Paso / 60480.0));
         }

         t = tiempo[6] + Paso;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[7][i];

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
             paso[8][i] = paso[6][i] + ( ((36799.0 * aux8[i]) + (139849.0 * aux7[i]) - (121797.0 * aux6[i]) + (123133.0 * aux5[i]) - (88547.0 * aux4[i]) + (41499.0 * aux3[i]) - (11351.0 * aux2[i]) + (1375.0 * aux1[i]) ) *  (Paso / 120960.0) );
         }

         delta = 0.0;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             xdelta = (19.0 * fabsl(paso[8][i] - paso[7][i])) / (270.0 * fabsl(Paso));
             // Toma la menos de la xdeltas
             if(xdelta > delta) delta = xdelta;
             // No se hacepta 
             if(xdelta > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         if (delta != 0.0) q = powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / (2.0 * delta)),0.25);
          else q = 5.0;
         
          
         // Ajuste del paso 
         if (sw) {
            if (fabsl(Paso) <= Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) sw = 0;
             else {
               // Disminuye el paso y continua
               if (q < 0.1 || q > 0.9) {
                  if (q < 0.1) Paso = Paso * 0.1;
                  if (q > 0.9) Paso = Paso * 0.9;
               } else Paso = Paso * q;
               // Revisa si es necesario ajustar el paso al mínimo dado
               if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
               if(!Integracion_positiva) Paso = - fabsl(Paso);
               // Tome el valor del ultimo paso cálculado
               if (sw1) sw2 = 1;
               rk = 1;
            }
         }
      } while (sw);
      sw1 = 1;
      Paso_integracion = fabsl(Paso);

      if (rep) {
         if (Reporte_activo) {
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
         } else Numero_iteraciones += 6;
         Tiempo_integracion += fabsl(Paso * 6.0);
         rep = 0;
      }
      
      // Actualiza la nueva condicion inicial
      for (i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
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

      if(!Integracion_positiva) Paso = - fabsl(Paso);
      tiempo[0]  = tiempo[1];
      tiempo[1]  = tiempo[2];
      tiempo[2]  = tiempo[3];
      tiempo[3]  = tiempo[4];
      tiempo[4]  = tiempo[5];
      tiempo[5]  = tiempo[6];
      tiempo[6]  += Paso;

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] = tiempo[6];

      // Actualiza el numero de iteraciones
      Tiempo_integracion += fabsl(Paso);
      Numero_iteraciones++;
         
      // Almacena el paso maximo y el minimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Si el reporte esta activo
      if (Reporte_activo) Detalle_reporte(6);
      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con lineas
         if(!Grafica_puntos[Sistema_actual]) Dibuja_linea(c_ini,At_Condicion[Sistema_actual],Tiempo_actual,At_Tiempo[Sistema_actual],Color_Integracion);
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

      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];


      // Revisa si aumenta el paso de integración
      if (delta <= (0.1 * Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2])) {
         // Aumenta el paso
         if (q > 6.0) Paso = 6.0 * Paso;  
          else Paso = q * Paso;
         // Revisa si es necesario ajustar el paso al máximo dado
         if(fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
         sw2 = 1;
         if(!Integracion_positiva) Paso = -fabsl(Paso);
      } 
      
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + (fabsl(Paso) * 7.0)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = (fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion) / 7.0);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      
      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   if (Reporte_activo) {
      sprintf(C_imp,"Maximum Step %+1.8Le" ,Paso_maximo);
      Rep_num->Formato_impresion(3,3,C_imp);
      sprintf(C_imp,"Minimum Step %+1.8Le" ,Paso_minimo);
      Rep_num->Formato_impresion(3,1,C_imp);
   }
   if (Visualiza_ultima_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }
}

