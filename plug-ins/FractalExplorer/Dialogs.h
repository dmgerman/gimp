begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__FRACTALEXPLORER_DIALOGS_H__
end_ifndef

begin_define
DECL|macro|__FRACTALEXPLORER_DIALOGS_H__
define|#
directive|define
name|__FRACTALEXPLORER_DIALOGS_H__
end_define

begin_function_decl
name|gint
name|explorer_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialog_update_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|set_cmap_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|make_color_map
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|dialog_change_scale
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_options
parameter_list|(
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|save_callback
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|file_selection_ok
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkFileSelection
modifier|*
name|fs
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|load_file_selection_ok
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkFileSelection
modifier|*
name|fs
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_load_file_selection
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|create_file_selection
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|get_line
parameter_list|(
name|gchar
modifier|*
name|buf
parameter_list|,
name|gint
name|s
parameter_list|,
name|FILE
modifier|*
name|from
parameter_list|,
name|gint
name|init
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|load_options
parameter_list|(
name|fractalexplorerOBJ
modifier|*
name|xxx
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|explorer_load
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

