begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This is a plug-in for the GIMP.  *  * Copyright (C) Pavel Grinfeld (pavel@ml.com)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
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
file|"fp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_decl_stmt
DECL|variable|Current
name|FP_Params
name|Current
init|=
block|{
literal|1
block|,
literal|.25
block|,
comment|/* Initial Roughness */
name|NULL
block|,
literal|.6
block|,
comment|/* Initial Degree of Aliasing */
name|NULL
block|,
literal|80
block|,
name|NULL
block|,
name|MIDTONES
block|,
comment|/* Initial Range */
name|BY_VAL
block|,
comment|/* Initial God knows what */
name|TRUE
block|,
comment|/* Selection Only */
name|TRUE
block|,
comment|/* Real Time */
literal|0
block|,
comment|/* Offset */
literal|0
block|,
block|{
literal|32
block|,
literal|224
block|,
literal|255
block|}
block|,
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|drawable
DECL|variable|mask
name|GDrawable
modifier|*
name|drawable
decl_stmt|,
modifier|*
name|mask
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|query
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
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
function_decl|;
end_function_decl

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
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_function
name|void
name|query
parameter_list|(
name|void
parameter_list|)
block|{
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
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (used for indexed images)"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"Input drawable"
block|}
block|,   }
decl_stmt|;
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
literal|"plug_in_filter_pack"
argument_list|,
literal|"Allows the user to change H, S, or C with many previews"
argument_list|,
literal|"No help available"
argument_list|,
literal|"Pavel Grinfeld (pavel@ml.com)"
argument_list|,
literal|"Pavel Grinfeld (pavel@ml.com)"
argument_list|,
literal|"27th March 1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Colors/Filter Pack..."
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

begin_comment
comment|/********************************STANDARD RUN*************************/
end_comment

begin_function
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
name|GParam
name|values
index|[
literal|1
index|]
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
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
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
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
name|initializeFilterPacks
argument_list|()
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
name|mask
operator|=
name|gimp_drawable_get
argument_list|(
name|gimp_image_get_selection
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|gimp_message
argument_list|(
name|_
argument_list|(
literal|"Convert the image to RGB first!"
argument_list|)
argument_list|)
expr_stmt|;
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|&&
name|fp_dialog
argument_list|()
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Applying the Filter Pack..."
argument_list|)
argument_list|)
expr_stmt|;
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
name|fp
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|fp_row (const guchar * src_row,guchar * dest_row,gint row,gint row_width,gint bytes)
name|fp_row
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src_row
parameter_list|,
name|guchar
modifier|*
name|dest_row
parameter_list|,
name|gint
name|row
parameter_list|,
name|gint
name|row_width
parameter_list|,
name|gint
name|bytes
parameter_list|)
block|{
name|gint
name|col
decl_stmt|,
name|bytenum
decl_stmt|,
name|k
decl_stmt|;
name|int
name|JudgeBy
decl_stmt|,
name|Intensity
init|=
literal|0
decl_stmt|,
name|P
index|[
literal|3
index|]
decl_stmt|,
name|backupP
index|[
literal|3
index|]
decl_stmt|;
name|hsv
name|H
decl_stmt|,
name|S
decl_stmt|,
name|V
decl_stmt|;
name|gint
name|M
decl_stmt|,
name|m
decl_stmt|,
name|middle
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|row_width
condition|;
name|col
operator|++
control|)
block|{
name|backupP
index|[
literal|0
index|]
operator|=
name|P
index|[
literal|0
index|]
operator|=
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
expr_stmt|;
name|backupP
index|[
literal|0
index|]
operator|=
name|P
index|[
literal|1
index|]
operator|=
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
expr_stmt|;
name|backupP
index|[
literal|0
index|]
operator|=
name|P
index|[
literal|2
index|]
operator|=
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
expr_stmt|;
name|H
operator|=
name|P
index|[
literal|0
index|]
operator|/
literal|255.0
expr_stmt|;
name|S
operator|=
name|P
index|[
literal|1
index|]
operator|/
literal|255.0
expr_stmt|;
name|V
operator|=
name|P
index|[
literal|2
index|]
operator|/
literal|255.0
expr_stmt|;
name|gimp_rgb_to_hsv_double
argument_list|(
operator|&
name|H
argument_list|,
operator|&
name|S
argument_list|,
operator|&
name|V
argument_list|)
expr_stmt|;
for|for
control|(
name|JudgeBy
operator|=
name|BY_HUE
init|;
name|JudgeBy
operator|<
name|JUDGE_BY
condition|;
name|JudgeBy
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|Current
operator|.
name|Touched
index|[
name|JudgeBy
index|]
condition|)
continue|continue;
switch|switch
condition|(
name|JudgeBy
condition|)
block|{
case|case
name|BY_HUE
case|:
name|Intensity
operator|=
literal|255
operator|*
name|H
expr_stmt|;
break|break;
case|case
name|BY_SAT
case|:
name|Intensity
operator|=
literal|255
operator|*
name|S
expr_stmt|;
break|break;
case|case
name|BY_VAL
case|:
name|Intensity
operator|=
literal|255
operator|*
name|V
expr_stmt|;
break|break;
block|}
comment|/* It's important to take care of Saturation first!!! */
name|m
operator|=
name|MIN
argument_list|(
name|MIN
argument_list|(
name|P
index|[
literal|0
index|]
argument_list|,
name|P
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|P
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|M
operator|=
name|MAX
argument_list|(
name|MAX
argument_list|(
name|P
index|[
literal|0
index|]
argument_list|,
name|P
index|[
literal|1
index|]
argument_list|)
argument_list|,
name|P
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
name|middle
operator|=
operator|(
name|M
operator|+
name|m
operator|)
operator|/
literal|2
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|3
condition|;
name|k
operator|++
control|)
if|if
condition|(
name|P
index|[
name|k
index|]
operator|!=
name|m
operator|&&
name|P
index|[
name|k
index|]
operator|!=
name|M
condition|)
name|middle
operator|=
name|P
index|[
name|k
index|]
expr_stmt|;
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
literal|3
condition|;
name|k
operator|++
control|)
if|if
condition|(
name|M
operator|!=
name|m
condition|)
block|{
if|if
condition|(
name|P
index|[
name|k
index|]
operator|==
name|M
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MAX
argument_list|(
name|P
index|[
name|k
index|]
operator|+
name|Current
operator|.
name|satAdj
index|[
name|JudgeBy
index|]
index|[
name|Intensity
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|P
index|[
name|k
index|]
operator|==
name|m
condition|)
name|P
index|[
name|k
index|]
operator|=
name|MIN
argument_list|(
name|P
index|[
name|k
index|]
operator|-
name|Current
operator|.
name|satAdj
index|[
name|JudgeBy
index|]
index|[
name|Intensity
index|]
argument_list|,
name|middle
argument_list|)
expr_stmt|;
block|}
name|P
index|[
literal|0
index|]
operator|+=
name|Current
operator|.
name|redAdj
index|[
name|JudgeBy
index|]
index|[
name|Intensity
index|]
expr_stmt|;
name|P
index|[
literal|1
index|]
operator|+=
name|Current
operator|.
name|greenAdj
index|[
name|JudgeBy
index|]
index|[
name|Intensity
index|]
expr_stmt|;
name|P
index|[
literal|2
index|]
operator|+=
name|Current
operator|.
name|blueAdj
index|[
name|JudgeBy
index|]
index|[
name|Intensity
index|]
expr_stmt|;
name|P
index|[
literal|0
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
literal|255
argument_list|,
name|P
index|[
literal|0
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|P
index|[
literal|1
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
literal|255
argument_list|,
name|P
index|[
literal|1
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|P
index|[
literal|2
index|]
operator|=
name|MAX
argument_list|(
literal|0
argument_list|,
name|MIN
argument_list|(
literal|255
argument_list|,
name|P
index|[
literal|2
index|]
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|0
index|]
operator|=
name|P
index|[
literal|0
index|]
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|1
index|]
operator|=
name|P
index|[
literal|1
index|]
expr_stmt|;
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
literal|2
index|]
operator|=
name|P
index|[
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|bytes
operator|>
literal|3
condition|)
for|for
control|(
name|bytenum
operator|=
literal|3
init|;
name|bytenum
operator|<
name|bytes
condition|;
name|bytenum
operator|++
control|)
name|dest_row
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
operator|=
name|src_row
index|[
name|col
operator|*
name|bytes
operator|+
name|bytenum
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|fp (GDrawable * drawable)
name|void
name|fp
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
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
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|dest_row
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
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
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
name|src_row
operator|=
operator|(
name|guchar
operator|*
operator|)
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|)
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
name|malloc
argument_list|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
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
for|for
control|(
name|row
operator|=
name|y1
init|;
name|row
operator|<
name|y2
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
name|x1
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|fp_row
argument_list|(
name|src_row
argument_list|,
name|dest_row
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_row
argument_list|,
name|x1
argument_list|,
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|10
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
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  update the processed region  */
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|free
argument_list|(
name|dest_row
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

