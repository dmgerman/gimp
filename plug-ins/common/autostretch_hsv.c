begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Autostretch HSV 0.10 --- image filter plug-in for The Gimp image  * manipulation program  *  * Copyright (C) 1997 Scott Goehring  * Copyright (C) 1996 Federico Mena Quintero  *  * You can contact me at scott@poverty.bloomington.in.us  * You can contact the original The Gimp authors at gimp@xcf.berkeley.edu  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This simple plug-in does an automatic contrast stretch.  For each    channel in the image, it finds the minimum and maximum values... it    uses those values to stretch the individual histograms to the full    contrast range.  For some images it may do just what you want; for    others it may be total crap :) This version operates in HSV space    and preserves hue, unlike the original Contrast Autostretch. */
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
file|<stdio.h>
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
name|autostretch_hsv
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
name|indexed_autostretch_hsv
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
decl_stmt|;
end_decl_stmt

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
literal|"Input drawable"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_autostretch_hsv"
argument_list|,
literal|"Automatically stretch the contrast of the specified "
literal|"drawable to cover all possible ranges."
argument_list|,
literal|"This simple plug-in does an automatic contrast "
literal|"stretch.  For each channel in the image, it finds "
literal|"the minimum and maximum values... it uses those "
literal|"values to stretch the individual histograms to the "
literal|"full contrast range.  For some images it may do "
literal|"just what you want; for others it may be total "
literal|"crap :).  This version differs from Contrast "
literal|"Autostretch in that it works in HSV space, and "
literal|"preserves hue."
argument_list|,
literal|"Scott Goehring and Federico Mena Quintero"
argument_list|,
literal|"Scott Goehring and Federico Mena Quintero"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"Stretch _HSV"
argument_list|)
argument_list|,
literal|"RGB*, INDEXED*"
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
literal|"plug_in_autostretch_hsv"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Layer/Colors/Auto"
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
literal|1
index|]
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
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
comment|/*  Make sure that the drawable is gray or RGB color  */
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
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Auto-Stretching HSV..."
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
name|autostretch_hsv
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|indexed_autostretch_hsv
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|GIMP_RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("autostretch_hsv: cannot operate on indexed color images"); */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|struct|__anon2bb98d600108
typedef|typedef
struct|struct
block|{
DECL|member|shi
name|double
name|shi
decl_stmt|;
DECL|member|slo
name|double
name|slo
decl_stmt|;
DECL|member|vhi
name|double
name|vhi
decl_stmt|;
DECL|member|vlo
name|double
name|vlo
decl_stmt|;
DECL|typedef|AutostretchData
block|}
name|AutostretchData
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|find_max (guchar * src,gint bpp,AutostretchData * data)
name|find_max
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|AutostretchData
modifier|*
name|data
parameter_list|)
block|{
name|double
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gimp_rgb_to_hsv4
argument_list|(
name|src
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|>
name|data
operator|->
name|shi
condition|)
name|data
operator|->
name|shi
operator|=
name|s
expr_stmt|;
if|if
condition|(
name|s
operator|<
name|data
operator|->
name|slo
condition|)
name|data
operator|->
name|slo
operator|=
name|s
expr_stmt|;
if|if
condition|(
name|v
operator|>
name|data
operator|->
name|vhi
condition|)
name|data
operator|->
name|vhi
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|v
operator|<
name|data
operator|->
name|vlo
condition|)
name|data
operator|->
name|vlo
operator|=
name|v
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|autostretch_hsv_func (guchar * src,guchar * dest,gint bpp,AutostretchData * data)
name|autostretch_hsv_func
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|AutostretchData
modifier|*
name|data
parameter_list|)
block|{
name|double
name|h
decl_stmt|,
name|s
decl_stmt|,
name|v
decl_stmt|;
name|gimp_rgb_to_hsv4
argument_list|(
name|src
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|s
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|shi
operator|!=
name|data
operator|->
name|slo
condition|)
name|s
operator|=
operator|(
name|s
operator|-
name|data
operator|->
name|slo
operator|)
operator|/
operator|(
name|data
operator|->
name|shi
operator|-
name|data
operator|->
name|slo
operator|)
expr_stmt|;
if|if
condition|(
name|data
operator|->
name|vhi
operator|!=
name|data
operator|->
name|vlo
condition|)
name|v
operator|=
operator|(
name|v
operator|-
name|data
operator|->
name|vlo
operator|)
operator|/
operator|(
name|data
operator|->
name|vhi
operator|-
name|data
operator|->
name|vlo
operator|)
expr_stmt|;
name|gimp_hsv_to_rgb4
argument_list|(
name|dest
argument_list|,
name|h
argument_list|,
name|s
argument_list|,
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
name|dest
index|[
literal|3
index|]
operator|=
name|src
index|[
literal|3
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_autostretch_hsv (gint32 image_ID)
name|indexed_autostretch_hsv
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
comment|/* a.d.m. */
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|AutostretchData
name|data
init|=
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|gint
name|ncols
decl_stmt|,
name|i
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_cmap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmap
operator|==
name|NULL
condition|)
block|{
name|fprintf
argument_list|(
name|stderr
argument_list|,
literal|"autostretch_hsv: cmap was NULL!  Quitting...\n"
argument_list|)
expr_stmt|;
name|gimp_quit
argument_list|()
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ncols
condition|;
name|i
operator|++
control|)
block|{
name|find_max
argument_list|(
operator|&
name|cmap
index|[
name|i
operator|*
literal|3
index|]
argument_list|,
literal|3
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ncols
condition|;
name|i
operator|++
control|)
block|{
name|autostretch_hsv_func
argument_list|(
operator|&
name|cmap
index|[
name|i
operator|*
literal|3
index|]
argument_list|,
operator|&
name|cmap
index|[
name|i
operator|*
literal|3
index|]
argument_list|,
literal|3
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_cmap
argument_list|(
name|image_ID
argument_list|,
name|cmap
argument_list|,
name|ncols
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|autostretch_hsv (GimpDrawable * drawable)
name|autostretch_hsv
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|AutostretchData
name|data
init|=
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
decl_stmt|;
name|gimp_rgn_iterate1
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|,
operator|(
name|GimpRgnFunc1
operator|)
name|find_max
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|,
operator|(
name|GimpRgnFunc2
operator|)
name|autostretch_hsv_func
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

