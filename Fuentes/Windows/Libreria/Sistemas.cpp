//////////////////////////////////////////////////////////////////////////////////////////////
// Definición de sistemas                                                                   //
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


#include "Sistemas.hpp"

 // Fija en numero de escenarios a visualizar simultaneamente
void Sistemas::Fija_numero_escenarios_visualizar(const int num)
{
   if (num < 1) {
      Visualizacion_simultanea[Sistema_actual] = false;
      Numero_escenarios_visualizar[Sistema_actual] = 0;
      return;
   }   
   Visualizacion_simultanea[Sistema_actual] = true;
   Numero_escenarios_visualizar[Sistema_actual] = num;
   for (int i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) Escenarios_visualizar[Sistema_actual][i] = 0;
}


// Fija los escenarios a visualizar simultaneamente
void Sistemas::Fija_escenarios_visualizar(const int num[])
{
   int xxi, i, sw = 0, xi = 0;
   for (i = 0; i < Numero_escenarios_visualizar[Sistema_actual]; i++) {
      if (num[i] > 0 && num[i] <= Numero_ecuaciones[Sistema_actual]) {
         for (xxi = 0; xxi < xi; xxi++) {
            if (Escenarios_visualizar[Sistema_actual][xxi] == num[i]) {
               sw =1;
               break;
            }
         }
         if (!sw) {
            Escenarios_visualizar[Sistema_actual][xi] = num[i];
            xi++;
         }
      }
   }
   Numero_escenarios_visualizar[Sistema_actual] = xi;
}
  
