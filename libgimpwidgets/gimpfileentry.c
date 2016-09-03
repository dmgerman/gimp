begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpfileentry.c  * Copyright (C) 1999-2004 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|"gimpfileentry.h"
end_include

begin_include
include|#
directive|include
file|"gimphelpui.h"
end_include

begin_include
include|#
directive|include
file|"gimpicons.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpfileentry  * @title: GimpFileEntry  * @short_description: Widget for entering a filename.  * @see_also: #GimpPathEditor  *  * This widget is used to enter filenames or directories.  *  * There is a #GtkEntry for entering the filename manually and a "..."  * button which will pop up a #GtkFileChooserDialog.  *  * You can restrict the #GimpFileEntry to directories. In this  * case the filename listbox of the #GtkFileChooser dialog will be  * set to directory mode.  *  * If you specify @check_valid as #TRUE in gimp_file_entry_new() the  * entered filename will be checked for validity and a pixmap will be  * shown which indicates if the file exists or not.  *  * Whenever the user changes the filename, the "filename_changed"  * signal will be emitted.  **/
end_comment

begin_enum
enum|enum
DECL|enum|__anon2870b6000103
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
name|gimp_file_entry_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_entry_entry_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_entry_entry_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gint
name|gimp_file_entry_entry_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_entry_file_manager_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_entry_browse_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_file_entry_check_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFileEntry
argument_list|,
argument|gimp_file_entry
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_file_entry_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|gimp_file_entry_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_class_init (GimpFileEntryClass * klass)
name|gimp_file_entry_class_init
parameter_list|(
name|GimpFileEntryClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
comment|/**    * GimpFileEntry::filename-changed:    *    * This signal is emitted whenever the user changes the filename.    **/
name|gimp_file_entry_signals
index|[
name|FILENAME_CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"filename-changed"
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
name|GimpFileEntryClass
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
name|dispose
operator|=
name|gimp_file_entry_dispose
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
DECL|function|gimp_file_entry_init (GimpFileEntry * entry)
name|gimp_file_entry_init
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|entry
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|file_dialog
operator|=
name|NULL
expr_stmt|;
name|entry
operator|->
name|check_valid
operator|=
name|FALSE
expr_stmt|;
name|entry
operator|->
name|file_exists
operator|=
name|NULL
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|GIMP_STOCK_FILE_MANAGER
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
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
name|gimp_file_entry_file_manager_clicked
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|button
argument_list|,
name|_
argument_list|(
literal|"Show file location in the file manager"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|->
name|browse_button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|entry
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
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|browse_button
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
literal|"document-open"
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|entry
operator|->
name|browse_button
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|browse_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_entry_browse_clicked
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|entry
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
name|entry
argument_list|)
argument_list|,
name|entry
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
name|gtk_widget_show
argument_list|(
name|entry
operator|->
name|entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_entry_entry_changed
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_entry_entry_activate
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
literal|"focus-out-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_entry_entry_focus_out
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_dispose (GObject * object)
name|gimp_file_entry_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFileEntry
modifier|*
name|entry
init|=
name|GIMP_FILE_ENTRY
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|entry
operator|->
name|file_dialog
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|entry
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|entry
operator|->
name|file_dialog
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|entry
operator|->
name|title
condition|)
block|{
name|g_free
argument_list|(
name|entry
operator|->
name|title
argument_list|)
expr_stmt|;
name|entry
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_entry_new:  * @title:       The title of the #GimpFileEntry dialog.  * @filename:    The initial filename.  * @dir_only:    %TRUE if the file entry should accept directories only.  * @check_valid: %TRUE if the widget should check if the entered file  *               really exists.  *  * You should use #GtkFileChooserButton instead.  *  * Returns: A pointer to the new #GimpFileEntry widget.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_entry_new (const gchar * title,const gchar * filename,gboolean dir_only,gboolean check_valid)
name|gimp_file_entry_new
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
name|GimpFileEntry
modifier|*
name|entry
decl_stmt|;
name|entry
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILE_ENTRY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|entry
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|entry
operator|->
name|dir_only
operator|=
name|dir_only
expr_stmt|;
name|entry
operator|->
name|check_valid
operator|=
name|check_valid
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|entry
operator|->
name|browse_button
argument_list|,
name|dir_only
condition|?
name|_
argument_list|(
literal|"Open a file selector to browse your folders"
argument_list|)
else|:
name|_
argument_list|(
literal|"Open a file selector to browse your files"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|check_valid
condition|)
block|{
name|entry
operator|->
name|file_exists
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
literal|"gtk-no"
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|entry
argument_list|)
argument_list|,
name|entry
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
name|entry
operator|->
name|file_exists
argument_list|)
expr_stmt|;
block|}
name|gimp_file_entry_set_filename
argument_list|(
name|entry
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|entry
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_entry_get_filename:  * @entry: The file entry you want to know the filename from.  *  * Note that you have to g_free() the returned string.  *  * Returns: The file or directory the user has entered.  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_file_entry_get_filename (GimpFileEntry * entry)
name|gimp_file_entry_get_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|utf8
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
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
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|utf8
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
return|return
name|filename
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_file_entry_set_filename:  * @entry:    The file entry you want to set the filename for.  * @filename: The new filename.  *  * If you specified @check_valid as %TRUE in gimp_file_entry_new()  * the #GimpFileEntry will immediately check the validity of the file  * name.  **/
end_comment

begin_function
name|void
DECL|function|gimp_file_entry_set_filename (GimpFileEntry * entry,const gchar * filename)
name|gimp_file_entry_set_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
condition|)
name|utf8
operator|=
name|g_filename_to_utf8
argument_list|(
name|filename
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
else|else
name|utf8
operator|=
name|g_strdup
argument_list|(
literal|""
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
operator|->
name|entry
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
comment|/*  update everything    */
name|gimp_file_entry_entry_activate
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_entry_changed (GtkWidget * widget,GtkWidget * button)
name|gimp_file_entry_entry_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|button
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|text
init|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
decl_stmt|;
if|if
condition|(
name|text
operator|&&
name|strlen
argument_list|(
name|text
argument_list|)
condition|)
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_entry_activate (GtkWidget * widget,GimpFileEntry * entry)
name|gimp_file_entry_entry_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|len
decl_stmt|;
comment|/*  filenames still need more sanity checking    *  (erase double G_DIR_SEPARATORS, ...)    */
name|utf8
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
name|utf8
operator|=
name|g_strstrip
argument_list|(
name|utf8
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
name|utf8
argument_list|)
operator|)
operator|>
literal|1
operator|)
operator|&&
operator|(
name|utf8
index|[
name|len
operator|-
literal|1
index|]
operator|==
name|G_DIR_SEPARATOR
operator|)
condition|)
name|utf8
index|[
name|len
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|utf8
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
name|gimp_file_entry_entry_activate
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|entry
operator|->
name|entry
argument_list|)
argument_list|,
name|utf8
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|entry
operator|->
name|entry
argument_list|,
name|gimp_file_entry_entry_activate
argument_list|,
name|entry
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|file_dialog
condition|)
name|gtk_file_chooser_set_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|entry
operator|->
name|file_dialog
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
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|gimp_file_entry_check_filename
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|gtk_editable_set_position
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
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
name|entry
argument_list|,
name|gimp_file_entry_signals
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
DECL|function|gimp_file_entry_entry_focus_out (GtkWidget * widget,GdkEvent * event,GimpFileEntry * entry)
name|gimp_file_entry_entry_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEvent
modifier|*
name|event
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gimp_file_entry_entry_activate
argument_list|(
name|widget
argument_list|,
name|entry
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  local callback of gimp_file_entry_browse_clicked()  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_chooser_response (GtkWidget * dialog,gint response_id,GimpFileEntry * entry)
name|gimp_file_entry_chooser_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
name|gchar
modifier|*
name|filename
decl_stmt|;
name|filename
operator|=
name|gtk_file_chooser_get_filename
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_file_entry_set_filename
argument_list|(
name|entry
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_hide
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_file_manager_clicked (GtkWidget * widget,GimpFileEntry * entry)
name|gimp_file_entry_file_manager_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|utf8
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
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
name|file
operator|=
name|g_file_parse_name
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_file_show_in_file_manager
argument_list|(
name|file
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Can't show file in file manager: %s"
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_browse_clicked (GtkWidget * widget,GimpFileEntry * entry)
name|gimp_file_entry_browse_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|GtkFileChooser
modifier|*
name|chooser
decl_stmt|;
name|gchar
modifier|*
name|utf8
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|utf8
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
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
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|utf8
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|entry
operator|->
name|file_dialog
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|title
init|=
name|entry
operator|->
name|title
decl_stmt|;
if|if
condition|(
operator|!
name|title
condition|)
block|{
if|if
condition|(
name|entry
operator|->
name|dir_only
condition|)
name|title
operator|=
name|_
argument_list|(
literal|"Select Folder"
argument_list|)
expr_stmt|;
else|else
name|title
operator|=
name|_
argument_list|(
literal|"Select File"
argument_list|)
expr_stmt|;
block|}
name|entry
operator|->
name|file_dialog
operator|=
name|gtk_file_chooser_dialog_new
argument_list|(
name|title
argument_list|,
name|NULL
argument_list|,
name|entry
operator|->
name|dir_only
condition|?
name|GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER
else|:
name|GTK_FILE_CHOOSER_ACTION_OPEN
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
name|entry
operator|->
name|file_dialog
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
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|entry
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
literal|"gimp-file-entry-file-dialog"
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_file_entry_chooser_response
argument_list|)
argument_list|,
name|entry
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|chooser
argument_list|,
literal|"delete-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_true
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|entry
argument_list|,
literal|"unmap"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_hide
argument_list|)
argument_list|,
name|chooser
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|chooser
operator|=
name|GTK_FILE_CHOOSER
argument_list|(
name|entry
operator|->
name|file_dialog
argument_list|)
expr_stmt|;
block|}
name|gtk_file_chooser_set_filename
argument_list|(
name|chooser
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
name|gtk_window_set_screen
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|chooser
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_entry_check_filename (GimpFileEntry * entry)
name|gimp_file_entry_check_filename
parameter_list|(
name|GimpFileEntry
modifier|*
name|entry
parameter_list|)
block|{
name|gchar
modifier|*
name|utf8
decl_stmt|;
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
name|entry
operator|->
name|check_valid
operator|||
operator|!
name|entry
operator|->
name|file_exists
condition|)
return|return;
name|utf8
operator|=
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|entry
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
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|utf8
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|utf8
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
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
name|gtk_image_set_from_icon_name
argument_list|(
name|GTK_IMAGE
argument_list|(
name|entry
operator|->
name|file_exists
argument_list|)
argument_list|,
name|exists
condition|?
literal|"gtk-yes"
else|:
literal|"gtk-no"
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

