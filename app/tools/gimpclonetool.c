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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
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
file|"widgets/gimppropwidgets.h"
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

begin_define
DECL|macro|TARGET_WIDTH
define|#
directive|define
name|TARGET_WIDTH
value|15
end_define

begin_define
DECL|macro|TARGET_HEIGHT
define|#
directive|define
name|TARGET_HEIGHT
value|15
end_define

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_class_init
parameter_list|(
name|GimpCloneToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_init
parameter_list|(
name|GimpCloneTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_clone_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_init_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_finish_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_pretrace_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_clone_posttrace_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintToolClass
modifier|*
name|parent_class
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_clone_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
literal|"/Tools/Paint Tools/_Clone"
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
name|GType
DECL|function|gimp_clone_tool_get_type (void)
name|gimp_clone_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpCloneToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_clone_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpCloneTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_clone_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|,
literal|"GimpCloneTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_comment
comment|/* static functions  */
end_comment

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
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_clone_tool_constructor
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_clone_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_clone_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_clone_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_clone_tool_draw
expr_stmt|;
block|}
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
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|clone
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|clone
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CLONE_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_clone_tool_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_clone_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|GimpClone
modifier|*
name|clone_core
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|clone_core
operator|=
name|GIMP_CLONE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
expr_stmt|;
name|clone_core
operator|->
name|init_callback
operator|=
name|gimp_clone_init_callback
expr_stmt|;
name|clone_core
operator|->
name|finish_callback
operator|=
name|gimp_clone_finish_callback
expr_stmt|;
name|clone_core
operator|->
name|pretrace_callback
operator|=
name|gimp_clone_pretrace_callback
expr_stmt|;
name|clone_core
operator|->
name|posttrace_callback
operator|=
name|gimp_clone_posttrace_callback
expr_stmt|;
name|clone_core
operator|->
name|callback_data
operator|=
name|object
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_clone_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|GIMP_CLONE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
operator|->
name|set_source
operator|=
name|TRUE
expr_stmt|;
else|else
name|GIMP_CLONE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
operator|->
name|set_source
operator|=
name|FALSE
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_clone_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|GIMP_CLONE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
operator|->
name|set_source
operator|=
name|TRUE
expr_stmt|;
else|else
name|GIMP_CLONE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
operator|->
name|set_source
operator|=
name|FALSE
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|motion
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_clone_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_clone_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpCloneOptions
modifier|*
name|options
decl_stmt|;
name|GdkCursorType
name|ctype
init|=
name|GIMP_MOUSE_CURSOR
decl_stmt|;
name|options
operator|=
operator|(
name|GimpCloneOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
if|if
condition|(
name|gimp_display_coords_in_active_drawable
argument_list|(
name|gdisp
argument_list|,
name|coords
argument_list|)
condition|)
block|{
comment|/*  One more test--is there a selected region?        *  if so, is cursor inside?        */
if|if
condition|(
name|gimp_image_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
condition|)
name|ctype
operator|=
name|GIMP_MOUSE_CURSOR
expr_stmt|;
elseif|else
if|if
condition|(
name|gimp_image_mask_value
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
condition|)
name|ctype
operator|=
name|GIMP_MOUSE_CURSOR
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|clone_type
operator|==
name|GIMP_IMAGE_CLONE
condition|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|ctype
operator|=
name|GIMP_CROSSHAIR_SMALL_CURSOR
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GIMP_CLONE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|core
argument_list|)
operator|->
name|src_drawable
condition|)
name|ctype
operator|=
name|GIMP_BAD_CURSOR
expr_stmt|;
block|}
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|ctype
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_tool_draw (GimpDrawTool * draw_tool)
name|gimp_clone_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
block|{
name|GimpCloneOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|GimpCloneOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
if|if
condition|(
name|draw_tool
operator|->
name|gdisp
operator|&&
name|options
operator|->
name|clone_type
operator|==
name|GIMP_IMAGE_CLONE
condition|)
block|{
name|GimpClone
modifier|*
name|clone
decl_stmt|;
name|clone
operator|=
name|GIMP_CLONE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|draw_tool
argument_list|)
operator|->
name|core
argument_list|)
expr_stmt|;
if|if
condition|(
name|clone
operator|->
name|src_drawable
condition|)
block|{
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|clone
operator|->
name|src_drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|clone
operator|->
name|src_x
operator|+
name|off_x
argument_list|,
name|clone
operator|->
name|src_y
operator|+
name|off_y
argument_list|,
name|TARGET_WIDTH
argument_list|,
name|TARGET_WIDTH
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|draw
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_init_callback (GimpClone * clone,gpointer data)
name|gimp_clone_init_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|data
argument_list|)
argument_list|,
name|GIMP_TOOL
argument_list|(
name|data
argument_list|)
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_finish_callback (GimpClone * clone,gpointer data)
name|gimp_clone_finish_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_pretrace_callback (GimpClone * clone,gpointer data)
name|gimp_clone_pretrace_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_clone_posttrace_callback (GimpClone * clone,gpointer data)
name|gimp_clone_posttrace_callback
parameter_list|(
name|GimpClone
modifier|*
name|clone
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|data
argument_list|)
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
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
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
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"align-mode"
argument_list|,
name|_
argument_list|(
literal|"Alignment"
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
return|return
name|vbox
return|;
block|}
end_function

end_unit

