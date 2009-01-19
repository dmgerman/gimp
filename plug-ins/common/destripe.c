begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Destripe filter  *  * Copyright 1997 Marc Lehmann, heavily modified from a filter by  * Michael Sweet.  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  *  */
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
file|<libgimp/gimpui.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/*  * Constants...  */
end_comment

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-destripe"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"destripe"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"0.2"
end_define

begin_define
DECL|macro|SCALE_WIDTH
define|#
directive|define
name|SCALE_WIDTH
value|140
end_define

begin_define
DECL|macro|MAX_AVG
define|#
directive|define
name|MAX_AVG
value|100
end_define

begin_comment
comment|/*  * Local functions...  */
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
name|destripe
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|destripe_dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Globals...  */
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
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b2059070108
block|{
DECL|member|histogram
name|gboolean
name|histogram
decl_stmt|;
DECL|member|avg_width
name|gint
name|avg_width
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|DestripeValues
block|}
name|DestripeValues
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|vals
specifier|static
name|DestripeValues
name|vals
init|=
block|{
name|FALSE
block|,
comment|/* histogram     */
literal|36
block|,
comment|/* average width */
name|TRUE
comment|/* preview */
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
literal|"Input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"avg-width"
block|,
literal|"Averaging filter width (default = 36)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Remove vertical stripe artifacts from the image"
argument_list|)
argument_list|,
literal|"This plug-in tries to remove vertical stripes from "
literal|"an image."
argument_list|,
literal|"Marc Lehmann<pcg@goof.com>"
argument_list|,
literal|"Marc Lehmann<pcg@goof.com>"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"Des_tripe..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
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
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Filters/Enhance"
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
decl_stmt|;
comment|/* Current run mode */
name|GimpPDBStatusType
name|status
decl_stmt|;
comment|/* Return status */
specifier|static
name|GimpParam
name|values
index|[
literal|1
index|]
decl_stmt|;
comment|/* Return values */
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/*    * Initialize parameter data...    */
name|status
operator|=
name|GIMP_PDB_SUCCESS
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
comment|/*    * Get drawable information...    */
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
comment|/*    * See how we will run    */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
comment|/*        * Possibly retrieve data...        */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|vals
argument_list|)
expr_stmt|;
comment|/*        * Get information from the dialog...        */
if|if
condition|(
operator|!
name|destripe_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/*        * Make sure all the arguments are present...        */
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
else|else
name|vals
operator|.
name|avg_width
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
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/*        * Possibly retrieve data...        */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|vals
argument_list|)
expr_stmt|;
break|break;
default|default :
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
break|break;
block|}
empty_stmt|;
comment|/*    * Destripe the image...    */
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
if|if
condition|(
operator|(
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
operator|)
condition|)
block|{
comment|/*            * Set the tile cache size...            */
name|gimp_tile_cache_ntiles
argument_list|(
operator|(
name|drawable
operator|->
name|width
operator|+
name|gimp_tile_width
argument_list|()
operator|-
literal|1
operator|)
operator|/
name|gimp_tile_width
argument_list|()
argument_list|)
expr_stmt|;
comment|/*            * Run!            */
name|destripe
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*            * If run mode is interactive, flush displays...            */
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
comment|/*            * Store data...            */
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|vals
argument_list|,
sizeof|sizeof
argument_list|(
name|vals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
empty_stmt|;
comment|/*    * Reset the current run status...    */
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
comment|/*    * Detach from the drawable...    */
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
DECL|function|destripe (GimpDrawable * drawable,GimpPreview * preview)
name|destripe
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|;
comment|/* source image region */
name|GimpPixelRgn
name|dst_rgn
decl_stmt|;
comment|/* destination image region */
name|guchar
modifier|*
name|src_rows
decl_stmt|;
comment|/* image data */
name|gdouble
name|progress
decl_stmt|,
name|progress_inc
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
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|glong
modifier|*
name|hist
decl_stmt|,
modifier|*
name|corr
decl_stmt|;
comment|/* "histogram" data */
name|gint
name|tile_width
init|=
name|gimp_tile_width
argument_list|()
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|x
decl_stmt|,
name|y
decl_stmt|,
name|ox
decl_stmt|,
name|cols
decl_stmt|;
comment|/* initialize */
name|progress
operator|=
literal|0.0
expr_stmt|;
name|progress_inc
operator|=
literal|0.0
expr_stmt|;
comment|/*    * Let the user know what we're doing...    */
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|)
expr_stmt|;
name|gimp_preview_get_size
argument_list|(
name|preview
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|x1
operator|+
name|width
expr_stmt|;
name|y2
operator|=
name|y1
operator|+
name|height
expr_stmt|;
block|}
else|else
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Destriping"
argument_list|)
argument_list|)
expr_stmt|;
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
name|width
operator|=
name|x2
operator|-
name|x1
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y1
expr_stmt|;
name|progress
operator|=
literal|0
expr_stmt|;
name|progress_inc
operator|=
literal|0.5
operator|*
name|tile_width
operator|/
name|width
expr_stmt|;
block|}
comment|/*    * Setup for filter...    */
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
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
name|dst_rgn
argument_list|,
name|drawable
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|(
name|preview
operator|==
name|NULL
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|hist
operator|=
name|g_new
argument_list|(
name|long
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|corr
operator|=
name|g_new
argument_list|(
name|long
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|src_rows
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|tile_width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|hist
argument_list|,
literal|0
argument_list|,
name|width
operator|*
name|bpp
operator|*
sizeof|sizeof
argument_list|(
name|long
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    * collect "histogram" data.    */
for|for
control|(
name|ox
operator|=
name|x1
init|;
name|ox
operator|<
name|x2
condition|;
name|ox
operator|+=
name|tile_width
control|)
block|{
name|guchar
modifier|*
name|rows
init|=
name|src_rows
decl_stmt|;
name|cols
operator|=
name|x2
operator|-
name|ox
expr_stmt|;
if|if
condition|(
name|cols
operator|>
name|tile_width
condition|)
name|cols
operator|=
name|tile_width
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|rows
argument_list|,
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
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
name|long
modifier|*
name|h
init|=
name|hist
operator|+
operator|(
name|ox
operator|-
name|x1
operator|)
operator|*
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|row_end
init|=
name|rows
operator|+
name|cols
operator|*
name|bpp
decl_stmt|;
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
operator|*
name|h
operator|++
operator|+=
operator|*
name|rows
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
expr_stmt|;
block|}
comment|/*    * average out histogram    */
block|{
name|gint
name|extend
init|=
operator|(
name|vals
operator|.
name|avg_width
operator|/
literal|2
operator|)
operator|*
name|bpp
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|MIN
argument_list|(
literal|3
argument_list|,
name|bpp
argument_list|)
condition|;
name|i
operator|++
control|)
block|{
name|long
modifier|*
name|h
init|=
name|hist
operator|-
name|extend
operator|+
name|i
decl_stmt|;
name|long
modifier|*
name|c
init|=
name|corr
operator|-
name|extend
operator|+
name|i
decl_stmt|;
name|long
name|sum
init|=
literal|0
decl_stmt|;
name|gint
name|cnt
init|=
literal|0
decl_stmt|;
for|for
control|(
name|x
operator|=
operator|-
name|extend
init|;
name|x
operator|<
name|width
operator|*
name|bpp
condition|;
name|x
operator|+=
name|bpp
control|)
block|{
if|if
condition|(
name|x
operator|+
name|extend
operator|<
name|width
operator|*
name|bpp
condition|)
block|{
name|sum
operator|+=
name|h
index|[
name|extend
index|]
expr_stmt|;
name|cnt
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|-
name|extend
operator|>=
literal|0
condition|)
block|{
name|sum
operator|-=
name|h
index|[
operator|-
name|extend
index|]
expr_stmt|;
name|cnt
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
operator|*
name|h
condition|)
operator|*
name|c
operator|=
operator|(
operator|(
name|sum
operator|/
name|cnt
operator|-
operator|*
name|h
operator|)
operator|<<
literal|10
operator|)
operator|/
operator|*
name|h
expr_stmt|;
else|else
operator|*
name|c
operator|=
name|G_MAXINT
expr_stmt|;
block|}
name|h
operator|+=
name|bpp
expr_stmt|;
name|c
operator|+=
name|bpp
expr_stmt|;
block|}
block|}
block|}
comment|/*    * remove stripes.    */
for|for
control|(
name|ox
operator|=
name|x1
init|;
name|ox
operator|<
name|x2
condition|;
name|ox
operator|+=
name|tile_width
control|)
block|{
name|guchar
modifier|*
name|rows
init|=
name|src_rows
decl_stmt|;
name|cols
operator|=
name|x2
operator|-
name|ox
expr_stmt|;
if|if
condition|(
name|cols
operator|>
name|tile_width
condition|)
name|cols
operator|=
name|tile_width
expr_stmt|;
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|rows
argument_list|,
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
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
name|long
modifier|*
name|c
init|=
name|corr
operator|+
operator|(
name|ox
operator|-
name|x1
operator|)
operator|*
name|bpp
decl_stmt|;
name|guchar
modifier|*
name|row_end
init|=
name|rows
operator|+
name|cols
operator|*
name|bpp
decl_stmt|;
if|if
condition|(
name|vals
operator|.
name|histogram
condition|)
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
block|{
operator|*
name|rows
operator|=
name|MIN
argument_list|(
literal|255
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
literal|128
operator|+
operator|(
operator|*
name|rows
operator|*
operator|*
name|c
operator|>>
literal|10
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
name|rows
operator|++
expr_stmt|;
block|}
else|else
while|while
condition|(
name|rows
operator|<
name|row_end
condition|)
block|{
operator|*
name|rows
operator|=
name|MIN
argument_list|(
literal|255
argument_list|,
name|MAX
argument_list|(
literal|0
argument_list|,
operator|*
name|rows
operator|+
operator|(
operator|*
name|rows
operator|*
operator|*
name|c
operator|>>
literal|10
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|++
expr_stmt|;
name|rows
operator|++
expr_stmt|;
block|}
block|}
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dst_rgn
argument_list|,
name|src_rows
argument_list|,
name|ox
argument_list|,
name|y1
argument_list|,
name|cols
argument_list|,
name|height
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|preview
condition|)
name|gimp_progress_update
argument_list|(
name|progress
operator|+=
name|progress_inc
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|src_rows
argument_list|)
expr_stmt|;
comment|/*    * Update the screen...    */
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_drawable_preview_draw_region
argument_list|(
name|GIMP_DRAWABLE_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|dst_rgn
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|x1
argument_list|,
name|y1
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|hist
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|corr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|destripe_dialog (GimpDrawable * drawable)
name|destripe_dialog
parameter_list|(
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
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkObject
modifier|*
name|adj
decl_stmt|;
name|gboolean
name|run
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
literal|"Destripe"
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
name|gimp_window_set_transient
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
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
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
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
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|destripe
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
name|SCALE_WIDTH
argument_list|,
literal|0
argument_list|,
name|vals
operator|.
name|avg_width
argument_list|,
literal|2
argument_list|,
name|MAX_AVG
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_int_adjustment_update
argument_list|)
argument_list|,
operator|&
name|vals
operator|.
name|avg_width
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Create _histogram"
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
name|button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|vals
operator|.
name|histogram
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|vals
operator|.
name|histogram
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
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

end_unit

