# ltmain.sh - Provide generalized library-building support services.
# Generated automatically from ltmain.sh.in by configure.
# Copyright (C) 1996, 1997 Free Software Foundation, Inc.
# Gordon Matzigkeit <gord@gnu.ai.mit.edu>, 1996
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
# As a special exception to the GNU General Public License, if you
# distribute this file as part of a program that contains a
# configuration script generated by Autoconf, you may include it under
# the same distribution terms that you use for the rest of that program.

# The name of this program.
progname=`echo "$0" | sed 's%^.*/%%'`

# Constants.
PROGRAM=ltmain.sh
PACKAGE=libtool
VERSION=0.9g

default_mode=NONE
help="Try \`$progname --help' for more information."
ln_s="ln -s"
cp_p="cp -p"
magic="%%%MAGIC variable%%%"
mkdir="mkdir"
mv="mv -f"
objdir=.libs
rm="rm -f"

if test "$LTCONFIG_VERSION" != "$VERSION"; then
  echo "$progname: ltconfig version \`$LTCONFIG_VERSION' does not match $PROGRAM version \`$VERSION'" 1>&2
  echo "Fatal configuration error.  See the $PACKAGE docs for more information." 1>&2
  exit 1
fi

# Global variables.
mode=$default_mode
nonopt=
prev=
prevopt=
run=
show=echo
show_help=

# Parse our command line options once, thoroughly.
while test -n "$1"
do
  arg="$1"
  shift

  case "$arg" in
  -*=*) optarg=`echo "$arg" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
  *) optarg= ;;
  esac

  # If the previous option needs an argument, assign it.
  if test -n "$prev"; then
    eval "$prev=\$arg"
    prev=
    prevopt=
    continue
  fi

  # Have we seen a non-optional argument yet?
  case "$arg" in
  --help)
    show_help=yes
    ;;

  --version)
    echo "$PROGRAM (GNU $PACKAGE) $VERSION"
    exit 0
    ;;

  --dry-run | -n)
    run=:
    ;;

  --features)
    echo "host: $host"
    if test "$build_libtool_libs" = yes; then
      echo "enable shared libraries"
    else
      echo "disable shared libraries"
    fi
    if test "$build_old_libs" = yes; then
      echo "enable static libraries"
    else
      echo "disable static libraries"
    fi
    exit 0
    ;;

  --finish) mode="finish" ;;

  --mode) prevopt="--mode" prev=mode ;;
  --mode=*) mode="$optarg" ;;

  -*)
    echo "$progname: unrecognized option \`$arg'" 1>&2
    echo "$help" 1>&2
    exit 1
    ;;

  *)
    nonopt="$arg"
    break
    ;;
  esac
done


if test -n "$prevopt"; then
  echo "$progname: option \`$prevopt' requires an argument" 1>&2
  echo "$help" 1>&2
  exit 1
fi


if test -z "$show_help"; then

  # Infer the operation mode.
  if test "$mode" = NONE; then
    case "$nonopt" in
    *cc)
      if echo " $@ " | egrep "[ 	]-c[ 	]" > /dev/null 2>&1; then
        mode=compile
      else
        mode=link
      fi
      ;;
    *install*|cp)
      mode=install
      ;;
    *rm)
      mode=uninstall
      ;;
    *)
      # Just use the default operation mode.
      if test "$mode" = NONE; then
	if test -n "$nonopt"; then
	  echo "$progname: warning: cannot infer operation mode from \`$nonopt $@'" 1>&2
	else
	  echo "$progname: warning: cannot infer operation mode from no MODE-ARGS" 1>&2
	fi
      fi
      ;;
    esac
  fi

  # Change the help message to a mode-specific one.
  generic_help="$help"
  help="Try \`$progname --help --mode=$mode' for more information."

  # These modes are in order of execution frequency so that they run quickly.
  case "$mode" in
  # libtool compile mode
  compile)
    # Get the compilation command and the source file.
    base_compile="$nonopt"
    lastarg=
    srcfile=

    for arg
    do
      # Quote any args containing shell metacharacters.
      case "$arg" in
      *" "*|*"	"*|*[\[\]\~\#\$\^\&\*\(\)\{\}\\\|\;\<\>\?]*|*\"*)
	 quote_arg="'$arg'" ;;
      *) quote_arg="$arg" ;;
      esac

      base_compile="$base_compile$lastarg"
      srcfile="$quote_arg"
      lastarg=" $srcfile"
    done

    # Get the name of the library object.
    libobj=`echo "$srcfile" | sed -e 's%^.*/%%'`

    # Recognize several different file suffixes.
    xform='[cCFSf]'
    case "$libobj" in
    *.c++) xform='c++' ;;
    *.cc) xform=cc ;;
    *.cpp) xform=cpp ;;
    *.cxx) xform=cxx ;;
    *.f90) xform=f90 ;;
    *.for) xform='for' ;;
    esac

    libobj=`echo "$libobj" | sed -e "s/\.$xform$/.lo/"`

    case "$libobj" in
    *.lo) obj=`echo "$libobj" | sed -e 's/\.lo$/.o/'` ;;
    *)
      echo "$progname: cannot determine name of library object from \`$srcfile'" 1>&2
      exit 1
      ;;
    esac

    if test -z "$base_compile"; then
      echo "$progname: you must specify a compilation command" 1>&2
      echo "$help" 1>&2
      exit 1
    fi

    # Delete any old library objects.
    $run $rm $obj $libobj
    trap "$run $rm $obj $libobj; exit 1" 1 2 15

    # Only build a PIC object if we are building libtool libraries.
    if test "$build_libtool_libs" = yes; then
      # All platforms use -DPIC, to notify preprocessed assembler code.
      $show "$base_compile$pic_flag -DPIC $srcfile"
      if eval "$run $base_compile$pic_flag -DPIC $srcfile"; then :
      else
	$run $rm $obj
	exit 1
      fi

      # If we have no pic_flag, then copy the object into place and finish.
      if test -z "$pic_flag"; then
	$show "$ln_s $obj $libobj"
	$run $ln_s $obj $libobj || $run $cp_p $obj $libobj
	exit $?
      fi

      # Just move the object, then go on to compile the next one
      $show "$mv $obj $libobj"
      $run $mv $obj $libobj || exit 1
    fi

    # Compile the position-dependent object.
    $show "$base_compile $srcfile"
    if eval "$run $base_compile $srcfile"; then :
    else
      $run $rm $obj $libobj
      exit 1
    fi

    # Symlink or copy the object file into library object, if no PIC.
    if test "$build_libtool_libs" != yes; then
      $show "$ln_s $obj $libobj"
      $run $ln_s $obj $libobj || $run $cp_p $obj $libobj
      exit $?
    fi

    exit 0
    ;;

  # libtool link mode
  link)
    # Go through the arguments, transforming them on the way.
    cc="$nonopt"
    args="$cc"
    compile_command="$cc"
    finalize_command="$cc"
    compile_shlibpath=
    finalize_shlibpath=
    deplibs=
    install_libdir=
    libobjs=
    link_against_libtool_libs=
    link_static=
    ltlibs=
    objs=
    output=
    prev=
    prevarg=
    temp_rpath=
    vinfo=


#    FIXME Maybe set the library names to libNAME_p.a if we are doing profiling.
#    if echo " $@ " | egrep "[ 	]$profile_flag_pattern[	 ]" > /dev/null 2>&1; then
#      suffix=p
#    else
#      suffix=
#    fi

    # We need to know -static, to get the right output filenames.
    case " $@ " in
    *" -static "*) build_libtool_libs=no ;;
    esac

    for arg
    do
      # If the previous option needs an argument, assign it.
      if test -n "$prev"; then
	case "$prev" in
	output)
	  if test "$build_libtool_libs" = yes; then
	    compile_command="$compile_command $objdir/$arg"
	    finalize_command="$finalize_command $objdir/$arg"T
	  else
	    compile_command="$compile_command $arg"
	    finalize_command="$finalize_command $arg"
	  fi
	  args="$args $arg"
	  ;;
	esac

	eval "$prev=\$arg"
	prev=

	continue
      fi

      args="$args $arg"
      prevarg="$arg"

      case "$arg" in
      -L*)
	dir=`echo "$arg" | sed 's%^-L\(.*\)$%\1%'`
	case "$dir" in
	/*)
	  ;;
	*)
	  echo "$progname: \`-L$dir' cannot specify a relative directory" 1>&2
	  exit 1
	  ;;
	esac
	deplibs="$deplibs $arg"
	;;

      -l*) deplibs="$deplibs $arg" ;;

      -o) prev=output ;;

      -rpath)
	prev=install_libdir
	continue
	;;

      -static)
	link_static="`eval echo \"$link_static_flag\"`"
	compile_command="$compile_command $link_static"
	continue
	;;

      -version-file)
	echo "$progname: \`-version-file' has been replaced by \`-version-info'" 1>&2
	echo "$help" 1>&2
	exit 1
	;;

      -version-info)
	prev=vinfo
	continue
	;;

      -*) cc="$cc $arg" ;; # Some other compiler flag.

      *.o | *.a)
	# A standard object.
	objs="$objs $arg"
	;;

      *.lo)
	# A library object.
	libobjs="$libobjs $arg"
	;;

      *.la)
	# A libtool-controlled library.

	libdir=
	library_names=
	old_library=

	# Check to see that this really is a libtool archive.
	if egrep "^# Generated by $PROGRAM" $arg >/dev/null 2>&1; then :
	else
	  echo "$progname: \`$arg' is not a valid libtool archive" 1>&2
	  exit 1
	fi

	# If there is no directory component, then add one.
	case "$arg" in
	*/*) . $arg ;;
	*) . ./$arg ;;
	esac

	if test -z "$libdir"; then
	  echo "$progname: \`$arg' contains no -rpath information" 1>&2
	  exit 1
	fi

	# Get the name of the link library.
	linklib=
	for l in $library_names; do
	  linklib="$l"
	done

	# Find the relevant object directory and library name.
	name=`echo "$arg" | sed 's%^.*/%%; s/\.la$//; s/^lib//'`
	dir=`echo "$arg" | sed 's%/[^/]*$%%'`
	if test "$dir" = "$arg"; then
	  dir="$objdir"
	else
	  dir="$dir/$objdir"
	fi

	link_against_libtool_libs="$link_against_libtool_libs $arg"

	if test "$build_libtool_libs" = yes; then
	  if test -n "$shlibpath_var"; then
	    # Make sure the rpath contains only unique directories.
	    case "$temp_rpath " in
	    "* $dir *") ;;
	    *) temp_rpath="$temp_rpath $dir" ;;
	    esac
	  fi

	  if test -z "$linklib"; then
	    echo "$progname: cannot find name of link library for \`$arg'" 1>&2
	    exit 1
	  fi

	  if test -n "$hardcode_libdir_flag_spec"; then
	    hardcode_libdir_flag=`eval echo \"$hardcode_libdir_flag_spec\"`
	    compile_command="$compile_command $hardcode_libdir_flag"
	    finalize_command="$finalize_command $hardcode_libdir_flag"
	  fi

	  case "$hardcode_action" in
	  immediate)
	    if test "$hardcode_direct" = no; then
	      compile_command="$compile_command $dir/$linklib"
	    elif test "$hardcode_minus_L" = no; then
	      compile_command="$compile_command -L$dir -l$name"
	    elif test "$hardcode_shlibpath_var" = no; then
	      compile_shlibpath="$compile_shlibpath$dir:"
	      compile_command="$compile_command -l$name"
	    fi
	    ;;

	  relink)
	    # We need an absolute path.
	    case "$dir" in
	    /*) ;;
	    *)
	      absdir=`cd "$dir" && pwd`
	      if test -z "$absdir"; then
		echo "$progname: cannot determine absolute directory name of \`$dir'" 1>&2
		exit 1
	      fi
	      dir="$absdir"
	      ;;
	    esac

	    if test "$hardcode_direct" = yes; then
	      compile_command="$compile_command $dir/$linklib"
	    elif test "$hardcode_minus_L" = yes; then
	      compile_command="$compile_command -L$dir -l$name"
	    elif test "$hardcode_shlibpath_var" = yes; then
	      compile_shlibpath="$compile_shlibpath$dir:"
	      compile_command="$compile_command -l$name"
	    fi
	    ;;

	  *)
	    echo "$progname: \`$hardcode_action' is an unknown hardcode action" 1>&2
	    exit 1
	    ;;
	  esac

	  # Finalize command for both is simple: just hardcode it.
	  if test "$hardcode_direct" = yes; then
	    finalize_command="$finalize_command $libdir/$linklib"
	  elif test "$hardcode_minus_L" = yes; then
	    finalize_command="$finalize_command -L$libdir -l$name"
	  elif test "$hardcode_shlibpath_var" = yes; then
	    finalize_shlibpath="$finalize_shlibpath$libdir:"
	    finalize_command="$finalize_command -l$name"
          else
            # We can't seem to hardcode it, guess we'll fake it.
	    finalize_command="$finalize_command -L$libdir -l$name"
	  fi
        else
          # Transform directly to old archives if we don't build new libraries.
	  test -z "$old_library" && old_library="$linklib"
          compile_command="$compile_command $dir/$old_library"
	  finalize_command="$finalize_command $dir/$old_library"
        fi
	continue
	;;

      *)
        echo "$progname: unknown file suffix for \`$arg'" 1>&2
	echo "$help" 1>&2
	exit 1
	;;
      esac

      compile_command="$compile_command $arg"
      finalize_command="$finalize_command $arg"
    done

    if test -n "$prev"; then
      echo "$progname: the \`$prevarg' option requires an argument" 1>&2
      echo "$help" 1>&2
      exit 1
    fi

    oldlib=
    oldobjs=
    case "$output" in
    "")
      echo "$progname: you must specify an output file" 1>&2
      echo "$help" 1>&2
      exit 1
      ;;

    */*)
      echo "$progname: output file \`$output' must have no directory components" 1>&2
      exit 1
      ;;

    *.a)
      # Old archive.
      build_old_libs=yes

      if test -n "$install_libdir"; then
        echo "$progname: warning: \`-rpath' is ignored while linking old-style libraries" 1>&2
      fi

      if test -n "$vinfo"; then
	echo "$progname: warning: \`-version-info' is ignored while linking old-style libraries" 1>&2
      fi
      ;;

    *.la)
      libname=`echo "$output" | sed 's/\.la$//'`

      if test -n "$objs"; then
	echo "$progname: cannot build libtool library \`$output' from non-libtool objects"
	exit 1
      fi

      # How the heck are we supposed to write a wrapper for a shared library?
      if test -n "$link_against_libtool_libs"; then
        echo "$progname: libtool libraries may not depend on uninstalled libraries" 1>&2
	exit 1
      fi

      if test -z "$install_libdir"; then
	echo "$progname: you must specify an installation directory with \`-rpath'" 1>&2
	exit 1
      fi

      current=0
      revision=0
      age=0

      # Parse the version information argument.
      IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=':'
      set dummy $vinfo
      IFS="$save_ifs"

      if test -n "$5"; then
        echo "$progname: too many parameters to \`-version-info'" 1>&2
	echo "$help" 1>&2
	exit 1
      fi

      test -n "$2" && current="$2"
      test -n "$3" && revision="$3"
      test -n "$4" && age="$4"

      # Check that each of the things are valid numbers.
      case "$current" in
      0 | [1-9] | [1-9][0-9]*) ;;
      *)
	echo "$progname: CURRENT \`$current' is not a nonnegative integer" 1>&2
        echo "$progname: \`$vinfo' is not valid version information" 1>&2
        exit 1
	;;
      esac

      case "$revision" in
      0 | [1-9] | [1-9][0-9]*) ;;
      *)
	echo "$progname: REVISION \`$revision' is not a nonnegative integer" 1>&2
        echo "$progname: \`$vinfo' is not valid version information" 1>&2
        exit 1
	;;
      esac

      case "$age" in
      0 | [1-9] | [1-9][0-9]*) ;;
      *)
	echo "$progname: AGE \`$age' is not a nonnegative integer" 1>&2
        echo "$progname: \`$vinfo' is not valid version information" 1>&2
        exit 1
	;;
      esac

      if test $age -gt $current; then
        echo "$progname: AGE \`$age' is greater than the current interface number \`$current'" 1>&2
        echo "$progname: \`$vinfo' is not valid version information" 1>&2
        exit 1
      fi

      # Calculate the version variables.
      version_vars="version_type current age revision"
      case "$version_type" in
      none) ;;

      linux)
	version_vars="$version_vars major versuffix"
	major=`expr $current - $age`
	versuffix="$major.$age.$revision"
	;;

      osf)
	version_vars="$version_vars versuffix verstring"
	major=`expr $current - $age`
	versuffix="$current.$age.$revision"
	verstring="$versuffix"

	# Add in all the interfaces that we are compatible with.
	loop=$age
	while test $loop != 0; do
	  iface=`expr $current - $loop`
	  loop=`expr $loop - 1`
	  verstring="$verstring:${iface}.0"
	done

	# Make executables depend on our current version.
	verstring="$verstring:${current}.0"
	;;

      sunos)
	version_vars="$version_vars major versuffix"
	major="$current"
	versuffix="$current.$revision"
	;;

      *)
	echo "$progname: unknown library version type \`$version_type'" 1>&2
	echo "Fatal configuration error.  See the $PACKAGE docs for more information." 1>&2
	exit 1
	;;
      esac

      # Create the output directory, or remove our outputs if we need to.
      if test -d $objdir; then
        $show "$rm $objdir/$libname.*"
        $run $rm $objdir/$libname.*
      else
        $show "$mkdir $objdir"
	$run $mkdir $objdir || exit $?
      fi

      if test "$build_libtool_libs" = yes; then
	# Get the real and link names of the library.
	library_names=`eval echo \"$library_names_spec\"`
	set dummy $library_names
	realname="$2"
	shift; shift

	if test -n "$soname_spec"; then
	  soname=`eval echo \"$soname_spec\"`
	else
	  soname="$realname"
	fi

	lib="$objdir/$realname"
	linknames=
	for link
	do
	  linknames="$linknames $objdir/$link"
	done

	# Use standard objects if they are PIC.
	test -z "$pic_flag" && libobjs=`echo "$libobjs " | sed 's/\.lo /.o /g; s/ $//g'`

	# Do each of the archive commands.
	cmds=`eval echo \"$archive_cmds\"`
	IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
	for cmd in $cmds; do
	  IFS="$save_ifs"
	  $show "$cmd"
	  eval "$run $cmd" || exit $?
	done
	IFS="$save_ifs"

	# Create links to the real library.
	for link in $linknames; do
	  $show "$ln_s $realname $link"
	  $run $ln_s $realname $link || exit $?
	done
      fi
      ;;

    *.lo | *.o)
      if test -n "$link_against_libtool_libs"; then
	echo "$progname: error: cannot link libtool libraries into reloadable objects" 1>&2
	exit 1
      fi

      if test -n "$deplibs"; then
	echo "$progname: warning: \`-l' and \`-L' are ignored while creating objects" 1>&2
      fi

      if test -n "$install_libdir"; then
        echo "$progname: warning: \`-rpath' is ignored while creating objects" 1>&2
      fi

      if test -n "$vinfo"; then
	echo "$progname: warning: \`-version-info' is ignored while creating objects" 1>&2
      fi

      case "$output" in
      *.lo)
	if test -n "$objs"; then
	  echo "$progname: cannot build library object \`$output' from non-libtool objects" 1>&2
	  exit 1
	fi
	libobj="$output"
	obj=`echo "$output" | sed 's/\.lo$/.o/'`
	;;
      *)
        libobj=
	obj="$output"
	;;
      esac

      # Delete the old objects.
      $run $rm $obj $libobj

      # Create the old-style object.
      reload_objs="$objs"`echo "$libobjs " | sed 's/\.lo /.o /g; s/ $//g'`

      output="$obj"
      cmds=`eval echo \"$reload_cmds\"`
      IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
      for cmd in $cmds; do
        IFS="$save_ifs"
        $show "$cmd"
	eval "$run $cmd" || exit $?
      done
      IFS="$save_ifs"

      # Exit if we aren't doing a library object file.
      test -z "$libobj" && exit 0

      if test "$build_libtool_libs" = yes && test -n "$pic_flag"; then
	# Only do commands if we really have different PIC objects.
	reload_objs="$libobjs"
	output="$libobj"
        cmds=`eval echo \"$reload_cmds\"`
        IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
        for cmd in $cmds; do
          IFS="$save_ifs"
          $show "$cmd"
          eval "$run $cmd" || exit $?
        done
        IFS="$save_ifs"
      else
        # Just create a symlink.
        $show "$ln_s $obj $libobj"
        $run $ln_s $obj $libobj || $run $cp_p $obj $libobj || exit 1
      fi

      exit 0
      ;;

    *)
      if test -n "$install_libdir"; then
        echo "$progname: warning: \`-rpath' is ignored while linking programs" 1>&2
      fi

      if test -n "$vinfo"; then
	echo "$progname: warning: \`-version-info' is ignored while linking programs" 1>&2
      fi

      if test -n "$libobjs"; then
	# Transform all the library objects into standard objects.
	compile_command=`echo "$compile_command " | sed 's/\.lo /.o /g; s/ $//'`
      fi

      # Create the binary in the object directory, then wrap it.
      if test -d $objdir; then :
      else
        $show "$mkdir $objdir"
        $run $mkdir $objdir || exit $?
      fi

      if test -z "$link_against_libtool_libs" || test "$build_libtool_libs" != yes; then
	# We have no uninstalled library dependencies, so finalize right now.
	$show "$compile_command"
	$run $compile_command
	status=$?

	# If we failed to link statically, then try again.
	if test $status -ne 0 && test -n "$link_static"; then
	  echo "$progname: cannot link \`$output' statically; retrying semi-dynamically" 1>&2
	  compile_command=`echo "$compile_command " | sed "s% $link_static % %;s/ $//"`
	  $show "$finalize_command"
	  $run $finalize_command
	  status=$?
	fi
	exit $status
      fi

      if test -n "$shlibpath_var"; then
        # We should set the shlibpath_var
	rpath=
	for dir in $temp_rpath; do
	  case "$dir" in
	  /*)
	    # Absolute path.
	    rpath="$rpath$dir:"
	    ;;
	  *)
	    # Relative path: add a thisdir entry.
	    rpath="$rpath\$thisdir/$dir:"
	    ;;
	  esac
	done
      fi

      # Delete the old output file.
      $run $rm $output

      if test -n "$compile_shlibpath"; then
	compile_command="$shlibpath_var=$compile_shlibpath\$$shlibpath_var $compile_command"
      fi
      if test -n "$finalize_shlibpath"; then
	finalize_command="$shlibpath_var=$finalize_shlibpath\$$shlibpath_var $finalize_command"
      fi

      case "$hardcode_action" in
      relink)
	# AGH! Flame the AIX and HP-UX people for me, will ya?
	echo "$progname: warning: using a buggy system linker" 1>&2
	echo "$progname: relinking will be required before \`$output' can be installed" 1>&2
	;;
      esac

      $show "$compile_command"
      eval "$run $compile_command" || exit $?

      # Now create the wrapper script.
      echo "creating $output"

      # Only actually do things if our run command is non-null.
      if test -z "$run"; then
	$rm $output
	trap "$rm $output; exit 1" 1 2 15

	cat > $output <<EOF
#! /bin/sh

# $output - temporary wrapper script for $objdir/$output
# Generated by $PROGRAM - GNU $PACKAGE $VERSION
#
# The $output program cannot be directly executed until all the libtool
# libraries that it depends on are installed.
#
# This wrapper script should never be moved out of \``pwd`'.
# If it is, it will not operate correctly.

# This environment variable determines our operation mode.
if test "\$libtool_install_magic" = "$magic"; then
  # install mode needs the following variables:
  link_against_libtool_libs="$link_against_libtool_libs"
  finalize_command="$finalize_command"
else
  # Find the directory that this script lives in.
  thisdir=\`echo \$0 | sed 's%/[^/]*$%%'\`
  test "x\$thisdir" = "x\$0" && thisdir=.

  # Try to get the absolute directory name.
  absdir=\`cd "\$thisdir" && pwd\`
  test -n "\$absdir" && thisdir="\$absdir"

  progdir="\$thisdir/$objdir"
  program="$output"

  if test -f "\$progdir/\$program"; then
    # Run the actual program with our arguments.
    args=
    for arg
    do
      # Quote arguments (to preserve shell metacharacters).
      args="\$args '\$arg'"
    done

    # Export the path to the program.
    PATH="\$progdir:\$PATH"
    export PATH
EOF

	# Export our shlibpath_var if we have one.
	if test -n "$shlibpath_var" && test -n "$rpath"; then
	  cat >> $output <<EOF

    # Add our own library path to $shlibpath_var
    $shlibpath_var="$rpath\$$shlibpath_var"
    export $shlibpath_var
EOF
	fi

        cat >> $output <<EOF

    eval "exec \$program \$args"

    echo "\$0: cannot exec \$program \$args"
    exit 1
  else
    # The program doesn't exist.
    echo "\$0: error: \$progdir/\$program does not exist" 1>&2
    echo "This script is just a wrapper for \$program." 1>&2
    echo "See the $PACKAGE documentation for more information." 1>&2
    exit 1
  fi
fi
EOF
	chmod +x $output
      fi
      exit 0
      ;;
    esac


    # See if we need to build an old-fashioned archive.
    if test "$build_old_libs" = "yes"; then
      # Transform .lo files to .o
      oldobjs="$objs"`echo "$libobjs " | sed 's/\.lo /.o /g; s/ $//g'`
      case "$output" in
      *.la)
	# Now set the variables for building old libraries.
	oldlib="$objdir/$libname.a"
	;;
      *)
	oldlib="$output"
	$show "$rm $oldlib"
	$run $rm $oldlib
	;;
      esac

      # Do each command in the archive commands.
      cmds=`eval echo \"$old_archive_cmds\"`
      IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
      for cmd in $cmds; do
        IFS="$save_ifs"
        $show "$cmd"
	eval "$run $cmd" || exit $?
      done
      IFS="$save_ifs"
    fi

    # Now create the libtool archive.
    case "$output" in
    *.la)
      old_library=
      test "$build_old_libs" = yes && old_library="$libname.a"

      echo "creating $output"

      # Only create the output if not a dry run.
      if test -z "$run"; then
	cat > $output <<EOF
# $output - a libtool library file
# Generated by $PROGRAM - GNU $PACKAGE $VERSION

# Names of this library.
library_names='$library_names'

# The name of the static archive.
old_library='$old_library'

# Version information for $libname.
current=$current
age=$age
revision=$revision

# Directory that this library needs to be installed in:
libdir='$install_libdir'
EOF
      fi
      ;;
    esac
    exit 0
    ;;

  # libtool install mode
  install)

    # The first argument is the name of the installation program.
    install_prog="$nonopt"

    # We need to accept at least all the BSD install flags.
    dest=
    files=
    opts=
    prev=
    install_type=
    isdir=
    stripme=
    for arg
    do
      if test -n "$dest"; then
        files="$files $dest"
	dest="$arg"
	continue
      fi

      case "$arg" in
      -d) isdir=yes ;;
      -f) prev="-f" ;;
      -g) prev="-g" ;;
      -m) prev="-m" ;;
      -o) prev="-o" ;;
      -s)
	stripme=" -s"
	continue
	;;
      -*) ;;

      *)
	# If the previous option needed an argument, then skip it.
	if test -n "$prev"; then
	  prev=
	else
	  dest="$arg"
	  continue
	fi
        ;;
      esac
      install_prog="$install_prog $arg"
    done

    if test -z "$install_prog"; then
      echo "$progname: you must specify an install program" 1>&2
      echo "$help" 1>&2
      exit 1
    fi

    if test -n "$prev"; then
      echo "$progname: the \`$prev' option requires an argument" 1>&2
      echo "$help" 1>&2
      exit 1
    fi

    if test -z "$files"; then
      if test -z "$dest"; then
        echo "$progname: no file or destination specified" 1>&2
      else
	echo "$progname: you must specify a destination" 1>&2
      fi
      echo "$help" 1>&2
      exit 1
    fi

    # Strip any trailing slash from the destination.
    dest=`echo "$dest" | sed 's%/$%%'`

    # Check to see that the destination is a directory.
    test -d "$dest" && isdir=yes
    if test -n "$isdir"; then
      destdir="$dest"
    else
      destdir=`echo "$dest" | sed 's%/[^/]*$%%'`
    fi
    case "$destdir" in
    /*) ;;
    *)
      echo "$progname: $destdir must be an absolute directory name" 1>&2
      echo "$help" 1>&2
      exit 1
    esac

    staticlibs=
    future_libdirs=
    current_libdirs=
    for file in $files; do

      # Do each installation.
      case "$file" in
      *.a)
	# Do the static libraries later.
	staticlibs="$staticlibs $file"
	;;

      *.la)
	# Check to see that this really is a libtool archive.
	if egrep "^# Generated by $PROGRAM" $file >/dev/null 2>&1; then :
	else
	  echo "$progname: \`$file' is not a valid libtool archive" 1>&2
	  echo "$help" 1>&2
	  exit 1
	fi

	library_names=
	old_library=
	# If there is no directory component, then add one.
	case "$file" in
	*/*) . $file ;;
	*) . ./$file ;;
	esac

	# Add the libdir to current_libdirs if it is the destination.
	if test "$destdir" = "$libdir"; then
	  case "$current_libdirs " in
	  "* $libdir *") ;;
	  *) current_libdirs="$current_libdirs $libdir" ;;
	  esac
	else
	  # Note the libdir as a future libdir.
	  case "$future_libdirs " in
	  "* $libdir *") ;;
	  *) future_libdirs="$future_libdirs $libdir" ;;
	  esac
	fi

	dir="`echo "$file" | sed 's%/[^/]*$%%'`/"
	test "$dir" = "$file/" && dir=
	dir="$dir$objdir"

	# See the names of the shared library.
	set dummy $library_names
	if test -n "$2"; then
	  realname="$2"
	  shift
	  shift

	  # Install the shared library and build the symlinks.
	  $show "$install_prog $dir/$realname $destdir/$realname"
	  eval "$run $install_prog $dir/$realname $destdir/$realname" || exit $?

	  # Support stripping libraries.
	  if test -n "$stripme"; then
	    if test -n "$striplib"; then
	      $show "$striplib $destdir/$realname"
	      $run $striplib $destdir/$realname || exit $?
	    else
	      echo "$progname: warning: no library stripping program" 1>&2
	    fi
	  fi

	  if test -n "$1"; then
	    # Delete the old symlinks.
            rmcmd="$rm"
            for linkname
            do
              rmcmd="$rmcmd $destdir/$linkname"
            done
            $show "$rmcmd"
            $run $rmcmd

	    # ... and create new ones.
	    for linkname
	    do
	      $show "$ln_s $realname $destdir/$linkname"
	      $run $ln_s $realname $destdir/$linkname
	    done
	  fi

	  # Do each command in the postinstall commands.
	  lib="$destdir/$realname"
	  cmds=`eval echo \"$postinstall_cmds\"`
	  IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
	  for cmd in $cmds; do
	    IFS="$save_ifs"
	    $show "$cmd"
	    eval "$run $cmd" || exit $?
	  done
	  IFS="$save_ifs"
	fi

	# Install the pseudo-library for information purposes.
	name=`echo "$file" | sed 's%^.*/%%'`
	$show "$install_prog $file $destdir/$name"
	$run $install_prog $file $destdir/$name || exit $?

	# Maybe install the static library, too.
	test -n "$old_library" && staticlibs="$staticlibs $dir/$old_library"
	;;

      *)
	# Do a test to see if this is really a libtool program.
	if egrep "^# Generated by $PROGRAM" $file >/dev/null 2>&1; then
	  # This variable tells wrapper scripts just to set variables rather
	  # than running their programs.
	  libtool_install_magic="$magic"
	  link_against_libtool_libs=
	  finalize_command=

	  # If there is no directory component, then add one.
	  case "$file" in
	  */*) . $file ;;
	  *) . ./$file ;;
	  esac

	  # Check the variables that should have been set.
	  if test -z "$link_against_libtool_libs" || test -z "$finalize_command"; then
	    echo "$progname: invalid libtool wrapper script \`$file'" 1>&2
	    exit 1
	  fi

	  finalize=yes
	  for lib in $link_against_libtool_libs; do
	    # Check to see that each library is installed.
	    libdir=
	    if test -f "$lib"; then
	      # If there is no directory component, then add one.
	      case "$lib" in
	      */*) . $lib ;;
	      *) . ./$lib ;;
	      esac
	    fi
	    libfile="$libdir/`echo "$lib" | sed 's%^.*/%%g'`"
	    if test -z "$libdir"; then
	      echo "$progname: warning: \`$lib' contains no -rpath information" 1>&2
	    elif test -f "$libfile"; then :
	    else
	      echo "$progname: warning: \`$lib' has not been installed in \`$libdir'" 1>&2
	      finalize=no
	    fi
	  done

	  if test "$hardcode_direct" != no && test "$hardcode_minus_L" != no && test "$hardcode_shlibpath_var" != no; then
	    if test "$finalize" = no; then
	      echo "$progname: warning: cannot relink \`$file' on behalf of your buggy system linker" 1>&2
	    else
	      echo "$progname: warning: relinking \`$file' on behalf of your buggy system linker" 1>&2
	      $show "$finalize_command"
	      if $run $finalize_command; then :
	      else
		echo "$progname: error: relink \`$file' with the above command before installing it" 1>&2
		continue
	      fi
	      file="$objdir/$file"T
	    fi
	  else
	    # Install the binary that we compiled earlier.
	    dir=`echo "$file" | sed 's%/[^/]*$%%'`
	    if test "$file" = "$dir"; then
	      file="$objdir/$file"
	    else
	      file="$dir/$objdir/`echo "$file" | sed 's%^.*/%%'`"
	    fi
	  fi
	fi

	$show "$install_prog$stripme $file $dest"
	$run $install_prog$stripme $file $dest || exit $?
	;;
      esac
    done

# FIXME Install any profiled libraries, too.
#    newfiles=
#    for file in $staticlibs; do
#      newfiles="$newfiles $file"
#      pfile=`echo "$file" | sed 's/\.a$/_p.a/'`
#      test -f "$pfile" && newfiles="$newfiles $pfile"
#    done
#    staticlibs="$newfiles"

    for file in $staticlibs; do
      name=`echo "$file" | sed 's%^.*/%%'`

      # Set up the ranlib parameters.
      oldlib="$destdir/$name"

      $show "$install_prog $file $oldlib"
      $run $install_prog $file $oldlib || exit $?

      # Support stripping libraries.
      if test -n "$stripme"; then
	if test -n "$old_striplib"; then
	  $show "$old_striplib $oldlib"
	  $run $old_striplib $oldlib || exit $?
	else
	  echo "$progname: warning: no static library stripping program" 1>&2
	fi
      fi

      # Do each command in the postinstall commands.
      cmds=`eval echo \"$old_postinstall_cmds\"`
      IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
      for cmd in $cmds; do
        IFS="$save_ifs"
        $show "$cmd"
        eval "$run $cmd" || exit $?
      done
      IFS="$save_ifs"
    done

    if test -n "$future_libdirs"; then
      echo "$progname: warning: remember to run \`$progname --finish$future_libdirs'" 1>&2
    fi

    if test -n "$current_libdirs"; then
      # Maybe just do a dry run.
      test -n "$run" && current_libdirs=" -n$current_libdirs"
      exec $0 --finish$current_libdirs
      exit 1
    fi

    exit 0
    ;;

  # libtool finish mode
  finish)
    libdirs="$nonopt"

    if test -n "$finish_cmds" && test -n "$libdirs"; then
      for dir
      do
	libdirs="$libdirs $dir"
      done

      for libdir in $libdirs; do
	# Do each command in the postinstall commands.
	cmds=`eval echo \"$finish_cmds\"`
	IFS="${IFS= 	}"; save_ifs="$IFS"; IFS=';'
	for cmd in $cmds; do
	  IFS="$save_ifs"
	  $show "$cmd"
	  eval "$run $cmd"
	done
	IFS="$save_ifs"
      done
    fi

    echo "To link against installed libraries in LIBDIR, users may have to:"
    if test -n "$shlibpath_var"; then
      echo "   - add LIBDIR to their \`$shlibpath_var' environment variable"
    fi
    echo "   - use the \`-LLIBDIR' linker flag"
    exit 0
    ;;

  # libtool uninstall mode
  uninstall)
    rm="$nonopt"
    files=

    for arg
    do
      case "$arg" in
      -*) rm="$rm $arg" ;;
      *) files="$files $arg" ;;
      esac
    done

    if test -z "$rm"; then
      echo "$progname: you must specify an RM program" 1>&2
      echo "$help" 1>&2
      exit 1
    fi

    for file in $files; do
      dir=`echo "$file" | sed -e 's%/[^/]*$%%'`
      test "$dir" = "$file" && dir=.
      name=`echo "$file" | sed -e 's%^.*/%%'`

      case "$name" in
      *.la)
	# Possibly a libtool archive, so verify it.
	if egrep "^# Generated by $PROGRAM" $file >/dev/null 2>&1; then
	  . $dir/$name

	  # Delete the libtool libraries and symlinks.
	  for n in $library_names; do
	    $show "$rm $dir/$n"
	    $run $rm $dir/$n
	  done

	  # Delete the old-fashioned archive.
	  if test -n "$old_library"; then
	    $show "$rm $dir/$old_library"
	    $run $rm $dir/$old_library
	  fi
	fi
	;;
      esac

      $show "$rm $file"
      $run $rm $file
    done
    exit 0
    ;;

  NONE)
    echo "$progname: you must specify a MODE" 1>&2
    echo "$generic_help" 1>&2
    exit 1
    ;;
  esac

  echo "$progname: invalid operation mode \`$mode'" 1>&2
  echo "$generic_help" 1>&2
  exit 1
fi # test -z "$show_help"

# We need to display help for each of the modes.
case "$mode" in
NONE) cat <<EOF
Usage: $progname [OPTION]... [MODE-ARG]...

Provide generalized library-building support services.

-n, --dry-run         display commands without modifying any files
    --features        display configuration information and exit
    --finish          same as \`--mode=finish'
    --help            display this help message and exit
    --mode=MODE       use operation mode MODE [default=inferred from MODE-ARGS]
    --version         print version information

MODE must be one of the following:

      compile         compile a source file into a libtool object
      finish          complete the installation of libtool libraries
      install         install libraries or executables
      link            create a library or an executable
      uninstall       remove libraries from an installed directory

MODE-ARGS vary depending on the MODE.  Try \`$progname --help --mode=MODE' for
a more detailed description of MODE.
EOF
  ;;

compile)
  cat <<EOF
Usage: $progname [OPTION]... --mode=compile COMPILE-COMMAND... SOURCEFILE

Compile a source file into a libtool library object.

COMPILE-COMMAND is a command to be used in creating a \`standard' object file
from the given SOURCEFILE.

The output file name is determined by removing the directory component from
SOURCEFILE, then substituting the C source code suffix \`.c' with the
library object suffix, \`.lo'.
EOF
  ;;

finish)
  cat <<EOF
Usage: $progname [OPTION]... --mode=finish [LIBDIR]...

Complete the installation of libtool libraries.

Each LIBDIR is a directory that contains libtool libraries.

The commands that this mode executes may require superuser privileges.  Use
the \`--dry-run' option if you just want to see what would be executed.
EOF
  ;;

install)
  cat <<EOF
Usage: $progname [OPTION]... --mode=install INSTALL-COMMAND...

Install executables or libraries.

INSTALL-COMMAND is the installation command.  The first component should be
either the \`install' or \`cp' program.

The rest of the components are interpreted as arguments to that command (only
BSD-compatible install options are recognized).
EOF
  ;;

link)
  cat <<EOF
Usage: $progname [OPTION]... --mode=link LINK-COMMAND...

Link object files or libraries together to form another library, or to
create an executable program.

LINK-COMMAND is a command using the C compiler that you would use to create
a program from several object files.

The following components of LINK-COMMAND are treated specially:

  -LLIBDIR        search LIBDIR for required installed libraries
  -lNAME          OUTPUT-FILE requires the installed library libNAME
  -o OUTPUT-FILE  create OUTPUT-FILE from the specified objects
  -rpath LIBDIR   the created library will eventually be installed in LIBDIR
  -static         do not do any dynamic linking or shared library creation
  -version-info CURRENT[:REVISION[:AGE]]
		  specify library version info [each variable defaults to 0]

All other options (arguments beginning with \`-') are ignored.

Every other argument is treated as a filename.  Files ending in \`.la' are
treated as uninstalled libtool libraries, other files are standard or library
object files.

If the OUTPUT-FILE ends in \`.la', then a libtool library is created, only
library objects (\`.lo' files) may be specified, and \`-rpath' is required.

If OUTPUT-FILE ends in \`.a', then a standard library is created using \`ar'
and \`ranlib'.

If OUTPUT-FILE ends in \`.lo' or \`.o', then a reloadable object file is
created, otherwise an executable program is created.
EOF
  ;;

uninstall)
  cat <<EOF
Usage: $progname [OPTION]... --mode=uninstall RM [RM-OPTION]... FILE...

Remove libraries from an installation directory.

RM is the name of the program to use to delete files associated with each FILE
(typically \`/bin/rm').  RM-OPTIONS are options (such as \`-f') to be passed
to RM.

If FILE is a libtool library, all the files associated with it are deleted.
Otherwise, only FILE itself is deleted using RM.
EOF
  ;;

*)
  echo "$progname: invalid operation mode \`$mode'" 1>&2
  echo "$help" 1>&2
  exit 1
  ;;
esac

case "$mode" in
archive|compile)
  echo
  echo "Try \`$progname --help' for more information about other modes."
  ;;
esac

exit 0

# Local Variables:
# mode:shell-script
# sh-indentation:2
# End:
