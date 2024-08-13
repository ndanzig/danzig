<?php 
// Program for the ESP program to send email registrations to 
// the esp secretary  currently hard coded to be moss@jct.ac.il
//Course registration
$courses_registration = '';
if ($_POST['course'] != '')
{
	foreach($_POST['course'] as $variable) {
		$courses_registration .= $variable."\n ";
		}
}
//Major would like to take
$majorChecked = '';
if ($_POST['major']  != '')
{
	foreach($_POST['major'] as $variable) {
		$majorChecked .= $variable.", ";
		}
}
//Math courses took
$mathChecked = '';
if ($_POST['math']  != '')
{
	foreach($_POST['math'] as $variable) {
		$mathChecked .= $variable.", ";
		}
}

//Math would like to take
$wantMathChecked = '';
if ($_POST['math_interested']  != '')
{
	foreach($_POST['math_interested'] as $variable) {
		$wantMathChecked .= $variable.", ";
		}
}

//computer courses taken
$computersChecked = '';
if ($_POST['courses_taken'] != '')
{
	foreach($_POST['courses_taken'] as $variable) {
		$computersChecked .= $variable.", ";
		}
}
?>

<?php

$name = $_POST['name'];
$email = $_POST['email'];
$phone = $_POST['phone'];


$plans = $_POST['plans'];
$college = $_POST['college']; 
$majorConcidering = $_POST['majorConcidering']; 
$hebrew = $_POST['hebrew']; 



$ap1 = $_POST['ap1']; $ap1_score = $_POST['ap1_score'];
$ap2 = $_POST['ap2']; $ap2_score = $_POST['ap2_score'];
$ap3 = $_POST['ap3']; $ap3_score = $_POST['ap3_score'];
$ap4 = $_POST['ap4']; $ap4_score = $_POST['ap4_score'];   




$hebrew_school = $_POST['hebrew_school']; 
$conversation = $_POST['conversation']; 
$level = $_POST['level']; 
$capable = $_POST['capable']; 
$be = $_POST['be'];  


$math_other = $_POST['math_other']; 


$courses_taken_other  = $_POST['courses_taken_other']; 		
  
$programming = $_POST['programming']; 
$language = $_POST['language'];  
 

$taken_physics = $_POST['taken_physics']; 
$grade = $_POST['grade']; 


$roommate = $_POST['roommate']; 
$medical = $_POST['medical']; 
$flight = $_POST['flight']; 
$arrive = $_POST['arrive']; 
?>



<!--____________ Process Form ______________-->
<?php
// e-mail address to send
$myemail = "moss@jct.ac.il"; //moss@jct.ac.il

 if (!isset($_POST['name'])) {
	echo "You forgot to write your name." ; 
 }

else {
	$todayis = date("l, F j, Y, g:i a") ;

	$subject = "Registration from Esp.jct.il" ;

	$message = " $todayis [EST] \n
PERSONAL DETAILS \n


Full Name: $name \n
E-mail: $email \n
Phone: $phone \n
Interested in courses: $courses_registration \n \n

----------- \n \n

 
COURSE QUESTIONNAIRE \n \n

A. Future Plans \n

1. What are your plans for the year after your first year at Machon Lev's English Speakers' Program? If University, which University?: $plans \n
2. What major are you considering?: $majorConcidering \n
3. Are you considering continuing on to the Hebrew program in Machon Lev?: $hebrew \n
4. If so, what major are you interested in?: $majorChecked \n \n


B. Testing \n

Did you take any APs or SAT II? If so, please list which SAT II tests and/or AP you took and grades: 
$ap1 Score: $ap1_score
$ap2 Score: $ap2_score
$ap3 Score: $ap3_score
$ap4 Score: $ap4_score  \n \n


C. Hebrew Language \n


1. Did you have Hebrew in High School?: $hebrew_school \n
2. Can you understand a conversation in Hebrew?: $conversation \n
3. Objectively, do you feel you want a beginners or advanced level?: $level \n
4. Would you feel capable of taking a course in Hebrew?: $capable \n
5. At the end of ESP's Ulpan, where would you like to be?: $be \n \n


D. Math \n

1. What math courses did you take in High School?: \n $mathChecked \n 
	Other: $math_other \n

2. What math course would you be interested in taking next year?:\n $wantMathChecked \n

			

E. Computers \n


1. What courses have you previously taken in Computer Science?:\n $computersChecked \n	
  Other: $courses_taken_other \n		
  
2. Do you have programming experience outside of school courses above?: $programming \n
If so, in what language(s)?: $language \n \n
 

F. Have you taken Physics in High School?: $taken_physics \n
What grade did you get?: $grade \n

----------- \n \n

ADDITIONAL REGISTRATION INFORMATION \n

1. Roommate preferences: $roommate \n
2. Which medical insurance plan are you registered with?: $medical \n
3. Flight arrival day and time: $flight \n
Day and time expected to arrive at Machon Lev if not coming from the airport: $arrive \n
		";

	$from = "From: $myemail\r\n";

	if ($myemail != "") 
	mail($myemail, $subject, $message, $from);

	?>

	<!-- ______ Dysplay thank you note upon submition ______ -->

	<img src="http://esp.jct.ac.il/images/logo_gold.jpg" width="190" height="86" /><br />

	<h2>Information Sent!</h2>
	<p>Thank you <strong> <?php echo $name ?> </strong> for your registration.</p>
	<p><a href="http://esp.jct.ac.il">Return to the ESP website</a></p>

	<!--____________ End thank you note ______________-->

<?php 
} // end else
?>