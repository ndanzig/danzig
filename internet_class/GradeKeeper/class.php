<?php
include "code_class.php";
session_start(); 


$UserID = $_SESSION["UserID"];
if(!isset($_SESSION["UserID"]) || $_SESSION["UserID"] == -1)
	master_redirect("index.php");
	
$classID = $_GET["CID"];
$SQL = "SELECT COUNT(*) AS TheCount FROM Classes WHERE ClassID = " . $classID . " AND UserID = " . $UserID;
$result = runSQLQuery($SQL, true);
if($result[0]["TheCount"] != 1)
	master_redirect("main.php");

$action = $_POST["action"];
if($action == "updateGrade" && is_numeric($_POST["grade"]))
{
	$SQL = "UPDATE Classes_Students_Assignments SET Grade = " . $_POST["grade"] . " WHERE ClassID = " . $_POST["classID"] . " AND StudentID = " . $_POST["studentID"] . " AND AssignmentID = " . $_POST["assignmentID"];
	runSQLNonQuery($SQL);
}
if($action == "updateClassName")
{
	$newClassName = $_POST["className"];
	$newClassName = makeSafe($newClassName);
	$SQL = "UPDATE Classes SET Name = '" . $newClassName . "' WHERE ClassID = " . $classID;
	runSQLNonQuery($SQL);
}
if($action == "addNewStudent")
{
	$newStudentID = -1;
	$newStudentID = $_POST["studentID"];
	if($_POST["addNewStudentOption"] != "existingStudent")
	{
		if($newStudentID == -1)
		{
			$firstName = makeSafe($_POST["firstName"]);
			$lastName = makeSafe($_POST["lastName"]);
			
			$SQL = "INSERT INTO Students (FirstName, LastName) VALUES ('" . $firstName . "', '" . $lastName . "');";
	
			$newStudentID = runSQLQueryWithIdentity($SQL, false);
		}
	}
	
	//$SQL = "INSERT INTO Classes_Students (ClassID, StudentID) VALUES (" . $classID . ", " . $newStudentID . ");";
	$SQL = "INSERT INTO Classes_Students (ClassID, StudentID) VALUES ('" . $classID . "', '" . $newStudentID . "');";
	runSQLNonQuery($SQL);
	
	$SQL = "SELECT AssignmentID FROM Assignments WHERE ClassID = " . $classID;
	$assignments = runSQLQuery($SQL, true);
	for($i = 0; $i < sizeof($assignments); $i++)
	{
		$SQL = "INSERT INTO Classes_Students_Assignments (ClassID, StudentID, AssignmentID, Grade) VALUES (" . $classID . ", " . $newStudentID . ", " . $assignments[$i]["AssignmentID"] . ", 0);";
		
		runSQLNonQuery($SQL);
	}
	
}
if($action == "deleteStudent")
{
	$studentID = $_POST["studentID"];
	if(is_numeric($studentID))
	{
		$SQL = "DELETE FROM Classes_Students_Assignments WHERE StudentID = " . $studentID;
		runSQLNonQuery($SQL);
		$SQL = "DELETE FROM Classes_Students WHERE StudentID = " . $studentID;
		runSQLNonQuery($SQL);
	}
}
if($action == "updatePassingGrade" && is_numeric($_POST["passingGrade"]))
{
	$newPassingGrade = $_POST["passingGrade"];
	$SQL = "UPDATE Classes SET PassingGrade = " . $newPassingGrade . " WHERE ClassID = " . $classID;
	runSQLNonQuery($SQL);
}
if($action == "updateAssignment" && is_numeric($_POST["assignmentID"]) && is_numeric($_POST["assignmentMaxGrade"]) && is_numeric($_POST["assignmentPointValue"]))
{
	$assignmentID = $_POST["assignmentID"];
	$assignmentName = $_POST["assignmentName"];
	$assignmentMaxGrade = $_POST["assignmentMaxGrade"];
	$assignmentPointValue = $_POST["assignmentPointValue"];
	
	$assignmentName = makeSafe($assignmentName);
	
	$SQL = "UPDATE Assignments SET Name = '" . $assignmentName . "', MaxGrade = " . $assignmentMaxGrade . ", PointValue = " . $assignmentPointValue . " WHERE AssignmentID = " . $assignmentID;
	runSQLNonQuery($SQL);
}
if($action == "addNewAssignment" && is_numeric($_POST["assignmentMaxGrade"]) && is_numeric($_POST["assignmentPointValue"]))
{
	$assignmentName = $_POST["assignmentName"];
	$assignmentMaxGrade = $_POST["assignmentMaxGrade"];
	$assignmentPointValue = $_POST["assignmentPointValue"];
	
	$SQL = "INSERT INTO Assignments (ClassID, Name, PointValue, MaxGrade) VALUES (" . $classID . ", '" . makeSafe($assignmentName) . "', " . $assignmentPointValue . ", " . $assignmentMaxGrade . ")";
	
	$assignmentID = runSQLQueryWithIdentity($SQL);
	
	$SQL = "SELECT StudentID FROM Classes_Students WHERE ClassID = " . $classID;
	$allStudents = runSQLQuery($SQL, true);
	
	for($i = 0; $i < sizeof($allStudents); $i++)
	{
		$SQL = "INSERT INTO Classes_Students_Assignments (ClassID, StudentID, AssignmentID, Grade) VALUES (" . $classID . ", " . $allStudents[$i]["StudentID"] . ", " . $assignmentID . ",0)";
		runSQLNonQuery($SQL);
	}
}
if($action == "deleteAssignment" && is_numeric($_POST["assignmentID"]))
{
	$assignmentID = $_POST["assignmentID"];
	$SQL = "DELETE FROM Classes_Students_Assignments WHERE AssignmentID = " . $assignmentID;
	runSQLNonQuery($SQL);
	$SQL = "DELETE FROM Assignments WHERE AssignmentID = " . $assignmentID;
	runSQLNonQuery($SQL);
}





$studentID = -1;
if(is_numeric($_GET["SID"]))
{
	$studentID = $_GET["SID"];
}










master_printHeader("GradeKeeper :: View Class");
printClassPage($classID, $studentID);
master_printFooter();


?>