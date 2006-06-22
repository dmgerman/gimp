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
file|"libgimp/stdplugins-intl.h"
end_include

begin_define
DECL|macro|PROC_NAME
define|#
directive|define
name|PROC_NAME
value|"file-print-gtk"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"gtkprint"
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
name|print
parameter_list|,
name|GtkPrintContext
modifier|*
name|context
parameter_list|,
name|gpointer
name|user_data
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
name|gpointer
name|user_data
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
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|write_print_settings_to_file
parameter_list|(
name|GtkPrintSettings
modifier|*
name|settings
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|add_setting_to_key_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|load_print_settings_from_file
parameter_list|(
name|GtkPrintSettings
modifier|*
name|settings
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2b6e36a40108
block|{
DECL|member|num_pages
name|gint
name|num_pages
decl_stmt|;
DECL|member|drawable_id
name|gint32
name|drawable_id
decl_stmt|;
DECL|typedef|PrintData
block|}
name|PrintData
typedef|;
end_typedef

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
name|PROC_NAME
argument_list|,
name|N_
argument_list|(
literal|"Print the image using the Gtk Print system"
argument_list|)
argument_list|,
literal|"FIXME: write help"
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
name|GtkPrintOperation
modifier|*
name|operation
init|=
name|gtk_print_operation_new
argument_list|()
decl_stmt|;
name|GtkPrintSettings
modifier|*
name|settings
init|=
name|gtk_print_settings_new
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
if|if
condition|(
name|load_print_settings_from_file
argument_list|(
name|settings
argument_list|)
condition|)
name|gtk_print_operation_set_print_settings
argument_list|(
name|operation
argument_list|,
name|settings
argument_list|)
expr_stmt|;
comment|/* begin junk */
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
name|drawable_id
operator|=
name|drawable_ID
expr_stmt|;
comment|/* end junk */
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
name|res
decl_stmt|;
name|res
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
if|if
condition|(
name|res
operator|==
name|GTK_PRINT_OPERATION_RESULT_APPLY
condition|)
block|{
name|settings
operator|=
name|gtk_print_operation_get_print_settings
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|settings
condition|)
name|write_print_settings_to_file
argument_list|(
name|settings
argument_list|)
expr_stmt|;
block|}
block|}
else|else
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
name|g_object_unref
argument_list|(
name|operation
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
name|g_message
argument_list|(
name|error
operator|->
name|message
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
DECL|function|begin_print (GtkPrintOperation * operation,GtkPrintContext * context,gpointer user_data)
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
name|gpointer
name|user_data
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
operator|(
name|PrintData
operator|*
operator|)
name|user_data
decl_stmt|;
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
DECL|function|end_print (GtkPrintOperation * operation,GtkPrintContext * context,gpointer user_data)
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
name|gpointer
name|user_data
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
DECL|function|draw_page (GtkPrintOperation * operation,GtkPrintContext * context,int page_nr,gpointer user_data)
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
name|gpointer
name|user_data
parameter_list|)
block|{
name|PrintData
modifier|*
name|data
init|=
operator|(
name|PrintData
operator|*
operator|)
name|user_data
decl_stmt|;
name|cairo_t
modifier|*
name|cr
decl_stmt|;
name|gdouble
name|cr_width
decl_stmt|;
name|gdouble
name|cr_height
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
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
name|cairo_format_t
name|format
decl_stmt|;
name|cairo_surface_t
modifier|*
name|surface
decl_stmt|;
name|cr
operator|=
name|gtk_print_context_get_cairo_context
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cr_width
operator|=
name|gtk_print_context_get_width
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|cr_height
operator|=
name|gtk_print_context_get_height
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_drawable_get
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
expr_stmt|;
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
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|data
operator|->
name|drawable_id
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB_IMAGE
case|:
name|format
operator|=
name|CAIRO_FORMAT_RGB24
expr_stmt|;
break|break;
case|case
name|GIMP_RGBA_IMAGE
case|:
name|format
operator|=
name|CAIRO_FORMAT_ARGB32
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY_IMAGE
case|:
name|format
operator|=
name|CAIRO_FORMAT_A8
expr_stmt|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"drawable type not implemented"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
return|return;
break|break;
block|}
name|surface
operator|=
name|cairo_image_surface_create_for_data
argument_list|(
name|pixels
argument_list|,
name|format
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
name|rowstride
argument_list|)
expr_stmt|;
name|cairo_set_source_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
literal|0
argument_list|,
literal|0
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
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|cairo_clip
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|cairo_mask_surface
argument_list|(
name|cr
argument_list|,
name|surface
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|pixels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|write_print_settings_to_file (GtkPrintSettings * settings)
name|write_print_settings_to_file
parameter_list|(
name|GtkPrintSettings
modifier|*
name|settings
parameter_list|)
block|{
name|gchar
modifier|*
name|fname
decl_stmt|;
name|FILE
modifier|*
name|settings_file
decl_stmt|;
name|GKeyFile
modifier|*
name|key_file
init|=
name|g_key_file_new
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|contents
decl_stmt|;
name|gsize
name|length
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|g_key_file_set_list_separator
argument_list|(
name|key_file
argument_list|,
literal|'='
argument_list|)
expr_stmt|;
name|gtk_print_settings_foreach
argument_list|(
name|settings
argument_list|,
name|add_setting_to_key_file
argument_list|,
name|key_file
argument_list|)
expr_stmt|;
name|contents
operator|=
name|g_key_file_to_data
argument_list|(
name|key_file
argument_list|,
operator|&
name|length
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|error
condition|)
block|{
name|g_message
argument_list|(
literal|"Unable to get contents of settings key file.\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|fname
operator|=
name|g_strconcat
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|"print-settings"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|settings_file
operator|=
name|fopen
argument_list|(
name|fname
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|settings_file
condition|)
block|{
name|g_message
argument_list|(
literal|"Unable to create save file for print settings.\n"
argument_list|)
expr_stmt|;
return|return;
block|}
name|fwrite
argument_list|(
name|contents
argument_list|,
sizeof|sizeof
argument_list|(
name|gchar
argument_list|)
argument_list|,
name|length
argument_list|,
name|settings_file
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|settings_file
argument_list|)
expr_stmt|;
name|g_key_file_free
argument_list|(
name|key_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|contents
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fname
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|add_setting_to_key_file (const gchar * key,const gchar * value,gpointer data)
name|add_setting_to_key_file
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
specifier|const
name|gchar
modifier|*
name|value
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GKeyFile
modifier|*
name|key_file
init|=
name|data
decl_stmt|;
name|g_key_file_set_value
argument_list|(
name|key_file
argument_list|,
literal|"settings"
argument_list|,
name|key
argument_list|,
name|value
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|load_print_settings_from_file (GtkPrintSettings * settings)
name|load_print_settings_from_file
parameter_list|(
name|GtkPrintSettings
modifier|*
name|settings
parameter_list|)
block|{
name|GKeyFile
modifier|*
name|key_file
init|=
name|g_key_file_new
argument_list|()
decl_stmt|;
name|gchar
modifier|*
name|fname
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|keys
decl_stmt|;
name|gsize
name|n_keys
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_key_file_set_list_separator
argument_list|(
name|key_file
argument_list|,
literal|'='
argument_list|)
expr_stmt|;
name|fname
operator|=
name|g_strconcat
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
literal|"print-settings"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_key_file_load_from_file
argument_list|(
name|key_file
argument_list|,
name|fname
argument_list|,
name|G_KEY_FILE_NONE
argument_list|,
operator|&
name|error
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|keys
operator|=
name|g_key_file_get_keys
argument_list|(
name|key_file
argument_list|,
literal|"settings"
argument_list|,
operator|&
name|n_keys
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|keys
condition|)
block|{
name|g_message
argument_list|(
literal|"Error reading print settings keys: %s\n"
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_keys
condition|;
name|i
operator|++
control|)
block|{
name|gchar
modifier|*
name|value
init|=
name|g_key_file_get_value
argument_list|(
name|key_file
argument_list|,
literal|"settings"
argument_list|,
name|keys
index|[
name|i
index|]
argument_list|,
operator|&
name|error
argument_list|)
decl_stmt|;
name|gtk_print_settings_set
argument_list|(
name|settings
argument_list|,
name|keys
index|[
name|i
index|]
argument_list|,
name|value
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|value
argument_list|)
expr_stmt|;
block|}
name|g_key_file_free
argument_list|(
name|key_file
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|fname
argument_list|)
expr_stmt|;
name|g_strfreev
argument_list|(
name|keys
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

