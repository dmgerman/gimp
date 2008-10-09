begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"display-types.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcursor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcursorview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-cursor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_real_set_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|,
name|gboolean
name|always_install
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_set_cursor (GimpDisplayShell * shell,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier)
name|gimp_display_shell_set_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|using_override_cursor
condition|)
block|{
name|gimp_display_shell_real_set_cursor
argument_list|(
name|shell
argument_list|,
name|cursor_type
argument_list|,
name|tool_cursor
argument_list|,
name|modifier
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_unset_cursor (GimpDisplayShell * shell)
name|gimp_display_shell_unset_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|using_override_cursor
condition|)
block|{
name|gimp_display_shell_real_set_cursor
argument_list|(
name|shell
argument_list|,
operator|(
name|GimpCursorType
operator|)
operator|-
literal|1
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_override_cursor (GimpDisplayShell * shell,GimpCursorType cursor_type)
name|gimp_display_shell_set_override_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|using_override_cursor
operator|||
operator|(
name|shell
operator|->
name|using_override_cursor
operator|&&
name|shell
operator|->
name|override_cursor
operator|!=
name|cursor_type
operator|)
condition|)
block|{
name|shell
operator|->
name|override_cursor
operator|=
name|cursor_type
expr_stmt|;
name|shell
operator|->
name|using_override_cursor
operator|=
name|TRUE
expr_stmt|;
name|gimp_cursor_set
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|shell
operator|->
name|cursor_format
argument_list|,
name|cursor_type
argument_list|,
name|GIMP_TOOL_CURSOR_NONE
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_unset_override_cursor (GimpDisplayShell * shell)
name|gimp_display_shell_unset_override_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|using_override_cursor
condition|)
block|{
name|shell
operator|->
name|using_override_cursor
operator|=
name|FALSE
expr_stmt|;
name|gimp_display_shell_real_set_cursor
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|current_cursor
argument_list|,
name|shell
operator|->
name|tool_cursor
argument_list|,
name|shell
operator|->
name|cursor_modifier
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_update_cursor (GimpDisplayShell * shell,GimpCursorPrecision precision,gint display_x,gint display_y,gdouble image_x,gdouble image_y)
name|gimp_display_shell_update_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCursorPrecision
name|precision
parameter_list|,
name|gint
name|display_x
parameter_list|,
name|gint
name|display_y
parameter_list|,
name|gdouble
name|image_x
parameter_list|,
name|gdouble
name|image_y
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|factory
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|session_info
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|gboolean
name|new_cursor
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|shell
operator|->
name|display
operator|->
name|image
expr_stmt|;
name|new_cursor
operator|=
operator|(
name|shell
operator|->
name|draw_cursor
operator|&&
name|shell
operator|->
name|proximity
operator|&&
name|display_x
operator|>=
literal|0
operator|&&
name|display_y
operator|>=
literal|0
operator|)
expr_stmt|;
comment|/* Erase old cursor, if necessary */
if|if
condition|(
name|shell
operator|->
name|have_cursor
operator|&&
operator|(
operator|!
name|new_cursor
operator|||
name|display_x
operator|!=
name|shell
operator|->
name|cursor_x
operator|||
name|display_y
operator|!=
name|shell
operator|->
name|cursor_y
operator|)
condition|)
block|{
name|gimp_display_shell_expose_area
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|cursor_x
operator|-
literal|7
argument_list|,
name|shell
operator|->
name|cursor_y
operator|-
literal|7
argument_list|,
literal|15
argument_list|,
literal|15
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|new_cursor
condition|)
name|shell
operator|->
name|have_cursor
operator|=
name|FALSE
expr_stmt|;
block|}
name|shell
operator|->
name|have_cursor
operator|=
name|new_cursor
expr_stmt|;
name|shell
operator|->
name|cursor_x
operator|=
name|display_x
expr_stmt|;
name|shell
operator|->
name|cursor_y
operator|=
name|display_y
expr_stmt|;
comment|/*  use the passed image_coords for the statusbar because they are    *  possibly snapped...    */
name|gimp_statusbar_update_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|precision
argument_list|,
name|image_x
argument_list|,
name|image_y
argument_list|)
expr_stmt|;
name|factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
argument_list|)
expr_stmt|;
name|session_info
operator|=
name|gimp_dialog_factory_find_session_info
argument_list|(
name|factory
argument_list|,
literal|"gimp-cursor-view"
argument_list|)
expr_stmt|;
if|if
condition|(
name|session_info
operator|&&
name|session_info
operator|->
name|widget
condition|)
block|{
name|GtkWidget
modifier|*
name|cursor_view
decl_stmt|;
name|cursor_view
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|session_info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cursor_view
condition|)
block|{
name|gint
name|t_x
init|=
operator|-
literal|1
decl_stmt|;
name|gint
name|t_y
init|=
operator|-
literal|1
decl_stmt|;
comment|/*  ...but use the unsnapped display_coords for the info window  */
if|if
condition|(
name|display_x
operator|>=
literal|0
operator|&&
name|display_y
operator|>=
literal|0
condition|)
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
name|display_x
argument_list|,
name|display_y
argument_list|,
operator|&
name|t_x
argument_list|,
operator|&
name|t_y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_cursor_view_update_cursor
argument_list|(
name|GIMP_CURSOR_VIEW
argument_list|(
name|cursor_view
argument_list|)
argument_list|,
name|shell
operator|->
name|display
operator|->
name|image
argument_list|,
name|shell
operator|->
name|unit
argument_list|,
name|t_x
argument_list|,
name|t_y
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_clear_cursor (GimpDisplayShell * shell)
name|gimp_display_shell_clear_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpDialogFactory
modifier|*
name|factory
decl_stmt|;
name|GimpSessionInfo
modifier|*
name|session_info
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_statusbar_clear_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
argument_list|)
expr_stmt|;
name|session_info
operator|=
name|gimp_dialog_factory_find_session_info
argument_list|(
name|factory
argument_list|,
literal|"gimp-cursor-view"
argument_list|)
expr_stmt|;
if|if
condition|(
name|session_info
operator|&&
name|session_info
operator|->
name|widget
condition|)
block|{
name|GtkWidget
modifier|*
name|cursor_view
decl_stmt|;
name|cursor_view
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|session_info
operator|->
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cursor_view
condition|)
name|gimp_cursor_view_clear_cursor
argument_list|(
name|GIMP_CURSOR_VIEW
argument_list|(
name|cursor_view
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_real_set_cursor (GimpDisplayShell * shell,GimpCursorType cursor_type,GimpToolCursorType tool_cursor,GimpCursorModifier modifier,gboolean always_install)
name|gimp_display_shell_real_set_cursor
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCursorType
name|cursor_type
parameter_list|,
name|GimpToolCursorType
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
name|modifier
parameter_list|,
name|gboolean
name|always_install
parameter_list|)
block|{
name|GimpCursorFormat
name|cursor_format
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cursor_type
operator|==
operator|(
name|GimpCursorType
operator|)
operator|-
literal|1
condition|)
block|{
name|shell
operator|->
name|current_cursor
operator|=
name|cursor_type
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_DRAWABLE
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
condition|)
name|gdk_window_set_cursor
argument_list|(
name|shell
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|cursor_type
operator|!=
name|GIMP_CURSOR_NONE
operator|&&
name|cursor_type
operator|!=
name|GIMP_CURSOR_BAD
condition|)
block|{
switch|switch
condition|(
name|shell
operator|->
name|display
operator|->
name|config
operator|->
name|cursor_mode
condition|)
block|{
case|case
name|GIMP_CURSOR_MODE_TOOL_ICON
case|:
break|break;
case|case
name|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
case|:
if|if
condition|(
name|cursor_type
operator|<
name|GIMP_CURSOR_CORNER_TOP_LEFT
operator|||
name|cursor_type
operator|>
name|GIMP_CURSOR_SIDE_BOTTOM
condition|)
block|{
comment|/* the corner and side cursors count as crosshair, so leave                * them and override everything else                */
name|cursor_type
operator|=
name|GIMP_CURSOR_CROSSHAIR_SMALL
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CURSOR_MODE_CROSSHAIR
case|:
name|cursor_type
operator|=
name|GIMP_CURSOR_CROSSHAIR
expr_stmt|;
name|tool_cursor
operator|=
name|GIMP_TOOL_CURSOR_NONE
expr_stmt|;
if|if
condition|(
name|modifier
operator|!=
name|GIMP_CURSOR_MODIFIER_BAD
condition|)
block|{
comment|/* the bad modifier is always shown */
name|modifier
operator|=
name|GIMP_CURSOR_MODIFIER_NONE
expr_stmt|;
block|}
break|break;
block|}
block|}
name|cursor_format
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|shell
operator|->
name|display
operator|->
name|config
argument_list|)
operator|->
name|cursor_format
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|cursor_format
operator|!=
name|cursor_format
operator|||
name|shell
operator|->
name|current_cursor
operator|!=
name|cursor_type
operator|||
name|shell
operator|->
name|tool_cursor
operator|!=
name|tool_cursor
operator|||
name|shell
operator|->
name|cursor_modifier
operator|!=
name|modifier
operator|||
name|always_install
condition|)
block|{
name|shell
operator|->
name|cursor_format
operator|=
name|cursor_format
expr_stmt|;
name|shell
operator|->
name|current_cursor
operator|=
name|cursor_type
expr_stmt|;
name|shell
operator|->
name|tool_cursor
operator|=
name|tool_cursor
expr_stmt|;
name|shell
operator|->
name|cursor_modifier
operator|=
name|modifier
expr_stmt|;
name|gimp_cursor_set
argument_list|(
name|shell
operator|->
name|canvas
argument_list|,
name|cursor_format
argument_list|,
name|cursor_type
argument_list|,
name|tool_cursor
argument_list|,
name|modifier
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

