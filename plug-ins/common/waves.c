begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/**************************************************  * file: waves/waves.c  *  * Copyright (c) 1997 Eric L. Hernes (erich@rrnet.com)  * All rights reserved.  *  * Redistribution and use in source and binary forms, with or without  * modification, are permitted provided that the following conditions  * are met:  * 1. Redistributions of source code must retain the above copyright  *    notice, this list of conditions and the following disclaimer.  * 2. The name of the author may not be used to endorse or promote products  *    derived from this software withough specific prior written permission  *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
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
value|"plug-in-waves"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"waves"
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2be74eee0103
block|{
DECL|enumerator|MODE_SMEAR
name|MODE_SMEAR
block|,
DECL|enumerator|MODE_BLACKEN
name|MODE_BLACKEN
DECL|typedef|BorderType
block|}
name|BorderType
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2be74eee0208
block|{
DECL|member|amplitude
name|gdouble
name|amplitude
decl_stmt|;
DECL|member|phase
name|gdouble
name|phase
decl_stmt|;
DECL|member|wavelength
name|gdouble
name|wavelength
decl_stmt|;
DECL|member|type
name|BorderType
name|type
decl_stmt|;
DECL|member|reflective
name|gboolean
name|reflective
decl_stmt|;
DECL|typedef|piArgs
block|}
name|piArgs
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|wvals
specifier|static
name|piArgs
name|wvals
init|=
block|{
literal|10.0
block|,
comment|/* amplitude  */
literal|0.0
block|,
comment|/* phase      */
literal|10.0
block|,
comment|/* wavelength */
name|MODE_SMEAR
block|,
comment|/* type       */
name|FALSE
comment|/* reflective */
block|}
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
name|nparam
parameter_list|,
specifier|const
name|GimpParam
modifier|*
name|param
parameter_list|,
name|gint
modifier|*
name|nretvals
parameter_list|,
name|GimpParam
modifier|*
modifier|*
name|retvals
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|waves
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
name|waves_dialog
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
name|waves_preview
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
name|void
name|wave
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dest
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bpp
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gdouble
name|amplitude
parameter_list|,
name|gdouble
name|wavelength
parameter_list|,
name|gdouble
name|phase
parameter_list|,
name|gboolean
name|smear
parameter_list|,
name|gboolean
name|reflective
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|WITHIN (a,b,c)
define|#
directive|define
name|WITHIN
parameter_list|(
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|)
value|((((a)<= (b))&& ((b)<= (c))) ? TRUE : FALSE)
end_define

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
literal|"The Image"
block|}
block|,
block|{
name|GIMP_PDB_DRAWABLE
block|,
literal|"drawable"
block|,
literal|"The Drawable"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"amplitude"
block|,
literal|"The Amplitude of the Waves"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"phase"
block|,
literal|"The Phase of the Waves"
block|}
block|,
block|{
name|GIMP_PDB_FLOAT
block|,
literal|"wavelength"
block|,
literal|"The Wavelength of the Waves"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"type"
block|,
literal|"Type of waves, black/smeared"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"reflective"
block|,
literal|"Use Reflection"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Distort the image with waves"
argument_list|)
argument_list|,
literal|"none yet"
argument_list|,
literal|"Eric L. Hernes, Stephen Norris"
argument_list|,
literal|"Stephen Norris"
argument_list|,
literal|"1997"
argument_list|,
name|N_
argument_list|(
literal|"_Waves..."
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
literal|"<Image>/Filters/Distorts"
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
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
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
name|INIT_I18N
argument_list|()
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
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
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
name|wvals
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|waves_dialog
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
literal|8
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
expr_stmt|;
block|}
else|else
block|{
name|wvals
operator|.
name|amplitude
operator|=
name|param
index|[
literal|3
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|wvals
operator|.
name|phase
operator|=
name|param
index|[
literal|4
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|wvals
operator|.
name|wavelength
operator|=
name|param
index|[
literal|5
index|]
operator|.
name|data
operator|.
name|d_float
expr_stmt|;
name|wvals
operator|.
name|type
operator|=
name|param
index|[
literal|6
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
name|wvals
operator|.
name|reflective
operator|=
name|param
index|[
literal|7
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
name|PLUG_IN_PROC
argument_list|,
operator|&
name|wvals
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
name|waves
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|wvals
argument_list|,
sizeof|sizeof
argument_list|(
name|piArgs
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|waves (GimpDrawable * drawable)
name|waves
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GimpPixelRgn
name|srcPr
decl_stmt|,
name|dstPr
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dst
decl_stmt|;
name|guint
name|width
decl_stmt|,
name|height
decl_stmt|,
name|bpp
decl_stmt|,
name|has_alpha
decl_stmt|;
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
name|bpp
operator|=
name|drawable
operator|->
name|bpp
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
name|dst
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
name|srcPr
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
name|dstPr
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
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|srcPr
argument_list|,
name|src
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|wave
argument_list|(
name|src
argument_list|,
name|dst
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|,
name|has_alpha
argument_list|,
name|wvals
operator|.
name|amplitude
argument_list|,
name|wvals
operator|.
name|wavelength
argument_list|,
name|wvals
operator|.
name|phase
argument_list|,
name|wvals
operator|.
name|type
operator|==
name|MODE_SMEAR
argument_list|,
name|wvals
operator|.
name|reflective
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_set_rect
argument_list|(
operator|&
name|dstPr
argument_list|,
name|dst
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dst
argument_list|)
expr_stmt|;
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
literal|0
argument_list|,
literal|0
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_displays_flush
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|waves_dialog (GimpDrawable * drawable)
name|waves_dialog
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|smear
decl_stmt|;
name|GtkWidget
modifier|*
name|blacken
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|adj
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
literal|"Waves"
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
name|gimp_zoom_preview_new
argument_list|(
name|drawable
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
name|waves_preview
argument_list|)
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_int_radio_group_new
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Mode"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|wvals
operator|.
name|type
argument_list|,
name|wvals
operator|.
name|type
argument_list|,
name|_
argument_list|(
literal|"_Smear"
argument_list|)
argument_list|,
name|MODE_SMEAR
argument_list|,
operator|&
name|smear
argument_list|,
name|_
argument_list|(
literal|"_Blacken"
argument_list|)
argument_list|,
name|MODE_BLACKEN
argument_list|,
operator|&
name|blacken
argument_list|,
name|NULL
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
name|g_signal_connect_swapped
argument_list|(
name|smear
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
name|blacken
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
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Reflective"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|wvals
operator|.
name|reflective
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
name|wvals
operator|.
name|reflective
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|toggle
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|3
argument_list|,
name|FALSE
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
name|adj
operator|=
name|gimp_scale_entry_new
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
literal|"_Amplitude:"
argument_list|)
argument_list|,
literal|140
argument_list|,
literal|6
argument_list|,
name|wvals
operator|.
name|amplitude
argument_list|,
literal|0.0
argument_list|,
literal|101.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|wvals
operator|.
name|amplitude
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"_Phase:"
argument_list|)
argument_list|,
literal|140
argument_list|,
literal|6
argument_list|,
name|wvals
operator|.
name|phase
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|2.0
argument_list|,
literal|5.0
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|wvals
operator|.
name|phase
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|adj
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Wavelength:"
argument_list|)
argument_list|,
literal|140
argument_list|,
literal|6
argument_list|,
name|wvals
operator|.
name|wavelength
argument_list|,
literal|0.1
argument_list|,
literal|50.0
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|wvals
operator|.
name|wavelength
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|adj
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_invalidate
argument_list|)
argument_list|,
name|preview
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

begin_function
specifier|static
name|void
DECL|function|waves_preview (GimpDrawable * drawable,GimpPreview * preview)
name|waves_preview
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
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|dest
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|gint
name|bpp
decl_stmt|;
name|src
operator|=
name|gimp_zoom_preview_get_source
argument_list|(
name|GIMP_ZOOM_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|,
operator|&
name|width
argument_list|,
operator|&
name|height
argument_list|,
operator|&
name|bpp
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
name|bpp
argument_list|)
expr_stmt|;
name|wave
argument_list|(
name|src
argument_list|,
name|dest
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|bpp
argument_list|,
name|bpp
operator|==
literal|2
operator|||
name|bpp
operator|==
literal|4
argument_list|,
name|wvals
operator|.
name|amplitude
operator|*
name|width
operator|/
name|drawable
operator|->
name|width
argument_list|,
name|wvals
operator|.
name|wavelength
operator|*
name|height
operator|/
name|drawable
operator|->
name|height
argument_list|,
name|wvals
operator|.
name|phase
argument_list|,
name|wvals
operator|.
name|type
operator|==
name|MODE_SMEAR
argument_list|,
name|wvals
operator|.
name|reflective
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_preview_draw_buffer
argument_list|(
name|preview
argument_list|,
name|dest
argument_list|,
name|width
operator|*
name|bpp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|dest
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Wave the image.  For each pixel in the destination image  * which is inside the selection, we compute the corresponding  * waved location in the source image.  We use bilinear  * interpolation to avoid ugly jaggies.  *  * Let's assume that we are operating on a circular area.  * Every point within<radius> distance of the wave center is  * waveed to its destination position.  *  * Basically, introduce a wave into the image. I made up the  * forumla initially, but it looks good. Quartic added the  * wavelength etc. to it while I was asleep :) Just goes to show  * we should work with people in different time zones more.  *  */
end_comment

begin_function
specifier|static
name|void
DECL|function|wave (guchar * src,guchar * dst,gint width,gint height,gint bypp,gboolean has_alpha,gdouble amplitude,gdouble wavelength,gdouble phase,gboolean smear,gboolean reflective,gboolean verbose)
name|wave
parameter_list|(
name|guchar
modifier|*
name|src
parameter_list|,
name|guchar
modifier|*
name|dst
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gint
name|bypp
parameter_list|,
name|gboolean
name|has_alpha
parameter_list|,
name|gdouble
name|amplitude
parameter_list|,
name|gdouble
name|wavelength
parameter_list|,
name|gdouble
name|phase
parameter_list|,
name|gboolean
name|smear
parameter_list|,
name|gboolean
name|reflective
parameter_list|,
name|gboolean
name|verbose
parameter_list|)
block|{
name|glong
name|rowsiz
decl_stmt|;
name|guchar
modifier|*
name|p
decl_stmt|;
name|guchar
modifier|*
name|dest
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
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|prog_interval
init|=
literal|0
decl_stmt|;
name|gint
name|x1_in
decl_stmt|,
name|y1_in
decl_stmt|,
name|x2_in
decl_stmt|,
name|y2_in
decl_stmt|;
name|gdouble
name|cen_x
decl_stmt|,
name|cen_y
decl_stmt|;
comment|/* Center of wave */
name|gdouble
name|xhsiz
decl_stmt|,
name|yhsiz
decl_stmt|;
comment|/* Half size of selection */
name|gdouble
name|radius
decl_stmt|,
name|radius2
decl_stmt|;
comment|/* Radius and radius^2 */
name|gdouble
name|amnt
decl_stmt|,
name|d
decl_stmt|;
name|gdouble
name|needx
decl_stmt|,
name|needy
decl_stmt|;
name|gdouble
name|dx
decl_stmt|,
name|dy
decl_stmt|;
name|gdouble
name|xscale
decl_stmt|,
name|yscale
decl_stmt|;
name|gint
name|xi
decl_stmt|,
name|yi
decl_stmt|;
name|guchar
modifier|*
name|values
index|[
literal|4
index|]
decl_stmt|;
name|guchar
name|zeroes
index|[
literal|4
index|]
init|=
block|{
literal|0
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
decl_stmt|;
name|phase
operator|=
name|phase
operator|*
name|G_PI
operator|/
literal|180.0
expr_stmt|;
name|rowsiz
operator|=
name|width
operator|*
name|bypp
expr_stmt|;
if|if
condition|(
name|verbose
condition|)
block|{
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Waving"
argument_list|)
argument_list|)
expr_stmt|;
name|prog_interval
operator|=
name|height
operator|/
literal|10
expr_stmt|;
block|}
name|x1
operator|=
name|y1
operator|=
literal|0
expr_stmt|;
name|x2
operator|=
name|width
expr_stmt|;
name|y2
operator|=
name|height
expr_stmt|;
comment|/* Center of selection */
name|cen_x
operator|=
call|(
name|double
call|)
argument_list|(
name|x2
operator|-
literal|1
operator|+
name|x1
argument_list|)
operator|/
literal|2.0
expr_stmt|;
name|cen_y
operator|=
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
literal|1
operator|+
name|y1
argument_list|)
operator|/
literal|2.0
expr_stmt|;
comment|/* Compute wave radii (semiaxes) */
name|xhsiz
operator|=
call|(
name|double
call|)
argument_list|(
name|x2
operator|-
name|x1
argument_list|)
operator|/
literal|2.0
expr_stmt|;
name|yhsiz
operator|=
call|(
name|double
call|)
argument_list|(
name|y2
operator|-
name|y1
argument_list|)
operator|/
literal|2.0
expr_stmt|;
comment|/* These are the necessary scaling factors to turn the wave      ellipse into a large circle */
if|if
condition|(
name|xhsiz
operator|<
name|yhsiz
condition|)
block|{
name|xscale
operator|=
name|yhsiz
operator|/
name|xhsiz
expr_stmt|;
name|yscale
operator|=
literal|1.0
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|xhsiz
operator|>
name|yhsiz
condition|)
block|{
name|xscale
operator|=
literal|1.0
expr_stmt|;
name|yscale
operator|=
name|xhsiz
operator|/
name|yhsiz
expr_stmt|;
block|}
else|else
block|{
name|xscale
operator|=
literal|1.0
expr_stmt|;
name|yscale
operator|=
literal|1.0
expr_stmt|;
block|}
name|radius
operator|=
name|MAX
argument_list|(
name|xhsiz
argument_list|,
name|yhsiz
argument_list|)
expr_stmt|;
name|radius2
operator|=
name|radius
operator|*
name|radius
expr_stmt|;
comment|/* Wave the image! */
name|dst
operator|+=
name|y1
operator|*
name|rowsiz
operator|+
name|x1
operator|*
name|bypp
expr_stmt|;
name|wavelength
operator|*=
literal|2
expr_stmt|;
for|for
control|(
name|y
operator|=
name|y1
init|;
name|y
operator|<
name|y2
condition|;
name|y
operator|++
control|)
block|{
name|dest
operator|=
name|dst
expr_stmt|;
if|if
condition|(
name|verbose
operator|&&
operator|(
name|y
operator|%
name|prog_interval
operator|==
literal|0
operator|)
condition|)
name|gimp_progress_update
argument_list|(
operator|(
name|double
operator|)
name|y
operator|/
operator|(
name|double
operator|)
name|height
argument_list|)
expr_stmt|;
for|for
control|(
name|x
operator|=
name|x1
init|;
name|x
operator|<
name|x2
condition|;
name|x
operator|++
control|)
block|{
comment|/* Distance from current point to wave center, scaled */
name|dx
operator|=
operator|(
name|x
operator|-
name|cen_x
operator|)
operator|*
name|xscale
expr_stmt|;
name|dy
operator|=
operator|(
name|y
operator|-
name|cen_y
operator|)
operator|*
name|yscale
expr_stmt|;
comment|/* Distance^2 to center of *circle* (our scaled ellipse) */
name|d
operator|=
name|sqrt
argument_list|(
name|dx
operator|*
name|dx
operator|+
name|dy
operator|*
name|dy
argument_list|)
expr_stmt|;
comment|/* Use the formula described above. */
comment|/* Calculate waved point and scale again to ellipsify */
comment|/*            * Reflective waves are strange - the effect is much            * more like a mirror which is in the shape of            * the wave than anything else.            */
if|if
condition|(
name|reflective
condition|)
block|{
name|amnt
operator|=
name|amplitude
operator|*
name|fabs
argument_list|(
name|sin
argument_list|(
operator|(
operator|(
name|d
operator|/
name|wavelength
operator|)
operator|*
operator|(
literal|2.0
operator|*
name|G_PI
operator|)
operator|+
name|phase
operator|)
argument_list|)
argument_list|)
expr_stmt|;
name|needx
operator|=
operator|(
name|amnt
operator|*
name|dx
operator|)
operator|/
name|xscale
operator|+
name|cen_x
expr_stmt|;
name|needy
operator|=
operator|(
name|amnt
operator|*
name|dy
operator|)
operator|/
name|yscale
operator|+
name|cen_y
expr_stmt|;
block|}
else|else
block|{
name|amnt
operator|=
name|amplitude
operator|*
name|sin
argument_list|(
operator|(
operator|(
name|d
operator|/
name|wavelength
operator|)
operator|*
operator|(
literal|2.0
operator|*
name|G_PI
operator|)
operator|+
name|phase
operator|)
argument_list|)
expr_stmt|;
name|needx
operator|=
operator|(
name|amnt
operator|+
name|dx
operator|)
operator|/
name|xscale
operator|+
name|cen_x
expr_stmt|;
name|needy
operator|=
operator|(
name|amnt
operator|+
name|dy
operator|)
operator|/
name|yscale
operator|+
name|cen_y
expr_stmt|;
block|}
comment|/* Calculations complete; now copy the proper pixel */
if|if
condition|(
name|smear
condition|)
block|{
name|xi
operator|=
name|CLAMP
argument_list|(
name|needx
argument_list|,
literal|0
argument_list|,
name|width
operator|-
literal|2
argument_list|)
expr_stmt|;
name|yi
operator|=
name|CLAMP
argument_list|(
name|needy
argument_list|,
literal|0
argument_list|,
name|height
operator|-
literal|2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|xi
operator|=
name|needx
expr_stmt|;
name|yi
operator|=
name|needy
expr_stmt|;
block|}
name|p
operator|=
name|src
operator|+
name|rowsiz
operator|*
name|yi
operator|+
name|xi
operator|*
name|bypp
expr_stmt|;
name|x1_in
operator|=
name|WITHIN
argument_list|(
literal|0
argument_list|,
name|xi
argument_list|,
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y1_in
operator|=
name|WITHIN
argument_list|(
literal|0
argument_list|,
name|yi
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
name|x2_in
operator|=
name|WITHIN
argument_list|(
literal|0
argument_list|,
name|xi
operator|+
literal|1
argument_list|,
name|width
operator|-
literal|1
argument_list|)
expr_stmt|;
name|y2_in
operator|=
name|WITHIN
argument_list|(
literal|0
argument_list|,
name|yi
operator|+
literal|1
argument_list|,
name|height
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|x1_in
operator|&&
name|y1_in
condition|)
name|values
index|[
literal|0
index|]
operator|=
name|p
expr_stmt|;
else|else
name|values
index|[
literal|0
index|]
operator|=
name|zeroes
expr_stmt|;
if|if
condition|(
name|x2_in
operator|&&
name|y1_in
condition|)
name|values
index|[
literal|1
index|]
operator|=
name|p
operator|+
name|bypp
expr_stmt|;
else|else
name|values
index|[
literal|1
index|]
operator|=
name|zeroes
expr_stmt|;
if|if
condition|(
name|x1_in
operator|&&
name|y2_in
condition|)
name|values
index|[
literal|2
index|]
operator|=
name|p
operator|+
name|rowsiz
expr_stmt|;
else|else
name|values
index|[
literal|2
index|]
operator|=
name|zeroes
expr_stmt|;
if|if
condition|(
name|x2_in
operator|&&
name|y2_in
condition|)
name|values
index|[
literal|3
index|]
operator|=
name|p
operator|+
name|bypp
operator|+
name|rowsiz
expr_stmt|;
else|else
name|values
index|[
literal|3
index|]
operator|=
name|zeroes
expr_stmt|;
name|gimp_bilinear_pixels_8
argument_list|(
name|dest
argument_list|,
name|needx
argument_list|,
name|needy
argument_list|,
name|bypp
argument_list|,
name|has_alpha
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|dest
operator|+=
name|bypp
expr_stmt|;
block|}
name|dst
operator|+=
name|rowsiz
expr_stmt|;
block|}
if|if
condition|(
name|verbose
condition|)
name|gimp_progress_update
argument_list|(
literal|1.0
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

