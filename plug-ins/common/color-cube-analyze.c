begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
end_comment

begin_comment
comment|/*  * Analyze colorcube.  *  * Author: robert@experimental.net  */
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
file|<glib/gstdio.h>
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
value|"plug-in-ccanalyze"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"color-cube-analyze"
end_define

begin_define
DECL|macro|PLUG_IN_ROLE
define|#
directive|define
name|PLUG_IN_ROLE
value|"gimp-color-cube-analyze"
end_define

begin_comment
comment|/* size of histogram image */
end_comment

begin_define
DECL|macro|PREWIDTH
define|#
directive|define
name|PREWIDTH
value|256
end_define

begin_define
DECL|macro|PREHEIGHT
define|#
directive|define
name|PREHEIGHT
value|150
end_define

begin_comment
comment|/* lets prototype */
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
name|n_params
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
name|doDialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|analyze
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
name|histogram
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|gdouble
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|fillPreview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|insertcolor
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|gdouble
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|doLabel
parameter_list|(
name|GtkWidget
modifier|*
name|table
parameter_list|,
specifier|const
name|char
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
function_decl|G_GNUC_PRINTF
parameter_list|(
function_decl|2
operator|,
function_decl|3
end_function_decl

begin_empty_stmt
unit|)
empty_stmt|;
end_empty_stmt

begin_comment
comment|/* some global variables */
end_comment

begin_decl_stmt
DECL|variable|width
DECL|variable|height
DECL|variable|bpp
specifier|static
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|hist_red
DECL|variable|hist_green
DECL|variable|hist_blue
specifier|static
name|gdouble
name|hist_red
index|[
literal|256
index|]
decl_stmt|,
name|hist_green
index|[
literal|256
index|]
decl_stmt|,
name|hist_blue
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|maxred
DECL|variable|maxgreen
DECL|variable|maxblue
specifier|static
name|gdouble
name|maxred
init|=
literal|0.0
decl_stmt|,
name|maxgreen
init|=
literal|0.0
decl_stmt|,
name|maxblue
init|=
literal|0.0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|uniques
specifier|static
name|gint
name|uniques
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|imageID
specifier|static
name|gint32
name|imageID
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* lets declare what we want to do */
end_comment

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

begin_comment
comment|/* run program */
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_comment
comment|/* tell GIMP who we are */
end_comment

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
literal|"Input drawable"
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
literal|"num-colors"
block|,
literal|"Number of colors in the image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Analyze the set of colors in the image"
argument_list|)
argument_list|,
literal|"Analyze colorcube and print some information about "
literal|"the current image (also displays a color-histogram)"
argument_list|,
literal|"robert@experimental.net"
argument_list|,
literal|"robert@experimental.net"
argument_list|,
literal|"June 20th, 1997"
argument_list|,
name|N_
argument_list|(
literal|"Colorcube A_nalysis..."
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
literal|"<Image>/Colors/Info"
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* main function */
end_comment

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint n_params,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|n_params
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
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
name|INIT_I18N
argument_list|()
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
operator|*
name|return_vals
operator|=
name|values
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_NONINTERACTIVE
condition|)
block|{
if|if
condition|(
name|n_params
operator|!=
literal|3
condition|)
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
name|imageID
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
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|memset
argument_list|(
name|hist_red
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|hist_red
argument_list|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|hist_green
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|hist_green
argument_list|)
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|hist_blue
argument_list|,
literal|0
argument_list|,
sizeof|sizeof
argument_list|(
name|hist_blue
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
name|analyze
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
comment|/* show dialog after we analyzed image */
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|doDialog
argument_list|()
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
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
name|uniques
expr_stmt|;
block|}
end_function

begin_comment
comment|/* do the analyzing */
end_comment

begin_function
specifier|static
name|void
DECL|function|analyze (GimpDrawable * drawable)
name|analyze
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|;
name|guchar
modifier|*
name|src_row
decl_stmt|,
modifier|*
name|cmap
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|numcol
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|guchar
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|a
decl_stmt|;
name|guchar
name|idx
decl_stmt|;
name|gboolean
name|gray
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|gboolean
name|has_sel
decl_stmt|;
name|guchar
modifier|*
name|sel
decl_stmt|;
name|GimpPixelRgn
name|selPR
decl_stmt|;
name|gint
name|ofsx
decl_stmt|,
name|ofsy
decl_stmt|;
name|GimpDrawable
modifier|*
name|selDrawable
decl_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Colorcube Analysis"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_drawable_mask_intersect
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
name|w
argument_list|,
operator|&
name|h
argument_list|)
condition|)
return|return;
name|x2
operator|=
name|x1
operator|+
name|w
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|h
expr_stmt|;
comment|/*    * Get the size of the input image (this will/must be the same    * as the size of the output image).    */
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
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|has_sel
operator|=
operator|!
name|gimp_selection_is_empty
argument_list|(
name|imageID
argument_list|)
expr_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|ofsx
argument_list|,
operator|&
name|ofsy
argument_list|)
expr_stmt|;
comment|/* initialize the pixel region */
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
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|imageID
argument_list|,
operator|&
name|numcol
argument_list|)
expr_stmt|;
name|gray
operator|=
operator|(
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|||
name|gimp_item_is_channel
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|)
expr_stmt|;
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|selDrawable
operator|=
name|gimp_drawable_get
argument_list|(
name|gimp_image_get_selection
argument_list|(
name|imageID
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|selPR
argument_list|,
name|selDrawable
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
comment|/* allocate row buffer */
name|src_row
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
name|bpp
argument_list|)
expr_stmt|;
name|sel
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
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
name|src_row
argument_list|,
name|x1
argument_list|,
name|y
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
name|has_sel
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|selPR
argument_list|,
name|sel
argument_list|,
name|x1
operator|+
name|ofsx
argument_list|,
name|y
operator|+
name|ofsy
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
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|w
condition|;
name|x
operator|++
control|)
block|{
comment|/* Start with full opacity.  */
name|a
operator|=
literal|255
expr_stmt|;
comment|/*            * If the image is indexed, fetch RGB values            * from colormap.            */
if|if
condition|(
name|cmap
condition|)
block|{
name|idx
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
index|]
expr_stmt|;
name|r
operator|=
name|cmap
index|[
name|idx
operator|*
literal|3
index|]
expr_stmt|;
name|g
operator|=
name|cmap
index|[
name|idx
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|cmap
index|[
name|idx
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|a
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
operator|+
literal|1
index|]
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gray
condition|)
block|{
name|r
operator|=
name|g
operator|=
name|b
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|a
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
operator|+
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|r
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
index|]
expr_stmt|;
name|g
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
operator|+
literal|1
index|]
expr_stmt|;
name|b
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|a
operator|=
name|src_row
index|[
name|x
operator|*
name|bpp
operator|+
literal|3
index|]
expr_stmt|;
block|}
if|if
condition|(
name|has_sel
condition|)
name|a
operator|*=
name|sel
index|[
name|x
index|]
expr_stmt|;
else|else
name|a
operator|*=
literal|255
expr_stmt|;
if|if
condition|(
name|a
operator|!=
literal|0
condition|)
name|insertcolor
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
operator|(
name|gdouble
operator|)
name|a
operator|*
operator|(
literal|1.0
operator|/
operator|(
literal|255.0
operator|*
literal|255.0
operator|)
operator|)
argument_list|)
expr_stmt|;
block|}
comment|/* tell the user what we're doing */
if|if
condition|(
operator|(
name|y
operator|%
literal|10
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|gdouble
operator|)
name|y
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
comment|/* clean up */
name|gimp_drawable_detach
argument_list|(
name|selDrawable
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src_row
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|insertcolor (guchar r,guchar g,guchar b,gdouble a)
name|insertcolor
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
specifier|static
name|GHashTable
modifier|*
name|hash_table
decl_stmt|;
name|guint
name|key
decl_stmt|;
if|if
condition|(
operator|!
name|hash_table
condition|)
name|hash_table
operator|=
name|g_hash_table_new
argument_list|(
name|g_direct_hash
argument_list|,
name|g_direct_equal
argument_list|)
expr_stmt|;
name|histogram
argument_list|(
name|r
argument_list|,
name|g
argument_list|,
name|b
argument_list|,
name|a
argument_list|)
expr_stmt|;
name|key
operator|=
name|r
operator|+
literal|256
operator|*
operator|(
name|g
operator|+
literal|256
operator|*
name|b
operator|)
expr_stmt|;
if|if
condition|(
name|g_hash_table_lookup
argument_list|(
name|hash_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|key
argument_list|)
argument_list|)
condition|)
block|{
return|return;
block|}
name|g_hash_table_insert
argument_list|(
name|hash_table
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|key
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|uniques
operator|++
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * Update RGB count, and keep track of maximum values (which aren't used  * anywhere as of yet, but they might be useful sometime).  */
end_comment

begin_function
specifier|static
name|void
DECL|function|histogram (guchar r,guchar g,guchar b,gdouble a)
name|histogram
parameter_list|(
name|guchar
name|r
parameter_list|,
name|guchar
name|g
parameter_list|,
name|guchar
name|b
parameter_list|,
name|gdouble
name|a
parameter_list|)
block|{
name|hist_red
index|[
name|r
index|]
operator|+=
name|a
expr_stmt|;
name|hist_green
index|[
name|g
index|]
operator|+=
name|a
expr_stmt|;
name|hist_blue
index|[
name|b
index|]
operator|+=
name|a
expr_stmt|;
if|if
condition|(
name|hist_red
index|[
name|r
index|]
operator|>
name|maxred
condition|)
name|maxred
operator|=
name|hist_red
index|[
name|r
index|]
expr_stmt|;
if|if
condition|(
name|hist_green
index|[
name|g
index|]
operator|>
name|maxgreen
condition|)
name|maxgreen
operator|=
name|hist_green
index|[
name|g
index|]
expr_stmt|;
if|if
condition|(
name|hist_blue
index|[
name|b
index|]
operator|>
name|maxblue
condition|)
name|maxblue
operator|=
name|hist_blue
index|[
name|b
index|]
expr_stmt|;
block|}
end_function

begin_comment
comment|/* show our results */
end_comment

begin_function
specifier|static
name|void
DECL|function|doDialog (void)
name|doDialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Colorcube Analysis"
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
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
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
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
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
name|vbox
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
comment|/* use preview for histogram window */
name|preview
operator|=
name|gimp_preview_area_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|preview
argument_list|,
name|PREWIDTH
argument_list|,
name|PREHEIGHT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
comment|/* output results */
name|doLabel
argument_list|(
name|vbox
argument_list|,
name|_
argument_list|(
literal|"Image dimensions: %d Ã %d"
argument_list|)
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
name|uniques
operator|==
literal|0
condition|)
name|doLabel
argument_list|(
name|vbox
argument_list|,
name|_
argument_list|(
literal|"No colors"
argument_list|)
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|uniques
operator|==
literal|1
condition|)
name|doLabel
argument_list|(
name|vbox
argument_list|,
name|_
argument_list|(
literal|"Only one unique color"
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|doLabel
argument_list|(
name|vbox
argument_list|,
name|_
argument_list|(
literal|"Number of unique colors: %d"
argument_list|)
argument_list|,
name|uniques
argument_list|)
expr_stmt|;
comment|/* show stuff */
name|gtk_widget_show_all
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
name|fillPreview
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* shortcut */
end_comment

begin_function
specifier|static
name|void
DECL|function|doLabel (GtkWidget * vbox,const gchar * format,...)
name|doLabel
parameter_list|(
name|GtkWidget
modifier|*
name|vbox
parameter_list|,
specifier|const
name|gchar
modifier|*
name|format
parameter_list|,
modifier|...
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|format
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_vprintf
argument_list|(
name|format
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|text
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
name|vbox
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
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* fill our preview image with the color-histogram */
end_comment

begin_function
specifier|static
name|void
DECL|function|fillPreview (GtkWidget * preview)
name|fillPreview
parameter_list|(
name|GtkWidget
modifier|*
name|preview
parameter_list|)
block|{
name|guchar
modifier|*
name|image
decl_stmt|,
modifier|*
name|column
decl_stmt|,
modifier|*
name|pixel
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|rowstride
decl_stmt|;
name|gdouble
name|histcount
decl_stmt|,
name|val
decl_stmt|;
name|rowstride
operator|=
name|PREWIDTH
operator|*
literal|3
expr_stmt|;
name|image
operator|=
name|g_new0
argument_list|(
name|guchar
argument_list|,
name|PREWIDTH
operator|*
name|rowstride
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
operator|,
name|column
operator|=
name|image
init|;
name|x
operator|<
name|PREWIDTH
condition|;
name|x
operator|++
operator|,
name|column
operator|+=
literal|3
control|)
block|{
comment|/*        * For every channel, calculate a logarithmic value, scale it,        * and build a one-pixel bar.        *  ... in the respective channel, preserving the other ones. --hb        */
name|histcount
operator|=
name|hist_red
index|[
name|x
index|]
operator|>
literal|1.0
condition|?
name|hist_red
index|[
name|x
index|]
else|:
literal|1.0
expr_stmt|;
name|val
operator|=
name|log
argument_list|(
name|histcount
argument_list|)
operator|*
operator|(
name|PREHEIGHT
operator|/
literal|12
operator|)
expr_stmt|;
if|if
condition|(
name|val
operator|>
name|PREHEIGHT
condition|)
name|val
operator|=
name|PREHEIGHT
expr_stmt|;
name|y
operator|=
name|PREHEIGHT
operator|-
literal|1
expr_stmt|;
name|pixel
operator|=
name|column
operator|+
operator|(
name|y
operator|*
name|rowstride
operator|)
expr_stmt|;
for|for
control|(
init|;
name|y
operator|>
operator|(
name|PREHEIGHT
operator|-
name|val
operator|)
condition|;
name|y
operator|--
control|)
block|{
name|pixel
index|[
literal|0
index|]
operator|=
literal|255
expr_stmt|;
name|pixel
operator|-=
name|rowstride
expr_stmt|;
block|}
name|histcount
operator|=
name|hist_green
index|[
name|x
index|]
operator|>
literal|1.0
condition|?
name|hist_green
index|[
name|x
index|]
else|:
literal|1.0
expr_stmt|;
name|val
operator|=
name|log
argument_list|(
name|histcount
argument_list|)
operator|*
operator|(
name|PREHEIGHT
operator|/
literal|12
operator|)
expr_stmt|;
if|if
condition|(
name|val
operator|>
name|PREHEIGHT
condition|)
name|val
operator|=
name|PREHEIGHT
expr_stmt|;
name|y
operator|=
name|PREHEIGHT
operator|-
literal|1
expr_stmt|;
name|pixel
operator|=
name|column
operator|+
operator|(
name|y
operator|*
name|rowstride
operator|)
expr_stmt|;
for|for
control|(
init|;
name|y
operator|>
operator|(
name|PREHEIGHT
operator|-
name|val
operator|)
condition|;
name|y
operator|--
control|)
block|{
name|pixel
index|[
literal|1
index|]
operator|=
literal|255
expr_stmt|;
name|pixel
operator|-=
name|rowstride
expr_stmt|;
block|}
name|histcount
operator|=
name|hist_blue
index|[
name|x
index|]
operator|>
literal|1.0
condition|?
name|hist_blue
index|[
name|x
index|]
else|:
literal|1.0
expr_stmt|;
name|val
operator|=
name|log
argument_list|(
name|histcount
argument_list|)
operator|*
operator|(
name|PREHEIGHT
operator|/
literal|12
operator|)
expr_stmt|;
if|if
condition|(
name|val
operator|>
name|PREHEIGHT
condition|)
name|val
operator|=
name|PREHEIGHT
expr_stmt|;
name|y
operator|=
name|PREHEIGHT
operator|-
literal|1
expr_stmt|;
name|pixel
operator|=
name|column
operator|+
operator|(
name|y
operator|*
name|rowstride
operator|)
expr_stmt|;
for|for
control|(
init|;
name|y
operator|>
operator|(
name|PREHEIGHT
operator|-
name|val
operator|)
condition|;
name|y
operator|--
control|)
block|{
name|pixel
index|[
literal|2
index|]
operator|=
literal|255
expr_stmt|;
name|pixel
operator|-=
name|rowstride
expr_stmt|;
block|}
block|}
comment|/* move our data into the preview image */
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|PREWIDTH
argument_list|,
name|PREHEIGHT
argument_list|,
name|GIMP_RGB_IMAGE
argument_list|,
name|image
argument_list|,
literal|3
operator|*
name|PREWIDTH
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

