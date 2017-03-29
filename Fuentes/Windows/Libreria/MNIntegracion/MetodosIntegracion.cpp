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





// Nombre de los métodos numéricos
const char *Metodos_integracion[] = {
   "Euler-Cauchy                            (1 order, Fixed 1 Step)",
   "Modified Euler-Cauchy                   (2 order, Fixed 1 Step)",
   "Midpoint                                (2 order, Fixed 1 Step)",
   "Heun                                    (2 order, Fixed 1 Step)",
   "Runge-Kutta I                           (3 order, Fixed 1 Step)",
   "Runge-Kutta II                          (3 order, Fixed 1 Step)",
   "3/8 Formula                             (4 order, Fixed 1 Step)",
   "Runge-Kutta Classical                   (4 order, Fixed 1 Step)", 
   "Runge-Kutta-Gill                        (4 order, Fixed 1 Step)",
   "England                                 (4 order, Fixed 1 Step)",
   "Runge-Kutta-Fehlberg                    (4 order, Fixed 1 Step)",
   "Runge-Kutta-Fehlberg I                  (5 order, Fixed 1 Step)",
   "England                                 (5 order, Fixed 1 Step)",
   "Kutta-Nyström                           (5 order, Fixed 1 Step)",
   "Runge-Kutta-Fehlberg II                 (5 order, Fixed 1 Step)",
   "Butcher                                 (6 order, Fixed 1 Step)",
   "Runge-Kutta-Fehlberg                    (6 order, Fixed 1 Step)",

   
   "Runge-Kutta                       (3(2) order, Variable 1 Step)",
   "Runge-Kutta-Fehlberg             (4(3) order), Variable 1 Step)",
   "Prince-Dormand                   (5(4)6 order, Variable 1 Step)",
   "Prince-Dormand I                 (5(4)7 order, Variable 1 Step)",
   "Prince-Dormand II                (5(4)7 order, Variable 1 Step)",
   "Runge-Kutta-Fehlberg              (5(4) order, Variable 1 Step)",
   "England                           (5(4) order, Variable 1 Step)",
   "Prince-Dormand                   (6(5)8 order, Variable 1 Step)",
   "Runge-Kutta-Fehlberg              (6(5) order, Variable 1 Step)",
   "Runge-Kutta-Verner I              (6(5) order, Variable 1 Step)",
   "Runge-Kutta-Verner II             (6(5) order, Variable 1 Step)",
   "Runge-Kutta-Verner              (7(6)10 order, Variable 1 Step)",
   "Runge-Kutta-Verner              (8(7)13 order, Variable 1 Step)",
   "Runge-Kutta-Fehlberg            (8(7)13 order, Variable 1 Step)",
   "Prince-Dormand                  (8(7)13 order, Variable 1 Step)",
   "Runge-Kutta-Verner              (9(8)16 order, Variable 1 Step)",

   "Adams-Bashforth                                       (2 Steps)",
   "Adams-Bashforth                                       (3 Steps)",
   "Milne                                                 (3 Steps)",
   "Adams-Bashforth                                       (4 Steps)",
   "Adams-Bashforth                                       (5 Steps)",
   "Adams-Bashforth                                       (6 Steps)",
   "Adams-Bashforth                                       (7 Steps)",
   
   "Adams-Bashforth-Moulton                               (3 order)",
   "Milne-Simpson                                         (3 order)",
   "Adams-Bashforth-Moulton                               (4 order)",
   "Adams-Bashforth-Moulton I                             (5 order)",
   "Adams-Bashforth-Moulton II                            (5 order)",
   "Adams-Bashforth-Moulton                               (6 order)",
   "Adams-Bashforth-Moulton                               (7 order)",
   
   "Adams-Bashforth-Moulton                (3 order, Variable Step)",
   "Adams-Bashforth-Moulton                (4 order, Variable Step)",
   "Adams-Bashforth-Moulton I              (5 order, Variable Step)",
   "Adams-Bashforth-Moulton II             (5 order, Variable Step)",
   "Adams-Bashforth-Moulton                (6 order, Variable Step)",
   "Adams-Bashforth-Moulton                (7 order, Variable Step)",

   "Extrapolation                                      (V.S. Gragg)",

   "Trapezium                          (A-stable Secant iterations)",
   "Regresive Euler                    (A-stable Secant iterations)"
};

// Nombre de los parametros del tipo 1
const char *Parametros_metodos_integracion1[] = {
   "Time:",
   "Step:"
};

// Nombre de los parametros del tipo 2
const char *Parametros_metodos_integracion2[] = {
   "Time:",
   "Tolerace:",
   "Maximum Step:",
   "Minimum Step:"
};

// Nombre de los parametros del tipo 3
const char *Parametros_metodos_integracion3[] = {
   "Time:",
   "Step:",
   "Tolerace:",
   "Iterations:",
   "Derivate step:"
};


//////////////////////////////////////////////////////////////////////
//           Inicializa la clase de métodos numéricos               //
//////////////////////////////////////////////////////////////////////
              
void Metodos_Numericos_Integracion::Inicializa(void)
{
   // Asignacion de los métodos numéricos
   Metodos[0]   = &Metodos_Numericos_Integracion::Euler;
   Metodos[1]   = &Metodos_Numericos_Integracion::Euler_modificado;
   Metodos[2]   = &Metodos_Numericos_Integracion::Punto_medio;
   Metodos[3]   = &Metodos_Numericos_Integracion::Heun;
   
   Metodos[4]   = &Metodos_Numericos_Integracion::RKI_3;
   Metodos[5]   = &Metodos_Numericos_Integracion::RKII_3;
   Metodos[6]   = &Metodos_Numericos_Integracion::F38_4;
   Metodos[7]   = &Metodos_Numericos_Integracion::RK_Clasico_4;
   Metodos[8]   = &Metodos_Numericos_Integracion::RK_Gill_4;
   Metodos[9]   = &Metodos_Numericos_Integracion::England_4;
   Metodos[10]  = &Metodos_Numericos_Integracion::RK_Fehlberg_4;
   Metodos[11]  = &Metodos_Numericos_Integracion::RK_FehlbergI_5;
   Metodos[12]  = &Metodos_Numericos_Integracion::England_5;
   Metodos[13]  = &Metodos_Numericos_Integracion::Kutta_Nystrom_5;
   Metodos[14]  = &Metodos_Numericos_Integracion::RK_FehlbergII_5;
   Metodos[15]  = &Metodos_Numericos_Integracion::Butcher_6;
   Metodos[16]  = &Metodos_Numericos_Integracion::RK_Fehlberg_6;
   
   Metodos[17]  = &Metodos_Numericos_Integracion::VS_RK_3_2;
   Metodos[18]  = &Metodos_Numericos_Integracion::VS_RKF_4_3;
   Metodos[19]  = &Metodos_Numericos_Integracion::VS_RK_5_4_6;
   Metodos[20]  = &Metodos_Numericos_Integracion::VS_RK_5_4_7I;
   Metodos[21]  = &Metodos_Numericos_Integracion::VS_RK_5_4_7II;
   Metodos[22]  = &Metodos_Numericos_Integracion::VS_RKF_5_4;
   Metodos[23]  = &Metodos_Numericos_Integracion::VS_RKE_5_4;
   Metodos[24]  = &Metodos_Numericos_Integracion::VS_RK_6_5_8;
   Metodos[25]  = &Metodos_Numericos_Integracion::VS_RKF_6_5;
   Metodos[26]  = &Metodos_Numericos_Integracion::VS_RKV_6_5I;
   Metodos[27]  = &Metodos_Numericos_Integracion::VS_RKV_6_5II;
   Metodos[28]  = &Metodos_Numericos_Integracion::VS_RKV_7_6_10;
   Metodos[29]  = &Metodos_Numericos_Integracion::VS_RKV_8_7_13;
   Metodos[30]  = &Metodos_Numericos_Integracion::VS_RK_8_7_13;
   Metodos[31]  = &Metodos_Numericos_Integracion::VS_RK_8_7_13;
   Metodos[32]  = &Metodos_Numericos_Integracion::VS_RKV_9_8_16;

   Metodos[33]  = &Metodos_Numericos_Integracion::Adams_Bashforth_2pasos;
   Metodos[34]  = &Metodos_Numericos_Integracion::Adams_Bashforth_3pasos;
   Metodos[35]  = &Metodos_Numericos_Integracion::Milne_3pasos;
   Metodos[36]  = &Metodos_Numericos_Integracion::Adams_Bashforth_4pasos;
   Metodos[37]  = &Metodos_Numericos_Integracion::Adams_Bashforth_5pasos;
   Metodos[38]  = &Metodos_Numericos_Integracion::Adams_Bashforth_6pasos;
   Metodos[39]  = &Metodos_Numericos_Integracion::Adams_Bashforth_7pasos;
   
   Metodos[40]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM3;
   Metodos[41]  = &Metodos_Numericos_Integracion::Predictor_corrector_MS3;
   Metodos[42]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM4;
   Metodos[43]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM5;
   Metodos[44]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM5a;
   Metodos[45]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM6;
   Metodos[46]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM7;
   
   Metodos[47]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM3PV;
   Metodos[48]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM4PV;
   Metodos[49]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM5PV;
   Metodos[50]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM5aPV;
   Metodos[51]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM6PV;
   Metodos[52]  = &Metodos_Numericos_Integracion::Predictor_corrector_ABM7PV;

   Metodos[53]  = &Metodos_Numericos_Integracion::Extrapolacion;
   Metodos[54]  = &Metodos_Numericos_Integracion::Trapecio_iteraciones_secante;
   Metodos[55]  = &Metodos_Numericos_Integracion::Euler_iteraciones_secante;

   Tipo_parametros_metodo_integracion[0] = 1;
   Tipo_parametros_metodo_integracion[1] = 1;
   Tipo_parametros_metodo_integracion[2] = 1;
   Tipo_parametros_metodo_integracion[3] = 1;
   
   Tipo_parametros_metodo_integracion[4] = 1;
   Tipo_parametros_metodo_integracion[5] = 1;
   Tipo_parametros_metodo_integracion[6] = 1;
   Tipo_parametros_metodo_integracion[7] = 1;
   Tipo_parametros_metodo_integracion[8] = 1;
   Tipo_parametros_metodo_integracion[9] = 1;
   Tipo_parametros_metodo_integracion[10] = 1;
   Tipo_parametros_metodo_integracion[11] = 1;
   Tipo_parametros_metodo_integracion[12] = 1;
   Tipo_parametros_metodo_integracion[13] = 1;
   Tipo_parametros_metodo_integracion[14] = 1;
   Tipo_parametros_metodo_integracion[15] = 1;
   Tipo_parametros_metodo_integracion[16] = 1;

   Tipo_parametros_metodo_integracion[17] = 2;
   Tipo_parametros_metodo_integracion[18] = 2;
   Tipo_parametros_metodo_integracion[19] = 2;
   Tipo_parametros_metodo_integracion[20] = 2;
   Tipo_parametros_metodo_integracion[21] = 2;
   Tipo_parametros_metodo_integracion[22] = 2;
   Tipo_parametros_metodo_integracion[23] = 2;
   Tipo_parametros_metodo_integracion[24] = 2;
   Tipo_parametros_metodo_integracion[25] = 2;
   Tipo_parametros_metodo_integracion[26] = 2;
   Tipo_parametros_metodo_integracion[27] = 2;
   Tipo_parametros_metodo_integracion[28] = 2;
   Tipo_parametros_metodo_integracion[29] = 2;
   Tipo_parametros_metodo_integracion[30] = 2;
   Tipo_parametros_metodo_integracion[31] = 2;
   Tipo_parametros_metodo_integracion[32] = 2;

   Tipo_parametros_metodo_integracion[33] = 1;
   Tipo_parametros_metodo_integracion[34] = 1;
   Tipo_parametros_metodo_integracion[35] = 1;
   Tipo_parametros_metodo_integracion[36] = 1;
   Tipo_parametros_metodo_integracion[37] = 1;
   Tipo_parametros_metodo_integracion[38] = 1;
   Tipo_parametros_metodo_integracion[39] = 1;
   Tipo_parametros_metodo_integracion[40] = 1;
   Tipo_parametros_metodo_integracion[41] = 1;
   Tipo_parametros_metodo_integracion[42] = 1;
   Tipo_parametros_metodo_integracion[43] = 1;
   Tipo_parametros_metodo_integracion[44] = 1;
   Tipo_parametros_metodo_integracion[45] = 1;
   Tipo_parametros_metodo_integracion[46] = 1;

   Tipo_parametros_metodo_integracion[47] = 2;
   Tipo_parametros_metodo_integracion[48] = 2;
   Tipo_parametros_metodo_integracion[49] = 2;
   Tipo_parametros_metodo_integracion[50] = 2;
   Tipo_parametros_metodo_integracion[51] = 2;
   Tipo_parametros_metodo_integracion[52] = 2;


////////////////////////////////////////////////////////////////
// #error estos son de otro tipo no implementado
   Tipo_parametros_metodo_integracion[53] = 2;
////////////////////////////////////////////////////////////////   
   Tipo_parametros_metodo_integracion[54] = 3;
   Tipo_parametros_metodo_integracion[55] = 3;
   Numero_iteraciones = 0;
   Paso_maximo = Paso_minimo = 0.0;
   Reporte_activo = false;
}

//////////////////////////////////////////////////////////////////////
//        Controla la integración n£merica del sistema              //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Integra_numericamente(const int ti)
{
   Integracion_positiva = ti;
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = Ac_Condicion[Sistema_actual][i];
   Tiempo_actual  = Ac_Tiempo[Sistema_actual];
   // Hace las conversiones necesarias en el caso de coordenadas polares
   if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
      long double xx,xy;
      Convierte_rectangulares_polares(Ac_Condicion[Sistema_actual][0], Ac_Condicion[Sistema_actual][1],xx,xy);
      c_ini[0] = xx;
      c_ini[1] = xy;
   } 
   Tiempo_integracion = 0.0;
   Numero_iteraciones = 0;
   Ultima_integracion = false;
   Suspende_Calculo = false;
   Visualiza_integracion = true;
   Visualiza_ultima_integracion = false;
   Posible_desbordamiento_numerico = false; 
   Paso_integracion  = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(!Integracion_positiva) Paso_integracion = - Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
   if(Guarda_posicion) {
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
      Tiempo_actual  = At_Tiempo[Sistema_actual];
   }
   if (Reporte_activo) Titulo_reporte();
     
   // Manda a ejecutar el metodo activo con las condiciones iniciales
   try {
      (this->*Metodos[Metodo_N_actual[Sistema_actual]])();
    } catch (...) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para visualizar errores
///////////////////////////////////////////////////////////////
#else 
      ShowMessage("Possible overflow, calculate stop");
#endif      
   };
}  



//////////////////////////////////////////////////////////////////////
//        Controla la integración n£merica del sistema              //
//////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Integracion::Mapeo_periodo(const int ti, const int num)
{
   for (int xi = 0; xi < num; xi++) {
      Integracion_positiva = ti;
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = Ac_Condicion[Sistema_actual][i];
      Tiempo_actual  = Ac_Tiempo[Sistema_actual];
      // Hace las conversiones necesarias en el caso de coordenadas polares
      if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
         long double xx,xy;
         Convierte_rectangulares_polares(Ac_Condicion[Sistema_actual][0], Ac_Condicion[Sistema_actual][1],xx,xy);
         c_ini[0] = xx;
         c_ini[1] = xy;
      } 
      Tiempo_integracion = 0.0;
      Numero_iteraciones = 0;
      Ultima_integracion = false;
      Suspende_Calculo = false;
      Visualiza_integracion = false;
      Visualiza_ultima_integracion = true; 
      Posible_desbordamiento_numerico = false;
      Paso_integracion  = Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][2];
      if(!Integracion_positiva) Paso_integracion *= -1.0;
      if(Guarda_posicion) {
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_ini[i] = At_Condicion[Sistema_actual][i];
         Tiempo_actual  = At_Tiempo[Sistema_actual];
      }
   //   if (Reporte_activo) Titulo_reporte();
     
      // Manda a ejecutar el metodo activo con las condiciones iniciales
      try {
         (this->*Metodos[Metodo_N_actual[Sistema_actual]])();
       } catch (...) {
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para visualizar errores
///////////////////////////////////////////////////////////////
#else 
         ShowMessage("Possible overflow, calculate stop");
#endif      
         Suspende_Calculo = true;
      };
      if(Suspende_Calculo || Posible_desbordamiento_numerico) break;
      Guarda_posicion = true;
   }
}  


// Visualiza el error en el calculo
void Metodos_Numericos_Integracion::Error_calculo(void)
{
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para visualizar errores
///////////////////////////////////////////////////////////////
#else 
   ShowMessage("There are error to calculate");
#endif      
   ERROR_MATEMATICO = 0;
}


// Visualiza el error del posible error de desbordamiento
int Metodos_Numericos_Integracion::Desbordamiento_numerico(void)
{
#ifndef __PROGRAMACION_BORLAND__    
///////////////////////////////////////////////////////////////
// #error Definir algún método para visualizar errores
///////////////////////////////////////////////////////////////
#else 
   Posible_desbordamiento_numerico = false;
   if (MessageBox(NULL,"Possible overflow, do you continue?","Numerical integrate",MB_YESNO + MB_ICONQUESTION)  == IDYES) return 0;
   Posible_desbordamiento_numerico = true;
#endif      
   return 1;
}


// Retorna el nombre del metodo numerico
const char *Metodos_Numericos_Integracion::Retorna_nombre_metodo_integracion(const int i)
{
   return (Metodos_integracion[i]);
}              

// Retorna el nombre del parametro dentro del metodo numerico
const char *Metodos_Numericos_Integracion::Retorna_nombre_parametro_metodo_integracion(const int tp, const int i)
{
   if (tp == 1) return (Parametros_metodos_integracion1[i]);
   if (tp == 2) return (Parametros_metodos_integracion2[i]);
   if (tp == 3) return (Parametros_metodos_integracion3[i]);
   return "";
}              


// Inicializa el reporte de integración
void Metodos_Numericos_Integracion::Inicializa_reporte(const char *nombre)
{
   Finaliza_reporte();
   Rep_num = new Ctrl_reporte;
   Rep_num->Parametros(0,66,120,REPORTE_GRABADO,LPT1,nombre);
   Reporte_activo = true;
}                    

// Finaliza el reporte de integración
void Metodos_Numericos_Integracion::Finaliza_reporte(void)
{
   if (Reporte_activo) {
      delete Rep_num;
      Rep_num = NULL;
      Reporte_activo = false;
   }
}                    



// Titulo en el reporte de integración
void Metodos_Numericos_Integracion::Titulo_reporte(void)
{
   int i2;
   // Datos del Laboratorio de Dinamica no Lineal
   Rep_num->Formato_impresion(1,1,"Laboratorio de Dinámica no Lineal");
   Rep_num->Formato_impresion(1,1,"Departamento de Matemáticas"); 
   Rep_num->Formato_impresion(1,1,"Facultad de Ciencias"); 
   Rep_num->Formato_impresion(1,1,"Universidad Nacional Autónoma de México");
   Rep_num->Formato_impresion(1,1,"México, D.F.");
   Rep_num->Formato_impresion(1,1,"Teléfono: (01-55) 56-22-48-70 y 69");
   Rep_num->Formato_impresion(1,1,"Fax: (01-55) 56-22-48-59");
   Rep_num->Formato_impresion(1,1,"E-mail: dinamica@www.dynamics.unam.edu"); 
   Rep_num->Formato_impresion(1,1,"Página: http://www.dynamics.unam.edu");


   // Nombre del sistema
   Rep_num->Formato_impresion(1,4,Nombre_sistema[Sistema_actual]);
   // Ecuaciones
   Rep_num->Formato_impresion(3,2,"Ecuations:");
   for (i2 = 0; i2 < Numero_ecuaciones[Sistema_actual]; i2++) {
       Rep_num->Formato_impresion(6,1,Nombre_ecuacion[Sistema_actual][i2]);
   }
   // Parámetros
   Rep_num->Formato_impresion(3,2,"Parameters:");
   if (Numero_parametros[Sistema_actual]) {
      for (i2 = 0; i2 < Numero_parametros[Sistema_actual]; i2++) {
          sprintf(C_imp,"%s = %1.16Lf",Nombre_parametro[Sistema_actual][i2],P[Sistema_actual][i2]);
          Rep_num->Formato_impresion(6,1,C_imp);
      }
   }
   // Imprime la configuración de los métodos numéricos
   Rep_num->Formato_impresion(3,2,"Numerical Method:");
   Rep_num->Formato_impresion(6,1,Metodos_integracion[Metodo_N_actual[Sistema_actual]]);
   for (i2 = 0; i2 < Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][0]; i2++) {
      if (Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][0] < 3.0) Rep_num->Formato_impresion(3,1,Parametros_metodos_integracion1[i2]);
       else Rep_num->Formato_impresion(6,1,Parametros_metodos_integracion2[i2]);
      sprintf(C_imp,"= %1.16Lf",Parametros_metodo[Sistema_actual][Metodo_N_actual[Sistema_actual]][i2+1]);
      Rep_num->Formato_impresion(20,0,C_imp);
   }
   // Titulo de los campos
   Rep_num->Formato_impresion(1,3,"");
   sprintf(C_imp,"Iteration         Step                Time");
   Rep_num->Formato_impresion(1,1,C_imp);
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
      Retorna_variable_ecuacion_sistema_activo(i+1,C_imp);
      Rep_num->Formato_impresion(60 + 20*i,0,C_imp);
   }
   Rep_num->Formato_impresion(1,2,"=======================================================================================");
}                    





// Detalle en el reporte de integración
void Metodos_Numericos_Integracion::Detalle_reporte(const int tp)
{
   Rep_num->Formato_impresion(1,1,"");
   // Iteración número y Paso de Integración
   sprintf(C_imp,"%6d   %+1.10Le",Numero_iteraciones,Paso_integracion);
   Rep_num->Formato_impresion(3,0,C_imp);
   if (tp < 0) {
      // Tiempo
      sprintf(C_imp,"%+1.10Le",At_Tiempo[Sistema_actual]);
      Rep_num->Formato_impresion(33,0,C_imp);
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
         // Condición inicial
         sprintf(C_imp,"%+1.10Le",At_Condicion[Sistema_actual][i]);
         Rep_num->Formato_impresion(53 + 20*i,0,C_imp);
      }
    } else {
      // Tiempo
      sprintf(C_imp,"%+1.10Le",tiempo[tp]);
      Rep_num->Formato_impresion(33,0,C_imp);
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
         // Condición inicial
         sprintf(C_imp,"%+1.10Le",paso[tp][i]);
         Rep_num->Formato_impresion(53 + 20*i,0,C_imp);
      }
   }
}





//////////////////////////////////////////////////////////////////////
//                                                                  //
// Genera n pasos homogeneamente espaciados usando el método        //
// Runge-Kutta-Fehlberg de orden 6                                  //
//                                                                  //
// Retorna (0) Sin errores                                          //
//         (1) Error al cálcular                                    //
//                                                                  //
//////////////////////////////////////////////////////////////////////
int Metodos_Numericos_Integracion::Genera_n_pasos(const int n_pasos, const long double incremento)
{
   int n = 0;
   while(n < n_pasos) {
      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i]; 
      t = tiempo[n];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * (1.0 / 6.0)); 
      t = tiempo[n] + (incremento * (1.0 / 6.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * (4.0 / 75.0)) + (aux2[i] * (16.0 / 75.0)); 
      t = tiempo[n] + (incremento * (4.0 / 15.0));
      
      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * (5.0 / 6.0)) - (aux2[i] * (8.0 / 3.0)) + (aux3[i] * (5.0 / 2.0));
      t = tiempo[n] + (incremento * (2.0 / 3.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] - (aux1[i] * (8.0 / 5.0)) + (aux2[i] * (144.0 / 25.0)) - (aux3[i] * 4.0) + (aux4[i] * (16.0 / 25.0));
      t = tiempo[n] + (incremento * (4.0 / 5.0));

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux5[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * (361.0 / 320.0)) - (aux2[i] * (18.0 / 5.0)) + (aux3[i] * (407.0 / 128.0)) - (aux4[i] * (11.0 / 80.0)) + (aux5[i] * (55.0 / 128.0));
      t = tiempo[n] + incremento;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux6[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }


      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] - (aux1[i] * (11.0 / 640.0)) + (aux3[i] * (11.0 / 256.0)) - (aux4[i] * (11.0 / 160.0)) + (aux5[i] * (11.0 / 256.0));
      t = tiempo[n];

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux7[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * (93.0 / 640.0)) - (aux2[i] * (18.0 / 5.0)) + (aux3[i] * (803.0 / 256.0)) - (aux4[i] * (11.0 / 160.0)) + (aux5[i] * (99.0 / 256.0)) + aux7[i];
      t = tiempo[n] + incremento;

      // Calcula valores temporales
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          // Calcula con la ecuación diferencial
          aux8[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el cálculo matemático
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }
      
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[n+1][i] = paso[n][i] + ((aux1[i] * (7.0 / 1408.0)) + (aux3[i] * (1125.0 / 2816.0)) + (aux4[i] * (9.0 / 32.0)) + (aux5[i] * (125.0 / 768.0)) + (aux7[i] * (5.0 / 66.0)) + (aux8[i] * (5.0 / 66.0)));
      }
      n++;
      tiempo[n] = tiempo[0] + (incremento * n);
   }
   return 0;
}


/*
// Runge Kutta 4 orden
{
   int n = 0;
   while(n < n_pasos) {
      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i]; 
      t = tiempo[n];

      // Primer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux1[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux1[i] * 0.5); 
      t = tiempo[n] + incremento * 0.5;

      // Segundo calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux2[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + (aux2[i] * 0.5); 
      
      // Tercer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux3[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = paso[n][i] + aux3[i];
      t = tiempo[n] + incremento;

      // Cuarto paso temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          // Controla los errores en el calculo matematico
          if(ERROR_MATEMATICO) {
             ERROR_MATEMATICO = 0;
             return 1;
          }
      }
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          paso[n+1][i] = paso[n][i] + (aux1[i] + (2.0 * aux2[i]) + (2.0 * aux3[i]) + aux4[i]) / 6.0;
      }
      n++;
      tiempo[n] = tiempo[0] + (incremento * n);
   }
   return 0;
}
*/





// Calcula el período de una trayectoria cerrada
void Metodos_Numericos_Integracion::Calculo_periodo_trayectoria_cerrada(const long double tiempo, const long double paso, const long double tiempo_no_revision, const long double tolerancia, long double &period)
{
   long double xperiod;
   // Transitorio
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = Ac_Condicion[Sistema_actual][i];
   t_i_rk = Ac_Tiempo[Sistema_actual];
   if (!Integra_sin_visualizacion(tiempo, paso)) {
      // Busqueda del período
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = At_Condicion[Sistema_actual][i];
      t_i_rk = At_Tiempo[Sistema_actual];
      if (!busqueda_periodo_trayectoria_cerrada(tiempo, paso, tiempo_no_revision, tolerancia, xperiod)) {
         period = xperiod;
         // Confirmación del período
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = At_Condicion[Sistema_actual][i];
         t_i_rk = At_Tiempo[Sistema_actual];
         if (!busqueda_periodo_trayectoria_cerrada(tiempo, paso, tiempo_no_revision, tolerancia, xperiod)) {
            if (fabs(period - xperiod) < 1e-3)  return;
         }
      }
   }
   period = 0.0;   
}


//////////////////////////////////////////////////////////////////////
// Busqueda del período de una trayectoria cerrada                  //
// Retorna (0) Sin errores                                          //
//         (1) Error en cálculo                                     //
//         (2) Desbordamiento de limites                            //
//////////////////////////////////////////////////////////////////////

int Metodos_Numericos_Integracion::busqueda_periodo_trayectoria_cerrada(const long double tiempo, const long double incremento, const long double tiempo_no_revision, const long double tolerancia, long double &period)
{
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_i_rk[i];
   At_Tiempo[Sistema_actual] = t_i_rk;
   Tiempo_integracion = 0.0;
   Numero_iteraciones = 0;
   period = 0.0;

   long double Base[NUMERO_ECUACIONES];
   int sw = 0;
   // Iniciación de la Base con las condiciones iniciales
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) Base[i] = c_i_rk[i];
   
   while(Tiempo_integracion < tiempo) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Primer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux1[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += incremento * 0.5;

      // Segundo calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux2[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * 0.5); 
      
      // Tercer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux3[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + aux3[i];
      t = At_Tiempo[Sistema_actual] + incremento;

      // Cuarto paso temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux4[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (2.0 * aux2[i]) + (2.0 * aux3[i]) + aux4[i]) / 6.0;
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza el numero de iteraciones expl
      Numero_iteraciones ++;
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += incremento;
      Tiempo_integracion = Numero_iteraciones * fabsl(incremento);

      if (Tiempo_integracion > tiempo_no_revision) {
         sw = 0;
         // Revisa si esta cerca de la condición inicial base 
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
            if (fabsl(At_Condicion[Sistema_actual][i] - Base[i]) > tolerancia) sw = 1;
         }
         // Si esta cerca
         if (!sw) {
            // Guarda el periodo
            period = Tiempo_integracion;
            return 0;
         }
      }

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   return 0;
}




//////////////////////////////////////////////////////////////////////
//                                                                  //
// Integra sin visualizar usando el Método:                         //
// Runge-Kutta orden 4                                              //
//                                                                  //
//                                                                  //
// Retorna (0) Sin errores                                          //
//         (1) Error en cálculo                                     //
//         (2) Desbordamiento de limites                            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

int Metodos_Numericos_Integracion::Integra_sin_visualizacion(const long double tiempo, const long double incremento)
//#cambiarlo por algun otro metodo de paso variable 
{
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) At_Condicion[Sistema_actual][i] = c_i_rk[i];
   At_Tiempo[Sistema_actual] = t_i_rk;
   Tiempo_integracion = 0.0;
   Numero_iteraciones = 0;
   
   while(Tiempo_integracion < tiempo) {
      // Acciones a realizar antes de integrar
      Antes_integrar(0);

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i]; 
      t = At_Tiempo[Sistema_actual];

      // Primer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux1[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux1[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux1[i] * 0.5); 
      t += incremento * 0.5;

      // Segundo calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux2[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux2[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores 
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + (aux2[i] * 0.5); 
      
      // Tercer calculo temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux3[i] = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux3[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza valores
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) X[i] = At_Condicion[Sistema_actual][i] + aux3[i];
      t = At_Tiempo[Sistema_actual] + incremento;

      // Cuarto paso temporal
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          try {
             aux4[i]  = ( this->*funcion[Sistema_actual][i] )() * incremento;
          } catch (...) {return 1;}
          // Controla los errores en el calculo matematico
          if(fabsl(aux4[i]) > MAX_VALOR[Sistema_actual]) return 2;
      }
      // Obtiene la siguiente condición inicial    
      for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          At_Condicion[Sistema_actual][i] += (aux1[i] + (2.0 * aux2[i]) + (2.0 * aux3[i]) + aux4[i]) / 6.0;
          // Controla el desbordamiento numerico
          if(fabsl(At_Condicion[Sistema_actual][i]) > MAX_VALOR[Sistema_actual]) return 2;
      }

      // Actualiza el numero de iteraciones expl
      Numero_iteraciones ++;
      // Actualiza el tiempo
      At_Tiempo[Sistema_actual] += incremento;
      Tiempo_integracion = Numero_iteraciones * fabsl(incremento);

      // Acciones a realizar después de integrar
      Despues_integrar(0);
   }
   return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////









// Extrapolación
////////////////////////////////////////////////////////////////////////////////////
//                             Método de Extrapolación                            //
////////////////////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Integracion::Extrapolacion(void)
{
   Predictor_corrector_ABM5PV();
}



