begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__PARSE_H__
end_ifndef

begin_define
DECL|macro|__PARSE_H__
define|#
directive|define
name|__PARSE_H__
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"gcg.h"
end_include

begin_function_decl
name|gint
name|yylex
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|yyerror
parameter_list|(
name|gchar
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|yyparse
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|yydebug
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|yy_flex_debug
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|FILE
modifier|*
name|yyin
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|Module
modifier|*
name|current_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

end_unit

