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
value|"plug-in-deinterlace"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"deinterlace"
end_define

begin_enum
enum|enum
DECL|enum|__anon2c88eaa70103
block|{
DECL|enumerator|ODD_FIELDS
name|ODD_FIELDS
block|,
DECL|enumerator|EVEN_FIELDS
name|EVEN_FIELDS
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2c88eaa70208
block|{
DECL|member|evenness
name|gint
name|evenness
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|DeinterlaceValues
block|}
name|DeinterlaceValues
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
name|void
name|deinterlace
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
name|deinterlace_dialog
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

begin_decl_stmt
DECL|variable|devals
specifier|static
name|DeinterlaceValues
name|devals
init|=
block|{
name|EVEN_FIELDS
block|,
comment|/* evenness */
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
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Fix images where every other row is missing"
argument_list|)
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|devals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|deinterlace_dialog
argument_list|(
name|drawable
argument_list|)
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
name|devals
operator|.
name|evenness
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|devals
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
literal|"Deinterlace"
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
argument_list|,
name|NULL
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|devals
argument_list|,
sizeof|sizeof
argument_list|(
name|DeinterlaceValues
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
DECL|function|deinterlace (GimpDrawable * drawable,GimpPreview * preview)
name|deinterlace
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
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gboolean
name|has_alpha
decl_stmt|;
name|guchar
modifier|*
name|dest
decl_stmt|;
name|guchar
modifier|*
name|dest_buffer
init|=
name|NULL
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
name|bytes
decl_stmt|;
name|bytes
operator|=
name|drawable
operator|->
name|bpp
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
name|dest_buffer
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|height
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_buffer
expr_stmt|;
block|}
else|else
block|{
name|gint
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
name|x
argument_list|,
operator|&
name|y
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
name|x
expr_stmt|;
name|height
operator|=
name|y2
operator|-
name|y
expr_stmt|;
name|dest
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|destPR
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
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|MAX
argument_list|(
name|y
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
argument_list|,
name|width
argument_list|,
name|MIN
argument_list|(
name|height
operator|+
literal|1
argument_list|,
name|drawable
operator|->
name|height
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
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
comment|/*  allocate row buffers  */
name|upper
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
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
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
comment|/*  loop through the rows, performing our magic  */
for|for
control|(
name|row
operator|=
name|y
init|;
name|row
operator|<
name|y
operator|+
name|height
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
name|x
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|row
operator|%
literal|2
operator|!=
name|devals
operator|.
name|evenness
condition|)
block|{
if|if
condition|(
name|row
operator|>
literal|0
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|upper
argument_list|,
name|x
argument_list|,
name|row
operator|-
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
else|else
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|upper
argument_list|,
name|x
argument_list|,
name|devals
operator|.
name|evenness
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|row
operator|+
literal|1
operator|<
name|drawable
operator|->
name|height
condition|)
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|lower
argument_list|,
name|x
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|width
argument_list|)
expr_stmt|;
else|else
name|gimp_pixel_rgn_get_row
argument_list|(
operator|&
name|srcPR
argument_list|,
name|lower
argument_list|,
name|x
argument_list|,
name|row
operator|-
literal|1
operator|+
name|devals
operator|.
name|evenness
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
name|has_alpha
condition|)
block|{
specifier|const
name|guchar
modifier|*
name|upix
init|=
name|upper
decl_stmt|;
specifier|const
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
name|width
condition|;
name|col
operator|++
control|)
block|{
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
name|width
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
operator|(
name|guint
operator|)
name|upper
index|[
name|col
index|]
operator|+
operator|(
name|guint
operator|)
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
if|if
condition|(
name|preview
condition|)
block|{
name|dest
operator|+=
name|width
operator|*
name|bytes
expr_stmt|;
block|}
else|else
block|{
name|gimp_pixel_rgn_set_row
argument_list|(
operator|&
name|destPR
argument_list|,
name|dest
argument_list|,
name|x
argument_list|,
name|row
argument_list|,
name|width
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|row
operator|%
literal|20
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
name|height
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dest_buffer
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|dest
operator|=
name|dest_buffer
expr_stmt|;
block|}
else|else
block|{
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
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
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
DECL|function|deinterlace_dialog (GimpDrawable * drawable)
name|deinterlace_dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|odd
decl_stmt|;
name|GtkWidget
modifier|*
name|even
decl_stmt|;
name|gboolean
name|run
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Deinterlace"
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
operator|&
name|devals
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
name|g_signal_connect_swapped
argument_list|(
name|preview
argument_list|,
literal|"invalidated"
argument_list|,
name|G_CALLBACK
argument_list|(
name|deinterlace
argument_list|)
argument_list|,
name|drawable
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
name|devals
operator|.
name|evenness
argument_list|,
name|devals
operator|.
name|evenness
argument_list|,
name|_
argument_list|(
literal|"Keep o_dd fields"
argument_list|)
argument_list|,
name|ODD_FIELDS
argument_list|,
operator|&
name|odd
argument_list|,
name|_
argument_list|(
literal|"Keep _even fields"
argument_list|)
argument_list|,
name|EVEN_FIELDS
argument_list|,
operator|&
name|even
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|odd
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
name|g_signal_connect_swapped
argument_list|(
name|even
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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

