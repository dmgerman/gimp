begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_G_P_P_PORTABILITY_H_
end_ifndef

begin_define
DECL|macro|_G_P_P_PORTABILITY_H_
define|#
directive|define
name|_G_P_P_PORTABILITY_H_
end_define

begin_undef
undef|#
directive|undef
name|_P_P_PORTABILITY_H_
end_undef

begin_define
DECL|macro|_P_P_PORTABILITY_H_
define|#
directive|define
name|_P_P_PORTABILITY_H_
end_define

begin_comment
comment|/* Perl/Pollution/Portability Version 1.0007-gimp-2 */
end_comment

begin_comment
comment|/* Copyright (C) 1999, Kenneth Albanowski. This code may be used and    distributed under the same license as any version of Perl. */
end_comment

begin_comment
comment|/* For the latest version of this code, please retreive the Devel::PPPort    module from CPAN, contact the author at<kjahds@kjahds.com>, or check    with the Perl maintainers. */
end_comment

begin_comment
comment|/* If you needed to customize this file for your project, please mention    your changes, and visible alter the version number. */
end_comment

begin_comment
comment|/*    In order for a Perl extension module to be as portable as possible    across differing versions of Perl itself, certain steps need to be taken.    Including this header is the first major one, then using dTHR is all the    appropriate places and using a PL_ prefix to refer to global Perl    variables is the second. */
end_comment

begin_comment
comment|/* If you use one of a few functions that were not present in earlier    versions of Perl, please add a define before the inclusion of ppport.h    for a static include, or use the GLOBAL request in a single module to    produce a global definition that can be referenced from the other    modules.        Function:            Static define:           Extern define:    newCONSTSUB()        NEED_newCONSTSUB         NEED_newCONSTSUB_GLOBAL  */
end_comment

begin_comment
comment|/* To verify whether ppport.h is needed for your module, and whether any    special defines should be used, ppport.h can be run through Perl to check    your source code. Simply say:        	perl -x ppport.h *.c *.h *.xs foo/any.c [etc]        The result will be a list of patches suggesting changes that should at    least be acceptable, if not necessarily the most efficient solution, or a    fix for all possible problems. It won't catch where dTHR is needed, and    doesn't attempt to account for global macro or function definitions,    nested includes, typemaps, etc.        In order to test for the need of dTHR, please try your module under a    recent version of Perl that has threading compiled-in.   */
end_comment

begin_comment
comment|/* #!/usr/bin/perl @ARGV = ("*.xs") if !@ARGV; %badmacros = %funcs = %macros = (); $replace = 0; foreach (<DATA>) { 	$funcs{$1} = 1 if /Provide:\s+(\S+)/; 	$macros{$1} = 1 if /^#\s*define\s+([a-zA-Z0-9_]+)/; 	$replace = $1 if /Replace:\s+(\d+)/; 	$badmacros{$2}=$1 if $replace and /^#\s*define\s+([a-zA-Z0-9_]+).*?\s+([a-zA-Z0-9_]+)/; 	$badmacros{$1}=$2 if /Replace (\S+) with (\S+)/; } foreach $filename (map(glob($_),@ARGV)) { 	unless (open(IN, "<$filename")) { 		warn "Unable to read from $file: $!\n"; 		next; 	} 	print "Scanning $filename...\n"; 	$c = ""; while (<IN>) { $c .= $_; } close(IN); 	$need_include = 0; %add_func = (); $changes = 0; 	$has_include = ($c =~ /#.*include.*ppport/m);  	foreach $func (keys %funcs) { 		if ($c =~ /#.*define.*\bNEED_$func(_GLOBAL)?\b/m) { 			if ($c !~ /\b$func\b/m) { 				print "If $func isn't needed, you don't need to request it.\n" if 				$changes += ($c =~ s/^.*#.*define.*\bNEED_$func\b.*\n//m); 			} else { 				print "Uses $func\n"; 				$need_include = 1; 			} 		} else { 			if ($c =~ /\b$func\b/m) { 				$add_func{$func} =1 ; 				print "Uses $func\n"; 				$need_include = 1; 			} 		} 	}  	if (not $need_include) { 		foreach $macro (keys %macros) { 			if ($c =~ /\b$macro\b/m) { 				print "Uses $macro\n"; 				$need_include = 1; 			} 		} 	}  	foreach $badmacro (keys %badmacros) { 		if ($c =~ /\b$badmacro\b/m) { 			$changes += ($c =~ s/\b$badmacro\b/$badmacros{$badmacro}/gm); 			print "Uses $badmacros{$badmacro} (instead of $badmacro)\n"; 			$need_include = 1; 		} 	} 	 	if (scalar(keys %add_func) or $need_include != $has_include) { 		if (!$has_include) { 			$inc = join('',map("#define NEED_$_\n", sort keys %add_func)). 			       "#include \"ppport.h\"\n"; 			$c = "$inc$c" unless $c =~ s/#.*include.*XSUB.*\n/$&$inc/m; 		} elsif (keys %add_func) { 			$inc = join('',map("#define NEED_$_\n", sort keys %add_func)); 			$c = "$inc$c" unless $c =~ s/^.*#.*include.*ppport.*$/$inc$&/m; 		} 		if (!$need_include) { 			print "Doesn't seem to need ppport.h.\n"; 			$c =~ s/^.*#.*include.*ppport.*\n//m; 		} 		$changes++; 	} 	 	if ($changes) { 		open(OUT,">/tmp/ppport.h.$$"); 		print OUT $c; 		close(OUT); 		open(DIFF, "diff -u $filename /tmp/ppport.h.$$|"); 		while (<DIFF>) { s!/tmp/ppport\.h\.$$!$filename.patched!; print STDOUT; } 		close(DIFF); 		unlink("/tmp/ppport.h.$$"); 	} else { 		print "Looks OK\n"; 	} } __DATA__ */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|PERL_REVISION
end_ifndef

begin_ifndef
ifndef|#
directive|ifndef
name|__PATCHLEVEL_H_INCLUDED__
end_ifndef

begin_include
include|#
directive|include
file|"patchlevel.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|PERL_REVISION
end_ifndef

begin_define
DECL|macro|PERL_REVISION
define|#
directive|define
name|PERL_REVISION
value|(5)
end_define

begin_comment
comment|/* Replace: 1 */
end_comment

begin_define
DECL|macro|PERL_VERSION
define|#
directive|define
name|PERL_VERSION
value|PATCHLEVEL
end_define

begin_define
DECL|macro|PERL_SUBVERSION
define|#
directive|define
name|PERL_SUBVERSION
value|SUBVERSION
end_define

begin_comment
comment|/* Replace PERL_PATCHLEVEL with PERL_VERSION */
end_comment

begin_comment
comment|/* Replace: 0 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|PERL_BCDVERSION
define|#
directive|define
name|PERL_BCDVERSION
value|((PERL_REVISION * 0x1000000L) + (PERL_VERSION * 0x1000L) + PERL_SUBVERSION)
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|ERRSV
end_ifndef

begin_define
DECL|macro|ERRSV
define|#
directive|define
name|ERRSV
value|perl_get_sv("@",FALSE)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|PERL_VERSION
operator|<
literal|4
operator|)
operator|||
operator|(
operator|(
name|PERL_VERSION
operator|==
literal|4
operator|)
operator|&&
operator|(
name|PERL_SUBVERSION
operator|<=
literal|5
operator|)
operator|)
end_if

begin_comment
comment|/* Replace: 1 */
end_comment

begin_define
DECL|macro|PL_sv_undef
define|#
directive|define
name|PL_sv_undef
value|sv_undef
end_define

begin_define
DECL|macro|PL_sv_yes
define|#
directive|define
name|PL_sv_yes
value|sv_yes
end_define

begin_define
DECL|macro|PL_sv_no
define|#
directive|define
name|PL_sv_no
value|sv_no
end_define

begin_define
DECL|macro|PL_na
define|#
directive|define
name|PL_na
value|na
end_define

begin_define
DECL|macro|PL_stdingv
define|#
directive|define
name|PL_stdingv
value|stdingv
end_define

begin_define
DECL|macro|PL_hints
define|#
directive|define
name|PL_hints
value|hints
end_define

begin_define
DECL|macro|PL_curcop
define|#
directive|define
name|PL_curcop
value|curcop
end_define

begin_define
DECL|macro|PL_curstash
define|#
directive|define
name|PL_curstash
value|curstash
end_define

begin_define
DECL|macro|PL_copline
define|#
directive|define
name|PL_copline
value|copline
end_define

begin_define
DECL|macro|PL_Sv
define|#
directive|define
name|PL_Sv
value|Sv
end_define

begin_define
DECL|macro|PL_perl_destruct_level
define|#
directive|define
name|PL_perl_destruct_level
value|perl_destruct_level
end_define

begin_comment
comment|/* Replace: 0 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|dTHR
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|WIN32
end_ifdef

begin_define
DECL|macro|dTHR
define|#
directive|define
name|dTHR
value|extern int Perl___notused
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|dTHR
define|#
directive|define
name|dTHR
value|extern int errno
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|boolSV
end_ifndef

begin_define
DECL|macro|boolSV (b)
define|#
directive|define
name|boolSV
parameter_list|(
name|b
parameter_list|)
value|((b) ?&PL_sv_yes :&PL_sv_no)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|gv_stashpvn
end_ifndef

begin_define
DECL|macro|gv_stashpvn (str,len,flags)
define|#
directive|define
name|gv_stashpvn
parameter_list|(
name|str
parameter_list|,
name|len
parameter_list|,
name|flags
parameter_list|)
value|gv_stashpv(str,flags)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|newSVpvn
end_ifndef

begin_define
DECL|macro|newSVpvn (data,len)
define|#
directive|define
name|newSVpvn
parameter_list|(
name|data
parameter_list|,
name|len
parameter_list|)
value|((len) ? newSVpv ((data), (len)) : newSVpv ("", 0))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|newRV_inc
end_ifndef

begin_comment
comment|/* Replace: 1 */
end_comment

begin_define
DECL|macro|newRV_inc (sv)
define|#
directive|define
name|newRV_inc
parameter_list|(
name|sv
parameter_list|)
value|newRV(sv)
end_define

begin_comment
comment|/* Replace: 0 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|newRV_noinc
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_define
DECL|macro|newRV_noinc (sv)
define|#
directive|define
name|newRV_noinc
parameter_list|(
name|sv
parameter_list|)
define|\
value|({                                  \           SV *nsv = (SV*)newRV(sv);       \           SvREFCNT_dec(sv);               \           nsv;                            \       })
end_define

begin_else
else|#
directive|else
end_else

begin_if
if|#
directive|if
name|defined
argument_list|(
name|CRIPPLED_CC
argument_list|)
operator|||
name|defined
argument_list|(
name|USE_THREADS
argument_list|)
end_if

begin_function
DECL|function|newRV_noinc (SV * sv)
specifier|static
name|SV
modifier|*
name|newRV_noinc
parameter_list|(
name|SV
modifier|*
name|sv
parameter_list|)
block|{
name|SV
modifier|*
name|nsv
init|=
operator|(
name|SV
operator|*
operator|)
name|newRV
argument_list|(
name|sv
argument_list|)
decl_stmt|;
name|SvREFCNT_dec
argument_list|(
name|sv
argument_list|)
expr_stmt|;
return|return
name|nsv
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|newRV_noinc (sv)
define|#
directive|define
name|newRV_noinc
parameter_list|(
name|sv
parameter_list|)
define|\
value|((PL_Sv=(SV*)newRV(sv), SvREFCNT_dec(sv), (SV*)PL_Sv)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Provide: newCONSTSUB */
end_comment

begin_comment
comment|/* newCONSTSUB from IO.xs is in the core starting with 5.004_63 */
end_comment

begin_if
if|#
directive|if
operator|(
name|PERL_VERSION
operator|<
literal|4
operator|)
operator|||
operator|(
operator|(
name|PERL_VERSION
operator|==
literal|4
operator|)
operator|&&
operator|(
name|PERL_SUBVERSION
operator|<
literal|63
operator|)
operator|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|NEED_newCONSTSUB
argument_list|)
end_if

begin_decl_stmt
specifier|static
else|#
directive|else
specifier|extern
name|void
name|newCONSTSUB
name|_
argument_list|(
operator|(
name|HV
operator|*
name|stash
operator|,
name|char
operator|*
name|name
operator|,
name|SV
operator|*
name|sv
operator|)
argument_list|)
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|defined
argument_list|(
name|NEED_newCONSTSUB
argument_list|)
operator|||
name|defined
argument_list|(
name|NEED_newCONSTSUB_GLOBAL
argument_list|)
end_if

begin_function
name|void
DECL|function|newCONSTSUB (stash,name,sv)
name|newCONSTSUB
parameter_list|(
name|stash
parameter_list|,
name|name
parameter_list|,
name|sv
parameter_list|)
name|HV
modifier|*
name|stash
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|;
name|SV
modifier|*
name|sv
decl_stmt|;
block|{
name|U32
name|oldhints
init|=
name|PL_hints
decl_stmt|;
name|HV
modifier|*
name|old_cop_stash
init|=
name|PL_curcop
operator|->
name|cop_stash
decl_stmt|;
name|HV
modifier|*
name|old_curstash
init|=
name|PL_curstash
decl_stmt|;
name|line_t
name|oldline
init|=
name|PL_curcop
operator|->
name|cop_line
decl_stmt|;
name|PL_curcop
operator|->
name|cop_line
operator|=
name|PL_copline
expr_stmt|;
name|PL_hints
operator|&=
operator|~
name|HINT_BLOCK_SCOPE
expr_stmt|;
if|if
condition|(
name|stash
condition|)
name|PL_curstash
operator|=
name|PL_curcop
operator|->
name|cop_stash
operator|=
name|stash
expr_stmt|;
name|newSUB
argument_list|(
if|#
directive|if
operator|(
name|PERL_VERSION
operator|<
literal|3
operator|)
operator|||
operator|(
operator|(
name|PERL_VERSION
operator|==
literal|3
operator|)
operator|&&
operator|(
name|PERL_SUBVERSION
operator|<
literal|22
operator|)
operator|)
comment|/* before 5.003_22 */
name|start_subparse
argument_list|()
argument_list|,
else|#
directive|else
if|#
directive|if
operator|(
name|PERL_VERSION
operator|==
literal|3
operator|)
operator|&&
operator|(
name|PERL_SUBVERSION
operator|==
literal|22
operator|)
comment|/* 5.003_22 */
name|start_subparse
argument_list|(
literal|0
argument_list|)
argument_list|,
else|#
directive|else
comment|/* 5.003_23  onwards */
name|start_subparse
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
argument_list|,
endif|#
directive|endif
endif|#
directive|endif
name|newSVOP
argument_list|(
name|OP_CONST
argument_list|,
literal|0
argument_list|,
name|newSVpv
argument_list|(
name|name
argument_list|,
literal|0
argument_list|)
argument_list|)
argument_list|,
name|newSVOP
argument_list|(
name|OP_CONST
argument_list|,
literal|0
argument_list|,
operator|&
name|PL_sv_no
argument_list|)
argument_list|,
comment|/* SvPV(&PL_sv_no) == "" -- GMB */
name|newSTATEOP
argument_list|(
literal|0
argument_list|,
name|Nullch
argument_list|,
name|newSVOP
argument_list|(
name|OP_CONST
argument_list|,
literal|0
argument_list|,
name|sv
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|PL_hints
operator|=
name|oldhints
expr_stmt|;
name|PL_curcop
operator|->
name|cop_stash
operator|=
name|old_cop_stash
expr_stmt|;
name|PL_curstash
operator|=
name|old_curstash
expr_stmt|;
name|PL_curcop
operator|->
name|cop_line
operator|=
name|oldline
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* newCONSTSUB */
end_comment

begin_comment
comment|/*GIMP*/
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|SvPV_nolen
end_ifndef

begin_define
DECL|macro|SvPV_nolen (b)
define|#
directive|define
name|SvPV_nolen
parameter_list|(
name|b
parameter_list|)
value|SvPV((b),PL_na)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _G_P_P_PORTABILITY_H_ */
end_comment

end_unit

