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
file|"procedural_db.h"
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
file|"core/gimplist.h"
end_include

begin_decl_stmt
DECL|variable|brushes_refresh_proc
specifier|static
name|ProcRecord
name|brushes_refresh_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_list_proc
specifier|static
name|ProcRecord
name|brushes_get_list_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_proc
specifier|static
name|ProcRecord
name|brushes_get_brush_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_spacing_proc
specifier|static
name|ProcRecord
name|brushes_get_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_spacing_proc
specifier|static
name|ProcRecord
name|brushes_set_spacing_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_data_proc
specifier|static
name|ProcRecord
name|brushes_get_brush_data_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_brushes_procs (Gimp * gimp)
name|register_brushes_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_refresh_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_get_list_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_get_brush_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_get_spacing_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_set_spacing_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_get_brush_data_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_refresh_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_refresh_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_data_factory_data_refresh
argument_list|(
name|gimp
operator|->
name|brush_factory
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_refresh_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_refresh_proc
specifier|static
name|ProcRecord
name|brushes_refresh_proc
init|=
block|{
literal|"gimp_brushes_refresh"
block|,
literal|"Refresh current brushes. This function always succeeds."
block|,
literal|"This procedure retrieves all brushes currently in the user's brush path and updates the brush dialogs accordingly."
block|,
literal|"Seth Burgess"
block|,
literal|"Seth Burgess"
block|,
literal|"1997"
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
name|brushes_refresh_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_list_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_get_list_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_brushes
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
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|filter
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|filter
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|brush_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|filter
argument_list|,
operator|&
name|num_brushes
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_list_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_brushes
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|brush_list
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_get_list_inargs
specifier|static
name|ProcArg
name|brushes_get_list_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"filter"
block|,
literal|"An optional regular expression used to filter the list"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_list_outargs
specifier|static
name|ProcArg
name|brushes_get_list_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num_brushes"
block|,
literal|"The number of brushes in the brush list"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"brush_list"
block|,
literal|"The list of brush names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_list_proc
specifier|static
name|ProcRecord
name|brushes_get_list_proc
init|=
block|{
literal|"gimp_brushes_get_list"
block|,
literal|"Retrieve a complete listing of the available brushes."
block|,
literal|"This procedure returns a complete listing of available GIMP brushes. Each name returned can be used as input to the 'gimp_context_set_brush' procedure."
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|brushes_get_list_inargs
block|,
literal|2
block|,
name|brushes_get_list_outargs
block|,
block|{
block|{
name|brushes_get_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_brush_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_get_brush_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|success
operator|=
operator|(
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_brush_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|spacing
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_get_brush_outargs
specifier|static
name|ProcArg
name|brushes_get_brush_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"name"
block|,
literal|"The brush name"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The brush width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The brush height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The brush spacing: 0<= spacing<= 1000"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_proc
specifier|static
name|ProcRecord
name|brushes_get_brush_proc
init|=
block|{
literal|"gimp_brushes_get_brush"
block|,
literal|"This procedure is deprecated! Use 'gimp_context_get_brush' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp_context_get_brush' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp_context_get_brush"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|4
block|,
name|brushes_get_brush_outargs
block|,
block|{
block|{
name|brushes_get_brush_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_spacing_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_get_spacing_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_spacing_proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_brush_get_spacing
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_get_spacing_outargs
specifier|static
name|ProcArg
name|brushes_get_spacing_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The brush spacing: 0<= spacing<= 1000"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_spacing_proc
specifier|static
name|ProcRecord
name|brushes_get_spacing_proc
init|=
block|{
literal|"gimp_brushes_get_spacing"
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_get_spacing' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_get_spacing' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp_brush_get_spacing"
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|1
block|,
name|brushes_get_spacing_outargs
block|,
block|{
block|{
name|brushes_get_spacing_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_spacing_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_set_spacing_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
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
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|spacing
operator|<
literal|0
operator|||
name|spacing
operator|>
literal|1000
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
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
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_set_spacing_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_set_spacing_inargs
specifier|static
name|ProcArg
name|brushes_set_spacing_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The brush spacing: 0<= spacing<= 1000"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_spacing_proc
specifier|static
name|ProcRecord
name|brushes_set_spacing_proc
init|=
block|{
literal|"gimp_brushes_set_spacing"
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_set_spacing' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_set_spacing' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp_brush_set_spacing"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|brushes_set_spacing_inargs
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|brushes_set_spacing_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_get_brush_data_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_get_brush_data_invoker
parameter_list|(
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
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|GimpBrush
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|name
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|name
operator|&&
name|strlen
argument_list|(
name|name
argument_list|)
condition|)
block|{
name|brush
operator|=
operator|(
name|GimpBrush
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|brush
condition|)
block|{
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
name|temp_buf_data
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
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_get_brush_data_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|g_strdup
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
operator|=
literal|1.0
expr_stmt|;
name|return_args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|spacing
expr_stmt|;
name|return_args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
literal|0
expr_stmt|;
name|return_args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|mask
operator|->
name|width
expr_stmt|;
name|return_args
index|[
literal|6
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|brush
operator|->
name|mask
operator|->
name|height
expr_stmt|;
name|return_args
index|[
literal|7
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|length
expr_stmt|;
name|return_args
index|[
literal|8
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|mask_data
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_get_brush_data_inargs
specifier|static
name|ProcArg
name|brushes_get_brush_data_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"name"
block|,
literal|"The brush name (\"\" means current active brush)"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_data_outargs
specifier|static
name|ProcArg
name|brushes_get_brush_data_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"name"
block|,
literal|"The brush name"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The brush opacity: 0<= opacity<= 100"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The brush spacing: 0<= spacing<= 1000"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The paint mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_SOFTLIGHT_MODE (19), GIMP_GRAIN_EXTRACT_MODE (20), GIMP_GRAIN_MERGE_MODE (21), GIMP_COLOR_ERASE_MODE (22) }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The brush width"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"height"
block|,
literal|"The brush height"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"length"
block|,
literal|"Length of brush mask data"
block|}
block|,
block|{
name|GIMP_PDB_INT8ARRAY
block|,
literal|"mask_data"
block|,
literal|"The brush mask data"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_get_brush_data_proc
specifier|static
name|ProcRecord
name|brushes_get_brush_data_proc
init|=
block|{
literal|"gimp_brushes_get_brush_data"
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_get_pixels' instead."
block|,
literal|"This procedure is deprecated! Use 'gimp_brush_get_pixels' instead."
block|,
literal|""
block|,
literal|""
block|,
literal|""
block|,
literal|"gimp_brush_get_pixels"
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|brushes_get_brush_data_inargs
block|,
literal|8
block|,
name|brushes_get_brush_data_outargs
block|,
block|{
block|{
name|brushes_get_brush_data_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

