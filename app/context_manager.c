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
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"tools/paint_options.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gui/brush-select.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpipe.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdatalist.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimppalette.h"
end_include

begin_include
include|#
directive|include
file|"gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_define
DECL|macro|PAINT_OPTIONS_MASK
define|#
directive|define
name|PAINT_OPTIONS_MASK
value|GIMP_CONTEXT_OPACITY_MASK | \                            GIMP_CONTEXT_PAINT_MODE_MASK
end_define

begin_comment
comment|/* HACK: provide prototype without tools/tools.h */
end_comment

begin_function_decl
specifier|extern
name|void
name|register_tools
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  *  the list of all images  */
end_comment

begin_decl_stmt
DECL|variable|image_context
name|GimpContainer
modifier|*
name|image_context
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  the global data lists  */
end_comment

begin_decl_stmt
DECL|variable|global_brush_factory
name|GimpDataFactory
modifier|*
name|global_brush_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_pattern_factory
name|GimpDataFactory
modifier|*
name|global_pattern_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_gradient_factory
name|GimpDataFactory
modifier|*
name|global_gradient_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|global_palette_factory
name|GimpDataFactory
modifier|*
name|global_palette_factory
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  *  the global tool context  */
end_comment

begin_decl_stmt
DECL|variable|global_tool_context
name|GimpContext
modifier|*
name|global_tool_context
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|context_manager_display_changed (GimpContext * context,GDisplay * display,gpointer data)
name|context_manager_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GDisplay
modifier|*
name|display
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gdisplay_set_menu_sensitivity
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|context_manager_tool_changed (GimpContext * user_context,GimpToolInfo * tool_info,gpointer data)
name|context_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
comment|/* FIXME: gimp_busy HACK */
if|if
condition|(
name|gimp_busy
condition|)
block|{
comment|/*  there may be contexts waiting for the user_context's "tool_changed"        *  signal, so stop emitting it.        */
name|gtk_signal_emit_stop_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|user_context
argument_list|)
argument_list|,
literal|"tool_changed"
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT
argument_list|(
name|active_tool
argument_list|)
operator|->
name|klass
operator|->
name|type
operator|!=
name|tool_info
operator|->
name|tool_type
condition|)
block|{
name|gtk_signal_handler_block_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|user_context
argument_list|)
argument_list|,
name|context_manager_tool_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  explicitly set the current tool  */
name|gimp_context_set_tool
argument_list|(
name|user_context
argument_list|,
name|tool_manager_get_info_by_tool
argument_list|(
name|active_tool
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_func
argument_list|(
name|GTK_OBJECT
argument_list|(
name|user_context
argument_list|)
argument_list|,
name|context_manager_tool_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|GimpTool
modifier|*
name|new_tool
init|=
name|NULL
decl_stmt|;
name|GimpContext
modifier|*
name|tool_context
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|tool_type
operator|!=
name|GTK_TYPE_NONE
condition|)
block|{
name|new_tool
operator|=
name|gtk_type_new
argument_list|(
name|tool_info
operator|->
name|tool_type
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s(): tool_info contains no valid GtkType"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|global_paint_options
condition|)
block|{
if|if
condition|(
name|active_tool
operator|&&
operator|(
name|tool_context
operator|=
name|tool_manager_get_info_by_tool
argument_list|(
name|active_tool
argument_list|)
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_context_unset_parent
argument_list|(
name|tool_context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|tool_context
operator|=
name|tool_info
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_context_copy_args
argument_list|(
name|tool_context
argument_list|,
name|user_context
argument_list|,
name|PAINT_OPTIONS_MASK
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|tool_context
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
block|}
name|tool_manager_select_tool
argument_list|(
name|new_tool
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|context_manager_init (void)
name|context_manager_init
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpContext
modifier|*
name|standard_context
decl_stmt|;
name|GimpContext
modifier|*
name|default_context
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|GimpContext
modifier|*
name|tool_context
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|brush_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_brush_load
block|,
name|GIMP_BRUSH_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_load
block|,
name|GIMP_BRUSH_PIXMAP_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_generated_load
block|,
name|GIMP_BRUSH_GENERATED_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_brush_pipe_load
block|,
name|GIMP_BRUSH_PIPE_FILE_EXTENSION
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_brush_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|brush_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|brush_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|pattern_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_pattern_load
block|,
name|GIMP_PATTERN_FILE_EXTENSION
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_pattern_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|pattern_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|pattern_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|gradient_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_gradient_load
block|,
name|GIMP_GRADIENT_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_gradient_load
block|,
name|NULL
comment|/* legacy loader */
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_gradient_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|gradient_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|gradient_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
specifier|static
specifier|const
name|GimpDataFactoryLoaderEntry
name|palette_loader_entries
index|[]
init|=
block|{
block|{
name|gimp_palette_load
block|,
name|GIMP_PALETTE_FILE_EXTENSION
block|}
block|,
block|{
name|gimp_palette_load
block|,
name|NULL
comment|/* legacy loader */
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|n_palette_loader_entries
init|=
operator|(
sizeof|sizeof
argument_list|(
name|palette_loader_entries
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|palette_loader_entries
index|[
literal|0
index|]
argument_list|)
operator|)
decl_stmt|;
comment|/* Create the context of all existing images */
name|image_context
operator|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_CONTAINER_POLICY_WEAK
argument_list|)
expr_stmt|;
comment|/* Create the global data factories */
name|global_brush_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|brush_path
argument_list|,
name|brush_loader_entries
argument_list|,
name|n_brush_loader_entries
argument_list|,
name|gimp_brush_new
argument_list|,
name|gimp_brush_get_standard
argument_list|)
expr_stmt|;
name|global_pattern_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_PATTERN
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|pattern_path
argument_list|,
name|pattern_loader_entries
argument_list|,
name|n_pattern_loader_entries
argument_list|,
name|gimp_pattern_new
argument_list|,
name|gimp_pattern_get_standard
argument_list|)
expr_stmt|;
name|global_gradient_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_GRADIENT
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|gradient_path
argument_list|,
name|gradient_loader_entries
argument_list|,
name|n_gradient_loader_entries
argument_list|,
name|gimp_gradient_new
argument_list|,
name|gimp_gradient_get_standard
argument_list|)
expr_stmt|;
name|global_palette_factory
operator|=
name|gimp_data_factory_new
argument_list|(
name|GIMP_TYPE_PALETTE
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
operator|&
name|palette_path
argument_list|,
name|palette_loader_entries
argument_list|,
name|n_palette_loader_entries
argument_list|,
name|gimp_palette_new
argument_list|,
name|gimp_palette_get_standard
argument_list|)
expr_stmt|;
comment|/*  Create the global tool info list  */
name|tool_manager_init
argument_list|()
expr_stmt|;
comment|/*  Implicitly create the standard context  */
name|standard_context
operator|=
name|gimp_context_get_standard
argument_list|()
expr_stmt|;
comment|/*  TODO: load from disk  */
name|default_context
operator|=
name|gimp_context_new
argument_list|(
literal|"Default"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_default
argument_list|(
name|default_context
argument_list|)
expr_stmt|;
comment|/*  Initialize the user context with the default context's values  */
name|user_context
operator|=
name|gimp_context_new
argument_list|(
literal|"User"
argument_list|,
name|default_context
argument_list|)
expr_stmt|;
name|gimp_context_set_user
argument_list|(
name|user_context
argument_list|)
expr_stmt|;
comment|/*  Update the tear-off menus  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|user_context
argument_list|)
argument_list|,
literal|"display_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|context_manager_display_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Update the tool system  */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|user_context
argument_list|)
argument_list|,
literal|"tool_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|context_manager_tool_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  Make the user contect the currently active context  */
name|gimp_context_set_current
argument_list|(
name|user_context
argument_list|)
expr_stmt|;
comment|/*  Create a context to store the paint options of the    *  global paint options mode    */
name|global_tool_context
operator|=
name|gimp_context_new
argument_list|(
literal|"Global Tool Context"
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
comment|/*  TODO: add foreground, background, brush, pattern, gradient  */
name|gimp_context_define_args
argument_list|(
name|global_tool_context
argument_list|,
name|PAINT_OPTIONS_MASK
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* register internal tools */
name|register_tools
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|global_paint_options
operator|&&
name|active_tool
operator|&&
operator|(
name|tool_context
operator|=
name|tool_manager_get_info_by_tool
argument_list|(
name|active_tool
argument_list|)
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_context_set_parent
argument_list|(
name|tool_context
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|global_paint_options
condition|)
block|{
name|gimp_context_set_parent
argument_list|(
name|global_tool_context
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
name|gimp_container_thaw
argument_list|(
name|global_tool_info_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|context_manager_free (void)
name|context_manager_free
parameter_list|(
name|void
parameter_list|)
block|{
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|global_tool_context
argument_list|)
argument_list|)
expr_stmt|;
name|global_tool_context
operator|=
name|NULL
expr_stmt|;
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_user
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_set_current
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
comment|/*  TODO: Save to disk before destroying  */
name|gtk_object_unref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp_context_get_default
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_context_set_default
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_free
argument_list|(
name|global_brush_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_free
argument_list|(
name|global_pattern_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_free
argument_list|(
name|global_gradient_factory
argument_list|)
expr_stmt|;
name|gimp_data_factory_data_free
argument_list|(
name|global_palette_factory
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|context_manager_set_global_paint_options (gboolean global)
name|context_manager_set_global_paint_options
parameter_list|(
name|gboolean
name|global
parameter_list|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
if|if
condition|(
name|global
operator|==
name|global_paint_options
condition|)
return|return;
name|paint_options_set_global
argument_list|(
name|global
argument_list|)
expr_stmt|;
comment|/*  NULL is the main brush selection  */
name|brush_select_show_paint_options
argument_list|(
name|NULL
argument_list|,
name|global
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_context_get_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
if|if
condition|(
name|global
condition|)
block|{
if|if
condition|(
name|tool_info
operator|&&
operator|(
name|context
operator|=
name|tool_info
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_context_unset_parent
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|gimp_context_copy_args
argument_list|(
name|global_tool_context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
name|PAINT_OPTIONS_MASK
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|global_tool_context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_unset_parent
argument_list|(
name|global_tool_context
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_info
operator|&&
operator|(
name|context
operator|=
name|tool_info
operator|->
name|context
operator|)
condition|)
block|{
name|gimp_context_copy_args
argument_list|(
name|context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
name|GIMP_CONTEXT_PAINT_ARGS_MASK
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

