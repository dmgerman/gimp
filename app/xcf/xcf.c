begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
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
file|<glib-object.h>
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
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
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
DECL|typedef|info
name|XcfInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
specifier|static
name|Argument
modifier|*
name|xcf_load_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|xcf_save_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|xcf_load_args
specifier|static
name|ProcArg
name|xcf_load_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"dummy_param"
block|,
literal|"dummy parameter"
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
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xcf_load_return_vals
specifier|static
name|ProcArg
name|xcf_load_return_vals
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
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xcf_plug_in_load_proc
specifier|static
name|PlugInProcDef
name|xcf_plug_in_load_proc
init|=
block|{
literal|"gimp_xcf_load"
block|,
literal|"<Load>/XCF (GIMP)"
block|,
name|NULL
block|,
literal|"xcf"
block|,
literal|""
block|,
literal|"0,string,gimp\\040xcf\\040"
block|,
name|NULL
block|,
comment|/* ignored for load */
literal|0
block|,
comment|/* ignored for load */
block|{
literal|"gimp_xcf_load"
block|,
literal|"loads file saved in the .xcf file format"
block|,
literal|"The xcf file format has been designed specifically for loading and saving tiled and layered images in the GIMP. This procedure will load the specified file."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|3
block|,
name|xcf_load_args
block|,
literal|1
block|,
name|xcf_load_return_vals
block|,
block|{
block|{
name|xcf_load_invoker
block|}
block|}
block|,   }
block|,
name|NULL
block|,
comment|/* fill me in at runtime */
name|NULL
block|,
comment|/* fill me in at runtime */
name|NULL
block|,
comment|/* fill me in at runtime */
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xcf_save_args
specifier|static
name|ProcArg
name|xcf_save_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"dummy_param"
block|,
literal|"dummy parameter"
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
literal|"Active drawable of input image"
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
literal|"raw_filename"
block|,
literal|"The name of the file to load"
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xcf_plug_in_save_proc
specifier|static
name|PlugInProcDef
name|xcf_plug_in_save_proc
init|=
block|{
literal|"gimp_xcf_save"
block|,
literal|"<Save>/XCF (GIMP)"
block|,
name|NULL
block|,
literal|"xcf"
block|,
literal|""
block|,
name|NULL
block|,
literal|"RGB*, GRAY*, INDEXED*"
block|,
literal|0
block|,
comment|/* fill me in at runtime */
block|{
literal|"gimp_xcf_save"
block|,
literal|"saves file in the .xcf file format"
block|,
literal|"The xcf file format has been designed specifically for loading and saving tiled and layered images in the GIMP. This procedure will save the specified image in the xcf file format."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|GIMP_INTERNAL
block|,
literal|5
block|,
name|xcf_save_args
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|xcf_save_invoker
block|}
block|}
block|,   }
block|,
name|NULL
block|,
comment|/* fill me in at runtime */
name|NULL
block|,
comment|/* fill me in at runtime */
name|NULL
block|,
comment|/* fill me in at runtime */
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|xcf_loaders
specifier|static
name|GimpXcfLoaderFunc
modifier|*
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
comment|/* version 2 */
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
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* So this is sort of a hack, but its better than it was before.  To do this    * right there would be a file load-save handler type and the whole interface    * would change but there isn't, and currently the plug-in structure contains    * all the load-save info, so it makes sense to use that for the XCF load/save    * handlers, even though they are internal.  The only thing it requires is    * using a PlugInProcDef struct.  -josh    */
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|xcf_plug_in_save_proc
operator|.
name|db_info
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|xcf_plug_in_load_proc
operator|.
name|db_info
argument_list|)
expr_stmt|;
name|xcf_plug_in_save_proc
operator|.
name|image_types_val
operator|=
name|plug_ins_image_types_parse
argument_list|(
name|xcf_plug_in_save_proc
operator|.
name|image_types
argument_list|)
expr_stmt|;
name|xcf_plug_in_load_proc
operator|.
name|image_types_val
operator|=
name|plug_ins_image_types_parse
argument_list|(
name|xcf_plug_in_load_proc
operator|.
name|image_types
argument_list|)
expr_stmt|;
name|plug_ins_add_internal
argument_list|(
name|gimp
argument_list|,
operator|&
name|xcf_plug_in_save_proc
argument_list|)
expr_stmt|;
name|plug_ins_add_internal
argument_list|(
name|gimp
argument_list|,
operator|&
name|xcf_plug_in_load_proc
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
name|Argument
modifier|*
DECL|function|xcf_load_invoker (Gimp * gimp,Argument * args)
name|xcf_load_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|XcfInfo
name|info
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|gchar
name|id
index|[
literal|14
index|]
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|NULL
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
name|filename
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|info
operator|.
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|.
name|fp
condition|)
block|{
name|info
operator|.
name|cp
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|info
operator|.
name|active_layer
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|active_channel
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel_drawable
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel_offset
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|swap_num
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|ref_count
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|compression
operator|=
name|COMPRESS_NONE
expr_stmt|;
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
name|fp
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
name|strncmp
argument_list|(
name|id
argument_list|,
literal|"gimp xcf "
argument_list|,
literal|9
argument_list|)
operator|!=
literal|0
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
operator|<
name|G_N_ELEMENTS
argument_list|(
name|xcf_loaders
argument_list|)
condition|)
block|{
name|gimage
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
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
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
name|fclose
argument_list|(
name|info
operator|.
name|fp
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|xcf_plug_in_load_proc
operator|.
name|db_info
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_image_get_ID
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|xcf_save_invoker (Gimp * gimp,Argument * args)
name|xcf_save_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|XcfInfo
name|info
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
name|gimage
operator|=
name|gimp_image_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
argument_list|)
expr_stmt|;
name|filename
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|info
operator|.
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"wb"
argument_list|)
expr_stmt|;
if|if
condition|(
name|info
operator|.
name|fp
condition|)
block|{
name|info
operator|.
name|cp
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|filename
operator|=
name|filename
expr_stmt|;
name|info
operator|.
name|active_layer
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|active_channel
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel_drawable
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|floating_sel_offset
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|swap_num
operator|=
literal|0
expr_stmt|;
name|info
operator|.
name|ref_count
operator|=
name|NULL
expr_stmt|;
name|info
operator|.
name|compression
operator|=
name|COMPRESS_RLE
expr_stmt|;
name|xcf_save_choose_format
argument_list|(
operator|&
name|info
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|success
operator|=
name|xcf_save_image
argument_list|(
operator|&
name|info
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|fclose
argument_list|(
name|info
operator|.
name|fp
argument_list|)
operator|==
name|EOF
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Error saving XCF file: %s"
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"open failed on %s: %s\n"
argument_list|)
argument_list|,
name|filename
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|xcf_plug_in_save_proc
operator|.
name|db_info
argument_list|,
name|success
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

end_unit

