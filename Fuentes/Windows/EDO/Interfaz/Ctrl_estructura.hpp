//////////////////////////////////////////////////////////////////////////////////////////////
// Control de la INTERFAZ DE INTEGRA                                                        //
// Revisión: 10 de Nobiembre del 2003                                                       //
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


#ifndef __CTRL_ESTRUCTURA_HPP__
#define __CTRL_ESTRUCTURA_HPP__



#include "../Libreria/Cadenas.hpp"
#include "../Libreria/Gen_rep.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definiciones de valores máximos para INTERFAZ
#define NUMERO_SISTEMAS                                     100   // Indica el numero maximo de sistemas por proyecto
#define NUMERO_ECUACIONES                                  1000   // Indica el numero maximo de ecuaciones por sistema
#define NUMERO_MAX_PARAMETROS                               500   // Indica el numero maximo de parametros por sistema

// Valores estaticos que afectan directamente a INTEGRA
#define NUMERO_MAX_FUNCIONES_AUX                              9   // Indica el numero maximo de funciones auxiliares
#define LG_MAX_NOM_SISTEMA                                  100   // Indica la longitud maxima del nombre del systema
#define LG_MAX_NOM_PARAMETRO                                 22   // Indica la longitud maxima del nombre del parametro
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef _IDIOMA_ESPANOL_
   #define CTRTXT01 "SinNombre"

#else
   #define CTRTXT01 "NoName"

#endif

// Controla el tipo de versión del sistema
typedef struct Inf_sistema {
   char                  *Nombre;             // Nombre del sistema
   int                    N_e_Descripcion;    // Numero de lineas de la descipcion del sistema
   char                 **Descripcion;        // Descripcion del sistema
   int                    N_e_Ecuaciones;     // Numero de lineas de las ecuaciones del sistema
   char                 **Ecuaciones;         // Ecuaciones, parámetros y funciones auxiliares del sistema 
   int                    N_Ecuaciones;       // Numero de lineas de las ecuaciones del sistema
   char                 **TEcuaciones;        // Ecuaciones del sistema
   int                    N_Parametros;       // Numero de lineas de los parámetros del sistema
   char                 **TParametros;        // Ecuaciones del sistema
   int                    N_FuncionesAux;     // Numero de lineas de las funciones auxiliares del sistema
   char                 **TFuncionesAux;      // Ecuaciones del sistema
} Informacion_sistema;


// Estructura a la información del proyecto
typedef struct Inf_proyecto {
   int                    Modificada;         // Indica si la estructura fue modificada
   char                  *Nombre;             // Nombre del proyecto
   int                    N_e_Descripcion;    // Numero de elementos de la descripcion
   char                 **Descripcion;        // Contienen la descripcion del proyecto
   int                    Numero_sistemas;    // Indica el numero de sistemas en el proyecto
   Informacion_sistema  **Inf_sistema;        // Contiene a los sistemas del proyecto
   int                    N_e_CodigoEnC;      // Numero de elementos del codigo en C del proyecto
   char                 **CodigoEnC;          // Contiene en codigo en C del proyecto
} Informacion_proyecto;


// Clase Ctrl_estructura de proyectos
class Ctrl_estructura: public Cadenas 
{
   private:
                         
      Inf_proyecto      *Informacion;         // Definicion de la estructura de informacion del proyecto


                         // Genera encabezado del CPP y HPP
      void               Genera_Encabezado(Ctrl_reporte *Ip);
                         // Genera codigo base en C++
      void               Genera_codigo_base_en_C(Ctrl_reporte *Ip, const int tp);

                         // Genera el archivo CPP
      void               Genera_cpp(void);
                         // Genera el archivo HPP
      void               Genera_hpp(void);
                         // Genera los archivos de descripcion
      void               Genera_descripcion(void);
                         // Remplaza las funciones auxiliares
      void               Remplaza_funciones_auxiliares(const char *exp, char *xexp, const unsigned int i);
                         // Remplaza los parámetros
      void               Remplaza_parametros(const char *exp, char *xexp, const unsigned int i);

   public:

                         // Constructor de la clase
                         Ctrl_estructura(void)
                         {
                            Informacion = NULL;
                            Nuevo_proyecto(CTRTXT01);
                         }
                         
                         // Destructor de la clase
                        ~Ctrl_estructura()
                         {
                            Borra_proyecto();
                            Informacion = NULL;
                         }


                         // Nuevo proyecto
      void               Nuevo_proyecto(const char *proy);
                         // Borra el proyecto
      void               Borra_proyecto(void);
                         // Actualiza la estructura del proyecto
      void               Actualiza_estructura_proyecto(void);
                         // Cambia el nombre del proyecto
      void               Cambia_nombre_proyecto(const char *proy);
                         // Graba el proyecto
      void               Graba_proyecto(void);
                         // Lee el proyecto
      void               Lee_proyecto(const char *nombre);
                         // Imprime el proyecto
      void               Imprime_proyecto(void);
                         // Imprime el sistema indicado
      void               Imprime_sistema(const int sis);
                         // Revisa que el sistema no tenga errores
      int                Revisa_sistema(const int sis);
                         // Generar EXE
      int                Generar(void);


      
                         // Nuevo sistema
      int                Nuevo_sistema(const char *nom);
                         // Duplica el sistema N_S con el nombre NOMBRE
      int                Duplica_sistema(const int n_s, const char *nombre, const int nnsis);
                         // Cambia el nombre del sistema
      void               Cambia_nombre_sistema(const int sis, const char *nom);
                         // Borra el sistema indicado
      void               Borra_sistema(const int n_s);
                         // Borra las ecuaciones del sistema dado
      void               Borra_ecuaciones(const int n_s);
                         // Borra la descripción del sistema dado
      void               Borra_descripcion(const int n_s);
                         // Borra la descripción del proyecto
      void               Borra_descripcion_proyecto(void);
                         // Borra el codigo en C
      void               Borra_codigo_en_C(void);
                         // Indica si el nombre del sistema es unico o no
      int                Valida_nombre_sistema(const char *sist);
                         // Retorna si el proyecto se ha modificado
      int                Proyecto_modificado(void)
                         {
                            return (Informacion->Modificada);
                         }
      void               Proyecto_modificado(const bool st)
                         {
                            Informacion->Modificada = st;
                         }
                         // Retorna el numero de sistemas
      int                Numero_sistemas(void)
                         {
                            return Informacion->Numero_sistemas;
                         }
                         // Retorna nombre del sistema
      const char        *Retorna_nombre_sistema(const int sis)
                         {
                            return (Informacion->Inf_sistema[sis]->Nombre);
                         }
                         // Crea espacio para la descripcion del proyecto
      int                Crea_espacio_descripcion_proyecto(const int i)
                         {
                            Informacion->Descripcion = new char *[i];
                            Informacion->N_e_Descripcion  = 0;
                            if (Informacion->Descripcion)return 1;
                            return 0;
                         }
                         // Almacena la descripcion del proyecto
      void               Almacena_descripcion_proyecto(const char *cad)
                         {
                            Informacion->Descripcion[Informacion->N_e_Descripcion] = new char[strlen(cad)+1];
                            if (!Informacion->Descripcion[Informacion->N_e_Descripcion]) return;
                            strcpy(Informacion->Descripcion[Informacion->N_e_Descripcion],cad);
                            Informacion->N_e_Descripcion ++;
                         }
                         // Retorna el numero de lineas de la descripcion del proyecto
      int                Numero_lineas_descripcion_proyecto(void)
                         {
                            return (Informacion->N_e_Descripcion);
                         }
                         // Retorna la cadena i-esima de la descripcion del proyecto
      char              *Retorna_cadena_descripcion_proyecto(const int lin)
                         {
                            return(Informacion->Descripcion[lin]);
                         }
                         // Crea espacio para el codigo en C
      int                Crea_espacio_codigo_en_C(const int i)
                         {
                            Informacion->CodigoEnC = new char *[i];
                            Informacion->N_e_CodigoEnC = 0;
                            if (Informacion->CodigoEnC)return 1;
                            return 0;
                         }
                         // Almacena el codigo en C
      void               Almacena_codigo_en_C(const char *cad)
                         {
                            Informacion->CodigoEnC[Informacion->N_e_CodigoEnC] = new char[strlen(cad)+1];
                            if (!Informacion->CodigoEnC[Informacion->N_e_CodigoEnC]) return;
                            strcpy(Informacion->CodigoEnC[Informacion->N_e_CodigoEnC],cad);
                            Informacion->N_e_CodigoEnC ++;
                         }
                         // Retorna el numero de lineas del codigo en C
      int                Numero_lineas_codigo_en_C(void)
                         {
                            return (Informacion->N_e_CodigoEnC);
                         }
                         // Retorna la cadena i-esima del codigo en C
      char              *Retorna_cadena_codigo_en_C(const int lin)
                         {
                            return(Informacion->CodigoEnC[lin]);
                         }

                         // Retorna TRUE si esta definida la función FUNC en el codigo C++, caso contrario retorna FALSE
      bool               Funcion_definida_en_codigo_C(const char *func);
      
                         // Retorna nombre del proyecto
      const char        *Retorna_nombre_proyecto(void)
                         {
                            return (Informacion->Nombre);
                         }
                         // Crea espacio para la descripcion del sistema
      int                Crea_espacio_descripcion_sistema(const int sis, const int i)
                         {
                            Informacion->Inf_sistema[sis]->Descripcion = new char *[i];
                            Informacion->Inf_sistema[sis]->N_e_Descripcion  = 0;
                            if (Informacion->Inf_sistema[sis]->Descripcion)return 1;
                            return 0;
                         }
                         // Almacena la descripcion del sistema
      void               Almacena_descripcion_sistema(const int sis, const char *cad)
                         {
                            Informacion->Inf_sistema[sis]->Descripcion[Informacion->Inf_sistema[sis]->N_e_Descripcion] = new char[strlen(cad)+1];
                            if (!Informacion->Inf_sistema[sis]->Descripcion[Informacion->Inf_sistema[sis]->N_e_Descripcion]) return;
                            strcpy(Informacion->Inf_sistema[sis]->Descripcion[Informacion->Inf_sistema[sis]->N_e_Descripcion],cad);
                            Informacion->Inf_sistema[sis]->N_e_Descripcion ++;
                         }
                         // Retorna el numero de lineas de la descripcion del sistema
      int                Numero_lineas_descripcion_sistema(const int sis)
                         {
                            if (Numero_sistemas() > 0) {
                               return (Informacion->Inf_sistema[sis]->N_e_Descripcion);
                            }
                            return 0;
                         }
                         // Retorna la cadena i-esima de la descripcion del sistema
      char              *Retorna_cadena_descripcion_sistema(const int sis, const int lin)
                         {
                            return(Informacion->Inf_sistema[sis]->Descripcion[lin]);
                         }
                         // Crea espacio para las ecuaciones del sistema
      int                Crea_espacio_ecuaciones_sistema(const int sis, const int i)
                         {
                            Informacion->Inf_sistema[sis]->Ecuaciones= new char *[i];
                            Informacion->Inf_sistema[sis]->N_e_Ecuaciones= 0;
                            if (Informacion->Inf_sistema[sis]->Ecuaciones) return 1;
                            return 0;
                         }
                         // Almacena las ecuaciones del sistema
      void               Almacena_ecuaciones_sistema(const int sis, const char *cad)
                         {
                            Informacion->Inf_sistema[sis]->Ecuaciones[Informacion->Inf_sistema[sis]->N_e_Ecuaciones] = new char[strlen(cad)+1];
                            if (!Informacion->Inf_sistema[sis]->Ecuaciones[Informacion->Inf_sistema[sis]->N_e_Ecuaciones]) return;
                            strcpy(Informacion->Inf_sistema[sis]->Ecuaciones[Informacion->Inf_sistema[sis]->N_e_Ecuaciones],cad);
                            Informacion->Inf_sistema[sis]->N_e_Ecuaciones++;
                         }
                         // Retorna el numero de lineas de las ecuaciones del sistema
      int                Numero_lineas_ecuaciones_sistema(const int sis)
                         {
                            if (Numero_sistemas() > 0) {
                               return (Informacion->Inf_sistema[sis]->N_e_Ecuaciones);
                            }
                            return 0;
                         }
                         // Retorna la cadena i-esima de las ecuaciones del sistema
      char              *Retorna_cadena_ecuaciones_sistema(const int sis, const int lin)
                         {
                            return(Informacion->Inf_sistema[sis]->Ecuaciones[lin]);
                         }

                 // Indica el tipo de expresion pasada como parametro
                 // (0)  No reconocida 
                 // (1)  Funcion
                 // (2)  Parametro
                 // (3)  Expresion aritmetica
                 // (4)  Ecuacion Diferencial
                 // (5)  Expresion de configuracion
     int         Tipo_expresion(const char *exp);
                         
};

#endif
