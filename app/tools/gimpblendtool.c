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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-blend.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendtool.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|TARGET_SIZE
define|#
directive|define
name|TARGET_SIZE
value|15
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_blend_tool_class_init
parameter_list|(
name|GimpBlendToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blend_tool_init
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blend_tool_button_press
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
name|gimp_blend_tool_button_release
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
name|gimp_blend_tool_motion
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
name|gimp_blend_tool_cursor_update
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
name|gimp_blend_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_blend_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_blend_tool_register
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
name|GIMP_TYPE_BLEND_TOOL
argument_list|,
name|GIMP_TYPE_BLEND_OPTIONS
argument_list|,
name|gimp_blend_options_gui
argument_list|,
name|TRUE
argument_list|,
literal|"gimp-blend-tool"
argument_list|,
name|_
argument_list|(
literal|"Blend"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Fill with a color gradient"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/Blend"
argument_list|)
argument_list|,
literal|"L"
argument_list|,
name|NULL
argument_list|,
literal|"tools/blend.html"
argument_list|,
name|GIMP_STOCK_TOOL_BLEND
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_blend_tool_get_type (void)
name|gimp_blend_tool_get_type
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
name|GimpBlendToolClass
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
name|gimp_blend_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBlendTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_blend_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
literal|"GimpBlendTool"
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
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_class_init (GimpBlendToolClass * klass)
name|gimp_blend_tool_class_init
parameter_list|(
name|GimpBlendToolClass
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
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_blend_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_blend_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_blend_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_blend_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_blend_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_init (GimpBlendTool * blend_tool)
name|gimp_blend_tool_init
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
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
name|blend_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_BLEND_TOOL_CURSOR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_blend_tool_button_press
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
name|GimpBlendTool
modifier|*
name|blend_tool
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|blend_tool
operator|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|GIMP_INDEXED_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Blend: Invalid for indexed images."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
break|break;
default|default:
break|break;
block|}
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|blend_tool
operator|->
name|endx
operator|=
name|blend_tool
operator|->
name|startx
operator|=
name|coords
operator|->
name|x
operator|-
name|off_x
expr_stmt|;
name|blend_tool
operator|->
name|endy
operator|=
name|blend_tool
operator|->
name|starty
operator|=
name|coords
operator|->
name|y
operator|-
name|off_y
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/* initialize the statusbar display */
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Blend: 0, 0"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Start drawing the blend tool  */
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_blend_tool_button_release
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
name|GimpBlendTool
modifier|*
name|blend_tool
decl_stmt|;
name|GimpBlendOptions
modifier|*
name|options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|blend_tool
operator|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_BLEND_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|/*  if the 3rd button isn't pressed, fill the selected region  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
operator|&&
operator|(
operator|(
name|blend_tool
operator|->
name|startx
operator|!=
name|blend_tool
operator|->
name|endx
operator|)
operator|||
operator|(
name|blend_tool
operator|->
name|starty
operator|!=
name|blend_tool
operator|->
name|endy
operator|)
operator|)
condition|)
block|{
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Blending..."
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_blend
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|GIMP_CUSTOM_MODE
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|gradient_type
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|offset
argument_list|,
name|options
operator|->
name|repeat
argument_list|,
name|options
operator|->
name|supersample
argument_list|,
name|options
operator|->
name|supersample_depth
argument_list|,
name|options
operator|->
name|supersample_threshold
argument_list|,
name|blend_tool
operator|->
name|startx
argument_list|,
name|blend_tool
operator|->
name|starty
argument_list|,
name|blend_tool
operator|->
name|endx
argument_list|,
name|blend_tool
operator|->
name|endy
argument_list|,
name|progress
condition|?
name|gimp_progress_update_and_flush
else|:
name|NULL
argument_list|,
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_blend_tool_motion
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
name|GimpBlendTool
modifier|*
name|blend_tool
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|blend_tool
operator|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
comment|/*  Get the current coordinates  */
name|blend_tool
operator|->
name|endx
operator|=
name|coords
operator|->
name|x
operator|-
name|off_x
expr_stmt|;
name|blend_tool
operator|->
name|endy
operator|=
name|coords
operator|->
name|y
operator|-
name|off_y
expr_stmt|;
comment|/* Restrict to multiples of 15 degrees if ctrl is pressed */
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|gint
name|tangens2
index|[
literal|6
index|]
init|=
block|{
literal|34
block|,
literal|106
block|,
literal|196
block|,
literal|334
block|,
literal|618
block|,
literal|1944
block|}
decl_stmt|;
name|gint
name|cosinus
index|[
literal|7
index|]
init|=
block|{
literal|256
block|,
literal|247
block|,
literal|222
block|,
literal|181
block|,
literal|128
block|,
literal|66
block|,
literal|0
block|}
decl_stmt|;
name|gint
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|i
decl_stmt|,
name|radius
decl_stmt|,
name|frac
decl_stmt|;
name|dx
operator|=
name|blend_tool
operator|->
name|endx
operator|-
name|blend_tool
operator|->
name|startx
expr_stmt|;
name|dy
operator|=
name|blend_tool
operator|->
name|endy
operator|-
name|blend_tool
operator|->
name|starty
expr_stmt|;
if|if
condition|(
name|dy
condition|)
block|{
name|radius
operator|=
name|sqrt
argument_list|(
name|SQR
argument_list|(
name|dx
argument_list|)
operator|+
name|SQR
argument_list|(
name|dy
argument_list|)
argument_list|)
expr_stmt|;
name|frac
operator|=
name|abs
argument_list|(
operator|(
name|dx
operator|<<
literal|8
operator|)
operator|/
name|dy
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|frac
operator|<
name|tangens2
index|[
name|i
index|]
condition|)
break|break;
block|}
name|dx
operator|=
name|dx
operator|>
literal|0
condition|?
operator|(
name|cosinus
index|[
literal|6
operator|-
name|i
index|]
operator|*
name|radius
operator|)
operator|>>
literal|8
else|:
operator|-
operator|(
operator|(
name|cosinus
index|[
literal|6
operator|-
name|i
index|]
operator|*
name|radius
operator|)
operator|>>
literal|8
operator|)
expr_stmt|;
name|dy
operator|=
name|dy
operator|>
literal|0
condition|?
operator|(
name|cosinus
index|[
name|i
index|]
operator|*
name|radius
operator|)
operator|>>
literal|8
else|:
operator|-
operator|(
operator|(
name|cosinus
index|[
name|i
index|]
operator|*
name|radius
operator|)
operator|>>
literal|8
operator|)
expr_stmt|;
block|}
name|blend_tool
operator|->
name|endx
operator|=
name|blend_tool
operator|->
name|startx
operator|+
name|dx
expr_stmt|;
name|blend_tool
operator|->
name|endy
operator|=
name|blend_tool
operator|->
name|starty
operator|+
name|dy
expr_stmt|;
block|}
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_push_status_coords
argument_list|(
name|tool
argument_list|,
name|_
argument_list|(
literal|"Blend: "
argument_list|)
argument_list|,
name|blend_tool
operator|->
name|endx
operator|-
name|blend_tool
operator|->
name|startx
argument_list|,
literal|", "
argument_list|,
name|blend_tool
operator|->
name|endy
operator|-
name|blend_tool
operator|->
name|starty
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_blend_tool_cursor_update
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
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GIMP_INDEXED_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_BAD_CURSOR
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOUSE_CURSOR
argument_list|)
expr_stmt|;
break|break;
block|}
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
DECL|function|gimp_blend_tool_draw (GimpDrawTool * draw_tool)
name|gimp_blend_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpBlendTool
modifier|*
name|blend_tool
decl_stmt|;
name|blend_tool
operator|=
name|GIMP_BLEND_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
comment|/*  Draw start target  */
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|startx
argument_list|)
operator|+
literal|0.5
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|starty
argument_list|)
operator|+
literal|0.5
argument_list|,
name|TARGET_SIZE
argument_list|,
name|TARGET_SIZE
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Draw end target  */
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|endx
argument_list|)
operator|+
literal|0.5
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|endy
argument_list|)
operator|+
literal|0.5
argument_list|,
name|TARGET_SIZE
argument_list|,
name|TARGET_SIZE
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  Draw the line between the start and end coords  */
name|gimp_draw_tool_draw_line
argument_list|(
name|draw_tool
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|startx
argument_list|)
operator|+
literal|0.5
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|starty
argument_list|)
operator|+
literal|0.5
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|endx
argument_list|)
operator|+
literal|0.5
argument_list|,
name|floor
argument_list|(
name|blend_tool
operator|->
name|endy
argument_list|)
operator|+
literal|0.5
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

