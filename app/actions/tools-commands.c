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
file|"actions-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"tools-commands.h"
end_include

begin_define
DECL|macro|return_if_no_gimp (gimp,data)
define|#
directive|define
name|return_if_no_gimp
parameter_list|(
name|gimp
parameter_list|,
name|data
parameter_list|)
define|\
value|if (GIMP_IS_DISPLAY (data)) \     gimp = ((GimpDisplay *) data)->gimage->gimp; \   else if (GIMP_IS_GIMP (data)) \     gimp = data; \   else if (GIMP_IS_DOCK (data)) \     gimp = ((GimpDock *) data)->context->gimp; \   else \     gimp = NULL; \   if (! gimp) \     return
end_define

begin_function
name|void
DECL|function|tools_default_colors_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tools_default_colors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_context_set_default_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_swap_colors_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tools_swap_colors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_context_swap_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_select_cmd_callback (GtkWidget * widget,gpointer data,guint action)
name|tools_select_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|return_if_no_gimp
argument_list|(
name|gimp
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|identifier
operator|=
name|g_quark_to_string
argument_list|(
operator|(
name|GQuark
operator|)
name|action
argument_list|)
expr_stmt|;
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|tool_info_list
argument_list|,
name|identifier
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  always allocate a new tool when selected from the image menu    */
if|if
condition|(
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
operator|!=
name|tool_info
condition|)
block|{
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_tool_changed
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|gdisp
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
name|tool_manager_initialize_active
argument_list|(
name|gimp
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

