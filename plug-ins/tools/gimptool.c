begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpproxy/gimpproxytypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimptool/gimptooltypes.h"
end_include

begin_include
include|#
directive|include
file|"libgimptool/gimptool.h"
end_include

begin_function
name|void
DECL|function|gimp_tool_push_status (GimpTool * tool,const gchar * message)
name|gimp_tool_push_status
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GimpStatusbar *statusbar;    g_return_if_fail (GIMP_IS_TOOL (tool));   g_return_if_fail (GIMP_IS_DISPLAY (tool->gdisp));   g_return_if_fail (message != NULL);    statusbar =     GIMP_STATUSBAR (GIMP_DISPLAY_SHELL (tool->gdisp->shell)->statusbar);    gimp_statusbar_push (statusbar,                        G_OBJECT_TYPE_NAME (tool),                        message);
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_push_status_coords (GimpTool * tool,const gchar * title,gdouble x,const gchar * separator,gdouble y)
name|gimp_tool_push_status_coords
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gdouble
name|x
parameter_list|,
specifier|const
name|gchar
modifier|*
name|separator
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GimpStatusbar *statusbar;    g_return_if_fail (GIMP_IS_TOOL (tool));   g_return_if_fail (GIMP_IS_DISPLAY (tool->gdisp));   g_return_if_fail (title != NULL);   g_return_if_fail (separator != NULL);    statusbar =     GIMP_STATUSBAR (GIMP_DISPLAY_SHELL (tool->gdisp->shell)->statusbar);    gimp_statusbar_push_coords (statusbar,                               G_OBJECT_TYPE_NAME (tool),                               title, x, separator, y);
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_pop_status (GimpTool * tool)
name|gimp_tool_pop_status
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
if|#
directive|if
literal|0
block|GimpStatusbar *statusbar;    g_return_if_fail (GIMP_IS_TOOL (tool));   g_return_if_fail (GIMP_IS_DISPLAY (tool->gdisp));    statusbar =     GIMP_STATUSBAR (GIMP_DISPLAY_SHELL (tool->gdisp->shell)->statusbar);    gimp_statusbar_pop (statusbar,                       G_OBJECT_TYPE_NAME (tool));
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_set_cursor (GimpTool * tool,GimpDisplay * gdisp,GdkCursorType cursor,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_tool_set_cursor
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GdkCursorType
name|cursor
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
if|#
directive|if
literal|0
block|g_return_if_fail (GIMP_IS_TOOL (tool));   g_return_if_fail (GIMP_IS_DISPLAY (gdisp));    gimp_display_shell_set_cursor (GIMP_DISPLAY_SHELL (gdisp->shell),                                  cursor,                                  tool_cursor,                                  modifier);
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_real_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_tool_real_button_press
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
if|#
directive|if
literal|0
block|tool->gdisp    = gdisp;   tool->drawable = gimp_image_active_drawable (gdisp->gimage);    tool->state = ACTIVE;
endif|#
directive|endif
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_real_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_tool_real_button_release
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
if|#
directive|if
literal|0
block|tool->state = INACTIVE;
endif|#
directive|endif
block|}
end_function

end_unit

