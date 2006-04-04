begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp-pdb.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_decl_stmt
DECL|variable|pattern_get_info_proc
specifier|static
name|GimpProcedure
name|pattern_get_info_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|pattern_get_pixels_proc
specifier|static
name|GimpProcedure
name|pattern_get_pixels_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_pattern_procs (Gimp * gimp)
name|register_pattern_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * pattern_get_info    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|pattern_get_info_proc
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The pattern name."
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
name|gimp_param_spec_int32
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The pattern width"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The pattern height"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"bpp"
argument_list|,
literal|"bpp"
argument_list|,
literal|"The pattern bpp"
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
name|gimp_pdb_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * pattern_get_pixels    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|pattern_get_pixels_proc
argument_list|,
literal|1
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The pattern name."
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
name|gimp_param_spec_int32
argument_list|(
literal|"width"
argument_list|,
literal|"width"
argument_list|,
literal|"The pattern width"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"height"
argument_list|,
literal|"height"
argument_list|,
literal|"The pattern height"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"bpp"
argument_list|,
literal|"bpp"
argument_list|,
literal|"The pattern bpp"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-color-bytes"
argument_list|,
literal|"num color bytes"
argument_list|,
literal|"Number of pattern bytes"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int8_array
argument_list|(
literal|"color-bytes"
argument_list|,
literal|"color bytes"
argument_list|,
literal|"The pattern data."
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|pattern_get_info_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|pattern_get_info_invoker
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|gint32
name|bpp
init|=
literal|0
decl_stmt|;
name|name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
operator|(
name|GimpPattern
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|pattern
condition|)
block|{
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|bpp
operator|=
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|3
index|]
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|pattern_get_info_proc
specifier|static
name|GimpProcedure
name|pattern_get_info_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-pattern-get-info"
block|,
literal|"gimp-pattern-get-info"
block|,
literal|"Retrieve information about the specified pattern."
block|,
literal|"This procedure retrieves information about the specified pattern. This includes the pattern extents (width and height)."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|pattern_get_info_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|pattern_get_pixels_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args)
name|pattern_get_pixels_invoker
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
name|GValueArray
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|GValueArray
modifier|*
name|return_vals
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|name
decl_stmt|;
name|gint32
name|width
init|=
literal|0
decl_stmt|;
name|gint32
name|height
init|=
literal|0
decl_stmt|;
name|gint32
name|bpp
init|=
literal|0
decl_stmt|;
name|gint32
name|num_color_bytes
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|color_bytes
init|=
name|NULL
decl_stmt|;
name|name
operator|=
name|g_value_get_string
argument_list|(
operator|&
name|args
operator|->
name|values
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|GimpPattern
modifier|*
name|pattern
init|=
operator|(
name|GimpPattern
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
decl_stmt|;
if|if
condition|(
name|pattern
condition|)
block|{
name|width
operator|=
name|pattern
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|bpp
operator|=
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
name|num_color_bytes
operator|=
name|pattern
operator|->
name|mask
operator|->
name|height
operator|*
name|pattern
operator|->
name|mask
operator|->
name|width
operator|*
name|pattern
operator|->
name|mask
operator|->
name|bytes
expr_stmt|;
name|color_bytes
operator|=
name|g_memdup
argument_list|(
name|temp_buf_data
argument_list|(
name|pattern
operator|->
name|mask
argument_list|)
argument_list|,
name|num_color_bytes
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
name|return_vals
operator|=
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|3
index|]
argument_list|,
name|bpp
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|4
index|]
argument_list|,
name|num_color_bytes
argument_list|)
expr_stmt|;
name|gimp_value_take_int8array
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|5
index|]
argument_list|,
name|color_bytes
argument_list|,
name|num_color_bytes
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|pattern_get_pixels_proc
specifier|static
name|GimpProcedure
name|pattern_get_pixels_proc
init|=
block|{
name|TRUE
block|,
name|TRUE
block|,
literal|"gimp-pattern-get-pixels"
block|,
literal|"gimp-pattern-get-pixels"
block|,
literal|"Retrieve information about the specified pattern (including pixels)."
block|,
literal|"This procedure retrieves information about the specified. This includes the pattern extents (width and height), its bpp and its pixel data."
block|,
literal|"Michael Natterer<mitch@gimp.org>"
block|,
literal|"Michael Natterer"
block|,
literal|"2004"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|pattern_get_pixels_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

