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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitemundo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimptext.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayer.h"
end_include

begin_include
include|#
directive|include
file|"gimptextundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29aa5f170103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PARAM
name|PROP_PARAM
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_text_undo_class_init
parameter_list|(
name|GimpTextUndoClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_text_undo_constructor
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
name|gimp_text_undo_set_property
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
name|void
name|gimp_text_undo_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
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
name|gint64
name|gimp_text_undo_get_memsize
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
name|void
name|gimp_text_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_text_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpUndoClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_undo_get_type (void)
name|gimp_text_undo_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|undo_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|undo_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|undo_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpTextUndoClass
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
name|gimp_text_undo_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpTextUndo
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|undo_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM_UNDO
argument_list|,
literal|"GimpTextUndo"
argument_list|,
operator|&
name|undo_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|undo_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_undo_class_init (GimpTextUndoClass * klass)
name|gimp_text_undo_class_init
parameter_list|(
name|GimpTextUndoClass
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
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
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
name|gimp_text_undo_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_text_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_text_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_text_undo_get_memsize
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_text_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_text_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PARAM
argument_list|,
name|g_param_spec_param
argument_list|(
literal|"param"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|G_TYPE_PARAM
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_text_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_text_undo_constructor
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
name|GimpTextUndo
modifier|*
name|text_undo
decl_stmt|;
name|GimpTextLayer
modifier|*
name|layer
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
name|text_undo
operator|=
name|GIMP_TEXT_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_TEXT_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|text_undo
argument_list|)
operator|->
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|layer
operator|=
name|GIMP_TEXT_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|text_undo
argument_list|)
operator|->
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_undo
operator|->
name|pspec
condition|)
block|{
name|g_assert
argument_list|(
name|text_undo
operator|->
name|pspec
operator|->
name|owner_type
operator|==
name|GIMP_TYPE_TEXT
argument_list|)
expr_stmt|;
name|text_undo
operator|->
name|value
operator|=
name|g_new0
argument_list|(
name|GValue
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
name|text_undo
operator|->
name|value
argument_list|,
name|text_undo
operator|->
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|,
name|text_undo
operator|->
name|pspec
operator|->
name|name
argument_list|,
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|layer
operator|->
name|text
condition|)
block|{
name|text_undo
operator|->
name|text
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|)
expr_stmt|;
block|}
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_text_undo_set_property
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
name|GimpTextUndo
modifier|*
name|text_undo
init|=
name|GIMP_TEXT_UNDO
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
name|PROP_PARAM
case|:
name|text_undo
operator|->
name|pspec
operator|=
name|g_value_get_param
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
name|void
DECL|function|gimp_text_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_text_undo_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpTextUndo
modifier|*
name|text_undo
init|=
name|GIMP_TEXT_UNDO
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
name|PROP_PARAM
case|:
name|g_value_set_param
argument_list|(
name|value
argument_list|,
operator|(
name|GParamSpec
operator|*
operator|)
name|text_undo
operator|->
name|pspec
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
name|gint64
DECL|function|gimp_text_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_text_undo_get_memsize
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
name|GimpTextUndo
modifier|*
name|undo
init|=
name|GIMP_TEXT_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|undo
operator|->
name|value
condition|)
name|memsize
operator|+=
name|gimp_g_value_get_memsize
argument_list|(
name|undo
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|text
condition|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|undo
operator|->
name|text
argument_list|)
argument_list|,
name|NULL
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
name|void
DECL|function|gimp_text_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_text_undo_pop
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|,
name|GimpUndoAccumulator
modifier|*
name|accum
parameter_list|)
block|{
name|GimpTextUndo
modifier|*
name|text_undo
init|=
name|GIMP_TEXT_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|GimpTextLayer
modifier|*
name|layer
init|=
name|GIMP_TEXT_LAYER
argument_list|(
name|GIMP_ITEM_UNDO
argument_list|(
name|undo
argument_list|)
operator|->
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|text_undo
operator|->
name|pspec
condition|)
block|{
name|GValue
modifier|*
name|value
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|layer
operator|->
name|text
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|value
operator|=
name|g_new0
argument_list|(
name|GValue
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_value_init
argument_list|(
name|value
argument_list|,
name|text_undo
operator|->
name|pspec
operator|->
name|value_type
argument_list|)
expr_stmt|;
name|g_object_get_property
argument_list|(
name|G_OBJECT
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|,
name|text_undo
operator|->
name|pspec
operator|->
name|name
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_object_set_property
argument_list|(
name|G_OBJECT
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|,
name|text_undo
operator|->
name|pspec
operator|->
name|name
argument_list|,
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_value_unset
argument_list|(
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
name|text_undo
operator|->
name|value
operator|=
name|value
expr_stmt|;
block|}
else|else
block|{
name|GimpText
modifier|*
name|text
decl_stmt|;
name|text
operator|=
operator|(
name|layer
operator|->
name|text
condition|?
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|)
else|:
name|NULL
operator|)
expr_stmt|;
if|if
condition|(
name|layer
operator|->
name|text
operator|&&
name|text_undo
operator|->
name|text
condition|)
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|text_undo
operator|->
name|text
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|layer
operator|->
name|text
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
else|else
name|gimp_text_layer_set_text
argument_list|(
name|layer
argument_list|,
name|text_undo
operator|->
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|text_undo
operator|->
name|text
condition|)
name|g_object_unref
argument_list|(
name|text_undo
operator|->
name|text
argument_list|)
expr_stmt|;
name|text_undo
operator|->
name|text
operator|=
name|text
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|pop
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_text_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_text_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpTextUndo
modifier|*
name|text_undo
init|=
name|GIMP_TEXT_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|text_undo
operator|->
name|text
condition|)
block|{
name|g_object_unref
argument_list|(
name|text_undo
operator|->
name|text
argument_list|)
expr_stmt|;
name|text_undo
operator|->
name|text
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|text_undo
operator|->
name|pspec
condition|)
block|{
name|g_value_unset
argument_list|(
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text_undo
operator|->
name|value
argument_list|)
expr_stmt|;
name|text_undo
operator|->
name|value
operator|=
name|NULL
expr_stmt|;
name|text_undo
operator|->
name|pspec
operator|=
name|NULL
expr_stmt|;
block|}
name|GIMP_UNDO_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|free
argument_list|(
name|undo
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

