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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"tool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"dialog_handler.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  Global Data  */
end_comment

begin_decl_stmt
DECL|variable|active_tool
name|GimpTool
modifier|*
name|active_tool
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|registered_tools
name|GSList
modifier|*
name|registered_tools
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Local  Data  */
end_comment

begin_comment
comment|/*  Function definitions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|active_tool_unref (void)
name|active_tool_unref
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
operator|!
name|active_tool
condition|)
return|return;
name|gimp_tool_hide_options
argument_list|(
name|active_tool
argument_list|)
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|active_tool
argument_list|)
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_select (GimpTool * tool)
name|tool_manager_select
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
if|if
condition|(
name|active_tool
condition|)
name|active_tool_unref
argument_list|()
expr_stmt|;
name|active_tool
operator|=
name|tool
expr_stmt|;
name|tool_options_show
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_control_active (ToolAction action,GDisplay * gdisp)
name|tool_manager_control_active
parameter_list|(
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|active_tool
condition|)
name|gimp_tool_control
argument_list|(
name|active_tool
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  standard member functions  */
end_comment

begin_warning
warning|#
directive|warning
warning|bogosity alert
end_warning

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|void tools_register (ToolType     tool_type, 		ToolOptions *tool_options) {   g_return_if_fail (tool_options != NULL);    tool_info [(gint) tool_type].tool_options = tool_options;
comment|/*  need to check whether the widget is visible...this can happen    *  because some tools share options such as the transformation tools    */
end_comment

begin_endif
unit|if (! GTK_WIDGET_VISIBLE (tool_options->main_vbox))     {       gtk_box_pack_start (GTK_BOX (options_vbox), tool_options->main_vbox, 			  TRUE, TRUE, 0);       gtk_widget_show (tool_options->main_vbox);     }    gtk_label_set_text (GTK_LABEL (options_label), tool_options->title);    gtk_pixmap_set (GTK_PIXMAP (options_pixmap), 		  tool_get_pixmap (tool_type), tool_get_mask (tool_type));    gtk_widget_queue_draw (options_pixmap);    gimp_help_set_help_data (options_eventbox, 			   gettext (tool_info[(gint) tool_type].tool_desc), 			   tool_info[(gint) tool_type].private_tip); }
endif|#
directive|endif
end_endif

begin_comment
comment|/*  Tool options function  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|tool_manager_get_active_PDB_string (void)
name|tool_manager_get_active_PDB_string
parameter_list|(
name|void
parameter_list|)
block|{
name|gchar
modifier|*
name|toolStr
init|=
literal|"gimp_paintbrush_default"
decl_stmt|;
comment|/*  Return the correct PDB function for the active tool    *  The default is paintbrush if the tool is not recognised    */
if|if
condition|(
operator|!
name|active_tool
condition|)
return|return
name|toolStr
return|;
return|return
name|gimp_tool_get_PDB_string
argument_list|(
name|active_tool
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|tool_manager_active_get_help_data (void)
name|tool_manager_active_get_help_data
parameter_list|(
name|void
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|active_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_tool_get_help_data
argument_list|(
name|active_tool
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|tool_manager_register (GimpToolClass * tool_type)
name|void
name|tool_manager_register
parameter_list|(
name|GimpToolClass
modifier|*
name|tool_type
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|objclass
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|tool_type
argument_list|)
decl_stmt|;
name|g_message
argument_list|(
literal|"registering %s."
argument_list|,
name|gtk_type_name
argument_list|(
name|objclass
operator|->
name|type
argument_list|)
argument_list|)
expr_stmt|;
name|registered_tools
operator|=
name|g_slist_append
argument_list|(
name|registered_tools
argument_list|,
name|tool_type
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|gtk_type_new
argument_list|(
name|objclass
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

