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
comment|/**  * gimp_file_load:  * @run_mode: The run mode.  * @filename: The name of the file to load.  * @raw_filename: The name as entered by the user.  *  * Loads an image file by invoking the right load handler.  *  * This procedure invokes the correct file load handler using magic if  * possible, and falling back on the file's extension and/or prefix if  * not. The name of the file to load is typically a full pathname, and  * the name entered is what the user actually typed before prepending a  * directory path. The reason for this is that if the user types  * https://www.gimp.org/foo.png he wants to fetch a URL, and the full  * pathname will not look like a URL.  *  * Returns: The output image.  **/
end_comment

begin_function
name|gint32
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
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|raw_filename
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|image_ID
operator|=
name|gimp_value_get_image_id
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
name|image_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_load_layer:  * @run_mode: The run mode.  * @image_ID: Destination image.  * @filename: The name of the file to load.  *  * Loads an image file as a layer for an existing image.  *  * This procedure behaves like the file-load procedure but opens the  * specified image as a layer for an existing image. The returned layer  * needs to be added to the existing image with  * gimp_image_insert_layer().  *  * Returns: The layer created when loading the image file.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_file_load_layer (GimpRunMode run_mode,gint32 image_ID,const gchar * filename)
name|gimp_file_load_layer
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_ID
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
name|gint32
name|layer_ID
init|=
operator|-
literal|1
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|layer_ID
operator|=
name|gimp_value_get_layer_id
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
name|layer_ID
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_load_layers:  * @run_mode: The run mode.  * @image_ID: Destination image.  * @filename: The name of the file to load.  * @num_layers: The number of loaded layers.  *  * Loads an image file as layers for an existing image.  *  * This procedure behaves like the file-load procedure but opens the  * specified image as layers for an existing image. The returned layers  * needs to be added to the existing image with  * gimp_image_insert_layer().  *  * Returns: (transfer full) The list of loaded layers.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint
modifier|*
DECL|function|gimp_file_load_layers (GimpRunMode run_mode,gint32 image_ID,const gchar * filename,gint * num_layers)
name|gimp_file_load_layers
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_ID
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
name|gint
modifier|*
name|layer_ids
init|=
name|NULL
decl_stmt|;
name|args
operator|=
name|gimp_value_array_new_from_types
argument_list|(
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
argument_list|)
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
operator|*
name|num_layers
operator|=
name|g_value_get_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|layer_ids
operator|=
name|gimp_value_dup_int32_array
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_value_array_unref
argument_list|(
name|return_vals
argument_list|)
expr_stmt|;
return|return
name|layer_ids
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_save:  * @run_mode: The run mode.  * @image_ID: Input image.  * @drawable_ID: Drawable to save.  * @filename: The name of the file to save the image in.  * @raw_filename: The name as entered by the user.  *  * Saves a file by extension.  *  * This procedure invokes the correct file save handler according to  * the file's extension and/or prefix. The name of the file to save is  * typically a full pathname, and the name entered is what the user  * actually typed before prepending a directory path. The reason for  * this is that if the user types https://www.gimp.org/foo.png she  * wants to fetch a URL, and the full pathname will not look like a  * URL.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_file_save (GimpRunMode run_mode,gint32 image_ID,gint32 drawable_ID,const gchar * filename,const gchar * raw_filename)
name|gimp_file_save
parameter_list|(
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
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
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|GIMP_TYPE_DRAWABLE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|gimp_value_set_drawable_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
argument_list|,
name|raw_filename
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_file_save_thumbnail:  * @image_ID: The image.  * @filename: The name of the file the thumbnail belongs to.  *  * Saves a thumbnail for the given image  *  * This procedure saves a thumbnail for the given image according to  * the Free Desktop Thumbnail Managing Standard. The thumbnail is saved  * so that it belongs to the file with the given filename. This means  * you have to save the image under this name first, otherwise this  * procedure will fail. This procedure may become useful if you want to  * explicitly save a thumbnail with a file.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_file_save_thumbnail (gint32 image_ID,const gchar * filename)
name|gimp_file_save_thumbnail
parameter_list|(
name|gint32
name|image_ID
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
name|GIMP_TYPE_IMAGE_ID
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_magic_load_handler:  * @procedure_name: The name of the procedure to be used for loading.  * @extensions: comma separated list of extensions this handler can load (i.e. \"jpg,jpeg\").  * @prefixes: comma separated list of prefixes this handler can load (i.e. \"http:,ftp:\").  * @magics: comma separated list of magic file information this handler can load (i.e. \"0,string,GIF\").  *  * Registers a file load handler procedure.  *  * Registers a procedural database procedure to be called to load files  * of a particular file format using magic file information.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_magic_load_handler (const gchar * procedure_name,const gchar * extensions,const gchar * prefixes,const gchar * magics)
name|gimp_register_magic_load_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
parameter_list|,
specifier|const
name|gchar
modifier|*
name|magics
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|extensions
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|prefixes
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|,
name|magics
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-magic-load-handler"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_load_handler:  * @procedure_name: The name of the procedure to be used for loading.  * @extensions: comma separated list of extensions this handler can load (i.e. \"jpg,jpeg\").  * @prefixes: comma separated list of prefixes this handler can load (i.e. \"http:,ftp:\").  *  * Registers a file load handler procedure.  *  * Registers a procedural database procedure to be called to load files  * of a particular file format.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_load_handler (const gchar * procedure_name,const gchar * extensions,const gchar * prefixes)
name|gimp_register_load_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|extensions
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|prefixes
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-load-handler"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_save_handler:  * @procedure_name: The name of the procedure to be used for saving.  * @extensions: comma separated list of extensions this handler can save (i.e. \"jpg,jpeg\").  * @prefixes: comma separated list of prefixes this handler can save (i.e. \"http:,ftp:\").  *  * Registers a file save handler procedure.  *  * Registers a procedural database procedure to be called to save files  * in a particular file format.  *  * Returns: TRUE on success.  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_save_handler (const gchar * procedure_name,const gchar * extensions,const gchar * prefixes)
name|gimp_register_save_handler
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extensions
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prefixes
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|extensions
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
argument_list|,
name|prefixes
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-save-handler"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_file_handler_priority:  * @procedure_name: The name of the procedure to set the priority of.  * @priority: The procedure priority.  *  * Sets the priority of a file handler procedure.  *  * Sets the priority of a file handler procedure. When more than one  * procedure matches a given file, the procedure with the lowest  * priority is used; if more than one procedure has the lowest  * priority, it is unspecified which one of them is used. The default  * priority for file handler procedures is 0.  *  * Returns: TRUE on success.  *  * Since: 2.10.6  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_file_handler_priority (const gchar * procedure_name,gint priority)
name|gimp_register_file_handler_priority
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|gint
name|priority
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
name|G_TYPE_STRING
argument_list|,
name|GIMP_TYPE_INT32
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|priority
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-file-handler-priority"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_file_handler_mime:  * @procedure_name: The name of the procedure to associate a MIME type with.  * @mime_types: A comma-separated list of MIME types, such as \"image/jpeg\".  *  * Associates MIME types with a file handler procedure.  *  * Registers MIME types for a file handler procedure. This allows GIMP  * to determine the MIME type of the file opened or saved using this  * procedure. It is recommended that only one MIME type is registered  * per file procedure; when registering more than one MIME type, GIMP  * will associate the first one with files opened or saved with this  * procedure.  *  * Returns: TRUE on success.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_file_handler_mime (const gchar * procedure_name,const gchar * mime_types)
name|gimp_register_file_handler_mime
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_types
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|mime_types
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-file-handler-mime"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_file_handler_uri:  * @procedure_name: The name of the procedure to enable URIs for.  *  * Registers a file handler procedure as capable of handling URIs.  *  * Registers a file handler procedure as capable of handling URIs. This  * allows GIMP to call the procedure directly for all kinds of URIs,  * and the 'filename' traditionally passed to file procedures turns  * into an URI.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_file_handler_uri (const gchar * procedure_name)
name|gimp_register_file_handler_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-file-handler-uri"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_file_handler_raw:  * @procedure_name: The name of the procedure to enable raw handling for.  *  * Registers a file handler procedure as capable of handling raw camera  * files.  *  * Registers a file handler procedure as capable of handling raw  * digital camera files. Use this procedure only to register raw load  * handlers, calling it on a save handler will generate an error.  *  * Returns: TRUE on success.  *  * Since: 2.10  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_file_handler_raw (const gchar * procedure_name)
name|gimp_register_file_handler_raw
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|procedure_name
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-file-handler-raw"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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
comment|/**  * gimp_register_thumbnail_loader:  * @load_proc: The name of the procedure the thumbnail loader with.  * @thumb_proc: The name of the thumbnail load procedure.  *  * Associates a thumbnail loader with a file load procedure.  *  * Some file formats allow for embedded thumbnails, other file formats  * contain a scalable image or provide the image data in different  * resolutions. A file plug-in for such a format may register a special  * procedure that allows GIMP to load a thumbnail preview of the image.  * This procedure is then associated with the standard load procedure  * using this function.  *  * Returns: TRUE on success.  *  * Since: 2.2  **/
end_comment

begin_function
name|gboolean
DECL|function|gimp_register_thumbnail_loader (const gchar * load_proc,const gchar * thumb_proc)
name|gimp_register_thumbnail_loader
parameter_list|(
specifier|const
name|gchar
modifier|*
name|load_proc
parameter_list|,
specifier|const
name|gchar
modifier|*
name|thumb_proc
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
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_NONE
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|,
name|load_proc
argument_list|)
expr_stmt|;
name|g_value_set_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|thumb_proc
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure_with_array
argument_list|(
literal|"gimp-register-thumbnail-loader"
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
name|g_value_get_enum
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|0
argument_list|)
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

