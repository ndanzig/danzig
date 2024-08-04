<?php
include "code_master.php";

function printClassPage($classID, $selectedStudentID)
{
	$SQL = "SELECT c.Name, COUNT(cs.StudentID) AS StudentCount, PassingGrade
			FROM Classes AS c
			LEFT JOIN Classes_Students AS cs
			ON cs.ClassID = c.ClassID
			WHERE c.ClassID = " . $classID . "
			GROUP BY c.Name, c.PassingGrade";
	$result = runSQLQuery($SQL, true);
	$className = $result[0]["Name"];
	
	if($selectedStudentID == -1)
		$studentCount = $result[0]["StudentCount"];
	else
		$studentCount = 1;
	$passingGrade = $result[0]["PassingGrade"];
	
	$SQL = "SELECT AssignmentID, Name, PointValue, MaxGrade, (PointValue * 100) / (SELECT SUM(PointValue) FROM Assignments WHERE ClassID = " . $classID . ") AS PointPercentage FROM Assignments WHERE ClassID = " . $classID;
	$assignmentResults = runSQLQuery($SQL, true);
	
	$assignmentCount = sizeof($assignmentResults);
	

	echo '
	
	
	
	
	<a href="main.php">Back to main</a>
	
	
			<br /><br />
	
	
	
	
	
	
	
	<table class="myTable" cellspacing="0" cellpadding="4" border="1">
			
			
			<tr class="header"><form action="" method="post">
			<th scope="col" colspan="' . ($assignmentCount + 3) . '">
			<span id="spnViewClassName">' . $className . ' <a href="javascript:document.getElementById(\'txtClassName\').value = className;ShowItem(\'spnEditClassName\');HideItem(\'spnViewClassName\');" style="text-decoration: none"><img src="images/icon_edit.gif" border="0" /></a></span>
			<span id="spnEditClassName" style="display: none">
			
			<input type="hidden" name="action" value="updateClassName" />
			<input type="text" name="className" id="txtClassName" value="' . releaseSafety($className) . '" />
			<input type="submit" id="btnSubmitUpdateClassName" style="display: none" />
			<a href="javascript:document.getElementById(\'btnSubmitUpdateClassName\').click();" style="text-decoration: none"><img src="images/icon_save.gif" border="0" /></a>
			<a href="javascript:HideItem(\'spnEditClassName\');ShowItem(\'spnViewClassName\');" style="text-decoration: none"><img src="images/icon_cancel.gif" border="0" /></a>
			
			</span>
			</th></form>
			</tr>
			
			<tr>
			<td valign="bottom" rowspan="2"><embed type="application/x-silverlight" id="scAssignment_gradesummart" width="60" height="125" background="white" source="silverlight.php?text=' . urlencode('Student Name') . '&angle=-60&cleft=0&ctop=115"></td>';
	for($i = 0; $i < $assignmentCount; $i++)
	{
		echo '<td>';
		
		echo '<embed type="application/x-silverlight" id="scAssignment_' . $assignmentResults[$i]["AssignmentID"] . '" width="20" height="125" background="white" source="silverlightAssignmentName.php?AID=' . urlencode($assignmentResults[$i]["AssignmentID"]) . '">';
		
		echo '</td>';
	}		
	
				
	echo '  	<td valign="bottom"><embed type="application/x-silverlight" id="scAssignment_gradesummart" width="60" height="125" background="white" source="silverlight.php?text=' . urlencode('Grade Summary') . '&angle=-60&cleft=0&ctop=115"></td>
			<td rowspan="2"></td>
			
			
			</tr>
			
			<tr>
			
			';
	
	for($i = 0; $i < $assignmentCount; $i++)
	{
		echo '<td height="20" align="center">';
		
		//echo '<a href="#" style="text-decoration: none"><img src="images/icon_edit.gif" border="0" /></a>';
		echo '<span style="font-size: 8pt">' . $assignmentResults[$i]["MaxGrade"] . '<br />%';
		
		
		echo floatval(floor($assignmentResults[$i]["PointPercentage"] * 100)) / 100;
		
		echo '</span>';
		echo '</td>';
	}
	
	echo '
			<form action="" method="post">
			<td style="font-size: 8pt">
			<span id="spnViewPassingGrade">
			Pass: ' . $passingGrade . ' 
			<a href="javascript:document.getElementById(\'txtPassingGrade\').value = passingGrade;className;ShowItem(\'spnEditPassingGrade\');HideItem(\'spnViewPassingGrade\');" style="text-decoration: none">
			<img src="images/icon_edit.gif" border="0" />
			</a>
			</span>
			<span id="spnEditPassingGrade" style="display: none">
			
			<input type="hidden" name="action" value="updatePassingGrade" />
			Pass: <input type="text" name="passingGrade" id="txtPassingGrade" value="' . $passingGrade . '" style="font-size: 8pt; width: 30px;" />
			<input type="submit" id="btnSubmitUpdatePassingGrade" style="display: none" />
			<a href="javascript:document.getElementById(\'btnSubmitUpdatePassingGrade\').click();" style="text-decoration: none"><img src="images/icon_save.gif" border="0" /></a>
			<a href="javascript:HideItem(\'spnEditPassingGrade\');ShowItem(\'spnViewPassingGrade\');" style="text-decoration: none"><img src="images/icon_cancel.gif" border="0" /></a>
			
			</span>
	
	</td>
	
	</form>';
	
	
	
	
	
	echo '</tr>';
	
	$SQL = "SELECT s.StudentID, s.LastName, s.FirstName, 0 AS Grade 
			FROM Students AS s
			LEFT JOIN Classes_Students AS cs
			ON cs.StudentID = s.StudentID
			WHERE cs.ClassID = " . $classID;
	if($selectedStudentID != -1)
		$SQL .= " AND s.StudentID = " . $selectedStudentID;
			
	$SQL .= " ORDER BY s.LastName, s.FirstName";
	$studentResults = runSQLQuery($SQL, true);
	
	
	
	echo '
			
			<script language="javascript">
			
			var className = "' . releaseSafety($className) . '";
			var passingGrade = ' . $passingGrade . ';
			';
			
	
	echo 'var assignments = new Array();
				
';
	for($i = 0; $i < $assignmentCount; $i++)
	{
		echo 'assignments[' . $i . '] = ' . $assignmentResults[$i]["AssignmentID"] . ';
				';
	}
	
	echo 'var students = new Array();
			
			';
	for($i = 0; $i < $studentCount; $i++)
	{
		echo 'students[' . $i . '] = ' . $studentResults[$i]["StudentID"] . ';
				';
	}
	
	
	
	
	echo '
			
			var classID = ' . $classID . ';
			
			function ShowEdit(studentID, assignmentID)
			{
				for(i = 0; i < students.length; i++)
				{
					for(j = 0; j < assignments.length; j++)
					{
						HideEdit(students[i], assignments[j]);
					}
				}
				HideItem("spnView_" + studentID + "_" + assignmentID);
				ShowItem("spnEdit_" + studentID + "_" + assignmentID);
			}
			function HideEdit(studentID, assignmentID)
			{
				ShowItem("spnView_" + studentID + "_" + assignmentID);
				HideItem("spnEdit_" + studentID + "_" + assignmentID);
			}
			function SubmitGrade(grade, studentID, assignmentID)
			{
				document.getElementById(\'txtStudentID\').value = studentID;
				document.getElementById(\'txtAssignmentID\').value = assignmentID;
				document.getElementById(\'txtClassID\').value = classID;
				document.getElementById(\'txtGrade\').value = grade;
				document.getElementById(\'btnSubmitChangeGrade\').click();
			}
			function HideItem(itemID)
			{
			document.getElementById(itemID).style.display = \'none\';
			}
			function ShowItem(itemID)
			{
			document.getElementById(itemID).style.display = \'block\';
			}
			
			</script>
			
			
			
			';
	
	
	
	for($studentIndex = 0; $studentIndex < $studentCount; $studentIndex++)
	{
		$studentID = $studentResults[$studentIndex]["StudentID"];
		
		$SQL = "SELECT SUM(PointValue) FROM Assignments WHERE ClassID = " . $classID;
		$totalPoints = runSQLQueryScalar($SQL);
		
		$SQL = "SELECT CAST(SUM((CAST(csa.Grade AS decimal(9,2)) * 100.0) / CAST(a.MaxGrade AS decimal(9,2)) * CAST(a.PointValue AS decimal(9,2)) / " . $totalPoints  . ".0 ) AS decimal(9,2))
				FROM Classes_Students_Assignments AS csa
				INNER JOIN Assignments AS a
				ON a.AssignmentID = csa.AssignmentID
				WHERE csa.StudentID = " . $studentID . "
				AND csa.ClassID = " . $classID;
		$totalGrade = runSQLQueryScalar($SQL);		
	
		
		if($totalGrade < $passingGrade)
			echo '<tr class="normalrow_failing">';
		elseif ($studentIndex % 2 == 0)
			echo '<tr class="normalrow_alt">';
		else
			echo '<tr class="normalrow">';
			
		
		echo '<td><b>' . $studentResults[$studentIndex]["LastName"] . ', ' . $studentResults[$studentIndex]["FirstName"] . '</b></td>';
		
		
		
		
		for($i = 0; $i < $assignmentCount; $i++)
		{
			$assignmentID = $assignmentResults[$i]["AssignmentID"];
			echo '<td align="center">';
			
			$SQL = "SELECT Grade FROM Classes_Students_Assignments
			WHERE ClassID = " . $classID . "
					AND StudentID = " . $studentID . "
					AND AssignmentID = " . $assignmentID;
			
			$temp = runSQLQuery($SQL, true);
			
			echo '
			
					<span id="spnView_' . $studentID . '_' . $assignmentID . '" onclick="javascript:ShowEdit(' . $studentID . ',' . $assignmentID . ');" style="cursor: hand;">
					' . $temp[0]["Grade"] . '
					</span>
					<span id="spnEdit_' . $studentID . '_' . $assignmentID . '" style="display: none">
					<input type="text" value="' . $temp[0]["Grade"] . '" style="width: 30px" id="txtGrade_' . $studentID . '_' . $assignmentID . '" />
					
					<a href="javascript:SubmitGrade(document.getElementById(\'txtGrade_' . $studentID . '_' . $assignmentID . '\').value,' . $studentID . ',' . $assignmentID . ');" style="text-decoration: none"><img src="images/icon_save.gif" border="0"/></a>
					<a href="javascript:HideEdit(' . $studentID . ',' . $assignmentID . ');" style="text-decoration: none"><img src="images/icon_cancel.gif" border="0"/></a>
        </span>
		
			';
			
			
			echo '</td>';
		}
		
		echo '<td align="center"><b>' . $totalGrade. '</b></td>
		
		
		
		
		<td>
				
				
				
				';
		
		if($selectedStudentID == -1)
		{
			echo '<a href="?CID=' . $classID . '&SID=' . $studentID . '" style="text-decoration: none;">
					<img src="images/icon_zoomin.gif" border="0" />
					</a>';
		}
		else
		{
			echo '<a href="?CID=' . $classID . '&SID=-1" style="text-decoration: none;">
					<img src="images/icon_zoomout.gif" border="0" />
					</a>';
		}
		
		echo '
				
				
				<a href="studentReport.php?SID=' . $studentID . '" style="text-decoration: none;">
				<img src="images/icon_report.gif" border="0" />
				</a>
		
		<a href="javascript:deleteStudent(' . $studentID . ')" style="text-decoration: none;">
				<img src="images/icon_delete.gif" border="0" />
				</a>';
		
		
		echo'</td>';
		echo '</tr>';
	}
	echo '</table>';
	
	
	
	
	
	
	
	
	
	
	
	echo '
	
	
	
	
	
			<script language="javascript">
			function addNewAssignment(name, maxGrade, points)
			{
			document.getElementById(\'assignments_action\').value = \'addNewAssignment\';
			document.getElementById(\'assignments_id\').value = -1;
			document.getElementById(\'assignments_name\').value = name;
			document.getElementById(\'assignments_maxGrade\').value = maxGrade;
			document.getElementById(\'assignments_points\').value = points;
			document.getElementById(\'assignments_submit\').click();
			}
			function updateAssignment(assignmentID, name, maxGrade, points)
			{
			document.getElementById(\'assignments_action\').value = \'updateAssignment\';
			document.getElementById(\'assignments_id\').value = assignmentID;
			document.getElementById(\'assignments_name\').value = name;
			document.getElementById(\'assignments_maxGrade\').value = maxGrade;
			document.getElementById(\'assignments_points\').value = points;
			document.getElementById(\'assignments_submit\').click();
			}
			function deleteAssignment(assignmentID)
			{
			if(confirm(\'Are you sure you want to delete this assignment?\\nAll relevant data for this assignment will be lost...\'))
			{
			document.getElementById(\'assignments_action\').value = \'deleteAssignment\';
			document.getElementById(\'assignments_id\').value = assignmentID;
			document.getElementById(\'assignments_name\').value = -1;
			document.getElementById(\'assignments_maxGrade\').value = -1;
			document.getElementById(\'assignments_points\').value = -1;
			document.getElementById(\'assignments_submit\').click();
			}
			}
			function showEditAssignment(assignmentID)
			{
			for(i = 0; i < assignments.length; i++)
			{
			hideEditAssignment(assignments[i]);
			}
			
			ShowItem(\'spnEditAssignment_options_\' + assignmentID);
			ShowItem(\'txtAssignment_name_\' + assignmentID);
			ShowItem(\'txtAssignment_maxGrade_\' + assignmentID);
			ShowItem(\'txtAssignment_points_\' + assignmentID);
			HideItem(\'spnViewAssignment_options_\' + assignmentID);
			HideItem(\'spnAssignment_name_\' + assignmentID);
			HideItem(\'spnAssignment_maxGrade_\' + assignmentID);
			HideItem(\'spnAssignment_points_\' + assignmentID);
			}
			function hideEditAssignment(assignmentID)
			{
			HideItem(\'spnEditAssignment_options_\' + assignmentID);
			HideItem(\'txtAssignment_name_\' + assignmentID);
			HideItem(\'txtAssignment_maxGrade_\' + assignmentID);
			HideItem(\'txtAssignment_points_\' + assignmentID);
			ShowItem(\'spnViewAssignment_options_\' + assignmentID);
			ShowItem(\'spnAssignment_name_\' + assignmentID);
			ShowItem(\'spnAssignment_maxGrade_\' + assignmentID);
			ShowItem(\'spnAssignment_points_\' + assignmentID);
			}
			</script>
			<form action="" method="post">
			<input type="hidden" id="assignments_action" name="action" />
			<input type="hidden" id="assignments_id" name="assignmentID" />
			<input type="hidden" id="assignments_name" name="assignmentName" />
			<input type="hidden" id="assignments_maxGrade" name="assignmentMaxGrade" />
			<input type="hidden" id="assignments_points" name="assignmentPointValue" />
			<input type="submit" id="assignments_submit" style="display: none" />
			</form>
	
	<table border="0" cellpadding="10"><tr><td valign="top">
			
			
			
			
			
			
			';
	
	
	
	
	
	echo '
			
			
			<table style="font-size: 10pt; border: 1px gray solid; padding: 3px;" cellpadding="3" cellspacing="0">
			<tr>
				<td colspan="4" style="font-weight: bold; font-size: 12pt;">All Assignments</td>
			</tr>
			<tr style="font-size: 8pt; font-style: oblique;">
			<td style="border-bottom: 1px #CCCCCC solid;">Name</td>
			<td style="border-bottom: 1px #CCCCCC solid;">Max Grade</td>
			<td style="border-bottom: 1px #CCCCCC solid;">Point Value</td>
			<td style="border-bottom: 1px #CCCCCC solid;">&nbsp;</td>
			</tr>
			';
			
	for($i = 0; $i < $assignmentCount; $i++)
	{
		$assignmentID = $assignmentResults[$i]["AssignmentID"];
		$assignmentName = $assignmentResults[$i]["Name"];
		$assignmentPointValue = $assignmentResults[$i]["PointValue"];
		$assignmentMaxGrade = $assignmentResults[$i]["MaxGrade"];
		if($i % 2 == 0)
			echo '<tr class="normalrow">';
		else
			echo '<tr class="normalrow_alt">';
		
		echo '<td>
				<span id="spnAssignment_name_' . $assignmentID . '">' . $assignmentName . '</span>
				<input type="text" id="txtAssignment_name_' . $assignmentID . '" value="' . ($assignmentName) . '" style="display:none; width:100px;" />
				</td>';
		echo '<td>
				<span id="spnAssignment_maxGrade_' . $assignmentID . '">' . $assignmentMaxGrade . '</span>
				<input type="text" id="txtAssignment_maxGrade_' . $assignmentID . '" value="' . $assignmentMaxGrade . '" style="display:none; width:30px;" />			
				</td>';
		echo '<td>
				<span id="spnAssignment_points_' . $assignmentID . '">' . $assignmentPointValue . '</span>
				<input type="text" id="txtAssignment_points_' . $assignmentID . '" value="' . $assignmentPointValue . '" style="display:none; width:30px;" />			
				</td>';
		echo '<td>
				<span id="spnViewAssignment_options_' . $assignmentID . '">
					<a href="javascript:showEditAssignment(' . $assignmentID . ')" style="text-decoration: none"><img src="images/icon_edit.gif" border="0"></a>
					<a href="javascript:deleteAssignment(' . $assignmentID . ')" style="text-decoration: none"><img src="images/icon_delete.gif" border="0"></a>
				</span>
				<span id="spnEditAssignment_options_' . $assignmentID . '" style="display: none;">
				<a href="javascript:updateAssignment(' . $assignmentID . ', document.getElementById(\'txtAssignment_name_' . $assignmentID . '\').value, document.getElementById(\'txtAssignment_maxGrade_' . $assignmentID . '\').value, document.getElementById(\'txtAssignment_points_' . $assignmentID . '\').value)" style="text-decoration: none"><img src="images/icon_save.gif" border="0"></a>
					<a href="javascript:hideEditAssignment(' . $assignmentID . ')" style="text-decoration: none"><img src="images/icon_cancel.gif" border="0"></a>
					<a href="javascript:deleteAssignment(' . $assignmentID . ')" style="text-decoration: none"><img src="images/icon_delete.gif" border="0"></a>
				
				</span>
		
		
		
		</td>';
		
		echo '</tr>';
	}
				
	echo '
		<tr><td colspan="4" style="border-top: 1px dashed black">
		<b>New...</b>
		<table border="0" style="font-size: 10pt; width: 100%;">
			<tr>
			<td align="right">Name</td>
			<td><input type="text" id="txtAssignment_name_new" /></td>
			</tr>
			<tr>
			<td align="right">Max Grade</td>
			<td><input type="text" id="txtAssignment_maxGrade_new" /></td>
			</tr>
			<tr>
			<td align="right">Point Value</td>
			<td><input type="text" id="txtAssignment_points_new" /></td>
			</tr>
			<tr>
			<td colspan="2" align="right" style="padding: 5px;">
			<a class="specialLink" style="background-image: url(\'images/icon_add.gif\');" href="javascript:addNewAssignment(document.getElementById(\'txtAssignment_name_new\').value, document.getElementById(\'txtAssignment_maxGrade_new\').value,document.getElementById(\'txtAssignment_points_new\').value)">Add</a>
			</tr>
		
		</table>
		
		
		</td>
		</tr>
	
	
	
	
	
	';
				
			echo '</table> ';
	
	
	
	
	
	
	
	echo '
	
	
	
	
	
	
	
	
	</td><td valign="top">
	
	
	
	
	
	
	
	
	';
	
	
	
	
	
	
	
	
	
	
	
	
	
	echo '<form action="" method="post">
			
			';
	
	$SQL = "SELECT s.StudentID, s.FirstName, s.LastName FROM Students AS s WHERE NOT EXISTS(SELECT * FROM Classes_Students WHERE ClassID = " . $classID . " AND StudentID = s.StudentID) ORDER BY LastName, FirstName";
	$allStudents = runSQLQuery($SQL, true);
	
	echo '<table style="font-size: 10pt; border: 1px gray solid;">
		<tr>
			<td colspan="2" style="font-weight: bold; font-size: 12pt;">Add New Student</td>
		</tr>
		<tr>
			<td width="20">
			<input type="radio" name="addNewStudentOption" value="existingStudent" checked />
			</td>
			<td>
				<b>Existing Student:</b>
				<select name=\'studentID\' id="ddlChooseStudent">
					<option value="-1" selected>Choose student...</option>
				
				';
					
	
	for($i = 0; $i < sizeof($allStudents); $i++)
		echo '  <option value="' . $allStudents[$i]["StudentID"] . '">' . $allStudents[$i]["LastName"] . ', ' . $allStudents[$i]["FirstName"] . '</option>
		';
	
	echo '				</select>
			</td>
		</tr>
		<tr>
			<td width="20">
				<input type="radio" name="addNewStudentOption" value="newStudent"  />
			</td>
			<td>
				<b>New Student:</b>
			</td>
		</tr>
		<tr>
			<td></td>
			<td>
				First: <input type="text" name="firstName" />
			</td>
		</tr>
		<tr>
			<td></td>
			<td>
				Last: <input type="text" name="lastName" /> 
			</td>
		</tr>
		<tr>
			<td colspan="2" style="padding: 5px; text-align: right;">
			<input type="submit" id="btnSubmitAddNewStudent" style="display:none;" />
				<input type="hidden" name="action" value="addNewStudent"  />
				<a class="specialLink" style="background-image: url(\'images/icon_add.gif\');" href="javascript:document.getElementById(\'btnSubmitAddNewStudent\').click();">Add</a>
			</td>
		</tr>
		
		</table>
	
	';
	
	
	echo '</form>';
	
	
	
	echo '<form action="" method="post">
			<input type="hidden" name="action" value="updateGrade" />
			<input type="hidden" name="studentID" id="txtStudentID" />
			<input type="hidden" name="classID" id="txtClassID" />
			<input type="hidden" name="assignmentID" id="txtAssignmentID" />
			<input type="hidden" name="grade" id="txtGrade" />
			<input type="submit" id="btnSubmitChangeGrade" style="display: none;" />
			</form>
			
			
		<script language="javascript">
		function deleteStudent(studentID)
		{
			if(confirm(\'Are you sure you want to remove this student from this class?\\nAll grades related to the student will be lost...\'))
			{
				document.getElementById(\'delStudentID\').value = studentID;
				document.getElementById(\'btnSubmitDeleteStudent\').click();
			}
		}
		</script>	
		<form action="" method="post">
			<input type="hidden" name="action" value="deleteStudent" />
			<input type="hidden" name="studentID" id="delStudentID" />
			<input type="submit" style="display: none;" id="btnSubmitDeleteStudent" />
		
		
		</form>
			
			
			
			
			
			
			
			
			
			</td></tr></table>';
	
	
}
?>