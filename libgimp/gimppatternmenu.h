begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppatternmenu.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATTERN_MENU_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATTERN_MENU_H__
define|#
directive|define
name|__GIMP_PATTERN_MENU_H__
end_define

begin_comment
comment|/*  These functions are deprecated and should not be used in newly  *  written code.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_function_decl
name|G_BEGIN_DECLS
name|GtkWidget
modifier|*
name|gimp_pattern_select_widget_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
parameter_list|,
name|GimpRunPatternCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pattern_select_widget_close
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pattern_select_widget_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|pattern_name
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
comment|/*  GIMP_DISABLE_DEPRECATED  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PATTERN_MENU_H__ */
end_comment

end_unit

