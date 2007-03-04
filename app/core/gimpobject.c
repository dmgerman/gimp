begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b2f96640103
block|{
DECL|enumerator|DISCONNECT
name|DISCONNECT
block|,
DECL|enumerator|NAME_CHANGED
name|NAME_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2b2f96640203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_NAME
name|PROP_NAME
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_object_dispose
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
name|gimp_object_finalize
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
name|gimp_object_set_property
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
name|gimp_object_get_property
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
name|gimp_object_real_get_memsize
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
name|gimp_object_name_normalize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpObject
argument_list|,
argument|gimp_object
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_object_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|object_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_object_class_init (GimpObjectClass * klass)
name|gimp_object_class_init
parameter_list|(
name|GimpObjectClass
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
name|object_signals
index|[
name|DISCONNECT
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"disconnect"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpObjectClass
argument_list|,
name|disconnect
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_signals
index|[
name|NAME_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"name-changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpObjectClass
argument_list|,
name|name_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_object_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_object_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_object_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_object_get_property
expr_stmt|;
name|klass
operator|->
name|disconnect
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|name_changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_memsize
operator|=
name|gimp_object_real_get_memsize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_NAME
argument_list|,
name|g_param_spec_string
argument_list|(
literal|"name"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_init (GimpObject * object)
name|gimp_object_init
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|object
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|object
operator|->
name|normalized
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_dispose (GObject * object)
name|gimp_object_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpObject
modifier|*
name|gimp_object
init|=
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_object
operator|->
name|disconnected
condition|)
block|{
name|g_signal_emit
argument_list|(
name|object
argument_list|,
name|object_signals
index|[
name|DISCONNECT
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_object
operator|->
name|disconnected
operator|=
name|TRUE
expr_stmt|;
block|}
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
DECL|function|gimp_object_finalize (GObject * object)
name|gimp_object_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gimp_object_name_free
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|object
argument_list|)
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
name|void
DECL|function|gimp_object_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_object_set_property
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
name|GimpObject
modifier|*
name|gimp_object
init|=
name|GIMP_OBJECT
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
name|PROP_NAME
case|:
name|gimp_object_set_name
argument_list|(
name|gimp_object
argument_list|,
name|g_value_get_string
argument_list|(
name|value
argument_list|)
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
DECL|function|gimp_object_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_object_get_property
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
name|GimpObject
modifier|*
name|gimp_object
init|=
name|GIMP_OBJECT
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
name|PROP_NAME
case|:
if|if
condition|(
name|gimp_object
operator|->
name|static_name
condition|)
name|g_value_set_static_string
argument_list|(
name|value
argument_list|,
name|gimp_object
operator|->
name|name
argument_list|)
expr_stmt|;
else|else
name|g_value_set_string
argument_list|(
name|value
argument_list|,
name|gimp_object
operator|->
name|name
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

begin_comment
comment|/**  * gimp_object_set_name:  * @object: a #GimpObject  * @name: the @object's new name  *  * Sets the @object's name. Takes care of freeing the old name and  * emitting the "name_changed" signal if the old and new name differ.  **/
end_comment

begin_function
name|void
DECL|function|gimp_object_set_name (GimpObject * object,const gchar * name)
name|gimp_object_set_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|object
operator|->
name|name
operator|&&
operator|!
name|name
operator|)
operator|||
operator|(
name|object
operator|->
name|name
operator|&&
name|name
operator|&&
operator|!
name|strcmp
argument_list|(
name|object
operator|->
name|name
argument_list|,
name|name
argument_list|)
operator|)
condition|)
return|return;
name|gimp_object_name_free
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|object
operator|->
name|static_name
operator|=
name|FALSE
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_object_set_name_safe:  * @object: a #GimpObject  * @name: the @object's new name  *  * A safe version of gimp_object_set_name() that takes care of  * handling newlines and overly long names. The actual name set  * may be different to the @name you pass.  **/
end_comment

begin_function
name|void
DECL|function|gimp_object_set_name_safe (GimpObject * object,const gchar * name)
name|gimp_object_set_name_safe
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
name|object
operator|->
name|name
operator|&&
operator|!
name|name
operator|)
operator|||
operator|(
name|object
operator|->
name|name
operator|&&
name|name
operator|&&
operator|!
name|strcmp
argument_list|(
name|object
operator|->
name|name
argument_list|,
name|name
argument_list|)
operator|)
condition|)
return|return;
name|gimp_object_name_free
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
name|gimp_utf8_strtrim
argument_list|(
name|name
argument_list|,
literal|30
argument_list|)
expr_stmt|;
name|object
operator|->
name|static_name
operator|=
name|FALSE
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_object_set_static_name (GimpObject * object,const gchar * name)
name|gimp_object_set_static_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_name_free
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|name
expr_stmt|;
name|object
operator|->
name|static_name
operator|=
name|TRUE
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_object_take_name (GimpObject * object,gchar * name)
name|gimp_object_take_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_name_free
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|object
operator|->
name|static_name
operator|=
name|FALSE
expr_stmt|;
name|gimp_object_name_changed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|"name"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_object_get_name:  * @object: a #GimpObject  *  * This function gives access to the name of a GimpObject. The  * returned name belongs to the object and must not be freed.  *  * Return value: a pointer to the @object's name  **/
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_object_get_name (const GimpObject * object)
name|gimp_object_get_name
parameter_list|(
specifier|const
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|object
operator|->
name|name
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_object_name_changed:  * @object: a #GimpObject  *  * Causes the "name-changed" signal to be emitted.  **/
end_comment

begin_function
name|void
DECL|function|gimp_object_name_changed (GimpObject * object)
name|gimp_object_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|object
argument_list|,
name|object_signals
index|[
name|NAME_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_object_name_free:  * @object: a #GimpObject  *  * Frees the name of @object and sets the name pointer to %NULL. Also  * takes care of the normalized name that the object might be caching.  *  * In general you should be using gimp_object_set_name() instead. But  * if you ever need to free the object name but don't want the  * "name-changed" signal to be emitted, then use this function. Never  * ever free the object name directly!  **/
end_comment

begin_function
name|void
DECL|function|gimp_object_name_free (GimpObject * object)
name|gimp_object_name_free
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|object
operator|->
name|normalized
condition|)
block|{
if|if
condition|(
name|object
operator|->
name|normalized
operator|!=
name|object
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|object
operator|->
name|normalized
argument_list|)
expr_stmt|;
name|object
operator|->
name|normalized
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|object
operator|->
name|name
condition|)
block|{
if|if
condition|(
operator|!
name|object
operator|->
name|static_name
condition|)
name|g_free
argument_list|(
name|object
operator|->
name|name
argument_list|)
expr_stmt|;
name|object
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|object
operator|->
name|static_name
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/**  * gimp_object_name_collate:  * @object1: a #GimpObject  * @object2: another #GimpObject  *  * Compares two object names for ordering using the linguistically  * correct rules for the current locale. It caches the normalized  * version of the object name to speed up subsequent calls.  *  * Return value: -1 if object1 compares before object2,  *                0 if they compare equal,  *                1 if object1 compares after object2.  **/
end_comment

begin_function
name|gint
DECL|function|gimp_object_name_collate (GimpObject * object1,GimpObject * object2)
name|gimp_object_name_collate
parameter_list|(
name|GimpObject
modifier|*
name|object1
parameter_list|,
name|GimpObject
modifier|*
name|object2
parameter_list|)
block|{
if|if
condition|(
operator|!
name|object1
operator|->
name|normalized
condition|)
name|gimp_object_name_normalize
argument_list|(
name|object1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|object2
operator|->
name|normalized
condition|)
name|gimp_object_name_normalize
argument_list|(
name|object2
argument_list|)
expr_stmt|;
return|return
name|strcmp
argument_list|(
name|object1
operator|->
name|normalized
argument_list|,
name|object2
operator|->
name|normalized
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_object_name_normalize (GimpObject * object)
name|gimp_object_name_normalize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|object
operator|->
name|normalized
operator|==
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|object
operator|->
name|name
condition|)
block|{
name|gchar
modifier|*
name|key
init|=
name|g_utf8_collate_key
argument_list|(
name|object
operator|->
name|name
argument_list|,
operator|-
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|key
argument_list|,
name|object
operator|->
name|name
argument_list|)
condition|)
block|{
name|object
operator|->
name|normalized
operator|=
name|key
expr_stmt|;
block|}
else|else
block|{
name|g_free
argument_list|(
name|key
argument_list|)
expr_stmt|;
name|object
operator|->
name|normalized
operator|=
name|object
operator|->
name|name
expr_stmt|;
block|}
block|}
block|}
end_function

begin_define
DECL|macro|DEBUG_MEMSIZE
define|#
directive|define
name|DEBUG_MEMSIZE
value|1
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG_MEMSIZE
end_ifdef

begin_decl_stmt
DECL|variable|gimp_debug_memsize
name|gboolean
name|gimp_debug_memsize
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|gint64
DECL|function|gimp_object_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_object_get_memsize
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
name|gint64
name|my_size
init|=
literal|0
decl_stmt|;
name|gint64
name|my_gui_size
init|=
literal|0
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_OBJECT
argument_list|(
name|object
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_MEMSIZE
if|if
condition|(
name|gimp_debug_memsize
condition|)
block|{
specifier|static
name|gint
name|indent_level
init|=
literal|0
decl_stmt|;
specifier|static
name|GList
modifier|*
name|aggregation_tree
init|=
name|NULL
decl_stmt|;
specifier|static
name|gchar
name|indent_buf
index|[
literal|256
index|]
decl_stmt|;
name|gint64
name|memsize
decl_stmt|;
name|gint64
name|gui_memsize
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|my_indent_level
decl_stmt|;
name|gchar
modifier|*
name|object_size
decl_stmt|;
name|indent_level
operator|++
expr_stmt|;
name|my_indent_level
operator|=
name|indent_level
expr_stmt|;
name|memsize
operator|=
name|GIMP_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
operator|&
name|gui_memsize
argument_list|)
expr_stmt|;
name|indent_level
operator|--
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MIN
argument_list|(
name|my_indent_level
operator|*
literal|2
argument_list|,
sizeof|sizeof
argument_list|(
name|indent_buf
argument_list|)
operator|-
literal|1
argument_list|)
condition|;
name|i
operator|++
control|)
name|indent_buf
index|[
name|i
index|]
operator|=
literal|' '
expr_stmt|;
name|indent_buf
index|[
name|i
index|]
operator|=
literal|'\0'
expr_stmt|;
name|object_size
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s \"%s\": "
literal|"%"
name|G_GINT64_FORMAT
literal|"(%"
name|G_GINT64_FORMAT
literal|")\n"
argument_list|,
name|indent_buf
argument_list|,
name|g_type_name
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|object
argument_list|)
argument_list|)
argument_list|,
name|object
operator|->
name|name
condition|?
name|object
operator|->
name|name
else|:
literal|"anonymous"
argument_list|,
name|memsize
argument_list|,
name|gui_memsize
argument_list|)
expr_stmt|;
name|aggregation_tree
operator|=
name|g_list_prepend
argument_list|(
name|aggregation_tree
argument_list|,
name|object_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|indent_level
operator|==
literal|0
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|aggregation_tree
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
name|g_print
argument_list|(
literal|"%s"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|aggregation_tree
argument_list|)
expr_stmt|;
name|aggregation_tree
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|memsize
return|;
block|}
endif|#
directive|endif
comment|/* DEBUG_MEMSIZE */
name|my_size
operator|=
name|GIMP_OBJECT_GET_CLASS
argument_list|(
name|object
argument_list|)
operator|->
name|get_memsize
argument_list|(
name|object
argument_list|,
operator|&
name|my_gui_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|gui_size
condition|)
operator|*
name|gui_size
operator|=
name|my_gui_size
expr_stmt|;
return|return
name|my_size
return|;
block|}
end_function

begin_function
specifier|static
name|gint64
DECL|function|gimp_object_real_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_object_real_get_memsize
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
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|object
operator|->
name|name
operator|&&
operator|!
name|object
operator|->
name|static_name
condition|)
name|memsize
operator|+=
name|strlen
argument_list|(
name|object
operator|->
name|name
argument_list|)
operator|+
literal|1
expr_stmt|;
return|return
name|memsize
operator|+
name|gimp_g_object_get_memsize
argument_list|(
operator|(
name|GObject
operator|*
operator|)
name|object
argument_list|)
return|;
block|}
end_function

end_unit

