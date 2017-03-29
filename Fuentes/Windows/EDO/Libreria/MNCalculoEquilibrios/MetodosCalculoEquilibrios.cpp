//////////////////////////////////////////////////////////////////////////////////////////////
// M�todos de c�lculo de equilibrios                                                        //
// Revisi�n: 20 de abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001-2002                                                                  //
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


#include "MetodosCalculoEquilibrios.hpp"
#include "../Libreria/Gen_rep.hpp"
#include <math.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculo de equilibriosusando fuerza bruta                                                           //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int Metodos_Numericos_Calculo_Equilibrios::Calculo_equilibrios_fuerza_bruta(void) 
{
    char xcad[100];
    int ii, i, n_i;

    // Inicializaci�n de datos
    n_e = 0;
    Inc = (Max - Min) / Numero_puntos;


    Ctrl_reporte *Ip = new Ctrl_reporte;
    Ip->Parametros(0,66,120,CONFIGURACION,LPT1,"ESPECIFICATIONS");

    Ip->Formato_impresion(1,2,"Equilbriums Stable");
    Ip->Formato_impresion(1,1,"");
    // Busqueda de equilibrios estables
    Barrido_condiciones_iniciales((Numero_ecuaciones[Sistema_actual] - 1), Paso_busqueda_equilibrio);
    for(ii = 0; ii < n_e; ii++) {
       for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          sprintf(xcad,"%+1.18Lf",pos_equilibrio[ii][i]);
          Ip->Formato_impresion(1 + 25*i,0,xcad);
       }
       Ip->Formato_impresion(1,1,"");
    }
    n_i = n_e;

    Ip->Formato_impresion(1,2,"Equilbriums Unstable");
    Ip->Formato_impresion(1,1,"");
    // Busqueda de equilibrios inestables
    Barrido_condiciones_iniciales((Numero_ecuaciones[Sistema_actual] - 1), -Paso_busqueda_equilibrio);
    for(ii = n_i; ii < n_e; ii++) {
       for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
          sprintf(xcad,"%+1.18Lf",pos_equilibrio[ii][i]);
          Ip->Formato_impresion(1 + 25*i,0,xcad);
       }
       Ip->Formato_impresion(1,1,"");
    }
    delete Ip;
    return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Barrido de condiciones iniciales para la busqueda de equilibrios usando fuerza bruta                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Metodos_Numericos_Calculo_Equilibrios::Barrido_condiciones_iniciales(const int elem, const long double paso)
////////////////////////////////////////////////////////////////////////////////////////////////////////
// Error por programar ...
// Utilizar el hecho que si converge hacia un equilibrio ya conocido no continue con la integraci�n
////////////////////////////////////////////////////////////////////////////////////////////////////////
{
   int i, ii, sw, sw1; 

   for (c_i[elem] = Min; c_i[elem] <= Max; c_i[elem] += Inc) {
       if (elem > 0) Barrido_condiciones_iniciales((elem - 1), paso);
       // Fija condicion inicial
       for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = c_i[i];
       t_i_rk = 0.0;
       // Si no esta lleno el arreglo
       if (n_e < 99) {
          // C�lculo del Transitorio
          if (!Integra_sin_visualizacion(Tiempo_minimo, paso)) {
              // Descarta que sea uno de los ya c�lculados
              if (n_e) {
                 sw1 = 0;
                 for(ii = 0; ii < n_e; ii++) {
                    sw = 0;
                    for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
                       if (fabsl(pos_equilibrio[ii][i] - At_Condicion[Sistema_actual][i]) > 1.0e-3) sw = 1;
                    }
                    if (!sw) {
                       sw1 = 1;
                       break;
                    }
                 }
                 if (sw1) continue;
              }
              // Guardo la ultima posici�n calculada
              for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_f[i] = At_Condicion[Sistema_actual][i];
              t_f = At_Tiempo[Sistema_actual];
              // Actualizo la candici�n inicial
              for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = c_f[i];
              t_i_rk = t_f;
              // C�lculo nuevamente
              if (!Integra_sin_visualizacion((Tiempo_minimo/10.0), paso)) {
                  // Reviso si estoy en un equilibrio
                  sw = 0;
                  for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
                     if (fabsl(c_f[i] - At_Condicion[Sistema_actual][i]) > 1.0e-5) sw = 1;
                  }
                  // Continuo con el c�lculo pues no estoy en un equilibrio
                  if (sw) continue;
                  // Guardo el ultimo valor calculado
                  for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_f[i] = At_Condicion[Sistema_actual][i];
                  t_f = At_Tiempo[Sistema_actual];
                  // Actualizo la condici�n inicial
                  for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) c_i_rk[i] = c_f[i];
                  t_i_rk = t_f;
                  // C�lculo para refinar el equilibrio
                  if (!Integra_sin_visualizacion(Tiempo_minimo, paso)) {
                     sw = 0;
                     for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
                        if (fabsl(c_f[i] - At_Condicion[Sistema_actual][i]) > 1.0e-10) sw = 1;
                     }
                     if (!sw) {
                        if (n_e == 0) {
                           for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) pos_equilibrio[n_e][i] = At_Condicion[Sistema_actual][i];
                           n_e ++;
                         } else {
                           sw1 = 0;
                           for(ii = 0; ii < n_e; ii++) {
                              sw = 0;
                              for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
                                 if (fabsl(pos_equilibrio[ii][i] - At_Condicion[Sistema_actual][i]) > 1.0e-10) sw = 1;
                              }
                              if (!sw) {
                                 sw1 = 1;
                                 break;
                              }
                           }
                           if (!sw1) {
                              for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) pos_equilibrio[n_e][i] = At_Condicion[Sistema_actual][i];
                              n_e ++;
                           }
                        }
                     }
                  }
              }
          }
       }
   }
}

