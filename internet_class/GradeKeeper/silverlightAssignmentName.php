<?php
include "code_master.php";
session_start();
$assignmentID = $_GET["AID"];
if(isset($_SESSION["UserID"]) && $_SESSION["UserID"] != -1 && is_numeric($assignmentID))
{
	$SQL = "SELECT Name FROM Assignments WHERE AssignmentID = " . $assignmentID;
	$results = runSQLQuery($SQL, false);
	

}



?>



<Canvas
   xmlns="http://schemas.microsoft.com/client/2007"
   xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
    <TextBlock FontSize="12" Canvas.Left="0" Canvas.Top="125" Foreground="Black" Text="<?php echo $results[0][0]; ?>">
        <TextBlock.RenderTransform>
          <TransformGroup>
                <RotateTransform Angle="-90"/>
          </TransformGroup>
        </TextBlock.RenderTransform>
    </TextBlock>
</Canvas>
