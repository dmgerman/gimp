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
file|"print-page-setup.h"
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
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"print"
end_define

begin_define
DECL|macro|PRINT_PROC_NAME
define|#
directive|define
name|PRINT_PROC_NAME
value|"file-print-gtk"
end_define

begin_define
DECL|macro|PAGE_SETUP_PROC_NAME
define|#
directive|define
name|PAGE_SETUP_PROC_NAME
value|"file-print-gtk-page-setup"
end_define

begin_define
DECL|macro|PRINT_TEMP_PROC_NAME
define|#
directive|define
name|PRINT_TEMP_PROC_NAME
value|"file-print-gtk-page-setup-notify-temp"
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
name|GimpPDBStatusType
name|print_image
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpPDBStatusType
name|page_setup
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_show_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|print_operation_set_name
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|gint
name|image_ID
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
name|gint32
modifier|*
name|image_ID
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
name|gint
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
name|gchar
modifier|*
name|print_temp_proc_name
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|print_temp_proc_install
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Keep a reference to the current GtkPrintOperation  *  for access by the temporary procedure.  */
end_comment

begin_decl_stmt
DECL|variable|print_operation
specifier|static
name|GtkPrintOperation
modifier|*
name|print_operation
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
literal|"Image to print"
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
literal|"Bill Skaggs, Sven Neumann, Stefan RÃ¶llin"
argument_list|,
literal|"Bill Skaggs<weskaggs@primate.ucdavis.edu>"
argument_list|,
literal|"2006, 2007"
argument_list|,
name|N_
argument_list|(
literal|"_Print..."
argument_list|)
argument_list|,
literal|"*"
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
name|gimp_install_procedure
argument_list|(
name|PAGE_SETUP_PROC_NAME
argument_list|,
name|N_
argument_list|(
literal|"Adjust page size and orientation for printing"
argument_list|)
argument_list|,
literal|"Adjust page size and orientation for printing for "
literal|"printing the image using the GTK+ Print API."
argument_list|,
literal|"Bill Skaggs, Sven Neumann, Stefan RÃ¶llin"
argument_list|,
literal|"Sven Neumann<sven@gimp.org>"
argument_list|,
literal|"2008"
argument_list|,
name|N_
argument_list|(
literal|"Page Set_up"
argument_list|)
argument_list|,
literal|"*"
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
name|PAGE_SETUP_PROC_NAME
argument_list|,
literal|"<Image>/File/Send"
argument_list|)
expr_stmt|;
if|#
directive|if
name|GTK_CHECK_VERSION
argument_list|(
literal|2
operator|,
literal|13
operator|,
literal|0
argument_list|)
name|gimp_plugin_icon_register
argument_list|(
name|PAGE_SETUP_PROC_NAME
argument_list|,
name|GIMP_ICON_TYPE_STOCK_ID
argument_list|,
operator|(
specifier|const
name|guint8
operator|*
operator|)
name|GTK_STOCK_PAGE_SETUP
argument_list|)
expr_stmt|;
endif|#
directive|endif
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
name|g_thread_init
argument_list|(
name|NULL
argument_list|)
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
name|status
operator|=
name|print_image
argument_list|(
name|image_ID
argument_list|,
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|name
argument_list|,
name|PAGE_SETUP_PROC_NAME
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
block|{
name|status
operator|=
name|page_setup
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|GIMP_PDB_CALLING_ERROR
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
name|GimpPDBStatusType
DECL|function|print_image (gint32 image_ID,gboolean interactive)
name|print_image
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|GtkPrintOperation
modifier|*
name|operation
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint32
name|orig_image_ID
init|=
name|image_ID
decl_stmt|;
name|gint32
name|drawable_ID
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|temp_proc
decl_stmt|;
name|PrintData
name|data
decl_stmt|;
name|GimpExportReturn
name|export
decl_stmt|;
comment|/* export the image */
name|export
operator|=
name|gimp_export_image
argument_list|(
operator|&
name|image_ID
argument_list|,
operator|&
name|drawable_ID
argument_list|,
name|NULL
argument_list|,
name|GIMP_EXPORT_CAN_HANDLE_RGB
operator||
name|GIMP_EXPORT_CAN_HANDLE_GRAY
operator||
name|GIMP_EXPORT_CAN_HANDLE_ALPHA
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|==
name|GIMP_EXPORT_CANCEL
condition|)
return|return
name|GIMP_PDB_EXECUTION_ERROR
return|;
name|operation
operator|=
name|gtk_print_operation_new
argument_list|()
expr_stmt|;
name|print_operation_set_name
argument_list|(
name|operation
argument_list|,
name|orig_image_ID
argument_list|)
expr_stmt|;
name|print_page_setup_load
argument_list|(
name|operation
argument_list|,
name|orig_image_ID
argument_list|)
expr_stmt|;
comment|/* fill in the PrintData struct */
name|data
operator|.
name|num_pages
operator|=
literal|1
expr_stmt|;
name|data
operator|.
name|image_id
operator|=
name|orig_image_ID
expr_stmt|;
name|data
operator|.
name|drawable_id
operator|=
name|drawable_ID
expr_stmt|;
name|data
operator|.
name|unit
operator|=
name|gimp_get_default_unit
argument_list|()
expr_stmt|;
name|data
operator|.
name|image_unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
name|data
operator|.
name|offset_x
operator|=
literal|0
expr_stmt|;
name|data
operator|.
name|offset_y
operator|=
literal|0
expr_stmt|;
name|data
operator|.
name|center
operator|=
name|CENTER_BOTH
expr_stmt|;
name|data
operator|.
name|use_full_page
operator|=
name|FALSE
expr_stmt|;
name|data
operator|.
name|operation
operator|=
name|operation
expr_stmt|;
name|gimp_image_get_resolution
argument_list|(
name|image_ID
argument_list|,
operator|&
name|data
operator|.
name|xres
argument_list|,
operator|&
name|data
operator|.
name|yres
argument_list|)
expr_stmt|;
name|load_print_settings
argument_list|(
operator|&
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|export
operator|!=
name|GIMP_EXPORT_EXPORT
condition|)
name|image_ID
operator|=
operator|-
literal|1
expr_stmt|;
name|gtk_print_operation_set_unit
argument_list|(
name|operation
argument_list|,
name|GTK_UNIT_POINTS
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
operator|&
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
operator|&
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
operator|&
name|image_ID
argument_list|)
expr_stmt|;
name|print_operation
operator|=
name|operation
expr_stmt|;
name|temp_proc
operator|=
name|print_temp_proc_install
argument_list|(
name|orig_image_ID
argument_list|)
expr_stmt|;
name|gimp_extension_enable
argument_list|()
expr_stmt|;
if|if
condition|(
name|interactive
condition|)
block|{
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|operation
argument_list|,
literal|"end-print"
argument_list|,
name|G_CALLBACK
argument_list|(
name|save_print_settings
argument_list|)
argument_list|,
operator|&
name|data
argument_list|)
expr_stmt|;
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
operator|&
name|data
argument_list|)
expr_stmt|;
name|gtk_print_operation_set_custom_tab_label
argument_list|(
name|operation
argument_list|,
name|_
argument_list|(
literal|"Image Settings"
argument_list|)
argument_list|)
expr_stmt|;
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
name|gimp_uninstall_temp_proc
argument_list|(
name|temp_proc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|temp_proc
argument_list|)
expr_stmt|;
name|print_operation
operator|=
name|NULL
expr_stmt|;
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_is_valid
argument_list|(
name|image_ID
argument_list|)
condition|)
name|gimp_image_delete
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|print_show_error
argument_list|(
name|error
operator|->
name|message
argument_list|,
name|interactive
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|GimpPDBStatusType
DECL|function|page_setup (gint32 image_ID)
name|page_setup
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
name|GtkPrintOperation
modifier|*
name|operation
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|gimp_ui_init
argument_list|(
name|PLUG_IN_BINARY
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|operation
operator|=
name|gtk_print_operation_new
argument_list|()
expr_stmt|;
name|print_page_setup_load
argument_list|(
name|operation
argument_list|,
name|image_ID
argument_list|)
expr_stmt|;
name|print_page_setup_dialog
argument_list|(
name|operation
argument_list|)
expr_stmt|;
name|print_page_setup_save
argument_list|(
name|operation
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
comment|/* now notify a running print procedure about this change */
name|name
operator|=
name|print_temp_proc_name
argument_list|(
name|image_ID
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
block|{
name|GimpParam
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
name|return_vals
operator|=
name|gimp_run_procedure
argument_list|(
name|name
argument_list|,
operator|&
name|n_return_vals
argument_list|,
name|GIMP_PDB_IMAGE
argument_list|,
name|image_ID
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|gimp_destroy_params
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|GIMP_PDB_SUCCESS
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_show_error (const gchar * message,gboolean interactive)
name|print_show_error
parameter_list|(
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|interactive
parameter_list|)
block|{
name|g_printerr
argument_list|(
literal|"Print: %s\n"
argument_list|,
name|message
argument_list|)
expr_stmt|;
if|if
condition|(
name|interactive
condition|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gtk_message_dialog_new
argument_list|(
name|NULL
argument_list|,
literal|0
argument_list|,
name|GTK_MESSAGE_ERROR
argument_list|,
name|GTK_BUTTONS_OK
argument_list|,
name|_
argument_list|(
literal|"An error occurred "
literal|"while trying to print:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_message_dialog_format_secondary_text
argument_list|(
name|GTK_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|message
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|print_operation_set_name (GtkPrintOperation * operation,gint image_ID)
name|print_operation_set_name
parameter_list|(
name|GtkPrintOperation
modifier|*
name|operation
parameter_list|,
name|gint
name|image_ID
parameter_list|)
block|{
name|gchar
modifier|*
name|name
init|=
name|gimp_image_get_name
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gtk_print_operation_set_job_name
argument_list|(
name|operation
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
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
name|gtk_print_operation_set_n_pages
argument_list|(
name|operation
argument_list|,
name|data
operator|->
name|num_pages
argument_list|)
expr_stmt|;
name|gtk_print_operation_set_use_full_page
argument_list|(
name|operation
argument_list|,
name|data
operator|->
name|use_full_page
argument_list|)
expr_stmt|;
name|gimp_progress_init
argument_list|(
name|_
argument_list|(
literal|"Printing"
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|end_print (GtkPrintOperation * operation,GtkPrintContext * context,gint32 * image_ID)
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
name|gint32
modifier|*
name|image_ID
parameter_list|)
block|{
comment|/* we don't need the export image any longer, delete it */
if|if
condition|(
name|gimp_image_is_valid
argument_list|(
operator|*
name|image_ID
argument_list|)
condition|)
block|{
name|gimp_image_delete
argument_list|(
operator|*
name|image_ID
argument_list|)
expr_stmt|;
operator|*
name|image_ID
operator|=
operator|-
literal|1
expr_stmt|;
block|}
name|gimp_progress_end
argument_list|()
expr_stmt|;
comment|/* generate events to solve the problems described in bug #466928 */
name|g_timeout_add_seconds
argument_list|(
literal|1
argument_list|,
operator|(
name|GSourceFunc
operator|)
name|gtk_true
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|draw_page (GtkPrintOperation * operation,GtkPrintContext * context,gint page_nr,PrintData * data)
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
name|gint
name|page_nr
parameter_list|,
name|PrintData
modifier|*
name|data
parameter_list|)
block|{
name|print_draw_page
argument_list|(
name|context
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_progress_update
argument_list|(
literal|1.0
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

begin_function
specifier|static
name|void
DECL|function|print_temp_proc_run (const gchar * name,gint nparams,const GimpParam * param,gint * nreturn_vals,GimpParam ** return_vals)
name|print_temp_proc_run
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
name|GIMP_PDB_SUCCESS
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
if|if
condition|(
name|print_operation
operator|&&
name|nparams
operator|==
literal|1
condition|)
name|print_page_setup_load
argument_list|(
name|print_operation
argument_list|,
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|print_temp_proc_name (gint32 image_ID)
name|print_temp_proc_name
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
return|return
name|g_strdup_printf
argument_list|(
name|PRINT_TEMP_PROC_NAME
literal|"-%d"
argument_list|,
name|image_ID
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|print_temp_proc_install (gint32 image_ID)
name|print_temp_proc_install
parameter_list|(
name|gint32
name|image_ID
parameter_list|)
block|{
specifier|static
specifier|const
name|GimpParamDef
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Image to print"
block|}
block|}
decl_stmt|;
name|gchar
modifier|*
name|name
init|=
name|print_temp_proc_name
argument_list|(
name|image_ID
argument_list|)
decl_stmt|;
name|gimp_install_temp_proc
argument_list|(
name|name
argument_list|,
literal|"DON'T USE THIS ONE"
argument_list|,
literal|"Temporary procedure to notify the Print plug-in "
literal|"about changes to the Page Setup."
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"Sven Neumann"
argument_list|,
literal|"2008"
argument_list|,
name|NULL
argument_list|,
literal|""
argument_list|,
name|GIMP_TEMPORARY
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
argument_list|,
name|print_temp_proc_run
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

end_unit

