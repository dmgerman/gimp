begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Lighting Effects 0.2.2 -- image filter plug-in for The Gimp program  *  * Copyright (C) 1996-98 Tom Bech  * Copyright (C) 1996-98 Federico Mena Quintero  *  * E-mail: tomb@gimp.org (Tom) or quartic@gimp.org (Federico)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"lighting_apply.h"
end_include

begin_include
include|#
directive|include
file|"lighting_image.h"
end_include

begin_include
include|#
directive|include
file|"lighting_main.h"
end_include

begin_include
include|#
directive|include
file|"lighting_preview.h"
end_include

begin_include
include|#
directive|include
file|"lighting_shade.h"
end_include

begin_include
include|#
directive|include
file|"lighting_ui.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|mapvals
name|LightingValues
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
name|k
decl_stmt|;
name|mapvals
operator|.
name|update_enabled
operator|=
name|TRUE
expr_stmt|;
name|mapvals
operator|.
name|light_selected
operator|=
literal|0
expr_stmt|;
name|mapvals
operator|.
name|light_isolated
operator|=
name|FALSE
expr_stmt|;
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
literal|0.25
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|planenormal
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|position
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
name|lightsource
index|[
literal|0
index|]
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
name|gimp_rgba_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|intensity
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|POINT_LIGHT
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
operator|.
name|active
operator|=
name|TRUE
expr_stmt|;
comment|/* init lights 2 and 3 pos to upper left and below */
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
index|[
literal|1
index|]
operator|.
name|position
argument_list|,
literal|2.0
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
name|lightsource
index|[
literal|1
index|]
operator|.
name|direction
argument_list|,
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
name|lightsource
index|[
literal|2
index|]
operator|.
name|position
argument_list|,
literal|1.0
argument_list|,
literal|2.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
index|[
literal|2
index|]
operator|.
name|direction
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
comment|/* init any remaining lights to directly overhead */
for|for
control|(
name|k
operator|=
literal|3
init|;
name|k
operator|<
name|NUM_LIGHTS
condition|;
name|k
operator|++
control|)
block|{
name|gimp_vector3_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|position
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
name|lightsource
index|[
name|k
index|]
operator|.
name|direction
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|k
operator|=
literal|1
init|;
name|k
operator|<
name|NUM_LIGHTS
condition|;
name|k
operator|++
control|)
block|{
name|gimp_rgba_set
argument_list|(
operator|&
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
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
name|lightsource
index|[
name|k
index|]
operator|.
name|intensity
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|type
operator|=
name|NO_LIGHT
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
name|k
index|]
operator|.
name|active
operator|=
name|TRUE
expr_stmt|;
block|}
name|mapvals
operator|.
name|material
operator|.
name|ambient_int
operator|=
literal|0.2
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_int
operator|=
literal|0.5
expr_stmt|;
name|mapvals
operator|.
name|material
operator|.
name|diffuse_ref
operator|=
literal|0.4
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
name|mapvals
operator|.
name|material
operator|.
name|metallic
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|pixel_treshold
operator|=
literal|0.25
expr_stmt|;
name|mapvals
operator|.
name|max_depth
operator|=
literal|3.0
expr_stmt|;
name|mapvals
operator|.
name|preview_zoom_factor
operator|=
literal|1.0
expr_stmt|;
name|mapvals
operator|.
name|bumpmaptype
operator|=
literal|0
expr_stmt|;
name|mapvals
operator|.
name|bumpmin
operator|=
literal|0.0
expr_stmt|;
name|mapvals
operator|.
name|bumpmax
operator|=
literal|0.1
expr_stmt|;
name|mapvals
operator|.
name|antialiasing
operator|=
name|FALSE
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
name|bump_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|env_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|ref_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|previewquality
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|interactive_preview
operator|=
name|TRUE
expr_stmt|;
name|mapvals
operator|.
name|bumpmap_id
operator|=
operator|-
literal|1
expr_stmt|;
name|mapvals
operator|.
name|envmap_id
operator|=
operator|-
literal|1
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|check_drawables (void)
name|check_drawables
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|mapvals
operator|.
name|bumpmap_id
operator|!=
operator|-
literal|1
operator|&&
name|gimp_drawable_get_image
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|mapvals
operator|.
name|bump_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|bumpmap_id
operator|=
operator|-
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|mapvals
operator|.
name|envmap_id
operator|!=
operator|-
literal|1
operator|&&
name|gimp_drawable_get_image
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|mapvals
operator|.
name|env_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|envmap_id
operator|=
operator|-
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|mapvals
operator|.
name|bump_mapped
condition|)
block|{
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
operator|||
operator|(
name|gimp_drawable_width
argument_list|(
name|mapvals
operator|.
name|drawable_id
argument_list|)
operator|!=
name|gimp_drawable_width
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
operator|)
operator|||
operator|(
name|gimp_drawable_height
argument_list|(
name|mapvals
operator|.
name|drawable_id
argument_list|)
operator|!=
name|gimp_drawable_height
argument_list|(
name|mapvals
operator|.
name|bumpmap_id
argument_list|)
operator|)
condition|)
block|{
name|mapvals
operator|.
name|bump_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|bumpmap_id
operator|=
operator|-
literal|1
expr_stmt|;
block|}
block|}
if|if
condition|(
name|mapvals
operator|.
name|env_mapped
condition|)
block|{
if|if
condition|(
name|gimp_drawable_is_gray
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
operator|||
name|gimp_drawable_has_alpha
argument_list|(
name|mapvals
operator|.
name|envmap_id
argument_list|)
condition|)
block|{
name|mapvals
operator|.
name|bump_mapped
operator|=
name|FALSE
expr_stmt|;
name|mapvals
operator|.
name|bumpmap_id
operator|=
operator|-
literal|1
expr_stmt|;
block|}
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
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run_mode"
block|,
literal|"Interactive (0), non-interactive (1)"
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
name|GIMP_PDB_DRAWABLE
block|,
literal|"bumpdrawable"
block|,
literal|"Bumpmap drawable (set to 0 if disabled)"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"envdrawable"
block|,
literal|"Environmentmap drawable (set to 0 if disabled)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"dobumpmap"
block|,
literal|"Enable bumpmapping (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"doenvmap"
block|,
literal|"Enable envmapping (TRUE/FALSE)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"bumpmaptype"
block|,
literal|"Type of mapping (0=linear,1=log, 2=sinusoidal, 3=spherical)"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"lighttype"
block|,
literal|"Type of lightsource (0=point,1=directional,3=spot,4=none)"
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
literal|"lightposition_x"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightposition_y"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightposition_z"
block|,
literal|"Lightsource position (x,y,z)"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection_x"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection_y"
block|,
literal|"Lightsource direction [x,y,z]"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"lightdirection_z"
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
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_lighting"
argument_list|,
literal|"Apply various lighting effects to an image"
argument_list|,
literal|"No help yet"
argument_list|,
literal|"Tom Bech& Federico Mena Quintero"
argument_list|,
literal|"Tom Bech& Federico Mena Quintero"
argument_list|,
literal|"Version 0.2.0, March 15 1998"
argument_list|,
name|N_
argument_list|(
literal|"_Lighting Effects..."
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
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_lighting"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Light Effects"
argument_list|)
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
comment|/* Set default values */
comment|/* ================== */
name|set_default_settings
argument_list|()
expr_stmt|;
comment|/* Possibly retrieve data */
comment|/* ====================== */
name|gimp_get_data
argument_list|(
literal|"plug_in_lighting"
argument_list|,
operator|&
name|mapvals
argument_list|)
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
name|mapvals
operator|.
name|drawable_id
operator|=
name|drawable
operator|->
name|drawable_id
expr_stmt|;
name|check_drawables
argument_list|()
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/* Make sure that the drawable is RGBA or RGB color */
comment|/* ================================================ */
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
comment|/* Set the tile cache size */
comment|/* ======================= */
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
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
literal|"plug_in_lighting"
argument_list|,
operator|&
name|mapvals
argument_list|,
sizeof|sizeof
argument_list|(
name|LightingValues
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
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
name|gimp_displays_flush
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
literal|24
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
name|bumpmap_id
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|mapvals
operator|.
name|envmap_id
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_drawable
expr_stmt|;
name|mapvals
operator|.
name|bump_mapped
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|env_mapped
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|bumpmaptype
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|7
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
operator|.
name|type
operator|=
operator|(
name|LightType
operator|)
name|param
index|[
literal|8
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
operator|.
name|color
operator|=
name|param
index|[
literal|9
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
name|mapvals
operator|.
name|lightsource
index|[
literal|0
index|]
operator|.
name|position
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|position
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|position
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|direction
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|direction
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
name|lightsource
index|[
literal|0
index|]
operator|.
name|direction
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
name|material
operator|.
name|ambient_int
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
name|material
operator|.
name|diffuse_int
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
name|material
operator|.
name|diffuse_ref
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
name|material
operator|.
name|specular_ref
operator|=
name|param
index|[
literal|19
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
literal|20
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
literal|21
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
literal|22
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
literal|23
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|check_drawables
argument_list|()
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
default|default:
break|break;
block|}
block|}
else|else
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|xpostab
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|ypostab
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
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

