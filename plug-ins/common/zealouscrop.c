begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * ZealousCrop plug-in version 1.00  * by Adam D. Moss<adam@foxbox.org>  * loosely based on Autocrop by Tim Newsome<drz@froody.bloke.com>  */
end_comment

begin_comment
comment|/*  * BUGS:  *  Doesn't undo properly.  *  Progress bar doesn't do anything yet.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_CONFIG_H
end_ifdef

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Declare local functions. */
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
specifier|inline
name|int
name|colours_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|int
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|do_zcrop
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
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

begin_decl_stmt
DECL|variable|bytes
name|gint
name|bytes
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|sx1
DECL|variable|sy1
DECL|variable|sx2
DECL|variable|sy2
name|gint
name|sx1
decl_stmt|,
name|sy1
decl_stmt|,
name|sx2
decl_stmt|,
name|sy2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_flag
name|int
name|run_flag
init|=
literal|0
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_zealouscrop"
argument_list|,
name|_
argument_list|(
literal|"Automagically crops unused space from the edges and middle of a picture."
argument_list|)
argument_list|,
literal|""
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"Adam D. Moss"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Transforms/Zealous Crop"
argument_list|)
argument_list|,
literal|"RGB*, GRAY*, INDEXED*"
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
DECL|function|run (char * name,int n_params,GParam * param,int * nreturn_vals,GParam ** return_vals)
specifier|static
name|void
name|run
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
name|int
name|n_params
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
name|gint32
name|image_id
decl_stmt|;
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
name|RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|n_params
operator|!=
literal|3
condition|)
block|{
name|status
operator|=
name|STATUS_CALLING_ERROR
expr_stmt|;
block|}
block|}
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
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
name|image_id
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
expr_stmt|;
comment|/*  Make sure that the drawable is gray or RGB or indexed  */
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
operator|||
name|gimp_drawable_indexed
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"ZealousCropping(tm)..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
literal|1
operator|+
literal|2
operator|*
operator|(
name|drawable
operator|->
name|width
operator|>
name|drawable
operator|->
name|height
condition|?
operator|(
name|drawable
operator|->
name|width
operator|/
name|gimp_tile_width
argument_list|()
operator|)
else|:
operator|(
name|drawable
operator|->
name|height
operator|/
name|gimp_tile_height
argument_list|()
operator|)
operator|)
argument_list|)
expr_stmt|;
name|do_zcrop
argument_list|(
name|drawable
argument_list|,
name|image_id
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
expr_stmt|;
block|}
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
block|}
end_function

begin_function
DECL|function|do_zcrop (GDrawable * drawable,gint32 image_id)
specifier|static
name|void
name|do_zcrop
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|,
name|gint32
name|image_id
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
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|int
name|nreturn_vals
decl_stmt|;
name|gint8
modifier|*
name|killrows
decl_stmt|;
name|gint8
modifier|*
name|killcols
decl_stmt|;
name|gint32
name|livingrows
decl_stmt|,
name|livingcols
decl_stmt|,
name|destrow
decl_stmt|,
name|destcol
decl_stmt|;
name|int
name|total_area
decl_stmt|,
name|area
decl_stmt|;
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
name|total_area
operator|=
name|width
operator|*
name|height
operator|*
literal|4
expr_stmt|;
name|area
operator|=
literal|0
expr_stmt|;
name|killrows
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gint8
argument_list|)
operator|*
name|height
argument_list|)
expr_stmt|;
name|killcols
operator|=
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|gint8
argument_list|)
operator|*
name|width
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|g_malloc
argument_list|(
operator|(
name|width
operator|>
name|height
condition|?
name|width
else|:
name|height
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the pixel regions  */
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
name|livingrows
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
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
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|killrows
index|[
name|y
index|]
operator|=
name|TRUE
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
operator|*
name|bytes
condition|;
name|x
operator|+=
name|bytes
control|)
block|{
if|if
condition|(
operator|!
name|colours_equal
argument_list|(
name|buffer
argument_list|,
operator|&
name|buffer
index|[
name|x
index|]
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|livingrows
operator|++
expr_stmt|;
name|killrows
index|[
name|y
index|]
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
name|area
operator|+=
name|width
expr_stmt|;
if|if
condition|(
name|y
operator|%
literal|20
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
name|livingcols
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
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
name|x
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|killcols
index|[
name|x
index|]
operator|=
name|TRUE
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
operator|*
name|bytes
condition|;
name|y
operator|+=
name|bytes
control|)
block|{
if|if
condition|(
operator|!
name|colours_equal
argument_list|(
name|buffer
argument_list|,
operator|&
name|buffer
index|[
name|y
index|]
argument_list|,
name|bytes
argument_list|)
condition|)
block|{
name|livingcols
operator|++
expr_stmt|;
name|killcols
index|[
name|x
index|]
operator|=
name|FALSE
expr_stmt|;
break|break;
block|}
block|}
name|area
operator|+=
name|height
expr_stmt|;
if|if
condition|(
name|x
operator|%
literal|20
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|(
name|livingcols
operator|==
literal|0
operator|)
operator|||
operator|(
name|livingrows
operator|==
literal|0
operator|)
operator|)
operator|||
operator|(
operator|(
name|livingcols
operator|==
name|width
operator|)
operator|&&
operator|(
name|livingrows
operator|==
name|height
operator|)
operator|)
condition|)
block|{
name|printf
argument_list|(
name|_
argument_list|(
literal|"ZealousCrop(tm): Nothing to be done.\n"
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|destrow
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|height
condition|;
name|y
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|killrows
index|[
name|y
index|]
condition|)
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
name|y
argument_list|,
name|width
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
name|destrow
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|destrow
operator|++
expr_stmt|;
block|}
name|area
operator|+=
name|width
expr_stmt|;
if|if
condition|(
name|y
operator|%
literal|20
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
name|destcol
operator|=
literal|0
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
name|TRUE
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|killcols
index|[
name|x
index|]
condition|)
block|{
name|gimp_pixel_rgn_get_col
argument_list|(
operator|&
name|srcPR
argument_list|,
name|buffer
argument_list|,
name|x
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_col
argument_list|(
operator|&
name|destPR
argument_list|,
name|buffer
argument_list|,
name|destcol
argument_list|,
literal|0
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|destcol
operator|++
expr_stmt|;
block|}
name|area
operator|+=
name|height
expr_stmt|;
if|if
condition|(
name|x
operator|%
literal|20
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|area
operator|/
operator|(
name|double
operator|)
name|total_area
argument_list|)
expr_stmt|;
block|}
comment|/*  printf("dc: %d, lc: %d  - - - dr: %d, lr: %d\n",destcol, livingcols, destrow, livingrows);*/
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|killrows
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|killcols
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.00
argument_list|)
expr_stmt|;
name|gimp_run_procedure
argument_list|(
literal|"gimp_undo_push_group_start"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_id
argument_list|,
name|PARAM_END
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
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_run_procedure
argument_list|(
literal|"gimp_crop"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_id
argument_list|,
name|PARAM_INT32
argument_list|,
operator|(
name|gint32
operator|)
name|livingcols
argument_list|,
name|PARAM_INT32
argument_list|,
operator|(
name|gint32
operator|)
name|livingrows
argument_list|,
name|PARAM_INT32
argument_list|,
literal|0
argument_list|,
name|PARAM_INT32
argument_list|,
literal|0
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
name|gimp_run_procedure
argument_list|(
literal|"gimp_undo_push_group_end"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_id
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|colours_equal (guchar * col1,guchar * col2,int bytes)
specifier|static
specifier|inline
name|int
name|colours_equal
parameter_list|(
name|guchar
modifier|*
name|col1
parameter_list|,
name|guchar
modifier|*
name|col2
parameter_list|,
name|int
name|bytes
parameter_list|)
block|{
name|int
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bytes
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
name|col1
index|[
name|b
index|]
operator|!=
name|col2
index|[
name|b
index|]
condition|)
block|{
return|return
operator|(
name|FALSE
operator|)
return|;
break|break;
block|}
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

