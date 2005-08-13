begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* borderaverage 0.01 - image processing plug-in for the Gimp.  *  * Copyright (C) 1998 Philipp Klaus (webmaster@access.ch)  *  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|"plug-in-borderaverage"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"borderaverage"
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
name|gboolean
name|borderaverage_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
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
specifier|const
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

begin_function_decl
specifier|static
name|void
name|thickness_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
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
decl|static
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
literal|"bucket-exponent"
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
name|PLUG_IN_PROC
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Colors"
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
name|gint32
name|image_ID
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpRGB
name|result_color
decl_stmt|;
name|GimpRunMode
name|run_mode
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
name|PLUG_IN_PROC
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
argument_list|(
name|image_ID
argument_list|,
name|drawable
argument_list|)
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
name|PLUG_IN_PROC
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
name|gimp_context_set_foreground
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
name|PLUG_IN_PROC
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

begin_typedef
DECL|struct|__anon275871460108
typedef|typedef
struct|struct
block|{
DECL|member|x1
DECL|member|x2
DECL|member|y1
DECL|member|y2
name|gint
name|x1
decl_stmt|,
name|x2
decl_stmt|,
name|y1
decl_stmt|,
name|y2
decl_stmt|;
DECL|member|bucket_expo
name|gint
name|bucket_expo
decl_stmt|;
DECL|member|cube
name|gint
modifier|*
name|cube
decl_stmt|;
DECL|typedef|BorderAverageParam_t
block|}
name|BorderAverageParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|borderaverage_func (gint x,gint y,const guchar * src,gint bpp,gpointer data)
name|borderaverage_func
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BorderAverageParam_t
modifier|*
name|param
init|=
operator|(
name|BorderAverageParam_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|x
operator|<
name|param
operator|->
name|x1
operator|+
name|borderaverage_thickness
operator|||
name|x
operator|>=
name|param
operator|->
name|x2
operator|-
name|borderaverage_thickness
operator|||
name|y
operator|<
name|param
operator|->
name|y1
operator|+
name|borderaverage_thickness
operator|||
name|y
operator|>=
name|param
operator|->
name|y2
operator|-
name|borderaverage_thickness
condition|)
block|{
name|add_new_color
argument_list|(
name|bpp
argument_list|,
name|src
argument_list|,
name|param
operator|->
name|cube
argument_list|,
name|param
operator|->
name|bucket_expo
argument_list|)
expr_stmt|;
block|}
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
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
comment|/* index variables */
name|GimpRgnIterator
modifier|*
name|iter
decl_stmt|;
name|BorderAverageParam_t
name|param
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
name|param
operator|.
name|cube
operator|=
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
name|param
operator|.
name|x1
operator|=
name|x1
expr_stmt|;
name|param
operator|.
name|y1
operator|=
name|y1
expr_stmt|;
name|param
operator|.
name|x2
operator|=
name|x2
expr_stmt|;
name|param
operator|.
name|y2
operator|=
name|y2
expr_stmt|;
name|param
operator|.
name|bucket_expo
operator|=
name|bucket_expo
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
name|iter
operator|=
name|gimp_rgn_iterator_new
argument_list|(
name|drawable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_src
argument_list|(
name|iter
argument_list|,
name|borderaverage_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_free
argument_list|(
name|iter
argument_list|)
expr_stmt|;
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
DECL|function|add_new_color (gint bytes,const guchar * buffer,gint * cube,gint bucket_expo)
name|add_new_color
parameter_list|(
name|gint
name|bytes
parameter_list|,
specifier|const
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
name|g
operator|=
operator|(
name|bytes
operator|>
literal|1
operator|)
condition|?
name|buffer
index|[
literal|1
index|]
operator|>>
name|bucket_expo
else|:
literal|0
expr_stmt|;
name|b
operator|=
operator|(
name|bytes
operator|>
literal|2
operator|)
condition|?
name|buffer
index|[
literal|2
index|]
operator|>>
name|bucket_expo
else|:
literal|0
expr_stmt|;
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
name|gboolean
DECL|function|borderaverage_dialog (gint32 image_ID,GimpDrawable * drawable)
name|borderaverage_dialog
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
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
name|size_entry
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkSizeGroup
modifier|*
name|group
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gdouble
name|xres
decl_stmt|,
name|yres
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
literal|"Borderaverage"
argument_list|)
argument_list|,
name|PLUG_IN_BINARY
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|main_vbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
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
name|main_vbox
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
literal|6
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
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
name|group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|group
argument_list|)
expr_stmt|;
comment|/*  Get the image resolution and unit  */
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|xres
argument_list|,
operator|&
name|yres
argument_list|)
expr_stmt|;
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|size_entry
operator|=
name|gimp_size_entry_new
argument_list|(
literal|1
argument_list|,
name|unit
argument_list|,
literal|"%a"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|4
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|size_entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_unit
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_resolution
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|xres
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  set the size (in pixels) that will be treated as 0% and 100%  */
name|gimp_size_entry_set_size
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|,
name|drawable
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval_boundaries
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1.0
argument_list|,
literal|256.0
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|(
name|gdouble
operator|)
name|borderaverage_thickness
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|size_entry
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|thickness_callback
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|size_entry
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
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
name|main_vbox
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
literal|6
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
literal|"_Bucket size:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
name|gtk_size_group_add_widget
argument_list|(
name|group
argument_list|,
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

begin_function
specifier|static
name|void
DECL|function|thickness_callback (GtkWidget * widget,gpointer data)
name|thickness_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|borderaverage_thickness
operator|=
name|gimp_size_entry_get_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

