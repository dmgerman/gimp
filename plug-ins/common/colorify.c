begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Colorify. Changes the pixel's luminosity to a specified color  * Copyright (C) 1997 Francisco Bustamante  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
value|"plug-in-colorify"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"colorify"
end_define

begin_define
DECL|macro|PLUG_IN_VERSION
define|#
directive|define
name|PLUG_IN_VERSION
value|"1.1"
end_define

begin_define
DECL|macro|COLOR_SIZE
define|#
directive|define
name|COLOR_SIZE
value|30
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
name|colorify
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
name|colorify_dialog
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
name|predefined_color_callback
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

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2ba8a10a0108
block|{
DECL|member|color
name|GimpRGB
name|color
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|typedef|ColorifyVals
block|}
name|ColorifyVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|cvals
specifier|static
name|ColorifyVals
name|cvals
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
name|TRUE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|button_color
specifier|static
name|GimpRGB
name|button_color
index|[]
init|=
block|{
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|,
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|,
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|}
block|,
block|{
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,
block|{
literal|0.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,
block|{
literal|1.0
block|,
literal|0.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|,
block|{
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|,
literal|1.0
block|}
block|, }
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
name|NULL
block|,
name|query
block|,
name|run
block|, }
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|custom_color_button
specifier|static
name|GtkWidget
modifier|*
name|custom_color_button
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lum_red_lookup
specifier|static
name|gint
name|lum_red_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lum_green_lookup
specifier|static
name|gint
name|lum_green_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|lum_blue_lookup
specifier|static
name|gint
name|lum_blue_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|final_red_lookup
specifier|static
name|gint
name|final_red_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|final_green_lookup
specifier|static
name|gint
name|final_green_lookup
index|[
literal|256
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|final_blue_lookup
specifier|static
name|gint
name|final_blue_lookup
index|[
literal|256
index|]
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
block|,
block|{
name|GIMP_PDB_COLOR
block|,
literal|"color"
block|,
literal|"Color to apply"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"Similar to the \"Color\" mode for layers."
argument_list|,
literal|"Makes an average of the RGB channels and uses it "
literal|"to set the color"
argument_list|,
literal|"Francisco Bustamante"
argument_list|,
literal|"Francisco Bustamante"
argument_list|,
name|PLUG_IN_VERSION
argument_list|,
name|N_
argument_list|(
literal|"_Colorify..."
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
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/Colors"
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
name|GimpPDBStatusType
name|status
decl_stmt|;
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
name|INIT_I18N
argument_list|()
expr_stmt|;
name|status
operator|=
name|GIMP_PDB_SUCCESS
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
name|cvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|colorify_dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
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
name|cvals
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
comment|/*  Possibly retrieve data  */
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
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
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Colorifying..."
argument_list|)
argument_list|)
expr_stmt|;
name|colorify
argument_list|(
name|drawable
argument_list|,
name|NULL
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
name|cvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ColorifyVals
argument_list|)
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
name|void
DECL|function|colorify_func (const guchar * src,guchar * dest,gint bpp,gpointer data)
name|colorify_func
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
name|gint
name|lum
decl_stmt|;
name|lum
operator|=
name|lum_red_lookup
index|[
name|src
index|[
literal|0
index|]
index|]
operator|+
name|lum_green_lookup
index|[
name|src
index|[
literal|1
index|]
index|]
operator|+
name|lum_blue_lookup
index|[
name|src
index|[
literal|2
index|]
index|]
expr_stmt|;
name|dest
index|[
literal|0
index|]
operator|=
name|final_red_lookup
index|[
name|lum
index|]
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
name|final_green_lookup
index|[
name|lum
index|]
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
name|final_blue_lookup
index|[
name|lum
index|]
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
DECL|function|colorify (GimpDrawable * drawable,GimpPreview * preview)
name|colorify
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
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|256
condition|;
name|i
operator|++
control|)
block|{
name|lum_red_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_RED
expr_stmt|;
name|lum_green_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_GREEN
expr_stmt|;
name|lum_blue_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|GIMP_RGB_LUMINANCE_BLUE
expr_stmt|;
name|final_red_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
operator|.
name|r
expr_stmt|;
name|final_green_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
operator|.
name|g
expr_stmt|;
name|final_blue_lookup
index|[
name|i
index|]
operator|=
name|i
operator|*
name|cvals
operator|.
name|color
operator|.
name|b
expr_stmt|;
block|}
if|if
condition|(
name|preview
condition|)
block|{
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bytes
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|;
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
name|src
operator|=
name|gimp_drawable_get_thumbnail_data
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bytes
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
name|colorify_func
argument_list|(
name|src
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|src
operator|+
name|i
operator|*
name|bytes
argument_list|,
name|bytes
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|src
argument_list|,
name|width
operator|*
name|bytes
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
literal|0
comment|/* unused */
argument_list|,
name|colorify_func
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|colorify_dialog (GimpDrawable * drawable)
name|colorify_dialog
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|color_area
decl_stmt|;
name|gint
name|i
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
literal|"Colorify"
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
name|gimp_aspect_preview_new
argument_list|(
name|drawable
argument_list|,
operator|&
name|cvals
operator|.
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
name|preview
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
name|colorify
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|7
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
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
name|table
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
name|table
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Custom color:"
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
name|label
argument_list|,
literal|4
argument_list|,
literal|6
argument_list|,
literal|0
argument_list|,
literal|1
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
name|label
argument_list|)
expr_stmt|;
name|custom_color_button
operator|=
name|gimp_color_button_new
argument_list|(
name|_
argument_list|(
literal|"Colorify Custom Color"
argument_list|)
argument_list|,
name|COLOR_SIZE
argument_list|,
name|COLOR_SIZE
argument_list|,
operator|&
name|cvals
operator|.
name|color
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|custom_color_button
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_button_get_color
argument_list|)
argument_list|,
operator|&
name|cvals
operator|.
name|color
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|custom_color_button
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
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|custom_color_button
argument_list|,
literal|6
argument_list|,
literal|7
argument_list|,
literal|0
argument_list|,
literal|1
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
name|custom_color_button
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
literal|7
condition|;
name|i
operator|++
control|)
block|{
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|button_color
index|[
name|i
index|]
argument_list|,
name|GIMP_COLOR_AREA_FLAT
argument_list|,
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|GTK_WIDGET
argument_list|(
name|color_area
argument_list|)
argument_list|,
name|COLOR_SIZE
argument_list|,
name|COLOR_SIZE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|color_area
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|predefined_color_callback
argument_list|)
argument_list|,
operator|&
name|button_color
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|color_area
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|button
argument_list|,
name|i
argument_list|,
name|i
operator|+
literal|1
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
name|button
argument_list|)
expr_stmt|;
block|}
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

begin_function
specifier|static
name|void
DECL|function|predefined_color_callback (GtkWidget * widget,gpointer data)
name|predefined_color_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_color_button_set_color
argument_list|(
name|GIMP_COLOR_BUTTON
argument_list|(
name|custom_color_button
argument_list|)
argument_list|,
operator|(
name|GimpRGB
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

