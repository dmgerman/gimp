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
file|"core/gimpcontainer.h"
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
file|"widgets/gimpactionfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpactiongroup.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainereditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimageeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemtreeview.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpnavigationeditor.h"
end_include

begin_include
include|#
directive|include
file|"dialogs/dialogs.h"
end_include

begin_include
include|#
directive|include
file|"brush-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"brushes-actions.h"
end_include

begin_include
include|#
directive|include
file|"buffers-actions.h"
end_include

begin_include
include|#
directive|include
file|"channels-actions.h"
end_include

begin_include
include|#
directive|include
file|"colormap-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"context-actions.h"
end_include

begin_include
include|#
directive|include
file|"cursor-info-actions.h"
end_include

begin_include
include|#
directive|include
file|"debug-actions.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-actions.h"
end_include

begin_include
include|#
directive|include
file|"dock-actions.h"
end_include

begin_include
include|#
directive|include
file|"dockable-actions.h"
end_include

begin_include
include|#
directive|include
file|"documents-actions.h"
end_include

begin_include
include|#
directive|include
file|"drawable-actions.h"
end_include

begin_include
include|#
directive|include
file|"edit-actions.h"
end_include

begin_include
include|#
directive|include
file|"error-console-actions.h"
end_include

begin_include
include|#
directive|include
file|"file-actions.h"
end_include

begin_include
include|#
directive|include
file|"fonts-actions.h"
end_include

begin_include
include|#
directive|include
file|"gradient-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"gradients-actions.h"
end_include

begin_include
include|#
directive|include
file|"help-actions.h"
end_include

begin_include
include|#
directive|include
file|"image-actions.h"
end_include

begin_include
include|#
directive|include
file|"images-actions.h"
end_include

begin_include
include|#
directive|include
file|"layers-actions.h"
end_include

begin_include
include|#
directive|include
file|"palette-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"palettes-actions.h"
end_include

begin_include
include|#
directive|include
file|"patterns-actions.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-actions.h"
end_include

begin_include
include|#
directive|include
file|"quick-mask-actions.h"
end_include

begin_include
include|#
directive|include
file|"sample-point-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"select-actions.h"
end_include

begin_include
include|#
directive|include
file|"templates-actions.h"
end_include

begin_include
include|#
directive|include
file|"text-editor-actions.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-actions.h"
end_include

begin_include
include|#
directive|include
file|"tools-actions.h"
end_include

begin_include
include|#
directive|include
file|"vectors-actions.h"
end_include

begin_include
include|#
directive|include
file|"view-actions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|global_action_factory
name|GimpActionFactory
modifier|*
name|global_action_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|action_groups
specifier|static
name|GimpActionFactoryEntry
name|action_groups
index|[]
init|=
block|{
block|{
literal|"brush-editor"
block|,
name|N_
argument_list|(
literal|"Brush Editor"
argument_list|)
block|,
name|GIMP_STOCK_BRUSH
block|,
name|brush_editor_actions_setup
block|,
name|brush_editor_actions_update
block|}
block|,
block|{
literal|"brushes"
block|,
name|N_
argument_list|(
literal|"Brushes"
argument_list|)
block|,
name|GIMP_STOCK_BRUSH
block|,
name|brushes_actions_setup
block|,
name|brushes_actions_update
block|}
block|,
block|{
literal|"buffers"
block|,
name|N_
argument_list|(
literal|"Buffers"
argument_list|)
block|,
name|GIMP_STOCK_BUFFER
block|,
name|buffers_actions_setup
block|,
name|buffers_actions_update
block|}
block|,
block|{
literal|"channels"
block|,
name|N_
argument_list|(
literal|"Channels"
argument_list|)
block|,
name|GIMP_STOCK_CHANNEL
block|,
name|channels_actions_setup
block|,
name|channels_actions_update
block|}
block|,
block|{
literal|"colormap-editor"
block|,
name|N_
argument_list|(
literal|"Colormap Editor"
argument_list|)
block|,
name|GIMP_STOCK_COLORMAP
block|,
name|colormap_editor_actions_setup
block|,
name|colormap_editor_actions_update
block|}
block|,
block|{
literal|"context"
block|,
name|N_
argument_list|(
literal|"Context"
argument_list|)
block|,
name|NULL
block|,
name|context_actions_setup
block|,
name|context_actions_update
block|}
block|,
block|{
literal|"cursor-info"
block|,
name|N_
argument_list|(
literal|"Pointer Information"
argument_list|)
block|,
name|NULL
block|,
name|cursor_info_actions_setup
block|,
name|cursor_info_actions_update
block|}
block|,
block|{
literal|"debug"
block|,
name|N_
argument_list|(
literal|"Debug"
argument_list|)
block|,
name|NULL
block|,
name|debug_actions_setup
block|,
name|debug_actions_update
block|}
block|,
block|{
literal|"dialogs"
block|,
name|N_
argument_list|(
literal|"Dialogs"
argument_list|)
block|,
name|NULL
block|,
name|dialogs_actions_setup
block|,
name|dialogs_actions_update
block|}
block|,
block|{
literal|"dock"
block|,
name|N_
argument_list|(
literal|"Dock"
argument_list|)
block|,
name|NULL
block|,
name|dock_actions_setup
block|,
name|dock_actions_update
block|}
block|,
block|{
literal|"dockable"
block|,
name|N_
argument_list|(
literal|"Dockable"
argument_list|)
block|,
name|NULL
block|,
name|dockable_actions_setup
block|,
name|dockable_actions_update
block|}
block|,
block|{
literal|"documents"
block|,
name|N_
argument_list|(
literal|"Document History"
argument_list|)
block|,
name|NULL
block|,
name|documents_actions_setup
block|,
name|documents_actions_update
block|}
block|,
block|{
literal|"drawable"
block|,
name|N_
argument_list|(
literal|"Drawable"
argument_list|)
block|,
name|GIMP_STOCK_LAYER
block|,
name|drawable_actions_setup
block|,
name|drawable_actions_update
block|}
block|,
block|{
literal|"edit"
block|,
name|N_
argument_list|(
literal|"Edit"
argument_list|)
block|,
name|GTK_STOCK_EDIT
block|,
name|edit_actions_setup
block|,
name|edit_actions_update
block|}
block|,
block|{
literal|"error-console"
block|,
name|N_
argument_list|(
literal|"Error Console"
argument_list|)
block|,
name|GIMP_STOCK_WARNING
block|,
name|error_console_actions_setup
block|,
name|error_console_actions_update
block|}
block|,
block|{
literal|"file"
block|,
name|N_
argument_list|(
literal|"File"
argument_list|)
block|,
name|GTK_STOCK_FILE
block|,
name|file_actions_setup
block|,
name|file_actions_update
block|}
block|,
block|{
literal|"fonts"
block|,
name|N_
argument_list|(
literal|"Fonts"
argument_list|)
block|,
name|GIMP_STOCK_FONT
block|,
name|fonts_actions_setup
block|,
name|fonts_actions_update
block|}
block|,
block|{
literal|"gradient-editor"
block|,
name|N_
argument_list|(
literal|"Gradient Editor"
argument_list|)
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|gradient_editor_actions_setup
block|,
name|gradient_editor_actions_update
block|}
block|,
block|{
literal|"gradients"
block|,
name|N_
argument_list|(
literal|"Gradients"
argument_list|)
block|,
name|GIMP_STOCK_GRADIENT
block|,
name|gradients_actions_setup
block|,
name|gradients_actions_update
block|}
block|,
block|{
literal|"help"
block|,
name|N_
argument_list|(
literal|"Help"
argument_list|)
block|,
name|GTK_STOCK_HELP
block|,
name|help_actions_setup
block|,
name|help_actions_update
block|}
block|,
block|{
literal|"image"
block|,
name|N_
argument_list|(
literal|"Image"
argument_list|)
block|,
name|GIMP_STOCK_IMAGE
block|,
name|image_actions_setup
block|,
name|image_actions_update
block|}
block|,
block|{
literal|"images"
block|,
name|N_
argument_list|(
literal|"Images"
argument_list|)
block|,
name|GIMP_STOCK_IMAGE
block|,
name|images_actions_setup
block|,
name|images_actions_update
block|}
block|,
block|{
literal|"layers"
block|,
name|N_
argument_list|(
literal|"Layers"
argument_list|)
block|,
name|GIMP_STOCK_LAYER
block|,
name|layers_actions_setup
block|,
name|layers_actions_update
block|}
block|,
block|{
literal|"palette-editor"
block|,
name|N_
argument_list|(
literal|"Palette Editor"
argument_list|)
block|,
name|GIMP_STOCK_PALETTE
block|,
name|palette_editor_actions_setup
block|,
name|palette_editor_actions_update
block|}
block|,
block|{
literal|"palettes"
block|,
name|N_
argument_list|(
literal|"Palettes"
argument_list|)
block|,
name|GIMP_STOCK_PALETTE
block|,
name|palettes_actions_setup
block|,
name|palettes_actions_update
block|}
block|,
block|{
literal|"patterns"
block|,
name|N_
argument_list|(
literal|"Patterns"
argument_list|)
block|,
name|GIMP_STOCK_PATTERN
block|,
name|patterns_actions_setup
block|,
name|patterns_actions_update
block|}
block|,
block|{
literal|"plug-in"
block|,
name|N_
argument_list|(
literal|"Plug-Ins"
argument_list|)
block|,
name|GIMP_STOCK_PLUGIN
block|,
name|plug_in_actions_setup
block|,
name|plug_in_actions_update
block|}
block|,
block|{
literal|"quick-mask"
block|,
name|N_
argument_list|(
literal|"Quick Mask"
argument_list|)
block|,
name|GIMP_STOCK_QUICK_MASK_ON
block|,
name|quick_mask_actions_setup
block|,
name|quick_mask_actions_update
block|}
block|,
block|{
literal|"sample-point-editor"
block|,
name|N_
argument_list|(
literal|"Sample Points"
argument_list|)
block|,
name|GIMP_STOCK_SAMPLE_POINT
block|,
name|sample_point_editor_actions_setup
block|,
name|sample_point_editor_actions_update
block|}
block|,
block|{
literal|"select"
block|,
name|N_
argument_list|(
literal|"Select"
argument_list|)
block|,
name|GIMP_STOCK_SELECTION
block|,
name|select_actions_setup
block|,
name|select_actions_update
block|}
block|,
block|{
literal|"templates"
block|,
name|N_
argument_list|(
literal|"Templates"
argument_list|)
block|,
name|GIMP_STOCK_TEMPLATE
block|,
name|templates_actions_setup
block|,
name|templates_actions_update
block|}
block|,
block|{
literal|"text-editor"
block|,
name|N_
argument_list|(
literal|"Text Editor"
argument_list|)
block|,
name|GTK_STOCK_EDIT
block|,
name|text_editor_actions_setup
block|,
name|text_editor_actions_update
block|}
block|,
block|{
literal|"tool-options"
block|,
name|N_
argument_list|(
literal|"Tool Options"
argument_list|)
block|,
name|GIMP_STOCK_TOOL_OPTIONS
block|,
name|tool_options_actions_setup
block|,
name|tool_options_actions_update
block|}
block|,
block|{
literal|"tools"
block|,
name|N_
argument_list|(
literal|"Tools"
argument_list|)
block|,
name|GIMP_STOCK_TOOLS
block|,
name|tools_actions_setup
block|,
name|tools_actions_update
block|}
block|,
block|{
literal|"vectors"
block|,
name|N_
argument_list|(
literal|"Paths"
argument_list|)
block|,
name|GIMP_STOCK_PATH
block|,
name|vectors_actions_setup
block|,
name|vectors_actions_update
block|}
block|,
block|{
literal|"view"
block|,
name|N_
argument_list|(
literal|"View"
argument_list|)
block|,
name|GIMP_STOCK_VISIBLE
block|,
name|view_actions_setup
block|,
name|view_actions_update
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|actions_init (Gimp * gimp)
name|actions_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|gui_config
decl_stmt|;
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
name|global_action_factory
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gui_config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|global_action_factory
operator|=
name|gimp_action_factory_new
argument_list|(
name|gimp
argument_list|,
name|gui_config
operator|->
name|menu_mnemonics
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
name|action_groups
argument_list|)
condition|;
name|i
operator|++
control|)
name|gimp_action_factory_group_register
argument_list|(
name|global_action_factory
argument_list|,
name|action_groups
index|[
name|i
index|]
operator|.
name|identifier
argument_list|,
name|gettext
argument_list|(
name|action_groups
index|[
name|i
index|]
operator|.
name|label
argument_list|)
argument_list|,
name|action_groups
index|[
name|i
index|]
operator|.
name|stock_id
argument_list|,
name|action_groups
index|[
name|i
index|]
operator|.
name|setup_func
argument_list|,
name|action_groups
index|[
name|i
index|]
operator|.
name|update_func
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|actions_exit (Gimp * gimp)
name|actions_exit
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
name|g_return_if_fail
argument_list|(
name|global_action_factory
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|global_action_factory
operator|->
name|gimp
operator|==
name|gimp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|global_action_factory
argument_list|)
expr_stmt|;
name|global_action_factory
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|Gimp
modifier|*
DECL|function|action_data_get_gimp (gpointer data)
name|action_data_get_gimp
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpDisplay
operator|*
operator|)
name|data
operator|)
operator|->
name|image
operator|->
name|gimp
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|data
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpDock
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpItemTreeView
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
operator|(
name|GimpContainerView
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
operator|(
operator|(
name|GimpContainerEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|view
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpImageEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_NAVIGATION_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpNavigationEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
if|if
condition|(
name|context
condition|)
return|return
name|context
operator|->
name|gimp
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpContext
modifier|*
DECL|function|action_data_get_context (gpointer data)
name|action_data_get_context
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|gimp_get_user_context
argument_list|(
operator|(
operator|(
name|GimpDisplay
operator|*
operator|)
name|data
operator|)
operator|->
name|image
operator|->
name|gimp
argument_list|)
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|gimp_get_user_context
argument_list|(
name|data
argument_list|)
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpDock
operator|*
operator|)
name|data
operator|)
operator|->
name|context
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpItemTreeView
operator|*
operator|)
name|data
operator|)
operator|->
name|context
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTAINER_VIEW
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|gimp_container_view_get_context
argument_list|(
operator|(
name|GimpContainerView
operator|*
operator|)
name|data
argument_list|)
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_CONTAINER_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|gimp_container_view_get_context
argument_list|(
operator|(
operator|(
name|GimpContainerEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|view
argument_list|)
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpImageEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_NAVIGATION_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpNavigationEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpImage
modifier|*
DECL|function|action_data_get_image (gpointer data)
name|action_data_get_image
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpDisplay
operator|*
operator|)
name|data
operator|)
operator|->
name|image
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpDock
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM_TREE_VIEW
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpItemTreeView
operator|*
operator|)
name|data
operator|)
operator|->
name|image
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
return|return
operator|(
operator|(
name|GimpImageEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|image
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_NAVIGATION_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpNavigationEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
if|if
condition|(
name|context
condition|)
return|return
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpDisplay
modifier|*
DECL|function|action_data_get_display (gpointer data)
name|action_data_get_display
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|data
return|;
elseif|else
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|data
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpDock
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_NAVIGATION_EDITOR
argument_list|(
name|data
argument_list|)
condition|)
name|context
operator|=
operator|(
operator|(
name|GimpNavigationEditor
operator|*
operator|)
name|data
operator|)
operator|->
name|context
expr_stmt|;
if|if
condition|(
name|context
condition|)
return|return
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|action_data_get_widget (gpointer data)
name|action_data_get_widget
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
return|return
name|NULL
return|;
if|if
condition|(
name|GIMP_IS_DISPLAY
argument_list|(
name|data
argument_list|)
condition|)
name|display
operator|=
name|data
expr_stmt|;
elseif|else
if|if
condition|(
name|GIMP_IS_GIMP
argument_list|(
name|data
argument_list|)
condition|)
name|display
operator|=
name|gimp_context_get_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|GTK_IS_WIDGET
argument_list|(
name|data
argument_list|)
condition|)
return|return
name|data
return|;
if|if
condition|(
name|display
condition|)
return|return
name|display
operator|->
name|shell
return|;
return|return
name|dialogs_get_toolbox
argument_list|()
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|action_select_value (GimpActionSelectType select_type,gdouble value,gdouble min,gdouble max,gdouble inc,gdouble skip_inc,gboolean wrap)
name|action_select_value
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|gdouble
name|value
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|,
name|gdouble
name|inc
parameter_list|,
name|gdouble
name|skip_inc
parameter_list|,
name|gboolean
name|wrap
parameter_list|)
block|{
switch|switch
condition|(
name|select_type
condition|)
block|{
case|case
name|GIMP_ACTION_SELECT_FIRST
case|:
name|value
operator|=
name|min
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_LAST
case|:
name|value
operator|=
name|max
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_PREVIOUS
case|:
name|value
operator|-=
name|inc
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_NEXT
case|:
name|value
operator|+=
name|inc
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
case|:
name|value
operator|-=
name|skip_inc
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_NEXT
case|:
name|value
operator|+=
name|skip_inc
expr_stmt|;
break|break;
default|default:
if|if
condition|(
operator|(
name|gint
operator|)
name|select_type
operator|>=
literal|0
condition|)
name|value
operator|=
operator|(
name|gdouble
operator|)
name|select_type
operator|*
operator|(
name|max
operator|-
name|min
operator|)
operator|/
literal|1000.0
operator|+
name|min
expr_stmt|;
else|else
name|g_return_val_if_reached
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|wrap
condition|)
block|{
while|while
condition|(
name|value
operator|<
name|min
condition|)
name|value
operator|=
name|max
operator|-
operator|(
name|min
operator|-
name|value
operator|)
expr_stmt|;
while|while
condition|(
name|value
operator|>
name|max
condition|)
name|value
operator|=
name|min
operator|+
operator|(
name|max
operator|-
name|value
operator|)
expr_stmt|;
block|}
else|else
block|{
name|value
operator|=
name|CLAMP
argument_list|(
name|value
argument_list|,
name|min
argument_list|,
name|max
argument_list|)
expr_stmt|;
block|}
return|return
name|value
return|;
block|}
end_function

begin_function
name|void
DECL|function|action_select_property (GimpActionSelectType select_type,GObject * object,const gchar * property_name,gdouble inc,gdouble skip_inc,gboolean wrap)
name|action_select_property
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|GObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
name|gdouble
name|inc
parameter_list|,
name|gdouble
name|skip_inc
parameter_list|,
name|gboolean
name|wrap
parameter_list|)
block|{
name|GParamSpec
modifier|*
name|pspec
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|property_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|pspec
operator|=
name|g_object_class_find_property
argument_list|(
name|G_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
argument_list|,
name|property_name
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|object
argument_list|,
name|property_name
argument_list|,
operator|&
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|value
operator|=
name|action_select_value
argument_list|(
name|select_type
argument_list|,
name|value
argument_list|,
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|->
name|minimum
argument_list|,
name|G_PARAM_SPEC_DOUBLE
argument_list|(
name|pspec
argument_list|)
operator|->
name|maximum
argument_list|,
name|inc
argument_list|,
name|skip_inc
argument_list|,
name|wrap
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|object
argument_list|,
name|property_name
argument_list|,
name|value
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpObject
modifier|*
DECL|function|action_select_object (GimpActionSelectType select_type,GimpContainer * container,GimpObject * current)
name|action_select_object
parameter_list|(
name|GimpActionSelectType
name|select_type
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObject
modifier|*
name|current
parameter_list|)
block|{
name|gint
name|select_index
decl_stmt|;
name|gint
name|n_children
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|current
operator|==
name|NULL
operator|||
name|GIMP_IS_OBJECT
argument_list|(
name|current
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|current
condition|)
return|return
name|NULL
return|;
name|n_children
operator|=
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_children
operator|==
literal|0
condition|)
return|return
name|NULL
return|;
switch|switch
condition|(
name|select_type
condition|)
block|{
case|case
name|GIMP_ACTION_SELECT_FIRST
case|:
name|select_index
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_LAST
case|:
name|select_index
operator|=
name|n_children
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_PREVIOUS
case|:
name|select_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|current
argument_list|)
operator|-
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_NEXT
case|:
name|select_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|current
argument_list|)
operator|+
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_PREVIOUS
case|:
name|select_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|current
argument_list|)
operator|-
literal|10
expr_stmt|;
break|break;
case|case
name|GIMP_ACTION_SELECT_SKIP_NEXT
case|:
name|select_index
operator|=
name|gimp_container_get_child_index
argument_list|(
name|container
argument_list|,
name|current
argument_list|)
operator|+
literal|10
expr_stmt|;
break|break;
default|default:
if|if
condition|(
operator|(
name|gint
operator|)
name|select_type
operator|>=
literal|0
condition|)
name|select_index
operator|=
operator|(
name|gint
operator|)
name|select_type
expr_stmt|;
else|else
name|g_return_val_if_reached
argument_list|(
name|current
argument_list|)
expr_stmt|;
break|break;
block|}
name|select_index
operator|=
name|CLAMP
argument_list|(
name|select_index
argument_list|,
literal|0
argument_list|,
name|n_children
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|select_index
argument_list|)
return|;
block|}
end_function

end_unit

