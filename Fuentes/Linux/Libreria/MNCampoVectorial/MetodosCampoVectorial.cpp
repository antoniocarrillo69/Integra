//////////////////////////////////////////////////////////////////////////////////////////////
// Métodos de visualización del campo vectorial                                             //
// Revisión: 26 de Octubre del 2001                                                         //
//                                                                                          //
// Copyright (C) 2001                                                                       //
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
// Revisión y correcciones:                                                                 //
//                                                                                          //
// Autor:    Dr. Guillermo Sienra Loera                                                     //
// E-mail:   gsl@hp.fciencias.unam.mx                                                       //
// Página:   http://www.dynamics.unam.edu/gsl                                               //
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


#include "MetodosCampoVectorial.hpp"
#include <math.h>

////////////////////////////////////////////////////////////////////////
// Dibuja el campo vectorial o de direcciones                         //
////////////////////////////////////////////////////////////////////////
// (0) Calculo correctamente
// (1) No calcula campo vectorial si se tiene como un escenario al tiempo
int Metodos_Numericos_Campo_Vectorial::Dibuja_campo(void)
{
   // Se descarta hacer campo vectorial cuando un escenario es el TIEMPO
   if(Escenario[Sistema_actual].x == (Numero_ecuaciones[Sistema_actual] + 1)) return 1; // (1) No calcula campo vectorial si se tiene como un escenario al tiempo

   int i;
   long double Norma, aux[2], aux2[2], t1, t2, cpx,cpy;
   long double Dif_max, ajus_homo; 
   long double ini[NUMERO_ECUACIONES], fin[NUMERO_ECUACIONES], aux1[NUMERO_ECUACIONES+2];
   long double AjusteNorma, AjusteNormaX, AjusteNormaY;
   bool sw;

   // Inicializa valores
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) ini[i] = fin[i] =  aux1[i] = X[i] = 0;

   // Proyeccion XY
   aux[0] = (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) / Parametros_campo_vectorial[Sistema_actual][0];
   aux[1] = (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) / Parametros_campo_vectorial[Sistema_actual][1];


   // Cálculo del ajuste a la norma
   Dif_max = (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) > (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) ? (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) : (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi);
   AjusteNormaX = (Dimensiones[Sistema_actual].Yf - Dimensiones[Sistema_actual].Yi) / Dif_max;
   AjusteNormaY = (Dimensiones[Sistema_actual].Xf - Dimensiones[Sistema_actual].Xi) / Dif_max;
   if (AjusteNormaX < AjusteNormaY) AjusteNorma = AjusteNormaX;
    else AjusteNorma = AjusteNormaY;

   // Ajusta para sistema de ejes no homogeneos
   if (AjusteNorma < 1.0) ajus_homo = 0.12;
    else ajus_homo = 0.7;
    
   for(aux2[0] = Dimensiones[Sistema_actual].Xi; aux2[0] < Dimensiones[Sistema_actual].Xf; aux2[0] += aux[0]) {
      for(aux2[1] = Dimensiones[Sistema_actual].Yi; aux2[1] < Dimensiones[Sistema_actual].Yf; aux2[1] += aux[1]) {

         // Ajusta a cero variables de resultados
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) fin[i] = 0;
         t = 0;


         if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
            Convierte_rectangulares_polares(aux2[0], aux2[1],cpx,cpy);
            X[Escenario[Sistema_actual].x - 1] = ini[Escenario[Sistema_actual].x - 1] = cpx;
            X[Escenario[Sistema_actual].y - 1] = ini[Escenario[Sistema_actual].y - 1] = cpy;
          } else {
            // Inicializa valores
            X[Escenario[Sistema_actual].x - 1] = ini[Escenario[Sistema_actual].x - 1] = aux2[0];
            X[Escenario[Sistema_actual].y - 1] = ini[Escenario[Sistema_actual].y - 1] = aux2[1];
         }

         
         // Calcula el vector
         for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
            // Calculo con la ecuacion diferencial
            try {
               aux1[i] = (this->*funcion[Sistema_actual][i])();
            } catch (...) {   
               ERROR_MATEMATICO = 1;
            };
            // Controla el error en las funciones matematicas
            if(ERROR_MATEMATICO) break;
         }

         // Control del error matemático
         if(ERROR_MATEMATICO) {
            ERROR_MATEMATICO = 0;
            continue;
         }

         // Cálculo de Norma
         Norma = AjusteNorma * (sqrt((pow(aux1[Escenario[Sistema_actual].x - 1],2)) + ((pow(aux1[Escenario[Sistema_actual].y - 1],2))))); 
         if(fabsl(Norma) < 1e-3) {
            Dibuja_punto(ini,0.0,Color_Cuerpo_Campo_Vectorial);
            continue;
         }
         // Revisa si debe de homogenizar o no
         if (Homogenizacion) {
            fin[Escenario[Sistema_actual].x - 1] = ini[Escenario[Sistema_actual].x - 1] + ((Parametros_campo_vectorial[Sistema_actual][2] * aux1[Escenario[Sistema_actual].x - 1]) / Norma) * Factor_direccional[Sistema_actual] * ajus_homo;
            fin[Escenario[Sistema_actual].y - 1] = ini[Escenario[Sistema_actual].y - 1] + ((Parametros_campo_vectorial[Sistema_actual][3] * aux1[Escenario[Sistema_actual].y - 1]) / Norma) * Factor_direccional[Sistema_actual] * ajus_homo;
          } else {
            fin[Escenario[Sistema_actual].x - 1] = ini[Escenario[Sistema_actual].x - 1] + (Parametros_campo_vectorial[Sistema_actual][2] * aux1[Escenario[Sistema_actual].x - 1]) * Factor_vectorial[Sistema_actual];
            fin[Escenario[Sistema_actual].y - 1] = ini[Escenario[Sistema_actual].y - 1] + (Parametros_campo_vectorial[Sistema_actual][3] * aux1[Escenario[Sistema_actual].y - 1]) * Factor_vectorial[Sistema_actual];
         }
         fin[Escenario[Sistema_actual].z - 1] = ini[Escenario[Sistema_actual].z - 1] = 0.0;
         t1 = t2 = 0;

         // Evita a los puntos singulares
         sw = false;
//         for (i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) {
         if(fabsl(ini[Escenario[Sistema_actual].x - 1] - fin[Escenario[Sistema_actual].x - 1]) > 1e-3 && fabsl(ini[Escenario[Sistema_actual].y - 1] - fin[Escenario[Sistema_actual].y - 1]) > 1e-3) sw = true;
//         }
         
         // Dibuja el campo para el punto dado
         if (sw) {
            Dibuja_linea(ini,fin,t1,t2,Color_Cuerpo_Campo_Vectorial);
            if (Muestra_cabeza_vector[Sistema_actual]) Cabeza_flecha(ini,fin);
          } else {
            Dibuja_punto(ini,0.0,Color_Cuerpo_Campo_Vectorial);
         } 
      }
   }
   // Visualiza los errores en el calculo numerico
   return 0; // (0) Calculo correctamente
}


                               
////////////////////////////////////////////////////////////////////////
//               Cabeza de flecha del campo vectorial                 //
////////////////////////////////////////////////////////////////////////

void Metodos_Numericos_Campo_Vectorial::Cabeza_flecha(const long double ini[], const long double fin[])
{
   long double l, ang, a, ca, sa, m, xi, yi, xf, yf;
   long double a1[NUMERO_ECUACIONES];

   
   xi = ini[Escenario[Sistema_actual].x - 1], yi = ini[Escenario[Sistema_actual].y - 1];
   xf = fin[Escenario[Sistema_actual].x - 1], yf = fin[Escenario[Sistema_actual].y - 1];
   
   // Calcula el tamaño del vector
   l = sqrt(pow(xi - xf,2) + pow(yi - yf,2)) / 4.0;

   // Calcula el angulo
   if(xf - xi) {
      // Calcula la pendiente
      m = (yf - yi) / (xf - xi); 
      ang = xf < xi ? atan(m) + M_PI : atan(m);
   } else ang = yi < yf ? M_PI_2 : - M_PI_2;

   a = sin(M_PI / 5.0) * l;
   ca = cos(ang);
   sa = sin(ang);

   
   a1[Escenario[Sistema_actual].x - 1] = xf - l * ca - a * sa;
   a1[Escenario[Sistema_actual].y - 1] = yf - l * sa + a * ca;
   if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
///////////////////////////////////////////////////////////////////////////////////////////   
//#error se ajusta por dibujo erroneo en cabeza de flecha
      a1[Escenario[Sistema_actual].x - 1] = xf - l * ca;
      a1[Escenario[Sistema_actual].y - 1] = yf - l * sa;
///////////////////////////////////////////////////////////////////////////////////////////   
   }
   a1[Escenario[Sistema_actual].z - 1] = 0.0;
   Dibuja_linea(a1,fin,0.0,0.0,Color_Flecha_Campo_Vectorial);

    
   a1[Escenario[Sistema_actual].x - 1] = xf - l * ca + a * sa;
   a1[Escenario[Sistema_actual].y - 1] = yf - l * sa - a * ca;
   if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
///////////////////////////////////////////////////////////////////////////////////////////   
//#error se ajusta por dibujo erroneo en cabeza de flecha
      a1[Escenario[Sistema_actual].x - 1] = xf - l * ca;
      a1[Escenario[Sistema_actual].y - 1] = yf - l * sa;
///////////////////////////////////////////////////////////////////////////////////////////   
   }
   a1[Escenario[Sistema_actual].z - 1] = 0.0;
   Dibuja_linea(a1,fin,0.0,0.0,Color_Flecha_Campo_Vectorial);
}



