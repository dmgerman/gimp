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
file|"libgimpmath/gimpmath.h"
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
file|"gimpimage-arrange.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-guides.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpguide.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GList
modifier|*
name|sort_by_offset
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|compute_offsets
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|compute_offset
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|offset_compare
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_image_arrange_objects:  * @image:                The #GimpImage to which the objects belong.  * @list:                 A #GList of objects to be aligned.  * @alignment:            The point on each target object to bring into alignment.  * @reference:            The #GObject to align the targets with, or #NULL.  * @reference_alignment:  The point on the reference object to align the target item with..  * @offset:               How much to shift the target from perfect alignment..  *  * This function shifts the positions of a set of target objects,  * which can be "items" or guides, to bring them into a specified type  * of alignment with a reference object, which can be an item, guide,  * or image.  If the requested alignment does not make sense (i.e.,  * trying to align a vertical guide vertically), nothing happens and  * no error message is generated.  *  * The objects in the list are sorted into increasing order before  * being arranged, where the order is defined by the type of alignment  * being requested.  If the @reference argument is #NULL, then the  * first object in the sorted list is used as reference.  *  * When there are multiple target objects, they are arranged so that  * the spacing between consecutive ones is given by the argument  * @offset but for HFILL and VFILL - in this case, @offset works as an  * internal margin for the distribution (and it can be negative).  */
end_comment

begin_function
name|void
DECL|function|gimp_image_arrange_objects (GimpImage * image,GList * list,GimpAlignmentType alignment,GObject * reference,GimpAlignmentType reference_alignment,gint offset)
name|gimp_image_arrange_objects
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|,
name|GObject
modifier|*
name|reference
parameter_list|,
name|GimpAlignmentType
name|reference_alignment
parameter_list|,
name|gint
name|offset
parameter_list|)
block|{
name|gboolean
name|do_x
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|do_y
init|=
name|FALSE
decl_stmt|;
name|gint
name|z0
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|object_list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|G_IS_OBJECT
argument_list|(
name|reference
argument_list|)
operator|||
name|reference
operator|==
name|NULL
argument_list|)
expr_stmt|;
comment|/* get offsets used for sorting */
switch|switch
condition|(
name|alignment
condition|)
block|{
comment|/* order vertically for horizontal alignment */
case|case
name|GIMP_ALIGN_LEFT
case|:
case|case
name|GIMP_ALIGN_HCENTER
case|:
case|case
name|GIMP_ALIGN_RIGHT
case|:
name|do_x
operator|=
name|TRUE
expr_stmt|;
name|compute_offsets
argument_list|(
name|list
argument_list|,
name|GIMP_ALIGN_TOP
argument_list|)
expr_stmt|;
break|break;
comment|/* order horizontally for horizontal arrangement */
case|case
name|GIMP_ARRANGE_LEFT
case|:
case|case
name|GIMP_ARRANGE_HCENTER
case|:
case|case
name|GIMP_ARRANGE_RIGHT
case|:
case|case
name|GIMP_ARRANGE_HFILL
case|:
name|do_x
operator|=
name|TRUE
expr_stmt|;
name|compute_offsets
argument_list|(
name|list
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
break|break;
comment|/* order horizontally for vertical alignment */
case|case
name|GIMP_ALIGN_TOP
case|:
case|case
name|GIMP_ALIGN_VCENTER
case|:
case|case
name|GIMP_ALIGN_BOTTOM
case|:
name|do_y
operator|=
name|TRUE
expr_stmt|;
name|compute_offsets
argument_list|(
name|list
argument_list|,
name|GIMP_ALIGN_LEFT
argument_list|)
expr_stmt|;
break|break;
comment|/* order vertically for vertical arrangement */
case|case
name|GIMP_ARRANGE_TOP
case|:
case|case
name|GIMP_ARRANGE_VCENTER
case|:
case|case
name|GIMP_ARRANGE_BOTTOM
case|:
case|case
name|GIMP_ARRANGE_VFILL
case|:
name|do_y
operator|=
name|TRUE
expr_stmt|;
name|compute_offsets
argument_list|(
name|list
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
break|break;
block|}
name|object_list
operator|=
name|sort_by_offset
argument_list|(
name|list
argument_list|)
expr_stmt|;
comment|/* now get offsets used for aligning */
name|compute_offsets
argument_list|(
name|list
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
if|if
condition|(
name|reference
operator|==
name|NULL
condition|)
block|{
name|reference
operator|=
name|G_OBJECT
argument_list|(
name|object_list
operator|->
name|data
argument_list|)
expr_stmt|;
name|object_list
operator|=
name|g_list_next
argument_list|(
name|object_list
argument_list|)
expr_stmt|;
name|reference_alignment
operator|=
name|alignment
expr_stmt|;
block|}
else|else
block|{
name|compute_offset
argument_list|(
name|reference
argument_list|,
name|reference_alignment
argument_list|)
expr_stmt|;
block|}
name|z0
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|reference
argument_list|,
literal|"align-offset"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|object_list
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n
decl_stmt|;
name|gint
name|distr_width
init|=
literal|0
decl_stmt|;
name|gint
name|distr_height
init|=
literal|0
decl_stmt|;
name|gdouble
name|fill_offset
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|reference_alignment
operator|==
name|GIMP_ARRANGE_HFILL
condition|)
block|{
name|distr_width
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|reference
argument_list|,
literal|"align-width"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* The offset parameter works as an internal margin */
name|fill_offset
operator|=
operator|(
name|distr_width
operator|-
literal|2
operator|*
name|offset
operator|)
operator|/
name|g_list_length
argument_list|(
name|object_list
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|reference_alignment
operator|==
name|GIMP_ARRANGE_VFILL
condition|)
block|{
name|distr_height
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|reference
argument_list|,
literal|"align-height"
argument_list|)
argument_list|)
expr_stmt|;
name|fill_offset
operator|=
operator|(
name|distr_height
operator|-
literal|2
operator|*
name|offset
operator|)
operator|/
name|g_list_length
argument_list|(
name|object_list
argument_list|)
expr_stmt|;
block|}
comment|/* FIXME: undo group type is wrong */
name|gimp_image_undo_group_start
argument_list|(
name|image
argument_list|,
name|GIMP_UNDO_GROUP_ITEM_DISPLACE
argument_list|,
name|C_
argument_list|(
literal|"undo-type"
argument_list|,
literal|"Arrange Objects"
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|object_list
operator|,
name|n
operator|=
literal|1
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|n
operator|++
control|)
block|{
name|GObject
modifier|*
name|target
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gint
name|xtranslate
init|=
literal|0
decl_stmt|;
name|gint
name|ytranslate
init|=
literal|0
decl_stmt|;
name|gint
name|z1
decl_stmt|;
name|z1
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|target
argument_list|,
literal|"align-offset"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|reference_alignment
operator|==
name|GIMP_ARRANGE_HFILL
condition|)
block|{
name|gint
name|width
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|target
argument_list|,
literal|"align-width"
argument_list|)
argument_list|)
decl_stmt|;
name|xtranslate
operator|=
name|ROUND
argument_list|(
name|z0
operator|-
name|z1
operator|+
operator|(
name|n
operator|-
literal|0.5
operator|)
operator|*
name|fill_offset
operator|-
name|width
operator|/
literal|2.0
operator|+
name|offset
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|reference_alignment
operator|==
name|GIMP_ARRANGE_VFILL
condition|)
block|{
name|gint
name|height
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|target
argument_list|,
literal|"align-height"
argument_list|)
argument_list|)
decl_stmt|;
name|ytranslate
operator|=
name|ROUND
argument_list|(
name|z0
operator|-
name|z1
operator|+
operator|(
name|n
operator|-
literal|0.5
operator|)
operator|*
name|fill_offset
operator|-
name|height
operator|/
literal|2.0
operator|+
name|offset
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* the normal computing, when we don't depend on the                 * width or height of the reference object                 */
block|{
if|if
condition|(
name|do_x
condition|)
name|xtranslate
operator|=
name|z0
operator|-
name|z1
operator|+
name|n
operator|*
name|offset
expr_stmt|;
if|if
condition|(
name|do_y
condition|)
name|ytranslate
operator|=
name|z0
operator|-
name|z1
operator|+
name|n
operator|*
name|offset
expr_stmt|;
block|}
comment|/* now actually align the target object */
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|target
argument_list|)
condition|)
block|{
name|gimp_item_translate
argument_list|(
name|GIMP_ITEM
argument_list|(
name|target
argument_list|)
argument_list|,
name|xtranslate
argument_list|,
name|ytranslate
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_GUIDE
argument_list|(
name|target
argument_list|)
condition|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|GIMP_GUIDE
argument_list|(
name|target
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gimp_guide_get_orientation
argument_list|(
name|guide
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|z1
operator|+
name|xtranslate
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|gimp_image_move_guide
argument_list|(
name|image
argument_list|,
name|guide
argument_list|,
name|z1
operator|+
name|ytranslate
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|object_list
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|sort_by_offset (GList * list)
name|sort_by_offset
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|)
block|{
return|return
name|g_list_sort
argument_list|(
name|g_list_copy
argument_list|(
name|list
argument_list|)
argument_list|,
name|offset_compare
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|offset_compare (gconstpointer a,gconstpointer b)
name|offset_compare
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
name|gint
name|offset1
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|a
argument_list|)
argument_list|,
literal|"align-offset"
argument_list|)
argument_list|)
decl_stmt|;
name|gint
name|offset2
init|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|b
argument_list|)
argument_list|,
literal|"align-offset"
argument_list|)
argument_list|)
decl_stmt|;
return|return
name|offset1
operator|-
name|offset2
return|;
block|}
end_function

begin_comment
comment|/* this function computes the position of the alignment point  * for each object in the list, and attaches it to the  * object as object data.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|compute_offsets (GList * list,GimpAlignmentType alignment)
name|compute_offsets
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|)
block|{
name|GList
modifier|*
name|l
decl_stmt|;
for|for
control|(
name|l
operator|=
name|list
init|;
name|l
condition|;
name|l
operator|=
name|g_list_next
argument_list|(
name|l
argument_list|)
control|)
name|compute_offset
argument_list|(
name|l
operator|->
name|data
argument_list|,
name|alignment
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|compute_offset (GObject * object,GimpAlignmentType alignment)
name|compute_offset
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GimpAlignmentType
name|alignment
parameter_list|)
block|{
name|gint
name|object_offset_x
init|=
literal|0
decl_stmt|;
name|gint
name|object_offset_y
init|=
literal|0
decl_stmt|;
name|gint
name|object_height
init|=
literal|0
decl_stmt|;
name|gint
name|object_width
init|=
literal|0
decl_stmt|;
name|gint
name|offset
init|=
literal|0
decl_stmt|;
if|if
condition|(
name|GIMP_IS_IMAGE
argument_list|(
name|object
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|object_offset_x
operator|=
literal|0
expr_stmt|;
name|object_offset_y
operator|=
literal|0
expr_stmt|;
name|object_height
operator|=
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|object_width
operator|=
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_ITEM
argument_list|(
name|object
argument_list|)
condition|)
block|{
name|GimpItem
modifier|*
name|item
init|=
name|GIMP_ITEM
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_item_bounds
argument_list|(
name|item
argument_list|,
operator|&
name|object_offset_x
argument_list|,
operator|&
name|object_offset_y
argument_list|,
operator|&
name|object_width
argument_list|,
operator|&
name|object_height
argument_list|)
expr_stmt|;
name|gimp_item_get_offset
argument_list|(
name|item
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|object_offset_x
operator|+=
name|off_x
expr_stmt|;
name|object_offset_y
operator|+=
name|off_y
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IS_GUIDE
argument_list|(
name|object
argument_list|)
condition|)
block|{
name|GimpGuide
modifier|*
name|guide
init|=
name|GIMP_GUIDE
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gimp_guide_get_orientation
argument_list|(
name|guide
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|object_offset_x
operator|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|object_width
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|object_offset_y
operator|=
name|gimp_guide_get_position
argument_list|(
name|guide
argument_list|)
expr_stmt|;
name|object_height
operator|=
literal|0
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
else|else
block|{
name|g_printerr
argument_list|(
literal|"Alignment object is not an image, item or guide.\n"
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|alignment
condition|)
block|{
case|case
name|GIMP_ALIGN_LEFT
case|:
case|case
name|GIMP_ARRANGE_LEFT
case|:
case|case
name|GIMP_ARRANGE_HFILL
case|:
name|offset
operator|=
name|object_offset_x
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_HCENTER
case|:
case|case
name|GIMP_ARRANGE_HCENTER
case|:
name|offset
operator|=
name|object_offset_x
operator|+
name|object_width
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_RIGHT
case|:
case|case
name|GIMP_ARRANGE_RIGHT
case|:
name|offset
operator|=
name|object_offset_x
operator|+
name|object_width
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_TOP
case|:
case|case
name|GIMP_ARRANGE_TOP
case|:
case|case
name|GIMP_ARRANGE_VFILL
case|:
name|offset
operator|=
name|object_offset_y
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_VCENTER
case|:
case|case
name|GIMP_ARRANGE_VCENTER
case|:
name|offset
operator|=
name|object_offset_y
operator|+
name|object_height
operator|/
literal|2
expr_stmt|;
break|break;
case|case
name|GIMP_ALIGN_BOTTOM
case|:
case|case
name|GIMP_ARRANGE_BOTTOM
case|:
name|offset
operator|=
name|object_offset_y
operator|+
name|object_height
expr_stmt|;
break|break;
default|default:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
block|}
name|g_object_set_data
argument_list|(
name|object
argument_list|,
literal|"align-offset"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|offset
argument_list|)
argument_list|)
expr_stmt|;
comment|/* These are only used for HFILL and VFILL, but since the call to    * gimp_image_arrange_objects allows for two different alignments    * (object and reference_alignment) we better be on the safe side in    * case they differ.  (the current implementation of the align tool    * always pass the same value to both parameters)    */
name|g_object_set_data
argument_list|(
name|object
argument_list|,
literal|"align-width"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|object_width
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|object
argument_list|,
literal|"align-height"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|object_height
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

