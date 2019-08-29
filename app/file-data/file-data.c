begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpparamspecs.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/gimppluginprocedure.h"
end_include

begin_include
include|#
directive|include
file|"file-data.h"
end_include

begin_include
include|#
directive|include
file|"file-data-gbr.h"
end_include

begin_include
include|#
directive|include
file|"file-data-gex.h"
end_include

begin_include
include|#
directive|include
file|"file-data-gih.h"
end_include

begin_include
include|#
directive|include
file|"file-data-pat.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
name|void
DECL|function|file_data_init (Gimp * gimp)
name|file_data_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpPlugInProcedure
modifier|*
name|proc
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GimpProcedure
modifier|*
name|procedure
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  file-gbr-load  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-gbr-load"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_gbr_load_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP brush"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-brush"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-brush"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"gbr, gbp"
argument_list|,
literal|""
argument_list|,
literal|"20, string, GIMP"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|proc
argument_list|,
literal|"image/gimp-x-gbr"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_handles_remote
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-gbr-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Loads GIMP brushes"
argument_list|,
literal|"Loads GIMP brushes (1 or 4 bpp "
literal|"and old .gpb format)"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, "
literal|"Sven Neumann, Michael Natterer"
argument_list|,
literal|"Tim Newsome, Jens Lautenbacher, "
literal|"Sven Neumann, Michael Natterer"
argument_list|,
literal|"1995-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Output image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-gbr-save-internal  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-gbr-save-internal"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_gbr_save_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP brush"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-brush"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-brush"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* do not register as file procedure */
block|gimp_plug_in_procedure_set_image_types (proc, "RGB*, GRAY*, INDEXED*");   gimp_plug_in_procedure_set_file_proc (proc, "gbr", "", NULL);   gimp_plug_in_procedure_set_mime_types (proc, "image/x-gimp-gbr");   gimp_plug_in_procedure_set_handles_remote (proc);
endif|#
directive|endif
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-gbr-save-internal"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Exports Gimp brush file (.GBR)"
argument_list|,
literal|"Exports Gimp brush file (.GBR)"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"1995-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"Active drawable "
literal|"of input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"Spacing of the brush"
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The name of the "
literal|"brush"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP Brush"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-gih-load  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-gih-load"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_gih_load_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP brush (animated)"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-brush"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-brush"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"gih"
argument_list|,
literal|""
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|proc
argument_list|,
literal|"image/gimp-x-gih"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_handles_remote
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-gih-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Loads GIMP animated brushes"
argument_list|,
literal|"This procedure loads a GIMP brush "
literal|"pipe as an image."
argument_list|,
literal|"Tor Lillqvist, Michael Natterer"
argument_list|,
literal|"Tor Lillqvist, Michael Natterer"
argument_list|,
literal|"1999-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Output image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-gih-save-internal  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-gih-save-internal"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_gih_save_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP brush (animated)"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-brush"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-brush"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* do not register as file procedure */
block|gimp_plug_in_procedure_set_image_types (proc, "RGB*, GRAY*, INDEXED*");   gimp_plug_in_procedure_set_file_proc (proc, "gih", "", NULL);   gimp_plug_in_procedure_set_mime_types (proc, "image/x-gimp-gih");   gimp_plug_in_procedure_set_handles_remote (proc);
endif|#
directive|endif
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-gih-save-internal"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Exports Gimp animated brush file (.gih)"
argument_list|,
literal|"Exports Gimp animated brush file (.gih)"
argument_list|,
literal|"Tor Lillqvist, Michael Natterer"
argument_list|,
literal|"Tor Lillqvist, Michael Natterer"
argument_list|,
literal|"1999-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"Active drawable "
literal|"of input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"spacing"
argument_list|,
literal|"spacing"
argument_list|,
literal|"Spacing of the brush"
argument_list|,
literal|1
argument_list|,
literal|1000
argument_list|,
literal|10
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The name of the "
literal|"brush"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP Brush"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"params"
argument_list|,
literal|"params"
argument_list|,
literal|"The pipe's parameters"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-pat-load  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-pat-load"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_pat_load_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP pattern"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-pattern"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-pattern"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_image_types
argument_list|(
name|proc
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"pat"
argument_list|,
literal|""
argument_list|,
literal|"20,string,GPAT"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|proc
argument_list|,
literal|"image/gimp-x-pat"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_handles_remote
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-pat-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Loads GIMP patterns"
argument_list|,
literal|"Loads GIMP patterns"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"1997-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Output image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-pat-save-internal  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-pat-save-internal"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_pat_save_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP pattern"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-pattern"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-pattern"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
comment|/* do not register as file procedure */
block|gimp_plug_in_procedure_set_image_types (proc, "RGB*, GRAY*, INDEXED*");   gimp_plug_in_procedure_set_file_proc (proc, "pat", "", NULL);   gimp_plug_in_procedure_set_mime_types (proc, "image/x-gimp-pat");   gimp_plug_in_procedure_set_handles_remote (proc);
endif|#
directive|endif
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-pat-save-internal"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Exports Gimp pattern file (.PAT)"
argument_list|,
literal|"Exports Gimp pattern file (.PAT)"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"Tim Newsome, Michael Natterer"
argument_list|,
literal|"1995-2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_image
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_drawable
argument_list|(
literal|"drawable"
argument_list|,
literal|"Drawable"
argument_list|,
literal|"Active drawable "
literal|"of input image"
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to export"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"name"
argument_list|,
literal|"name"
argument_list|,
literal|"The name of the "
literal|"pattern"
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|"GIMP Pattern"
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
comment|/*  file-gex-load  */
name|file
operator|=
name|g_file_new_for_path
argument_list|(
literal|"file-gex-load"
argument_list|)
expr_stmt|;
name|procedure
operator|=
name|gimp_plug_in_procedure_new
argument_list|(
name|GIMP_PLUGIN
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|procedure
operator|->
name|proc_type
operator|=
name|GIMP_INTERNAL
expr_stmt|;
name|procedure
operator|->
name|marshal_func
operator|=
name|file_gex_load_invoker
expr_stmt|;
name|proc
operator|=
name|GIMP_PLUG_IN_PROCEDURE
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
name|proc
operator|->
name|menu_label
operator|=
name|g_strdup
argument_list|(
name|N_
argument_list|(
literal|"GIMP extension"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_icon
argument_list|(
name|proc
argument_list|,
name|GIMP_ICON_TYPE_ICON_NAME
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
literal|"gimp-plugin"
argument_list|,
name|strlen
argument_list|(
literal|"gimp-plugin"
argument_list|)
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_file_proc
argument_list|(
name|proc
argument_list|,
literal|"gex"
argument_list|,
literal|""
argument_list|,
literal|"20, string, GIMP"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_generic_file_proc
argument_list|(
name|proc
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_mime_types
argument_list|(
name|proc
argument_list|,
literal|"image/gimp-x-gex"
argument_list|)
expr_stmt|;
name|gimp_plug_in_procedure_set_handles_remote
argument_list|(
name|proc
argument_list|)
expr_stmt|;
name|gimp_object_set_static_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|procedure
argument_list|)
argument_list|,
literal|"file-gex-load"
argument_list|)
expr_stmt|;
name|gimp_procedure_set_static_strings
argument_list|(
name|procedure
argument_list|,
literal|"Loads GIMP extension"
argument_list|,
literal|"Loads GIMP extension"
argument_list|,
literal|"Jehan"
argument_list|,
literal|"Jehan"
argument_list|,
literal|"2019"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_enum
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|GIMP_TYPE_RUN_MODE
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"uri"
argument_list|,
literal|"URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_argument
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"raw-uri"
argument_list|,
literal|"Raw URI"
argument_list|,
literal|"The URI of the file "
literal|"to load"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_procedure_add_return_value
argument_list|(
name|procedure
argument_list|,
name|gimp_param_spec_string
argument_list|(
literal|"extension-id"
argument_list|,
literal|"ID of installed extension"
argument_list|,
literal|"Identifier of the newly installed extension"
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_plug_in_manager_add_procedure
argument_list|(
name|gimp
operator|->
name|plug_in_manager
argument_list|,
name|proc
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|procedure
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_data_exit (Gimp * gimp)
name|file_data_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

