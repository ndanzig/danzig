
<html>
<head><title> Initial Logon to JCT</title>
<META HTTP-EQUIV="Content-Type"   CONTENT="text/html; CHARSET=iso8859-8-i" > 

</head>
<body>
<?php

if( isset($_GET["fail"] ))
{
echo "<font color=red> Make sure to copy names and secret <b>exactly</b> as they appear on the form you received.</font>";

}
?>

<form  action="choosepasswd.php" method="POST">
<h2>Welcome to JCT Password Distributer</h2>
<p>Please read these laws of the State of Israel regarding Internet use.
Then, click on accept so you can get your password. <br>
<iframe src="http://www.knesset.gov.il/laws/heb/FileD.asp?Type=1&SubNum=1&LawNum=1534&menu=folded-3-3-1" width=80% height=80%> hidden text </iframe> 

<p> I accept <input type=checkbox name=israeliLaw value=yes> <p>
<br><p>Please read these laws of the JCT Computer Center.
Then, click on accept so you can get your password. <br>
</p>
<iframe src="rules.html" width=80% height=90%> hidden text </iframe>
<p> I accept <input type=checkbox name=rules value=yes> <p>





<h3>Please Enter your First and Last names and secret code as they appear on the form you received from the mazkirut </h3>

Hebrew First Name: 
<input type="text" name="fname" size="20" maxlength="20"  /><br />
Hebrew Last Name: 
<input type="text" name="last" size="20" maxlength="20" /><br />
Secret: 
<input type="text" name="secret" size="30" maxlength="30"  /><br />
<br />
<input type="submit"  value="Send" />



</form>
</body>
</html>