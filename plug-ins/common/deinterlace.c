begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Deinterlace 1.00 - image processing plug-in for the Gimp  *  * Copyright (C) 1997 Andrew Kieschnick (andrewk@mail.utexas.edu)  *  * Original deinterlace for the Gimp 0.54 API by Federico Mena Quintero  *  * Copyright (C) 1996 Federico Mena Quintero  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_enum
enum|enum
DECL|enum|__anon29c6d47b0103
block|{
DECL|enumerator|ODD_FIELDS
name|ODD_FIELDS
block|,
DECL|enumerator|EVEN_FIELDS
name|EVEN_FIELDS
block|}
enum|;
end_enum

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
name|deinterlace
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|deinterlace_dialog
parameter_list|(
name|void
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
DECL|variable|DeinterlaceValue
specifier|static
name|gint
name|DeinterlaceValue
init|=
name|EVEN_FIELDS
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
literal|"evenodd"
block|,
literal|"0 = keep odd, 1 = keep even"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
literal|"plug_in_deinterlace"
argument_list|,
literal|"Deinterlace"
argument_list|,
literal|"Deinterlace is useful for processing images from "
literal|"video capture cards. When only the odd or even "
literal|"fields get captured, deinterlace can be used to "
literal|"interpolate between the existing fields to correct "
literal|"this."
argument_list|,
literal|"Andrew Kieschnick"
argument_list|,
literal|"Andrew Kieschnick"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Deinterlace..."
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
literal|"plug_in_deinterlace"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Enhance"
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
name|GimpRunMode
name|run_mode
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
literal|"plug_in_deinterlace"
argument_list|,
operator|&
name|DeinterlaceValue
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|deinterlace_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
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
name|DeinterlaceValue
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
name|gimp_get_data
argument_list|(
literal|"plug_in_deinterlace"
argument_list|,
operator|&
name|DeinterlaceValue
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
condition|)
block|{
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
literal|"Deinterlace..."
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
name|deinterlace
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
literal|"plug_in_deinterlace"
argument_list|,
operator|&
name|DeinterlaceValue
argument_list|,
sizeof|sizeof
argument_list|(
name|DeinterlaceValue
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* gimp_message ("deinterlace: cannot operate on indexed color images"); */
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
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
DECL|function|deinterlace (GimpDrawable * drawable)
name|deinterlace
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bytes
decl_stmt|;
name|gint
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|upper
decl_stmt|;
name|guchar
modifier|*
name|lower
decl_stmt|;
name|gint
name|row
decl_stmt|,
name|col
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
name|has_alpha
operator|=
name|gimp_drawable_has_alpha
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
comment|/* Get the size of the input image. (This will/must be the same    *  as the size of the output image.    */
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
name|bytes
operator|=
name|drawable
operator|->
name|bpp
expr_stmt|;
comment|/*  allocate row buffers  */
name|dest
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
name|bytes
argument_list|)
expr_stmt|;
name|upper
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
name|bytes
argument_list|)
expr_stmt|;
name|lower
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
name|bytes
argument_list|)
expr_stmt|;
comment|/*  initialize the pixel regions  */
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
name|width
argument_list|,
name|height
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/*  loop through the rows, performing our magic*/
for|for
control|(
name|row
operator|=
name|y1
init|;
name|row
operator|<
name|y2
condition|;
name|row
operator|++
control|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|dest
argument_list|,
name|x1
argument_list|,
name|row
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
comment|/* Only do interpolation if the row: 	 (1) Isn't one we want to keep 	 (2) Has both an upper and a lower row 	 Otherwise, just duplicate the source row       */
if|if
condition|(
operator|!
operator|(
operator|(
name|row
operator|%
literal|2
operator|==
name|DeinterlaceValue
operator|)
operator|||
operator|(
name|row
operator|-
literal|1
operator|<
literal|0
operator|)
operator|||
operator|(
name|row
operator|+
literal|1
operator|>=
name|height
operator|)
operator|)
condition|)
block|{
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|upper
argument_list|,
name|x1
argument_list|,
name|row
operator|-
literal|1
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|lower
argument_list|,
name|x1
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
name|guchar
modifier|*
name|upix
init|=
name|upper
decl_stmt|;
name|guchar
modifier|*
name|lpix
init|=
name|lower
decl_stmt|;
name|guchar
modifier|*
name|dpix
init|=
name|dest
decl_stmt|;
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
name|x2
operator|-
name|x1
condition|;
name|col
operator|++
control|)
block|{
name|gint
name|b
decl_stmt|;
name|guint
name|ualpha
init|=
name|upix
index|[
name|bytes
operator|-
literal|1
index|]
decl_stmt|;
name|guint
name|lalpha
init|=
name|lpix
index|[
name|bytes
operator|-
literal|1
index|]
decl_stmt|;
name|guint
name|alpha
init|=
name|ualpha
operator|+
name|lalpha
decl_stmt|;
if|if
condition|(
operator|(
name|dpix
index|[
name|bytes
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
name|bytes
operator|-
literal|1
condition|;
name|b
operator|++
control|)
name|dpix
index|[
name|b
index|]
operator|=
operator|(
name|upix
index|[
name|b
index|]
operator|*
name|ualpha
operator|+
name|lpix
index|[
name|b
index|]
operator|*
name|lalpha
operator|)
operator|/
name|alpha
expr_stmt|;
block|}
name|upix
operator|+=
name|bytes
expr_stmt|;
name|lpix
operator|+=
name|bytes
expr_stmt|;
name|dpix
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
else|else
block|{
for|for
control|(
name|col
operator|=
literal|0
init|;
name|col
operator|<
operator|(
name|x2
operator|-
name|x1
operator|)
operator|*
name|bytes
condition|;
name|col
operator|++
control|)
name|dest
index|[
name|col
index|]
operator|=
operator|(
name|upper
index|[
name|col
index|]
operator|+
name|lower
index|[
name|col
index|]
operator|)
operator|/
literal|2
expr_stmt|;
block|}
block|}
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest
argument_list|,
name|x1
argument_list|,
name|row
argument_list|,
name|x2
operator|-
name|x1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|5
operator|)
operator|==
literal|0
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|row
operator|/
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  update the deinterlaced region  */
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
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lower
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|upper
argument_list|)
expr_stmt|;
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
DECL|function|deinterlace_dialog (void)
name|deinterlace_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dlg
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"deinterlace"
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
literal|"Deinterlace"
argument_list|)
argument_list|,
literal|"deinterlace"
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"plug-in-deinterlace"
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
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|FALSE
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|DeinterlaceValue
argument_list|,
name|DeinterlaceValue
argument_list|,
name|_
argument_list|(
literal|"Keep o_dd Fields"
argument_list|)
argument_list|,
name|ODD_FIELDS
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Keep _even Fields"
argument_list|)
argument_list|,
name|EVEN_FIELDS
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
literal|12
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
name|frame
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
name|frame
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
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
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

