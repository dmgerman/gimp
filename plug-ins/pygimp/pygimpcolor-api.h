begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2005-2006  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PYGIMPCOLOR_API_H_
end_ifndef

begin_define
DECL|macro|_PYGIMPCOLOR_API_H_
define|#
directive|define
name|_PYGIMPCOLOR_API_H_
end_define

begin_include
include|#
directive|include
file|<Python.h>
end_include

begin_include
include|#
directive|include
file|<libgimpcolor/gimpcolor.h>
end_include

begin_struct
DECL|struct|_PyGimpColor_Functions
struct|struct
name|_PyGimpColor_Functions
block|{
DECL|member|RGB_Type
name|PyTypeObject
modifier|*
name|RGB_Type
decl_stmt|;
DECL|member|rgb_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|rgb_new
function_decl|)
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|)
function_decl|;
DECL|member|HSV_Type
name|PyTypeObject
modifier|*
name|HSV_Type
decl_stmt|;
DECL|member|hsv_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|hsv_new
function_decl|)
parameter_list|(
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
DECL|member|HSL_Type
name|PyTypeObject
modifier|*
name|HSL_Type
decl_stmt|;
DECL|member|hsl_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|hsl_new
function_decl|)
parameter_list|(
specifier|const
name|GimpHSL
modifier|*
name|hsl
parameter_list|)
function_decl|;
DECL|member|CMYK_Type
name|PyTypeObject
modifier|*
name|CMYK_Type
decl_stmt|;
DECL|member|cmyk_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|cmyk_new
function_decl|)
parameter_list|(
specifier|const
name|GimpCMYK
modifier|*
name|cmyk
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_ifndef
ifndef|#
directive|ifndef
name|_INSIDE_PYGIMPCOLOR_
end_ifndef

begin_if
if|#
directive|if
name|defined
argument_list|(
name|NO_IMPORT
argument_list|)
operator|||
name|defined
argument_list|(
name|NO_IMPORT_PYGIMPCOLOR
argument_list|)
end_if

begin_decl_stmt
specifier|extern
name|struct
name|_PyGimpColor_Functions
modifier|*
name|_PyGimpColor_API
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|_PyGimpColor_API
name|struct
name|_PyGimpColor_Functions
modifier|*
name|_PyGimpColor_API
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|PyGimpRGB_Type
define|#
directive|define
name|PyGimpRGB_Type
value|(_PyGimpColor_API->RGB_Type)
end_define

begin_define
DECL|macro|PyGimpHSV_Type
define|#
directive|define
name|PyGimpHSV_Type
value|(_PyGimpColor_API->HSV_Type)
end_define

begin_define
DECL|macro|PyGimpHSL_Type
define|#
directive|define
name|PyGimpHSL_Type
value|(_PyGimpColor_API->HSL_Type)
end_define

begin_define
DECL|macro|PyGimpCMYK_Type
define|#
directive|define
name|PyGimpCMYK_Type
value|(_PyGimpColor_API->CMYK_Type)
end_define

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

begin_define
DECL|macro|pygimp_rgb_new
define|#
directive|define
name|pygimp_rgb_new
value|(_PyGimpColor_API->rgb_new)
end_define

begin_define
DECL|macro|pygimp_hsv_new
define|#
directive|define
name|pygimp_hsv_new
value|(_PyGimpColor_API->hsv_new)
end_define

begin_define
DECL|macro|pygimp_hsl_new
define|#
directive|define
name|pygimp_hsl_new
value|(_PyGimpColor_API->hsl_new)
end_define

begin_define
DECL|macro|pygimp_cmyk_new
define|#
directive|define
name|pygimp_cmyk_new
value|(_PyGimpColor_API->cmyk_new)
end_define

begin_define
DECL|macro|init_pygimpcolor ()
define|#
directive|define
name|init_pygimpcolor
parameter_list|()
value|G_STMT_START { \     PyObject *gimpcolormodule = PyImport_ImportModule("gimpcolor"); \     if (gimpcolormodule != NULL) { \ 	PyObject *mdict = PyModule_GetDict(gimpcolormodule); \ 	PyObject *cobject = PyDict_GetItemString(mdict, "_PyGimpColor_API"); \ 	if (PyCObject_Check(cobject)) \ 	    _PyGimpColor_API = PyCObject_AsVoidPtr(cobject); \ 	else { \ 	    PyErr_SetString(PyExc_RuntimeError, \ 		            "could not find _PyGimpColor_API object"); \ 	    return; \ 	} \     } else { \ 	PyErr_SetString(PyExc_ImportError, \ 	                "could not import gimpcolor"); \ 	return; \     } \ } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! _INSIDE_PYGIMPCOLOR_ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _PYGIMPCOLOR_API_H_ */
end_comment

end_unit

