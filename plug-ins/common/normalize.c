begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Normalize 1.00 --- image filter plug-in for The GIMP  *  * Copyright (C) 1997 Adam D. Moss (adam@foxbox.org)  * Very largely based on Quartic's "Contrast Autostretch"  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* This plugin performs almost the same operation as the 'contrast  * autostretch' plugin, except that it won't allow the colour channels  * to normalize independently.  This is actually what most people probably  * want instead of contrast-autostretch; use c-a only if you wish to remove  * an undesirable colour-tint from a source image which is supposed to  * contain pure-white and pure-black.  */
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

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-normalize"
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
name|normalize
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
name|indexed_normalize
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
literal|"Stretch brightness values to cover the full range"
argument_list|)
argument_list|,
literal|"This plugin performs almost the same operation as "
literal|"the 'contrast autostretch' plugin, except that it "
literal|"won't allow the color channels to normalize "
literal|"independently.  This is actually what most people "
literal|"probably want instead of contrast-autostretch; use "
literal|"c-a only if you wish to remove an undesirable "
literal|"color-tint from a source image which is supposed to "
literal|"contain pure-white and pure-black."
argument_list|,
literal|"Adam D. Moss, Federico Mena Quintero"
argument_list|,
literal|"Adam D. Moss, Federico Mena Quintero"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Normalize"
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
literal|"Normalizing"
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
name|normalize
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
name|indexed_normalize
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
name|void
DECL|function|indexed_normalize (gint32 image_ID)
name|indexed_normalize
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
name|gint
name|ncols
decl_stmt|,
name|i
decl_stmt|;
name|gint
name|hi
init|=
literal|0
decl_stmt|,
name|lo
init|=
literal|255
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
name|cmap
operator|==
name|NULL
condition|)
block|{
name|g_printerr
argument_list|(
literal|"normalize: cmap was NULL!  Quitting...\n"
argument_list|)
expr_stmt|;
return|return;
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
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|>
name|hi
condition|)
name|hi
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|<
name|lo
condition|)
name|lo
operator|=
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
expr_stmt|;
block|}
if|if
condition|(
name|hi
operator|!=
name|lo
condition|)
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
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|=
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|0
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
expr_stmt|;
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|=
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|1
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
expr_stmt|;
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|=
operator|(
literal|255
operator|*
operator|(
name|cmap
index|[
name|i
operator|*
literal|3
operator|+
literal|2
index|]
operator|-
name|lo
operator|)
operator|)
operator|/
operator|(
name|hi
operator|-
name|lo
operator|)
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
DECL|struct|__anon29ec7b760108
block|{
DECL|member|lut
name|guchar
name|lut
index|[
literal|256
index|]
decl_stmt|;
DECL|member|min
name|gdouble
name|min
decl_stmt|;
DECL|member|max
name|gdouble
name|max
decl_stmt|;
DECL|member|alpha
name|gint
name|alpha
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|typedef|NormalizeParam_t
block|}
name|NormalizeParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|find_min_max (const guchar * src,gint bpp,gpointer data)
name|find_min_max
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
name|NormalizeParam_t
modifier|*
name|param
init|=
operator|(
name|NormalizeParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|param
operator|->
name|alpha
condition|;
name|b
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|param
operator|->
name|has_alpha
operator|||
name|src
index|[
name|param
operator|->
name|alpha
index|]
condition|)
block|{
if|if
condition|(
name|src
index|[
name|b
index|]
operator|<
name|param
operator|->
name|min
condition|)
name|param
operator|->
name|min
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
if|if
condition|(
name|src
index|[
name|b
index|]
operator|>
name|param
operator|->
name|max
condition|)
name|param
operator|->
name|max
operator|=
name|src
index|[
name|b
index|]
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|normalize_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|normalize_func
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
name|NormalizeParam_t
modifier|*
name|param
init|=
operator|(
name|NormalizeParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|b
decl_stmt|;
for|for
control|(
name|b
operator|=
literal|0
init|;
name|b
operator|<
name|param
operator|->
name|alpha
condition|;
name|b
operator|++
control|)
name|dest
index|[
name|b
index|]
operator|=
name|param
operator|->
name|lut
index|[
name|src
index|[
name|b
index|]
index|]
expr_stmt|;
if|if
condition|(
name|param
operator|->
name|has_alpha
condition|)
name|dest
index|[
name|param
operator|->
name|alpha
index|]
operator|=
name|src
index|[
name|param
operator|->
name|alpha
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|normalize (GimpDrawable * drawable)
name|normalize
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|NormalizeParam_t
name|param
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|guchar
name|range
decl_stmt|;
name|param
operator|.
name|min
operator|=
literal|255
expr_stmt|;
name|param
operator|.
name|max
operator|=
literal|0
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
name|alpha
operator|=
operator|(
name|param
operator|.
name|has_alpha
operator|)
condition|?
name|drawable
operator|->
name|bpp
operator|-
literal|1
else|:
name|drawable
operator|->
name|bpp
expr_stmt|;
name|gimp_rgn_iterate1
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|find_min_max
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
comment|/* Calculate LUT */
name|range
operator|=
name|param
operator|.
name|max
operator|-
name|param
operator|.
name|min
expr_stmt|;
if|if
condition|(
name|range
operator|!=
literal|0
condition|)
for|for
control|(
name|x
operator|=
name|param
operator|.
name|min
init|;
name|x
operator|<=
name|param
operator|.
name|max
condition|;
name|x
operator|++
control|)
name|param
operator|.
name|lut
index|[
name|x
index|]
operator|=
literal|255
operator|*
operator|(
name|x
operator|-
name|param
operator|.
name|min
operator|)
operator|/
name|range
expr_stmt|;
else|else
name|param
operator|.
name|lut
index|[
operator|(
name|gint
operator|)
name|param
operator|.
name|min
index|]
operator|=
name|param
operator|.
name|min
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|normalize_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

