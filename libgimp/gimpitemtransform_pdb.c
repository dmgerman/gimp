begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpitemtransform_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * SECTION: gimpitemtransform  * @title: gimpitemtransform  * @short_description: Functions to perform transformations on items.  *  * Functions to perform transformations on items.  **/
end_comment

begin_comment
comment|/**  * gimp_item_transform_translate:  * @item: The item.  * @off_x: Offset in x direction.  * @off_y: Offset in y direction.  *  * Translate the item by the specified offsets.  *  * This procedure translates the item by the amounts specified in the  * off_x and off_y arguments. These can be negative, and are considered  * offsets from the current position. The offsets will be rounded to  * the nearest pixel unless the item is a path.  *  * If the item is attached to an image and has its linked flag set to  * TRUE, all additional items contained in the image which have the  * linked flag set to TRUE will also be translated by the specified  * offsets.  *  * Returns: (transfer none): The translated item.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_translate (GimpItem * item,gdouble off_x,gdouble off_y)
name|gimp_item_transform_translate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|off_x
parameter_list|,
name|gdouble
name|off_y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|off_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|off_y
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-translate"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_flip_simple:  * @item: The affected item.  * @flip_type: Type of flip.  * @auto_center: Whether to automatically position the axis in the selection center.  * @axis: coord. of flip axis.  *  * Flip the specified item either vertically or horizontally.  *  * This procedure flips the specified item.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then flipped. If auto_center  * is set to TRUE, the flip is around the selection's center.  * Otherwise, the coordinate of the axis needs to be specified. The  * return value is the ID of the flipped floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be flipped around its center if auto_center is set to  * TRUE, otherwise the coordinate of the axis needs to be specified.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be flipped around the same axis. The return  * value will be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The flipped item.  *  * Since: 2.2  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_flip_simple (GimpItem * item,GimpOrientationType flip_type,gboolean auto_center,gdouble axis)
name|gimp_item_transform_flip_simple
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpOrientationType
name|flip_type
parameter_list|,
name|gboolean
name|auto_center
parameter_list|,
name|gdouble
name|axis
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|flip_type
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|auto_center
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|axis
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-flip-simple"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_flip:  * @item: The affected item.  * @x0: horz. coord. of one end of axis.  * @y0: vert. coord. of one end of axis.  * @x1: horz. coord. of other end of axis.  * @y1: vert. coord. of other end of axis.  *  * Flip the specified item around a given line.  *  * This procedure flips the specified item.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then flipped. The axis to  * flip around is specified by specifying two points from that line.  * The return value is the ID of the flipped floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be flipped around the specified axis. Additionally, if the  * item has its linked flag set to TRUE, all additional items contained  * in the image which have the linked flag set to TRUE will also be  * flipped around the same axis. The return value will be equal to the  * item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The flipped item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_flip (GimpItem * item,gdouble x0,gdouble y0,gdouble x1,gdouble y1)
name|gimp_item_transform_flip
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y1
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-flip"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_perspective:  * @item: The affected item.  * @x0: The new x coordinate of upper-left corner of original bounding box.  * @y0: The new y coordinate of upper-left corner of original bounding box.  * @x1: The new x coordinate of upper-right corner of original bounding box.  * @y1: The new y coordinate of upper-right corner of original bounding box.  * @x2: The new x coordinate of lower-left corner of original bounding box.  * @y2: The new y coordinate of lower-left corner of original bounding box.  * @x3: The new x coordinate of lower-right corner of original bounding box.  * @y3: The new y coordinate of lower-right corner of original bounding box.  *  * Perform a possibly non-affine transformation on the specified item.  *  * This procedure performs a possibly non-affine transformation on the  * specified item by allowing the corners of the original bounding box  * to be arbitrarily remapped to any values.  *  * The 4 coordinates specify the new locations of each corner of the  * original bounding box. By specifying these values, any affine  * transformation (rotation, scaling, translation) can be affected.  * Additionally, these values can be specified such that the resulting  * transformed item will appear to have been projected via a  * perspective transform.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then transformed as  * specified. The return value is the ID of the transformed floating  * selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be transformed according to the specified mapping.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be transformed the same way. The return value  * will be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The transformed item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_perspective (GimpItem * item,gdouble x0,gdouble y0,gdouble x1,gdouble y1,gdouble x2,gdouble y2,gdouble x3,gdouble y3)
name|gimp_item_transform_perspective
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|gdouble
name|x3
parameter_list|,
name|gdouble
name|y3
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x2
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y2
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x3
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y3
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-perspective"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_rotate_simple:  * @item: The affected item.  * @rotate_type: Type of rotation.  * @auto_center: Whether to automatically rotate around the selection center.  * @center_x: The hor. coordinate of the center of rotation.  * @center_y: The vert. coordinate of the center of rotation.  *  * Rotate the specified item about given coordinates through the  * specified angle.  *  * This function rotates the specified item.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then rotated by the  * specified amount. If auto_center is set to TRUE, the rotation is  * around the selection's center. Otherwise, the coordinate of the  * center point needs to be specified. The return value is the ID of  * the rotated floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be rotated around its center if auto_center is set to  * TRUE, otherwise the coordinate of the center point needs to be  * specified. Additionally, if the item has its linked flag set to  * TRUE, all additional items contained in the image which have the  * linked flag set to TRUE will also be rotated around the same center  * point. The return value will be equal to the item ID supplied as  * input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The rotated item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_rotate_simple (GimpItem * item,GimpRotationType rotate_type,gboolean auto_center,gdouble center_x,gdouble center_y)
name|gimp_item_transform_rotate_simple
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpRotationType
name|rotate_type
parameter_list|,
name|gboolean
name|auto_center
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|GIMP_TYPE_ROTATION_TYPE
argument_list|,
name|rotate_type
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|auto_center
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|center_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|center_y
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-rotate-simple"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_rotate:  * @item: The affected item.  * @angle: The angle of rotation (radians).  * @auto_center: Whether to automatically rotate around the selection center.  * @center_x: The hor. coordinate of the center of rotation.  * @center_y: The vert. coordinate of the center of rotation.  *  * Rotate the specified item about given coordinates through the  * specified angle.  *  * This function rotates the specified item.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then rotated by the  * specified amount. If auto_center is set to TRUE, the rotation is  * around the selection's center. Otherwise, the coordinate of the  * center point needs to be specified. The return value is the ID of  * the rotated floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be rotated around its center if auto_center is set to  * TRUE, otherwise the coordinate of the center point needs to be  * specified. Additionally, if the item has its linked flag set to  * TRUE, all additional items contained in the image which have the  * linked flag set to TRUE will also be rotated around the same center  * point. The return value will be equal to the item ID supplied as  * input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The rotated item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_rotate (GimpItem * item,gdouble angle,gboolean auto_center,gdouble center_x,gdouble center_y)
name|gimp_item_transform_rotate
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gboolean
name|auto_center
parameter_list|,
name|gdouble
name|center_x
parameter_list|,
name|gdouble
name|center_y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|angle
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|auto_center
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|center_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|center_y
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-rotate"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_scale:  * @item: The affected item.  * @x0: The new x coordinate of the upper-left corner of the scaled region.  * @y0: The new y coordinate of the upper-left corner of the scaled region.  * @x1: The new x coordinate of the lower-right corner of the scaled region.  * @y1: The new y coordinate of the lower-right corner of the scaled region.  *  * Scale the specified item.  *  * This procedure scales the specified item.  *  * The 2 coordinates specify the new locations of the top-left and  * bottom-roght corners of the original bounding box.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then scaled as specified.  * The return value is the ID of the scaled floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be scaled according to the specified coordinates.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be scaled the same way. The return value will  * be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The scaled item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_scale (GimpItem * item,gdouble x0,gdouble y0,gdouble x1,gdouble y1)
name|gimp_item_transform_scale
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x0
parameter_list|,
name|gdouble
name|y0
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|x1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|y1
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-scale"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_shear:  * @item: The affected item.  * @shear_type: Type of shear.  * @magnitude: The magnitude of the shear.  *  * Shear the specified item about its center by the specified  * magnitude.  *  * This procedure shears the specified item.  *  * The shear type parameter indicates whether the shear will be applied  * horizontally or vertically. The magnitude can be either positive or  * negative and indicates the extent (in pixels) to shear by.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then sheared as specified.  * The return value is the ID of the sheared floating selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be sheared according to the specified parameters.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be sheared the same way. The return value will  * be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The sheared item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_shear (GimpItem * item,GimpOrientationType shear_type,gdouble magnitude)
name|gimp_item_transform_shear
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|GimpOrientationType
name|shear_type
parameter_list|,
name|gdouble
name|magnitude
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|GIMP_TYPE_ORIENTATION_TYPE
argument_list|,
name|shear_type
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|magnitude
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-shear"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_2d:  * @item: The affected item.  * @source_x: X coordinate of the transformation center.  * @source_y: Y coordinate of the transformation center.  * @scale_x: Amount to scale in x direction.  * @scale_y: Amount to scale in y direction.  * @angle: The angle of rotation (radians).  * @dest_x: X coordinate of where the center goes.  * @dest_y: Y coordinate of where the center goes.  *  * Transform the specified item in 2d.  *  * This procedure transforms the specified item.  *  * The transformation is done by scaling by the x and y scale factors  * about the point (source_x, source_y), then rotating around the same  * point, then translating that point to the new position (dest_x,  * dest_y).  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then transformed as  * specified. The return value is the ID of the transformed floating  * selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be transformed according to the specified parameters.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be transformed the same way. The return value  * will be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The transformed item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_2d (GimpItem * item,gdouble source_x,gdouble source_y,gdouble scale_x,gdouble scale_y,gdouble angle,gdouble dest_x,gdouble dest_y)
name|gimp_item_transform_2d
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|source_x
parameter_list|,
name|gdouble
name|source_y
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|gdouble
name|angle
parameter_list|,
name|gdouble
name|dest_x
parameter_list|,
name|gdouble
name|dest_y
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|source_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|source_y
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|scale_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|scale_y
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|angle
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|dest_x
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|dest_y
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-2d"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_item_transform_matrix:  * @item: The affected item.  * @coeff_0_0: coefficient (0,0) of the transformation matrix.  * @coeff_0_1: coefficient (0,1) of the transformation matrix.  * @coeff_0_2: coefficient (0,2) of the transformation matrix.  * @coeff_1_0: coefficient (1,0) of the transformation matrix.  * @coeff_1_1: coefficient (1,1) of the transformation matrix.  * @coeff_1_2: coefficient (1,2) of the transformation matrix.  * @coeff_2_0: coefficient (2,0) of the transformation matrix.  * @coeff_2_1: coefficient (2,1) of the transformation matrix.  * @coeff_2_2: coefficient (2,2) of the transformation matrix.  *  * Transform the specified item in 2d.  *  * This procedure transforms the specified item.  *  * The transformation is done by assembling a 3x3 matrix from the  * coefficients passed.  *  * If a selection exists and the item is a drawable, the portion of the  * drawable which lies under the selection is cut from the drawable and  * made into a floating selection which is then transformed as  * specified. The return value is the ID of the transformed floating  * selection.  *  * If there is no selection or the item is not a drawable, the entire  * item will be transformed according to the specified matrix.  * Additionally, if the item has its linked flag set to TRUE, all  * additional items contained in the image which have the linked flag  * set to TRUE will also be transformed the same way. The return value  * will be equal to the item ID supplied as input.  *  * This procedure is affected by the following context setters:  * gimp_context_set_interpolation(),  * gimp_context_set_transform_direction(),  * gimp_context_set_transform_resize().  *  * Returns: (transfer none): The transformed item.  *  * Since: 2.8  **/
end_comment

begin_function
name|GimpItem
modifier|*
DECL|function|gimp_item_transform_matrix (GimpItem * item,gdouble coeff_0_0,gdouble coeff_0_1,gdouble coeff_0_2,gdouble coeff_1_0,gdouble coeff_1_1,gdouble coeff_1_2,gdouble coeff_2_0,gdouble coeff_2_1,gdouble coeff_2_2)
name|gimp_item_transform_matrix
parameter_list|(
name|GimpItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|coeff_0_0
parameter_list|,
name|gdouble
name|coeff_0_1
parameter_list|,
name|gdouble
name|coeff_0_2
parameter_list|,
name|gdouble
name|coeff_1_0
parameter_list|,
name|gdouble
name|coeff_1_1
parameter_list|,
name|gdouble
name|coeff_1_2
parameter_list|,
name|gdouble
name|coeff_2_0
parameter_list|,
name|gdouble
name|coeff_2_1
parameter_list|,
name|gdouble
name|coeff_2_2
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|args
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpItem
modifier|*
name|ret_item
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_ITEM
argument_list|,
name|item
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_0_0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_0_1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_0_2
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_1_0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_1_1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_1_2
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_2_0
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_2_1
argument_list|,
name|G_TYPE_DOUBLE
argument_list|,
name|coeff_2_2
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_pdb_run_procedure_array
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|,
literal|"gimp-item-transform-matrix"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|ret_item
operator|=
name|g_value_get_object
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|ret_item
return|;
block|}
end_function

end_unit

