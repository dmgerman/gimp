begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_include
include|#
directive|include
file|"openexr-wrapper.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-exr-load"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-exr"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"0.0.0"
end_define

begin_typedef
DECL|typedef|Exr
typedef|typedef
name|struct
name|_Exr
name|Exr
typedef|;
end_typedef

begin_typedef
DECL|typedef|ExrClass
typedef|typedef
name|struct
name|_ExrClass
name|ExrClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Exr
struct|struct
name|_Exr
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ExrClass
struct|struct
name|_ExrClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|EXR_TYPE
define|#
directive|define
name|EXR_TYPE
value|(exr_get_type ())
end_define

begin_define
DECL|macro|EXR
define|#
directive|define
name|EXR
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXR_TYPE, Exr))
end_define

begin_decl_stmt
name|GType
name|exr_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|GList
modifier|*
name|exr_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpProcedure
modifier|*
name|exr_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|exr_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|sanitize_comment
parameter_list|(
name|gchar
modifier|*
name|comment
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (Exr,exr,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Exr
argument_list|,
argument|exr
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|EXR_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|exr_class_init
parameter_list|(
name|ExrClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPlugInClass
modifier|*
name|plug_in_class
init|=
name|GIMP_PLUG_IN_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|plug_in_class
operator|->
name|query_procedures
operator|=
name|exr_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|exr_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|exr_init (Exr * exr)
name|exr_init
parameter_list|(
name|Exr
modifier|*
name|exr
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|exr_query_procedures (GimpPlugIn * plug_in)
name|exr_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|)
block|{
return|return
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|g_strdup
argument_list|(
name|LOAD_PROC
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|exr_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|exr_create_procedure
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_load_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|exr_load
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"OpenEXR image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads files in the OpenEXR file format"
argument_list|,
literal|"This plug-in loads OpenEXR files. "
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Dominik Ernst<dernst@gmx.de>, "
literal|"Mukund Sivaraman<muks@banu.com>"
argument_list|,
literal|"Dominik Ernst<dernst@gmx.de>, "
literal|"Mukund Sivaraman<muks@banu.com>"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-exr"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"exr"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"0,long,0x762f3101"
argument_list|)
expr_stmt|;
block|}
return|return
name|procedure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|exr_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|exr_load
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|GFile
modifier|*
name|file
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|gpointer
name|run_data
parameter_list|)
block|{
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gegl_init
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_ID
operator|=
name|load_image
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|<
literal|1
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_EXECUTION_ERROR
argument_list|,
name|error
argument_list|)
return|;
name|return_vals
operator|=
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_SUCCESS
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_VALUES_SET_IMAGE
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|load_image (const gchar * filename,gboolean interactive,GError ** error)
name|load_image
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|interactive
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|EXRLoader
modifier|*
name|loader
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|GimpImageBaseType
name|image_type
decl_stmt|;
name|GimpPrecision
name|image_precision
decl_stmt|;
name|gint32
name|image
init|=
operator|-
literal|1
decl_stmt|;
name|GimpImageType
name|layer_type
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|GeglBuffer
modifier|*
name|buffer
init|=
name|NULL
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|tile_height
decl_stmt|;
name|gchar
modifier|*
name|pixels
init|=
name|NULL
decl_stmt|;
name|gint
name|begin
decl_stmt|;
name|gint32
name|success
init|=
name|FALSE
decl_stmt|;
name|gchar
modifier|*
name|comment
init|=
name|NULL
decl_stmt|;
name|GimpColorProfile
modifier|*
name|profile
init|=
name|NULL
decl_stmt|;
name|guchar
modifier|*
name|exif_data
decl_stmt|;
name|guint
name|exif_size
decl_stmt|;
name|guchar
modifier|*
name|xmp_data
decl_stmt|;
name|guint
name|xmp_size
decl_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
name|loader
operator|=
name|exr_loader_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|loader
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error opening file '%s' for reading"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|width
operator|=
name|exr_loader_get_width
argument_list|(
name|loader
argument_list|)
expr_stmt|;
name|height
operator|=
name|exr_loader_get_height
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|width
operator|<
literal|1
operator|)
operator|||
operator|(
name|height
operator|<
literal|1
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error querying image dimensions from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|has_alpha
operator|=
name|exr_loader_has_alpha
argument_list|(
name|loader
argument_list|)
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
switch|switch
condition|(
name|exr_loader_get_precision
argument_list|(
name|loader
argument_list|)
condition|)
block|{
case|case
name|PREC_UINT
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_U32_LINEAR
expr_stmt|;
break|break;
case|case
name|PREC_HALF
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_HALF_LINEAR
expr_stmt|;
break|break;
case|case
name|PREC_FLOAT
case|:
name|image_precision
operator|=
name|GIMP_PRECISION_FLOAT_LINEAR
expr_stmt|;
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error querying image precision from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
switch|switch
condition|(
name|exr_loader_get_image_type
argument_list|(
name|loader
argument_list|)
condition|)
block|{
case|case
name|IMAGE_TYPE_RGB
case|:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|has_alpha
condition|?
name|GIMP_RGBA_IMAGE
else|:
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
name|IMAGE_TYPE_GRAY
case|:
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|has_alpha
condition|?
name|GIMP_GRAYA_IMAGE
else|:
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
default|default:
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error querying image type from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|image
operator|=
name|gimp_image_new_with_precision
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|image_type
argument_list|,
name|image_precision
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
operator|==
operator|-
literal|1
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Could not create new image for '%s': %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|gimp_pdb_get_last_error
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
name|gimp_image_set_filename
argument_list|(
name|image
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/* try to load an icc profile, it will be generated on the fly if    * chromaticities are given    */
if|if
condition|(
name|image_type
operator|==
name|GIMP_RGB
condition|)
block|{
name|profile
operator|=
name|exr_loader_get_profile
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|gimp_image_set_color_profile
argument_list|(
name|image
argument_list|,
name|profile
argument_list|)
expr_stmt|;
block|}
name|layer
operator|=
name|gimp_layer_new
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Background"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|layer_type
argument_list|,
literal|100
argument_list|,
name|gimp_image_get_default_new_layer_mode
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|format
operator|=
name|gimp_drawable_get_format
argument_list|(
name|layer
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|babl_format_get_bytes_per_pixel
argument_list|(
name|format
argument_list|)
expr_stmt|;
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new0
argument_list|(
name|gchar
argument_list|,
name|tile_height
operator|*
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
for|for
control|(
name|begin
operator|=
literal|0
init|;
name|begin
operator|<
name|height
condition|;
name|begin
operator|+=
name|tile_height
control|)
block|{
name|gint
name|end
decl_stmt|;
name|gint
name|num
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|end
operator|=
name|MIN
argument_list|(
name|begin
operator|+
name|tile_height
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|num
operator|=
name|end
operator|-
name|begin
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num
condition|;
name|i
operator|++
control|)
block|{
name|gint
name|retval
decl_stmt|;
name|retval
operator|=
name|exr_loader_read_pixel_row
argument_list|(
name|loader
argument_list|,
name|pixels
operator|+
operator|(
name|i
operator|*
name|width
operator|*
name|bpp
operator|)
argument_list|,
name|bpp
argument_list|,
name|begin
operator|+
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|retval
operator|<
literal|0
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
name|G_FILE_ERROR
argument_list|,
name|G_FILE_ERROR_FAILED
argument_list|,
name|_
argument_list|(
literal|"Error reading pixel data from '%s'"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
goto|goto
name|out
goto|;
block|}
block|}
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|begin
argument_list|,
name|width
argument_list|,
name|num
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|pixels
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|begin
operator|/
operator|(
name|gdouble
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
comment|/* try to read the file comment */
name|comment
operator|=
name|exr_loader_get_comment
argument_list|(
name|loader
argument_list|)
expr_stmt|;
if|if
condition|(
name|comment
condition|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
name|sanitize_comment
argument_list|(
name|comment
argument_list|)
expr_stmt|;
name|parasite
operator|=
name|gimp_parasite_new
argument_list|(
literal|"gimp-comment"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|,
name|strlen
argument_list|(
name|comment
argument_list|)
operator|+
literal|1
argument_list|,
name|comment
argument_list|)
expr_stmt|;
name|gimp_image_attach_parasite
argument_list|(
name|image
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
name|gimp_parasite_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
comment|/* check if the image contains Exif or Xmp data and read it */
name|exif_data
operator|=
name|exr_loader_get_exif
argument_list|(
name|loader
argument_list|,
operator|&
name|exif_size
argument_list|)
expr_stmt|;
name|xmp_data
operator|=
name|exr_loader_get_xmp
argument_list|(
name|loader
argument_list|,
operator|&
name|xmp_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|exif_data
operator|||
name|xmp_data
condition|)
block|{
name|GimpMetadata
modifier|*
name|metadata
init|=
name|gimp_metadata_new
argument_list|()
decl_stmt|;
name|GimpMetadataLoadFlags
name|flags
init|=
name|GIMP_METADATA_LOAD_ALL
decl_stmt|;
if|if
condition|(
name|exif_data
condition|)
block|{
name|gimp_metadata_set_from_exif
argument_list|(
name|metadata
argument_list|,
name|exif_data
argument_list|,
name|exif_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|exif_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|xmp_data
condition|)
block|{
name|gimp_metadata_set_from_xmp
argument_list|(
name|metadata
argument_list|,
name|xmp_data
argument_list|,
name|xmp_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|xmp_data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|comment
condition|)
name|flags
operator|&=
operator|~
name|GIMP_METADATA_LOAD_COMMENT
expr_stmt|;
if|if
condition|(
name|profile
condition|)
name|flags
operator|&=
operator|~
name|GIMP_METADATA_LOAD_COLORSPACE
expr_stmt|;
name|gimp_image_metadata_load_finish
argument_list|(
name|image
argument_list|,
literal|"image/exr"
argument_list|,
name|metadata
argument_list|,
name|flags
argument_list|,
name|interactive
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|metadata
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
name|success
operator|=
name|TRUE
expr_stmt|;
name|out
label|:
name|g_clear_object
argument_list|(
operator|&
name|profile
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|buffer
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|pixels
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|comment
argument_list|,
name|g_free
argument_list|)
expr_stmt|;
name|g_clear_pointer
argument_list|(
operator|&
name|loader
argument_list|,
name|exr_loader_unref
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
return|return
name|image
return|;
if|if
condition|(
name|image
operator|!=
operator|-
literal|1
condition|)
name|gimp_image_delete
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_comment
comment|/* copy& pasted from file-jpeg/jpeg-load.c */
end_comment

begin_function
specifier|static
name|void
DECL|function|sanitize_comment (gchar * comment)
name|sanitize_comment
parameter_list|(
name|gchar
modifier|*
name|comment
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|start_invalid
decl_stmt|;
if|if
condition|(
operator|!
name|g_utf8_validate
argument_list|(
name|comment
argument_list|,
operator|-
literal|1
argument_list|,
operator|&
name|start_invalid
argument_list|)
condition|)
block|{
name|guchar
modifier|*
name|c
decl_stmt|;
for|for
control|(
name|c
operator|=
operator|(
name|guchar
operator|*
operator|)
name|start_invalid
init|;
operator|*
name|c
condition|;
name|c
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|c
operator|>
literal|126
operator|||
operator|(
operator|*
name|c
operator|<
literal|32
operator|&&
operator|*
name|c
operator|!=
literal|'\t'
operator|&&
operator|*
name|c
operator|!=
literal|'\n'
operator|&&
operator|*
name|c
operator|!=
literal|'\r'
operator|)
condition|)
operator|*
name|c
operator|=
literal|'?'
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

