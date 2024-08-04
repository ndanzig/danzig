<?php
include "code_master.php";
function printMainPage()
{
	
	echo '<table class="myTable" cellspacing="0" cellpadding="4" border="1">

			<tr class="header">
			<th scope="col" colspan="4">My Classes</th>
			</tr>';

	$SQL = "SELECT c.ClassID, c.Name, COUNT(cs.StudentID) AS StudentCount
			FROM Classes AS c
			LEFT JOIN Classes_Students AS cs
			ON cs.ClassID = c.ClassID
			WHERE c.UserID = " . $_SESSION["UserID"] . "
			GROUP BY c.ClassID, c.Name";
	$result = runSQLQuery($SQL, true);
	for($i = 0; $i < sizeof($result); $i++)
	{
		if($i % 2 == 0)
			echo '<tr class="normalrow_alt">';
		else
			echo '<tr class="normalrow">';
		echo'
				<td>
				' . $result[$i]["Name"] . '
				</td>
				<td>
				' . $result[$i]["StudentCount"] . '
				</td>
				<td>
				<a class="specialLink" style="background-image: url(\'images/icon_view.gif\');" href="class.php?CID=' . $result[$i]["ClassID"] . '">View</a>
				</td>
				<form action="" method="post">
				<td>
				<input type="hidden" name="action" value="deleteClass" />
				<input type="hidden" name="deleteClassID" value="' . $result[$i]["ClassID"] . '" />
				<input type="submit" id="btnSubmitDeleteClass_' . $i . '" style="display: none;" />
				<a class="specialLink" style="background-image: url(\'images/icon_delete.gif\');" href="javascript:if(confirm(\'Are you sure you want to delete this class?\\n all grades and students assigned will be lost...\'))document.getElementById(\'btnSubmitDeleteClass_' . $i . '\').click();">Delete</a>
				</td></form>
				</tr>';
	}		
	
	echo '
	
		
		</table>
		
		<hr />
			<form action="" method="post">
		<input type="hidden" name="action" value="addNewClass" />
		<b>Add New Class</b><br />
			Name: <input type="text" name="className" id="className" /><br />
			Passing Grade: <input type="text" name="passingGrade" id="passingGrade" value="65"/><br /><br />
			<input type="submit" id="btnSubmitAddNewClass" name="btnSubmitAddNewClass" style="display: none;" />
			<a class="specialLink" style="background-image: url(\'images/icon_add.gif\');" href="javascript:document.getElementById(\'btnSubmitAddNewClass\').click();">Add New...</a>
		</form>
		';
}

?>