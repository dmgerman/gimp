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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
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
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"brushes-menu.h"
end_include

begin_include
include|#
directive|include
file|"buffers-menu.h"
end_include

begin_include
include|#
directive|include
file|"channels-menu.h"
end_include

begin_include
include|#
directive|include
file|"colormap-editor-menu.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-menu.h"
end_include

begin_include
include|#
directive|include
file|"documents-menu.h"
end_include

begin_include
include|#
directive|include
file|"error-console-menu.h"
end_include

begin_include
include|#
directive|include
file|"file-open-menu.h"
end_include

begin_include
include|#
directive|include
file|"file-save-menu.h"
end_include

begin_include
include|#
directive|include
file|"file-commands.h"
end_include

begin_include
include|#
directive|include
file|"fonts-menu.h"
end_include

begin_include
include|#
directive|include
file|"gradient-editor-menu.h"
end_include

begin_include
include|#
directive|include
file|"gradients-menu.h"
end_include

begin_include
include|#
directive|include
file|"image-menu.h"
end_include

begin_include
include|#
directive|include
file|"images-menu.h"
end_include

begin_include
include|#
directive|include
file|"layers-menu.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"palette-editor-menu.h"
end_include

begin_include
include|#
directive|include
file|"palettes-menu.h"
end_include

begin_include
include|#
directive|include
file|"patterns-menu.h"
end_include

begin_include
include|#
directive|include
file|"qmask-menu.h"
end_include

begin_include
include|#
directive|include
file|"templates-menu.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-menu.h"
end_include

begin_include
include|#
directive|include
file|"toolbox-menu.h"
end_include

begin_include
include|#
directive|include
file|"vectors-menu.h"
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
name|menus_last_opened_update
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|menus_last_opened_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused1
parameter_list|,
name|gint
name|unused2
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|menu_can_change_accels
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  global variables  */
end_comment

begin_decl_stmt
DECL|variable|global_menu_factory
name|GimpMenuFactory
modifier|*
name|global_menu_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|menus_initialized
specifier|static
name|gboolean
name|menus_initialized
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|menus_init (Gimp * gimp)
name|menus_init
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
name|menus_initialized
operator|==
name|FALSE
argument_list|)
expr_stmt|;
name|menus_initialized
operator|=
name|TRUE
expr_stmt|;
comment|/* We need to make sure the property is installed before using it */
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_MENU
argument_list|)
expr_stmt|;
name|menu_can_change_accels
argument_list|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"notify::can-change-accels"
argument_list|,
name|G_CALLBACK
argument_list|(
name|menu_can_change_accels
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|global_menu_factory
operator|=
name|gimp_menu_factory_new
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Toolbox>"
argument_list|,
name|_
argument_list|(
literal|"Toolbox Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_TOOLBOX
argument_list|,
name|toolbox_menu_setup
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|n_toolbox_menu_entries
argument_list|,
name|toolbox_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Image>"
argument_list|,
name|_
argument_list|(
literal|"Image Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_IMAGE_WINDOW
argument_list|,
name|image_menu_setup
argument_list|,
name|image_menu_update
argument_list|,
name|FALSE
argument_list|,
name|n_image_menu_entries
argument_list|,
name|image_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Load>"
argument_list|,
name|_
argument_list|(
literal|"Open Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_FILE_OPEN
argument_list|,
name|file_open_menu_setup
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|n_file_open_menu_entries
argument_list|,
name|file_open_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Save>"
argument_list|,
name|_
argument_list|(
literal|"Save Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_FILE_SAVE
argument_list|,
name|file_save_menu_setup
argument_list|,
name|file_save_menu_update
argument_list|,
name|FALSE
argument_list|,
name|n_file_save_menu_entries
argument_list|,
name|file_save_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Layers>"
argument_list|,
name|_
argument_list|(
literal|"Layers Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_LAYER_DIALOG
argument_list|,
name|NULL
argument_list|,
name|layers_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_layers_menu_entries
argument_list|,
name|layers_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Channels>"
argument_list|,
name|_
argument_list|(
literal|"Channels Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_CHANNEL_DIALOG
argument_list|,
name|NULL
argument_list|,
name|channels_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_channels_menu_entries
argument_list|,
name|channels_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Vectors>"
argument_list|,
name|_
argument_list|(
literal|"Paths Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_PATH_DIALOG
argument_list|,
name|NULL
argument_list|,
name|vectors_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_vectors_menu_entries
argument_list|,
name|vectors_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Dialogs>"
argument_list|,
name|_
argument_list|(
literal|"Dialogs Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_DOCK
argument_list|,
name|NULL
argument_list|,
name|dialogs_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_dialogs_menu_entries
argument_list|,
name|dialogs_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Brushes>"
argument_list|,
name|_
argument_list|(
literal|"Brushes Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_BRUSH_DIALOG
argument_list|,
name|NULL
argument_list|,
name|brushes_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_brushes_menu_entries
argument_list|,
name|brushes_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Patterns>"
argument_list|,
name|_
argument_list|(
literal|"Patterns Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_PATTERN_DIALOG
argument_list|,
name|NULL
argument_list|,
name|patterns_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_patterns_menu_entries
argument_list|,
name|patterns_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Gradients>"
argument_list|,
name|_
argument_list|(
literal|"Gradients Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_GRADIENT_DIALOG
argument_list|,
name|NULL
argument_list|,
name|gradients_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_gradients_menu_entries
argument_list|,
name|gradients_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Palettes>"
argument_list|,
name|_
argument_list|(
literal|"Palettes Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_PALETTE_DIALOG
argument_list|,
name|NULL
argument_list|,
name|palettes_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_palettes_menu_entries
argument_list|,
name|palettes_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Fonts>"
argument_list|,
name|_
argument_list|(
literal|"Fonts Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_FONT_DIALOG
argument_list|,
name|NULL
argument_list|,
name|fonts_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_fonts_menu_entries
argument_list|,
name|fonts_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Buffers>"
argument_list|,
name|_
argument_list|(
literal|"Buffers Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_BUFFER_DIALOG
argument_list|,
name|NULL
argument_list|,
name|buffers_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_buffers_menu_entries
argument_list|,
name|buffers_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Documents>"
argument_list|,
name|_
argument_list|(
literal|"Documents Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_DOCUMENT_DIALOG
argument_list|,
name|NULL
argument_list|,
name|documents_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_documents_menu_entries
argument_list|,
name|documents_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Templates>"
argument_list|,
name|_
argument_list|(
literal|"Templates Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_TEMPLATE_DIALOG
argument_list|,
name|NULL
argument_list|,
name|templates_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_templates_menu_entries
argument_list|,
name|templates_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Images>"
argument_list|,
name|_
argument_list|(
literal|"Images Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_IMAGE_DIALOG
argument_list|,
name|NULL
argument_list|,
name|images_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_images_menu_entries
argument_list|,
name|images_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<GradientEditor>"
argument_list|,
name|_
argument_list|(
literal|"Gradient Editor Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_GRADIENT_EDITOR_DIALOG
argument_list|,
name|NULL
argument_list|,
name|gradient_editor_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_gradient_editor_menu_entries
argument_list|,
name|gradient_editor_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<PaletteEditor>"
argument_list|,
name|_
argument_list|(
literal|"Palette Editor Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_PALETTE_EDITOR_DIALOG
argument_list|,
name|NULL
argument_list|,
name|palette_editor_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_palette_editor_menu_entries
argument_list|,
name|palette_editor_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ColormapEditor>"
argument_list|,
name|_
argument_list|(
literal|"Indexed Palette Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_INDEXED_PALETTE_DIALOG
argument_list|,
name|NULL
argument_list|,
name|colormap_editor_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_colormap_editor_menu_entries
argument_list|,
name|colormap_editor_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<QMask>"
argument_list|,
name|_
argument_list|(
literal|"QuickMask Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_QMASK
argument_list|,
name|NULL
argument_list|,
name|qmask_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_qmask_menu_entries
argument_list|,
name|qmask_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ErrorConsole>"
argument_list|,
name|_
argument_list|(
literal|"Error Console Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_ERRORS_DIALOG
argument_list|,
name|NULL
argument_list|,
name|error_console_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_error_console_menu_entries
argument_list|,
name|error_console_menu_entries
argument_list|)
expr_stmt|;
name|gimp_menu_factory_menu_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ToolOptions>"
argument_list|,
name|_
argument_list|(
literal|"Tool Options Menu"
argument_list|)
argument_list|,
name|GIMP_HELP_TOOL_OPTIONS_DIALOG
argument_list|,
name|tool_options_menu_setup
argument_list|,
name|tool_options_menu_update
argument_list|,
name|TRUE
argument_list|,
name|n_tool_options_menu_entries
argument_list|,
name|tool_options_menu_entries
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_exit (Gimp * gimp)
name|menus_exit
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
name|g_object_unref
argument_list|(
name|global_menu_factory
argument_list|)
expr_stmt|;
name|global_menu_factory
operator|=
name|NULL
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
name|menu_can_change_accels
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_restore (Gimp * gimp)
name|menus_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"menurc"
argument_list|)
expr_stmt|;
name|gtk_accel_map_load
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_save (Gimp * gimp)
name|menus_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"menurc"
argument_list|)
expr_stmt|;
name|gtk_accel_map_save
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_clear (Gimp * gimp)
name|menus_clear
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
name|g_print
argument_list|(
literal|"TODO: implement menus_clear()\n"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_last_opened_add (GimpItemFactory * item_factory)
name|menus_last_opened_add
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|GimpItemFactoryEntry
modifier|*
name|last_opened_entries
decl_stmt|;
name|gint
name|n_last_opened_entries
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|)
expr_stmt|;
name|n_last_opened_entries
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_opened_size
expr_stmt|;
name|last_opened_entries
operator|=
name|g_new
argument_list|(
name|GimpItemFactoryEntry
argument_list|,
name|n_last_opened_entries
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
name|n_last_opened_entries
condition|;
name|i
operator|++
control|)
block|{
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|path
operator|=
name|g_strdup_printf
argument_list|(
literal|"/File/Open Recent/%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|accelerator
operator|=
name|g_strdup_printf
argument_list|(
literal|"<control>%d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|i
operator|==
literal|9
condition|)
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|accelerator
operator|=
literal|"<control>0"
expr_stmt|;
else|else
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|accelerator
operator|=
literal|""
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|callback
operator|=
name|file_last_opened_cmd_callback
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|callback_action
operator|=
name|i
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|item_type
operator|=
literal|"<StockItem>"
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|extra_data
operator|=
name|GTK_STOCK_OPEN
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|quark_string
operator|=
name|NULL
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|help_id
operator|=
name|GIMP_HELP_FILE_OPEN_RECENT
expr_stmt|;
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|description
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_item_factory_create_items
argument_list|(
name|item_factory
argument_list|,
name|n_last_opened_entries
argument_list|,
name|last_opened_entries
argument_list|,
name|item_factory
operator|->
name|gimp
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_sensitive
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/File/Open Recent/(None)"
argument_list|,
name|FALSE
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
name|n_last_opened_entries
condition|;
name|i
operator|++
control|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|widget
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
name|gtk_menu_reorder_child
argument_list|(
name|GTK_MENU
argument_list|(
name|widget
operator|->
name|parent
argument_list|)
argument_list|,
name|widget
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_visible
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|path
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|path
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
literal|9
condition|)
name|g_free
argument_list|(
name|last_opened_entries
index|[
name|i
index|]
operator|.
name|entry
operator|.
name|accelerator
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|last_opened_entries
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"add"
argument_list|,
name|G_CALLBACK
argument_list|(
name|menus_last_opened_update
argument_list|)
argument_list|,
name|item_factory
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|menus_last_opened_update
argument_list|)
argument_list|,
name|item_factory
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|documents
argument_list|,
literal|"reorder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|menus_last_opened_reorder
argument_list|)
argument_list|,
name|item_factory
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|menus_last_opened_update
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|documents
argument_list|,
name|NULL
argument_list|,
name|item_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|menus_filters_subdirs_to_top (GtkMenu * menu)
name|menus_filters_subdirs_to_top
parameter_list|(
name|GtkMenu
modifier|*
name|menu
parameter_list|)
block|{
name|GtkMenuItem
modifier|*
name|menu_item
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gboolean
name|submenus_passed
init|=
name|FALSE
decl_stmt|;
name|gint
name|pos
decl_stmt|;
name|gint
name|items
decl_stmt|;
name|pos
operator|=
literal|1
expr_stmt|;
name|items
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
operator|->
name|children
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
name|menu_item
operator|=
name|GTK_MENU_ITEM
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|items
operator|++
expr_stmt|;
if|if
condition|(
name|menu_item
operator|->
name|submenu
condition|)
block|{
if|if
condition|(
name|submenus_passed
condition|)
block|{
name|menus_filters_subdirs_to_top
argument_list|(
name|GTK_MENU
argument_list|(
name|menu_item
operator|->
name|submenu
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_menu_reorder_child
argument_list|(
name|menu
argument_list|,
name|GTK_WIDGET
argument_list|(
name|menu_item
argument_list|)
argument_list|,
name|pos
operator|++
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|submenus_passed
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
if|if
condition|(
name|pos
operator|>
literal|1
operator|&&
name|items
operator|>
name|pos
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|separator
operator|=
name|gtk_menu_item_new
argument_list|()
expr_stmt|;
name|gtk_menu_shell_insert
argument_list|(
name|GTK_MENU_SHELL
argument_list|(
name|menu
argument_list|)
argument_list|,
name|separator
argument_list|,
name|pos
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|separator
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
DECL|function|menus_last_opened_update (GimpContainer * container,GimpImagefile * unused,GimpItemFactory * item_factory)
name|menus_last_opened_update
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|gint
name|num_documents
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|n
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|item_factory
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|last_opened_size
decl_stmt|;
name|num_documents
operator|=
name|gimp_container_num_children
argument_list|(
name|container
argument_list|)
expr_stmt|;
name|gimp_item_factory_set_visible
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
literal|"/File/Open Recent/(None)"
argument_list|,
name|num_documents
operator|==
literal|0
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
name|n
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|path_str
decl_stmt|;
name|path_str
operator|=
name|g_strdup_printf
argument_list|(
literal|"/File/Open Recent/%02d"
argument_list|,
name|i
operator|+
literal|1
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_item_factory_get_widget
argument_list|(
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|,
name|path_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|<
name|num_documents
condition|)
block|{
name|GimpImagefile
modifier|*
name|imagefile
decl_stmt|;
name|imagefile
operator|=
operator|(
name|GimpImagefile
operator|*
operator|)
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|)
operator|!=
operator|(
name|gpointer
operator|)
name|imagefile
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|file_utils_uri_to_utf8_filename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|widget
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|widget
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|,
name|imagefile
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-imagefile"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|widget
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menus_last_opened_reorder (GimpContainer * container,GimpImagefile * unused1,gint unused2,GimpItemFactory * item_factory)
name|menus_last_opened_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpImagefile
modifier|*
name|unused1
parameter_list|,
name|gint
name|unused2
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|menus_last_opened_update
argument_list|(
name|container
argument_list|,
name|unused1
argument_list|,
name|item_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|menu_can_change_accels (GimpGuiConfig * config)
name|menu_can_change_accels
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|gtk_settings_get_for_screen
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|)
argument_list|,
literal|"gtk-can-change-accels"
argument_list|,
name|config
operator|->
name|can_change_accels
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

