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


#ifndef __Ctrl_Funciones_Auxliares__
#define __Ctrl_Funciones_Auxliares__


#define VENTANA_2D                    0
#define EJES_COORDENADOS_2D           1
#define EJES_COORDENADOS_2DM          2
#define EJES_COORDENADOS_3D           3
#define EJES_CAJA_2D                  4
#define EJES_CAJA_3D                  5
#define EJES_COORDENADAS_POLARES      6
#define EJES_CAJA_3DM                 7



////////////////////////////////////////////////////////////////////////
//                 Control de funciones auxiliares                    //
////////////////////////////////////////////////////////////////////////
 
 class Ctrl_Funciones_Auxiliares
 {
    protected: 

       long double         aux1, aux2, aux3, aux4;


    public:
                           // Inverso de X
       long double         invl(const long double x);
                           // Signo de X
                           // (1)  Positivo
                           // (-1) Negativo
                           // (0)  Cero 
       long double         sigl(const long double x);

                           // Controla el error matematico
       int                 ERROR_MATEMATICO;
                           // Tiempo
       long double         t;

 };


#endif
