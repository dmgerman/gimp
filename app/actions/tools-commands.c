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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"app_procs.h"
end_include

begin_define
DECL|macro|return_if_no_display (gdisp)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|)
define|\
value|gdisp = gdisplay_active (); \         if (!gdisp) return
end_define

begin_function
name|void
DECL|function|tools_default_colors_cmd_callback (GtkWidget * widget,gpointer data)
name|tools_default_colors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_context_set_default_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_swap_colors_cmd_callback (GtkWidget * widget,gpointer data)
name|tools_swap_colors_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_context_swap_colors
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tools_swap_contexts_cmd_callback (GtkWidget * widget,gpointer data)
name|tools_swap_contexts_cmd_callback
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
name|GimpContext
modifier|*
name|swap_context
init|=
name|NULL
decl_stmt|;
specifier|static
name|GimpContext
modifier|*
name|temp_context
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|swap_context
condition|)
block|{
name|swap_context
operator|=
name|gimp_create_context
argument_list|(
name|the_gimp
argument_list|,
literal|"Swap Context"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|)
expr_stmt|;
name|temp_context
operator|=
name|gimp_create_context
argument_list|(
name|the_gimp
argument_list|,
literal|"Temp Context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gimp_context_copy_properties
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|temp_context
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
argument_list|)
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|swap_context
argument_list|,
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
argument_list|)
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|temp_context
argument_list|,
name|swap_context
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
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
name|GtkType
name|tool_type
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|tool_type
operator|=
operator|(
name|GtkType
operator|)
name|action
expr_stmt|;
name|tool_info
operator|=
name|tool_manager_get_info_by_type
argument_list|(
name|the_gimp
argument_list|,
name|tool_type
argument_list|)
expr_stmt|;
name|gdisp
operator|=
name|gdisplay_active
argument_list|()
expr_stmt|;
name|gimp_context_set_tool
argument_list|(
name|gimp_get_user_context
argument_list|(
name|the_gimp
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME (let the tool manager to this stuff)
endif|#
directive|endif
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
comment|/*  Paranoia  */
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
comment|/*  Complete the initialisation by doing the same stuff    *  tools_initialize() does after it did what tools_select() does    */
if|if
condition|(
name|GIMP_TOOL_GET_CLASS
argument_list|(
name|active_tool
argument_list|)
operator|->
name|initialize
condition|)
block|{
name|gimp_tool_initialize
argument_list|(
name|active_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
comment|/*  setting the tool->gdisp here is a HACK to allow the tools'    *  dialog windows being hidden if the tool was selected from    *  a tear-off-menu and there was no mouse click in the display    *  before deleting it    */
name|active_tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
block|}
end_function

end_unit

