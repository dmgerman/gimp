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
DECL|variable|dialogs_dockable_actions
specifier|const
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Tool _Options"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the tool options dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Device Status"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the device status dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Layers"
argument_list|)
block|,
literal|"<control>L"
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the layers dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Channels"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the channels dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Paths"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the paths dialog"
argument_list|)
block|,
literal|"gimp-vectors-list"
block|,
name|GIMP_HELP_PATH_DIALOG
block|}
block|,
block|{
literal|"dialogs-indexed-palette"
block|,
name|GIMP_STOCK_COLORMAP
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Color_map"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the colormap dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Histogra_m"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the histogram dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Selection Editor"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the selection editor"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Na_vigation"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the display navigation dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Undo _History"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the undo history dialog"
argument_list|)
block|,
literal|"gimp-undo-history"
block|,
name|GIMP_HELP_UNDO_DIALOG
block|}
block|,
block|{
literal|"dialogs-cursor"
block|,
name|GIMP_STOCK_CURSOR
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Pointer"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the pointer information dialog"
argument_list|)
block|,
literal|"gimp-cursor-view"
block|,
name|GIMP_HELP_POINTER_INFO_DIALOG
block|}
block|,
block|{
literal|"dialogs-sample-points"
block|,
name|GIMP_STOCK_SAMPLE_POINT
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Sample Points"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the sample points dialog"
argument_list|)
block|,
literal|"gimp-sample-point-editor"
block|,
name|GIMP_HELP_SAMPLE_POINT_DIALOG
block|}
block|,
block|{
literal|"dialogs-colors"
block|,
name|GIMP_STOCK_DEFAULT_COLORS
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Colo_rs"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the FG/BG color dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Brushes"
argument_list|)
block|,
literal|"<control><shift>B"
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the brushes dialog"
argument_list|)
block|,
literal|"gimp-brush-grid|gimp-brush-list"
block|,
name|GIMP_HELP_BRUSH_DIALOG
block|}
block|,
block|{
literal|"dialogs-brush-editor"
block|,
name|GIMP_STOCK_BRUSH
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Brush Editor"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the brush editor"
argument_list|)
block|,
literal|"gimp-brush-editor"
block|,
name|GIMP_HELP_BRUSH_EDIT
block|}
block|,
block|{
literal|"dialogs-dynamics-editor"
block|,
name|GIMP_STOCK_DYNAMICS
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Dynamics Editor"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the dynamics editor"
argument_list|)
block|,
literal|"gimp-dynamics-editor"
block|,
name|GIMP_HELP_DYNAMICS_EDITOR_DIALOG
block|}
block|,
block|{
literal|"dialogs-dynamics"
block|,
name|GIMP_STOCK_PATTERN
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Dynamics"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open dynamics list dialog"
argument_list|)
block|,
literal|"gimp-dynamics-list"
block|,
name|GIMP_HELP_DYNAMICS_DIALOG
block|}
block|,
block|{
literal|"dialogs-patterns"
block|,
name|GIMP_STOCK_PATTERN
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"P_atterns"
argument_list|)
block|,
literal|"<control><shift>P"
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the patterns dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Gradients"
argument_list|)
block|,
literal|"<control>G"
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the gradients dialog"
argument_list|)
block|,
literal|"gimp-gradient-list|gimp-gradient-grid"
block|,
name|GIMP_HELP_GRADIENT_DIALOG
block|}
block|,
block|{
literal|"dialogs-gradient-editor"
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Gradient Editor"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the gradient editor"
argument_list|)
block|,
literal|"gimp-gradient-editor"
block|,
name|GIMP_HELP_GRADIENT_EDIT
block|}
block|,
block|{
literal|"dialogs-palettes"
block|,
name|GIMP_STOCK_PALETTE
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Pal_ettes"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the palettes dialog"
argument_list|)
block|,
literal|"gimp-palette-list|gimp-palette-grid"
block|,
name|GIMP_HELP_PALETTE_DIALOG
block|}
block|,
block|{
literal|"dialogs-palette-editor"
block|,
name|GIMP_STOCK_PALETTE
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Palette Editor"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the palette editor"
argument_list|)
block|,
literal|"gimp-palette-editor"
block|,
name|GIMP_HELP_PALETTE_EDIT
block|}
block|,
block|{
literal|"dialogs-fonts"
block|,
name|GIMP_STOCK_FONT
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Fonts"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the fonts dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"B_uffers"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the named buffers dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Images"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the images dialog"
argument_list|)
block|,
literal|"gimp-image-list|gimp-image-grid"
block|,
name|GIMP_HELP_IMAGE_DIALOG
block|}
block|,
block|{
literal|"dialogs-document-history"
block|,
literal|"document-open-recent"
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Document Histor_y"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the document history dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Templates"
argument_list|)
block|,
literal|""
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the image templates dialog"
argument_list|)
block|,
literal|"gimp-template-list|gimp-template-grid"
block|,
name|GIMP_HELP_TEMPLATE_DIALOG
block|}
block|,
block|{
literal|"dialogs-error-console"
block|,
name|GIMP_STOCK_WARNING
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Error Co_nsole"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the error console"
argument_list|)
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
specifier|const
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Preferences"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the preferences dialog"
argument_list|)
block|,
literal|"gimp-preferences-dialog"
block|,
name|GIMP_HELP_PREFS_DIALOG
block|}
block|,
block|{
literal|"dialogs-keyboard-shortcuts"
block|,
name|GIMP_STOCK_CHAR_PICKER
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Keyboard Shortcuts"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the keyboard shortcuts editor"
argument_list|)
block|,
literal|"gimp-keyboard-shortcuts-dialog"
block|,
name|GIMP_HELP_KEYBOARD_SHORTCUTS
block|}
block|,
block|{
literal|"dialogs-module-dialog"
block|,
name|GTK_STOCK_EXECUTE
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Modules"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Open the module manager dialog"
argument_list|)
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
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_Tip of the Day"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"Show some helpful tips on using GIMP"
argument_list|)
block|,
literal|"gimp-tips-dialog"
block|,
name|GIMP_HELP_TIPS_DIALOG
block|}
block|,
block|{
literal|"dialogs-about"
block|,
name|GTK_STOCK_ABOUT
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"_About"
argument_list|)
block|,
name|NULL
block|,
name|NC_
argument_list|(
literal|"dialogs-action"
argument_list|,
literal|"About GIMP"
argument_list|)
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
name|gimp_action_group_add_string_actions
argument_list|(
name|group
argument_list|,
literal|"dialogs-action"
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
literal|"dialogs-action"
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

