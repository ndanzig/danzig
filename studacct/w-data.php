<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-8-i">
</head>
<body>
<?php
$cfg['server']="w-data";
$cfg['username']="cc_user";
$cfg['password']="VeryHard2Find";
$cfg['database']="mazak";

$conn = mssql_connect($cfg['server'],$cfg['username'],$cfg['password']);
$db = mssql_select_db($cfg['database'],$conn) or die("Error selecting the database");

#$sql_statement =  mssql_init("[GetStudentInfoForCC]", $conn);
#$result=mssql_execute($sql_statement);
#if (!$result)
#{
#  $message = "Last message from SQL : " . mssql_get_last_message() . "\n";
#  echo $message;
#}

# we didn't get to run stored procedure - so we use it via VIEWS

$result=mssql_query("SELECT * from vwStudentInfoForCC WHERE AcademicYear=5767");
echo "<table>";
while ($row = mssql_fetch_assoc($result)) {
     echo "<tr>";
     foreach ($row as $key=>$value) {
       if ($key=="OwnerKeyNumber") {
          $code=substr($value*17,0,4);
          echo "<td><b> $code </b></td>";
   }
       echo "<td> $value </td>";
    } 
    echo "</tr>";

}


?>
</table></body></html>
