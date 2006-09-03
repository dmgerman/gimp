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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpsourcecore.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpsourceoptions.h"
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
file|"gimpsourcetool.h"
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
name|gboolean
name|gimp_source_tool_has_display
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpDisplay
modifier|*
name|gimp_source_tool_has_image
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
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
name|gimp_source_tool_button_press
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_tool_motion
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_tool_cursor_update
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_source_tool_modifier_key
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
name|gimp_source_tool_oper_update
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
name|gboolean
name|proximity
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
name|gimp_source_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSourceTool,gimp_source_tool,GIMP_TYPE_BRUSH_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSourceTool
argument_list|,
argument|gimp_source_tool
argument_list|,
argument|GIMP_TYPE_BRUSH_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_source_tool_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_source_tool_class_init
parameter_list|(
name|GimpSourceToolClass
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
name|has_display
operator|=
name|gimp_source_tool_has_display
expr_stmt|;
name|tool_class
operator|->
name|has_image
operator|=
name|gimp_source_tool_has_image
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_source_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_source_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_source_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_source_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_source_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_source_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_source_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_tool_init (GimpSourceTool * source)
name|gimp_source_tool_init
parameter_list|(
name|GimpSourceTool
modifier|*
name|source
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_source_tool_has_display (GimpTool * tool,GimpDisplay * display)
name|gimp_source_tool_has_display
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
return|return
operator|(
name|display
operator|==
name|source_tool
operator|->
name|src_display
operator|||
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|has_display
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpDisplay
modifier|*
DECL|function|gimp_source_tool_has_image (GimpTool * tool,GimpImage * image)
name|gimp_source_tool_has_image
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|display
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|has_image
argument_list|(
name|tool
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|display
operator|&&
name|source_tool
operator|->
name|src_display
condition|)
block|{
if|if
condition|(
name|image
operator|&&
name|source_tool
operator|->
name|src_display
operator|->
name|image
operator|==
name|image
condition|)
name|display
operator|=
name|source_tool
operator|->
name|src_display
expr_stmt|;
comment|/*  NULL image means any display  */
if|if
condition|(
operator|!
name|image
condition|)
name|display
operator|=
name|source_tool
operator|->
name|src_display
expr_stmt|;
block|}
return|return
name|display
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_source_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_TOOL_ACTION_PAUSE
case|:
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|source_tool
operator|->
name|src_display
operator|=
name|NULL
expr_stmt|;
name|g_object_set
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|core
argument_list|,
literal|"src-drawable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_source_tool_button_press
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
name|display
parameter_list|)
block|{
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
name|GimpSourceCore
modifier|*
name|source
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_SOURCE_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
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
name|paint_tool
operator|->
name|core
operator|->
name|use_saved_proj
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
operator|(
name|state
operator|&
operator|(
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
operator|)
operator|)
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
name|source
operator|->
name|set_source
operator|=
name|TRUE
expr_stmt|;
name|source_tool
operator|->
name|src_display
operator|=
name|display
expr_stmt|;
block|}
else|else
block|{
name|source
operator|->
name|set_source
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|use_source
operator|&&
name|options
operator|->
name|sample_merged
operator|&&
name|display
operator|==
name|source_tool
operator|->
name|src_display
condition|)
block|{
name|paint_tool
operator|->
name|core
operator|->
name|use_saved_proj
operator|=
name|TRUE
expr_stmt|;
block|}
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
name|display
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|src_x
operator|=
name|source
operator|->
name|src_x
expr_stmt|;
name|source_tool
operator|->
name|src_y
operator|=
name|source
operator|->
name|src_y
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
DECL|function|gimp_source_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_source_tool_motion
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
name|display
parameter_list|)
block|{
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
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
name|GimpSourceCore
modifier|*
name|source
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|paint_tool
operator|->
name|core
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
if|if
condition|(
operator|(
name|state
operator|&
operator|(
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
operator|)
operator|)
operator|==
name|GDK_CONTROL_MASK
condition|)
name|source
operator|->
name|set_source
operator|=
name|TRUE
expr_stmt|;
else|else
name|source
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
name|display
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|src_x
operator|=
name|source
operator|->
name|src_x
expr_stmt|;
name|source_tool
operator|->
name|src_y
operator|=
name|source
operator|->
name|src_y
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
DECL|function|gimp_source_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_source_tool_modifier_key
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
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
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
name|GimpSourceOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_SOURCE_OPTIONS
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
operator|!
operator|(
name|state
operator|&
name|GDK_BUTTON1_MASK
operator|)
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|use_source
operator|&&
name|key
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
if|if
condition|(
name|press
condition|)
name|paint_tool
operator|->
name|status
operator|=
name|source_tool
operator|->
name|status_set_source
expr_stmt|;
else|else
name|paint_tool
operator|->
name|status
operator|=
name|source_tool
operator|->
name|status_paint
expr_stmt|;
block|}
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
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
DECL|function|gimp_source_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_source_tool_cursor_update
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
name|display
parameter_list|)
block|{
name|GimpSourceOptions
modifier|*
name|options
decl_stmt|;
name|GimpCursorType
name|cursor
init|=
name|GIMP_CURSOR_MOUSE
decl_stmt|;
name|GimpCursorModifier
name|modifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
name|options
operator|=
name|GIMP_SOURCE_OPTIONS
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
name|options
operator|->
name|use_source
condition|)
block|{
if|if
condition|(
operator|(
name|state
operator|&
operator|(
name|GDK_CONTROL_MASK
operator||
name|GDK_SHIFT_MASK
operator|)
operator|)
operator|==
name|GDK_CONTROL_MASK
condition|)
block|{
name|cursor
operator|=
name|GIMP_CURSOR_CROSSHAIR_SMALL
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|GIMP_SOURCE_CORE
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
block|{
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_BAD
expr_stmt|;
block|}
block|}
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|cursor
argument_list|)
expr_stmt|;
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
DECL|function|gimp_source_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_source_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_SOURCE_OPTIONS
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
name|proximity
condition|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|options
operator|->
name|use_source
condition|)
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|source_tool
operator|->
name|status_set_source_ctrl
expr_stmt|;
else|else
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|oper_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|use_source
condition|)
block|{
name|GimpSourceCore
modifier|*
name|source
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|core
argument_list|)
decl_stmt|;
if|if
condition|(
name|source
operator|->
name|src_drawable
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
name|gimp_tool_replace_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|source_tool
operator|->
name|status_set_source
argument_list|)
expr_stmt|;
else|else
block|{
name|gchar
modifier|*
name|status
decl_stmt|;
name|status
operator|=
name|g_strconcat
argument_list|(
name|gimp_get_mod_name_control
argument_list|()
argument_list|,
name|gimp_get_mod_separator
argument_list|()
argument_list|,
name|source_tool
operator|->
name|status_set_source
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_tool_replace_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|status
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|source_tool
operator|->
name|src_x
operator|=
name|source
operator|->
name|src_x
expr_stmt|;
name|source_tool
operator|->
name|src_y
operator|=
name|source
operator|->
name|src_y
expr_stmt|;
if|if
condition|(
operator|!
name|source
operator|->
name|first_stroke
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|align_mode
condition|)
block|{
case|case
name|GIMP_SOURCE_ALIGN_YES
case|:
name|source_tool
operator|->
name|src_x
operator|=
name|coords
operator|->
name|x
operator|+
name|source
operator|->
name|offset_x
expr_stmt|;
name|source_tool
operator|->
name|src_y
operator|=
name|coords
operator|->
name|y
operator|+
name|source
operator|->
name|offset_y
expr_stmt|;
break|break;
case|case
name|GIMP_SOURCE_ALIGN_REGISTERED
case|:
name|source_tool
operator|->
name|src_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|source_tool
operator|->
name|src_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_source_tool_draw (GimpDrawTool * draw_tool)
name|gimp_source_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpSourceTool
modifier|*
name|source_tool
init|=
name|GIMP_SOURCE_TOOL
argument_list|(
name|draw_tool
argument_list|)
decl_stmt|;
name|GimpSourceCore
modifier|*
name|source
init|=
name|GIMP_SOURCE_CORE
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|core
argument_list|)
decl_stmt|;
name|GimpSourceOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_SOURCE_OPTIONS
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
name|options
operator|->
name|use_source
operator|&&
name|source
operator|->
name|src_drawable
operator|&&
name|source_tool
operator|->
name|src_display
condition|)
block|{
name|GimpDisplay
modifier|*
name|tmp_display
decl_stmt|;
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
name|source
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
name|tmp_display
operator|=
name|draw_tool
operator|->
name|display
expr_stmt|;
name|draw_tool
operator|->
name|display
operator|=
name|source_tool
operator|->
name|src_display
expr_stmt|;
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_CROSS
argument_list|,
name|source_tool
operator|->
name|src_x
operator|+
name|off_x
argument_list|,
name|source_tool
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
name|draw_tool
operator|->
name|display
operator|=
name|tmp_display
expr_stmt|;
block|}
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
end_function

end_unit

