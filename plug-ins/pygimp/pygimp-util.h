begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2006  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_PYGIMP_UTIL_H_
end_ifndef

begin_define
DECL|macro|_PYGIMP_UTIL_H_
define|#
directive|define
name|_PYGIMP_UTIL_H_
end_define

begin_include
include|#
directive|include
file|<Python.h>
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

begin_define
DECL|macro|pygimp_init_pygobject ()
define|#
directive|define
name|pygimp_init_pygobject
parameter_list|()
value|G_STMT_START { \     PyObject *pygtkmodule = PyImport_ImportModule("pygtk"); \     if (pygtkmodule != NULL) { \ 	PyObject *mdict, *require_obj, *require_ver, *require_res; \ 	mdict = PyModule_GetDict(pygtkmodule); \ 	require_obj = PyDict_GetItemString(mdict, "require"); \ 	require_ver = PyString_FromString("2.0"); \ 	require_res = PyObject_CallFunctionObjArgs(require_obj, require_ver, \ 						   NULL); \ 	Py_XDECREF(require_ver); \ 	if (require_res) { \ 	    Py_DECREF(require_res); \ 	    if (PyErr_Occurred()) \ 		return; \ 	} else { \ 	    return; \ 	} \     } else { \ 	PyErr_SetString(PyExc_ImportError, \ 	                "could not import pygtk"); \ 	return; \     } \     init_pygobject(); \ } G_STMT_END
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _PYGIMP_UTIL_H_ */
end_comment

end_unit

