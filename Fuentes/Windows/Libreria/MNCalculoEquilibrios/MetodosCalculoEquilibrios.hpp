//////////////////////////////////////////////////////////////////////////////////////////////
// M�todos de c�lculo de equilibrios                                                        //
// Revisi�n: 20 de abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001-2020                                                                  //
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


#ifndef __MetodosCalculoEquilibrios__
#define __MetodosCalculoEquilibrios__


#include "MetodosIntegracion.hpp"


class Metodos_Numericos_Calculo_Equilibrios: virtual public Metodos_Numericos_Integracion
{
   private:
      long double    Paso_busqueda_equilibrio;
      long double    Tiempo_minimo;
                     // Dimensi�n m�nima
      long double    Min;
                     // Dimensi�n m�xima
      long double    Max;
                     // Incremento en el barrido
      long double    Inc;
                     // N�mero de puntos de la partici�n 
      int            Numero_puntos;
                     // Numero de Elemntos en el arreglo de equilibrios
      int            n_e;
      long double    c_i[NUMERO_ECUACIONES], c_f[NUMERO_ECUACIONES];
      long double    pos_equilibrio[100][NUMERO_ECUACIONES], t_f;


   


                     // C�lculo de equilibrios usando fuerza bruta 
      int            Calculo_equilibrios_fuerza_bruta(void);
      void           Barrido_condiciones_iniciales(const int i, const long double paso);


                 
   public:

                     // Inicializa la clase
      virtual void   Inicializa(void)
                     {
                        Numero_puntos = 40;
                        Max = 10.0;
                        Min = -10.0;
                        Paso_busqueda_equilibrio = 5.0e-2;
                        Tiempo_minimo = 200.0;
                     }
   
                     // C�lculo de equilibrios usando fuerza bruta 
      int            Calculo_equilibrios(void)
                     {
                        return (Calculo_equilibrios_fuerza_bruta());
                     }

      void           Retorna_configura_calculo_equilibrios(int &num, long double &min, long double &max, long double &paso, long double &tiempo)
                     {
                        num = Numero_puntos;
                        max = Max;
                        min = Min;
                        paso = Paso_busqueda_equilibrio;
                        tiempo = Tiempo_minimo;
                     }
                     
      void           Fija_configura_calculo_equilibrios(const int num, const long double min, const long double max, const long double paso, const long double tiempo)
                     {
                        Numero_puntos = num;
                        Max = max;
                        Min = min;
                        Paso_busqueda_equilibrio = paso;
                        Tiempo_minimo = tiempo;
                     }
};


#endif
