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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpclone.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpcloneoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewablebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_clone_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCloneTool,gimp_clone_tool,GIMP_TYPE_SOURCE_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCloneTool
argument_list|,
argument|gimp_clone_tool
argument_list|,
argument|GIMP_TYPE_SOURCE_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_clone_tool_parent_class
end_define

begin_function
name|void
name|gimp_clone_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_CLONE_TOOL
argument_list|,
name|GIMP_TYPE_CLONE_OPTIONS
argument_list|,
name|gimp_clone_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
argument_list|,
literal|"gimp-clone-tool"
argument_list|,
name|_
argument_list|(
literal|"Clone"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paint using Patterns or Image Regions"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Clone"
argument_list|)
argument_list|,
literal|"C"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_CLONE
argument_list|,
name|GIMP_STOCK_TOOL_CLONE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_class_init (GimpCloneToolClass * klass)
name|gimp_clone_tool_class_init
parameter_list|(
name|GimpCloneToolClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_init (GimpCloneTool * clone)
name|gimp_clone_tool_init
parameter_list|(
name|GimpCloneTool
modifier|*
name|clone
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|clone
argument_list|)
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_CLONE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_object_2
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-pattern-select-set"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to clone"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to set a new clone source"
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|status_paint
operator|=
name|_
argument_list|(
literal|"Click to clone."
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|status_set_source
operator|=
name|_
argument_list|(
literal|"Click to set a new clone source"
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|status_set_source_ctrl
operator|=
name|_
argument_list|(
literal|"%s to set a new clone source"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_clone_options_gui (GimpToolOptions * tool_options)
name|gimp_clone_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"clone-type"
argument_list|,
name|_
argument_list|(
literal|"Source"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"sample-merged"
argument_list|,
name|_
argument_list|(
literal|"Sample merged"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
argument_list|,
name|GIMP_IMAGE_CLONE
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gimp_prop_pattern_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|"pattern-view-type"
argument_list|,
literal|"pattern-view-size"
argument_list|)
expr_stmt|;
name|gimp_enum_radio_frame_add
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|GIMP_PATTERN_CLONE
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"align-mode"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Alignment:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

