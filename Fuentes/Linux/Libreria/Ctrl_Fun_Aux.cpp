 //////////////////////////////////////////////////////////////////////////////////////////////
 // Definición de sistemas                                                                   //
 // Revisión: 29 de Diciembre del 2001                                                       //
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

