begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"libgimptool/gimptooltypes.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_tool_control_class_init
parameter_list|(
name|GimpToolControlClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_control_init
parameter_list|(
name|GimpToolControl
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_tool_control_get_type (void)
name|gimp_tool_control_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_control_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_control_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_control_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpToolControlClass
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
name|gimp_tool_control_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpToolControl
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_tool_control_init
block|,       }
decl_stmt|;
name|tool_control_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpToolControl"
argument_list|,
operator|&
name|tool_control_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_control_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_control_class_init (GimpToolControlClass * klass)
name|gimp_tool_control_class_init
parameter_list|(
name|GimpToolControlClass
modifier|*
name|klass
parameter_list|)
block|{
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_control_init (GimpToolControl * control)
name|gimp_tool_control_init
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
if|#
directive|if
literal|0
block|control->state                  = INACTIVE;   control->paused_count           = 0;    control->toggled                = FALSE;
endif|#
directive|endif
block|}
end_function

begin_function
name|GimpToolControl
modifier|*
DECL|function|gimp_tool_control_new (gboolean scroll_lock,gboolean auto_snap_to,gboolean preserve,gboolean handle_empty_image,gboolean perfectmouse,GdkCursorType cursor,GimpToolCursorType tool_cursor,GimpCursorModifier cursor_modifier,GdkCursorType toggle_cursor,GimpToolCursorType toggle_tool_cursor,GimpCursorModifier toggle_cursor_modifier)
name|gimp_tool_control_new
parameter_list|(
name|gboolean
name|scroll_lock
parameter_list|,
name|gboolean
name|auto_snap_to
parameter_list|,
name|gboolean
name|preserve
parameter_list|,
name|gboolean
name|handle_empty_image
parameter_list|,
name|gboolean
name|perfectmouse
parameter_list|,
comment|/* are all these necessary? */
name|GdkCursorType
name|cursor
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|cursor_modifier
parameter_list|,
name|GdkCursorType
name|toggle_cursor
parameter_list|,
name|GimpToolCursorType
name|toggle_tool_cursor
parameter_list|,
name|GimpCursorModifier
name|toggle_cursor_modifier
parameter_list|)
block|{
name|GimpToolControl
modifier|*
name|control
decl_stmt|;
name|control
operator|=
name|GIMP_TOOL_CONTROL
argument_list|(
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_CONTROL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|control->scroll_lock            = scroll_lock;   control->auto_snap_to           = auto_snap_to;   control->preserve               = preserve;   control->handle_empty_image     = handle_empty_image;   control->perfectmouse           = perfectmouse;      control->cursor                 = cursor;   control->tool_cursor            = tool_cursor;   control->cursor_modifier        = cursor_modifier;   control->toggle_cursor          = toggle_cursor;   control->toggle_tool_cursor     = toggle_tool_cursor;   control->toggle_cursor_modifier = toggle_cursor_modifier;
endif|#
directive|endif
return|return
name|control
return|;
block|}
end_function

begin_function
DECL|function|gimp_tool_control_pause (GimpToolControl * control)
name|void
name|gimp_tool_control_pause
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
comment|/* control->state = PAUSED ? */
if|#
directive|if
literal|0
block|control->paused_count++;
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|gimp_tool_control_resume (GimpToolControl * control)
name|void
name|gimp_tool_control_resume
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|control->paused_count--;
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|gimp_tool_control_is_paused (GimpToolControl * control)
name|gboolean
name|gimp_tool_control_is_paused
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_return_val_if_fail(GIMP_IS_TOOL_CONTROL(control), FALSE);    return control->paused_count> 0;
else|#
directive|else
return|return
literal|0
return|;
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|gimp_tool_control_halt (GimpToolControl * control)
name|void
name|gimp_tool_control_halt
parameter_list|(
name|GimpToolControl
modifier|*
name|control
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_CONTROL
argument_list|(
name|control
argument_list|)
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|control->state = INACTIVE;    control->paused_count = 0;
endif|#
directive|endif
block|}
end_function

end_unit

