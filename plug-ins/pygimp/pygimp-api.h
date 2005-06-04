begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2005  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PYGIMP_API_H_
end_ifndef

begin_define
DECL|macro|_PYGIMP_API_H_
define|#
directive|define
name|_PYGIMP_API_H_
end_define

begin_include
include|#
directive|include
file|<Python.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_struct
DECL|struct|_PyGimp_Functions
struct|struct
name|_PyGimp_Functions
block|{
DECL|member|image_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|image_new
function_decl|)
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
DECL|member|display_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|display_new
function_decl|)
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
DECL|member|layer_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|layer_new
function_decl|)
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
DECL|member|channel_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|channel_new
function_decl|)
parameter_list|(
name|gint32
name|ID
parameter_list|)
function_decl|;
DECL|member|PDBFunction_Type
name|PyTypeObject
modifier|*
name|PDBFunction_Type
decl_stmt|;
DECL|member|pdb_function_new
name|PyObject
modifier|*
function_decl|(
modifier|*
name|pdb_function_new
function_decl|)
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
specifier|const
name|char
modifier|*
name|blurb
parameter_list|,
specifier|const
name|char
modifier|*
name|help
parameter_list|,
specifier|const
name|char
modifier|*
name|author
parameter_list|,
specifier|const
name|char
modifier|*
name|copyright
parameter_list|,
specifier|const
name|char
modifier|*
name|date
parameter_list|,
name|GimpPDBProcType
name|proc_type
parameter_list|,
name|int
name|n_params
parameter_list|,
name|int
name|n_return_vals
parameter_list|,
name|GimpParamDef
modifier|*
name|params
parameter_list|,
name|GimpParamDef
modifier|*
name|return_vals
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_ifndef
ifndef|#
directive|ifndef
name|_INSIDE_PYGIMP_
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
name|NO_IMPORT_PYGIMP
argument_list|)
end_if

begin_decl_stmt
specifier|extern
name|struct
name|_PyGimp_Functions
modifier|*
name|_PyGimp_API
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|_PyGimp_API
name|struct
name|_PyGimp_Functions
modifier|*
name|_PyGimp_API
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|pygimp_image_new
define|#
directive|define
name|pygimp_image_new
value|(_PyGimp_API->image_new)
end_define

begin_define
DECL|macro|pygimp_display_new
define|#
directive|define
name|pygimp_display_new
value|(_PyGimp_API->display_new)
end_define

begin_define
DECL|macro|pygimp_drawable_new
define|#
directive|define
name|pygimp_drawable_new
value|(_PyGimp_API->drawable_new)
end_define

begin_define
DECL|macro|pygimp_layer_new
define|#
directive|define
name|pygimp_layer_new
value|(_PyGimp_API->layer_new)
end_define

begin_define
DECL|macro|pygimp_channel_new
define|#
directive|define
name|pygimp_channel_new
value|(_PyGimp_API->channel_new)
end_define

begin_define
DECL|macro|PyGimpPDBFunction_Type
define|#
directive|define
name|PyGimpPDBFunction_Type
value|(_PyGimp_API->PDBFunction_Type)
end_define

begin_define
DECL|macro|pygimp_pdb_function_new
define|#
directive|define
name|pygimp_pdb_function_new
value|(_PyGimp_API->pdb_function_new)
end_define

begin_define
DECL|macro|init_pygimp ()
define|#
directive|define
name|init_pygimp
parameter_list|()
value|G_STMT_START { \     PyObject *gimpmodule = PyImport_ImportModule("gimp"); \     if (gimpmodule != NULL) { \ 	PyObject *mdict = PyModule_GetDict(gimpmodule); \ 	PyObject *cobject = PyDict_GetItemString(mdict, "_PyGimp_API"); \ 	if (PyCObject_Check(cobject)) \ 	    _PyGimp_API = PyCObject_AsVoidPtr(cobject); \ 	else { \ 	    PyErr_SetString(PyExc_RuntimeError, \ 		            "could not find _PyGimp_API object"); \ 	    return; \ 	} \     } else { \ 	PyErr_SetString(PyExc_ImportError, \ 	                "could not import gimp"); \ 	return; \     } \ } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! _INSIDE_PYGIMP_ */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _PYGIMP_API_H_ */
end_comment

end_unit

