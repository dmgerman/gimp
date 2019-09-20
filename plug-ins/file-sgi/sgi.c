begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * SGI image file plug-in for GIMP.  *  * Copyright 1997-1998 Michael Sweet (mike@easysw.com)  *  * This program is free software: you can redistribute it and/or modify it  * under the terms of the GNU General Public License as published by the Free  * Software Foundation; either version 3 of the License, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful, but  * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License  * for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  * Contents:  *  *   main()                      - Main entry - just call gimp_main()...  *   query()                     - Respond to a plug-in query...  *   run()                       - Run the plug-in...  *   load_image()                - Load a PNG image into a new image window.  *   save_image()                - Export the specified image to a PNG file.  *   save_ok_callback()          - Destroy the export dialog and export the image.  *   save_dialog()               - Pop up the export dialog.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"sgi-lib.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|LOAD_PROC
define|#
directive|define
name|LOAD_PROC
value|"file-sgi-load"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-sgi-save"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"file-sgi"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-file-sgi"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"1.1.1 - 17 May 1998"
end_define

begin_typedef
DECL|typedef|Sgi
typedef|typedef
name|struct
name|_Sgi
name|Sgi
typedef|;
end_typedef

begin_typedef
DECL|typedef|SgiClass
typedef|typedef
name|struct
name|_SgiClass
name|SgiClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Sgi
struct|struct
name|_Sgi
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_SgiClass
struct|struct
name|_SgiClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|SGI_TYPE
define|#
directive|define
name|SGI_TYPE
value|(sgi_get_type ())
end_define

begin_define
DECL|macro|SGI
define|#
directive|define
name|SGI
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SGI_TYPE, Sgi))
end_define

begin_decl_stmt
name|GType
name|sgi_get_type
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
name|sgi_query_procedures
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
name|sgi_create_procedure
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
name|sgi_load
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
name|GimpValueArray
modifier|*
name|sgi_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GimpImage
modifier|*
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
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
name|gint
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
name|gboolean
name|save_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|Sgi
argument_list|,
argument|sgi
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|SGI_TYPE
argument_list|)
end_macro

begin_decl_stmt
specifier|static
name|gint
name|compression
init|=
name|SGI_COMP_RLE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|sgi_class_init (SgiClass * klass)
name|sgi_class_init
parameter_list|(
name|SgiClass
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
name|sgi_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|sgi_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|sgi_init (Sgi * sgi)
name|sgi_init
parameter_list|(
name|Sgi
modifier|*
name|sgi
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|sgi_query_procedures (GimpPlugIn * plug_in)
name|sgi_query_procedures
parameter_list|(
name|GimpPlugIn
modifier|*
name|plug_in
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
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|LOAD_PROC
argument_list|)
argument_list|)
expr_stmt|;
name|list
operator|=
name|g_list_append
argument_list|(
name|list
argument_list|,
name|g_strdup
argument_list|(
name|SAVE_PROC
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|GimpProcedure
modifier|*
DECL|function|sgi_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|sgi_create_procedure
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
name|GIMP_PDB_PROC_TYPE_PLUGIN
argument_list|,
name|sgi_load
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
literal|"Silicon Graphics IRIS image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads files in SGI image file format"
argument_list|,
literal|"This plug-in loads SGI image files."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Michael Sweet<mike@easysw.com>"
argument_list|,
literal|"Copyright 1997-1998 by Michael Sweet"
argument_list|,
name|PLUG_IN_VERSION
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-sgi"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"sgi,rgb,rgba,bw,icon"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"0,short,474"
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_save_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PDB_PROC_TYPE_PLUGIN
argument_list|,
name|sgi_save
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_image_types
argument_list|(
name|procedure
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_menu_label
argument_list|(
name|procedure
argument_list|,
name|N_
argument_list|(
literal|"Silicon Graphics IRIS image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_icon_name
argument_list|(
name|procedure
argument_list|,
name|GIMP_ICON_BRUSH
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Exports files in SGI image file format"
argument_list|,
literal|"This plug-in exports SGI image files."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Michael Sweet<mike@easysw.com>"
argument_list|,
literal|"Copyright 1997-1998 by Michael Sweet"
argument_list|,
name|PLUG_IN_VERSION
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-sgi"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"sgi,rgb,rgba,bw,icon"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"compression"
argument_list|,
literal|"Compression"
argument_list|,
literal|"Compression level (0 = none, 1 = RLE, 2 = ARLE)"
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
name|G_PARAM_STATIC_STRINGS
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
DECL|function|sgi_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|sgi_load
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
name|GimpImage
modifier|*
name|image
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
name|image
operator|=
name|load_image
argument_list|(
name|file
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
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
name|image
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|sgi_save (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,GFile * file,const GimpValueArray * args,gpointer run_data)
name|sgi_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_CANCEL
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
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image
argument_list|,
operator|&
name|drawable
argument_list|,
literal|"SGI"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_CANCEL
condition|)
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_CANCEL
argument_list|,
name|NULL
argument_list|)
return|;
break|break;
default|default:
break|break;
block|}
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|save_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|compression
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
empty_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
name|save_image
argument_list|(
name|file
argument_list|,
name|image
argument_list|,
name|drawable
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|compression
argument_list|,
sizeof|sizeof
argument_list|(
name|compression
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_new_return_values
argument_list|(
name|procedure
argument_list|,
name|status
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GimpImage
modifier|*
DECL|function|load_image (GFile * file,GError ** error)
name|load_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
comment|/* Looping var */
name|x
decl_stmt|,
comment|/* Current X coordinate */
name|y
decl_stmt|,
comment|/* Current Y coordinate */
name|image_type
decl_stmt|,
comment|/* Type of image */
name|layer_type
decl_stmt|,
comment|/* Type of drawable/layer */
name|tile_height
decl_stmt|,
comment|/* Height of tile in GIMP */
name|count
decl_stmt|,
comment|/* Count of rows to put in image */
name|bytes
decl_stmt|;
comment|/* Number of channels to use */
name|gchar
modifier|*
name|filename
decl_stmt|;
name|sgi_t
modifier|*
name|sgip
decl_stmt|;
comment|/* File pointer */
name|GimpImage
modifier|*
name|image
decl_stmt|;
comment|/* Image */
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
comment|/* Layer */
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
comment|/* Buffer for layer */
name|guchar
modifier|*
modifier|*
name|pixels
decl_stmt|,
comment|/* Pixel rows */
modifier|*
name|pptr
decl_stmt|;
comment|/* Current pixel */
name|gushort
modifier|*
modifier|*
name|rows
decl_stmt|;
comment|/* SGI image data */
comment|/*   * Open the file for reading...   */
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|sgip
operator|=
name|sgiOpen
argument_list|(
name|filename
argument_list|,
name|SGI_READ
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sgip
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
literal|"Could not open '%s' for reading."
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
empty_stmt|;
comment|/*    * Get the image dimensions and create the image...    */
comment|/* Sanitize dimensions (note that they are unsigned short and can    * thus never be larger than GIMP_MAX_IMAGE_SIZE    */
if|if
condition|(
name|sgip
operator|->
name|xsize
operator|==
literal|0
comment|/*|| sgip->xsize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid width: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|xsize
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|sgip
operator|->
name|ysize
operator|==
literal|0
comment|/*|| sgip->ysize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid height: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|ysize
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|sgip
operator|->
name|zsize
operator|==
literal|0
comment|/*|| sgip->zsize> GIMP_MAX_IMAGE_SIZE*/
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
literal|"Invalid number of channels: %hu"
argument_list|)
argument_list|,
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|bytes
operator|=
name|sgip
operator|->
name|zsize
expr_stmt|;
switch|switch
condition|(
name|sgip
operator|->
name|zsize
condition|)
block|{
case|case
literal|1
case|:
comment|/* Grayscale */
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|GIMP_GRAY_IMAGE
expr_stmt|;
break|break;
case|case
literal|2
case|:
comment|/* Grayscale + alpha */
name|image_type
operator|=
name|GIMP_GRAY
expr_stmt|;
name|layer_type
operator|=
name|GIMP_GRAYA_IMAGE
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/* RGB */
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGB_IMAGE
expr_stmt|;
break|break;
case|case
literal|4
case|:
comment|/* RGBA */
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
break|break;
default|default:
name|image_type
operator|=
name|GIMP_RGB
expr_stmt|;
name|layer_type
operator|=
name|GIMP_RGBA_IMAGE
expr_stmt|;
name|bytes
operator|=
literal|4
expr_stmt|;
break|break;
block|}
name|image
operator|=
name|gimp_image_new
argument_list|(
name|sgip
operator|->
name|xsize
argument_list|,
name|sgip
operator|->
name|ysize
argument_list|,
name|image_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
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
literal|"Could not allocate new image: %s"
argument_list|,
name|gimp_pdb_get_last_error
argument_list|(
name|gimp_get_pdb
argument_list|()
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|gimp_image_set_file
argument_list|(
name|image
argument_list|,
name|file
argument_list|)
expr_stmt|;
comment|/*    * Create the "background" layer to hold the image...    */
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
name|sgip
operator|->
name|xsize
argument_list|,
name|sgip
operator|->
name|ysize
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
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*    * Get the drawable and set the pixel region for our load...    */
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    * Temporary buffers...    */
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|pixels
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|tile_height
operator|)
operator|*
name|sgip
operator|->
name|xsize
operator|*
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tile_height
condition|;
name|i
operator|++
control|)
name|pixels
index|[
name|i
index|]
operator|=
name|pixels
index|[
literal|0
index|]
operator|+
name|sgip
operator|->
name|xsize
operator|*
name|bytes
operator|*
name|i
expr_stmt|;
name|rows
operator|=
name|g_new
argument_list|(
argument|unsigned short *
argument_list|,
argument|sgip->zsize
argument_list|)
expr_stmt|;
name|rows
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
argument|unsigned short
argument_list|,
argument|((gsize) sgip->xsize) * sgip->zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
name|rows
index|[
name|i
index|]
operator|=
name|rows
index|[
literal|0
index|]
operator|+
name|i
operator|*
name|sgip
operator|->
name|xsize
expr_stmt|;
comment|/*    * Load the image...    */
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|count
operator|=
literal|0
init|;
name|y
operator|<
name|sgip
operator|->
name|ysize
condition|;
name|y
operator|++
operator|,
name|count
operator|++
control|)
block|{
if|if
condition|(
name|count
operator|>=
name|tile_height
condition|)
block|{
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|y
operator|-
name|count
argument_list|,
name|sgip
operator|->
name|xsize
argument_list|,
name|count
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
name|count
operator|=
literal|0
expr_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|sgip
operator|->
name|ysize
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|sgiGetRow
argument_list|(
name|sgip
argument_list|,
name|rows
index|[
name|i
index|]
argument_list|,
name|sgip
operator|->
name|ysize
operator|-
literal|1
operator|-
name|y
argument_list|,
name|i
argument_list|)
operator|<
literal|0
condition|)
name|g_printerr
argument_list|(
literal|"sgiGetRow(sgip, rows[i], %d, %d) failed!\n"
argument_list|,
name|sgip
operator|->
name|ysize
operator|-
literal|1
operator|-
name|y
argument_list|,
name|i
argument_list|)
expr_stmt|;
if|if
condition|(
name|sgip
operator|->
name|bpp
operator|==
literal|1
condition|)
block|{
comment|/*            * 8-bit (unsigned) pixels...            */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
name|count
index|]
init|;
name|x
operator|<
name|sgip
operator|->
name|xsize
condition|;
name|x
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
operator|,
name|pptr
operator|++
control|)
operator|*
name|pptr
operator|=
name|rows
index|[
name|i
index|]
index|[
name|x
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/*            * 16-bit (unsigned) pixels...            */
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
name|count
index|]
init|;
name|x
operator|<
name|sgip
operator|->
name|xsize
condition|;
name|x
operator|++
control|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
operator|,
name|pptr
operator|++
control|)
operator|*
name|pptr
operator|=
name|rows
index|[
name|i
index|]
index|[
name|x
index|]
operator|>>
literal|8
expr_stmt|;
block|}
block|}
comment|/*    * Do the last n rows (count always> 0)    */
name|gegl_buffer_set
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|y
operator|-
name|count
argument_list|,
name|sgip
operator|->
name|xsize
argument_list|,
name|count
argument_list|)
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|)
expr_stmt|;
comment|/*    * Done with the file...    */
name|sgiClose
argument_list|(
name|sgip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|image
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|save_image (GFile * file,GimpImage * image,GimpDrawable * drawable,GError ** error)
name|save_image
parameter_list|(
name|GFile
modifier|*
name|file
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
comment|/* Looping var */
name|x
decl_stmt|,
comment|/* Current X coordinate */
name|y
decl_stmt|,
comment|/* Current Y coordinate */
name|width
decl_stmt|,
comment|/* Drawable width */
name|height
decl_stmt|,
comment|/* Drawable height */
name|tile_height
decl_stmt|,
comment|/* Height of tile in GIMP */
name|count
decl_stmt|,
comment|/* Count of rows to put in image */
name|zsize
decl_stmt|;
comment|/* Number of channels in file */
name|gchar
modifier|*
name|filename
decl_stmt|;
name|sgi_t
modifier|*
name|sgip
decl_stmt|;
comment|/* File pointer */
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
comment|/* Buffer for layer */
specifier|const
name|Babl
modifier|*
name|format
decl_stmt|;
name|guchar
modifier|*
modifier|*
name|pixels
decl_stmt|,
comment|/* Pixel rows */
modifier|*
name|pptr
decl_stmt|;
comment|/* Current pixel */
name|gushort
modifier|*
modifier|*
name|rows
decl_stmt|;
comment|/* SGI image data */
comment|/*    * Get the drawable for the current image...    */
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gimp_drawable_get_buffer
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
case|case
name|GIMP_GRAY_IMAGE
case|:
name|zsize
operator|=
literal|1
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|zsize
operator|=
literal|2
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"Y'A u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGB_IMAGE
case|:
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|zsize
operator|=
literal|3
expr_stmt|;
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B' u8"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|format
operator|=
name|babl_format
argument_list|(
literal|"R'G'B'A u8"
argument_list|)
expr_stmt|;
name|zsize
operator|=
literal|4
expr_stmt|;
break|break;
default|default:
return|return
name|FALSE
return|;
block|}
comment|/*    * Open the file for writing...    */
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Exporting '%s'"
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_file_get_path
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|sgip
operator|=
name|sgiOpen
argument_list|(
name|filename
argument_list|,
name|SGI_WRITE
argument_list|,
name|compression
argument_list|,
literal|1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|zsize
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|sgip
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
literal|"Could not open '%s' for writing."
argument_list|)
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
empty_stmt|;
comment|/*    * Allocate memory for "tile_height" rows...    */
name|tile_height
operator|=
name|gimp_tile_height
argument_list|()
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|tile_height
argument_list|)
expr_stmt|;
name|pixels
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|tile_height
operator|)
operator|*
name|width
operator|*
name|zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|tile_height
condition|;
name|i
operator|++
control|)
name|pixels
index|[
name|i
index|]
operator|=
name|pixels
index|[
literal|0
index|]
operator|+
name|width
operator|*
name|zsize
operator|*
name|i
expr_stmt|;
name|rows
operator|=
name|g_new
argument_list|(
name|gushort
operator|*
argument_list|,
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
name|rows
index|[
literal|0
index|]
operator|=
name|g_new
argument_list|(
name|gushort
argument_list|,
operator|(
operator|(
name|gsize
operator|)
name|sgip
operator|->
name|xsize
operator|)
operator|*
name|sgip
operator|->
name|zsize
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|sgip
operator|->
name|zsize
condition|;
name|i
operator|++
control|)
name|rows
index|[
name|i
index|]
operator|=
name|rows
index|[
literal|0
index|]
operator|+
name|i
operator|*
name|sgip
operator|->
name|xsize
expr_stmt|;
comment|/*    * Save the image...    */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|+=
name|count
control|)
block|{
comment|/*        * Grab more pixel data...        */
if|if
condition|(
operator|(
name|y
operator|+
name|tile_height
operator|)
operator|>=
name|height
condition|)
name|count
operator|=
name|height
operator|-
name|y
expr_stmt|;
else|else
name|count
operator|=
name|tile_height
expr_stmt|;
name|gegl_buffer_get
argument_list|(
name|buffer
argument_list|,
name|GEGL_RECTANGLE
argument_list|(
literal|0
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|count
argument_list|)
argument_list|,
literal|1.0
argument_list|,
name|format
argument_list|,
name|pixels
index|[
literal|0
index|]
argument_list|,
name|GEGL_AUTO_ROWSTRIDE
argument_list|,
name|GEGL_ABYSS_NONE
argument_list|)
expr_stmt|;
comment|/*        * Convert to shorts and write each color plane separately...        */
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|pptr
operator|=
name|pixels
index|[
literal|0
index|]
init|;
name|i
operator|<
name|count
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|zsize
condition|;
name|j
operator|++
operator|,
name|pptr
operator|++
control|)
name|rows
index|[
name|j
index|]
index|[
name|x
index|]
operator|=
operator|*
name|pptr
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|zsize
condition|;
name|j
operator|++
control|)
name|sgiPutRow
argument_list|(
name|sgip
argument_list|,
name|rows
index|[
name|j
index|]
argument_list|,
name|height
operator|-
literal|1
operator|-
name|y
operator|-
name|i
argument_list|,
name|j
argument_list|)
expr_stmt|;
block|}
empty_stmt|;
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
comment|/*    * Done with the file...    */
name|sgiClose
argument_list|(
name|sgip
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rows
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|save_dialog (void)
name|save_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|dialog
operator|=
name|gimp_export_dialog_new
argument_list|(
name|_
argument_list|(
literal|"SGI"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
argument_list|,
name|SAVE_PROC
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Compression type"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|compression
argument_list|,
name|compression
argument_list|,
name|_
argument_list|(
literal|"_No compression"
argument_list|)
argument_list|,
name|SGI_COMP_NONE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_RLE compression"
argument_list|)
argument_list|,
name|SGI_COMP_RLE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Aggressive RLE\n(not supported by SGI)"
argument_list|)
argument_list|,
name|SGI_COMP_ARLE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gimp_export_dialog_get_content_area
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

