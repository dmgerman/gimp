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
file|"gui-types.h"
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
file|"widgets/gimpitemfactory.h"
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
file|"menus.h"
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

begin_decl_stmt
DECL|variable|toplevel_entries
specifier|static
specifier|const
name|GimpDialogFactoryEntry
name|toplevel_entries
index|[]
init|=
block|{
block|{
literal|"gimp-device-status-dialog"
block|,
name|dialogs_device_status_get
block|,
literal|0
block|,
name|TRUE
block|,
name|TRUE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-preferences-dialog"
block|,
name|dialogs_preferences_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-module-browser-dialog"
block|,
name|dialogs_module_browser_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-display-filters-dialog"
block|,
name|dialogs_display_filters_get
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-tips-dialog"
block|,
name|dialogs_tips_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-about-dialog"
block|,
name|dialogs_about_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dock_entries
specifier|static
specifier|const
name|GimpDialogFactoryEntry
name|dock_entries
index|[]
init|=
block|{
block|{
literal|"gimp-tool-options"
block|,
name|dialogs_tool_options_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-error-console"
block|,
name|dialogs_error_console_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-image-list"
block|,
name|dialogs_image_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-brush-list"
block|,
name|dialogs_brush_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-pattern-list"
block|,
name|dialogs_pattern_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-gradient-list"
block|,
name|dialogs_gradient_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-palette-list"
block|,
name|dialogs_palette_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-tool-list"
block|,
name|dialogs_tool_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_SMALL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-buffer-list"
block|,
name|dialogs_buffer_list_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-image-grid"
block|,
name|dialogs_image_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-brush-grid"
block|,
name|dialogs_brush_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-pattern-grid"
block|,
name|dialogs_pattern_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-gradient-grid"
block|,
name|dialogs_gradient_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-palette-grid"
block|,
name|dialogs_palette_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-tool-grid"
block|,
name|dialogs_tool_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_SMALL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-buffer-grid"
block|,
name|dialogs_buffer_grid_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-image-tree"
block|,
name|dialogs_image_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-brush-tree"
block|,
name|dialogs_brush_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-pattern-tree"
block|,
name|dialogs_pattern_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-gradient-tree"
block|,
name|dialogs_gradient_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-palette-tree"
block|,
name|dialogs_palette_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-tool-tree"
block|,
name|dialogs_tool_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_SMALL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-buffer-tree"
block|,
name|dialogs_buffer_tree_view_new
block|,
name|GIMP_PREVIEW_SIZE_MEDIUM
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-layer-list"
block|,
name|dialogs_layer_list_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-layer-tree"
block|,
name|dialogs_layer_tree_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-channel-list"
block|,
name|dialogs_channel_list_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-channel-tree"
block|,
name|dialogs_channel_tree_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-vectors-list"
block|,
name|dialogs_vectors_list_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-vectors-tree"
block|,
name|dialogs_vectors_tree_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-path-list"
block|,
name|dialogs_path_list_view_new
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-indexed-palette"
block|,
name|dialogs_indexed_palette_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-selection-editor"
block|,
name|dialogs_selection_editor_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-undo-history"
block|,
name|dialogs_undo_history_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-color-editor"
block|,
name|dialogs_color_editor_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-document-list"
block|,
name|dialogs_document_list_new
block|,
name|GIMP_PREVIEW_SIZE_LARGE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-document-grid"
block|,
name|dialogs_document_grid_new
block|,
name|GIMP_PREVIEW_SIZE_LARGE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-document-tree"
block|,
name|dialogs_document_tree_new
block|,
name|GIMP_PREVIEW_SIZE_LARGE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-brush-editor"
block|,
name|dialogs_brush_editor_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-gradient-editor"
block|,
name|dialogs_gradient_editor_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-palette-editor"
block|,
name|dialogs_palette_editor_get
block|,
literal|0
block|,
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|,
block|{
literal|"gimp-navigation-view"
block|,
name|dialogs_navigation_view_new
block|,
literal|0
block|,
name|FALSE
block|,
name|FALSE
block|,
name|FALSE
block|,
name|TRUE
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|dialogs_init (Gimp * gimp)
name|dialogs_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
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
name|NULL
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
name|global_menu_factory
argument_list|,
name|dialogs_toolbox_get
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
name|global_menu_factory
argument_list|,
name|dialogs_dock_new
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

end_unit

