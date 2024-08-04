<?php
@extract($_POST);
$name = stripslashes($name);
$email = stripslashes($email);
$subject = stripslashes($subject);
$text = stripslashes($text);
mail('danzig@jct.ac.il',$subject,$text,"From: $name <$email>");
header("location:mailform.html");
?>
