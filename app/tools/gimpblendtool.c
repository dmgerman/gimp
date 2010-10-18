begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
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
file|"core/gimperror.h"
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
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
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
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
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
name|gboolean
name|gimp_blend_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
specifier|const
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
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
specifier|const
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
specifier|const
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_blend_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
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

begin_function_decl
specifier|static
name|void
name|gimp_blend_tool_push_status
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBlendTool,gimp_blend_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBlendTool
argument_list|,
argument|gimp_blend_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_blend_tool_parent_class
end_define

begin_function
name|void
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
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
operator||
name|GIMP_CONTEXT_OPACITY_MASK
operator||
name|GIMP_CONTEXT_PAINT_MODE_MASK
operator||
name|GIMP_CONTEXT_GRADIENT_MASK
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
literal|"Blend Tool: Fill selected area with a color gradient"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Blen_d"
argument_list|)
argument_list|,
literal|"L"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_BLEND
argument_list|,
name|GIMP_STOCK_TOOL_BLEND
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

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
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_blend_tool_initialize
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
name|active_modifier_key
operator|=
name|gimp_blend_tool_active_modifier_key
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
init|=
name|GIMP_TOOL
argument_list|(
name|blend_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_PRECISION_SUBPIXEL
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MOUSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_BLEND
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_value_1
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-opacity-set"
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_object_1
argument_list|(
name|tool
operator|->
name|control
argument_list|,
literal|"context/context-gradient-select-set"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_blend_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_blend_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Blend does not operate on indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Cannot modify the pixels of layer groups."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"The active layer's pixels are locked."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_blend_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBlendTool
modifier|*
name|blend_tool
init|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|blend_tool
operator|->
name|start_x
operator|=
name|blend_tool
operator|->
name|end_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|blend_tool
operator|->
name|start_y
operator|=
name|blend_tool
operator|->
name|end_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|blend_tool
operator|->
name|last_x
operator|=
name|blend_tool
operator|->
name|mouse_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|blend_tool
operator|->
name|last_y
operator|=
name|blend_tool
operator|->
name|mouse_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_blend_tool_push_status
argument_list|(
name|blend_tool
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_blend_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBlendTool
modifier|*
name|blend_tool
init|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpBlendOptions
modifier|*
name|options
init|=
name|GIMP_BLEND_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|paint_options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
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
if|if
condition|(
operator|(
name|release_type
operator|!=
name|GIMP_BUTTON_RELEASE_CANCEL
operator|)
operator|&&
operator|(
operator|(
name|blend_tool
operator|->
name|start_x
operator|!=
name|blend_tool
operator|->
name|end_x
operator|)
operator|||
operator|(
name|blend_tool
operator|->
name|start_y
operator|!=
name|blend_tool
operator|->
name|end_y
operator|)
operator|)
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
name|gint
name|off_x
decl_stmt|;
name|gint
name|off_y
decl_stmt|;
name|progress
operator|=
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Blending"
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|gimp_drawable_blend
argument_list|(
name|drawable
argument_list|,
name|context
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
name|paint_options
operator|->
name|gradient_options
operator|->
name|gradient_repeat
argument_list|,
name|paint_options
operator|->
name|gradient_options
operator|->
name|gradient_reverse
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
name|options
operator|->
name|dither
argument_list|,
name|blend_tool
operator|->
name|start_x
operator|-
name|off_x
argument_list|,
name|blend_tool
operator|->
name|start_y
operator|-
name|off_y
argument_list|,
name|blend_tool
operator|->
name|end_x
operator|-
name|off_x
argument_list|,
name|blend_tool
operator|->
name|end_y
operator|-
name|off_y
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
name|image
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_blend_tool_motion
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|display
parameter_list|)
block|{
name|GimpBlendTool
modifier|*
name|blend_tool
init|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|blend_tool
operator|->
name|mouse_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|blend_tool
operator|->
name|mouse_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
comment|/* Move the whole line if alt is pressed */
if|if
condition|(
name|state
operator|&
name|GDK_MOD1_MASK
condition|)
block|{
name|gdouble
name|dx
init|=
name|blend_tool
operator|->
name|last_x
operator|-
name|coords
operator|->
name|x
decl_stmt|;
name|gdouble
name|dy
init|=
name|blend_tool
operator|->
name|last_y
operator|-
name|coords
operator|->
name|y
decl_stmt|;
name|blend_tool
operator|->
name|start_x
operator|-=
name|dx
expr_stmt|;
name|blend_tool
operator|->
name|start_y
operator|-=
name|dy
expr_stmt|;
name|blend_tool
operator|->
name|end_x
operator|-=
name|dx
expr_stmt|;
name|blend_tool
operator|->
name|end_y
operator|-=
name|dy
expr_stmt|;
block|}
else|else
block|{
name|blend_tool
operator|->
name|end_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|blend_tool
operator|->
name|end_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|gimp_constrain_line
argument_list|(
name|blend_tool
operator|->
name|start_x
argument_list|,
name|blend_tool
operator|->
name|start_y
argument_list|,
operator|&
name|blend_tool
operator|->
name|end_x
argument_list|,
operator|&
name|blend_tool
operator|->
name|end_y
argument_list|,
name|GIMP_CONSTRAIN_LINE_15_DEGREES
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_blend_tool_push_status
argument_list|(
name|blend_tool
argument_list|,
name|state
argument_list|,
name|display
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
name|blend_tool
operator|->
name|last_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|blend_tool
operator|->
name|last_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_active_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_blend_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpBlendTool
modifier|*
name|blend_tool
init|=
name|GIMP_BLEND_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|blend_tool
operator|->
name|end_x
operator|=
name|blend_tool
operator|->
name|mouse_x
expr_stmt|;
name|blend_tool
operator|->
name|end_y
operator|=
name|blend_tool
operator|->
name|mouse_y
expr_stmt|;
comment|/* Restrict to multiples of 15 degrees if ctrl is pressed */
if|if
condition|(
name|press
condition|)
block|{
name|gimp_constrain_line
argument_list|(
name|blend_tool
operator|->
name|start_x
argument_list|,
name|blend_tool
operator|->
name|start_y
argument_list|,
operator|&
name|blend_tool
operator|->
name|end_x
argument_list|,
operator|&
name|blend_tool
operator|->
name|end_y
argument_list|,
name|GIMP_CONSTRAIN_LINE_15_DEGREES
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_blend_tool_push_status
argument_list|(
name|blend_tool
argument_list|,
name|state
argument_list|,
name|display
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_blend_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
operator|||
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|||
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|modifier
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
name|display
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
init|=
name|GIMP_BLEND_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
comment|/*  Draw the line between the start and end coords  */
name|gimp_draw_tool_add_line
argument_list|(
name|draw_tool
argument_list|,
name|blend_tool
operator|->
name|start_x
argument_list|,
name|blend_tool
operator|->
name|start_y
argument_list|,
name|blend_tool
operator|->
name|end_x
argument_list|,
name|blend_tool
operator|->
name|end_y
argument_list|)
expr_stmt|;
comment|/*  Draw start target  */
name|gimp_draw_tool_add_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|blend_tool
operator|->
name|start_x
argument_list|,
name|blend_tool
operator|->
name|start_y
argument_list|,
name|TARGET_SIZE
argument_list|,
name|TARGET_SIZE
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
expr_stmt|;
comment|/*  Draw end target  */
name|gimp_draw_tool_add_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|blend_tool
operator|->
name|end_x
argument_list|,
name|blend_tool
operator|->
name|end_y
argument_list|,
name|TARGET_SIZE
argument_list|,
name|TARGET_SIZE
argument_list|,
name|GIMP_HANDLE_ANCHOR_CENTER
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_blend_tool_push_status (GimpBlendTool * blend_tool,GdkModifierType state,GimpDisplay * display)
name|gimp_blend_tool_push_status
parameter_list|(
name|GimpBlendTool
modifier|*
name|blend_tool
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|blend_tool
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|status_help
decl_stmt|;
name|status_help
operator|=
name|gimp_suggest_modifiers
argument_list|(
literal|""
argument_list|,
operator|(
operator|(
name|GDK_CONTROL_MASK
operator||
name|GDK_MOD1_MASK
operator|)
operator|&
operator|~
name|state
operator|)
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"%s for constrained angles"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"%s to move the whole line"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_push_status_coords
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|gimp_tool_control_get_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Blend: "
argument_list|)
argument_list|,
name|blend_tool
operator|->
name|end_x
operator|-
name|blend_tool
operator|->
name|start_x
argument_list|,
literal|", "
argument_list|,
name|blend_tool
operator|->
name|end_y
operator|-
name|blend_tool
operator|->
name|start_y
argument_list|,
name|status_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status_help
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

