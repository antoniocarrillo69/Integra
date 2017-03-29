<?php
   $string = implode(" ",$_SERVER["argv"]);
   $arr = explode("_",$string);
   $string = implode($arr," ");
   $im = imagecreate(190,20);
   $Fondo = ImageColorAllocate($im, 179, 201, 206);
   $Texto = ImageColorAllocate($im,0,0,0);
   ImageString($im,3,5,3,$string,$Texto);
   Header("Content-type: image/PNG");
   ImagePNG($im);
   ImageDestroy($im);
?>

