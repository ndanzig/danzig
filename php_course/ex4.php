<html>
<head>
<title>My Fourth PHP Example</title>
</head>
<body>

<?php

$var="Global";   //Assign the value 'Global' to the variable $var 

print "Printing the $var scoped variable.\n<br>"; //use the variable

//write a function to change $var
function Test_1()
{
  $var="Local"; 
}
Test_1();

//did my function change $var?
print "Printing the $var scoped variable.\n<br>"; 

//write a better function to change $var
function Test_2()
{
  global $var;
  $var="Local"; 
}
Test_2();

//did my new function change $var?
print "Printing the $var scoped variable.\n<br>"; 

?>

</body>
</html>

