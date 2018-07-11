begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"config/gimpdisplayoptions.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockcolumns.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimprender.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvas.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasitem.h"
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
file|"gimpdisplayshell-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagewindow.h"
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
name|GimpDisplayOptions
modifier|*
name|appearance_get_options
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_display_shell_appearance_update (GimpDisplayShell * shell)
name|gimp_display_shell_appearance_update
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GimpImageWindow
modifier|*
name|window
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|window
operator|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
condition|)
block|{
name|gboolean
name|fullscreen
init|=
name|gimp_image_window_get_fullscreen
argument_list|(
name|window
argument_list|)
decl_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-fullscreen"
argument_list|,
name|fullscreen
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_set_show_menubar
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_menubar
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_statusbar
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_statusbar
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_rulers
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_rulers
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_scrollbars
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_scrollbars
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_selection
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_selection
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_layer
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_layer_boundary
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_guides
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_guides
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_grid
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_grid
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_show_sample_points
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|show_sample_points
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_padding
argument_list|(
name|shell
argument_list|,
name|options
operator|->
name|padding_mode
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_menubar (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GimpImageWindow
modifier|*
name|window
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|window
operator|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-menubar"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|window
operator|&&
name|gimp_image_window_get_active_shell
argument_list|(
name|window
argument_list|)
operator|==
name|shell
condition|)
block|{
name|gimp_image_window_keep_canvas_pos
argument_list|(
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_window_set_show_menubar
argument_list|(
name|window
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-menubar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_menubar (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_menubar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_menubar
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_statusbar (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-statusbar"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_window_keep_canvas_pos
argument_list|(
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_statusbar_set_visible
argument_list|(
name|GIMP_STATUSBAR
argument_list|(
name|shell
operator|->
name|statusbar
argument_list|)
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-statusbar"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_statusbar (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_statusbar
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_statusbar
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_rulers (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-rulers"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_window_keep_canvas_pos
argument_list|(
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|origin
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|hrule
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|vrule
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-rulers"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_rulers (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_rulers
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_rulers
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_scrollbars (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-scrollbars"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_window_keep_canvas_pos
argument_list|(
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|nav_ebox
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|hsb
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|vsb
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|quick_mask_button
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gtk_widget_set_visible
argument_list|(
name|shell
operator|->
name|zoom_button
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-scrollbars"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_scrollbars (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_scrollbars
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_scrollbars
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_selection (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-selection"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_display_shell_selection_set_show
argument_list|(
name|shell
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-selection"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_selection (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_selection
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_selection
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_layer (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-layer-boundary"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|layer_boundary
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-layer-boundary"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_layer (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_layer
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_layer_boundary
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_guides (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-guides"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|guides
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-guides"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_guides (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_guides
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_grid (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-grid"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|grid
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-grid"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_grid (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_grid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_show_sample_points (GimpDisplayShell * shell,gboolean show)
name|gimp_display_shell_set_show_sample_points
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"show-sample-points"
argument_list|,
name|show
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_item_set_visible
argument_list|(
name|shell
operator|->
name|sample_points
argument_list|,
name|show
argument_list|)
expr_stmt|;
name|gimp_display_shell_set_action_active
argument_list|(
name|shell
argument_list|,
literal|"view-show-sample-points"
argument_list|,
name|show
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_show_sample_points (GimpDisplayShell * shell)
name|gimp_display_shell_get_show_sample_points
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|show_sample_points
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_grid (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"snap-to-grid"
argument_list|,
name|snap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_grid (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_grid
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|snap_to_grid
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_guides (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"snap-to-guides"
argument_list|,
name|snap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_guides (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_guides
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|snap_to_guides
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_canvas (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_canvas
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"snap-to-canvas"
argument_list|,
name|snap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_canvas (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_canvas
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|snap_to_canvas
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_snap_to_vectors (GimpDisplayShell * shell,gboolean snap)
name|gimp_display_shell_set_snap_to_vectors
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|gboolean
name|snap
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"snap-to-path"
argument_list|,
name|snap
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_display_shell_get_snap_to_vectors (GimpDisplayShell * shell)
name|gimp_display_shell_get_snap_to_vectors
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
operator|->
name|snap_to_path
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_set_padding (GimpDisplayShell * shell,GimpCanvasPaddingMode padding_mode,const GimpRGB * padding_color)
name|gimp_display_shell_set_padding
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasPaddingMode
name|padding_mode
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|padding_color
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|GimpRGB
name|color
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
name|padding_color
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|color
operator|=
operator|*
name|padding_color
expr_stmt|;
switch|switch
condition|(
name|padding_mode
condition|)
block|{
case|case
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
case|:
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
case|:
name|color
operator|=
operator|*
name|gimp_render_light_check_color
argument_list|()
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
case|:
name|color
operator|=
operator|*
name|gimp_render_dark_check_color
argument_list|()
expr_stmt|;
break|break;
case|case
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
case|:
case|case
name|GIMP_CANVAS_PADDING_MODE_RESET
case|:
break|break;
block|}
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"padding-mode"
argument_list|,
name|padding_mode
argument_list|,
literal|"padding-color"
argument_list|,
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_canvas_set_padding
argument_list|(
name|GIMP_CANVAS
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
argument_list|,
name|padding_mode
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
if|if
condition|(
name|padding_mode
operator|!=
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
condition|)
name|gimp_display_shell_set_action_color
argument_list|(
name|shell
argument_list|,
literal|"view-padding-color-menu"
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
else|else
name|gimp_display_shell_set_action_color
argument_list|(
name|shell
argument_list|,
literal|"view-padding-color-menu"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_shell_get_padding (GimpDisplayShell * shell,GimpCanvasPaddingMode * padding_mode,GimpRGB * padding_color)
name|gimp_display_shell_get_padding
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GimpCanvasPaddingMode
modifier|*
name|padding_mode
parameter_list|,
name|GimpRGB
modifier|*
name|padding_color
parameter_list|)
block|{
name|GimpDisplayOptions
modifier|*
name|options
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
name|appearance_get_options
argument_list|(
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|padding_mode
condition|)
operator|*
name|padding_mode
operator|=
name|options
operator|->
name|padding_mode
expr_stmt|;
if|if
condition|(
name|padding_color
condition|)
operator|*
name|padding_color
operator|=
name|options
operator|->
name|padding_color
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpDisplayOptions
modifier|*
DECL|function|appearance_get_options (GimpDisplayShell * shell)
name|appearance_get_options
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
if|if
condition|(
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
condition|)
block|{
name|GimpImageWindow
modifier|*
name|window
init|=
name|gimp_display_shell_get_window
argument_list|(
name|shell
argument_list|)
decl_stmt|;
if|if
condition|(
name|window
operator|&&
name|gimp_image_window_get_fullscreen
argument_list|(
name|window
argument_list|)
condition|)
return|return
name|shell
operator|->
name|fullscreen_options
return|;
else|else
return|return
name|shell
operator|->
name|options
return|;
block|}
return|return
name|shell
operator|->
name|no_image_options
return|;
block|}
end_function

end_unit

