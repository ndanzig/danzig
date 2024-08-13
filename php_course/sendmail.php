<?php
print "<html>";
print '<head> <META HTTP-EQUIV="CONTENT-TYPE" CONTENT="TEXT/HTML; CHARSET=WINDOWS-1255">';
print "</head>";

$name = $_POST["username"];
$sub="testmessage";
$message="
Name: $name ";
mail("danzig@jct.ac.il",$sub,$message,"From: ESP Feedback <apache@cc.jct.ac.il>\n");

print "<body>";
print " Hello $name again. We sent mail to danzig.";
print "</body>";
print "<html>";

?>