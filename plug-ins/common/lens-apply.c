begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Apply lens plug-in --- makes your selected part of the image look like it  *                        is viewed under a solid lens.  * Copyright (C) 1997 Morten Eriksen  * mortene@pvv.ntnu.no  * (If you do anything cool with this plug-in, or have ideas for  * improvements (which aren't on my ToDo-list) - send me an email).  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*   TO DO:   - antialiasing   - adjustable (R, G, B and A) filter   - optimize for speed!   - refraction index warning dialog box when value< 1.0   - use "true" lens with specified thickness   - option to apply inverted lens   - adjustable "c" value in the ellipsoid formula   - radiobuttons for "ellipsoid" or "only horiz" and "only vert" (like in the     Ad*b* Ph*t*sh*p Spherify plug-in..)   - clean up source code  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-applylens"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"lens-apply"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-lens-apply"
end_define

begin_comment
comment|/* Declare local functions.  */
end_comment

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

begin_function_decl
specifier|static
name|void
name|drawlens
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|lens_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c4a09df0108
block|{
DECL|member|refraction
name|gdouble
name|refraction
decl_stmt|;
DECL|member|keep_surr
name|gboolean
name|keep_surr
decl_stmt|;
DECL|member|use_bkgr
name|gboolean
name|use_bkgr
decl_stmt|;
DECL|member|set_transparent
name|gboolean
name|set_transparent
decl_stmt|;
DECL|typedef|LensValues
block|}
name|LensValues
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|lvals
specifier|static
name|LensValues
name|lvals
init|=
block|{
comment|/* Lens refraction value */
literal|1.7
block|,
comment|/* Surroundings options */
name|TRUE
block|,
name|FALSE
block|,
name|FALSE
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
literal|"Input image (unused)"
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
name|GIMP_PDB_FLOAT
block|,
literal|"refraction"
block|,
literal|"Lens refraction index"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"keep-surroundings"
block|,
literal|"Keep lens surroundings { TRUE, FALSE }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"set-background"
block|,
literal|"Set lens surroundings to BG value { TRUE, FALSE }"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"set-transparent"
block|,
literal|"Set lens surroundings transparent { TRUE, FALSE }"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Simulate an elliptical lens over the image"
argument_list|)
argument_list|,
literal|"This plug-in uses Snell's law to draw "
literal|"an ellipsoid lens over the image"
argument_list|,
literal|"Morten Eriksen"
argument_list|,
literal|"Morten Eriksen"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Apply _Lens..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Light and Shadow/Glass"
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
name|INIT_I18N
argument_list|()
expr_stmt|;
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
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|lvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|lens_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|7
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|lvals
operator|.
name|refraction
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|lvals
operator|.
name|keep_surr
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|lvals
operator|.
name|use_bkgr
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|lvals
operator|.
name|set_transparent
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
operator|&&
operator|(
name|lvals
operator|.
name|refraction
operator|<
literal|1.0
operator|)
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|lvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Applying lens"
argument_list|)
argument_list|)
expr_stmt|;
name|drawlens
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
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
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|lvals
argument_list|,
sizeof|sizeof
argument_list|(
name|LensValues
argument_list|)
argument_list|)
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*   Ellipsoid formula: x^2/a^2 + y^2/b^2 + z^2/c^2 = 1  */
end_comment

begin_function
specifier|static
name|void
DECL|function|find_projected_pos (gfloat a2,gfloat b2,gfloat c2,gfloat x,gfloat y,gfloat * projx,gfloat * projy)
name|find_projected_pos
parameter_list|(
name|gfloat
name|a2
parameter_list|,
name|gfloat
name|b2
parameter_list|,
name|gfloat
name|c2
parameter_list|,
name|gfloat
name|x
parameter_list|,
name|gfloat
name|y
parameter_list|,
name|gfloat
modifier|*
name|projx
parameter_list|,
name|gfloat
modifier|*
name|projy
parameter_list|)
block|{
name|gfloat
name|z
decl_stmt|;
name|gfloat
name|nxangle
decl_stmt|,
name|nyangle
decl_stmt|,
name|theta1
decl_stmt|,
name|theta2
decl_stmt|;
name|gfloat
name|ri1
init|=
literal|1.0
decl_stmt|;
name|gfloat
name|ri2
init|=
name|lvals
operator|.
name|refraction
decl_stmt|;
name|z
operator|=
name|sqrt
argument_list|(
operator|(
literal|1
operator|-
name|x
operator|*
name|x
operator|/
name|a2
operator|-
name|y
operator|*
name|y
operator|/
name|b2
operator|)
operator|*
name|c2
argument_list|)
expr_stmt|;
name|nxangle
operator|=
name|acos
argument_list|(
name|x
operator|/
name|sqrt
argument_list|(
name|x
operator|*
name|x
operator|+
name|z
operator|*
name|z
argument_list|)
argument_list|)
expr_stmt|;
name|theta1
operator|=
name|G_PI
operator|/
literal|2
operator|-
name|nxangle
expr_stmt|;
name|theta2
operator|=
name|asin
argument_list|(
name|sin
argument_list|(
name|theta1
argument_list|)
operator|*
name|ri1
operator|/
name|ri2
argument_list|)
expr_stmt|;
name|theta2
operator|=
name|G_PI
operator|/
literal|2
operator|-
name|nxangle
operator|-
name|theta2
expr_stmt|;
operator|*
name|projx
operator|=
name|x
operator|-
name|tan
argument_list|(
name|theta2
argument_list|)
operator|*
name|z
expr_stmt|;
name|nyangle
operator|=
name|acos
argument_list|(
name|y
operator|/
name|sqrt
argument_list|(
name|y
operator|*
name|y
operator|+
name|z
operator|*
name|z
argument_list|)
argument_list|)
expr_stmt|;
name|theta1
operator|=
name|G_PI
operator|/
literal|2
operator|-
name|nyangle
expr_stmt|;
name|theta2
operator|=
name|asin
argument_list|(
name|sin
argument_list|(
name|theta1
argument_list|)
operator|*
name|ri1
operator|/
name|ri2
argument_list|)
expr_stmt|;
name|theta2
operator|=
name|G_PI
operator|/
literal|2
operator|-
name|nyangle
operator|-
name|theta2
expr_stmt|;
operator|*
name|projy
operator|=
name|y
operator|-
name|tan
argument_list|(
name|theta2
argument_list|)
operator|*
name|z
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|drawlens (GimpDrawable * drawable,GimpPreview * preview)
name|drawlens
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpImageType
name|drawtype
init|=
name|gimp_drawable_type
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
decl_stmt|;
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|row
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|col
decl_stmt|;
name|gfloat
name|regionwidth
decl_stmt|,
name|regionheight
decl_stmt|,
name|dx
decl_stmt|,
name|dy
decl_stmt|,
name|xsqr
decl_stmt|,
name|ysqr
decl_stmt|;
name|gfloat
name|a
decl_stmt|,
name|b
decl_stmt|,
name|c
decl_stmt|,
name|asqr
decl_stmt|,
name|bsqr
decl_stmt|,
name|csqr
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|glong
name|pixelpos
decl_stmt|,
name|pos
decl_stmt|;
name|GimpRGB
name|background
decl_stmt|;
name|guchar
name|bgr_red
decl_stmt|,
name|bgr_blue
decl_stmt|,
name|bgr_green
decl_stmt|;
name|guchar
name|alphaval
decl_stmt|;
name|gimp_context_get_background
argument_list|(
operator|&
name|background
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|background
argument_list|,
operator|&
name|bgr_red
argument_list|,
operator|&
name|bgr_green
argument_list|,
operator|&
name|bgr_blue
argument_list|)
expr_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
name|src
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bytes
argument_list|)
expr_stmt|;
name|regionwidth
operator|=
name|width
expr_stmt|;
name|regionheight
operator|=
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|regionwidth
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|regionheight
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|width
operator|=
name|drawable
operator|->
name|width
expr_stmt|;
name|height
operator|=
name|drawable
operator|->
name|height
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|src
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|regionwidth
operator|*
name|regionheight
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|regionwidth
argument_list|,
name|regionheight
argument_list|)
expr_stmt|;
block|}
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|regionwidth
operator|*
name|regionheight
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|a
operator|=
name|regionwidth
operator|/
literal|2
expr_stmt|;
name|b
operator|=
name|regionheight
operator|/
literal|2
expr_stmt|;
name|c
operator|=
name|MIN
argument_list|(
name|a
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|asqr
operator|=
name|a
operator|*
name|a
expr_stmt|;
name|bsqr
operator|=
name|b
operator|*
name|b
expr_stmt|;
name|csqr
operator|=
name|c
operator|*
name|c
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|regionwidth
condition|;
name|col
operator|++
control|)
block|{
name|dx
operator|=
operator|(
name|gfloat
operator|)
name|col
operator|-
name|a
operator|+
literal|0.5
expr_stmt|;
name|xsqr
operator|=
name|dx
operator|*
name|dx
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|regionheight
condition|;
name|row
operator|++
control|)
block|{
name|pixelpos
operator|=
operator|(
name|col
operator|+
name|row
operator|*
name|regionwidth
operator|)
operator|*
name|bytes
expr_stmt|;
name|dy
operator|=
operator|-
operator|(
operator|(
name|gfloat
operator|)
name|row
operator|-
name|b
operator|)
operator|-
literal|0.5
expr_stmt|;
name|ysqr
operator|=
name|dy
operator|*
name|dy
expr_stmt|;
if|if
condition|(
name|ysqr
operator|<
operator|(
name|bsqr
operator|-
operator|(
name|bsqr
operator|*
name|xsqr
operator|)
operator|/
name|asqr
operator|)
condition|)
block|{
name|find_projected_pos
argument_list|(
name|asqr
argument_list|,
name|bsqr
argument_list|,
name|csqr
argument_list|,
name|dx
argument_list|,
name|dy
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|y
operator|=
operator|-
name|y
expr_stmt|;
name|pos
operator|=
operator|(
call|(
name|gint
call|)
argument_list|(
name|y
operator|+
name|b
argument_list|)
operator|*
name|regionwidth
operator|+
call|(
name|gint
call|)
argument_list|(
name|x
operator|+
name|a
argument_list|)
operator|)
operator|*
name|bytes
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
block|{
name|dest
index|[
name|pixelpos
operator|+
name|i
index|]
operator|=
name|src
index|[
name|pos
operator|+
name|i
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|lvals
operator|.
name|keep_surr
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bytes
condition|;
name|i
operator|++
control|)
block|{
name|dest
index|[
name|pixelpos
operator|+
name|i
index|]
operator|=
name|src
index|[
name|pixelpos
operator|+
name|i
index|]
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|lvals
operator|.
name|set_transparent
condition|)
name|alphaval
operator|=
literal|0
expr_stmt|;
else|else
name|alphaval
operator|=
literal|255
expr_stmt|;
switch|switch
condition|(
name|drawtype
condition|)
block|{
case|case
name|GIMP_INDEXEDA_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|1
index|]
operator|=
name|alphaval
expr_stmt|;
case|case
name|GIMP_INDEXED_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|0
index|]
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|3
index|]
operator|=
name|alphaval
expr_stmt|;
case|case
name|GIMP_RGB_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|0
index|]
operator|=
name|bgr_red
expr_stmt|;
name|dest
index|[
name|pixelpos
operator|+
literal|1
index|]
operator|=
name|bgr_green
expr_stmt|;
name|dest
index|[
name|pixelpos
operator|+
literal|2
index|]
operator|=
name|bgr_blue
expr_stmt|;
break|break;
case|case
name|GIMP_GRAYA_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|1
index|]
operator|=
name|alphaval
expr_stmt|;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|dest
index|[
name|pixelpos
operator|+
literal|0
index|]
operator|=
name|bgr_red
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
if|if
condition|(
operator|!
name|preview
condition|)
block|{
if|if
condition|(
operator|(
call|(
name|gint
call|)
argument_list|(
name|regionwidth
operator|-
name|col
argument_list|)
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|col
operator|/
operator|(
name|gdouble
operator|)
name|regionwidth
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dest
argument_list|,
name|bytes
operator|*
name|regionwidth
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|regionwidth
argument_list|,
name|regionheight
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|lens_dialog (GimpDrawable * drawable)
name|lens_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Lens Effect"
argument_list|)
argument_list|,
name|PLUG_IN_ROLE
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|PLUG_IN_PROC
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|main_vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_aspect_preview_new
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|drawlens
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"_Keep original surroundings"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|lvals
operator|.
name|keep_surr
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|lvals
operator|.
name|keep_surr
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|?
name|_
argument_list|(
literal|"_Set surroundings to index 0"
argument_list|)
else|:
name|_
argument_list|(
literal|"_Set surroundings to background color"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|lvals
operator|.
name|use_bkgr
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|lvals
operator|.
name|use_bkgr
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|toggle
operator|=
name|gtk_radio_button_new_with_mnemonic_from_widget
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Make surroundings transparent"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|lvals
operator|.
name|set_transparent
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|lvals
operator|.
name|set_transparent
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
block|}
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Lens refraction index:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|lvals
operator|.
name|refraction
argument_list|,
literal|1.0
argument_list|,
literal|100.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|lvals
operator|.
name|refraction
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

