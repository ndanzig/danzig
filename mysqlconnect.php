<?php
/*  ob_start();
print "hello";
function master_redirect($newURL)
{
	header('Location:' . $newURL);
}
master_redirect("http://www.huji.ac.il");
*/

$serverName = "98.130.0.73";
$serverName = "mysql406.ixwebhosting.com";
	$username = "Kamione_User9";
	$password = "sp1nAch";
	$dbName = "Kamione_IP9";
	$ret = array();

/*1*/	     $connection = mysql_connect($serverName, $username, $password) or die("HELP! BAD CONNECTION");
/*2 */	     mysql_select_db($dbName);
/*3*/        $sql= "SELECT * from students";

/*4*/  $ret = mysql_query($sql, $connection)  or die("HELP! BAD SQL = '" . $SQL . "'");

/*5*/  $data= mysql_result($ret,1,0);
/*6*/ print "&nbsp; $data";	

/*5*/  $data= mysql_result($ret,1,1);
/*6*/ print "&nbsp; $data";	

/*5*/  $data= mysql_result($ret,1,2);
/*6*/ print "&nbsp; $data";	
	

mysql_close($connection);
?>
