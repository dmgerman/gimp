begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* lcms.h uses the "inline" keyword */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LCMS_LCMS_H
end_ifdef

begin_include
include|#
directive|include
file|<lcms/lcms.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<lcms.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC_SET
define|#
directive|define
name|PLUG_IN_PROC_SET
value|"plug-in-icc-set"
end_define

begin_define
DECL|macro|PLUG_IN_PROC_SET_RGB
define|#
directive|define
name|PLUG_IN_PROC_SET_RGB
value|"plug-in-icc-set-rgb"
end_define

begin_define
DECL|macro|PLUG_IN_PROC_APPLY
define|#
directive|define
name|PLUG_IN_PROC_APPLY
value|"plug-in-icc-apply"
end_define

begin_define
DECL|macro|PLUG_IN_PROC_APPLY_RGB
define|#
directive|define
name|PLUG_IN_PROC_APPLY_RGB
value|"plug-in-icc-apply-rgb"
end_define

begin_define
DECL|macro|PLUG_IN_PROC_INFO
define|#
directive|define
name|PLUG_IN_PROC_INFO
value|"plug-in-icc-info"
end_define

begin_function_decl
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
specifier|const
name|GimpPlugInInfo
name|PLUG_IN_INFO
init|=
block|{
name|NULL
block|,
comment|/* init_proc  */
name|NULL
block|,
comment|/* quit_proc  */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
specifier|static
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|base_args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,   }
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"profile"
block|,
literal|"Filename of an ICC color profile"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|info_return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"product-name"
block|,
literal|"Name"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"product-desc"
block|,
literal|"Description"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"product-info"
block|,
literal|"Info"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"manufacturer"
block|,
literal|"Manufacturer"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"model"
block|,
literal|"Model"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"copyright"
block|,
literal|"Copyright"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC_SET
argument_list|,
literal|"Set ICC color profile on the image"
argument_list|,
literal|"This procedure sets an ICC color profile on an "
literal|"image using the 'icc-profile' parasite. It does "
literal|"not do any color conversion."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC_SET_RGB
argument_list|,
literal|"Set the default RGB color profile on the image"
argument_list|,
literal|"This procedure sets the user-configured RGB "
literal|"profile on an image using the 'icc-profile' "
literal|"parasite. If no RGB profile is, sRGB is assumed "
literal|"and the parasite is unset. This procedure does "
literal|"not do any color conversion."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|base_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|base_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC_APPLY
argument_list|,
literal|"Apply a color profile on the image"
argument_list|,
literal|"This procedure transform from the image's color "
literal|"profile (or the default RGB profile if none is "
literal|"set) to the given ICC color profile. The profile "
literal|"is then set on the image using the 'icc-profile' "
literal|"parasite."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC_APPLY_RGB
argument_list|,
literal|"Apply default RGB color profile on the image"
argument_list|,
literal|"This procedure transform from the image's color "
literal|"profile (or the default RGB profile if none is "
literal|"set) to the configured default RGB color profile. "
literal|"is then set on the image using the 'icc-profile' "
literal|"parasite. If no RGB color profile is configured, "
literal|"sRGB is assumed and the parasite is unset."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|base_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|base_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC_INFO
argument_list|,
literal|"Retrieve information about an image's color profile"
argument_list|,
literal|"This procedure returns information about the "
literal|"color profile attached to an image. If no profile "
literal|"is attached, sRGB is assumed."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2006"
argument_list|,
name|NULL
argument_list|,
literal|"RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|base_args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|info_return_vals
argument_list|)
argument_list|,
name|base_args
argument_list|,
name|info_return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|run_mode
operator|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
if|if
condition|(
name|nparams
operator|!=
literal|3
condition|)
block|{
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC_SET
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC_SET_RGB
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC_APPLY
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC_APPLY_RGB
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC_INFO
argument_list|)
operator|==
literal|0
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|=
name|status
expr_stmt|;
block|}
end_function

end_unit

