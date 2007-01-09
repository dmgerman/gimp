begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpselection_pdb.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SELECTION_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SELECTION_PDB_H__
define|#
directive|define
name|__GIMP_SELECTION_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_selection_bounds
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
modifier|*
name|non_empty
parameter_list|,
name|gint
modifier|*
name|x1
parameter_list|,
name|gint
modifier|*
name|y1
parameter_list|,
name|gint
modifier|*
name|x2
parameter_list|,
name|gint
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_selection_value
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_is_empty
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_translate
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|G_GNUC_INTERNAL
name|gint32
name|_gimp_selection_float
parameter_list|(
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_invert
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_sharpen
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_all
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_none
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_feather
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gdouble
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_border
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|radius
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_grow
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_shrink
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_layer_alpha
parameter_list|(
name|gint32
name|layer_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_load
parameter_list|(
name|gint32
name|channel_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|gimp_selection_save
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_selection_combine
parameter_list|(
name|gint32
name|channel_ID
parameter_list|,
name|GimpChannelOps
name|operation
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SELECTION_PDB_H__ */
end_comment

end_unit

