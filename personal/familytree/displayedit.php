<?php
include 'successclose.php';
include 'validate.php';
  echo "<html>";
  echo "<head>";
echo "<LINK REL=STYLESHEET HREF='forms.css' TYPE='text/css'>";

  echo "<title>Edit Family Member</title>";
  echo "</head>";
  echo "<body >"; 

if (isset($_POST["person"]))
{
  $name = $_POST["person"];
}
else
{
  echo "<h3>Specify Person! </h3>";
closephp();
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

mysql_select_db('danzig') or die('Could not select database danzig ');

//find person by first name
$query = "SELECT * FROM people WHERE firstname LIKE \"%$name%\"";

$result = mysql_query($query) or die('Query failed: ' . mysql_error());
$num_rows = mysql_num_rows($result);

if ($num_rows==0)
{
print "Not Found! <br>";
closephp();
  }

$fields=array(1,2,3,4,5,6,7,8,9,10,11,12,13);
$counter=0;
$result2="";
$result3="";


// EXACTLY ONE FOUND
//////////////////////

if ($num_rows==1)
{
//get person's data
while ($line = mysql_fetch_array($result, MYSQL_ASSOC)) 
   {
     foreach ($line as $col_value) 
      {
        $fields[$counter]=$col_value;
        $counter++;
      }
   }
$counter=0;
$uid = $fields[0];
$firstname = $fields[1];
$lastname = $fields[2];
$hebrewname = $fields[3];
$birth = $fields[4];
$death = $fields[5];
$birthplace = $fields[6];
$deathplace = $fields[7];
$imagefile = $fields[8];
$gender = $fields[9];

print "<form>";
print " UID is  <input type='text' name='uid' size='25' maxlength='8' value=$uid >";
print "<br>\n";
print " First Name is  <input type='text' name='firstname' size='25' maxlength='8' value=$firstname >";
print "<br>\n";
print " Last Name is  <input type='text' name='lastname' size='25' maxlength='8' value=$lastname >";
print "<br>\n";
print " Hebrew Name is  <input type='text' name='hebrewname' size='25' maxlength='8' value=$hebrew >";
print "<br>\n";
print " Birth Date is  <input type='text' name='birth' size='25' maxlength='8' value=$birth >";
print "<br>\n";
print " Death Date is  <input type='text' name='death' size='25' maxlength='8' value=$death >";
print "<br>\n";
print " Birth Place is  <input type='text' name='birthplace' size='25' maxlength='8' value=$birthplace >";
print "<br>\n";
print " Place of Death is  <input type='text' name='deathplace' size='25' maxlength='8' value=$deathplace >";
print "<br>\n";
print " UID is  <input type='text' name='uid' size='25' maxlength='8' value=$uid >";
  		echo " <input type=submit value='apply changes'>";
print "</form>";

mysql_free_result($result);
//------------------------------------------------------------------
//get person's parents (and spouse)
// Performing SQL query

$query2 = "SELECT * FROM relations WHERE relative LIKE \"$uid\" ";
$result2 = mysql_query($query2) or die('Query failed: ' . mysql_error());

   $num_rows = mysql_num_rows($result2);
   if ($num_rows==0)
   {
   closephp();
   }
while ($line2 = mysql_fetch_array($result2, MYSQL_ASSOC))  //for each line
{
   foreach ($line2 as $col_value2) 
     { //get the other person
     $fields[$counter]=$col_value2;
     $counter++;
     }
   $counter=0;
   $relation = $fields[1];
   $otheruid = $fields[0]; 
                //get other person's name 
   $query3 = "SELECT firstname FROM people WHERE uid LIKE \"$otheruid\"";
   $result3 = mysql_query($query3) or die('Query failed: ' . mysql_error());
   $num_rows = mysql_num_rows($result3);
   if ($num_rows==0)
   {
   closephp();
   }
   $line3 = mysql_fetch_array($result3, MYSQL_ASSOC); 
   foreach ($line3 as $col_value3) 
             { //get name
   		$displayname=$col_value3 ;
	     }

if ($relation==p && $gender==m)
   {
   $relationship=" son ";
   }
if ($relation==p && $gender==f)
   {
   $relationship=" daughter ";
   }
if ($relation==s && $gender==m)
   {
   $relationship=" husband ";
   }
if ($relation==s && $gender==f)
   {
   $relationship=" wife ";
   }

echo '<form action="displayedit.php" method="POST" >';
echo " <input type='hidden' name='person' value=$displayname > $relationship of  $displayname ";
echo " <select name='actiontype'>  <option value='view'>View</option>";
echo " <select name='actiontype'>  <option value='edit'>Edit</option>";
echo " <select name='actiontype'>  <option value='addchild'>Add Child</option>";
echo " <select name='actiontype'>  <option value='addparent'>Add Parent</option>";

echo " <select name='actiontype'>  <option value='addspouse'>Add Spouse</option>";


echo "</select>";

  		echo " <input type=submit value='select'>";
  		echo "</form>";



}

// Free resultset
mysql_free_result($result2);
mysql_free_result($result3);



//-----------------------------------------------------------------------
//get person's children (and spouse)
// Performing SQL query

$query2 = "SELECT * FROM relations WHERE person LIKE \"$uid\"";
$result2 = mysql_query($query2) or die('Query failed: ' . mysql_error());

   $num_rows = mysql_num_rows($result2);
   if ($num_rows==0)
   {
   closephp();
   }
while ($line2 = mysql_fetch_array($result2, MYSQL_ASSOC))  //for each line
{
   foreach ($line2 as $col_value2) 
     { //get the other person
     $fields[$counter]=$col_value2;
     $counter++;
     }
   $counter=0;
   $relation = $fields[1];
   $otheruid = $fields[2]; 
                //get other person's name 
   $query3 = "SELECT firstname FROM people WHERE uid LIKE \"$otheruid\"";
   $result3 = mysql_query($query3) or die('Query failed: ' . mysql_error());
   $num_rows = mysql_num_rows($result3);
   if ($num_rows==0)
   {
   closephp();
   }
   $line3 = mysql_fetch_array($result3, MYSQL_ASSOC); 
   foreach ($line3 as $col_value3) 
             { //get name
   		$displayname=$col_value3 ;
	     }

if ($relation==p && $gender==m)
   {
   $relationship=" father ";
   }
if ($relation==p && $gender==f)
   {
   $relationship=" mother ";
   }
if ($relation==s && $gender==m)
   {
   $relationship=" husband ";
   }
if ($relation==s && $gender==f)
   {
   $relationship=" wife ";
   }


echo '<form action="displayedit.php" method="POST" >';
echo " <input type='hidden' name='person' value=$displayname > $relationship of  $displayname ";
echo " <select name='actiontype'>  <option value='view'>View</option>";
echo " <select name='actiontype'>  <option value='edit'>Edit</option>";
echo " <select name='actiontype'>  <option value='addchild'>Add Child</option>";
echo " <select name='actiontype'>  <option value='addparent'>Add Parent</option>";

echo " <select name='actiontype'>  <option value='addspouse'>Add Spouse</option>";

echo "</select>";
  		echo " <input type=submit value='select'>";
  		echo "</form>";

}

// Free resultset
mysql_free_result($result2);
mysql_free_result($result3);

}

//MANY FOUND
///////////////////////
else{
while ($line = mysql_fetch_array($result, MYSQL_ASSOC)) 
   {
   foreach ($line as $col_value) 
     {
       $fields[$counter]=$col_value;
       $counter++;
     }

   $counter=0;
   $firstname = $fields[1];
   $lastname = $fields[2];

echo '<form action="displayedit.php" method="POST" >';
echo " <input type='hidden' name='person' value=$displayname > $relationship of  $displayname ";
echo " <select name='actiontype'>  <option value='view'>View</option>";
echo " <select name='actiontype'>  <option value='edit'>Edit</option>";
echo " <select name='actiontype'>  <option value='addchild'>Add Child</option>";
echo " <select name='actiontype'>  <option value='addparent'>Add Parent</option>";

echo " <select name='actiontype'>  <option value='addspouse'>Add Spouse</option>";


echo "</select>";

  		echo " <input type=submit value='select'>";
  		echo "</form>";

   }
}

// Closing connection
mysql_close($link);
closephp ();

function closephp ()
{

  echo '<form action="displayedit.php" method="POST" >';
  echo " Family Member Name <input type='text' name='person' size='27' maxlength='25'>";
  echo '<input type="submit" value="New Search">';
  echo "</form>";
  echo "</body>";
  echo "</html>";
  exit (0);
}


?> 

