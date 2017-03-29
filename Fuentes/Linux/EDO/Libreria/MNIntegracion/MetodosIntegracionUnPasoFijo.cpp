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
//                          de paso fijo                           //
//                                                                 //
//                                                                 //
// Euler-Cauchy             (1 order)                              //
// Modified Euler-Cauchy    (2 order)                              //
// Midpoint                 (2 order)                              //
// Heun                     (2 order)                              //
// Runge-Kutta I            (3 order)                              //
// Runge-Kutta II           (3 order)                              //
// 3/8 Formula              (4 order)                              //
// Runge-Kutta Classical    (4 order)                              //
// Runge-Kutta-Gill         (4 order)                              //
// England                  (4 order)                              //
// Runge-Kutta-Fehlberg     (4 order)                              //
// Runge-Kutta-Fehlberg I   (5 order)                              //
// England                  (5 order)                              //
// Kutta-Nyström            (5 order)                              //
// Runge-Kutta-Fehlberg II  (5 order)                              //
// Butcher                  (6 order)                              //
// Runge-Kutta-Fehlberg     (6 order)                              //
//                                                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                    Método de orden uno                           //
//                                                                  //
// Euler-Cauchy                                                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//               Método de integración Euler-Cauchy                 //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Euler(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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
      
      // Actualiza valores
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Cálculo con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] * Paso_integracion);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }
      
      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con líneas
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


      // Guarda el último valor calculado
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




/////////////////////////////////////////////////////////////////////
//                                                                 //
//                 Métodos de integración númerica                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////
//                                                                  //
//                   Métodos de orden dos                           //
//                                                                  //
// Euler-Cauchy Modificado                                          //
// Punto medio                                                      //
// Heun                                                             //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//             Método de integración Euler modificado               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Euler_modificado(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores 
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
     
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Cálculo con la ecuación diferencial
          aux1[i]  = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] += (aux1[i] * Paso_integracion);
      t += Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux2[i]   = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (((aux1[i] + aux2[i]) * 0.5) * Paso_integracion);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif 
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

      if (Visualiza_integracion) {
         // Dibuja la gráfica con puntos
         if(Grafica_puntos[Sistema_actual]) Dibuja_punto(At_Condicion[Sistema_actual],At_Tiempo[Sistema_actual],Color_Integracion);
         // Dibuja la gráfica con líneas
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

      // Guarda el último valor calculado
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
//                 Método de integración Punto medio                //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Punto_medio(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
     
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Cálculo con la ecuación diferencial
          aux1[i]  = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] += (aux1[i] * Paso_integracion * 0.5);
      t += (Paso_integracion * 0.5);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux2[i]   = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {    
          At_Condicion[Sistema_actual][i] += (aux2[i] * Paso_integracion);
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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
// #error Definir algún método para procesar mensajes pendientes del sistema
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
//                    Método de integración Heun                    //
//                                                                  //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Heun(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores 
      t = At_Tiempo[Sistema_actual];
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
     
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i]  = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] += (((aux1[i] * Paso_integracion) * 2) / 3);
      t += ((Paso_integracion * 2) / 3);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux2[i]   = ( this->*funcion[Sistema_actual][i] )();
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] + (3 * aux2[i])) * Paso_integracion) / 4;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif 
      }

      // Actualiza el número de iteraciones
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
// #error Definir algún método para procesar mensajes pendientes del sistema
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
//                    Métodos de orden tres                         //
//                                                                  //
//  Runge-Kutta I                                                   //
//  Runge-Kutta II                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//               Método Runge-Kutta I de orden 3                    //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RKI_3(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += Paso_integracion * 0.5;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - aux1[i] + (2.0 * aux2[i]);
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (4.0 * aux2[i]) + aux3[i]) / 6.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//               Método Runge-Kutta II de orden 3                   //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RKII_3(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 3.0)); 
      t += Paso_integracion * (1.0 / 3.0);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + ((2.0/3.0) * aux2[i]);
      t = At_Tiempo[Sistema_actual] + (Paso_integracion  * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (3.0 * aux3[i])) / 4.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//                    Métodos de orden cuatro                       //
//                                                                  //
// Formula 3/8                                                      //
// Runge-Kutta Clásico                                              //
// Runge-Kutta-Gill                                                 //
// England                                                          //
// Runge-Kutta-Fehlberg                                             //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                 Método Formula 3/8 de orden 4                    //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::F38_4(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 3.0)); 
      t += Paso_integracion * (1.0 / 3.0);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1.0 / 3.0)) + aux2[i]; 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + aux1[i] - aux2[i] + aux3[i];
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (3.0 * aux2[i]) + (3.0 * aux3[i]) + aux4[i]) / 8.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//             Método Runge-Kutta clásico de orden 4                //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_Clasico_4(void)
{ 
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

////////////////////////////////////////////////////////////////////////
// Grafica el parametro contra el tiempo cada vez que integre
/* 
      C_3D aux;
      if (Sistema_actual == 0) {
          aux.x = At_Tiempo[Sistema_actual];
          aux.z = 0;
          aux.y = P[Sistema_actual][3]*P[Sistema_actual][13];
          if (P[Sistema_actual][14]) Control_Visualizacion::Dibuja_punto(aux,Color_Integracion);
          aux.y = -1.0;
          if (P[Sistema_actual][15]) {
              if (P[Sistema_actual][16]) Control_Visualizacion::Dibuja_punto(aux,Color_Integracion);
          }
       } else {
          aux.x = At_Tiempo[Sistema_actual];
          aux.z = 0;
          aux.y = P[Sistema_actual][21]*P[Sistema_actual][17];
          if (P[Sistema_actual][15]) Control_Visualizacion::Dibuja_punto(aux,Color_Integracion);

          aux.y = P[Sistema_actual][3]*P[Sistema_actual][18];
          if (P[Sistema_actual][16]) Control_Visualizacion::Dibuja_punto(aux,Color_Integracion);

          aux.y = -1.0;
          if (P[Sistema_actual][19]) {
              if (P[Sistema_actual][20]) Control_Visualizacion::Dibuja_punto(aux,Color_Integracion);
          }
      }
*/      
////////////////////////////////////////////////////////////////////////      
      
      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += Paso_integracion * 0.5;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * 0.5); 
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + aux3[i];
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (2.0 * aux2[i]) + (2.0 * aux3[i]) + aux4[i]) / 6.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
      Numero_iteraciones ++;
      // Actualiza el tiempo
#ifdef _INTEGRAR_TIEMPO_EXACTO_
      if (Ultima_integracion) { 
         At_Tiempo[Sistema_actual] += Paso_integracion;
         Tiempo_integracion += fabsl(Paso_integracion);
       } else {
////////////////////////////////////////////////////////////////////////
// Control del tiempo de integracion 
///* 
         At_Tiempo[Sistema_actual] += Paso_integracion;
//*/      
////////////////////////////////////////////////////////////////////////      
//         At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
         Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
      }
#else      
      At_Tiempo[Sistema_actual] = tiempo_inicial  + (Paso_integracion * Numero_iteraciones);
      Tiempo_integracion = Numero_iteraciones * fabsl(Paso_integracion);
#endif

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//              Método Runge-Kutta-Gill de orden 4                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_Gill_4(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += Paso_integracion * 0.5;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * 0.5) + (aux1[i] * (sqrtl(2.0)* 0.5))  + (aux2[i] * ((1.0 - (sqrtl(2.0)) * 0.5))); 
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux2[i] * (sqrtl(2.0) / 2.0)) + aux3[i] + (aux3[i] * (sqrtl(2.0)* 0.5));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (aux2[i] * (2.0 - sqrtl(2.0))) + (aux3[i] * (2.0 + sqrtl(2.0))) + aux4[i]) / 6.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//                  Método England de orden 4                       //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::England_4(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += Paso_integracion * 0.5;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.25) + (aux2[i] * 0.25); 
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - aux2[i] + (aux3[i] * 2.0);
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (4.0 * aux3[i]) + aux4[i]) / 6.0;
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//           Método Runge-Kutta-Fehlberg de orden 4                 //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_Fehlberg_4(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.25); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.25);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0 / 32.0)) + (aux2[i] * (9.0 / 32.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (3.0 / 8.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1932.0 / 2197.0)) - (aux2[i] * (7200.0 / 2197.0)) + (aux3[i] * (7296.0 / 2197));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (12.0 / 13.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (439.0 / 216.0)) - (aux2[i] * 8.0) + (aux3[i] * (3680.0 / 513.0)) - (aux4[i] * (845.0 / 4104.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (25.0 / 216.0)) + (aux3[i] * (1408.0 / 2565.0)) + (aux4[i] * (2197.0 / 4104.0)) - (aux5[i] * (1.0 / 5.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//                    Métodos de orden cinco                        //
//                                                                  //
// Runge-Kutta-Fehlberg I                                           //
// England                                                          //
// Kutta-Nyström                                                    //
// Runge-Kutta-Fehlberg II                                          //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//          Método Runge-Kutta-Fehlberg I de orden 5                //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_FehlbergI_5(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.25); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.25);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (3.0 / 32.0)) + (aux2[i] * (9.0 / 32.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (3.0 / 8.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1932.0 / 2197.0)) - (aux2[i] * (7200.0 / 2197.0)) + (aux3[i] * (7296.0 / 2197));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (12.0 / 13.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (439.0 / 216.0)) - (aux2[i] * 8.0) + (aux3[i] * (3680.0 / 513.0)) - (aux4[i] * (845.0 / 4104.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8.0 / 27.0)) + (aux2[i] * 2.0) - (aux3[i] * (3544.0 / 2565.0)) + (aux4[i] * (1859.0 / 4104.0)) - (aux5[i] * (11.0 / 40.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.5);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (16.0 / 135.0)) + (aux3[i] * (6656.0 / 12825.0)) + (aux4[i] * (28561.0 / 56430.0)) - (aux5[i] * (9.0 / 50.0)) + (aux6[i] * (2.0 / 55.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//                Método England de orden 5                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::England_5(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.5);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.25) + (aux2[i] * 0.25); 
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - aux2[i] + (aux3[i] * 2.0);
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (7.0 / 27.0)) + (aux2[i] * (10.0 / 27.0)) + (aux4[i] * (1.0 / 27.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (28.0 / 625.0)) - (aux2[i] * (125.0 / 625.0)) + (aux3[i] * (546.0 / 625.0)) + (aux4[i] * (54.0 / 625.0)) - (aux5[i] * (378.0 / 625.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 5.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (14.0 / 336.0)) + (aux4[i] * (35.0 / 336.0)) + (aux5[i] * (162.0 / 336.0)) + (aux6[i] * (125.0 / 336.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//              Método Kutta-Nyström de orden 5                     //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Kutta_Nystrom_5(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 3.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (4.0 / 25.0)) + (aux2[i] * (6.0 / 25.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 5.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 4.0)) - (aux2[i] * (12.0 / 4.0)) + (aux3[i] * (15.0 / 4.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (6.0 / 81.0)) + (aux2[i] * (90.0 / 81.0)) - (aux3[i] * (50.0 / 81.0)) + (aux4[i] * (8.0 / 81.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (6.0 / 75.0)) + (aux2[i] * (36.0 / 75.0)) + (aux3[i] * (10.0 / 75.0)) + (aux4[i] * (8.0 / 75.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (4.0 / 5.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (23.0 / 192.0)) + (aux3[i] * (125.0 / 192.0)) - (aux5[i] * (81.0 / 192.0)) + (aux6[i] * (125.0 / 192.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//          Método Runge-Kutta-Fehlberg II de orden 5               //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_FehlbergII_5(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 6.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 6.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (4.0 / 75.0)) + (aux2[i] * (16.0 / 75.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (4.0 / 15.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0 / 6.0)) - (aux2[i] * (8.0 / 3.0)) + (aux3[i] * (5.0 / 2.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8.0 / 5.0)) + (aux2[i] * (144.0 / 25.0)) - (aux3[i] * 4.0) + (aux4[i] * (16.0 / 25.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (4.0 / 5.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (361.0 / 320.0)) - (aux2[i] * (18.0 / 5.0)) + (aux3[i] * (407.0 / 128.0)) - (aux4[i] * (11.0 / 80.0)) + (aux5[i] * (55.0 / 128.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (31.0 / 384.0)) + (aux3[i] * (1125.0 / 2816.0)) + (aux4[i] * (9.0 / 32.0)) + (aux5[i] * (125.0 / 768.0)) + (aux6[i] * (5.0 / 66.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//                    Métodos de orden seis                         //
//                                                                  //
// Butcher                                                          //
// Runge-Kutta-Fehlberg                                             //
//                                                                  //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Método Butcher de orden 6                       //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Butcher_6(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 3.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * (2.0 / 3.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 12.0)) + (aux2[i] * (1.0 / 3.0)) - (aux3[i] * (1.0 / 12.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (1.0 / 16.0)) + (aux2[i] * (9.0 / 8.0)) - (aux3[i] * (3.0 / 16.0)) - (aux4[i] * (3.0 / 8.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.5);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * (9.0 / 8.0)) - (aux3[i] * (3.0 / 8.0)) - (aux4[i] * (3.0 / 4.0)) + (aux5[i] * 0.5);
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * 0.5);

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (9.0 / 44.0)) - (aux2[i] * (9.0 / 11.0)) + (aux3[i] * (63.0 / 44.0)) + (aux4[i] * (18.0 / 11.0)) - (aux6[i] * (16.0 / 11.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (11.0 / 120.0)) + (aux3[i] * (27.0 / 40.0)) + (aux4[i] * (27.0 / 40.0)) - (aux5[i] * (4.0 / 15.0)) - (aux6[i] * (4.0 / 15.0)) + (aux7[i] * (11.0 / 120.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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
//             Método Runge-Kutta-Fehlberg de orden 6               //
//                                                                  //
//////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::RK_Fehlberg_6(void)
{
   // Inicializa las variables
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_ini[i];
   tiempo_inicial = At_Tiempo[Sistema_actual] = Tiempo_actual;

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

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (1.0 / 6.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (1.0 / 6.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (4.0 / 75.0)) + (aux2[i] * (16.0 / 75.0)); 
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (4.0 / 15.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (5.0 / 6.0)) - (aux2[i] * (8.0 / 3.0)) + (aux3[i] * (5.0 / 2.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (8.0 / 5.0)) + (aux2[i] * (144.0 / 25.0)) - (aux3[i] * 4.0) + (aux4[i] * (16.0 / 25.0));
      t = At_Tiempo[Sistema_actual] + (Paso_integracion * (4.0 / 5.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (361.0 / 320.0)) - (aux2[i] * (18.0 / 5.0)) + (aux3[i] * (407.0 / 128.0)) - (aux4[i] * (11.0 / 80.0)) + (aux5[i] * (55.0 / 128.0));
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] - (aux1[i] * (11.0 / 640.0)) + (aux3[i] * (11.0 / 256.0)) - (aux4[i] * (11.0 / 160.0)) + (aux5[i] * (11.0 / 256.0));
      t = At_Tiempo[Sistema_actual];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * (93.0 / 640.0)) - (aux2[i] * (18.0 / 5.0)) + (aux3[i] * (803.0 / 256.0)) - (aux4[i] * (11.0 / 160.0)) + (aux5[i] * (99.0 / 256.0)) + aux7[i];
      t = At_Tiempo[Sistema_actual] + Paso_integracion;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * Paso_integracion;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             Error_calculo();
             return;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += ((aux1[i] * (7.0 / 1408.0)) + (aux3[i] * (1125.0 / 2816.0)) + (aux4[i] * (9.0 / 32.0)) + (aux5[i] * (125.0 / 768.0)) + (aux7[i] * (5.0 / 66.0)) + (aux8[i] * (5.0 / 66.0)));
          #ifdef _VALIDA_CALCULO_
          // Controla el desbordamiento numérico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) {
             if(Desbordamiento_numerico()) return;
          }
          #endif
      }

      // Actualiza el número de iteraciones
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

      // Si el reporte esta activo genera en el reporte el detalle de la integración
      if (Reporte_activo) Detalle_reporte(-1);

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

      // Guarda el último valor calculado
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


