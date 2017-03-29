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


#include "BaseMetodosNumericos.hpp"
#include "../Libreria/Gen_rep.hpp"
#include <math.h>
#include <ctype.h>

#ifdef _IDIOMA_ESPANOL_
   #define BMN_TXT01 "TIEMPO"
#else
   #define BMN_TXT01 "TIME"

#endif

// Declaración de arreglo de colores a utilizar
TColor Colores[] = {
   clGray,
   clSilver,
   clMaroon,
   clGreen,
   clOlive,
   clNavy,
   clPurple,
   clTeal,
   clRed,
   clLime,
   clYellow,
   clBlue,
   clFuchsia,
   clAqua,
   clBlack,
   clWhite
};



// Inicializa la base de los métodos numéricos
void Base_Metodos_Numericos::Inicializa(void)
{
    // Inicializa las clases base
    Definicion_Usuario::Inicializa();
    Definicion_Usuario::Configuracion();
    Color_Integracion = clBlack;               // Gráfico de integración
    Color_Funcion_Auxiliar = clMaroon;         // Gráfico de la función auxiliar
    Color_Flecha_Campo_Vectorial = clRed;      // Cabeza de la flecha del campo vectorial
    Color_Cuerpo_Campo_Vectorial = clBlack;    // Cuerpo de la flecha del campo vectorial
    Color_Isoclina = clAqua;                   // Gráfico de la Isoclina
   
    Suspende_Calculo = false;
    Guarda_posicion = false;
    ERROR_MATEMATICO = 0;
    Sistema_actual = 0;
    for (int i = 0; i < Numero_sistemas; i++) {
       Ac_Tiempo[i] = 0.0;
       At_Tiempo[i] = 0.0;
       Grafica_puntos[i] = true;
       // Dimensiones de la ventana de trabajo
       Dimensiones[i].Xi = Config[i][0];
       Dimensiones[i].Yi = Config[i][1];
       Dimensiones[i].Zi = Config[i][2];
       Dimensiones[i].Xf = Config[i][3];
       Dimensiones[i].Yf = Config[i][4];
       Dimensiones[i].Zf = Config[i][5];

       // Establece el metodo numerico de integracion
       if (Metodo_N_actual[i] == 99) Metodo_N_actual[i] = 7;
       // Actualiza los valores para evitar overflow
       Actualiza_valores_evitar_overflow(i);
       // Asignacion de los parametros de los metodos numéricos
       // Euler
       Parametros_metodo[i][0][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][0][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][0][2] = 1.0e-3;   // Paso
       // Euler Modificado
       Parametros_metodo[i][1][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][1][1] = 100.0;
       Parametros_metodo[i][1][2] = 1.0e-3;
       // Punto Medio
       Parametros_metodo[i][2][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][2][1] = 100.0;
       Parametros_metodo[i][2][2] = 1.0e-3;
       // Heun
       Parametros_metodo[i][3][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][3][1] = 100.0;
       Parametros_metodo[i][3][2] = 1.0e-3;


       // Runge-Kutta I orden 3
       Parametros_metodo[i][4][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][4][1] = 100.0;
       Parametros_metodo[i][4][2] = 1.0e-3;
       // Runge-Kutta II orden 3
       Parametros_metodo[i][5][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][5][1] = 100.0;
       Parametros_metodo[i][5][2] = 1.0e-3;
       // Formula 3/8 orden 4
       Parametros_metodo[i][6][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][6][1] = 100.0;
       Parametros_metodo[i][6][2] = 1.0e-3;
       // Runge-Kutta Clasico orden 4
       Parametros_metodo[i][7][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][7][1] = 100.0;
       Parametros_metodo[i][7][2] = 1.0e-3;
       // Runge-Kutta-Gill orden 4
       Parametros_metodo[i][8][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][8][1] = 100.0;
       Parametros_metodo[i][8][2] = 1.0e-3;
       // England orden 4
       Parametros_metodo[i][9][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][9][1] = 100.0;
       Parametros_metodo[i][9][2] = 1.0e-3;
       // Runge-Kutta-Fehlberg orden 4
       Parametros_metodo[i][10][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][10][1] = 100.0;
       Parametros_metodo[i][10][2] = 1.0e-3;
       // Runge-Kutta-Fehlberg I orden 5
       Parametros_metodo[i][11][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][11][1] = 100.0;
       Parametros_metodo[i][11][2] = 1.0e-3;
       // England orden 5
       Parametros_metodo[i][12][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][12][1] = 100.0;
       Parametros_metodo[i][12][2] = 1.0e-3;
       // Kutta-Nyström orden 5
       Parametros_metodo[i][13][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][13][1] = 100.0;
       Parametros_metodo[i][13][2] = 1.0e-3;
       // Runge-Kutta-Fehlberg II orden 5
       Parametros_metodo[i][14][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][14][1] = 100.0;
       Parametros_metodo[i][14][2] = 1.0e-3;
       // Butcher orden 6
       Parametros_metodo[i][15][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][15][1] = 100.0;
       Parametros_metodo[i][15][2] = 1.0e-3;
       // Runge-Kutta-Fehlberg orden 6
       Parametros_metodo[i][16][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][16][1] = 100.0;
       Parametros_metodo[i][16][2] = 1.0e-3;


       // Método de un paso, paso variable Runge-Kutta de orden 3/2 
       Parametros_metodo[i][17][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][17][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][17][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][17][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][17][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 4/3 
       Parametros_metodo[i][18][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][18][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][18][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][18][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][18][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Prince-Dormand de orden 5/4/6 
       Parametros_metodo[i][19][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][19][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][19][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][19][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][19][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Prince-Dormand I de orden 5/4/7 
       Parametros_metodo[i][20][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][20][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][20][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][20][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][20][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Prince-Dormand II de orden 5/4/7 
       Parametros_metodo[i][21][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][21][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][21][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][21][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][21][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 5/4 
       Parametros_metodo[i][22][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][22][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][22][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][22][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][22][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable England de orden 5/4 
       Parametros_metodo[i][23][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][23][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][23][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][23][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][23][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Prince-Dormand de orden 6/5/8 
       Parametros_metodo[i][24][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][24][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][24][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][24][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][24][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 6/5 
       Parametros_metodo[i][25][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][25][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][25][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][25][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][25][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Verner I de orden 6/5 
       Parametros_metodo[i][26][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][26][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][26][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][26][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][26][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Verner II de orden 6/5 
       Parametros_metodo[i][27][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][27][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][27][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][27][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][27][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Verner de orden 7/6/10 
       Parametros_metodo[i][28][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][28][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][28][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][28][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][28][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Verner de orden 8/7/13 
       Parametros_metodo[i][29][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][29][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][29][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][29][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][29][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Fehlberg de orden 8/7/13 
       Parametros_metodo[i][30][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][30][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][30][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][30][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][30][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Prince-Dormand de orden 8/7/13 
       Parametros_metodo[i][31][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][31][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][31][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][31][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][31][4] = 1.0e-3;   // Paso mínimo
       // Método de un paso, paso variable Runge-Kutta-Verner de orden 9/8/16 
       Parametros_metodo[i][32][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][32][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][32][2] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][32][3] = 1.0;      // Paso máximo
       Parametros_metodo[i][32][4] = 1.0e-3;   // Paso mínimo
       

       // Adams-Bashforth-2Pasos
       Parametros_metodo[i][33][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][33][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][33][2] = 1.0e-3;   // Paso
       // Adams-Bashforth-3Pasos
       Parametros_metodo[i][34][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][34][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][34][2] = 1.0e-3;   // Paso
       // Milne-3Pasos
       Parametros_metodo[i][35][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][35][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][35][2] = 1.0e-3;   // Paso
       // Adams-Bashforth-4Pasos
       Parametros_metodo[i][36][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][36][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][36][2] = 1.0e-3;   // Paso
       // Adams-Bashforth-5Pasos
       Parametros_metodo[i][37][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][37][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][37][2] = 1.0e-3;   // Paso
       // Adams-Bashforth-6Pasos
       Parametros_metodo[i][38][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][38][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][38][2] = 1.0e-3;   // Paso
       // Adams-Bashforth-7Pasos
       Parametros_metodo[i][39][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][39][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][39][2] = 1.0e-3;   // Paso

       
       // Predictor-Corrector Adams-Bashforth-Moulton de 3 orden
       Parametros_metodo[i][40][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][40][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][40][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Milne-Simpson de 3 orden
       Parametros_metodo[i][41][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][41][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][41][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Adams-Bashforth-Moulton de 4 orden
       Parametros_metodo[i][42][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][42][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][42][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Adams-Bashforth-Moulton I de 5 orden
       Parametros_metodo[i][43][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][43][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][43][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Adams-Bashforth-Moulton II de 5 orden
       Parametros_metodo[i][44][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][44][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][44][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Adams-Bashforth-Moulton de 6 orden
       Parametros_metodo[i][45][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][45][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][45][2] = 1.0e-3;   // Paso
       // Predictor-Corrector Adams-Bashforth-Moulton de 7 orden
       Parametros_metodo[i][46][0] = 2.0;      // Numero de Parámetros
       Parametros_metodo[i][46][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][46][2] = 1.0e-3;   // Paso

       
       // Predictor-Corrector Adams-Bashforth-Moulton de 3 orden Paso Variable
       Parametros_metodo[i][47][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][47][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][47][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][47][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][47][4] = 1.0e-3;   // Paso mínimo
       // Predictor-Corrector Adams-Bashforth-Moulton de 4 orden Paso Variable
       Parametros_metodo[i][48][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][48][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][48][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][48][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][48][4] = 1.0e-3;   // Paso mínimo
       // Predictor-Corrector Adams-Bashforth-Moulton I de 5 orden Paso Variable
       Parametros_metodo[i][49][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][49][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][49][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][49][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][49][4] = 1.0e-3;   // Paso mínimo
       // Predictor-Corrector Adams-Bashforth-Moulton II de 5 orden Paso Variable
       Parametros_metodo[i][50][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][50][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][50][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][50][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][50][4] = 1.0e-3;   // Paso mínimo
       // Predictor-Corrector Adams-Bashforth-Moulton de 6 orden Paso Variable
       Parametros_metodo[i][51][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][51][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][51][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][51][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][51][4] = 1.0e-3;   // Paso mínimo
       // Predictor-Corrector Adams-Bashforth-Moulton de 7 orden Paso Variable
       Parametros_metodo[i][52][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][52][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][52][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][52][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][52][4] = 1.0e-3;   // Paso mínimo


       // Extrapolación
       Parametros_metodo[i][53][0] = 4.0;      // Numero de Parámetros
       Parametros_metodo[i][53][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][53][2] = 1.0e-15;  // Tolerancia
       Parametros_metodo[i][53][3] = 1.0e-1;   // Paso máximo
       Parametros_metodo[i][53][4] = 1.0e-3;   // Paso mínimo
       
       // Trapecio con iteraciones por Secante
       Parametros_metodo[i][54][0] = 5.0;      // Numero de Parámetros
       Parametros_metodo[i][54][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][54][2] = 1.0e-3;   // Paso 
       Parametros_metodo[i][54][3] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][54][4] = 1000.0;   // Numero de iteraciones
       Parametros_metodo[i][54][5] = 1.0e-10;  // Paso para el cálculo de la derivada
       // Euler regresivo con iteraciones por Secante
       Parametros_metodo[i][55][0] = 5.0;      // Numero de Parámetros
       Parametros_metodo[i][55][1] = 100.0;    // Tiempo de integración
       Parametros_metodo[i][55][2] = 1.0e-3;   // Paso 
       Parametros_metodo[i][55][3] = 1.0e-10;  // Tolerancia
       Parametros_metodo[i][55][4] = 1000.0;   // Numero de iteraciones
       Parametros_metodo[i][55][5] = 1.0e-10;  // Paso para el cálculo de la derivada

       
       // Configura el campo vectorial
       Parametros_campo_vectorial[i][0] = 30.0; // Numero de vectores X
       Parametros_campo_vectorial[i][1] = 30.0; // Numero de vectores Y
       Factor_direccional[i] = 1.0;
       Factor_vectorial[i] = 0.1;
       Muestra_cabeza_vector[i] = true;  // Muestra cabeza vector
       AjustaConfiguracionCampoVectorial(i); 

       // fija la condición inicial del sistema
       for (int xi = 0; xi <  Numero_ecuaciones[i]; xi++) {
          Ac_Condicion[i][xi] = 0.0;
          At_Condicion[i][xi] = 1.0;
       }

       // Define el paso del cursor
       Paso_cursor[i].x = ((Dimensiones[i].Xf - Dimensiones[i].Xi) / 200.0);
       Paso_cursor[i].y = ((Dimensiones[i].Yf - Dimensiones[i].Yi) / 200.0);
       Paso_cursor[i].z = ((Dimensiones[i].Zf - Dimensiones[i].Zi) / 200.0);
       // Define el incremento del paso del cursor
       Incremento_paso_cursor[i].x = Paso_cursor[i].x;
       Incremento_paso_cursor[i].y = Paso_cursor[i].y;
       Incremento_paso_cursor[i].z = Paso_cursor[i].z;

       // Indica si esta activa la visualizacion simultanea
       Visualizacion_simultanea[i] = false;
       Numero_escenarios_visualizar[i] = 0;
       // Indica los escenarios activos en la visualizacion simultanea
       for (int xi = 0; xi <  Numero_ecuaciones[i]; xi++) {
          Escenarios_visualizar[i][xi] = 0;
       }
    }
}




// Hace las conversiones necesarias para dibujar un punto
void Base_Metodos_Numericos::Dibuja_punto(const long double ini[NUMERO_ECUACIONES], const long double t, const TColor color)
{
   aux[0] = 0;
   for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) aux[ind+1] = ini[ind];
   aux[ind+1] = t;
   if (Visualizacion_simultanea[Sistema_actual]) {
      aux1.z = 0.0;
      aux1.x = t;
      for (int xx = 0; xx < Numero_escenarios_visualizar[Sistema_actual]; xx++) {
         aux1.y = aux[Escenarios_visualizar[Sistema_actual][xx]];
         Control_Visualizacion::Dibuja_punto(aux1,Colores[xx%16]); 
      }
    } else {
      aux1.x = aux[Escenario[Sistema_actual].x];
      aux1.y = aux[Escenario[Sistema_actual].y];
      aux1.z = aux[Escenario[Sistema_actual].z];
      Control_Visualizacion::Dibuja_punto(aux1,color);
   }
}
      
// Hace las conversiones necesarias para dibujar una linea
void Base_Metodos_Numericos::Dibuja_linea(const long double ini[NUMERO_ECUACIONES], const long double fin[NUMERO_ECUACIONES], const long double t_ini, const long double t_fin, const TColor color)
{
   if (Visualizacion_simultanea[Sistema_actual]) {
      aux1.z = 0.0;
      for (int xx = 0; xx < Numero_escenarios_visualizar[Sistema_actual]; xx++) {
         aux[0] = 0;
         for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) aux[ind+1] = ini[ind];
         aux[ind+1] = t_ini;

         aux1.x = t_ini;
         aux1.y = aux[Escenarios_visualizar[Sistema_actual][xx]];
        
         aux[0] = 0;
         for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) aux[ind+1] = fin[ind];
         aux[ind+1] = t_fin;

         aux2.x = t_fin;
         aux2.y = aux[Escenarios_visualizar[Sistema_actual][xx]];
         Control_Visualizacion::Dibuja_linea(aux1, aux2,Colores[xx%16]);
      }
    } else {
      aux[0] = 0;
      for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) aux[ind+1] = ini[ind];
      aux[ind+1] = t_ini;

      aux1.x = aux[Escenario[Sistema_actual].x];
      aux1.y = aux[Escenario[Sistema_actual].y];
      aux1.z = aux[Escenario[Sistema_actual].z];

      aux[0] = 0;
      for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) aux[ind+1] = fin[ind];
      aux[ind+1] = t_fin;

      aux2.x = aux[Escenario[Sistema_actual].x];
      aux2.y = aux[Escenario[Sistema_actual].y];
      aux2.z = aux[Escenario[Sistema_actual].z];
      Control_Visualizacion::Dibuja_linea(aux1, aux2,color);
   }
}

// Retorna las coordenadas iniciales
void Base_Metodos_Numericos::Condiciones_iniciales_texto(char *cad)
{
   long double aux[NUMERO_ECUACIONES+2];
   char xcad1[40], xcad2[40], xcad3[40], xcad[400];
   C_3D aux1;
   int i;
   aux[0] = 0.0;
   for(i = 0; i < Numero_ecuaciones[Sistema_actual]; i++) aux[i+1] = Ac_Condicion[Sistema_actual][i];
   aux[i+1] = Ac_Tiempo[Sistema_actual];
   aux1.x = aux[Escenario[Sistema_actual].x];
   aux1.y = aux[Escenario[Sistema_actual].y];
   aux1.z = aux[Escenario[Sistema_actual].z];
   // Cambia dependiendo del escenario ver que se visualizara
   Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].x,xcad1);
   Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].y,xcad2);
   Retorna_variable_ecuacion_sistema_activo(Escenario[Sistema_actual].z,xcad3);
   if(Escenario[Sistema_actual].z) sprintf(xcad,"%s = %3.5Lf  Step = %3.5Lf  %s = %3.5Lf  Step = %3.5Lf  %s = %3.5Lf  Step = %3.5Lf",xcad1,aux1.x,Paso_cursor[Sistema_actual].x,xcad2,aux1.y,Paso_cursor[Sistema_actual].x,xcad3,aux1.z,Paso_cursor[Sistema_actual].z);
    else {
      if (Tipo_ventana == EJES_COORDENADAS_POLARES) {
         // Hace las conversiones necesarias en el caso de coordenadas polares
         aux1.x = sqrtl((Ac_Condicion[Sistema_actual][0] * Ac_Condicion[Sistema_actual][0])+(Ac_Condicion[Sistema_actual][1] * Ac_Condicion[Sistema_actual][1]));
         if (Ac_Condicion[Sistema_actual][0] != 0) aux1.y = atanl(fabsl(Ac_Condicion[Sistema_actual][1]) / fabsl(Ac_Condicion[Sistema_actual][0]));
          else aux1.y = 0.0;
         if (Ac_Condicion[Sistema_actual][0] < 0 && Ac_Condicion[Sistema_actual][1] > 0) aux1.y = (M_PI_2 - aux1.y) + M_PI_2;
         if (Ac_Condicion[Sistema_actual][0] < 0 && Ac_Condicion[Sistema_actual][1] < 0) aux1.y = -((M_PI_2 - aux1.y) + M_PI_2);
         if (Ac_Condicion[Sistema_actual][0] > 0 && Ac_Condicion[Sistema_actual][1] < 0) aux1.y = - aux1.y;
      }   
      sprintf(xcad,"%s = %3.5Lf  Step = %3.5Lf  %s = %3.5Lf  Step = %3.5Lf",xcad1,aux1.x,Paso_cursor[Sistema_actual].x,xcad2,aux1.y,Paso_cursor[Sistema_actual].y);
   }
   strcpy(cad,xcad);
}

// Establece las condiciones iniciales en el origen de los ejes coordenados
void Base_Metodos_Numericos::Condiciones_iniciales_al_origen(void)
{
   for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) Ac_Condicion[Sistema_actual][ind] = 0.0;
   Ac_Tiempo[Sistema_actual] = 0.0;
   Actualiza_condicion_inicial();
   Guarda_posicion = false;
}

// Establece las condiciones iniciales al centro de la ventana
void Base_Metodos_Numericos::Condiciones_iniciales_al_centro_ventana(void)
{
   Dimension_Ventana  dim;
   Retorna_dimensiones_sistema(dim);
///////////////////////////////////////////////////////////////////////////////////   
//#error Hay que tomar en cuenta la condición inicial segun el escenario activo
   for(ind = 0; ind < Numero_ecuaciones[Sistema_actual]; ind++) Ac_Condicion[Sistema_actual][ind] = 0.0;
   Ac_Condicion[Sistema_actual][0] = (dim.Xf - dim.Xi) / 2.0 + dim.Xi;
   Ac_Condicion[Sistema_actual][1] = (dim.Yf - dim.Yi) / 2.0 + dim.Yi;
   Ac_Condicion[Sistema_actual][2] = (dim.Zf - dim.Zi) / 2.0 + dim.Zi;
   Ac_Tiempo[Sistema_actual] = 0.0;
///////////////////////////////////////////////////////////////////////////////////   
   Actualiza_condicion_inicial();
   Guarda_posicion = false;
}


// Nombre de la ecuacion numero N_E en el sistema SIS
void Base_Metodos_Numericos::Retorna_variable_ecuacion_sistema_activo(const int i, char *cad)
{
   int xi = 0;
   if (i > 0 && i <= Numero_ecuaciones[Sistema_actual]) {
      while (Nombre_ecuacion[Sistema_actual][i - 1][xi] != '\'') {
         cad[xi] = (char) toupper(Nombre_ecuacion[Sistema_actual][i - 1][xi]);
         xi++;
      }
      cad[xi] = 0;
   } else strcpy(cad,BMN_TXT01);
}

// Nombre de la ecuacion numero N_E en el sistema SIS
void Base_Metodos_Numericos::Retorna_variable_ecuacion_sistema(const int sis, const int i, char *cad)
{
   int xi = 0;
   if (i > 0 && i <= Numero_ecuaciones[sis]) {
      while (Nombre_ecuacion[sis][i - 1][xi] != '\'') {
         cad[xi] = (char) toupper(Nombre_ecuacion[sis][i - 1][xi]);
         xi++;
      }
      cad[xi] = 0;
   } else strcpy(cad,BMN_TXT01);
}

// Actualiza las cotas que se usarán en el cálculo númerico
void Base_Metodos_Numericos::Actualiza_valores_evitar_overflow(const int i)
{
   long double x1,x2,x3, xt1, xt2;
   // Encuantra la cota para evitar desbordamientos numéricos
   x1 = fabsl(Dimensiones[i].Xf - Dimensiones[i].Xi);
   x2 = fabsl(Dimensiones[i].Yf - Dimensiones[i].Yi);
   x3 = fabsl(Dimensiones[i].Zf - Dimensiones[i].Zi);
   xt1 = x2 > x3 ? x2 : x3;
   xt2 = x1 > xt1 ? x1 : xt1;
   MAX_VALOR[i] = xt2 * 2.0;
}              


void Base_Metodos_Numericos::Actualiza_condicion_inicial(void)
{
   C_3D cda;
   if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].x) cda.x = Ac_Tiempo[Sistema_actual];
    else cda.x = Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].x -1];
   if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].y) cda.x = Ac_Tiempo[Sistema_actual];
    else cda.y = Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].y -1];
   if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].z) cda.x = Ac_Tiempo[Sistema_actual];
    else cda.z = Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].z -1];
   Establece_coordenadas(cda);
   Poner_cursor();
}              


void Base_Metodos_Numericos::Establece_condiciones_iniciales(const int i, const long double aux)
{
   if (i < Numero_ecuaciones[Sistema_actual]) Ac_Condicion[Sistema_actual][i] = aux;
    else Ac_Tiempo[Sistema_actual] = aux;
   Actualiza_condicion_inicial();
   Guarda_posicion = false;
}


void Base_Metodos_Numericos::Incrementa_condicion_inicial(const bool x, const bool y, const bool z)
{
   if (x) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].x) Ac_Tiempo[Sistema_actual] += Paso_cursor[Sistema_actual].x;
       else Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].x -1] += Paso_cursor[Sistema_actual].x;
   }   
   if (y) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].y) Ac_Tiempo[Sistema_actual] += Paso_cursor[Sistema_actual].y;
       else Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].y -1] += Paso_cursor[Sistema_actual].y;
   }   
   if (z) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].z) Ac_Tiempo[Sistema_actual] += Paso_cursor[Sistema_actual].z;
       else 
       if (Escenario[Sistema_actual].z > 0) Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].z -1] += Paso_cursor[Sistema_actual].z;
   }   
   Actualiza_condicion_inicial();
   Guarda_posicion = false;
}              


void Base_Metodos_Numericos::Decrementa_condicion_inicial(const bool x, const bool y, const bool z)
{
   if (x) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].x) Ac_Tiempo[Sistema_actual] -= Paso_cursor[Sistema_actual].x;
       else Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].x -1] -= Paso_cursor[Sistema_actual].x;
//      if (Tipo_ventana == EJES_COORDENADAS_POLARES && Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].x -1] < 0.0) Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].x -1] = 0.0;
   }   
   if (y) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].y) Ac_Tiempo[Sistema_actual] -= Paso_cursor[Sistema_actual].y;
       else Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].y -1] -= Paso_cursor[Sistema_actual].y;
   }   
   if (z) {
      if ((Numero_ecuaciones[Sistema_actual] + 1) == Escenario[Sistema_actual].z) Ac_Tiempo[Sistema_actual] -= Paso_cursor[Sistema_actual].z;
       else 
       if (Escenario[Sistema_actual].z > 0) Ac_Condicion[Sistema_actual][Escenario[Sistema_actual].z -1] -= Paso_cursor[Sistema_actual].z;
   }   
   Actualiza_condicion_inicial();
   Guarda_posicion = false;
}              

