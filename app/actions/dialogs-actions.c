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
file|"actions-types.h"
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
file|"dialogs-actions.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-commands.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|dialogs_actions
specifier|static
name|GimpActionEntry
name|dialogs_actions
index|[]
init|=
block|{
block|{
literal|"dialogs-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Dialogs"
argument_list|)
block|}
block|,
block|{
literal|"dialogs-new-dock-menu"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Create New Doc_k"
argument_list|)
block|}
block|,
block|{
literal|"dialogs-new-dock-lcp"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Layers, Channels& Paths"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dialogs_create_lc_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK
block|}
block|,
block|{
literal|"dialogs-new-dock-data"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Brushes, Patterns& Gradients"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dialogs_create_data_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK
block|}
block|,
block|{
literal|"dialogs-new-dock-stuff"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"_Misc. Stuff"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dialogs_create_stuff_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_DOCK
block|}
block|,
block|{
literal|"dialogs-toolbox"
block|,
name|NULL
block|,
name|N_
argument_list|(
literal|"Tool_box"
argument_list|)
block|,
literal|"<control>B"
block|,
name|NULL
block|,
name|G_CALLBACK
argument_list|(
name|dialogs_show_toolbox_cmd_callback
argument_list|)
block|,
name|GIMP_HELP_TOOLBOX
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dialogs_dockable_actions
name|GimpStringActionEntry
name|dialogs_dockable_actions
index|[]
init|=
block|{
block|{
literal|"dialogs-tool-options"
block|,
name|GIMP_STOCK_TOOL_OPTIONS
block|,
name|N_
argument_list|(
literal|"Tool _Options"
argument_list|)
block|,
literal|"<control><shift>T"
block|,
name|NULL
block|,
literal|"gimp-tool-options"
block|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
block|}
block|,
block|{
literal|"dialogs-device-status"
block|,
name|GIMP_STOCK_DEVICE_STATUS
block|,
name|N_
argument_list|(
literal|"_Device Status"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-device-status"
block|,
name|GIMP_HELP_DEVICE_STATUS_DIALOG
block|}
block|,
block|{
literal|"dialogs-layers"
block|,
name|GIMP_STOCK_LAYERS
block|,
name|N_
argument_list|(
literal|"_Layers"
argument_list|)
block|,
literal|"<control>L"
block|,
name|NULL
block|,
literal|"gimp-layer-list"
block|,
name|GIMP_HELP_LAYER_DIALOG
block|}
block|,
block|{
literal|"dialogs-channels"
block|,
name|GIMP_STOCK_CHANNELS
block|,
name|N_
argument_list|(
literal|"_Channels"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-channel-list"
block|,
name|GIMP_HELP_CHANNEL_DIALOG
block|}
block|,
block|{
literal|"dialogs-vectors"
block|,
name|GIMP_STOCK_PATHS
block|,
name|N_
argument_list|(
literal|"_Paths"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-vectors-list"
block|,
name|GIMP_HELP_PATH_DIALOG
block|}
block|,
block|{
literal|"dialogs-indexed-palette"
block|,
name|GIMP_STOCK_INDEXED_PALETTE
block|,
name|N_
argument_list|(
literal|"Color_map"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-indexed-palette"
block|,
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
block|}
block|,
block|{
literal|"dialogs-histogram"
block|,
name|GIMP_STOCK_HISTOGRAM
block|,
name|N_
argument_list|(
literal|"Histogra_m"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-histogram-editor"
block|,
name|GIMP_HELP_HISTOGRAM_DIALOG
block|}
block|,
block|{
literal|"dialogs-selection-editor"
block|,
name|GIMP_STOCK_TOOL_RECT_SELECT
block|,
name|N_
argument_list|(
literal|"_Selection Editor"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-selection-editor"
block|,
name|GIMP_HELP_SELECTION_DIALOG
block|}
block|,
block|{
literal|"dialogs-navigation"
block|,
name|GIMP_STOCK_NAVIGATION
block|,
name|N_
argument_list|(
literal|"Na_vigation"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-navigation-view"
block|,
name|GIMP_HELP_NAVIGATION_DIALOG
block|}
block|,
block|{
literal|"dialogs-undo-history"
block|,
name|GIMP_STOCK_UNDO_HISTORY
block|,
name|N_
argument_list|(
literal|"Undo _History"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-undo-history"
block|,
name|GIMP_HELP_UNDO_DIALOG
block|}
block|,
block|{
literal|"dialogs-colors"
block|,
name|GIMP_STOCK_DEFAULT_COLORS
block|,
name|N_
argument_list|(
literal|"Colo_rs"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-color-editor"
block|,
name|GIMP_HELP_COLOR_DIALOG
block|}
block|,
block|{
literal|"dialogs-brushes"
block|,
name|GIMP_STOCK_BRUSH
block|,
name|N_
argument_list|(
literal|"_Brushes"
argument_list|)
block|,
literal|"<control><shift>B"
block|,
name|NULL
block|,
literal|"gimp-brush-grid|gimp-brush-list"
block|,
name|GIMP_HELP_BRUSH_DIALOG
block|}
block|,
block|{
literal|"dialogs-patterns"
block|,
name|GIMP_STOCK_PATTERN
block|,
name|N_
argument_list|(
literal|"P_atterns"
argument_list|)
block|,
literal|"<control><shift>P"
block|,
name|NULL
block|,
literal|"gimp-pattern-grid|gimp-pattern-list"
block|,
name|GIMP_HELP_PATTERN_DIALOG
block|}
block|,
block|{
literal|"dialogs-gradients"
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|N_
argument_list|(
literal|"_Gradients"
argument_list|)
block|,
literal|"<control>G"
block|,
name|NULL
block|,
literal|"gimp-gradient-list|gimp-gradient-grid"
block|,
name|GIMP_HELP_GRADIENT_DIALOG
block|}
block|,
block|{
literal|"dialogs-palettes"
block|,
name|GIMP_STOCK_PALETTE
block|,
name|N_
argument_list|(
literal|"Pal_ettes"
argument_list|)
block|,
literal|"<control>P"
block|,
name|NULL
block|,
literal|"gimp-palette-list|gimp-palette-list"
block|,
name|GIMP_HELP_PALETTE_DIALOG
block|}
block|,
block|{
literal|"dialogs-fonts"
block|,
name|GIMP_STOCK_FONT
block|,
name|N_
argument_list|(
literal|"_Fonts"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-font-list|gimp-font-grid"
block|,
name|GIMP_HELP_FONT_DIALOG
block|}
block|,
block|{
literal|"dialogs-buffers"
block|,
name|GIMP_STOCK_BUFFER
block|,
name|N_
argument_list|(
literal|"B_uffers"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|"gimp-buffer-list|gimp-buffer-grid"
block|,
name|GIMP_HELP_BUFFER_DIALOG
block|}
block|,
block|{
literal|"dialogs-images"
block|,
name|GIMP_STOCK_IMAGES
block|,
name|N_
argument_list|(
literal|"_Images"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-image-list|gimp-image-grid"
block|,
name|GIMP_HELP_IMAGE_DIALOG
block|}
block|,
block|{
literal|"dialogs-document-history"
block|,
name|GTK_STOCK_OPEN
block|,
name|N_
argument_list|(
literal|"Document Histor_y"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|"gimp-document-list|gimp-document-grid"
block|,
name|GIMP_HELP_DOCUMENT_DIALOG
block|}
block|,
block|{
literal|"dialogs-templates"
block|,
name|GIMP_STOCK_TEMPLATE
block|,
name|N_
argument_list|(
literal|"_Templates"
argument_list|)
block|,
literal|""
block|,
name|NULL
block|,
literal|"gimp-template-list|gimp-template-grid"
block|,
name|GIMP_HELP_TEMPLATE_DIALOG
block|}
block|,
block|{
literal|"dialogs-tools"
block|,
name|GIMP_STOCK_TOOLS
block|,
name|N_
argument_list|(
literal|"T_ools"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-tool-list|gimp-tool-grid"
block|,
name|GIMP_HELP_TOOLS_DIALOG
block|}
block|,
block|{
literal|"dialogs-error-console"
block|,
name|GIMP_STOCK_WARNING
block|,
name|N_
argument_list|(
literal|"Error Co_nsole"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-error-console"
block|,
name|GIMP_HELP_ERRORS_DIALOG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_dialogs_dockable_actions
init|=
name|G_N_ELEMENTS
argument_list|(
name|dialogs_dockable_actions
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dialogs_toplevel_actions
specifier|static
name|GimpStringActionEntry
name|dialogs_toplevel_actions
index|[]
init|=
block|{
block|{
literal|"dialogs-preferences"
block|,
name|GTK_STOCK_PREFERENCES
block|,
name|N_
argument_list|(
literal|"_Preferences"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-preferences-dialog"
block|,
name|GIMP_HELP_PREFS_DIALOG
block|}
block|,
block|{
literal|"dialogs-module-dialog"
block|,
name|GTK_STOCK_EXECUTE
block|,
name|N_
argument_list|(
literal|"_Module Manager"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-module-dialog"
block|,
name|GIMP_HELP_MODULE_DIALOG
block|}
block|,
block|{
literal|"dialogs-tips"
block|,
name|GIMP_STOCK_INFO
block|,
name|N_
argument_list|(
literal|"_Tip of the Day"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-tips-dialog"
block|,
name|GIMP_HELP_TIPS_DIALOG
block|}
block|,
block|{
literal|"dialogs-about"
block|,
name|GIMP_STOCK_WILBER
block|,
name|N_
argument_list|(
literal|"_About"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|,
literal|"gimp-about-dialog"
block|,
name|GIMP_HELP_ABOUT_DIALOG
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|dialogs_actions_setup (GimpActionGroup * group)
name|dialogs_actions_setup
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|)
block|{
name|gimp_action_group_add_actions
argument_list|(
name|group
argument_list|,
name|dialogs_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialogs_actions
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
name|dialogs_dockable_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialogs_dockable_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialogs_create_dockable_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
name|dialogs_toplevel_actions
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|dialogs_toplevel_actions
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|dialogs_create_toplevel_cmd_callback
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_actions_update (GimpActionGroup * group,gpointer data)
name|dialogs_actions_update
parameter_list|(
name|GimpActionGroup
modifier|*
name|group
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{ }
end_function

end_unit

