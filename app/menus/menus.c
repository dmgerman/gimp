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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"menus-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-file.h"
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
file|"widgets/gimpactionfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"dockable-menu.h"
end_include

begin_include
include|#
directive|include
file|"image-menu.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-menus.h"
end_include

begin_include
include|#
directive|include
file|"tool-options-menu.h"
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
name|menus_can_change_accels
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|menus_remove_accels
parameter_list|(
name|gpointer
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|accel_path
parameter_list|,
name|guint
name|accel_key
parameter_list|,
name|GdkModifierType
name|accel_mods
parameter_list|,
name|gboolean
name|changed
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
DECL|variable|menurc_deleted
specifier|static
name|gboolean
name|menurc_deleted
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|menus_init (Gimp * gimp,GimpActionFactory * action_factory)
name|menus_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpActionFactory
modifier|*
name|action_factory
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
name|GIMP_IS_ACTION_FACTORY
argument_list|(
name|action_factory
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|global_menu_factory
operator|==
name|NULL
argument_list|)
expr_stmt|;
comment|/* We need to make sure the property is installed before using it */
name|g_type_class_ref
argument_list|(
name|GTK_TYPE_MENU
argument_list|)
expr_stmt|;
name|menus_can_change_accels
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
name|menus_can_change_accels
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
argument_list|,
name|action_factory
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Image>"
argument_list|,
literal|"file"
argument_list|,
literal|"context"
argument_list|,
literal|"debug"
argument_list|,
literal|"help"
argument_list|,
literal|"edit"
argument_list|,
literal|"select"
argument_list|,
literal|"view"
argument_list|,
literal|"image"
argument_list|,
literal|"drawable"
argument_list|,
literal|"layers"
argument_list|,
literal|"channels"
argument_list|,
literal|"vectors"
argument_list|,
literal|"tools"
argument_list|,
literal|"dialogs"
argument_list|,
literal|"windows"
argument_list|,
literal|"plug-in"
argument_list|,
literal|"filters"
argument_list|,
literal|"quick-mask"
argument_list|,
name|NULL
argument_list|,
literal|"/image-menubar"
argument_list|,
literal|"image-menu.xml"
argument_list|,
name|image_menu_setup
argument_list|,
literal|"/dummy-menubar"
argument_list|,
literal|"image-menu.xml"
argument_list|,
name|image_menu_setup
argument_list|,
literal|"/quick-mask-popup"
argument_list|,
literal|"quick-mask-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Toolbox>"
argument_list|,
literal|"file"
argument_list|,
literal|"context"
argument_list|,
literal|"help"
argument_list|,
literal|"edit"
argument_list|,
literal|"select"
argument_list|,
literal|"view"
argument_list|,
literal|"image"
argument_list|,
literal|"drawable"
argument_list|,
literal|"layers"
argument_list|,
literal|"channels"
argument_list|,
literal|"vectors"
argument_list|,
literal|"tools"
argument_list|,
literal|"windows"
argument_list|,
literal|"dialogs"
argument_list|,
literal|"plug-in"
argument_list|,
literal|"filters"
argument_list|,
literal|"quick-mask"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Dock>"
argument_list|,
literal|"file"
argument_list|,
literal|"context"
argument_list|,
literal|"edit"
argument_list|,
literal|"select"
argument_list|,
literal|"view"
argument_list|,
literal|"image"
argument_list|,
literal|"drawable"
argument_list|,
literal|"layers"
argument_list|,
literal|"channels"
argument_list|,
literal|"vectors"
argument_list|,
literal|"tools"
argument_list|,
literal|"windows"
argument_list|,
literal|"dialogs"
argument_list|,
literal|"plug-in"
argument_list|,
literal|"quick-mask"
argument_list|,
literal|"dock"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Layers>"
argument_list|,
literal|"layers"
argument_list|,
literal|"plug-in"
argument_list|,
literal|"filters"
argument_list|,
name|NULL
argument_list|,
literal|"/layers-popup"
argument_list|,
literal|"layers-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Channels>"
argument_list|,
literal|"channels"
argument_list|,
literal|"plug-in"
argument_list|,
literal|"filters"
argument_list|,
name|NULL
argument_list|,
literal|"/channels-popup"
argument_list|,
literal|"channels-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Vectors>"
argument_list|,
literal|"vectors"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/vectors-popup"
argument_list|,
literal|"vectors-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Colormap>"
argument_list|,
literal|"colormap"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/colormap-popup"
argument_list|,
literal|"colormap-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Dockable>"
argument_list|,
literal|"dockable"
argument_list|,
literal|"dock"
argument_list|,
name|NULL
argument_list|,
literal|"/dockable-popup"
argument_list|,
literal|"dockable-menu.xml"
argument_list|,
name|dockable_menu_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Brushes>"
argument_list|,
literal|"brushes"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/brushes-popup"
argument_list|,
literal|"brushes-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Dynamics>"
argument_list|,
literal|"dynamics"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/dynamics-popup"
argument_list|,
literal|"dynamics-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Patterns>"
argument_list|,
literal|"patterns"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/patterns-popup"
argument_list|,
literal|"patterns-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Gradients>"
argument_list|,
literal|"gradients"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/gradients-popup"
argument_list|,
literal|"gradients-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Palettes>"
argument_list|,
literal|"palettes"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/palettes-popup"
argument_list|,
literal|"palettes-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ToolPresets>"
argument_list|,
literal|"tool-presets"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/tool-presets-popup"
argument_list|,
literal|"tool-presets-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Fonts>"
argument_list|,
literal|"fonts"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/fonts-popup"
argument_list|,
literal|"fonts-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Buffers>"
argument_list|,
literal|"buffers"
argument_list|,
literal|"plug-in"
argument_list|,
name|NULL
argument_list|,
literal|"/buffers-popup"
argument_list|,
literal|"buffers-menu.xml"
argument_list|,
name|plug_in_menus_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Documents>"
argument_list|,
literal|"documents"
argument_list|,
name|NULL
argument_list|,
literal|"/documents-popup"
argument_list|,
literal|"documents-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Templates>"
argument_list|,
literal|"templates"
argument_list|,
name|NULL
argument_list|,
literal|"/templates-popup"
argument_list|,
literal|"templates-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Images>"
argument_list|,
literal|"images"
argument_list|,
name|NULL
argument_list|,
literal|"/images-popup"
argument_list|,
literal|"images-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<BrushEditor>"
argument_list|,
literal|"brush-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/brush-editor-popup"
argument_list|,
literal|"brush-editor-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<DynamicsEditor>"
argument_list|,
literal|"dynamics-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/dynamics-editor-popup"
argument_list|,
literal|"dynamics-editor-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<GradientEditor>"
argument_list|,
literal|"gradient-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/gradient-editor-popup"
argument_list|,
literal|"gradient-editor-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<PaletteEditor>"
argument_list|,
literal|"palette-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/palette-editor-popup"
argument_list|,
literal|"palette-editor-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ToolPresetEditor>"
argument_list|,
literal|"tool-preset-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/tool-preset-editor-popup"
argument_list|,
literal|"tool-preset-editor-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Selection>"
argument_list|,
literal|"select"
argument_list|,
literal|"vectors"
argument_list|,
name|NULL
argument_list|,
literal|"/selection-popup"
argument_list|,
literal|"selection-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<NavigationEditor>"
argument_list|,
literal|"view"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<Undo>"
argument_list|,
literal|"edit"
argument_list|,
name|NULL
argument_list|,
literal|"/undo-popup"
argument_list|,
literal|"undo-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ErrorConsole>"
argument_list|,
literal|"error-console"
argument_list|,
name|NULL
argument_list|,
literal|"/error-console-popup"
argument_list|,
literal|"error-console-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<ToolOptions>"
argument_list|,
literal|"tool-options"
argument_list|,
name|NULL
argument_list|,
literal|"/tool-options-popup"
argument_list|,
literal|"tool-options-menu.xml"
argument_list|,
name|tool_options_menu_setup
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<TextEditor>"
argument_list|,
literal|"text-editor"
argument_list|,
name|NULL
argument_list|,
literal|"/text-editor-toolbar"
argument_list|,
literal|"text-editor-toolbar.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<TextTool>"
argument_list|,
literal|"text-tool"
argument_list|,
name|NULL
argument_list|,
literal|"/text-tool-popup"
argument_list|,
literal|"text-tool-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<CursorInfo>"
argument_list|,
literal|"cursor-info"
argument_list|,
name|NULL
argument_list|,
literal|"/cursor-info-popup"
argument_list|,
literal|"cursor-info-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_menu_factory_manager_register
argument_list|(
name|global_menu_factory
argument_list|,
literal|"<SamplePoints>"
argument_list|,
literal|"sample-points"
argument_list|,
name|NULL
argument_list|,
literal|"/sample-points-popup"
argument_list|,
literal|"sample-points-menu.xml"
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|g_return_if_fail
argument_list|(
name|global_menu_factory
operator|!=
name|NULL
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
name|menus_can_change_accels
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
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
DECL|function|menus_save (Gimp * gimp,gboolean always_save)
name|menus_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|always_save
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
if|if
condition|(
name|menurc_deleted
operator|&&
operator|!
name|always_save
condition|)
return|return;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"menurc"
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"Writing '%s'\n"
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
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
name|menurc_deleted
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|menus_clear (Gimp * gimp,GError ** error)
name|menus_clear
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|GFile
modifier|*
name|source
decl_stmt|;
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"menurc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|source
operator|=
name|gimp_sysconf_directory_file
argument_list|(
literal|"menurc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_file_copy
argument_list|(
name|source
argument_list|,
name|file
argument_list|,
name|G_FILE_COPY_OVERWRITE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|menurc_deleted
operator|=
name|TRUE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|g_file_delete
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
operator|&&
name|my_error
operator|->
name|code
operator|!=
name|G_IO_ERROR_NOT_FOUND
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|my_error
operator|->
name|domain
argument_list|,
name|my_error
operator|->
name|code
argument_list|,
name|_
argument_list|(
literal|"Deleting \"%s\" failed: %s"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|,
name|my_error
operator|->
name|message
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|menurc_deleted
operator|=
name|TRUE
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|my_error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|source
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_function
name|void
DECL|function|menus_remove (Gimp * gimp)
name|menus_remove
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
name|gtk_accel_map_foreach
argument_list|(
name|gimp
argument_list|,
name|menus_remove_accels
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
DECL|function|menus_can_change_accels (GimpGuiConfig * config)
name|menus_can_change_accels
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

begin_function
specifier|static
name|void
DECL|function|menus_remove_accels (gpointer data,const gchar * accel_path,guint accel_key,GdkModifierType accel_mods,gboolean changed)
name|menus_remove_accels
parameter_list|(
name|gpointer
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|accel_path
parameter_list|,
name|guint
name|accel_key
parameter_list|,
name|GdkModifierType
name|accel_mods
parameter_list|,
name|gboolean
name|changed
parameter_list|)
block|{
name|gtk_accel_map_change_entry
argument_list|(
name|accel_path
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

