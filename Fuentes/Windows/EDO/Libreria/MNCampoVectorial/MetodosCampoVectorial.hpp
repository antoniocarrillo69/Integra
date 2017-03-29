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



#ifndef __MetodosCampoVectorial__
#define __MetodosCampoVectorial__


#include "BaseMetodosNumericos.hpp"

class Metodos_Numericos_Campo_Vectorial: virtual public Base_Metodos_Numericos
{
   private:

      int            ind_no_avil;
      bool           Homogenizacion;

                     // Dibuja la cabeza de la flecha del campo vectorial
      void           Cabeza_flecha(const long double ini[], const long double fin[]);

                     // Dibuja el campo vectorial o direccional
      int            Dibuja_campo(void);

   protected:

                     // Dibuja el campo vectorial
      int            Dibuja_campo_vectorial(void)
                     {
                        Homogenizacion = false;
                        return (Dibuja_campo());
                     }
                     // Dibuja el campo direccional
      int            Dibuja_campo_direccional(void)
                     {
                        Homogenizacion = true;
                        return (Dibuja_campo());
                     }


      
   public:
                     // Inicializa la clase
      virtual void   Inicializa(void)
                     {
                        ind_no_avil = 0;
                        Homogenizacion = true;
                     }

                     // Retorna el factor de ajuste al campo homogeneo
      long double    Retorna_factor_ajuste_homogeneo(void)
                     {
                        return (Factor_direccional[Sistema_actual]);
                     }
                     // Retorna el factor de ajuste al campo no homogeneo
      long double    Retorna_factor_ajuste_no_homogeneo(void)
                     {
                        return (Factor_vectorial[Sistema_actual]);
                     }
                     
      bool           Retorna_muestra_cabeza_vector(void)
                     {
                        return (Muestra_cabeza_vector[Sistema_actual]);
                     }

      void           Fija_muestra_cabeza_vector(const bool st)
                     {
                        Muestra_cabeza_vector[Sistema_actual] = st;
                     }

                     // Retorna la configuración del campo vectorial
      void           Retorna_configuracion_campo_vectorial(long double &numx, long double &numy, long double &tamx, long double &tamy)
                     {
                        numx = Parametros_campo_vectorial[Sistema_actual][0];
                        numy = Parametros_campo_vectorial[Sistema_actual][1];
                        tamx = Parametros_campo_vectorial[Sistema_actual][2];
                        tamy = Parametros_campo_vectorial[Sistema_actual][3];
                     }

                     // Establece la configuración del campo vectorial
      void           Establece_configuracion_campo_vectorial(const long double numx, const long double numy, const long double tamx, const long double tamy, const long double factnohom, const long double facthom)
                     {
                        Parametros_campo_vectorial[Sistema_actual][0] = numx;
                        Parametros_campo_vectorial[Sistema_actual][1] = numy;
                        Parametros_campo_vectorial[Sistema_actual][2] = tamx;
                        Parametros_campo_vectorial[Sistema_actual][3] = tamy;
                        Factor_direccional[Sistema_actual] = facthom;
                        Factor_vectorial[Sistema_actual] = factnohom;
                     }

                        
};


#endif
