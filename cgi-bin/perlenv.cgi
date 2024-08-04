#!/usr/local/bin/perl
print "Content-type: text/html\n\n<HTML><HEAD><TITLE>Environment variables</TITLE></HEAD><BODY>";
print "List of environment keys/values in this environment:<BR>";
while (($nam, $val) = each (%ENV))
{
    print "KEY- $nam\t:VALUE-$val<BR>";
}
print "</BODY></HTML>\n";
