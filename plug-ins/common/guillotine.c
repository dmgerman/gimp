begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  *  Guillotine plug-in v0.9 by Adam D. Moss, adam@foxbox.org.  1998/09/01  */
end_comment

begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-guillotine"
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
name|GList
modifier|*
name|guillotine
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
name|interactive
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
specifier|static
specifier|const
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"image-count"
block|,
literal|"Number of images created"
block|}
block|,
block|{
name|GIMP_PDB_INT32ARRAY
block|,
literal|"image-ids"
block|,
literal|"Output images"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Slice the image into subimages using guides"
argument_list|)
argument_list|,
literal|"This function takes an image and slices it along "
literal|"its guides, creating new images. The original "
literal|"image is not modified."
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"Adam D. Moss (adam@foxbox.org)"
argument_list|,
literal|"1998"
argument_list|,
name|N_
argument_list|(
literal|"Slice Using G_uides"
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
name|G_N_ELEMENTS
argument_list|(
name|return_vals
argument_list|)
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Image/Crop"
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
literal|3
index|]
decl_stmt|;
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
operator|*
name|nreturn_vals
operator|=
literal|3
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
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
literal|0
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_INT32ARRAY
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32array
operator|=
name|NULL
expr_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|GList
modifier|*
name|images
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Guillotine"
argument_list|)
argument_list|)
expr_stmt|;
name|images
operator|=
name|guillotine
argument_list|(
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
operator|=
name|g_list_length
argument_list|(
name|images
argument_list|)
expr_stmt|;
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32array
operator|=
name|g_new
argument_list|(
name|gint32
argument_list|,
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|images
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
operator|,
name|i
operator|++
control|)
block|{
name|values
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32array
index|[
name|i
index|]
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
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
name|GList
modifier|*
DECL|function|guillotine (gint32 image_ID,gboolean interactive)
name|guillotine
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|GList
modifier|*
name|images
init|=
name|NULL
decl_stmt|;
name|gint
name|guide
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gboolean
name|guides_found
init|=
name|FALSE
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
name|image_width
operator|=
name|gimp_image_width
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_image_height
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
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
name|hguides
operator|=
name|g_list_append
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|image_height
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
name|vguides
operator|=
name|g_list_append
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|image_width
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|guide
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
literal|0
argument_list|)
init|;
name|guide
operator|>
literal|0
condition|;
name|guide
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|image_ID
argument_list|,
name|guide
argument_list|)
control|)
block|{
name|gint
name|position
init|=
name|gimp_image_get_guide_position
argument_list|(
name|image_ID
argument_list|,
name|guide
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|gimp_image_get_guide_orientation
argument_list|(
name|image_ID
argument_list|,
name|guide
argument_list|)
condition|)
block|{
case|case
name|GIMP_ORIENTATION_HORIZONTAL
case|:
if|if
condition|(
operator|!
name|g_list_find
argument_list|(
name|hguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|)
condition|)
block|{
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
name|guides_found
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_ORIENTATION_VERTICAL
case|:
if|if
condition|(
operator|!
name|g_list_find
argument_list|(
name|vguides
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|position
argument_list|)
argument_list|)
condition|)
block|{
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
name|guides_found
operator|=
name|TRUE
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_ORIENTATION_UNKNOWN
case|:
name|g_assert_not_reached
argument_list|()
expr_stmt|;
break|break;
block|}
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
name|h
decl_stmt|,
name|v
decl_stmt|,
name|hpad
decl_stmt|,
name|vpad
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gchar
modifier|*
name|hformat
decl_stmt|;
name|gchar
modifier|*
name|format
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
comment|/* get the number horizontal and vertical slices */
name|h
operator|=
name|g_list_length
argument_list|(
name|hguides
argument_list|)
expr_stmt|;
name|v
operator|=
name|g_list_length
argument_list|(
name|vguides
argument_list|)
expr_stmt|;
comment|/* need the number of digits of h and v for the padding */
name|hpad
operator|=
name|log10
argument_list|(
name|h
argument_list|)
operator|+
literal|1
expr_stmt|;
name|vpad
operator|=
name|log10
argument_list|(
name|v
argument_list|)
operator|+
literal|1
expr_stmt|;
comment|/* format for the x-y coordinates in the filename */
name|hformat
operator|=
name|g_strdup_printf
argument_list|(
literal|"%%0%i"
argument_list|,
name|MAX
argument_list|(
name|hpad
argument_list|,
name|vpad
argument_list|)
argument_list|)
expr_stmt|;
name|format
operator|=
name|g_strdup_printf
argument_list|(
literal|"-%si-%si"
argument_list|,
name|hformat
argument_list|,
name|hformat
argument_list|)
expr_stmt|;
comment|/*  Do the actual dup'ing and cropping... this isn't a too naive a        *  way to do this since we got copy-on-write tiles, either.        */
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
name|GString
modifier|*
name|new_filename
decl_stmt|;
name|gchar
modifier|*
name|fileextension
decl_stmt|;
name|gchar
modifier|*
name|fileindex
decl_stmt|;
name|gint
name|pos
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
name|g_free
argument_list|(
name|hformat
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|format
argument_list|)
expr_stmt|;
return|return
name|images
return|;
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
name|new_filename
operator|=
name|g_string_new
argument_list|(
name|filename
argument_list|)
expr_stmt|;
comment|/* show the rough coordinates of the image in the title */
name|fileindex
operator|=
name|g_strdup_printf
argument_list|(
name|format
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
comment|/* get the position of the file extension - last . in filename */
name|fileextension
operator|=
name|strrchr
argument_list|(
name|new_filename
operator|->
name|str
argument_list|,
literal|'.'
argument_list|)
expr_stmt|;
name|pos
operator|=
name|fileextension
operator|-
name|new_filename
operator|->
name|str
expr_stmt|;
comment|/* insert the coordinates before the extension */
name|g_string_insert
argument_list|(
name|new_filename
argument_list|,
name|pos
argument_list|,
name|fileindex
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fileindex
argument_list|)
expr_stmt|;
name|gimp_image_set_filename
argument_list|(
name|new_image
argument_list|,
name|new_filename
operator|->
name|str
argument_list|)
expr_stmt|;
name|g_string_free
argument_list|(
name|new_filename
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
name|guide
operator|=
name|gimp_image_find_next_guide
argument_list|(
name|new_image
argument_list|,
literal|0
argument_list|)
operator|)
condition|)
name|gimp_image_delete_guide
argument_list|(
name|new_image
argument_list|,
name|guide
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|interactive
condition|)
name|gimp_display_new
argument_list|(
name|new_image
argument_list|)
expr_stmt|;
name|images
operator|=
name|g_list_prepend
argument_list|(
name|images
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|new_image
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|hformat
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|format
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
return|return
name|g_list_reverse
argument_list|(
name|images
argument_list|)
return|;
block|}
end_function

end_unit

