<?php
function successclose()
{
global $attribute;
global  $name;
global $auth_pass;
if (isset($_POST["username"]))
{
  echo "<h3>Changed $attribute of $name.</h3>";
}
else
{
  echo "<h3>New Search</h3>";
}
echo '<form action="displayuser.php" method="POST" >';
echo " User Name <input type='text' name='username' size='10' maxlength='8' value=$name > ";
echo " Admin Password <input type='hidden' name='adminpass' size='10' maxlength='8' value=$auth_pass>";
echo '<input type="submit" value="Display Info">';
echo '<br> Search Login';
echo '<input type="radio" name="search" value="login" checked>';
echo 'Search Full Name: <input type="radio" name="search" value="fullname">';

echo "</form>";

echo '<form action="logout.php" method="POST" >';
echo '<input type="submit" value="Logout">';
echo "</form>";

echo "</body>";
echo "</html>";
exit(0);
}

?>