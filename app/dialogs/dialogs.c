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
file|"dialogs-types.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-constructors.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|global_dialog_factory
name|GimpDialogFactory
modifier|*
name|global_dialog_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_dock_factory
name|GimpDialogFactory
modifier|*
name|global_dock_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_toolbox_factory
name|GimpDialogFactory
modifier|*
name|global_toolbox_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|FOREIGN (id,remember_size)
define|#
directive|define
name|FOREIGN
parameter_list|(
name|id
parameter_list|,
name|remember_size
parameter_list|)
define|\
value|{ id, NULL, NULL, NULL, NULL, \     NULL, 0, TRUE,  TRUE, remember_size, FALSE }
end_define

begin_define
DECL|macro|TOPLEVEL (id,new_func,singleton,session_managed,remember_size)
define|#
directive|define
name|TOPLEVEL
parameter_list|(
name|id
parameter_list|,
name|new_func
parameter_list|,
name|singleton
parameter_list|,
name|session_managed
parameter_list|,
name|remember_size
parameter_list|)
define|\
value|{ id, NULL, NULL, NULL, NULL, \     new_func, 0, singleton, session_managed, remember_size, FALSE }
end_define

begin_decl_stmt
DECL|variable|toplevel_entries
specifier|static
specifier|const
name|GimpDialogFactoryEntry
name|toplevel_entries
index|[]
init|=
block|{
comment|/*  foreign toplevels without constructor  */
name|FOREIGN
argument_list|(
literal|"gimp-brightness-contrast-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-color-picker-tool-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-colorize-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-crop-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-curves-tool-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-color-balance-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-hue-saturation-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-levels-tool-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-measure-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-posterize-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-rotate-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-scale-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-shear-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-text-tool-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-threshold-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-perspective-tool-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-toolbox-color-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-gradient-editor-color-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-palette-editor-color-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-colormap-editor-color-dialog"
argument_list|,
name|FALSE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-keyboard-shortcuts-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
name|FOREIGN
argument_list|(
literal|"gimp-controller-action-dialog"
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  ordinary toplevels  */
name|TOPLEVEL
argument_list|(
literal|"gimp-image-new-dialog"
argument_list|,
name|dialogs_image_new_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-open-dialog"
argument_list|,
name|dialogs_file_open_new
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-open-location-dialog"
argument_list|,
name|dialogs_file_open_location_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-file-save-dialog"
argument_list|,
name|dialogs_file_save_new
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  singleton toplevels  */
name|TOPLEVEL
argument_list|(
literal|"gimp-preferences-dialog"
argument_list|,
name|dialogs_preferences_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-module-dialog"
argument_list|,
name|dialogs_module_get
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-tips-dialog"
argument_list|,
name|dialogs_tips_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-about-dialog"
argument_list|,
name|dialogs_about_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-error-dialog"
argument_list|,
name|dialogs_error_get
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
block|,
name|TOPLEVEL
argument_list|(
literal|"gimp-quit-dialog"
argument_list|,
argument|dialogs_quit_get
argument_list|,
argument|TRUE
argument_list|,
argument|FALSE
argument_list|,
argument|FALSE
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_define
define|#
directive|define
name|DOCKABLE
parameter_list|(
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|stock_id
parameter_list|,
name|help_id
parameter_list|,\
DECL|macro|DOCKABLE (id,name,blurb,stock_id,help_id,\\\nnew_func,preview_size,singleton)
name|new_func
parameter_list|,
name|preview_size
parameter_list|,
name|singleton
parameter_list|)
define|\
value|{ id, name, blurb, stock_id, help_id, \     new_func, preview_size, singleton, FALSE, FALSE, TRUE }
end_define

begin_define
define|#
directive|define
name|LISTGRID
parameter_list|(
name|id
parameter_list|,
name|name
parameter_list|,
name|blurb
parameter_list|,
name|stock_id
parameter_list|,
name|help_id
parameter_list|,\
DECL|macro|LISTGRID (id,name,blurb,stock_id,help_id,\\\npreview_size)
name|preview_size
parameter_list|)
define|\
value|{ "gimp-"#id"-list", name, blurb, stock_id, help_id, \     dialogs_##id##_list_view_new, preview_size, FALSE, FALSE, FALSE, TRUE }, \   { "gimp-"#id"-grid", name, blurb, stock_id, help_id, \     dialogs_##id##_grid_view_new, preview_size, FALSE, FALSE, FALSE, TRUE }
end_define

begin_decl_stmt
DECL|variable|dock_entries
specifier|static
specifier|const
name|GimpDialogFactoryEntry
name|dock_entries
index|[]
init|=
block|{
comment|/*  singleton dockables  */
name|DOCKABLE
argument_list|(
literal|"gimp-tool-options"
argument_list|,
name|N_
argument_list|(
literal|"Tool Options"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_TOOL_OPTIONS
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|dialogs_tool_options_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-device-status"
argument_list|,
name|N_
argument_list|(
literal|"Devices"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Device Status"
argument_list|)
argument_list|,
name|GIMP_STOCK_DEVICE_STATUS
argument_list|,
name|GIMP_HELP_DEVICE_STATUS_DIALOG
argument_list|,
name|dialogs_device_status_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-error-console"
argument_list|,
name|N_
argument_list|(
literal|"Errors"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Error Console"
argument_list|)
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|GIMP_HELP_ERRORS_DIALOG
argument_list|,
name|dialogs_error_console_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
comment|/*  list& grid views  */
name|LISTGRID
argument_list|(
name|image
argument_list|,
name|N_
argument_list|(
literal|"Images"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_IMAGES
argument_list|,
name|GIMP_HELP_IMAGE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|brush
argument_list|,
name|N_
argument_list|(
literal|"Brushes"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|GIMP_HELP_BRUSH_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|pattern
argument_list|,
name|N_
argument_list|(
literal|"Patterns"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PATTERN
argument_list|,
name|GIMP_HELP_PATTERN_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|gradient
argument_list|,
name|N_
argument_list|(
literal|"Gradients"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|GIMP_HELP_GRADIENT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|palette
argument_list|,
name|N_
argument_list|(
literal|"Palettes"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PALETTE
argument_list|,
name|GIMP_HELP_PALETTE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|font
argument_list|,
name|N_
argument_list|(
literal|"Fonts"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_FONT
argument_list|,
name|GIMP_HELP_FONT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|tool
argument_list|,
name|N_
argument_list|(
literal|"Tools"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_TOOLS
argument_list|,
name|GIMP_HELP_TOOLS_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|buffer
argument_list|,
name|N_
argument_list|(
literal|"Buffers"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BUFFER
argument_list|,
name|GIMP_HELP_BUFFER_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|document
argument_list|,
name|N_
argument_list|(
literal|"History"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Document History"
argument_list|)
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|GIMP_HELP_DOCUMENT_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_LARGE
argument_list|)
block|,
name|LISTGRID
argument_list|(
name|template
argument_list|,
name|N_
argument_list|(
literal|"Templates"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Image Templates"
argument_list|)
argument_list|,
name|GIMP_STOCK_TEMPLATE
argument_list|,
name|GIMP_HELP_TEMPLATE_DIALOG
argument_list|,
name|GIMP_VIEW_SIZE_SMALL
argument_list|)
block|,
comment|/*  image related  */
name|DOCKABLE
argument_list|(
literal|"gimp-layer-list"
argument_list|,
name|N_
argument_list|(
literal|"Layers"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_LAYERS
argument_list|,
name|GIMP_HELP_LAYER_DIALOG
argument_list|,
name|dialogs_layer_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-channel-list"
argument_list|,
name|N_
argument_list|(
literal|"Channels"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_CHANNELS
argument_list|,
name|GIMP_HELP_CHANNEL_DIALOG
argument_list|,
name|dialogs_channel_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-vectors-list"
argument_list|,
name|N_
argument_list|(
literal|"Paths"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_PATHS
argument_list|,
name|GIMP_HELP_PATH_DIALOG
argument_list|,
name|dialogs_vectors_list_view_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-indexed-palette"
argument_list|,
name|N_
argument_list|(
literal|"Colormap"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_INDEXED_PALETTE
argument_list|,
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
argument_list|,
name|dialogs_colormap_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-histogram-editor"
argument_list|,
name|N_
argument_list|(
literal|"Histogram"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_HISTOGRAM
argument_list|,
name|GIMP_HELP_HISTOGRAM_DIALOG
argument_list|,
name|dialogs_histogram_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-selection-editor"
argument_list|,
name|N_
argument_list|(
literal|"Selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Selection Editor"
argument_list|)
argument_list|,
name|GIMP_STOCK_SELECTION
argument_list|,
name|GIMP_HELP_SELECTION_DIALOG
argument_list|,
name|dialogs_selection_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-undo-history"
argument_list|,
name|N_
argument_list|(
literal|"Undo"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Undo History"
argument_list|)
argument_list|,
name|GIMP_STOCK_UNDO_HISTORY
argument_list|,
name|GIMP_HELP_UNDO_DIALOG
argument_list|,
name|dialogs_undo_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  display related  */
name|DOCKABLE
argument_list|(
literal|"gimp-navigation-view"
argument_list|,
name|N_
argument_list|(
literal|"Navigation"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Display Navigation"
argument_list|)
argument_list|,
name|GIMP_STOCK_NAVIGATION
argument_list|,
name|GIMP_HELP_NAVIGATION_DIALOG
argument_list|,
name|dialogs_navigation_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  editors  */
name|DOCKABLE
argument_list|(
literal|"gimp-color-editor"
argument_list|,
name|N_
argument_list|(
literal|"FG/BG"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"FG/BG Color"
argument_list|)
argument_list|,
name|GIMP_STOCK_DEFAULT_COLORS
argument_list|,
name|GIMP_HELP_COLOR_DIALOG
argument_list|,
name|dialogs_color_editor_new
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
block|,
comment|/*  singleton editors  */
name|DOCKABLE
argument_list|(
literal|"gimp-brush-editor"
argument_list|,
name|N_
argument_list|(
literal|"Brush Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|GIMP_HELP_BRUSH_EDITOR_DIALOG
argument_list|,
name|dialogs_brush_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-gradient-editor"
argument_list|,
name|N_
argument_list|(
literal|"Gradient Editor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|GIMP_HELP_GRADIENT_EDITOR_DIALOG
argument_list|,
name|dialogs_gradient_editor_get
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
block|,
name|DOCKABLE
argument_list|(
literal|"gimp-palette-editor"
argument_list|,
argument|N_(
literal|"Palette Editor"
argument|)
argument_list|,
argument|NULL
argument_list|,
argument|GIMP_STOCK_PALETTE
argument_list|,
argument|GIMP_HELP_PALETTE_EDITOR_DIALOG
argument_list|,
argument|dialogs_palette_editor_get
argument_list|,
literal|0
argument_list|,
argument|TRUE
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dialogs_init (Gimp * gimp,GimpMenuFactory * menu_factory)
name|dialogs_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|)
expr_stmt|;
name|global_dialog_factory
operator|=
name|gimp_dialog_factory_new
argument_list|(
literal|"toplevel"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|global_toolbox_factory
operator|=
name|gimp_dialog_factory_new
argument_list|(
literal|"toolbox"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
name|dialogs_toolbox_get
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_set_constructor
argument_list|(
name|global_toolbox_factory
argument_list|,
name|dialogs_dockable_constructor
argument_list|)
expr_stmt|;
name|global_dock_factory
operator|=
name|gimp_dialog_factory_new
argument_list|(
literal|"dock"
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
name|dialogs_dock_new
argument_list|)
expr_stmt|;
name|gimp_dialog_factory_set_constructor
argument_list|(
name|global_dock_factory
argument_list|,
name|dialogs_dockable_constructor
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|toplevel_entries
argument_list|)
condition|;
name|i
operator|++
control|)
name|gimp_dialog_factory_register_entry
argument_list|(
name|global_dialog_factory
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|identifier
argument_list|,
name|gettext
argument_list|(
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|blurb
argument_list|)
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|help_id
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|new_func
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|preview_size
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|singleton
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|session_managed
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|remember_size
argument_list|,
name|toplevel_entries
index|[
name|i
index|]
operator|.
name|remember_if_open
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|G_N_ELEMENTS
argument_list|(
name|dock_entries
argument_list|)
condition|;
name|i
operator|++
control|)
name|gimp_dialog_factory_register_entry
argument_list|(
name|global_dock_factory
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|identifier
argument_list|,
name|gettext
argument_list|(
name|dock_entries
index|[
name|i
index|]
operator|.
name|name
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|dock_entries
index|[
name|i
index|]
operator|.
name|blurb
argument_list|)
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|help_id
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|new_func
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|preview_size
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|singleton
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|session_managed
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|remember_size
argument_list|,
name|dock_entries
index|[
name|i
index|]
operator|.
name|remember_if_open
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|dialogs_exit (Gimp * gimp)
name|dialogs_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|global_dialog_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|global_dialog_factory
argument_list|)
expr_stmt|;
name|global_dialog_factory
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  destroy the "global_toolbox_factory" _before_ destroying the    *  "global_dock_factory" because the "global_toolbox_factory" owns    *  dockables which were created by the "global_dock_factory".  This    *  way they are properly removed from the "global_dock_factory", which    *  would complain about stale entries otherwise.    */
if|if
condition|(
name|global_toolbox_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|global_toolbox_factory
argument_list|)
expr_stmt|;
name|global_toolbox_factory
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|global_dock_factory
condition|)
block|{
name|g_object_unref
argument_list|(
name|global_dock_factory
argument_list|)
expr_stmt|;
name|global_dock_factory
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|dialogs_get_toolbox (void)
name|dialogs_get_toolbox
parameter_list|(
name|void
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|global_toolbox_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|global_toolbox_factory
operator|->
name|open_dialogs
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
name|GTK_WIDGET_TOPLEVEL
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
return|return
name|list
operator|->
name|data
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

