begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__BRUSH_H
end_ifndef

begin_define
DECL|macro|__BRUSH_H
define|#
directive|define
name|__BRUSH_H
end_define

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_function_decl
name|void
name|brush_store
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_brushpage
parameter_list|(
name|GtkNotebook
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|brush_get_selected
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* #ifndef __BRUSH_H */
end_comment

end_unit

