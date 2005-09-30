begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  *  Rotate plug-in v1.0  *  Copyright 1997-2000 by Sven Neumann<sven@gimp.org>  *& Adam D. Moss<adam@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* Revision history  *  (09/28/97)  v0.1   first development release  *  (09/29/97)  v0.2   nicer dialog,  *                     changed the menu-location to Filters/Transforms  *  (10/01/97)  v0.3   now handles layered images and undo  *  (10/13/97)  v0.3a  small bugfix, no real changes  *  (10/17/97)  v0.4   now handles selections  *  (01/09/98)  v0.5   a few fixes to support portability  *  (01/15/98)  v0.6   fixed a line that caused rotate to crash on some  *                     systems  *  (05/28/98)  v0.7   use the new gimp_message function for error output  *  (10/09/99)  v0.8   rotate guides too  *  (11/13/99)  v0.9   merge rotators and rotate plug-ins  *                     -> drop the dialog, register directly into menus instead  *  (06/18/00)  v1.0   speed up 180° rotations,  *                     declare version 1.0 for gimp-1.2 release  */
end_comment

begin_comment
comment|/* TODO List  *  - handle channels and masks  *  - rewrite the main function to make it work on tiles rather than  *    process the image row by row. This should result in a significant  *    speedup (thanks to quartic for this suggestion).  *  - do something magical so that only one rotate can be occuring at a time!  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

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

begin_comment
comment|/* Defines */
end_comment

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-rotate"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"v1.0 (2000/06/18)"
end_define

begin_define
DECL|macro|PLUG_IN_IMAGE_TYPES
define|#
directive|define
name|PLUG_IN_IMAGE_TYPES
value|"RGB*, INDEXED*, GRAY*"
end_define

begin_define
DECL|macro|PLUG_IN_AUTHOR
define|#
directive|define
name|PLUG_IN_AUTHOR
value|"Sven Neumann<sven@gimp.org>, Adam D. Moss<adam@gimp.org>"
end_define

begin_define
DECL|macro|PLUG_IN_COPYRIGHT
define|#
directive|define
name|PLUG_IN_COPYRIGHT
value|"Sven Neumann, Adam D. Moss"
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c63c44f0108
block|{
DECL|member|angle
name|gint
name|angle
decl_stmt|;
DECL|member|everything
name|gint
name|everything
decl_stmt|;
DECL|typedef|RotateValues
block|}
name|RotateValues
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c63c44f0208
block|{
DECL|member|ID
name|gint32
name|ID
decl_stmt|;
DECL|member|orientation
name|gint32
name|orientation
decl_stmt|;
DECL|member|position
name|gint32
name|position
decl_stmt|;
DECL|typedef|GuideInfo
block|}
name|GuideInfo
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|rotvals
specifier|static
name|RotateValues
name|rotvals
init|=
block|{
literal|1
block|,
comment|/* default to 90 degrees */
literal|1
comment|/* default to whole image */
block|}
decl_stmt|;
end_decl_stmt

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
name|rotate
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|rotate_compute_offsets
parameter_list|(
name|gint
modifier|*
name|offsetx
parameter_list|,
name|gint
modifier|*
name|offsety
parameter_list|,
name|gint
name|image_width
parameter_list|,
name|gint
name|image_height
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Global Variables */
end_comment

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
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* the image and drawable that will be used later */
end_comment

begin_decl_stmt
DECL|variable|active_drawable
specifier|static
name|GimpDrawable
modifier|*
name|active_drawable
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_ID
specifier|static
name|gint32
name|image_ID
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Functions */
end_comment

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
literal|"angle"
block|,
literal|"Angle { 90 (1), 180 (2), 270 (3) } degrees"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"everything"
block|,
literal|"Rotate the whole image? { TRUE, FALSE }"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"Rotates a layer or the whole image by 90, 180 or 270 degrees"
argument_list|,
literal|"This plug-in does rotate the active layer or the "
literal|"whole image clockwise by multiples of 90 degrees. "
literal|"When the whole image is choosen, the image is "
literal|"resized if necessary."
argument_list|,
name|PLUG_IN_AUTHOR
argument_list|,
name|PLUG_IN_COPYRIGHT
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|NULL
argument_list|,
name|PLUG_IN_IMAGE_TYPES
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
name|GimpRunMode
name|run_mode
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|image_ID
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
name|active_drawable
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
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PLUG_IN_PROC
argument_list|)
operator|==
literal|0
condition|)
block|{
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/* check to see if invoked with the correct number of parameters */
if|if
condition|(
name|nparams
operator|==
literal|5
condition|)
block|{
name|rotvals
operator|.
name|angle
operator|=
operator|(
name|gint
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
name|rotvals
operator|.
name|angle
operator|=
name|rotvals
operator|.
name|angle
operator|%
literal|4
expr_stmt|;
name|rotvals
operator|.
name|everything
operator|=
operator|(
name|gint
operator|)
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
comment|/* Store variable states for next run */
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|rotvals
argument_list|,
sizeof|sizeof
argument_list|(
name|RotateValues
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/* Possibly retrieve data from a previous run */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|rotvals
argument_list|)
expr_stmt|;
name|rotvals
operator|.
name|angle
operator|=
name|rotvals
operator|.
name|angle
operator|%
literal|4
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/* Run the main function */
name|rotate
argument_list|()
expr_stmt|;
comment|/* If run mode is interactive, flush displays, else (script) don't 	 do it, as the screen updates would make the scripts slow */
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
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

begin_function
specifier|static
name|void
DECL|function|rotate_compute_offsets (gint * offsetx,gint * offsety,gint image_width,gint image_height,gint width,gint height)
name|rotate_compute_offsets
parameter_list|(
name|gint
modifier|*
name|offsetx
parameter_list|,
name|gint
modifier|*
name|offsety
parameter_list|,
name|gint
name|image_width
parameter_list|,
name|gint
name|image_height
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|gint
name|buffer
decl_stmt|;
if|if
condition|(
name|rotvals
operator|.
name|everything
condition|)
comment|/* rotate around the image center */
block|{
switch|switch
condition|(
name|rotvals
operator|.
name|angle
condition|)
block|{
case|case
literal|1
case|:
comment|/* 90° */
name|buffer
operator|=
operator|*
name|offsetx
expr_stmt|;
operator|*
name|offsetx
operator|=
name|image_height
operator|-
operator|*
name|offsety
operator|-
name|height
expr_stmt|;
operator|*
name|offsety
operator|=
name|buffer
expr_stmt|;
break|break;
case|case
literal|2
case|:
comment|/* 180° */
operator|*
name|offsetx
operator|=
name|image_width
operator|-
operator|*
name|offsetx
operator|-
name|width
expr_stmt|;
operator|*
name|offsety
operator|=
name|image_height
operator|-
operator|*
name|offsety
operator|-
name|height
expr_stmt|;
break|break;
case|case
literal|3
case|:
comment|/* 270° */
name|buffer
operator|=
operator|*
name|offsetx
expr_stmt|;
operator|*
name|offsetx
operator|=
operator|*
name|offsety
expr_stmt|;
operator|*
name|offsety
operator|=
name|image_width
operator|-
name|buffer
operator|-
name|width
expr_stmt|;
block|}
block|}
else|else
comment|/* rotate around the drawable center */
block|{
if|if
condition|(
name|rotvals
operator|.
name|angle
operator|!=
literal|2
condition|)
block|{
operator|*
name|offsetx
operator|=
operator|*
name|offsetx
operator|+
operator|(
name|width
operator|-
name|height
operator|)
operator|/
literal|2
expr_stmt|;
operator|*
name|offsety
operator|=
operator|*
name|offsety
operator|+
operator|(
name|height
operator|-
name|width
operator|)
operator|/
literal|2
expr_stmt|;
block|}
block|}
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|rotate_drawable (GimpDrawable * drawable)
name|rotate_drawable
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
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
name|longside
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|offsetx
decl_stmt|,
name|offsety
decl_stmt|;
name|gboolean
name|was_lock_alpha
init|=
name|FALSE
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
decl_stmt|;
comment|/* initialize */
name|row
operator|=
literal|0
expr_stmt|;
comment|/* Get the size of the input drawable. */
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
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|was_lock_alpha
operator|=
name|TRUE
expr_stmt|;
name|gimp_layer_set_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|rotvals
operator|.
name|angle
operator|==
literal|2
condition|)
comment|/* we're rotating by 180° */
block|{
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
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
name|src_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|src_row
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
control|)
block|{
name|memcpy
argument_list|(
name|dest_row
operator|+
name|col
operator|*
name|bytes
argument_list|,
name|src_row
operator|+
operator|(
name|width
operator|-
literal|1
operator|-
name|col
operator|)
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_row
argument_list|,
literal|0
argument_list|,
operator|(
name|height
operator|-
name|row
operator|-
literal|1
operator|)
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest_row
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
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* we're rotating by 90° or 270° */
block|{
operator|(
name|width
operator|>
name|height
operator|)
condition|?
operator|(
name|longside
operator|=
name|width
operator|)
else|:
operator|(
name|longside
operator|=
name|height
operator|)
expr_stmt|;
name|gimp_layer_resize
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|longside
argument_list|,
name|longside
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
name|longside
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
operator|+
operator|(
name|longside
operator|/
name|gimp_tile_height
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
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
name|longside
argument_list|,
name|longside
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
name|longside
argument_list|,
name|longside
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_malloc
argument_list|(
name|longside
operator|*
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|rotvals
operator|.
name|angle
operator|==
literal|1
condition|)
comment|/* we're rotating by 90° */
block|{
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|height
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_col
argument_list|(
operator|&
name|destPR
argument_list|,
name|buffer
argument_list|,
operator|(
name|height
operator|-
name|row
operator|-
literal|1
operator|)
argument_list|,
literal|0
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|row
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
block|}
block|}
else|else
comment|/* we're rotating by 270° */
block|{
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|width
condition|;
name|col
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_col
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
name|col
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|buffer
argument_list|,
literal|0
argument_list|,
operator|(
name|width
operator|-
name|col
operator|-
literal|1
operator|)
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|col
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|col
operator|/
operator|(
name|double
operator|)
name|width
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
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
literal|0
argument_list|,
literal|0
argument_list|,
name|height
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|gimp_layer_resize
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|height
argument_list|,
name|width
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|height
argument_list|,
name|width
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|offsetx
argument_list|,
operator|&
name|offsety
argument_list|)
expr_stmt|;
name|rotate_compute_offsets
argument_list|(
operator|&
name|offsetx
argument_list|,
operator|&
name|offsety
argument_list|,
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
argument_list|,
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_layer_set_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|offsetx
argument_list|,
name|offsety
argument_list|)
expr_stmt|;
if|if
condition|(
name|was_lock_alpha
condition|)
name|gimp_layer_set_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_comment
comment|/* The main rotate function */
end_comment

begin_function
specifier|static
name|void
DECL|function|rotate (void)
name|rotate
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint32
modifier|*
name|layers
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|nlayers
decl_stmt|;
name|gint32
name|guide_ID
decl_stmt|;
name|GuideInfo
modifier|*
name|guide
decl_stmt|;
name|GList
modifier|*
name|guides
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|rotvals
operator|.
name|angle
operator|==
literal|0
condition|)
return|return;
comment|/* if there's a selection and we try to rotate the whole image */
comment|/* create an error message and exit                            */
if|if
condition|(
name|rotvals
operator|.
name|everything
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_selection_is_empty
argument_list|(
name|image_ID
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"You can not rotate the whole image if there's a selection."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gimp_drawable_is_layer
argument_list|(
name|active_drawable
operator|->
name|drawable_id
argument_list|)
operator|&&
name|gimp_layer_is_floating_sel
argument_list|(
name|active_drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"You can not rotate the whole image if there's a floating selection."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
else|else
comment|/* if we are trying to rotate a channel or a mask,        create an error message and exit */
block|{
if|if
condition|(
operator|!
name|gimp_drawable_is_layer
argument_list|(
name|active_drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"Sorry, channels and masks can not be rotated."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Rotating"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|rotvals
operator|.
name|everything
condition|)
comment|/* rotate the whole image */
block|{
name|gint32
name|width
init|=
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gint32
name|height
init|=
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gimp_drawable_detach
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image_ID
argument_list|,
operator|&
name|nlayers
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
name|nlayers
condition|;
name|i
operator|++
control|)
block|{
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|layers
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|rotate_drawable
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|layers
argument_list|)
expr_stmt|;
comment|/* build a list of all guides and remove them */
name|guide_ID
operator|=
literal|0
expr_stmt|;
while|while
condition|(
operator|(
name|guide_ID
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
name|guide_ID
argument_list|)
operator|)
operator|!=
literal|0
condition|)
block|{
name|guide
operator|=
name|g_new
argument_list|(
name|GuideInfo
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|guide
operator|->
name|ID
operator|=
name|guide_ID
expr_stmt|;
name|guide
operator|->
name|orientation
operator|=
name|gimp_image_get_guide_orientation
argument_list|(
name|image_ID
argument_list|,
name|guide_ID
argument_list|)
expr_stmt|;
name|guide
operator|->
name|position
operator|=
name|gimp_image_get_guide_position
argument_list|(
name|image_ID
argument_list|,
name|guide_ID
argument_list|)
expr_stmt|;
name|guides
operator|=
name|g_list_prepend
argument_list|(
name|guides
argument_list|,
name|guide
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|list
operator|=
name|guides
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|guide
operator|=
operator|(
name|GuideInfo
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|gimp_image_delete_guide
argument_list|(
name|image_ID
argument_list|,
name|guide
operator|->
name|ID
argument_list|)
expr_stmt|;
block|}
comment|/* if rotation is not 180 degrees, resize the image */
comment|/*    Do it now after the guides are removed, since */
comment|/*    gimp_image_resize() moves the guides.         */
if|if
condition|(
name|rotvals
operator|.
name|angle
operator|!=
literal|2
condition|)
name|gimp_image_resize
argument_list|(
name|image_ID
argument_list|,
name|height
argument_list|,
name|width
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* add the guides back to the image */
if|if
condition|(
name|guides
condition|)
block|{
switch|switch
condition|(
name|rotvals
operator|.
name|angle
condition|)
block|{
case|case
literal|1
case|:
for|for
control|(
name|list
operator|=
name|guides
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|guide
operator|=
operator|(
name|GuideInfo
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_image_add_vguide
argument_list|(
name|image_ID
argument_list|,
name|height
operator|-
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
else|else
name|gimp_image_add_hguide
argument_list|(
name|image_ID
argument_list|,
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guide
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|2
case|:
for|for
control|(
name|list
operator|=
name|guides
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|guide
operator|=
operator|(
name|GuideInfo
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_image_add_hguide
argument_list|(
name|image_ID
argument_list|,
name|height
operator|-
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
else|else
name|gimp_image_add_vguide
argument_list|(
name|image_ID
argument_list|,
name|width
operator|-
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guide
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
literal|3
case|:
for|for
control|(
name|list
operator|=
name|guides
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|guide
operator|=
operator|(
name|GuideInfo
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|guide
operator|->
name|orientation
operator|==
name|GIMP_ORIENTATION_HORIZONTAL
condition|)
name|gimp_image_add_vguide
argument_list|(
name|image_ID
argument_list|,
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
else|else
name|gimp_image_add_hguide
argument_list|(
name|image_ID
argument_list|,
name|width
operator|-
name|guide
operator|->
name|position
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|guide
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
name|g_list_free
argument_list|(
name|guides
argument_list|)
expr_stmt|;
block|}
block|}
else|else
comment|/* rotate only the active layer */
block|{
comment|/* check for active selection and float it */
if|if
condition|(
operator|!
name|gimp_selection_is_empty
argument_list|(
name|image_ID
argument_list|)
operator|&&
operator|!
name|gimp_layer_is_floating_sel
argument_list|(
name|active_drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|active_drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|gimp_selection_float
argument_list|(
name|image_ID
argument_list|,
name|active_drawable
operator|->
name|drawable_id
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|rotate_drawable
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|active_drawable
argument_list|)
expr_stmt|;
block|}
name|gimp_image_undo_group_end
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

end_unit

