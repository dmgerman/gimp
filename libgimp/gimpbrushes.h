begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpbrushes.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimp.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSHES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSHES_H__
define|#
directive|define
name|__GIMP_BRUSHES_H__
end_define

begin_decl_stmt
name|G_BEGIN_DECLS
comment|/* For information look into the C source or the html documentation */
name|GIMP_DEPRECATED_FOR
argument_list|(
name|gimp_context_get_opacity
argument_list|)
name|gdouble
name|gimp_brushes_get_opacity
argument_list|(
name|void
argument_list|)
decl_stmt|;
end_decl_stmt

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_context_set_opacity
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_brushes_set_opacity
parameter_list|(
name|gdouble
name|opacity
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_context_get_paint_mode
argument_list|)
end_macro

begin_function_decl
name|GimpLayerModeEffects
name|gimp_brushes_get_paint_mode
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_context_set_paint_mode
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_brushes_set_paint_mode
parameter_list|(
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_context_set_brush
argument_list|)
end_macro

begin_function_decl
name|gboolean
name|gimp_brushes_set_brush
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
comment|/* __GIMP_BRUSHES_H__ */
end_comment

end_unit

