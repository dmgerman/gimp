begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpbrushselect_pdb.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|void
DECL|function|gimp_brushes_popup (gchar * brush_callback,gchar * popup_title,gchar * initial_brush,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode)
name|gimp_brushes_popup
parameter_list|(
name|gchar
modifier|*
name|brush_callback
parameter_list|,
name|gchar
modifier|*
name|popup_title
parameter_list|,
name|gchar
modifier|*
name|initial_brush
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_brushes_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|brush_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|popup_title
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|initial_brush
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|spacing
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brushes_close_popup (gchar * brush_callback)
name|gimp_brushes_close_popup
parameter_list|(
name|gchar
modifier|*
name|brush_callback
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_brushes_close_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|brush_callback
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brushes_set_popup (gchar * brush_callback,gchar * brush_name,gdouble opacity,gint spacing,GimpLayerModeEffects paint_mode)
name|gimp_brushes_set_popup
parameter_list|(
name|gchar
modifier|*
name|brush_callback
parameter_list|,
name|gchar
modifier|*
name|brush_name
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gint
name|spacing
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_brushes_set_popup"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|brush_callback
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|brush_name
argument_list|,
name|GIMP_PDB_FLOAT
argument_list|,
name|opacity
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|spacing
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|paint_mode
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

