begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* max_rgb.c -- This is a plug-in for the GIMP  * Author: Shuji Narazaki<narazaki@InetQ.or.jp>  * Time-stamp:<2000-02-08 16:26:24 yasuhiro>  * Version: 0.35  *  * Copyright (C) 1997 Shuji Narazaki<narazaki@InetQ.or.jp>  *  * May 2000 - tim copperfield [timecop@japan.co.jp]  *  * Added a preview mode.  After adding preview mode realised just exactly  * how useless this plugin is :)  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Replace them with the right ones */
end_comment

begin_define
DECL|macro|PLUG_IN_NAME
define|#
directive|define
name|PLUG_IN_NAME
value|"plug_in_max_rgb"
end_define

begin_define
DECL|macro|SHORT_NAME
define|#
directive|define
name|SHORT_NAME
value|"max_rgb"
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
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|GimpPDBStatusType
name|main_function
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|dialog
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
name|ok_callback
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

begin_function_decl
specifier|static
name|void
name|radio_callback
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

begin_enum
enum|enum
DECL|enum|__anon27942a5a0103
block|{
DECL|enumerator|MIN_CHANNELS
name|MIN_CHANNELS
init|=
literal|0
block|,
DECL|enumerator|MAX_CHANNELS
name|MAX_CHANNELS
init|=
literal|1
block|}
enum|;
end_enum

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27942a5a0208
block|{
DECL|member|max_p
name|gint
name|max_p
decl_stmt|;
DECL|typedef|ValueType
block|}
name|ValueType
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27942a5a0308
block|{
DECL|member|run
name|gint
name|run
decl_stmt|;
DECL|typedef|Interface
block|}
name|Interface
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|pvals
specifier|static
name|ValueType
name|pvals
init|=
block|{
name|MAX_CHANNELS
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|interface
specifier|static
name|Interface
name|interface
init|=
block|{
name|FALSE
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|run_mode
specifier|static
name|GimpRunMode
name|run_mode
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
literal|"Input image (not used)"
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
literal|"max_p"
block|,
literal|"1 for maximizing, 0 for minimizing"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_NAME
argument_list|,
literal|"Return an image in which each pixel holds only "
literal|"the channel that has the maximum value in three "
literal|"(red, green, blue) channels, and other channels "
literal|"are zero-cleared"
argument_list|,
literal|"the help is not yet written for this plug-in since none is needed."
argument_list|,
literal|"Shuji Narazaki (narazaki@InetQ.or.jp)"
argument_list|,
literal|"Shuji Narazaki"
argument_list|,
literal|"May 2000"
argument_list|,
name|N_
argument_list|(
literal|"<Image>/Filters/Colors/Max RGB..."
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|run (gchar * name,gint nparams,GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|run
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
name|nparams
parameter_list|,
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
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
name|GIMP_PDB_EXECUTION_ERROR
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
name|pvals
argument_list|)
expr_stmt|;
comment|/* Since a channel might be selected, we must check wheter RGB or not. */
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Max RGB: Can only operate on RGB drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|!
name|dialog
argument_list|(
name|drawable
argument_list|)
condition|)
return|return;
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
comment|/* You must copy the values of parameters to pvals or dialog variables. */
name|pvals
operator|.
name|max_p
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
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pvals
argument_list|)
expr_stmt|;
break|break;
block|}
name|status
operator|=
name|main_function
argument_list|(
name|drawable
argument_list|,
name|FALSE
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
operator|&&
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
name|gimp_set_data
argument_list|(
name|PLUG_IN_NAME
argument_list|,
operator|&
name|pvals
argument_list|,
sizeof|sizeof
argument_list|(
name|ValueType
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

begin_typedef
DECL|struct|__anon27942a5a0408
typedef|typedef
struct|struct
block|{
DECL|member|init_value
name|gint
name|init_value
decl_stmt|;
DECL|member|flag
name|gint
name|flag
decl_stmt|;
DECL|member|has_alpha
name|gboolean
name|has_alpha
decl_stmt|;
DECL|typedef|MaxRgbParam_t
block|}
name|MaxRgbParam_t
typedef|;
end_typedef

begin_function
specifier|static
name|void
DECL|function|max_rgb_func (guchar * src,guchar * dest,gint bpp,gpointer data)
name|max_rgb_func
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
name|bpp
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|MaxRgbParam_t
modifier|*
name|param
init|=
operator|(
name|MaxRgbParam_t
operator|*
operator|)
name|data
decl_stmt|;
name|gint
name|ch
decl_stmt|,
name|max_ch
init|=
literal|0
decl_stmt|;
name|guchar
name|max
decl_stmt|,
name|tmp_value
decl_stmt|;
name|max
operator|=
name|param
operator|->
name|init_value
expr_stmt|;
for|for
control|(
name|ch
operator|=
literal|0
init|;
name|ch
operator|<
literal|3
condition|;
name|ch
operator|++
control|)
if|if
condition|(
name|param
operator|->
name|flag
operator|*
name|max
operator|<=
name|param
operator|->
name|flag
operator|*
operator|(
name|tmp_value
operator|=
operator|(
operator|*
name|src
operator|++
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|max
operator|==
name|tmp_value
condition|)
block|{
name|max_ch
operator|+=
literal|1
operator|<<
name|ch
expr_stmt|;
block|}
else|else
block|{
name|max_ch
operator|=
literal|1
operator|<<
name|ch
expr_stmt|;
comment|/* clear memories of old channels */
name|max
operator|=
name|tmp_value
expr_stmt|;
block|}
block|}
name|dest
index|[
literal|0
index|]
operator|=
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
literal|0
operator|)
operator|)
condition|?
name|max
else|:
literal|0
expr_stmt|;
name|dest
index|[
literal|1
index|]
operator|=
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
literal|1
operator|)
operator|)
condition|?
name|max
else|:
literal|0
expr_stmt|;
name|dest
index|[
literal|2
index|]
operator|=
operator|(
name|max_ch
operator|&
operator|(
literal|1
operator|<<
literal|2
operator|)
operator|)
condition|?
name|max
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|param
operator|->
name|has_alpha
condition|)
name|dest
index|[
literal|3
index|]
operator|=
operator|*
name|src
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GimpPDBStatusType
DECL|function|main_function (GimpDrawable * drawable,gboolean preview_mode)
name|main_function
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|preview_mode
parameter_list|)
block|{
name|MaxRgbParam_t
name|param
decl_stmt|;
name|param
operator|.
name|init_value
operator|=
operator|(
name|pvals
operator|.
name|max_p
operator|>
literal|0
operator|)
condition|?
literal|0
else|:
literal|255
expr_stmt|;
name|param
operator|.
name|flag
operator|=
operator|(
literal|0
operator|<
name|pvals
operator|.
name|max_p
operator|)
condition|?
literal|1
else|:
operator|-
literal|1
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
if|if
condition|(
name|preview_mode
condition|)
block|{
name|gimp_fixme_preview_update
argument_list|(
name|preview
argument_list|,
name|max_rgb_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* normal mode */
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Max RGB: Scanning..."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rgn_iterate2
argument_list|(
name|drawable
argument_list|,
name|run_mode
argument_list|,
name|max_rgb_func
argument_list|,
operator|&
name|param
argument_list|)
expr_stmt|;
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_comment
comment|/* dialog stuff */
end_comment

begin_function
specifier|static
name|gint
DECL|function|dialog (GimpDrawable * drawable)
name|dialog
parameter_list|(
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
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|max
decl_stmt|;
name|GtkWidget
modifier|*
name|min
decl_stmt|;
name|gimp_ui_init
argument_list|(
literal|"max_rgb"
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
literal|"Max RGB"
argument_list|)
argument_list|,
literal|"max_rgb"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"filters/max_rgb.html"
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
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
name|GTK_STOCK_OK
argument_list|,
name|ok_callback
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
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dlg
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_main_quit
argument_list|)
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
name|drawable
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
name|main_function
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
operator|->
name|widget
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_radio_group_new2
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Parameter Settings"
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|radio_callback
argument_list|)
argument_list|,
operator|&
name|pvals
operator|.
name|max_p
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|pvals
operator|.
name|max_p
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Hold the Maximal Channels"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|MAX_CHANNELS
argument_list|)
argument_list|,
operator|&
name|max
argument_list|,
name|_
argument_list|(
literal|"Ho_ld the Minimal Channels"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|MIN_CHANNELS
argument_list|)
argument_list|,
operator|&
name|min
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|max
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|min
argument_list|)
argument_list|,
literal|"drawable"
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|frame
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
name|gtk_main
argument_list|()
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
return|return
name|interface
operator|.
name|run
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|radio_callback (GtkWidget * widget,gpointer data)
name|radio_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_radio_button_update
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"drawable"
argument_list|)
expr_stmt|;
name|main_function
argument_list|(
name|drawable
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ok_callback (GtkWidget * widget,gpointer data)
name|ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|interface
operator|.
name|run
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

end_unit

