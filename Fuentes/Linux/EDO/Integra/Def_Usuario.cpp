 //////////////////////////////////////////////////////////////////////////////////////////////
 // Definición de sistemas                                                                   //
 // Revisión: 8 de Enero del 2003                                                            //
 //                                                                                          //
 // Copyright (C) 1997-2003                                                                  //
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

 #include "Def_Usuario.hpp"


 void Definicion_Usuario::Inicializa(void)
 {

   Proyecto = "C:\\Integra\\Proyects\\Demo.D";

   Numero_sistemas = 25;


   Nombre_sistema[0] = "Atractor de Lorenz";
   Tipo_ecuacion[0] = 0;
   Nombre_sistema[1] = "Atrcator de Rosler";
   Tipo_ecuacion[1] = 0;
   Nombre_sistema[2] = "Atractor de Chua";
   Tipo_ecuacion[2] = 0;
   Nombre_sistema[3] = "Atractor de Duffing";
   Tipo_ecuacion[3] = 0;
   Nombre_sistema[4] = "Atractor de Duffing Forzado";
   Tipo_ecuacion[4] = 0;
   Nombre_sistema[5] = "FitzHugh-Nagumo";
   Tipo_ecuacion[5] = 0;
   Nombre_sistema[6] = "FitzHugh-Nagumo Perturbado";
   Tipo_ecuacion[6] = 0;
   Nombre_sistema[7] = "Hodgkin-Huxley";
   Tipo_ecuacion[7] = 0;
   Nombre_sistema[8] = "Oscilador Armonico";
   Tipo_ecuacion[8] = 0;
   Nombre_sistema[9] = "Pendulo sin Fricción";
   Tipo_ecuacion[9] = 0;
   Nombre_sistema[10] = "Pendulo con Fricción";
   Tipo_ecuacion[10] = 0;
   Nombre_sistema[11] = "Mendelson (polar)";
   Tipo_ecuacion[11] = 0;
   Nombre_sistema[12] = "Pendulo Forzado";
   Tipo_ecuacion[12] = 0;
   Nombre_sistema[13] = "Logística";
   Tipo_ecuacion[13] = 0;
   Nombre_sistema[14] = "Depredador-Presa";
   Tipo_ecuacion[14] = 0;
   Nombre_sistema[15] = "Hodgkin-Huxley Rapido";
   Tipo_ecuacion[15] = 0;
   Nombre_sistema[16] = "Hodgkin-Huxley Rapido-Lento";
   Tipo_ecuacion[16] = 0;
   Nombre_sistema[17] = "Modelo cuadrático";
   Tipo_ecuacion[17] = 0;
   Nombre_sistema[18] = "van der Pol";
   Tipo_ecuacion[18] = 0;
   Nombre_sistema[19] = "Poblaciones Chile";
   Tipo_ecuacion[19] = 0;
   Nombre_sistema[20] = "ValidarMetodosNumericos";
   Tipo_ecuacion[20] = 0;
   Nombre_sistema[21] = "ValidarMetodosNumericosRigidos";
   Tipo_ecuacion[21] = 0;
   Nombre_sistema[22] = "Belusov-Zhabotinsky";
   Tipo_ecuacion[22] = 0;
   Nombre_sistema[23] = "Mathieu";
   Tipo_ecuacion[23] = 0;
   Nombre_sistema[24] = "Lineal";
   Tipo_ecuacion[24] = 0;

   Ecuacion_original[0]=" ";
   Nombre_ecuacion[0][0]="x'=s*(y-x)";
   Nombre_ecuacion[0][1]="y'=r*x-y-x*z";
   Nombre_ecuacion[0][2]="z'=x*y-b*z";
   Ecuacion_original[1]=" ";
   Nombre_ecuacion[1][0]="x'=-(y+z)";
   Nombre_ecuacion[1][1]="y'=x+a*y";
   Nombre_ecuacion[1][2]="z'=a+z*(x-b)";
   Ecuacion_original[2]=" ";
   Nombre_ecuacion[2][0]="V1'=C1*(G*(V2-V1)-a*V1*((b*b*V1*V1/3)-1))";
   Nombre_ecuacion[2][1]="V2'=C2*(G*(V1-V2)+i)";
   Nombre_ecuacion[2][2]="i'=-L*V2";
   Ecuacion_original[3]=" ";
   Nombre_ecuacion[3][0]="y'=v";
   Nombre_ecuacion[3][1]="v'=y-y*y*y";
   Ecuacion_original[4]=" ";
   Nombre_ecuacion[4][0]="y'=v";
   Nombre_ecuacion[4][1]="v'=y-y*y*y+e*sinl(t)";
   Ecuacion_original[5]=" ";
   Nombre_ecuacion[5][0]="v'=I-v*(v-1.0)*(v-a)-w";
   Nombre_ecuacion[5][1]="w'=b*(v-(g*w))";
   Ecuacion_original[6]=" ";
   Nombre_ecuacion[6][0]="v'=-v*(v-1.0)*(v-a)-w";
   Nombre_ecuacion[6][1]="w'=b*(v-(g*w))";
   Ecuacion_original[7]=" ";
   Nombre_ecuacion[7][0]="v'=1.0/C*(-(gk*powl(n,4.0)*(v-vk))-(gn*powl(m,3.0)*h*(v-vn))-(gl*(v-vl))+I)";
   Nombre_ecuacion[7][1]="m'=(((0.1*((25.0-v)/(expl((25.0-v)/10.0)-1.0))))*(1.0-m))-(((4.0*expl(-v/18.0)))*m)";
   Nombre_ecuacion[7][2]="h'=(((0.07*expl(-v/20.0)))*(1.0-h))-(((1.0/(expl((30.0-v)/10.0)+1.0)))*h)";
   Nombre_ecuacion[7][3]="n'=(((0.01*((10.0-v)/(expl((10.0-v)/10.0)-1.0))))*(1.0-n))-(((0.125*expl(-v/80.0)))*n)";
   Ecuacion_original[8]=" ";
   Nombre_ecuacion[8][0]="x'=y";
   Nombre_ecuacion[8][1]="y'=-a*x";
   Ecuacion_original[9]=" ";
   Nombre_ecuacion[9][0]="x'=y";
   Nombre_ecuacion[9][1]="y'=-c*sinl(x)";
   Ecuacion_original[10]=" ";
   Nombre_ecuacion[10][0]="x'=y";
   Nombre_ecuacion[10][1]="y'=-k*y-c*sinl(x)";
   Ecuacion_original[11]=" ";
   Nombre_ecuacion[11][0]="p'=p*(1.0-p)";
   Nombre_ecuacion[11][1]="o'=sinl(o/2.0)*sinl(o/2.0)";
   Ecuacion_original[12]=" ";
   Nombre_ecuacion[12][0]="w'=-(w/q)-sinl(te)+g*cosl(fi)";
   Nombre_ecuacion[12][1]="te'=w";
   Nombre_ecuacion[12][2]="fi'=wd";
   Ecuacion_original[13]=" ";
   Nombre_ecuacion[13][0]="T'=1.0";
   Nombre_ecuacion[13][1]="P'=K*(1-(P*invl(N))*P)";
   Ecuacion_original[14]=" ";
   Nombre_ecuacion[14][0]="C'=(a*C)-(b*C*Z)";
   Nombre_ecuacion[14][1]="Z'=-(g*Z)+(d*C*Z)";
   Ecuacion_original[15]=" ";
   Nombre_ecuacion[15][0]="v'=1.0/C*(-(gk*powl(n,4.0)*(v-vk))-(gn*powl(m,3.0)*h*(v-vn))-(gl*(v-vl))+I)";
   Nombre_ecuacion[15][1]="m'=(((0.1*((25.0-v)/(expl((25.0-v)/10.0)-1.0))))*(1.0-m))-(((4.0*expl(-v/18.0)))*m)";
   Ecuacion_original[16]=" ";
   Nombre_ecuacion[16][0]="v'=1.0/C*(-(gk*powl(n,4.0)*(v-vk))-(gn*powl((((0.1*((25.0-v)/(expl((25.0-v)/10.0)-1.0))))/(((0.1*((25.0-v)/(expl((25.0-v)/10.0)-1.0))))+((4.0*expl(-v/18.0))))),3.0)*(0.8-n)*(v-vn))-(gl*(v-vl))+I)";
   Nombre_ecuacion[16][1]="n'=(((0.01*((10.0-v)/(expl((10.0-v)/10.0)-1.0))))*(1.0-n))-(((0.125*expl(-v/80.0)))*n)";
   Ecuacion_original[17]=" ";
   Nombre_ecuacion[17][0]="x'=x*(a+b*x+c*y)";
   Nombre_ecuacion[17][1]="y'=y*(d+e*x+f*y)";
   Ecuacion_original[18]=" ";
   Nombre_ecuacion[18][0]="x'=y-(((x*x*x)/a)-x)";
   Nombre_ecuacion[18][1]="y'=-e*x+b*cosl(t)";
   Ecuacion_original[19]=" ";
   Nombre_ecuacion[19][0]="x'=((1.0-x)*(A+(x*x))-Q*y)*(x*x)";
   Nombre_ecuacion[19][1]="y'=B*(x-y)*(A+(x*x))*y";
   Ecuacion_original[20]=" ";
   Nombre_ecuacion[20][0]="x'=1";
   Nombre_ecuacion[20][1]="y'=y-x*x+1";
   Ecuacion_original[21]=" ";
   Nombre_ecuacion[21][0]="x'=1";
   Nombre_ecuacion[21][1]="y'=5*expl(5*x)*(y-x)*(y-x)+1";
   Ecuacion_original[22]=" ";
   Nombre_ecuacion[22][0]="x'=a-x-((4.0*x*y)/(1.0+x*x))";
   Nombre_ecuacion[22][1]="y'=b*x+(1.0-(y/(1.0+x*x)))";
   Ecuacion_original[23]=" ";
   Nombre_ecuacion[23][0]="x'=v";
   Nombre_ecuacion[23][1]="v'=-(a+b*cosl(z))*x";
   Nombre_ecuacion[23][2]="z'=1";
   Ecuacion_original[24]=" ";
   Nombre_ecuacion[24][0]="x'=a*x+b*y+c*z";
   Nombre_ecuacion[24][1]="y'=d*x+e*y+f*z";
   Nombre_ecuacion[24][2]="z'=g*x+h*y+i*z";

   Numero_ecuaciones[0] = 3;
   Numero_parametros[0] = 3;
   Nombre_parametro[0][0] = "s";
   Nombre_parametro[0][1] = "r";
   Nombre_parametro[0][2] = "b";

   Numero_ecuaciones[1] = 3;
   Numero_parametros[1] = 2;
   Nombre_parametro[1][0] = "a";
   Nombre_parametro[1][1] = "b";

   Numero_ecuaciones[2] = 3;
   Numero_parametros[2] = 6;
   Nombre_parametro[2][0] = "C1";
   Nombre_parametro[2][1] = "C2";
   Nombre_parametro[2][2] = "L";
   Nombre_parametro[2][3] = "G";
   Nombre_parametro[2][4] = "a";
   Nombre_parametro[2][5] = "b";

   Numero_ecuaciones[3] = 2;
   Numero_parametros[3] = 0;

   Numero_ecuaciones[4] = 2;
   Numero_parametros[4] = 1;
   Nombre_parametro[4][0] = "e";

   Numero_ecuaciones[5] = 2;
   Numero_parametros[5] = 4;
   Nombre_parametro[5][0] = "a";
   Nombre_parametro[5][1] = "b";
   Nombre_parametro[5][2] = "g";
   Nombre_parametro[5][3] = "I";

   Numero_ecuaciones[6] = 2;
   Numero_parametros[6] = 5;
   Nombre_parametro[6][0] = "a";
   Nombre_parametro[6][1] = "b";
   Nombre_parametro[6][2] = "g";
   Nombre_parametro[6][3] = "vi";
   Nombre_parametro[6][4] = "ti";

   Numero_ecuaciones[7] = 4;
   Numero_parametros[7] = 8;
   Nombre_parametro[7][0] = "gk";
   Nombre_parametro[7][1] = "gn";
   Nombre_parametro[7][2] = "gl";
   Nombre_parametro[7][3] = "vn";
   Nombre_parametro[7][4] = "vk";
   Nombre_parametro[7][5] = "vl";
   Nombre_parametro[7][6] = "C";
   Nombre_parametro[7][7] = "I";

   Numero_ecuaciones[8] = 2;
   Numero_parametros[8] = 1;
   Nombre_parametro[8][0] = "a";

   Numero_ecuaciones[9] = 2;
   Numero_parametros[9] = 1;
   Nombre_parametro[9][0] = "c";

   Numero_ecuaciones[10] = 2;
   Numero_parametros[10] = 2;
   Nombre_parametro[10][0] = "k";
   Nombre_parametro[10][1] = "c";

   Numero_ecuaciones[11] = 2;
   Numero_parametros[11] = 0;

   Numero_ecuaciones[12] = 3;
   Numero_parametros[12] = 3;
   Nombre_parametro[12][0] = "q";
   Nombre_parametro[12][1] = "wd";
   Nombre_parametro[12][2] = "g";

   Numero_ecuaciones[13] = 2;
   Numero_parametros[13] = 2;
   Nombre_parametro[13][0] = "K";
   Nombre_parametro[13][1] = "N";

   Numero_ecuaciones[14] = 2;
   Numero_parametros[14] = 4;
   Nombre_parametro[14][0] = "a";
   Nombre_parametro[14][1] = "b";
   Nombre_parametro[14][2] = "g";
   Nombre_parametro[14][3] = "d";

   Numero_ecuaciones[15] = 2;
   Numero_parametros[15] = 10;
   Nombre_parametro[15][0] = "gk";
   Nombre_parametro[15][1] = "gn";
   Nombre_parametro[15][2] = "gl";
   Nombre_parametro[15][3] = "vn";
   Nombre_parametro[15][4] = "vk";
   Nombre_parametro[15][5] = "vl";
   Nombre_parametro[15][6] = "C";
   Nombre_parametro[15][7] = "I";
   Nombre_parametro[15][8] = "h";
   Nombre_parametro[15][9] = "n";

   Numero_ecuaciones[16] = 2;
   Numero_parametros[16] = 8;
   Nombre_parametro[16][0] = "gk";
   Nombre_parametro[16][1] = "gn";
   Nombre_parametro[16][2] = "gl";
   Nombre_parametro[16][3] = "vn";
   Nombre_parametro[16][4] = "vk";
   Nombre_parametro[16][5] = "vl";
   Nombre_parametro[16][6] = "C";
   Nombre_parametro[16][7] = "I";

   Numero_ecuaciones[17] = 2;
   Numero_parametros[17] = 6;
   Nombre_parametro[17][0] = "a";
   Nombre_parametro[17][1] = "b";
   Nombre_parametro[17][2] = "c";
   Nombre_parametro[17][3] = "d";
   Nombre_parametro[17][4] = "e";
   Nombre_parametro[17][5] = "f";

   Numero_ecuaciones[18] = 2;
   Numero_parametros[18] = 3;
   Nombre_parametro[18][0] = "a";
   Nombre_parametro[18][1] = "b";
   Nombre_parametro[18][2] = "e";

   Numero_ecuaciones[19] = 2;
   Numero_parametros[19] = 3;
   Nombre_parametro[19][0] = "A";
   Nombre_parametro[19][1] = "B";
   Nombre_parametro[19][2] = "Q";

   Numero_ecuaciones[20] = 2;
   Numero_parametros[20] = 0;

   Numero_ecuaciones[21] = 2;
   Numero_parametros[21] = 0;

   Numero_ecuaciones[22] = 2;
   Numero_parametros[22] = 2;
   Nombre_parametro[22][0] = "a";
   Nombre_parametro[22][1] = "b";

   Numero_ecuaciones[23] = 3;
   Numero_parametros[23] = 2;
   Nombre_parametro[23][0] = "a";
   Nombre_parametro[23][1] = "b";

   Numero_ecuaciones[24] = 3;
   Numero_parametros[24] = 9;
   Nombre_parametro[24][0] = "a";
   Nombre_parametro[24][1] = "b";
   Nombre_parametro[24][2] = "c";
   Nombre_parametro[24][3] = "d";
   Nombre_parametro[24][4] = "e";
   Nombre_parametro[24][5] = "f";
   Nombre_parametro[24][6] = "g";
   Nombre_parametro[24][7] = "h";
   Nombre_parametro[24][8] = "i";



   funcion[0][0] = &Definicion_Usuario::Fn00000000;
   funcion[0][1] = &Definicion_Usuario::Fn00000001;
   funcion[0][2] = &Definicion_Usuario::Fn00000002;
   funcion[1][0] = &Definicion_Usuario::Fn00010000;
   funcion[1][1] = &Definicion_Usuario::Fn00010001;
   funcion[1][2] = &Definicion_Usuario::Fn00010002;
   funcion[2][0] = &Definicion_Usuario::Fn00020000;
   funcion[2][1] = &Definicion_Usuario::Fn00020001;
   funcion[2][2] = &Definicion_Usuario::Fn00020002;
   funcion[3][0] = &Definicion_Usuario::Fn00030000;
   funcion[3][1] = &Definicion_Usuario::Fn00030001;
   funcion[4][0] = &Definicion_Usuario::Fn00040000;
   funcion[4][1] = &Definicion_Usuario::Fn00040001;
   funcion[5][0] = &Definicion_Usuario::Fn00050000;
   funcion[5][1] = &Definicion_Usuario::Fn00050001;
   funcion[6][0] = &Definicion_Usuario::Fn00060000;
   funcion[6][1] = &Definicion_Usuario::Fn00060001;
   funcion[7][0] = &Definicion_Usuario::Fn00070000;
   funcion[7][1] = &Definicion_Usuario::Fn00070001;
   funcion[7][2] = &Definicion_Usuario::Fn00070002;
   funcion[7][3] = &Definicion_Usuario::Fn00070003;
   funcion[8][0] = &Definicion_Usuario::Fn00080000;
   funcion[8][1] = &Definicion_Usuario::Fn00080001;
   funcion[9][0] = &Definicion_Usuario::Fn00090000;
   funcion[9][1] = &Definicion_Usuario::Fn00090001;
   funcion[10][0] = &Definicion_Usuario::Fn00100000;
   funcion[10][1] = &Definicion_Usuario::Fn00100001;
   funcion[11][0] = &Definicion_Usuario::Fn00110000;
   funcion[11][1] = &Definicion_Usuario::Fn00110001;
   funcion[12][0] = &Definicion_Usuario::Fn00120000;
   funcion[12][1] = &Definicion_Usuario::Fn00120001;
   funcion[12][2] = &Definicion_Usuario::Fn00120002;
   funcion[13][0] = &Definicion_Usuario::Fn00130000;
   funcion[13][1] = &Definicion_Usuario::Fn00130001;
   funcion[14][0] = &Definicion_Usuario::Fn00140000;
   funcion[14][1] = &Definicion_Usuario::Fn00140001;
   funcion[15][0] = &Definicion_Usuario::Fn00150000;
   funcion[15][1] = &Definicion_Usuario::Fn00150001;
   funcion[16][0] = &Definicion_Usuario::Fn00160000;
   funcion[16][1] = &Definicion_Usuario::Fn00160001;
   funcion[17][0] = &Definicion_Usuario::Fn00170000;
   funcion[17][1] = &Definicion_Usuario::Fn00170001;
   funcion[18][0] = &Definicion_Usuario::Fn00180000;
   funcion[18][1] = &Definicion_Usuario::Fn00180001;
   funcion[19][0] = &Definicion_Usuario::Fn00190000;
   funcion[19][1] = &Definicion_Usuario::Fn00190001;
   funcion[20][0] = &Definicion_Usuario::Fn00200000;
   funcion[20][1] = &Definicion_Usuario::Fn00200001;
   funcion[21][0] = &Definicion_Usuario::Fn00210000;
   funcion[21][1] = &Definicion_Usuario::Fn00210001;
   funcion[22][0] = &Definicion_Usuario::Fn00220000;
   funcion[22][1] = &Definicion_Usuario::Fn00220001;
   funcion[23][0] = &Definicion_Usuario::Fn00230000;
   funcion[23][1] = &Definicion_Usuario::Fn00230001;
   funcion[23][2] = &Definicion_Usuario::Fn00230002;
   funcion[24][0] = &Definicion_Usuario::Fn00240000;
   funcion[24][1] = &Definicion_Usuario::Fn00240001;
   funcion[24][2] = &Definicion_Usuario::Fn00240002;


   Numero_funciones_auxiliares[0] = 0;
   Numero_funciones_auxiliares[1] = 0;
   Numero_funciones_auxiliares[2] = 0;
   Numero_funciones_auxiliares[3] = 0;
   Numero_funciones_auxiliares[4] = 0;
   Numero_funciones_auxiliares[5] = 0;
   Numero_funciones_auxiliares[6] = 0;
   Numero_funciones_auxiliares[7] = 0;
   Numero_funciones_auxiliares[8] = 0;
   Numero_funciones_auxiliares[9] = 0;
   Numero_funciones_auxiliares[10] = 0;
   Numero_funciones_auxiliares[11] = 0;
   Numero_funciones_auxiliares[12] = 0;
   Numero_funciones_auxiliares[13] = 0;
   Numero_funciones_auxiliares[14] = 0;
   Numero_funciones_auxiliares[15] = 0;
   Numero_funciones_auxiliares[16] = 0;
   Numero_funciones_auxiliares[17] = 0;
   Numero_funciones_auxiliares[18] = 0;
   Numero_funciones_auxiliares[19] = 0;
   Numero_funciones_auxiliares[20] = 0;
   Numero_funciones_auxiliares[21] = 0;
   Numero_funciones_auxiliares[22] = 0;
   Numero_funciones_auxiliares[23] = 0;
   Numero_funciones_auxiliares[24] = 0;


   Parametros(99);
 }


 void Definicion_Usuario::Parametros(const unsigned int i)
 {
   if (i == 0 || i == 99) P[0][0] = 10;
   if (i == 0 || i == 99) P[0][1] = 28;
   if (i == 0 || i == 99) P[0][2] = 2.666667;
   if (i == 1 || i == 99) P[1][0] = 0.2;
   if (i == 1 || i == 99) P[1][1] = 5.7;
   if (i == 2 || i == 99) P[2][0] = 9;
   if (i == 2 || i == 99) P[2][1] = 0.5;
   if (i == 2 || i == 99) P[2][2] = 7;
   if (i == 2 || i == 99) P[2][3] = 0.65;
   if (i == 2 || i == 99) P[2][4] = 0.8;
   if (i == 2 || i == 99) P[2][5] = 0.1;
   if (i == 4 || i == 99) P[4][0] = 0.06;
   if (i == 5 || i == 99) P[5][0] = 0.15;
   if (i == 5 || i == 99) P[5][1] = 0.01;
   if (i == 5 || i == 99) P[5][2] = 2.5;
   if (i == 5 || i == 99) P[5][3] = 0.05;
   if (i == 6 || i == 99) P[6][0] = 0.15;
   if (i == 6 || i == 99) P[6][1] = 0.01;
   if (i == 6 || i == 99) P[6][2] = 2.5;
   if (i == 6 || i == 99) P[6][3] = 0.33;
   if (i == 6 || i == 99) P[6][4] = 120.0;
   if (i == 7 || i == 99) P[7][0] = 36.0;
   if (i == 7 || i == 99) P[7][1] = 120.0;
   if (i == 7 || i == 99) P[7][2] = 0.3;
   if (i == 7 || i == 99) P[7][3] = 115.0;
   if (i == 7 || i == 99) P[7][4] = -12.0;
   if (i == 7 || i == 99) P[7][5] = 10.6;
   if (i == 7 || i == 99) P[7][6] = 1.0;
   if (i == 7 || i == 99) P[7][7] = 0.0;
   if (i == 8 || i == 99) P[8][0] = 1.0;
   if (i == 9 || i == 99) P[9][0] = 1.0;
   if (i == 10 || i == 99) P[10][0] = 0.5;
   if (i == 10 || i == 99) P[10][1] = 1.0;
   if (i == 12 || i == 99) P[12][0] = 2;
   if (i == 12 || i == 99) P[12][1] = 0.666666666666666666666;
   if (i == 12 || i == 99) P[12][2] = 1.0;
   if (i == 13 || i == 99) P[13][0] = 0.3;
   if (i == 13 || i == 99) P[13][1] = 6.0;
   if (i == 14 || i == 99) P[14][0] = 2.0;
   if (i == 14 || i == 99) P[14][1] = 1.2;
   if (i == 14 || i == 99) P[14][2] = 1.0;
   if (i == 14 || i == 99) P[14][3] = 0.9;
   if (i == 15 || i == 99) P[15][0] = 36.0;
   if (i == 15 || i == 99) P[15][1] = 120.0;
   if (i == 15 || i == 99) P[15][2] = 0.3;
   if (i == 15 || i == 99) P[15][3] = 115.0;
   if (i == 15 || i == 99) P[15][4] = -12.0;
   if (i == 15 || i == 99) P[15][5] = 10.6;
   if (i == 15 || i == 99) P[15][6] = 1.0;
   if (i == 15 || i == 99) P[15][7] = 0.0;
   if (i == 15 || i == 99) P[15][8] = 0.596;
   if (i == 15 || i == 99) P[15][9] = 0.3176;
   if (i == 16 || i == 99) P[16][0] = 36.0;
   if (i == 16 || i == 99) P[16][1] = 120.0;
   if (i == 16 || i == 99) P[16][2] = 0.3;
   if (i == 16 || i == 99) P[16][3] = 115.0;
   if (i == 16 || i == 99) P[16][4] = -12.0;
   if (i == 16 || i == 99) P[16][5] = 10.6;
   if (i == 16 || i == 99) P[16][6] = 1.0;
   if (i == 16 || i == 99) P[16][7] = 0.0;
   if (i == 17 || i == 99) P[17][0] = 1.0;
   if (i == 17 || i == 99) P[17][1] = 0.0;
   if (i == 17 || i == 99) P[17][2] = -0.5;
   if (i == 17 || i == 99) P[17][3] = -1.0;
   if (i == 17 || i == 99) P[17][4] = 0.0;
   if (i == 17 || i == 99) P[17][5] = 0.2;
   if (i == 18 || i == 99) P[18][0] = 3.0;
   if (i == 18 || i == 99) P[18][1] = 0.0;
   if (i == 18 || i == 99) P[18][2] = 1.0;
   if (i == 19 || i == 99) P[19][0] = 0.1;
   if (i == 19 || i == 99) P[19][1] = 0.27;
   if (i == 19 || i == 99) P[19][2] = 0.277225;
   if (i == 22 || i == 99) P[22][0] = 1.0;
   if (i == 22 || i == 99) P[22][1] = 1.0;
   if (i == 23 || i == 99) P[23][0] = 1.0;
   if (i == 23 || i == 99) P[23][1] = 1.0;
   if (i == 24 || i == 99) P[24][0] = 1;
   if (i == 24 || i == 99) P[24][1] = 1;
   if (i == 24 || i == 99) P[24][2] = 1;
   if (i == 24 || i == 99) P[24][3] = 1;
   if (i == 24 || i == 99) P[24][4] = 1;
   if (i == 24 || i == 99) P[24][5] = 1;
   if (i == 24 || i == 99) P[24][6] = 1;
   if (i == 24 || i == 99) P[24][7] = 1;
   if (i == 24 || i == 99) P[24][8] = 1;
 }


 void Definicion_Usuario::Configuracion(void)
 {
   Config[0][0] = -20.000000;
   Config[0][1] = -20.000000;
   Config[0][2] = -20.000000;
   Config[0][3] = 20.000000;
   Config[0][4] = 20.000000;
   Config[0][5] = 20.000000;
   Config[1][0] = -10.000000;
   Config[1][1] = -10.000000;
   Config[1][2] = -10.000000;
   Config[1][3] = 10.000000;
   Config[1][4] = 10.000000;
   Config[1][5] = 10.000000;
   Config[2][0] = -10.000000;
   Config[2][1] = -10.000000;
   Config[2][2] = -10.000000;
   Config[2][3] = 10.000000;
   Config[2][4] = 10.000000;
   Config[2][5] = 10.000000;
   Config[3][0] = -4.000000;
   Config[3][1] = -4.000000;
   Config[3][2] = -4.000000;
   Config[3][3] = 4.000000;
   Config[3][4] = 4.000000;
   Config[3][5] = 4.000000;
   Config[4][0] = -4.000000;
   Config[4][1] = -4.000000;
   Config[4][2] = -4.000000;
   Config[4][3] = 4.000000;
   Config[4][4] = 4.000000;
   Config[4][5] = 4.000000;
   Config[5][0] = -1000.000000;
   Config[5][1] = -1.000000;
   Config[5][2] = -10.000000;
   Config[5][3] = 1000.000000;
   Config[5][4] = 1.000000;
   Config[5][5] = 10.000000;
   Config[6][0] = -1000.000000;
   Config[6][1] = -1.000000;
   Config[6][2] = -10.000000;
   Config[6][3] = 1000.000000;
   Config[6][4] = 1.000000;
   Config[6][5] = 10.000000;
   Config[7][0] = -10.000000;
   Config[7][1] = -100.000000;
   Config[7][2] = -10.000000;
   Config[7][3] = 10.000000;
   Config[7][4] = 100.000000;
   Config[7][5] = 10.000000;
   Config[8][0] = -10.000000;
   Config[8][1] = -10.000000;
   Config[8][2] = -10.000000;
   Config[8][3] = 10.000000;
   Config[8][4] = 10.000000;
   Config[8][5] = 10.000000;
   Config[9][0] = -10.000000;
   Config[9][1] = -10.000000;
   Config[9][2] = -10.000000;
   Config[9][3] = 10.000000;
   Config[9][4] = 10.000000;
   Config[9][5] = 10.000000;
   Config[10][0] = -10.000000;
   Config[10][1] = -10.000000;
   Config[10][2] = -10.000000;
   Config[10][3] = 10.000000;
   Config[10][4] = 10.000000;
   Config[10][5] = 10.000000;
   Config[11][0] = -3.000000;
   Config[11][1] = -3.000000;
   Config[11][2] = -3.000000;
   Config[11][3] = 3.000000;
   Config[11][4] = 3.000000;
   Config[11][5] = 3.000000;
   Config[12][0] = -10.000000;
   Config[12][1] = -10.000000;
   Config[12][2] = -1000.000000;
   Config[12][3] = 10.000000;
   Config[12][4] = 10.000000;
   Config[12][5] = 1000.000000;
   Config[13][0] = -10.000000;
   Config[13][1] = -10.000000;
   Config[13][2] = -10.000000;
   Config[13][3] = 10.000000;
   Config[13][4] = 10.000000;
   Config[13][5] = 10.000000;
   Config[14][0] = -10.000000;
   Config[14][1] = -10.000000;
   Config[14][2] = -10.000000;
   Config[14][3] = 10.000000;
   Config[14][4] = 10.000000;
   Config[14][5] = 10.000000;
   Config[15][0] = -150.000000;
   Config[15][1] = -1.000000;
   Config[15][2] = -10.000000;
   Config[15][3] = 150.000000;
   Config[15][4] = 1.000000;
   Config[15][5] = 10.000000;
   Config[16][0] = -100.000000;
   Config[16][1] = -1.000000;
   Config[16][2] = -10.000000;
   Config[16][3] = 100.000000;
   Config[16][4] = 1.000000;
   Config[16][5] = 10.000000;
   Config[17][0] = -10.000000;
   Config[17][1] = -10.000000;
   Config[17][2] = -10.000000;
   Config[17][3] = 10.000000;
   Config[17][4] = 10.000000;
   Config[17][5] = 10.000000;
   Config[18][0] = -10.000000;
   Config[18][1] = -10.000000;
   Config[18][2] = -10.000000;
   Config[18][3] = 10.000000;
   Config[18][4] = 10.000000;
   Config[18][5] = 10.000000;
   Config[19][0] = -10.000000;
   Config[19][1] = -10.000000;
   Config[19][2] = -10.000000;
   Config[19][3] = 10.000000;
   Config[19][4] = 10.000000;
   Config[19][5] = 10.000000;
   Config[20][0] = -10.000000;
   Config[20][1] = -10.000000;
   Config[20][2] = -10.000000;
   Config[20][3] = 10.000000;
   Config[20][4] = 10.000000;
   Config[20][5] = 10.000000;
   Config[21][0] = -10.000000;
   Config[21][1] = -10.000000;
   Config[21][2] = -10.000000;
   Config[21][3] = 10.000000;
   Config[21][4] = 10.000000;
   Config[21][5] = 10.000000;
   Config[22][0] = -10.000000;
   Config[22][1] = -10.000000;
   Config[22][2] = -10.000000;
   Config[22][3] = 10.000000;
   Config[22][4] = 10.000000;
   Config[22][5] = 10.000000;
   Config[23][0] = -10.000000;
   Config[23][1] = -10.000000;
   Config[23][2] = -10.000000;
   Config[23][3] = 10.000000;
   Config[23][4] = 10.000000;
   Config[23][5] = 10.000000;
   Config[24][0] = -10.000000;
   Config[24][1] = -10.000000;
   Config[24][2] = -10.000000;
   Config[24][3] = 10.000000;
   Config[24][4] = 10.000000;
   Config[24][5] = 10.000000;

   for(int i = 0; i < Numero_sistemas ; i++) {
      Escenario[i].x = 1, Escenario[i].y = 2;
      if (Numero_ecuaciones[i] >= 3) Escenario[i].z = 3, Ventana_activa[i] = EJES_COORDENADOS_3D;
       else Escenario[i].z = 0, Ventana_activa[i] = EJES_COORDENADOS_2D;
      Metodo_N_actual[i] = 99;
   }
   Ventana_activa[5] = 1;
   Escenario[5].x = Numero_ecuaciones[5] + 1;
   Escenario[5].y = 1;
   Escenario[5].z = 0;
   Ventana_activa[6] = 2;
   Escenario[6].x = Numero_ecuaciones[6] + 1;
   Escenario[6].y = 1;
   Escenario[6].z = 0;
   Metodo_N_actual[6] = 4;
   Escenario[7].x = Numero_ecuaciones[7] + 1;
   Escenario[7].y = 1;
   Escenario[7].z = 0;
   Ventana_activa[7] = 2;
   Ventana_activa[11] = 6;
   Escenario[12].x = 2;
   Escenario[12].y = 1;
   Escenario[12].z = 0;
   Ventana_activa[12] = 1;
   Escenario[15].x = Numero_ecuaciones[15] + 1;
   Escenario[15].y = 1;
   Escenario[15].z = 0;
   Ventana_activa[15] = 1;
   Escenario[16].x = Numero_ecuaciones[16] + 1;
   Escenario[16].y = 1;
   Escenario[16].z = 0;
   Ventana_activa[16] = 1;
 }

 long double Definicion_Usuario::Fn00000000(void)
 {
   return ( P[0][0]*(X[1]-X[0]) );
 }

 long double Definicion_Usuario::Fn00000001(void)
 {
   return ( P[0][1]*X[0]-X[1]-X[0]*X[2] );
 }

 long double Definicion_Usuario::Fn00000002(void)
 {
   return ( X[0]*X[1]-P[0][2]*X[2] );
 }

 long double Definicion_Usuario::Fn00010000(void)
 {
   return ( -(X[1]+X[2]) );
 }

 long double Definicion_Usuario::Fn00010001(void)
 {
   return ( X[0]+P[1][0]*X[1] );
 }

 long double Definicion_Usuario::Fn00010002(void)
 {
   return ( P[1][0]+X[2]*(X[0]-P[1][1]) );
 }

 long double Definicion_Usuario::Fn00020000(void)
 {
   return ( P[2][0]*(P[2][3]*(X[1]-X[0])-P[2][4]*X[0]*((P[2][5]*P[2][5]*X[0]*X[0]/3)-1)) );
 }

 long double Definicion_Usuario::Fn00020001(void)
 {
   return ( P[2][1]*(P[2][3]*(X[0]-X[1])+X[2]) );
 }

 long double Definicion_Usuario::Fn00020002(void)
 {
   return ( -P[2][2]*X[1] );
 }

 long double Definicion_Usuario::Fn00030000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00030001(void)
 {
   return ( X[0]-X[0]*X[0]*X[0] );
 }

 long double Definicion_Usuario::Fn00040000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00040001(void)
 {
   return ( X[0]-X[0]*X[0]*X[0]+P[4][0]*sinl(t) );
 }

 long double Definicion_Usuario::Fn00050000(void)
 {
   return ( P[5][3]-X[0]*(X[0]-1.0)*(X[0]-P[5][0])-X[1] );
 }

 long double Definicion_Usuario::Fn00050001(void)
 {
   return ( P[5][1]*(X[0]-(P[5][2]*X[1])) );
 }

 long double Definicion_Usuario::Fn00060000(void)
 {
   return ( -X[0]*(X[0]-1.0)*(X[0]-P[6][0])-X[1] );
 }

 long double Definicion_Usuario::Fn00060001(void)
 {
   return ( P[6][1]*(X[0]-(P[6][2]*X[1])) );
 }

 long double Definicion_Usuario::Fn00070000(void)
 {
   return ( 1.0/P[7][6]*(-(P[7][0]*powl(X[3],4.0)*(X[0]-P[7][4]))-(P[7][1]*powl(X[1],3.0)*X[2]*(X[0]-P[7][3]))-(P[7][2]*(X[0]-P[7][5]))+P[7][7]) );
 }

 long double Definicion_Usuario::Fn00070001(void)
 {
   return ( (((0.1*((25.0-X[0])/(expl((25.0-X[0])/10.0)-1.0))))*(1.0-X[1]))-(((4.0*expl(-X[0]/18.0)))*X[1]) );
 }

 long double Definicion_Usuario::Fn00070002(void)
 {
   return ( (((0.07*expl(-X[0]/20.0)))*(1.0-X[2]))-(((1.0/(expl((30.0-X[0])/10.0)+1.0)))*X[2]) );
 }

 long double Definicion_Usuario::Fn00070003(void)
 {
   return ( (((0.01*((10.0-X[0])/(expl((10.0-X[0])/10.0)-1.0))))*(1.0-X[3]))-(((0.125*expl(-X[0]/80.0)))*X[3]) );
 }

 long double Definicion_Usuario::Fn00080000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00080001(void)
 {
   return ( -P[8][0]*X[0] );
 }

 long double Definicion_Usuario::Fn00090000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00090001(void)
 {
   return ( -P[9][0]*sinl(X[0]) );
 }

 long double Definicion_Usuario::Fn00100000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00100001(void)
 {
   return ( -P[10][0]*X[1]-P[10][1]*sinl(X[0]) );
 }

 long double Definicion_Usuario::Fn00110000(void)
 {
   return ( X[0]*(1.0-X[0]) );
 }

 long double Definicion_Usuario::Fn00110001(void)
 {
   return ( sinl(X[1]/2.0)*sinl(X[1]/2.0) );
 }

 long double Definicion_Usuario::Fn00120000(void)
 {
   return ( -(X[0]/P[12][0])-sinl(X[1])+P[12][2]*cosl(X[2]) );
 }

 long double Definicion_Usuario::Fn00120001(void)
 {
   return ( X[0] );
 }

 long double Definicion_Usuario::Fn00120002(void)
 {
   return ( P[12][1] );
 }

 long double Definicion_Usuario::Fn00130000(void)
 {
   return ( 1.0 );
 }

 long double Definicion_Usuario::Fn00130001(void)
 {
   return ( P[13][0]*(1-(X[1]*invl(P[13][1]))*X[1]) );
 }

 long double Definicion_Usuario::Fn00140000(void)
 {
   return ( (P[14][0]*X[0])-(P[14][1]*X[0]*X[1]) );
 }

 long double Definicion_Usuario::Fn00140001(void)
 {
   return ( -(P[14][2]*X[1])+(P[14][3]*X[0]*X[1]) );
 }

 long double Definicion_Usuario::Fn00150000(void)
 {
   return ( 1.0/P[15][6]*(-(P[15][0]*powl(P[15][9],4.0)*(X[0]-P[15][4]))-(P[15][1]*powl(X[1],3.0)*P[15][8]*(X[0]-P[15][3]))-(P[15][2]*(X[0]-P[15][5]))+P[15][7]) );
 }

 long double Definicion_Usuario::Fn00150001(void)
 {
   return ( (((0.1*((25.0-X[0])/(expl((25.0-X[0])/10.0)-1.0))))*(1.0-X[1]))-(((4.0*expl(-X[0]/18.0)))*X[1]) );
 }

 long double Definicion_Usuario::Fn00160000(void)
 {
   return ( 1.0/P[16][6]*(-(P[16][0]*powl(X[1],4.0)*(X[0]-P[16][4]))-(P[16][1]*powl((((0.1*((25.0-X[0])/(expl((25.0-X[0])/10.0)-1.0))))/(((0.1*((25.0-X[0])/(expl((25.0-X[0])/10.0)-1.0))))+((4.0*expl(-X[0]/18.0))))),3.0)*(0.8-X[1])*(X[0]-P[16][3]))-(P[16][2]*(X[0]-P[16][5]))+P[16][7]) );
 }

 long double Definicion_Usuario::Fn00160001(void)
 {
   return ( (((0.01*((10.0-X[0])/(expl((10.0-X[0])/10.0)-1.0))))*(1.0-X[1]))-(((0.125*expl(-X[0]/80.0)))*X[1]) );
 }

 long double Definicion_Usuario::Fn00170000(void)
 {
   return ( X[0]*(P[17][0]+P[17][1]*X[0]+P[17][2]*X[1]) );
 }

 long double Definicion_Usuario::Fn00170001(void)
 {
   return ( X[1]*(P[17][3]+P[17][4]*X[0]+P[17][5]*X[1]) );
 }

 long double Definicion_Usuario::Fn00180000(void)
 {
   return ( X[1]-(((X[0]*X[0]*X[0])/P[18][0])-X[0]) );
 }

 long double Definicion_Usuario::Fn00180001(void)
 {
   return ( -P[18][2]*X[0]+P[18][1]*cosl(t) );
 }

 long double Definicion_Usuario::Fn00190000(void)
 {
   return ( ((1.0-X[0])*(P[19][0]+(X[0]*X[0]))-P[19][2]*X[1])*(X[0]*X[0]) );
 }

 long double Definicion_Usuario::Fn00190001(void)
 {
   return ( P[19][1]*(X[0]-X[1])*(P[19][0]+(X[0]*X[0]))*X[1] );
 }

 long double Definicion_Usuario::Fn00200000(void)
 {
   return ( 1 );
 }

 long double Definicion_Usuario::Fn00200001(void)
 {
   return ( X[1]-X[0]*X[0]+1 );
 }

 long double Definicion_Usuario::Fn00210000(void)
 {
   return ( 1 );
 }

 long double Definicion_Usuario::Fn00210001(void)
 {
   return ( 5*expl(5*X[0])*(X[1]-X[0])*(X[1]-X[0])+1 );
 }

 long double Definicion_Usuario::Fn00220000(void)
 {
   return ( P[22][0]-X[0]-((4.0*X[0]*X[1])/(1.0+X[0]*X[0])) );
 }

 long double Definicion_Usuario::Fn00220001(void)
 {
   return ( P[22][1]*X[0]+(1.0-(X[1]/(1.0+X[0]*X[0]))) );
 }

 long double Definicion_Usuario::Fn00230000(void)
 {
   return ( X[1] );
 }

 long double Definicion_Usuario::Fn00230001(void)
 {
   return ( -(P[23][0]+P[23][1]*cosl(X[2]))*X[0] );
 }

 long double Definicion_Usuario::Fn00230002(void)
 {
   return ( 1 );
 }

 long double Definicion_Usuario::Fn00240000(void)
 {
   return ( P[24][0]*X[0]+P[24][1]*X[1]+P[24][2]*X[2] );
 }

 long double Definicion_Usuario::Fn00240001(void)
 {
   return ( P[24][3]*X[0]+P[24][4]*X[1]+P[24][5]*X[2] );
 }

 long double Definicion_Usuario::Fn00240002(void)
 {
   return ( P[24][6]*X[0]+P[24][7]*X[1]+P[24][8]*X[2] );
 }

