begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MAPOBJECT_UI_H__
end_ifndef

begin_define
DECL|macro|__MAPOBJECT_UI_H__
define|#
directive|define
name|__MAPOBJECT_UI_H__
end_define

begin_comment
comment|/* Externally visible variables */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_decl_stmt
specifier|extern
name|GtkWidget
modifier|*
name|previewarea
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Externally visible functions */
end_comment

begin_comment
comment|/* ============================ */
end_comment

begin_function_decl
name|gboolean
name|main_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MAPOBJECT_UI_H__ */
end_comment

end_unit

