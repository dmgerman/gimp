begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Tiler v0.3  * 22 May 1997  * Tim Rowley<tor@cs.brown.edu>  */
end_comment

begin_comment
comment|/* TODO:  * + better basis function  * + optimize  */
end_comment

begin_comment
comment|/* History:  * v0.1: initial version  * v0.2: fix edge conditions  * v0.3: port to 0.99 API  */
end_comment

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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

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
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
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

begin_function_decl
specifier|static
name|void
name|tile
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|scale
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|data
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
comment|/* init_proc */
name|NULL
block|,
comment|/* quit_proc */
name|query
block|,
comment|/* query_proc */
name|run
block|,
comment|/* run_proc */
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
parameter_list|()
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
literal|"Interactive, non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"Input image (unused)"
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
specifier|static
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
specifier|static
name|int
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
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_make_seamless"
argument_list|,
literal|"Seamless tile creation"
argument_list|,
literal|"This plugin creates a seamless tileable from the input image"
argument_list|,
literal|"Tim Rowley"
argument_list|,
literal|"Tim Rowley"
argument_list|,
literal|"1997"
argument_list|,
literal|"<Image>/Filters/Map/Make Seamless"
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (char * name,int nparams,GParam * param,int * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|nparams
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|int
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
comment|/*  Get the specified drawable  */
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
comment|/*  Make sure that the drawable is gray or RGB color  */
if|if
condition|(
name|gimp_drawable_color
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_gray
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
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
name|tile
argument_list|(
name|drawable
argument_list|)
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
block|}
else|else
block|{
comment|/* gimp_message ("laplace: cannot operate on indexed color images"); */
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|scale (int width,int height,int x,int y,int data)
specifier|static
name|int
name|scale
parameter_list|(
name|int
name|width
parameter_list|,
name|int
name|height
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|data
parameter_list|)
block|{
name|int
name|A
init|=
name|width
operator|/
literal|2
operator|-
literal|1
decl_stmt|;
name|int
name|B
init|=
name|height
operator|/
literal|2
operator|-
literal|1
decl_stmt|;
name|int
name|a
decl_stmt|,
name|b
decl_stmt|;
if|if
condition|(
name|x
operator|<
name|width
operator|/
literal|2
condition|)
name|a
operator|=
name|width
operator|/
literal|2
operator|-
name|x
operator|-
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|x
operator|==
name|width
operator|/
literal|2
operator|)
operator|&&
operator|(
name|width
operator|&
literal|1
operator|)
condition|)
return|return
name|data
return|;
else|else
name|a
operator|=
name|x
operator|-
name|width
operator|/
literal|2
operator|-
operator|(
name|width
operator|&
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|height
operator|/
literal|2
condition|)
name|b
operator|=
name|height
operator|/
literal|2
operator|-
name|y
operator|-
literal|1
expr_stmt|;
elseif|else
if|if
condition|(
operator|(
name|y
operator|==
name|height
operator|/
literal|2
operator|)
operator|&&
operator|(
name|height
operator|&
literal|1
operator|)
condition|)
return|return
name|data
return|;
else|else
name|b
operator|=
name|y
operator|-
name|height
operator|/
literal|2
operator|-
operator|(
name|height
operator|&
literal|1
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|B
operator|*
name|a
operator|<
name|A
operator|*
name|b
operator|)
operator|||
operator|(
operator|(
name|B
operator|*
name|a
operator|==
name|A
operator|*
name|b
operator|)
operator|&&
operator|(
name|a
operator|&
literal|1
operator|)
operator|)
condition|)
block|{
name|a
operator|=
name|A
operator|-
name|a
expr_stmt|;
name|b
operator|=
name|B
operator|-
name|b
expr_stmt|;
if|if
condition|(
name|a
operator|==
name|A
condition|)
return|return
name|data
return|;
else|else
return|return
name|data
operator|-
operator|(
operator|(
name|data
operator|*
operator|(
name|A
operator|*
name|B
operator|-
name|a
operator|*
name|B
operator|)
operator|)
operator|/
operator|(
name|A
operator|*
name|b
operator|+
name|A
operator|*
name|B
operator|-
name|a
operator|*
name|B
operator|)
operator|)
return|;
block|}
else|else
block|{
if|if
condition|(
name|a
operator|==
name|A
condition|)
return|return
literal|0
return|;
else|else
return|return
operator|(
name|data
operator|*
operator|(
name|A
operator|*
name|B
operator|-
name|a
operator|*
name|B
operator|)
operator|)
operator|/
operator|(
name|A
operator|*
name|b
operator|+
name|A
operator|*
name|B
operator|-
name|a
operator|*
name|B
operator|)
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tile (GDrawable * drawable)
name|tile
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|long
name|width
decl_stmt|,
name|height
decl_stmt|;
name|long
name|bytes
decl_stmt|;
name|long
name|val
decl_stmt|;
name|int
name|wodd
decl_stmt|,
name|hodd
decl_stmt|;
name|GPixelRgn
name|srcPR
decl_stmt|,
name|destPR
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
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|,
name|c
decl_stmt|;
name|guchar
modifier|*
name|cur_row
decl_stmt|,
modifier|*
name|dest_cur
decl_stmt|,
modifier|*
name|dest_top
decl_stmt|,
modifier|*
name|dest_bot
decl_stmt|;
comment|/* Get the input */
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
name|gimp_progress_init
argument_list|(
literal|"Tiler"
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
comment|/*  allocate row buffers  */
name|cur_row
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
name|dest_cur
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
name|dest_top
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
name|dest_bot
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
name|y
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|x
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|wodd
operator|=
name|x
operator|&
literal|1
expr_stmt|;
name|hodd
operator|=
name|y
operator|&
literal|1
expr_stmt|;
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|y
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_cur
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|dest_cur
argument_list|,
literal|0
argument_list|,
name|y
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_cur
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|row
operator|=
literal|0
init|;
name|row
operator|<
name|y
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
name|cur_row
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
name|row
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_cur
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
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
name|row
operator|>=
name|y
operator|/
literal|2
operator|+
name|hodd
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_top
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
operator|(
name|row
operator|-
name|y
operator|/
literal|2
operator|-
name|hodd
operator|)
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
name|row
operator|<
name|y
operator|/
literal|2
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_bot
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
operator|(
name|row
operator|+
name|y
operator|/
literal|2
operator|+
name|hodd
operator|)
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
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
name|x
condition|;
name|col
operator|++
control|)
block|{
for|for
control|(
name|c
operator|=
literal|0
init|;
name|c
operator|<
name|bytes
condition|;
name|c
operator|++
control|)
block|{
name|val
operator|=
name|scale
argument_list|(
name|x
argument_list|,
name|y
argument_list|,
name|col
argument_list|,
name|row
argument_list|,
name|cur_row
index|[
name|col
operator|*
name|bytes
operator|+
name|c
index|]
argument_list|)
expr_stmt|;
comment|/* Main image */
name|dest_cur
index|[
name|col
operator|*
name|bytes
operator|+
name|c
index|]
operator|+=
name|val
expr_stmt|;
comment|/* top left */
if|if
condition|(
operator|(
name|col
operator|>=
name|x
operator|/
literal|2
operator|+
name|wodd
operator|)
operator|&&
operator|(
name|row
operator|>=
name|y
operator|/
literal|2
operator|+
name|hodd
operator|)
condition|)
name|dest_top
index|[
operator|(
name|col
operator|-
name|x
operator|/
literal|2
operator|-
name|wodd
operator|)
operator|*
name|bytes
operator|+
name|c
index|]
operator|+=
name|val
expr_stmt|;
comment|/* top right */
if|if
condition|(
operator|(
name|col
operator|<
name|x
operator|/
literal|2
operator|)
operator|&&
operator|(
name|row
operator|>=
name|y
operator|/
literal|2
operator|+
name|hodd
operator|)
condition|)
name|dest_top
index|[
operator|(
name|x
operator|/
literal|2
operator|+
name|col
operator|+
name|wodd
operator|)
operator|*
name|bytes
operator|+
name|c
index|]
operator|+=
name|val
expr_stmt|;
comment|/* bottom left */
if|if
condition|(
operator|(
name|col
operator|>=
name|x
operator|/
literal|2
operator|+
name|wodd
operator|)
operator|&&
operator|(
name|row
operator|<
name|y
operator|/
literal|2
operator|)
condition|)
name|dest_bot
index|[
operator|(
name|col
operator|-
name|x
operator|/
literal|2
operator|-
name|wodd
operator|)
operator|*
name|bytes
operator|+
name|c
index|]
operator|+=
name|val
expr_stmt|;
comment|/* bottom right */
if|if
condition|(
operator|(
name|col
operator|<
name|x
operator|/
literal|2
operator|)
operator|&&
operator|(
name|row
operator|<
name|y
operator|/
literal|2
operator|)
condition|)
name|dest_bot
index|[
operator|(
name|col
operator|+
name|x
operator|/
literal|2
operator|+
name|wodd
operator|)
operator|*
name|bytes
operator|+
name|c
index|]
operator|+=
name|val
expr_stmt|;
block|}
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_cur
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
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
name|row
operator|>=
name|y
operator|/
literal|2
operator|+
name|hodd
condition|)
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_top
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
operator|(
name|row
operator|-
name|y
operator|/
literal|2
operator|-
name|hodd
operator|)
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
name|row
operator|<
name|y
operator|/
literal|2
condition|)
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest_bot
argument_list|,
name|x1
argument_list|,
name|y1
operator|+
operator|(
name|row
operator|+
name|y
operator|/
literal|2
operator|+
name|hodd
operator|)
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
block|}
end_function

end_unit

