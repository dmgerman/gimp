begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Gradient Map plug-in  * Copyright (C) 1997 Eiichi Takamori<taka@ma1.seikyou.ne.jp>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  * version 1.07  * This plug-in requires GIMP v0.99.10 or above.  *  * This plug-in maps the image using active gradient. (See help_string  * in query ()).  *  *	Eiichi Takamori<taka@ma1.seikyou.ne.jp>  *	http://ha1.seikyou.ne.jp/home/taka/gimp/  *  * Changes from version 1.06 to version 1.07:  * - If layer is RGBA or GRAYA (partially transparent), preserve  *   the alpha channel instead of making invisible pixels visible.  *   See also: http://bugzilla.gnome.org/show_bug.cgi?id=70964  *  * Changes from version 1.05 to version 1.06:  * - Fixed bug that completely white pixel (= grayscale 255) was not  *   mapped properly.  (Thanks to Dov Grobgeld)  *  * Changes from version 1.04 to version 1.05:  * - Now it uses gimp_gradients_sample_uniform () instead of blend  *   tool. Maybe right thing.  *  * Changes from revision 1.1 to version 1.04:  * - Fix bug that it didn't work with alpha channel.  * - Changed calling `gimp_blend' so that it works in v0.99.9.  * - Changed calling `gimp_blend' so that it works with Quartic's  *   asupsample patch.  * - Fix the way to calculate luminosity of RGB image.  *   (Thanks to Michael Lamertz)  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|RCSID
end_ifdef

begin_decl_stmt
DECL|variable|rcsid
specifier|static
name|char
name|rcsid
index|[]
init|=
literal|"$Id$"
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Some useful macros */
end_comment

begin_define
DECL|macro|NSAMPLES
define|#
directive|define
name|NSAMPLES
value|256
end_define

begin_define
DECL|macro|TILE_CACHE_SIZE
define|#
directive|define
name|TILE_CACHE_SIZE
value|32
end_define

begin_define
DECL|macro|LUMINOSITY (X)
define|#
directive|define
name|LUMINOSITY
parameter_list|(
name|X
parameter_list|)
value|(INTENSITY (X[0], X[1], X[2]))
end_define

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Declare a local function.  */
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
name|gradmap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guchar
modifier|*
name|get_samples
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
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
parameter_list|()
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
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_gradmap"
argument_list|,
literal|"Map the contents of the specified drawable with "
literal|"active gradient"
argument_list|,
literal|" This plug-in maps the contents of the specified "
literal|"drawable with active gradient. It calculates "
literal|"luminosity of each pixel and replaces the pixel "
literal|"by the sample of active gradient at the position "
literal|"proportional to that luminosity. Complete black "
literal|"pixel becomes the leftmost color of the gradient, "
literal|"and complete white becomes the rightmost. Works on "
literal|"both Grayscale and RGB image with/without alpha "
literal|"channel."
argument_list|,
literal|"Eiichi Takamori"
argument_list|,
literal|"Eiichi Takamori"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Map/_Gradient Map"
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
comment|/*  Make sure that the drawable is gray or RGB color	*/
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
literal|"Gradient Map..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tile_cache_ntiles
argument_list|(
name|TILE_CACHE_SIZE
argument_list|)
expr_stmt|;
name|gradmap
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
comment|/* g_message ("gradmap: cannot operate on indexed color images"); */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
end_function

begin_typedef
DECL|struct|__anon27b969790108
typedef|typedef
struct|struct
block|{
DECL|member|samples
name|guchar
modifier|*
name|samples
decl_stmt|;
DECL|member|is_rgb
name|gboolean
name|is_rgb
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|typedef|GradMapParam_t
block|}
name|GradMapParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|gradmap_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|gradmap_func
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
name|GradMapParam_t
modifier|*
name|param
init|=
operator|(
name|GradMapParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|lum
decl_stmt|;
name|gint
name|b
decl_stmt|;
name|guchar
modifier|*
name|samp
decl_stmt|;
name|lum
operator|=
operator|(
name|param
operator|->
name|is_rgb
operator|)
condition|?
name|LUMINOSITY
argument_list|(
name|src
argument_list|)
else|:
name|src
index|[
literal|0
index|]
expr_stmt|;
name|samp
operator|=
operator|&
name|param
operator|->
name|samples
index|[
name|lum
operator|*
name|bpp
index|]
expr_stmt|;
if|if
condition|(
name|param
operator|->
name|has_alpha
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
name|samp
index|[
name|b
index|]
expr_stmt|;
name|dest
index|[
name|b
index|]
operator|=
operator|(
operator|(
name|guint
operator|)
name|samp
index|[
name|b
index|]
operator|*
operator|(
name|guint
operator|)
name|src
index|[
name|b
index|]
operator|)
operator|/
literal|255
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
name|samp
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
DECL|function|gradmap (GimpDrawable * drawable)
name|gradmap
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GradMapParam_t
name|param
decl_stmt|;
name|param
operator|.
name|is_rgb
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
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
name|samples
operator|=
name|get_samples
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|,
name|gradmap_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*   Returns 256 samples of active gradient.   Each sample has (gimp_drawable_bpp (drawable->drawable_id)) bytes.  */
end_comment

begin_function
specifier|static
name|guchar
modifier|*
DECL|function|get_samples (GimpDrawable * drawable)
name|get_samples
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|gdouble
modifier|*
name|f_samples
decl_stmt|,
modifier|*
name|f_samp
decl_stmt|;
comment|/* float samples */
name|guchar
modifier|*
name|b_samples
decl_stmt|,
modifier|*
name|b_samp
decl_stmt|;
comment|/* byte samples */
name|gint
name|bpp
decl_stmt|,
name|color
decl_stmt|,
name|has_alpha
decl_stmt|,
name|alpha
decl_stmt|;
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|f_samples
operator|=
name|gimp_gradients_sample_uniform
argument_list|(
name|NSAMPLES
argument_list|)
expr_stmt|;
name|bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|color
operator|=
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
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
name|alpha
operator|=
operator|(
name|has_alpha
condition|?
name|bpp
operator|-
literal|1
else|:
name|bpp
operator|)
expr_stmt|;
name|b_samples
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|NSAMPLES
operator|*
name|bpp
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
name|NSAMPLES
condition|;
name|i
operator|++
control|)
block|{
name|b_samp
operator|=
operator|&
name|b_samples
index|[
name|i
operator|*
name|bpp
index|]
expr_stmt|;
name|f_samp
operator|=
operator|&
name|f_samples
index|[
name|i
operator|*
literal|4
index|]
expr_stmt|;
if|if
condition|(
name|color
condition|)
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
literal|3
condition|;
name|j
operator|++
control|)
name|b_samp
index|[
name|j
index|]
operator|=
name|f_samp
index|[
name|j
index|]
operator|*
literal|255
expr_stmt|;
else|else
name|b_samp
index|[
literal|0
index|]
operator|=
name|LUMINOSITY
argument_list|(
name|f_samp
argument_list|)
operator|*
literal|255
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
name|b_samp
index|[
name|alpha
index|]
operator|=
name|f_samp
index|[
literal|3
index|]
operator|*
literal|255
expr_stmt|;
block|}
name|g_free
argument_list|(
name|f_samples
argument_list|)
expr_stmt|;
return|return
name|b_samples
return|;
block|}
end_function

end_unit

