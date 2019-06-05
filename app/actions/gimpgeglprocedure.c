begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpgeglprocedure.c  * Copyright (C) 2016-2018 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
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
file|"operations/gimp-operation-config.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-memsize.h"
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
file|"core/gimpdrawable-operation.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayermask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpoperationtool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpgeglprocedure.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_gegl_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint64
name|gimp_gegl_procedure_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_gegl_procedure_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_gegl_procedure_get_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_gegl_procedure_get_menu_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
specifier|const
name|gchar
modifier|*
name|gimp_gegl_procedure_get_help_id
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_gegl_procedure_get_sensitive
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|gimp_gegl_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_gegl_procedure_execute_async
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpGeglProcedure,gimp_gegl_procedure,GIMP_TYPE_PROCEDURE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpGeglProcedure
argument_list|,
argument|gimp_gegl_procedure
argument_list|,
argument|GIMP_TYPE_PROCEDURE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_gegl_procedure_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_gegl_procedure_class_init
parameter_list|(
name|GimpGeglProcedureClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
init|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
init|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpProcedureClass
modifier|*
name|proc_class
init|=
name|GIMP_PROCEDURE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_gegl_procedure_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_gegl_procedure_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_icon_name
operator|=
literal|"gimp-gegl"
expr_stmt|;
name|viewable_class
operator|->
name|get_description
operator|=
name|gimp_gegl_procedure_get_description
expr_stmt|;
name|proc_class
operator|->
name|get_label
operator|=
name|gimp_gegl_procedure_get_label
expr_stmt|;
name|proc_class
operator|->
name|get_menu_label
operator|=
name|gimp_gegl_procedure_get_menu_label
expr_stmt|;
name|proc_class
operator|->
name|get_help_id
operator|=
name|gimp_gegl_procedure_get_help_id
expr_stmt|;
name|proc_class
operator|->
name|get_sensitive
operator|=
name|gimp_gegl_procedure_get_sensitive
expr_stmt|;
name|proc_class
operator|->
name|execute
operator|=
name|gimp_gegl_procedure_execute
expr_stmt|;
name|proc_class
operator|->
name|execute_async
operator|=
name|gimp_gegl_procedure_execute_async
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_procedure_init (GimpGeglProcedure * proc)
name|gimp_gegl_procedure_init
parameter_list|(
name|GimpGeglProcedure
modifier|*
name|proc
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_procedure_finalize (GObject * object)
name|gimp_gegl_procedure_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGeglProcedure
modifier|*
name|proc
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|proc
operator|->
name|default_settings
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|proc
operator|->
name|menu_label
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|proc
operator|->
name|label
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|proc
operator|->
name|help_id
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_gegl_procedure_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_gegl_procedure_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
block|{
name|GimpGeglProcedure
modifier|*
name|proc
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|proc
operator|->
name|menu_label
argument_list|)
expr_stmt|;
name|memsize
operator|+=
name|gimp_string_get_memsize
argument_list|(
name|proc
operator|->
name|label
argument_list|)
expr_stmt|;
return|return
name|memsize
operator|+
name|GIMP_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
name|gui_size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_gegl_procedure_get_description (GimpViewable * viewable,gchar ** tooltip)
name|gimp_gegl_procedure_get_description
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|GIMP_PROCEDURE
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|tooltip
condition|)
operator|*
name|tooltip
operator|=
name|g_strdup
argument_list|(
name|gimp_procedure_get_blurb
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_gegl_procedure_get_label (GimpProcedure * procedure)
name|gimp_gegl_procedure_get_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpGeglProcedure
modifier|*
name|proc
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|ellipsis
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
if|if
condition|(
name|proc
operator|->
name|label
condition|)
return|return
name|proc
operator|->
name|label
return|;
name|label
operator|=
name|gimp_strip_uline
argument_list|(
name|gimp_procedure_get_menu_label
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
name|ellipsis
operator|=
name|strstr
argument_list|(
name|label
argument_list|,
literal|"..."
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ellipsis
condition|)
name|ellipsis
operator|=
name|strstr
argument_list|(
name|label
argument_list|,
literal|"\342\200\246"
comment|/* U+2026 HORIZONTAL ELLIPSIS */
argument_list|)
expr_stmt|;
if|if
condition|(
name|ellipsis
operator|&&
name|ellipsis
operator|==
operator|(
name|label
operator|+
name|strlen
argument_list|(
name|label
argument_list|)
operator|-
literal|3
operator|)
condition|)
operator|*
name|ellipsis
operator|=
literal|'\0'
expr_stmt|;
name|proc
operator|->
name|label
operator|=
name|label
expr_stmt|;
return|return
name|proc
operator|->
name|label
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_gegl_procedure_get_menu_label (GimpProcedure * procedure)
name|gimp_gegl_procedure_get_menu_label
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpGeglProcedure
modifier|*
name|proc
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
if|if
condition|(
name|proc
operator|->
name|menu_label
condition|)
return|return
name|proc
operator|->
name|menu_label
return|;
return|return
name|GIMP_PROCEDURE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|get_menu_label
argument_list|(
name|procedure
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
specifier|const
name|gchar
modifier|*
DECL|function|gimp_gegl_procedure_get_help_id (GimpProcedure * procedure)
name|gimp_gegl_procedure_get_help_id
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|)
block|{
name|GimpGeglProcedure
modifier|*
name|proc
init|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
decl_stmt|;
return|return
name|proc
operator|->
name|help_id
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_gegl_procedure_get_sensitive (GimpProcedure * procedure,GimpObject * object,const gchar ** tooltip)
name|gimp_gegl_procedure_get_sensitive
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|tooltip
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|GIMP_DRAWABLE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gboolean
name|sensitive
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|drawable
condition|)
block|{
name|GimpItem
modifier|*
name|item
decl_stmt|;
if|if
condition|(
name|GIMP_IS_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
condition|)
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|gimp_layer_mask_get_layer
argument_list|(
name|GIMP_LAYER_MASK
argument_list|(
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|sensitive
operator|=
operator|!
name|gimp_item_is_content_locked
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_viewable_get_children
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
name|sensitive
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|sensitive
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|gimp_gegl_procedure_execute (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpValueArray * args,GError ** error)
name|gimp_gegl_procedure_execute
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GObject
modifier|*
name|config
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_value_get_drawable
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|config
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|node
operator|=
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
name|procedure
operator|->
name|original_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
condition|)
name|gimp_operation_config_sync_node
argument_list|(
name|config
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|gimp_drawable_apply_operation
argument_list|(
name|drawable
argument_list|,
name|progress
argument_list|,
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|node
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|node
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_gegl_procedure_execute_async (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,GimpValueArray * args,GimpObject * display)
name|gimp_gegl_procedure_execute_async
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
block|{
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpObject
modifier|*
name|settings
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|tool_name
decl_stmt|;
name|run_mode
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|settings
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|settings
operator|&&
operator|(
name|run_mode
operator|!=
name|GIMP_RUN_INTERACTIVE
operator|||
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|filter_tool_use_last_settings
operator|)
condition|)
block|{
comment|/*  if we didn't get settings passed, get the last used settings  */
name|GType
name|config_type
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|config_type
operator|=
name|G_VALUE_TYPE
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_operation_config_get_container
argument_list|(
name|gimp
argument_list|,
name|config_type
argument_list|,
operator|(
name|GCompareFunc
operator|)
name|gimp_settings_compare
argument_list|)
expr_stmt|;
name|settings
operator|=
name|gimp_container_get_child_by_index
argument_list|(
name|container
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  only use the settings if they are automatically created        *  "last used" values, not if they were saved explicitly and        *  have a zero timestamp; and if they are not a separator.        */
if|if
condition|(
name|settings
operator|&&
operator|(
name|GIMP_SETTINGS
argument_list|(
name|settings
argument_list|)
operator|->
name|time
operator|==
literal|0
operator|||
operator|!
name|gimp_object_get_name
argument_list|(
name|settings
argument_list|)
operator|)
condition|)
block|{
name|settings
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
operator|||
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
block|{
if|if
condition|(
name|settings
operator|||
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|g_value_set_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|settings
argument_list|)
expr_stmt|;
name|gimp_procedure_execute
argument_list|(
name|procedure
argument_list|,
name|gimp
argument_list|,
name|context
argument_list|,
name|progress
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|G_OBJECT
argument_list|(
name|progress
argument_list|)
argument_list|,
name|GIMP_MESSAGE_WARNING
argument_list|,
name|_
argument_list|(
literal|"There are no last settings for '%s', "
literal|"showing the filter dialog instead."
argument_list|)
argument_list|,
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|,
literal|"gimp:brightness-contrast"
argument_list|)
condition|)
block|{
name|tool_name
operator|=
literal|"gimp-brightness-contrast-tool"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|,
literal|"gimp:curves"
argument_list|)
condition|)
block|{
name|tool_name
operator|=
literal|"gimp-curves-tool"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|,
literal|"gimp:levels"
argument_list|)
condition|)
block|{
name|tool_name
operator|=
literal|"gimp-levels-tool"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|,
literal|"gimp:threshold"
argument_list|)
condition|)
block|{
name|tool_name
operator|=
literal|"gimp-threshold-tool"
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|procedure
operator|->
name|original_name
argument_list|,
literal|"gimp:offset"
argument_list|)
condition|)
block|{
name|tool_name
operator|=
literal|"gimp-offset-tool"
expr_stmt|;
block|}
else|else
block|{
name|tool_name
operator|=
literal|"gimp-operation-tool"
expr_stmt|;
block|}
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
comment|/*  do not use the passed context because we need to set the active    *  tool on the global user context    */
name|context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|gimp_object_get_name
argument_list|(
name|active_tool
operator|->
name|tool_info
argument_list|)
argument_list|,
name|tool_name
argument_list|)
condition|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|gimp_get_tool_info
argument_list|(
name|gimp
argument_list|,
name|tool_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|GIMP_IS_TOOL_INFO
argument_list|(
name|tool_info
argument_list|)
condition|)
name|gimp_context_set_tool
argument_list|(
name|context
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_context_tool_changed
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|gimp_object_get_name
argument_list|(
name|active_tool
operator|->
name|tool_info
argument_list|)
argument_list|,
name|tool_name
argument_list|)
condition|)
block|{
comment|/*  Remember the procedure that created this tool, because        *  we can't just switch to an operation tool using        *  gimp_context_set_tool(), we also have to go through the        *  initialization code below, otherwise we end up with a        *  dummy tool that does nothing. See bug #776370.        */
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|active_tool
argument_list|)
argument_list|,
literal|"gimp-gegl-procedure"
argument_list|,
name|g_object_ref
argument_list|(
name|procedure
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|tool_name
argument_list|,
literal|"gimp-operation-tool"
argument_list|)
condition|)
block|{
name|gimp_operation_tool_set_operation
argument_list|(
name|GIMP_OPERATION_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|,
name|procedure
operator|->
name|original_name
argument_list|,
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|gimp_procedure_get_label
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|gimp_viewable_get_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|procedure
argument_list|)
argument_list|)
argument_list|,
name|gimp_procedure_get_help_id
argument_list|(
name|procedure
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|tool_manager_initialize_active
argument_list|(
name|gimp
argument_list|,
name|GIMP_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|settings
condition|)
name|gimp_filter_tool_set_config
argument_list|(
name|GIMP_FILTER_TOOL
argument_list|(
name|active_tool
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|settings
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpProcedure
modifier|*
DECL|function|gimp_gegl_procedure_new (Gimp * gimp,GimpRunMode default_run_mode,GimpObject * default_settings,const gchar * operation,const gchar * name,const gchar * menu_label,const gchar * tooltip,const gchar * icon_name,const gchar * help_id)
name|gimp_gegl_procedure_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpRunMode
name|default_run_mode
parameter_list|,
name|GimpObject
modifier|*
name|default_settings
parameter_list|,
specifier|const
name|gchar
modifier|*
name|operation
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tooltip
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|GimpGeglProcedure
modifier|*
name|gegl_procedure
decl_stmt|;
name|GType
name|config_type
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|operation
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_label
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config_type
operator|=
name|gimp_operation_config_get_type
argument_list|(
name|gimp
argument_list|,
name|operation
argument_list|,
name|icon_name
argument_list|,
name|GIMP_TYPE_SETTINGS
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_GEGL_PROCEDURE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_procedure
operator|=
name|GIMP_GEGL_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|gegl_procedure
operator|->
name|default_run_mode
operator|=
name|default_run_mode
expr_stmt|;
name|gegl_procedure
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|menu_label
argument_list|)
expr_stmt|;
name|gegl_procedure
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_settings
condition|)
name|gegl_procedure
operator|->
name|default_settings
operator|=
name|g_object_ref
argument_list|(
name|default_settings
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_viewable_set_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_strings
argument_list|(
name|procedure
argument_list|,
name|operation
argument_list|,
name|tooltip
argument_list|,
name|tooltip
argument_list|,
literal|"author"
argument_list|,
literal|"copyright"
argument_list|,
literal|"date"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"run-mode"
argument_list|,
literal|"Run mode"
argument_list|,
literal|"Run mode"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Input image"
argument_list|,
name|gimp
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable_id
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"Input drawable"
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"settings"
argument_list|,
literal|"Settings"
argument_list|,
literal|"Settings"
argument_list|,
name|config_type
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|procedure
return|;
block|}
end_function

end_unit

