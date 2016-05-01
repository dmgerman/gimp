begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-  * Gimp-Python - allows the writing of Gimp plugins in Python.  * Copyright (C) 2005  Manish Singh<yosh@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|<config.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<Python.h>
end_include

begin_include
include|#
directive|include
file|<pygobject.h>
end_include

begin_include
include|#
directive|include
file|<pygtk/pygtk.h>
end_include

begin_include
include|#
directive|include
file|<pycairo.h>
end_include

begin_decl_stmt
DECL|variable|Pycairo_CAPI
name|Pycairo_CAPI_t
modifier|*
name|Pycairo_CAPI
decl_stmt|;
end_decl_stmt

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"pygimpcolor-api.h"
end_include

begin_include
include|#
directive|include
file|"pygimp-api.h"
end_include

begin_include
include|#
directive|include
file|"pygimp-util.h"
end_include

begin_function_decl
name|void
name|gimpui_register_classes
parameter_list|(
name|PyObject
modifier|*
name|d
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimpui_add_constants
parameter_list|(
name|PyObject
modifier|*
name|module
parameter_list|,
specifier|const
name|gchar
modifier|*
name|strip_prefix
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|PyMethodDef
name|gimpui_functions
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimpui_doc
specifier|static
name|char
name|gimpui_doc
index|[]
init|=
literal|"This module provides interfaces to allow you to write gimp plugins"
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|init_gimpui
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|gboolean
DECL|function|init_pycairo (void)
name|init_pycairo
parameter_list|(
name|void
parameter_list|)
block|{
name|Pycairo_IMPORT
expr_stmt|;
if|if
condition|(
name|Pycairo_CAPI
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|PyMODINIT_FUNC
DECL|function|init_gimpui (void)
name|init_gimpui
parameter_list|(
name|void
parameter_list|)
block|{
name|PyObject
modifier|*
name|m
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|PyObject
modifier|*
name|av
decl_stmt|;
name|char
modifier|*
name|prog_name
init|=
literal|"pygimp"
decl_stmt|;
name|av
operator|=
name|PySys_GetObject
argument_list|(
literal|"argv"
argument_list|)
expr_stmt|;
if|if
condition|(
name|av
operator|!=
name|NULL
condition|)
block|{
if|if
condition|(
name|PyList_Check
argument_list|(
name|av
argument_list|)
operator|&&
name|PyList_Size
argument_list|(
name|av
argument_list|)
operator|>
literal|0
operator|&&
name|PyString_Check
argument_list|(
name|PyList_GetItem
argument_list|(
name|av
argument_list|,
literal|0
argument_list|)
argument_list|)
condition|)
name|prog_name
operator|=
name|PyString_AsString
argument_list|(
name|PyList_GetItem
argument_list|(
name|av
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|PyErr_Warn
argument_list|(
name|PyExc_Warning
argument_list|,
literal|"ignoring sys.argv: it must be a list of strings"
argument_list|)
expr_stmt|;
block|}
name|gimp_ui_init
argument_list|(
name|prog_name
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pygimp_init_pygobject
argument_list|()
expr_stmt|;
name|init_pygtk
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|init_pycairo
argument_list|()
condition|)
return|return;
name|init_pygimpcolor
argument_list|()
expr_stmt|;
name|init_pygimp
argument_list|()
expr_stmt|;
name|m
operator|=
name|Py_InitModule3
argument_list|(
literal|"_gimpui"
argument_list|,
name|gimpui_functions
argument_list|,
name|gimpui_doc
argument_list|)
expr_stmt|;
name|d
operator|=
name|PyModule_GetDict
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|gimpui_register_classes
argument_list|(
name|d
argument_list|)
expr_stmt|;
name|gimpui_add_constants
argument_list|(
name|m
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
if|if
condition|(
name|PyErr_Occurred
argument_list|()
condition|)
name|Py_FatalError
argument_list|(
literal|"can't initialize module _gimpui"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

