begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"xcf.h"
end_include

begin_include
include|#
directive|include
file|"xcf-private.h"
end_include

begin_include
include|#
directive|include
file|"xcf-load.h"
end_include

begin_include
include|#
directive|include
file|"xcf-read.h"
end_include

begin_include
include|#
directive|include
file|"xcf-save.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
name|GimpImage
modifier|*
name|GimpXcfLoaderFunc
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|XcfInfo
modifier|*
name|info
parameter_list|,
DECL|typedef|error
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
specifier|static
name|GimpValueArray
modifier|*
name|xcf_load_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
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
name|GimpValueArray
modifier|*
name|xcf_save_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|xcf_loaders
specifier|static
name|GimpXcfLoaderFunc
modifier|*
specifier|const
name|xcf_loaders
index|[]
init|=
block|{
name|xcf_load_image
block|,
comment|/* version 0 */
name|xcf_load_image
block|,
comment|/* version 1 */
name|xcf_load_image
block|,
comment|/* version 2 */
name|xcf_load_image
block|,
comment|/* version 3 */
name|xcf_load_image
block|,
comment|/* version 4 */
name|xcf_load_image
block|,
comment|/* version 5 */
name|xcf_load_image
block|,
comment|/* version 6 */
name|xcf_load_image
comment|/* version 7 */
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|xcf_init (Gimp * gimp)
name|xcf_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* So this is sort of a hack, but its better than it was before.  To    * do this right there would be a file load-save handler type and    * the whole interface would change but there isn't, and currently    * the plug-in structure contains all the load-save info, so it    * makes sense to use that for the XCF load/save handlers, even    * though they are internal.  The only thing it requires is using a    * PlugInProcDef struct.  -josh    */
comment|/*  gimp-xcf-save  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"gimp-xcf-save"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|xcf_save_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP XCF image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-wilber"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-wilber"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"xcf"
argument_list|,
literal|""
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_type
argument_list|(
name|proc
argument_list|,
literal|"image/xcf"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIO_IS_FIXED
name|gimp_plug_in_procedure_set_handles_uri
argument_list|(
name|proc
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-xcf-save"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-xcf-save"
argument_list|,
literal|"Saves file in the .xcf file format"
argument_list|,
literal|"The XCF file format has been designed "
literal|"specifically for loading and saving "
literal|"tiled and layered images in GIMP. "
literal|"This procedure will save the specified "
literal|"image in the xcf file format."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Input image"
argument_list|,
name|gimp
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable_id
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"Active drawable of input image"
argument_list|,
name|gimp
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
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
literal|"The name of the file "
literal|"to save the image in, "
literal|"in the on-disk "
literal|"character set and "
literal|"encoding"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
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
name|gimp_param_spec_string
argument_list|(
literal|"raw-filename"
argument_list|,
literal|"Raw filename"
argument_list|,
literal|"The basename of the "
literal|"file, in UTF-8"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  gimp-xcf-load  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"gimp-xcf-load"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|xcf_load_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP XCF image"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-wilber"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-wilber"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"xcf"
argument_list|,
literal|""
argument_list|,
literal|"0,string,gimp\\040xcf\\040"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_type
argument_list|(
name|proc
argument_list|,
literal|"image/xcf"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIO_IS_FIXED
name|gimp_plug_in_procedure_set_handles_uri
argument_list|(
name|proc
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-xcf-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-xcf-load"
argument_list|,
literal|"Loads file saved in the .xcf file format"
argument_list|,
literal|"The XCF file format has been designed "
literal|"specifically for loading and saving "
literal|"tiled and layered images in GIMP. "
literal|"This procedure will load the specified "
literal|"file."
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"Spencer Kimball& Peter Mattis"
argument_list|,
literal|"1995-1996"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
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
literal|"The name of the file "
literal|"to load, in the "
literal|"on-disk character "
literal|"set and encoding"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
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
name|gimp_param_spec_string
argument_list|(
literal|"raw-filename"
argument_list|,
literal|"Raw filename"
argument_list|,
literal|"The basename of the "
literal|"file, in UTF-8"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
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
literal|"Output image"
argument_list|,
name|gimp
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|xcf_exit (Gimp * gimp)
name|xcf_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpValueArray
modifier|*
DECL|function|xcf_load_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|xcf_load_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|XcfInfo
name|info
init|=
block|{
literal|0
block|, }
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
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|gchar
name|id
index|[
literal|14
index|]
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIO_IS_FIXED
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
else|#
directive|else
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|filename
operator|=
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|info
operator|.
name|input
operator|=
name|G_INPUT_STREAM
argument_list|(
name|g_file_read
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|.
name|input
condition|)
block|{
name|info
operator|.
name|gimp
operator|=
name|gimp
expr_stmt|;
name|info
operator|.
name|seekable
operator|=
name|G_SEEKABLE
argument_list|(
name|info
operator|.
name|input
argument_list|)
expr_stmt|;
name|info
operator|.
name|progress
operator|=
name|progress
expr_stmt|;
name|info
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|info
operator|.
name|compression
operator|=
name|COMPRESS_NONE
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_filename_display_name
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Opening '%s'"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|success
operator|=
name|TRUE
expr_stmt|;
name|info
operator|.
name|cp
operator|+=
name|xcf_read_int8
argument_list|(
name|info
operator|.
name|input
argument_list|,
operator|(
name|guint8
operator|*
operator|)
name|id
argument_list|,
literal|14
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_str_has_prefix
argument_list|(
name|id
argument_list|,
literal|"gimp xcf "
argument_list|)
condition|)
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|id
operator|+
literal|9
argument_list|,
literal|"file"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|info
operator|.
name|file_version
operator|=
literal|0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|id
index|[
literal|9
index|]
operator|==
literal|'v'
condition|)
block|{
name|info
operator|.
name|file_version
operator|=
name|atoi
argument_list|(
name|id
operator|+
literal|10
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|info
operator|.
name|file_version
operator|>=
literal|0
operator|&&
name|info
operator|.
name|file_version
operator|<
name|G_N_ELEMENTS
argument_list|(
name|xcf_loaders
argument_list|)
condition|)
block|{
name|image
operator|=
operator|(
operator|*
operator|(
name|xcf_loaders
index|[
name|info
operator|.
name|file_version
index|]
operator|)
operator|)
operator|(
name|gimp
operator|,
operator|&
name|info
operator|,
name|error
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|image
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
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
literal|"XCF error: unsupported XCF file version %d "
literal|"encountered"
argument_list|)
argument_list|,
name|info
operator|.
name|file_version
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
name|g_object_unref
argument_list|(
name|info
operator|.
name|input
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_propagate_prefixed_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for reading: "
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|gimp_value_set_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|return_vals
argument_list|,
literal|1
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
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
DECL|function|xcf_save_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GimpValueArray * args,GError ** error)
name|xcf_save_invoker
parameter_list|(
name|GimpProcedure
modifier|*
name|procedure
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|GimpValueArray
modifier|*
name|args
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|XcfInfo
name|info
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GimpValueArray
modifier|*
name|return_vals
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|gboolean
name|success
init|=
name|FALSE
decl_stmt|;
name|GError
modifier|*
name|my_error
init|=
name|NULL
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_value_get_image
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|1
argument_list|)
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_value_get_string
argument_list|(
name|gimp_value_array_index
argument_list|(
name|args
argument_list|,
literal|3
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIO_IS_FIXED
name|file
operator|=
name|g_file_new_for_uri
argument_list|(
name|uri
argument_list|)
expr_stmt|;
else|#
directive|else
name|file
operator|=
name|g_file_new_for_path
argument_list|(
name|uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|filename
operator|=
name|g_file_get_parse_name
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|info
operator|.
name|output
operator|=
name|G_OUTPUT_STREAM
argument_list|(
name|g_file_replace
argument_list|(
name|file
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
operator|&
name|my_error
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|.
name|output
condition|)
block|{
name|info
operator|.
name|gimp
operator|=
name|gimp
expr_stmt|;
name|info
operator|.
name|seekable
operator|=
name|G_SEEKABLE
argument_list|(
name|info
operator|.
name|output
argument_list|)
expr_stmt|;
name|info
operator|.
name|progress
operator|=
name|progress
expr_stmt|;
name|info
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|info
operator|.
name|compression
operator|=
name|COMPRESS_RLE
expr_stmt|;
if|if
condition|(
name|progress
condition|)
block|{
name|gchar
modifier|*
name|name
init|=
name|g_filename_display_name
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|gimp_progress_start
argument_list|(
name|progress
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Saving '%s'"
argument_list|)
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
name|xcf_save_choose_format
argument_list|(
operator|&
name|info
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|success
operator|=
name|xcf_save_image
argument_list|(
operator|&
name|info
argument_list|,
name|image
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|info
operator|.
name|output
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress
condition|)
name|gimp_progress_end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_propagate_prefixed_error
argument_list|(
name|error
argument_list|,
name|my_error
argument_list|,
name|_
argument_list|(
literal|"Could not open '%s' for writing: "
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|,
name|error
condition|?
operator|*
name|error
else|:
name|NULL
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

end_unit

