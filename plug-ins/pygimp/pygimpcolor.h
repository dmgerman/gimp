begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-  * Gimp-Python - allows the writing of Gimp plugins in Python.  * Copyright (C) 2003  Manish Singh<yosh@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PYGIMPCOLOR_H_
end_ifndef

begin_define
DECL|macro|_PYGIMPCOLOR_H_
define|#
directive|define
name|_PYGIMPCOLOR_H_
end_define

begin_include
include|#
directive|include
file|<Python.h>
end_include

begin_include
include|#
directive|include
file|<cairo.h>
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<pygobject.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolor.h>
end_include

begin_decl_stmt
name|G_BEGIN_DECLS
specifier|extern
name|PyTypeObject
name|PyGimpRGB_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_rgb_check (v)
define|#
directive|define
name|pygimp_rgb_check
parameter_list|(
name|v
parameter_list|)
value|(pyg_boxed_check((v), GIMP_TYPE_RGB))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_rgb_new
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpHSV_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_hsv_check (v)
define|#
directive|define
name|pygimp_hsv_check
parameter_list|(
name|v
parameter_list|)
value|(pyg_boxed_check((v), GIMP_TYPE_HSV))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_hsv_new
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpHSL_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_hsl_check (v)
define|#
directive|define
name|pygimp_hsl_check
parameter_list|(
name|v
parameter_list|)
value|(pyg_boxed_check((v), GIMP_TYPE_HSL))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_hsl_new
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyTypeObject
name|PyGimpCMYK_Type
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|pygimp_cmyk_check (v)
define|#
directive|define
name|pygimp_cmyk_check
parameter_list|(
name|v
parameter_list|)
value|(pyg_boxed_check((v), GIMP_TYPE_CMYK))
end_define

begin_function_decl
name|PyObject
modifier|*
name|pygimp_cmyk_new
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|pygimp_rgb_from_pyobject
parameter_list|(
name|PyObject
modifier|*
name|object
parameter_list|,
name|GimpRGB
modifier|*
name|color
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

end_unit

