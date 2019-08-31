begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpimage.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|"libgimpbase/gimpwire.h"
end_include

begin_comment
comment|/* FIXME kill this include */
end_comment

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_include
include|#
directive|include
file|"gimpplugin-private.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure-private.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29f7bb570103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID
name|PROP_ID
block|,
DECL|enumerator|N_PROPS
name|N_PROPS
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpImagePrivate
struct|struct
name|_GimpImagePrivate
block|{
DECL|member|id
name|gint
name|id
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_image_set_property
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
name|gimp_image_get_property
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

begin_macro
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpImage
argument_list|,
argument|gimp_image
argument_list|,
argument|G_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_image_parent_class
end_define

begin_decl_stmt
specifier|static
name|GParamSpec
modifier|*
name|props
index|[
name|N_PROPS
index|]
init|=
block|{
name|NULL
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_image_class_init (GimpImageClass * klass)
name|gimp_image_class_init
parameter_list|(
name|GimpImageClass
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
name|object_class
operator|->
name|set_property
operator|=
name|gimp_image_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_image_get_property
expr_stmt|;
name|props
index|[
name|PROP_ID
index|]
operator|=
name|g_param_spec_int
argument_list|(
literal|"id"
argument_list|,
literal|"The image id"
argument_list|,
literal|"The image id for internal use"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
expr_stmt|;
name|g_object_class_install_properties
argument_list|(
name|object_class
argument_list|,
name|N_PROPS
argument_list|,
name|props
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_init (GimpImage * image)
name|gimp_image_init
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|image
operator|->
name|priv
operator|=
name|gimp_image_get_instance_private
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_image_set_property
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
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
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
name|PROP_ID
case|:
name|image
operator|->
name|priv
operator|->
name|id
operator|=
name|g_value_get_int
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
DECL|function|gimp_image_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_image_get_property
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
name|GimpImage
modifier|*
name|image
init|=
name|GIMP_IMAGE
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
name|PROP_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|image
operator|->
name|priv
operator|->
name|id
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
comment|/* Public API */
end_comment

begin_comment
comment|/**  * gimp_image_get_id:  * @image: The image.  *  * Returns: the image ID.  *  * Since: 3.0  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_image_get_id (GimpImage * image)
name|gimp_image_get_id
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
return|return
name|image
condition|?
name|image
operator|->
name|priv
operator|->
name|id
else|:
operator|-
literal|1
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_by_id:  * @image_id: The image id.  *  * Returns: (nullable) (transfer none): a #GimpImage for @image_id or  *          %NULL if @image_id does not represent a valid image.  *          The object belongs to libgimp and you must not modify  *          or unref it.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_image_get_by_id (gint32 image_id)
name|gimp_image_get_by_id
parameter_list|(
name|gint32
name|image_id
parameter_list|)
block|{
if|if
condition|(
name|image_id
operator|>
literal|0
condition|)
block|{
name|GimpPlugIn
modifier|*
name|plug_in
init|=
name|gimp_get_plug_in
argument_list|()
decl_stmt|;
if|if
condition|(
name|plug_in
condition|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|_gimp_plug_in_get_procedure
argument_list|(
name|plug_in
argument_list|)
decl_stmt|;
return|return
name|_gimp_procedure_get_image
argument_list|(
name|procedure
argument_list|,
name|image_id
argument_list|)
return|;
block|}
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE
argument_list|,
literal|"id"
argument_list|,
name|image_id
argument_list|,
name|NULL
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_is_valid:  * @image: The image to check.  *  * Returns TRUE if the image is valid.  *  * This procedure checks if the given image is valid and refers to  * an existing image.  *  * Returns: Whether the image is valid.  *  * Since: 2.4  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_is_valid (GimpImage * image)
name|gimp_image_is_valid
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
return|return
name|gimp_image_id_is_valid
argument_list|(
name|gimp_image_get_id
argument_list|(
name|image
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_get_images:  * @num_images: (out): The number of images in the returned array.  *  * Returns the list of images currently open.  *  * This procedure returns the list of images currently open in GIMP.  *  * Returns: (array length=num_images) (transfer container):  *          The list of images currently open.  *          The returned array must be freed with g_free(). Image  *          elements belong to libgimp and must not be freed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GimpImage
modifier|*
modifier|*
DECL|function|gimp_get_images (gint * num_images)
name|gimp_get_images
parameter_list|(
name|gint
modifier|*
name|num_images
parameter_list|)
block|{
name|GimpImage
modifier|*
modifier|*
name|images
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_list
argument_list|(
name|num_images
argument_list|)
expr_stmt|;
name|images
operator|=
name|g_new
argument_list|(
name|GimpImage
operator|*
argument_list|,
operator|*
name|num_images
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_images
condition|;
name|i
operator|++
control|)
name|images
index|[
name|i
index|]
operator|=
name|gimp_image_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|images
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_list_images:  *  * Returns the list of images currently open.  *  * This procedure returns the list of images currently open in GIMP.  *  * Returns: (element-type GimpImage) (transfer container):  *          The list of images currently open.  *          The returned list must be freed with g_list_free(). Image  *          elements belong to libgimp and must not be freed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_list_images (void)
name|gimp_list_images
parameter_list|(
name|void
parameter_list|)
block|{
name|GList
modifier|*
name|images
init|=
name|NULL
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|num_images
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_list
argument_list|(
operator|&
name|num_images
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_images
condition|;
name|i
operator|++
control|)
name|images
operator|=
name|g_list_prepend
argument_list|(
name|images
argument_list|,
name|gimp_image_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|images
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_layers:  * @image:      The image.  * @num_layers: (out): The number of layers in the returned array.  *  * Returns the list of layers contained in the specified image.  *  * This procedure returns the list of layers contained in the specified  * image. The order of layers is from topmost to bottommost.  *  * Returns: (array length=num_layers) (transfer container):  *          The list of layers contained in the image.  *          The returned array must be freed with g_free(). Layer  *          elements belong to libgimp and must not be freed.  **/
end_comment

begin_function
name|GimpLayer
modifier|*
modifier|*
DECL|function|gimp_image_get_layers (GimpImage * image,gint * num_layers)
name|gimp_image_get_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_layers
parameter_list|)
block|{
name|GimpLayer
modifier|*
modifier|*
name|layers
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_layers
argument_list|(
name|image
argument_list|,
name|num_layers
argument_list|)
expr_stmt|;
name|layers
operator|=
name|g_new
argument_list|(
name|GimpLayer
operator|*
argument_list|,
operator|*
name|num_layers
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_layers
condition|;
name|i
operator|++
control|)
name|layers
index|[
name|i
index|]
operator|=
name|GIMP_LAYER
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|layers
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_channels:  * @image:        The image.  * @num_channels: (out): The number of channels in the returned array.  *  * Returns the list of channels contained in the specified image.  *  * This procedure returns the list of channels contained in the  * specified image. This does not include the selection mask, or layer  * masks. The order is from topmost to bottommost. Note that  * "channels" are custom channels and do not include the image's color  * components.  *  * Returns: (array length=num_channels) (transfer container):  *          The list of channels contained in the image.  *          The returned array must be freed with g_free(). Channel  *          elements belong to libgimp and must not be freed.  **/
end_comment

begin_function
name|GimpChannel
modifier|*
modifier|*
DECL|function|gimp_image_get_channels (GimpImage * image,gint * num_channels)
name|gimp_image_get_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_channels
parameter_list|)
block|{
name|GimpChannel
modifier|*
modifier|*
name|channels
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_channels
argument_list|(
name|image
argument_list|,
name|num_channels
argument_list|)
expr_stmt|;
name|channels
operator|=
name|g_new
argument_list|(
name|GimpChannel
operator|*
argument_list|,
operator|*
name|num_channels
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_channels
condition|;
name|i
operator|++
control|)
name|channels
index|[
name|i
index|]
operator|=
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|channels
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_vectors:  * @image:        The image.  * @num_vectors: (out): The number of vectors in the returned array.  *  * Returns the list of vectors contained in the specified image.  *  * This procedure returns the list of vectors contained in the  * specified image.  *  * Returns: (array length=num_vectors) (transfer container):  *          The list of vectors contained in the image.  *          The returned array must be freed with g_free(). Vectors  *          elements belong to libgimp and must not be freed.  **/
end_comment

begin_function
name|GimpVectors
modifier|*
modifier|*
DECL|function|gimp_image_get_vectors (GimpImage * image,gint * num_vectors)
name|gimp_image_get_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_vectors
parameter_list|)
block|{
name|GimpVectors
modifier|*
modifier|*
name|vectors
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_vectors
argument_list|(
name|image
argument_list|,
name|num_vectors
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|g_new
argument_list|(
name|GimpVectors
operator|*
argument_list|,
operator|*
name|num_vectors
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|*
name|num_vectors
condition|;
name|i
operator|++
control|)
name|vectors
index|[
name|i
index|]
operator|=
name|GIMP_VECTORS
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|vectors
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_list_layers:  * @image: The image.  *  * Returns the list of layers contained in the specified image.  *  * This procedure returns the list of layers contained in the specified  * image. The order of layers is from topmost to bottommost.  *  * Returns: (element-type GimpImage) (transfer container):  *          The list of layers contained in the image.  *          The returned list must be freed with g_list_free(). Layer  *          elements belong to libgimp and must not be freed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_list_layers (GimpImage * image)
name|gimp_image_list_layers
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GList
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|num_layers
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_layers
argument_list|(
name|image
argument_list|,
operator|&
name|num_layers
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_layers
condition|;
name|i
operator|++
control|)
name|layers
operator|=
name|g_list_prepend
argument_list|(
name|layers
argument_list|,
name|GIMP_LAYER
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|layers
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_list_channels:  * @image: The image.  *  * Returns the list of channels contained in the specified image.  *  * This procedure returns the list of channels contained in the  * specified image. This does not include the selection mask, or layer  * masks. The order is from topmost to bottommost. Note that  * "channels" are custom channels and do not include the image's  * color components.  *  * Returns: (element-type GimpChannel) (transfer container):  *          The list of channels contained in the image.  *          The returned list must be freed with g_list_free(). Channel  *          elements belong to libgimp and must not be freed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_list_channels (GimpImage * image)
name|gimp_image_list_channels
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GList
modifier|*
name|channels
init|=
name|NULL
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|num_channels
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_channels
argument_list|(
name|image
argument_list|,
operator|&
name|num_channels
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_channels
condition|;
name|i
operator|++
control|)
name|channels
operator|=
name|g_list_prepend
argument_list|(
name|channels
argument_list|,
name|GIMP_CHANNEL
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|channels
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_list_vectors:  * @image: The image.  *  * Returns the list of vectors contained in the specified image.  *  * This procedure returns the list of vectors contained in the  * specified image.  *  * Returns: (element-type GimpVectors) (transfer container):  *          The list of vectors contained in the image.  *          The returned value must be freed with g_list_free(). Vectors  *          elements belong to libgimp and must not be freed.  *  * Since: 3.0  **/
end_comment

begin_function
name|GList
modifier|*
DECL|function|gimp_image_list_vectors (GimpImage * image)
name|gimp_image_list_vectors
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GList
modifier|*
name|vectors
init|=
name|NULL
decl_stmt|;
name|gint
modifier|*
name|ids
decl_stmt|;
name|gint
name|num_vectors
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|ids
operator|=
name|_gimp_image_get_vectors
argument_list|(
name|image
argument_list|,
operator|&
name|num_vectors
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_vectors
condition|;
name|i
operator|++
control|)
name|vectors
operator|=
name|g_list_prepend
argument_list|(
name|vectors
argument_list|,
name|GIMP_VECTORS
argument_list|(
name|gimp_item_get_by_id
argument_list|(
name|ids
index|[
name|i
index|]
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ids
argument_list|)
expr_stmt|;
return|return
name|g_list_reverse
argument_list|(
name|vectors
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_colormap:  * @image:      The image.  * @num_colors: Returns the number of colors in the colormap array.  *  * Returns the image's colormap  *  * This procedure returns an actual pointer to the image's colormap, as  * well as the number of colors contained in the colormap. If the image  * is not of base type INDEXED, this pointer will be NULL.  *  * Returns: The image's colormap.  */
end_comment

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_colormap (GimpImage * image,gint * num_colors)
name|gimp_image_get_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|num_colors
parameter_list|)
block|{
name|gint
name|num_bytes
decl_stmt|;
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|cmap
operator|=
name|_gimp_image_get_colormap
argument_list|(
name|image
argument_list|,
operator|&
name|num_bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|num_colors
condition|)
operator|*
name|num_colors
operator|=
name|num_bytes
operator|/
literal|3
expr_stmt|;
return|return
name|cmap
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_set_colormap:  * @image:      The image.  * @colormap:   The new colormap values.  * @num_colors: Number of colors in the colormap array.  *  * Sets the entries in the image's colormap.  *  * This procedure sets the entries in the specified image's colormap.  * The number of colors is specified by the "num_colors" parameter  * and corresponds to the number of INT8 triples that must be contained  * in the "cmap" array.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_colormap (GimpImage * image,const guchar * colormap,gint num_colors)
name|gimp_image_set_colormap
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|guchar
modifier|*
name|colormap
parameter_list|,
name|gint
name|num_colors
parameter_list|)
block|{
return|return
name|_gimp_image_set_colormap
argument_list|(
name|image
argument_list|,
name|num_colors
operator|*
literal|3
argument_list|,
name|colormap
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_thumbnail_data:  * @image:  The image.  * @width:  (inout): The requested thumbnail width.  * @height: (inout): The requested thumbnail height.  * @bpp:    (out): The previews bpp.  *  * Get a thumbnail of an image.  *  * This function gets data from which a thumbnail of an image preview  * can be created. Maximum x or y dimension is 1024 pixels. The pixels  * are returned in RGB[A] or GRAY[A] format. The bpp return value  * gives the number of bytes per pixel in the image.  *  * Returns: (transfer full): the thumbnail data.  **/
end_comment

begin_function
name|guchar
modifier|*
DECL|function|gimp_image_get_thumbnail_data (GimpImage * image,gint * width,gint * height,gint * bpp)
name|gimp_image_get_thumbnail_data
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|,
name|gint
modifier|*
name|bpp
parameter_list|)
block|{
name|gint
name|ret_width
decl_stmt|;
name|gint
name|ret_height
decl_stmt|;
name|guchar
modifier|*
name|image_data
decl_stmt|;
name|gint
name|data_size
decl_stmt|;
name|_gimp_image_thumbnail
argument_list|(
name|image
argument_list|,
operator|*
name|width
argument_list|,
operator|*
name|height
argument_list|,
operator|&
name|ret_width
argument_list|,
operator|&
name|ret_height
argument_list|,
name|bpp
argument_list|,
operator|&
name|data_size
argument_list|,
operator|&
name|image_data
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|ret_width
expr_stmt|;
operator|*
name|height
operator|=
name|ret_height
expr_stmt|;
return|return
name|image_data
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_thumbnail:  * @image:  the image ID  * @width:  the requested thumbnail width  (<= 1024 pixels)  * @height: the requested thumbnail height (<= 1024 pixels)  * @alpha:  how to handle an alpha channel  *  * Retrieves a thumbnail pixbuf for the image identified by @image->priv->id.  * The thumbnail will be not larger than the requested size.  *  * Returns: (transfer full): a new #GdkPixbuf  *  * Since: 2.2  **/
end_comment

begin_function
name|GdkPixbuf
modifier|*
DECL|function|gimp_image_get_thumbnail (GimpImage * image,gint width,gint height,GimpPixbufTransparency alpha)
name|gimp_image_get_thumbnail
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpPixbufTransparency
name|alpha
parameter_list|)
block|{
name|gint
name|thumb_width
init|=
name|width
decl_stmt|;
name|gint
name|thumb_height
init|=
name|height
decl_stmt|;
name|gint
name|thumb_bpp
decl_stmt|;
name|guchar
modifier|*
name|data
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|>
literal|0
operator|&&
name|width
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|>
literal|0
operator|&&
name|height
operator|<=
literal|1024
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_image_get_thumbnail_data
argument_list|(
name|image
argument_list|,
operator|&
name|thumb_width
argument_list|,
operator|&
name|thumb_height
argument_list|,
operator|&
name|thumb_bpp
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
condition|)
return|return
name|_gimp_pixbuf_from_data
argument_list|(
name|data
argument_list|,
name|thumb_width
argument_list|,
name|thumb_height
argument_list|,
name|thumb_bpp
argument_list|,
name|alpha
argument_list|)
return|;
else|else
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_get_metadata:  * @image: The image.  *  * Returns the image's metadata.  *  * Returns exif/iptc/xmp metadata from the image.  *  * Returns: (nullable) (transfer full): The exif/ptc/xmp metadata,  *          or %NULL if there is none.  *  * Since: 2.10  **/
end_comment

begin_function
name|GimpMetadata
modifier|*
DECL|function|gimp_image_get_metadata (GimpImage * image)
name|gimp_image_get_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpMetadata
modifier|*
name|metadata
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|metadata_string
decl_stmt|;
name|metadata_string
operator|=
name|_gimp_image_get_metadata
argument_list|(
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata_string
condition|)
block|{
name|metadata
operator|=
name|gimp_metadata_deserialize
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
block|}
return|return
name|metadata
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_image_set_metadata:  * @image:    The image.  * @metadata: The exif/ptc/xmp metadata.  *  * Set the image's metadata.  *  * Sets exif/iptc/xmp metadata on the image, or deletes it if  * @metadata is %NULL.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_image_set_metadata (GimpImage * image,GimpMetadata * metadata)
name|gimp_image_set_metadata
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpMetadata
modifier|*
name|metadata
parameter_list|)
block|{
name|gchar
modifier|*
name|metadata_string
init|=
name|NULL
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
if|if
condition|(
name|metadata
condition|)
name|metadata_string
operator|=
name|gimp_metadata_serialize
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
name|success
operator|=
name|_gimp_image_set_metadata
argument_list|(
name|image
argument_list|,
name|metadata_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata_string
condition|)
name|g_free
argument_list|(
name|metadata_string
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

