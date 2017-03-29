//////////////////////////////////////////////////////////////////////////////////////////////
// Controlador de M�todos Num�ricos                                                         //
// Revisi�n: 16 de Abril del 2002                                                           //
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


#ifndef __MetodosNumericos__
#define __MetodosNumericos__


#include "BaseMetodosNumericos.hpp"
#include "MetodosBifurcaciones.hpp"
#include "MetodosIntegracion.hpp"
#include "MetodosIsoclinas.hpp"
#include "MetodosCampoVectorial.hpp"
#include "MetodosFuncionesAuxiliares.hpp"
#include "MetodosCalculoEquilibrios.hpp"


#define INTEGRA_POSITIVAMENTE     1
#define INTEGRA_NEGATIVAMENTE     0




// Clase controladora de los diversos m�todos num�ricos
class Metodos_Numericos: virtual public Metodos_Numericos_Integracion, virtual public Metodos_Numericos_Bifurcacion, virtual public Metodos_Numericos_Isoclinas, virtual public Metodos_Numericos_Campo_Vectorial, virtual public Metodos_Numericos_FuncionesAuxiliares, virtual public Metodos_Numericos_Calculo_Equilibrios
{
   private:

                    // Revisa el tipo de ejes coordenados que necesita el sistema
      void          Revisa_escenario_del_sistema(void)
                    {
                       if (Numero_ecuaciones[Sistema_actual] == 2) Tipo_ventana = EJES_COORDENADOS_2D;
                        else Tipo_ventana = EJES_COORDENADOS_3D;
                    }
   
   public:

                    // Inicializa la clase
      virtual  void Inicializa(void)
                    {
                       // Inicializa las clases bases
                       Base_Metodos_Numericos::Inicializa();
                       Metodos_Numericos_Integracion::Inicializa();
                       Metodos_Numericos_Bifurcacion::Inicializa();
                       Metodos_Numericos_Isoclinas::Inicializa();
                       Metodos_Numericos_Campo_Vectorial::Inicializa();
                       Metodos_Numericos_FuncionesAuxiliares::Inicializa();
                       Metodos_Numericos_Calculo_Equilibrios::Inicializa();
                       Control_Visualizacion::Inicializa();
                       Establece_Dimensiones(Dimensiones[Sistema_actual]);
                       // Revisa el tipo de ejes coordenados que necesita el sistema
                       Revisa_escenario_del_sistema();
                    }
      
                    // Destruye la clase
      virtual  void Destruye(void)
                    {
                       Control_Visualizacion::Destruye();
                    }

};




#endif
