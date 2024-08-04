<?php
include "code_main.php";
session_start(); 


$UserID = $_SESSION["UserID"];
if(!isset($_SESSION["UserID"]) || $_SESSION["UserID"] == -1)
	master_redirect("index.php");

$action = $_POST["action"];
if($action == "deleteClass")
{
	$deleteClassID = $_POST["deleteClassID"];
	runSQLNonQuery("DELETE FROM Classes_Students_Assignments WHERE ClassID = " . $deleteClassID);
	runSQLNonQuery("DELETE FROM Classes_Students WHERE ClassID = " . $deleteClassID);
	runSQLNonQuery("DELETE FROM Classes WHERE ClassID = " . $deleteClassID);
}
if($action == "addNewClass")
{
	$newClassName = $_POST["className"];
	$passingGrade = $_POST["passingGrade"];
	if($newClassName != "" && is_numeric($passingGrade))
	{
		$newClassName = makeSafe($newClassName);
		//$SQL = "INSERT INTO Classes (ClassID, Name, UserID, PassingGrade) VALUES (NULL, '" . $newClassName . "', " . $_SESSION["UserID"] . ", " . $passingGrade . ");";
		$SQL = "INSERT INTO Classes (Name, UserID, PassingGrade) VALUES ('" . $newClassName . "', '" . $_SESSION["UserID"] . "', '" . $passingGrade . "');";
		runSQLNonQuery($SQL);
	}
}



master_printHeader("GradeKeeper :: Main");
printMainPage();
master_printFooter();


?>