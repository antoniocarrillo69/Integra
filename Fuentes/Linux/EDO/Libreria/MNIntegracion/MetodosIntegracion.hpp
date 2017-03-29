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



// Nota: Si se desea agregar un nuevo método númerico hay que modiicar los siguientes archivos:
// MetodosIntegracion.cpp, MetodosIntegracion.hpp, 
// BaseMetodosNumericos.cpp, Sistemas.hpp 
// Y si cambian los parametros del método númerico hay que modificar VDMetodosIntegracion.*





#ifndef __MetodosIntegracion__
#define __MetodosIntegracion__


#include "BaseMetodosNumericos.hpp"
#include "../Libreria/Gen_rep.hpp"



// Activa la suspensión de integración numérica
#define _SUSPENDE_INTEGRACION_
// Activa la validacion del cálculo para evitar overflow
#define _VALIDA_CALCULO_
// Indica la cantidad de iteraciones hechas antes de revisar procesos pendientes
#define NUMERO_ITERACIONES_REVISAR  1000
// Indica que se integre el tiempo indicado exactamente
#define _INTEGRAR_TIEMPO_EXACTO_
// Indica que los metodos de paso variable inicien con el tamaño de paso mínimo, en caso contrario inicia con el tamaño de paso máximo
//#define _PASO_MINIMO_




class Metodos_Numericos_Integracion: virtual public Base_Metodos_Numericos
{
   protected:

      long double   c_i_rk[NUMERO_ECUACIONES];
      long double   t_i_rk;
      long double   tiempo_inicial;


                    // Integra sin visualizar usando el método 
                    // Runge-Kutta orden 4 
                    // Retorna (0) Sin errores
                    //         (1) Error en cálculo
                    //         (2) Desbordamiento de limites
      int           Integra_sin_visualizacion(const long double tiempo, const long double incremento);


      
   private:

      // Variables auxiliares
      long double   paso[20][NUMERO_ECUACIONES];     // Variable usada para reportar paso de métodos multipaso
      long double   aux1[NUMERO_ECUACIONES];         // Variables auxiliares para la integración numérica
      long double   aux2[NUMERO_ECUACIONES];
      long double   aux3[NUMERO_ECUACIONES];
      long double   aux4[NUMERO_ECUACIONES];
      long double   aux5[NUMERO_ECUACIONES];
      long double   aux6[NUMERO_ECUACIONES];
      long double   aux7[NUMERO_ECUACIONES];
      long double   aux8[NUMERO_ECUACIONES];
      long double   aux9[NUMERO_ECUACIONES];
      long double   aux10[NUMERO_ECUACIONES];
      long double   aux11[NUMERO_ECUACIONES];
      long double   aux12[NUMERO_ECUACIONES];
      long double   aux13[NUMERO_ECUACIONES];
      long double   aux14[NUMERO_ECUACIONES];
      long double   aux15[NUMERO_ECUACIONES];
      long double   aux16[NUMERO_ECUACIONES];
      long double   aux17[NUMERO_ECUACIONES];
      long double   aux18[NUMERO_ECUACIONES];
      int           i;                 

      bool          Integracion_positiva;            // Inidica si la integracion es en tiempo positivo o negativo
      bool          Visualiza_integracion;           // Indica si se visualiza la integración numérica
      bool          Visualiza_ultima_integracion;    // Indica si se visualiza la última integración numérica
      bool          Ultima_integracion;              // Indica que es la última integración
      bool          Posible_desbordamiento_numerico; // Indica que es posible el desbordamiento numérico
      long double   c_ini[NUMERO_ECUACIONES];        // Condicion inicial en la integración numérica
      long double   Tiempo_actual;                   // Tiempo actual en la integracion numérica
      long double   Tiempo_integracion;              // Tiempo de integración
      long double   Paso_integracion;                // Actual paso de integración
      long double   Paso;                            // Variable que contiene el paso de integración para métodos de paso variable
      long double   tiempo[NUMERO_ECUACIONES];

      


                    // Genera n pasos con Runge-Kutta-Fehlberg de orden 6
                    // Retorna (0) Sin errores
                    //         (1) Error en cálculo
      int           Genera_n_pasos(const int n_pasos, const long double incremento);


                    // Busqueda del período de una trayectoria cerrada
                    // Retorna (0) Sin errores
                    //         (1) Error en cálculo
      int           busqueda_periodo_trayectoria_cerrada(const long double tiempo, const long double paso, const long double tiempo_no_revision, const long double tolerancia, long double &period);


                    // Puntero a un arreglo de métodos numéricos
      void          (Metodos_Numericos_Integracion::*Metodos[NUMERO_METODOS_NUMERICOS])(void);

                    // Método de Euler
      void          Euler(void);
                    // Método Euler Modificado
      void          Euler_modificado(void);
                    // Método Punto medio
      void          Punto_medio(void);
                    // Método Hune
      void          Heun(void);
                    // Método Runge-Kutta I de orden 3
      void          RKI_3(void);
                    // Método Runge-Kutta II de orden 3
      void          RKII_3(void);
                    // Método 3/8 de orden 4
      void          F38_4(void);
                    // Método Runge-Kutta clasico de orden 4
      void          RK_Clasico_4(void);
                    // Método Runge-Kutta-Gill de orden 4
      void          RK_Gill_4(void);
                    // Método England de orden 4
      void          England_4(void);
                    // Método Runge-Kutta-Fehlberg de orden 4
      void          RK_Fehlberg_4(void);
                    // Método Runge-Kutta-Fehlberg I de orden 5
      void          RK_FehlbergI_5(void);
                    // Método England de orden 5
      void          England_5(void);
                    // Método Kutta-Nyström de orden 5
      void          Kutta_Nystrom_5(void);
                    // Método Runge-Kutta-Fehlberg II de orden 5
      void          RK_FehlbergII_5(void);
                    // Método Butcher de orden 5
      void          Butcher_6(void);
                    // Método Runge-Kutta-Fehlberg de orden 6
      void          RK_Fehlberg_6(void);


                    // Método de un paso, paso variable Runge-Kutta de orden 3/2 
      void          VS_RK_3_2(void);
                    // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 4/3 
      void          VS_RKF_4_3(void);
                    // Método de un paso, paso variable Prince-Dormand de orden 5/4 
      void          VS_RK_5_4_6(void);
                    // Método de un paso, paso variable Prince-Dormand I de orden 5/4/7 
      void          VS_RK_5_4_7I(void);
                    // Método de un paso, paso variable Prince-Dormand II de orden 5/4/7 
      void          VS_RK_5_4_7II(void);
                    // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 5/4 
      void          VS_RKF_5_4(void);
                    // Método de un paso, paso variable England de orden 5/4 
      void          VS_RKE_5_4(void);
                    // Método de un paso, paso variable Prince-Dormand de orden 6/5/8 
      void          VS_RK_6_5_8(void);
                    // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 6/5 
      void          VS_RKF_6_5(void);
                    // Método de un paso, paso variable Runge-Kutta-Verner I de orden 6/5 
      void          VS_RKV_6_5I(void);
                    // Método de un paso, paso variable Runge-Kutta-Verner II de orden 6/5 
      void          VS_RKV_6_5II(void);
                    // Método de un paso, paso variable Runge-Kutta-Verner de orden 6/7/10 
      void          VS_RKV_7_6_10(void);
                    // Método de un paso, paso variable Runge-Kutta-Verner de orden 7/8/13 
      void          VS_RKV_8_7_13(void);
                    // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 7/8/13 
      void          VS_RKF_8_7_13(void);
                    // Método de un paso, paso variable Prince-Dormand de orden 8/7/13 
      void          VS_RK_8_7_13(void);
                    // Método de un paso, paso variable Runge-Kutta-Verner de orden 8/9/16 
      void          VS_RKV_9_8_16(void);
      

      
                    // Método de Adams-Bashforth-2Pasos
      void          Adams_Bashforth_2pasos(void);
                    // Método de Adams-Bashforth-3Pasos
      void          Adams_Bashforth_3pasos(void);
                    // Método de Adams-Bashforth-4Pasos
      void          Adams_Bashforth_4pasos(void);
                    // Método de Adams-Bashforth-5Pasos
      void          Adams_Bashforth_5pasos(void);
                    // Método de Adams-Bashforth-6Pasos
      void          Adams_Bashforth_6pasos(void);
                    // Método de Adams-Bashforth-7Pasos
      void          Adams_Bashforth_7pasos(void);

      
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 3
      void          Predictor_corrector_ABM3(void);
                    // Método de Milne-3Pasos
      void          Milne_3pasos(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 4
      void          Predictor_corrector_ABM4(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 5
      void          Predictor_corrector_ABM5(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 5
      void          Predictor_corrector_ABM5a(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 6
      void          Predictor_corrector_ABM6(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 7
      void          Predictor_corrector_ABM7(void);

      

                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 3 Paso Variable
      void          Predictor_corrector_ABM3PV(void);
                    // Método de Predictor-Corrector Milne-Simpson de orden 3
      void          Predictor_corrector_MS3(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 4 Paso Variable
      void          Predictor_corrector_ABM4PV(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 5 Paso Variable
      void          Predictor_corrector_ABM5PV(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 5 Paso Variable
      void          Predictor_corrector_ABM5aPV(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 6 Paso Variable
      void          Predictor_corrector_ABM6PV(void);
                    // Método de Predictor-Corrector Adams-Bashforth-Moulton de orden 7 Paso Variable
      void          Predictor_corrector_ABM7PV(void);

                    // Método de Extrapolación
      void          Extrapolacion(void);

                    // Método de Trapecio con iteraciones de Secante
      void          Trapecio_iteraciones_secante(void);
                    // Método de Euler con iteraciones de Secante
      void          Euler_iteraciones_secante(void);

      
                    // Controla el error en calculos
      void          Error_calculo(void);
                    // Controla error por desbordamiento numerico
      int           Desbordamiento_numerico(void);


   protected:                                           

      //////////////////////////////////////////////////
      // Parametros de los métodos numéricos          //
      //////////////////////////////////////////////////

                    // Número de iteracion actual en la integracion numérica
      long          Numero_iteraciones;
                    // Paso máximo de integracion en métodos de P.V.
      long double   Paso_maximo;
                    // Paso mínimo de integracion en métodos de P.V.
      long double   Paso_minimo;

      Ctrl_reporte *Rep_num;                                        // Apuntador al manejador de reporte de la integracion numerica
      char          C_imp[1000];                                    // Contienen la cadena con la que se generara el reporte
      bool          Reporte_activo;                                 // Indica si esta activo la generacion del reporte de la integracion numerica

   public:



                    // Inicializa la clase
      virtual  void Inicializa(void);

                    // Integra numericamente
      void          Integra_numericamente(const int ti);

                    // Mapeo del período 
      void          Mapeo_periodo(const int ti, const int num);

                    // Calcula el período de una trayectoria cerrada
      void          Calculo_periodo_trayectoria_cerrada(const long double tiempo, const long double incremento, const long double tiempo_no_revision, const long double tolerancia, long double &period);
              
                    // Establece el método numerico activo
      void          Establece_metodo_numerico_integracion(const int tp)
                    {
                       Metodo_N_actual[Sistema_actual] = tp;
                    }

                    // Retorna el método numerico activo
      int           Retorna_metodo_numerico_integracion(void)
                    {
                       return Metodo_N_actual[Sistema_actual];
                    }

                    // Retorna el nombre del metodo numerico
      const char   *Retorna_nombre_metodo_integracion(const int i);

                    // Retorna el valor del parámetro I del método de integracion MET
      long double   Retorna_valor_parametro_metodo_integracion(const int met, const int i)
                    {
                       return (Parametros_metodo[Sistema_actual][met][i+1]);
                    }

                    // Establece el valor VAL del parámetro I del método MET
      void          Establece_valor_parametro_metodo_integracion(const int met, const int i, const long double val)
                    {
                       Parametros_metodo[Sistema_actual][met][i+1] = val;
                    }

                    // Retorna el nombre del parametro dentro del metodo numerico
      const char   *Retorna_nombre_parametro_metodo_integracion(const int tp, const int i);

                    // Retorna el tipo de parámetro del método de integración I
      int           Retorna_tipo_parametros_metodo_integracion(const int i)
                    {
                       return (Tipo_parametros_metodo_integracion[i]);
                    }

                    // Inicializa el reporte de integración
      void          Inicializa_reporte(const char *nombre);

                    // Finaliza el reporte de integración
      void          Finaliza_reporte(void);

                    // Titulo en el reporte de integración
      void          Titulo_reporte(void);              

                    // Detalle en el reporte de integración
      void          Detalle_reporte(const int tp); 

                    // Retorna el valor actual del las iteraciones hechas por el método númerico
      int           Reporta_numero_iteraciones(void)
                    {
                       return Numero_iteraciones;
                    }
                    // Retorna el valor actual del tiempo integrado
      long double   Reporta_tiempo_integrado(void)
                    {
                       return Tiempo_integracion;
                    }

      
};


#endif
