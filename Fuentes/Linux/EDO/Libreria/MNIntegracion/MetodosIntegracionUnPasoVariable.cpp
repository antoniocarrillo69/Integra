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
//                        de un paso variable                      //
//                                                                 //
//                                                                 //
// Runge-Kutta                                    (V.S. 3/2 order) //
// Runge-Kutta-Fehlberg                           (V.S. 4/3 order) //
// Prince-Dormand                                 (V.S. 5/4 order) //
// Prince-Dormand I                             (V.S. 5/4/7 order) //
// Prince-Dormand II                            (V.S. 5/4/7 order) //
// Runge-Kutta-Fehlberg                           (V.S. 5/4 order) //
// England                                        (V.S. 5/4 order) //
// Prince-Dormand                               (V.S. 6/5/8 order) //
// Runge-Kutta-Fehlberg                           (V.S. 6/5 order) //
// Runge-Kutta-Verner I                           (V.S. 6/5 order) //
// Runge-Kutta-Verner II                          (V.S. 6/5 order) //
// Runge-Kutta-Verner                          (V.S. 6/7/10 order) //
// Runge-Kutta-Verner                          (V.S. 8/7/13 order) //
// Runge-Kutta-Fehlberg                        (V.S. 8/7/13 order) //
// Prince-Dormand                              (V.S. 8/7/13 order) //
// Runge-Kutta-Verner                          (V.S. 9/8/16 order) //
//                                                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
//                                                                 //
//    Método de un paso, paso variable Runge-Kutta de orden 3/2    //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_3_2(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
         t = At_Tiempo[Sistema_actual] + (Paso * 0.5);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - aux1[i] + (aux2[i] * 2.0); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
      

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux4[i] = fabsl( -((1.0/6.0) * aux1[i]) + ((1.0/3.0) * aux2[i]) - ((1.0/6.0) * aux3[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux4[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux4[i]), (1.0/2.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux4[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += aux2[i];
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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



/////////////////////////////////////////////////////////////////////
//                                                                 //
//    Método de un paso, paso variable Runge-Kutta-Fehlberg de     //
//                             orden 4/3                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKF_4_3(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2.0/7.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/7.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (77.0/900.0)) + (aux2[i] * (343.0/900.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (7.0/15.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (805.0/1444.0)) - (aux2[i] * (77175.0/54872.0)) + (aux3[i] * (97125.0/54872.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (35.0/38.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (79.0/490.0)) + (aux3[i] * (2175.0/3626.0)) + (aux4[i] * (2166.0/9065.0)) ; 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }


         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
//             aux6[i] = fabsl( (((4.0/735.0) * aux1[i]) - (75.0/3626.0) * aux3[i]) + ((5776.0/81585.0) * aux4[i]) - ((1.0/18.0) * aux5[i]) ) / fabsl(Paso);
             aux6[i] = fabsl( -((4.0/735.0) * aux1[i]) + ((75.0/3626.0) * aux3[i]) - ((5776.0/81585.0) * aux4[i]) + ((1.0/18.0) * aux5[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux6[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux6[i]), (1.0/3.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux6[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
//          At_Condicion[Sistema_actual][i] += ((79.0/490.0) * aux1[i]) + ((2175.0/3626.0) * aux3[i]) + ((2166.0/9065.0) * aux4[i]);
          At_Condicion[Sistema_actual][i] += ((229.0/1470.0) * aux1[i]) + ((1125.0/1813.0) * aux3[i]) + ((13718.0/81585.0) * aux4[i]) + ((1.0/18.0) * aux5[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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



/////////////////////////////////////////////////////////////////////
//                                                                 //
//       Método de un paso, paso variable Prince-Dormand de        //
//                         orden 5/4/6                             //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_5_4_6(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/5.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/40.0)) + (aux2[i] * (9.0/40.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/10.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/10.0)) - (aux2[i] * (9.0/10.0)) + (aux3[i] * (6.0/5.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (226.0/729.0)) - (aux2[i] * (25.0 / 27.0)) + (aux3[i] * (880.0/729.0)) + (aux4[i] * (55.0/729.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0 / 3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (181.0/270.0)) + (aux2[i] * (5.0/2.0)) - (aux3[i] * (266.0/297.0)) - (aux4[i] * (91.0/27.0)) + (aux5[i] * (189.0/55.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux7[i] = fabsl( -((11.0/360.0) * aux1[i]) + ((10.0/63.0) * aux3[i]) - ((55.0/72.0) * aux4[i]) + ((27.0/40.0) * aux5[i]) - ((11.0/280.0) * aux6[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux7[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux7[i]), (1.0/4.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux7[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((31.0/540.0) * aux1[i]) + ((190.0/297.0) * aux3[i]) - ((145.0/108.0) * aux4[i]) + ((351.0/220.0) * aux5[i]) + ((1.0/20.0) * aux6[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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


/////////////////////////////////////////////////////////////////////
//                                                                 //
//       Método de un paso, paso variable Prince-Dormand I de      //
//                         orden 5/4/7                             //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_5_4_7I(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/5.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/40.0)) + (aux2[i] * (9.0/40.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/10.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (44.0/45.0)) - (aux2[i] * (56.0/15.0)) + (aux3[i] * (32.0/9.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (19372.0/6561.0)) - (aux2[i] * (25360.0 / 2187.0)) + (aux3[i] * (64448.0/6561.0)) - (aux4[i] * (212.0/729.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (8.0 / 9.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (9017.0/3168.0)) - (aux2[i] * (355.0/33.0)) + (aux3[i] * (46732.0/5247.0)) + (aux4[i] * (49.0/176.0)) - (aux5[i] * (5103.0/18656.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (35.0/384.0)) + (aux3[i] * (500.0/1113.0)) + (aux4[i] * (125.0/192.0)) - (aux5[i] * (2187.0/6784.0)) + (aux6[i] * (11.0/84.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux8[i] = fabsl( -((71.0/57600.0) * aux1[i]) + ((71.0/16695.0) * aux3[i]) - ((71.0/1920.0) * aux4[i]) + ((17253.0/339200.0) * aux5[i]) - ((22.0/525.0) * aux6[i]) + ((1.0/40.0) * aux7[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux8[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux8[i]), (1.0/4.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux8[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += (((5179.0/57600.0) * aux1[i]) + ((7571.0/16695.0) * aux3[i]) + ((393.0/640.0) * aux4[i]) - ((92097.0/339200.0) * aux5[i]) + ((187.0/2100.0) * aux6[i]) + ((1.0/40.0) * aux7[i]));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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


/////////////////////////////////////////////////////////////////////
//                                                                 //
//       Método de un paso, paso variable Prince-Dormand II de     //
//                         orden 5/4/7                             //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_5_4_7II(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2.0/9.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/9.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/12.0)) + (aux2[i] * (1.0/4.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/3.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (55.0/324.0)) - (aux2[i] * (25.0/108.0)) + (aux3[i] * (50.0/81.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/9.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (83.0/330.0)) - (aux2[i] * (13.0 / 22.0)) + (aux3[i] * (61.0/66.0)) + (aux4[i] * (9.0/110.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0 / 3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (19.0/28.0)) + (aux2[i] * (9.0/4.0)) + (aux3[i] * (1.0/7.0)) - (aux4[i] * (27.0/7.0)) + (aux5[i] * (22.0/7.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (19.0/200.0)) + (aux3[i] * (3.0/5.0)) - (aux4[i] * (243.0/400.0)) + (aux5[i] * (33.0/40.0)) + (aux6[i] * (7.0/80.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux8[i] = fabsl( -((11.0/1250.0) * aux1[i]) + ((33.0/500.0) * aux3[i]) - ((891.0/5000.0) * aux4[i]) + ((33.0/250.0) * aux5[i]) + ((9.0/1000.0) * aux6[i]) - ((1.0/50.0) * aux7[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux8[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux8[i]), (1.0/4.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux8[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += (((431.0/5000.0) * aux1[i]) + ((333.0/500.0) * aux3[i]) - ((7857.0/10000.0) * aux4[i]) + ((957.0/1000.0) * aux5[i]) + ((193.0/2000.0) * aux6[i]) - ((1.0/50.0) * aux7[i]));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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




/////////////////////////////////////////////////////////////////////
//                                                                 //
//             Método Runge-Kutta-Fehlberg  de orden 5/4           //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKF_5_4(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/4.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/4.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/32.0)) + (aux2[i] * (9.0/32.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/8.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1932.0/2197.0)) - (aux2[i] * (7200.0/2197.0)) + (aux3[i] * (7296.0/2197.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (12.0/13.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (439.0/216.0)) - (aux2[i] * 8.0) + (aux3[i] * (3680.0/513.0)) - (aux4[i] * (845.0/4104.0)) ; 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8.0/27.0)) + (aux2[i] * 2.0) - (aux3[i] * (3544.0/2565.0)) + (aux4[i] * (1859.0/4104.0)) - (aux5[i] * (11.0/40.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * 0.5);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux7[i] = fabsl( ((1.0/360.0) * aux1[i]) - ((128.0/4275.0) * aux3[i]) - ((2197.0/75240.0) * aux4[i]) + ((1.0/50.0) * aux5[i]) + ((2.0/55.0) * aux6[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux7[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux7[i]), (1.0/4.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux7[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((25.0/216.0) * aux1[i]) + ((1408.0/2565.0) * aux3[i]) + ((2197.0/4104.0) * aux4[i]) - ((1.0/5.0) * aux5[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];


      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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


/////////////////////////////////////////////////////////////////////
//                                                                 //
//     Método de un paso, paso variable England de orden 5/4       //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKE_5_4(void)
//#error Revisar método (Control de error o ...)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso = - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/2.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/2.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/4.0)) + (aux2[i] * (1.0/4.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/2.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - aux2[i] + (aux3[i] * 2.0) ; 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (7.0/27.0)) + (aux2[i] * (10.0/27.0)) + (aux4[i] * (1.0/27.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (28.0/625.0)) - (aux2[i] * (125.0/625.0)) + (aux3[i] * (546.0/625.0)) + (aux4[i] * (54.0/625.0)) - (aux5[i] * (378.0/625.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             aux7[i] = fabsl( ((1.0/8.0) * aux1[i]) + ((2.0/3.0) * aux3[i]) + ((1.0/16.0) * aux4[i]) - ((27.0/56.0) * aux5[i]) - ((125.0/336.0) * aux6[i]) ) / fabsl(Paso);
             // Calcula la delta
             if (aux7[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux7[i]), (1.0/4.0));
              else xdelta = 1.0e+308;
             if(xdelta < delta) delta = xdelta;
             if (aux7[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
        
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((1.0/6.0) * aux1[i]) + ((4.0/6.0) * aux3[i]) + ((1.0/6.0) * aux4[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);

      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif 

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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


/////////////////////////////////////////////////////////////////////
//                                                                 //
// Método de un paso, paso variable Prince-Dormand de orden 6/5/8  //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_6_5_8(void)
//#error Revisar método (Control de error o ...)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/10.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/10.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (2.0/81.0)) + (aux2[i] * (20.0/81.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/9.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (615.0/1372.0)) - (aux2[i] * (270.0/343.0)) + (aux3[i] * (1053.0/1372.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/7.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3243.0/5500.0)) - (aux2[i] * (54.0/55.0)) + (aux3[i] * (50949.0/71500.0)) + (aux4[i] * (4998.0/17875.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (26492.0/37125.0)) + (aux2[i] * (72.0/55.0)) + (aux3[i] * (2808.0/23375.0)) - (aux4[i] * (24206.0/37125.0)) + (aux5[i] * (338.0/495.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5561.0/2376.0)) - (aux2[i] * (35.0/11.0)) - (aux3[i] * (24117.0/31603.0)) + (aux4[i] * (899983.0/200772.0)) - (aux5[i] * (5225.0/1836.0)) + (aux6[i] * (3925.0/4056.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (465467.0/266112.0)) - (aux2[i] * (2945.0/1232.0)) - (aux3[i] * (5610201.0/14158144.0)) + (aux4[i] * (10513573.0/3212352.0)) - (aux5[i] * (424325.0/205632.0)) + (aux6[i] * (376225.0/454272.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i] = fabsl( ((13.0/2400.0) * aux1[i]) - ((19683.0/618800.0) * aux3[i]) + ((2401.0/31200.0) * aux4[i]) - ((65.0/816.0) * aux5[i]) + ((15.0/416.0) * aux6[i]) +  ((521.0/5600.0) * aux7[i]) - ((1.0/10.0) * aux8[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux9[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux9[i]), (1.0/5.0));
              else xdelta = 1.0e+308;
 
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux9[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += (((821.0/10800.0) * aux1[i]) + ((19683.0/71825.0) * aux3[i]) + ((175273.0/912600.0) * aux4[i]) + ((395.0/3672.0) * aux5[i]) + ((785.0/2704.0) * aux6[i]) + ((3.0/50.0) * aux7[i]));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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

/////////////////////////////////////////////////////////////////////
//                                                                 //
//   Método de un paso, paso variable Runge-Kutta-Fehlberg de      //
//                             orden 6/5                           //
//                                                                 //
/////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKF_6_5(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/6.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (4.0/75.0)) + (aux2[i] * (16.0/75.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/15.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0/6.0)) - (aux2[i] * (8.0/3.0)) + (aux3[i] * (5.0/2.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8.0/5.0)) + (aux2[i] * (144/25.0)) - (aux3[i] * 4.0) + (aux4[i] * (16.0/25.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (361.0/320.0)) - (aux2[i] * (18.0/5)) + (aux3[i] * (407.0/128.0)) - (aux4[i] * (11.0/80.0)) + (aux5[i] * (55.0/128.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (11.0/640.0)) + (aux3[i] * (11.0/256.0)) - (aux4[i] * (11.0/160.0)) + (aux5[i] * (11.0/256.0)); 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (93.0/640.0)) - (aux2[i] * (18.0/5.0)) + (aux3[i] * (803.0/256.0)) - (aux4[i] * (11.0/160.0)) + (aux5[i] * (99.0/256.0)) + aux7[i]; 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i] = fabsl( (aux1[i] + aux6[i] -  aux7[i] - aux8[i]) * (5.0/66.0) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux9[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux9[i]), (1.0/5.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux9[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((31.0/384.0) * aux1[i]) + ((1125.0/2816.0) * aux3[i]) + ((9.0/32.0) * aux4[i]) + ((125.0/768.0) * aux5[i]) + ((5.0/66.0) * aux6[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//                      Método Runge-Kutta-Verner I                 //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKV_6_5I(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/6.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (4.0/75.0)) + (aux2[i] * (16.0/75.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/15.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0/6.0)) - (aux2[i] * (8.0/3.0)) + (aux3[i] * (5.0/2.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (165.0/64.0)) + (aux2[i] * (55/6.0)) - (aux3[i] * (425.0/64.0)) + (aux4[i] * (85.0/96.0)) ; 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (12.0/5.0)) - (aux2[i] * 8.0) + (aux3[i] * (4015.0/612.0)) - (aux4[i] * (11.0/36.0)) + (aux5[i] * (88.0/255.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8263.0/15000.0)) + (aux2[i] * (124.0/75.0)) - (aux3[i] * (643.0/680.0)) - (aux4[i] * (81.0/250.0)) + (aux5[i] * (2484.0/10625.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso/15.0);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3501.0/1720.0)) - (aux2[i] * (300.0/43.0)) + (aux3[i] * (297275.0/52632.0)) - (aux4[i] * (319.0/2322.0)) + (aux5[i] * (24068.0/84065.0)) + (aux7[i] * (3850.0/26703.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i] = fabsl(  -((1.0/160.0) * aux1[i]) - ((125.0/17952.0) * aux3[i]) + ((1.0/144.0) * aux4[i]) - ((12.0/1955.0) * aux5[i]) - ((3.0/44.0) * aux6[i]) +  ((125.0/11592.0) * aux7[i]) +  ((43.0/616.0) * aux8[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux9[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux9[i]), (1.0/5.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux9[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((13.0/160.0) * aux1[i]) + ((2375.0/5984.0) * aux3[i]) + ((5.0/16.0) * aux4[i]) + ((12.0/85.0) * aux5[i]) + ((3.0/44.0) * aux6[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];

      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//                     Método Runge-Kutta-Verner II                 //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKV_6_5II(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/18.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/18.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1.0/12.0)) + (aux2[i] * (1.0/4.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (2.0/81.0)) + (aux2[i] * (4.0/27.0)) + (aux3[i] * (8.0/81.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/9.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (40.0/33.0)) - (aux2[i] * (4.0/11.0)) - (aux3[i] * (56.0/11.0)) + (aux4[i] * (54.0/11.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (369.0/73.0)) + (aux2[i] * (72.0/73.0)) + (aux3[i] * (5380.0/219.0)) - (aux4[i] * (12285.0/584.0)) + (aux5[i] * (2695.0/1752.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8716.0/891.0)) + (aux2[i] * (656.0/297.0)) + (aux3[i] * (39520.0/891.0)) - (aux4[i] * (416.0/11.0)) + (aux5[i] * (52.0/27.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (8.0/9.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3015.0/256.0)) - (aux2[i] * (9.0/4.0)) - (aux3[i] * (4219.0/78.0)) + (aux4[i] * (5985.0/128.0)) - (aux5[i] * (539.0/384.0)) + (aux7[i] * (693.0/3328.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         

         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i] = fabsl(  -((33.0/640.0) * aux1[i]) + ((132.0/325.0) * aux3[i]) - ((891.0/2240.0) * aux4[i]) + ((33.0/320.0) * aux5[i]) + ((73.0/700.0) * aux6[i]) - ((891.0/8320.0) * aux7[i]) -  ((2.0/35.0) * aux8[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux9[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux9[i]), (1.0/5.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux9[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += (((3.0/80.0) * aux1[i]) + ((4.0/25.0) * aux3[i]) + ((243.0/1120.0) * aux4[i]) + ((77.0/160.0) * aux5[i]) + ((73.0/700.0) * aux6[i]));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//     Método de un paso, paso variable Runge-Kutta-Verner de       //
//                           orden 6/7/10                           //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKV_7_6_10(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/12.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/12.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * (1.0/6.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/16.0)) + (aux3[i] * (3.0/16.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/4.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (21.0/16.0)) - (aux3[i] * (81.0/16.0)) + (aux4[i] * (9.0/2.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/4.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1344688.0/250563.0)) - (aux3[i] * (1709184.0/83521.0)) + (aux4[i] * (1365632.0/83521.0)) - (aux5[i] * (78208.0/250563.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (16.0/17.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (559.0/384.0)) + (aux3[i] * 6.0) - (aux4[i] * (204.0/47.0)) + (aux5[i] * (14.0/39.0)) - (aux6[i] * (4913.0/78208.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * 0.5);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (625.0/224.0)) + (aux3[i] * 12.0) - (aux4[i] * (456.0/47.0)) + (aux5[i] * (48.0/91.0)) + (aux6[i] * (14739.0/136864.0)) + (aux7[i] * (6.0/7.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (12253.0/99144.0)) + (aux3[i] * (16.0/27.0)) + (aux4[i] * (16.0/459.0)) + (aux5[i] * (29072.0/161109.0)) - (aux6[i] * (2023.0/75816.0)) + (aux7[i] * (112.0/12393.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (30517.0/2512.0)) - (aux3[i] * (7296.0/157.0)) + (aux4[i] * (268728.0/7379.0)) + (aux5[i] * (2472.0/2041.0)) - (aux6[i] * (3522621.0/10743824.0)) + (aux7[i] * (132.0/157.0)) - (aux9[i] * (12393.0/4396.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux10[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    


         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux11[i] = fabsl( ((17.0/2688.0) * aux1[i]) - ((272.0/4935.0) * aux4[i]) + ((272.0/273.0) * aux5[i]) - ((24137569.0/57482880.0) * aux6[i]) +  ((34.0/105.0) * aux7[i]) + ((7.0/90.0) * aux8[i]) - ((4131.0/3920.0) * aux9[i]) + ((157.0/1260.0) * aux10[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux11[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux11[i]), (1.0/6.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux11[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((7.0/90.0) * aux1[i]) + ((16.0/45.0) * aux4[i]) + ((16.0/45.0) * aux5[i]) + ((2.0/15.0) * aux7[i]) + ((7.0/90.0) * aux8[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//     Método de un paso, paso variable Runge-Kutta-Verner de       //
//                           orden 7/8/13                           //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKV_8_7_13(void)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/4.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/4.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0/72.0)) + (aux2[i] * (1.0/72.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/12.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/32.0)) + (aux3[i] * (3.0/32.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/8.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (106.0/125.0)) - (aux3[i] * (408.0/125.0)) + (aux4[i] * (352.0/125.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/5.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/48.0)) + (aux4[i] * (8.0/33.0)) + (aux5[i] * (125.0/528.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * 0.5);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1263.0/2401.0)) + (aux4[i] * (39936.0/26411.0)) - (aux5[i] * (64125.0/26411.0)) + (aux6[i] * (5520.0/2401.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (6.0/7.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (37.0/392.0)) + (aux5[i] * (1625.0/9408.0)) - (aux6[i] * (2.0/15.0)) + (aux7[i] * (61.0/6720.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/7.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (17176.0/25516.0)) - (aux4[i] * (47104.0/25515.0)) + (aux5[i] * (1325.0/504.0)) - (aux6[i] * (41792.0/25515.0)) + (aux7[i] * (20237.0/145800.0)) + (aux8[i] * (4312.0/6075.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (23834.0/180075.0)) - (aux4[i] * (77824.0/1980825.0)) - (aux5[i] * (636635.0/633864.0)) + (aux6[i] * (254048.0/300125.0)) - (aux7[i] * (183.0/7000.0)) + (aux8[i] * (8.0/11.0)) -  (aux9[i] * (324.0/3773.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/7.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux10[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    


         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (12733.0/7600.0)) - (aux4[i] * (20032.0/5225.0)) + (aux5[i] * (456485.0/80256.0)) - (aux6[i] * (42599.0/7125.0)) + (aux7[i] * (339227.0/912000.0)) - (aux8[i] * (1029.0/4180.0)) + (aux9[i] * (1701.0/1408.0)) + (aux10[i] * (5145.0/2432.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux11[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (27061.0/204120.0)) + (aux4[i] * (40448.0/280665.0)) - (aux5[i] * (1353775.0/1197504.0)) + (aux6[i] * (17662.0/25515.0)) - (aux7[i] * (71687.0/1166400.0)) + (aux8[i] * (98.0/225.0)) + (aux9[i] * (1.0/16.0)) + (aux10[i] * (3773.0/11664.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux12[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (11203.0/8680.0)) - (aux4[i] * (38144.0/11935.0)) + (aux5[i] * (2354425.0/458304.0)) - (aux6[i] * (84046.0/16275.0)) + (aux7[i] * (673309.0/1636800.0)) + (aux8[i] * (4704.0/8525.0)) + (aux9[i] * (9477.0/10912.0)) - (aux10[i] * (1029.0/992.0)) + (aux12[i] * (729.0/341.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux13[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux14[i] = fabsl( ((1.0/480.0) * aux1[i]) + ((16.0/375.0) * aux6[i]) + ((2401.0/528000.0) * aux7[i]) - ((2401.0/132000.0) * aux8[i]) -  ((243.0/14080.0) * aux9[i]) + ((2401.0/19200.0) * aux10[i]) + ((19.0/450.0) * aux11[i]) - ((243.0/1760.0) * aux12[i]) - ((31.0/720.0) * aux13[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux14[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux14[i]), (1.0/7.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux14[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((13.0/288.0) * aux1[i]) + ((32.0/125.0) * aux6[i]) + ((31213.0/144000.0) * aux7[i]) + ((2401.0/12375.0) * aux8[i]) + ((1701.0/14080.0) * aux9[i]) + ((2401.0/19200.0) * aux10[i]) + ((19.0/450.0) * aux11[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//     Método de un paso, paso variable Runge-Kutta-Fehlberg        //
//                          de orden 7/8/13                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKF_8_7_13(void)
//#error Revisar método (Control de error o ...)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2.0/27.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/27.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/36.0)) + (aux2[i] * (1.0/12.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/9.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/24.0)) + (aux3[i] * (1.0/8.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0/12.0)) - (aux3[i] * (25.0/16.0)) + (aux4[i] * (25.0/16.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/12.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/20.0)) + (aux4[i] * (1.0/4.0)) + (aux5[i] * (1.0/5.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * 0.5);

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (25.0/108.0)) + (aux4[i] * (125.0/108.0)) - (aux5[i] * (65.0/27.0)) + (aux6[i] * (125.0/54.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (31.0/300.0)) + (aux5[i] * (61.0/225.0)) - (aux6[i] * (2.0/9.0)) + (aux7[i] * (13.0/900.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 2.0) - (aux4[i] * (53.0/6.0)) + (aux5[i] * (704.0/45.0)) - (aux6[i] * (107.0/9.0)) + (aux7[i] * (67.0/90.0)) + (aux8[i] * 3.0); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (91.0/108.0)) + (aux4[i] * (23.0/108.0)) - (aux5[i] * (976.0/135.0)) + (aux6[i] * (311.0/54.0)) - (aux7[i] * (19.0/60.0)) + (aux8[i] * (17.0/6.0)) -  (aux9[i] * (1.0/12.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux10[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    


         // Actualiza valores
//         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2383.0/4100.0)) - (aux4[i] * (341.0/164.0)) + (aux5[i] * (4496.0/1025.0)) - (aux6[i] * (301.0/82.0)) + (aux7[i] * (2133.0/4100.0)) + (aux8[i] * (45.0/82.0)) + (aux9[i] * (45.0/164.0)) + (aux10[i] * (18.0/41.0)); 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2383.0/4100.0)) - (aux4[i] * (314.0/164.0)) + (aux5[i] * (4496.0/1025.0)) - (aux6[i] * (301.0/82.0)) + (aux7[i] * (2133.0/4100.0)) + (aux8[i] * (45.0/82.0)) + (aux9[i] * (45.0/164.0)) + (aux10[i] * (18.0/41.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux11[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/205.0)) - (aux6[i] * (6.0/41.0)) - (aux7[i] * (3.0/205.0)) - (aux8[i] * (3.0/41.0)) + (aux9[i] * (3.0/41.0)) + (aux10[i] * (6.0/41.0)); 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux12[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1777.0/4100.0)) - (aux4[i] * (341.0/164.0)) + (aux5[i] * (4496.0/1025.0)) - (aux6[i] * (289.0/82.0)) + (aux7[i] * (2193.0/4100.0)) + (aux8[i] * (51.0/82.0)) + (aux9[i] * (33.0/164.0)) + (aux10[i] * (12.0/41.0)) + aux12[i]; 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux13[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux14[i] = fabsl( ((41.0/840.0) * aux1[i]) + ((41.0/840.0) * aux11[i]) - ((41.0/840.0) * aux12[i]) - ((41.0/840.0) * aux13[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux14[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux14[i]), (1.0/7.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux14[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((41.0/840.0) * aux1[i]) + ((34.0/105.0) * aux6[i]) + ((9.0/35.0) * aux7[i]) + ((9.0/35.0) * aux8[i]) + ((9.0/280.0) * aux9[i]) + ((9.0/280.0) * aux10[i]) + ((41.0/840.0) * aux11[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
// Método de un paso, paso variable Prince-Dormand de orden 8/7/13  //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RK_8_7_13(void)
//#error Revisar método (Control de error o ...)
{
   int sw;
   long double delta, xdelta;

   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/18.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/18.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/48.0)) + (aux2[i] * (1.0/16.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/12.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/32.0)) + (aux3[i] * (3.0/32.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/8.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0/16.0)) - (aux3[i] * (75.0/64.0)) + (aux4[i] * (75.0/64.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/16.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0/80.0)) + (aux4[i] * (3.0/16.0)) + (aux5[i] * (3.0/20.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (3.0/8.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (29443841.0/614563906.0)) + (aux4[i] * (77736538.0/692538347.0)) - (aux5[i] * (28693883.0/1125000000.0)) + (aux6[i] * (23124283.0/1800000000.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (59.0/400.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (16016141.0/946692911.0)) + (aux4[i] * (61564180.0/158732637.0)) + (aux5[i] * (2278713.0/633445777.0)) + (aux6[i] * (545815736.0/2771057229.0)) - (aux7[i] * (180193667.0/1043307555.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (93.0/200.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (39632708.0/573591083)) - (aux4[i] * (433636366.0/683701615.0)) - (aux5[i] * (421739975.0/2616292301.0)) + (aux6[i] * (100302831.0/723423059.0)) + (aux7[i] * (790204164.0/839813087.0)) + (aux8[i] * (800635310.0/3783071287.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5490023248.0/9719169821.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (246121993.0/1340847787.0)) - (aux4[i] * (37695042795.0/15268766246.0)) - (aux5[i] * (309121774.0/1061227803.0)) - (aux6[i] * (12992083.0/490766935.0)) + (aux7[i] * (6005943493.0/2108947869.0)) + (aux8[i] * (393006217.0/1396673457.0)) + (aux9[i] * (123872331.0/1001029789.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (13.0/20.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux10[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    


         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1028468189.0/846180014.0)) + (aux4[i] * (8478235783.0/508512852.0)) + (aux5[i] * (1311729495.0/1432422823.0)) - (aux6[i] * (10304129995.0/1701304382.0)) - (aux7[i] * (48777925059.0/3047939560.0)) + (aux8[i] * (15336726248.0/1032824649.0)) - (aux9[i] * (45442868181.0/3398467696.0)) + (aux10[i] * (3065993473.0/597172653.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1201146811.0/1299019798.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux11[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (185892177.0/718116043.0)) - (aux4[i] * (3185094517.0/667107341.0)) - (aux5[i] * (477755414.0/1098053517.0)) - (aux6[i] * (703635378.0/230739211.0)) + (aux7[i] * (5731566787.0/1027545527.0)) + (aux8[i] * (523286602.0/850066563.0)) - (aux9[i] * (4093664535.0/808688257.0)) + (aux10[i] * (3962137247.0/1805957418.0)) + (aux11[i] * (65686358.0/487910083.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux12[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (403863854.0/491063109.0)) - (aux4[i] * (5068492393.0/434740067.0)) - (aux5[i] * (411421997.0/543043805.0)) + (aux6[i] * (652783627.0/914296604.0)) + (aux7[i] * (11173962825.0/925320556.0)) - (aux8[i] * (13158990841.0/6184727034.0)) + (aux9[i] * (3936647629.0/1978049680.0)) - (aux10[i] * (160528059.0/685178525.0)) + (aux11[i] * (248638103.0/1413531060.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux13[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux14[i] = fabsl( -((206899875720925.0/16966964735038208.0) * aux1[i]) - ((161224140072326693.0/208527862420056925.0) * aux6[i]) + ((308134860501296901.0/4283929245060770651.0) * aux7[i]) + ((187090058122256469.0/106070073963259076.0) * aux8[i]) - ((3721643503328385829.0/2082408744123259974.0) * aux9[i]) + ((290897219666967667.0/371523099811498965.0) * aux10[i]) - ((39496005864008611.0/501397231350176553.0) * aux11[i]) + ((627441401.0/2220607170.0) * aux12[i]) - ((1.0/4.0) * aux13[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux14[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux14[i]), (1.0/7.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux14[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ((13451932.0/455176623.0) * aux1[i]) - ((808719846.0/976000145.0) * aux6[i]) + ((1757004468.0/5645159321.0) * aux7[i]) + ((656045339.0/265891186.0) * aux8[i]) - ((3867574721.0/1518517206.0) * aux9[i]) + ((465885868.0/322736535.0) * aux10[i]) + ((53011238.0/667516719.0) * aux11[i]) + ((2.0/45.0) * aux12[i]);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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
//     Método de un paso, paso variable Runge-Kutta-Verner de       //
//                           orden 8/9/16                           //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::VS_RKV_9_8_16(void)
//#error Revisar método (Control de error o ...)
{
   int sw;
   long double delta, xdelta;
   long s6 = sqrtl(6.0);
   
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   At_Tiempo[Sistema_actual] = Tiempo_actual;
#ifdef _PASO_MINIMO_   
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
#else
   Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
#endif
   if(!Integracion_positiva) Paso *= - fabsl(Paso);
   Paso_integracion = Paso_minimo = fabsl(Paso);
   Paso_maximo = 0.0;

   // Si el reporte esta activo graba encabezado
   if (Reporte_activo) Detalle_reporte(-1);

   if (Visualiza_integracion) {
      // Dibuja la gráfica con puntos
      if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
   }

   // Ciclo del método numérico
   while(Tiempo_integracion < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Ciclo para ver si se acepta la integración
      do {
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
         t = At_Tiempo[Sistema_actual];

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/12.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/12.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/27.0)) + (aux2[i] * (2.0/27.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/9.0));

      
         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0/24.0)) + (aux3[i] * (1.0/8.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((4.0+94.0*s6)/375.0)) + (aux3[i] * ((-94.0-84.0*s6)/125.0)) + (aux4[i] * ((328.0+208.0*s6)/375.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * ((2.0+2.0*s6)/15.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((9.0-1.0*s6)/150.0)) + (aux4[i] * ((312.0+32.0*s6)/1425.0)) + (aux5[i] * ((69.0+29.0*s6)/570.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * ((6.0+1.0*s6)/15.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * ((927.0-347.0*s6)/1250.0)) + (aux4[i] * ((-16248.0+7328.0*s6)/9375.0)) + (aux5[i] * ((-489.0+179.0*s6)/3750.0)) + (aux6[i] * ((14268.0-5798.0*s6)/9375.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * ((6.0-1.0*s6)/15.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (2.0/27.0)) + (aux6[i] * ((16.0-1.0*s6)/54.0)) + (aux7[i] * ((16.0+1.0*s6)/54.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (2.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    
         
         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (19.0/256.0)) + (aux6[i] * ((118.0-23.0*s6)/512.0)) + (aux7[i] * ((118.0+23.0*s6)/512.0)) - (aux8[i] * (9.0/256.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/2.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux9[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (11.0/144.0)) + (aux6[i] * ((266.0-1.0*s6)/864.0)) + (aux7[i] * ((266.0+1.0*s6)/864.0)) - (aux8[i] * (1.0/16.0)) -  (aux9[i] * (8.0/27.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux10[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    


         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((5034-271.0*s6)/61440.0)) + (aux7[i] * ((7859.0-1626.0*s6)/10240.0)) + (aux8[i] * ((-2232.0+813.0*s6)/20480.0)) + (aux9[i] * ((-594.0+271.0*s6)/960.0)) + (aux10[i] * ((657.0-813.0*s6)/5120.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/4.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux11[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((5996.0-3794.0*s6)/405.0)) + (aux6[i] * ((-4342.0-338.0*s6)/9.0)) + (aux7[i] * ((154922.0-40458.0*s6)/135.0)) + (aux8[i] * ((-4176.0+3794.0*s6)/45.0)) + (aux9[i] * ((-340864.0+242816.0*s6)/405.0)) + (aux10[i] * ((26304.0-15176.0*s6)/45.0)) - (aux11[i] * (26624.0/81.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (4.0/3.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux12[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((3793.0+2168.0*s6)/103680.0)) + (aux6[i] * ((-4042.0+2263.0*s6)/13824.0)) + (aux7[i] * ((-231278.0+40717.0*s6)/69120.0)) + (aux8[i] * ((7947.0-2168.0*s6)/11520.0)) + (aux9[i] * ((1048.0-542.0*s6)/405.0)) + (aux10[i] * ((-1383.0+542.0*s6)/720.0)) + (aux11[i] * (2624.0/1053.0)) + (aux12[i] * (3.0/1664.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (5.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux13[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (137.0/1296.0)) + (aux6[i] * ((5642.0-337.0*s6)/864.0)) + (aux7[i] * ((5642.0+337.0*s6)/864.0)) - (aux8[i] * (299.0/48.0)) + (aux9[i] * (184.0/81.0)) - (aux10[i] * (44.0/9.0)) - (aux11[i] * (5120.0/1053.0)) - (aux12[i] * (11.0/468.0)) + (aux13[i] * (16.0/9.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux14[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((33617.0-2168.0*s6)/518400.0)) + (aux6[i] * ((-3846.0+31.0*s6)/13824.0)) + (aux7[i] * ((155338.0-52807.0*s6)/345600.0)) + (aux8[i] * ((-12537.0+2168.0*s6)/57600.0)) + (aux9[i] * ((92.0+542.0*s6)/2025.0)) + (aux10[i] * ((-1797.0-542.0*s6)/3600.0)) + (aux11[i] * (320.0/567.0)) - (aux12[i] * (1.0/1920.0)) + (aux13[i] * (4.0/105.0)); 
         t = At_Tiempo[Sistema_actual] + (Paso * (1.0/6.0));

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux15[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         // Actualiza valores
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * ((-36487.0-30352.0*s6)/279600.0)) + (aux6[i] * ((-29666.0-4499.0*s6)/7456.0)) + (aux7[i] * ((2779182.0-615973.0*s6)/186400.0)) + (aux8[i] * ((-94329.0+91056.0*s6)/93200.0)) + (aux9[i] * ((-232192.0+121408.0*s6)/17475.0)) + (aux10[i] * ((101226.0-22764.0*s6)/5825.0)) - (aux11[i] * (169984.0/9087.0)) - (aux12[i] * (87.0/30290.0)) + (aux13[i] * (492.0/1165.0)) + (aux15[i] * (1260.0/233.0)); 
         t = At_Tiempo[Sistema_actual] + Paso;

         // Calcula valores temporales
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux16[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso;
             // Controla los errores en el cálculo matemático
             if(ERROR_MATEMATICO) {
                Error_calculo();
                return;
             }
         }    

         
         delta = 1.0e+108;
         sw = 0;
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
             // Calcula con la ecuación diferencial
             aux17[i] = fabsl(  ((7.0/400.0) * aux1[i]) - ((63.0/200.0) * aux8[i]) + ((14.0/25.0) * aux9[i]) + ((21.0/20.0) * aux10[i]) + ((1024.0/975.0) * aux11[i]) + ((3.0/5200.0) * aux12[i]) + ((3.0/25.0) * aux13[i]) + ((9.0/280.0) * aux14[i]) - ((9.0/25.0) * aux15[i]) - ((233.0/4200.0) * aux16[i]) ) / fabsl(Paso);
             // Se evita que sea cero
             if (aux17[i] != 0.0) xdelta = 0.84 * powl((Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2] / aux17[i]), (1.0/8.0));
              else xdelta = 1.0e+308;
             // Toma la menor de las xdeltas
             if(xdelta < delta) delta = xdelta;
             if (aux17[i] > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2]) sw = 1;
         }
         
         // Ajusta el paso de integración
         if (sw && Paso > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
             if (delta < 0.1 || delta >= 1.0) {
                if (delta < 0.1) Paso *= 0.1;  
                if (delta >= 1.0) Paso *= 0.9;  
             } else Paso *= delta;              // Ajusta   
             // Revisa si es necesario ajustar el paso al mínimo dado
             if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) {
                Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
             }
         } else sw = 0;
      } while (sw);
         
      // Almacena el paso máximo y el mínimo
      if(fabsl(Paso) > Paso_maximo) Paso_maximo = fabsl(Paso);
      if(fabsl(Paso) < Paso_minimo) Paso_minimo = fabsl(Paso);
      
      // Actualiza las condiciones iniciales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++)  {
          At_Condicion[Sistema_actual][i] += ( ((103.0/1680.0) * aux1[i]) - ((27.0/140.0) * aux8[i]) + ((76.0/105.0) * aux9[i]) - ((201.0/280.0) * aux10[i]) + ((1024.0/1365.0) * aux11[i]) + ((3.0/7280.0) * aux12[i]) + ((12.0/35.0) * aux13[i]) +  ((9.0/280.0) * aux14[i]) );
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      if(!Integracion_positiva) Paso = - fabs(Paso);
      
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += Paso;
      Tiempo_integracion += fabsl(Paso);
      Paso_integracion = fabsl(Paso);
      // Actualiza el número de iteraciones
      Numero_iteraciones++;

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);
      
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
// Definir algún método para procesar mensajes pendientes del sistema
///////////////////////////////////////////////////////////////
#else 
         Application->ProcessMessages();
#endif      
         if(Suspende_Calculo) break;
      }
      #endif

      // Guarda el último valor calculado
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual = At_Tiempo[Sistema_actual];

      // Ajuste del paso de integración
      if (delta < 0.5 || delta > 2.0) {
          if (delta < 0.5) Paso *= 0.5;  
          if (delta > 2.0) Paso *= 2.0;  
      } else if (delta != 1.0)Paso *= delta;
              else Paso *= 1.1;   
      if(fabsl(Paso) < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4]) Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][4];
      
      // Revisa si es necesario ajustar el paso al máximo dado
      if (fabsl(Paso) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3]) {
         Paso = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][3];
      }
#ifdef _INTEGRAR_TIEMPO_EXACTO_      
      if ((Tiempo_integracion + fabsl(Paso)) > Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1]) {
         Paso = fabsl(Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][1] - Tiempo_integracion);
         if(!Integracion_positiva) Paso *= -1.0;
      }
#endif      

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }

   // Si el reporte esta activo genera en el reporte detalle del paso de integración
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









