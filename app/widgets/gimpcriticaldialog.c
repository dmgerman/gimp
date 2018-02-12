begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcriticaldialog.c  * Copyright (C) 2018  Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_comment
comment|/*  * This widget is particular that I want to be able to use it  * internally but also from an alternate tool (gimp-debug-tool). It  * means that the implementation must stay as generic glib/GTK+ as  * possible.  */
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
file|<gegl.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|PLATFORM_OSX
end_ifdef

begin_empty
empty|#import<Cocoa/Cocoa.h>
end_empty

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_undef
undef|#
directive|undef
name|DATADIR
end_undef

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimpcriticaldialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_include
include|#
directive|include
file|"gimp-version.h"
end_include

begin_define
DECL|macro|GIMP_CRITICAL_RESPONSE_CLIPBOARD
define|#
directive|define
name|GIMP_CRITICAL_RESPONSE_CLIPBOARD
value|1
end_define

begin_define
DECL|macro|GIMP_CRITICAL_RESPONSE_URL
define|#
directive|define
name|GIMP_CRITICAL_RESPONSE_URL
value|2
end_define

begin_define
DECL|macro|GIMP_CRITICAL_RESPONSE_RESTART
define|#
directive|define
name|GIMP_CRITICAL_RESPONSE_RESTART
value|3
end_define

begin_define
DECL|macro|BUTTON1_TEXT
define|#
directive|define
name|BUTTON1_TEXT
value|_("Copy Bug Information")
end_define

begin_define
DECL|macro|BUTTON2_TEXT
define|#
directive|define
name|BUTTON2_TEXT
value|_("Open Bug Tracker")
end_define

begin_function_decl
specifier|static
name|void
name|gimp_critical_dialog_finalize
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
name|gimp_critical_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|browser_open_url
parameter_list|(
specifier|const
name|gchar
modifier|*
name|url
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCriticalDialog,gimp_critical_dialog,GTK_TYPE_DIALOG)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCriticalDialog
argument_list|,
argument|gimp_critical_dialog
argument_list|,
argument|GTK_TYPE_DIALOG
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_critical_dialog_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_critical_dialog_class_init
parameter_list|(
name|GimpCriticalDialogClass
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
name|GtkDialogClass
modifier|*
name|dialog_class
init|=
name|GTK_DIALOG_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_critical_dialog_finalize
expr_stmt|;
name|dialog_class
operator|->
name|response
operator|=
name|gimp_critical_dialog_response
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_critical_dialog_init (GimpCriticalDialog * dialog)
name|gimp_critical_dialog_init
parameter_list|(
name|GimpCriticalDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|PangoAttrList
modifier|*
name|attrs
decl_stmt|;
name|PangoAttribute
modifier|*
name|attr
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|gchar
modifier|*
name|version
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-critical"
argument_list|)
expr_stmt|;
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|BUTTON1_TEXT
argument_list|,
name|GIMP_CRITICAL_RESPONSE_CLIPBOARD
argument_list|,
name|BUTTON2_TEXT
argument_list|,
name|GIMP_CRITICAL_RESPONSE_URL
argument_list|,
name|_
argument_list|(
literal|"_Close"
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|6
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
comment|/* The error label. */
name|dialog
operator|->
name|top_label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dialog
operator|->
name|top_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|top_label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|top_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|top_label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_weight_new
argument_list|(
name|PANGO_WEIGHT_SEMIBOLD
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|top_label
argument_list|)
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|top_label
argument_list|)
expr_stmt|;
comment|/* Generic "report a bug" instructions. */
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s\n"
literal|" \xe2\x80\xa2 %s %s\n"
literal|" \xe2\x80\xa2 %s %s\n"
literal|" \xe2\x80\xa2 %s\n"
literal|" \xe2\x80\xa2 %s\n"
literal|" \xe2\x80\xa2 %s\n"
literal|" \xe2\x80\xa2 %s"
argument_list|,
name|_
argument_list|(
literal|"To help us improve GIMP, you can report the bug with "
literal|"these simple steps:"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Copy the bug information to the clipboard by clicking: "
argument_list|)
argument_list|,
name|BUTTON1_TEXT
argument_list|,
name|_
argument_list|(
literal|"Open our bug tracker in the browser by clicking: "
argument_list|)
argument_list|,
name|BUTTON2_TEXT
argument_list|,
name|_
argument_list|(
literal|"Create a login if you don't have one yet."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paste the clipboard text in a new bug report."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Add relevant information in English in the bug report "
literal|"explaining what you were doing when this error occurred."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"This error may have left GIMP in an inconsistent state. "
literal|"It is advised to save your work and restart GIMP."
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|bottom_label
operator|=
name|gtk_label_new
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|dialog
operator|->
name|bottom_label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_label_set_selectable
argument_list|(
name|GTK_LABEL
argument_list|(
name|dialog
operator|->
name|bottom_label
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|dialog
operator|->
name|bottom_label
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
name|dialog
operator|->
name|bottom_label
argument_list|)
expr_stmt|;
name|widget
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"You can also close the dialog directly but "
literal|"reporting bugs is the best way to make your "
literal|"software awesome."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|widget
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|attrs
operator|=
name|pango_attr_list_new
argument_list|()
expr_stmt|;
name|attr
operator|=
name|pango_attr_style_new
argument_list|(
name|PANGO_STYLE_ITALIC
argument_list|)
expr_stmt|;
name|pango_attr_list_insert
argument_list|(
name|attrs
argument_list|,
name|attr
argument_list|)
expr_stmt|;
name|gtk_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|widget
argument_list|)
argument_list|,
name|attrs
argument_list|)
expr_stmt|;
name|pango_attr_list_unref
argument_list|(
name|attrs
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|widget
argument_list|)
expr_stmt|;
comment|/* Bug details for developers. */
name|widget
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
operator|-
literal|1
argument_list|,
literal|200
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|widget
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
name|widget
argument_list|)
expr_stmt|;
name|buffer
operator|=
name|gtk_text_buffer_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|version
operator|=
name|gimp_version
argument_list|(
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_text_buffer_set_text
argument_list|(
name|buffer
argument_list|,
name|version
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|version
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|details
operator|=
name|gtk_text_view_new_with_buffer
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|gtk_text_view_set_editable
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|dialog
operator|->
name|details
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
operator|->
name|details
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|widget
argument_list|)
argument_list|,
name|dialog
operator|->
name|details
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|pid
operator|=
literal|0
expr_stmt|;
name|dialog
operator|->
name|program
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_critical_dialog_finalize (GObject * object)
name|gimp_critical_dialog_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCriticalDialog
modifier|*
name|dialog
init|=
name|GIMP_CRITICAL_DIALOG
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|dialog
operator|->
name|program
condition|)
name|g_free
argument_list|(
name|dialog
operator|->
name|program
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* XXX This is taken straight from plug-ins/common/web-browser.c  *  * This really sucks but this class also needs to be called by  * tools/gimp-debug-tool.c as a separate process and therefore cannot  * make use of the PDB. Anyway shouldn't we just move this as a utils  * function?  Why does such basic feature as opening a URL in a  * cross-platform way need to be a plug-in?  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|browser_open_url (const gchar * url,GError ** error)
name|browser_open_url
parameter_list|(
specifier|const
name|gchar
modifier|*
name|url
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
ifdef|#
directive|ifdef
name|G_OS_WIN32
name|HINSTANCE
name|hinst
init|=
name|ShellExecute
argument_list|(
name|GetDesktopWindow
argument_list|()
argument_list|,
literal|"open"
argument_list|,
name|url
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|SW_SHOW
argument_list|)
decl_stmt|;
if|if
condition|(
operator|(
name|gint
operator|)
name|hinst
operator|<=
literal|32
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|err
decl_stmt|;
switch|switch
condition|(
operator|(
name|gint
operator|)
name|hinst
condition|)
block|{
case|case
literal|0
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The operating system is out of memory or resources."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_FILE_NOT_FOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified file was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_PATH_NOT_FOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified path was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|ERROR_BAD_FORMAT
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image)."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_ACCESSDENIED
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The operating system denied access to the specified file."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_ASSOCINCOMPLETE
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The file name association is incomplete or invalid."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDEBUSY
case|:
name|err
operator|=
name|_
argument_list|(
literal|"DDE transaction busy"
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDEFAIL
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The DDE transaction failed."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DDETIMEOUT
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The DDE transaction timed out."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_DLLNOTFOUND
case|:
name|err
operator|=
name|_
argument_list|(
literal|"The specified DLL was not found."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_NOASSOC
case|:
name|err
operator|=
name|_
argument_list|(
literal|"There is no application associated with the given file name extension."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_OOM
case|:
name|err
operator|=
name|_
argument_list|(
literal|"There was not enough memory to complete the operation."
argument_list|)
expr_stmt|;
break|break;
case|case
name|SE_ERR_SHARE
case|:
name|err
operator|=
name|_
argument_list|(
literal|"A sharing violation occurred."
argument_list|)
expr_stmt|;
break|break;
default|default :
name|err
operator|=
name|_
argument_list|(
literal|"Unknown Microsoft Windows error."
argument_list|)
expr_stmt|;
block|}
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Failed to open '%s': %s"
argument_list|)
argument_list|,
name|url
argument_list|,
name|err
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
elif|#
directive|elif
name|defined
argument_list|(
name|PLATFORM_OSX
argument_list|)
name|NSURL
modifier|*
name|ns_url
decl_stmt|;
name|gboolean
name|retval
decl_stmt|;
block|@
name|autoreleasepool
block|{
name|ns_url
operator|=
index|[
name|NSURL
name|URLWithString
operator|:
index|[
name|NSString
name|stringWithUTF8String
operator|:
name|url
index|]
index|]
expr_stmt|;
name|retval
operator|=
index|[
index|[
name|NSWorkspace
name|sharedWorkspace
index|]
name|openURL
operator|:
name|ns_url
index|]
expr_stmt|;
block|}
return|return
name|retval
return|;
else|#
directive|else
return|return
name|gtk_show_uri
argument_list|(
name|gdk_screen_get_default
argument_list|()
argument_list|,
name|url
argument_list|,
name|gtk_get_current_event_time
argument_list|()
argument_list|,
name|error
argument_list|)
return|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_critical_dialog_response (GtkDialog * dialog,gint response_id)
name|gimp_critical_dialog_response
parameter_list|(
name|GtkDialog
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|)
block|{
name|GimpCriticalDialog
modifier|*
name|critical
init|=
name|GIMP_CRITICAL_DIALOG
argument_list|(
name|dialog
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GIMP_CRITICAL_RESPONSE_CLIPBOARD
case|:
block|{
name|GtkClipboard
modifier|*
name|clipboard
decl_stmt|;
name|clipboard
operator|=
name|gtk_clipboard_get_for_display
argument_list|(
name|gdk_display_get_default
argument_list|()
argument_list|,
name|GDK_SELECTION_CLIPBOARD
argument_list|)
expr_stmt|;
if|if
condition|(
name|clipboard
condition|)
block|{
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|GtkTextIter
name|start
decl_stmt|;
name|GtkTextIter
name|end
decl_stmt|;
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|critical
operator|->
name|details
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_iter_at_offset
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_iter_at_offset
argument_list|(
name|buffer
argument_list|,
operator|&
name|end
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|text
operator|=
name|gtk_text_buffer_get_text
argument_list|(
name|buffer
argument_list|,
operator|&
name|start
argument_list|,
operator|&
name|end
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_clipboard_set_text
argument_list|(
name|clipboard
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
block|}
break|break;
case|case
name|GIMP_CRITICAL_RESPONSE_URL
case|:
block|{
specifier|const
name|gchar
modifier|*
name|url
decl_stmt|;
comment|/* XXX Ideally I'd find a way to prefill the bug report          * through the URL or with POST data. But I could not find          * any. Anyway since we may soon ditch bugzilla to follow          * GNOME infrastructure changes, I don't want to waste too          * much time digging into it.          */
name|url
operator|=
literal|"https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP"
expr_stmt|;
name|browser_open_url
argument_list|(
name|url
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_CRITICAL_RESPONSE_RESTART
case|:
block|{
name|gchar
modifier|*
name|args
index|[
literal|2
index|]
init|=
block|{
name|critical
operator|->
name|program
block|,
name|NULL
block|}
decl_stmt|;
ifndef|#
directive|ifndef
name|G_OS_WIN32
comment|/* It is unneeded to kill the process on Win32. This was run          * as an async call and the main process should already be          * dead by now.          */
if|if
condition|(
name|critical
operator|->
name|pid
operator|>
literal|0
condition|)
name|kill
argument_list|(
operator|(
name|pid_t
operator|)
name|critical
operator|->
name|pid
argument_list|,
name|SIGINT
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|critical
operator|->
name|program
condition|)
name|g_spawn_async
argument_list|(
name|NULL
argument_list|,
name|args
argument_list|,
name|NULL
argument_list|,
name|G_SPAWN_DEFAULT
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* Fall through. */
case|case
name|GTK_RESPONSE_DELETE_EVENT
case|:
case|case
name|GTK_RESPONSE_CLOSE
case|:
default|default:
name|gtk_widget_destroy
argument_list|(
name|GTK_WIDGET
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_critical_dialog_new (const gchar * title)
name|gimp_critical_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CRITICAL_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_critical_dialog_add (GtkWidget * dialog,const gchar * message,const gchar * trace,gboolean is_fatal,const gchar * program,gint pid)
name|gimp_critical_dialog_add
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
specifier|const
name|gchar
modifier|*
name|trace
parameter_list|,
name|gboolean
name|is_fatal
parameter_list|,
specifier|const
name|gchar
modifier|*
name|program
parameter_list|,
name|gint
name|pid
parameter_list|)
block|{
name|GimpCriticalDialog
modifier|*
name|critical
decl_stmt|;
name|GtkTextBuffer
modifier|*
name|buffer
decl_stmt|;
name|GtkTextIter
name|end
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_CRITICAL_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|||
operator|!
name|message
condition|)
block|{
comment|/* This is a bit hackish. We usually should use        * g_return_if_fail(). But I don't want to end up in a critical        * recursing loop if our code had bugs. We would crash GIMP with        * a CRITICAL which would otherwise not have necessarily ended up        * in a crash.        */
return|return;
block|}
name|critical
operator|=
name|GIMP_CRITICAL_DIALOG
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
comment|/* The user text, which should be localized. */
if|if
condition|(
name|is_fatal
condition|)
block|{
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"GIMP crashed with a fatal error: %s"
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|gtk_label_get_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|critical
operator|->
name|top_label
argument_list|)
argument_list|)
operator|||
name|strlen
argument_list|(
name|gtk_label_get_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|critical
operator|->
name|top_label
argument_list|)
argument_list|)
argument_list|)
operator|==
literal|0
condition|)
block|{
comment|/* First error. Let's just display it. */
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"GIMP encountered an error: %s"
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* Let's not display all errors. They will be in the bug report        * part anyway.        */
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"GIMP encountered several critical errors!"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|critical
operator|->
name|top_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|is_fatal
condition|)
block|{
comment|/* Same text as before except that we don't need the last point        * about saving and restarting since anyway we are crashing and        * manual saving is not possible anymore (or even advisable since        * if it fails, one may corrupt files).        */
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s\n"
literal|" \xe2\x80\xa2 %s \"%s\"\n"
literal|" \xe2\x80\xa2 %s \"%s\"\n"
literal|" \xe2\x80\xa2 %s\n"
literal|" \xe2\x80\xa2 %s\n"
literal|" \xe2\x80\xa2 %s"
argument_list|,
name|_
argument_list|(
literal|"To help us improve GIMP, you can report the bug with "
literal|"these simple steps:"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Copy the bug information to the clipboard by clicking: "
argument_list|)
argument_list|,
name|BUTTON1_TEXT
argument_list|,
name|_
argument_list|(
literal|"Open our bug tracker in the browser by clicking: "
argument_list|)
argument_list|,
name|BUTTON2_TEXT
argument_list|,
name|_
argument_list|(
literal|"Create a login if you don't have one yet."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paste the clipboard text in a new bug report."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Add relevant information in English in the bug report "
literal|"explaining what you were doing when this error occurred."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|critical
operator|->
name|bottom_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
comment|/* The details text is untranslated on purpose. This is the message    * meant to go to clipboard for the bug report. It has to be in    * English.    */
name|buffer
operator|=
name|gtk_text_view_get_buffer
argument_list|(
name|GTK_TEXT_VIEW
argument_list|(
name|critical
operator|->
name|details
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_text_buffer_get_iter_at_offset
argument_list|(
name|buffer
argument_list|,
operator|&
name|end
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|trace
condition|)
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"\n> %s\n\nStack trace:\n%s"
argument_list|,
name|message
argument_list|,
name|trace
argument_list|)
expr_stmt|;
else|else
name|text
operator|=
name|g_strdup_printf
argument_list|(
literal|"\n> %s\n"
argument_list|,
name|message
argument_list|)
expr_stmt|;
name|gtk_text_buffer_insert
argument_list|(
name|buffer
argument_list|,
operator|&
name|end
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
comment|/* Finally when encountering a fatal message, propose one more button    * to restart GIMP.    */
if|if
condition|(
name|is_fatal
condition|)
block|{
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"_Restart GIMP"
argument_list|)
argument_list|,
name|GIMP_CRITICAL_RESPONSE_RESTART
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|critical
operator|->
name|program
operator|=
name|g_strdup
argument_list|(
name|program
argument_list|)
expr_stmt|;
name|critical
operator|->
name|pid
operator|=
name|pid
expr_stmt|;
block|}
block|}
end_function

end_unit

