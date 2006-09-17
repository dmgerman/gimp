begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2005-2006  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<libgimpthumb/gimpthumb.h>
end_include

begin_include
include|#
directive|include
file|"pygimp-util.h"
end_include

begin_function_decl
name|void
name|gimpthumb_register_classes
parameter_list|(
name|PyObject
modifier|*
name|d
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimpthumb_add_constants
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
name|gimpthumb_functions
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|gimpthumb_doc
specifier|static
name|char
name|gimpthumb_doc
index|[]
init|=
literal|"This module provides interfaces to allow you to write gimp plugins"
decl_stmt|;
end_decl_stmt

begin_macro
name|DL_EXPORT
argument_list|(
argument|void
argument_list|)
end_macro

begin_macro
DECL|function|initgimpthumb (void)
name|initgimpthumb
argument_list|(
argument|void
argument_list|)
end_macro

begin_block
block|{
name|PyObject
modifier|*
name|m
decl_stmt|,
modifier|*
name|d
decl_stmt|;
name|pygimp_init_pygobject
argument_list|()
expr_stmt|;
name|m
operator|=
name|Py_InitModule3
argument_list|(
literal|"gimpthumb"
argument_list|,
name|gimpthumb_functions
argument_list|,
name|gimpthumb_doc
argument_list|)
expr_stmt|;
name|d
operator|=
name|PyModule_GetDict
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|gimpthumb_register_classes
argument_list|(
name|d
argument_list|)
expr_stmt|;
name|gimpthumb_add_constants
argument_list|(
name|m
argument_list|,
literal|"GIMP_THUMB_"
argument_list|)
expr_stmt|;
if|if
condition|(
name|PyErr_Occurred
argument_list|()
condition|)
name|Py_FatalError
argument_list|(
literal|"can't initialize module gimpthumb"
argument_list|)
expr_stmt|;
block|}
end_block

end_unit

