#!/usr/local/bin/perl
# This is the Guestbook Writing routine...
# We'll use a static HTML page and set up the code to collect the POST
# and add it to a guestbook data HTML file...  We'll set up a static
# string say <!--NEXTDATA--> and replace it with NEW data followed by
# a new <!--NEXTDATA--> tag...
use CGI::Carp qw(fatalsToBrowser);

sub read_input
{
    local ($buffer, @pairs, $pair, $name, $value, %FORM);
    # Read in text
    $ENV{'REQUEST_METHOD'} =~ tr/a-z/A-Z/;
    if ($ENV{'REQUEST_METHOD'} eq "POST")
    {
	read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
    } else
    {
	$buffer = $ENV{'QUERY_STRING'};
    }
    # Split information into name/value pairs
    @pairs = split(/&/, $buffer);
    foreach $pair (@pairs)
    {
	($name, $value) = split(/=/, $pair);
	$value =~ tr/+/ /;
	$value =~ s/%(..)/pack("C", hex($1))/eg;
	$FORM{$name} = $value;
    }
    %FORM;
}
%INF=&read_input;
print "Content-type: text/html\n\n";
print "<HTML><HEAD><TITLE>Adding entry...</TITLE>";
$tmpfile='/usr/u/'.$INF{'dirname'}.'/public_html/gtmp.dat';
#We're going to set up a variable "spit-out" location
$file='/usr/u/'.$INF{'dirname'}.'/public_html/gbook.html';
#Change the directory to point to the brits or go generic on that.
#$file='/home/jctstud/public_html/gbook/gbook.html';
open (INFO,"<$file");
@lines=<INFO>;
close(INFO);
open (TMPINF,">$tmpfile") or die("Error opening temp for output: [$tmpfile]");
print TMPINF @lines;
close(TMPINF);
open(TMPINF1,"<$tmpfile");
open(INFO1,">$file") or die("Error opening file for output: [$file]");
$done="no";
while ($_ = <TMPINF1>)
{
	if ((/<!--NEXTDATA-->/) && ($done eq "no"))
	{
		print INFO1 "Name: $INF{'uname'}<BR>\n";
		print INFO1 "Email: <A HREF=".'"'."mailto:$INF{'umail'}".'"'.">$INF{'umail'}</A><BR>\n";
		print INFO1 "Sex: $INF{'usex'}<BR>\n";
		print INFO1 "Age: $INF{'uage'}<BR>\n";
		print INFO1 "Gave us a $INF{'urate'} star rating!!!&nbsp;&nbsp;";
		for ($I=0;$I<$INF{'urate'};$I++)
		{
		    print INFO1 '<IMG SRC="star.gif"></IMG>';
		}
		print INFO1 "<BR><HR>\n";
		print INFO1 '<!--NEXTDATA-->'."\n";
		$done="yes";
	}
	else
	{
		print INFO1 $_;
	}
}
close(INFO1);
close(TMPINF1);
if ($done eq 'no') {
print <<EOF
</HEAD><BODY><H1>Unexpected errror</H1><BR>
<h3>An unexpected error happened while trying to update the guestbook.<BR>
Please contact the author of this program at neoi\@writeme.com an let him 
know about this.  Thank you.</h3>
</body>
</html>

EOF
} else {
print <<EOF 

<META HTTP-EQUIV="refresh" CONTENT="0;URL=/~$INF{'targetdir'}/gbook.html">
</HEAD>
<BODY>
<h2>Parsing guestbook...Done! Target: $file</h2><BR>
<h4>If you are not automatically forwarded then please <A 
HREF="/~$INF{'targetdir'}/gbook.html">continue...</A></h4><BR>
</BODY></HTML>

EOF
}




