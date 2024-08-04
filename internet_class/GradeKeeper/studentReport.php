<?php
include "code_master.php";
session_start(); 
$UserID = $_SESSION["UserID"];
if(!isset($_SESSION["UserID"]) || $_SESSION["UserID"] == -1 || !is_numeric($_GET["SID"]))
	master_redirect("index.php");
$studentID = $_GET["SID"];

$SQL = "SELECT FirstName, LastName FROM Students WHERE StudentID = " . $studentID;
$studentDetails = runSQLQuery($SQL, true);
$firstName = $studentDetails[0]["FirstName"];
$lastName = $studentDetails[0]["LastName"];

master_printHeader("GradeKeeper :: Student Report");

echo '<h1>' . $lastName . ", " . $firstName . '</h1>';


echo '<h3 style="font-style: italic; color: Gray;">Classes & Final Grades</h3>
<table border="0" style="font-size: 12pt;">
	    <tr style="font-size: 10pt;">
	        <th style="border: 1px dotted gray">Course</th>
			<th style="border: 1px dotted gray">Grade</th>
			<th style="border: 1px dotted gray"></th>
		</tr>';

$SQL = "SELECT c.ClassID, c.PassingGrade, c.Name FROM Classes_Students AS cs INNER JOIN Classes AS c ON c.ClassID = cs.ClassID WHERE cs.StudentID = ". $studentID;
$classes = runSQLQuery($SQL, true);
$averageGrade = 0;
for($i = 0; $i < sizeof($classes); $i++)
{
	$classID = $classes[$i]["ClassID"];
	$SQL = "SELECT SUM(PointValue) FROM Assignments WHERE ClassID = " . $classID;
	$totalPoints = runSQLQueryScalar($SQL);
	$SQL = "SELECT CAST(SUM((CAST(csa.Grade AS decimal(9,5)) * 100.0) / CAST(a.MaxGrade AS decimal(9,5)) * CAST(a.PointValue AS decimal(9,5)) / " . $totalPoints  . ".0 ) AS decimal(9,2))
			FROM Classes_Students_Assignments AS csa
			INNER JOIN Assignments AS a
			ON a.AssignmentID = csa.AssignmentID
			WHERE csa.StudentID = " . $studentID . "
			AND csa.ClassID = " . $classID;
	$totalGrade = runSQLQueryScalar($SQL);	
	
	echo '<tr>';
	echo '<td style="font-weight: bold; border: 1px dotted gray;">' . $classes[$i]["Name"] . '</td>';
	echo '<td style="padding-left: 10px; padding-right: 10px; text-align: center; border: 1px dotted gray;">' . $totalGrade . '</td>';
	
	if($totalGrade < $classes[$i]["PassingGrade"])
		echo '<td style="padding-left: 10px; padding-right: 10px; text-align: center; border: 1px dotted gray;"><b>Fail</b></td>';
	else
		echo '<td style="padding-left: 10px; padding-right: 10px; text-align: center; border: 1px dotted gray;">Pass</td>';
	
	
	echo '</tr>';
	
	$averageGrade += $totalGrade;
}

echo '</table>
		
		
		<br /><br />
		<b>Average Grade: </b>' . ($averageGrade / sizeof($classes)) . '
		
		<br /><br/>
		<i>Student Report from GradeKeeper.com</i>
		
		
		';
		
			


			


master_printFooter();
?>

