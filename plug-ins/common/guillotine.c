begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Guillotine plug-in v0.9 by Adam D. Moss, adam@foxbox.org.  1998/09/01  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * HISTORY:  *     0.9 : 1998/09/01  *           Initial release.  */
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
file|<libgimp/gimp.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
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

begin_function_decl
specifier|static
name|void
name|guillotine
parameter_list|(
name|gint32
name|image_ID
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
specifier|static
name|void
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
literal|"Input drawable (unused)"
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
literal|"plug_in_guillotine"
argument_list|,
literal|"Slice up the image into subimages, cutting along the image's Guides.  Fooey to you and your broccoli, Pokey."
argument_list|,
literal|"This function takes an image and blah blah.  Hooray!"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"1998"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Image/Transforms/Guillotine"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
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
name|gint32
name|image_ID
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
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*  Get the specified drawable  */
name|image_ID
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
if|if
condition|(
name|status
operator|==
name|STATUS_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Guillotine..."
argument_list|)
argument_list|)
expr_stmt|;
name|guillotine
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
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
name|gint
DECL|function|unexciting (const void * a,const void * b)
name|unexciting
parameter_list|(
specifier|const
name|void
modifier|*
name|a
parameter_list|,
specifier|const
name|void
modifier|*
name|b
parameter_list|)
block|{
name|gint
name|j
init|=
operator|*
operator|(
name|gint
operator|*
operator|)
name|a
decl_stmt|;
name|gint
name|k
init|=
operator|*
operator|(
name|gint
operator|*
operator|)
name|b
decl_stmt|;
return|return
operator|(
name|j
operator|-
name|k
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|guillotine (gint32 image_ID)
name|guillotine
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|gint
name|num_vguides
decl_stmt|;
name|gint
name|num_hguides
decl_stmt|;
name|gint
name|guide_num
decl_stmt|;
name|gint
modifier|*
name|hguides
decl_stmt|;
name|gint
modifier|*
name|vguides
decl_stmt|;
name|gchar
name|filename
index|[
literal|1024
index|]
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|num_vguides
operator|=
literal|0
expr_stmt|;
name|num_hguides
operator|=
literal|0
expr_stmt|;
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/* Count the guides so we can allocate appropriate memory */
if|if
condition|(
name|guide_num
operator|>
literal|0
condition|)
block|{
do|do
block|{
switch|switch
condition|(
name|gimp_image_get_guide_orientation
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
condition|)
block|{
case|case
name|ORIENTATION_VERTICAL
case|:
name|num_vguides
operator|++
expr_stmt|;
break|break;
case|case
name|ORIENTATION_HORIZONTAL
case|:
name|num_hguides
operator|++
expr_stmt|;
break|break;
default|default:
name|g_print
argument_list|(
literal|"Aie!  Aie!  Aie!\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|guide_num
operator|>
literal|0
condition|)
do|;
block|}
if|if
condition|(
name|num_vguides
operator|+
name|num_hguides
condition|)
block|{
name|printf
argument_list|(
literal|"Yay... found %d horizontal guides and %d vertical guides.\n"
argument_list|,
name|num_hguides
argument_list|,
name|num_vguides
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|printf
argument_list|(
literal|"Poopy, no guides.\n"
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* Allocate memory for the arrays of guide offsets, build arrays */
name|vguides
operator|=
name|g_malloc
argument_list|(
operator|(
name|num_vguides
operator|+
literal|2
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|)
expr_stmt|;
name|hguides
operator|=
name|g_malloc
argument_list|(
operator|(
name|num_hguides
operator|+
literal|2
operator|)
operator|*
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|)
expr_stmt|;
name|num_vguides
operator|=
literal|0
expr_stmt|;
name|num_hguides
operator|=
literal|0
expr_stmt|;
name|vguides
index|[
name|num_vguides
operator|++
index|]
operator|=
literal|0
expr_stmt|;
name|hguides
index|[
name|num_hguides
operator|++
index|]
operator|=
literal|0
expr_stmt|;
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|guide_num
operator|>
literal|0
condition|)
block|{
do|do
block|{
switch|switch
condition|(
name|gimp_image_get_guide_orientation
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
condition|)
block|{
case|case
name|ORIENTATION_VERTICAL
case|:
name|vguides
index|[
name|num_vguides
operator|++
index|]
operator|=
name|gimp_image_get_guide_position
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
expr_stmt|;
break|break;
case|case
name|ORIENTATION_HORIZONTAL
case|:
name|hguides
index|[
name|num_hguides
operator|++
index|]
operator|=
name|gimp_image_get_guide_position
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
expr_stmt|;
break|break;
default|default:
name|printf
argument_list|(
literal|"Aie!  Aie!  Aie!  Too!\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
name|guide_num
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|guide_num
operator|>
literal|0
condition|)
do|;
block|}
name|vguides
index|[
name|num_vguides
operator|++
index|]
operator|=
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|hguides
index|[
name|num_hguides
operator|++
index|]
operator|=
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|qsort
argument_list|(
name|hguides
argument_list|,
name|num_hguides
argument_list|,
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|,
operator|&
name|unexciting
argument_list|)
expr_stmt|;
name|qsort
argument_list|(
name|vguides
argument_list|,
name|num_vguides
argument_list|,
sizeof|sizeof
argument_list|(
name|gint
argument_list|)
argument_list|,
operator|&
name|unexciting
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
name|num_vguides
condition|;
name|i
operator|++
control|)
name|printf
argument_list|(
literal|"%d,"
argument_list|,
name|vguides
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
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
name|num_hguides
condition|;
name|i
operator|++
control|)
name|printf
argument_list|(
literal|"%d,"
argument_list|,
name|hguides
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
comment|/* Do the actual dup'ing and cropping... this isn't a too naive a      way to do this since we got copy-on-write tiles, either. */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|num_hguides
operator|-
literal|1
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|num_vguides
operator|-
literal|1
condition|;
name|x
operator|++
control|)
block|{
name|gint32
name|new_image
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
literal|"gimp_channel_ops_duplicate"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
if|if
condition|(
name|return_vals
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_status
operator|==
name|STATUS_SUCCESS
condition|)
name|new_image
operator|=
name|return_vals
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
else|else
block|{
name|printf
argument_list|(
literal|"Aie3!\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
comment|/*  	  gimp_undo_push_group_start (new_image); */
comment|/* 	  printf("(%dx%d:%d,%d:%d,%d)\n", */
comment|/* 		 (vguides[x+1]-vguides[x]), */
comment|/* 		 (hguides[y+1]-hguides[y]), */
comment|/* 		 vguides[x], hguides[y],x, y);  */
name|gimp_run_procedure
argument_list|(
literal|"gimp_crop"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PARAM_IMAGE
argument_list|,
name|new_image
argument_list|,
name|PARAM_INT32
argument_list|,
operator|(
name|vguides
index|[
name|x
operator|+
literal|1
index|]
operator|-
name|vguides
index|[
name|x
index|]
operator|)
argument_list|,
name|PARAM_INT32
argument_list|,
operator|(
name|hguides
index|[
name|y
operator|+
literal|1
index|]
operator|-
name|hguides
index|[
name|y
index|]
operator|)
argument_list|,
name|PARAM_INT32
argument_list|,
name|vguides
index|[
name|x
index|]
argument_list|,
name|PARAM_INT32
argument_list|,
name|hguides
index|[
name|y
index|]
argument_list|,
name|PARAM_END
argument_list|)
expr_stmt|;
comment|/*  	  gimp_undo_push_group_end (new_image); */
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
comment|/* show the rough coordinates of the image in the title */
name|sprintf
argument_list|(
name|filename
argument_list|,
literal|"%s-(%i,%i)"
argument_list|,
name|gimp_image_get_filename
argument_list|(
name|image_ID
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|new_image
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_display_new
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

