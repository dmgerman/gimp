begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"config/gimpconfig-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-color.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcoloroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolortool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28a6c4590103
block|{
DECL|enumerator|PICKED
name|PICKED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_tool_class_init
parameter_list|(
name|GimpColorToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_tool_init
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_tool_finalize
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
name|gimp_color_tool_button_press
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
name|gimp_color_tool_button_release
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
name|gimp_color_tool_motion
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
name|gimp_color_tool_cursor_update
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
name|gimp_color_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_color_tool_real_pick
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_tool_pick
parameter_list|(
name|GimpColorTool
modifier|*
name|tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_color_tool_signals
specifier|static
name|guint
name|gimp_color_tool_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

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

begin_function
name|GtkType
DECL|function|gimp_color_tool_get_type (void)
name|gimp_color_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GimpColorToolClass
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
name|gimp_color_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
literal|"GimpColorTool"
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

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_class_init (GimpColorToolClass * klass)
name|gimp_color_tool_class_init
parameter_list|(
name|GimpColorToolClass
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
name|draw_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_color_tool_signals
index|[
name|PICKED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"picked"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpColorToolClass
argument_list|,
name|picked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM_ENUM_BOXED_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|GIMP_TYPE_COLOR_PICK_STATE
argument_list|,
name|GIMP_TYPE_IMAGE_TYPE
argument_list|,
name|GIMP_TYPE_COLOR
operator||
name|G_SIGNAL_TYPE_STATIC_SCOPE
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_color_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_color_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_color_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_color_tool_cursor_update
expr_stmt|;
name|draw_class
operator|->
name|draw
operator|=
name|gimp_color_tool_draw
expr_stmt|;
name|klass
operator|->
name|pick
operator|=
name|gimp_color_tool_real_pick
expr_stmt|;
name|klass
operator|->
name|picked
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_finalize (GObject * object)
name|gimp_color_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorTool
modifier|*
name|color_tool
init|=
name|GIMP_COLOR_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|color_tool
operator|->
name|options
condition|)
block|{
name|g_object_unref
argument_list|(
name|color_tool
operator|->
name|options
argument_list|)
expr_stmt|;
name|color_tool
operator|->
name|options
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_init (GimpColorTool * color_tool)
name|gimp_color_tool_init
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
block|{
name|color_tool
operator|->
name|enabled
operator|=
name|FALSE
expr_stmt|;
name|color_tool
operator|->
name|center_x
operator|=
literal|0
expr_stmt|;
name|color_tool
operator|->
name|center_y
operator|=
literal|0
expr_stmt|;
name|color_tool
operator|->
name|pick_mode
operator|=
name|GIMP_COLOR_PICK_MODE_NONE
expr_stmt|;
name|color_tool
operator|->
name|options
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_color_tool_button_press
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
name|GimpColorTool
modifier|*
name|color_tool
decl_stmt|;
comment|/*  Make the tool active and set it's gdisplay& drawable  */
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|tool
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
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|color_tool
operator|=
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|color_tool
operator|->
name|enabled
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
comment|/*  Keep the coordinates of the target  */
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|tool
operator|->
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
name|color_tool
operator|->
name|center_x
operator|=
name|coords
operator|->
name|x
operator|-
name|off_x
expr_stmt|;
name|color_tool
operator|->
name|center_y
operator|=
name|coords
operator|->
name|y
operator|-
name|off_y
expr_stmt|;
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
name|gimp_color_tool_pick
argument_list|(
name|color_tool
argument_list|,
name|GIMP_COLOR_PICK_STATE_NEW
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_color_tool_button_release
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
if|if
condition|(
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|enabled
condition|)
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_color_tool_motion
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
name|GimpColorTool
modifier|*
name|color_tool
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|color_tool
operator|=
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_tool
operator|->
name|enabled
condition|)
return|return;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|tool
operator|->
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
name|color_tool
operator|->
name|center_x
operator|=
name|coords
operator|->
name|x
operator|-
name|off_x
expr_stmt|;
name|color_tool
operator|->
name|center_y
operator|=
name|coords
operator|->
name|y
operator|-
name|off_y
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_tool_pick
argument_list|(
name|color_tool
argument_list|,
name|GIMP_COLOR_PICK_STATE_UPDATE
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_color_tool_cursor_update
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
name|GimpColorTool
modifier|*
name|color_tool
init|=
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|color_tool
operator|->
name|enabled
condition|)
block|{
name|GimpCursorType
name|cursor
init|=
name|GIMP_CURSOR_BAD
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|>
literal|0
operator|&&
name|coords
operator|->
name|x
operator|<
name|gdisp
operator|->
name|gimage
operator|->
name|width
operator|&&
name|coords
operator|->
name|y
operator|>
literal|0
operator|&&
name|coords
operator|->
name|y
operator|<
name|gdisp
operator|->
name|gimage
operator|->
name|height
operator|&&
operator|(
name|color_tool
operator|->
name|options
operator|->
name|sample_merged
operator|||
name|gimp_display_coords_in_active_drawable
argument_list|(
name|gdisp
argument_list|,
name|coords
argument_list|)
operator|)
condition|)
block|{
name|cursor
operator|=
name|GIMP_CURSOR_COLOR_PICKER
expr_stmt|;
block|}
switch|switch
condition|(
name|color_tool
operator|->
name|pick_mode
condition|)
block|{
case|case
name|GIMP_COLOR_PICK_MODE_NONE
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_FOREGROUND
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_BACKGROUND
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BACKGROUND
expr_stmt|;
break|break;
block|}
name|gimp_tool_set_cursor
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|cursor
argument_list|,
name|GIMP_TOOL_CURSOR_COLOR_PICKER
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
return|return;
comment|/*  don't chain up  */
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
DECL|function|gimp_color_tool_draw (GimpDrawTool * draw_tool)
name|gimp_color_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpColorTool
modifier|*
name|color_tool
init|=
name|GIMP_COLOR_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|color_tool
operator|->
name|enabled
condition|)
return|return;
if|if
condition|(
name|color_tool
operator|->
name|options
operator|->
name|sample_average
condition|)
block|{
name|gdouble
name|radius
init|=
name|color_tool
operator|->
name|options
operator|->
name|average_radius
decl_stmt|;
name|gimp_draw_tool_draw_rectangle
argument_list|(
name|draw_tool
argument_list|,
name|FALSE
argument_list|,
name|color_tool
operator|->
name|center_x
operator|-
name|radius
argument_list|,
name|color_tool
operator|->
name|center_y
operator|-
name|radius
argument_list|,
literal|2
operator|*
name|radius
operator|+
literal|1
argument_list|,
literal|2
operator|*
name|radius
operator|+
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_tool_real_pick (GimpColorTool * color_tool,gint x,gint y,GimpImageType * sample_type,GimpRGB * color,gint * color_index)
name|gimp_color_tool_real_pick
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|color_tool
argument_list|)
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool
operator|->
name|gdisp
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool
operator|->
name|drawable
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|gimp_image_pick_color
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|,
name|tool
operator|->
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|color_tool
operator|->
name|options
operator|->
name|sample_merged
argument_list|,
name|color_tool
operator|->
name|options
operator|->
name|sample_average
argument_list|,
name|color_tool
operator|->
name|options
operator|->
name|average_radius
argument_list|,
name|sample_type
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_tool_pick (GimpColorTool * tool,GimpColorPickState pick_state,gint x,gint y)
name|gimp_color_tool_pick
parameter_list|(
name|GimpColorTool
modifier|*
name|tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|GimpColorToolClass
modifier|*
name|klass
decl_stmt|;
name|GimpImageType
name|sample_type
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|color_index
decl_stmt|;
name|klass
operator|=
name|GIMP_COLOR_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|klass
operator|->
name|pick
operator|&&
name|klass
operator|->
name|pick
argument_list|(
name|tool
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|sample_type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|color_index
argument_list|)
condition|)
block|{
name|g_signal_emit
argument_list|(
name|tool
argument_list|,
name|gimp_color_tool_signals
index|[
name|PICKED
index|]
argument_list|,
literal|0
argument_list|,
name|pick_state
argument_list|,
name|sample_type
argument_list|,
operator|&
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_tool_enable (GimpColorTool * color_tool,GimpColorOptions * options)
name|gimp_color_tool_enable
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpColorOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_TOOL
argument_list|(
name|color_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|color_tool
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
name|g_warning
argument_list|(
literal|"Trying to enable GimpColorTool while it is active."
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|color_tool
operator|->
name|options
condition|)
block|{
name|g_object_unref
argument_list|(
name|color_tool
operator|->
name|options
argument_list|)
expr_stmt|;
name|color_tool
operator|->
name|options
operator|=
name|NULL
expr_stmt|;
block|}
name|color_tool
operator|->
name|options
operator|=
name|g_object_ref
argument_list|(
name|options
argument_list|)
expr_stmt|;
name|color_tool
operator|->
name|enabled
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_color_tool_disable (GimpColorTool * color_tool)
name|gimp_color_tool_disable
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COLOR_TOOL
argument_list|(
name|color_tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|color_tool
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
name|g_warning
argument_list|(
literal|"Trying to disable GimpColorTool while it is active."
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|color_tool
operator|->
name|options
condition|)
block|{
name|g_object_unref
argument_list|(
name|color_tool
operator|->
name|options
argument_list|)
expr_stmt|;
name|color_tool
operator|->
name|options
operator|=
name|NULL
expr_stmt|;
block|}
name|color_tool
operator|->
name|enabled
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_color_tool_is_enabled (GimpColorTool * color_tool)
name|gimp_color_tool_is_enabled
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|)
block|{
return|return
name|color_tool
operator|->
name|enabled
return|;
block|}
end_function

end_unit

