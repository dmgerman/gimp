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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-edit.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-bucket-fill.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
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
file|"gimpbucketfilloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpbucketfilltool.h"
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|gimp_bucket_fill_tool_initialize
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
name|gimp_bucket_fill_tool_button_release
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
name|gimp_bucket_fill_tool_modifier_key
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
name|gimp_bucket_fill_tool_cursor_update
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBucketFillTool,gimp_bucket_fill_tool,GIMP_TYPE_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBucketFillTool
argument_list|,
argument|gimp_bucket_fill_tool
argument_list|,
argument|GIMP_TYPE_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_bucket_fill_tool_parent_class
end_define

begin_function
name|void
name|gimp_bucket_fill_tool_register
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
name|GIMP_TYPE_BUCKET_FILL_TOOL
argument_list|,
name|GIMP_TYPE_BUCKET_FILL_OPTIONS
argument_list|,
name|gimp_bucket_fill_options_gui
argument_list|,
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
operator||
name|GIMP_CONTEXT_OPACITY_MASK
operator||
name|GIMP_CONTEXT_PAINT_MODE_MASK
operator||
name|GIMP_CONTEXT_PATTERN_MASK
argument_list|,
literal|"gimp-bucket-fill-tool"
argument_list|,
name|_
argument_list|(
literal|"Bucket Fill"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Bucket Fill Tool: Fill selected area with a color or pattern"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Bucket Fill"
argument_list|)
argument_list|,
literal|"<shift>B"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_BUCKET_FILL
argument_list|,
name|GIMP_STOCK_TOOL_BUCKET_FILL
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_class_init (GimpBucketFillToolClass * klass)
name|gimp_bucket_fill_tool_class_init
parameter_list|(
name|GimpBucketFillToolClass
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
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_bucket_fill_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_bucket_fill_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_bucket_fill_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_bucket_fill_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_init (GimpBucketFillTool * bucket_fill_tool)
name|gimp_bucket_fill_tool_init
parameter_list|(
name|GimpBucketFillTool
modifier|*
name|bucket_fill_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|bucket_fill_tool
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
name|gimp_tool_control_set_wants_click
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
name|GIMP_TOOL_CURSOR_BUCKET_FILL
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_action_opacity
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
literal|"context/context-pattern-select-set"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_bucket_fill_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_bucket_fill_tool_initialize
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
if|if
condition|(
operator|!
name|gimp_item_is_visible
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
literal|"The active layer is not visible."
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
DECL|function|gimp_bucket_fill_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_bucket_fill_tool_button_release
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
name|GimpBucketFillOptions
modifier|*
name|options
init|=
name|GIMP_BUCKET_FILL_TOOL_GET_OPTIONS
argument_list|(
name|tool
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
if|if
condition|(
operator|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CLICK
operator|||
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_NO_MOTION
operator|)
operator|&&
name|gimp_image_coords_in_active_pickable
argument_list|(
name|image
argument_list|,
name|coords
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|TRUE
argument_list|)
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
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
if|if
condition|(
operator|!
name|options
operator|->
name|sample_merged
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
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
name|x
operator|-=
name|off_x
expr_stmt|;
name|y
operator|-=
name|off_y
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|fill_selection
condition|)
block|{
name|GimpFillType
name|fill_type
decl_stmt|;
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
default|default:
case|case
name|GIMP_BUCKET_FILL_FG
case|:
name|fill_type
operator|=
name|GIMP_FILL_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_BG
case|:
name|fill_type
operator|=
name|GIMP_FILL_BACKGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_PATTERN
case|:
name|fill_type
operator|=
name|GIMP_FILL_PATTERN
expr_stmt|;
break|break;
block|}
name|gimp_edit_fill
argument_list|(
name|image
argument_list|,
name|drawable
argument_list|,
name|context
argument_list|,
name|fill_type
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_bucket_fill
argument_list|(
name|drawable
argument_list|,
name|context
argument_list|,
name|options
operator|->
name|fill_mode
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|fill_transparent
argument_list|,
name|options
operator|->
name|fill_criterion
argument_list|,
name|options
operator|->
name|threshold
operator|/
literal|255.0
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_release
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|release_type
argument_list|,
name|display
argument_list|)
expr_stmt|;
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
DECL|function|gimp_bucket_fill_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_bucket_fill_tool_modifier_key
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
name|GimpBucketFillOptions
modifier|*
name|options
init|=
name|GIMP_BUCKET_FILL_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|gimp_get_toggle_behavior_mask
argument_list|()
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
case|case
name|GIMP_BUCKET_FILL_FG
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"fill-mode"
argument_list|,
name|GIMP_BUCKET_FILL_BG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_BG
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"fill-mode"
argument_list|,
name|GIMP_BUCKET_FILL_FG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
elseif|else
if|if
condition|(
name|key
operator|==
name|GDK_SHIFT_MASK
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"fill-selection"
argument_list|,
operator|!
name|options
operator|->
name|fill_selection
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_bucket_fill_tool_cursor_update
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
name|GimpBucketFillOptions
modifier|*
name|options
init|=
name|GIMP_BUCKET_FILL_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_BAD
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
if|if
condition|(
name|gimp_image_coords_in_active_pickable
argument_list|(
name|image
argument_list|,
name|coords
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|TRUE
argument_list|)
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
if|if
condition|(
operator|!
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|&&
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
operator|&&
name|gimp_item_is_visible
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
case|case
name|GIMP_BUCKET_FILL_FG
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_BG
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BACKGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BUCKET_FILL_PATTERN
case|:
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_PATTERN
expr_stmt|;
break|break;
block|}
block|}
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

end_unit

