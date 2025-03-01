#!/usr/bin/perl
$rockbox_version="3.15";
$meyertime_version="3";

require "tools/builds.pm";

my $verbose;
if($ARGV[0] eq "-v") {
    $verbose =1;
    shift @ARGV;
}

my $update;
if($ARGV[0] eq "-u") {
    $update =1;
    shift @ARGV;
}

my $doonly;
if($ARGV[0]) {
    $doonly = $ARGV[0];
    print "only build $doonly\n" if($verbose);
}

if($update) {
    # svn update!
    system("svn -q up");
}

$rev = `svnversion`;
chomp $rev;
print "rev $rev\n" if($verbose);

sub get_version {
    my ($meyertime)=@_;
    return "$rockbox_version-$meyertime.$meyertime_version";
}

# made once for all targets
sub runone {
    my ($b, $confnum, $extra, $meyertime)=@_;
    my $a;
    my $dir = "$b-$meyertime";

    if($doonly && ($doonly ne $dir)) {
        return;
    }

    my $version=get_version($meyertime);

    mkdir "build-$dir";
    chdir "build-$dir";
    print "Build in build-$dir\n" if($verbose);

    # build the manual(s)
    $a = buildit($dir, $confnum, $extra, $meyertime);

    chdir "..";

    my $o="build-$dir/rockbox.zip";
    my $map="build-$dir/rockbox-maps.zip";
    my $elf="build-$dir/rockbox-elfs.zip";
    if (-f $o) {
        my $newo="output/rockbox-$b-$version.zip";
        my $newmap="output/rockbox-$b-$version-maps.zip";
        my $newelf="output/rockbox-$b-$version-elfs.zip";
        system("mkdir -p output");
        system("mv $o $newo");
        print "moved $o to $newo\n" if($verbose);
        system("mv $map $newmap");
        print "moved $map to $newmap\n" if($verbose);
        system("mv $elf $newelf");
        print "moved $elf to $newelf\n" if($verbose);
    }

    print "remove all contents in build-$dir\n" if($verbose);
    system("rm -rf build-$dir");

    return $a;
};

sub fonts {
    my ($dir, $confnum, $newl)=@_;
    my $a;

    if($doonly && ($doonly ne $dir)) {
        return;
    }

    my $version=$rockbox_version;

    mkdir "build-$dir";
    chdir "build-$dir";
    print "Build fonts in build-$dir\n" if($verbose);

    # build the fonts
    $a = buildfonts($dir, $confnum, $newl);

    chdir "..";

    my $o="build-$dir/rockbox-fonts.zip";
    if (-f $o) {
        my $newo="output/rockbox-fonts-$version.zip";
        system("mv $o $newo");
        print "moved $o to $newo\n" if($verbose);
    }

    print "remove all contents in build-$dir\n" if($verbose);
    system("rm -rf build-$dir");

    return $a;
};



sub buildit {
    my ($target, $confnum, $extra, $meyertime)=@_;

    my $version=get_version($meyertime);

    `rm -rf * >/dev/null 2>&1`;

    my $ram = $extra ? $extra : -1;
    my $c = "../tools/configure --type=n --target=$confnum --ram=$ram --meyertime=$meyertime";

    print "C: $c\n" if($verbose);
    `$c`;

    print "Run 'make'\n" if($verbose);
    `make VERSION=$version`;

    print "Run 'make zip'\n" if($verbose);
    `make zip VERSION=$version`;

    print "Run 'make mapzip'\n" if($verbose);
    `make mapzip VERSION=$version`;

    print "Run 'make elfzip'\n" if($verbose);
    `make elfzip VERSION=$version`;
}

sub buildfonts {
    my ($target, $confnum, $newl)=@_;

    `rm -rf * >/dev/null 2>&1`;

    my $ram = $extra ? $extra : -1;
    my $c = "../tools/configure --type=n --target=$confnum --ram=$ram";

    print "C: $c\n" if($verbose);
    `$c`;

    print "Run 'make fontzip'\n" if($verbose);
    `make fontzip`;
}

# run make in tools first to make sure they're up-to-date
print "cd tools && make\n" if($verbose);
`(cd tools && make ) >/dev/null`;

for my $b (&stablebuilds) {
    my $configname = $builds{$b}{configname} ? $builds{$b}{configname} : $b;
    for my $m (@{$builds{$b}{meyertime}}) {
        runone($b, $configname, $builds{$b}{ram}, $m);
    }
}

#fonts("fonts", "iaudiox5");

