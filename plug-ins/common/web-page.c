begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/* Webpage plug-in.  * Copyright (C) 2011 Mukund Sivaraman<muks@banu.com>.  * Portions are copyright of the author of the  * file-open-location-dialog.c code.  *  * TODO:  * - Add a font scale combo: default, larger, smaller etc.  * - Set GIMP as user agent  */
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
file|<webkit/webkit.h>
end_include

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_comment
comment|/* Defines */
end_comment

begin_define
DECL|macro|PLUG_IN_PROC
define|#
directive|define
name|PLUG_IN_PROC
value|"plug-in-web-page"
end_define

begin_define
DECL|macro|PLUG_IN_BINARY
define|#
directive|define
name|PLUG_IN_BINARY
value|"web-page"
end_define

begin_define
DECL|macro|MAX_URL_LEN
define|#
directive|define
name|MAX_URL_LEN
value|256
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2be254180108
block|{
DECL|member|url
name|char
modifier|*
name|url
decl_stmt|;
DECL|member|width
name|gint32
name|width
decl_stmt|;
DECL|typedef|WebpageVals
block|}
name|WebpageVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|webpagevals
specifier|static
name|WebpageVals
name|webpagevals
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2be254180208
block|{
DECL|member|url
name|char
name|url
index|[
name|MAX_URL_LEN
index|]
decl_stmt|;
DECL|member|width
name|gint32
name|width
decl_stmt|;
DECL|typedef|WebpageSaveVals
block|}
name|WebpageSaveVals
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|webpixbuf
specifier|static
name|GdkPixbuf
modifier|*
name|webpixbuf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|weberror
specifier|static
name|GError
modifier|*
name|weberror
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
name|gboolean
name|webpage_dialog
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint32
name|webpage_capture
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Global Variables */
end_comment

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
comment|/* run_proc   */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Functions */
end_comment

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
name|args
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"run-mode"
block|,
literal|"The run mode { RUN-INTERACTIVE (0), RUN-NONINTERACTIVE (1) }"
block|}
block|,
block|{
name|GIMP_PDB_STRING
block|,
literal|"url"
block|,
literal|"URL of the webpage to screenshot"
block|}
block|,
block|{
name|GIMP_PDB_INT32
block|,
literal|"width"
block|,
literal|"The width of the screenshot"
block|}
block|}
decl_stmt|;
specifier|static
specifier|const
name|GimpParamDef
name|return_vals
index|[]
init|=
block|{
block|{
name|GIMP_PDB_IMAGE
block|,
literal|"image"
block|,
literal|"Output image"
block|}
block|}
decl_stmt|;
name|gimp_install_procedure
argument_list|(
name|PLUG_IN_PROC
argument_list|,
name|N_
argument_list|(
literal|"Create an image of a webpage"
argument_list|)
argument_list|,
literal|"The plug-in allows you to take a screenshot "
literal|"of a webpage."
argument_list|,
literal|"Mukund Sivaraman<muks@banu.com>"
argument_list|,
literal|"2011"
argument_list|,
literal|"2011"
argument_list|,
name|N_
argument_list|(
literal|"From _Webpage..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PLUGIN
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|args
argument_list|)
argument_list|,
name|G_N_ELEMENTS
argument_list|(
name|return_vals
argument_list|)
argument_list|,
name|args
argument_list|,
name|return_vals
argument_list|)
expr_stmt|;
name|gimp_plugin_menu_register
argument_list|(
name|PLUG_IN_PROC
argument_list|,
literal|"<Image>/File/Create/Acquire"
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
name|GimpRunMode
name|run_mode
init|=
name|param
index|[
literal|0
index|]
operator|.
name|data
operator|.
name|d_int32
decl_stmt|;
name|GimpPDBStatusType
name|status
init|=
name|GIMP_PDB_EXECUTION_ERROR
decl_stmt|;
name|gint32
name|image_id
init|=
operator|-
literal|1
decl_stmt|;
specifier|static
name|GimpParam
name|values
index|[
literal|2
index|]
decl_stmt|;
name|WebpageSaveVals
name|save
init|=
block|{
literal|"http://www.gimp.org/"
block|,
literal|1024
block|}
decl_stmt|;
name|INIT_I18N
argument_list|()
expr_stmt|;
comment|/* initialize the return of the status */
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
comment|/* MUST call this before any RSVG funcs */
name|g_type_init
argument_list|()
expr_stmt|;
name|gimp_get_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|save
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|url
operator|=
name|g_strdup
argument_list|(
name|save
operator|.
name|url
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|width
operator|=
name|save
operator|.
name|width
expr_stmt|;
comment|/* how are we running today? */
switch|switch
condition|(
name|run_mode
condition|)
block|{
case|case
name|GIMP_RUN_INTERACTIVE
case|:
if|if
condition|(
name|webpage_dialog
argument_list|()
condition|)
name|status
operator|=
name|GIMP_PDB_SUCCESS
expr_stmt|;
else|else
name|status
operator|=
name|GIMP_PDB_CANCEL
expr_stmt|;
break|break;
case|case
name|GIMP_RUN_WITH_LAST_VALS
case|:
comment|/* This is currently not supported. */
break|break;
case|case
name|GIMP_RUN_NONINTERACTIVE
case|:
name|webpagevals
operator|.
name|url
operator|=
name|param
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
expr_stmt|;
name|webpagevals
operator|.
name|width
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
name|status
operator|=
name|GIMP_PDB_SUCCESS
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
name|image_id
operator|=
name|webpage_capture
argument_list|()
expr_stmt|;
if|if
condition|(
name|image_id
operator|==
operator|-
literal|1
condition|)
block|{
name|status
operator|=
name|GIMP_PDB_EXECUTION_ERROR
expr_stmt|;
if|if
condition|(
name|weberror
condition|)
block|{
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_string
operator|=
name|weberror
operator|->
name|message
expr_stmt|;
block|}
block|}
else|else
block|{
name|save
operator|.
name|width
operator|=
name|webpagevals
operator|.
name|width
expr_stmt|;
if|if
condition|(
name|strlen
argument_list|(
name|webpagevals
operator|.
name|url
argument_list|)
operator|<
name|MAX_URL_LEN
condition|)
block|{
name|strncpy
argument_list|(
name|save
operator|.
name|url
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|,
name|MAX_URL_LEN
argument_list|)
expr_stmt|;
name|save
operator|.
name|url
index|[
name|MAX_URL_LEN
operator|-
literal|1
index|]
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|memset
argument_list|(
name|save
operator|.
name|url
argument_list|,
literal|0
argument_list|,
name|MAX_URL_LEN
argument_list|)
expr_stmt|;
block|}
name|gimp_set_data
argument_list|(
name|PLUG_IN_PROC
argument_list|,
operator|&
name|save
argument_list|,
sizeof|sizeof
name|save
argument_list|)
expr_stmt|;
if|if
condition|(
name|run_mode
operator|==
name|GIMP_RUN_INTERACTIVE
condition|)
name|gimp_display_new
argument_list|(
name|image_id
argument_list|)
expr_stmt|;
operator|*
name|nreturn_vals
operator|=
literal|2
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|values
index|[
literal|1
index|]
operator|.
name|data
operator|.
name|d_image
operator|=
name|image_id
expr_stmt|;
block|}
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
DECL|function|webpage_dialog (void)
name|webpage_dialog
parameter_list|(
name|void
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|gint
name|status
decl_stmt|;
name|gboolean
name|ret
init|=
name|FALSE
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
literal|"Create from webpage"
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
name|_
argument_list|(
literal|"_Create"
argument_list|)
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
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gtk_dialog_get_content_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GIMP_STOCK_WEB
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
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
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Enter location (URI):"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_entry_set_activates_default
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|entry
argument_list|,
literal|400
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|entry
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|webpagevals
operator|.
name|url
condition|)
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Width (pixels):"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gimp_spin_button_new
argument_list|(
operator|&
name|adjustment
argument_list|,
name|webpagevals
operator|.
name|width
argument_list|,
literal|1
argument_list|,
literal|8192
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|spinbutton
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
name|spinbutton
argument_list|)
expr_stmt|;
name|status
operator|=
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|g_free
argument_list|(
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|url
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|width
operator|=
operator|(
name|gint
operator|)
name|gtk_adjustment_get_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|ret
operator|=
name|TRUE
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
return|return
name|ret
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|notify_progress_cb (WebKitWebView * view,GParamSpec * pspec,gpointer user_data)
name|notify_progress_cb
parameter_list|(
name|WebKitWebView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
specifier|static
name|gdouble
name|old_progress
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|progress
decl_stmt|;
name|g_object_get
argument_list|(
name|view
argument_list|,
literal|"progress"
argument_list|,
operator|&
name|progress
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|progress
operator|-
name|old_progress
operator|)
operator|>
literal|0.01
condition|)
block|{
name|gimp_progress_update
argument_list|(
name|progress
argument_list|)
expr_stmt|;
name|old_progress
operator|=
name|progress
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|load_error_cb (WebKitWebView * view,WebKitWebFrame * web_frame,gchar * uri,gpointer web_error,gpointer user_data)
name|load_error_cb
parameter_list|(
name|WebKitWebView
modifier|*
name|view
parameter_list|,
name|WebKitWebFrame
modifier|*
name|web_frame
parameter_list|,
name|gchar
modifier|*
name|uri
parameter_list|,
name|gpointer
name|web_error
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|weberror
operator|=
name|g_error_copy
argument_list|(
operator|(
name|GError
operator|*
operator|)
name|web_error
argument_list|)
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|notify_load_status_cb (WebKitWebView * view,GParamSpec * pspec,gpointer user_data)
name|notify_load_status_cb
parameter_list|(
name|WebKitWebView
modifier|*
name|view
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|WebKitLoadStatus
name|status
decl_stmt|;
name|g_object_get
argument_list|(
name|view
argument_list|,
literal|"load-status"
argument_list|,
operator|&
name|status
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|WEBKIT_LOAD_FINISHED
condition|)
block|{
if|if
condition|(
operator|!
name|weberror
condition|)
block|{
name|webpixbuf
operator|=
name|gtk_offscreen_window_get_pixbuf
argument_list|(
name|GTK_OFFSCREEN_WINDOW
argument_list|(
name|user_data
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gint32
DECL|function|webpage_capture (void)
name|webpage_capture
parameter_list|(
name|void
parameter_list|)
block|{
name|gint32
name|image
init|=
operator|-
literal|1
decl_stmt|;
name|gchar
modifier|*
name|scheme
decl_stmt|;
name|GtkWidget
modifier|*
name|window
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
if|if
condition|(
name|webpixbuf
condition|)
block|{
name|g_object_unref
argument_list|(
name|webpixbuf
argument_list|)
expr_stmt|;
name|webpixbuf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|weberror
condition|)
block|{
name|g_error_free
argument_list|(
name|weberror
argument_list|)
expr_stmt|;
name|weberror
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
operator|(
operator|!
name|webpagevals
operator|.
name|url
operator|)
operator|||
operator|(
name|strlen
argument_list|(
name|webpagevals
operator|.
name|url
argument_list|)
operator|==
literal|0
operator|)
condition|)
block|{
name|g_set_error
argument_list|(
operator|&
name|weberror
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"No URL was specified"
argument_list|)
argument_list|)
expr_stmt|;
return|return
operator|-
literal|1
return|;
block|}
name|scheme
operator|=
name|g_uri_parse_scheme
argument_list|(
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|scheme
condition|)
block|{
name|char
modifier|*
name|url
decl_stmt|;
comment|/* If we were not given a well-formed URL, make one. */
name|url
operator|=
name|g_strconcat
argument_list|(
literal|"http://"
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|url
operator|=
name|url
expr_stmt|;
name|g_free
argument_list|(
name|scheme
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|webpagevals
operator|.
name|width
operator|<
literal|32
condition|)
block|{
name|g_warning
argument_list|(
literal|"Width '%d' is too small. Clamped to 32."
argument_list|,
name|webpagevals
operator|.
name|width
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|width
operator|=
literal|32
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|webpagevals
operator|.
name|width
operator|>
literal|8192
condition|)
block|{
name|g_warning
argument_list|(
literal|"Width '%d' is too large. Clamped to 8192."
argument_list|,
name|webpagevals
operator|.
name|width
argument_list|)
expr_stmt|;
name|webpagevals
operator|.
name|width
operator|=
literal|8192
expr_stmt|;
block|}
name|window
operator|=
name|gtk_offscreen_window_new
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|window
argument_list|)
expr_stmt|;
name|view
operator|=
name|webkit_web_view_new
argument_list|()
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|view
argument_list|,
name|webpagevals
operator|.
name|width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|window
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"notify::progress"
argument_list|,
name|G_CALLBACK
argument_list|(
name|notify_progress_cb
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"load-error"
argument_list|,
name|G_CALLBACK
argument_list|(
name|load_error_cb
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
argument_list|,
literal|"notify::load-status"
argument_list|,
name|G_CALLBACK
argument_list|(
name|notify_load_status_cb
argument_list|)
argument_list|,
name|window
argument_list|)
expr_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Downloading webpage '%s'"
argument_list|)
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|webkit_web_view_open
argument_list|(
name|WEBKIT_WEB_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|window
argument_list|)
expr_stmt|;
if|if
condition|(
name|webpixbuf
condition|)
block|{
name|gint
name|width
decl_stmt|;
name|gint
name|height
decl_stmt|;
name|gint32
name|layer
decl_stmt|;
name|gimp_progress_init_printf
argument_list|(
name|_
argument_list|(
literal|"Transferring webpage image for '%s'"
argument_list|)
argument_list|,
name|webpagevals
operator|.
name|url
argument_list|)
expr_stmt|;
name|width
operator|=
name|gdk_pixbuf_get_width
argument_list|(
name|webpixbuf
argument_list|)
expr_stmt|;
name|height
operator|=
name|gdk_pixbuf_get_height
argument_list|(
name|webpixbuf
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_image_new
argument_list|(
name|width
argument_list|,
name|height
argument_list|,
name|GIMP_RGB
argument_list|)
expr_stmt|;
name|gimp_image_undo_disable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|layer
operator|=
name|gimp_layer_new_from_pixbuf
argument_list|(
name|image
argument_list|,
name|_
argument_list|(
literal|"Webpage"
argument_list|)
argument_list|,
name|webpixbuf
argument_list|,
literal|100
argument_list|,
name|GIMP_NORMAL_MODE
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gimp_image_insert_layer
argument_list|(
name|image
argument_list|,
name|layer
argument_list|,
operator|-
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_undo_enable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|webpixbuf
argument_list|)
expr_stmt|;
name|webpixbuf
operator|=
name|NULL
expr_stmt|;
block|}
return|return
name|image
return|;
block|}
end_function

end_unit

