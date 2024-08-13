<html>
<head>
<title>Homework Assignment #2</title>
</head>
<body>
<h1>Question #1</h1>
<p>Write a brief description of what the following program does. Then,
comment each line.</p>
<xmp>
<html>
<body>
<table border="1" cellpadding="3">
<tr>
<td>Date</td>
<td colspan="10">Correct/Incorrect Answers</td>
<td>% Correct</td>
</tr>
<?php

$results=array(
	       array('21/1',0,0,1,1,1,1,1,1,1,1),
	       array('22/1',0,1,1,1,1,1,1,1,1,1),
	       array('23/1',0,1,1,1,1,1,1,1,1,1),
	       array('24/1',0,0,0,0,0,1,1,1,1,1),
	       array('25/1',0,0,0,0,0,1,1,1,1,1),
	       array('26/1',0,1,1,1,1,1,1,1,1,1),
	       array('27/1',0,0,0,0,0,1,1,1,1,1)
	       );
	       $previous_pct=.6;
foreach($results as $date_record)
{


  $total=-1;
  $correct=0;
  foreach($date_record as $value)
    {
      if($total<0)
	{
	  $total++;
	  continue;
	}
      elseif($value)
	{
	  $correct++;
	}
      $total++;
    }
  if((( $correct / $total)+$previous_pct)>=1.8)
    {
      $color="lightgreen";
    }
  elseif((( $correct / $total)+$previous_pct)<=1.2)
    {
      $color="red";
    }
  else
    {
      $color="yellow";
    }
  $previous_pct=($correct/$total);
  
  print "<tr bgcolor=\"$color\">\n";

  foreach($date_record as $value)
    {
     print "
<td>$value</td>
";
    }
  print "<td>".($correct/$total)."</td>\n";
 print "</tr>\n";
}
 ?>
</table>
</body>
</html></xmp>

<h1>Question #2</h1>
<p>Write a brief description of what the following program does. Then,
comment each line.</p>
<xmp>
<?php

$a=array(0,0,1,1);
$b=array(0,1,0,1);
print '<table border="1" cellpadding="3">
<tr>
<td>a</td><td>b</td><td>!a</td><td>a&&b</td><td>a||b</td>
</tr>';
for($i=0;$i<4;$i++)
{
  print '<tr> <td>'.$a[$i].
    '</td> <td>'.$b[$i].
    '</td> <td>'.(int)(!$a[$i]).
    '</td> <td>'.(int)($a[$i]&&$b[$i]).
    '</td> <td>'.(int)($a[$i]||$b[$i]).
    '</td> </tr>';
}
print '</table>';

?></xmp>


<h1>Question #3</h1>
<p>Write a Madlib web page using a form to get the words and a php
page to write the story.</p>

</body>
</html>
