<?php
include 'successclose.php';
include 'validate.php';
  echo "<html>";
  echo "<head>";
  echo "<title>Add Info</title>";
  echo "</head>";
  echo "<body bgcolor=#f2c09f>";

$name="";
if (isset($_POST["person"]))
{
  $name = $_POST["person"];

  $endline="<br>";
  $horizon_line="<hr>";
}

$valid_results=validate($name);

if ($valid_results == "false")
{
echo "invalid name <br>";
closephp();
}




// Connecting, selecting database
$link = mysql_connect('localhost', 'danzig', 'Hell0')
   or die('Could not connect: ' . mysql_error());
echo 'Connected successfully';
mysql_select_db('danzig') or die('Could not select database danzig ');


// Performing SQL query
$query = 'SELECT $name FROM people';
$result = mysql_query($query) or die('Query failed: ' . mysql_error());

// Printing results in HTML

echo '<form action="addinfo.php" method="POST" >';
while ($line = mysql_fetch_array($result, MYSQL_ASSOC)) {

  print "<input type='text' name='adminpass' size='10' maxlength='8'> ";


   }
echo "</form>\n";

// Free resultset
mysql_free_result($result);
// Closing connection
mysql_close($link);
exit(0);










$sql = 'INSERT INTO `people` (`uid`, `firstname`, `lastname`, `hebrewname`, `father`, `mother`, `birth`, `death`, `birthplace`, `deathplace`) VALUES (''1'', ''Harris'', ''Danzig'', ''Hirsh'', ''Abe'', '''', '''', '''', '''', '''')';




function closephp ()
{

  echo '<form action="displayperson.php" method="POST" >';
  echo " Family Member Name <input type='text' name='person' size='27' maxlength='25'>";
  echo '<input type="submit" value="New Search">';
  echo "</form>";
  echo "</body>";
  echo "</html>";
  exit (0);
}
 

?>