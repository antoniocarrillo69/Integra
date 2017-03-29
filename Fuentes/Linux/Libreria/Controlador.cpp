//////////////////////////////////////////////////////////////////////////////////////////////
// Control del sistema                                                                      //
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


#include "Controlador.hpp"
#include "../Libreria/Gen_rep.hpp"
#include <math.h>
#ifdef __PROGRAMACION_BORLAND__
#include <io.h>
#else
#include <unistd.h>
#endif

// Incrementa la condicion inicial
void Controlador::Condicion_inicial(const int x, const int y, const int z)
{
   if (x > 0) Incrementa_condicion_inicial(true,false,false);
   if (x < 0) Decrementa_condicion_inicial(true,false,false);
   if (y > 0) Incrementa_condicion_inicial(false,true,false);
   if (y < 0) Decrementa_condicion_inicial(false,true,false);
   if (z > 0) Incrementa_condicion_inicial(false,false,true);
   if (z < 0) Decrementa_condicion_inicial(false,false,true);
   Poner_cursor();
}



// Establece las dimensiones del sistema actual
void Controlador::Establece_dimensiones_sistema(Dimension_Ventana dim, const long double todos, const long double factor)
{
   long double xdim, max;
   // Revisa y ajusta el orden de los puntos inicial y final de la ventana
   if (dim.Xi > dim.Xf) xdim = dim.Xf, dim.Xi = dim.Xf, dim.Xf = xdim;
   if (dim.Yi > dim.Yf) xdim = dim.Yf, dim.Yi = dim.Yf, dim.Yf = xdim;
   if (dim.Zi > dim.Zf) xdim = dim.Zf, dim.Zi = dim.Zf, dim.Zf = xdim;

   if (dim.Xi < dim.Xf && dim.Yi < dim.Yf && dim.Zi < dim.Zf) {
      // Actualiza la Dimension de la ventana (Todos)
      if (todos > 0.0) dim.Xi = -todos, dim.Xf = todos, dim.Yi = -todos, dim.Yf = todos, dim.Zi = -todos, dim.Zf = todos;
      // Actualiza la Dimension de la ventana (Factor)
      if (factor > 0.0) dim.Xi *= factor, dim.Xf *= factor, dim.Yi *= factor, dim.Yf *= factor, dim.Zi *= factor, dim.Zf *= factor;
      if (Retorna_tipo_ventana() == EJES_COORDENADAS_POLARES) {
         // Homogeniza dimensiones de los ejes coordenados en 2D y 3D
         max = fabsl(dim.Xi) > fabsl(dim.Xf) ? fabsl(dim.Xi) : fabsl(dim.Xf);
         dim.Xi = -max, dim.Xf = max;
         max = fabsl(dim.Yi) > fabsl(dim.Yf) ? fabsl(dim.Yi) : fabsl(dim.Yf);
         dim.Yi = -max, dim.Yf = max;
         max = fabsl(dim.Zi) > fabsl(dim.Zf) ? fabsl(dim.Zi) : fabsl(dim.Zf);
         dim.Zi = -max, dim.Zf = max;
      }
      // Actualiza la dimension de los ejes coordenados
      Dimensiones[Sistema_actual] = dim;
      // Actualiza la dimension de la ventana de trabajo
      Base_Ventana_Graficacion::Establece_Dimensiones(Dimensiones[Sistema_actual]);
      // Ajusta tamano de vestores del campo vectorial
      AjustaConfiguracionCampoVectorial(Sistema_actual); 
      // Actualiza los valores para evitar overflow
      Actualiza_valores_evitar_overflow(Sistema_actual);
      // Limpia la ventana sin conservar la posición de la última integración
      Limpiar_ventana_sin_conservar_condicion_inicial();
      // Define el paso del cursor
      Paso_cursor[Sistema_actual].x = ((Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) / 200.0);
      Paso_cursor[Sistema_actual].y = ((Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) / 200.0);
      Paso_cursor[Sistema_actual].z = ((Dimensiones[Sistema_actual].Zf - Dimensiones[Sistema_actual].Zi) / 200.0);
      // Define el incremento del paso del cursor
      Incremento_paso_cursor[Sistema_actual].x = Paso_cursor[Sistema_actual].x;
      Incremento_paso_cursor[Sistema_actual].y = Paso_cursor[Sistema_actual].y;
      Incremento_paso_cursor[Sistema_actual].z = Paso_cursor[Sistema_actual].z;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//#error Se agrega esto para evitar el error que se genera al tener ejes coordenados en 2D y seleccionar
// una ventana que este fuera de los ejes coordenados, por ello se cambia a ventana de 2D.
      // Cambia el tipo de ventana de ejes coordenados 2D a Ventana de 2D si la ventana esta fuera de los ejes coordenados
      if (Ventana_activa[Sistema_actual] == EJES_COORDENADOS_2D) {
         bool sw = false;
         if (dim.Xi > 0.0 && dim.Yi > 0.0) sw = true;
         if (dim.Xi > 0.0 && dim.Yi < 0.0) sw = true;
         if (dim.Xf < 0.0 && dim.Yf > 0.0) sw = true;
         if (dim.Xf < 0.0 && dim.Yi < 0.0) sw = true;
         if (sw) Establece_tipo_ventana(VENTANA_2D);
      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
   } 
}


// Actualiza el escenario Grafico
void Controlador::Actualiza_escenario(void)
{
   if (!Visualizacion_simultanea[Sistema_actual]) {
      if (Ventana_activa[Sistema_actual] >= 0) {
          if (Ventana_activa[Sistema_actual] == EJES_COORDENADAS_POLARES) {
            if (Escenario[Sistema_actual].z == 0) Establece_tipo_ventana(Ventana_activa[Sistema_actual]);
             else Establece_tipo_ventana(EJES_COORDENADOS_2D);
          } else Establece_tipo_ventana(Ventana_activa[Sistema_actual]);
       } else {
         if (Escenario[Sistema_actual].z == 0) Establece_tipo_ventana(EJES_COORDENADOS_2D);
          else Establece_tipo_ventana(EJES_COORDENADOS_3D);
      } 
      char xcad[100], ycad[100], zcad[100];
      // Asigna nombres a los ejes coordenados
      Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].x, xcad);
      Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].y, ycad);
      Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].z, zcad);
      Establece_nombre_ejes(xcad, ycad, zcad);
    } else {
      char xcad[100], xcadfin[400];
      // Fija escenario en 2D para cursos temporales multiples
      Establece_tipo_ventana(EJES_COORDENADOS_2DM);
      // Asigna nombres a los ejes coordenados
      Retorna_variable_ecuacion_sistema_activo(Retorna_escenarios_visualizar(0), xcad);
      strcpy(xcadfin,xcad);
      for (int i = 1; i < Retorna_numero_escenarios_visualizar(); i++) {
         strcat(xcadfin,",");
         Retorna_variable_ecuacion_sistema_activo(Retorna_escenarios_visualizar(i), xcad);
         strcat(xcadfin,xcad);
      }   
      Retorna_variable_ecuacion_sistema_activo(Retorna_escenarios_visualizar(Retorna_numero_escenarios_visualizar()+1), xcad);
      Establece_nombre_ejes(xcad, xcadfin, "");
   }  
   Limpiar();
   Dibuja();
}


   
// Imprime el estado del proyecto o sistema
// Si TR es (0) Reporte de todo el proyecto
//          (1) Reporte de estado del sistema
void Controlador::Imprime_estado(const int tr)
{
   int i1, i2, xi = 0, xxi = Numero_sistemas;
   char xcad[100], xcad1[20];
   Ctrl_reporte *Ip = new Ctrl_reporte;
   
   // Solo el sistema actual
   if(tr) xi = Sistema_actual, xxi = Sistema_actual + 1;
   // Selecciona el dispositivo del reporte
   Ip->Parametros(0,66,120,CONFIGURACION,LPT1,"ESPECIFICATIONS");

   // Loop por cada sistema
   for(i1 = xi; i1 < xxi; i1++) {
       // Imprime el nombre del sistema
       sprintf(xcad,"%s %s","SYSTEM:",Nombre_sistema[i1]);
       Ip->Formato_impresion(1,3,xcad);

       // Imprime las ecuaciones del sistema
       Ip->Formato_impresion(3,2,"EQUATIONS:");
       if (Retorna_tipo_ecuacion(i1)) {
          Ip->Formato_impresion(3,2," ORIGINAL:");
          sprintf(xcad,"   %s",Retorna_ecuacion_original(i1));
          Ip->Formato_impresion(3,2,xcad);
          Ip->Formato_impresion(3,2," SYSTEM:");
       }
       
       for(i2 = 0; i2 < Numero_ecuaciones[i1]; i2++) {
           Ip->Formato_impresion(6,1,Nombre_ecuacion[i1][i2]);
       }
       // Imprime los parametros del sistema
       Ip->Formato_impresion(3,2,"PARAMETERS:");
       if(Numero_parametros[i1]) {
          for(i2 = 0; i2 < Numero_parametros[i1]; i2++) {
              sprintf(xcad,"%s = %1.9Le",Nombre_parametro[i1][i2],P[i1][i2]);
              Ip->Formato_impresion(6,1,xcad);
          }
       } else Ip->Formato_impresion(6,1,"No hay parámetros para este sistema");
       // Funciones auxliliares a graficar
       Ip->Formato_impresion(3,2,"FUNCIONES AUXILIARES A GRAFICAR:");
       if(Numero_funciones_auxiliares[i1]) {
          for(i2 = 0; i2 < Numero_funciones_auxiliares[i1]; i2 ++) {
             sprintf(xcad,"[CTRL-F%d]  %s",i2+1,Funciones_auxiliares[i1][i2]);
             Ip->Formato_impresion(6,1,xcad);
          }
       } else Ip->Formato_impresion(6,1,"No hay funciones auxiliares definidas por el usuario");

       // Imprime la dimension las ventanas
       Ip->Formato_impresion(3,2,"DIMENSIONS WINDOW");
       sprintf(xcad,"Horizontal   Maximum: %Lf,  Minimum: %Lf",Dimensiones[i1].Xi,Dimensiones[i1].Xf);
       Ip->Formato_impresion(6,1,xcad);
       sprintf(xcad,"Vertical     Maximum: %Lf,  Minimum: %Lf",Dimensiones[i1].Yi,Dimensiones[i1].Yf);
       Ip->Formato_impresion(6,1,xcad);
       sprintf(xcad,"Tree axis    Maximum: %Lf,  Minimum: %Lf",Dimensiones[i1].Zi,Dimensiones[i1].Zf);
       Ip->Formato_impresion(6,1,xcad);

       // Imprime la configuracion de los métodos numéricos
       Ip->Formato_impresion(3,2,"NUMERICAL METHOD:");
       Ip->Formato_impresion(6,1,Retorna_nombre_metodo_integracion(Metodo_N_actual[i1]));

       for(i2 = 0; i2 < Parametros_metodo[i1][Metodo_N_actual[i1]][0]; i2++) {
          strcpy(xcad,Retorna_nombre_parametro_metodo_integracion(Retorna_tipo_parametros_metodo_integracion(Metodo_N_actual[i1]),i2)); 
          Ip->Formato_impresion(6,1,xcad);
          sprintf(xcad,"= %1.9Le",Parametros_metodo[i1][Metodo_N_actual[i1]][i2+1]);
          Ip->Formato_impresion(30,0,xcad);
       }

       // Condiciones iniciales y finales
       Ip->Formato_impresion(3,2,"NUMERICAL INTEGRATE:");
       Ip->Formato_impresion(6,1,"INITIAL CONDITION");
       Ip->Formato_impresion(35,0,"END CONDITION");
       for (i2 = 0; i2 < Numero_ecuaciones[i1]; i2++) {
           Retorna_variable_ecuacion_sistema(i1,i2+1,xcad1);
           strcat(xcad1,"(t)");
           sprintf(xcad,"%s = %1.9Le",xcad1,Ac_Condicion[i1][i2]);
           Ip->Formato_impresion(6,1,xcad);
           sprintf(xcad,"%s = %1.9Le",xcad1,At_Condicion[i1][i2]);
           Ip->Formato_impresion(35,0,xcad);
       }
       sprintf(xcad,"Time  = %1.9Le",Ac_Tiempo[i1]);
       Ip->Formato_impresion(6,1,xcad);
       sprintf(xcad,"Time  = %1.9Le",At_Tiempo[i1]);
       Ip->Formato_impresion(35,0,xcad);
       Ip->Formato_impresion(6,2,"Number of Iterations");
       sprintf(xcad,"= %ld",Numero_iteraciones);
       Ip->Formato_impresion(30,0,xcad);
       if(Parametros_metodo[i1][Metodo_N_actual[i1]][0] == 2.0) {
          Ip->Formato_impresion(6,1,"Minimum Step");
          sprintf(xcad,"= %1.9Le",Paso_minimo);
          Ip->Formato_impresion(30,0,xcad);
          Ip->Formato_impresion(6,1,"Maximum Step");
          sprintf(xcad,"= %1.9Le",Paso_maximo);
          Ip->Formato_impresion(30,0,xcad);
       }
       Ip->Formato_impresion(35,4," ");
   }
   delete Ip;
}

// Graba la configuración del sistema con el nombre indicado
void Controlador::Graba_configuracion(const char *xarch)
{
   int i1, i2, i3;
   char arch[1024];
   
   // Inicializa el objeto manipulador de archivos
   Manipulador_archivos *Grab_param = new Manipulador_archivos;
   Grab_param->Parametros(xarch,GRABA_ARCHIVO,0,"Save config");
   strcpy(arch,Proyecto);
   // Graba el nombre del proyecto
   Grab_param->Graba_caracteres(arch,40);
   // Graba el sistema actual
   Grab_param->Graba_entero(Retorna_numero_sistema_actual());
   // Graba los datos pertenecientes a cada sistema
   for(i1 = 0; i1 < Numero_sistemas; i1++) {
       // Graba la configuración de los parámetros
       Grab_param->Graba_entero(Numero_parametros[i1]);
       for(i2 = 0; i2 < Numero_parametros[i1]; i2 ++) Grab_param->Graba_ldouble(P[i1][i2]);

       // Graba la configuración de la condición inicial y el tiempo
       for(i2 = 0; i2 < Numero_ecuaciones[i1]; i2 ++) Grab_param->Graba_ldouble(Ac_Condicion[i1][i2]);
       Grab_param->Graba_ldouble(Ac_Tiempo[i1]);
       
       // Graba la configuración de los métodos numéricos
       Grab_param->Graba_entero(Metodo_N_actual[i1]);
       for(i2 = 0; i2 < NUMERO_METODOS_NUMERICOS; i2 ++) {
           for(i3 = 0; i3 < Parametros_metodo[i1][i2][0]; i3++) Grab_param->Graba_ldouble(Parametros_metodo[i1][i2][i3]);
       }
       
       // Graba  la configuración de la dimención la ventana
       Grab_param->Graba_ldouble(Dimensiones[i1].Xi);
       Grab_param->Graba_ldouble(Dimensiones[i1].Xf);
       Grab_param->Graba_ldouble(Dimensiones[i1].Yi);
       Grab_param->Graba_ldouble(Dimensiones[i1].Yf);
       Grab_param->Graba_ldouble(Dimensiones[i1].Zi);
       Grab_param->Graba_ldouble(Dimensiones[i1].Zf);

       // Graba la configuracion de la ventana
//       Grab_param->Graba_entero(Color_ejes[i1].x);
//       Grab_param->Graba_entero(Color_ejes[i1].y);
//       Grab_param->Graba_entero(Color_ejes[i1].z);
//       Grab_param->Graba_entero(Color_grafica[i1]);
//       Grab_param->Graba_entero(Color_grafica_aux[i1]);
/*
       for(i3 = 0; i3 < 2; i3++) {
          Grab_param->Graba_ldouble(Escala[i3][i1].x);
          Grab_param->Graba_ldouble(Escala[i3][i1].y);
          Grab_param->Graba_ldouble(Escala[i3][i1].z);
          Grab_param->Graba_entero(Centro[i3][i1].x);
          Grab_param->Graba_entero(Centro[i3][i1].y);
          Grab_param->Graba_ldouble(Angulos[i3][i1][0]);
          Grab_param->Graba_ldouble(Angulos[i3][i1][1]);
       }
*/       
       // Graba la configuración del paso e incremento del cursor
       Grab_param->Graba_ldouble(Paso_cursor[i1].x);
       Grab_param->Graba_ldouble(Incremento_paso_cursor[i1].x);
       Grab_param->Graba_ldouble(Paso_cursor[i1].y);
       Grab_param->Graba_ldouble(Incremento_paso_cursor[i1].y);
       Grab_param->Graba_ldouble(Paso_cursor[i1].z);
       Grab_param->Graba_ldouble(Incremento_paso_cursor[i1].z);

       // Graba la configuración del esenario activo
       Grab_param->Graba_entero(Escenario[i1].x);
       Grab_param->Graba_entero(Escenario[i1].y);
       Grab_param->Graba_entero(Escenario[i1].z);

       // Graba la configuración del campo vectorial
       for(i2 = 0; i2 < 4; i2++) Grab_param->Graba_ldouble(Parametros_campo_vectorial[i1][i2]);

       
   }
   delete Grab_param;
}



// Lee la configuración del sistema con el nombre indicado
// Si tp es (-1) restaura la configuración de todos los sistemas
//          (n)  restaura la configuración del sistema n
// si RS es (99) restaura toda la configuración
//          (1)  parámetros
//          (2)  condiciones iniciales
//          (3)  métodos numéricos
//          (4)  dimensiones
//          (5)  escenarios
int Controlador::Lee_configuracion(const char *archivo, const int xtp, const int rs)
{
   if (access(archivo,04) != 0) return 0;
   int i1, i2, i3;
   char arch[1024];

   int ent, tp = xtp;
   long double ld;

   // Inicializa el objeto manipulador de archivos
   Manipulador_archivos *Lee_param = new Manipulador_archivos;
   Lee_param->Parametros(archivo,LEE_ARCHIVO,0,"Load config");
   // Lee el nombre del proyecto
   Lee_param->Lee_caracteres(arch,40);
   // Revisa que el archivo corresponda al proyecto
   i1 = 0;
   while (Proyecto[i1]) {
      if (arch[i1] != Proyecto[i1]) {
         delete Lee_param;
         return 0;
      }
      i1++;
   }
   
   // Lee la configuración de los parámetros
   Lee_param->Lee_entero(ent);
//   if (Establece_numero_sistema_actual(ent) == Retorna_numero_sistema_actual()) {
//   } else {
//   }
   if (tp == -1 || tp == i1) {
      if (rs == 99 || rs == 1) Numero_parametros[i1] = ent;
   }
   // Lee los datos correspondientes a cada sistemas
   for(i1 = 0; i1 < Numero_sistemas; i1++) {
       // Lee la configuración de los parámetros
       Lee_param->Lee_entero(ent);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 1) Numero_parametros[i1] = ent;
       }
       for (i2 = 0; i2 < Numero_parametros[i1]; i2 ++) {
          Lee_param->Lee_ldouble(ld);
          if (tp == -1 || tp == i1) {
             if (rs == 99 || rs == 1) P[i1][i2] = ld;
          }
       }

       // Lee la configuración de la condición inicial y el tiempo
       for (i2 = 0; i2 < Numero_ecuaciones[i1]; i2 ++) {
          Lee_param->Lee_ldouble(ld);
          if (tp == -1 || tp == i1) {
             if (rs == 99 || rs == 2) Ac_Condicion[i1][i2] = ld;
          }
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 2) Ac_Tiempo[i1] = ld;
       }

       // Lee la configuración de los métodos númericos
       Lee_param->Lee_entero(ent);
       Metodo_N_actual[i1] = ent;
       for(i2 = 0; i2 < NUMERO_METODOS_NUMERICOS; i2 ++) {
           Lee_param->Lee_ldouble(ld);
           if (tp == -1 || tp == i1) {
              if (rs == 99 || rs == 3) Parametros_metodo[i1][i2][0] = ld;
           }
           for (i3 = 1; i3 < Parametros_metodo[i1][i2][0]; i3++) {
              Lee_param->Lee_ldouble(ld);
              if (tp == -1 || tp == i1) {
                 if (rs == 99 || rs == 3) Parametros_metodo[i1][i2][i3] = ld;
              }
           }
       }
       
       // Lee la configuración de las dimensiones de la ventana
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Xi = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Xf = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Yi = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Yf = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Zi = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Dimensiones[i1].Zf = ld;
       }

       // Lee la configuracion de la ventana
//          Lee_param->Lee_entero(Color_ejes[i1].x);
//          Lee_param->Lee_entero(Color_ejes[i1].y);
//          Lee_param->Lee_entero(Color_ejes[i1].z);
//          Lee_param->Lee_entero(Color_grafica[i1]);
//          Lee_param->Lee_entero(Color_grafica_aux[i1]);

/*
       for(i3 = 0; i3 < 2; i3++) {
          Lee_param->Lee_ldouble(Escala[i3][i1].x);
          Lee_param->Lee_ldouble(Escala[i3][i1].y);
          Lee_param->Lee_ldouble(Escala[i3][i1].z);
          Lee_param->Lee_entero(Centro[i3][i1].x);
          Lee_param->Lee_entero(Centro[i3][i1].y);
          Lee_param->Lee_ldouble(Angulos[i3][i1][0]);
          Lee_param->Lee_ldouble(Angulos[i3][i1][1]);
       }
*/          
       // Lee la configuración del paso e incremento del cursor
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Paso_cursor[i1].x = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Incremento_paso_cursor[i1].x = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Paso_cursor[i1].y = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Incremento_paso_cursor[i1].y = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Paso_cursor[i1].z = ld;
       }
       Lee_param->Lee_ldouble(ld);
       if (tp == -1 || tp == i1) {
          if (rs == 99 || rs == 4) Incremento_paso_cursor[i1].z = ld;
       }

       // Lee la configuración del escenario activo
       Lee_param->Lee_entero(ent);
       if (tp == -1) {
          if (rs == 99 || rs == 5) Escenario[i1].x = ent;
       }
       Lee_param->Lee_entero(ent);
       if (tp == -1) {
          if (rs == 99 || rs == 5) Escenario[i1].y = ent;
       }
       Lee_param->Lee_entero(ent);
       if (tp == -1) {
          if (rs == 99 || rs == 5) Escenario[i1].z = ent;
       }

       // Lee la configuración del campo vectorial
       for (i2 = 0; i2 < 4; i2++) {
          Lee_param->Lee_ldouble(ld);
          if (tp == -1 || tp == i1) {
             if (rs == 99 || rs == 3) Parametros_campo_vectorial[i1][i2] = ld;
          }
       }

   }
   delete Lee_param;
   // Actualiza la condición inicial
   Actualiza_condicion_inicial();
   return 1;
}



