begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimpfileselection.c  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *   * This library is distributed in the hope that it will be useful,   * but WITHOUT ANY WARRANTY; without even the implied warranty of   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|"gimpfileselection.h"
end_include

begin_include
include|#
directive|include
file|"libgimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps/yes.xpm"
end_include

begin_include
include|#
directive|include
file|"pixmaps/no.xpm"
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

begin_comment
comment|/*  callbacks  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_realize
parameter_list|(
name|GtkWidget
modifier|*
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
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|gimp_file_selection_entry_focus_out_callback
parameter_list|(
name|GtkWidget
modifier|*
parameter_list|,
name|GdkEvent
modifier|*
parameter_list|,
name|gpointer
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
parameter_list|,
name|gpointer
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_file_selection_check_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
function_decl|;
end_function_decl

begin_enum
enum|enum
DECL|enum|__anon2ad0daff0103
block|{
DECL|enumerator|FILENAME_CHANGED
name|FILENAME_CHANGED
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

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
name|gfs
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|object
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|gfs
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|gfs
operator|->
name|file_selection
condition|)
name|gtk_widget_destroy
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
expr_stmt|;
if|if
condition|(
name|gfs
operator|->
name|title
condition|)
name|g_free
argument_list|(
name|gfs
operator|->
name|title
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
operator|(
operator|*
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
operator|)
operator|(
name|object
operator|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_class_init (GimpFileSelectionClass * class)
name|gimp_file_selection_class_init
parameter_list|(
name|GimpFileSelectionClass
modifier|*
name|class
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|class
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|class
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|gtk_hbox_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gimp_file_selection_signals
index|[
name|FILENAME_CHANGED
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"filename_changed"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpFileSelectionClass
argument_list|,
name|filename_changed
argument_list|)
argument_list|,
name|gtk_signal_default_marshaller
argument_list|,
name|GTK_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_file_selection_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|class
operator|->
name|filename_changed
operator|=
name|NULL
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_file_selection_destroy
expr_stmt|;
name|widget_class
operator|->
name|realize
operator|=
name|gimp_file_selection_realize
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_init (GimpFileSelection * gfs)
name|gimp_file_selection_init
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
block|{
name|gfs
operator|->
name|title
operator|=
name|NULL
expr_stmt|;
name|gfs
operator|->
name|file_selection
operator|=
name|NULL
expr_stmt|;
name|gfs
operator|->
name|file_exists
operator|=
name|FALSE
expr_stmt|;
name|gfs
operator|->
name|check_valid
operator|=
name|FALSE
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|gfs
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_set_homogeneous
argument_list|(
name|GTK_BOX
argument_list|(
name|gfs
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gfs
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
name|gfs
argument_list|)
argument_list|,
name|gfs
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|browse_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_browse_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gfs
operator|->
name|browse_button
argument_list|)
expr_stmt|;
name|gfs
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
name|gfs
argument_list|)
argument_list|,
name|gfs
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_entry_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
literal|"focus_out_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_entry_focus_out_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkType
DECL|function|gimp_file_selection_get_type (void)
name|gimp_file_selection_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|gfs_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|gfs_type
condition|)
block|{
name|GtkTypeInfo
name|gfs_info
init|=
block|{
literal|"GimpFileSelection"
block|,
sizeof|sizeof
argument_list|(
name|GimpFileSelection
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpFileSelectionClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_file_selection_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_file_selection_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|gfs_type
operator|=
name|gtk_type_unique
argument_list|(
name|gtk_hbox_get_type
argument_list|()
argument_list|,
operator|&
name|gfs_info
argument_list|)
expr_stmt|;
block|}
return|return
name|gfs_type
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_file_selection_new (gchar * title,gchar * filename,gboolean dir_only,gboolean check_valid)
name|gimp_file_selection_new
parameter_list|(
name|gchar
modifier|*
name|title
parameter_list|,
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
name|gfs
decl_stmt|;
name|gfs
operator|=
name|gtk_type_new
argument_list|(
name|gimp_file_selection_get_type
argument_list|()
argument_list|)
expr_stmt|;
name|gfs
operator|->
name|title
operator|=
name|g_strdup
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|gfs
operator|->
name|dir_only
operator|=
name|dir_only
expr_stmt|;
name|gfs
operator|->
name|check_valid
operator|=
name|check_valid
expr_stmt|;
name|gimp_file_selection_set_filename
argument_list|(
name|gfs
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|gfs
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_realize (GtkWidget * widget)
name|gimp_file_selection_realize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpFileSelection
modifier|*
name|gfs
decl_stmt|;
name|GtkStyle
modifier|*
name|style
decl_stmt|;
name|gfs
operator|=
name|GIMP_FILE_SELECTION
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gfs
operator|->
name|check_valid
condition|)
return|return;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
condition|)
operator|(
operator|*
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|realize
operator|)
operator|(
name|widget
operator|)
expr_stmt|;
name|style
operator|=
name|gtk_widget_get_style
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gfs
operator|->
name|yes_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|gfs
operator|->
name|yes_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|yes_xpm
argument_list|)
expr_stmt|;
name|gfs
operator|->
name|no_pixmap
operator|=
name|gdk_pixmap_create_from_xpm_d
argument_list|(
name|widget
operator|->
name|window
argument_list|,
operator|&
name|gfs
operator|->
name|no_mask
argument_list|,
operator|&
name|style
operator|->
name|bg
index|[
name|GTK_STATE_NORMAL
index|]
argument_list|,
name|no_xpm
argument_list|)
expr_stmt|;
name|gfs
operator|->
name|file_exists
operator|=
name|gtk_pixmap_new
argument_list|(
name|gfs
operator|->
name|no_pixmap
argument_list|,
name|gfs
operator|->
name|no_mask
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|gfs
argument_list|)
argument_list|,
name|gfs
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
name|gimp_file_selection_check_filename
argument_list|(
name|gfs
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gfs
operator|->
name|file_exists
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_file_selection_get_filename (GimpFileSelection * gfs)
name|gimp_file_selection_get_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|gfs
operator|!=
name|NULL
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|gfs
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
literal|""
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|gtk_editable_get_chars
argument_list|(
name|GTK_EDITABLE
argument_list|(
name|gfs
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

begin_function
name|void
DECL|function|gimp_file_selection_set_filename (GimpFileSelection * gfs,gchar * filename)
name|gimp_file_selection_set_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|,
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gfs
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_FILE_SELECTION
argument_list|(
name|gfs
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  update everything    */
name|gimp_file_selection_entry_callback
argument_list|(
name|gfs
operator|->
name|entry
argument_list|,
operator|(
name|gpointer
operator|)
name|gfs
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
name|gfs
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gint
name|len
decl_stmt|;
name|gfs
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
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
if|if
condition|(
name|gfs
operator|->
name|file_selection
condition|)
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
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
name|gfs
argument_list|)
expr_stmt|;
name|gtk_entry_set_position
argument_list|(
name|GTK_ENTRY
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_signal_emit
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
argument_list|)
argument_list|,
name|gimp_file_selection_signals
index|[
name|FILENAME_CHANGED
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
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
name|TRUE
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
name|gfs
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gfs
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
name|gfs
operator|->
name|file_selection
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|gfs
operator|->
name|entry
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
comment|/*  update everything  */
name|gimp_file_selection_entry_callback
argument_list|(
name|gfs
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
DECL|function|gimp_file_selection_filesel_cancel_callback (GtkWidget * widget,gpointer data)
name|gimp_file_selection_filesel_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_widget_hide
argument_list|(
name|GIMP_FILE_SELECTION
argument_list|(
name|data
argument_list|)
operator|->
name|file_selection
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|gimp_file_selection_filesel_delete_callback (GtkWidget * widget,GdkEvent * event,gpointer data)
name|gimp_file_selection_filesel_delete_callback
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
name|gimp_file_selection_filesel_cancel_callback
argument_list|(
name|NULL
argument_list|,
name|data
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
name|gfs
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gfs
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
name|gfs
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
name|gfs
operator|->
name|file_selection
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|gfs
operator|->
name|dir_only
condition|)
block|{
name|gfs
operator|->
name|file_selection
operator|=
name|gtk_file_selection_new
argument_list|(
name|gfs
operator|->
name|title
argument_list|)
expr_stmt|;
comment|/*  hiding these widgets uses internal gtk+ knowledge, but it's 	   *  easier than creating my own directory browser -- michael 	   */
name|gtk_widget_hide
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
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
name|gfs
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
name|gfs
operator|->
name|file_selection
operator|=
name|gtk_file_selection_new
argument_list|(
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
name|gfs
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
name|gfs
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
name|gfs
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
name|gfs
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
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
operator|->
name|ok_button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|GTK_BIN
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
operator|->
name|cancel_button
argument_list|)
operator|->
name|child
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Close"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_filesel_ok_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
operator|->
name|selection_entry
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_filesel_ok_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_filesel_cancel_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
argument_list|)
argument_list|,
literal|"unmap"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_filesel_cancel_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_file_selection_filesel_delete_callback
argument_list|)
argument_list|,
name|gfs
argument_list|)
expr_stmt|;
block|}
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|gfs
operator|->
name|file_selection
argument_list|)
expr_stmt|;
else|else
name|gdk_window_raise
argument_list|(
name|gfs
operator|->
name|file_selection
operator|->
name|window
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_file_selection_check_filename (GimpFileSelection * gfs)
name|gimp_file_selection_check_filename
parameter_list|(
name|GimpFileSelection
modifier|*
name|gfs
parameter_list|)
block|{
specifier|static
name|struct
name|stat
name|statbuf
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
operator|!
name|gfs
operator|->
name|check_valid
condition|)
return|return;
if|if
condition|(
name|gfs
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
name|gfs
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
operator|(
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|statbuf
argument_list|)
operator|==
literal|0
operator|)
operator|&&
operator|(
name|gfs
operator|->
name|dir_only
condition|?
name|S_ISDIR
argument_list|(
name|statbuf
operator|.
name|st_mode
argument_list|)
else|:
name|S_ISREG
argument_list|(
name|statbuf
operator|.
name|st_mode
argument_list|)
operator|)
condition|)
block|{
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gfs
operator|->
name|file_exists
argument_list|)
argument_list|,
name|gfs
operator|->
name|yes_pixmap
argument_list|,
name|gfs
operator|->
name|yes_mask
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_pixmap_set
argument_list|(
name|GTK_PIXMAP
argument_list|(
name|gfs
operator|->
name|file_exists
argument_list|)
argument_list|,
name|gfs
operator|->
name|no_pixmap
argument_list|,
name|gfs
operator|->
name|no_mask
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

