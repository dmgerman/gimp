begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* -*- Mode: C; c-basic-offset: 4 -*-  * Gimp-Python - allows the writing of Gimp plugins in Python.  * Copyright (C) 2005  Manish Singh<yosh@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|"libgimp/gimpui.h"
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
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PIXEL_FETCHER_EDGE_NONE"
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_NONE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PIXEL_FETCHER_EDGE_WRAP"
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_WRAP
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PIXEL_FETCHER_EDGE_SMEAR"
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_SMEAR
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PIXEL_FETCHER_EDGE_BLACK"
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_BLACK
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PIXEL_FETCHER_EDGE_BACKGROUND"
argument_list|,
name|GIMP_PIXEL_FETCHER_EDGE_BACKGROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_compat_enums (PyObject * m)
name|add_compat_enums
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
literal|"EXPORT_CAN_HANDLE_RGB"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_GRAY"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_GRAY
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_INDEXED"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_INDEXED
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_BITMAP"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_BITMAP
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_ALPHA"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_LAYERS"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_LAYERS
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_LAYERS_AS_ANIMATION
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CAN_HANDLE_LAYER_MASKS"
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_LAYER_MASKS
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_NEEDS_ALPHA"
argument_list|,
name|GIMP_EXPORT_NEEDS_ALPHA
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_CANCEL"
argument_list|,
name|GIMP_EXPORT_CANCEL
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_IGNORE"
argument_list|,
name|GIMP_EXPORT_IGNORE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"EXPORT_EXPORT"
argument_list|,
name|GIMP_EXPORT_EXPORT
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
name|gint
name|num_names
decl_stmt|,
name|i
decl_stmt|;
specifier|const
name|gchar
modifier|*
modifier|*
name|names
decl_stmt|;
name|GQuark
name|quark
init|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-compat-enum"
argument_list|)
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
block|{
name|GType
name|enum_type
init|=
name|g_type_from_name
argument_list|(
name|names
index|[
name|i
index|]
argument_list|)
decl_stmt|;
name|pyg_enum_add_constants
argument_list|(
name|m
argument_list|,
name|enum_type
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
name|enum_type
operator|=
operator|(
name|GType
operator|)
name|g_type_get_qdata
argument_list|(
name|enum_type
argument_list|,
name|quark
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_type
condition|)
name|pyg_enum_add_constants
argument_list|(
name|m
argument_list|,
name|enum_type
argument_list|,
literal|"GIMP_"
argument_list|)
expr_stmt|;
block|}
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
literal|"This module provides interfaces to allow you to write gimp plug-ins"
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|init_gimpenums
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|PyMODINIT_FUNC
DECL|function|init_gimpenums (void)
name|init_gimpenums
parameter_list|(
name|void
parameter_list|)
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
name|add_compat_enums
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
end_function

end_unit

