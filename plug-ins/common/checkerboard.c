begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for the GIMP.  *  * Copyright (C) 1997 Brent Burton& the Edward Blevins  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  *  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
DECL|macro|SPIN_BUTTON_WIDTH
define|#
directive|define
name|SPIN_BUTTON_WIDTH
value|8
end_define

begin_comment
comment|/* Variables set in dialog box */
end_comment

begin_typedef
DECL|struct|data
typedef|typedef
struct|struct
name|data
block|{
DECL|member|mode
name|gint
name|mode
decl_stmt|;
DECL|member|size
name|gint
name|size
decl_stmt|;
DECL|typedef|CheckVals
block|}
name|CheckVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
decl_stmt|;
end_decl_stmt

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
name|do_checkerboard_pattern
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|inblock
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|do_checkerboard_dialog
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
name|check_size_update_callback
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
DECL|variable|cvals
specifier|static
name|CheckVals
name|cvals
init|=
block|{
literal|0
block|,
literal|10
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
literal|"check_mode"
block|,
literal|"Regular or Psychobilly"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"check_size"
block|,
literal|"Size of the checks"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_checkerboard"
argument_list|,
literal|"Adds a checkerboard pattern to an image"
argument_list|,
literal|"More here later"
argument_list|,
literal|"Brent Burton& the Edward Blevins"
argument_list|,
literal|"Brent Burton& the Edward Blevins"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Render/Pattern/_Checkerboard..."
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
name|gint32
name|image_ID
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
literal|"plug_in_checkerboard"
argument_list|,
operator|&
name|cvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|do_checkerboard_dialog
argument_list|(
name|image_ID
argument_list|,
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
name|cvals
operator|.
name|mode
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
name|cvals
operator|.
name|size
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
literal|"plug_in_checkerboard"
argument_list|,
operator|&
name|cvals
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
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
literal|"Adding Checkerboard..."
argument_list|)
argument_list|)
expr_stmt|;
name|do_checkerboard_pattern
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
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_set_data
argument_list|(
literal|"plug_in_checkerboard"
argument_list|,
operator|&
name|cvals
argument_list|,
sizeof|sizeof
argument_list|(
name|CheckVals
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
DECL|struct|__anon2793af3f0108
typedef|typedef
struct|struct
block|{
DECL|member|fg
name|guchar
name|fg
index|[
literal|4
index|]
decl_stmt|;
DECL|member|bg
name|guchar
name|bg
index|[
literal|4
index|]
decl_stmt|;
DECL|typedef|CheckerboardParam_t
block|}
name|CheckerboardParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|checkerboard_func (gint x,gint y,guchar * dest,gint bpp,gpointer data)
name|checkerboard_func
parameter_list|(
name|gint
name|x
parameter_list|,
name|gint
name|y
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
name|CheckerboardParam_t
modifier|*
name|param
init|=
operator|(
name|CheckerboardParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|val
decl_stmt|,
name|xp
decl_stmt|,
name|yp
decl_stmt|;
name|gint
name|b
decl_stmt|;
if|if
condition|(
name|cvals
operator|.
name|mode
condition|)
block|{
comment|/* Psychobilly Mode */
name|val
operator|=
operator|(
name|inblock
argument_list|(
name|x
argument_list|,
name|cvals
operator|.
name|size
argument_list|)
operator|!=
name|inblock
argument_list|(
name|y
argument_list|,
name|cvals
operator|.
name|size
argument_list|)
operator|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Normal, regular checkerboard mode.        * Determine base factor (even or odd) of block        * this x/y position is in.        */
name|xp
operator|=
name|x
operator|/
name|cvals
operator|.
name|size
expr_stmt|;
name|yp
operator|=
name|y
operator|/
name|cvals
operator|.
name|size
expr_stmt|;
comment|/* if both even or odd, color sqr */
name|val
operator|=
operator|(
operator|(
name|xp
operator|&
literal|1
operator|)
operator|!=
operator|(
name|yp
operator|&
literal|1
operator|)
operator|)
expr_stmt|;
block|}
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
name|val
condition|?
name|param
operator|->
name|fg
index|[
name|b
index|]
else|:
name|param
operator|->
name|bg
index|[
name|b
index|]
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|do_checkerboard_pattern (GimpDrawable * drawable)
name|do_checkerboard_pattern
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|CheckerboardParam_t
name|param
decl_stmt|;
name|GimpRgnIterator
modifier|*
name|iter
decl_stmt|;
name|gimp_get_bg_guchar
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|param
operator|.
name|bg
argument_list|)
expr_stmt|;
name|gimp_get_fg_guchar
argument_list|(
name|drawable
argument_list|,
name|FALSE
argument_list|,
name|param
operator|.
name|fg
argument_list|)
expr_stmt|;
if|if
condition|(
name|cvals
operator|.
name|size
operator|<
literal|1
condition|)
block|{
comment|/* make size 1 to prevent division by zero */
name|cvals
operator|.
name|size
operator|=
literal|1
expr_stmt|;
block|}
name|iter
operator|=
name|gimp_rgn_iterator_new
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|)
expr_stmt|;
name|gimp_rgn_iterator_dest
argument_list|(
name|iter
argument_list|,
name|checkerboard_func
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
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|inblock (gint pos,gint size)
name|inblock
parameter_list|(
name|gint
name|pos
parameter_list|,
name|gint
name|size
parameter_list|)
block|{
specifier|static
name|gint
modifier|*
name|in
init|=
name|NULL
decl_stmt|;
comment|/* initialized first time */
name|gint
name|len
decl_stmt|;
comment|/* avoid a FP exception */
if|if
condition|(
name|size
operator|==
literal|1
condition|)
name|size
operator|=
literal|2
expr_stmt|;
name|len
operator|=
name|size
operator|*
name|size
expr_stmt|;
comment|/*    * Initialize the array; since we'll be called thousands of    * times with the same size value, precompute the array.    */
if|if
condition|(
name|in
operator|==
name|NULL
condition|)
block|{
name|gint
name|cell
init|=
literal|1
decl_stmt|;
comment|/* cell value */
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|in
operator|=
name|g_new
argument_list|(
name|gint
argument_list|,
name|len
argument_list|)
expr_stmt|;
comment|/*        * i is absolute index into in[]        * j is current number of blocks to fill in with a 1 or 0.        * k is just counter for the j cells.        */
name|i
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|1
init|;
name|j
operator|<=
name|size
condition|;
name|j
operator|++
control|)
block|{
comment|/* first half */
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|j
condition|;
name|k
operator|++
control|)
block|{
name|in
index|[
name|i
operator|++
index|]
operator|=
name|cell
expr_stmt|;
block|}
name|cell
operator|=
operator|!
name|cell
expr_stmt|;
block|}
for|for
control|(
name|j
operator|=
name|size
operator|-
literal|1
init|;
name|j
operator|>=
literal|1
condition|;
name|j
operator|--
control|)
block|{
comment|/* second half */
for|for
control|(
name|k
operator|=
literal|0
init|;
name|k
operator|<
name|j
condition|;
name|k
operator|++
control|)
block|{
name|in
index|[
name|i
operator|++
index|]
operator|=
name|cell
expr_stmt|;
block|}
name|cell
operator|=
operator|!
name|cell
expr_stmt|;
block|}
block|}
comment|/* place pos within 0..(len-1) grid and return the value. */
return|return
name|in
index|[
name|pos
operator|%
operator|(
name|len
operator|-
literal|1
operator|)
index|]
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|do_checkerboard_dialog (gint32 image_ID,GimpDrawable * drawable)
name|do_checkerboard_dialog
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
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|size_entry
decl_stmt|;
name|gint
name|size
decl_stmt|,
name|width
decl_stmt|,
name|height
decl_stmt|;
name|GimpUnit
name|unit
decl_stmt|;
name|gdouble
name|xres
decl_stmt|;
name|gdouble
name|yres
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"checkerboard"
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dlg
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Checkerboard"
argument_list|)
argument_list|,
literal|"checkerboard"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/checkerboard.html"
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
name|width
operator|=
name|gimp_drawable_width
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|height
operator|=
name|gimp_drawable_height
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
name|size
operator|=
name|MIN
argument_list|(
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_parameter_settings_new
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dlg
argument_list|)
operator|->
name|vbox
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Psychobilly"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
argument_list|,
name|cvals
operator|.
name|mode
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|cvals
operator|.
name|mode
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
name|SPIN_BUTTON_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
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
literal|1
argument_list|,
literal|4
argument_list|)
expr_stmt|;
comment|/*  set the unit back to pixels, since most times we will want pixels */
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
comment|/*  set the resolution to the image resolution  */
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
name|size
argument_list|)
expr_stmt|;
comment|/*  set upper and lower limits (in pixels)  */
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
name|size
argument_list|)
expr_stmt|;
comment|/*  initialize the values  */
name|gimp_size_entry_set_refval
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
literal|0
argument_list|,
name|cvals
operator|.
name|size
argument_list|)
expr_stmt|;
comment|/*  attach labels  */
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|size_entry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Size:"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|size_entry
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|check_size_update_callback
argument_list|)
argument_list|,
operator|&
name|cvals
operator|.
name|size
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|size_entry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|size_entry
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

begin_function
specifier|static
name|void
DECL|function|check_size_update_callback (GtkWidget * widget,gpointer data)
name|check_size_update_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|cvals
operator|.
name|size
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

