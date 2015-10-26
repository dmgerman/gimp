begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* MapObject 1.2.0 -- image filter plug-in for GIMP  *  * Copyright (C) 1996-98 Tom Bech  * Copyright (C) 1996-98 Federico Mena Quintero  *  * E-mail: tomb@gimp.org (Tom) or quartic@gimp.org (Federico)  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

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
file|"map-object-ui.h"
end_include

begin_include
include|#
directive|include
file|"map-object-image.h"
end_include

begin_include
include|#
directive|include
file|"map-object-apply.h"
end_include

begin_include
include|#
directive|include
file|"map-object-preview.h"
end_include

begin_include
include|#
directive|include
file|"map-object-main.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Global variables */
end_comment

begin_comment
comment|/* ================ */
end_comment

begin_decl_stmt
DECL|variable|mapvals
name|MapObjectValues
name|mapvals
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/* Implementation */
end_comment

begin_comment
comment|/******************/
end_comment

begin_comment
comment|/*************************************/
end_comment

begin_comment
comment|/* Set parameters to standard values */
end_comment

begin_comment
comment|/*************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|set_default_settings (void)
name|set_default_settings
parameter_list|(
name|void
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|viewpoint
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|2.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|firstaxis
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|secondaxis
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|normal
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|position
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
operator|.
name|position
argument_list|,
operator|-
literal|0.5
argument_list|,
operator|-
literal|0.5
argument_list|,
literal|2.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
argument_list|,
operator|-
literal|1.0
argument_list|,
operator|-
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|scale
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|mapvals
operator|.
name|maptype
operator|=
name|MAP_PLANE
expr_stmt|;
name|mapvals
operator|.
name|pixeltreshold
operator|=
literal|0.25
expr_stmt|;
name|mapvals
operator|.
name|alpha
operator|=
literal|0.0
expr_stmt|;
name|mapvals
operator|.
name|beta
operator|=
literal|0.0
expr_stmt|;
name|mapvals
operator|.
name|gamma
operator|=
literal|0.0
expr_stmt|;
name|mapvals
operator|.
name|maxdepth
operator|=
literal|3.0
expr_stmt|;
name|mapvals
operator|.
name|radius
operator|=
literal|0.25
expr_stmt|;
name|mapvals
operator|.
name|cylinder_radius
operator|=
literal|0.25
expr_stmt|;
name|mapvals
operator|.
name|cylinder_length
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|zoom
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|type
operator|=
name|POINT_LIGHT
expr_stmt|;
name|mapvals
operator|.
name|antialiasing
operator|=
name|TRUE
expr_stmt|;
name|mapvals
operator|.
name|create_new_image
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|create_new_layer
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|transparent_background
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|tiled
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|livepreview
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|showgrid
operator|=
name|TRUE
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|intensity
operator|=
literal|1.0
expr_stmt|;
name|gimp_rgba_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
operator|.
name|color
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|ambient_int
operator|=
literal|0.3
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_int
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_ref
operator|=
literal|0.5
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|specular_ref
operator|=
literal|0.5
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|highlight
operator|=
literal|27.0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
operator|=
operator|-
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|check_drawables (GimpDrawable * drawable)
name|check_drawables
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
comment|/* Check that boxmap images are valid */
comment|/* ================================== */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
operator|==
operator|-
literal|1
operator|||
operator|!
name|gimp_item_is_valid
argument_list|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
argument_list|)
condition|)
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
operator|=
name|drawable
operator|->
name|drawable_id
expr_stmt|;
block|}
comment|/* Check that cylindermap images are valid */
comment|/* ======================================= */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
operator|==
operator|-
literal|1
operator|||
operator|!
name|gimp_item_is_valid
argument_list|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
argument_list|)
condition|)
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
operator|=
name|drawable
operator|->
name|drawable_id
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|query (void)
name|query
parameter_list|(
name|void
parameter_list|)
block|{
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
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
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
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"maptype"
block|,
literal|"Type of mapping (0=plane,1=sphere,2=box,3=cylinder)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"viewpoint-x"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"viewpoint-y"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"viewpoint-z"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"position-x"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"position-y"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"position-z"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"firstaxis-x"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"firstaxis-y"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"firstaxis-z"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"secondaxis-x"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"secondaxis-y"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"secondaxis-z"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"rotationangle-x"
block|,
literal|"Rotation about X axis in degrees"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"rotationangle-y"
block|,
literal|"Rotation about Y axis in degrees"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"rotationangle-z"
block|,
literal|"Rotation about Z axis in degrees"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"lighttype"
block|,
literal|"Type of lightsource (0=point,1=directional,2=none)"
block|}
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"lightcolor"
block|,
literal|"Lightsource color (r,g,b)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightposition-x"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightposition-y"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightposition-z"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection-x"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection-y"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection-z"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"ambient_intensity"
block|,
literal|"Material ambient intensity (0..1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"diffuse_intensity"
block|,
literal|"Material diffuse intensity (0..1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"diffuse_reflectivity"
block|,
literal|"Material diffuse reflectivity (0..1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"specular_reflectivity"
block|,
literal|"Material specular reflectivity (0..1)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"highlight"
block|,
literal|"Material highlight (0..->), note: it's expotential"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"antialiasing"
block|,
literal|"Apply antialiasing (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"tiled"
block|,
literal|"Tile source image (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"newimage"
block|,
literal|"Create a new image (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"transparentbackground"
block|,
literal|"Make background transparent (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"radius"
block|,
literal|"Sphere/cylinder radius (only used when maptype=1 or 3)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"x-scale"
block|,
literal|"Box x size (0..->)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"y-scale"
block|,
literal|"Box y size (0..->)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"z-scale"
block|,
literal|"Box z size (0..->)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"cylinder-length"
block|,
literal|"Cylinder length (0..->)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-front-drawable"
block|,
literal|"Box front face (set these to -1 if not used)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-back-drawable"
block|,
literal|"Box back face"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-top-drawable"
block|,
literal|"Box top face"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-bottom-drawable"
block|,
literal|"Box bottom face"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-left-drawable"
block|,
literal|"Box left face"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"box-right-drawable"
block|,
literal|"Box right face"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"cyl-top-drawable"
block|,
literal|"Cylinder top face (set these to -1 if not used)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"cyl-bottom-drawable"
block|,
literal|"Cylinder bottom face"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Map the image to an object (plane, sphere, box or cylinder)"
argument_list|)
argument_list|,
literal|"No help yet"
argument_list|,
literal|"Tom Bech& Federico Mena Quintero"
argument_list|,
literal|"Tom Bech& Federico Mena Quintero"
argument_list|,
literal|"Version 1.2.0, July 16 1998"
argument_list|,
name|N_
argument_list|(
literal|"Map _Object..."
argument_list|)
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
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint
name|i
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
comment|/* Set default values */
comment|/* ================== */
name|set_default_settings
argument_list|()
expr_stmt|;
comment|/* Get the specified drawable */
comment|/* ========================== */
name|image_id
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/* Possibly retrieve data */
comment|/* ====================== */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|mapvals
argument_list|)
expr_stmt|;
name|check_drawables
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|main_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|compute_image
argument_list|()
expr_stmt|;
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|mapvals
argument_list|,
sizeof|sizeof
argument_list|(
name|MapObjectValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|mapvals
argument_list|)
expr_stmt|;
name|check_drawables
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_setup
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
condition|)
name|compute_image
argument_list|()
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|49
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|mapvals
operator|.
name|maptype
operator|=
operator|(
name|MapType
operator|)
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|viewpoint
operator|.
name|x
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|viewpoint
operator|.
name|y
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|viewpoint
operator|.
name|z
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|position
operator|.
name|x
operator|=
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|position
operator|.
name|y
operator|=
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|position
operator|.
name|z
operator|=
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|firstaxis
operator|.
name|x
operator|=
name|param
index|[
literal|10
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|firstaxis
operator|.
name|y
operator|=
name|param
index|[
literal|11
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|firstaxis
operator|.
name|z
operator|=
name|param
index|[
literal|12
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|secondaxis
operator|.
name|x
operator|=
name|param
index|[
literal|13
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|secondaxis
operator|.
name|y
operator|=
name|param
index|[
literal|14
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|secondaxis
operator|.
name|z
operator|=
name|param
index|[
literal|15
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|alpha
operator|=
name|param
index|[
literal|16
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|beta
operator|=
name|param
index|[
literal|17
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|gamma
operator|=
name|param
index|[
literal|18
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|type
operator|=
operator|(
name|LightType
operator|)
name|param
index|[
literal|19
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|color
operator|=
name|param
index|[
literal|20
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|position
operator|.
name|x
operator|=
name|param
index|[
literal|21
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|position
operator|.
name|y
operator|=
name|param
index|[
literal|22
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|position
operator|.
name|z
operator|=
name|param
index|[
literal|23
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|x
operator|=
name|param
index|[
literal|24
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|y
operator|=
name|param
index|[
literal|25
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|direction
operator|.
name|z
operator|=
name|param
index|[
literal|26
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|ambient_int
operator|=
name|param
index|[
literal|27
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_int
operator|=
name|param
index|[
literal|28
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_ref
operator|=
name|param
index|[
literal|29
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|specular_ref
operator|=
name|param
index|[
literal|30
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|highlight
operator|=
name|param
index|[
literal|31
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|antialiasing
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|32
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|tiled
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|33
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|create_new_image
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|34
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|transparent_background
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|35
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|radius
operator|=
name|param
index|[
literal|36
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|cylinder_radius
operator|=
name|param
index|[
literal|36
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|scale
operator|.
name|x
operator|=
name|param
index|[
literal|37
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|scale
operator|.
name|y
operator|=
name|param
index|[
literal|38
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|scale
operator|.
name|z
operator|=
name|param
index|[
literal|39
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|mapvals
operator|.
name|cylinder_length
operator|=
name|param
index|[
literal|40
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|6
condition|;
name|i
operator|++
control|)
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
operator|=
name|param
index|[
literal|41
operator|+
name|i
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
operator|=
name|param
index|[
literal|47
operator|+
name|i
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|check_drawables
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_setup
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
condition|)
name|compute_image
argument_list|()
expr_stmt|;
block|}
break|break;
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
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

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
name|MAIN
argument_list|()
end_macro

end_unit

