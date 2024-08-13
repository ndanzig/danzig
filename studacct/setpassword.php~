<html>
<head><META HTTP-EQUIV="Content-Type"   CONTENT="text/html; CHARSET=iso8859-8-i" >
 </head>
<body>
<?php
$fail=0;
if(isset($_SESSION['hissecret']))
{
$secret = $_SESSION['hissecret'];
}
else
{
echo "<b>Secret not set.</b><br>";
$fail=1;
}


if(isset($_SESSION['hislogin']))
{
$secret = $_SESSION['hislogin'];
}
else
{
echo "<b>Login not set.</b><br>";
$fail=1;
}

@extract($_POST);
$passwd= stripslashes($passwd);
$proxy = stripslashes($proxy);
$passwd = rtrim($passwd);//remove whitespaces 
$proxy = rtrim($proxy);//remove whitespaces 

echo "The Main Password you selected is <b>$passwd.</b><br>";
echo "The Internet Proxy Password you selected is <b>$proxy.</b><br>";

if (strcmp($passwd, $proxy) == 0)
{
echo "<b>Passwords must be different</b><br>";
$fail=1;

}
if (strlen($passwd) != 8)
{
echo "<b>Main Password must be 8 letters long.</b><br>";
$fail=1;

}
if (strlen($proxy) != 8)
{
echo "<b>Proxy Password must be 8 letters long.</b><br>";
$fail=1;
}
if (! ereg ( "[0-9]", $passwd ))
{
echo "<b>Main Password must contain at least one numerical digit.</b><br>";
$fail=1;
}
if ( !ereg ( "[0-9]", $proxy ))
{
echo "<b>Proxy Password must contain at least one numerical digit.</b><br>";
$fail=1;
}

if (! ereg ( "[a-z]", $passwd ))
{
echo "<b>Main Password must contain at least one lowercase letter.</b><br>";
$fail=1;
}
if ( !ereg ( "[a-z]", $proxy ))
{
echo "<b>Proxy Password must contain at least one lowercase letter.</b><br>";
$fail=1;
}
if (! ereg ( "[A-Z]", $passwd ))
{
echo "<b>Main Password must contain at least one CAPITAL letter.</b><br>";
$fail=1;
}
if ( !ereg ( "[A-Z]", $proxy ))
{
echo "<b>Proxy Password must contain at least one CAPITAL letter.</b><br>";
$fail=1;
}


echo "<br> fail is $fail" ;





?>
</body>
</html>