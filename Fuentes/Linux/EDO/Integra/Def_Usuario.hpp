 //////////////////////////////////////////////////////////////////////////////////////////////
 // Definici�n de sistemas                                                                   //
 // Revisi�n: 8 de Enero del 2003                                                            //
 //                                                                                          //
 // Copyright (C) 1997-2003                                                                  //
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


 #ifndef __Definicion_Usuario__
 #define __Definicion_Usuario__


 #include "Ctrl_Fun_Aux.hpp"
 #include "../Libreria/Definiciones.hpp"
 #include <math.h>


 // Indica el n�mero m�ximo de sistemas por proyecto
 #define NUMERO_SISTEMAS               25
 // Indica el n�mero m�ximo de ecuaciones por sistema
 #define NUMERO_ECUACIONES             4
 // Indica el n�mero m�ximo de par�metros por sistema
 #define NUMERO_MAX_PARAMETROS         10
 // Indica el n�mero m�ximo de funciones auxiliares
 #define NUMERO_MAX_FUNCIONES_AUX      9


 class Definicion_Usuario: public Ctrl_Funciones_Auxiliares
 {

    public:

                          // N�mero de sistemas definidos
       int                Numero_sistemas;
                          // Sistema actual
       int                Sistema_actual;
                          // Nombre del proyecto
       const char        *Proyecto;
                          // Nombre del sistema
       const char        *Nombre_sistema[NUMERO_SISTEMAS];
                          // N�mero de ecuaciones por sistema
       int                Numero_ecuaciones[NUMERO_SISTEMAS];
                          // Ecuaci�n original para orden uno y dos
       const char        *Ecuacion_original[NUMERO_SISTEMAS];
                          // Nombre de la ecuaci�n por sistema
       const char        *Nombre_ecuacion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
                          // N�mero de par�metros por sistema
       int                Numero_parametros[NUMERO_SISTEMAS];
                          // Nombre del par�metro por cada sistema
       const char        *Nombre_parametro[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];
                          // Tipo de Ecuaci�n (0) Sistema de ecuaciones (1) Ecuaci�n ordinaria de primer orden
       int                Tipo_ecuacion[NUMERO_SISTEMAS];
                          // N�mero de funciones auxiliares por sistema
       int                Numero_funciones_auxiliares[NUMERO_SISTEMAS];
                          // Contiene las funciones auxiliares por sistema
       const char        *Funciones_auxiliares[NUMERO_SISTEMAS][NUMERO_MAX_FUNCIONES_AUX];
                          // Contiene los valores de configuraci�n del archivo EXE
       long double        Config[NUMERO_SISTEMAS][6];
                          // Escenarios a trabajar por cada ventana y cada sistema
       C_3I               Escenario[NUMERO_SISTEMAS];
                          // Tipo de ventana activa en el sistema
       int                Ventana_activa[NUMERO_SISTEMAS];
                          // Indica el m�todo actual de integraci�n
       unsigned int       Metodo_N_actual[NUMERO_SISTEMAS];
                          // Par�metros por cada sistema
       long double        P[NUMERO_SISTEMAS][NUMERO_MAX_PARAMETROS];
                          // Variable para las distintas ecuaciones
       long double        X[NUMERO_ECUACIONES];
                          // Actual condici�n en la integraci�n n�merica
       long double        At_Condicion[NUMERO_SISTEMAS][NUMERO_ECUACIONES];
                          // Actual tiempo en la integraci�n n�merica
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

      // Codigo para limpiar parametros usadas como variables de integraci�n
      int Limpiar_variables(const int tp)
      {
         return 0;
      }
 };


 #endif

