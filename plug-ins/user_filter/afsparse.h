begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Written 1997 Jens Ch. Restemeier<jchrr@hrz.uni-bielefeld.de>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  *  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|AFSPARSE_H
end_ifndef

begin_define
DECL|macro|AFSPARSE_H
define|#
directive|define
name|AFSPARSE_H
end_define

begin_define
DECL|macro|YYSTYPE
define|#
directive|define
name|YYSTYPE
value|s_afstree *
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|YYDEBUG
end_ifdef

begin_decl_stmt
specifier|extern
name|int
name|yydebug
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|s_afstree
modifier|*
name|get_afstree
parameter_list|(
name|char
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|free_tree
parameter_list|(
name|s_afstree
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|do_parse
parameter_list|(
name|char
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|yylex
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|int
name|yyparse
parameter_list|()
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

