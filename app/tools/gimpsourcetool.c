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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
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
name|GimpToolOptions
modifier|*
name|clone_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|clone_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
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
name|clone_options_new
argument_list|,
name|TRUE
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
literal|"/Tools/Paint Tools/Clone"
argument_list|)
argument_list|,
literal|"C"
argument_list|,
name|NULL
argument_list|,
literal|"tools/clone.html"
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
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
decl_stmt|;
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
name|GimpClone
modifier|*
name|clone_core
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
name|clone_core
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_CLONE
argument_list|,
name|NULL
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
name|clone
expr_stmt|;
name|paint_tool
operator|->
name|core
operator|=
name|GIMP_PAINT_CORE
argument_list|(
name|clone_core
argument_list|)
expr_stmt|;
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
block|{
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
block|}
else|else
block|{
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
block|}
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
block|{
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
block|}
else|else
block|{
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
block|}
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
name|GimpLayer
modifier|*
name|layer
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
operator|(
name|layer
operator|=
name|gimp_image_get_active_layer
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|>=
name|off_x
operator|&&
name|coords
operator|->
name|y
operator|>=
name|off_y
operator|&&
name|coords
operator|->
name|x
operator|<
operator|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
operator|&&
name|coords
operator|->
name|y
operator|<
operator|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
operator|)
condition|)
block|{
comment|/*  One more test--is there a selected region? 	   *  if so, is cursor inside? 	   */
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
block|}
if|if
condition|(
name|options
operator|->
name|type
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
name|type
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
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|clone
operator|->
name|src_x
argument_list|,
name|clone
operator|->
name|src_y
argument_list|,
name|TARGET_WIDTH
argument_list|,
name|TARGET_WIDTH
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
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
name|GimpCloneTool
modifier|*
name|clone_tool
decl_stmt|;
name|clone_tool
operator|=
name|GIMP_CLONE_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|clone_tool
argument_list|)
argument_list|,
name|GIMP_TOOL
argument_list|(
name|clone_tool
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
name|GimpCloneTool
modifier|*
name|clone_tool
decl_stmt|;
name|clone_tool
operator|=
name|GIMP_CLONE_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|clone_tool
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
name|GimpCloneTool
modifier|*
name|clone_tool
decl_stmt|;
name|clone_tool
operator|=
name|GIMP_CLONE_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|clone_tool
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
name|GimpCloneTool
modifier|*
name|clone_tool
decl_stmt|;
name|clone_tool
operator|=
name|GIMP_CLONE_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|clone_tool
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
name|GimpToolOptions
modifier|*
DECL|function|clone_options_new (GimpToolInfo * tool_info)
name|clone_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|GimpCloneOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|options
operator|=
name|gimp_clone_options_new
argument_list|()
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|reset_func
operator|=
name|clone_options_reset
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_CLONE_TYPE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Source"
argument_list|)
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type
argument_list|,
operator|&
name|options
operator|->
name|type_w
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|type
argument_list|)
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
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_CLONE_ALIGN_MODE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Alignment"
argument_list|)
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|aligned
argument_list|,
operator|&
name|options
operator|->
name|aligned_w
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|aligned_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|aligned
argument_list|)
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
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|clone_options_reset (GimpToolOptions * tool_options)
name|clone_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
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
name|tool_options
expr_stmt|;
name|paint_options_reset
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|type_d
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|aligned_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|aligned_d
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

