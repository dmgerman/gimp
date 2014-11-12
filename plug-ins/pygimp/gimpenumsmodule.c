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
literal|"ADD_WHITE_MASK"
argument_list|,
name|GIMP_ADD_MASK_WHITE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_BLACK_MASK"
argument_list|,
name|GIMP_ADD_MASK_BLACK
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_ALPHA_MASK"
argument_list|,
name|GIMP_ADD_MASK_ALPHA
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_ALPHA_TRANSFER_MASK"
argument_list|,
name|GIMP_ADD_MASK_ALPHA_TRANSFER
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_SELECTION_MASK"
argument_list|,
name|GIMP_ADD_MASK_SELECTION
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_COPY_MASK"
argument_list|,
name|GIMP_ADD_MASK_COPY
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"ADD_CHANNEL_MASK"
argument_list|,
name|GIMP_ADD_MASK_CHANNEL
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"FG_BG_RGB_MODE"
argument_list|,
name|GIMP_BLEND_FG_BG_RGB
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"FG_BG_HSV_MODE"
argument_list|,
name|GIMP_BLEND_FG_BG_HSV
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"FG_TRANSPARENT_MODE"
argument_list|,
name|GIMP_BLEND_FG_TRANSPARENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"CUSTOM_MODE"
argument_list|,
name|GIMP_BLEND_CUSTOM
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"FG_BUCKET_FILL"
argument_list|,
name|GIMP_BUCKET_FILL_FG
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"BG_BUCKET_FILL"
argument_list|,
name|GIMP_BUCKET_FILL_BG
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PATTERN_BUCKET_FILL"
argument_list|,
name|GIMP_BUCKET_FILL_PATTERN
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"BLUR_CONVOLVE"
argument_list|,
name|GIMP_CONVOLVE_BLUR
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"SHARPEN_CONVOLVE"
argument_list|,
name|GIMP_CONVOLVE_SHARPEN
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"IMAGE_CLONE"
argument_list|,
name|GIMP_CLONE_IMAGE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PATTERN_CLONE"
argument_list|,
name|GIMP_CLONE_PATTERN
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"FOREGROUND_FILL"
argument_list|,
name|GIMP_FILL_FOREGROUND
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"BACKGROUND_FILL"
argument_list|,
name|GIMP_FILL_BACKGROUND
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"WHITE_FILL"
argument_list|,
name|GIMP_FILL_WHITE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"TRANSPARENT_FILL"
argument_list|,
name|GIMP_FILL_TRANSPARENT
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"PATTERN_FILL"
argument_list|,
name|GIMP_FILL_PATTERN
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"DODGE"
argument_list|,
name|GIMP_DODGE_BURN_TYPE_DODGE
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"BURN"
argument_list|,
name|GIMP_DODGE_BURN_TYPE_BURN
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"SHADOWS"
argument_list|,
name|GIMP_TRANSFER_SHADOWS
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"MIDTONES"
argument_list|,
name|GIMP_TRANSFER_MIDTONES
argument_list|)
expr_stmt|;
name|PyModule_AddIntConstant
argument_list|(
name|m
argument_list|,
literal|"HIGHLIGHTS"
argument_list|,
name|GIMP_TRANSFER_HIGHLIGHTS
argument_list|)
expr_stmt|;
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

