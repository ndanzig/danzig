<?php

session_start();
include "code_login.php";

if(isset($_SESSION["UserID"]))
	$_SESSION["UserID"] = null;

if($_POST["action"] == "login")
{
	$username = $_POST["username"];
	$password = $_POST["password"];
	$UserID = checkLogin($username, $password);
	if($UserID == -1)
	{
		master_printHeader("GradeKeeper :: Login");
		printLoginPage($username, true);
		master_printFooter();
	}
	else
	{
		$_SESSION["UserID"] = $UserID;
		master_redirect("main.php");
	}
}
elseif(!isset($_SESSION["UserID"]) || !isset($_POST["action"]))
{
	master_printHeader("GradeKeeper :: Login");
	printLoginPage('', false);
	master_printFooter();
}	
?>