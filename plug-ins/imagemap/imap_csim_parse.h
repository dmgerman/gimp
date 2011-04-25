begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* A Bison parser, made by GNU Bison 2.4.3.  */
end_comment

begin_comment
comment|/* Skeleton interface for Bison's Yacc-like parsers in C           Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,    2009, 2010 Free Software Foundation, Inc.        This program is free software: you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation, either version 3 of the License, or    (at your option) any later version.        This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.        You should have received a copy of the GNU General Public License    along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* As a special exception, you may create a larger work that contains    part or all of the Bison parser skeleton and distribute that work    under terms of your choice, so long as that work isn't itself a    parser generator using the skeleton or a modified version thereof    as a parser skeleton.  Alternatively, if you modify or redistribute    the parser skeleton itself, you may (at your option) remove this    special exception, which will cause the skeleton and the resulting    Bison output files to be licensed under the GNU General Public    License without this special exception.        This special exception was added by the Free Software Foundation in    version 2.2 of Bison.  */
end_comment

begin_comment
comment|/* Tokens.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|YYTOKENTYPE
end_ifndef

begin_define
DECL|macro|YYTOKENTYPE
define|#
directive|define
name|YYTOKENTYPE
end_define

begin_comment
comment|/* Put the tokens into the symbol table, so that GDB and other debuggers       know about them.  */
end_comment

begin_enum
DECL|enum|yytokentype
enum|enum
name|yytokentype
block|{
DECL|enumerator|IMG
name|IMG
init|=
literal|258
block|,
DECL|enumerator|SRC
name|SRC
init|=
literal|259
block|,
DECL|enumerator|WIDTH
name|WIDTH
init|=
literal|260
block|,
DECL|enumerator|HEIGHT
name|HEIGHT
init|=
literal|261
block|,
DECL|enumerator|BORDER
name|BORDER
init|=
literal|262
block|,
DECL|enumerator|USEMAP
name|USEMAP
init|=
literal|263
block|,
DECL|enumerator|START_MAP
name|START_MAP
init|=
literal|264
block|,
DECL|enumerator|END_MAP
name|END_MAP
init|=
literal|265
block|,
DECL|enumerator|NAME
name|NAME
init|=
literal|266
block|,
DECL|enumerator|AREA
name|AREA
init|=
literal|267
block|,
DECL|enumerator|SHAPE
name|SHAPE
init|=
literal|268
block|,
DECL|enumerator|COORDS
name|COORDS
init|=
literal|269
block|,
DECL|enumerator|ALT
name|ALT
init|=
literal|270
block|,
DECL|enumerator|HREF
name|HREF
init|=
literal|271
block|,
DECL|enumerator|NOHREF
name|NOHREF
init|=
literal|272
block|,
DECL|enumerator|TARGET
name|TARGET
init|=
literal|273
block|,
DECL|enumerator|ONMOUSEOVER
name|ONMOUSEOVER
init|=
literal|274
block|,
DECL|enumerator|ONMOUSEOUT
name|ONMOUSEOUT
init|=
literal|275
block|,
DECL|enumerator|ONFOCUS
name|ONFOCUS
init|=
literal|276
block|,
DECL|enumerator|ONBLUR
name|ONBLUR
init|=
literal|277
block|,
DECL|enumerator|AUTHOR
name|AUTHOR
init|=
literal|278
block|,
DECL|enumerator|DESCRIPTION
name|DESCRIPTION
init|=
literal|279
block|,
DECL|enumerator|BEGIN_COMMENT
name|BEGIN_COMMENT
init|=
literal|280
block|,
DECL|enumerator|END_COMMENT
name|END_COMMENT
init|=
literal|281
block|,
DECL|enumerator|FLOAT
name|FLOAT
init|=
literal|282
block|,
DECL|enumerator|STRING
name|STRING
init|=
literal|283
block|}
enum|;
end_enum

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Tokens.  */
end_comment

begin_define
DECL|macro|IMG
define|#
directive|define
name|IMG
value|258
end_define

begin_define
DECL|macro|SRC
define|#
directive|define
name|SRC
value|259
end_define

begin_define
DECL|macro|WIDTH
define|#
directive|define
name|WIDTH
value|260
end_define

begin_define
DECL|macro|HEIGHT
define|#
directive|define
name|HEIGHT
value|261
end_define

begin_define
DECL|macro|BORDER
define|#
directive|define
name|BORDER
value|262
end_define

begin_define
DECL|macro|USEMAP
define|#
directive|define
name|USEMAP
value|263
end_define

begin_define
DECL|macro|START_MAP
define|#
directive|define
name|START_MAP
value|264
end_define

begin_define
DECL|macro|END_MAP
define|#
directive|define
name|END_MAP
value|265
end_define

begin_define
DECL|macro|NAME
define|#
directive|define
name|NAME
value|266
end_define

begin_define
DECL|macro|AREA
define|#
directive|define
name|AREA
value|267
end_define

begin_define
DECL|macro|SHAPE
define|#
directive|define
name|SHAPE
value|268
end_define

begin_define
DECL|macro|COORDS
define|#
directive|define
name|COORDS
value|269
end_define

begin_define
DECL|macro|ALT
define|#
directive|define
name|ALT
value|270
end_define

begin_define
DECL|macro|HREF
define|#
directive|define
name|HREF
value|271
end_define

begin_define
DECL|macro|NOHREF
define|#
directive|define
name|NOHREF
value|272
end_define

begin_define
DECL|macro|TARGET
define|#
directive|define
name|TARGET
value|273
end_define

begin_define
DECL|macro|ONMOUSEOVER
define|#
directive|define
name|ONMOUSEOVER
value|274
end_define

begin_define
DECL|macro|ONMOUSEOUT
define|#
directive|define
name|ONMOUSEOUT
value|275
end_define

begin_define
DECL|macro|ONFOCUS
define|#
directive|define
name|ONFOCUS
value|276
end_define

begin_define
DECL|macro|ONBLUR
define|#
directive|define
name|ONBLUR
value|277
end_define

begin_define
DECL|macro|AUTHOR
define|#
directive|define
name|AUTHOR
value|278
end_define

begin_define
DECL|macro|DESCRIPTION
define|#
directive|define
name|DESCRIPTION
value|279
end_define

begin_define
DECL|macro|BEGIN_COMMENT
define|#
directive|define
name|BEGIN_COMMENT
value|280
end_define

begin_define
DECL|macro|END_COMMENT
define|#
directive|define
name|END_COMMENT
value|281
end_define

begin_define
DECL|macro|FLOAT
define|#
directive|define
name|FLOAT
value|282
end_define

begin_define
DECL|macro|STRING
define|#
directive|define
name|STRING
value|283
end_define

begin_if
if|#
directive|if
operator|!
name|defined
name|YYSTYPE
operator|&&
operator|!
name|defined
name|YYSTYPE_IS_DECLARED
end_if

begin_typedef
DECL|union|YYSTYPE
typedef|typedef
union|union
name|YYSTYPE
block|{
comment|/* Line 1685 of yacc.c  */
line|#
directive|line
number|48
file|"imap_csim.y"
DECL|member|val
name|int
name|val
decl_stmt|;
DECL|member|value
name|double
name|value
decl_stmt|;
DECL|member|id
name|char
modifier|*
name|id
decl_stmt|;
comment|/* Line 1685 of yacc.c  */
line|#
directive|line
number|115
file|"y.tab.h"
DECL|typedef|YYSTYPE
block|}
name|YYSTYPE
typedef|;
end_typedef

begin_define
DECL|macro|YYSTYPE_IS_TRIVIAL
define|#
directive|define
name|YYSTYPE_IS_TRIVIAL
value|1
end_define

begin_define
DECL|macro|yystype
define|#
directive|define
name|yystype
value|YYSTYPE
end_define

begin_comment
DECL|macro|yystype
comment|/* obsolescent; will be withdrawn */
end_comment

begin_define
DECL|macro|YYSTYPE_IS_DECLARED
define|#
directive|define
name|YYSTYPE_IS_DECLARED
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|YYSTYPE
name|csim_lval
decl_stmt|;
end_decl_stmt

end_unit

