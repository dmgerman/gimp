begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*******************************************************************************    illusion.c  -- This is a plug-in for the GIMP 1.0    Copyright (C) 1997  Hirotsuna Mizuno                       s1041150@u-aizu.ac.jp    This program is free software; you can redistribute it and/or modify it   under the terms of the GNU General Public License as published by the Free   Software Foundation; either version 2 of the License, or (at your option)   any later version.    This program is distributed in the hope that it will be useful, but WITHOUT   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for   more details.    You should have received a copy of the GNU General Public License along with   this program; if not, write to the Free Software Foundation, Inc.,   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *******************************************************************************/
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
file|<libgimp/gimpmath.h>
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
value|"v0.7 (Dec. 25 1997)"
end_define

begin_comment
comment|/******************************************************************************/
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparam
parameter_list|,
name|GParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
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
name|GDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/******************************************************************************/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28e653450108
block|{
DECL|member|division
name|gint32
name|division
decl_stmt|;
DECL|typedef|parameter_t
block|}
name|parameter_t
typedef|;
end_typedef

begin_comment
comment|/******************************************************************************/
end_comment

begin_decl_stmt
DECL|variable|PLUG_IN_INFO
name|GPlugInInfo
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
DECL|variable|parameters
specifier|static
name|parameter_t
name|parameters
init|=
block|{
literal|8
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_width
specifier|static
name|gint
name|image_width
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_height
specifier|static
name|gint
name|image_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_bpp
specifier|static
name|gint
name|image_bpp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|image_has_alpha
specifier|static
name|gint
name|image_has_alpha
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_x1
specifier|static
name|gint
name|select_x1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_y1
specifier|static
name|gint
name|select_y1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_x2
specifier|static
name|gint
name|select_x2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_y2
specifier|static
name|gint
name|select_y2
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_width
specifier|static
name|gint
name|select_width
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_height
specifier|static
name|gint
name|select_height
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_x
specifier|static
name|gdouble
name|center_x
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|center_y
specifier|static
name|gdouble
name|center_y
decl_stmt|;
end_decl_stmt

begin_comment
comment|/******************************************************************************/
end_comment

begin_macro
DECL|function|MAIN ()
name|MAIN
argument_list|()
end_macro

begin_comment
comment|/******************************************************************************/
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
name|int
name|nargs
init|=
literal|4
decl_stmt|;
specifier|static
name|GParamDef
name|args
index|[]
init|=
block|{
block|{
name|PARAM_INT32
block|,
literal|"run_mode"
block|,
literal|"interactive / non-interactive"
block|}
block|,
block|{
name|PARAM_IMAGE
block|,
literal|"image"
block|,
literal|"input image"
block|}
block|,
block|{
name|PARAM_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"input drawable"
block|}
block|,
block|{
name|PARAM_INT32
block|,
literal|"division"
block|,
literal|"the number of divisions"
block|}
block|}
decl_stmt|;
specifier|static
name|int
name|nreturn_vals
init|=
literal|0
decl_stmt|;
specifier|static
name|GParamDef
modifier|*
name|return_vals
init|=
name|NULL
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
name|_
argument_list|(
literal|"produce illusion"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"produce illusion"
argument_list|)
argument_list|,
literal|"Hirotsuna Mizuno<s1041150@u-aizu.ac.jp>"
argument_list|,
literal|"Hirotsuna Mizuno"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Map/Illusion..."
argument_list|)
argument_list|,
literal|"RGB*, GRAY*"
argument_list|,
name|PROC_PLUG_IN
argument_list|,
name|nargs
argument_list|,
name|nreturn_vals
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GParam * params,gint * nreturn_vals,GParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
name|GParam
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|nreturn_vals
parameter_list|,
name|GParam
modifier|*
modifier|*
name|return_vals
parameter_list|)
block|{
name|GDrawable
modifier|*
name|drawable
decl_stmt|;
name|GRunModeType
name|run_mode
decl_stmt|;
specifier|static
name|GParam
name|returnv
index|[
literal|1
index|]
decl_stmt|;
name|GStatusType
name|status
init|=
name|STATUS_SUCCESS
decl_stmt|;
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
name|image_width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|image_height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|image_bpp
operator|=
name|gimp_drawable_bpp
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|image_has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
expr_stmt|;
name|gimp_drawable_mask_bounds
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
operator|&
name|select_x1
argument_list|,
operator|&
name|select_y1
argument_list|,
operator|&
name|select_x2
argument_list|,
operator|&
name|select_y2
argument_list|)
expr_stmt|;
name|select_width
operator|=
name|select_x2
operator|-
name|select_x1
expr_stmt|;
name|select_height
operator|=
name|select_y2
operator|-
name|select_y1
expr_stmt|;
name|center_x
operator|=
name|select_x1
operator|+
operator|(
name|gdouble
operator|)
name|select_width
operator|/
literal|2
expr_stmt|;
name|center_y
operator|=
name|select_y1
operator|+
operator|(
name|gdouble
operator|)
name|select_height
operator|/
literal|2
expr_stmt|;
comment|/* switch the run mode */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|RUN_INTERACTIVE
case|:
name|INIT_I18N_UI
argument_list|()
expr_stmt|;
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
argument_list|()
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
name|parameter_t
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|RUN_NONINTERACTIVE
case|:
if|if
condition|(
name|nparams
operator|!=
literal|4
condition|)
block|{
name|status
operator|=
name|STATUS_CALLING_ERROR
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
block|}
break|break;
case|case
name|RUN_WITH_LAST_VALS
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
name|STATUS_SUCCESS
condition|)
block|{
if|if
condition|(
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|id
argument_list|)
operator|||
name|gimp_drawable_is_gray
argument_list|(
name|drawable
operator|->
name|id
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
name|filter
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|!=
name|RUN_NONINTERACTIVE
condition|)
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|STATUS_EXECUTION_ERROR
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
name|PARAM_STATUS
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

begin_comment
comment|/******************************************************************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|filter (GDrawable * drawable)
name|filter
parameter_list|(
name|GDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GPixelRgn
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
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
name|x
decl_stmt|,
name|y
decl_stmt|,
name|b
decl_stmt|;
name|gint
name|xx
decl_stmt|,
name|yy
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
name|image_width
argument_list|,
name|image_height
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|,
name|image_height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|pixels
operator|=
operator|(
name|guchar
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
name|image_height
operator|*
sizeof|sizeof
argument_list|(
name|guchar
operator|*
argument_list|)
argument_list|)
expr_stmt|;
name|destpixels
operator|=
operator|(
name|guchar
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
name|image_height
operator|*
sizeof|sizeof
argument_list|(
name|guchar
operator|*
argument_list|)
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
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|image_width
operator|*
name|image_bpp
argument_list|)
expr_stmt|;
name|destpixels
index|[
name|y
index|]
operator|=
operator|(
name|guchar
operator|*
operator|)
name|g_malloc
argument_list|(
name|image_width
operator|*
name|image_bpp
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|pixels
index|[
name|y
index|]
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
block|}
comment|/*     for( y = select_y1; y< select_y2; y++ ){     for( x = select_x1; x< select_x2; x++ ){     for( b = 0; b< image_bpp; b++ ){     destpixels[y][x*image_bpp+b] = 0;     }     }     }   */
name|gimp_progress_init
argument_list|(
name|PLUG_IN_NAME
argument_list|)
expr_stmt|;
name|scale
operator|=
name|sqrt
argument_list|(
name|select_width
operator|*
name|select_width
operator|+
name|select_height
operator|*
name|select_height
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
name|select_y1
init|;
name|y
operator|<
name|select_y2
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
name|select_x1
init|;
name|x
operator|<
name|select_x2
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
if|if
condition|(
name|xx
operator|<
literal|0
condition|)
name|xx
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|image_width
operator|<=
name|xx
condition|)
name|xx
operator|=
name|image_width
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|yy
operator|<
literal|0
condition|)
name|yy
operator|=
literal|0
expr_stmt|;
elseif|else
if|if
condition|(
name|image_height
operator|<=
name|yy
condition|)
name|yy
operator|=
name|image_height
operator|-
literal|1
expr_stmt|;
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
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|destpixels
index|[
name|y
index|]
argument_list|,
literal|0
argument_list|,
name|y
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
call|(
name|double
call|)
argument_list|(
name|y
operator|-
name|select_y1
argument_list|)
operator|/
operator|(
name|double
operator|)
name|select_height
argument_list|)
expr_stmt|;
block|}
name|gimp_drawable_flush
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_drawable_merge_shadow
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|drawable
operator|->
name|id
argument_list|,
name|select_x1
argument_list|,
name|select_y1
argument_list|,
name|select_width
argument_list|,
name|select_height
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|select_y1
init|;
name|y
operator|<
name|select_y2
condition|;
name|y
operator|++
control|)
name|g_free
argument_list|(
name|pixels
index|[
name|y
operator|-
name|select_y1
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
name|select_y1
init|;
name|y
operator|<
name|select_y2
condition|;
name|y
operator|++
control|)
name|g_free
argument_list|(
name|destpixels
index|[
name|y
operator|-
name|select_y1
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|destpixels
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************************************************************/
end_comment

begin_decl_stmt
DECL|variable|dialog_status
specifier|static
name|int
name|dialog_status
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|dialog_ok_handler (GtkWidget * widget,gpointer data)
name|dialog_ok_handler
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|dialog_status
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/******************************************************************************/
end_comment

begin_function
specifier|static
name|int
DECL|function|dialog (void)
name|dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
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
name|gint
name|argc
init|=
literal|1
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|argv
init|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|argv
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
literal|"illusion"
argument_list|)
expr_stmt|;
name|gtk_init
argument_list|(
operator|&
name|argc
argument_list|,
operator|&
name|argv
argument_list|)
expr_stmt|;
name|gtk_rc_parse
argument_list|(
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
comment|/* dialog window */
name|window
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
name|gimp_plugin_help_func
argument_list|,
literal|"filters/illusion.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"OK"
argument_list|)
argument_list|,
name|dialog_ok_handler
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Cancel"
argument_list|)
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|window
argument_list|)
argument_list|,
literal|"destroy"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gtk_main_quit
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Parameter Settings"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
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
name|window
argument_list|)
operator|->
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
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
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
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
name|G_MININT
argument_list|,
name|G_MAXINT
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
name|_
argument_list|(
literal|"Division:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
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
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|dialog_status
return|;
block|}
end_function

end_unit

