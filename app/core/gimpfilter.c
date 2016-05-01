begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfilter.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-memsize.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilter.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28d89bbf0103
block|{
DECL|enumerator|VISIBILITY_CHANGED
name|VISIBILITY_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon28d89bbf0203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_VISIBLE
name|PROP_VISIBLE
block|,
DECL|enumerator|PROP_IS_LAST_NODE
name|PROP_IS_LAST_NODE
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpFilterPrivate
typedef|typedef
name|struct
name|_GimpFilterPrivate
name|GimpFilterPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFilterPrivate
struct|struct
name|_GimpFilterPrivate
block|{
DECL|member|node
name|GeglNode
modifier|*
name|node
decl_stmt|;
DECL|member|visible
name|guint
name|visible
range|:
literal|1
decl_stmt|;
DECL|member|is_last_node
name|guint
name|is_last_node
range|:
literal|1
decl_stmt|;
DECL|member|applicator
name|GimpApplicator
modifier|*
name|applicator
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (filter)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|filter
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (filter, \                                                          GIMP_TYPE_FILTER, \                                                          GimpFilterPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_filter_finalize
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
name|gimp_filter_set_property
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
name|gimp_filter_get_property
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
name|gimp_filter_get_memsize
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
name|gimp_filter_real_visibility_changed
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GeglNode
modifier|*
name|gimp_filter_real_get_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFilter
argument_list|,
argument|gimp_filter
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_filter_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_filter_signals
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
DECL|function|gimp_filter_class_init (GimpFilterClass * klass)
name|gimp_filter_class_init
parameter_list|(
name|GimpFilterClass
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
name|gimp_filter_signals
index|[
name|VISIBILITY_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"visibility-changed"
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
name|GimpFilterClass
argument_list|,
name|visibility_changed
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
name|finalize
operator|=
name|gimp_filter_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_filter_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_filter_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_filter_get_memsize
expr_stmt|;
name|klass
operator|->
name|visibility_changed
operator|=
name|gimp_filter_real_visibility_changed
expr_stmt|;
name|klass
operator|->
name|get_node
operator|=
name|gimp_filter_real_get_node
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VISIBLE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"visible"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IS_LAST_NODE
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"is-last-node"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpFilterPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_init (GimpFilter * filter)
name|gimp_filter_init
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GimpFilterPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
decl_stmt|;
name|private
operator|->
name|visible
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_filter_finalize (GObject * object)
name|gimp_filter_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFilterPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|node
condition|)
block|{
name|g_object_unref
argument_list|(
name|private
operator|->
name|node
argument_list|)
expr_stmt|;
name|private
operator|->
name|node
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
DECL|function|gimp_filter_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_filter_set_property
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
name|GimpFilter
modifier|*
name|filter
init|=
name|GIMP_FILTER
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
name|PROP_VISIBLE
case|:
name|gimp_filter_set_visible
argument_list|(
name|filter
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IS_LAST_NODE
case|:
name|gimp_filter_set_is_last_node
argument_list|(
name|filter
argument_list|,
name|g_value_get_boolean
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
DECL|function|gimp_filter_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_filter_get_property
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
name|GimpFilterPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_VISIBLE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|visible
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IS_LAST_NODE
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|is_last_node
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
DECL|function|gimp_filter_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_filter_get_memsize
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
name|GimpFilterPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|gimp_g_object_get_memsize
argument_list|(
name|G_OBJECT
argument_list|(
name|private
operator|->
name|node
argument_list|)
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
DECL|function|gimp_filter_real_visibility_changed (GimpFilter * filter)
name|gimp_filter_real_visibility_changed
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GeglNode
modifier|*
name|node
init|=
name|gimp_filter_peek_node
argument_list|(
name|filter
argument_list|)
decl_stmt|;
if|if
condition|(
name|node
condition|)
block|{
if|if
condition|(
name|gimp_filter_get_visible
argument_list|(
name|filter
argument_list|)
condition|)
block|{
comment|/* Leave this up to subclasses */
block|}
else|else
block|{
name|GeglNode
modifier|*
name|input
init|=
name|gegl_node_get_input_proxy
argument_list|(
name|node
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|output
init|=
name|gegl_node_get_output_proxy
argument_list|(
name|node
argument_list|,
literal|"output"
argument_list|)
decl_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_filter_real_get_node (GimpFilter * filter)
name|gimp_filter_real_get_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GimpFilterPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
decl_stmt|;
name|private
operator|->
name|node
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
if|if
condition|(
name|gimp_filter_get_visible
argument_list|(
name|filter
argument_list|)
condition|)
block|{
comment|/* Leave this up to subclasses */
block|}
else|else
block|{
name|GeglNode
modifier|*
name|input
init|=
name|gegl_node_get_input_proxy
argument_list|(
name|private
operator|->
name|node
argument_list|,
literal|"input"
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|output
init|=
name|gegl_node_get_output_proxy
argument_list|(
name|private
operator|->
name|node
argument_list|,
literal|"output"
argument_list|)
decl_stmt|;
name|gegl_node_connect_to
argument_list|(
name|input
argument_list|,
literal|"output"
argument_list|,
name|output
argument_list|,
literal|"input"
argument_list|)
expr_stmt|;
block|}
return|return
name|private
operator|->
name|node
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpFilter
modifier|*
DECL|function|gimp_filter_new (const gchar * name)
name|gimp_filter_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILTER
argument_list|,
literal|"name"
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_filter_get_node (GimpFilter * filter)
name|gimp_filter_get_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|GimpFilterPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|node
condition|)
return|return
name|private
operator|->
name|node
return|;
return|return
name|GIMP_FILTER_GET_CLASS
argument_list|(
name|filter
argument_list|)
operator|->
name|get_node
argument_list|(
name|filter
argument_list|)
return|;
block|}
end_function

begin_function
name|GeglNode
modifier|*
DECL|function|gimp_filter_peek_node (GimpFilter * filter)
name|gimp_filter_peek_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|node
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_filter_set_visible (GimpFilter * filter,gboolean visible)
name|gimp_filter_set_visible
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|visible
operator|=
name|visible
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|visible
operator|!=
name|gimp_filter_get_visible
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|visible
operator|=
name|visible
expr_stmt|;
name|g_signal_emit
argument_list|(
name|filter
argument_list|,
name|gimp_filter_signals
index|[
name|VISIBILITY_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|,
literal|"visible"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_filter_get_visible (GimpFilter * filter)
name|gimp_filter_get_visible
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|visible
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_filter_is_visible (GimpFilter * filter)
name|gimp_filter_is_visible
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_filter_get_visible
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|GimpFilter
modifier|*
name|parent
decl_stmt|;
name|parent
operator|=
name|GIMP_FILTER
argument_list|(
name|gimp_viewable_get_parent
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|filter
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
return|return
name|gimp_filter_is_visible
argument_list|(
name|parent
argument_list|)
return|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_filter_set_is_last_node (GimpFilter * filter,gboolean is_last_node)
name|gimp_filter_set_is_last_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|gboolean
name|is_last_node
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|is_last_node
operator|=
name|is_last_node
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|is_last_node
operator|!=
name|gimp_filter_get_is_last_node
argument_list|(
name|filter
argument_list|)
condition|)
block|{
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|is_last_node
operator|=
name|is_last_node
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|filter
argument_list|)
argument_list|,
literal|"is-last-node"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_filter_get_is_last_node (GimpFilter * filter)
name|gimp_filter_get_is_last_node
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|is_last_node
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_filter_set_applicator (GimpFilter * filter,GimpApplicator * applicator)
name|gimp_filter_set_applicator
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|,
name|GimpApplicator
modifier|*
name|applicator
parameter_list|)
block|{
name|GimpFilterPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
expr_stmt|;
name|private
operator|->
name|applicator
operator|=
name|applicator
expr_stmt|;
block|}
end_function

begin_function
name|GimpApplicator
modifier|*
DECL|function|gimp_filter_get_applicator (GimpFilter * filter)
name|gimp_filter_get_applicator
parameter_list|(
name|GimpFilter
modifier|*
name|filter
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILTER
argument_list|(
name|filter
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|filter
argument_list|)
operator|->
name|applicator
return|;
block|}
end_function

end_unit

