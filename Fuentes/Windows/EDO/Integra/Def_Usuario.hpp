 //////////////////////////////////////////////////////////////////////////////////////////////
 // Definición de sistemas                                                                   //
 // Revisión: 8 de Enero del 2003                                                            //
 //                                                                                          //
 // Copyright (C) 1997-2003                                                                  //
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


 #ifndef __Definicion_Usuario__
 #define __Definicion_Usuario__


 #include "Ctrl_Fun_Aux.hpp"
 #include "../Libreria/Definiciones.hpp"
 #include <math.h>


 // Indica el número máximo de sistemas por proyecto
 #define NUMERO_SISTEMAS               25
 // Indica el número máximo de ecuaciones por sistema
 #define NUMERO_ECUACIONES             4
 // Indica el número máximo de parámetros por sistema
 #define NUMERO_MAX_PARAMETROS         10
 // Indica el número máximo de funciones auxiliares
 #define NUMERO_MAX_FUNCIONES_AUX      9


 class Definicion_Usuario: public Ctrl_Funciones_Auxiliares
 {

    public:

                          // Número de sistemas definidos
       int                Numero_sistemas;
                          // Sistema actual
       int                Sistema_actual;
                          // Nombre del proyecto
       const char        *Proyecto;
                          // Nombre del sistema
       const char        *Nombre_sistema[NUMERO_SISTEMAS];
                          // Número de ecuaciones por sistema
       int                Numero_ecuaciones[NUMERO_SISTEMAS];
                          // Ecuación original para orden uno y dos
       const char        *Ecuacion_original[NUMERO_SISTEMAS];
                          // Nombre de la ecuación por sistema
       const char        *Nombre_ecuacion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
                          // Número de parámetros por sistema
       int                Numero_parametros[NUMERO_SISTEMAS];
                          // Nombre del parámetro por cada sistema
       const char        *Nombre_parametro[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];
                          // Tipo de Ecuación (0) Sistema de ecuaciones (1) Ecuación ordinaria de primer orden
       int                Tipo_ecuacion[NUMERO_SISTEMAS];
                          // Número de funciones auxiliares por sistema
       int                Numero_funciones_auxiliares[NUMERO_SISTEMAS];
                          // Contiene las funciones auxiliares por sistema
       const char        *Funciones_auxiliares[NUMERO_SISTEMAS][NUMERO_MAX_FUNCIONES_AUX];
                          // Contiene los valores de configuración del archivo EXE
       long double        Config[NUMERO_SISTEMAS][6];
                          // Escenarios a trabajar por cada ventana y cada sistema
       C_3I               Escenario[NUMERO_SISTEMAS];
                          // Tipo de ventana activa en el sistema
       int                Ventana_activa[NUMERO_SISTEMAS];
                          // Indica el método actual de integración
       unsigned int       Metodo_N_actual[NUMERO_SISTEMAS];
                          // Parámetros por cada sistema
       long double        P[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];
                          // Variable para las distintas ecuaciones
       long double        X[NUMERO_ECUACIONES];
                          // Actual condición en la integración númerica
       long double        At_Condicion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
                          // Actual tiempo en la integración númerica
       long double        At_Tiempo[NUMERO_SISTEMAS];
                          // Puntero a un arreglo de funciones
       long double        (Definicion_Usuario::*funcion[NUMERO_SISTEMAS][NUMERO_ECUACIONES])(void);
                          // Configuracion del archivo EXE
       void               Configuracion(void);
                          // Iniciliza la clase
       virtual void       Inicializa(void);
                          // Asigna los parametros
       void               Parametros(const unsigned int i);

    protected:
       // Funciones definidas apartir de las ecuaciones diferenciales
      long double Definicion_Usuario::Fn00000000(void);
      long double Definicion_Usuario::Fn00000001(void);
      long double Definicion_Usuario::Fn00000002(void);
      long double Definicion_Usuario::Fn00010000(void);
      long double Definicion_Usuario::Fn00010001(void);
      long double Definicion_Usuario::Fn00010002(void);
      long double Definicion_Usuario::Fn00020000(void);
      long double Definicion_Usuario::Fn00020001(void);
      long double Definicion_Usuario::Fn00020002(void);
      long double Definicion_Usuario::Fn00030000(void);
      long double Definicion_Usuario::Fn00030001(void);
      long double Definicion_Usuario::Fn00040000(void);
      long double Definicion_Usuario::Fn00040001(void);
      long double Definicion_Usuario::Fn00050000(void);
      long double Definicion_Usuario::Fn00050001(void);
      long double Definicion_Usuario::Fn00060000(void);
      long double Definicion_Usuario::Fn00060001(void);
      long double Definicion_Usuario::Fn00070000(void);
      long double Definicion_Usuario::Fn00070001(void);
      long double Definicion_Usuario::Fn00070002(void);
      long double Definicion_Usuario::Fn00070003(void);
      long double Definicion_Usuario::Fn00080000(void);
      long double Definicion_Usuario::Fn00080001(void);
      long double Definicion_Usuario::Fn00090000(void);
      long double Definicion_Usuario::Fn00090001(void);
      long double Definicion_Usuario::Fn00100000(void);
      long double Definicion_Usuario::Fn00100001(void);
      long double Definicion_Usuario::Fn00110000(void);
      long double Definicion_Usuario::Fn00110001(void);
      long double Definicion_Usuario::Fn00120000(void);
      long double Definicion_Usuario::Fn00120001(void);
      long double Definicion_Usuario::Fn00120002(void);
      long double Definicion_Usuario::Fn00130000(void);
      long double Definicion_Usuario::Fn00130001(void);
      long double Definicion_Usuario::Fn00140000(void);
      long double Definicion_Usuario::Fn00140001(void);
      long double Definicion_Usuario::Fn00150000(void);
      long double Definicion_Usuario::Fn00150001(void);
      long double Definicion_Usuario::Fn00160000(void);
      long double Definicion_Usuario::Fn00160001(void);
      long double Definicion_Usuario::Fn00170000(void);
      long double Definicion_Usuario::Fn00170001(void);
      long double Definicion_Usuario::Fn00180000(void);
      long double Definicion_Usuario::Fn00180001(void);
      long double Definicion_Usuario::Fn00190000(void);
      long double Definicion_Usuario::Fn00190001(void);
      long double Definicion_Usuario::Fn00200000(void);
      long double Definicion_Usuario::Fn00200001(void);
      long double Definicion_Usuario::Fn00210000(void);
      long double Definicion_Usuario::Fn00210001(void);
      long double Definicion_Usuario::Fn00220000(void);
      long double Definicion_Usuario::Fn00220001(void);
      long double Definicion_Usuario::Fn00230000(void);
      long double Definicion_Usuario::Fn00230001(void);
      long double Definicion_Usuario::Fn00230002(void);
      long double Definicion_Usuario::Fn00240000(void);
      long double Definicion_Usuario::Fn00240001(void);
      long double Definicion_Usuario::Fn00240002(void);



      // Codigo a ejecutarse antes de integrar
      int Antes_integrar(const int tp)
      {
         return 0;
      }

      // Codigo a ejecutarse despues de integrar
      int Despues_integrar(const int tp)
      {
         return 0;
      }

      // Codigo para limpiar parametros usadas como variables de integración
      int Limpiar_variables(const int tp)
      {
         return 0;
      }
 };


 #endif

