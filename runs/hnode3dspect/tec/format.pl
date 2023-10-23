#! /usr/bin/perl -n

BEGIN {
  $first_title     = 1;
  $first_variables = 1;
}

if (/^TITLE/) {
  if ($first_title) {
    print;
    $first_title = 0;
  }
  ($null, $null, $t) = split /[=,]/;
  next;
}
if (/^VARIABLES/) { 
  if ($first_variables) {
    print;
    $first_variables = 0;
  }
  next; 
}
if (/^ZONE/) {
  chop;
  printf "%s, SOLUTIONTIME=%14.8f\n", $_, $t;
  next;
}
print;
if (eof) { print "\n"; }

