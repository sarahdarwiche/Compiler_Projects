#!/usr/bin/perl
use strict;
use warnings;
use Spreadsheet::Read;

$dirname = '.';
opendir(DIR, $dirname) or die "Could not open $dirname\n";

