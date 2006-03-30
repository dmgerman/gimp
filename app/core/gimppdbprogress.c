begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdbprogress.c  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"gimppdbprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28945d230103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_CALLBACK_NAME
name|PROP_CALLBACK_NAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_class_init
parameter_list|(
name|GimpPdbProgressClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_init
parameter_list|(
name|GimpPdbProgress
modifier|*
name|progress
parameter_list|,
name|GimpPdbProgressClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_pdb_progress_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProgress
modifier|*
name|gimp_pdb_progress_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_pdb_progress_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_pdb_progress_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pdb_progress_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint32
name|gimp_pdb_progress_progress_get_window
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_pdb_progress_get_type (void)
name|gimp_pdb_progress_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpPdbProgressClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_pdb_progress_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpPdbProgress
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_pdb_progress_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|progress_iface_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_pdb_progress_progress_iface_init
block|,
name|NULL
block|,
comment|/* iface_finalize */
name|NULL
comment|/* iface_data     */
block|}
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_OBJECT
argument_list|,
literal|"GimpPdbProgress"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|type
argument_list|,
name|GIMP_TYPE_PROGRESS
argument_list|,
operator|&
name|progress_iface_info
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_class_init (GimpPdbProgressClass * klass)
name|gimp_pdb_progress_class_init
parameter_list|(
name|GimpPdbProgressClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_pdb_progress_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_pdb_progress_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pdb_progress_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_pdb_progress_set_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CALLBACK_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"callback-name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_WRITABLE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_init (GimpPdbProgress * progress,GimpPdbProgressClass * klass)
name|gimp_pdb_progress_init
parameter_list|(
name|GimpPdbProgress
modifier|*
name|progress
parameter_list|,
name|GimpPdbProgressClass
modifier|*
name|klass
parameter_list|)
block|{
name|klass
operator|->
name|progresses
operator|=
name|g_list_prepend
argument_list|(
name|klass
operator|->
name|progresses
argument_list|,
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_progress_iface_init (GimpProgressInterface * iface)
name|gimp_pdb_progress_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_pdb_progress_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_pdb_progress_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_pdb_progress_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_pdb_progress_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_pdb_progress_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_pdb_progress_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_pdb_progress_progress_pulse
expr_stmt|;
name|iface
operator|->
name|get_window
operator|=
name|gimp_pdb_progress_progress_get_window
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_pdb_progress_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_pdb_progress_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpPdbProgress
modifier|*
name|progress
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|progress
operator|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|progress
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_dispose (GObject * object)
name|gimp_pdb_progress_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPdbProgressClass
modifier|*
name|klass
init|=
name|GIMP_PDB_PROGRESS_GET_CLASS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|klass
operator|->
name|progresses
operator|=
name|g_list_remove
argument_list|(
name|klass
operator|->
name|progresses
argument_list|,
name|object
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_finalize (GObject * object)
name|gimp_pdb_progress_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|progress
operator|->
name|context
condition|)
block|{
name|g_object_unref
argument_list|(
name|progress
operator|->
name|context
argument_list|)
expr_stmt|;
name|progress
operator|->
name|context
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|progress
operator|->
name|callback_name
condition|)
block|{
name|g_free
argument_list|(
name|progress
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|progress
operator|->
name|callback_name
operator|=
name|NULL
expr_stmt|;
block|}
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
name|void
DECL|function|gimp_pdb_progress_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_pdb_progress_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
if|if
condition|(
name|progress
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|progress
operator|->
name|context
argument_list|)
expr_stmt|;
name|progress
operator|->
name|context
operator|=
operator|(
name|GimpContext
operator|*
operator|)
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_CALLBACK_NAME
case|:
if|if
condition|(
name|progress
operator|->
name|callback_name
condition|)
name|g_free
argument_list|(
name|progress
operator|->
name|callback_name
argument_list|)
expr_stmt|;
name|progress
operator|->
name|callback_name
operator|=
name|g_value_dup_string
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_pdb_progress_run_callback (GimpPdbProgress * progress,GimpProgressCommand command,const gchar * text,gdouble value)
name|gimp_pdb_progress_run_callback
parameter_list|(
name|GimpPdbProgress
modifier|*
name|progress
parameter_list|,
name|GimpProgressCommand
name|command
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|,
name|gdouble
name|value
parameter_list|)
block|{
name|gdouble
name|retval
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|progress
operator|->
name|callback_name
operator|&&
operator|!
name|progress
operator|->
name|callback_busy
condition|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|progress
operator|->
name|callback_busy
operator|=
name|TRUE
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|progress
operator|->
name|context
operator|->
name|gimp
argument_list|,
name|progress
operator|->
name|context
argument_list|,
name|NULL
argument_list|,
name|progress
operator|->
name|callback_name
argument_list|,
operator|&
name|n_return_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|command
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|text
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|value
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_value_get_enum
argument_list|(
operator|&
name|return_vals
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
operator|!=
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Unable to run %s callback. "
literal|"The corresponding plug-in may have crashed."
argument_list|)
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|progress
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|n_return_vals
operator|>=
literal|2
operator|&&
name|return_vals
index|[
literal|1
index|]
operator|.
name|type
operator|==
name|GIMP_PDB_FLOAT
condition|)
block|{
name|retval
operator|=
name|g_value_get_double
argument_list|(
operator|&
name|return_vals
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|return_vals
condition|)
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|progress
operator|->
name|callback_busy
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProgress
modifier|*
DECL|function|gimp_pdb_progress_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_pdb_progress_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|pdb_progress
operator|->
name|active
condition|)
block|{
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_START
argument_list|,
name|message
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|pdb_progress
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
name|pdb_progress
operator|->
name|value
operator|=
literal|0.0
expr_stmt|;
return|return
name|progress
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_progress_end (GimpProgress * progress)
name|gimp_pdb_progress_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|pdb_progress
operator|->
name|active
condition|)
block|{
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_END
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|pdb_progress
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
name|pdb_progress
operator|->
name|value
operator|=
literal|0.0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_pdb_progress_progress_is_active (GimpProgress * progress)
name|gimp_pdb_progress_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|pdb_progress
operator|->
name|active
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_pdb_progress_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|pdb_progress
operator|->
name|active
condition|)
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_SET_TEXT
argument_list|,
name|message
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_pdb_progress_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|pdb_progress
operator|->
name|active
condition|)
block|{
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_SET_VALUE
argument_list|,
name|NULL
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
name|pdb_progress
operator|->
name|value
operator|=
name|percentage
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_pdb_progress_progress_get_value (GimpProgress * progress)
name|gimp_pdb_progress_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
name|pdb_progress
operator|->
name|value
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pdb_progress_progress_pulse (GimpProgress * progress)
name|gimp_pdb_progress_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|pdb_progress
operator|->
name|active
condition|)
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_PULSE
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gimp_pdb_progress_progress_get_window (GimpProgress * progress)
name|gimp_pdb_progress_progress_get_window
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpPdbProgress
modifier|*
name|pdb_progress
init|=
name|GIMP_PDB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
return|return
operator|(
name|guint32
operator|)
name|gimp_pdb_progress_run_callback
argument_list|(
name|pdb_progress
argument_list|,
name|GIMP_PROGRESS_COMMAND_GET_WINDOW
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPdbProgress
modifier|*
DECL|function|gimp_pdb_progress_get_by_callback (GimpPdbProgressClass * klass,const gchar * callback_name)
name|gimp_pdb_progress_get_by_callback
parameter_list|(
name|GimpPdbProgressClass
modifier|*
name|klass
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PDB_PROGRESS_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|callback_name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|klass
operator|->
name|progresses
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
name|GimpPdbProgress
modifier|*
name|progress
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|progress
operator|->
name|callback_name
operator|&&
name|strcmp
argument_list|(
name|callback_name
argument_list|,
name|progress
operator|->
name|callback_name
argument_list|)
operator|==
literal|0
condition|)
return|return
name|progress
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

