begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
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
file|<string.h>
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
file|<libgnomeprint/gnome-print.h>
end_include

begin_include
include|#
directive|include
file|<libgnomeprint/gnome-print-job.h>
end_include

begin_include
include|#
directive|include
file|<libgnomeprintui/gnome-print-dialog.h>
end_include

begin_include
include|#
directive|include
file|<libgnomeprintui/gnome-print-job-preview.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PROC_NAME
define|#
directive|define
name|PROC_NAME
value|"file-print-gnome"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"gnomeprint"
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
name|gboolean
name|print_image
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GnomePrintJob
modifier|*
name|print_job_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|print_job_do
parameter_list|(
name|GnomePrintJob
modifier|*
name|job
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_drawable
parameter_list|(
name|GnomePrintContext
modifier|*
name|context
parameter_list|,
name|GnomePrintConfig
modifier|*
name|config
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_fit_size
parameter_list|(
name|GnomePrintConfig
modifier|*
name|config
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
modifier|*
name|scale_x
parameter_list|,
name|gdouble
modifier|*
name|scale_y
parameter_list|,
name|gdouble
modifier|*
name|trans_x
parameter_list|,
name|gdouble
modifier|*
name|trans_y
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
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GimpParamDef
name|print_args
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
literal|"Drawable to print"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PROC_NAME
argument_list|,
name|N_
argument_list|(
literal|"Print the image using the GNOME Print system."
argument_list|)
argument_list|,
literal|"FIXME: write help"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"2005"
argument_list|,
name|N_
argument_list|(
literal|"_GNOME Print..."
argument_list|)
argument_list|,
literal|"GRAY, RGB*"
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|print_args
argument_list|)
argument_list|,
literal|0
argument_list|,
name|print_args
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PROC_NAME
argument_list|,
literal|"<Image>/File/Send"
argument_list|)
expr_stmt|;
name|gimp_plugin_icon_register
argument_list|(
name|PROC_NAME
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
name|GTK_STOCK_PRINT
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
literal|2
index|]
decl_stmt|;
name|GimpRunMode
name|run_mode
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_SUCCESS
decl_stmt|;
name|gint32
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
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
name|GIMP_PDB_EXECUTION_ERROR
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
name|drawable_ID
operator|=
name|param
index|[
literal|2
index|]
operator|.
name|data
operator|.
name|d_int32
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PROC_NAME
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|print_image
argument_list|(
name|image_ID
argument_list|,
name|drawable_ID
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
block|}
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|print_image (gint32 image_ID,gint32 drawable_ID,gboolean interactive)
name|print_image
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|GnomePrintJob
modifier|*
name|job
init|=
name|print_job_new
argument_list|()
decl_stmt|;
name|gboolean
name|done
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|interactive
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|gint
name|response
decl_stmt|;
name|dialog
operator|=
name|gnome_print_dialog_new
argument_list|(
name|job
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|_
argument_list|(
literal|"Print"
argument_list|)
argument_list|,
name|GNOME_PRINT_DIALOG_COPIES
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
do|do
block|{
switch|switch
condition|(
name|response
operator|=
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|GNOME_PRINT_DIALOG_RESPONSE_PRINT
case|:
break|break;
case|case
name|GNOME_PRINT_DIALOG_RESPONSE_PREVIEW
case|:
block|{
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
if|if
condition|(
operator|!
name|done
condition|)
name|done
operator|=
name|print_job_do
argument_list|(
name|job
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gnome_print_job_preview_new
argument_list|(
name|job
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|_
argument_list|(
literal|"Print Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_modal
argument_list|(
name|GTK_WINDOW
argument_list|(
name|preview
argument_list|)
argument_list|,
name|TRUE
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
name|gtk_main
argument_list|()
expr_stmt|;
block|}
break|break;
case|case
name|GNOME_PRINT_DIALOG_RESPONSE_CANCEL
case|:
break|break;
block|}
block|}
do|while
condition|(
name|response
operator|==
name|GNOME_PRINT_DIALOG_RESPONSE_PREVIEW
condition|)
do|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
if|if
condition|(
name|response
operator|==
name|GNOME_PRINT_DIALOG_RESPONSE_CANCEL
condition|)
block|{
name|g_object_unref
argument_list|(
name|job
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
if|if
condition|(
operator|!
name|done
condition|)
name|done
operator|=
name|print_job_do
argument_list|(
name|job
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|gnome_print_job_print
argument_list|(
name|job
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|job
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GnomePrintJob
modifier|*
DECL|function|print_job_new (void)
name|print_job_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GnomePrintConfig
modifier|*
name|config
decl_stmt|;
name|GnomePrintJob
modifier|*
name|job
decl_stmt|;
name|config
operator|=
name|gnome_print_config_default
argument_list|()
expr_stmt|;
name|job
operator|=
name|gnome_print_job_new
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
return|return
name|job
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|print_job_do (GnomePrintJob * job,gint32 drawable_ID)
name|print_job_do
parameter_list|(
name|GnomePrintJob
modifier|*
name|job
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GnomePrintContext
modifier|*
name|context
decl_stmt|;
name|GnomePrintConfig
modifier|*
name|config
decl_stmt|;
name|context
operator|=
name|gnome_print_job_get_context
argument_list|(
name|job
argument_list|)
expr_stmt|;
name|config
operator|=
name|gnome_print_job_get_config
argument_list|(
name|job
argument_list|)
expr_stmt|;
name|print_drawable
argument_list|(
name|context
argument_list|,
name|config
argument_list|,
name|drawable_ID
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|config
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gnome_print_job_close
argument_list|(
name|job
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_drawable (GnomePrintContext * context,GnomePrintConfig * config,gint32 drawable_ID)
name|print_drawable
parameter_list|(
name|GnomePrintContext
modifier|*
name|context
parameter_list|,
name|GnomePrintConfig
modifier|*
name|config
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_drawable_get
argument_list|(
name|drawable_ID
argument_list|)
decl_stmt|;
name|GimpPixelRgn
name|region
decl_stmt|;
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint
name|rowstride
decl_stmt|;
name|guchar
modifier|*
name|pixels
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gdouble
name|scale_x
decl_stmt|;
name|gdouble
name|scale_y
decl_stmt|;
name|gdouble
name|trans_x
decl_stmt|;
name|gdouble
name|trans_y
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
name|rowstride
operator|=
name|width
operator|*
name|drawable
operator|->
name|bpp
expr_stmt|;
name|pixels
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|height
operator|*
name|rowstride
argument_list|)
expr_stmt|;
name|gimp_pixel_rgn_init
argument_list|(
operator|&
name|region
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
name|gimp_pixel_rgn_get_rect
argument_list|(
operator|&
name|region
argument_list|,
name|pixels
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
name|gimp_drawable_detach
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|name
operator|=
name|gimp_drawable_get_name
argument_list|(
name|drawable_ID
argument_list|)
expr_stmt|;
name|gnome_print_beginpage
argument_list|(
name|context
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|print_fit_size
argument_list|(
name|config
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
operator|&
name|scale_x
argument_list|,
operator|&
name|scale_y
argument_list|,
operator|&
name|trans_x
argument_list|,
operator|&
name|trans_y
argument_list|)
expr_stmt|;
name|gnome_print_gsave
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gnome_print_scale
argument_list|(
name|context
argument_list|,
name|scale_x
argument_list|,
name|scale_y
argument_list|)
expr_stmt|;
name|gnome_print_translate
argument_list|(
name|context
argument_list|,
name|trans_x
argument_list|,
name|trans_y
argument_list|)
expr_stmt|;
name|gnome_print_moveto
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gnome_print_lineto
argument_list|(
name|context
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gnome_print_lineto
argument_list|(
name|context
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gnome_print_lineto
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gnome_print_lineto
argument_list|(
name|context
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gnome_print_stroke
argument_list|(
name|context
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|drawable_ID
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|gnome_print_rgbimage
argument_list|(
name|context
argument_list|,
name|pixels
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|gnome_print_rgbaimage
argument_list|(
name|context
argument_list|,
name|pixels
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|gnome_print_grayimage
argument_list|(
name|context
argument_list|,
name|pixels
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"drawable type not implemented"
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
name|gnome_print_grestore
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|gnome_print_showpage
argument_list|(
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_fit_size (GnomePrintConfig * config,gint width,gint height,gdouble * scale_x,gdouble * scale_y,gdouble * trans_x,gdouble * trans_y)
name|print_fit_size
parameter_list|(
name|GnomePrintConfig
modifier|*
name|config
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|gdouble
modifier|*
name|scale_x
parameter_list|,
name|gdouble
modifier|*
name|scale_y
parameter_list|,
name|gdouble
modifier|*
name|trans_x
parameter_list|,
name|gdouble
modifier|*
name|trans_y
parameter_list|)
block|{
specifier|const
name|GnomePrintUnit
modifier|*
name|base
decl_stmt|;
specifier|const
name|GnomePrintUnit
modifier|*
name|unit
decl_stmt|;
name|gdouble
name|paper_width
decl_stmt|;
name|gdouble
name|paper_height
decl_stmt|;
name|gdouble
name|margin_bottom
decl_stmt|;
name|gdouble
name|margin_right
decl_stmt|;
name|gdouble
name|margin_left
decl_stmt|;
name|gdouble
name|margin_top
decl_stmt|;
name|base
operator|=
name|gnome_print_unit_get_identity
argument_list|(
name|GNOME_PRINT_UNIT_DIMENSIONLESS
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_WIDTH
argument_list|,
operator|&
name|paper_width
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|paper_width
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_HEIGHT
argument_list|,
operator|&
name|paper_height
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|paper_height
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_MARGIN_BOTTOM
argument_list|,
operator|&
name|margin_bottom
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|margin_bottom
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_MARGIN_TOP
argument_list|,
operator|&
name|margin_top
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|margin_top
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_MARGIN_LEFT
argument_list|,
operator|&
name|margin_left
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|margin_left
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|gnome_print_config_get_length
argument_list|(
name|config
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|GNOME_PRINT_KEY_PAPER_MARGIN_RIGHT
argument_list|,
operator|&
name|margin_right
argument_list|,
operator|&
name|unit
argument_list|)
expr_stmt|;
name|gnome_print_convert_distance
argument_list|(
operator|&
name|margin_right
argument_list|,
name|unit
argument_list|,
name|base
argument_list|)
expr_stmt|;
name|paper_width
operator|-=
name|margin_left
operator|+
name|margin_right
expr_stmt|;
name|paper_height
operator|-=
name|margin_top
operator|+
name|margin_left
expr_stmt|;
operator|*
name|scale_x
operator|=
name|paper_width
expr_stmt|;
operator|*
name|scale_y
operator|=
name|paper_height
expr_stmt|;
operator|*
name|trans_x
operator|=
name|margin_left
expr_stmt|;
operator|*
name|trans_y
operator|=
name|margin_bottom
expr_stmt|;
block|}
end_function

end_unit

