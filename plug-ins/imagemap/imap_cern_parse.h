begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* A Bison parser, made by GNU Bison 1.875a.  */
end_comment

begin_comment
comment|/* Skeleton parser for Yacc-like parsing with Bison,    Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.     This program is free software; you can redistribute it and/or modify    it under the terms of the GNU General Public License as published by    the Free Software Foundation; either version 2, or (at your option)    any later version.     This program is distributed in the hope that it will be useful,    but WITHOUT ANY WARRANTY; without even the implied warranty of    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    GNU General Public License for more details.     You should have received a copy of the GNU General Public License    along with this program; if not, write to the Free Software    Foundation, Inc., 59 Temple Place - Suite 330,    Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* As a special exception, when this file is copied by Bison into a    Bison output file, you may use that output file without restriction.    This special exception was added by the Free Software Foundation    in version 1.24 of Bison.  */
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
DECL|enumerator|DESCRIPTION
name|DESCRIPTION
init|=
literal|263
block|,
DECL|enumerator|BEGIN_COMMENT
name|BEGIN_COMMENT
init|=
literal|264
block|,
DECL|enumerator|FLOAT
name|FLOAT
init|=
literal|265
block|,
DECL|enumerator|COMMENT
name|COMMENT
init|=
literal|266
block|,
DECL|enumerator|LINK
name|LINK
init|=
literal|267
block|}
enum|;
end_enum

begin_endif
endif|#
directive|endif
end_endif

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
DECL|macro|DESCRIPTION
define|#
directive|define
name|DESCRIPTION
value|263
end_define

begin_define
DECL|macro|BEGIN_COMMENT
define|#
directive|define
name|BEGIN_COMMENT
value|264
end_define

begin_define
DECL|macro|FLOAT
define|#
directive|define
name|FLOAT
value|265
end_define

begin_define
DECL|macro|COMMENT
define|#
directive|define
name|COMMENT
value|266
end_define

begin_define
DECL|macro|LINK
define|#
directive|define
name|LINK
value|267
end_define

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|YYSTYPE
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|YYSTYPE_IS_DECLARED
argument_list|)
end_if

begin_line
line|#
directive|line
number|45
file|"imap_cern.y"
end_line

begin_typedef
DECL|union|YYSTYPE
typedef|typedef
union|union
name|YYSTYPE
block|{
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
name|id
index|[
literal|256
index|]
decl_stmt|;
DECL|typedef|YYSTYPE
block|}
name|YYSTYPE
typedef|;
end_typedef

begin_comment
comment|/* Line 1240 of yacc.c.  */
end_comment

begin_line
line|#
directive|line
number|67
file|"y.tab.h"
end_line

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

begin_define
DECL|macro|YYSTYPE_IS_TRIVIAL
define|#
directive|define
name|YYSTYPE_IS_TRIVIAL
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|YYSTYPE
name|cern_lval
decl_stmt|;
end_decl_stmt

end_unit

