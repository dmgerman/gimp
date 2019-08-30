begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * file-webp - WebP file format plug-in for the GIMP  * Copyright (C) 2015  Nathan Osman  * Copyright (C) 2016  Ben Touchette  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation, either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|<webp/encode.h>
end_include

begin_include
include|#
directive|include
file|"file-webp-dialog.h"
end_include

begin_include
include|#
directive|include
file|"file-webp-load.h"
end_include

begin_include
include|#
directive|include
file|"file-webp-save.h"
end_include

begin_include
include|#
directive|include
file|"file-webp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_typedef
DECL|typedef|Webp
typedef|typedef
name|struct
name|_Webp
name|Webp
typedef|;
end_typedef

begin_typedef
DECL|typedef|WebpClass
typedef|typedef
name|struct
name|_WebpClass
name|WebpClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Webp
struct|struct
name|_Webp
block|{
DECL|member|parent_instance
name|GimpPlugIn
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_WebpClass
struct|struct
name|_WebpClass
block|{
DECL|member|parent_class
name|GimpPlugInClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|WEBP_TYPE
define|#
directive|define
name|WEBP_TYPE
value|(webp_get_type ())
end_define

begin_define
DECL|macro|WEBP
define|#
directive|define
name|WEBP
value|(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), WEBP_TYPE, Webp))
end_define

begin_decl_stmt
name|GType
name|webp_get_type
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
name|webp_query_procedures
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
name|webp_create_procedure
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
name|webp_load
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
name|webp_save
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

begin_macro
DECL|function|G_DEFINE_TYPE (Webp,webp,GIMP_TYPE_PLUG_IN)
name|G_DEFINE_TYPE
argument_list|(
argument|Webp
argument_list|,
argument|webp
argument_list|,
argument|GIMP_TYPE_PLUG_IN
argument_list|)
end_macro

begin_macro
name|GIMP_MAIN
argument_list|(
argument|WEBP_TYPE
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|webp_class_init
parameter_list|(
name|WebpClass
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
name|webp_query_procedures
expr_stmt|;
name|plug_in_class
operator|->
name|create_procedure
operator|=
name|webp_create_procedure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|webp_init (Webp * webp)
name|webp_init
parameter_list|(
name|Webp
modifier|*
name|webp
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|webp_query_procedures (GimpPlugIn * plug_in)
name|webp_query_procedures
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
DECL|function|webp_create_procedure (GimpPlugIn * plug_in,const gchar * name)
name|webp_create_procedure
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
name|webp_load
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
literal|"WebP image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Loads images in the WebP file format"
argument_list|,
literal|"Loads images in the WebP file format"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Nathan Osman, Ben Touchette"
argument_list|,
literal|"(C) 2015-2016 Nathan Osman, "
literal|"(C) 2016 Ben Touchette"
argument_list|,
literal|"2015,2016"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/webp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"webp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_magics
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"8,string,WEBP"
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
name|webp_save
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
literal|"WebP image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_set_documentation
argument_list|(
name|procedure
argument_list|,
literal|"Saves files in the WebP image format"
argument_list|,
literal|"Saves files in the WebP image format"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|gimp_procedure_set_attribution
argument_list|(
name|procedure
argument_list|,
literal|"Nathan Osman, Ben Touchette"
argument_list|,
literal|"(C) 2015-2016 Nathan Osman, "
literal|"(C) 2016 Ben Touchette"
argument_list|,
literal|"2015,2016"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_mime_types
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"image/webp"
argument_list|)
expr_stmt|;
name|gimp_file_procedure_set_extensions
argument_list|(
name|GIMP_FILE_PROCEDURE
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"webp"
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"preset"
argument_list|,
literal|"Preset"
argument_list|,
literal|"Preset (Default=0, Picture=1, Photo=2, Drawing=3, "
literal|"Icon=4, Text=5)"
argument_list|,
literal|0
argument_list|,
literal|5
argument_list|,
name|WEBP_PRESET_DEFAULT
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"lossless"
argument_list|,
literal|"Lossless"
argument_list|,
literal|"Use lossless encoding"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"quality"
argument_list|,
literal|"Quality"
argument_list|,
literal|"Quality of the image"
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|,
literal|90
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_DOUBLE
argument_list|(
name|procedure
argument_list|,
literal|"alpha-quality"
argument_list|,
literal|"Alpha quality"
argument_list|,
literal|"Quality of the image's alpha channel"
argument_list|,
literal|0
argument_list|,
literal|100
argument_list|,
literal|100
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"animation"
argument_list|,
literal|"Animation"
argument_list|,
literal|"Use layers for animation"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"animation-loop"
argument_list|,
literal|"Animation loop"
argument_list|,
literal|"Loop animation infinitely"
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"minimize-size"
argument_list|,
literal|"Minimize size"
argument_list|,
literal|"Minimize animation size"
argument_list|,
name|TRUE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"kf-distance"
argument_list|,
literal|"KF distance"
argument_list|,
literal|"Maximum distance between key-frames"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|50
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"exif"
argument_list|,
literal|"EXIF"
argument_list|,
literal|"Toggle saving exif data"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"iptc"
argument_list|,
literal|"IPTC"
argument_list|,
literal|"Toggle saving iptc data"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"xmp"
argument_list|,
literal|"XMP"
argument_list|,
literal|"Toggle saving xmp data"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_INT
argument_list|(
name|procedure
argument_list|,
literal|"delay"
argument_list|,
literal|"Delay"
argument_list|,
literal|"Delay to use when timestamps are not available "
literal|"or forced"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|200
argument_list|,
name|G_PARAM_READWRITE
argument_list|)
expr_stmt|;
name|GIMP_PROC_ARG_BOOLEAN
argument_list|(
name|procedure
argument_list|,
literal|"force-delay"
argument_list|,
literal|"Force delay"
argument_list|,
literal|"Force delay on all frames"
argument_list|,
name|FALSE
argument_list|,
name|G_PARAM_READWRITE
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
DECL|function|webp_load (GimpProcedure * procedure,GimpRunMode run_mode,GFile * file,const GimpValueArray * args,gpointer run_data)
name|webp_load
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
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
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|FALSE
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
name|status
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
DECL|function|webp_save (GimpProcedure * procedure,GimpRunMode run_mode,GimpImage * image,GimpDrawable * drawable,GFile * file,const GimpValueArray * args,gpointer run_data)
name|webp_save
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
name|GimpMetadata
modifier|*
name|metadata
init|=
name|NULL
decl_stmt|;
name|GimpMetadataSaveFlags
name|metadata_flags
decl_stmt|;
name|WebPSaveParams
name|params
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
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|||
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Default settings */
name|params
operator|.
name|preset
operator|=
name|WEBP_PRESET_DEFAULT
expr_stmt|;
name|params
operator|.
name|lossless
operator|=
name|FALSE
expr_stmt|;
name|params
operator|.
name|animation
operator|=
name|FALSE
expr_stmt|;
name|params
operator|.
name|loop
operator|=
name|TRUE
expr_stmt|;
name|params
operator|.
name|minimize_size
operator|=
name|TRUE
expr_stmt|;
name|params
operator|.
name|kf_distance
operator|=
literal|50
expr_stmt|;
name|params
operator|.
name|quality
operator|=
literal|90.0f
expr_stmt|;
name|params
operator|.
name|alpha_quality
operator|=
literal|100.0f
expr_stmt|;
name|params
operator|.
name|exif
operator|=
name|FALSE
expr_stmt|;
name|params
operator|.
name|iptc
operator|=
name|FALSE
expr_stmt|;
name|params
operator|.
name|xmp
operator|=
name|FALSE
expr_stmt|;
name|params
operator|.
name|delay
operator|=
literal|200
expr_stmt|;
name|params
operator|.
name|force_delay
operator|=
name|FALSE
expr_stmt|;
comment|/* Override the defaults with preferences. */
name|metadata
operator|=
name|gimp_image_metadata_save_prepare
argument_list|(
name|image
argument_list|,
literal|"image/webp"
argument_list|,
operator|&
name|metadata_flags
argument_list|)
expr_stmt|;
name|params
operator|.
name|exif
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_EXIF
operator|)
operator|!=
literal|0
expr_stmt|;
name|params
operator|.
name|xmp
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_XMP
operator|)
operator|!=
literal|0
expr_stmt|;
name|params
operator|.
name|iptc
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_IPTC
operator|)
operator|!=
literal|0
expr_stmt|;
name|params
operator|.
name|profile
operator|=
operator|(
name|metadata_flags
operator|&
name|GIMP_METADATA_SAVE_COLOR_PROFILE
operator|)
operator|!=
literal|0
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*  Possibly override with session data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|params
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*  Possibly override with session data  */
name|gimp_get_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|params
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|save_dialog
argument_list|(
operator|&
name|params
argument_list|,
name|image
argument_list|)
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
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|params
operator|.
name|preset
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|params
operator|.
name|lossless
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|params
operator|.
name|quality
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|params
operator|.
name|alpha_quality
operator|=
name|GIMP_VALUES_GET_DOUBLE
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|params
operator|.
name|animation
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|params
operator|.
name|loop
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|params
operator|.
name|minimize_size
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|params
operator|.
name|kf_distance
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|params
operator|.
name|exif
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|params
operator|.
name|iptc
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|params
operator|.
name|xmp
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|params
operator|.
name|delay
operator|=
name|GIMP_VALUES_GET_INT
argument_list|(
name|args
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|params
operator|.
name|force_delay
operator|=
name|GIMP_VALUES_GET_BOOLEAN
argument_list|(
name|args
argument_list|,
literal|12
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
operator|||
name|run_mode
operator|==
name|GIMP_RUN_WITH_LAST_VALS
condition|)
block|{
name|GimpExportCapabilities
name|capabilities
init|=
operator|(
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
operator|)
decl_stmt|;
if|if
condition|(
name|params
operator|.
name|animation
condition|)
name|capabilities
operator||=
name|GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION
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
literal|"WebP"
argument_list|,
name|capabilities
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
block|}
if|if
condition|(
operator|!
name|save_image
argument_list|(
name|g_file_get_path
argument_list|(
name|file
argument_list|)
argument_list|,
name|image
argument_list|,
name|drawable
argument_list|,
name|metadata
argument_list|,
name|metadata_flags
argument_list|,
operator|&
name|params
argument_list|,
operator|&
name|error
argument_list|)
condition|)
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
name|image
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
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/* save parameters for later */
name|gimp_set_data
argument_list|(
name|SAVE_PROC
argument_list|,
operator|&
name|params
argument_list|,
sizeof|sizeof
argument_list|(
name|params
argument_list|)
argument_list|)
expr_stmt|;
block|}
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

