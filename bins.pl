#!/usr/bin/perl
use lib ".";
$ENV{'PATH'} = $ENV{'PWD'} . '/tools/build/bin:' . $ENV{'PATH'};

do './tools/release/bins.pl';
