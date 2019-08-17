begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GIMP PSD Plug-in  * Copyright 2007 by John Marshall  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"psd.h"
end_include

begin_include
include|#
directive|include
file|"psd-load.h"
end_include

begin_include
include|#
directive|include
file|"psd-save.h"
end_include

begin_include
include|#
directive|include
file|"psd-thumb-load.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|typedef|Psd
typedef|typedef
name|struct
name|_Psd
name|Psd
typedef|;
end_typedef

begin_typedef
DECL|typedef|PsdClass
typedef|typedef
name|struct
name|_PsdClass
name|PsdClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Psd
struct|struct
name|_Psd
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_PsdClass
struct|struct
name|_PsdClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|PSD_TYPE
define|#
directive|define
name|PSD_TYPE
value|(psd_get_type ())
end_define

begin_define
DECL|macro|PSD
define|#
directive|define
name|PSD
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), PSD_TYPE, Psd))
end_define

begin_decl_stmt
name|GType
name|psd_get_type
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
name|psd_query_procedures
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
name|psd_create_procedure
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
name|psd_load
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
name|psd_load_thumb
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
name|psd_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
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

begin_macro
DECL|function|G_DEFINE_TYPE (Psd,psd,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Psd
argument_list|,
argument|psd
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|PSD_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|psd_class_init
parameter_list|(
name|PsdClass
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
name|psd_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|psd_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|psd_init (Psd * psd)
name|psd_init
parameter_list|(
name|Psd
modifier|*
name|psd
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|psd_query_procedures (GimpPlugIn * plug_in)
name|psd_query_procedures
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
name|LOAD_MERGED_PROC
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
name|LOAD_THUMB_PROC
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
DECL|function|psd_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|psd_create_procedure
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
name|psd_load
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
literal|"Photoshop image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads images from the Photoshop "
literal|"PSD file format"
argument_list|,
literal|"This plug-in loads images in Adobe "
literal|"Photoshop (TM) native PSD format."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"2007"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-psd"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"psd"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"0,string,8BPS"
argument_list|)
expr_stmt|;
name|gimp_load_procedure_set_thumbnail_loader
argument_list|(
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|LOAD_THUMB_PROC
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
name|LOAD_MERGED_PROC
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
name|psd_load
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
literal|"Photoshop image (merged)"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads images from the Photoshop "
literal|"PSD file format"
argument_list|,
literal|"This plug-in loads the merged image "
literal|"data in Adobe Photoshop (TM) native "
literal|"PSD format."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Ell"
argument_list|,
literal|"Ell"
argument_list|,
literal|"2018"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-psd"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"psd"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"0,string,8BPS"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_priority
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_load_procedure_set_thumbnail_loader
argument_list|(
name|GIMP_LOAD_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|LOAD_THUMB_PROC
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
name|LOAD_THUMB_PROC
argument_list|)
condition|)
block|{
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|plug_in
argument_list|,
name|name
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|psd_load_thumb
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads thumbnails from the "
literal|"Photoshop PSD file format"
argument_list|,
literal|"This plug-in loads thumbnail images "
literal|"from Adobe Photoshop (TM) native "
literal|"PSD format files."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"John Marshall"
argument_list|,
literal|"2007"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"filename"
argument_list|,
literal|"Filename"
argument_list|,
literal|"Name of the file "
literal|"to load"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"thumb-size"
argument_list|,
literal|"Thumb Size"
argument_list|,
literal|"Preferred thumbnail size"
argument_list|,
literal|16
argument_list|,
literal|2014
argument_list|,
literal|256
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Thumbnail image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"image-width"
argument_list|,
literal|"Image width"
argument_list|,
literal|"Width of the "
literal|"full-sized image"
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"image-height"
argument_list|,
literal|"Image height"
argument_list|,
literal|"Height of the "
literal|"full-sized image"
argument_list|,
literal|1
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
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
name|GIMP_PLUGIN
argument_list|,
name|psd_save
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
literal|"Photoshop image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Saves files in the Photoshop(tm) "
literal|"PSD file format"
argument_list|,
literal|"This filter saves files of Adobe "
literal|"Photoshop(tm) native PSD format. "
literal|"These files may be of any image type "
literal|"supported by GIMP, with or without "
literal|"layers, layer masks, aux channels "
literal|"and guides."
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Monigotes"
argument_list|,
literal|"Monigotes"
argument_list|,
literal|"2000"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/x-psd"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"psd"
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
DECL|function|psd_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|psd_load
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
name|gboolean
name|resolution_loaded
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|profile_loaded
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|interactive
decl_stmt|;
name|gint32
name|image_id
decl_stmt|;
name|GimpMetadata
modifier|*
name|metadata
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|interactive
operator|=
name|TRUE
expr_stmt|;
break|break;
default|default:
name|interactive
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
name|image_id
operator|=
name|load_image
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|strcmp
argument_list|(
name|gimp_procedure_get_name
argument_list|(
name|procedure
argument_list|)
argument_list|,
name|LOAD_MERGED_PROC
argument_list|)
operator|==
literal|0
argument_list|,
operator|&
name|resolution_loaded
argument_list|,
operator|&
name|profile_loaded
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_id
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
name|metadata
operator|=
name|gimp_image_metadata_load_prepare
argument_list|(
name|image_id
argument_list|,
literal|"image/x-psd"
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
block|{
name|GimpMetadataLoadFlags
name|flags
init|=
name|GIMP_METADATA_LOAD_ALL
decl_stmt|;
if|if
condition|(
name|resolution_loaded
condition|)
name|flags
operator|&=
operator|~
name|GIMP_METADATA_LOAD_RESOLUTION
expr_stmt|;
if|if
condition|(
name|profile_loaded
condition|)
name|flags
operator|&=
operator|~
name|GIMP_METADATA_LOAD_COLORSPACE
expr_stmt|;
name|gimp_image_metadata_load_finish
argument_list|(
name|image_id
argument_list|,
literal|"image/x-psd"
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
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_id
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
DECL|function|psd_load_thumb (GimpProcedure * procedure,const GimpValueArray * args,gpointer run_data)
name|psd_load_thumb
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
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
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|width
init|=
literal|0
decl_stmt|;
name|gint
name|height
init|=
literal|0
decl_stmt|;
name|gint32
name|image_id
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
name|filename
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|image_id
operator|=
name|load_thumbnail_image
argument_list|(
name|filename
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_id
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
name|gimp_value_set_image_id
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image_id
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|2
argument_list|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|3
argument_list|)
argument_list|,
name|height
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
DECL|function|psd_save (GimpProcedure * procedure,GimpRunMode run_mode,gint32 image_id,gint32 drawable_id,GFile * file,const GimpValueArray * args,gpointer run_data)
name|psd_save
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|GimpRunMode
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|drawable_id
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
name|GimpMetadata
modifier|*
name|metadata
decl_stmt|;
name|GimpMetadataSaveFlags
name|metadata_flags
decl_stmt|;
name|GimpExportReturn
name|export
init|=
name|GIMP_EXPORT_IGNORE
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
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image_id
argument_list|,
operator|&
name|drawable_id
argument_list|,
literal|"PSD"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYERS
operator||
name|GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS
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
name|metadata
operator|=
name|gimp_image_metadata_save_prepare
argument_list|(
name|image_id
argument_list|,
literal|"image/x-psd"
argument_list|,
operator|&
name|metadata_flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|save_image
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|image_id
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|metadata
condition|)
block|{
name|gimp_metadata_set_bits_per_sample
argument_list|(
name|metadata
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|gimp_image_metadata_save_finish
argument_list|(
name|image_id
argument_list|,
literal|"image/x-psd"
argument_list|,
name|metadata
argument_list|,
name|metadata_flags
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_EXPORT
condition|)
name|gimp_image_delete
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|metadata
condition|)
name|g_object_unref
argument_list|(
name|metadata
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

end_unit

