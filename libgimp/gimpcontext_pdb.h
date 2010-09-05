begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpcontext_pdb.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* NOTE: This file is auto-generated by pdbgen.pl */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTEXT_PDB_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTEXT_PDB_H__
define|#
directive|define
name|__GIMP_CONTEXT_PDB_H__
end_define

begin_function_decl
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|gboolean
name|gimp_context_push
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_pop
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_list_paint_methods
parameter_list|(
name|gint
modifier|*
name|num_paint_methods
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|paint_methods
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_paint_method
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_paint_method
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_get_foreground
parameter_list|(
name|GimpRGB
modifier|*
name|foreground
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_foreground
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|foreground
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_get_background
parameter_list|(
name|GimpRGB
modifier|*
name|background
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_background
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|background
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_default_colors
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_swap_colors
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_context_get_opacity
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_opacity
parameter_list|(
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerModeEffects
name|gimp_context_get_paint_mode
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_paint_mode
parameter_list|(
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_brush
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_brush
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_pattern
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_pattern
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_gradient
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_gradient
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_palette
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_palette
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_context_get_font
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_font
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_get_antialias
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_antialias
parameter_list|(
name|gboolean
name|antialias
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_get_feather
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_feather
parameter_list|(
name|gboolean
name|feather
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_get_feather_radius
parameter_list|(
name|gdouble
modifier|*
name|feather_radius_x
parameter_list|,
name|gdouble
modifier|*
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_context_set_feather_radius
parameter_list|(
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
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
comment|/* __GIMP_CONTEXT_PDB_H__ */
end_comment

end_unit

