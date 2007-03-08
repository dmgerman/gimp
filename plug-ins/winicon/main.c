begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * GIMP Plug-in for Windows Icon files.  * Copyright (C) 2002 Christian Kreibich<christian@whoop.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_comment
comment|/* #define ICO_DBG */
end_comment

begin_include
include|#
directive|include
file|"main.h"
end_include

begin_include
include|#
directive|include
file|"icoload.h"
end_include

begin_include
include|#
directive|include
file|"icosave.h"
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
value|"file-ico-load"
end_define

begin_define
DECL|macro|LOAD_THUMB_PROC
define|#
directive|define
name|LOAD_THUMB_PROC
value|"file-ico-load-thumb"
end_define

begin_define
DECL|macro|SAVE_PROC
define|#
directive|define
name|SAVE_PROC
value|"file-ico-save"
end_define

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|load_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|,   }
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|thumb_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to load"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"thumb-size"
block|,
literal|"Preferred thumbnail size"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|thumb_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Thumbnail image"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"image-width"
block|,
literal|"Width of full-sized image"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"image-height"
block|,
literal|"Height of full-sized image"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|save_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Drawable to save"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"filename"
block|,
literal|"The name of the file to save the image in"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"raw-filename"
block|,
literal|"The name entered"
block|}
block|,   }
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"Loads files of Windows ICO file format"
argument_list|,
literal|"Loads files of Windows ICO file format"
argument_list|,
literal|"Christian Kreibich<christian@whoop.org>"
argument_list|,
literal|"Christian Kreibich<christian@whoop.org>"
argument_list|,
literal|"2002"
argument_list|,
name|N_
argument_list|(
literal|"Microsoft Windows icon"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|load_return_vals
argument_list|)
argument_list|,
name|load_args
argument_list|,
name|load_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"image/x-ico"
argument_list|)
expr_stmt|;
name|gimp_register_magic_load_handler
argument_list|(
name|LOAD_PROC
argument_list|,
literal|"ico"
argument_list|,
literal|""
argument_list|,
literal|"0,string,\\000\\001\\000\\000,0,string,\\000\\002\\000\\000"
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|LOAD_THUMB_PROC
argument_list|,
literal|"Loads a preview from an Windows ICO file"
argument_list|,
literal|""
argument_list|,
literal|"Dom Lachowicz, Sven Neumann"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|thumb_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|thumb_return_vals
argument_list|)
argument_list|,
name|thumb_args
argument_list|,
name|thumb_return_vals
argument_list|)
expr_stmt|;
name|gimp_register_thumbnail_loader
argument_list|(
name|LOAD_PROC
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"Saves files in Windows ICO file format"
argument_list|,
literal|"Saves files in Windows ICO file format"
argument_list|,
literal|"Christian Kreibich<christian@whoop.org>"
argument_list|,
literal|"Christian Kreibich<christian@whoop.org>"
argument_list|,
literal|"2002"
argument_list|,
name|N_
argument_list|(
literal|"Microsoft Windows icon"
argument_list|)
argument_list|,
literal|"*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|save_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|save_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_register_file_handler_mime
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"image/x-ico"
argument_list|)
expr_stmt|;
name|gimp_register_save_handler
argument_list|(
name|SAVE_PROC
argument_list|,
literal|"ico"
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GimpParam
name|values
index|[
literal|4
index|]
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|3
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|image_ID
operator|=
name|ico_load_image
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
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
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|LOAD_THUMB_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|nparams
operator|<
literal|2
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
specifier|const
name|gchar
modifier|*
name|filename
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_string
decl_stmt|;
name|gint
name|width
init|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|gint
name|height
init|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|image_ID
operator|=
name|ico_load_thumbnail_image
argument_list|(
name|filename
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_ID
operator|!=
operator|-
literal|1
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|4
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_ID
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|width
expr_stmt|;
name|values
index|[
literal|3
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|height
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
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|SAVE_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
name|gchar
modifier|*
name|file_name
decl_stmt|;
name|image_ID
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable_ID
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|file_name
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*  Make sure all the arguments are there!  */
if|if
condition|(
name|nparams
operator|<
literal|5
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|status
operator|=
name|ico_save_image
argument_list|(
name|file_name
argument_list|,
name|image_ID
argument_list|,
name|run_mode
argument_list|)
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
name|image_ID
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|ico_rowstride (gint width,gint bpp)
name|ico_rowstride
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|bpp
parameter_list|)
block|{
switch|switch
condition|(
name|bpp
condition|)
block|{
case|case
literal|1
case|:
if|if
condition|(
operator|(
name|width
operator|%
literal|32
operator|)
operator|==
literal|0
condition|)
return|return
name|width
operator|/
literal|8
return|;
else|else
return|return
literal|4
operator|*
operator|(
name|width
operator|/
literal|32
operator|+
literal|1
operator|)
return|;
break|break;
case|case
literal|4
case|:
if|if
condition|(
operator|(
name|width
operator|%
literal|8
operator|)
operator|==
literal|0
condition|)
return|return
name|width
operator|/
literal|2
return|;
else|else
return|return
literal|4
operator|*
operator|(
name|width
operator|/
literal|8
operator|+
literal|1
operator|)
return|;
break|break;
case|case
literal|8
case|:
if|if
condition|(
operator|(
name|width
operator|%
literal|4
operator|)
operator|==
literal|0
condition|)
return|return
name|width
return|;
else|else
return|return
literal|4
operator|*
operator|(
name|width
operator|/
literal|4
operator|+
literal|1
operator|)
return|;
break|break;
case|case
literal|24
case|:
if|if
condition|(
operator|(
operator|(
name|width
operator|*
literal|3
operator|)
operator|%
literal|4
operator|)
operator|==
literal|0
condition|)
return|return
name|width
operator|*
literal|3
return|;
else|else
return|return
literal|4
operator|*
operator|(
name|width
operator|*
literal|3
operator|/
literal|4
operator|+
literal|1
operator|)
return|;
case|case
literal|32
case|:
return|return
name|width
operator|*
literal|4
return|;
default|default:
name|g_warning
argument_list|(
literal|"invalid bitrate: %d\n"
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
name|g_assert_not_reached
argument_list|()
expr_stmt|;
return|return
name|width
operator|*
operator|(
name|bpp
operator|/
literal|8
operator|)
return|;
block|}
block|}
end_function

begin_function
name|guint8
modifier|*
DECL|function|ico_alloc_map (gint width,gint height,gint bpp,gint * length)
name|ico_alloc_map
parameter_list|(
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|)
block|{
name|gint
name|len
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|map
init|=
name|NULL
decl_stmt|;
name|len
operator|=
name|ico_rowstride
argument_list|(
name|width
argument_list|,
name|bpp
argument_list|)
operator|*
name|height
expr_stmt|;
operator|*
name|length
operator|=
name|len
expr_stmt|;
name|map
operator|=
name|g_new0
argument_list|(
name|guint8
argument_list|,
name|len
argument_list|)
expr_stmt|;
return|return
name|map
return|;
block|}
end_function

end_unit

