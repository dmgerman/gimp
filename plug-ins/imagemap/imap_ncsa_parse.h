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
DECL|enumerator|RECTANGLE
name|RECTANGLE
init|=
literal|258
block|,
DECL|enumerator|POLYGON
name|POLYGON
init|=
literal|259
block|,
DECL|enumerator|CIRCLE
name|CIRCLE
init|=
literal|260
block|,
DECL|enumerator|DEFAULT
name|DEFAULT
init|=
literal|261
block|,
DECL|enumerator|AUTHOR
name|AUTHOR
init|=
literal|262
block|,
DECL|enumerator|TITLE
name|TITLE
init|=
literal|263
block|,
DECL|enumerator|DESCRIPTION
name|DESCRIPTION
init|=
literal|264
block|,
DECL|enumerator|BEGIN_COMMENT
name|BEGIN_COMMENT
init|=
literal|265
block|,
DECL|enumerator|FLOAT
name|FLOAT
init|=
literal|266
block|,
DECL|enumerator|LINK
name|LINK
init|=
literal|267
block|,
DECL|enumerator|COMMENT
name|COMMENT
init|=
literal|268
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
DECL|macro|RECTANGLE
define|#
directive|define
name|RECTANGLE
value|258
end_define

begin_define
DECL|macro|POLYGON
define|#
directive|define
name|POLYGON
value|259
end_define

begin_define
DECL|macro|CIRCLE
define|#
directive|define
name|CIRCLE
value|260
end_define

begin_define
DECL|macro|DEFAULT
define|#
directive|define
name|DEFAULT
value|261
end_define

begin_define
DECL|macro|AUTHOR
define|#
directive|define
name|AUTHOR
value|262
end_define

begin_define
DECL|macro|TITLE
define|#
directive|define
name|TITLE
value|263
end_define

begin_define
DECL|macro|DESCRIPTION
define|#
directive|define
name|DESCRIPTION
value|264
end_define

begin_define
DECL|macro|BEGIN_COMMENT
define|#
directive|define
name|BEGIN_COMMENT
value|265
end_define

begin_define
DECL|macro|FLOAT
define|#
directive|define
name|FLOAT
value|266
end_define

begin_define
DECL|macro|LINK
define|#
directive|define
name|LINK
value|267
end_define

begin_define
DECL|macro|COMMENT
define|#
directive|define
name|COMMENT
value|268
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
number|45
file|"imap_ncsa.y"
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
number|85
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
name|ncsa_lval
decl_stmt|;
end_decl_stmt

end_unit

