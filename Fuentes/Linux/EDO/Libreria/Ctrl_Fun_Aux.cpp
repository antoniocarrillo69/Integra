 //////////////////////////////////////////////////////////////////////////////////////////////
 // Definici�n de sistemas                                                                   //
 // Revisi�n: 29 de Diciembre del 2001                                                       //
 //                                                                                          //
 // Copyright (C) 2001                                                                       //
 //                                                                                          //
 // An�lisis y Dise�o:                                                                       //
 //                                                                                          //
 // Autor     Dr. Humberto Carrillo Calvet                                                   //
 // E-mail:   carr@servidor.unam.mx                                                          //
 // P�gina:   http://www.dynamics.unam.edu/hcc                                               //
 //                                                                                          //
 // Autor:    Luis Alonso Nava Fernandez                                                     //
 // E-mail:   nava@athena.fciencias.unam.mx                                                  //
 // P�gina:   http://www.dynamics.unam.edu/lanf                                              //
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


#include "Ctrl_Fun_Aux.hpp"

 
// Calcula el inverso de X
long double Ctrl_Funciones_Auxiliares::invl(const long double x)
{
   if (x != 0.0) return (1.0 / x);
   ERROR_MATEMATICO = 1;
   return 0.0;
}

// Calcula el signo de X
long double Ctrl_Funciones_Auxiliares::sigl(const long double x)
{
   if (x > 0.0) return 1.0;
   if (x < 0.0) return -1.0;
   return 0.0;
}

