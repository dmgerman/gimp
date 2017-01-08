begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpbrushmenu.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_UI_H_INSIDE__
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
literal|"Only<libgimp/gimpui.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_MENU_H__
define|#
directive|define
name|__GIMP_BRUSH_MENU_H__
end_define

begin_comment
comment|/*  These functions are deprecated and should not be used in newly  *  written code.  */
end_comment

begin_decl_stmt
name|G_BEGIN_DECLS
name|GIMP_DEPRECATED_FOR
argument_list|(
name|gimp_brush_select_button_new
argument_list|)
name|GtkWidget
modifier|*
name|gimp_brush_select_widget_new
argument_list|(
specifier|const
name|gchar
operator|*
name|title
argument_list|,
specifier|const
name|gchar
operator|*
name|brush_name
argument_list|,
name|gdouble
name|opacity
argument_list|,
name|gint
name|spacing
argument_list|,
name|GimpLayerMode
name|paint_mode
argument_list|,
name|GimpRunBrushCallback
name|callback
argument_list|,
name|gpointer
name|data
argument_list|)
decl_stmt|;
end_decl_stmt

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_select_button_close_popup
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_brush_select_widget_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|GIMP_DEPRECATED_FOR
argument_list|(
argument|gimp_brush_select_button_set_brush
argument_list|)
end_macro

begin_function_decl
name|void
name|gimp_brush_select_widget_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
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
name|GimpLayerMode
name|paint_mode
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
comment|/* __GIMP_BRUSH_MENU_H__ */
end_comment

end_unit

