begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorProfileChooserDialog  * Copyright (C) 2006-2014 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|PLATFORM_OSX
end_ifdef

begin_include
include|#
directive|include
file|<AppKit/AppKit.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofilechooserdialog.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorprofileview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_struct
DECL|struct|_GimpColorProfileChooserDialogPrivate
struct|struct
name|_GimpColorProfileChooserDialogPrivate
block|{
DECL|member|profile_view
name|GimpColorProfileView
modifier|*
name|profile_view
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_color_profile_chooser_dialog_constructed
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
name|gimp_color_profile_chooser_dialog_add_shortcut
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_profile_chooser_dialog_update_preview
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpColorProfileChooserDialog
argument_list|,
name|gimp_color_profile_chooser_dialog
argument_list|,
name|GTK_TYPE_FILE_CHOOSER_DIALOG
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_profile_chooser_dialog_parent_class
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_chooser_dialog_class_init (GimpColorProfileChooserDialogClass * klass)
name|gimp_color_profile_chooser_dialog_class_init
parameter_list|(
name|GimpColorProfileChooserDialogClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_profile_chooser_dialog_constructed
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpColorProfileChooserDialogPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_chooser_dialog_init (GimpColorProfileChooserDialog * dialog)
name|gimp_color_profile_chooser_dialog_init
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|dialog
operator|->
name|priv
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|dialog
argument_list|,
name|GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|,
name|GimpColorProfileChooserDialogPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_chooser_dialog_constructed (GObject * object)
name|gimp_color_profile_chooser_dialog_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
decl_stmt|;
name|GtkFileFilter
modifier|*
name|filter
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_window
decl_stmt|;
name|GtkWidget
modifier|*
name|profile_view
decl_stmt|;
name|dialog
operator|=
name|GIMP_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-profile-chooser-dialog"
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"All files (*.*)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|filter
operator|=
name|gtk_file_filter_new
argument_list|()
expr_stmt|;
name|gtk_file_filter_set_name
argument_list|(
name|filter
argument_list|,
name|_
argument_list|(
literal|"ICC color profile (*.icc, *.icm)"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*.[Ii][Cc][Cc]"
argument_list|)
expr_stmt|;
name|gtk_file_filter_add_pattern
argument_list|(
name|filter
argument_list|,
literal|"*.[Ii][Cc][Mm]"
argument_list|)
expr_stmt|;
name|gtk_file_chooser_add_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_filter
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|filter
argument_list|)
expr_stmt|;
comment|/*  the preview widget  */
name|scrolled_window
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|scrolled_window
argument_list|,
literal|300
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_shadow_type
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|profile_view
operator|=
name|gimp_color_profile_view_new
argument_list|()
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_window
argument_list|)
argument_list|,
name|profile_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|profile_view
argument_list|)
expr_stmt|;
name|dialog
operator|->
name|priv
operator|->
name|profile_view
operator|=
name|GIMP_COLOR_PROFILE_VIEW
argument_list|(
name|profile_view
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_preview_widget
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|scrolled_window
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"update-preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_profile_chooser_dialog_update_preview
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_profile_chooser_dialog_new (const gchar * title,GtkWindow * parent,GtkFileChooserAction action)
name|gimp_color_profile_chooser_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|GtkWindow
modifier|*
name|parent
parameter_list|,
name|GtkFileChooserAction
name|action
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|title
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WINDOW
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|,
literal|"title"
argument_list|,
name|title
argument_list|,
literal|"action"
argument_list|,
name|action
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|parent
condition|)
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_file_chooser_get_action
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_FILE_CHOOSER_ACTION_SAVE
condition|)
block|{
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_SAVE
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_file_chooser_set_do_overwrite_confirmation
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_dialog_add_buttons
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OPEN
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gtk_dialog_set_alternative_button_order
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_dialog_set_default_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_RESPONSE_ACCEPT
argument_list|)
expr_stmt|;
name|gimp_color_profile_chooser_dialog_add_shortcut
argument_list|(
name|GIMP_COLOR_PROFILE_CHOOSER_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/* Add shortcuts for default ICC profile locations */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|add_shortcut (GimpColorProfileChooserDialog * dialog,const gchar * folder)
name|add_shortcut
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|folder
parameter_list|)
block|{
return|return
operator|(
name|g_file_test
argument_list|(
name|folder
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
operator|&&
name|gtk_file_chooser_add_shortcut_folder
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|folder
argument_list|,
name|NULL
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_chooser_dialog_add_shortcut (GimpColorProfileChooserDialog * dialog)
name|gimp_color_profile_chooser_dialog_add_shortcut
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|gboolean
name|save
init|=
operator|(
name|gtk_file_chooser_get_action
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_FILE_CHOOSER_ACTION_SAVE
operator|)
decl_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
block|{
specifier|const
name|gchar
modifier|*
name|prefix
init|=
name|g_getenv
argument_list|(
literal|"SystemRoot"
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|folder
decl_stmt|;
if|if
condition|(
operator|!
name|prefix
condition|)
name|prefix
operator|=
literal|"c:\\windows"
expr_stmt|;
name|folder
operator|=
name|g_strconcat
argument_list|(
name|prefix
argument_list|,
literal|"\\system32\\spool\\drivers\\color"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|PLATFORM_OSX
argument_list|)
block|{
name|NSAutoreleasePool
modifier|*
name|pool
decl_stmt|;
name|NSArray
modifier|*
name|path
decl_stmt|;
name|NSString
modifier|*
name|library_dir
decl_stmt|;
name|gchar
modifier|*
name|folder
decl_stmt|;
name|gboolean
name|folder_set
init|=
name|FALSE
decl_stmt|;
name|pool
operator|=
index|[
index|[
name|NSAutoreleasePool
name|alloc
index|]
name|init
index|]
expr_stmt|;
if|if
condition|(
name|save
condition|)
block|{
name|path
operator|=
name|NSSearchPathForDirectoriesInDomains
argument_list|(
name|NSLibraryDirectory
argument_list|,
name|NSUserDomainMask
argument_list|,
name|YES
argument_list|)
expr_stmt|;
name|library_dir
operator|=
index|[
name|path
name|objectAtIndex
operator|:
literal|0
index|]
expr_stmt|;
name|folder
operator|=
name|g_build_filename
argument_list|(
argument|[library_dir UTF8String]
argument_list|,
literal|"ColorSync"
argument_list|,
literal|"Profiles"
argument_list|,
argument|NULL
argument_list|)
expr_stmt|;
name|folder_set
operator|=
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|folder_set
condition|)
block|{
name|path
operator|=
name|NSSearchPathForDirectoriesInDomains
argument_list|(
name|NSLibraryDirectory
argument_list|,
name|NSSystemDomainMask
argument_list|,
name|YES
argument_list|)
expr_stmt|;
name|library_dir
operator|=
index|[
name|path
name|objectAtIndex
operator|:
literal|0
index|]
expr_stmt|;
name|folder
operator|=
name|g_build_filename
argument_list|(
argument|[library_dir UTF8String]
argument_list|,
literal|"ColorSync"
argument_list|,
literal|"Profiles"
argument_list|,
argument|NULL
argument_list|)
expr_stmt|;
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
block|}
index|[
name|pool
name|drain
index|]
expr_stmt|;
block|}
else|#
directive|else
block|{
name|gboolean
name|folder_set
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|save
condition|)
block|{
name|gchar
modifier|*
name|folder
init|=
name|g_build_filename
argument_list|(
name|g_get_user_data_dir
argument_list|()
argument_list|,
literal|"color"
argument_list|,
literal|"icc"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|folder_set
operator|=
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|folder_set
condition|)
block|{
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
comment|/* Some software, like GNOME color, will save profiles in              * $XDG_DATA_HOME/icc/              */
name|folder
operator|=
name|g_build_filename
argument_list|(
name|g_get_user_data_dir
argument_list|()
argument_list|,
literal|"icc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|folder_set
operator|=
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|folder_set
condition|)
block|{
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
name|folder
operator|=
name|g_build_filename
argument_list|(
name|g_get_home_dir
argument_list|()
argument_list|,
literal|".color"
argument_list|,
literal|"icc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|folder_set
operator|=
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
name|folder
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|folder
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|folder_set
condition|)
name|add_shortcut
argument_list|(
name|dialog
argument_list|,
literal|"/usr/share/color/icc"
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_profile_chooser_dialog_update_preview (GimpColorProfileChooserDialog * dialog)
name|gimp_color_profile_chooser_dialog_update_preview
parameter_list|(
name|GimpColorProfileChooserDialog
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpColorProfile
modifier|*
name|profile
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
name|file
operator|=
name|gtk_file_chooser_get_preview_file
argument_list|(
name|GTK_FILE_CHOOSER
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|gimp_color_profile_view_set_profile
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|profile_view
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return;
block|}
switch|switch
condition|(
name|g_file_query_file_type
argument_list|(
name|file
argument_list|,
name|G_FILE_QUERY_INFO_NONE
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
case|case
name|G_FILE_TYPE_REGULAR
case|:
name|profile
operator|=
name|gimp_color_profile_new_from_file
argument_list|(
name|file
argument_list|,
operator|&
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|profile
condition|)
block|{
name|gimp_color_profile_view_set_error
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|profile_view
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
else|else
block|{
name|gimp_color_profile_view_set_profile
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|profile_view
argument_list|,
name|profile
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|profile
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|G_FILE_TYPE_DIRECTORY
case|:
name|gimp_color_profile_view_set_error
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|profile_view
argument_list|,
name|_
argument_list|(
literal|"Folder"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_color_profile_view_set_error
argument_list|(
name|dialog
operator|->
name|priv
operator|->
name|profile_view
argument_list|,
name|_
argument_list|(
literal|"Not a regular file."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

