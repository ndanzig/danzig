<?php

function master_printHeader($Page_Title)
{
	echo '<html>
			
			<head>
			<title>' . $Page_Title . '</title>
			<link href="Style.css" rel="stylesheet" />
			</head>
			<body>
			';
}
function master_printFooter()
{
	echo '
			</body>
			</html>';
}

function master_redirect($newURL)
{
	header('Location:' . $newURL);
}

function runSQLQuery($SQL, $useColumnNames)
{
	$serverName = "mysql406.ixwebhosting.com";
	$username = "Kamione_GKDBUser";
	$password = "somepassword";
	$dbName = "Kamione_GradeKeeper";
	$ret = array();
	
	$connection = mysql_connect($serverName, $username, $password) or die("HELP! BAD CONNECTION");
	mysql_select_db($dbName);
	$process = mysql_query($SQL, $connection)  or die("HELP! BAD SQL = '" . $SQL . "'");
	
	
	$columnCount = mysql_num_fields($process);
	$columnNames = array();
	if($useColumnNames)
	{
		for($i = 0; $i < $columnCount; $i++)
			$columnNames[] = mysql_field_name($process, $i);
	}

	for($rowCount = 0; $rowCount < mysql_num_rows($process); $rowCount++)
	{
		for($i = 0; $i < $columnCount; $i++)
		{
			if($useColumnNames)
				$ret[$rowCount][$columnNames[$i]] = mysql_result($process, $rowCount, $i);
			else
				$ret[$rowCount][$i] = mysql_result($process, $rowCount, $i);
		}
		
	}
	mysql_close($connection);
	return $ret;
	
	/*
	//echo $SQL;
	$dsn = "mssqlserver";
	$username = "sa";
	$password = "";
	
	$ret = array();
	
	$sqlconnect = odbc_connect($dsn, $username, $password) or die("help me!");
	//echo $SQL;
	$process = odbc_exec($sqlconnect, $SQL);
	$columnCount = odbc_num_fields($process);
	$columnNames = array();
	if($useColumnNames)
	{
		for($i = 1; $i <= $columnCount; $i++)
			$columnNames[] = odbc_field_name($process, $i);
	}
	
	
	//for($i = 1; $i <= $columnCount; $i++)
	//{
	//	if($useColumnNames)
	//		$ret[] = array();
	//	else
	//		$ret[$columnNames[$i - 1]] = array();
	//}
	
	$rowCount = 0;
	while(odbc_fetch_row($process))
	{
		for($i = 1; $i <= $columnCount; $i++)
		{
			if($useColumnNames)
				$ret[$rowCount][$columnNames[$i - 1]] = odbc_result($process, $i);
			else
				$ret[$rowCount][$i - 1] = odbc_result($process, $i);
		}
		$rowCount++;
	}
	
	odbc_close($sqlconnect);
	return $ret;
	
	*/
}

function runSQLQueryScalar($SQL)
{
	$result = runSQLQuery($SQL, false);
	return $result[0][0];
}

function runSQLQueryWithIdentity($SQL)
{
	$serverName = "mysql406.ixwebhosting.com";
	$username = "Kamione_GKDBUser";
	$password = "mkd100";
	$dbName = "Kamione_GradeKeeper";
	$connection = mysql_connect($serverName, $username, $password);
	mysql_select_db($dbName);
	
	mysql_query($SQL, $connection);
	
	$ret = mysql_insert_id();
	
	mysql_close($connection);
	return $ret;
	
	/*
	//echo $SQL;
	$dsn = "mssqlserver";
	$username = "sa";
	$password = "";
	
	$sqlconnect = odbc_connect($dsn, $username, $password) or die("help me!");
	//echo $SQL;
	$tempProcess = odbc_exec($sqlconnect, $SQL);
	$process = odbc_exec($sqlconnect, "SELECT @"."@IDENTITY");
	$rc = odbc_fetch_into($process, $row);
	$ret = $row[0];
	odbc_close($sqlconnect);
	return $ret;*/
}

function runSQLNonQuery($SQL)
{
	$serverName = "mysql406.ixwebhosting.com";
	$username = "Kamione_GKDBUser";
	$password = "mkd100";
	$dbName = "Kamione_GradeKeeper";
	$connection = mysql_connect($serverName, $username, $password) or die("ERROR1! " . mysql_error());
	mysql_select_db($dbName);
	mysql_query($SQL, $connection) or die("ERROR2! " . mysql_error());

	mysql_close($connection);

}

function makeSafe($value)
{
	$value = str_replace("&", "&amp;", $value);
	$value = str_replace("\\\\", "\\", $value);
	$value = str_replace("\\'", "&#39;", $value);
	$value = str_replace("\\\"", "&quot;", $value);
	
	$value = str_replace("<", "&lt;", $value);
	$value = str_replace(">", "&gt;", $value);
	return $value;
}
function releaseSafety($value)
{
	$value = str_replace("&amp;", "&", $value);
	$value = str_replace("&#39;", "'", $value);
	$value = str_replace("\\", "\\\\", $value);
	$value = str_replace("&quot;", "\\\"", $value);
	
	$value = str_replace("&lt;", "<", $value);
	$value = str_replace("&gt;", ">", $value);
	return $value;
}
?>