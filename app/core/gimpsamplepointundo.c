begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-sample-points.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepoint.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepointundo.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28c9b4e40103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SAMPLE_POINT
name|PROP_SAMPLE_POINT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_sample_point_undo_constructor
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
name|gimp_sample_point_undo_set_property
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
name|gimp_sample_point_undo_get_property
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
name|void
name|gimp_sample_point_undo_pop
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
name|gimp_sample_point_undo_free
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSamplePointUndo,gimp_sample_point_undo,GIMP_TYPE_UNDO)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSamplePointUndo
argument_list|,
argument|gimp_sample_point_undo
argument_list|,
argument|GIMP_TYPE_UNDO
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_sample_point_undo_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_sample_point_undo_class_init
parameter_list|(
name|GimpSamplePointUndoClass
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
name|GimpUndoClass
modifier|*
name|undo_class
init|=
name|GIMP_UNDO_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_sample_point_undo_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_sample_point_undo_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_sample_point_undo_get_property
expr_stmt|;
name|undo_class
operator|->
name|pop
operator|=
name|gimp_sample_point_undo_pop
expr_stmt|;
name|undo_class
operator|->
name|free
operator|=
name|gimp_sample_point_undo_free
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_POINT
argument_list|,
name|g_param_spec_boxed
argument_list|(
literal|"sample-point"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_SAMPLE_POINT
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
DECL|function|gimp_sample_point_undo_init (GimpSamplePointUndo * undo)
name|gimp_sample_point_undo_init
parameter_list|(
name|GimpSamplePointUndo
modifier|*
name|undo
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_sample_point_undo_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_sample_point_undo_constructor
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
name|GimpSamplePointUndo
modifier|*
name|sample_point_undo
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
name|sample_point_undo
operator|=
name|GIMP_SAMPLE_POINT_UNDO
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|sample_point_undo
operator|->
name|sample_point
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|sample_point_undo
operator|->
name|x
operator|=
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|x
expr_stmt|;
name|sample_point_undo
operator|->
name|y
operator|=
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|y
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_undo_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_sample_point_undo_set_property
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
name|GimpSamplePointUndo
modifier|*
name|sample_point_undo
init|=
name|GIMP_SAMPLE_POINT_UNDO
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
name|PROP_SAMPLE_POINT
case|:
name|sample_point_undo
operator|->
name|sample_point
operator|=
name|g_value_dup_boxed
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
DECL|function|gimp_sample_point_undo_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_sample_point_undo_get_property
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
name|GimpSamplePointUndo
modifier|*
name|sample_point_undo
init|=
name|GIMP_SAMPLE_POINT_UNDO
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
name|PROP_SAMPLE_POINT
case|:
name|g_value_set_boxed
argument_list|(
name|value
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
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
DECL|function|gimp_sample_point_undo_pop (GimpUndo * undo,GimpUndoMode undo_mode,GimpUndoAccumulator * accum)
name|gimp_sample_point_undo_pop
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
name|GimpSamplePointUndo
modifier|*
name|sample_point_undo
init|=
name|GIMP_SAMPLE_POINT_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|gint
name|y
decl_stmt|;
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
name|x
operator|=
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|y
expr_stmt|;
comment|/*  add and move sample points manually (nor using the    *  gimp_image_sample_point API), because we might be in the middle    *  of an image resizing undo group and the sample point's position    *  might be temporarily out of image.    */
if|if
condition|(
name|x
operator|==
operator|-
literal|1
condition|)
block|{
name|undo
operator|->
name|image
operator|->
name|sample_points
operator|=
name|g_list_append
argument_list|(
name|undo
operator|->
name|image
operator|->
name|sample_points
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|x
operator|=
name|sample_point_undo
operator|->
name|x
expr_stmt|;
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|y
operator|=
name|sample_point_undo
operator|->
name|y
expr_stmt|;
name|gimp_sample_point_ref
argument_list|(
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_sample_point_added
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
name|gimp_image_update_sample_point
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|sample_point_undo
operator|->
name|x
operator|==
operator|-
literal|1
condition|)
block|{
name|gimp_image_remove_sample_point
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_update_sample_point
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|x
operator|=
name|sample_point_undo
operator|->
name|x
expr_stmt|;
name|sample_point_undo
operator|->
name|sample_point
operator|->
name|y
operator|=
name|sample_point_undo
operator|->
name|y
expr_stmt|;
name|gimp_image_update_sample_point
argument_list|(
name|undo
operator|->
name|image
argument_list|,
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
block|}
name|sample_point_undo
operator|->
name|x
operator|=
name|x
expr_stmt|;
name|sample_point_undo
operator|->
name|y
operator|=
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_undo_free (GimpUndo * undo,GimpUndoMode undo_mode)
name|gimp_sample_point_undo_free
parameter_list|(
name|GimpUndo
modifier|*
name|undo
parameter_list|,
name|GimpUndoMode
name|undo_mode
parameter_list|)
block|{
name|GimpSamplePointUndo
modifier|*
name|sample_point_undo
init|=
name|GIMP_SAMPLE_POINT_UNDO
argument_list|(
name|undo
argument_list|)
decl_stmt|;
if|if
condition|(
name|sample_point_undo
operator|->
name|sample_point
condition|)
block|{
name|gimp_sample_point_unref
argument_list|(
name|sample_point_undo
operator|->
name|sample_point
argument_list|)
expr_stmt|;
name|sample_point_undo
operator|->
name|sample_point
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

