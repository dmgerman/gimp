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
name|guillotine
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

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
literal|"run_mode"
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
literal|"Input drawable (unused)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_guillotine"
argument_list|,
literal|"Slice up the image into subimages, cutting along "
literal|"the image's Guides.  Fooey to you and your "
literal|"broccoli, Pokey."
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
literal|"<Image>/Image/Transform/Guillotine"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*, GRAY*"
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
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|gint32
name|image_ID
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
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
name|GIMP_PDB_SUCCESS
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
DECL|function|guide_sort_func (gconstpointer a,gconstpointer b)
name|guide_sort_func
parameter_list|(
name|gconstpointer
name|a
parameter_list|,
name|gconstpointer
name|b
parameter_list|)
block|{
return|return
name|GPOINTER_TO_INT
argument_list|(
name|a
argument_list|)
operator|-
name|GPOINTER_TO_INT
argument_list|(
name|b
argument_list|)
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
name|guide_num
decl_stmt|;
name|gboolean
name|guides_found
decl_stmt|;
name|GList
modifier|*
name|hguides
decl_stmt|,
modifier|*
name|hg
decl_stmt|;
name|GList
modifier|*
name|vguides
decl_stmt|,
modifier|*
name|vg
decl_stmt|;
name|hguides
operator|=
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|vguides
operator|=
name|g_list_append
argument_list|(
name|NULL
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|0
argument_list|)
argument_list|)
expr_stmt|;
name|hguides
operator|=
name|g_list_append
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|vguides
operator|=
name|g_list_append
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
argument_list|)
argument_list|)
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
name|guides_found
operator|=
operator|(
name|guide_num
operator|!=
literal|0
operator|)
expr_stmt|;
while|while
condition|(
name|guide_num
operator|>
literal|0
condition|)
block|{
name|gint
name|position
init|=
name|gimp_image_get_guide_position
argument_list|(
name|image_ID
argument_list|,
name|guide_num
argument_list|)
decl_stmt|;
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
name|GIMP_ORIENTATION_HORIZONTAL
case|:
name|hguides
operator|=
name|g_list_insert_sorted
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|,
name|guide_sort_func
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
name|vguides
operator|=
name|g_list_insert_sorted
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|,
name|guide_sort_func
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_ORIENTATION_UNKNOWN
case|:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
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
if|if
condition|(
name|guides_found
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|filename
operator|=
name|gimp_image_get_filename
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filename
condition|)
name|filename
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Untitled"
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Do the actual dup'ing and cropping... this isn't a too naive a 	 way to do this since we got copy-on-write tiles, either. */
for|for
control|(
name|y
operator|=
literal|0
operator|,
name|hg
operator|=
name|hguides
init|;
name|hg
operator|&&
name|hg
operator|->
name|next
condition|;
name|y
operator|++
operator|,
name|hg
operator|=
name|hg
operator|->
name|next
control|)
block|{
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|vg
operator|=
name|vguides
init|;
name|vg
operator|&&
name|vg
operator|->
name|next
condition|;
name|x
operator|++
operator|,
name|vg
operator|=
name|vg
operator|->
name|next
control|)
block|{
name|gint32
name|new_image
init|=
name|gimp_image_duplicate
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|new_filename
decl_stmt|;
if|if
condition|(
name|new_image
operator|==
operator|-
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"Couldn't create new image."
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_image_undo_disable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_image_crop
argument_list|(
name|new_image
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|vg
operator|->
name|next
operator|->
name|data
argument_list|)
operator|-
name|GPOINTER_TO_INT
argument_list|(
name|vg
operator|->
name|data
argument_list|)
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|hg
operator|->
name|next
operator|->
name|data
argument_list|)
operator|-
name|GPOINTER_TO_INT
argument_list|(
name|hg
operator|->
name|data
argument_list|)
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|vg
operator|->
name|data
argument_list|)
argument_list|,
name|GPOINTER_TO_INT
argument_list|(
name|hg
operator|->
name|data
argument_list|)
argument_list|)
expr_stmt|;
comment|/* show the rough coordinates of the image in the title */
name|new_filename
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-(%i,%i)"
argument_list|,
name|filename
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
name|new_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|new_filename
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|gimp_display_new
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|hguides
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|vguides
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

