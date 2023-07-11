#             __________               __   ___.
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/
# $Id$
#

sub print_credit {
    my ($credit)=@_;
    $credit =~ s/\"/\\\"/g;
    $credit =~ s/\s+$//;
    print "\"$credit\",\n";
}

while (<STDIN>) {
    last if ($_ =~ /^People/);
}

while (<STDIN>) {
    if ($_ !~ /^\s*$/) {
        print_credit($_);
        last;
    }
}

while (<STDIN>) {
    print_credit($_);
}
