begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * illusion.c  -- This is a plug-in for the GIMP 1.0  *  * Copyright (C) 1997  Hirotsuna Mizuno  *                     s1041150@u-aizu.ac.jp  *  * Preview and new mode added May 2000 by tim copperfield  * 		       timecop@japan.co.jp  * 		       http://www.ne.jp/asahi/linux/timecop  *  * This program is free software; you can redistribute it and/or modify it  * under the terms of the GNU General Public License as published by the Free  * Software Foundation; either version 2 of the License, or (at your option)  * any later version.  *  * This program is distributed in the hope that it will be useful, but WITHOUT  * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or  * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  * more details.  *  * You should have received a copy of the GNU General Public License along with  * this program; if not, write to the Free Software Foundation, Inc.,  * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
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
file|<string.h>
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

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_illusion"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"v0.8 (May 14 2000)"
end_define

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
name|nparam
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
name|filter
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
name|filter_preview
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon296aced70108
block|{
DECL|member|division
name|gint32
name|division
decl_stmt|;
DECL|member|type1
name|gint
name|type1
decl_stmt|;
DECL|member|type2
name|gint
name|type2
decl_stmt|;
DECL|typedef|IllValues
block|}
name|IllValues
typedef|;
end_typedef

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
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parameters
specifier|static
name|IllValues
name|parameters
init|=
block|{
literal|8
block|,
comment|/* division */
literal|1
block|,
comment|/* type 1 */
literal|0
comment|/* type 2 */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|preview
specifier|static
name|GimpFixMePreview
modifier|*
name|preview
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
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
literal|"interactive / non-interactive"
block|}
block|,
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"input image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"input drawable"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"division"
block|,
literal|"the number of divisions"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"type"
block|,
literal|"illusion type (0=type1, 1=type2)"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"produce illusion"
argument_list|,
literal|"produce illusion"
argument_list|,
literal|"Hirotsuna Mizuno<s1041150@u-aizu.ac.jp>"
argument_list|,
literal|"Hirotsuna Mizuno"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Map/_Illusion..."
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (const gchar * name,gint nparams,const GimpParam * params,gint * nreturn_vals,GimpParam ** return_vals)
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
name|params
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
specifier|static
name|GimpParam
name|returnv
index|[
literal|1
index|]
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|run_mode
operator|=
name|params
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|params
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_drawable
argument_list|)
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|1
expr_stmt|;
operator|*
name|return_vals
operator|=
name|returnv
expr_stmt|;
comment|/* get the drawable info */
comment|/* switch the run mode */
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
name|PLUG_IN_NAME
argument_list|,
operator|&
name|parameters
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|parameters
argument_list|,
sizeof|sizeof
argument_list|(
name|IllValues
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_fixme_preview_free
argument_list|(
name|preview
argument_list|)
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
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|parameters
operator|.
name|division
operator|=
name|params
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|params
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_int32
operator|==
literal|0
condition|)
block|{
name|parameters
operator|.
name|type1
operator|=
literal|1
expr_stmt|;
name|parameters
operator|.
name|type2
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|parameters
operator|.
name|type1
operator|=
literal|0
expr_stmt|;
name|parameters
operator|.
name|type2
operator|=
literal|1
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|parameters
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
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
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Illusion..."
argument_list|)
argument_list|)
expr_stmt|;
name|filter
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
else|else
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
name|returnv
index|[
literal|0
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STATUS
expr_stmt|;
name|returnv
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
DECL|struct|__anon296aced70208
typedef|typedef
struct|struct
block|{
DECL|member|pft
name|GimpPixelFetcher
modifier|*
name|pft
decl_stmt|;
DECL|member|center_x
name|gdouble
name|center_x
decl_stmt|;
DECL|member|center_y
name|gdouble
name|center_y
decl_stmt|;
DECL|member|scale
name|gdouble
name|scale
decl_stmt|;
DECL|member|offset
name|gdouble
name|offset
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|typedef|IllusionParam_t
block|}
name|IllusionParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|illusion_func (gint x,gint y,const guchar * src,guchar * dest,gint bpp,gpointer data)
name|illusion_func
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
name|IllusionParam_t
modifier|*
name|param
init|=
operator|(
name|IllusionParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|xx
decl_stmt|,
name|yy
decl_stmt|,
name|b
decl_stmt|;
name|gdouble
name|radius
decl_stmt|,
name|cx
decl_stmt|,
name|cy
decl_stmt|,
name|angle
decl_stmt|;
name|guchar
name|pixel
index|[
literal|4
index|]
decl_stmt|;
name|cy
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|y
operator|-
name|param
operator|->
name|center_y
operator|)
operator|/
name|param
operator|->
name|scale
expr_stmt|;
name|cx
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|x
operator|-
name|param
operator|->
name|center_x
operator|)
operator|/
name|param
operator|->
name|scale
expr_stmt|;
name|angle
operator|=
name|floor
argument_list|(
name|atan2
argument_list|(
name|cy
argument_list|,
name|cx
argument_list|)
operator|*
name|parameters
operator|.
name|division
operator|/
name|G_PI_2
argument_list|)
operator|*
name|G_PI_2
operator|/
name|parameters
operator|.
name|division
operator|+
operator|(
name|G_PI
operator|/
name|parameters
operator|.
name|division
operator|)
expr_stmt|;
name|radius
operator|=
name|sqrt
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|cx
operator|*
name|cx
operator|+
name|cy
operator|*
name|cy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parameters
operator|.
name|type1
condition|)
block|{
name|xx
operator|=
name|x
operator|-
name|param
operator|->
name|offset
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|yy
operator|=
name|y
operator|-
name|param
operator|->
name|offset
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* Type 2 */
block|{
name|xx
operator|=
name|x
operator|-
name|param
operator|->
name|offset
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|yy
operator|=
name|y
operator|-
name|param
operator|->
name|offset
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
expr_stmt|;
block|}
name|gimp_pixel_fetcher_get_pixel2
argument_list|(
name|param
operator|->
name|pft
argument_list|,
name|xx
argument_list|,
name|yy
argument_list|,
name|PIXEL_SMEAR
argument_list|,
name|pixel
argument_list|)
expr_stmt|;
if|if
condition|(
name|param
operator|->
name|has_alpha
condition|)
block|{
name|guint
name|alpha1
init|=
name|src
index|[
name|bpp
operator|-
literal|1
index|]
decl_stmt|;
name|guint
name|alpha2
init|=
name|pixel
index|[
name|bpp
operator|-
literal|1
index|]
decl_stmt|;
name|guint
name|alpha
init|=
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|alpha1
operator|+
name|radius
operator|*
name|alpha2
decl_stmt|;
if|if
condition|(
operator|(
name|dest
index|[
name|bpp
operator|-
literal|1
index|]
operator|=
operator|(
name|alpha
operator|>>
literal|1
operator|)
operator|)
condition|)
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bpp
operator|-
literal|1
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
operator|(
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|src
index|[
name|b
index|]
operator|*
name|alpha1
operator|+
name|radius
operator|*
name|pixel
index|[
name|b
index|]
operator|*
name|alpha2
operator|)
operator|/
name|alpha
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|bpp
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|src
index|[
name|b
index|]
operator|+
name|radius
operator|*
name|pixel
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|filter (GimpDrawable * drawable)
name|filter
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|IllusionParam_t
name|param
decl_stmt|;
name|GimpRgnIterator
modifier|*
name|iter
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
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
name|param
operator|.
name|pft
operator|=
name|gimp_pixel_fetcher_new
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
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
name|center_x
operator|=
operator|(
name|x1
operator|+
name|x2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|param
operator|.
name|center_y
operator|=
operator|(
name|y1
operator|+
name|y2
operator|)
operator|/
literal|2.0
expr_stmt|;
name|param
operator|.
name|scale
operator|=
name|sqrt
argument_list|(
name|width
operator|*
name|width
operator|+
name|height
operator|*
name|height
argument_list|)
operator|/
literal|2
expr_stmt|;
name|param
operator|.
name|offset
operator|=
call|(
name|gint
call|)
argument_list|(
name|param
operator|.
name|scale
operator|/
literal|2
argument_list|)
expr_stmt|;
name|iter
operator|=
name|gimp_rgn_iterator_new
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_src_dest
argument_list|(
name|iter
argument_list|,
name|illusion_func
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
name|gimp_pixel_fetcher_destroy
argument_list|(
name|param
operator|.
name|pft
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|filter_preview (void)
name|filter_preview
parameter_list|(
name|void
parameter_list|)
block|{
name|guchar
modifier|*
modifier|*
name|pixels
decl_stmt|;
name|guchar
modifier|*
modifier|*
name|destpixels
decl_stmt|;
name|gint
name|image_width
decl_stmt|;
name|gint
name|image_height
decl_stmt|;
name|gint
name|image_bpp
decl_stmt|;
name|gdouble
name|center_x
decl_stmt|;
name|gdouble
name|center_y
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|xx
init|=
literal|0
decl_stmt|;
name|gint
name|yy
init|=
literal|0
decl_stmt|;
name|gdouble
name|scale
decl_stmt|,
name|radius
decl_stmt|,
name|cx
decl_stmt|,
name|cy
decl_stmt|,
name|angle
decl_stmt|,
name|offset
decl_stmt|;
name|image_width
operator|=
name|preview
operator|->
name|width
expr_stmt|;
name|image_height
operator|=
name|preview
operator|->
name|height
expr_stmt|;
name|image_bpp
operator|=
name|preview
operator|->
name|bpp
expr_stmt|;
name|center_x
operator|=
operator|(
name|gdouble
operator|)
name|image_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
operator|(
name|gdouble
operator|)
name|image_height
operator|/
literal|2
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|destpixels
operator|=
name|g_new
argument_list|(
name|guchar
operator|*
argument_list|,
name|image_height
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
name|image_height
condition|;
name|y
operator|++
control|)
block|{
name|pixels
index|[
name|y
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|preview
operator|->
name|rowstride
argument_list|)
expr_stmt|;
name|destpixels
index|[
name|y
index|]
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|preview
operator|->
name|rowstride
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|pixels
index|[
name|y
index|]
argument_list|,
name|preview
operator|->
name|cache
operator|+
name|preview
operator|->
name|rowstride
operator|*
name|y
argument_list|,
name|preview
operator|->
name|rowstride
argument_list|)
expr_stmt|;
block|}
name|scale
operator|=
name|sqrt
argument_list|(
name|image_width
operator|*
name|image_width
operator|+
name|image_height
operator|*
name|image_height
argument_list|)
operator|/
literal|2
expr_stmt|;
name|offset
operator|=
call|(
name|gint
call|)
argument_list|(
name|scale
operator|/
literal|2
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
name|image_height
condition|;
name|y
operator|++
control|)
block|{
name|cy
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|y
operator|-
name|center_y
operator|)
operator|/
name|scale
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|image_width
condition|;
name|x
operator|++
control|)
block|{
name|cx
operator|=
operator|(
operator|(
name|gdouble
operator|)
name|x
operator|-
name|center_x
operator|)
operator|/
name|scale
expr_stmt|;
name|angle
operator|=
name|floor
argument_list|(
name|atan2
argument_list|(
name|cy
argument_list|,
name|cx
argument_list|)
operator|*
name|parameters
operator|.
name|division
operator|/
name|G_PI_2
argument_list|)
operator|*
name|G_PI_2
operator|/
name|parameters
operator|.
name|division
operator|+
operator|(
name|G_PI
operator|/
name|parameters
operator|.
name|division
operator|)
expr_stmt|;
name|radius
operator|=
name|sqrt
argument_list|(
call|(
name|gdouble
call|)
argument_list|(
name|cx
operator|*
name|cx
operator|+
name|cy
operator|*
name|cy
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|parameters
operator|.
name|type1
condition|)
block|{
name|xx
operator|=
name|x
operator|-
name|offset
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|yy
operator|=
name|y
operator|-
name|offset
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
expr_stmt|;
block|}
else|else
comment|/* Type 2 */
block|{
name|xx
operator|=
name|x
operator|-
name|offset
operator|*
name|sin
argument_list|(
name|angle
argument_list|)
expr_stmt|;
name|yy
operator|=
name|y
operator|-
name|offset
operator|*
name|cos
argument_list|(
name|angle
argument_list|)
expr_stmt|;
block|}
name|xx
operator|=
name|CLAMP
argument_list|(
name|xx
argument_list|,
literal|0
argument_list|,
name|image_width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|yy
operator|=
name|CLAMP
argument_list|(
name|yy
argument_list|,
literal|0
argument_list|,
name|image_height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_bpp
operator|==
literal|2
operator|||
name|image_bpp
operator|==
literal|4
condition|)
block|{
name|gdouble
name|alpha1
init|=
name|pixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|image_bpp
operator|-
literal|1
index|]
decl_stmt|;
name|gdouble
name|alpha2
init|=
name|pixels
index|[
name|yy
index|]
index|[
name|xx
operator|*
name|image_bpp
operator|+
name|image_bpp
operator|-
literal|1
index|]
decl_stmt|;
name|gdouble
name|alpha
init|=
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|alpha1
operator|+
name|radius
operator|*
name|alpha2
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|alpha
operator|>
literal|0
operator|&&
name|b
operator|<
name|image_bpp
operator|-
literal|1
condition|;
name|b
operator|++
control|)
block|{
name|destpixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|b
index|]
operator|=
operator|(
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|alpha1
operator|*
name|pixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|b
index|]
operator|+
name|radius
operator|*
name|alpha2
operator|*
name|pixels
index|[
name|yy
index|]
index|[
name|xx
operator|*
name|image_bpp
operator|+
name|b
index|]
operator|)
operator|/
name|alpha
expr_stmt|;
block|}
name|destpixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|image_bpp
operator|-
literal|1
index|]
operator|=
name|alpha
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|image_bpp
condition|;
name|b
operator|++
control|)
name|destpixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|b
index|]
operator|=
operator|(
literal|1
operator|-
name|radius
operator|)
operator|*
name|pixels
index|[
name|y
index|]
index|[
name|x
operator|*
name|image_bpp
operator|+
name|b
index|]
operator|+
name|radius
operator|*
name|pixels
index|[
name|yy
index|]
index|[
name|xx
operator|*
name|image_bpp
operator|+
name|b
index|]
expr_stmt|;
block|}
block|}
name|gimp_fixme_preview_do_row
argument_list|(
name|preview
argument_list|,
name|y
argument_list|,
name|image_width
argument_list|,
name|destpixels
index|[
name|y
index|]
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|image_height
condition|;
name|y
operator|++
control|)
name|g_free
argument_list|(
name|pixels
index|[
name|y
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
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
name|image_height
condition|;
name|y
operator|++
control|)
name|g_free
argument_list|(
name|destpixels
index|[
name|y
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|destpixels
argument_list|)
expr_stmt|;
name|gtk_widget_queue_draw
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|dialog (GimpDrawable * mangle)
name|dialog
parameter_list|(
name|GimpDrawable
modifier|*
name|mangle
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
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
name|radio
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"illusion"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Illusion"
argument_list|)
argument_list|,
literal|"illusion"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/illusion.html"
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
name|main_vbox
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
name|main_vbox
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
name|main_vbox
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
name|main_vbox
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_fixme_preview_new
argument_list|(
name|mangle
argument_list|,
name|TRUE
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
operator|->
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|filter_preview
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
name|table
operator|=
name|gimp_parameter_settings_new
argument_list|(
name|main_vbox
argument_list|,
literal|3
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adj
argument_list|,
name|parameters
operator|.
name|division
argument_list|,
operator|-
literal|32
argument_list|,
literal|64
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"_Division:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|TRUE
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
name|parameters
operator|.
name|division
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
name|filter_preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|radio
operator|=
name|gtk_radio_button_new_with_mnemonic
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Mode _1"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|radio
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|parameters
operator|.
name|type1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|filter_preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|radio
argument_list|)
argument_list|,
name|parameters
operator|.
name|type1
argument_list|)
expr_stmt|;
name|radio
operator|=
name|gtk_radio_button_new_with_mnemonic
argument_list|(
name|group
argument_list|,
name|_
argument_list|(
literal|"Mode _2"
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_get_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|radio
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
name|GTK_FILL
argument_list|,
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|parameters
operator|.
name|type2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|radio
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|filter_preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|radio
argument_list|)
argument_list|,
name|parameters
operator|.
name|type2
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
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
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

