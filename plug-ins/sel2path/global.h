begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* global.h: extend the standard programming environment a little.  This    is included from config.h, which everyone includes.  Copyright (C) 1992 Free Software Foundation, Inc.  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GLOBAL_H
end_ifndef

begin_define
DECL|macro|GLOBAL_H
define|#
directive|define
name|GLOBAL_H
end_define

begin_include
include|#
directive|include
file|"types.h"
end_include

begin_comment
comment|/* Define common sorts of messages.  */
end_comment

begin_comment
comment|/* This should be called only after a system call fails.  */
end_comment

begin_define
DECL|macro|FATAL_PERROR (s)
define|#
directive|define
name|FATAL_PERROR
parameter_list|(
name|s
parameter_list|)
value|do { perror (s); exit (errno); } while (0)
end_define

begin_define
DECL|macro|START_FATAL ()
define|#
directive|define
name|START_FATAL
parameter_list|()
value|do { fputs ("fatal: ", stderr)
end_define

begin_define
DECL|macro|END_FATAL ()
define|#
directive|define
name|END_FATAL
parameter_list|()
value|fputs (".\n", stderr); exit (1); } while (0)
end_define

begin_define
DECL|macro|FATAL (s)
define|#
directive|define
name|FATAL
parameter_list|(
name|s
parameter_list|)
define|\
value|START_FATAL (); fprintf (stderr, "%s", s); END_FATAL ()
end_define

begin_define
DECL|macro|FATAL1 (s,e1)
define|#
directive|define
name|FATAL1
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|)
define|\
value|START_FATAL (); fprintf (stderr, s, e1); END_FATAL ()
end_define

begin_define
DECL|macro|FATAL2 (s,e1,e2)
define|#
directive|define
name|FATAL2
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|)
define|\
value|START_FATAL (); fprintf (stderr, s, e1, e2); END_FATAL ()
end_define

begin_define
DECL|macro|FATAL3 (s,e1,e2,e3)
define|#
directive|define
name|FATAL3
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|,
name|e3
parameter_list|)
define|\
value|START_FATAL (); fprintf (stderr, s, e1, e2, e3); END_FATAL ()
end_define

begin_define
DECL|macro|FATAL4 (s,e1,e2,e3,e4)
define|#
directive|define
name|FATAL4
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|,
name|e3
parameter_list|,
name|e4
parameter_list|)
define|\
value|START_FATAL (); fprintf (stderr, s, e1, e2, e3, e4); END_FATAL ()
end_define

begin_define
DECL|macro|START_WARNING ()
define|#
directive|define
name|START_WARNING
parameter_list|()
value|do { fputs ("warning: ", stderr)
end_define

begin_define
DECL|macro|END_WARNING ()
define|#
directive|define
name|END_WARNING
parameter_list|()
value|fputs (".\n", stderr); fflush (stderr); } while (0)
end_define

begin_define
DECL|macro|WARNING (s)
define|#
directive|define
name|WARNING
parameter_list|(
name|s
parameter_list|)
define|\
value|START_WARNING (); fprintf (stderr, "%s", s); END_WARNING ()
end_define

begin_define
DECL|macro|WARNING1 (s,e1)
define|#
directive|define
name|WARNING1
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|)
define|\
value|START_WARNING (); fprintf (stderr, s, e1); END_WARNING ()
end_define

begin_define
DECL|macro|WARNING2 (s,e1,e2)
define|#
directive|define
name|WARNING2
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|)
define|\
value|START_WARNING (); fprintf (stderr, s, e1, e2); END_WARNING ()
end_define

begin_define
DECL|macro|WARNING3 (s,e1,e2,e3)
define|#
directive|define
name|WARNING3
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|,
name|e3
parameter_list|)
define|\
value|START_WARNING (); fprintf (stderr, s, e1, e2, e3); END_WARNING ()
end_define

begin_define
DECL|macro|WARNING4 (s,e1,e2,e3,e4)
define|#
directive|define
name|WARNING4
parameter_list|(
name|s
parameter_list|,
name|e1
parameter_list|,
name|e2
parameter_list|,
name|e3
parameter_list|,
name|e4
parameter_list|)
define|\
value|START_WARNING (); fprintf (stderr, s, e1, e2, e3, e4); END_WARNING ()
end_define

begin_escape
end_escape

begin_comment
comment|/* Define useful abbreviations.  */
end_comment

begin_comment
comment|/* This is the maximum number of numerals that result when a 64-bit    integer is converted to a string, plus one for a trailing null byte,    plus one for a sign.  */
end_comment

begin_define
DECL|macro|MAX_INT_LENGTH
define|#
directive|define
name|MAX_INT_LENGTH
value|21
end_define

begin_comment
comment|/* Printer's points, as defined by TeX (and good typesetters everywhere).  */
end_comment

begin_define
DECL|macro|POINTS_PER_INCH
define|#
directive|define
name|POINTS_PER_INCH
value|72.27
end_define

begin_comment
comment|/* Convert a number V in pixels to printer's points, and vice versa,    assuming a resolution of DPI pixels per inch.  */
end_comment

begin_define
DECL|macro|PIXELS_TO_POINTS (v,dpi)
define|#
directive|define
name|PIXELS_TO_POINTS
parameter_list|(
name|v
parameter_list|,
name|dpi
parameter_list|)
value|(POINTS_PER_INCH * (v) / (dpi))
end_define

begin_define
DECL|macro|POINTS_TO_REAL_PIXELS (v,dpi)
define|#
directive|define
name|POINTS_TO_REAL_PIXELS
parameter_list|(
name|v
parameter_list|,
name|dpi
parameter_list|)
value|((v) * (dpi) / POINTS_PER_INCH)
end_define

begin_define
DECL|macro|POINTS_TO_PIXELS (v,dpi)
define|#
directive|define
name|POINTS_TO_PIXELS
parameter_list|(
name|v
parameter_list|,
name|dpi
parameter_list|)
value|((int) (POINTS_TO_REAL_PIXELS (v, dpi) + .5))
end_define

begin_comment
comment|/* Some simple numeric operations.  It is possible to define these much    more cleanly in GNU C, but we haven't done that (yet).  */
end_comment

begin_define
DECL|macro|SQUARE (x)
define|#
directive|define
name|SQUARE
parameter_list|(
name|x
parameter_list|)
value|((x) * (x))
end_define

begin_define
DECL|macro|CUBE (x)
define|#
directive|define
name|CUBE
parameter_list|(
name|x
parameter_list|)
value|((x) * (x) * (x))
end_define

begin_define
DECL|macro|SAME_SIGN (u,v)
define|#
directive|define
name|SAME_SIGN
parameter_list|(
name|u
parameter_list|,
name|v
parameter_list|)
value|((u)>= 0&& (v)>= 0 || (u)< 0&& (v)< 0)
end_define

begin_define
DECL|macro|ROUND (x)
define|#
directive|define
name|ROUND
parameter_list|(
name|x
parameter_list|)
value|((int) ((int) (x) + .5 * SIGN (x)))
end_define

begin_define
DECL|macro|SIGN (x)
define|#
directive|define
name|SIGN
parameter_list|(
name|x
parameter_list|)
value|((x)> 0 ? 1 : (x)< 0 ? -1 : 0)
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|MAX
end_ifndef

begin_define
DECL|macro|MAX (a,b)
define|#
directive|define
name|MAX
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)> (b) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|MIN
end_ifndef

begin_define
DECL|macro|MIN (a,b)
define|#
directive|define
name|MIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|)
value|((a)< (b) ? (a) : (b))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Too bad C doesn't define operators for these.  */
end_comment

begin_define
DECL|macro|MAX_EQUALS (var,expr)
define|#
directive|define
name|MAX_EQUALS
parameter_list|(
name|var
parameter_list|,
name|expr
parameter_list|)
value|if ((expr)> (var)) (var) = (expr)
end_define

begin_define
DECL|macro|MIN_EQUALS (var,expr)
define|#
directive|define
name|MIN_EQUALS
parameter_list|(
name|var
parameter_list|,
name|expr
parameter_list|)
value|if ((expr)< (var)) (var) = (expr)
end_define

begin_define
DECL|macro|STREQ (s1,s2)
define|#
directive|define
name|STREQ
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|)
value|(strcmp (s1, s2) == 0)
end_define

begin_escape
end_escape

begin_comment
comment|/* Declarations for commonly-used routines we provide ourselves.  The    ones here are only needed by us, so we do not provide them in    unprototyped form.  Others are declared both ways in lib.h.  */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* These aren't actually defined anywhere */
end_comment

begin_comment
comment|/* Return the current date and time a la date(1).  */
end_comment

begin_comment
unit|extern string now (void);
comment|/* Check if a string is a valid floating-point or decimal integer.    Returns false if passed NULL.  */
end_comment

begin_comment
unit|extern boolean float_ok (string); extern boolean integer_ok (string);
comment|/* Like `atoi', but disallow negative numbers.  */
end_comment

begin_comment
unit|extern const unsigned atou (string);
comment|/* The converses of atoi, atou, and atof.  These all return dynamically    allocated strings.  `dtoa' is so-named because `ftoa' is a library    function on some systems (the IBM RT), and the loader complains that    is defined twice, for reasons I don't understand.  */
end_comment

begin_endif
unit|extern string itoa (int); extern string utoa (unsigned); extern string dtoa (double);
endif|#
directive|endif
end_endif

begin_comment
comment|/* Like their stdio counterparts, but abort on error, after calling    perror(3) with FILENAME as its argument.  */
end_comment

begin_comment
comment|/* extern FILE *xfopen (string filename, string mode); */
end_comment

begin_comment
comment|/* extern void xfclose (FILE *, string filename); */
end_comment

begin_comment
comment|/* extern void xfseek (FILE *, long, int, string filename); */
end_comment

begin_comment
comment|/* extern four_bytes xftell (FILE *, string filename); */
end_comment

begin_comment
comment|/* Copies the file FROM to the file TO, then unlinks FROM.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|xrename
parameter_list|(
name|string
name|from
parameter_list|,
name|string
name|to
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return NAME with any leading path stripped off.  This returns a    pointer into NAME.  */
end_comment

begin_comment
comment|/* ALT extern string basename (string name); */
end_comment

begin_comment
comment|/* If P or *P is null, abort.  Otherwise, call free(3) on P,    and then set *P to NULL.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|safe_free
parameter_list|(
name|address
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Math functions.  */
end_comment

begin_comment
comment|/* Says whether V1 and V2 are within REAL_EPSILON of each other.    Fixed-point arithmetic would be better, to guarantee machine    independence, but it's so much more painful to work with.  The value    here is smaller than can be represented in either a `fix_word' or a    `scaled_num', so more precision than this will be lost when we    output, anyway.  */
end_comment

begin_define
DECL|macro|REAL_EPSILON
define|#
directive|define
name|REAL_EPSILON
value|0.00001
end_define

begin_function_decl
specifier|extern
specifier|const
name|boolean
name|epsilon_equal
parameter_list|(
name|real
name|v1
parameter_list|,
name|real
name|v2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Arc cosine, in degrees.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real
name|my_acosd
parameter_list|(
name|real
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Return the Euclidean distance between the two points.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real
name|distance
parameter_list|(
name|real_coordinate_type
parameter_list|,
name|real_coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|real
name|int_distance
parameter_list|(
name|coordinate_type
parameter_list|,
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Slope between two points (delta y per unit x).  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real
name|slope
parameter_list|(
name|real_coordinate_type
parameter_list|,
name|real_coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Make a real coordinate from an integer one, and vice versa.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|real_coordinate_type
name|int_to_real_coord
parameter_list|(
name|coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
specifier|const
name|coordinate_type
name|real_to_int_coord
parameter_list|(
name|real_coordinate_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Test if two integer points are adjacent.  */
end_comment

begin_function_decl
specifier|extern
specifier|const
name|boolean
name|points_adjacent_p
parameter_list|(
name|int
name|row1
parameter_list|,
name|int
name|col1
parameter_list|,
name|int
name|r2
parameter_list|,
name|int
name|c2
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Find the largest and smallest elements of an array.  */
end_comment

begin_function_decl
specifier|extern
name|void
name|find_bounds
parameter_list|(
name|real
name|values
index|[]
parameter_list|,
name|unsigned
name|value_count
parameter_list|,
comment|/* returned: */
name|real
modifier|*
name|the_min
parameter_list|,
name|real
modifier|*
name|the_max
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Make all the elements in the array between zero and one.  */
end_comment

begin_function_decl
specifier|extern
name|real
modifier|*
name|map_to_unit
parameter_list|(
name|real
modifier|*
name|values
parameter_list|,
name|unsigned
name|value_count
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* String functions.  */
end_comment

begin_comment
comment|/* Return (a fresh copy of) SOURCE beginning at START and ending at    LIMIT.  (Or NULL if LIMIT< START.)  */
end_comment

begin_function_decl
specifier|extern
name|string
name|substring
parameter_list|(
name|string
name|source
parameter_list|,
specifier|const
name|unsigned
name|start
parameter_list|,
specifier|const
name|unsigned
name|limit
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Change all uppercase letters in S to lowercase.  */
end_comment

begin_function_decl
specifier|extern
name|string
name|lowercasify
parameter_list|(
name|string
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Character code parsing.  */
end_comment

begin_comment
comment|/* If the string S parses as a character code, this sets *VALID to    `true' and returns the number.  If it doesn't, it sets *VALID to    `false' and the return value is garbage.        We allow any of the following possibilies: a single character, as in    `a' or `0'; a decimal number, as in `21'; an octal number, as in `03'    or `0177'; a hexadecimal number, as in `0x3' or `0xff'.  */
end_comment

begin_function_decl
specifier|extern
name|charcode_type
name|parse_charcode
parameter_list|(
name|string
name|s
parameter_list|,
name|boolean
modifier|*
name|valid
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Like `parse_charcode', but gives a fatal error if the string isn't a    valid character code.  */
end_comment

begin_function_decl
specifier|extern
name|charcode_type
name|xparse_charcode
parameter_list|(
name|string
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_escape
end_escape

begin_comment
comment|/* The environment variable name with which to look up auxiliary files.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|LIB_ENVVAR
end_ifndef

begin_define
DECL|macro|LIB_ENVVAR
define|#
directive|define
name|LIB_ENVVAR
value|"FONTUTIL_LIB"
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
comment|/* not GLOBAL_H */
end_comment

end_unit

