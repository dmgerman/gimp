begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpvectors.c  * Copyright (C) 2002 Simon Budig<simon@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"glib-object.h"
end_include

begin_include
include|#
directive|include
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"gimpstroke.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectors-preview.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_vectors_class_init
parameter_list|(
name|GimpVectorsClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_init
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vectors_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gsize
name|gimp_vectors_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpItemClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_vectors_get_type (void)
name|gimp_vectors_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|vectors_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|vectors_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|vectors_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpVectorsClass
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
name|gimp_vectors_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpVectors
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_vectors_init
block|,       }
decl_stmt|;
name|vectors_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_ITEM
argument_list|,
literal|"GimpVectors"
argument_list|,
operator|&
name|vectors_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|vectors_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_class_init (GimpVectorsClass * klass)
name|gimp_vectors_class_init
parameter_list|(
name|GimpVectorsClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpObjectClass
modifier|*
name|gimp_object_class
decl_stmt|;
name|GimpViewableClass
modifier|*
name|viewable_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_object_class
operator|=
name|GIMP_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|viewable_class
operator|=
name|GIMP_VIEWABLE_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_vectors_finalize
expr_stmt|;
name|gimp_object_class
operator|->
name|get_memsize
operator|=
name|gimp_vectors_get_memsize
expr_stmt|;
name|viewable_class
operator|->
name|get_new_preview
operator|=
name|gimp_vectors_get_new_preview
expr_stmt|;
name|klass
operator|->
name|changed
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|stroke_add
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|stroke_get
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|stroke_get_next
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|stroke_get_length
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|anchor_get
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_length
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|get_distance
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|interpolate
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|make_bezier
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_init (GimpVectors * vectors)
name|gimp_vectors_init
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|vectors
operator|->
name|strokes
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_empty_stmt
empty_stmt|;
end_empty_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_finalize (GObject * object)
name|gimp_vectors_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: implement gimp_vectors_finalize()
endif|#
directive|endif
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
name|gsize
DECL|function|gimp_vectors_get_memsize (GimpObject * object)
name|gimp_vectors_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|gsize
name|memsize
init|=
literal|0
decl_stmt|;
name|vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|object
argument_list|)
expr_stmt|;
for|for
control|(
name|stroke
operator|=
name|vectors
operator|->
name|strokes
init|;
name|stroke
condition|;
name|stroke
operator|=
name|stroke
operator|->
name|next
control|)
name|memsize
operator|+=
name|gimp_object_get_memsize
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|stroke
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
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_vectors_new (GimpImage * gimage,const gchar * name)
name|gimp_vectors_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_VECTORS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_item_configure
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|gimage
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|vectors
return|;
block|}
end_function

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_vectors_copy (const GimpVectors * vectors,GType new_type,gboolean add_alpha)
name|gimp_vectors_copy
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GType
name|new_type
parameter_list|,
name|gboolean
name|add_alpha
comment|/* unused */
parameter_list|)
block|{
name|GimpVectors
modifier|*
name|new_vectors
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|new_type
argument_list|,
name|GIMP_TYPE_VECTORS
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|new_vectors
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_item_copy
argument_list|(
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|new_type
argument_list|,
name|add_alpha
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: implement gimp_vectors_copy()
endif|#
directive|endif
return|return
name|new_vectors
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_vectors_copy_strokes (const GimpVectors * src_vectors,GimpVectors * dest_vectors)
name|gimp_vectors_copy_strokes
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|src_vectors
parameter_list|,
name|GimpVectors
modifier|*
name|dest_vectors
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|src_vectors
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|dest_vectors
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|FIXME: implement gimp_vectors_copy_strokes()
endif|#
directive|endif
block|}
end_function

begin_comment
comment|/* Calling the virtual functions */
end_comment

begin_function
name|GimpAnchor
modifier|*
DECL|function|gimp_vectors_anchor_get (const GimpVectors * vectors,const GimpCoords * coord,GimpStroke ** ret_stroke)
name|gimp_vectors_anchor_get
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|,
name|GimpStroke
modifier|*
modifier|*
name|ret_stroke
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|anchor_get
condition|)
return|return
name|vectors_class
operator|->
name|anchor_get
argument_list|(
name|vectors
argument_list|,
name|coord
argument_list|,
name|ret_stroke
argument_list|)
return|;
else|else
block|{
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|mindist
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
init|=
name|NULL
decl_stmt|,
modifier|*
name|minanchor
init|=
name|NULL
decl_stmt|;
name|mindist
operator|=
operator|-
literal|1
expr_stmt|;
for|for
control|(
name|stroke
operator|=
name|vectors
operator|->
name|strokes
init|;
name|stroke
condition|;
name|stroke
operator|=
name|stroke
operator|->
name|next
control|)
block|{
name|anchor
operator|=
name|gimp_stroke_anchor_get
argument_list|(
name|stroke
argument_list|,
name|coord
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
condition|)
block|{
name|dx
operator|=
name|coord
operator|->
name|x
operator|-
name|anchor
operator|->
name|position
operator|.
name|x
expr_stmt|;
name|dy
operator|=
name|coord
operator|->
name|y
operator|-
name|anchor
operator|->
name|position
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|mindist
operator|>
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
operator|||
name|mindist
operator|<
literal|0
condition|)
block|{
name|mindist
operator|=
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
expr_stmt|;
name|minanchor
operator|=
name|anchor
expr_stmt|;
if|if
condition|(
name|ret_stroke
condition|)
operator|*
name|ret_stroke
operator|=
name|stroke
expr_stmt|;
block|}
block|}
block|}
return|return
name|minanchor
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_vectors_stroke_add (GimpVectors * vectors,GimpStroke * stroke)
name|gimp_vectors_stroke_add
parameter_list|(
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpStroke
modifier|*
name|stroke
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_STROKE
argument_list|(
name|stroke
argument_list|)
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|stroke_add
condition|)
block|{
name|vectors_class
operator|->
name|stroke_add
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|stroke
operator|->
name|next
operator|=
name|vectors
operator|->
name|strokes
expr_stmt|;
name|vectors
operator|->
name|strokes
operator|=
name|stroke
expr_stmt|;
name|g_object_ref
argument_list|(
name|stroke
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpStroke
modifier|*
DECL|function|gimp_vectors_stroke_get (const GimpVectors * vectors,const GimpCoords * coord)
name|gimp_vectors_stroke_get
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|stroke_get
condition|)
return|return
name|vectors_class
operator|->
name|stroke_get
argument_list|(
name|vectors
argument_list|,
name|coord
argument_list|)
return|;
else|else
block|{
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|mindist
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
decl_stmt|;
name|GimpStroke
modifier|*
name|minstroke
init|=
name|NULL
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
init|=
name|NULL
decl_stmt|;
name|mindist
operator|=
operator|-
literal|1
expr_stmt|;
name|stroke
operator|=
name|GIMP_STROKE
argument_list|(
name|vectors
operator|->
name|strokes
argument_list|)
expr_stmt|;
while|while
condition|(
name|stroke
condition|)
block|{
name|anchor
operator|=
name|gimp_stroke_anchor_get
argument_list|(
name|stroke
argument_list|,
name|coord
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
condition|)
block|{
name|dx
operator|=
name|coord
operator|->
name|x
operator|-
name|anchor
operator|->
name|position
operator|.
name|x
expr_stmt|;
name|dy
operator|=
name|coord
operator|->
name|y
operator|-
name|anchor
operator|->
name|position
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|mindist
operator|>
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
operator|||
name|mindist
operator|<
literal|0
condition|)
block|{
name|mindist
operator|=
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
expr_stmt|;
name|minstroke
operator|=
name|stroke
expr_stmt|;
block|}
block|}
name|stroke
operator|=
name|stroke
operator|->
name|next
expr_stmt|;
block|}
return|return
name|minstroke
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GimpStroke
modifier|*
DECL|function|gimp_vectors_stroke_get_next (const GimpVectors * vectors,const GimpStroke * prev)
name|gimp_vectors_stroke_get_next
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|prev
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|stroke_get_next
condition|)
return|return
name|vectors_class
operator|->
name|stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|prev
argument_list|)
return|;
else|else
block|{
if|if
condition|(
operator|!
name|prev
condition|)
block|{
return|return
name|vectors
operator|->
name|strokes
return|;
block|}
else|else
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_STROKE
argument_list|(
name|prev
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|prev
operator|->
name|next
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_vectors_stroke_get_length (const GimpVectors * vectors,const GimpStroke * prev)
name|gimp_vectors_stroke_get_length
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|prev
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|stroke_get_length
condition|)
return|return
name|vectors_class
operator|->
name|stroke_get_length
argument_list|(
name|vectors
argument_list|,
name|prev
argument_list|)
return|;
else|else
name|g_printerr
argument_list|(
literal|"gimp_vectors_stroke_get_length: default implementation\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_vectors_get_length (const GimpVectors * vectors,const GimpAnchor * start)
name|gimp_vectors_get_length
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpAnchor
modifier|*
name|start
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|get_length
condition|)
return|return
name|vectors_class
operator|->
name|get_length
argument_list|(
name|vectors
argument_list|,
name|start
argument_list|)
return|;
else|else
name|g_printerr
argument_list|(
literal|"gimp_vectors_get_length: default implementation\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_vectors_get_distance (const GimpVectors * vectors,const GimpCoords * coord)
name|gimp_vectors_get_distance
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coord
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|get_distance
condition|)
return|return
name|vectors_class
operator|->
name|get_distance
argument_list|(
name|vectors
argument_list|,
name|coord
argument_list|)
return|;
else|else
name|g_printerr
argument_list|(
literal|"gimp_vectors_get_distance: default implementation\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_vectors_interpolate (const GimpVectors * vectors,const GimpStroke * stroke,const gdouble precision,const gint max_points,GimpCoords * ret_coords)
name|gimp_vectors_interpolate
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
specifier|const
name|GimpStroke
modifier|*
name|stroke
parameter_list|,
specifier|const
name|gdouble
name|precision
parameter_list|,
specifier|const
name|gint
name|max_points
parameter_list|,
name|GimpCoords
modifier|*
name|ret_coords
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|interpolate
condition|)
return|return
name|vectors_class
operator|->
name|interpolate
argument_list|(
name|vectors
argument_list|,
name|stroke
argument_list|,
name|precision
argument_list|,
name|max_points
argument_list|,
name|ret_coords
argument_list|)
return|;
else|else
name|g_printerr
argument_list|(
literal|"gimp_vectors_interpolate: default implementation\n"
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|GimpVectors
modifier|*
DECL|function|gimp_vectors_make_bezier (const GimpVectors * vectors)
name|gimp_vectors_make_bezier
parameter_list|(
specifier|const
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GimpVectorsClass
modifier|*
name|vectors_class
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vectors_class
operator|=
name|GIMP_VECTORS_GET_CLASS
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors_class
operator|->
name|make_bezier
condition|)
return|return
name|vectors_class
operator|->
name|make_bezier
argument_list|(
name|vectors
argument_list|)
return|;
else|else
name|g_printerr
argument_list|(
literal|"gimp_vectors_make_bezier: default implementation\n"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

