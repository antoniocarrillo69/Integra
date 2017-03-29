//////////////////////////////////////////////////////////////////////////////////////////////
// Base de Métodos Numéricos                                                                //
// Revisión: 6 de Abril del 2001                                                            //
//                                                                                          //
// Copyright (C) 2001                                                                       //
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


#ifndef __BaseMetodosNumericos__
#define __BaseMetodosNumericos__

#include <stdio.h>
#include "Sistemas.hpp"
#include "Vent_Graf_Controlador.hpp"
   
#define PUNTOS                              1
#define LINEAS                              0


// Base de los métodos numéricos
class Base_Metodos_Numericos: virtual public Sistemas, virtual public Control_Visualizacion
{

   private:
      long double        aux[NUMERO_ECUACIONES+2];
      C_3D               aux1, aux2;
      int                ind;


   public:
      bool          Suspende_Calculo;
      bool          Guarda_posicion;
      TColor        Color_Integracion;
      TColor        Color_Flecha_Campo_Vectorial;
      TColor        Color_Cuerpo_Campo_Vectorial;
      TColor        Color_Funcion_Auxiliar;
      TColor        Color_Isoclina;

      void          Retorna_colores(TColor &c1, TColor &c2, TColor &c3, TColor &c4, TColor &c5, TColor &c6, TColor &c7, TColor &c8) 
                    {
                       c1 = Color_Flecha_Campo_Vectorial;
                       c2 = Color_Cuerpo_Campo_Vectorial;
                       c3 = Color_Funcion_Auxiliar;
                       c4 = Color_Integracion;
                       c5 = Color_Isoclina;
                       c6 = Color_Eje_X;
                       c7 = Color_Eje_Y;
                       c8 = Color_Eje_Z;
                    }

      void          Fija_colores(const TColor c1, const TColor c2, const TColor c3, const TColor c4, const TColor c5, const TColor c6, const TColor c7, const TColor c8) 
                    {
                       Color_Flecha_Campo_Vectorial = c1;
                       Color_Cuerpo_Campo_Vectorial = c2;
                       Color_Funcion_Auxiliar = c3;
                       Color_Integracion = c4;
                       Color_Isoclina = c5;
                       Color_Eje_X = c6;
                       Color_Eje_Y = c7;
                       Color_Eje_Z = c8;
                    }


      TColor        Retorna_color_integracion(void)
                    {
                       return Color_Integracion;
                    }              
                    
      void          Fija_color_integracion(const TColor col)
                    {
                       Color_Integracion = col;
                    }              
      
                    // Inicializa la base
      void          Inicializa(void);

                    // Hace las conversiones necesarias para dibujar un punto
      void          Dibuja_punto(const long double ini[], const long double t, const TColor color);

                    // Hace las conversiones necesarias para dibujar una linea
      void          Dibuja_linea(const long double ini[], const long double fin[], const long double t_ini, const long double t_fin, const TColor color);

      void          Actualiza_condicion_inicial(void);

      const char   *Retorna_nombre_proyecto(void)
                    {
                       return (Proyecto);
                    }

      long double   Retorna_condiciones_iniciales(const int i)
                    {
                       if (i < Numero_ecuaciones[Sistema_actual]) return (Ac_Condicion[Sistema_actual][i]);
                        else return (Ac_Tiempo[Sistema_actual]);
                    }

                    // Establece el valor AUX de la condición inicial I
      void          Establece_condiciones_iniciales(const int i, const long double aux);

                    // Retorna las coordenadas iniciales
      void          Condiciones_iniciales_texto(char *cad);

                    // Establece las condiciones iniciales en el origen de los ejes coordenados
      void          Condiciones_iniciales_al_origen(void);
      
                    // Establece las condiciones iniciales al centro de la ventana
      void          Condiciones_iniciales_al_centro_ventana(void);
      
      void          Incrementa_condicion_inicial(const bool x, const bool y, const bool z);

      void          Decrementa_condicion_inicial(const bool x, const bool y, const bool z);
                    
                    // Retorna el paso del cursor
      void          Retorna_paso_cursor(C_3D &paso)
                    {
                       paso.x = Paso_cursor[Sistema_actual].x;
                       paso.y = Paso_cursor[Sistema_actual].y;
                       paso.z = Paso_cursor[Sistema_actual].z;
                    }

                    // fija el paso del cursor
      void          Establece_paso_cursor(const C_3D paso)
                    {
                       if (paso.x > 0.0) Paso_cursor[Sistema_actual].x = paso.x;
                       if (paso.y > 0.0) Paso_cursor[Sistema_actual].y = paso.y;
                       if (paso.z > 0.0) Paso_cursor[Sistema_actual].z = paso.z;
                    }
                    
                    // Retorna el incremento del paso del cursor
      void          Retorna_incremento_paso_cursor(C_3D &incremento_paso)
                    {
                       incremento_paso.x = Incremento_paso_cursor[Sistema_actual].x;
                       incremento_paso.y = Incremento_paso_cursor[Sistema_actual].y;
                       incremento_paso.z = Incremento_paso_cursor[Sistema_actual].z;
                    }

                    // Incrementa el paso del cursor de manera homogénea
      void          Incrementa_paso_cursor(void)
                    {
                       Paso_cursor[Sistema_actual].x += Incremento_paso_cursor[Sistema_actual].x;
                       Paso_cursor[Sistema_actual].y += Incremento_paso_cursor[Sistema_actual].y;
                       Paso_cursor[Sistema_actual].z += Incremento_paso_cursor[Sistema_actual].z;
                    }

                    // Decrementa el paso del cursor de manera homogénea
      void          Decrementa_paso_cursor(void)
                    {
                       if (Paso_cursor[Sistema_actual].x > (2.0 *Incremento_paso_cursor[Sistema_actual].x)) Paso_cursor[Sistema_actual].x -= Incremento_paso_cursor[Sistema_actual].x;
                       if (Paso_cursor[Sistema_actual].y > (2.0 *Incremento_paso_cursor[Sistema_actual].y)) Paso_cursor[Sistema_actual].y -= Incremento_paso_cursor[Sistema_actual].y;
                       if (Paso_cursor[Sistema_actual].z > (2.0 *Incremento_paso_cursor[Sistema_actual].z)) Paso_cursor[Sistema_actual].z -= Incremento_paso_cursor[Sistema_actual].z;
                    }
                    
                    // fija el incremento del paso del cursor
      void          Establece_incremento_paso_cursor(const C_3D incremento_paso)
                    {
                       if (incremento_paso.x > 0.0) Incremento_paso_cursor[Sistema_actual].x = incremento_paso.x;
                       if (incremento_paso.x > 0.0) Incremento_paso_cursor[Sistema_actual].y = incremento_paso.y;
                       if (incremento_paso.x > 0.0) Incremento_paso_cursor[Sistema_actual].z = incremento_paso.z;
                    }

      int           Retorna_numero_sistemas(void)
                    {
                       return Numero_sistemas;
                    }
                    
                    // Retorna el numero de sistema actual
      int           Retorna_numero_sistema_actual(void)
                    {
                       return Sistema_actual;
                    }

      void          Establece_numero_sistema_actual(const int sistema)
                    {
                       Sistema_actual = sistema;
                    }

      const char   *Retorna_nombre_sistema(const int i)
                    {
                       return (Nombre_sistema[i]);
                    }

      int           Retorna_numero_ecuaciones_sistema(void)
                    {
                       return (Numero_ecuaciones[Sistema_actual]);
                    }

      int           Retorna_numero_ecuaciones_sistema(const int i)
                    {
                       return (Numero_ecuaciones[i]);
                    }
                    
      const char   *Retorna_ecuacion_sistema(const int i)
                    {
                       return (Nombre_ecuacion[Sistema_actual][i]);
                    }

      const char   *Retorna_ecuacion_sistema(const int i, const int xi)
                    {
                       return (Nombre_ecuacion[i][xi]);
                    }

      const char   *Retorna_ecuacion_original(const int i)
                    {
                       return (Ecuacion_original[i]);
                    }

                    // Retorna el numero de la condición inicial asociada al escenario
                    // (1) X, (2) Y, (3) Z
      int           Retorna_esenario_activo(const int i)
                    {
                       if(i == 1) return (Escenario[Sistema_actual].x);
                       if(i == 2) return (Escenario[Sistema_actual].y);
                       if(i == 3) return (Escenario[Sistema_actual].z);
                       return 0;
                    }

      void          Establece_esenario_activo(const int i, const int esc)
                    {
                       if(i == 1) Escenario[Sistema_actual].x = esc;
                       if(i == 2) Escenario[Sistema_actual].y = esc;
                       if(i == 3) {
                          Escenario[Sistema_actual].z = esc;
                          if (Escenario[Sistema_actual].z == 0) Ventana_activa[Sistema_actual] = EJES_COORDENADOS_2D;
                           else Ventana_activa[Sistema_actual] = EJES_COORDENADOS_3D;
                       }
                    }

      void          Establece_grafica_puntos_o_lineas(const int val)
                    {
                       Grafica_puntos[Sistema_actual] = val;
                    }

      int           Retorna_grafica_puntos_o_lineas(void)
                    {
                       if(Grafica_puntos[Sistema_actual]) return PUNTOS;
                       return LINEAS;
                    }

       int          Numero_parametros_sistema(void)
                    {
                       return (Numero_parametros[Sistema_actual]);
                    }           

       int          Numero_parametros_sistema(const int i)
                    {
                       return (Numero_parametros[i]);
                    }           

       const char  *Retorna_nombre_parametro(const int i)
                    {
                      return(Nombre_parametro[Sistema_actual][i]);
                    }

       const char  *Retorna_nombre_parametro(const int sis, const int par)
                    {
                      return(Nombre_parametro[sis][par]);
                    }
       
       long double  Retorna_valor_parametro(const int i)
                    {
                       return (P[Sistema_actual][i]);
                    }             

       long double  Retorna_valor_parametro(const int sis, const int par)
                    {
                       return (P[sis][par]);
                    }             
      
       void         Establece_valor_parametro(const int i, const long double val)
                    {
                       P[Sistema_actual][i] = val;
                    }             

                    // Nombre de la ecuacion numero N_E en el sistema SIS
      void          Retorna_variable_ecuacion_sistema_activo(const int i, char *cad);

                    // Nombre de la ecuacion numero N_E en el sistema SIS
      void          Retorna_variable_ecuacion_sistema(const int sis, const int i, char *cad);

                    // Actualiza el valor de la cota para evitar errores de desbordamiento en el cálculo
      void          Actualiza_valores_evitar_overflow(const int i);

                    // Retorna el valor de la cota para evitar errores de desbordamiento en el cálculo
      long double   Retorna_cota_evitar_overflow(void)
                    {
                        return (MAX_VALOR[Sistema_actual]);
                    }

                    // Fila el valor de la cota para evitar errores de desbordamiento en el cálculo
      void          Fija_cota_evitar_overflow(const long double cot)
                    {
                        MAX_VALOR[Sistema_actual] = cot;
                    }              
                    
                    // Ajusta tamano de los vectores del campo vectorial
      void          AjustaConfiguracionCampoVectorial(const int i) 
                    {
                       Parametros_campo_vectorial[i][2] = ((Dimensiones[i].Xf - Dimensiones[i].Xi) / Parametros_campo_vectorial[Sistema_actual][0]) * 0.95;
                       Parametros_campo_vectorial[i][3] = ((Dimensiones[i].Yf - Dimensiones[i].Yi) / Parametros_campo_vectorial[Sistema_actual][1]) * 0.95;
                    } 

                    // Fija el estado de guardar la última posición de integración
      void          Fija_Guardar_posicion_integracion(const bool st)
                    {
                       Guarda_posicion = st;
                    }  

                    // Solocita detener calculo
      void          Detiene_calculo(void)
                    {
                       Suspende_Calculo = true;
                    } 
                    
};


#endif
