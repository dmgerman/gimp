#!/usr/bin/perl -w

use lib '../../tools/pdbgen';

require 'util.pl';

*write_file = \&Gimp::CodeGen::util::write_file;
*FILE_EXT   = \$Gimp::CodeGen::util::FILE_EXT;

$outmk = "Makefile.am$FILE_EXT";
$outignore = ".cvsignore$FILE_EXT";
open MK, "> $outmk";
open IGNORE, "> $outignore";

require 'plugin-defs.pl';

$bins = ""; $opts = "";

foreach (sort keys %plugins) {
    $bins .= "\t";
    if (exists $plugins{$_}->{optional}) {
	$bins .= "\$(\U$_\E)";
	$opts .= "\t$_ \\\n";
    }
    else {
	$bins .= $_;
    }
    $bins .= " \\\n";
}

$extra = "";
foreach (@extra) { $extra .= "\t$_\t\\\n" }
if ($extra) {
    $extra =~ s/\t\\\n$//s;
    $extra = "\t\\\n$extra";
}

foreach ($bins, $opts) { s/ \\\n$//s }

print MK <<EOT;
## This file is autogenerated by mkgen.pl and plugin-defs.pl

libgimpui = \$(top_builddir)/libgimp/libgimpui-\$(GIMP_API_VERSION).la
libgimpwidgets = \$(top_builddir)/libgimpwidgets/libgimpwidgets-\$(GIMP_API_VERSION).la
libgimp = \$(top_builddir)/libgimp/libgimp-\$(GIMP_API_VERSION).la
libgimpcolor = \$(top_builddir)/libgimpcolor/libgimpcolor-\$(GIMP_API_VERSION).la
libgimpbase = \$(top_builddir)/libgimpbase/libgimpbase-\$(GIMP_API_VERSION).la

if OS_WIN32
mwindows = -mwindows
endif

AM_LDFLAGS = \$(mwindows)

libexecdir = \$(gimpplugindir)/plug-ins

EXTRA_DIST = \\
	mkgen.pl	\\
	plugin-defs.pl$extra

INCLUDES = \\
	-I\$(top_srcdir)					\\
	-I\$(top_srcdir)/plug-ins/libgimpoldpreview	\\
	\$(GTK_CFLAGS)					\\
	\$(EXIF_CFLAGS)					\\
	\$(SVG_CFLAGS)					\\
	\$(WMF_CFLAGS)					\\
	-I\$(includedir)

libexec_PROGRAMS = \\
$bins

EXTRA_PROGRAMS = \\
$opts

install-\%: \%
	\@\$(NORMAL_INSTALL)
	\$(mkinstalldirs) \$(DESTDIR)\$(libexecdir)
	\@if test -f \$<; then \\
	  echo " \$(LIBTOOL)  --mode=install \$(INSTALL_PROGRAM) \$< \$(DESTDIR)\$(libexecdir)/`echo \$<|sed 's/\$(EXEEXT)\$\$//'|sed '\$(transform)'|sed 's/\$\$/\$(EXEEXT)/'`"; \\
	  \$(LIBTOOL)  --mode=install \$(INSTALL_PROGRAM) \$< \$(DESTDIR)\$(libexecdir)/`echo \$<|sed 's/\$(EXEEXT)\$\$//'|sed '\$(transform)'|sed 's/\$\$/\$(EXEEXT)/'`; \\
	else :; fi
EOT

print IGNORE <<EOT;
Makefile
Makefile.in
.deps
.libs
EOT

foreach (sort keys %plugins) {
    my $libgimp = "";

    if (exists $plugins{$_}->{ui}) {
        $libgimp .= "\$(libgimpui)";
        $libgimp .= "\t\t\t\t\t\t\t\\\n\t\$(libgimpwidgets)";
	$libgimp .= "\t\t\t\t\t\t\\\n\t\$(libgimp)";
        $libgimp .= "\t\t\t\t\t\t\t\\\n\t\$(libgimpcolor)";
        $libgimp .= "\t\t\t\t\t\t\t\\\n\t\$(libgimpbase)";
    } else {
        $libgimp .= "\$(libgimp)";
        $libgimp .= "\t\t\t\t\t\t\t\\\n\t\$(libgimpcolor)";
        $libgimp .= "\t\t\t\t\t\t\t\\\n\t\$(libgimpbase)";
    }

    my $optlib = "";
    if (exists $plugins{$_}->{optional}) {
	my $name = exists $plugins{$_}->{libopt} ? $plugins{$_}->{libopt} : $_;
	$optlib = "\n\t\$(LIB\U$name\E)\t\t\t\t\t\t\t\\";
    }

    my $deplib = "\$(RT_LIBS)\t\t\t\t\t\t\t\\\n\t\$(INTLLIBS)";
    if (exists $plugins{$_}->{libdep}) {
	my @lib = split(/:/, $plugins{$_}->{libdep});
	foreach $lib (@lib) {
	    $deplib = "\$(\U$lib\E_LIBS)\t\t\t\t\t\t\t\\\n\t$deplib";
	}
    }

    if (exists $plugins{$_}->{libsupp}) {
	my @lib = split(/:/, $plugins{$_}->{libsupp});
	foreach $lib (@lib) {
	    $libgimp = "\$(top_builddir)/plug-ins/lib$lib/lib$lib.a\t\\\n\t$libgimp";
	}
    }

    print MK <<EOT;

${_}_SOURCES = \\
	$_.c

${_}_LDADD = \\
	$libgimp							\\$optlib
	$deplib
EOT

    print IGNORE "$_\n";
}

close MK;
close IGNORE;

&write_file($outmk);
&write_file($outignore);
