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
file|"gimpprocedure.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_decl_stmt
DECL|variable|brushes_popup_proc
specifier|static
name|ProcRecord
name|brushes_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_close_popup_proc
specifier|static
name|ProcRecord
name|brushes_close_popup_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_popup_proc
specifier|static
name|ProcRecord
name|brushes_set_popup_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_brush_select_procs (Gimp * gimp)
name|register_brush_select_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|procedure
decl_stmt|;
comment|/*    * brushes_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|brushes_popup_proc
argument_list|,
literal|6
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"brush-callback"
argument_list|,
literal|"brush callback"
argument_list|,
literal|"The callback PDB proc to call when brush selection is made"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"popup-title"
argument_list|,
literal|"popup title"
argument_list|,
literal|"Title to give the brush popup window"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"initial-brush"
argument_list|,
literal|"initial brush"
argument_list|,
literal|"The name of the brush to set as the first selected"
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
name|GIMP_PDB_FLOAT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"opacity"
argument_list|,
literal|"opacity"
argument_list|,
literal|"The initial opacity of the brush"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The initial spacing of the brush (if< 0 then use brush default spacing)"
argument_list|,
name|G_MININT32
argument_list|,
literal|1000
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
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"paint-mode"
argument_list|,
literal|"paint mode"
argument_list|,
literal|"The initial paint mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_SOFTLIGHT_MODE (19), GIMP_GRAIN_EXTRACT_MODE (20), GIMP_GRAIN_MERGE_MODE (21), GIMP_COLOR_ERASE_MODE (22) }"
argument_list|,
name|GIMP_TYPE_LAYER_MODE_EFFECTS
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * brushes_close_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|brushes_close_popup_proc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"brush-callback"
argument_list|,
literal|"brush callback"
argument_list|,
literal|"The name of the callback registered for this popup"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
name|procedure
argument_list|)
expr_stmt|;
comment|/*    * brushes_set_popup    */
name|procedure
operator|=
name|gimp_procedure_init
argument_list|(
operator|&
name|brushes_set_popup_proc
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"brush-callback"
argument_list|,
literal|"brush callback"
argument_list|,
literal|"The name of the callback registered for this popup"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"brush-name"
argument_list|,
literal|"brush name"
argument_list|,
literal|"The name of the brush to set as selected"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"opacity"
argument_list|,
literal|"opacity"
argument_list|,
literal|"The initial opacity of the brush"
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
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"The initial spacing of the brush (if< 0 then use brush default spacing)"
argument_list|,
name|G_MININT32
argument_list|,
literal|1000
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
name|GIMP_PDB_INT32
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"paint-mode"
argument_list|,
literal|"paint mode"
argument_list|,
literal|"The initial paint mode: { GIMP_NORMAL_MODE (0), GIMP_DISSOLVE_MODE (1), GIMP_BEHIND_MODE (2), GIMP_MULTIPLY_MODE (3), GIMP_SCREEN_MODE (4), GIMP_OVERLAY_MODE (5), GIMP_DIFFERENCE_MODE (6), GIMP_ADDITION_MODE (7), GIMP_SUBTRACT_MODE (8), GIMP_DARKEN_ONLY_MODE (9), GIMP_LIGHTEN_ONLY_MODE (10), GIMP_HUE_MODE (11), GIMP_SATURATION_MODE (12), GIMP_COLOR_MODE (13), GIMP_VALUE_MODE (14), GIMP_DIVIDE_MODE (15), GIMP_DODGE_MODE (16), GIMP_BURN_MODE (17), GIMP_HARDLIGHT_MODE (18), GIMP_SOFTLIGHT_MODE (19), GIMP_GRAIN_EXTRACT_MODE (20), GIMP_GRAIN_MERGE_MODE (21), GIMP_COLOR_ERASE_MODE (22) }"
argument_list|,
name|GIMP_TYPE_LAYER_MODE_EFFECTS
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|procedural_db_register
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
name|Argument
modifier|*
DECL|function|brushes_popup_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_popup_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|gchar
modifier|*
name|brush_callback
decl_stmt|;
name|gchar
modifier|*
name|popup_title
decl_stmt|;
name|gchar
modifier|*
name|initial_brush
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gint32
name|spacing
decl_stmt|;
name|gint32
name|paint_mode
decl_stmt|;
name|brush_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|popup_title
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|initial_brush
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|2
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|g_value_get_double
argument_list|(
operator|&
name|args
index|[
literal|3
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|spacing
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
literal|4
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|paint_mode
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
index|[
literal|5
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|brush_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_new
argument_list|(
name|gimp
argument_list|,
name|context
argument_list|,
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|popup_title
argument_list|,
name|brush_callback
argument_list|,
name|initial_brush
argument_list|,
literal|"opacity"
argument_list|,
name|opacity
operator|/
literal|100.0
argument_list|,
literal|"paint-mode"
argument_list|,
name|paint_mode
argument_list|,
literal|"spacing"
argument_list|,
name|spacing
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_popup_proc
specifier|static
name|ProcRecord
name|brushes_popup_proc
init|=
block|{
literal|"gimp-brushes-popup"
block|,
literal|"gimp-brushes-popup"
block|,
literal|"Invokes the Gimp brush selection."
block|,
literal|"This procedure popups the brush selection dialog."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|brushes_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_close_popup_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_close_popup_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|gchar
modifier|*
name|brush_callback
decl_stmt|;
name|brush_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|brush_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_close
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|brush_callback
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_close_popup_proc
specifier|static
name|ProcRecord
name|brushes_close_popup_proc
init|=
block|{
literal|"gimp-brushes-close-popup"
block|,
literal|"gimp-brushes-close-popup"
block|,
literal|"Popdown the Gimp brush selection."
block|,
literal|"This procedure closes an opened brush selection dialog."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|brushes_close_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_set_popup_invoker (ProcRecord * proc_record,Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|brushes_set_popup_invoker
parameter_list|(
name|ProcRecord
modifier|*
name|proc_record
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
name|gchar
modifier|*
name|brush_callback
decl_stmt|;
name|gchar
modifier|*
name|brush_name
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gint32
name|spacing
decl_stmt|;
name|gint32
name|paint_mode
decl_stmt|;
name|brush_callback
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|brush_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|g_value_get_string
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|opacity
operator|=
name|g_value_get_double
argument_list|(
operator|&
name|args
index|[
literal|2
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|spacing
operator|=
name|g_value_get_int
argument_list|(
operator|&
name|args
index|[
literal|3
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
name|paint_mode
operator|=
name|g_value_get_enum
argument_list|(
operator|&
name|args
index|[
literal|4
index|]
operator|.
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
if|if
condition|(
name|gimp
operator|->
name|no_interface
operator|||
operator|!
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|brush_callback
argument_list|)
operator|||
operator|!
name|gimp_pdb_dialog_set
argument_list|(
name|gimp
argument_list|,
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|brush_callback
argument_list|,
name|brush_name
argument_list|,
literal|"opacity"
argument_list|,
name|opacity
operator|/
literal|100.0
argument_list|,
literal|"paint-mode"
argument_list|,
name|paint_mode
argument_list|,
literal|"spacing"
argument_list|,
name|spacing
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|gimp_procedure_get_return_values
argument_list|(
name|proc_record
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_set_popup_proc
specifier|static
name|ProcRecord
name|brushes_set_popup_proc
init|=
block|{
literal|"gimp-brushes-set-popup"
block|,
literal|"gimp-brushes-set-popup"
block|,
literal|"Sets the current brush selection in a popup."
block|,
literal|"Sets the current brush selection in a popup."
block|,
literal|"Andy Thomas"
block|,
literal|"Andy Thomas"
block|,
literal|"1998"
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
name|brushes_set_popup_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

