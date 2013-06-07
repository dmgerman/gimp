begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolgui.c  * Copyright (C) 2013  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpoverlaybox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpoverlaydialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimptooldialog.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolgui.h"
end_include

begin_typedef
DECL|typedef|GimpToolGuiPrivate
typedef|typedef
name|struct
name|_GimpToolGuiPrivate
name|GimpToolGuiPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolGuiPrivate
struct|struct
name|_GimpToolGuiPrivate
block|{
DECL|member|overlay
name|gboolean
name|overlay
decl_stmt|;
DECL|member|desc
name|gchar
modifier|*
name|desc
decl_stmt|;
DECL|member|tool_info
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (gui)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|gui
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (gui, \                                                       GIMP_TYPE_TOOL_GUI, \                                                       GimpToolGuiPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_tool_gui_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_gui_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolGui,gimp_tool_gui,GIMP_TYPE_OBJECT)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolGui
argument_list|,
argument|gimp_tool_gui
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_tool_gui_class_init
parameter_list|(
name|GimpToolGuiClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_tool_gui_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_tool_gui_finalize
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpToolGuiPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_gui_init (GimpToolGui * gui)
name|gimp_tool_gui_init
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_gui_dispose (GObject * object)
name|gimp_tool_gui_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|shell
condition|)
name|gimp_tool_gui_set_shell
argument_list|(
name|GIMP_TOOL_GUI
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|dialog
condition|)
block|{
if|if
condition|(
name|private
operator|->
name|overlay
condition|)
name|g_object_unref
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_destroy
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|private
operator|->
name|dialog
operator|=
name|NULL
expr_stmt|;
name|private
operator|->
name|vbox
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|gimp_tool_gui_parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_gui_finalize (GObject * object)
name|gimp_tool_gui_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|desc
condition|)
block|{
name|g_free
argument_list|(
name|private
operator|->
name|desc
argument_list|)
expr_stmt|;
name|private
operator|->
name|desc
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|gimp_tool_gui_parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tool_gui_new:  * @tool_info: a #GimpToolInfo  * @shell:     the parent display shell this gui  * @desc:      a string to use in the gui header or %NULL to use the help  *             field from #GimpToolInfo  * @...:       a %NULL-terminated valist of button parameters as described in  *             gtk_gui_new_with_buttons().  *  * This function creates a #GimpToolGui using the information stored  * in @tool_info.  *  * Return value: a new #GimpToolGui  **/
end_comment

begin_function
name|GimpToolGui
modifier|*
DECL|function|gimp_tool_gui_new (GimpToolInfo * tool_info,GimpDisplayShell * shell,const gchar * desc,gboolean overlay,...)
name|gimp_tool_gui_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
name|gboolean
name|overlay
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GimpToolGui
modifier|*
name|gui
decl_stmt|;
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gui
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_GUI
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
name|private
operator|->
name|overlay
operator|=
name|overlay
expr_stmt|;
name|private
operator|->
name|desc
operator|=
name|g_strdup
argument_list|(
name|desc
argument_list|)
expr_stmt|;
name|private
operator|->
name|tool_info
operator|=
name|tool_info
expr_stmt|;
if|if
condition|(
name|overlay
condition|)
block|{
name|private
operator|->
name|dialog
operator|=
name|gimp_overlay_dialog_new
argument_list|(
name|tool_info
argument_list|,
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_ref_sink
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|overlay
argument_list|)
expr_stmt|;
name|gimp_overlay_dialog_add_buttons_valist
argument_list|(
name|GIMP_OVERLAY_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|private
operator|->
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|private
operator|->
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|vbox
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|private
operator|->
name|dialog
operator|=
name|gimp_tool_dialog_new
argument_list|(
name|tool_info
argument_list|,
name|shell
argument_list|,
name|desc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|overlay
argument_list|)
expr_stmt|;
name|gimp_dialog_add_buttons_valist
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|private
operator|->
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|private
operator|->
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|private
operator|->
name|vbox
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
name|private
operator|->
name|vbox
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_gui_set_shell
argument_list|(
name|GIMP_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
return|return
name|gui
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_set_shell (GimpToolGui * gui,GimpDisplayShell * shell)
name|gimp_tool_gui_set_shell
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|shell
operator|==
name|NULL
operator|||
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|==
name|private
operator|->
name|shell
condition|)
return|return;
if|if
condition|(
operator|!
name|private
operator|->
name|overlay
condition|)
block|{
name|gimp_tool_dialog_set_shell
argument_list|(
name|GIMP_TOOL_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
name|private
operator|->
name|shell
operator|=
name|shell
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_set_viewable (GimpToolGui * gui,GimpViewable * viewable)
name|gimp_tool_gui_set_viewable
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VIEWABLE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|private
operator|->
name|overlay
condition|)
block|{
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|viewable
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|private
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_gui_get_dialog (GimpToolGui * gui)
name|gimp_tool_gui_get_dialog
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
operator|->
name|dialog
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_gui_get_vbox (GimpToolGui * gui)
name|gimp_tool_gui_get_vbox
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
operator|->
name|vbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_show (GimpToolGui * gui)
name|gimp_tool_gui_show
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overlay
condition|)
block|{
if|if
condition|(
operator|!
name|gtk_widget_get_parent
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
condition|)
block|{
name|gimp_overlay_box_add_child
argument_list|(
name|GIMP_OVERLAY_BOX
argument_list|(
name|private
operator|->
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|private
operator|->
name|dialog
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_hide (GimpToolGui * gui)
name|gimp_tool_gui_hide
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overlay
condition|)
block|{
if|if
condition|(
name|gtk_widget_get_parent
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
condition|)
block|{
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|gtk_widget_get_parent
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|gimp_dialog_factory_from_widget
argument_list|(
name|private
operator|->
name|dialog
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_dialog_factory_hide_dialog
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_widget_hide
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_set_default_response (GimpToolGui * gui,gint response_id)
name|gimp_tool_gui_set_default_response
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overlay
condition|)
block|{
comment|/* TODO */
block|}
else|else
block|{
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|response_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_gui_set_response_sensitive (GimpToolGui * gui,gint response_id,gboolean sensitive)
name|gimp_tool_gui_set_response_sensitive
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|GimpToolGuiPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_GUI
argument_list|(
name|gui
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|overlay
condition|)
block|{
comment|/* TODO */
block|}
else|else
block|{
name|gtk_dialog_set_response_sensitive
argument_list|(
name|GTK_DIALOG
argument_list|(
name|private
operator|->
name|dialog
argument_list|)
argument_list|,
name|response_id
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

