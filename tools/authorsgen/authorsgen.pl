#!/usr/bin/perl -w

# The GIMP -- an image manipulation program
# Copyright (C) 2000 Sven Neumann <sven@gimp.org>

# No, this script does not create new GIMP authors ;-)


my $contributors = {};


open (INPUT, "contributors")
    or die ("Couldn't open file 'contributors'.");
while (<INPUT>) 
{
    chomp;    
    s/[,\.]$//;
    if (length ($_) and not (/^\#/))
    {
	if (/(.{1,})\[(.{1,})\]/)
	{
	    $iso{$1} = $2;
	    push (@contributors, $1);
	}
	else 
	{
	    push (@contributors, $_);
	}
    }
}
close (INPUT);


open (ICONV, "iconv -f iso-8859-1 -t utf-8 contributors |")
   or die ("Call to iconv failed."); 
while (<ICONV>)
{
    chomp;
    if (length ($_) and not (/^\#/) and (/(.{1,})\[(.{1,})\]/))
    {
	$utf{$1} = $2;
    }
}
close (ICONV);



open (AUTHORS, ">../../AUTHORS")
    or die ("Couldn't write to file '../../AUTHORS'.");
print AUTHORS <<EOT;
The GIMP: Authors
=================

The people that made it happen!

1. Main Authors
===============

Spencer Kimball
Peter Mattis

2. Contributers
===============

With patches, fixes, plugins, extensions, scripts, translations, documentation,
and more from (in alphabetical order):

EOT
foreach $author (@contributors)
{
    print AUTHORS "$author\n";
}
close (AUTHORS);


open (AUTHORS, ">../../app/authors.h")
    or die ("Couldn't write to file '../../app/authors.h'.");
print AUTHORS <<EOT;
/* NOTE: This file is autogenerated by authorgen.pl. */

/*
 * The main authors are Spencer Kimball and Peter Mattis.
 */

static gchar *authors[] =
{
EOT
foreach $author (@contributors)
{   
    if ($iso{$author} and $utf{$author})
    {
	print AUTHORS "#ifndef GDK_USE_UTF8_MBS\n";
	print AUTHORS "  \"$iso{$author}\",\n";
	print AUTHORS "#else\n";
	print AUTHORS "  \"$utf{$author}\",\n";
	print AUTHORS "#endif\n";
    }
    else
    {
	print AUTHORS "  \"$author\",\n";
    }
}
print AUTHORS "};\n";
close (AUTHORS);


exit;

