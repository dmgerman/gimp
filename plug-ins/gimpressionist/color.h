begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__COLOR_H
end_ifndef

begin_define
DECL|macro|__COLOR_H
define|#
directive|define
name|__COLOR_H
end_define

begin_enum
DECL|enum|COLOR_TYPE_ENUM
enum|enum
name|COLOR_TYPE_ENUM
block|{
DECL|enumerator|COLOR_TYPE_AVERAGE
name|COLOR_TYPE_AVERAGE
init|=
literal|0
block|,
DECL|enumerator|COLOR_TYPE_CENTER
name|COLOR_TYPE_CENTER
init|=
literal|1
block|, }
enum|;
end_enum

begin_function_decl
name|void
name|create_colorpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|color_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* #ifndef __COLOR_H */
end_comment

end_unit

