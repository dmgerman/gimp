begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__file_dialog_new_h__
end_ifndef

begin_define
DECL|macro|__file_dialog_new_h__
define|#
directive|define
name|__file_dialog_new_h__
end_define

begin_include
include|#
directive|include
file|"gtk/gtk.h"
end_include

begin_function_decl
name|void
name|file_new_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|guint
name|callback_action
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FILE_DIALOG_NEW_H__ */
end_comment

end_unit

