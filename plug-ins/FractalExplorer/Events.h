begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__FRACTALEXPLORER_EVENTS_H__
end_ifndef

begin_define
DECL|macro|__FRACTALEXPLORER_EVENTS_H__
define|#
directive|define
name|__FRACTALEXPLORER_EVENTS_H__
end_define

begin_comment
comment|/* Preview events */
end_comment

begin_function_decl
name|gint
name|preview_button_press_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_button_release_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_motion_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_leave_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|preview_enter_notify_event
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

