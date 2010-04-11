begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl. */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
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
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer-filter.h"
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
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb.h"
end_include

begin_include
include|#
directive|include
file|"gimppdb-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"internal-procs.h"
end_include

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_refresh_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_refresh_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gimp_data_factory_data_refresh
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|procedure
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_get_list_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_get_list_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|filter
decl_stmt|;
name|gint32
name|num_brushes
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|brush_list
init|=
name|NULL
decl_stmt|;
name|filter
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
name|brush_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
argument_list|,
name|filter
argument_list|,
operator|&
name|num_brushes
argument_list|)
expr_stmt|;
block|}
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
name|num_brushes
argument_list|)
expr_stmt|;
name|gimp_value_take_stringarray
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|brush_list
argument_list|,
name|num_brushes
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_get_brush_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_get_brush_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gchar
modifier|*
name|name
init|=
name|NULL
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
name|spacing
init|=
literal|0
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
init|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|brush
condition|)
block|{
name|name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|spacing
operator|=
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
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
block|{
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|name
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
literal|3
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
literal|4
index|]
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_get_spacing_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_get_spacing_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gint32
name|spacing
init|=
literal|0
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
init|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
decl_stmt|;
if|if
condition|(
name|brush
condition|)
name|spacing
operator|=
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
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
name|spacing
argument_list|)
expr_stmt|;
return|return
name|return_vals
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_set_spacing_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_set_spacing_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gint32
name|spacing
decl_stmt|;
name|spacing
operator|=
name|g_value_get_int
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
name|gimp_brush_set_spacing
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
block|}
return|return
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
return|;
block|}
end_function

begin_function
specifier|static
name|GValueArray
modifier|*
DECL|function|brushes_get_brush_data_invoker (GimpProcedure * procedure,Gimp * gimp,GimpContext * context,GimpProgress * progress,const GValueArray * args,GError ** error)
name|brushes_get_brush_data_invoker
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|gchar
modifier|*
name|actual_name
init|=
name|NULL
decl_stmt|;
name|gdouble
name|opacity
init|=
literal|0.0
decl_stmt|;
name|gint32
name|spacing
init|=
literal|0
decl_stmt|;
name|gint32
name|paint_mode
init|=
literal|0
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
name|length
init|=
literal|0
decl_stmt|;
name|guint8
modifier|*
name|mask_data
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
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
name|brush
operator|=
name|gimp_pdb_get_brush
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|,
name|FALSE
argument_list|,
name|error
argument_list|)
expr_stmt|;
else|else
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
condition|)
block|{
name|actual_name
operator|=
name|g_strdup
argument_list|(
name|gimp_object_get_name
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|opacity
operator|=
literal|1.0
expr_stmt|;
name|spacing
operator|=
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|paint_mode
operator|=
literal|0
expr_stmt|;
name|width
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|length
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
operator|*
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|mask_data
operator|=
name|g_memdup
argument_list|(
name|temp_buf_get_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
argument_list|,
name|length
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
block|{
name|g_value_take_string
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|1
index|]
argument_list|,
name|actual_name
argument_list|)
expr_stmt|;
name|g_value_set_double
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|2
index|]
argument_list|,
name|opacity
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
name|spacing
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|4
index|]
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|5
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
literal|6
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
literal|7
index|]
argument_list|,
name|length
argument_list|)
expr_stmt|;
name|gimp_value_take_int8array
argument_list|(
operator|&
name|return_vals
operator|->
name|values
index|[
literal|8
index|]
argument_list|,
name|mask_data
argument_list|,
name|length
argument_list|)
expr_stmt|;
block|}
return|return
name|return_vals
return|;
block|}
end_function

begin_function
name|void
DECL|function|register_brushes_procs (GimpPDB * pdb)
name|register_brushes_procs
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|)
block|{
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
comment|/*    * gimp-brushes-refresh    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_refresh_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-refresh"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-refresh"
argument_list|,
literal|"Refresh current brushes. This function always succeeds."
argument_list|,
literal|"This procedure retrieves all brushes currently in the user's brush path and updates the brush dialogs accordingly."
argument_list|,
literal|"Seth Burgess"
argument_list|,
literal|"Seth Burgess"
argument_list|,
literal|"1997"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-brushes-get-list    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_get_list_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-get-list"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-get-list"
argument_list|,
literal|"Retrieve a complete listing of the available brushes."
argument_list|,
literal|"This procedure returns a complete listing of available GIMP brushes. Each name returned can be used as input to the 'gimp-context-set-brush' procedure."
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
name|gimp_param_spec_string
argument_list|(
literal|"filter"
argument_list|,
literal|"filter"
argument_list|,
literal|"An optional regular expression used to filter the list"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"num-brushes"
argument_list|,
literal|"num brushes"
argument_list|,
literal|"The number of brushes in the brush list"
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
name|gimp_param_spec_string_array
argument_list|(
literal|"brush-list"
argument_list|,
literal|"brush list"
argument_list|,
literal|"The list of brush names"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-brushes-get-brush    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_get_brush_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-get-brush"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-get-brush"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-context-get-brush' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-context-get-brush' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-context-get-brush"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The brush name"
argument_list|,
name|FALSE
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
literal|"The brush width"
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
literal|"The brush height"
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
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The brush spacing"
argument_list|,
literal|0
argument_list|,
literal|1000
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-brushes-get-spacing    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_get_spacing_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-get-spacing"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-get-spacing"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-get-spacing' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-get-spacing' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-brush-get-spacing"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The brush spacing"
argument_list|,
literal|0
argument_list|,
literal|1000
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-brushes-set-spacing    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_set_spacing_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-set-spacing"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-set-spacing"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-set-spacing' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-set-spacing' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-brush-set-spacing"
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_int32
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The brush spacing"
argument_list|,
literal|0
argument_list|,
literal|1000
argument_list|,
literal|0
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * gimp-brushes-get-brush-data    */
name|procedure
operator|=
name|gimp_procedure_new
argument_list|(
name|brushes_get_brush_data_invoker
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"gimp-brushes-get-brush-data"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"gimp-brushes-get-brush-data"
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-get-pixels' instead."
argument_list|,
literal|"This procedure is deprecated! Use 'gimp-brush-get-pixels' instead."
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|,
literal|"gimp-brush-get-pixels"
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
literal|"The brush name (\"\" means current active brush)"
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
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"actual-name"
argument_list|,
literal|"actual name"
argument_list|,
literal|"The brush name"
argument_list|,
name|FALSE
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
name|g_param_spec_double
argument_list|(
literal|"opacity"
argument_list|,
literal|"opacity"
argument_list|,
literal|"The brush opacity"
argument_list|,
literal|0
argument_list|,
literal|100
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
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The brush spacing"
argument_list|,
literal|0
argument_list|,
literal|1000
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
name|g_param_spec_enum
argument_list|(
literal|"paint-mode"
argument_list|,
literal|"paint mode"
argument_list|,
literal|"The paint mode"
argument_list|,
name|GIMP_TYPE_LAYER_MODE_EFFECTS
argument_list|,
name|GIMP_NORMAL_MODE
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
literal|"The brush width"
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
literal|"The brush height"
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
literal|"length"
argument_list|,
literal|"length"
argument_list|,
literal|"Length of brush mask data"
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
literal|"mask-data"
argument_list|,
literal|"mask data"
argument_list|,
literal|"The brush mask data"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pdb_register_procedure
argument_list|(
name|pdb
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

