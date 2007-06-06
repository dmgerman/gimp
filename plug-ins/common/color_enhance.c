begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Color Enhance 0.10 --- image filter plug-in for GIMP  *  * Copyright (C) 1999 Martin Weber  * Copyright (C) 1996 Federico Mena Quintero  *  * You can contact me at martweb@gmx.net  * You can contact the original GIMP authors at gimp@xcf.berkeley.edu  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-color-enhance"
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
name|Color_Enhance
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
name|indexed_Color_Enhance
parameter_list|(
name|gint32
name|image_ID
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
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Stretch color saturation to cover maximum possible range"
argument_list|)
argument_list|,
literal|"This simple plug-in does an automatic saturation "
literal|"stretch.  For each channel in the image, it finds "
literal|"the minimum and maximum values... it uses those "
literal|"values to stretch the individual histograms to the "
literal|"full range.  For some images it may do just what "
literal|"you want; for others it may not work that well.  "
literal|"This version differs from Contrast Autostretch in "
literal|"that it works in HSV space, and preserves hue."
argument_list|,
literal|"Martin Weber"
argument_list|,
literal|"Martin Weber"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Color Enhance"
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Colors/Auto"
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
name|GimpRunMode
name|run_mode
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
literal|"Color Enhance"
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
name|Color_Enhance
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
name|indexed_Color_Enhance
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

begin_function
specifier|static
name|gdouble
DECL|function|get_v (const guchar * src)
name|get_v
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|)
block|{
name|gdouble
name|h
decl_stmt|,
name|z
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|k
decl_stmt|;
name|guchar
name|map
index|[
literal|3
index|]
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|src
index|[
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|src
index|[
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|src
index|[
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|map
index|[
literal|0
index|]
operator|=
name|c
operator|-
name|k
expr_stmt|;
name|map
index|[
literal|1
index|]
operator|=
name|m
operator|-
name|k
expr_stmt|;
name|map
index|[
literal|2
index|]
operator|=
name|y
operator|-
name|k
expr_stmt|;
name|gimp_rgb_to_hsv4
argument_list|(
name|map
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|z
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
return|return
name|v
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|enhance_it (const guchar * src,guchar * dest,gdouble vlo,gdouble vhi)
name|enhance_it
parameter_list|(
specifier|const
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gdouble
name|vlo
parameter_list|,
name|gdouble
name|vhi
parameter_list|)
block|{
name|gdouble
name|h
decl_stmt|,
name|z
decl_stmt|,
name|v
decl_stmt|;
name|gint
name|c
decl_stmt|,
name|m
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|k
decl_stmt|;
name|guchar
name|map
index|[
literal|3
index|]
decl_stmt|;
name|c
operator|=
literal|255
operator|-
name|src
index|[
literal|0
index|]
expr_stmt|;
name|m
operator|=
literal|255
operator|-
name|src
index|[
literal|1
index|]
expr_stmt|;
name|y
operator|=
literal|255
operator|-
name|src
index|[
literal|2
index|]
expr_stmt|;
name|k
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|m
operator|<
name|k
condition|)
name|k
operator|=
name|m
expr_stmt|;
if|if
condition|(
name|y
operator|<
name|k
condition|)
name|k
operator|=
name|y
expr_stmt|;
name|map
index|[
literal|0
index|]
operator|=
name|c
operator|-
name|k
expr_stmt|;
name|map
index|[
literal|1
index|]
operator|=
name|m
operator|-
name|k
expr_stmt|;
name|map
index|[
literal|2
index|]
operator|=
name|y
operator|-
name|k
expr_stmt|;
name|gimp_rgb_to_hsv4
argument_list|(
name|map
argument_list|,
operator|&
name|h
argument_list|,
operator|&
name|z
argument_list|,
operator|&
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|vhi
operator|!=
name|vlo
condition|)
name|v
operator|=
operator|(
name|v
operator|-
name|vlo
operator|)
operator|/
operator|(
name|vhi
operator|-
name|vlo
operator|)
expr_stmt|;
name|gimp_hsv_to_rgb4
argument_list|(
name|map
argument_list|,
name|h
argument_list|,
name|z
argument_list|,
name|v
argument_list|)
expr_stmt|;
name|c
operator|=
name|map
index|[
literal|0
index|]
expr_stmt|;
name|m
operator|=
name|map
index|[
literal|1
index|]
expr_stmt|;
name|y
operator|=
name|map
index|[
literal|2
index|]
expr_stmt|;
name|c
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|c
operator|>
literal|255
condition|)
name|c
operator|=
literal|255
expr_stmt|;
name|m
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|m
operator|>
literal|255
condition|)
name|m
operator|=
literal|255
expr_stmt|;
name|y
operator|+=
name|k
expr_stmt|;
if|if
condition|(
name|y
operator|>
literal|255
condition|)
name|y
operator|=
literal|255
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
literal|255
operator|-
name|c
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
literal|255
operator|-
name|m
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
literal|255
operator|-
name|y
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|indexed_Color_Enhance (gint32 image_ID)
name|indexed_Color_Enhance
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|guchar
modifier|*
name|cmap
decl_stmt|;
name|gint
name|ncols
decl_stmt|,
name|i
decl_stmt|;
name|gdouble
name|vhi
init|=
literal|0.0
decl_stmt|,
name|vlo
init|=
literal|1.0
decl_stmt|;
name|cmap
operator|=
name|gimp_image_get_colormap
argument_list|(
name|image_ID
argument_list|,
operator|&
name|ncols
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|cmap
condition|)
block|{
name|g_message
argument_list|(
literal|"colormap was NULL!  Quitting."
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
name|gdouble
name|v
init|=
name|get_v
argument_list|(
operator|&
name|cmap
index|[
literal|3
operator|*
name|i
index|]
argument_list|)
decl_stmt|;
if|if
condition|(
name|v
operator|>
name|vhi
condition|)
name|vhi
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|v
operator|<
name|vlo
condition|)
name|vlo
operator|=
name|v
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
name|enhance_it
argument_list|(
operator|&
name|cmap
index|[
literal|3
operator|*
name|i
index|]
argument_list|,
operator|&
name|cmap
index|[
literal|3
operator|*
name|i
index|]
argument_list|,
name|vlo
argument_list|,
name|vhi
argument_list|)
expr_stmt|;
block|}
name|gimp_image_set_colormap
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c7439a10108
block|{
DECL|member|vhi
name|gdouble
name|vhi
decl_stmt|;
DECL|member|vlo
name|gdouble
name|vlo
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|typedef|ColorEnhanceParam_t
block|}
name|ColorEnhanceParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|find_vhi_vlo (const guchar * src,gint bpp,gpointer data)
name|find_vhi_vlo
parameter_list|(
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
name|ColorEnhanceParam_t
modifier|*
name|param
init|=
operator|(
name|ColorEnhanceParam_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
operator|!
name|param
operator|->
name|has_alpha
operator|||
name|src
index|[
literal|3
index|]
condition|)
block|{
name|gdouble
name|v
init|=
name|get_v
argument_list|(
name|src
argument_list|)
decl_stmt|;
if|if
condition|(
name|v
operator|>
name|param
operator|->
name|vhi
condition|)
name|param
operator|->
name|vhi
operator|=
name|v
expr_stmt|;
if|if
condition|(
name|v
operator|<
name|param
operator|->
name|vlo
condition|)
name|param
operator|->
name|vlo
operator|=
name|v
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_enhance_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|color_enhance_func
parameter_list|(
specifier|const
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
name|gpointer
name|data
parameter_list|)
block|{
name|ColorEnhanceParam_t
modifier|*
name|param
init|=
operator|(
name|ColorEnhanceParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|enhance_it
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|param
operator|->
name|vlo
argument_list|,
name|param
operator|->
name|vhi
argument_list|)
expr_stmt|;
if|if
condition|(
name|param
operator|->
name|has_alpha
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
DECL|function|Color_Enhance (GimpDrawable * drawable)
name|Color_Enhance
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|ColorEnhanceParam_t
name|param
decl_stmt|;
name|param
operator|.
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|param
operator|.
name|vhi
operator|=
literal|0.0
expr_stmt|;
name|param
operator|.
name|vlo
operator|=
literal|1.0
expr_stmt|;
name|gimp_rgn_iterate1
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|find_vhi_vlo
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|color_enhance_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

