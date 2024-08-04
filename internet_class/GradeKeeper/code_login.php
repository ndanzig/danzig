<?php

include "code_master.php";

//master_redirect("index.php");

$connectionString = "Data Source=KAMIONER-LENOVO\\KAMIONERMSSQL05;Initial Catalog=GradeKeeper;Integrated Security=True";

function printLoginPage($username, $showErr)
{
	echo '
		<form action="" method="post">
			<table class="myTable" cellspacing="0" cellpadding="4" border="1">
				<tr class="header">
					<th scope="col" colspan="2">Login</th>
				</tr>
				
		
		
				<tr class="normalrow">
					<td>Username:</td>
					<td><input type="text" name="username" id="username" value="' . $username . '"></td>
				</tr>
				<tr class="normalrow_alt">
					<td>Password</td>
					<td><input type="password" name="password" id="password"></td>
				</tr>
				<tr class="normalrow">
					<td colspan="2">
					<input type="hidden" name="action" id="action" value="login" />
					<input type="submit" value="login" id="btnLogin" style="display: none;">
					<a style="background-image: url(\'images/icon_login.gif\');" class="specialLink" href="javascript:document.getElementById(\'btnLogin\').click();">Login</a> ';
			
	if($showErr)
		echo '<span style="color: red">Invalid Login</span>';
	
	echo'
		</td>
		</tr>
		</table></form>';
}



function checkLogin($Username, $Password)
{
	//$SQL = "SELECT UserID, Password FROM Users WHERE Username = '" . $Username . "'";
	$SQL = "SELECT UserID, Password FROM Users WHERE Username = '" . $Username . "'";
	$result = runSQLQuery($SQL, true);
	if(sizeof($result) == 1)
	{
		if($result[0]["Password"] == $Password)
			return $result[0]["UserID"];
	}
	return -1;

	
	


}




?>