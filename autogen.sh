#!/bin/sh 

# This script does all the magic calls to automake/autoconf and
# friends that are needed to configure a cvs checkout.  As described in
# the file HACKING you need a couple of extra tools to run this script
# successfully.
#
# If you are compiling from a released tarball you don't need these
# tools and you shouldn't use this script.  Just call ./configure
# directly.


PROJECT="The GIMP"
TEST_TYPE=-d
FILE=plug-ins

LIBTOOL_REQUIRED_VERSION=1.3.4
AUTOCONF_REQUIRED_VERSION=2.52
AUTOMAKE_REQUIRED_VERSION=1.4
AUTOMAKE16_REQUIRED_VERSION=1.6
GLIB_REQUIRED_VERSION=2.0.0
INTLTOOL_REQUIRED_VERSION=0.17

ACLOCAL_INTERNAL_FLAGS=


srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.
ORIGDIR=`pwd`
cd $srcdir


check_version ()
{
    if expr $1 \>= $2 > /dev/null; then
	echo "yes (version $1)"
    else
	echo "Too old (found version $1)!"
	DIE=1
    fi
}

echo
echo "I am testing that you have the required versions of libtool, autoconf," 
echo "automake, glib-gettextize and intltoolize. This test is not foolproof,"
echo "so if anything goes wrong, see the file HACKING for more information..."
echo

DIE=0

echo -n "checking for libtool >= $LIBTOOL_REQUIRED_VERSION ... "
if (libtoolize --version) < /dev/null > /dev/null 2>&1; then
    VER=`libtoolize --version \
         | grep libtool | sed "s/.* \([0-9.]*\)[-a-z0-9]*$/\1/"`
    check_version $VER $LIBTOOL_REQUIRED_VERSION
else
    echo
    echo "  You must have libtool installed to compile $PROJECT."
    echo "  Install the appropriate package for your distribution,"
    echo "  or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
    DIE=1;
fi

echo -n "checking for autoconf >= $AUTOCONF_REQUIRED_VERSION ... "
if (autoconf --version) < /dev/null > /dev/null 2>&1; then
    VER=`autoconf --version \
         | grep -iw autoconf | sed "s/.* \([0-9.]*\)[-a-z0-9]*$/\1/"`
    check_version $VER $AUTOCONF_REQUIRED_VERSION
else
    echo
    echo "  You must have autoconf installed to compile $PROJECT."
    echo "  Download the appropriate package for your distribution,"
    echo "  or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
    DIE=1;
fi

echo -n "checking for automake >= $AUTOMAKE_REQUIRED_VERSION ... "
if (automake-1.6 --version) < /dev/null > /dev/null 2>&1; then
    VER=`automake-1.6 --version \
         | grep automake | sed "s/.* \([0-9.]*\)[-a-z0-9]*$/\1/"`
    check_version $VER $AUTOMAKE16_REQUIRED_VERSION

    AUTOMAKE=automake-1.6
    ACLOCAL=aclocal-1.6
    ACLOCAL_INTERNAL_FLAGS="-I m4compat/1.6"
elif (automake --version) < /dev/null > /dev/null 2>&1; then
    VER=`automake --version \
         | grep automake | sed "s/.* \([0-9.]*\)[-a-z0-9]*$/\1/"`
    check_version $VER $AUTOMAKE_REQUIRED_VERSION

    AUTOMAKE=automake
    ACLOCAL=aclocal
    ACLOCAL_INTERNAL_FLAGS="-I m4compat/1.4"

    echo
    echo "  You do not have automake 1.6."
    echo "  $PROJECT build will work, but the python binding will not be there."
    echo "  Upgrade automake if you want this functionality."
    echo
    echo "  NOTE: you will get warnings from plug-ins/pygimp/Makefile.am."
    echo "  This is normal."
    echo
else
    echo
    echo "  You must have automake installed to compile $PROJECT."
    echo "  Get ftp://ftp.gnu.org/pub/gnu/automake/automake-1.6.3.tar.gz"
    echo "  (or a newer version if it is available)"
    DIE=1
fi

echo -n "checking for glib-gettextize >= $GLIB_REQUIRED_VERSION ... "
if (glib-gettextize --version) < /dev/null > /dev/null 2>&1; then
    VER=`glib-gettextize --version \
         | grep glib-gettextize | sed "s/.* \([0-9.]*\)/\1/"`
    check_version $VER $GLIB_REQUIRED_VERSION
else
    echo
    echo "  You must have glib-gettextize installed to compile $PROJECT."
    echo "  glib-gettextize is part of glib-2.0, so you should already"
    echo "  have it. Make sure it is in your PATH."
    DIE=1
fi

echo -n "checking for intltool >= $INTLTOOL_REQUIRED_VERSION ... "
if (intltoolize --version) < /dev/null > /dev/null 2>&1; then
    VER=`intltoolize --version \
         | grep intltoolize | sed "s/.* \([0-9.]*\)/\1/"`
    check_version $VER $INTLTOOL_REQUIRED_VERSION
else
    echo
    echo "You must have intltool installed to compile $PROJECT."
    echo "Get the latest version from"
    echo "ftp://ftp.gnome.org/pub/GNOME/sources/intltool/"
    DIE=1
fi

if test "$DIE" -eq 1; then
    echo
    echo "Please install/upgrade the missing tools and call me again."
    echo	
    exit 1
fi


test $TEST_TYPE $FILE || {
    echo
    echo "You must run this script in the top-level $PROJECT directory."
    echo
    exit 1
}


if test -z "$*"; then
    echo
    echo "I am going to run ./configure with no arguments - if you wish "
    echo "to pass any to it, please specify them on the $0 command line."
    echo
fi

case $CC in
    *xlc | *xlc\ * | *lcc | *lcc\ *)
	am_opt=--include-deps
    ;;
esac

echo

if test -z "$ACLOCAL_FLAGS"; then

    acdir=`aclocal --print-ac-dir`
    m4list="glib-2.0.m4 glib-gettext.m4 gtk-2.0.m4 intltool.m4 pkg.m4"

    for file in $m4list
    do
	if [ ! -f "$acdir/$file" ]; then
	    echo
	    echo "WARNING: aclocal's directory is $acdir, but..."
            echo "         no file $acdir/$file"
            echo "         You may see fatal macro warnings below."
            echo "         If these files are installed in /some/dir, set the ACLOCAL_FLAGS "
            echo "         environment variable to \"-I /some/dir\", or install"
            echo "         $acdir/$file."
            echo
        fi
    done
fi

if ! $ACLOCAL $ACLOCAL_INTERNAL_FLAGS $ACLOCAL_FLAGS; then
   echo "$ACLOCAL gave errors. Please fix the error conditions and try again."
   exit 1
fi

# optionally feature autoheader
(autoheader --version)  < /dev/null > /dev/null 2>&1 && autoheader

$AUTOMAKE --add-missing $am_opt
autoconf

libtoolize --copy --force
glib-gettextize --copy --force
intltoolize --copy --force --automake

cd $ORIGDIR

$srcdir/configure --enable-maintainer-mode --enable-gtk-doc "$@"

echo
echo "Now type 'make' to compile $PROJECT."
