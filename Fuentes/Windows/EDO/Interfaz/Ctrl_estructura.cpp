//////////////////////////////////////////////////////////////////////////////////////////////
// Control de la INTERFAZ DE INTEGRA                                                        //
// Revisión: 10 de Noviembre del 2003                                                       //
//                                                                                          //
// Copyright (C) 2003                                                                       //
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Ctrl_estructura.hpp"
#include "../Libreria/Man_arch.hpp"
#include "../Libreria/Ana_exp.hpp"


#define TAMANO_MAXIMO_CADENA 3000


#ifdef _IDIOMA_ESPANOL_
   #define TXT1      "CODIGO EN C++"
   #define TXT7      "PROJECT DESCRIPTION"
   #define TXT8      "SYSTEM DESCRIPTION"
   #define TXT9      "EQUATIONS"
#else
   #define TXT1      "CODE IN C++"
   #define TXT7      "PROJECT DESCRIPTION"
   #define TXT8      "SYSTEM DESCRIPTION"
   #define TXT9      "EQUATIONS"

#endif

// Configuracion de EXES de integra via interfaz
static char *Var_config_dimensiones[] = {
   "DIMENSION",        // Dimensión de la ventana (todos los ejes)
   "DIMENSION_X",      // Dimensión del eje X
   "DIMENSION_Y",      // Dimensión del eje Y
   "DIMENSION_Z",      // Dimensión del eje Z
   "DIMENSION_X_I",    // Dimensión del eje X mínimo
   "DIMENSION_X_F",    // Dimensión del eje X máximo
   "DIMENSION_Y_I",    // Dimensión del eje Y mínimo
   "DIMENSION_Y_F",    // Dimensión del eje Y máximo
   "DIMENSION_Z_I",    // Dimensión del eje Z mínimo
   "DIMENSION_Z_F",    // Dimensión del eje Z máximo
   "0"
};

static char *Var_config_ventana[] = {
   "VENTANA",          // Tipo de ventana activa     (0) No seleccionado, (1) Ejes 2D, (2) Ejes 2DM, (3) Ejes 3D, (4) Caja 2D, (5) Caja 3D, (6) Coordenadas Polares
   "ESCENARIO_X",      // Escenario para eje X     (negativo) No activo, (0) Tiempo, (1) Ecuación 1, ...,(n) Ecuanción n
   "ESCENARIO_Y",      // Escenario para eje Y     (negativo) No activo, (0) Tiempo, (1) Ecuación 1, ...,(n) Ecuanción n
   "ESCENARIO_Z",      // Escenario para eje Z     (negativo) No activo, (0) Tiempo, (1) Ecuación 1, ...,(n) Ecuanción n
   "METODO_NUMERICO",  // Indica el método númerico activo
   "0"
};
   





// Graba el proyecto con el nombre Informacion->NOMBRE
void Ctrl_estructura::Graba_proyecto(void)
{
   int i, xi;
   Manipulador_archivos *Gp = new Manipulador_archivos;
   Gp->Parametros(Informacion->Nombre,GRABA_ARCHIVO,200,"");
   // Graba el nombre del proyecto
   Gp->Graba_linea(Informacion->Nombre);
   // Graba el numero de lineas de la descripcion del proyecto
   Gp->Graba_entero(Informacion->N_e_Descripcion);
   // Graba la descripcion de proyecto
   for(i = 0; i < Informacion->N_e_Descripcion; i++) Gp->Graba_linea(Informacion->Descripcion[i]);
   // Graba el numero de sistemas
   Gp->Graba_entero(Informacion->Numero_sistemas);
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      // Graba el nombre del sistema
      Gp->Graba_linea(Informacion->Inf_sistema[i]->Nombre);
      // Graba el numero de lineas de la descripcion del sistema
      Gp->Graba_entero(Informacion->Inf_sistema[i]->N_e_Descripcion);
      // Graba la descricion del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Descripcion; xi++) Gp->Graba_linea(Informacion->Inf_sistema[i]->Descripcion[xi]);
      // Graba el numero de lineas de las ecuasciones
      Gp->Graba_entero(Informacion->Inf_sistema[i]->N_e_Ecuaciones);
      // Graba las ecuaciones del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xi++) Gp->Graba_linea(Informacion->Inf_sistema[i]->Ecuaciones[xi]);
   }
   // Graba el numero de lineas del codigo en C
   Gp->Graba_entero(Informacion->N_e_CodigoEnC);
   // Graba el codigo en C
   for(i = 0; i < Informacion->N_e_CodigoEnC; i++) Gp->Graba_linea(Informacion->CodigoEnC[i]);
   delete Gp;
   Informacion->Modificada = 0;
}


// Lee el proyecto de nombre NOMBRE 
void Ctrl_estructura::Lee_proyecto(const char *nombre)
{
   if (!nombre[0]) return;
   int i, xi;
   char xcad[TAMANO_MAXIMO_CADENA+1];
   // Borra el actual proyecto
   Borra_proyecto();
   // Solicita espacio para el proyecto
   Informacion = new Informacion_proyecto;
   // Inicializa la estructura que contendra a los sistemas
   Informacion->Inf_sistema = new Informacion_sistema *[NUMERO_SISTEMAS];
   for(i = 0; i < NUMERO_SISTEMAS; i++) Informacion->Inf_sistema[i] = NULL;
   Informacion->Numero_sistemas = 0;
   Informacion->Modificada = 0;
   Informacion->Nombre = new char [strlen(nombre)+1];
   Trim(nombre,Informacion->Nombre);

   Manipulador_archivos *La = new Manipulador_archivos;
   La->Parametros(nombre,LEE_ARCHIVO,TAMANO_MAXIMO_CADENA,"");
   // Lee el nombre del proyecto
   La->Lee_linea(xcad);
   // Lee el numero de lineas de la descripcion del proyecto
   La->Lee_entero(Informacion->N_e_Descripcion);
   // Lee la descripcion de proyecto
   if (Informacion->N_e_Descripcion) {
      Informacion->Descripcion = new char *[Informacion->N_e_Descripcion];
      for(i = 0; i < Informacion->N_e_Descripcion; i++) {
          La->Lee_linea(xcad);
          Informacion->Descripcion[i] = new char[strlen(xcad)+1];
          strcpy(Informacion->Descripcion[i],xcad);
      }
   } else Informacion->Descripcion = NULL;
   // Lee el numero de sistemas
   La->Lee_entero(Informacion->Numero_sistemas);
   if (Informacion->Numero_sistemas) {
      // Adiciona un nuevo sistema al proyecto
      for(i = 0; i < Informacion->Numero_sistemas; i++) {
        // Genera la estructura para contener el sistema
        Informacion->Inf_sistema[i] = new Informacion_sistema;
        // Lee el nombre del sistema
        La->Lee_linea(xcad);
        Informacion->Inf_sistema[i]->Nombre = new char[LG_MAX_NOM_SISTEMA+1];
        strcpy(Informacion->Inf_sistema[i]->Nombre,xcad);
        // Lee el numero de lineas de la descripcion del sistema
        La->Lee_entero(Informacion->Inf_sistema[i]->N_e_Descripcion);
        if (Informacion->Inf_sistema[i]->N_e_Descripcion) {
           // Lee la descricion del sistema
           Informacion->Inf_sistema[i]->Descripcion = new char *[Informacion->Inf_sistema[i]->N_e_Descripcion];
           for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Descripcion; xi++) {
               La->Lee_linea(xcad);
               Informacion->Inf_sistema[i]->Descripcion[xi] = new char[strlen(xcad)+1];
               strcpy(Informacion->Inf_sistema[i]->Descripcion[xi],xcad);
           }
        } else Informacion->Inf_sistema[i]->Descripcion = NULL;
        // Lee el numero de ecuaciones del sistema
        La->Lee_entero(Informacion->Inf_sistema[i]->N_e_Ecuaciones);
        if (Informacion->Inf_sistema[i]->N_e_Ecuaciones) {
           Informacion->Inf_sistema[i]->Ecuaciones = new char *[Informacion->Inf_sistema[i]->N_e_Ecuaciones];
           // Lee las ecuaciones del sistema
           for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xi++) {
               La->Lee_linea(xcad);
               Informacion->Inf_sistema[i]->Ecuaciones[xi] = new char[strlen(xcad)+1];
               strcpy(Informacion->Inf_sistema[i]->Ecuaciones[xi],xcad);
           }
        } else Informacion->Inf_sistema[i]->Ecuaciones = NULL;
      }
   }
   if (!La->Retorna_estado()) {
      // Lee el numero de lineas del codigo en C
      La->Lee_entero(Informacion->N_e_CodigoEnC);
      // Lee el Codigo en C
      if (Informacion->N_e_CodigoEnC) {
         Informacion->CodigoEnC = new char *[Informacion->N_e_CodigoEnC];
         for(i = 0; i < Informacion->N_e_CodigoEnC; i++) {
             La->Lee_linea(xcad);
             Informacion->CodigoEnC[i] = new char[strlen(xcad)+1];
             strcpy(Informacion->CodigoEnC[i],xcad);
         }
      } else Informacion->CodigoEnC = NULL;
   }
   delete La;
}




// Imprime el proyecto
void Ctrl_estructura::Imprime_proyecto(void)
{
   int i, xi;
   Ctrl_reporte *Ip = new Ctrl_reporte;
   Ip->Parametros(0,66,TAMANO_MAXIMO_CADENA,REPORTE_GRABADO,LPT1,"ARCH_PRN.$$$");
   // Imprime el nombre del proyecto
   Ip->Formato_impresion(1,0,Informacion->Nombre);
   // Imprime la descripcion de proyecto
   Ip->Formato_impresion(1,3,TXT7);
   for(i = 0; i < Informacion->N_e_Descripcion; i++) {
       Ip->Formato_impresion(5,1,Informacion->Descripcion[i]);
   }
   // Información del sistema
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      // Imprime el nombre del sistema
      Ip->Formato_impresion(1,3,Informacion->Inf_sistema[i]->Nombre);
      if (Informacion->Inf_sistema[i]->N_e_Descripcion) Ip->Formato_impresion(1,3,TXT8);
      // Imprime la descricion del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Descripcion; xi++) {
          Ip->Formato_impresion(5,1,Informacion->Inf_sistema[i]->Descripcion[xi]);
      }
      Ip->Formato_impresion(1,2,TXT9);
      // Imprime las ecuaciones del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xi++) {
          Ip->Formato_impresion(5,1,Informacion->Inf_sistema[i]->Ecuaciones[xi]);
      }
   }
   // Codigo en C++
   if (Informacion->N_e_CodigoEnC) Ip->Formato_impresion(1,3,TXT1);
   for(i = 0; i < Informacion->N_e_CodigoEnC; i++) {
      Ip->Formato_impresion(5,1,Informacion->CodigoEnC[i]);
   }
   delete Ip;
}

// Imprime el sistema indicado
void Ctrl_estructura::Imprime_sistema(const int sis)
{
   int xi;
   Ctrl_reporte *Ip = new Ctrl_reporte;
   Ip->Parametros(0,66,120,REPORTE_GRABADO,LPT1,"ARCH_PRN.$$$");
   // Imprime el nombre del sistema
   Ip->Formato_impresion(1,0,Informacion->Inf_sistema[sis]->Nombre);
   if (Informacion->Inf_sistema[sis]->N_e_Descripcion) Ip->Formato_impresion(1,3,TXT8);
   // Imprime la descricion del sistema
   for(xi = 0; xi < Informacion->Inf_sistema[sis]->N_e_Descripcion; xi++) {
       Ip->Formato_impresion(5,1,Informacion->Inf_sistema[sis]->Descripcion[xi]);
   }
   Ip->Formato_impresion(1,2,TXT9);
   // Imprime las ecuaciones del sistema
   for(xi = 0; xi < Informacion->Inf_sistema[sis]->N_e_Ecuaciones; xi++) {
       Ip->Formato_impresion(5,1,Informacion->Inf_sistema[sis]->Ecuaciones[xi]);
   }
   delete Ip;
}

// Revisa que el sistema no tenga errores
int Ctrl_estructura::Revisa_sistema(const int sis)
{
   int fau = 0, ecu = 0, par =0;
   int xi, tipo, i, err;
   int i1, i2;
   unsigned pos;
   char tcad1[100], tcad2[100];
   char xcad[TAMANO_MAXIMO_CADENA+1];
   
   // Valida que exista almenos un sistema en el proyecto
   if (!Informacion->Numero_sistemas) return 1; // No hay sistemas definidos

   // Valida que los sistemas tengan ecuaciones
   if (!Informacion->Inf_sistema[sis]->N_e_Ecuaciones) return 2; // El sistema no tiene ecuaciones

   // Analizar la informacion capturada
   Analizador_sintactico Aexp;
   for(xi = 0; xi < Informacion->Inf_sistema[sis]->N_e_Ecuaciones; xi++) {
      memccpy(xcad,Informacion->Inf_sistema[sis]->Ecuaciones[xi],0,TAMANO_MAXIMO_CADENA);
      Quitar_caracter(xcad,32);
      if (!xcad[0]) continue;
      // Indica el tipo de expresion de la que se trate
      tipo = Tipo_expresion(xcad);
      switch(tipo) {
         case 1: fau ++; break; // Funciones auxiliares
         case 2: par ++; break; // Parametros
         case 4: ecu ++; break; // Ecuaciones diferenciales
      }
   }
   // Revisa que exista almenos dos ecuaciones direfenciales
   if (ecu && ecu < 1) return 4; // Deben de existir almenos una ecuacion direfencial
   // Revisa que no se exedan los maximos definidos para las ecuaciones
   if (ecu >= NUMERO_ECUACIONES) return 5; // Se exedan los maximos definidos para las ecuaciones
   // Revisa que no se exedan los maximos definidos para los parametros
   if (par >= NUMERO_MAX_PARAMETROS) return 6; // Se exedan los maximos definidos para los parametros
   if (fau >= 9) return 9; // Se exedan los maximos definidos para las funciones auxiliares

   ///////////////////////////////////////////////////////////////////////
   // Valida por sistema que:                                           //
   //    Ecuaciones que sean unicas                                     //
   //    parametros que sean unicos                                     //
   //    funciones auxiliares que sean unicas                           //
   ///////////////////////////////////////////////////////////////////////
   // Toma linea por linea y extrae el nombre de la expresion
   for(i1 = 0; i1 < Informacion->Inf_sistema[sis]->N_e_Ecuaciones; i1++) {
      memccpy(xcad,Informacion->Inf_sistema[sis]->Ecuaciones[i1],0,TAMANO_MAXIMO_CADENA);
      Quitar_caracter(xcad,32);
      if (!xcad[0]) continue;
      // Descarta las funciones auxiliares a graficar
      if (xcad[0] == 'F' && xcad[1] == '(' && xcad[3] == ')' && xcad[4] == '=') continue;
      // Extrae el nombre de la expresion
      if (Busca_caracter(xcad,'=',pos)) {
         Substr(xcad,0,pos,tcad1);
         // Lo compara con el resto de las expresiones
         for(i2 = 0; i2 < Informacion->Inf_sistema[sis]->N_e_Ecuaciones; i2++) {
            if (i1 == i2) continue;
            memccpy(xcad,Informacion->Inf_sistema[sis]->Ecuaciones[i2],0,TAMANO_MAXIMO_CADENA);
            Quitar_caracter(xcad,32);
            if (!xcad[0]) continue;
            // Extrae el nombre de la expresion
            if (Busca_caracter(xcad,'=',pos)) {
               Substr(xcad,0,pos,tcad2);
               // Compara si son iguales
               if (Compara(tcad1,tcad2)) return 7; // Existen expresiones duplicadas
            }
         }
      }

      memccpy(xcad,Informacion->Inf_sistema[sis]->Ecuaciones[i1],0,TAMANO_MAXIMO_CADENA);
      Quitar_caracter(xcad,32);
      tipo = Tipo_expresion(xcad);
      switch(tipo) {
         case 1: fau ++; break; // Funciones auxiliares
         case 2: par ++; break; // Parametros
         case 4: ecu ++; break; // Ecuaciones diferenciales
      }
      // Analiza la estructura de la expresion
      if (tipo == 1 || tipo == 2 || tipo == 3 || tipo == 5) Aexp.Analiza_expresion_tipo_01(xcad);
       else if (tipo == 4) Aexp.Analiza_expresion_tipo_02(xcad);
             else return 8;
      // Revisa si existieron errores al analizar la expresion
      if (Aexp.Retorna_num_funciones_no_encontradas()) {
         char xcad[200];
         for (int xi = 0; xi < Aexp.Retorna_num_funciones_no_encontradas(); xi++) {
            Aexp.Retorna_funcion_no_encontrada(xi,xcad);
            if (!Funcion_definida_en_codigo_C(xcad)) {  
               err = 19; 
              return (err+9);
            }
         }   
      }
      if (Aexp.Numero_errores()) {
         for (i = 0; i < Aexp.Numero_errores(); i++) {
            err = Aexp.Retorna_codigo_error(i);
            return (err+9);
         }
      }
   }
   return 0;
}


// Indica el tipo de expresion pasada como parámetro 
// (0)  No reconocida
// (1)  Función auxiliar
//      F(x)=...
//      F(y)=... 
// (2)  Parámetro
//      A=10
// (3)  Expresión aritmética
//      A=10*sin(x)
// (4)  Ecuación Diferencial
//      x'= ...
//      ó
//      x''=...        
// (5)  Variable de configuración
//      VARIABLEDEFINIDA=0.1
//#error Soporte ecuaciones en diferencias y ecuación de orden n
//#error Revisar que haga correctamente el reconocimiento del tipo de expresion
int Ctrl_estructura::Tipo_expresion(const char *exp)
{
   char xcad[200], xcad2[TAMANO_MAXIMO_CADENA];
   unsigned int pos, xxi,lg = strlen(exp);
   bool st = 0, ct = 0;
   // Revisa si es una ecuacion diferencial
   xxi = 0;
   while (exp[xxi] != '=') {
      if (exp[xxi] == '\'') st = 1, ct ++;
      xxi ++;
   }
   if (st) {
      // Expresión no reconocida ya que sólo se soportan ecuaciones de segundo orden
      if (ct > 2) return 0;
      // Es una ecuación diferencial
      return 4;
   }

   // Revisa si es una función auxiliar
   if (exp[0] == 'F' && exp[1] == '(' && (exp[2] == 'x' || exp[2] == 'y') && exp[3] == ')' && exp[4] == '=') return 1; // Es una funcion auxiliar

   // Revisa si es un parametro o variable de configuración
   if (!Busca_caracteres(exp,"*+/,)(",pos)) {
      if (Busca_caracter(exp,'=',pos)) {
         Substr(exp,pos+1,lg,xcad);
         if (Es_cadena_numero(xcad)) {
            // Extrae el nombre de la variable
            xxi = 0;
            while (exp[xxi] != '=') {
               xcad2[xxi] = exp[xxi];
               xxi ++;
            }
            xcad2[xxi] = 0;
            xxi = 0;
            // Revisa si es una expresion de configuración del archivo EXE
            while (Var_config_dimensiones[xxi][0] != '0') {
               if (Compara(xcad2,Var_config_dimensiones[xxi])) return 1; // Es una variable de configuración
               xxi++;
            }
            xxi = 0;
            while (Var_config_ventana[xxi][0] != '0') {
               if (Compara(xcad2,Var_config_ventana[xxi])) return 1; // Es una variable de configuración
               xxi++;
            }
            return 2; // Es un parámetro
         }
      }
    } else {
      // Analizar la informacion capturada
      Analizador_sintactico Aexp;
      Aexp.Analiza_expresion_tipo_01(exp);
      // Revisa si existieron errores al analizar la expresion
      if (!Aexp.Numero_errores()) return 3; // Es una expresión aritmética
   }
   // No se reconocio el tipo
   return 0;
}


// Genera archivo ejecutable
int Ctrl_estructura::Generar(void)
{
   int xi, xxi, tipo;
   int i_e, i_p, i_f, lg;
   char xcad[TAMANO_MAXIMO_CADENA+1];

   // Solicirta la memoria necesaria para contener el arreglo de trabajo
   for (int i = 0; i < Informacion->Numero_sistemas; i++) {
      i_e = 0, i_p = 0, i_f = 0;
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xi++) {

         memccpy(xcad,Informacion->Inf_sistema[i]->Ecuaciones[xi],0,TAMANO_MAXIMO_CADENA);
         Quitar_caracter(xcad,32);
         if (!xcad[0]) continue;
         // Indica el tipo de expresion de la que se trate
         tipo = Tipo_expresion(xcad);

         switch(tipo) {
            case 3:
            case 1: i_f ++; break; // Funciones auxiliares
            case 2: i_p ++; break; // Parametros
            case 4: i_e ++; break; // Ecuaciones diferenciales
         }
   
      }
      Informacion->Inf_sistema[i]->TEcuaciones = new char *[i_e];
      Informacion->Inf_sistema[i]->TParametros = new char *[i_p];
      Informacion->Inf_sistema[i]->TFuncionesAux = new char *[i_f];
      i_e = 0, i_p = 0, i_f = 0;
      // Inserta la nueva informacion al arreglo de trabajo
      for(xxi = 0; xxi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xxi++) {
         memccpy(xcad,Informacion->Inf_sistema[i]->Ecuaciones[xxi],0,TAMANO_MAXIMO_CADENA);
         Quitar_caracter(xcad,32);
         if (!xcad[0]) continue;
         lg = strlen(xcad) + 1;
         tipo = Tipo_expresion(xcad);
     
         switch(tipo) {
           case 3:
           case 1: // Funciones auxiliares
             Informacion->Inf_sistema[i]->TFuncionesAux[i_f] = new char[lg];
             memccpy(Informacion->Inf_sistema[i]->TFuncionesAux[i_f],xcad,0,TAMANO_MAXIMO_CADENA);
             i_f ++;
             break;
           case 2: // Parámetros
             Informacion->Inf_sistema[i]->TParametros[i_p] = new char[lg];
             memccpy(Informacion->Inf_sistema[i]->TParametros[i_p],xcad,0,TAMANO_MAXIMO_CADENA);
             i_p ++;
             break;
           case 4: // Ecuaciones diferenciales
             Informacion->Inf_sistema[i]->TEcuaciones[i_e] = new char[lg];
             memccpy(Informacion->Inf_sistema[i]->TEcuaciones[i_e],xcad,0,TAMANO_MAXIMO_CADENA);
             i_e ++;
             break;
         }
      }
      Informacion->Inf_sistema[i]->N_Ecuaciones     = i_e;
      Informacion->Inf_sistema[i]->N_Parametros     = i_p;
      Informacion->Inf_sistema[i]->N_FuncionesAux   = i_f;
   }
   // Genera archivo CPP
   Genera_hpp();
   Genera_cpp();
   // Genera archivos de descripcion
   Genera_descripcion();
   // Borra las estructuras temporales de ecuaciones, parametros y funciones auxiliares
   for (int n_s = 0; n_s < Informacion->Numero_sistemas; n_s++) {
      // Borra las ecuaciones del sistema
      for (xi = 0; xi < Informacion->Inf_sistema[n_s]->N_Ecuaciones; xi++) delete[] Informacion->Inf_sistema[n_s]->TEcuaciones[xi];
      delete[] Informacion->Inf_sistema[n_s]->TEcuaciones;
      Informacion->Inf_sistema[n_s]->N_Ecuaciones = 0;
      Informacion->Inf_sistema[n_s]->TEcuaciones = NULL;
      // Borra los parámetros del sistema
      for (xi = 0; xi < Informacion->Inf_sistema[n_s]->N_Parametros; xi++) delete[] Informacion->Inf_sistema[n_s]->TParametros[xi];
      delete[] Informacion->Inf_sistema[n_s]->TParametros;
      Informacion->Inf_sistema[n_s]->N_Parametros= 0;
      Informacion->Inf_sistema[n_s]->TParametros= NULL;
      // Borra las funciones auxiliares del sistema
      for (xi = 0; xi < Informacion->Inf_sistema[n_s]->N_FuncionesAux; xi++) delete[] Informacion->Inf_sistema[n_s]->TFuncionesAux[xi];
      delete[] Informacion->Inf_sistema[n_s]->TFuncionesAux;
      Informacion->Inf_sistema[n_s]->N_FuncionesAux= 0;
      Informacion->Inf_sistema[n_s]->TFuncionesAux= NULL;
   }
  
   return 0; // Sin errores
}

//Genera el archivo HPP para generar al ejecutable
void Ctrl_estructura::Genera_hpp(void)
{
   int i, i4;
   char *xcad  = new char[TAMANO_MAXIMO_CADENA];
   char archivo[MAXPATH];
   Manipulador_archivos ma;
   ma.Cambia_ext_path(Informacion->Nombre,"hpp",archivo);
   Ctrl_reporte *Ip = new Ctrl_reporte;
   Ip->Parametros(0,66,TAMANO_MAXIMO_CADENA,REPORTE_GRABADO,LPT1,archivo);

   // Genera el encabezado 
   Genera_Encabezado(Ip);
   Ip->Formato_impresion(1,3,"#ifndef __Definicion_Usuario__");
   Ip->Formato_impresion(1,1,"#define __Definicion_Usuario__");
   Ip->Formato_impresion(1,3,"#include \"Ctrl_Fun_Aux.hpp\"");
   Ip->Formato_impresion(1,1,"#include \"../Libreria/Definiciones.hpp\"");
   Ip->Formato_impresion(1,1,"#include <math.h>");

   // Valores definidos dinámicamente
   Ip->Formato_impresion(1,3,"// Indica el número máximo de sistemas por proyecto");
   sprintf(xcad,"#define NUMERO_SISTEMAS               %d",Informacion->Numero_sistemas);
   Ip->Formato_impresion(1,1,xcad);
   Ip->Formato_impresion(1,1,"// Indica el número máximo de ecuaciones por sistema");
   i4 = 0;
   for (i = 0; i < Informacion->Numero_sistemas; i++) {
       if (Informacion->Inf_sistema[i]->N_Ecuaciones > i4) i4 = Informacion->Inf_sistema[i]->N_Ecuaciones;
   }
   sprintf(xcad,"#define NUMERO_ECUACIONES             %d",i4);
   Ip->Formato_impresion(1,1,xcad);
   Ip->Formato_impresion(1,1,"// Indica el número máximo de parámetros por sistema");
   i4 = 0;
   for (i = 0; i < Informacion->Numero_sistemas; i++) {
       if (Informacion->Inf_sistema[i]->N_Parametros > i4) i4 = Informacion->Inf_sistema[i]->N_Parametros;
   }
   sprintf(xcad,"#define NUMERO_MAX_PARAMETROS         %d",i4);
   Ip->Formato_impresion(1,1,xcad);

   // Valores definidos estaticamente
   Ip->Formato_impresion(1,1,"// Indica el número máximo de funciones auxiliares");
   Ip->Formato_impresion(1,1,"#define NUMERO_MAX_FUNCIONES_AUX      9");
   // Definición de la clase
   Ip->Formato_impresion(1,3,"class Definicion_Usuario: public Ctrl_Funciones_Auxiliares");
   Ip->Formato_impresion(1,1,"{");
   Ip->Formato_impresion(1,2,"   public:");
   Ip->Formato_impresion(1,2,"                         // Número de sistemas definidos");
   Ip->Formato_impresion(1,1,"      int                Numero_sistemas;");
   Ip->Formato_impresion(1,1,"                         // Sistema actual");
   Ip->Formato_impresion(1,1,"      int                Sistema_actual;");
   Ip->Formato_impresion(1,1,"                         // Nombre del proyecto");
   Ip->Formato_impresion(1,1,"      const char        *Proyecto;");
   Ip->Formato_impresion(1,1,"                         // Nombre del sistema");
   Ip->Formato_impresion(1,1,"      const char        *Nombre_sistema[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Número de ecuaciones por sistema");
   Ip->Formato_impresion(1,1,"      int                Numero_ecuaciones[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Ecuación original para orden uno y dos");
   Ip->Formato_impresion(1,1,"      const char        *Ecuacion_original[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Nombre de la ecuación por sistema");
   Ip->Formato_impresion(1,1,"      const char        *Nombre_ecuacion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];");
   Ip->Formato_impresion(1,1,"                         // Número de parámetros por sistema");
   Ip->Formato_impresion(1,1,"      int                Numero_parametros[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Nombre del parámetro por cada sistema");
   Ip->Formato_impresion(1,1,"      const char        *Nombre_parametro[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];");
   Ip->Formato_impresion(1,1,"                         // Tipo de Ecuación (0) Sistema de ecuaciones (1) Ecuación ordinaria de primer orden");
   Ip->Formato_impresion(1,1,"      int                Tipo_ecuacion[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Número de funciones auxiliares por sistema");
   Ip->Formato_impresion(1,1,"      int                Numero_funciones_auxiliares[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Contiene las funciones auxiliares por sistema");
   Ip->Formato_impresion(1,1,"      const char        *Funciones_auxiliares[NUMERO_SISTEMAS][NUMERO_MAX_FUNCIONES_AUX];");
   Ip->Formato_impresion(1,1,"                         // Contiene los valores de configuración del archivo EXE");
   Ip->Formato_impresion(1,1,"      long double        Config[NUMERO_SISTEMAS][6];");
   Ip->Formato_impresion(1,1,"                         // Escenarios a trabajar por cada ventana y cada sistema");
   Ip->Formato_impresion(1,1,"      C_3I               Escenario[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Tipo de ventana activa en el sistema");
   Ip->Formato_impresion(1,1,"      int                Ventana_activa[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Indica el método actual de integración");
   Ip->Formato_impresion(1,1,"      unsigned int       Metodo_N_actual[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Parámetros por cada sistema");
   Ip->Formato_impresion(1,1,"      long double        P[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];");
   Ip->Formato_impresion(1,1,"                         // Variable para las distintas ecuaciones");
   Ip->Formato_impresion(1,1,"      long double        X[NUMERO_ECUACIONES];");
   Ip->Formato_impresion(1,1,"                         // Actual condición en la integración númerica");
   Ip->Formato_impresion(1,1,"      long double        At_Condicion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];");
   Ip->Formato_impresion(1,1,"                         // Actual tiempo en la integración númerica"); 
   Ip->Formato_impresion(1,1,"      long double        At_Tiempo[NUMERO_SISTEMAS];");
   Ip->Formato_impresion(1,1,"                         // Puntero a un arreglo de funciones");
   Ip->Formato_impresion(1,1,"      long double        (Definicion_Usuario::*funcion[NUMERO_SISTEMAS][NUMERO_ECUACIONES])(void);");
   Ip->Formato_impresion(1,1,"                         // Configuracion del archivo EXE");
   Ip->Formato_impresion(1,1,"      void               Configuracion(void);");
   Ip->Formato_impresion(1,1,"                         // Iniciliza la clase");
   Ip->Formato_impresion(1,1,"      virtual void       Inicializa(void);");
   Ip->Formato_impresion(1,1,"                         // Asigna los parametros");
   Ip->Formato_impresion(1,1,"      void               Parametros(const unsigned int i);");
   Ip->Formato_impresion(1,2,"   protected:");
   Ip->Formato_impresion(1,1,"      // Funciones definidas apartir de las ecuaciones diferenciales");

   // Genera la declaración las funciones de cada sistema
   for (i = 0; i < Informacion->Numero_sistemas; i++) {
       if (Informacion->Inf_sistema[i]->N_Ecuaciones > 1) {
          // Declaración de sistema
          for(i4 = 0; i4 < Informacion->Inf_sistema[i]->N_Ecuaciones; i4++) {
             sprintf(xcad,"long double Definicion_Usuario::Fn%#04d%#04d(void);",i,i4);
             Ip->Formato_impresion(6,1,xcad);
          }
        } else {
          // Declaración de ecuación como sistema
          for(i4 = 0; i4 < 2; i4++) {
             sprintf(xcad,"long double Definicion_Usuario::Fn%#04d%#04d(void);",i,i4);
             Ip->Formato_impresion(6,1,xcad);
          }
       }
   }

   Ip->Formato_impresion(1,2," ");
   // Genera el codigo en C++
   if (Informacion->N_e_CodigoEnC) {
      // Revisa que funciones no estan incluidas en el código en C++ para ser incluidas
      // Antes de integrar
      if (!Funcion_definida_en_codigo_C("Antes_integrar")) Genera_codigo_base_en_C(Ip,1);
      // Despues de integrar
      if (!Funcion_definida_en_codigo_C("Despues_integrar")) Genera_codigo_base_en_C(Ip,2);
      // Limpiar variables               
      if (!Funcion_definida_en_codigo_C("Limpiar_variables")) Genera_codigo_base_en_C(Ip,3);

      // Incluye codigo en C++ definido por el usuario
      for (i = 0; i < Informacion->N_e_CodigoEnC; i++) {
          sprintf(xcad,"%s",Informacion->CodigoEnC[i]);
          Ip->Formato_impresion(6,1,xcad);
      }
   } else Genera_codigo_base_en_C(Ip,0);
   
   Ip->Formato_impresion(1,1,"};");
   Ip->Formato_impresion(1,3,"#endif");
   
   delete Ip;
}



//Genera el archivo CPP para generar al ejecutable
void Ctrl_estructura::Genera_cpp(void)
{
   int i, xi, i1, i2, i3, i4, tp_ecu, xxi;
   bool sw;
   unsigned int pos;
   double val[6];
   char archivo[MAXPATH];
   char *xcad    = new char[TAMANO_MAXIMO_CADENA];
   char *xcad1   = new char[TAMANO_MAXIMO_CADENA];
   char *xcad2   = new char[TAMANO_MAXIMO_CADENA];
   char *xcad3   = new char[TAMANO_MAXIMO_CADENA];
   char *xcad4   = new char[TAMANO_MAXIMO_CADENA];
   char *var     = new char[TAMANO_MAXIMO_CADENA];
   char *nom_ecu = new char[TAMANO_MAXIMO_CADENA];

   Manipulador_archivos ma;
   ma.Cambia_ext_path(Informacion->Nombre,"cpp",archivo);
   Ctrl_reporte *Ip = new Ctrl_reporte;
   Ip->Parametros(0,66,TAMANO_MAXIMO_CADENA,REPORTE_GRABADO,LPT1,archivo);
   // Genera el encabezado 
   Genera_Encabezado(Ip);
   // Inclusión de archivos h y hpp
   Ip->Formato_impresion(1,2,"#include \"Def_Usuario.hpp\"");
   // Especifica el nombre de los sistemas
   Ip->Formato_impresion(1,3,"void Definicion_Usuario::Inicializa(void)");
   Ip->Formato_impresion(1,1,"{");

   // Nombre del proyecto
   i = 0, xi = 0;
   while(Informacion->Nombre[i]) {
      if (Informacion->Nombre[i] == '\\') xcad1[xi] = '\\', xi++; 
      xcad1[xi] = Informacion->Nombre[i];
      xi++, i++; 
   }
   xcad1[xi] = 0;
   ma.Cambia_ext_path(xcad1,"D",xcad);
   sprintf(xcad1,"Proyecto = \"%s\";",xcad);
   Ip->Formato_impresion(3,2,xcad1);
   // Informacion de los sistemas
   sprintf(xcad1,"Numero_sistemas = %d;",Informacion->Numero_sistemas);
   Ip->Formato_impresion(3,2,xcad1);
   Ip->Formato_impresion(3,2,"");
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
       // Nombre del sistema
       sprintf(xcad,"Nombre_sistema[%d] = \"%s\";",i,Informacion->Inf_sistema[i]->Nombre);
       Ip->Formato_impresion(3,1,xcad);
       // Revisa el tipo de ecuación
       tp_ecu = 0;
       if (Informacion->Inf_sistema[i]->N_Ecuaciones == 1) {
           xxi = 0;
           while (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] != '=') {
              if (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] == '\'') tp_ecu ++;
              xxi ++;
           }
       }
       // Indica el tipo de ecuación
       // (0) Sistema de ecuaciones
       // (1) Ecuación ordinaria de primer orden
       // (2) Ecuación ordinaria de segundo orden
       sprintf(xcad,"Tipo_ecuacion[%d] = %d;",i,tp_ecu);
       Ip->Formato_impresion(3,1,xcad);
   }
   Ip->Formato_impresion(1,1,"");

   // Especifica el nombre de las ecuaciones
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      if (Informacion->Inf_sistema[i]->N_Ecuaciones > 1) {
         // Escribe la ecuación original
         sprintf(xcad,"Ecuacion_original[%d]=\" \";",i);
         Ip->Formato_impresion(3,1,xcad);
         // Nombre de la ecuacion de cada sistema
         for(xi = 0; xi < Informacion->Inf_sistema[i]->N_Ecuaciones ; xi++) {
             Remplaza_funciones_auxiliares(Informacion->Inf_sistema[i]->TEcuaciones[xi],xcad3,i);
             sprintf(xcad,"Nombre_ecuacion[%d][%d]=\"%s\";",i,xi,xcad3);
             Ip->Formato_impresion(3,1,xcad);
         }
       } else {
         // Escribe la ecuación original
         sprintf(xcad,"Ecuacion_original[%d]=\"%s\";",i,Informacion->Inf_sistema[i]->TEcuaciones[0]);
         Ip->Formato_impresion(3,1,xcad);
         // Revisa el tipo de ecuación de que se trate
         xxi = 0, tp_ecu = 0;
         while (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] != '=') {
            if (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] == '\'') tp_ecu ++;
            xxi ++;
         }
         // Informacion de la ecuación como sistema
         if (tp_ecu == 1) {
            // Ecuación de primer orden
            sprintf(xcad,"Nombre_ecuacion[%d][0]=\"T'=1\";",i);
            Ip->Formato_impresion(3,1,xcad);
            for(xi = 0; xi < Informacion->Inf_sistema[i]->N_Ecuaciones ; xi++) {
                Remplaza_funciones_auxiliares(Informacion->Inf_sistema[i]->TEcuaciones[xi],xcad3,i);
                // Cambia el tiempo por la variable T
                Busca_remplaza_expresion(xcad3,"t","T");
                sprintf(xcad,"Nombre_ecuacion[%d][%d]=\"%s\";",i,xi+1,xcad3);
                Ip->Formato_impresion(3,1,xcad);
            }
          } else {
            // Ecuación de segundo orden
            // Extrae el nombre de la ecuación
            xxi = 0;
            while (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] != '\'') {
               nom_ecu[xxi] = Informacion->Inf_sistema[i]->TEcuaciones[0][xxi];
               xxi ++;
            }
            int tp = 0;
            nom_ecu[xxi] = 0;
            // Graba la primera ecuación del sistema
            if (nom_ecu[1] == 0 && nom_ecu[0] == 'x') {
               sprintf(xcad,"Nombre_ecuacion[%d][0]=\"X'=%s\";",i,nom_ecu);
               Ip->Formato_impresion(3,1,xcad);
             } else {
               sprintf(xcad,"Nombre_ecuacion[%d][0]=\"x'=%s\";",i,nom_ecu);
               Ip->Formato_impresion(3,1,xcad);
               tp = 1;
            }
            // Remplaza las funciones auxiliares
            Remplaza_funciones_auxiliares(Informacion->Inf_sistema[i]->TEcuaciones[0],xcad1,i);
            // Cambia la variable cuyo nombre es NOM_ECU por x o X
            if (tp) Busca_remplaza_expresion(xcad1,nom_ecu,"x");
             else Busca_remplaza_expresion(xcad1,nom_ecu,"X");
            // Cambia la primera derivada por NOM_ECU
            strcpy(xcad2,nom_ecu);
            strcat(xcad2,"'");
            Busca_remplaza_expresion(xcad1,xcad2,nom_ecu);
            // Cambia la segunda derivada por la primera derivada
            Busca_remplaza_cadenas(xcad1,"''","'");
            // Escribe la segunda ecuación
            sprintf(xcad,"Nombre_ecuacion[%d][%d]=\"%s\";",i,1,xcad1);
            Ip->Formato_impresion(3,1,xcad);
         }
      }
   }

   // Especifica el número de ecuaciones, número y nombre de los parámetros de cada sistema
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      // Graba el numero de ecuaciones por sistema o 2 para cuando se trata de una ecuación única
      if (Informacion->Inf_sistema[i]->N_Ecuaciones > 1) sprintf(xcad,"Numero_ecuaciones[%d] = %d;",i,Informacion->Inf_sistema[i]->N_Ecuaciones);
       else sprintf(xcad,"Numero_ecuaciones[%d] = 2;",i);
      Ip->Formato_impresion(3,2,xcad);

      // Graba el número de parámetros
      sprintf(xcad,"Numero_parametros[%d] = %d;",i,Informacion->Inf_sistema[i]->N_Parametros);
      Ip->Formato_impresion(3,1,xcad);

      // Graba los nombres de cada parámetro
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_Parametros ; xi++) {
         if (Busca_caracter(Informacion->Inf_sistema[i]->TParametros[xi],'=',pos)) {
            Substr(Informacion->Inf_sistema[i]->TParametros[xi],0,pos,xcad3);
            sprintf(xcad,"Nombre_parametro[%d][%d] = \"%s\";",i,xi,xcad3);
            Ip->Formato_impresion(3,1,xcad);
         }
      }
   }
   Ip->Formato_impresion(1,3,"");

   // Declaracion de las funciones de cada uno de los sistemas
   for(i = 0; i  < Informacion->Numero_sistemas; i++) {
       if (Informacion->Inf_sistema[i]->N_Ecuaciones > 1) {
          // Declaración de funciones del sistema
          for(xi = 0; xi  < Informacion->Inf_sistema[i]->N_Ecuaciones; xi++) {
              sprintf(xcad,"funcion[%d][%d] = &Definicion_Usuario::Fn%#04d%#04d;",i,xi,i,xi);
              Ip->Formato_impresion(3,1,xcad);
          }
        } else {
          // Declaración de funciones de la ecuación como sistema
          for(xi = 0; xi  < 2; xi++) {
              sprintf(xcad,"funcion[%d][%d] = &Definicion_Usuario::Fn%#04d%#04d;",i,xi,i,xi);
              Ip->Formato_impresion(3,1,xcad);
          }   
       }
   }
   
   // Incluye las funcione auxiliares a graficar
   Ip->Formato_impresion(1,2," ");
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      i1 = 0;
      // Funciones auxiliares a graficar
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_FuncionesAux; xi++) {
         if (Informacion->Inf_sistema[i]->TFuncionesAux[xi][0] == 'F' && (Informacion->Inf_sistema[i]->TFuncionesAux[xi][2] == 'x' || Informacion->Inf_sistema[i]->TFuncionesAux[xi][2] == 'y') && Informacion->Inf_sistema[i]->TFuncionesAux[xi][4] == '=') {
            if (i1 < NUMERO_MAX_FUNCIONES_AUX) {
               // Remplaza las funciones auxiliares
               Substr(Informacion->Inf_sistema[i]->TFuncionesAux[xi], 5, TAMANO_MAXIMO_CADENA, xcad1);
               Remplaza_funciones_auxiliares(xcad1,xcad2,i);
               // Genera la nueva funcion auxiliar
               sprintf(xcad,"Funciones_auxiliares[%d][%d] = \"F(%c)=%s\";",i,i1,Informacion->Inf_sistema[i]->TFuncionesAux[xi][2],xcad2);
               Ip->Formato_impresion(3,1,xcad);
               i1++;
            }
         }
      }
      sprintf(xcad,"Numero_funciones_auxiliares[%d] = %d;",i,i1);
      Ip->Formato_impresion(3,1,xcad);
   }
   
   // Rutina que asigna los valores a los parametros
   Ip->Formato_impresion(3,3,"Parametros(99);");
   Ip->Formato_impresion(1,1,"}");
   // Especifica el valor para cada parametro de todos los sistemas
   Ip->Formato_impresion(1,3,"void Definicion_Usuario::Parametros(const unsigned int i)");
   Ip->Formato_impresion(1,1,"{");
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      // Graba el valor de cada parametro
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_Parametros ; xi++) {
         if (Busca_caracter(Informacion->Inf_sistema[i]->TParametros[xi],'=',pos)) {
            Substr(Informacion->Inf_sistema[i]->TParametros[xi],pos+1,100,xcad3);
               sprintf(xcad,"if (i == %d || i == 99) P[%d][%d] = %s;",i,i,xi,xcad3);
               Ip->Formato_impresion(3,1,xcad);
         }
      }
   }
   Ip->Formato_impresion(1,1,"}");
   
   // Contiene los valores de configuracion del archivo EXE
   Ip->Formato_impresion(1,3,"void Definicion_Usuario::Configuracion(void)");
   Ip->Formato_impresion(1,1,"{");
   // Configuracion de las dimensiones de la ventana de trabajo
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      // valores por omision
      for(xi = 0; xi < 3; xi++) val[xi] = -10.0;
      for(xi = 0; xi < 3; xi++) val[3+xi] = 10.0;
      // Rastrea cual de los parametros es de configuracion
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_FuncionesAux ; xi++) {
         if (Busca_caracter(Informacion->Inf_sistema[i]->TFuncionesAux[xi],'=',pos)) {
            Substr(Informacion->Inf_sistema[i]->TFuncionesAux[xi],0,pos,xcad2);
            Substr(Informacion->Inf_sistema[i]->TFuncionesAux[xi],pos+1,100,xcad3);
            i2 = 0;
            while(Var_config_dimensiones[i2][0] != '0') {
                // Es un parametro de configuracion
                if (Compara(xcad2,Var_config_dimensiones[i2])) {
                   double xval = atof(xcad3);
                   // Remplaza el valor de omicion
                   if (i2 == 0 && xval > 0.0) {
                      for(xi = 0; xi < 3; xi++) val[xi]   = -xval;
                      for(xi = 0; xi < 3; xi++) val[3+xi] =  xval;
                   }
                   // Remplaza el valor del eje X
                   if (i2 == 1 && xval > 0.0) val[0] = -xval, val[3] =  xval;
                   // Remplaza el valor del eje Y
                   if (i2 == 2 && xval > 0.0) val[1] = -xval, val[4] =  xval;
                   // Remplaza el valor del eje Z
                   if (i2 == 3 && xval > 0.0) val[2] = -xval, val[5] =  xval;
                   // Remplaza el valor minimo del eje X
                   if (i2 == 4) val[0] = xval;
                   // Remplaza el valor maximo del eje X
                   if (i2 == 5) val[3] = xval;
                   // Remplaza el valor minimo del eje Y
                   if (i2 == 6) val[1] = xval;
                   // Remplaza el valor maximo del eje Y
                   if (i2 == 7) val[4] = xval;
                   // Remplaza el valor minimo del eje Z
                   if (i2 == 8) val[2] = xval;
                   // Remplaza el valor maximo del eje Z
                   if (i2 == 9) val[5] = xval;
                   break;
                }
                i2++;
            }
         }
      }
      for(xi = 0; xi < 6; xi++) {
          sprintf(xcad,"Config[%d][%d] = %f;",i,xi,val[xi]);
          Ip->Formato_impresion(3,1,xcad);
      }
   }


   // Definicion de los escenarios graficos
   Ip->Formato_impresion(3,2,"for(int i = 0; i < Numero_sistemas ; i++) {");
   // Escenario gráfico por omisión
   Ip->Formato_impresion(6,1,"Escenario[i].x = 1, Escenario[i].y = 2;");
   Ip->Formato_impresion(6,1,"if (Numero_ecuaciones[i] >= 3) Escenario[i].z = 3, Ventana_activa[i] = EJES_COORDENADOS_3D;");
   Ip->Formato_impresion(7,1,"else Escenario[i].z = 0, Ventana_activa[i] = EJES_COORDENADOS_2D;");
   // Método númerico de integración
   Ip->Formato_impresion(6,1,"Metodo_N_actual[i] = 99;");
   Ip->Formato_impresion(3,1,"}");

   // Configuracion del tipo de ventana activa y escenario activo
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      int xval = 0;
      // Rastrea cual de los parametros es de configuracion
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_FuncionesAux ; xi++) {
         if (Busca_caracter(Informacion->Inf_sistema[i]->TFuncionesAux[xi],'=',pos)) {
            Substr(Informacion->Inf_sistema[i]->TFuncionesAux[xi],0,pos,xcad2);
            Substr(Informacion->Inf_sistema[i]->TFuncionesAux[xi],pos+1,100,xcad3);
            i2 = 0;
            sw = false;
            while(Var_config_ventana[i2][0] != '0') {
                // Es un parametro de configuracion
                if (Compara(xcad2,Var_config_ventana[i2])) {
                   sw = true;
                   // Remplaza el valor de omicion
                   xval = atoi(xcad3);
                   break;
                }
                i2++;
            }
            if (sw) {
               // Indica el tipo de ventana activa
               if (i2 == 0) sprintf(xcad,"Ventana_activa[%d] = %d;",i,xval);
               // Escenario para el eje X
               if (i2 == 1) {
                  if (xval >= 0) {
                      if (xval == 0) sprintf(xcad,"Escenario[%d].x = Numero_ecuaciones[%d] + 1;",i,i);
                       else sprintf(xcad,"Escenario[%d].x = %d;",i,xval);
                  } else sprintf(xcad,"Escenario[%d].x = 0;",i);
               }
               // Escenario para el eje Y
               if (i2 == 2) {
                  if (xval >= 0) {
                      if (xval == 0) sprintf(xcad,"Escenario[%d].y = Numero_ecuaciones[%d] + 1;",i,i);
                       else sprintf(xcad,"Escenario[%d].y = %d;",i,xval);
                  } else sprintf(xcad,"Escenario[%d].y = 0;",i);
               }
               // Escenario para el eje Z
               if (i2 == 3) {
                  if (xval >= 0) {
                      if (xval == 0) sprintf(xcad,"Escenario[%d].z = Numero_ecuaciones[%d] + 1;",i,i);
                       else sprintf(xcad,"Escenario[%d].z = %d;",i,xval);
                  } else sprintf(xcad,"Escenario[%d].z = 0;",i);
               }
               // Método númerico activo
               if (i2 == 4) {
                  if (xval >= 0) sprintf(xcad,"Metodo_N_actual[%d] = %d;",i,xval);
               }

               Ip->Formato_impresion(3,1,xcad);
            }
         }
      }
   }
   Ip->Formato_impresion(1,1,"}");

   
   // Genera las funciones de cada sistema
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
       if (Informacion->Inf_sistema[i]->N_Ecuaciones > 1) {
          for (i4 = 0; i4 < Informacion->Inf_sistema[i]->N_Ecuaciones; i4++) {
             sprintf(xcad,"long double Definicion_Usuario::Fn%#04d%#04d(void)",i,i4);
             Ip->Formato_impresion(1,2,xcad);
             Ip->Formato_impresion(1,1,"{");

             // Remplaza las funciones auxiliares
             Remplaza_funciones_auxiliares(Informacion->Inf_sistema[i]->TEcuaciones[i4],xcad3,i);

             // Calcula la longitud de la expresion de la ecuacion
             i3 = strlen(xcad3);
             // Busca el fin de la variable de asignacion
             Busca_caracter(xcad3,'=',pos);
             // Extrae la expresion de ecuacion
             Substr(xcad3,pos+1,i3,xcad2);

             // Cambia el nombre de la variable por X[0], X[1], X[2]...
             for(i1 = 0; i1 < Informacion->Inf_sistema[i]->N_Ecuaciones; i1++) {
                if (Busca_caracter(Informacion->Inf_sistema[i]->TEcuaciones[i1],'\'',pos)) {
                   Substr(Informacion->Inf_sistema[i]->TEcuaciones[i1],0,pos,var);
                   // Cambia las variables de las ecuaciones
                   sprintf(xcad3,"X[%d]",i1);
                   Busca_remplaza_expresion(xcad2,var,xcad3);
                }
             }
          
             // remplaza los parametros
             Remplaza_parametros(xcad2,xcad3,i);

             // Escribe la ecuacion diferencial
             sprintf(xcad,"return ( %s );",xcad3);
             Ip->Formato_impresion(3,1,xcad);
             Ip->Formato_impresion(1,1,"}");
          }
       } else {
          // Graba la ecuación ficticia
          sprintf(xcad,"long double Definicion_Usuario::Fn%#04d%#04d(void)",i,0);
          Ip->Formato_impresion(1,2,xcad);
          Ip->Formato_impresion(1,1,"{");
          // Revisa el tipo de ecuación de que se trate
          xxi = 0, tp_ecu = 0;
          while (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] != '=') {
             if (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] == '\'') tp_ecu ++;
             xxi ++;
          }
          // Graba la función correspondiente para la primera ecuación del sistema
          if (tp_ecu == 1) Ip->Formato_impresion(3,1,"return ( 1.0 );");
           else Ip->Formato_impresion(3,1,"return ( X[1] );");
          Ip->Formato_impresion(1,1,"}");
          // Graba la ecuación real
          sprintf(xcad,"long double Definicion_Usuario::Fn%#04d%#04d(void)",i,1);
          Ip->Formato_impresion(1,2,xcad);
          Ip->Formato_impresion(1,1,"{");
          // Graba la función correspondiente para la segunda ecuación del sistema
          if (tp_ecu == 1) {
             // Ecuación de primer orden
             strcpy(var,Informacion->Inf_sistema[i]->TEcuaciones[0]);
             // Calcula la longitud de la expresion de la ecuacion
             i3 = strlen(var);
             // Busca el fin de la variable de asignacion
             Busca_caracter(var,'=',pos);
             // Extrae la expresion de ecuacion
             Substr(var,pos+1,i3,xcad2);
             // Cambia el nombre de la variable por X[0], X[1], X[2]...
             if (Busca_caracter(var,'\'',pos)) {
                 Substr(var,0,pos,xcad4);
                 // Cambia las variables de las ecuaciones
                 sprintf(xcad3,"X[%d]",1);
                 Busca_remplaza_expresion(xcad2,xcad4,xcad3);
             }
             Busca_remplaza_expresion(xcad2,"t","X[0]");
           } else {
             // Extrae el nombre de la ecuación
             xxi = 0;
             while (Informacion->Inf_sistema[i]->TEcuaciones[0][xxi] != '\'') {
                nom_ecu[xxi] = Informacion->Inf_sistema[i]->TEcuaciones[0][xxi];
                xxi ++;
             }
             nom_ecu[xxi] = 0;
             // Graba la primera ecuación del sistema
             // Remplaza las funciones auxiliares
             Remplaza_funciones_auxiliares(Informacion->Inf_sistema[i]->TEcuaciones[0],xcad1,i);
             // Cambia la variable cuyo nombre es NOM_ECU por x o X
             Busca_remplaza_expresion(xcad1,nom_ecu,"X[0]");
             // Cambia la primera derivada por NOM_ECU
             strcpy(xcad2,nom_ecu);
             strcat(xcad2,"'");
             Busca_remplaza_expresion(xcad1,xcad2,nom_ecu);
             // Cambia la segunda derivada por la primera derivada
             Busca_remplaza_cadenas(xcad1,"''","'");
             // Escribe la segunda ecuación
             strcpy(var,xcad1);
             // Calcula la longitud de la expresion de la ecuacion
             i3 = strlen(var);
             // Busca el fin de la variable de asignacion
             Busca_caracter(var,'=',pos);
             // Extrae la expresion de ecuacion
             Substr(var,pos+1,i3,xcad2);
             // Cambia el nombre de la variable por X[0], X[1], X[2]...
             if (Busca_caracter(var,'\'',pos)) {
                Substr(var,0,pos,xcad4);
                // Cambia las variables de las ecuaciones
                sprintf(xcad3,"X[%d]",1);
                Busca_remplaza_expresion(xcad2,xcad4,xcad3);
             }
          }
          // Remplaza las funciones auxiliares
          Remplaza_funciones_auxiliares(xcad2,xcad3,i);
          memccpy(xcad2,xcad3,0,TAMANO_MAXIMO_CADENA);
          // remplaza los parametros
          Remplaza_parametros(xcad2,xcad3,i);
          // Escribe la ecuacion diferencial
          sprintf(xcad,"return ( %s );",xcad3);
          Ip->Formato_impresion(3,1,xcad);
          Ip->Formato_impresion(1,1,"}");
       }
   }

   delete Ip;
   delete []xcad;
   delete []xcad1;
   delete []xcad2;
   delete []xcad3;
   delete []var;
   delete []nom_ecu;
}


void Ctrl_estructura::Remplaza_funciones_auxiliares(const char *exp, char *xexp, const unsigned int i)
{
   int st = 1, i2, i1, lg;

   char *var1 = new char[TAMANO_MAXIMO_CADENA+1];
   char *var2 = new char[TAMANO_MAXIMO_CADENA+1];

   memccpy(xexp,exp,0,TAMANO_MAXIMO_CADENA);
   // Revisa si existen funciones auxiliares
   if (Informacion->Inf_sistema[i]->N_FuncionesAux) {
      while(st) {
         st = 0;
         // Remplaza la funcion auxiliar dentro de la ecuacion
         for(i1 = 0; i1 < Informacion->Inf_sistema[i]->N_FuncionesAux ;i1++) {
            // Extrae el nombre de la funcion auxiliar
            lg = 0, i2 = 0;
            while(Informacion->Inf_sistema[i]->TFuncionesAux[i1][lg] != '=') {
              var1[lg] = Informacion->Inf_sistema[i]->TFuncionesAux[i1][lg];
              lg ++;
            }
            var1[lg] = 0;

            // Descarta las funciones a graficar
            if (var1[0] == 'F' && var1[1] == '(' && var1[3] == ')' && var1[4] == '=') continue;

            lg++;
            // Agrega parentesis de apertura
            var2[i2] = '(';
            i2++;
            // Extrae el funcion auxiliar
            while(Informacion->Inf_sistema[i]->TFuncionesAux[i1][lg]) {
              var2[i2] = Informacion->Inf_sistema[i]->TFuncionesAux[i1][lg];
              i2 ++, lg ++;
            }
            // Agrega el parentesis de cerradura
            var2[i2] = ')';
            var2[i2+1] = 0;

            // Cambia el nombre de la función auxiliar por la función auxiliar
            st = Busca_remplaza_expresion(xexp,var1,var2);
         }
      }
   }
   delete []var1;
   delete []var2;
}



void Ctrl_estructura::Remplaza_parametros(const char *exp, char *xexp, const unsigned int i)
{
   int i1, i2;
   char *var1 = new char[TAMANO_MAXIMO_CADENA+1];
   char *var2 = new char[TAMANO_MAXIMO_CADENA+1];

   memccpy(xexp,exp,0,TAMANO_MAXIMO_CADENA);
   // Revisa si existen parametros a remplazar
   if (Informacion->Inf_sistema[i]->N_Parametros) {
      // Cambia el nombre del parametro por la expresion adecuada
      for(i1 = 0; i1 < Informacion->Inf_sistema[i]->N_Parametros ;i1++) {
         // Extrae el nombre del parametro
         i2 = 0;
         while(Informacion->Inf_sistema[i]->TParametros[i1][i2] != '=') {
           var1[i2] = Informacion->Inf_sistema[i]->TParametros[i1][i2];
           i2 ++;
         }
         var1[i2] = 0;
         // Cambia el parametro
         sprintf(var2,"P[%d][%d]",i,i1);
         Busca_remplaza_expresion(xexp,var1,var2);
      }
   }
   delete []var1;
   delete []var2;
}



// Genera los archivos de descripcion del proyecto
void Ctrl_estructura::Genera_descripcion(void)
{
   int i, xi;
   char arch[MAXPATH], xarch[MAXPATH];
   
   Manipulador_archivos ma;
   ma.Cambia_ext_path(Informacion->Nombre,"D",xarch);

   // Graba la descripcion del proyecto
   sprintf(arch,"%s%02d",xarch,0);
   Manipulador_archivos *Gp;
   Gp = new Manipulador_archivos;
   Gp->Parametros(arch,GRABA_ARCHIVO,200,"");
   for(i = 0; i < Informacion->N_e_Descripcion; i++) Gp->Graba_linea(Informacion->Descripcion[i]);
   delete Gp;

   // Graba la descripcion del sistema
   for(i = 0; i < Informacion->Numero_sistemas; i++) {
      sprintf(arch,"%s%02d",xarch,i+1);
      Gp = new Manipulador_archivos;
      Gp->Parametros(arch,GRABA_ARCHIVO,200,"");
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Descripcion; xi++) Gp->Graba_linea(Informacion->Inf_sistema[i]->Descripcion[xi]);
      delete Gp;
   }

   // Borra las descripciones que pudiesen existir que no fueron reescritas
   for(i = Informacion->Numero_sistemas; i <= NUMERO_SISTEMAS; i++) {
      sprintf(arch,"%s%02d",xarch,i+1);
      ma.Remueve_archivo(arch,0);
   }
}




// Indica si el nombre del sistema es unico o no
int Ctrl_estructura::Valida_nombre_sistema(const char *sist)
{
   int i, st = 1;
   // Revisa que no existe el nombre del sistema
   for(i = 0; i < Informacion->Numero_sistemas; i ++) {
     if (Compara(sist,Informacion->Inf_sistema[i]->Nombre)) st =0;
   }
   return st;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
// Control de Proyectos
//////////////////////////////////////////////////////////////////////////////////////////////////

// Adiciona un nuevo proyecto
void Ctrl_estructura::Nuevo_proyecto(const char *proy)
{
   // Solicita espacio para el proyecto
   if (Informacion) return;
   Informacion = new Informacion_proyecto;
   if (!Informacion) return;
   Informacion->Modificada = 1;
   // Solicita espacio para el nombre del proyecto
   Informacion->Nombre = new char[strlen(proy)+1];
   // Copia el nombre del proyecto
   strcpy(Informacion->Nombre,proy);
   // Inicializa valores
   Informacion->N_e_Descripcion = 0;
   Informacion->Descripcion = NULL;
   Informacion->Numero_sistemas = 0;
   Informacion->N_e_CodigoEnC = 0;
   Informacion->CodigoEnC = NULL;
   // Inicializa la estructura que contendra a los sistemas
   Informacion->Inf_sistema = new Informacion_sistema *[NUMERO_SISTEMAS];
   for(int i = 0; i < NUMERO_SISTEMAS; i++) Informacion->Inf_sistema[i] = NULL;
}

// Borra el actual proyecto de memoria
void Ctrl_estructura::Borra_proyecto(void)
{
   if (!Informacion) return;
   int i;
   // Borra los sistemas del proyecto
   for(i = 0; i < Informacion->Numero_sistemas; i++) Borra_sistema(i);
   Informacion->Inf_sistema = NULL;
   Informacion->Numero_sistemas = 0;
   // Borra la descripcion de proyecto
   if (Informacion->N_e_Descripcion) {
      for(i = 0; i < Informacion->N_e_Descripcion; i++) delete[] Informacion->Descripcion[i];
      delete[] Informacion->Descripcion;
   }
   Informacion->Descripcion = NULL;
   Informacion->N_e_Descripcion = 0;
   // Borra el nombre del proyecto
   if (Informacion->Nombre) delete[] Informacion->Nombre;
   Informacion->Nombre = NULL;
   // Borra el puntero a la estructura
   delete Informacion;
   Informacion = NULL;
}

// Actualiza la estructura del proyecto
void Ctrl_estructura::Actualiza_estructura_proyecto(void)
{
   if (!Informacion->Numero_sistemas) return;
   int xi, st = 1;
   // Loop para que solo existan nodos vacios al final de la estructura
   while (st)  {
      st = 0;
      for (xi = 0; xi < (NUMERO_SISTEMAS - 1); xi++) {
         if (Informacion->Inf_sistema[xi] == NULL && Informacion->Inf_sistema[xi + 1] != NULL) {
             // Duplica el sistema
             Duplica_sistema(xi + 1, Informacion->Inf_sistema[xi + 1]->Nombre, xi);
             Borra_sistema(xi + 1);
             st = 1;
         }
      }
   }
}

// Cambia el nombre del proyecto
void Ctrl_estructura::Cambia_nombre_proyecto(const char *proy)
{
   // Borra el nombre del proyecto
   if (Informacion->Nombre) delete[] Informacion->Nombre;
   // Solicita espacio para el nombre del proyecto
   Informacion->Nombre = new char[strlen(proy)+1];
   // Copia el nombre del proyecto
   strcpy(Informacion->Nombre,proy);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Control del sistemas
///////////////////////////////////////////////////////////////////////////////////////////////////


// Adiciona un nuevo sistema al proyecto
int Ctrl_estructura::Nuevo_sistema(const char *cad)
{
   if (!Informacion) return 3; // Error no inicializada la clase
   if (Informacion->Numero_sistemas >= NUMERO_SISTEMAS) return 1; // Se excede el numero de sistemas por proyecto
   if (Valida_nombre_sistema(cad)) {
      // Adiciona un nuevo sistema al proyecto
      Informacion->Inf_sistema[Informacion->Numero_sistemas] = new Informacion_sistema;
      if (!Informacion->Inf_sistema[Informacion->Numero_sistemas]) return 3; // Error al inicializar
      // Obtiene la longitud del nombre del sistema
      Informacion->Inf_sistema[Informacion->Numero_sistemas]->Nombre = new char[LG_MAX_NOM_SISTEMA+1];
      // Copia al nombre del nuevo sistema
      memccpy(Informacion->Inf_sistema[Informacion->Numero_sistemas]->Nombre,cad,0,TAMANO_MAXIMO_CADENA);
      // Inicializa los datos del sistema
      Informacion->Inf_sistema[Informacion->Numero_sistemas]->N_e_Descripcion = 0;
      Informacion->Inf_sistema[Informacion->Numero_sistemas]->N_e_Ecuaciones  = 0;
      Informacion->Inf_sistema[Informacion->Numero_sistemas]->Descripcion     = NULL;
      Informacion->Inf_sistema[Informacion->Numero_sistemas]->Ecuaciones      = NULL;
      // Actualiza el numero de sistemas en el proyecto
      Informacion->Numero_sistemas++;
      Informacion->Modificada = 1;
   } else return 2; // Nombre de sistema duplicado
   return 0;  // Sin errores
}


// Duplica el sistema N_S en el sistema  NNSIS con el nombre NOMBRE
int Ctrl_estructura::Duplica_sistema(const int n_s, const char *nombre, const int nnsis)
{
   if (Informacion->Numero_sistemas >= NUMERO_SISTEMAS) return 1; // Se excede el numero de sistemas por proyecto
   int i, xi;
   char xcad[TAMANO_MAXIMO_CADENA];
   i = nnsis;
   // Genera la estructura para contener el sistema
   Informacion->Inf_sistema[i] = new Informacion_sistema;
   Informacion->Inf_sistema[i]->Nombre = new char[LG_MAX_NOM_SISTEMA+1];
   memccpy(Informacion->Inf_sistema[i]->Nombre,nombre,0,TAMANO_MAXIMO_CADENA);
   // Descripcion del sistema
   Informacion->Inf_sistema[i]->N_e_Descripcion = Informacion->Inf_sistema[n_s]->N_e_Descripcion;
   if (Informacion->Inf_sistema[i]->N_e_Descripcion) {
      Informacion->Inf_sistema[i]->Descripcion = new char *[Informacion->Inf_sistema[i]->N_e_Descripcion];
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Descripcion; xi++) {
          memccpy(xcad,Informacion->Inf_sistema[n_s]->Descripcion[xi],0,TAMANO_MAXIMO_CADENA);
          Informacion->Inf_sistema[i]->Descripcion[xi] = new char[strlen(xcad)+1];
          strcpy(Informacion->Inf_sistema[i]->Descripcion[xi],xcad);
      }
   } else Informacion->Inf_sistema[i]->Descripcion = NULL;

   // Ecuaciones
   Informacion->Inf_sistema[i]->N_e_Ecuaciones = Informacion->Inf_sistema[n_s]->N_e_Ecuaciones;
   if (Informacion->Inf_sistema[i]->N_e_Ecuaciones) {
      Informacion->Inf_sistema[i]->Ecuaciones = new char *[Informacion->Inf_sistema[i]->N_e_Ecuaciones];
      // Lee las ecuaciones del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[i]->N_e_Ecuaciones; xi++) {
         memccpy(xcad,Informacion->Inf_sistema[n_s]->Ecuaciones[xi],0,TAMANO_MAXIMO_CADENA);
         Informacion->Inf_sistema[i]->Ecuaciones[xi] = new char[strlen(xcad)+1];
         strcpy(Informacion->Inf_sistema[i]->Ecuaciones[xi],xcad);
      }
   } else Informacion->Inf_sistema[i]->Ecuaciones = NULL;
   Informacion->Modificada = 1;
   return 0;
}


// Borra el actual proyecto de memoria
void Ctrl_estructura::Borra_sistema(const int n_s)
{
   int xi;
   if (!Informacion->Numero_sistemas) return;
   // Borra el nombre del sistema
   delete[] Informacion->Inf_sistema[n_s]->Nombre;

   if (Informacion->Inf_sistema[n_s]->N_e_Descripcion) {
      // Borra la descricion del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[n_s]->N_e_Descripcion; xi++) delete[] Informacion->Inf_sistema[n_s]->Descripcion[xi];
      delete[] Informacion->Inf_sistema[n_s]->Descripcion;
   }

   if (Informacion->Inf_sistema[n_s]->N_e_Ecuaciones) {
      // Borra las ecuaciones del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[n_s]->N_e_Ecuaciones; xi++) delete[] Informacion->Inf_sistema[n_s]->Ecuaciones[xi];
      delete[] Informacion->Inf_sistema[n_s]->Ecuaciones;
   }
   delete Informacion->Inf_sistema[n_s];
   Informacion->Inf_sistema[n_s] = NULL;
   Informacion->Numero_sistemas --;
   Informacion->Modificada = 1;
}

// Borra las ecuaciones del sistema dado
void Ctrl_estructura::Borra_ecuaciones(const int n_s)
{
   int xi;
   if (Informacion->Inf_sistema[n_s]->N_e_Ecuaciones) {
      // Borra las ecuaciones del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[n_s]->N_e_Ecuaciones; xi++) delete[] Informacion->Inf_sistema[n_s]->Ecuaciones[xi];
      delete[] Informacion->Inf_sistema[n_s]->Ecuaciones;
      Informacion->Inf_sistema[n_s]->N_e_Ecuaciones = 0;
      Informacion->Inf_sistema[n_s]->Ecuaciones = NULL;
   }
}

// Borra la descripción del sistema dado
void Ctrl_estructura::Borra_descripcion(const int n_s)
{
   int xi;
   if (Informacion->Inf_sistema[n_s]->N_e_Descripcion) {
      // Borra la descricion del sistema
      for(xi = 0; xi < Informacion->Inf_sistema[n_s]->N_e_Descripcion; xi++) delete[] Informacion->Inf_sistema[n_s]->Descripcion[xi];
      delete[] Informacion->Inf_sistema[n_s]->Descripcion;
      Informacion->Inf_sistema[n_s]->N_e_Descripcion = 0;
      Informacion->Inf_sistema[n_s]->Descripcion = NULL;
   }
}

// Borra la descripción del proyecto
void Ctrl_estructura::Borra_descripcion_proyecto(void)
{
   int xi;
   if (Informacion->N_e_Descripcion) {
      // Borra la descricion del sistema
      for(xi = 0; xi < Informacion->N_e_Descripcion; xi++) delete[] Informacion->Descripcion[xi];
      delete[] Informacion->Descripcion;
      Informacion->N_e_Descripcion = 0;
      Informacion->Descripcion = NULL;
   }
}

// Borra el codigo en C
void Ctrl_estructura::Borra_codigo_en_C(void)
{
   int xi;
   if (Informacion->N_e_CodigoEnC) {
      // Borra el codigo en C
      for(xi = 0; xi < Informacion->N_e_CodigoEnC; xi++) delete[] Informacion->CodigoEnC[xi];
      delete[] Informacion->CodigoEnC;
      Informacion->N_e_CodigoEnC= 0;
      Informacion->CodigoEnC= NULL;
   }
}


// Cambia el nombre del sistema
void Ctrl_estructura::Cambia_nombre_sistema(const int sis, const char *nom)
{
   // Borra el nombre del proyecto
   if (Informacion->Inf_sistema[sis]->Nombre) delete[] Informacion->Inf_sistema[sis]->Nombre;
   // Solicita espacio para el nombre del proyecto
   Informacion->Inf_sistema[sis]->Nombre = new char[strlen(nom)+1];
   // Copia el nombre del proyecto
   strcpy(Informacion->Inf_sistema[sis]->Nombre,nom);
}



// Retorna TRUE si esta definida la función FUNC en el codigo C++, caso contrario retorna FALSE
bool Ctrl_estructura::Funcion_definida_en_codigo_C(const char *func)
{
   int xi;
   unsigned int pos;
   char xcad[200];
   memccpy(xcad,func,0,198);
   strcat(xcad,"(");
   if (Informacion->N_e_CodigoEnC) {
      // Busca función el codigo en C
      for (xi = 0; xi < Informacion->N_e_CodigoEnC; xi++) {
          if (Busca_cadena(Informacion->CodigoEnC[xi],xcad,pos)) return true;
      }
   }
   return false;
}





// Genera encabezado del CPP y HPP
void Ctrl_estructura::Genera_Encabezado(Ctrl_reporte *Ip)
{
   Ip->Formato_impresion(1,1,"//////////////////////////////////////////////////////////////////////////////////////////////");
   Ip->Formato_impresion(1,1,"// Definición de sistemas                                                                   //");
   Ip->Formato_impresion(1,1,"// Revisión: 8 de Enero del 2003                                                            //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Copyright (C) 1997-2003                                                                  //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Análisis y Diseño:                                                                       //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Autor     Dr. Humberto Carrillo Calvet                                                   //");
   Ip->Formato_impresion(1,1,"// E-mail:   carr@servidor.unam.mx                                                          //");
   Ip->Formato_impresion(1,1,"// Página:   http://www.dynamics.unam.edu/hcc                                               //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Autor:    Antonio Carrillo Ledesma                                                       //");
   Ip->Formato_impresion(1,1,"// E-mail:   acl@www.dynamics.unam.edu                                                      //");
   Ip->Formato_impresion(1,1,"// Página:   http://www.dynamics.unam.edu/acl                                               //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Programación:                                                                            //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Autor:    Antonio Carrillo Ledesma                                                       //");
   Ip->Formato_impresion(1,1,"// E-mail:   acl@www.dynamics.unam.edu                                                      //");
   Ip->Formato_impresion(1,1,"// Página:   http://www.dynamics.unam.edu/acl                                               //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //");
   Ip->Formato_impresion(1,1,"// bajo los términos de la Licencia Pública General de GNU según es                         //");
   Ip->Formato_impresion(1,1,"// publicada por la Free Software Foundation, bien de la versión 2 de                       //");
   Ip->Formato_impresion(1,1,"// dicha Licencia o bien (según su elección) de cualquier versión                           //");
   Ip->Formato_impresion(1,1,"// posterior.                                                                               //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //");
   Ip->Formato_impresion(1,1,"// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //");
   Ip->Formato_impresion(1,1,"// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //");
   Ip->Formato_impresion(1,1,"// Licencia Pública General de GNU para más detalles.                                       //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"// Debería haber recibido una copia de la Licencia Pública General junto                    //");
   Ip->Formato_impresion(1,1,"// con este programa. Si no ha sido así, escriba a la Free Software                         //");
   Ip->Formato_impresion(1,1,"// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"//                                                                                          //");
   Ip->Formato_impresion(1,1,"//////////////////////////////////////////////////////////////////////////////////////////////");
}



// Genera codigo base en C++
void Ctrl_estructura::Genera_codigo_base_en_C(Ctrl_reporte *Ip, const int tp)
{
   // Se incerta el código para antes de integrar
   Ip->Formato_impresion(6,2,"// Codigo a ejecutarse antes de integrar"); 
   if (tp == 0 || tp == 1) {
      Ip->Formato_impresion(6,1,"int Antes_integrar(const int tp)"); 
      Ip->Formato_impresion(6,1,"{");
      Ip->Formato_impresion(6,1,"   return 0;");
      Ip->Formato_impresion(6,1,"}");
   }
   
   // Se incerta el código para despues de integrar
   Ip->Formato_impresion(6,2,"// Codigo a ejecutarse despues de integrar"); 
   if (tp == 0 || tp == 2) {
      Ip->Formato_impresion(6,1,"int Despues_integrar(const int tp)"); 
      Ip->Formato_impresion(6,1,"{");
      Ip->Formato_impresion(6,1,"   return 0;");
      Ip->Formato_impresion(6,1,"}");
   }

   // Se incerta el código para limpieza de varibles
   Ip->Formato_impresion(6,2,"// Codigo para limpiar parametros usadas como variables de integración"); 
   if (tp == 0 || tp == 3) {         
      Ip->Formato_impresion(6,1,"int Limpiar_variables(const int tp)"); 
      Ip->Formato_impresion(6,1,"{");
      Ip->Formato_impresion(6,1,"   return 0;");
      Ip->Formato_impresion(6,1,"}");
   }
}



