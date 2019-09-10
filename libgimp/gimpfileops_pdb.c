begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpfileops_pdb.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
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
comment|/**  * SECTION: gimpfileops  * @title: gimpfileops  * @short_description: Image file operations (load, save, etc.)  *  * Image file operations (load, save, etc.)  **/
end_comment

begin_comment
comment|/**  * gimp_file_load:  * @run_mode: The run mode.  * @filename: The name of the file to load.  * @raw_filename: The name as entered by the user.  *  * Loads an image file by invoking the right load handler.  *  * This procedure invokes the correct file load handler using magic if  * possible, and falling back on the file's extension and/or prefix if  * not. The name of the file to load is typically a full pathname, and  * the name entered is what the user actually typed before prepending a  * directory path. The reason for this is that if the user types  * https://www.gimp.org/foo.png he wants to fetch a URL, and the full  * pathname will not look like a URL.  *  * Returns: (transfer none): The output image.  **/
end_comment

begin_function
name|GimpImage
modifier|*
DECL|function|gimp_file_load (GimpRunMode run_mode,const gchar * filename,const gchar * raw_filename)
name|gimp_file_load
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
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
name|GimpImage
modifier|*
name|image
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|run_mode
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|raw_filename
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
literal|"gimp-file-load"
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
name|image
operator|=
name|GIMP_VALUES_GET_IMAGE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_load_layer:  * @run_mode: The run mode.  * @image: Destination image.  * @filename: The name of the file to load.  *  * Loads an image file as a layer for an existing image.  *  * This procedure behaves like the file-load procedure but opens the  * specified image as a layer for an existing image. The returned layer  * needs to be added to the existing image with  * gimp_image_insert_layer().  *  * Returns: (transfer none): The layer created when loading the image file.  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpLayer
modifier|*
DECL|function|gimp_file_load_layer (GimpRunMode run_mode,GimpImage * image,const gchar * filename)
name|gimp_file_load_layer
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
name|GimpLayer
modifier|*
name|layer
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|run_mode
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
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
literal|"gimp-file-load-layer"
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
name|layer
operator|=
name|GIMP_VALUES_GET_LAYER
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|layer
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_load_layers:  * @run_mode: The run mode.  * @image: Destination image.  * @filename: The name of the file to load.  * @num_layers: (out): The number of loaded layers.  *  * Loads an image file as layers for an existing image.  *  * This procedure behaves like the file-load procedure but opens the  * specified image as layers for an existing image. The returned layers  * needs to be added to the existing image with  * gimp_image_insert_layer().  *  * Returns: (array length=num_layers) (element-type GimpLayer) (transfer container):  *          The list of loaded layers.  *          The returned value must be freed with g_free().  *  * Since: 2.4  **/
end_comment

begin_function
name|GimpLayer
modifier|*
modifier|*
DECL|function|gimp_file_load_layers (GimpRunMode run_mode,GimpImage * image,const gchar * filename,gint * num_layers)
name|gimp_file_load_layers
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gint
modifier|*
name|num_layers
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
name|GimpLayer
modifier|*
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|run_mode
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
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
literal|"gimp-file-load-layers"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
operator|*
name|num_layers
operator|=
literal|0
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
block|{
operator|*
name|num_layers
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|{
name|GimpObjectArray
modifier|*
name|a
init|=
name|g_value_get_boxed
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|a
condition|)
name|layers
operator|=
name|g_memdup
argument_list|(
name|a
operator|->
name|data
argument_list|,
name|a
operator|->
name|length
operator|*
sizeof|sizeof
argument_list|(
name|gpointer
argument_list|)
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|layers
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_save:  * @run_mode: The run mode.  * @image: Input image.  * @drawable: Drawable to save.  * @filename: The name of the file to save the image in.  * @raw_filename: The name as entered by the user.  *  * Saves a file by extension.  *  * This procedure invokes the correct file save handler according to  * the file's extension and/or prefix. The name of the file to save is  * typically a full pathname, and the name entered is what the user  * actually typed before prepending a directory path. The reason for  * this is that if the user types https://www.gimp.org/foo.png she  * wants to fetch a URL, and the full pathname will not look like a  * URL.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_file_save (GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,const gchar * filename,const gchar * raw_filename)
name|gimp_file_save
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|run_mode
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|GIMP_TYPE_DRAWABLE
argument_list|,
name|drawable
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|raw_filename
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
literal|"gimp-file-save"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_save_thumbnail:  * @image: The image.  * @filename: The name of the file the thumbnail belongs to.  *  * Saves a thumbnail for the given image  *  * This procedure saves a thumbnail for the given image according to  * the Free Desktop Thumbnail Managing Standard. The thumbnail is saved  * so that it belongs to the file with the given filename. This means  * you have to save the image under this name first, otherwise this  * procedure will fail. This procedure may become useful if you want to  * explicitly save a thumbnail with a file.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_file_save_thumbnail (GimpImage * image,const gchar * filename)
name|gimp_file_save_thumbnail
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|filename
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
literal|"gimp-file-save-thumbnail"
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|success
operator|=
name|GIMP_VALUES_GET_ENUM
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
expr_stmt|;
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

