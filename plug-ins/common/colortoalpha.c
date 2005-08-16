begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Color To Alpha plug-in v1.0 by Seth Burgess, sjburges@gimp.org 1999/05/14  *  with algorithm by clahey  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|"plug-in-colortoalpha"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"colortoaplha"
end_define

begin_define
DECL|macro|PRV_WIDTH
define|#
directive|define
name|PRV_WIDTH
value|40
end_define

begin_define
DECL|macro|PRV_HEIGHT
define|#
directive|define
name|PRV_HEIGHT
value|20
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon287e73d70108
block|{
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|C2AValues
block|}
name|C2AValues
typedef|;
end_typedef

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
specifier|inline
name|void
name|color_to_alpha
parameter_list|(
name|GimpRGB
modifier|*
name|src
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|to_alpha_func
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
function_decl|;
end_function_decl

begin_comment
comment|/* UI stuff */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|color_to_alpha_dialog
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
name|color_to_alpha_preview
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
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

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|C2AValues
name|pvals
init|=
block|{
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,
comment|/* white default */
name|TRUE
comment|/* preview       */
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
name|GIMP_PDB_COLOR
block|,
literal|"color"
block|,
literal|"Color to remove"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"Convert the color in an image to alpha"
argument_list|,
literal|"This replaces as much of a given color as possible "
literal|"in each pixel with a corresponding amount of alpha, "
literal|"then readjusts the color accordingly."
argument_list|,
literal|"Seth Burgess"
argument_list|,
literal|"Seth Burgess<sjburges@gimp.org>"
argument_list|,
literal|"7th Aug 1999"
argument_list|,
name|N_
argument_list|(
literal|"Color to _Alpha..."
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
literal|0
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
literal|"<Image>/Colors"
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
literal|"plug_in_colortoalpha"
argument_list|,
literal|"<Image>/Layer/Transparency/Modify"
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
name|INIT_I18N
argument_list|()
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
name|pvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|color_to_alpha_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
return|return;
block|}
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
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
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|pvals
operator|.
name|color
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_color
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|pvals
argument_list|)
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
operator|&&
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
operator|&&
name|gimp_drawable_is_layer
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|gboolean
name|lock_alpha
decl_stmt|;
name|gimp_image_undo_group_start
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
comment|/*  Add alpha if not present */
name|gimp_layer_add_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/*  Reget the drawable, bpp might have changed  */
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/*  Unset 'Lock alpha'  */
name|lock_alpha
operator|=
name|gimp_layer_get_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|gimp_layer_set_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Removing color..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|to_alpha_func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_layer_set_lock_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
name|lock_alpha
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
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
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|pvals
argument_list|)
argument_list|)
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
block|}
end_function

begin_function
specifier|static
specifier|inline
name|void
DECL|function|color_to_alpha (GimpRGB * src,const GimpRGB * color)
name|color_to_alpha
parameter_list|(
name|GimpRGB
modifier|*
name|src
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|GimpRGB
name|alpha
decl_stmt|;
name|alpha
operator|.
name|a
operator|=
name|src
operator|->
name|a
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|r
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|r
operator|=
name|src
operator|->
name|r
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|r
operator|>
name|color
operator|->
name|r
condition|)
name|alpha
operator|.
name|r
operator|=
operator|(
name|src
operator|->
name|r
operator|-
name|color
operator|->
name|r
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|r
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|r
operator|<
name|color
operator|->
name|r
condition|)
name|alpha
operator|.
name|r
operator|=
operator|(
name|color
operator|->
name|r
operator|-
name|src
operator|->
name|r
operator|)
operator|/
name|color
operator|->
name|r
expr_stmt|;
else|else
name|alpha
operator|.
name|r
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|g
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|g
operator|=
name|src
operator|->
name|g
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|g
operator|>
name|color
operator|->
name|g
condition|)
name|alpha
operator|.
name|g
operator|=
operator|(
name|src
operator|->
name|g
operator|-
name|color
operator|->
name|g
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|g
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|g
operator|<
name|color
operator|->
name|g
condition|)
name|alpha
operator|.
name|g
operator|=
operator|(
name|color
operator|->
name|g
operator|-
name|src
operator|->
name|g
operator|)
operator|/
operator|(
name|color
operator|->
name|g
operator|)
expr_stmt|;
else|else
name|alpha
operator|.
name|g
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|color
operator|->
name|b
operator|<
literal|0.0001
condition|)
name|alpha
operator|.
name|b
operator|=
name|src
operator|->
name|b
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|b
operator|>
name|color
operator|->
name|b
condition|)
name|alpha
operator|.
name|b
operator|=
operator|(
name|src
operator|->
name|b
operator|-
name|color
operator|->
name|b
operator|)
operator|/
operator|(
literal|1.0
operator|-
name|color
operator|->
name|b
operator|)
expr_stmt|;
elseif|else
if|if
condition|(
name|src
operator|->
name|b
operator|<
name|color
operator|->
name|b
condition|)
name|alpha
operator|.
name|b
operator|=
operator|(
name|color
operator|->
name|b
operator|-
name|src
operator|->
name|b
operator|)
operator|/
operator|(
name|color
operator|->
name|b
operator|)
expr_stmt|;
else|else
name|alpha
operator|.
name|b
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
name|alpha
operator|.
name|r
operator|>
name|alpha
operator|.
name|g
condition|)
block|{
if|if
condition|(
name|alpha
operator|.
name|r
operator|>
name|alpha
operator|.
name|b
condition|)
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|r
expr_stmt|;
block|}
else|else
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|b
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|alpha
operator|.
name|g
operator|>
name|alpha
operator|.
name|b
condition|)
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|g
expr_stmt|;
block|}
else|else
block|{
name|src
operator|->
name|a
operator|=
name|alpha
operator|.
name|b
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|a
operator|<
literal|0.0001
condition|)
return|return;
name|src
operator|->
name|r
operator|=
operator|(
name|src
operator|->
name|r
operator|-
name|color
operator|->
name|r
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|r
expr_stmt|;
name|src
operator|->
name|g
operator|=
operator|(
name|src
operator|->
name|g
operator|-
name|color
operator|->
name|g
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|g
expr_stmt|;
name|src
operator|->
name|b
operator|=
operator|(
name|src
operator|->
name|b
operator|-
name|color
operator|->
name|b
operator|)
operator|/
name|src
operator|->
name|a
operator|+
name|color
operator|->
name|b
expr_stmt|;
name|src
operator|->
name|a
operator|*=
name|alpha
operator|.
name|a
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * An excerpt from a discussion on #gimp that sheds some light on the ideas  * behind the algorithm that is being used here.  *<clahey>   so if a1> c1, a2> c2, and a3> c2 and a1 - c1> a2-c2, a3-c3,              then a1 = b1 * alpha + c1 * (1-alpha)              So, maximizing alpha without taking b1 above 1 gives              a1 = alpha + c1(1-alpha) and therefore alpha = (a1-c1) / (1-c1).<sjburges> clahey: btw, the ordering of that a2, a3 in the white->alpha didn't              matter<clahey>   sjburges: You mean that it could be either a1, a2, a3 or              a1, a3, a2?<sjburges> yeah<sjburges> because neither one uses the other<clahey>   sjburges: That's exactly as it should be.  They are both just              getting reduced to the same amount, limited by the the darkest              color.<clahey>   Then a2 = b2 * alpha + c2 * (1- alpha).  Solving for b2 gives              b2 = (a1-c2)/alpha + c2.<sjburges> yeah<clahey>   That gives us are formula for if the background is darker than the              foreground? Yep.<clahey>   Next if a1< c1, a2< c2, a3< c3, and c1-a1> c2-a2, c3-a3, and              by our desired result a1 = b1 * alpha + c1 * (1-alpha),              we maximize alpha without taking b1 negative gives              alpha = 1 - a1 / c1.<clahey>   And then again, b2 = (a2-c2) / alpha + c2 by the same formula.              (Actually, I think we can use that formula for all cases, though              it may possibly introduce rounding error.<clahey>   sjburges: I like the idea of using floats to avoid rounding error.              Good call.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|to_alpha_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|to_alpha_func
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
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
name|bpp
operator|==
literal|3
condition|)
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|,
literal|255
argument_list|)
expr_stmt|;
else|else
name|gimp_rgba_set_uchar
argument_list|(
operator|&
name|color
argument_list|,
name|src
index|[
literal|0
index|]
argument_list|,
name|src
index|[
literal|1
index|]
argument_list|,
name|src
index|[
literal|2
index|]
argument_list|,
name|src
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
name|color_to_alpha
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|dest
index|[
literal|0
index|]
argument_list|,
operator|&
name|dest
index|[
literal|1
index|]
argument_list|,
operator|&
name|dest
index|[
literal|2
index|]
argument_list|,
operator|&
name|dest
index|[
literal|3
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_to_alpha_preview (GimpPreview * preview,GimpDrawable * drawable)
name|color_to_alpha_preview
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|src_rgn
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|bpp
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
name|gimp_preview_get_position
argument_list|(
name|preview
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
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
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
literal|4
argument_list|)
expr_stmt|;
name|src
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
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
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|src_rgn
argument_list|,
name|src
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
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
name|width
operator|*
name|height
condition|;
name|i
operator|++
control|)
name|to_alpha_func
argument_list|(
name|src
operator|+
name|i
operator|*
name|bpp
argument_list|,
name|dest
operator|+
name|i
operator|*
literal|4
argument_list|,
name|bpp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
comment|/* Our code assumes that the drawable has an alpha channel (and adds    * one later if the effect is actually performed). For that reason    * we have to take care when drawing the preview.    */
if|if
condition|(
name|bpp
operator|==
literal|4
condition|)
block|{
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dest
argument_list|,
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* This is not correct because we ignore the selection, but it        * is the best we can easily do.        */
name|gimp_preview_area_draw
argument_list|(
name|GIMP_PREVIEW_AREA
argument_list|(
name|preview
operator|->
name|area
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGBA_IMAGE
argument_list|,
name|dest
argument_list|,
name|width
operator|*
literal|4
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|color_to_alpha_dialog (GimpDrawable * drawable)
name|color_to_alpha_dialog
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|label
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
literal|"Color to Alpha"
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
name|preview
operator|=
name|gimp_drawable_preview_new
argument_list|(
name|drawable
argument_list|,
operator|&
name|pvals
operator|.
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_start_defaults
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_to_alpha_preview
argument_list|)
argument_list|,
name|drawable
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"From:"
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
name|button
operator|=
name|gimp_color_button_new
argument_list|(
name|_
argument_list|(
literal|"Color to Alpha Color Picker"
argument_list|)
argument_list|,
name|PRV_WIDTH
argument_list|,
name|PRV_HEIGHT
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|gimp_color_button_set_update
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_get_color
argument_list|)
argument_list|,
operator|&
name|pvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"to alpha"
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

