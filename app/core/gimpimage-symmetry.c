begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimage-symmetry.c  * Copyright (C) 2015 Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpsymmetry.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-symmetry.h"
end_include

begin_include
include|#
directive|include
file|"gimpsymmetry-mirror.h"
end_include

begin_comment
comment|/**  * gimp_image_symmetry_list:  *  * Returns a list of #GType of all existing symmetries.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_symmetry_list (void)
name|gimp_image_symmetry_list
parameter_list|(
name|void
parameter_list|)
block|{
name|GList
modifier|*
name|list
init|=
name|NULL
decl_stmt|;
name|list
operator|=
name|g_list_prepend
argument_list|(
name|list
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_TYPE_MIRROR
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_new:  * @image: the #GimpImage  * @type:  the #GType of the symmetry  *  * Creates a new #GimpSymmetry of @type attached to @image.  *  * Returns: the new #GimpSymmetry.  **/
end_comment

begin_function
name|GimpSymmetry
modifier|*
DECL|function|gimp_image_symmetry_new (GimpImage * image,GType type)
name|gimp_image_symmetry_new
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
block|{
name|GimpSymmetry
modifier|*
name|sym
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|type
operator|!=
name|G_TYPE_NONE
condition|)
block|{
name|sym
operator|=
name|g_object_new
argument_list|(
name|type
argument_list|,
literal|"image"
argument_list|,
name|image
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sym
operator|->
name|type
operator|=
name|type
expr_stmt|;
block|}
return|return
name|sym
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_add:  * @image: the #GimpImage  * @type:  the #GType of the symmetry  *  * Add a symmetry of type @type to @image and make it the  * selected transformation.  **/
end_comment

begin_function
name|void
DECL|function|gimp_image_symmetry_add (GimpImage * image,GimpSymmetry * sym)
name|gimp_image_symmetry_add
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
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
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|private
operator|->
name|symmetries
operator|=
name|g_list_prepend
argument_list|(
name|private
operator|->
name|symmetries
argument_list|,
name|sym
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_remove:  * @image:   the #GimpImage  * @sym: the #GimpSymmetry  *  * Remove @sym from the list of symmetries of @image.  * If it was the selected transformation, unselect it first.  **/
end_comment

begin_function
name|void
DECL|function|gimp_image_symmetry_remove (GimpImage * image,GimpSymmetry * sym)
name|gimp_image_symmetry_remove
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSymmetry
modifier|*
name|sym
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SYMMETRY
argument_list|(
name|sym
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|selected_symmetry
operator|==
name|sym
condition|)
name|gimp_image_symmetry_select
argument_list|(
name|image
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|private
operator|->
name|symmetries
operator|=
name|g_list_remove
argument_list|(
name|private
operator|->
name|symmetries
argument_list|,
name|sym
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|sym
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_get:  * @image: the #GimpImage  *  * Returns: the list of #GimpSymmetry set on @image.  * The returned list belongs to @image and should not be freed.  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_symmetry_get (GimpImage * image)
name|gimp_image_symmetry_get
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|symmetries
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_select:  * @image: the #GimpImage  * @type:  the #GType of the symmetry  *  * Select the symmetry of type @type.  * Using the GType allows to select a transformation without  * knowing whether one of the same @type was already created.  *  * Returns TRUE on success, FALSE if no such symmetry was found.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_symmetry_select (GimpImage * image,GType type)
name|gimp_image_symmetry_select
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GType
name|type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|image
argument_list|,
literal|"symmetry"
argument_list|,
name|type
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_symmetry_selected:  * @image: the #GimpImage  *  * Returns the #GimpSymmetry transformation selected on @image.  **/
end_comment

begin_function
name|GimpSymmetry
modifier|*
DECL|function|gimp_image_symmetry_selected (GimpImage * image)
name|gimp_image_symmetry_selected
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
specifier|static
name|GimpImage
modifier|*
name|last_image
init|=
name|NULL
decl_stmt|;
specifier|static
name|GimpSymmetry
modifier|*
name|identity
init|=
name|NULL
decl_stmt|;
name|GimpImagePrivate
modifier|*
name|private
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|last_image
operator|!=
name|image
condition|)
block|{
if|if
condition|(
name|identity
condition|)
name|g_object_unref
argument_list|(
name|identity
argument_list|)
expr_stmt|;
name|identity
operator|=
name|gimp_image_symmetry_new
argument_list|(
name|image
argument_list|,
name|GIMP_TYPE_SYMMETRY
argument_list|)
expr_stmt|;
block|}
name|private
operator|=
name|GIMP_IMAGE_GET_PRIVATE
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|private
operator|->
name|selected_symmetry
condition|?
name|private
operator|->
name|selected_symmetry
else|:
name|identity
return|;
block|}
end_function

end_unit

