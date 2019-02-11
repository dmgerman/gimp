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
name|gimp_plug_in_procedure_set_handles_uri
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
literal|"file-gbr-load"
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
name|gimp_param_spec_int32
argument_list|(
literal|"dummy-param"
argument_list|,
literal|"Dummy Param"
argument_list|,
literal|"Dummy parameter"
argument_list|,
name|G_MININT32
argument_list|,
name|G_MAXINT32
argument_list|,
literal|0
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
name|gimp_param_spec_image_id
argument_list|(
literal|"image"
argument_list|,
literal|"Image"
argument_list|,
literal|"Output image"
argument_list|,
name|gimp
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

