begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfileselection.c  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_comment
comment|/* Needed here by Win32 gcc compilation */
end_comment

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpfileselection.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISDIR
end_ifndef

begin_define
DECL|macro|S_ISDIR (m)
define|#
directive|define
name|S_ISDIR
parameter_list|(
name|m
parameter_list|)
value|((m)& _S_IFDIR)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|S_ISREG
end_ifndef

begin_define
DECL|macro|S_ISREG (m)
define|#
directive|define
name|S_ISREG
parameter_list|(
name|m
parameter_list|)
value|((m)& _S_IFREG)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_enum
enum|enum
DECL|enum|__anon299fe2870103
block|{
DECL|enumerator|FILENAME_CHANGED
name|FILENAME_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_class_init
parameter_list|(
name|GimpFileSelectionClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_init
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_entry_callback
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
name|gint
name|gimp_file_selection_entry_focus_out_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_browse_callback
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
name|gimp_file_selection_check_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|gimp_file_selection_signals
specifier|static
name|guint
name|gimp_file_selection_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkHBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_file_selection_get_type (void)
name|gimp_file_selection_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|selection_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|selection_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|selection_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpFileSelectionClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_file_selection_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpFileSelection
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_file_selection_init
block|,       }
decl_stmt|;
name|selection_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_HBOX
argument_list|,
literal|"GimpFileSelection"
argument_list|,
operator|&
name|selection_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|selection_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_class_init (GimpFileSelectionClass * klass)
name|gimp_file_selection_class_init
parameter_list|(
name|GimpFileSelectionClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|gimp_file_selection_signals
index|[
name|FILENAME_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"filename_changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpFileSelectionClass
argument_list|,
name|filename_changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_file_selection_destroy
expr_stmt|;
name|klass
operator|->
name|filename_changed
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_init (GimpFileSelection * selection)
name|gimp_file_selection_init
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|)
block|{
name|selection
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
name|selection
operator|->
name|file_selection
operator|=
name|NULL
expr_stmt|;
name|selection
operator|->
name|check_valid
operator|=
name|FALSE
expr_stmt|;
name|selection
operator|->
name|file_exists
operator|=
name|NULL
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|selection
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|selection
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|selection
operator|->
name|browse_button
operator|=
name|gtk_button_new_with_label
argument_list|(
literal|" ... "
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|selection
argument_list|)
argument_list|,
name|selection
operator|->
name|browse_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|selection
operator|->
name|browse_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_selection_browse_callback
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|selection
operator|->
name|browse_button
argument_list|)
expr_stmt|;
name|selection
operator|->
name|entry
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|selection
argument_list|)
argument_list|,
name|selection
operator|->
name|entry
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_selection_entry_callback
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
literal|"focus_out_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_selection_entry_focus_out_callback
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_destroy (GtkObject * object)
name|gimp_file_selection_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|selection
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|selection
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|file_selection
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
expr_stmt|;
name|selection
operator|->
name|file_selection
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|selection
operator|->
name|title
condition|)
block|{
name|g_free
argument_list|(
name|selection
operator|->
name|title
argument_list|)
expr_stmt|;
name|selection
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_selection_new:  * @title: The title of the #GtkFileSelection dialog.  * @filename: The initial filename.  * @dir_only: #TRUE if the file selection should accept directories only.  * @check_valid: #TRUE if the widget should check if the entered file  *               really exists.  *  * Creates a new #GimpFileSelection widget.  *  * Returns: A pointer to the new #GimpFileSelection widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_selection_new (const gchar * title,const gchar * filename,gboolean dir_only,gboolean check_valid)
name|gimp_file_selection_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
name|gboolean
name|dir_only
parameter_list|,
name|gboolean
name|check_valid
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|selection
decl_stmt|;
name|selection
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILE_SELECTION
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|selection
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|selection
operator|->
name|dir_only
operator|=
name|dir_only
expr_stmt|;
name|selection
operator|->
name|check_valid
operator|=
name|check_valid
expr_stmt|;
if|if
condition|(
name|check_valid
condition|)
block|{
name|selection
operator|->
name|file_exists
operator|=
name|gtk_image_new_from_stock
argument_list|(
name|GTK_STOCK_NO
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|selection
argument_list|)
argument_list|,
name|selection
operator|->
name|file_exists
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
name|selection
operator|->
name|file_exists
argument_list|)
expr_stmt|;
block|}
name|gimp_file_selection_set_filename
argument_list|(
name|selection
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|selection
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_selection_get_filename:  * @selection: The file selection you want to know the filename from.  *  * Note that you have to g_free() the returned string.  *  * Returns: The file or directory the user has entered.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_file_selection_get_filename (GimpFileSelection * selection)
name|gimp_file_selection_get_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|selection
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_selection_set_filename:  * @selection: The file selection you want to set the filename for.  * @filename: The new filename.  *  * If you specified @check_valid as #TRUE in gimp_file_selection_new()  * the #GimpFileSelection will immediately check the validity of the file  * name.  *  */
end_comment

begin_function
name|void
DECL|function|gimp_file_selection_set_filename (GimpFileSelection * selection,const gchar * filename)
name|gimp_file_selection_set_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|selection
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|""
argument_list|)
expr_stmt|;
comment|/*  update everything    */
name|gimp_file_selection_entry_callback
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
operator|(
name|gpointer
operator|)
name|selection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_entry_callback (GtkWidget * widget,gpointer data)
name|gimp_file_selection_entry_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|selection
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|selection
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  filenames still need more sanity checking    *  (erase double G_DIR_SEPARATORS, ...)    */
name|filename
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|filename
operator|=
name|g_strstrip
argument_list|(
name|filename
argument_list|)
expr_stmt|;
while|while
condition|(
operator|(
operator|(
name|len
operator|=
name|strlen
argument_list|(
name|filename
argument_list|)
operator|)
operator|>
literal|1
operator|)
operator|&&
operator|(
name|filename
index|[
name|len
operator|-
literal|1
index|]
operator|==
name|G_DIR_SEPARATOR
operator|)
condition|)
name|filename
index|[
name|len
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
name|gimp_file_selection_entry_callback
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
name|gimp_file_selection_entry_callback
argument_list|,
name|selection
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|file_selection
condition|)
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gimp_file_selection_check_filename
argument_list|(
name|selection
argument_list|)
expr_stmt|;
name|gtk_editable_set_position
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|selection
argument_list|,
name|gimp_file_selection_signals
index|[
name|FILENAME_CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_file_selection_entry_focus_out_callback (GtkWidget * widget,GdkEvent * event,gpointer data)
name|gimp_file_selection_entry_focus_out_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_file_selection_entry_callback
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  local callbacks of gimp_file_selection_browse_callback()  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_filesel_ok_callback (GtkWidget * widget,gpointer data)
name|gimp_file_selection_filesel_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|selection
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|selection
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
expr_stmt|;
comment|/*  update everything  */
name|gimp_file_selection_entry_callback
argument_list|(
name|selection
operator|->
name|entry
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_browse_callback (GtkWidget * widget,gpointer data)
name|gimp_file_selection_browse_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|selection
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|selection
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|file_selection
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|selection
operator|->
name|dir_only
condition|)
block|{
name|selection
operator|->
name|file_selection
operator|=
name|gtk_file_selection_new
argument_list|(
name|selection
operator|->
name|title
condition|?
name|selection
operator|->
name|title
else|:
name|_
argument_list|(
literal|"Select Folder"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  hiding these widgets uses internal gtk+ knowledge, but it's 	   *  easier than creating my own directory browser -- michael 	   */
name|gtk_widget_hide
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|fileop_del_file
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|file_list
operator|->
name|parent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|selection
operator|->
name|file_selection
operator|=
name|gtk_file_selection_new
argument_list|(
name|selection
operator|->
name|title
condition|?
name|selection
operator|->
name|title
else|:
name|_
argument_list|(
literal|"Select File"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|,
literal|"file_select"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
comment|/* slightly compress the dialog */
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|button_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|ok_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_selection_filesel_ok_callback
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|selection_entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_selection_filesel_ok_callback
argument_list|)
argument_list|,
name|selection
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
operator|->
name|cancel_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|selection
operator|->
name|file_selection
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|selection
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|selection
operator|->
name|file_selection
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|selection
operator|->
name|file_selection
argument_list|)
expr_stmt|;
block|}
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|selection
operator|->
name|file_selection
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_check_filename (GimpFileSelection * selection)
name|gimp_file_selection_check_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|selection
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gboolean
name|exists
decl_stmt|;
if|if
condition|(
operator|!
name|selection
operator|->
name|check_valid
condition|)
return|return;
if|if
condition|(
name|selection
operator|->
name|file_exists
operator|==
name|NULL
condition|)
return|return;
name|filename
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|selection
operator|->
name|entry
argument_list|)
argument_list|,
literal|0
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|selection
operator|->
name|dir_only
condition|)
name|exists
operator|=
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
expr_stmt|;
else|else
name|exists
operator|=
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gtk_image_set_from_stock
argument_list|(
name|GTK_IMAGE
argument_list|(
name|selection
operator|->
name|file_exists
argument_list|)
argument_list|,
name|exists
condition|?
name|GTK_STOCK_YES
else|:
name|GTK_STOCK_NO
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

