begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|SIOD_WRAPPER_H
end_ifndef

begin_define
DECL|macro|SIOD_WRAPPER_H
define|#
directive|define
name|SIOD_WRAPPER_H
end_define

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_function_decl
name|void
name|siod_init
parameter_list|(
name|gboolean
name|register_scripts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|FILE
modifier|*
name|siod_get_output_file
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_set_output_file
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|siod_get_verbose_level
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_set_verbose_level
parameter_list|(
name|int
name|verbose_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|siod_print_welcome
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|char
modifier|*
name|siod_get_error_msg
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|char
modifier|*
name|siod_get_success_msg
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* if the return value is 0, success. error otherwise. */
end_comment

begin_function_decl
name|int
name|siod_interpret_string
parameter_list|(
specifier|const
name|char
modifier|*
name|expr
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* SIOD_WRAPPER_H */
end_comment

end_unit

