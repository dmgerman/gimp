begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<glib/gstdio.h>
end_include

begin_include
include|#
directive|include
file|"print.h"
end_include

begin_include
include|#
directive|include
file|"print-settings.h"
end_include

begin_include
include|#
directive|include
file|"print-page-layout.h"
end_include

begin_include
include|#
directive|include
file|"print-draw-page.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PRINT_PROC_NAME
define|#
directive|define
name|PRINT_PROC_NAME
value|"file-print-gtk"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"print"
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
name|void
name|begin_print
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|end_print
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|draw_page
parameter_list|(
name|GtkPrintOperation
modifier|*
name|print
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|int
name|page_nr
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|create_custom_widget
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|custom_widget_apply
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|print_preview
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintOperationPreview
modifier|*
name|preview
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|GtkWindow
modifier|*
name|parent
parameter_list|,
name|PrintData
modifier|*
name|data
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
name|PRINT_PROC_NAME
argument_list|,
name|N_
argument_list|(
literal|"Print the image"
argument_list|)
argument_list|,
literal|"Print the image using the GTK+ Print API."
argument_list|,
literal|"Bill Skaggs<weskaggs@primate.ucdavis.edu>"
argument_list|,
literal|"Bill Skaggs<weskaggs@primate.ucdavis.edu>"
argument_list|,
literal|"2006"
argument_list|,
name|N_
argument_list|(
literal|"_Print..."
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
name|PRINT_PROC_NAME
argument_list|,
literal|"<Image>/File/Send"
argument_list|)
expr_stmt|;
name|gimp_plugin_icon_register
argument_list|(
name|PRINT_PROC_NAME
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
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
name|PRINT_PROC_NAME
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
name|GtkPrintOperation
modifier|*
name|operation
init|=
name|gtk_print_operation_new
argument_list|()
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|PrintData
modifier|*
name|data
decl_stmt|;
name|data
operator|=
name|g_new0
argument_list|(
name|PrintData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|data
operator|->
name|num_pages
operator|=
literal|1
expr_stmt|;
name|data
operator|->
name|image_id
operator|=
name|image_ID
expr_stmt|;
name|data
operator|->
name|drawable_id
operator|=
name|drawable_ID
expr_stmt|;
name|data
operator|->
name|operation
operator|=
name|operation
expr_stmt|;
name|data
operator|->
name|print_size_changed
operator|=
name|FALSE
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
operator|&
name|data
operator|->
name|xres
argument_list|,
operator|&
name|data
operator|->
name|yres
argument_list|)
expr_stmt|;
name|load_print_settings
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"begin-print"
argument_list|,
name|G_CALLBACK
argument_list|(
name|begin_print
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"draw-page"
argument_list|,
name|G_CALLBACK
argument_list|(
name|draw_page
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"end-print"
argument_list|,
name|G_CALLBACK
argument_list|(
name|end_print
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|interactive
condition|)
block|{
name|GtkPrintOperationResult
name|result
decl_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"create-custom-widget"
argument_list|,
name|G_CALLBACK
argument_list|(
name|create_custom_widget
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"custom-widget-apply"
argument_list|,
name|G_CALLBACK
argument_list|(
name|custom_widget_apply
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|operation
argument_list|,
literal|"preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|print_preview
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gtk_print_operation_set_custom_tab_label
argument_list|(
name|operation
argument_list|,
name|_
argument_list|(
literal|"Layout"
argument_list|)
argument_list|)
expr_stmt|;
name|result
operator|=
name|gtk_print_operation_run
argument_list|(
name|operation
argument_list|,
name|GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|result
condition|)
block|{
case|case
name|GTK_PRINT_OPERATION_RESULT_APPLY
case|:
case|case
name|GTK_PRINT_OPERATION_RESULT_IN_PROGRESS
case|:
name|save_print_settings
argument_list|(
name|data
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_PRINT_OPERATION_RESULT_ERROR
case|:
case|case
name|GTK_PRINT_OPERATION_RESULT_CANCEL
case|:
break|break;
block|}
block|}
else|else
block|{
name|gtk_print_operation_run
argument_list|(
name|operation
argument_list|,
name|GTK_PRINT_OPERATION_ACTION_PRINT
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_message
argument_list|(
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|begin_print (GtkPrintOperation * operation,GtkPrintContext * context,PrintData * data)
name|begin_print
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|data
operator|->
name|num_pages
operator|=
literal|1
expr_stmt|;
name|gtk_print_operation_set_n_pages
argument_list|(
name|operation
argument_list|,
name|data
operator|->
name|num_pages
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|end_print (GtkPrintOperation * operation,GtkPrintContext * context,PrintData * data)
name|end_print
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|GtkPrintSettings
modifier|*
name|settings
decl_stmt|;
name|settings
operator|=
name|gtk_print_operation_get_print_settings
argument_list|(
name|operation
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_page (GtkPrintOperation * operation,GtkPrintContext * context,int page_nr,PrintData * data)
name|draw_page
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|int
name|page_nr
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|draw_page_cairo
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * This callback creates a "custom" widget that gets inserted into the  * print operation dialog.  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|create_custom_widget (GtkPrintOperation * operation,PrintData * data)
name|create_custom_widget
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
return|return
name|print_page_layout_gui
argument_list|(
name|data
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  * This function is called once before printing begins, and should be  * used to apply any changes that have been made to the contents of the  * custom widget, since it is not guaranteed to be around later.  This  * function is guaranteed to be called at least once, even if printing  * is cancelled.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|custom_widget_apply (GtkPrintOperation * operation,GtkWidget * widget,PrintData * data)
name|custom_widget_apply
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
if|if
condition|(
name|data
operator|->
name|print_size_changed
condition|)
block|{
name|gimp_image_undo_group_start
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
name|gimp_image_set_resolution
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|data
operator|->
name|xres
argument_list|,
name|data
operator|->
name|yres
argument_list|)
expr_stmt|;
name|gimp_image_set_unit
argument_list|(
name|data
operator|->
name|image_id
argument_list|,
name|data
operator|->
name|unit
argument_list|)
expr_stmt|;
name|gimp_image_undo_group_end
argument_list|(
name|data
operator|->
name|image_id
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|PREVIEW_SCALE
define|#
directive|define
name|PREVIEW_SCALE
value|72
end_define

begin_function
specifier|static
name|gboolean
DECL|function|print_preview (GtkPrintOperation * operation,GtkPrintOperationPreview * preview,GtkPrintContext * context,GtkWindow * parent,PrintData * data)
name|print_preview
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|GtkPrintOperationPreview
modifier|*
name|preview
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|GtkWindow
modifier|*
name|parent
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|GtkPageSetup
modifier|*
name|page_setup
init|=
name|gtk_print_context_get_page_setup
argument_list|(
name|context
argument_list|)
decl_stmt|;
name|GtkPaperSize
modifier|*
name|paper_size
decl_stmt|;
name|gdouble
name|paper_width
decl_stmt|;
name|gdouble
name|paper_height
decl_stmt|;
name|gdouble
name|top_margin
decl_stmt|;
name|gdouble
name|bottom_margin
decl_stmt|;
name|gdouble
name|left_margin
decl_stmt|;
name|gdouble
name|right_margin
decl_stmt|;
name|gint
name|preview_width
decl_stmt|;
name|gint
name|preview_height
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|GtkPageOrientation
name|orientation
decl_stmt|;
name|paper_size
operator|=
name|gtk_page_setup_get_paper_size
argument_list|(
name|page_setup
argument_list|)
expr_stmt|;
name|paper_width
operator|=
name|gtk_paper_size_get_width
argument_list|(
name|paper_size
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
name|paper_height
operator|=
name|gtk_paper_size_get_height
argument_list|(
name|paper_size
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
name|top_margin
operator|=
name|gtk_page_setup_get_top_margin
argument_list|(
name|page_setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
name|bottom_margin
operator|=
name|gtk_page_setup_get_bottom_margin
argument_list|(
name|page_setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
name|left_margin
operator|=
name|gtk_page_setup_get_left_margin
argument_list|(
name|page_setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
name|right_margin
operator|=
name|gtk_page_setup_get_right_margin
argument_list|(
name|page_setup
argument_list|,
name|GTK_UNIT_INCH
argument_list|)
expr_stmt|;
comment|/* the print context does not have the page orientation, it is transformed */
name|orientation
operator|=
name|data
operator|->
name|orientation
expr_stmt|;
if|if
condition|(
name|orientation
operator|==
name|GTK_PAGE_ORIENTATION_PORTRAIT
operator|||
name|orientation
operator|==
name|GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT
condition|)
block|{
name|preview_width
operator|=
name|PREVIEW_SCALE
operator|*
name|paper_width
expr_stmt|;
name|preview_height
operator|=
name|PREVIEW_SCALE
operator|*
name|paper_height
expr_stmt|;
block|}
else|else
block|{
name|preview_width
operator|=
name|PREVIEW_SCALE
operator|*
name|paper_height
expr_stmt|;
name|preview_height
operator|=
name|PREVIEW_SCALE
operator|*
name|paper_width
expr_stmt|;
block|}
name|surface
operator|=
name|cairo_image_surface_create
argument_list|(
name|CAIRO_FORMAT_RGB24
argument_list|,
name|preview_width
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
if|if
condition|(
name|CAIRO_STATUS_SUCCESS
operator|!=
name|cairo_surface_status
argument_list|(
name|surface
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Unable to create preview (not enough memory?)"
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|cr
operator|=
name|cairo_create
argument_list|(
name|surface
argument_list|)
expr_stmt|;
name|gtk_print_context_set_cairo_context
argument_list|(
name|context
argument_list|,
name|cr
argument_list|,
name|PREVIEW_SCALE
argument_list|,
name|PREVIEW_SCALE
argument_list|)
expr_stmt|;
comment|/* fill page with white */
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cairo_new_path
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_rectangle
argument_list|(
name|cr
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|preview_width
argument_list|,
name|preview_height
argument_list|)
expr_stmt|;
name|cairo_fill
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|left_margin
operator|*
name|PREVIEW_SCALE
argument_list|,
name|right_margin
operator|*
name|PREVIEW_SCALE
argument_list|)
expr_stmt|;
if|if
condition|(
name|draw_page_cairo
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
condition|)
block|{
name|cairo_status_t
name|status
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gimp_temp_name
argument_list|(
literal|"png"
argument_list|)
expr_stmt|;
name|status
operator|=
name|cairo_surface_write_to_png
argument_list|(
name|surface
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|cairo_destroy
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_surface_destroy
argument_list|(
name|surface
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|CAIRO_STATUS_SUCCESS
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|dialog
operator|=
name|gtk_dialog_new
argument_list|()
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Print Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_file
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|g_unlink
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|image
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
name|image
argument_list|)
expr_stmt|;
name|gtk_dialog_run
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

end_unit

