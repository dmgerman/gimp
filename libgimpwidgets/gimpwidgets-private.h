begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpwidgets-private.h  * Copyright (C) 2003 Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_WIDGETS_PRIVATE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_WIDGETS_PRIVATE_H__
define|#
directive|define
name|__GIMP_WIDGETS_PRIVATE_H__
end_define

begin_typedef
DECL|typedef|GimpGetColorFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpGetColorFunc
function_decl|)
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpEnsureModulesFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpEnsureModulesFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|GimpHelpFunc
name|_gimp_standard_help_func
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpGetColorFunc
name|_gimp_get_foreground_func
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpGetColorFunc
name|_gimp_get_background_func
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|GimpEnsureModulesFunc
name|_gimp_ensure_modules_func
decl_stmt|;
end_decl_stmt

begin_function_decl
name|G_BEGIN_DECLS
name|void
name|gimp_widgets_init
parameter_list|(
name|GimpHelpFunc
name|standard_help_func
parameter_list|,
name|GimpGetColorFunc
name|get_foreground_func
parameter_list|,
name|GimpGetColorFunc
name|get_background_func
parameter_list|,
name|GimpEnsureModulesFunc
name|ensure_modules_func
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
comment|/* __GIMP_WIDGETS_PRIVATE_H__ */
end_comment

end_unit

