begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* borderaverage 0.01 - image processing plug-in for the Gimp 1.0 API  *  * Copyright (C) 1998 Philipp Klaus (webmaster@access.ch)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<libgimp/gimpui.h>
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
name|borderaverage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRGB
modifier|*
name|result
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|borderaverage_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|add_new_color
parameter_list|(
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
modifier|*
name|cube
parameter_list|,
name|gint
name|bucket_expo
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
comment|/* init  */
name|NULL
block|,
comment|/* quit  */
name|query
block|,
comment|/* query */
name|run
block|,
comment|/* run   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|borderaverage_thickness
specifier|static
name|gint
name|borderaverage_thickness
init|=
literal|3
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|borderaverage_bucket_exponent
specifier|static
name|gint
name|borderaverage_bucket_exponent
init|=
literal|4
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|borderaverage_data
struct|struct
name|borderaverage_data
block|{
DECL|member|thickness
name|gint
name|thickness
decl_stmt|;
DECL|member|bucket_exponent
name|gint
name|bucket_exponent
decl_stmt|;
block|}
DECL|variable|borderaverage_data
name|borderaverage_data
init|=
block|{
literal|3
block|,
literal|4
block|}
struct|;
end_struct

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
name|GIMP_PDB_INT32
block|,
literal|"thickness"
block|,
literal|"Border size to take in count"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"bucket_exponent"
block|,
literal|"Bits for bucket size (default=4: 16 Levels)"
block|}
block|,   }
decl_stmt|;
specifier|static
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_COLOR
block|,
literal|"borderaverage"
block|,
literal|"The average color of the specified border"
block|}
block|,   }
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_borderaverage"
argument_list|,
literal|"Borderaverage"
argument_list|,
literal|""
argument_list|,
literal|"Philipp Klaus"
argument_list|,
literal|"Internet Access AG"
argument_list|,
literal|"1998"
argument_list|,
name|N_
argument_list|(
literal|"_Border Average..."
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
literal|"plug_in_borderaverage"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors"
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
literal|3
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
name|GimpRGB
name|result_color
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
comment|/*    Get the specified drawable      */
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
literal|"plug_in_borderaverage"
argument_list|,
operator|&
name|borderaverage_data
argument_list|)
expr_stmt|;
name|borderaverage_thickness
operator|=
name|borderaverage_data
operator|.
name|thickness
expr_stmt|;
name|borderaverage_bucket_exponent
operator|=
name|borderaverage_data
operator|.
name|bucket_exponent
expr_stmt|;
if|if
condition|(
operator|!
name|borderaverage_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|5
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
name|borderaverage_thickness
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|borderaverage_bucket_exponent
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
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
literal|"plug_in_borderaverage"
argument_list|,
operator|&
name|borderaverage_data
argument_list|)
expr_stmt|;
name|borderaverage_thickness
operator|=
name|borderaverage_data
operator|.
name|thickness
expr_stmt|;
name|borderaverage_bucket_exponent
operator|=
name|borderaverage_data
operator|.
name|bucket_exponent
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
comment|/*  Make sure that the drawable is RGB color  */
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Border Average..."
argument_list|)
argument_list|)
expr_stmt|;
name|borderaverage
argument_list|(
name|drawable
argument_list|,
operator|&
name|result_color
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
name|gimp_palette_set_foreground
argument_list|(
operator|&
name|result_color
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
block|{
name|borderaverage_data
operator|.
name|thickness
operator|=
name|borderaverage_thickness
expr_stmt|;
name|borderaverage_data
operator|.
name|bucket_exponent
operator|=
name|borderaverage_bucket_exponent
expr_stmt|;
name|gimp_set_data
argument_list|(
literal|"plug_in_borderaverage"
argument_list|,
operator|&
name|borderaverage_data
argument_list|,
sizeof|sizeof
argument_list|(
name|borderaverage_data
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
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
name|GIMP_PDB_COLOR
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_color
operator|=
name|result_color
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|borderaverage (GimpDrawable * drawable,GimpRGB * result)
name|borderaverage
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpRGB
modifier|*
name|result
parameter_list|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|max
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|guchar
modifier|*
name|buffer
decl_stmt|;
name|gint
name|bucket_num
decl_stmt|,
name|bucket_expo
decl_stmt|,
name|bucket_rexpo
decl_stmt|;
name|gint
modifier|*
name|cube
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
comment|/* index variables */
name|GimpPixelRgn
name|myPR
decl_stmt|;
comment|/* allocate and clear the cube before */
name|bucket_expo
operator|=
name|borderaverage_bucket_exponent
expr_stmt|;
name|bucket_rexpo
operator|=
literal|8
operator|-
name|bucket_expo
expr_stmt|;
name|cube
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
literal|1
operator|<<
operator|(
name|bucket_rexpo
operator|*
literal|3
operator|)
argument_list|)
expr_stmt|;
name|bucket_num
operator|=
literal|1
operator|<<
name|bucket_rexpo
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bucket_num
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|bucket_num
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bucket_num
condition|;
name|k
operator|++
control|)
block|{
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
comment|/*  Get the input area. This is the bounding box of the selection in    *  the image (or the entire image if there is no selection). Only    *  operating on the input area is simply an optimization. It doesn't    *  need to be done for correct operation. (It simply makes it go    *  faster, since fewer pixels need to be operated on).    */
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
comment|/*  Get the size of the input image. (This will/must be the same    *  as the size of the output image.    */
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
name|gimp_tile_cache_ntiles
argument_list|(
literal|2
operator|*
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
comment|/*  allocate row buffer  */
name|buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the pixel regions  */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|myPR
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
comment|/*  loop through the rows, performing our magic*/
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
name|myPR
argument_list|,
name|buffer
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
name|row
operator|<
name|y1
operator|+
name|borderaverage_thickness
operator|||
name|row
operator|>=
name|y2
operator|-
name|borderaverage_thickness
condition|)
block|{
comment|/* add the whole row */
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
operator|)
condition|;
name|col
operator|+=
name|bytes
control|)
block|{
name|add_new_color
argument_list|(
name|bytes
argument_list|,
operator|&
name|buffer
index|[
name|col
index|]
argument_list|,
name|cube
argument_list|,
name|bucket_expo
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* add the left border */
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
operator|(
name|borderaverage_thickness
operator|*
name|bytes
operator|)
condition|;
name|col
operator|+=
name|bytes
control|)
block|{
name|add_new_color
argument_list|(
name|bytes
argument_list|,
operator|&
name|buffer
index|[
name|col
index|]
argument_list|,
name|cube
argument_list|,
name|bucket_expo
argument_list|)
expr_stmt|;
block|}
comment|/* add the right border */
for|for
control|(
name|col
operator|=
operator|(
operator|(
name|x2
operator|-
name|x1
operator|-
name|borderaverage_thickness
operator|)
operator|*
name|bytes
operator|)
init|;
name|col
operator|<
operator|(
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
operator|)
condition|;
name|col
operator|+=
name|bytes
control|)
block|{
name|add_new_color
argument_list|(
name|bytes
argument_list|,
operator|&
name|buffer
index|[
name|col
index|]
argument_list|,
name|cube
argument_list|,
name|bucket_expo
argument_list|)
expr_stmt|;
block|}
block|}
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
name|max
operator|=
literal|0
expr_stmt|;
name|r
operator|=
literal|0
expr_stmt|;
name|g
operator|=
literal|0
expr_stmt|;
name|b
operator|=
literal|0
expr_stmt|;
comment|/* get max of cube */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bucket_num
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|bucket_num
condition|;
name|j
operator|++
control|)
block|{
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|bucket_num
condition|;
name|k
operator|++
control|)
block|{
if|if
condition|(
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
operator|>
name|max
condition|)
block|{
name|max
operator|=
name|cube
index|[
operator|(
name|i
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|j
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|k
index|]
expr_stmt|;
name|r
operator|=
operator|(
name|i
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
name|g
operator|=
operator|(
name|j
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
name|b
operator|=
operator|(
name|k
operator|<<
name|bucket_expo
operator|)
operator|+
operator|(
literal|1
operator|<<
operator|(
name|bucket_expo
operator|-
literal|1
operator|)
operator|)
expr_stmt|;
block|}
block|}
block|}
block|}
comment|/* return the color */
name|gimp_rgb_set_uchar
argument_list|(
name|result
argument_list|,
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|cube
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_new_color (gint bytes,guchar * buffer,gint * cube,gint bucket_expo)
name|add_new_color
parameter_list|(
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|buffer
parameter_list|,
name|gint
modifier|*
name|cube
parameter_list|,
name|gint
name|bucket_expo
parameter_list|)
block|{
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|bucket_rexpo
decl_stmt|;
name|bucket_rexpo
operator|=
literal|8
operator|-
name|bucket_expo
expr_stmt|;
name|r
operator|=
name|buffer
index|[
literal|0
index|]
operator|>>
name|bucket_expo
expr_stmt|;
if|if
condition|(
name|bytes
operator|>
literal|1
condition|)
block|{
name|g
operator|=
name|buffer
index|[
literal|1
index|]
operator|>>
name|bucket_expo
expr_stmt|;
block|}
else|else
block|{
name|g
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|bytes
operator|>
literal|2
condition|)
block|{
name|b
operator|=
name|buffer
index|[
literal|2
index|]
operator|>>
name|bucket_expo
expr_stmt|;
block|}
else|else
block|{
name|b
operator|=
literal|0
expr_stmt|;
block|}
name|cube
index|[
operator|(
name|r
operator|<<
operator|(
name|bucket_rexpo
operator|<<
literal|1
operator|)
operator|)
operator|+
operator|(
name|g
operator|<<
name|bucket_rexpo
operator|)
operator|+
name|b
index|]
operator|++
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|borderaverage_dialog (void)
name|borderaverage_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|labels
index|[]
init|=
block|{
literal|"1"
block|,
literal|"2"
block|,
literal|"4"
block|,
literal|"8"
block|,
literal|"16"
block|,
literal|"32"
block|,
literal|"64"
block|,
literal|"128"
block|,
literal|"256"
block|}
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"borderaverage"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Borderaverage"
argument_list|)
argument_list|,
literal|"borderaverage"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-borderaverage"
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Border Size"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Thickness:"
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
name|borderaverage_thickness
argument_list|,
literal|0
argument_list|,
literal|256
argument_list|,
literal|1
argument_list|,
literal|5
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
literal|0
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
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|borderaverage_thickness
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Number of Colors"
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Bucket Size:"
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
name|combo
operator|=
name|gimp_int_combo_box_new_array
argument_list|(
name|G_N_ELEMENTS
argument_list|(
name|labels
argument_list|)
argument_list|,
name|labels
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
name|borderaverage_bucket_exponent
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_combo_box_get_active
argument_list|)
argument_list|,
operator|&
name|borderaverage_bucket_exponent
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|gtk_label_set_mnemonic_widget
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|combo
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
name|run
operator|=
operator|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dlg
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
operator|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dlg
argument_list|)
expr_stmt|;
return|return
name|run
return|;
block|}
end_function

end_unit

