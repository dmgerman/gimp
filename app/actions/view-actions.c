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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"actions-types.h"
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
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
file|"display/gimpdisplayoptions.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-appearance.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-render.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell-selection.h"
end_include

begin_include
include|#
directive|include
file|"actions.h"
end_include

begin_include
include|#
directive|include
file|"view-actions.h"
end_include

begin_include
include|#
directive|include
file|"view-commands.h"
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
name|void
name|view_actions_set_zoom
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
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
name|view_actions_check_type_notify
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|view_actions
specifier|static
name|GimpActionEntry
name|view_actions
index|[]
init|=
block|{
block|{
literal|"view-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_View"
argument_list|)
block|}
block|,
block|{
literal|"view-zoom-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Zoom"
argument_list|)
block|}
block|,
block|{
literal|"view-padding-color-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Padding Color"
argument_list|)
block|}
block|,
block|{
literal|"view-new"
block|,
name|GTK_STOCK_NEW
block|,
name|N_
argument_list|(
literal|"_New View"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_new_view_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_VIEW_NEW
block|}
block|,
block|{
literal|"view-close"
block|,
name|GTK_STOCK_CLOSE
block|,
name|N_
argument_list|(
literal|"_Close"
argument_list|)
block|,
literal|"<control>W"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_close_view_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_FILE_CLOSE
block|}
block|,
block|{
literal|"view-zoom-fit-in"
block|,
name|GTK_STOCK_ZOOM_FIT
block|,
name|N_
argument_list|(
literal|"_Fit Image in Window"
argument_list|)
block|,
literal|"<control><shift>E"
block|,
name|N_
argument_list|(
literal|"Fit image in window"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|view_zoom_fit_in_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_VIEW_ZOOM_FIT_IN
block|}
block|,
block|{
literal|"view-zoom-fit-to"
block|,
name|GTK_STOCK_ZOOM_FIT
block|,
name|N_
argument_list|(
literal|"Fit Image to Window"
argument_list|)
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Fit image to window"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|view_zoom_fit_to_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_VIEW_ZOOM_FIT_TO
block|}
block|,
block|{
literal|"view-info-window"
block|,
name|GIMP_STOCK_INFO
block|,
name|N_
argument_list|(
literal|"_Info Window"
argument_list|)
block|,
literal|"<control><shift>I"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_info_window_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_INFO_DIALOG
block|}
block|,
block|{
literal|"view-navigation-window"
block|,
name|GIMP_STOCK_NAVIGATION
block|,
name|N_
argument_list|(
literal|"Na_vigation Window"
argument_list|)
block|,
literal|"<control><shift>N"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_navigation_window_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_NAVIGATION_DIALOG
block|}
block|,
block|{
literal|"view-display-filters"
block|,
name|GIMP_STOCK_DISPLAY_FILTER
block|,
name|N_
argument_list|(
literal|"Display _Filters..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_display_filters_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DISPLAY_FILTER_DIALOG
block|}
block|,
block|{
literal|"view-shrink-wrap"
block|,
name|GTK_STOCK_ZOOM_FIT
block|,
name|N_
argument_list|(
literal|"Shrink _Wrap"
argument_list|)
block|,
literal|"<control>E"
block|,
name|N_
argument_list|(
literal|"Shrink wrap"
argument_list|)
block|,
name|G_CALLBACK
argument_list|(
name|view_shrink_wrap_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_VIEW_SHRINK_WRAP
block|}
block|,
block|{
literal|"view-move-to-screen"
block|,
name|GIMP_STOCK_MOVE_TO_SCREEN
block|,
name|N_
argument_list|(
literal|"Move to Screen..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_change_screen_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_VIEW_CHANGE_SCREEN
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_toggle_actions
specifier|static
name|GimpToggleActionEntry
name|view_toggle_actions
index|[]
init|=
block|{
block|{
literal|"view-dot-for-dot"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Dot for Dot"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_dot_for_dot_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_DOT_FOR_DOT
block|}
block|,
block|{
literal|"view-show-selection"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show _Selection"
argument_list|)
block|,
literal|"<control>T"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_selection_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_SELECTION
block|}
block|,
block|{
literal|"view-show-layer-boundary"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show _Layer Boundary"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_layer_boundary_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_LAYER_BOUNDARY
block|}
block|,
block|{
literal|"view-show-guides"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show _Guides"
argument_list|)
block|,
literal|"<control><shift>T"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_guides_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_GUIDES
block|}
block|,
block|{
literal|"view-snap-to-guides"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Sn_ap to Guides"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_snap_to_guides_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SNAP_TO_GUIDES
block|}
block|,
block|{
literal|"view-show-grid"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"S_how Grid"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_grid_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_VIEW_SHOW_GRID
block|}
block|,
block|{
literal|"view-snap-to-grid"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Sna_p to Grid"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_snap_to_grid_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_VIEW_SNAP_TO_GRID
block|}
block|,
block|{
literal|"view-show-menubar"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show _Menubar"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_menubar_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_MENUBAR
block|}
block|,
block|{
literal|"view-show-rulers"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show R_ulers"
argument_list|)
block|,
literal|"<control><shift>R"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_rulers_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_RULERS
block|}
block|,
block|{
literal|"view-show-scrollbars"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show Scroll_bars"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_scrollbars_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_SCROLLBARS
block|}
block|,
block|{
literal|"view-show-statusbar"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Show S_tatusbar"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_toggle_statusbar_cmd_callback
argument_list|)
block|,
name|TRUE
block|,
name|GIMP_HELP_VIEW_SHOW_STATUSBAR
block|}
block|,
block|{
literal|"view-fullscreen"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Fullscr_een"
argument_list|)
block|,
literal|"F11"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|view_fullscreen_cmd_callback
argument_list|)
block|,
name|FALSE
block|,
name|GIMP_HELP_VIEW_FULLSCREEN
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_zoom_actions
specifier|static
name|GimpEnumActionEntry
name|view_zoom_actions
index|[]
init|=
block|{
block|{
literal|"view-zoom"
block|,
name|NULL
block|,
literal|"Set zoom factor"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"view-zoom-minimum"
block|,
name|GTK_STOCK_ZOOM_OUT
block|,
literal|"Zoom out as far as possible"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-maximum"
block|,
name|GTK_STOCK_ZOOM_IN
block|,
literal|"Zoom in as far as possible"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-out"
block|,
name|GTK_STOCK_ZOOM_OUT
block|,
name|N_
argument_list|(
literal|"Zoom _Out"
argument_list|)
block|,
literal|"minus"
block|,
name|N_
argument_list|(
literal|"Zoom out"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-in"
block|,
name|GTK_STOCK_ZOOM_IN
block|,
name|N_
argument_list|(
literal|"Zoom _In"
argument_list|)
block|,
literal|"plus"
block|,
name|N_
argument_list|(
literal|"Zoom in"
argument_list|)
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-out-skip"
block|,
name|GTK_STOCK_ZOOM_OUT
block|,
literal|"Zoom out a lot"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-in-skip"
block|,
name|GTK_STOCK_ZOOM_IN
block|,
literal|"Zoom in a lot"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_zoom_explicit_actions
specifier|static
name|GimpRadioActionEntry
name|view_zoom_explicit_actions
index|[]
init|=
block|{
block|{
literal|"view-zoom-16-1"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"16:1  (1600%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|160000
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-8-1"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"8:1  (800%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|80000
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-4-1"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"4:1  (400%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|40000
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-2-1"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"2:1  (200%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|20000
block|,
name|GIMP_HELP_VIEW_ZOOM_IN
block|}
block|,
block|{
literal|"view-zoom-1-1"
block|,
name|GTK_STOCK_ZOOM_100
block|,
name|N_
argument_list|(
literal|"1:1  (100%)"
argument_list|)
block|,
literal|"1"
block|,
name|N_
argument_list|(
literal|"Zoom 1:1"
argument_list|)
block|,
literal|10000
block|,
name|GIMP_HELP_VIEW_ZOOM_100
block|}
block|,
block|{
literal|"view-zoom-1-2"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"1:2  (50%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|5000
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-1-4"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"1:4  (25%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|2500
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-1-8"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"1:8  (12.5%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|1250
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-1-16"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"1:16  (6.25%)"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|625
block|,
name|GIMP_HELP_VIEW_ZOOM_OUT
block|}
block|,
block|{
literal|"view-zoom-other"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"O_ther..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
name|GIMP_HELP_VIEW_ZOOM_OTHER
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_padding_color_actions
specifier|static
name|GimpEnumActionEntry
name|view_padding_color_actions
index|[]
init|=
block|{
block|{
literal|"view-padding-color-theme"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"From _Theme"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CANVAS_PADDING_MODE_DEFAULT
block|,
name|GIMP_HELP_VIEW_PADDING_COLOR
block|}
block|,
block|{
literal|"view-padding-color-light-check"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Light Check Color"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CANVAS_PADDING_MODE_LIGHT_CHECK
block|,
name|GIMP_HELP_VIEW_PADDING_COLOR
block|}
block|,
block|{
literal|"view-padding-color-dark-check"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Dark Check Color"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CANVAS_PADDING_MODE_DARK_CHECK
block|,
name|GIMP_HELP_VIEW_PADDING_COLOR
block|}
block|,
block|{
literal|"view-padding-color-custom"
block|,
name|GTK_STOCK_SELECT_COLOR
block|,
name|N_
argument_list|(
literal|"Select _Custom Color..."
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CANVAS_PADDING_MODE_CUSTOM
block|,
name|GIMP_HELP_VIEW_PADDING_COLOR
block|}
block|,
block|{
literal|"view-padding-color-prefs"
block|,
name|GIMP_STOCK_RESET
block|,
name|N_
argument_list|(
literal|"As in _Preferences"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_CANVAS_PADDING_MODE_RESET
block|,
name|GIMP_HELP_VIEW_PADDING_COLOR
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_scroll_horizontal_actions
specifier|static
name|GimpEnumActionEntry
name|view_scroll_horizontal_actions
index|[]
init|=
block|{
block|{
literal|"view-scroll-horizontal"
block|,
name|NULL
block|,
literal|"Set horizontal scroll offset"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-left-border"
block|,
name|NULL
block|,
literal|"Scroll to left border"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-right-border"
block|,
name|NULL
block|,
literal|"Scroll to right border"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-left"
block|,
name|NULL
block|,
literal|"Scroll left"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-right"
block|,
name|NULL
block|,
literal|"Scroll right"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-page-left"
block|,
name|NULL
block|,
literal|"Scroll page left"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-page-right"
block|,
name|NULL
block|,
literal|"Scroll page right"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|view_scroll_vertical_actions
specifier|static
name|GimpEnumActionEntry
name|view_scroll_vertical_actions
index|[]
init|=
block|{
block|{
literal|"view-scroll-vertical"
block|,
name|NULL
block|,
literal|"Set vertical scroll offset"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SET
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-top-border"
block|,
name|NULL
block|,
literal|"Scroll to top border"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_FIRST
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-bottom-border"
block|,
name|NULL
block|,
literal|"Scroll to bottom border"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_LAST
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-up"
block|,
name|NULL
block|,
literal|"Scroll up"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-down"
block|,
name|NULL
block|,
literal|"Scroll down"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_NEXT
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-page-up"
block|,
name|NULL
block|,
literal|"Scroll page up"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
block|,
name|NULL
block|}
block|,
block|{
literal|"view-scroll-page-down"
block|,
name|NULL
block|,
literal|"Scroll page down"
block|,
name|NULL
block|,
name|NULL
block|,
name|GIMP_ACTION_SELECT_SKIP_NEXT
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|view_actions_setup (GimpActionGroup * group)
name|view_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GtkAction
modifier|*
name|action
decl_stmt|;
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|view_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_toggle_actions
argument_list|(
name|group
argument_list|,
name|view_toggle_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_toggle_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|view_zoom_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_zoom_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_zoom_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_radio_actions
argument_list|(
name|group
argument_list|,
name|view_zoom_explicit_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_zoom_explicit_actions
argument_list|)
argument_list|,
literal|10000
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_zoom_explicit_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|view_padding_color_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_padding_color_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_padding_color_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|view_scroll_horizontal_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_scroll_horizontal_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_scroll_horizontal_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_enum_actions
argument_list|(
name|group
argument_list|,
name|view_scroll_vertical_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|view_scroll_vertical_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_scroll_vertical_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  connect "activate" of view-zoom-other manually so it can be    *  selected even if it's the active item of the radio group    */
name|action
operator|=
name|gtk_action_group_get_action
argument_list|(
name|GTK_ACTION_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
literal|"view-zoom-other"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|action
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_zoom_other_cmd_callback
argument_list|)
argument_list|,
name|group
operator|->
name|user_data
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::check-type"
argument_list|,
name|G_CALLBACK
argument_list|(
name|view_actions_check_type_notify
argument_list|)
argument_list|,
name|group
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|view_actions_check_type_notify
argument_list|(
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|group
operator|->
name|gimp
operator|->
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|view_actions_update (GimpActionGroup * group,gpointer data)
name|view_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|action_data_get_display
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|NULL
decl_stmt|;
name|GimpDisplayOptions
modifier|*
name|options
init|=
name|NULL
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
init|=
name|NULL
decl_stmt|;
name|gboolean
name|fullscreen
init|=
name|FALSE
decl_stmt|;
name|gint
name|n_screens
init|=
literal|1
decl_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|fullscreen
operator|=
name|gimp_display_shell_get_fullscreen
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|options
operator|=
name|fullscreen
condition|?
name|shell
operator|->
name|fullscreen_options
else|:
name|shell
operator|->
name|options
expr_stmt|;
name|n_screens
operator|=
name|gdk_display_get_n_screens
argument_list|(
name|gtk_widget_get_display
argument_list|(
name|GTK_WIDGET
argument_list|(
name|shell
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
DECL|macro|SET_ACTIVE (action,condition)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_active (group, action, (condition) != 0)
DECL|macro|SET_VISIBLE (action,condition)
define|#
directive|define
name|SET_VISIBLE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_visible (group, action, (condition) != 0)
DECL|macro|SET_LABEL (action,label)
define|#
directive|define
name|SET_LABEL
parameter_list|(
name|action
parameter_list|,
name|label
parameter_list|)
define|\
value|gimp_action_group_set_action_label (group, action, (label))
DECL|macro|SET_SENSITIVE (action,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|action
parameter_list|,
name|condition
parameter_list|)
define|\
value|gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
DECL|macro|SET_COLOR (action,color)
define|#
directive|define
name|SET_COLOR
parameter_list|(
name|action
parameter_list|,
name|color
parameter_list|)
define|\
value|gimp_action_group_set_action_color (group, action, color, FALSE)
name|SET_SENSITIVE
argument_list|(
literal|"view-new"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-close"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-dot-for-dot"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-dot-for-dot"
argument_list|,
name|gdisp
operator|&&
name|shell
operator|->
name|dot_for_dot
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-out"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-in"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-fit-in"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-fit-to"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-16-1"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-8-1"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-4-1"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-2-1"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-1-1"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-1-2"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-1-4"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-1-8"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-1-16"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-zoom-other"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
name|view_actions_set_zoom
argument_list|(
name|group
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-info-window"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-navigation-window"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-display-filters"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-show-selection"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-selection"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_selection
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-show-layer-boundary"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-layer-boundary"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_layer_boundary
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-guides"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_guides
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-snap-to-guides"
argument_list|,
name|gdisp
operator|&&
name|shell
operator|->
name|snap_to_guides
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-grid"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_grid
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-snap-to-grid"
argument_list|,
name|gdisp
operator|&&
name|shell
operator|->
name|snap_to_grid
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|SET_COLOR
argument_list|(
literal|"view-padding-color-menu"
argument_list|,
operator|&
name|options
operator|->
name|padding_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|canvas
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gtk_widget_ensure_style
argument_list|(
name|shell
operator|->
name|canvas
argument_list|)
expr_stmt|;
name|gimp_rgb_set_gdk_color
argument_list|(
operator|&
name|color
argument_list|,
name|shell
operator|->
name|canvas
operator|->
name|style
operator|->
name|bg
operator|+
name|GTK_STATE_NORMAL
argument_list|)
expr_stmt|;
name|gimp_rgb_set_alpha
argument_list|(
operator|&
name|color
argument_list|,
name|GIMP_OPACITY_OPAQUE
argument_list|)
expr_stmt|;
name|SET_COLOR
argument_list|(
literal|"view-padding-color-theme"
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
block|}
block|}
name|SET_SENSITIVE
argument_list|(
literal|"view-show-menubar"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-menubar"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_menubar
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-show-rulers"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-rulers"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_rulers
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-show-scrollbars"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-scrollbars"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_scrollbars
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-show-statusbar"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-show-statusbar"
argument_list|,
name|gdisp
operator|&&
name|options
operator|->
name|show_statusbar
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-shrink-wrap"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"view-fullscreen"
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|SET_ACTIVE
argument_list|(
literal|"view-fullscreen"
argument_list|,
name|gdisp
operator|&&
name|fullscreen
argument_list|)
expr_stmt|;
name|SET_VISIBLE
argument_list|(
literal|"view-move-to-screen"
argument_list|,
name|gdisp
operator|&&
name|n_screens
operator|>
literal|1
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_ACTIVE
undef|#
directive|undef
name|SET_VISIBLE
undef|#
directive|undef
name|SET_LABEL
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_COLOR
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|view_actions_set_zoom (GimpActionGroup * group,GimpDisplayShell * shell)
name|view_actions_set_zoom
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|action
init|=
name|NULL
decl_stmt|;
name|guint
name|scale
decl_stmt|;
name|gchar
name|buf
index|[
literal|16
index|]
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|scale
operator|=
name|ROUND
argument_list|(
name|shell
operator|->
name|scale
operator|*
literal|1000
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|scale
condition|)
block|{
case|case
literal|16000
case|:
name|action
operator|=
literal|"view-zoom-16-1"
expr_stmt|;
break|break;
case|case
literal|8000
case|:
name|action
operator|=
literal|"view-zoom-8-1"
expr_stmt|;
break|break;
case|case
literal|4000
case|:
name|action
operator|=
literal|"view-zoom-4-1"
expr_stmt|;
break|break;
case|case
literal|2000
case|:
name|action
operator|=
literal|"view-zoom-2-1"
expr_stmt|;
break|break;
case|case
literal|1000
case|:
name|action
operator|=
literal|"view-zoom-1-1"
expr_stmt|;
break|break;
case|case
literal|500
case|:
name|action
operator|=
literal|"view-zoom-1-2"
expr_stmt|;
break|break;
case|case
literal|250
case|:
name|action
operator|=
literal|"view-zoom-1-4"
expr_stmt|;
break|break;
case|case
literal|125
case|:
name|action
operator|=
literal|"view-zoom-1-8"
expr_stmt|;
break|break;
case|case
literal|63
case|:
case|case
literal|62
case|:
name|action
operator|=
literal|"view-zoom-1-16"
expr_stmt|;
break|break;
block|}
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|shell
operator|->
name|scale
operator|>=
literal|0.15
condition|?
literal|"%.0f%%"
else|:
literal|"%.2f%%"
argument_list|,
name|shell
operator|->
name|scale
operator|*
literal|100.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|action
condition|)
block|{
name|action
operator|=
literal|"view-zoom-other"
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Other (%s) ..."
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
name|action
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|shell
operator|->
name|other_scale
operator|=
name|shell
operator|->
name|scale
expr_stmt|;
block|}
name|gimp_action_group_set_action_active
argument_list|(
name|group
argument_list|,
name|action
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"_Zoom (%s)"
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_label
argument_list|(
name|group
argument_list|,
literal|"view-zoom-menu"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
comment|/* flag as dirty */
name|shell
operator|->
name|other_scale
operator|=
operator|-
name|fabs
argument_list|(
name|shell
operator|->
name|other_scale
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|view_actions_check_type_notify (GimpDisplayConfig * config,GParamSpec * pspec,GimpActionGroup * group)
name|view_actions_check_type_notify
parameter_list|(
name|GimpDisplayConfig
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|render_blend_light_check
index|[
literal|0
index|]
argument_list|,
name|render_blend_light_check
index|[
literal|1
index|]
argument_list|,
name|render_blend_light_check
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_color
argument_list|(
name|group
argument_list|,
literal|"view-padding-color-light-check"
argument_list|,
operator|&
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|render_blend_dark_check
index|[
literal|0
index|]
argument_list|,
name|render_blend_dark_check
index|[
literal|1
index|]
argument_list|,
name|render_blend_dark_check
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
name|gimp_action_group_set_action_color
argument_list|(
name|group
argument_list|,
literal|"view-padding-color-dark-check"
argument_list|,
operator|&
name|color
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

