begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                    * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialog.c  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *                                                     * This library is distributed in the hope that it will be useful  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_comment
comment|/* strcmp */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/wilber.xpm"
end_include

begin_comment
comment|/*  local callbacks of gimp_dialog_new ()  */
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_dialog_delete_callback (GtkWidget * widget,GdkEvent * event,gpointer data)
name|gimp_dialog_delete_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkSignalFunc
name|cancel_callback
decl_stmt|;
name|GtkWidget
modifier|*
name|cancel_widget
decl_stmt|;
name|cancel_callback
operator|=
operator|(
name|GtkSignalFunc
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_callback"
argument_list|)
expr_stmt|;
name|cancel_widget
operator|=
operator|(
name|GtkWidget
operator|*
operator|)
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_widget"
argument_list|)
expr_stmt|;
comment|/*  the cancel callback has to destroy the dialog  */
if|if
condition|(
name|cancel_callback
condition|)
call|(
modifier|*
name|cancel_callback
call|)
argument_list|(
name|cancel_widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dialog_realize_callback (GtkWidget * widget,gpointer data)
name|gimp_dialog_realize_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|GdkPixmap
modifier|*
name|wilber_pixmap
init|=
name|NULL
decl_stmt|;
specifier|static
name|GdkBitmap
modifier|*
name|wilber_mask
init|=
name|NULL
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|wilber_pixmap
operator|==
name|NULL
condition|)
name|wilber_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|wilber_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|wilber_xpm
argument_list|)
expr_stmt|;
name|gdk_window_set_icon
argument_list|(
name|widget
operator|->
name|window
argument_list|,
name|NULL
argument_list|,
name|wilber_pixmap
argument_list|,
name|wilber_mask
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_new:  * @title: The dialog's title which will be set with gtk_window_set_title().  * @wmclass_name: The dialog's @wmclass_name which will be set with  *                gtk_window_set_wmclass(). The @wmclass_class will be  *                automatically set to "Gimp".  * @help_func: The function which will be called if the user presses "F1".  * @help_data: The data pointer which will be passed to @help_func.  * @position: The dialog's initial position which will be set with  *            gtk_window_set_position().  * @allow_shrink: The dialog's @allow_shrink flag, ...  * @allow_grow: ... it't @allow_grow flag and ...  * @auto_shrink: ... it's @auto_shrink flag which will all be set with  *               gtk_window_set_policy().  * @...: A #NULL terminated @va_list destribing the action_area buttons.  *  * This function simply packs the action_area arguments passed in "..."  * into a @va_list variable and passes everything to gimp_dialog_newv().  *  * For a description of the format of the @va_list describing the  * action_area buttons see gimp_dialog_create_action_areav().  *  * Returns: A #GtkDialog.  *  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dialog_new (const gchar * title,const gchar * wmclass_name,GimpHelpFunc help_func,const gchar * help_data,GtkWindowPosition position,gint allow_shrink,gint allow_grow,gint auto_shrink,...)
name|gimp_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
comment|/* specify action area buttons as va_list: 		  *  const gchar    *label, 		  *  GtkSignalFunc   callback, 		  *  gpointer        data, 		  *  GtkObject      *slot_object, 		  *  GtkWidget     **widget_ptr, 		  *  gboolean        default_action, 		  *  gboolean        connect_delete, 		  */
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|auto_shrink
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_newv
argument_list|(
name|title
argument_list|,
name|wmclass_name
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|,
name|position
argument_list|,
name|allow_shrink
argument_list|,
name|allow_grow
argument_list|,
name|auto_shrink
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_newv:  * @title: The dialog's title which will be set with gtk_window_set_title().  * @wmclass_name: The dialog's @wmclass_name which will be set with  *                gtk_window_set_wmclass(). The @wmclass_class will be  *                automatically set to "Gimp".  * @help_func: The function which will be called if the user presses "F1".  * @help_data: The data pointer which will be passed to @help_func.  * @position: The dialog's initial position which will be set with  *            gtk_window_set_position().  * @allow_shrink: The dialog's @allow_shrink flag, ...  * @allow_grow: ... it't @allow_grow flag and ...  * @auto_shrink: ... it's @auto_shrink flag which will all be set with  *               gtk_window_set_policy().  * @args: A @va_list as obtained with va_start() describing the action_area  *        buttons.  *  * This function performs all neccessary setps to set up a standard GIMP  * dialog.  *  * The @va_list describing the action_area buttons will be passed to  * gimp_dialog_create_action_areav().  *  * Returns: A #GtkDialog.  *  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_dialog_newv (const gchar * title,const gchar * wmclass_name,GimpHelpFunc help_func,const gchar * help_data,GtkWindowPosition position,gint allow_shrink,gint allow_grow,gint auto_shrink,va_list args)
name|gimp_dialog_newv
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|wmclass_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|wmclass_name
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|position
argument_list|)
expr_stmt|;
name|gtk_window_set_policy
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|allow_shrink
argument_list|,
name|allow_grow
argument_list|,
name|auto_shrink
argument_list|)
expr_stmt|;
comment|/*  prepare the action_area  */
name|gimp_dialog_create_action_areav
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
comment|/*  connect the "F1" help key  */
if|if
condition|(
name|help_func
condition|)
name|gimp_help_connect_help_accel
argument_list|(
name|dialog
argument_list|,
name|help_func
argument_list|,
name|help_data
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_set_icon:  * @dialog: The #GtkWindow you want to set the pixmap icon for.  *  * This function sets the WM pixmap icon for the dialog which will appear  * e.g. in GNOME's or KDE's window list.  *  * Note that this function is automatically called by  * gimp_help_connect_help_accel() which in turn is called by  * gimp_dialog_newv(), so you only have to call it for #GtkWindow's which  * have no help page (like tear-off menus).  *  */
end_comment

begin_function
name|void
DECL|function|gimp_dialog_set_icon (GtkWindow * dialog)
name|gimp_dialog_set_icon
parameter_list|(
name|GtkWindow
modifier|*
name|dialog
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_REALIZED
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
condition|)
name|gimp_dialog_realize_callback
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"realize"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dialog_realize_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_create_action_area:  * @dialog: The #GtkDialog you want to create the action_area for.  * @...: A #NULL terminated @va_list destribing the action_area buttons.  *  * This function simply packs the action_area arguments passed in "..."  * into a @va_list variable and passes everything to  * gimp_dialog_create_action_areav().  *  */
end_comment

begin_function
name|void
DECL|function|gimp_dialog_create_action_area (GtkDialog * dialog,...)
name|gimp_dialog_create_action_area
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
comment|/* specify action area buttons as va_list: 				 *  const gchar    *label, 				 *  GtkSignalFunc   callback, 				 *  gpointer        data, 				 *  GtkObject      *slot_object, 				 *  GtkWidget     **widget_ptr, 				 *  gboolean        default_action, 				 *  gboolean        connect_delete, 				 */
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|gimp_dialog_create_action_areav
argument_list|(
name|dialog
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_dialog_create_action_areav:  * @dialog: The #GtkDialog you want to create the action_area for.  * @args: A @va_list as obtained with va_start() describing the action_area  *        buttons.  *  * Please note that the delete_event will only be connected to the first  * button with the "connect_delete" boolean set to true. It is possible  * to just connect the delete_event to a callback without adding a new  * button with a special label "_delete_event_", connect_delete == true  * and callback != NULL.  *  */
end_comment

begin_function
name|void
DECL|function|gimp_dialog_create_action_areav (GtkDialog * dialog,va_list args)
name|gimp_dialog_create_action_areav
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|va_list
name|args
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbbox
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
comment|/*  action area variables  */
specifier|const
name|gchar
modifier|*
name|label
decl_stmt|;
name|GtkSignalFunc
name|callback
decl_stmt|;
name|gpointer
name|data
decl_stmt|;
name|GtkObject
modifier|*
name|slot_object
decl_stmt|;
name|GtkWidget
modifier|*
modifier|*
name|widget_ptr
decl_stmt|;
name|gboolean
name|default_action
decl_stmt|;
name|gboolean
name|connect_delete
decl_stmt|;
name|gboolean
name|delete_connected
init|=
name|FALSE
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|dialog
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
specifier|const
name|gchar
operator|*
argument_list|)
expr_stmt|;
comment|/*  the action_area buttons  */
while|while
condition|(
name|label
condition|)
block|{
name|callback
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkSignalFunc
argument_list|)
expr_stmt|;
name|data
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gpointer
argument_list|)
expr_stmt|;
name|slot_object
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkObject
operator|*
argument_list|)
expr_stmt|;
name|widget_ptr
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|GtkWidget
operator|*
operator|*
argument_list|)
expr_stmt|;
name|default_action
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gboolean
argument_list|)
expr_stmt|;
name|connect_delete
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gboolean
argument_list|)
expr_stmt|;
if|if
condition|(
name|slot_object
operator|==
operator|(
name|GtkObject
operator|*
operator|)
literal|1
condition|)
name|slot_object
operator|=
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|==
name|NULL
condition|)
name|data
operator|=
name|dialog
expr_stmt|;
comment|/*        * Dont create a button if the label is "_delete_event_" --        * some dialogs just need to connect to the delete_event from        * the window...        */
if|if
condition|(
name|connect_delete
operator|&&
name|callback
operator|&&
operator|!
name|delete_connected
operator|&&
name|strcmp
argument_list|(
name|label
argument_list|,
literal|"_delete_event_"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|widget_ptr
condition|)
operator|*
name|widget_ptr
operator|=
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_callback"
argument_list|,
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_widget"
argument_list|,
name|slot_object
condition|?
name|slot_object
else|:
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  catch the WM delete event  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dialog_delete_callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|delete_connected
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/* otherwise just create the requested button. */
else|else
block|{
if|if
condition|(
name|hbbox
operator|==
name|NULL
condition|)
block|{
comment|/*  prepare the action_area  */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|hbbox
operator|=
name|gtk_hbutton_box_new
argument_list|()
expr_stmt|;
name|gtk_button_box_set_spacing
argument_list|(
name|GTK_BUTTON_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|dialog
operator|->
name|action_area
argument_list|)
argument_list|,
name|hbbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbbox
argument_list|)
expr_stmt|;
block|}
name|button
operator|=
name|gtk_button_new_with_label
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|GTK_WIDGET_SET_FLAGS
argument_list|(
name|button
argument_list|,
name|GTK_CAN_DEFAULT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbbox
argument_list|)
argument_list|,
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|callback
condition|)
block|{
if|if
condition|(
name|slot_object
condition|)
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|callback
argument_list|)
argument_list|,
name|slot_object
argument_list|)
expr_stmt|;
else|else
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|widget_ptr
condition|)
operator|*
name|widget_ptr
operator|=
name|button
expr_stmt|;
if|if
condition|(
name|connect_delete
operator|&&
name|callback
operator|&&
operator|!
name|delete_connected
condition|)
block|{
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_callback"
argument_list|,
name|callback
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp_dialog_cancel_widget"
argument_list|,
name|slot_object
condition|?
name|slot_object
else|:
name|GTK_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  catch the WM delete event  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_dialog_delete_callback
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|delete_connected
operator|=
name|TRUE
expr_stmt|;
block|}
if|if
condition|(
name|default_action
condition|)
name|gtk_widget_grab_default
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
name|label
operator|=
name|va_arg
argument_list|(
name|args
argument_list|,
name|gchar
operator|*
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

