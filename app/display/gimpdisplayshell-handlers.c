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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
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
file|"gimpdisplayshell-callbacks.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-handlers.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-scale.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-title.h"
end_include

begin_include
include|#
directive|include
file|"gimpstatusbar.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_clean_dirty_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_undo_event_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_name_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_selection_control_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpSelectionControl
name|control
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_size_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_resolution_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_unit_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_qmask_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_update_guide_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_invalidate_preview_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_check_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_title_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_nav_size_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_monitor_res_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_padding_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_shell_ants_speed_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_shell_idle_update_icon
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_connect (GimpDisplayShell * shell)
name|gimp_display_shell_connect
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|shell
operator|->
name|monitor_xres
operator|=
name|display_config
operator|->
name|monitor_xres
expr_stmt|;
name|shell
operator|->
name|monitor_yres
operator|=
name|display_config
operator|->
name|monitor_yres
expr_stmt|;
name|shell
operator|->
name|padding_mode
operator|=
name|display_config
operator|->
name|canvas_padding_mode
expr_stmt|;
name|shell
operator|->
name|padding_color
operator|=
name|display_config
operator|->
name|canvas_padding_color
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"clean"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_clean_dirty_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_clean_dirty_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"undo_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_undo_event_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"name_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_name_changed_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"selection_control"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_selection_control_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"size_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_size_changed_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"resolution_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_resolution_changed_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"unit_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_unit_changed_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"qmask_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_qmask_changed_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"update_guide"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_update_guide_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
argument_list|,
literal|"invalidate_preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_invalidate_preview_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::transparency-size"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_check_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::transparency-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_check_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::image-title-format"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_title_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::image-status-format"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_title_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::navigation-preview-size"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_nav_size_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::monitor-xresolution"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_monitor_res_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::monitor-yresolution"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_monitor_res_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::canvas-padding-mode"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_padding_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::canvas-padding-color"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_padding_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::marching-ants-speed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_shell_ants_speed_notify_handler
argument_list|)
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_invalidate_preview_handler
argument_list|(
name|gimage
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_display_shell_qmask_changed_handler
argument_list|(
name|gimage
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_disconnect (GimpDisplayShell * shell)
name|gimp_display_shell_disconnect
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|shell
operator|->
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|shell
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|icon_idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|shell
operator|->
name|icon_idle_id
argument_list|)
expr_stmt|;
name|shell
operator|->
name|icon_idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_ants_speed_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_padding_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_monitor_res_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_nav_size_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_title_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|,
name|gimp_display_shell_check_notify_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_invalidate_preview_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_update_guide_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_qmask_changed_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_unit_changed_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_resolution_changed_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_size_changed_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_selection_control_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_name_changed_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_undo_event_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimage
argument_list|,
name|gimp_display_shell_clean_dirty_handler
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_clean_dirty_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_clean_dirty_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_update_title
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_undo_event_handler (GimpImage * gimage,GimpUndoEvent event,GimpUndo * undo,GimpDisplayShell * shell)
name|gimp_display_shell_undo_event_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUndoEvent
name|event
parameter_list|,
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_update_title
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_name_changed_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_name_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_update_title
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_selection_control_handler (GimpImage * gimage,GimpSelectionControl control,GimpDisplayShell * shell)
name|gimp_display_shell_selection_control_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpSelectionControl
name|control
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_selection_visibility
argument_list|(
name|shell
argument_list|,
name|control
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_size_changed_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_size_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_statusbar_resize_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_scale_resize
argument_list|(
name|shell
argument_list|,
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|resize_windows_on_resize
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_resolution_changed_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_resolution_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|dot_for_dot
condition|)
name|gimp_display_shell_scale_setup
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_statusbar_resize_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_unit_changed_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_unit_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
operator|!
name|shell
operator|->
name|dot_for_dot
condition|)
name|gimp_display_shell_scale_setup
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_statusbar_resize_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_qmask_changed_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_qmask_changed_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GtkImage
modifier|*
name|image
decl_stmt|;
name|image
operator|=
name|GTK_IMAGE
argument_list|(
name|GTK_BIN
argument_list|(
name|shell
operator|->
name|qmask
argument_list|)
operator|->
name|child
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|shell
operator|->
name|qmask
argument_list|,
name|gimp_display_shell_qmask_toggled
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|shell
operator|->
name|qmask
argument_list|)
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
condition|)
name|gtk_image_set_from_stock
argument_list|(
name|image
argument_list|,
name|GIMP_STOCK_QMASK_ON
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
else|else
name|gtk_image_set_from_stock
argument_list|(
name|image
argument_list|,
name|GIMP_STOCK_QMASK_OFF
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|shell
operator|->
name|qmask
argument_list|,
name|gimp_display_shell_qmask_toggled
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_update_guide_handler (GimpImage * gimage,GimpGuide * guide,GimpDisplayShell * shell)
name|gimp_display_shell_update_guide_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpGuide
modifier|*
name|guide
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_expose_guide
argument_list|(
name|shell
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_invalidate_preview_handler (GimpImage * gimage,GimpDisplayShell * shell)
name|gimp_display_shell_invalidate_preview_handler
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|shell
operator|->
name|icon_idle_id
condition|)
name|g_source_remove
argument_list|(
name|shell
operator|->
name|icon_idle_id
argument_list|)
expr_stmt|;
name|shell
operator|->
name|icon_idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
name|gimp_display_shell_idle_update_icon
argument_list|,
name|shell
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_check_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_check_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
switch|switch
condition|(
name|shell
operator|->
name|padding_mode
condition|)
block|{
case|case
name|GIMP_DISPLAY_PADDING_MODE_LIGHT_CHECK
case|:
case|case
name|GIMP_DISPLAY_PADDING_MODE_DARK_CHECK
case|:
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|padding_mode
argument_list|,
operator|&
name|shell
operator|->
name|padding_color
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_title_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_title_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_update_title
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_nav_size_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_nav_size_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gboolean
name|sensitive
decl_stmt|;
if|if
condition|(
name|shell
operator|->
name|nav_popup
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|shell
operator|->
name|nav_popup
argument_list|)
expr_stmt|;
name|shell
operator|->
name|nav_popup
operator|=
name|NULL
expr_stmt|;
block|}
name|sensitive
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|nav_preview_size
operator|!=
name|GIMP_PREVIEW_SIZE_NONE
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|shell
operator|->
name|nav_ebox
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_monitor_res_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_monitor_res_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|shell
operator|->
name|monitor_xres
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|monitor_xres
expr_stmt|;
name|shell
operator|->
name|monitor_yres
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|config
argument_list|)
operator|->
name|monitor_yres
expr_stmt|;
if|if
condition|(
operator|!
name|shell
operator|->
name|dot_for_dot
condition|)
block|{
name|gimp_display_shell_scale_setup
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_statusbar_resize_cursor
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_full
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_padding_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_padding_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
comment|/*  if the user did not set the padding mode for this display explicitely  */
if|if
condition|(
operator|!
name|shell
operator|->
name|padding_mode_set
condition|)
block|{
name|GimpDisplayConfig
modifier|*
name|display_config
decl_stmt|;
name|display_config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|display_config
operator|->
name|canvas_padding_mode
argument_list|,
operator|&
name|display_config
operator|->
name|canvas_padding_color
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_shell_ants_speed_notify_handler (GObject * config,GParamSpec * param_spec,GimpDisplayShell * shell)
name|gimp_display_shell_ants_speed_notify_handler
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|gimp_display_shell_selection_pause
argument_list|(
name|shell
operator|->
name|select
argument_list|)
expr_stmt|;
name|gimp_display_shell_selection_resume
argument_list|(
name|shell
operator|->
name|select
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_shell_idle_update_icon (gpointer data)
name|gimp_display_shell_idle_update_icon
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|shell
operator|->
name|icon_idle_id
operator|=
literal|0
expr_stmt|;
name|gimp_display_shell_update_icon
argument_list|(
name|shell
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

