begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprogressdialog.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogressbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogressdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|PROGRESS_DIALOG_WIDTH
define|#
directive|define
name|PROGRESS_DIALOG_WIDTH
value|400
end_define

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProgress
modifier|*
name|gimp_progress_dialog_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_progress_dialog_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_progress_dialog_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_progress_dialog_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpProgressDialog,gimp_progress_dialog,GIMP_TYPE_DIALOG,G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,gimp_progress_dialog_progress_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpProgressDialog
argument_list|,
argument|gimp_progress_dialog
argument_list|,
argument|GIMP_TYPE_DIALOG
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,                                                 gimp_progress_dialog_progress_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_progress_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_progress_dialog_class_init
parameter_list|(
name|GimpProgressDialogClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|dialog_class
operator|->
name|response
operator|=
name|gimp_progress_dialog_response
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_init (GimpProgressDialog * dialog)
name|gimp_progress_dialog_init
parameter_list|(
name|GimpProgressDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|content_area
init|=
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
decl_stmt|;
name|dialog
operator|->
name|box
operator|=
name|gimp_progress_box_new
argument_list|()
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|content_area
argument_list|)
argument_list|,
name|dialog
operator|->
name|box
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
operator|->
name|box
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|dialog
operator|->
name|box
argument_list|)
expr_stmt|;
name|gtk_dialog_add_button
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|PROGRESS_DIALOG_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_progress_iface_init (GimpProgressInterface * iface)
name|gimp_progress_dialog_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_progress_dialog_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_progress_dialog_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_progress_dialog_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_progress_dialog_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_progress_dialog_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_progress_dialog_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_progress_dialog_progress_pulse
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_response (GtkDialog * dialog,gint response_id)
name|gimp_progress_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|progress_dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_PROGRESS_BOX
argument_list|(
name|progress_dialog
operator|->
name|box
argument_list|)
operator|->
name|cancelable
condition|)
name|gimp_progress_cancel
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gimp_progress_dialog_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_progress_dialog_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|message
argument_list|,
name|cancelable
argument_list|)
condition|)
block|{
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|cancelable
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|progress
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_progress_end (GimpProgress * progress)
name|gimp_progress_dialog_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return;
if|if
condition|(
name|GIMP_PROGRESS_BOX
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
operator|->
name|active
condition|)
block|{
name|gimp_progress_end
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_progress_dialog_progress_is_active (GimpProgress * progress)
name|gimp_progress_dialog_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return
name|FALSE
return|;
return|return
name|gimp_progress_is_active
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_progress_dialog_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return;
name|gimp_progress_set_text
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_progress_dialog_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return;
name|gimp_progress_set_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_progress_dialog_progress_get_value (GimpProgress * progress)
name|gimp_progress_dialog_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return
literal|0.0
return|;
return|return
name|gimp_progress_get_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_dialog_progress_pulse (GimpProgress * progress)
name|gimp_progress_dialog_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressDialog
modifier|*
name|dialog
init|=
name|GIMP_PROGRESS_DIALOG
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|dialog
operator|->
name|box
condition|)
return|return;
name|gimp_progress_pulse
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|dialog
operator|->
name|box
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_progress_dialog_new (void)
name|gimp_progress_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PROGRESS_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|_
argument_list|(
literal|"Progress"
argument_list|)
argument_list|,
literal|"role"
argument_list|,
literal|"progress"
argument_list|,
literal|"skip-taskbar-hint"
argument_list|,
name|TRUE
argument_list|,
literal|"skip-pager-hint"
argument_list|,
name|TRUE
argument_list|,
literal|"resizable"
argument_list|,
name|FALSE
argument_list|,
literal|"focus-on-map"
argument_list|,
name|FALSE
argument_list|,
literal|"window-position"
argument_list|,
name|GTK_WIN_POS_CENTER
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

