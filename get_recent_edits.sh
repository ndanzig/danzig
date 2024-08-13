#!/bin/bash
# get 15 most recent files (excluding those with tildas and the main page index.html 
# also exclude non-readable files
# Create webpage recent_edits.html
# list files there by file name or if file is an index, then by directory name


find . -perm -o=r -type f -printf '%T@ %p\n' | sort -nr | awk 'BEGIN {FS=" "} $2 !~"~" && $2 !~"recent_edits" {print    $2 }' | head -15 | awk 'BEGIN {FS="/"; print "<html><body> \n<h2>Here are recently added or edited pages</h2>"  }  { if ( $0 != "./index.html") { if ( $NF == "index.html" ) {print "<br><a href=\"" $0 "\">" $(NF-1) "</a>"} else {print "<br><a href=\"" $0 "\">" $NF "</a>"}}} END {print "<p> <a href=\"http://www.danzig.us\">Back to home </a>\n </body> </html>" }' > recent_edits.html

