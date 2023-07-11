#!/usr/bin/perl

print 'Did you remember to update the versions in tools/release/bins.pl? (y/n) ';
chomp(my $answer = <STDIN>);
if ($answer !~ /^y(es)?$/i) {
    print "Aborting...\n";
    exit 1;
}

print "Building...\n";
use lib ".";
$ENV{'PATH'} = $ENV{'PWD'} . '/tools/build/bin:' . $ENV{'PATH'};
push(@ARGV, '-v');
do './tools/release/bins.pl';
