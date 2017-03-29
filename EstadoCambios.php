<html>
<head>
   <title>INTEGRA C++</title>
</head>
<body text="#000000" bgcolor="#FFFFFF" link="#000066" vlink="#666666" alink="#000066" 
background="/acl/Imagenes/Fondo.gif" nosave bgproperties="fixed">


<CENTER><TABLE COLS=1 WIDTH=350><TD BGCOLOR=#D6D0AB><B><CENTER><font size=+2>
Estado de Cambios
</font></CENTER></b></td></table></CENTER>


<br><br><br>
<b>
Versi&oacute;n 1.0.0
<br><br>
<ul>
INTERFAZ del sistema INTEGRA WINDOWS / C++
<ul>
<li>Soporte para perturbar las condiciones iniciales antes y/o despues de integrar <i>(se adicion&oacute;)</i></li>
<li>Soporte para perturbar las condiciones iniciales al tiempo Ti o m&uacute;ltiplos de este <i>(se adicion&oacute;)</i></li>
<li>Definici&oacute;n y edici&oacute;n de ecuaciones homog&eacute;neas y no homog&eacute;neas de segundo orden <i>(se adicion&oacute;)</i></li>
<li>Definici&oacute;n y edici&oacute;n de ecuaciones homog&eacute;neas y no homog&eacute;neas de primer orden <i>(se adicion&oacute;)</i></li>
<li>Validaci&oacute;n de las funciones capturadas incluyendo las del codigo en C++ <i>(se adicion&oacute;)</i></li>
<li>Error en la validaci&oacute;n de la captura de los par&aacute;metros del sistema <i>(se corrigi&oacute;)</i></li>
<li>Borrado de sistemas dentro del proyecto <i>(se corrigi&oacute;)</i></li>
<li>Redise&ntilde;o de la estructura de proyectos para poder soportar:</li>
<ul>
<li>Cada proyecto puede contener hasta 100 sistemas <i>(se adicion&oacute;)</i></li>
<li>Cada sistema puede tener hasta 1000 ecuaciones diferenciales <i>(se adicion&oacute;)</i></li>
<li>Cada sistema puede tener hasta 500 par&aacute;metros <i>(se adicion&oacute;)</i></li>
<li>Definici&oacute;n de ecuaciones diferenciales por partes usando codigo en C++ <i>(se adicion&oacute;)</i></li>
</ul>
</ul>
</ul>
<br>

<ul>
Ejecutables que se solicitan por medio de la INTERFAZ
<ul>
<li><b>C&aacute;lculo de isoclinas</b> <i>(se corrigi&oacute;)</i></li>
<li><b>C&aacute;lculo del per&iacute;odo de una trayectoria cerrada</b> <i>(se adicion&oacute;)</i></li>
<li><b>C&aacute;lculo del mapeo del per&iacute;odo</b> <i>(se adicion&oacute;)</i></li>
<li><b>C&aacute;lculo de equilibrios primera versi&oacute;n</b> <i>(se adicion&oacute;)</i></li>
<li>M&eacute;todos de integraci&oacute;n n&uacute;merica:
<ul>
<li><b>Euler (1er orden)</b> <i>(se optimiz&oacute;)</i></li>
<li><b>Euler modificado (2do orden)</b> <i>(se optimiz&oacute;)</i></li>
<li><b>Punto medio (2do orden)</b> <i>(se optimiz&oacute;)</i></li>
<li><b>Heun (2do orden)</b> <i>(se optimiz&oacute;)</i></li>
<li><b>Runge-Kutta I (3 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta II (3 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Formula 3/8 (4 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta Cl&aacute;sico (4 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Gill (4 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>England (4 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Fehlberg (4 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Fehlberg I (5 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>England (5 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Kutta-Nyström (5 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Fehlberg II (5 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Butcher (6 order)</b>  <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Fehlberg de paso variable (5/4 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Runge-Kutta-Verner de paso variable (6/5 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Adams-Bashforth (2 pasos)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Adams-Bashforth (3 pasos)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Adams-Bashforth (4 pasos)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Adams-Bashforth (5 pasos)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Milne (3 pasos)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector  (Adams-Bashforth-Moulton 3 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector  (Adams-Bashforth-Moulton 4 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector  (Adams-Bashforth-Moulton 5 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector  (Milne-Simpson 3 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector de paso variable (Adams-Bashforth-Moulton 3 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector de paso variable (Adams-Bashforth-Moulton 4 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Predictor-Corrector de paso variable (Adams-Bashforth-Moulton 5 orden)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Trapecio (A-estable iteraciones por secante)</b> <i>(se adicion&oacute;)</i></li>
<li><b>Euler regresivo (A-estable iteraciones por secante)</b> <i>(se adicion&oacute;)</i></li>

</ul>
<li>Movimiento del cursor seleccionador de condiciones iniciales <i>(se optimiz&oacute;)</i></li>
<li>Soporte de colores de 24 bits <i>(se adicion&oacute;)</i></li>
<li>Control de errores al calcular el campo vectorial y direccional <i>(se adicion&oacute;)</i>
<br>(donde no estan definidas las ecuaciones diferenciales)</li> 
<li>Captura de condiciones iniciales incluyendo al tiempo <i>(se corrigi&oacute;)</i></li>
<li>Captura de configuraci&oacute;n de campo vectorial y direccional <i>(se corrigi&oacute;)</i></li>
<li>Selecci&oacute;n de condiciones iniciales en ejes en coordenadas polares <i>(se corrigi&oacute;)</i></li>
<li>Rotaci&oacute;n de ejes coordenados en tres dimensiones <i>(se adicion&oacute;)</i></li>
<li>Graba y restaura la configuraci&oacute;n del sistema activo <i>(se adicion&oacute;)</i></li>
<li>Graba y restaura la configuraci&oacute;n de todos los sistemas  <i>(se adicion&oacute;)</i></li>
<li>Graba el resultado de las integraciones n&uacute;mericas <i>(se adicion&oacute;)</i></li>
<li>C&aacute;lculo y graficaci&oacute;n del campo vectorial <i>(se corrigi&oacute;)</i></li>
<li>C&aacute;lculo y graficaci&oacute;n del campo direccional <i>(se adicion&oacute;)</i></li>
<li>C&aacute;lculo de ceroclinas e isoclinas <i>(se corrigi&oacute;)</i></li>
<li>Deficici&oacute;n y c&aacute;lculo de funciones auxiliares <i>(se optimiz&oacute;)</i></li>
<li>Tipo de ventana</li>
<ul>
<li>Ejes en dos dimensiones</li>
<ul>
<li>Ejes coordenados <i>(se redise&ntilde;o)</i></li>
<li>Ejes coordenados modificados <i>(se adicion&oacute;)</i></li>
<li>Caja <i>(se redise&ntilde;o)</i></li>
<li>Coordenadas polares <i>(se adicion&oacute;)</i></li>
</ul>
<li>Ejes en tres dimensiones</li>
<ul>
<li>Ejes coordenados <i>(se redise&ntilde;o)</i></li>
<li>Caja <i>(se redise&ntilde;o)</i></li>
</ul>
</ul>
<li>Escenario gr&aacute;fico</li>
<ul>
<li>Multiples escenarios se gr&aacute;fican simultaneamente en uno solo <i>(se adicion&oacute;)</i></li>
</ul>
</ul>
</ul>
</ul>


</b>


<?php
   include("FechaActualizacion.txt");
?>


</body>
</html>
