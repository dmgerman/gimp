# The GIMP -- an image manipulation program
# Copyright (C) 1998-2003 Manish Singh <yosh@gimp.org>

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

package Gimp::CodeGen::app;

$destdir = "$main::destdir/app/pdb";

*arg_types = \%Gimp::CodeGen::pdb::arg_types;
*arg_parse = \&Gimp::CodeGen::pdb::arg_parse;

*enums = \%Gimp::CodeGen::enums::enums;

*write_file = \&Gimp::CodeGen::util::write_file;
*FILE_EXT   = \$Gimp::CodeGen::util::FILE_EXT;

use Text::Wrap qw(wrap);

sub quotewrap {
    my ($str, $indent) = @_;
    my $leading = ' ' x $indent . '"';
    $Text::Wrap::columns = 1000;
    $str = wrap($leading, $leading, $str);
    $str =~ s/^\s*//s;
    $str =~ s/(.)$/$1"/mg;
    $str;
}

sub format_code_frag {
    my ($code, $indent) = @_;

    chomp $code;
    $code =~ s/\t/' ' x 8/eg;

    if (!$indent && $code =~ /^\s*{\s*\n.*\n\s*}\s*$/s) {
	$code =~ s/^\s*{\s*\n//s;
	$code =~ s/\n\s*}\s*$//s;
    }
    else {
	$code =~ s/^/' ' x ($indent ? 4 : 2)/meg;
    }
    $code .= "\n";

    $code =~ s/^\s+$//mg;

    $code;
}

sub declare_args {
    my $proc = shift;
    my $out = shift;
    my $init = shift;

    local $result = "";

    foreach (@_) {
	my @args = @{$proc->{$_}} if exists $proc->{$_};

	foreach (@args) {
	    my ($type, $name) = &arg_parse($_->{type});
	    my $arg = $arg_types{$type};

	    if ($arg->{array} && !exists $_->{array}) {
		warn "Array without number of elements param in $proc->{name}";
	    }

	    unless (exists $_->{no_declare}) {
		$result .= ' ' x 2 . $arg->{type} . $_->{name};
		if ($init) {
		    $result .= " = $arg->{init_value}";
		}
		$result .= ";\n";

		if (exists $arg->{headers}) {
		    foreach (@{$arg->{headers}}) {
			$out->{headers}->{$_}++;
		    }
		}
	    }
	}
    }

    $result;
}

sub make_desc {
    my $arg = shift;
    my ($type, $name, @remove) = &arg_parse($arg->{type});
    my $desc = $arg->{desc};
    my $info = $arg->{type};

    for ($type) {
	/array/     && do { 				     last };
	/boolean/   && do { $info = '(TRUE or FALSE)';	     last };
	/int|float/ && do { $info =~ s/$type/$arg->{name}/e;
			    $info = '('. $info . ')';        last };
	/enum/      && do { my $enum = $enums{$name};
			    $info = '{ ' . $enum->{info};
			    foreach (@remove) {
				$info =~ s/$_ \(.*?\)(, )?//
			    }				 
			    $info =~ s/, $//;
			    $info .= ' }';                   last };
    }

    $desc =~ s/%%desc%%/$info/eg;

    $desc;
}

sub marshal_inargs {
    my ($proc, $argc) = @_;

    my $result = "";
    my %decls;

    my @inargs = @{$proc->{inargs}} if exists $proc->{inargs};

    foreach (@inargs) {
	my($pdbtype, @typeinfo) = &arg_parse($_->{type});
	my $arg = $arg_types{$pdbtype};
	my $var = $_->{name};
	my $value;

	$value = "&args[$argc].value";
	$result .= eval qq/"  $arg->{get_value_func};\n"/;

	$argc++;

	if (!exists $_->{no_success}) {
	    $success = 1;
	}
    }

    $result = "\n" . $result . "\n" if $result;
    $result;
}

sub marshal_outargs {
    my $proc = shift;

    my $result = <<CODE;
  return_vals = gimp_procedure_get_return_values (procedure, success);
CODE

    my $argc = 0;
    my @outargs = @{$proc->{outargs}} if exists $proc->{outargs};

    if (scalar @outargs) {
	my $outargs = "";

	foreach (@{$proc->{outargs}}) {
	    my ($pdbtype) = &arg_parse($_->{type});
	    my $arg = $arg_types{$pdbtype};
	    my $var = $_->{name};
	    my $value;

	    $argc++;

	    $value = "&return_vals[$argc].value";

	    $outargs .= eval qq/"  $arg->{set_value_func};\n"/;
	}

	$outargs =~ s/^/' ' x 2/meg if $success;
	$outargs =~ s/^/' ' x 2/meg if $success && $argc > 1;

	$result .= "\n" if $success || $argc > 1;
	$result .= ' ' x 2 . "if (success)\n" if $success;
	$result .= ' ' x 4 . "{\n" if $success && $argc > 1;
	$result .= $outargs;
	$result .= ' ' x 4 . "}\n" if $success && $argc > 1;
        $result .= "\n" . ' ' x 2 . "return return_vals;\n";
    }
    else {
	$result =~ s/_vals =//;
    }

    $result =~ s/, success\);$/, TRUE);/m unless $success;
    $result;
}

sub generate_pspec {
    my $arg = shift;
    my ($pdbtype, @typeinfo) = &arg_parse($arg->{type});
    my $name = $arg->{canonical_name};
    my $nick = $arg->{canonical_name};
    my $blurb = &make_desc($arg);
    my $min;
    my $max;
    my $default;
    my $flags = 'GIMP_PARAM_READWRITE';
    my $pspec = "";
    my $postproc = "";

    $nick =~ s/-/ /g;

    if (exists $arg->{no_success}) {
	$flags .= ' | GIMP_PARAM_NO_VALIDATE';
    }

    if ($pdbtype eq 'image') {
	$pspec = <<CODE;
gimp_param_spec_image_id ("$name",
                          "$nick",
                          "$blurb",
                          gimp,
                          GIMP_PARAM_READWRITE)
CODE
    }
    elsif ($pdbtype eq 'drawable') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_DRAWABLE,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'layer') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_LAYER,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'channel') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_CHANNEL,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'layer_mask') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_LAYER_MASK,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'selection') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_CHANNEL,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'vectors') {
	$pspec = <<CODE;
gimp_param_spec_item_id ("$name",
                         "$nick",
                         "$blurb",
                         gimp,
                         GIMP_TYPE_VECTORS,
                         $flags)
CODE
    }
    elsif ($pdbtype eq 'display') {
	$pspec = <<CODE;
gimp_param_spec_display_id ("$name",
                            "$nick",
                            "$blurb",
                            gimp,
                            $flags)
CODE
    }
    elsif ($pdbtype eq 'tattoo') {
	$pspec = <<CODE;
g_param_spec_uint ("$name",
                   "$nick",
                   "$blurb",
                   1, G_MAXUINT32, 1,
                   $flags)
CODE
    }
    elsif ($pdbtype eq 'guide') {
	$pspec = <<CODE;
g_param_spec_uint ("$name",
                   "$nick",
                   "$blurb",
                   1, G_MAXUINT32, 1,
                   $flags)
CODE
    }
    elsif ($pdbtype eq 'float') {
	$min = defined $typeinfo[0] ? $typeinfo[0] : -G_MAXDOUBLE;
	$max = defined $typeinfo[2] ? $typeinfo[2] : G_MAXDOUBLE;
	$default = exists $arg->{default} ? $arg->{default} : defined $typeinfo[0] ? $typeinfo[0] : 0.0;
	$pspec = <<CODE;
g_param_spec_double ("$name",
                     "$nick",
                     "$blurb",
                     $min, $max, $default,
                     $flags)
CODE
    }
    elsif ($pdbtype eq 'int32') {
	$min = defined $typeinfo[0] ? $typeinfo[0] : G_MININT32;
	$max = defined $typeinfo[2] ? $typeinfo[2] : G_MAXINT32;
	$default = exists $arg->{default} ? $arg->{default} : defined $typeinfo[0] ? $typeinfo[0] : 0;
	$pspec = <<CODE;
g_param_spec_int ("$name",
                  "$nick",
                  "$blurb",
                  $min, $max, $default,
                  $flags)
CODE
    }
    elsif ($pdbtype eq 'int16') {
	$min = defined $typeinfo[0] ? $typeinfo[0] : G_MININT16;
	$max = defined $typeinfo[2] ? $typeinfo[2] : G_MAXINT16;
	$default = exists $arg->{default} ? $arg->{default} : defined $typeinfo[0] ? $typeinfo[0] : 0;
	$pspec = <<CODE;
g_param_spec_int ("$name",
                  "$nick",
                  "$blurb",
                  $min, $max, $default,
                  $flags)
CODE
    }
    elsif ($pdbtype eq 'int8') {
	$min = defined $typeinfo[0] ? $typeinfo[0] : G_MINUINT8;
	$max = defined $typeinfo[2] ? $typeinfo[2] : G_MAXUINT8;
	$default = exists $arg->{default} ? $arg->{default} : defined $typeinfo[0] ? $typeinfo[0] : 0;
	$pspec = <<CODE;
g_param_spec_uint ("$name",
                   "$nick",
                   "$blurb",
                   $min, $max, $default,
                   $flags)
CODE
    }
    elsif ($pdbtype eq 'boolean') {
	$default = exists $arg->{default} ? $arg->{default} : FALSE;
	$pspec = <<CODE;
g_param_spec_boolean ("$name",
                      "$nick",
                      "$blurb",
                      $default,
                      $flags)
CODE
    }
    elsif ($pdbtype eq 'string') {
	$no_validate = exists $arg->{no_validate} ? 'TRUE' : 'FALSE';
	$null_ok = exists $arg->{null_ok} ? 'TRUE' : 'FALSE';
	$default = exists $arg->{default} ? $arg->{default} : NULL;
	$pspec = <<CODE;
gimp_param_spec_string ("$name",
                        "$nick",
                        "$blurb",
                        $no_validate, $null_ok,
                        $default,
                        $flags)
CODE
    }
    elsif ($pdbtype eq 'enum') {
	$enum_type = $typeinfo[0];
	$enum_type =~ s/([a-z])([A-Z])/$1_$2/g;
	$enum_type =~ s/([A-Z]+)([A-Z])/$1_$2/g;
	$enum_type =~ tr/[a-z]/[A-Z]/;
	$enum_type =~ s/^GIMP/GIMP_TYPE/;
	$default = exists $arg->{default} ? $arg->{default} : $enums{$typeinfo[0]}->{symbols}[0];

	my ($foo, $bar, @remove) = &arg_parse($arg->{type});

	foreach (@remove) {
	    $postproc .= 'gimp_param_spec_enum_exclude_value (GIMP_PARAM_SPEC_ENUM ($pspec),';
	    $postproc .= "\n                                    $_);\n";
	}

	if ($postproc eq '') {
	    $pspec = <<CODE;
g_param_spec_enum ("$name",
                   "$nick",
                   "$blurb",
                   $enum_type,
                   $default,
                   $flags)
CODE
	}
	else {
	    $pspec = <<CODE;
gimp_param_spec_enum ("$name",
                      "$nick",
                      "$blurb",
                      $enum_type,
                      $default,
                      $flags)
CODE
        }
    }
    elsif ($pdbtype eq 'unit') {
	$typeinfo[0] = 'GIMP_UNIT_PIXEL' unless defined $typeinfo[0];
	$allow_pixels = $typeinfo[0] eq 'GIMP_UNIT_PIXEL' ? TRUE : FALSE;
	$allow_percent = exists $arg->{allow_percent} ? TRUE : FALSE;
	$default = exists $arg->{default} ? $arg->{default} : $typeinfo[0];
	$pspec = <<CODE;
gimp_param_spec_unit ("$name",
                      "$nick",
                      "$blurb",
                      $allow_pixels,
                      $allow_percent,
                      $default,
                      $flags)
CODE
    }
    elsif ($pdbtype eq 'color') {
	$default = exists $arg->{default} ? $arg->{default} : NULL;
	$pspec = <<CODE;
gimp_param_spec_rgb ("$name",
                     "$nick",
                     "$blurb",
                     $default,
                     $flags)
CODE
    }
    elsif ($pdbtype eq 'parasite') {
	$pspec = <<CODE;
gimp_param_spec_parasite ("$name",
                          "$nick",
                          "$blurb",
                          $flags)
CODE
    }
    elsif ($pdbtype eq 'int32array' ||
	   $pdbtype eq 'int16array' ||
	   $pdbtype eq 'int8array'  ||
	   $pdbtype eq 'floatarray' ||
	   $pdbtype eq 'stringarray') {
	$pspec = <<CODE;
g_param_spec_pointer ("$name",
                      "$nick",
                      "$blurb",
                      $flags)
CODE
    }
    else {
	warn "Unsupported PDB type: $arg->{name} ($arg->{type})";
	exit -1;
    }

    $pspec = "GIMP_PDB_$arg_types{$pdbtype}->{name},\n" . $pspec;
    $pspec =~ s/\s$//;

    return ($pspec, $postproc);
}

sub generate {
    my @procs = @{(shift)};
    my %out;
    my $total = 0.0;
    my $argc;

    foreach $name (@procs) {
	my $proc = $main::pdb{$name};
	my $out = \%{$out{$proc->{group}}};

	my @inargs = @{$proc->{inargs}} if exists $proc->{inargs};
	my @outargs = @{$proc->{outargs}} if exists $proc->{outargs};
	
	local $success = 0;

	$out->{pcount}++; $total++;

	$out->{procs} .= "static GimpProcedure ${name}_proc;\n";

	$out->{register} .= <<CODE;
  /*
   * ${name}
   */
  procedure = gimp_procedure_init (\&${name}_proc, @{[scalar @inargs]}, @{[scalar @outargs]});
CODE

        $argc = 0;

        foreach $arg (@inargs) {
	    my ($pspec, $postproc) = &generate_pspec($arg);

	    $pspec =~ s/^/' ' x length("  gimp_procedure_add_argument (")/meg;

	    $out->{register} .= <<CODE;
  gimp_procedure_add_argument (procedure,
${pspec});
CODE

            if (! ($postproc eq '')) {
		$pspec = "procedure->args[$argc].pspec";
		$postproc =~ s/^/'  '/meg;
		$out->{register} .= eval qq/"$postproc"/;
	    }

	    $argc++;
	}

	$argc = 0;

	foreach $arg (@outargs) {
	    my ($pspec, $postproc) = &generate_pspec($arg);
	    my $argc = 0;

	    $pspec =~ s/^/' ' x length("  gimp_procedure_add_return_value (")/meg;

	    $out->{register} .= <<CODE;
  gimp_procedure_add_return_value (procedure,
${pspec});
CODE

            if (! ($postproc eq '')) {
		$pspec = "procedure->values[$argc].pspec";
		$postproc =~ s/^/'  '/meg;
		$out->{register} .= eval qq/"$postproc"/;
	    }

	    $argc++;
	}

	$out->{register} .= <<CODE;
  procedural_db_register (gimp, procedure);

CODE

	if (exists $proc->{invoke}->{headers}) {
	    foreach $header (@{$proc->{invoke}->{headers}}) {
		$out->{headers}->{$header}++;
	    }
	}

	$out->{code} .= "\nstatic Argument *\n";
	$out->{code} .= "${name}_invoker (GimpProcedure *procedure,\n";
	$out->{code} .=  ' ' x length($name) . "          Gimp          *gimp,\n";
	$out->{code} .=  ' ' x length($name) . "          GimpContext   *context,\n";
	$out->{code} .=  ' ' x length($name) . "          GimpProgress  *progress,\n";
	$out->{code} .=  ' ' x length($name) . "          Argument      *args)\n{\n";

	my $code = "";

	if (exists $proc->{invoke}->{no_marshalling}) {
	    $code .= &format_code_frag($proc->{invoke}->{code}, 0) . "}\n";
	}
	else {
	    my $invoker = "";
	
	    $invoker .= ' ' x 2 . "Argument *return_vals;\n" if scalar @outargs;
	    $invoker .= &declare_args($proc, $out, 0, qw(inargs));
	    $invoker .= &declare_args($proc, $out, 1, qw(outargs));

	    $invoker .= &marshal_inargs($proc, 0);
	    $invoker .= "\n" if $invoker && $invoker !~ /\n\n/s;

	    my $frag = "";

	    if (exists $proc->{invoke}->{code}) {
		$frag = &format_code_frag($proc->{invoke}->{code}, $success);
		$frag = ' ' x 2 . "if (success)\n" . $frag if $success;
		$success = ($frag =~ /success =/) unless $success;
	    }

	    chomp $invoker if !$frag;
	    $code .= $invoker . $frag;
	    $code .= "\n" if $frag =~ /\n\n/s || $invoker;
	    $code .= &marshal_outargs($proc) . "}\n";
	}

	if ($success) {
	    $out->{code} .= ' ' x 2 . "gboolean success";
	    unless ($proc->{invoke}->{success} eq 'NONE') {
		$out->{code} .= " = $proc->{invoke}->{success}";
	    }
	    $out->{code} .= ";\n";
	}

        $out->{code} .= $code;

	$out->{code} .= <<CODE;

static GimpProcedure ${name}_proc =
{
  TRUE, TRUE,
  "gimp-$proc->{canonical_name}",
  "gimp-$proc->{canonical_name}",
  @{[ &quotewrap($proc->{blurb}, 2) ]},
  @{[ &quotewrap($proc->{help},  2) ]},
  "$proc->{author}",
  "$proc->{copyright}",
  "$proc->{date}",
  @{[$proc->{deprecated} ? "\"$proc->{deprecated}\"" : 'NULL']},
  GIMP_INTERNAL,
  0, NULL, 0, NULL,
  { { ${name}_invoker } }
};
CODE
    }

    my $gpl = <<'GPL';
/* The GIMP -- an image manipulation program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* NOTE: This file is autogenerated by pdbgen.pl. */

GPL

    my $group_procs = "";
    my $longest = 0;
    my $once = 0;
    my $pcount = 0.0;

    foreach $group (@main::groups) {
	my $out = $out{$group};

	foreach (@{$main::grp{$group}->{headers}}) { $out->{headers}->{$_}++ }

	my @headers = sort {
	    my ($x, $y) = ($a, $b);
	    foreach ($x, $y) {
		if (/^</) {
		    s/^</!/;
		}
		elsif (!/libgimp/) {
		    s/^/~/;
		}
	    }
	    $x cmp $y;
	} keys %{$out->{headers}};
        my $headers = ""; my $lib = 0; my $seen = 0; my $nl = 0;
	my $sys = 0; my $base = 0;
	foreach (@headers) {
	    $headers .= "\n" if $nl;
	    $nl = 0;

	    if ($_ eq '<unistd.h>') {
		$headers .= "\n" if $seen;
		$headers .= "#ifdef HAVE_UNISTD_H\n";
	    }
	    if ($_ eq '<process.h>') {
		$headers .= "\n" if $seen;
		$headers .= "#include <glib.h>\n\n";	
		$headers .= "#ifdef G_OS_WIN32\n";
	    }


	    $seen++ if /^</;

	    if ($sys == 0 && !/^</) {
		$sys = 1;
		$headers .= "\n";
		$headers .= '#include <glib-object.h>';
		$headers .= "\n\n";
	    }

	    $seen = 0 if !/^</;

	    if (/libgimp/) {
		$lib = 1;
	    }
	    else {
		$headers .= "\n" if $lib;
		$lib = 0;

		if ($sys == 1 && $base == 0) {
		    $base = 1;

		    $headers .= '#include "pdb-types.h"';
		    $headers .= "\n";
		    $headers .= '#include "gimpprocedure.h"';
		    $headers .= "\n";
		    $headers .= '#include "procedural_db.h"';
		    $headers .= "\n";
		    $headers .= '#include "core/gimpparamspecs.h"';
		    $headers .= "\n\n";
		}
	    }

            if ($_ eq '"regexrepl/regex.h"') {
		$headers .= "\n";
		$headers .= "#ifdef HAVE_GLIBC_REGEX\n";
		$headers .= "#include <regex.h>\n";
		$headers .= "#else\n";
	    }

	    $headers .= "#include $_\n";

            if ($_ eq '"regexrepl/regex.h"') {
		$headers .= "#endif\n";
		$nl = 1;
	    }

	    if ($_ eq '<unistd.h>') {
		$headers .= "#endif\n";
		$seen = 0;
		$nl = 1;
 	    }

            if ($_ eq '<process.h>') {
		$headers .= "#endif\n";
		$seen = 0;
		$nl = 1;
	    }

	    $headers .= "\n" if $_ eq '"config.h"';
	}

	my $extra = {};
	if (exists $main::grp{$group}->{extra}->{app}) {
	    $extra = $main::grp{$group}->{extra}->{app}
	}

	my $cfile = "$destdir/${group}_cmds.c$FILE_EXT";
	open CFILE, "> $cfile" or die "Can't open $cfile: $!\n";
	print CFILE $gpl;
	print CFILE qq/#include "config.h"\n\n/;
	print CFILE $headers, "\n";
	print CFILE $extra->{decls}, "\n" if exists $extra->{decls};
	print CFILE $out->{procs};
	print CFILE "\nvoid\nregister_${group}_procs (Gimp *gimp)\n";
	print CFILE "{\n  GimpProcedure *procedure;\n\n$out->{register}}\n";
	print CFILE "\n", $extra->{code} if exists $extra->{code};
	print CFILE $out->{code};
	close CFILE;
	&write_file($cfile);

	my $decl = "register_${group}_procs";
	push @group_decls, $decl;
	$longest = length $decl if $longest < length $decl;

	$group_procs .=  ' ' x 2 . "register_${group}_procs (gimp);\n\n";
	$pcount += $out->{pcount};
    }

    if (! $ENV{PDBGEN_GROUPS}) {
	my $internal = "$destdir/internal_procs.h$FILE_EXT";
	open IFILE, "> $internal" or die "Can't open $internal: $!\n";
	print IFILE $gpl;
	my $guard = "__INTERNAL_PROCS_H__";
	print IFILE <<HEADER;
#ifndef $guard
#define $guard

void internal_procs_init (Gimp *gimp);

#endif /* $guard */
HEADER
	close IFILE;
	&write_file($internal);

	$internal = "$destdir/internal_procs.c$FILE_EXT";
	open IFILE, "> $internal" or die "Can't open $internal: $!\n";
	print IFILE $gpl;
	print IFILE qq@#include "config.h"\n\n@;
	print IFILE qq@#include <glib-object.h>\n\n@;
	print IFILE qq@#include "pdb-types.h"\n\n@;
	print IFILE qq@#include "core/gimp.h"\n\n@;
	print IFILE "/* Forward declarations for registering PDB procs */\n\n";
	foreach (@group_decls) {
	    print IFILE "void $_" . ' ' x ($longest - length $_) . " (Gimp *gimp);\n";
	}
	chop $group_procs;
	print IFILE "\n/* $total procedures registered total */\n\n";
	print IFILE <<BODY;
void
internal_procs_init (Gimp *gimp)
{
  g_return_if_fail (GIMP_IS_GIMP (gimp));

$group_procs
}
BODY
	close IFILE;
	&write_file($internal);
    }
}

1;
