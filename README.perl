NAME

       Gimp - Perl extension for writing Gimp Extensions/Plug-ins/Load &
       Save-Handlers

SYNOPSIS

       my $img = new Image (600, 300, RGB);
       my $bg = $img->layer_new(600,300,RGB_IMAGE,"Background",100,NORMAL_MODE);
       $img->add_layer($bg, 1);
       $img->edit_fill($bg);
       $img->display_new;

DOCUMENTATION

       The Manpages in html format, the newest version, links and more
       information can be found on the gimp-perl homepage, where you
       should get an overview over the gimp-perl extension:

       http://gimp.pages.de/
       -or-
       http://www.goof.com/pcg/marc/gimp.html
       
PREREQUISITES

       To install/use this perl extension, you need to have the following
       software packages installed (the given order is best):

       Perl5.004 (or higher):

          While this extension should run fine with older versions (it has
          been tested with 5.004_04), I work with Perl5.005 or higher,
          which has much more bugs fixed than the old 5.004.

          When in doubt, upgrade.

       GTK+, the X11 toolkit:
       http://www.gtk.org/
       ftp://ftp.gimp.org/pub/gtk/

          gtk+-1.2 or higher is recommended, but older versions mostly
          work (some features not implemented in gtk+-1.0 do not work
          properly, of course).

       Gtk, the perl extension for the above:
       ftp://ftp.gimp.org/pub/gtk/perl/

          Gtk-0.5120 (or higher) is recommended. You might encounter some
          problems compiling it for Perl5.004 (or any version), in that
          case you might want to try the updated gnome-perl version on the
          gnome-cvs-server. See the the gimp-perl pages for more info.

       The GNU Image Manipulation Program, i.e. The GIMP:
       http://www.gimp.org/
       ftp://ftp.gimp.org/pub/gimp/

          gimp-1.1 (or newer, e.g. CVS or CVS snapshots) is recommended
          for full functionality, but any version since 1.0.2 should do,
          some features not implemented in 1.0 don't work, though.

       PDL, the Perl Data Language
       http://www.cpan.org/

          Optionally, you can install the PDL module to be able to
          manipulate pixel data (or to be able to run the example plug-ins
          that do pixel manipulation). PDL is available at any CPAN
          mirror, version 1.9906 or higher is recommended. Without PDL,
          some plug-ins do not work, and accessing raw image data is
          impossible.

INSTALLATION

       On unix, you should be able to run "perl Makefile.PL" make, make
       test && make install. To get a listing of configuration options,
       enter

       perl ./Makefile.PL --help
       
       a straight "perl Makefile.PL" should do the job on most systems,
       but watch out for warnings. If everything went fine, enter "make",
       "make test", "make install".

       After installation, these perl plug-ins should be visible from
       within the Gimp (and many, many more):

       <Toolbox>/Xtns/Perl Control Center
       <Toolbox>/Xtns/Perl-Server
       <Image>/Filters/Artistic/Windify
       <Image>/Filters/Misc/Prepare for GIF
       <Image>/Filters/Misc/Webify
       
       If you don't have unix, you can install linux instead
       (http://www.linux.org/)

OVERWRITING INSTALL LOCATIONS (PREFIX)

       In the rare case that you want to install the Gimp-Perl modules
       somewhere else than in the standard location then there is a
       standard way to accomplish this.

       Usually, you can just use the PREFIX=/path option to the
       Makefile.PL, or the other common solution of adding the INST* path
       definitions onto the "make install" commandline.

       These options are described in the "perldoc ExtUtils::MakeMaker"
       manpage.

       If you are configuring the gimp-pelr module that comes with the
       Gimp sourcetree this won't work. In that case you can set the
       environment variable:

       PERL_MM_OPT='whatever options you want to pass to MakeMaker'

       before running configure. The arguments that you put into that
       variable will be passed to the Makefile.PL as if given on the
       commandline.

SUPPORT/MAILING LISTS/MORE INFO

       There is a mailinglist for general discussion about Gimp-Perl.  To
       subscribe, send a mail with the single line

       subscribe
       
       to gimp-perl-request@lists.netcentral.net.

       If you want to get notified of new versions automatically, send a
       mail with the single line:

       subscribe notify-gimp
       
       to majordomo@gcc.ml.org.
       
       You can also upload your scripts to the gimp registry at
       http://registry.gimp.org/, part of it is dedicated to gimp-perl.

BLURB

       Scheme is the crappiest language ever. Have a look at Haskell
       (http://www.haskell.org) to see how functional is done right.

LICENSE

       The gimp-perl module is currently available under the GNU Public
       License (see COPYING.GPL for details) and the Artistic License (see
       COPYING.Artistic for details). Many of the scripts in the example
       section follow these rules, but some of them have a different
       licensing approach, please consult their source for more info.

THREATS

       Future versions of this package might be distributed under the
       terms of the GPL only, to be consistent with the rest of the
       Gimp. Andreas keeps me from doing this, though.


       (c)1998,1999 Marc Lehmann <pcg@goof.com>

