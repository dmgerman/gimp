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
file|<gdk/gdkkeysyms.h>
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
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-bucket-fill.h"
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
file|"widgets/gimphelp-ids.h"
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_class_init
parameter_list|(
name|GimpBucketFillToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_init
parameter_list|(
name|GimpBucketFillTool
modifier|*
name|bucket_fill_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_bucket_fill_tool_button_press
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
name|gimp_bucket_fill_tool_button_release
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
name|gdisp
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

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_bucket_fill_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
literal|"Fill with a color or pattern"
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
name|GType
DECL|function|gimp_bucket_fill_tool_get_type (void)
name|gimp_bucket_fill_tool_get_type
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
name|GimpBucketFillToolClass
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
name|gimp_bucket_fill_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBucketFillTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_bucket_fill_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
literal|"GimpBucketFillTool"
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
name|gimp_bucket_fill_tool_button_press
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
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_BUCKET_FILL
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
literal|"context/context-pattern-select-set"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_button_press
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
name|GimpBucketFillTool
modifier|*
name|bucket_tool
init|=
name|GIMP_BUCKET_FILL_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpBucketFillOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_BUCKET_FILL_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|bucket_tool
operator|->
name|target_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|bucket_tool
operator|->
name|target_y
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
name|gimp_item_offsets
argument_list|(
name|GIMP_ITEM
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|bucket_tool
operator|->
name|target_x
operator|-=
name|off_x
expr_stmt|;
name|bucket_tool
operator|->
name|target_y
operator|-=
name|off_y
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_bucket_fill_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_button_release
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
name|GimpBucketFillTool
modifier|*
name|bucket_tool
init|=
name|GIMP_BUCKET_FILL_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpBucketFillOptions
modifier|*
name|options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|options
operator|=
name|GIMP_BUCKET_FILL_OPTIONS
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
comment|/*  if the 3rd button isn't pressed, fill the selected region  */
if|if
condition|(
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
name|gimp_drawable_bucket_fill
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
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
operator|!
name|options
operator|->
name|fill_selection
argument_list|,
name|options
operator|->
name|fill_transparent
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|bucket_tool
operator|->
name|target_x
argument_list|,
name|bucket_tool
operator|->
name|target_y
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
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
DECL|function|gimp_bucket_fill_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
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
name|gdisp
parameter_list|)
block|{
name|GimpBucketFillOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_BUCKET_FILL_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
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
name|GIMP_FG_BUCKET_FILL
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"fill-mode"
argument_list|,
name|GIMP_BG_BUCKET_FILL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BG_BUCKET_FILL
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"fill-mode"
argument_list|,
name|GIMP_FG_BUCKET_FILL
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
DECL|function|gimp_bucket_fill_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_bucket_fill_tool_cursor_update
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
name|GimpBucketFillOptions
modifier|*
name|options
decl_stmt|;
name|GimpCursorModifier
name|cmodifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
name|options
operator|=
name|GIMP_BUCKET_FILL_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_coords_in_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
argument_list|)
condition|)
block|{
name|GimpChannel
modifier|*
name|selection
init|=
name|gimp_image_get_mask
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
decl_stmt|;
comment|/*  One more test--is there a selected region?        *  if so, is cursor inside?        */
if|if
condition|(
name|gimp_channel_is_empty
argument_list|(
name|selection
argument_list|)
operator|||
name|gimp_channel_value
argument_list|(
name|selection
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
block|{
switch|switch
condition|(
name|options
operator|->
name|fill_mode
condition|)
block|{
case|case
name|GIMP_FG_BUCKET_FILL
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_FOREGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_BG_BUCKET_FILL
case|:
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_BACKGROUND
expr_stmt|;
break|break;
case|case
name|GIMP_PATTERN_BUCKET_FILL
case|:
name|cmodifier
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
name|cmodifier
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

end_unit

