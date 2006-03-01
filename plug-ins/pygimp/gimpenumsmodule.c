begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-     Gimp-Python - allows the writing of Gimp plugins in Python.     Copyright (C) 2005  Manish Singh<yosh@gimp.org>      This program is free software; you can redistribute it and/or modify     it under the terms of the GNU General Public License as published by     the Free Software Foundation; either version 2 of the License, or     (at your option) any later version.      This program is distributed in the hope that it will be useful,     but WITHOUT ANY WARRANTY; without even the implied warranty of     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     GNU General Public License for more details.      You should have received a copy of the GNU General Public License     along with this program; if not, write to the Free Software     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA     02111-1307, USA.  */
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
file|"pygimp-api.h"
end_include

begin_include
include|#
directive|include
file|"pygimp-util.h"
end_include

begin_function
specifier|static
name|void
DECL|function|add_misc_enums (PyObject * m)
name|add_misc_enums
parameter_list|(
name|PyObject
modifier|*
name|m
parameter_list|)
block|{
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_PERSISTENT"
argument_list|,
name|GIMP_PARASITE_PERSISTENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_UNDOABLE"
argument_list|,
name|GIMP_PARASITE_UNDOABLE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_ATTACH_PARENT"
argument_list|,
name|GIMP_PARASITE_ATTACH_PARENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_PARENT_PERSISTENT"
argument_list|,
name|GIMP_PARASITE_PARENT_PERSISTENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_PARENT_UNDOABLE"
argument_list|,
name|GIMP_PARASITE_PARENT_UNDOABLE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_ATTACH_GRANDPARENT"
argument_list|,
name|GIMP_PARASITE_ATTACH_GRANDPARENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_GRANDPARENT_PERSISTENT"
argument_list|,
name|GIMP_PARASITE_GRANDPARENT_PERSISTENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PARASITE_GRANDPARENT_UNDOABLE"
argument_list|,
name|GIMP_PARASITE_GRANDPARENT_UNDOABLE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"UNIT_PIXEL"
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"UNIT_INCH"
argument_list|,
name|GIMP_UNIT_INCH
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"UNIT_MM"
argument_list|,
name|GIMP_UNIT_MM
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"UNIT_POINT"
argument_list|,
name|GIMP_UNIT_POINT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"UNIT_PICA"
argument_list|,
name|GIMP_UNIT_PICA
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"MIN_IMAGE_SIZE"
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"MAX_IMAGE_SIZE"
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"MIN_RESOLUTION"
argument_list|,
name|PyFloat_FromDouble
argument_list|(
name|GIMP_MIN_RESOLUTION
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"MAX_RESOLUTION"
argument_list|,
name|PyFloat_FromDouble
argument_list|(
name|GIMP_MAX_RESOLUTION
argument_list|)
argument_list|)
expr_stmt|;
name|PyModule_AddObject
argument_list|(
name|m
argument_list|,
literal|"MAX_MEMSIZE"
argument_list|,
name|PyLong_FromUnsignedLongLong
argument_list|(
name|GIMP_MAX_MEMSIZE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_registered_enums (PyObject * m)
name|add_registered_enums
parameter_list|(
name|PyObject
modifier|*
name|m
parameter_list|)
block|{
name|int
name|num_names
decl_stmt|,
name|i
decl_stmt|;
specifier|const
name|char
modifier|*
modifier|*
name|names
decl_stmt|;
name|names
operator|=
name|gimp_enums_get_type_names
argument_list|(
operator|&
name|num_names
argument_list|)
expr_stmt|;
name|pyg_enum_add_constants
argument_list|(
name|m
argument_list|,
name|GIMP_TYPE_CHECK_SIZE
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
name|pyg_enum_add_constants
argument_list|(
name|m
argument_list|,
name|GIMP_TYPE_CHECK_TYPE
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_names
condition|;
name|i
operator|++
control|)
name|pyg_enum_add_constants
argument_list|(
name|m
argument_list|,
name|g_type_from_name
argument_list|(
name|names
index|[
name|i
index|]
argument_list|)
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Initialization function for the module (*must* be called initgimpenums) */
end_comment

begin_decl_stmt
DECL|variable|gimpenums_doc
specifier|static
name|char
name|gimpenums_doc
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
DECL|function|init_gimpenums (void)
name|init_gimpenums
argument_list|(
argument|void
argument_list|)
end_macro

begin_block
block|{
name|PyObject
modifier|*
name|m
decl_stmt|;
name|pygimp_init_pygobject
argument_list|()
expr_stmt|;
name|init_pygimp
argument_list|()
expr_stmt|;
name|gimp_enums_init
argument_list|()
expr_stmt|;
comment|/* Create the module and add the functions */
name|m
operator|=
name|Py_InitModule3
argument_list|(
literal|"_gimpenums"
argument_list|,
name|NULL
argument_list|,
name|gimpenums_doc
argument_list|)
expr_stmt|;
name|add_misc_enums
argument_list|(
name|m
argument_list|)
expr_stmt|;
name|add_registered_enums
argument_list|(
name|m
argument_list|)
expr_stmt|;
comment|/* Check for errors */
if|if
condition|(
name|PyErr_Occurred
argument_list|()
condition|)
name|Py_FatalError
argument_list|(
literal|"can't initialize module _gimpenums"
argument_list|)
expr_stmt|;
block|}
end_block

end_unit

