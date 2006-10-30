begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__PREVIEW_H
end_ifndef

begin_define
DECL|macro|__PREVIEW_H
define|#
directive|define
name|__PREVIEW_H
end_define

begin_function_decl
name|GtkWidget
modifier|*
name|create_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|updatepreview
parameter_list|(
name|GtkWidget
modifier|*
name|wg
parameter_list|,
name|gpointer
name|d
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preview_free_resources
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|preview_set_button_label
parameter_list|(
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* #ifndef __PREVIEW_H */
end_comment

end_unit

