begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*********************************************************************************/
end_comment

begin_comment
comment|/* MapObject 1.2.0 -- image filter plug-in for The Gimp program                  */
end_comment

begin_comment
comment|/* Copyright (C) 1996-98 Tom Bech                                                */
end_comment

begin_comment
comment|/* Copyright (C) 1996-98 Federico Mena Quintero                                  */
end_comment

begin_comment
comment|/*===============================================================================*/
end_comment

begin_comment
comment|/* E-mail: tomb@gimp.org (Tom) or quartic@gimp.org (Federico)                    */
end_comment

begin_comment
comment|/* You can contact the original The Gimp authors at gimp@xcf.berkeley.edu        */
end_comment

begin_comment
comment|/*===============================================================================*/
end_comment

begin_comment
comment|/* This program is free software; you can redistribute it and/or modify it under */
end_comment

begin_comment
comment|/* the terms of the GNU General Public License as published by the Free Software */
end_comment

begin_comment
comment|/* Foundation; either version 2 of the License, or (at your option) any later    */
end_comment

begin_comment
comment|/* version.                                                                      */
end_comment

begin_comment
comment|/*===============================================================================*/
end_comment

begin_comment
comment|/* This program is distributed in the hope that it will be useful, but WITHOUT   */
end_comment

begin_comment
comment|/* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS */
end_comment

begin_comment
comment|/* FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.*/
end_comment

begin_comment
comment|/*===============================================================================*/
end_comment

begin_comment
comment|/* You should have received a copy of the GNU General Public License along with  */
end_comment

begin_comment
comment|/* this program (read the "COPYING" file); if not, write to the Free Software    */
end_comment

begin_comment
comment|/* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.    */
end_comment

begin_comment
comment|/*===============================================================================*/
end_comment

begin_comment
comment|/* In other words, you can't sue us for whatever happens while using this ;)     */
end_comment

begin_comment
comment|/*********************************************************************************/
end_comment

begin_include
include|#
directive|include
file|"mapobject_main.h"
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
name|preview_zoom_factor
operator|=
literal|0
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
name|showgrid
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|tooltips_enabled
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
name|gck_rgb_set
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
DECL|function|check_drawables (GDrawable * drawable)
name|check_drawables
parameter_list|(
name|GDrawable
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
name|id
expr_stmt|;
elseif|else
if|if
condition|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
operator|!=
operator|-
literal|1
operator|&&
name|gimp_drawable_image_id
argument_list|(
name|mapvals
operator|.
name|boxmap_id
index|[
name|i
index|]
argument_list|)
operator|==
operator|-
literal|1
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
name|id
expr_stmt|;
elseif|else
if|if
condition|(
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
name|id
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
name|id
expr_stmt|;
elseif|else
if|if
condition|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
operator|!=
operator|-
literal|1
operator|&&
name|gimp_drawable_image_id
argument_list|(
name|mapvals
operator|.
name|cylindermap_id
index|[
name|i
index|]
argument_list|)
operator|==
operator|-
literal|1
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
name|id
expr_stmt|;
elseif|else
if|if
condition|(
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
name|id
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
name|GParamDef
name|args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive (0), non-interactive (1)"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"maptype"
block|,
literal|"Type of mapping (0=plane,1=sphere,2=box,3=cylinder)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"viewpoint_x"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"viewpoint_y"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"viewpoint_z"
block|,
literal|"Position of viewpoint (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"position_x"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"position_y"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"position_z"
block|,
literal|"Object position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"firstaxis_x"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"firstaxis_y"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"firstaxis_z"
block|,
literal|"First axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"secondaxis_x"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"secondaxis_y"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"secondaxis_z"
block|,
literal|"Second axis of object [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"rotationangle_x"
block|,
literal|"Rotation about X axis in degrees"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"rotationangle_y"
block|,
literal|"Rotation about Y axis in degrees"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"rotationangle_z"
block|,
literal|"Rotation about Z axis in degrees"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"lighttype"
block|,
literal|"Type of lightsource (0=point,1=directional,3=none)"
block|}
block|,
block|{
name|PARAM_COLOR
block|,
literal|"lightcolor"
block|,
literal|"Lightsource color (r,g,b)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightposition_x"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightposition_y"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightposition_z"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightdirection_x"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightdirection_y"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"lightdirection_z"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"ambient_intensity"
block|,
literal|"Material ambient intensity (0..1)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"diffuse_intensity"
block|,
literal|"Material diffuse intensity (0..1)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"diffuse_reflectivity"
block|,
literal|"Material diffuse reflectivity (0..1)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"specular_reflectivity"
block|,
literal|"Material specular reflectivity (0..1)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"highlight"
block|,
literal|"Material highlight (0..->), note: it's expotential"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"antialiasing"
block|,
literal|"Apply antialiasing (TRUE/FALSE)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"tiled"
block|,
literal|"Tile source image (TRUE/FALSE)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"newimage"
block|,
literal|"Create a new image (TRUE/FALSE)"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"transparentbackground"
block|,
literal|"Make background transparent (TRUE/FALSE)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"radius"
block|,
literal|"Sphere/cylinder radius (only used when maptype=1 or 3)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"x_scale"
block|,
literal|"Box x size (0..->)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"y_scale"
block|,
literal|"Box y size (0..->)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"z_scale"
block|,
literal|"Box z size (0..->)"
block|}
block|,
block|{
name|PARAM_FLOAT
block|,
literal|"cylinder_length"
block|,
literal|"Cylinder length (0..->)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_front_drawable"
block|,
literal|"Box front face (set these to -1 if not used)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_back_drawable"
block|,
literal|"Box back face"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_top_drawable"
block|,
literal|"Box top face"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_bottom_drawable"
block|,
literal|"Box bottom face"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_left_drawable"
block|,
literal|"Box left face"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"box_right_drawable"
block|,
literal|"Box right face"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"cyl_top_drawable"
block|,
literal|"Cylinder top face (set these to -1 if not used)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"cyl_bottom_drawable"
block|,
literal|"Cylinder bottom face"
block|}
block|}
decl_stmt|;
specifier|static
name|gint
name|nargs
init|=
sizeof|sizeof
argument_list|(
name|args
argument_list|)
operator|/
sizeof|sizeof
argument_list|(
name|args
index|[
literal|0
index|]
argument_list|)
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_map_object"
argument_list|,
literal|"Maps a picture to a object (plane, sphere, box or cylinder)"
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
literal|"<Image>/Filters/Map/Map Object..."
argument_list|)
argument_list|,
literal|"RGB*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
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
DECL|function|run (gchar * name,gint nparams,GParam * param,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
specifier|static
name|GParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
if|if
condition|(
name|run_mode
operator|==
name|RUN_INTERACTIVE
condition|)
block|{
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|INIT_I18N
argument_list|()
expr_stmt|;
block|}
name|values
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|PARAM_STATUS
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
name|RUN_INTERACTIVE
case|:
comment|/* Possibly retrieve data */
comment|/* ====================== */
name|gimp_get_data
argument_list|(
literal|"plug_in_map_object"
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
literal|"plug_in_map_object"
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
name|RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_map_object"
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
name|image_setup
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|compute_image
argument_list|()
expr_stmt|;
break|break;
case|case
name|RUN_NONINTERACTIVE
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
name|STATUS_CALLING_ERROR
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
operator|.
name|r
operator|=
name|param
index|[
literal|20
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|red
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|color
operator|.
name|g
operator|=
name|param
index|[
literal|20
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|green
expr_stmt|;
name|mapvals
operator|.
name|lightsource
operator|.
name|color
operator|.
name|b
operator|=
name|param
index|[
literal|20
index|]
operator|.
name|data
operator|.
name|d_color
operator|.
name|blue
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
name|gimp_drawable_get
argument_list|(
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
argument_list|)
operator|->
name|id
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
name|gimp_drawable_get
argument_list|(
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
argument_list|)
operator|->
name|id
expr_stmt|;
name|check_drawables
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|image_setup
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|RUN_NONINTERACTIVE
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
name|GPlugInInfo
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

