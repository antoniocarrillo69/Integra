//////////////////////////////////////////////////////////////////////////////////////////////
// Controlador de Métodos Numéricos                                                         //
// Revisión: 16 de Abril del 2002                                                           //
//                                                                                          //
// Copyright (C) 2001-2002                                                                  //
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




// Clase controladora de los diversos métodos numéricos
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
