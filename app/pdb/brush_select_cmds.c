begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2000 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"base/base-types.h"
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
file|"gui/brush-select.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpbrushfactoryview.h"
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
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_close_popup_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|brushes_set_popup_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|brushes_popup_invoker (Gimp * gimp,Argument * args)
name|brushes_popup_invoker
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gchar
modifier|*
name|brush
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
name|ProcRecord
modifier|*
name|prec
decl_stmt|;
name|BrushSelect
modifier|*
name|newdialog
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
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|title
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|title
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|brush
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
name|opacity
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|spacing
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|paint_mode
operator|=
name|args
index|[
literal|5
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|<
name|NORMAL_MODE
operator|||
name|paint_mode
operator|>
name|HARDLIGHT_MODE
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
operator|(
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|brush
operator|&&
name|strlen
argument_list|(
name|brush
argument_list|)
condition|)
name|newdialog
operator|=
name|brush_select_new
argument_list|(
name|gimp
argument_list|,
name|title
argument_list|,
name|brush
argument_list|,
name|opacity
argument_list|,
name|spacing
argument_list|,
name|paint_mode
argument_list|,
name|name
argument_list|)
expr_stmt|;
else|else
name|newdialog
operator|=
name|brush_select_new
argument_list|(
name|gimp
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|,
literal|0.0
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|name
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
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_popup_inargs
specifier|static
name|ProcArg
name|brushes_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"brush_callback"
block|,
literal|"The callback PDB proc to call when brush selection is made"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"popup_title"
block|,
literal|"Title to give the brush popup window"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"initial_brush"
block|,
literal|"The name of the brush to set as the first selected"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The initial opacity of the brush"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The initial spacing of the brush (if< 0 then use brush default spacing)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The initial paint mode: { NORMAL_MODE (0), DISSOLVE_MODE (1), BEHIND_MODE (2), MULTIPLY_MODE (3), SCREEN_MODE (4), OVERLAY_MODE (5), DIFFERENCE_MODE (6), ADDITION_MODE (7), SUBTRACT_MODE (8), DARKEN_ONLY_MODE (9), LIGHTEN_ONLY_MODE (10), HUE_MODE (11), SATURATION_MODE (12), COLOR_MODE (13), VALUE_MODE (14), DIVIDE_MODE (15), DODGE_MODE (16), BURN_MODE (17), HARDLIGHT_MODE (18) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_popup_proc
specifier|static
name|ProcRecord
name|brushes_popup_proc
init|=
block|{
literal|"gimp_brushes_popup"
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
name|GIMP_INTERNAL
block|,
literal|6
block|,
name|brushes_popup_inargs
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
DECL|function|brushes_close_popup_invoker (Gimp * gimp,Argument * args)
name|brushes_close_popup_invoker
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|ProcRecord
modifier|*
name|prec
decl_stmt|;
name|BrushSelect
modifier|*
name|bsp
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
operator|==
name|NULL
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
operator|(
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|)
operator|)
operator|&&
operator|(
name|bsp
operator|=
name|brush_select_get_by_callback
argument_list|(
name|name
argument_list|)
operator|)
condition|)
block|{
name|brush_select_free
argument_list|(
name|bsp
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
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_close_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_close_popup_inargs
specifier|static
name|ProcArg
name|brushes_close_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"brush_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_close_popup_proc
specifier|static
name|ProcRecord
name|brushes_close_popup_proc
init|=
block|{
literal|"gimp_brushes_close_popup"
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
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|brushes_close_popup_inargs
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
DECL|function|brushes_set_popup_invoker (Gimp * gimp,Argument * args)
name|brushes_set_popup_invoker
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
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|gchar
modifier|*
name|name
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
name|ProcRecord
modifier|*
name|prec
decl_stmt|;
name|BrushSelect
modifier|*
name|bsp
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
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|brush_name
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|brush_name
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
name|opacity
operator|=
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_float
expr_stmt|;
name|spacing
operator|=
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|paint_mode
operator|=
name|args
index|[
literal|4
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
if|if
condition|(
name|paint_mode
operator|<
name|NORMAL_MODE
operator|||
name|paint_mode
operator|>
name|HARDLIGHT_MODE
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
operator|(
name|prec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
name|name
argument_list|)
operator|)
operator|&&
operator|(
name|bsp
operator|=
name|brush_select_get_by_callback
argument_list|(
name|name
argument_list|)
operator|)
condition|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|gimp_container_get_child_by_name
argument_list|(
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|brush_name
argument_list|)
decl_stmt|;
if|if
condition|(
name|object
condition|)
block|{
name|GimpBrush
modifier|*
name|active
init|=
name|GIMP_BRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkAdjustment
modifier|*
name|spacing_adj
decl_stmt|;
name|spacing_adj
operator|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|bsp
operator|->
name|view
argument_list|)
operator|->
name|spacing_adjustment
expr_stmt|;
comment|/* Updating the context updates the widgets as well */
name|gimp_context_set_brush
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|active
argument_list|)
expr_stmt|;
name|gimp_context_set_opacity
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|bsp
operator|->
name|context
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|spacing_adj
argument_list|,
name|spacing
argument_list|)
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|brushes_set_popup_proc
argument_list|,
name|success
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|brushes_set_popup_inargs
specifier|static
name|ProcArg
name|brushes_set_popup_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"brush_callback"
block|,
literal|"The name of the callback registered for this popup"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"brush_name"
block|,
literal|"The name of the brush to set as selected"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"opacity"
block|,
literal|"The initial opacity of the brush"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"spacing"
block|,
literal|"The initial spacing of the brush (if< 0 then use brush default spacing)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"paint_mode"
block|,
literal|"The initial paint mode: { NORMAL_MODE (0), DISSOLVE_MODE (1), BEHIND_MODE (2), MULTIPLY_MODE (3), SCREEN_MODE (4), OVERLAY_MODE (5), DIFFERENCE_MODE (6), ADDITION_MODE (7), SUBTRACT_MODE (8), DARKEN_ONLY_MODE (9), LIGHTEN_ONLY_MODE (10), HUE_MODE (11), SATURATION_MODE (12), COLOR_MODE (13), VALUE_MODE (14), DIVIDE_MODE (15), DODGE_MODE (16), BURN_MODE (17), HARDLIGHT_MODE (18) }"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|brushes_set_popup_proc
specifier|static
name|ProcRecord
name|brushes_set_popup_proc
init|=
block|{
literal|"gimp_brushes_set_popup"
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
name|GIMP_INTERNAL
block|,
literal|5
block|,
name|brushes_set_popup_inargs
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

