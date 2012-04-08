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
file|<time.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpundo.h"
end_include

begin_include
include|#
directive|include
file|"gimpundostack.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c895f970103
block|{
DECL|enumerator|POP
name|POP
block|,
DECL|enumerator|FREE
name|FREE
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2c895f970203
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|,
DECL|enumerator|PROP_TIME
name|PROP_TIME
block|,
DECL|enumerator|PROP_UNDO_TYPE
name|PROP_UNDO_TYPE
block|,
DECL|enumerator|PROP_DIRTY_MASK
name|PROP_DIRTY_MASK
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_undo_constructed
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
name|gimp_undo_finalize
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
name|gimp_undo_set_property
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
name|gimp_undo_get_property
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
name|gimp_undo_get_memsize
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
name|gboolean
name|gimp_undo_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpTempBuf
modifier|*
name|gimp_undo_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_real_pop
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
name|gimp_undo_real_free
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

begin_function_decl
specifier|static
name|gboolean
name|gimp_undo_create_preview_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_undo_create_preview_private
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpUndo
argument_list|,
argument|gimp_undo
argument_list|,
argument|GIMP_TYPE_VIEWABLE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_undo_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|undo_signals
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
DECL|function|gimp_undo_class_init (GimpUndoClass * klass)
name|gimp_undo_class_init
parameter_list|(
name|GimpUndoClass
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
name|undo_signals
index|[
name|POP
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"pop"
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
name|GimpUndoClass
argument_list|,
name|pop
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM_POINTER
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|2
argument_list|,
name|GIMP_TYPE_UNDO_MODE
argument_list|,
name|G_TYPE_POINTER
argument_list|)
expr_stmt|;
name|undo_signals
index|[
name|FREE
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"free"
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
name|GimpUndoClass
argument_list|,
name|free
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__ENUM
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|GIMP_TYPE_UNDO_MODE
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_undo_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_undo_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_undo_get_property
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_undo_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|default_stock_id
operator|=
literal|"gtk-undo"
expr_stmt|;
name|viewable_class
operator|->
name|get_popup_size
operator|=
name|gimp_undo_get_popup_size
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_undo_get_new_preview
expr_stmt|;
name|klass
operator|->
name|pop
operator|=
name|gimp_undo_real_pop
expr_stmt|;
name|klass
operator|->
name|free
operator|=
name|gimp_undo_real_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_TIME
argument_list|,
name|g_param_spec_uint
argument_list|(
literal|"time"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXUINT
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_UNDO_TYPE
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"undo-type"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_UNDO_TYPE
argument_list|,
name|GIMP_UNDO_GROUP_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_DIRTY_MASK
argument_list|,
name|g_param_spec_flags
argument_list|(
literal|"dirty-mask"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DIRTY_MASK
argument_list|,
name|GIMP_DIRTY_NONE
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gimp_undo_init (GimpUndo * undo)
name|gimp_undo_init
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
name|undo
operator|->
name|time
operator|=
name|time
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_constructed (GObject * object)
name|gimp_undo_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|undo
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_finalize (GObject * object)
name|gimp_undo_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview_idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|undo
operator|->
name|preview_idle_id
argument_list|)
expr_stmt|;
name|undo
operator|->
name|preview_idle_id
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|undo
operator|->
name|preview
condition|)
block|{
name|gimp_temp_buf_unref
argument_list|(
name|undo
operator|->
name|preview
argument_list|)
expr_stmt|;
name|undo
operator|->
name|preview
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
DECL|function|gimp_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_undo_set_property
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
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
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
name|PROP_IMAGE
case|:
comment|/* don't ref */
name|undo
operator|->
name|image
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TIME
case|:
name|undo
operator|->
name|time
operator|=
name|g_value_get_uint
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNDO_TYPE
case|:
name|undo
operator|->
name|undo_type
operator|=
name|g_value_get_enum
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIRTY_MASK
case|:
name|undo
operator|->
name|dirty_mask
operator|=
name|g_value_get_flags
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
DECL|function|gimp_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_undo_get_property
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
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
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
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|undo
operator|->
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_TIME
case|:
name|g_value_set_uint
argument_list|(
name|value
argument_list|,
name|undo
operator|->
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNDO_TYPE
case|:
name|g_value_set_enum
argument_list|(
name|value
argument_list|,
name|undo
operator|->
name|undo_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_DIRTY_MASK
case|:
name|g_value_set_flags
argument_list|(
name|value
argument_list|,
name|undo
operator|->
name|dirty_mask
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
DECL|function|gimp_undo_get_memsize (GimpObject * object,gint64 * gui_size)
name|gimp_undo_get_memsize
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
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint64
name|memsize
init|=
literal|0
decl_stmt|;
operator|*
name|gui_size
operator|+=
name|gimp_temp_buf_get_memsize
argument_list|(
name|undo
operator|->
name|preview
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
name|gboolean
DECL|function|gimp_undo_get_popup_size (GimpViewable * viewable,gint width,gint height,gboolean dot_for_dot,gint * popup_width,gint * popup_height)
name|gimp_undo_get_popup_size
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gboolean
name|dot_for_dot
parameter_list|,
name|gint
modifier|*
name|popup_width
parameter_list|,
name|gint
modifier|*
name|popup_height
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview
operator|&&
operator|(
name|undo
operator|->
name|preview
operator|->
name|width
operator|>
name|width
operator|||
name|undo
operator|->
name|preview
operator|->
name|height
operator|>
name|height
operator|)
condition|)
block|{
operator|*
name|popup_width
operator|=
name|undo
operator|->
name|preview
operator|->
name|width
expr_stmt|;
operator|*
name|popup_height
operator|=
name|undo
operator|->
name|preview
operator|->
name|height
expr_stmt|;
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
specifier|static
name|GimpTempBuf
modifier|*
DECL|function|gimp_undo_get_new_preview (GimpViewable * viewable,GimpContext * context,gint width,gint height)
name|gimp_undo_get_new_preview
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpUndo
modifier|*
name|undo
init|=
name|GIMP_UNDO
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview
condition|)
block|{
name|gint
name|preview_width
decl_stmt|;
name|gint
name|preview_height
decl_stmt|;
name|gimp_viewable_calc_preview_size
argument_list|(
name|undo
operator|->
name|preview
operator|->
name|width
argument_list|,
name|undo
operator|->
name|preview
operator|->
name|height
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
operator|&
name|preview_width
argument_list|,
operator|&
name|preview_height
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview_width
operator|<
name|undo
operator|->
name|preview
operator|->
name|width
operator|&&
name|preview_height
operator|<
name|undo
operator|->
name|preview
operator|->
name|height
condition|)
block|{
return|return
name|gimp_temp_buf_scale
argument_list|(
name|undo
operator|->
name|preview
argument_list|,
name|preview_width
argument_list|,
name|preview_height
argument_list|)
return|;
block|}
return|return
name|gimp_temp_buf_copy
argument_list|(
name|undo
operator|->
name|preview
argument_list|)
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
DECL|function|gimp_undo_real_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_undo_real_pop
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
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_real_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_undo_real_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{ }
end_function

begin_function
name|void
DECL|function|gimp_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_undo_pop
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|accum
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|dirty_mask
operator|!=
name|GIMP_DIRTY_NONE
condition|)
block|{
switch|switch
condition|(
name|undo_mode
condition|)
block|{
case|case
name|GIMP_UNDO_MODE_UNDO
case|:
name|gimp_image_clean
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|undo
operator|->
name|dirty_mask
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_UNDO_MODE_REDO
case|:
name|gimp_image_dirty
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|undo
operator|->
name|dirty_mask
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_signal_emit
argument_list|(
name|undo
argument_list|,
name|undo_signals
index|[
name|POP
index|]
argument_list|,
literal|0
argument_list|,
name|undo_mode
argument_list|,
name|accum
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|undo
argument_list|,
name|undo_signals
index|[
name|FREE
index|]
argument_list|,
literal|0
argument_list|,
name|undo_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|typedef|GimpUndoIdle
typedef|typedef
name|struct
name|_GimpUndoIdle
name|GimpUndoIdle
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpUndoIdle
struct|struct
name|_GimpUndoIdle
block|{
DECL|member|undo
name|GimpUndo
modifier|*
name|undo
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|gimp_undo_idle_free (GimpUndoIdle * idle)
name|gimp_undo_idle_free
parameter_list|(
name|GimpUndoIdle
modifier|*
name|idle
parameter_list|)
block|{
if|if
condition|(
name|idle
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|idle
operator|->
name|context
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpUndoIdle
argument_list|,
name|idle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_create_preview (GimpUndo * undo,GimpContext * context,gboolean create_now)
name|gimp_undo_create_preview
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|create_now
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview
operator|||
name|undo
operator|->
name|preview_idle_id
condition|)
return|return;
if|if
condition|(
name|create_now
condition|)
block|{
name|gimp_undo_create_preview_private
argument_list|(
name|undo
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpUndoIdle
modifier|*
name|idle
init|=
name|g_slice_new0
argument_list|(
name|GimpUndoIdle
argument_list|)
decl_stmt|;
name|idle
operator|->
name|undo
operator|=
name|undo
expr_stmt|;
if|if
condition|(
name|context
condition|)
name|idle
operator|->
name|context
operator|=
name|g_object_ref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|undo
operator|->
name|preview_idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|GIMP_VIEWABLE_PRIORITY_IDLE
argument_list|,
name|gimp_undo_create_preview_idle
argument_list|,
name|idle
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_undo_idle_free
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_undo_create_preview_idle (gpointer data)
name|gimp_undo_create_preview_idle
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpUndoIdle
modifier|*
name|idle
init|=
name|data
decl_stmt|;
name|GimpUndoStack
modifier|*
name|stack
init|=
name|gimp_image_get_undo_stack
argument_list|(
name|idle
operator|->
name|undo
operator|->
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|idle
operator|->
name|undo
operator|==
name|gimp_undo_stack_peek
argument_list|(
name|stack
argument_list|)
condition|)
block|{
name|gimp_undo_create_preview_private
argument_list|(
name|idle
operator|->
name|undo
argument_list|,
name|idle
operator|->
name|context
argument_list|)
expr_stmt|;
block|}
name|idle
operator|->
name|undo
operator|->
name|preview_idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_undo_create_preview_private (GimpUndo * undo,GimpContext * context)
name|gimp_undo_create_preview_private
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|undo
operator|->
name|image
decl_stmt|;
name|GimpViewable
modifier|*
name|preview_viewable
decl_stmt|;
name|GimpViewSize
name|preview_size
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
switch|switch
condition|(
name|undo
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_GROUP_IMAGE_QUICK_MASK
case|:
case|case
name|GIMP_UNDO_GROUP_MASK
case|:
case|case
name|GIMP_UNDO_MASK
case|:
name|preview_viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|preview_viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
expr_stmt|;
break|break;
block|}
name|preview_size
operator|=
name|image
operator|->
name|gimp
operator|->
name|config
operator|->
name|undo_preview_size
expr_stmt|;
if|if
condition|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|<=
name|preview_size
operator|&&
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|<=
name|preview_size
condition|)
block|{
name|width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|>
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
condition|)
block|{
name|width
operator|=
name|preview_size
expr_stmt|;
name|height
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|*
name|preview_size
operator|/
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|height
operator|=
name|preview_size
expr_stmt|;
name|width
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|*
name|preview_size
operator|/
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
name|undo
operator|->
name|preview
operator|=
name|gimp_viewable_get_new_preview
argument_list|(
name|preview_viewable
argument_list|,
name|context
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_undo_refresh_preview (GimpUndo * undo,GimpContext * context)
name|gimp_undo_refresh_preview
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|context
operator|==
name|NULL
operator|||
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|undo
operator|->
name|preview_idle_id
condition|)
return|return;
if|if
condition|(
name|undo
operator|->
name|preview
condition|)
block|{
name|gimp_temp_buf_unref
argument_list|(
name|undo
operator|->
name|preview
argument_list|)
expr_stmt|;
name|undo
operator|->
name|preview
operator|=
name|NULL
expr_stmt|;
name|gimp_undo_create_preview
argument_list|(
name|undo
argument_list|,
name|context
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_undo_type_to_name (GimpUndoType type)
name|gimp_undo_type_to_name
parameter_list|(
name|GimpUndoType
name|type
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|desc
decl_stmt|;
if|if
condition|(
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_UNDO_TYPE
argument_list|,
name|type
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|desc
argument_list|,
name|NULL
argument_list|)
condition|)
return|return
name|desc
return|;
else|else
return|return
literal|""
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_undo_is_weak (GimpUndo * undo)
name|gimp_undo_is_weak
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
if|if
condition|(
operator|!
name|undo
condition|)
return|return
name|FALSE
return|;
switch|switch
condition|(
name|undo
operator|->
name|undo_type
condition|)
block|{
case|case
name|GIMP_UNDO_GROUP_ITEM_VISIBILITY
case|:
case|case
name|GIMP_UNDO_GROUP_ITEM_PROPERTIES
case|:
case|case
name|GIMP_UNDO_GROUP_LAYER_APPLY_MASK
case|:
case|case
name|GIMP_UNDO_ITEM_VISIBILITY
case|:
case|case
name|GIMP_UNDO_LAYER_MODE
case|:
case|case
name|GIMP_UNDO_LAYER_OPACITY
case|:
case|case
name|GIMP_UNDO_LAYER_MASK_APPLY
case|:
case|case
name|GIMP_UNDO_LAYER_MASK_SHOW
case|:
return|return
name|TRUE
return|;
break|break;
default|default:
break|break;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_undo_get_age:  * @undo:  *  * Return value: the time in seconds since this undo item was created  */
end_comment

begin_function
name|gint
DECL|function|gimp_undo_get_age (GimpUndo * undo)
name|gimp_undo_get_age
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
name|guint
name|now
init|=
name|time
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|now
operator|>=
name|undo
operator|->
name|time
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|now
operator|-
name|undo
operator|->
name|time
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_undo_reset_age:  * @undo:  *  * Changes the creation time of this undo item to the current time.  */
end_comment

begin_function
name|void
DECL|function|gimp_undo_reset_age (GimpUndo * undo)
name|gimp_undo_reset_age
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_UNDO
argument_list|(
name|undo
argument_list|)
argument_list|)
expr_stmt|;
name|undo
operator|->
name|time
operator|=
name|time
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|undo
argument_list|)
argument_list|,
literal|"time"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

