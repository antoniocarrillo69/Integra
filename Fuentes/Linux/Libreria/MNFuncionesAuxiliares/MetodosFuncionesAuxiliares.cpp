//////////////////////////////////////////////////////////////////////////////////////////////
// Métodos de graficación de funciones auxiliares                                           //
// Revisión: 16 de Octubre del 2001                                                         //
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


#include "MetodosFuncionesAuxiliares.hpp"
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "../Libreria/Ana_exp.hpp"
#include "../Libreria/Calnpol.hpp"



//////////////////////////////////////////////////////////////////////////
//   Grafica la funcion pasada como parametro en forma de texto ASCII   //
//////////////////////////////////////////////////////////////////////////
void Metodos_Numericos_FuncionesAuxiliares::Grafica_funcion_auxiliar(const char *exp, Dimension_Ventana vtn) 
{
   C_3D c_ini, a_coord; 
   double inc;

   int i;
   unsigned int pos;
   char xcad[2000],cad[2000], xexp[2010];
   char *xcad1, *xcad2, *xcad3, *xcadX, *xcadY, *npcadX, *npcadY;
                                               
   strcpy(xexp,exp);

   // Función sobre X o Y
   if (xexp[2] == 'x' || xexp[2] == 'y') {
      // Cambia el F(x)= por X=
      xexp[0] = xexp[1] = xexp[2] = 32, xexp[3] = 'X';

      Analizador_sintactico *As = new Analizador_sintactico;
   
      // Valida la expresion
      As->Analiza_expresion_tipo_01(xexp);
      if(!As->Numero_errores()) {
         // Obtiene la expresion en notacion polaca
         As->Retorna_expresion(xcad,POSTORDEN,2000);

         xcad1 = new char[2000];
         xcad2 = new char[2000];
         xcad3 = new char[2000];
         // Remplaza el valor de los parametros del actual sistema
         if(Numero_parametros[Sistema_actual]) {
            for(i = 0; i < Numero_parametros[Sistema_actual]; i++) {
               sprintf(xcad3,"|%s|",Nombre_parametro[Sistema_actual][i]);
               while(Busca_cadena(xcad,xcad3,pos)) {
                  Substr(xcad,0,pos,xcad1);
                  Substr(xcad,pos+3,2000,xcad2);
                  sprintf(xcad,"%s|%f|%s",xcad1,P[Sistema_actual][i],xcad2);
               }
            }
         }

         // Inicializa variables
         c_ini.x = 0.0;
         c_ini.y = 0.0;
         c_ini.z = 0.0;

         // Inidca que no se visualize el error matematico
   //      VISUALIZA_ERROR_MATEMATICO = 0;

         Calculadora_notacion_polaca  cnp;

         // Revisa sobre que eje se hara la graficacion
         switch(exp[2]) {
            case 'y': // Graficacion sobre el eje X
               // Remplaza la variable por su valor
               strcpy(cad,xcad);
               while(Busca_cadena(cad,"|y|",pos)) {
                  Substr(cad,0,pos,xcad1);
                  Substr(cad,pos+3,200,xcad2);
                  sprintf(cad,"%s|M01|%s",xcad1,xcad2);
               }
               inc = (vtn.Yf - vtn.Yi) / (long double) NUMERO_PUNTOS;
               for(c_ini.y = vtn.Yi; c_ini.y <= vtn.Yf; c_ini.y += inc) {
                  a_coord = c_ini;

                  // Actualiza el valor a calcular
                  cnp.Asigna_valor(0,c_ini.y);
                  // Evalua la expresion en notacion polaca
                  c_ini.x = cnp.Evalua(cad);
                  if(ERROR_MATEMATICO) {
                     ERROR_MATEMATICO = 0;
                     continue;
                  }

                  if(!Grafica_puntos[Sistema_actual]) Control_Visualizacion::Dibuja_linea(a_coord,c_ini,1);
                   else Control_Visualizacion::Dibuja_punto(c_ini,Color_Funcion_Auxiliar);
               }
               break;
            case 'x': // Graficacion sobre el eje Y
               // Remplaza la variable por su valor
               strcpy(cad,xcad);
               while(Busca_cadena(cad,"|x|",pos)) {
                  Substr(cad,0,pos,xcad1);
                  Substr(cad,pos+3,200,xcad2);
                  sprintf(cad,"%s|M01|%s",xcad1,xcad2);
               }
               inc = (vtn.Xf - vtn.Xi) / (long double) NUMERO_PUNTOS;
               for(c_ini.x = vtn.Xi; c_ini.x <= vtn.Xf; c_ini.x += inc) {
                  a_coord = c_ini;
                  // Actualiza el valor a calcular
                  cnp.Asigna_valor(0,c_ini.x);
                  // Evalua la expresion en notacion polaca
                  c_ini.y = cnp.Evalua(cad);
                  if(ERROR_MATEMATICO) {
                     ERROR_MATEMATICO = 0;
                     continue;
                  }

                  if(!Grafica_puntos[Sistema_actual]) Control_Visualizacion::Dibuja_linea(a_coord,c_ini,1);
                   else Control_Visualizacion::Dibuja_punto(c_ini,Color_Funcion_Auxiliar);
               }
               break;
         }
         delete []xcad1;
         delete []xcad2;
         delete []xcad3;
      }
      delete As;
    } else {
      Analizador_sintactico *As = new Analizador_sintactico;
      Calculadora_notacion_polaca cnp;

      xcad1 = cnp.Asigna_puntero(2010);
      xcad2 = cnp.Asigna_puntero(2010);
      xcad3 = cnp.Asigna_puntero(2010);
      xcadX = cnp.Asigna_puntero(2010);
      xcadY = cnp.Asigna_puntero(2010);
      npcadX = cnp.Asigna_puntero(2010);
      npcadY = cnp.Asigna_puntero(2010);

      // Retorna la cadena en postorden
      As->Retorna_expresion(xcad,POSTORDEN,2000);
      // Remplaza el valor de los parametros del actual sistema
      if(Numero_parametros[Sistema_actual]) {
         for(i = 0; i < Numero_parametros[Sistema_actual]; i++) {
            sprintf(xcad3,"|%s|",Nombre_parametro[Sistema_actual][i]);
            while(Busca_cadena(xcad,xcad3,pos)) {
               Substr(xcad,0,pos,xcad1);
               Substr(xcad,pos+3,2000,xcad2);
               sprintf(xcad,"%s|%f|%s",xcad1,P[Sistema_actual][i],xcad2);
            }
         }
      }
      strcpy(xexp,xcad);
         
      // Cambia el F(t)= por X=P
      xexp[0] = xexp[1] = 32;
      xexp[2] = 'X';
      xexp[3] = '=';
      xexp[4] = 'P';
      
      // Valida la expresion
      As->Analiza_expresion_tipo_01(xexp);
      if(!As->Numero_errores()) {

         // Separa las funciones para X e Y de la funcion paramétrica 
         xexp[2] = xexp[3] = xexp[4] = xexp[5] = 32;
         pos = strlen(xexp);
         xexp[2] = xexp[3] = xexp[4] = xexp[5] = 32;
         xexp[pos-1] = 0;
         cnp.Trim(xexp);
         int i = 0, par = 0, n_v = 0;
         while (xexp[i]) {
            if (xexp[i] == '(') par ++;
            // Busca el siguiente operador segun precedencia definidas
            if (!par) {
               // Revisa si existe el operador de esa precedencia
               if (',' == xexp[i]) n_v++, pos = i;
            }
            if (xexp[i] == ')') par --;
            i++;
         }
         cnp.Substr(xexp, 0, pos, xcadX);
         cnp.Substr(xexp, pos+1, strlen(xexp), xcadY);

         // Obtiene la expresion en notacion polaca
         strcpy(cad,"X=");
         strcat(cad,xcadX);
         strcpy(xcadX,cad);
         As->Analiza_expresion_tipo_01(xcadX);
         As->Retorna_expresion(npcadX,POSTORDEN,2000);
         // Remplaza la variable por su valor
         while(cnp.Busca_cadena(npcadX,"|t|",pos)) {
            cnp.Substr(npcadX,0,pos,xcad1);
            cnp.Substr(npcadX,pos+3,200,xcad2);
            sprintf(npcadX,"%s|M01|%s",xcad1,xcad2);
         }

         strcpy(cad,"X=");
         strcat(cad,xcadY);
         strcpy(xcadY,cad);
         As->Analiza_expresion_tipo_01(xcadY);
         // Obtiene la expresion en notacion polaca
         As->Retorna_expresion(npcadY,POSTORDEN,2000);
         while(cnp.Busca_cadena(npcadY,"|t|",pos)) {
            cnp.Substr(npcadY,0,pos,xcad1);
            cnp.Substr(npcadY,pos+3,200,xcad2);
            sprintf(npcadY,"%s|M01|%s",xcad1,xcad2);
         }
               
         // Inicializa variables
         c_ini.x = 0.0;
         c_ini.y = 0.0;
         c_ini.z = 0.0;

         inc = (vtn.Xf - vtn.Xi) / (long double) NUMERO_PUNTOS;
         for(t = vtn.Xi; t <= vtn.Xf; t += inc) {
           try {
               // Actualiza el valor a calcular
               cnp.Asigna_valor(0,t);
               // Evalua la expresion en notacion polaca
               c_ini.x = cnp.Evalua(npcadX);
               c_ini.y = cnp.Evalua(npcadY);
               if(ERROR_MATEMATICO) {
                  ERROR_MATEMATICO = 0;
                  continue;
               }
               if(!Grafica_puntos[Sistema_actual]) Control_Visualizacion::Dibuja_linea(a_coord,c_ini,1);
                else Control_Visualizacion::Dibuja_punto(c_ini,Color_Funcion_Auxiliar);
           } catch (...) {return;}; 
         }                

      }
      delete []xcad1;
      delete []xcad2;
      delete []xcad3;
      delete []xcadX;
      delete []xcadY;
      delete []npcadX;
      delete []npcadY;
   }
}



