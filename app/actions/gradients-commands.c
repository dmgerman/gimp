begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gradients-commands.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gradients_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradients_save_as_pov_query
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gradients_save_as_pov_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gradients_save_as_pov_ray_cmd_callback (GtkWidget * widget,gpointer data)
name|gradients_save_as_pov_ray_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|editor
operator|=
operator|(
name|GimpContainerEditor
operator|*
operator|)
name|gimp_widget_get_callback_context
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|editor
condition|)
return|return;
name|gradients_save_as_pov_query
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gradients_show_context_menu (GimpContainerEditor * editor)
name|gradients_show_context_menu
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|gradients_menu_set_sensitivity
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|menus_get_gradients_factory
argument_list|()
expr_stmt|;
name|gimp_item_factory_popup_with_data
argument_list|(
name|item_factory
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gradients_menu_set_sensitivity (GimpContainerEditor * editor)
name|gradients_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (menu,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|menus_set_sensitive ("<Gradients>/" menu, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"Duplicate Gradient"
argument_list|,
name|gradient
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|gradient
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Edit Gradient..."
argument_list|,
name|gradient
operator|&&
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
operator|->
name|data_edit_func
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Delete Gradient..."
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Save as POV-Ray..."
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradients_save_as_pov_query (GimpContainerEditor * editor)
name|gradients_save_as_pov_query
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpGradient
modifier|*
name|gradient
decl_stmt|;
name|GtkFileSelection
modifier|*
name|filesel
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gradient
operator|=
name|gimp_context_get_gradient
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gradient
condition|)
return|return;
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Save \"%s\" as POV-Ray"
argument_list|)
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gradient
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|filesel
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|gtk_file_selection_new
argument_list|(
name|title
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"save_gradient"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesel
operator|->
name|button_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradients_save_as_pov_ok_callback
argument_list|)
argument_list|,
name|gradient
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroy
argument_list|)
argument_list|,
name|filesel
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|G_OBJECT
argument_list|(
name|filesel
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|g_object_unref
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|gradient
argument_list|)
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesel
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/save_as_povray.html"
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradients_save_as_pov_ok_callback (GtkWidget * widget,GimpGradient * gradient)
name|gradients_save_as_pov_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpGradient
modifier|*
name|gradient
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|filesel
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|GimpGradientSegment
modifier|*
name|seg
decl_stmt|;
name|gchar
name|buf
index|[
literal|3
index|]
index|[
name|G_ASCII_DTOSTR_BUF_SIZE
index|]
decl_stmt|;
name|filesel
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|filesel
argument_list|)
expr_stmt|;
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_message
argument_list|(
literal|"Could not open \"%s\""
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"/* color_map file created by the GIMP */\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"/* http://www.gimp.org/               */\n"
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"color_map {\n"
argument_list|)
expr_stmt|;
for|for
control|(
name|seg
operator|=
name|gradient
operator|->
name|segments
init|;
name|seg
condition|;
name|seg
operator|=
name|seg
operator|->
name|next
control|)
block|{
comment|/* Left */
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|left_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
name|seg
operator|->
name|left_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%f color rgbt<%s, %s, %s, %s>]\n"
argument_list|,
name|seg
operator|->
name|left
argument_list|,
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|buf
index|[
literal|2
index|]
argument_list|,
name|buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
comment|/* Middle */
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|r
operator|+
name|seg
operator|->
name|right_color
operator|.
name|r
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|g
operator|+
name|seg
operator|->
name|right_color
operator|.
name|g
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
operator|(
name|seg
operator|->
name|left_color
operator|.
name|b
operator|+
name|seg
operator|->
name|right_color
operator|.
name|b
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
operator|(
name|seg
operator|->
name|left_color
operator|.
name|a
operator|+
name|seg
operator|->
name|right_color
operator|.
name|a
operator|)
operator|/
literal|2.0
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%f color rgbt<%f, %f, %f, %f>]\n"
argument_list|,
name|seg
operator|->
name|middle
argument_list|,
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|buf
index|[
literal|2
index|]
argument_list|,
name|buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
comment|/* Right */
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|0
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|r
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|1
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|g
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|2
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
name|seg
operator|->
name|right_color
operator|.
name|b
argument_list|)
expr_stmt|;
name|g_ascii_formatd
argument_list|(
name|buf
index|[
literal|3
index|]
argument_list|,
name|G_ASCII_DTOSTR_BUF_SIZE
argument_list|,
literal|"%f"
argument_list|,
literal|1.0
operator|-
name|seg
operator|->
name|right_color
operator|.
name|a
argument_list|)
expr_stmt|;
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"\t[%f color rgbt<%f, %f, %f, %f>]\n"
argument_list|,
name|seg
operator|->
name|right
argument_list|,
name|buf
index|[
literal|0
index|]
argument_list|,
name|buf
index|[
literal|1
index|]
argument_list|,
name|buf
index|[
literal|2
index|]
argument_list|,
name|buf
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
block|}
name|fprintf
argument_list|(
name|file
argument_list|,
literal|"} /* color_map */\n"
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesel
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

