begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-new.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptemplate.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainermenuimpl.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptemplateeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"file-new-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon28b275c60108
block|{
DECL|member|dialog
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
DECL|member|confirm_dialog
name|GtkWidget
modifier|*
name|confirm_dialog
decl_stmt|;
DECL|member|template_menu
name|GtkWidget
modifier|*
name|template_menu
decl_stmt|;
DECL|member|editor
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
DECL|member|ok_button
name|GtkWidget
modifier|*
name|ok_button
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|memsize
name|gulong
name|memsize
decl_stmt|;
DECL|typedef|NewImageInfo
block|}
name|NewImageInfo
typedef|;
end_typedef

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|file_new_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_template_notify
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_template_select
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_confirm_dialog
parameter_list|(
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_new_create_image
parameter_list|(
name|NewImageInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_new_dialog_create (Gimp * gimp,GimpImage * gimage)
name|file_new_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|NewImageInfo
modifier|*
name|info
decl_stmt|;
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|optionmenu
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|info
operator|=
name|g_new0
argument_list|(
name|NewImageInfo
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|info
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
name|info
operator|->
name|memsize
operator|=
literal|0
expr_stmt|;
name|info
operator|->
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
argument_list|,
name|_
argument_list|(
literal|"New Image"
argument_list|)
argument_list|,
literal|"new_image"
argument_list|,
name|GIMP_STOCK_IMAGE
argument_list|,
name|_
argument_list|(
literal|"Create a New Image"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/file_new.html"
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|file_new_reset_callback
argument_list|,
name|info
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|file_new_cancel_callback
argument_list|,
name|info
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|file_new_ok_callback
argument_list|,
name|info
argument_list|,
name|NULL
argument_list|,
operator|&
name|info
operator|->
name|ok_button
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  vbox holding the rest of the dialog  */
name|main_vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|main_vbox
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
name|main_vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|optionmenu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"From _Template:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|optionmenu
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|info
operator|->
name|template_menu
operator|=
name|gimp_container_menu_new
argument_list|(
name|gimp
operator|->
name|templates
argument_list|,
name|NULL
argument_list|,
literal|16
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|optionmenu
argument_list|)
argument_list|,
name|info
operator|->
name|template_menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|info
operator|->
name|template_menu
argument_list|)
expr_stmt|;
name|gimp_container_menu_select_item
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|info
operator|->
name|template_menu
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|info
operator|->
name|template_menu
argument_list|,
literal|"select_item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_new_template_select
argument_list|)
argument_list|,
name|info
argument_list|)
expr_stmt|;
comment|/*  Template editor  */
name|info
operator|->
name|editor
operator|=
name|gimp_template_editor_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|info
operator|->
name|editor
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
name|info
operator|->
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
operator|->
name|template
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_new_template_notify
argument_list|)
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|template
operator|=
name|gimp_image_new_get_last_template
argument_list|(
name|gimp
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_template_editor_set_template
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|gimp_size_entry_grab_focus
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
operator|->
name|size_se
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_new_ok_callback (GtkWidget * widget,NewImageInfo * info)
name|file_new_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|info
operator|->
name|memsize
operator|>
name|GIMP_GUI_CONFIG
argument_list|(
name|info
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
condition|)
name|file_new_confirm_dialog
argument_list|(
name|info
argument_list|)
expr_stmt|;
else|else
name|file_new_create_image
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_cancel_callback (GtkWidget * widget,NewImageInfo * info)
name|file_new_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_reset_callback (GtkWidget * widget,NewImageInfo * info)
name|file_new_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|template
operator|=
name|gimp_template_new
argument_list|(
literal|"foo"
argument_list|)
expr_stmt|;
name|gimp_template_set_from_config
argument_list|(
name|template
argument_list|,
name|info
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
name|gimp_template_editor_set_template
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_template_notify (GimpTemplate * template,GParamSpec * param_spec,NewImageInfo * info)
name|file_new_template_notify
parameter_list|(
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|GParamSpec
modifier|*
name|param_spec
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|info
operator|->
name|memsize
operator|!=
name|template
operator|->
name|initial_size
condition|)
block|{
name|info
operator|->
name|memsize
operator|=
name|template
operator|->
name|initial_size
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|info
operator|->
name|ok_button
argument_list|,
operator|!
name|template
operator|->
name|initial_size_too_large
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_template_select (GimpContainerMenu * menu,GimpTemplate * template,gpointer insert_data,NewImageInfo * info)
name|file_new_template_select
parameter_list|(
name|GimpContainerMenu
modifier|*
name|menu
parameter_list|,
name|GimpTemplate
modifier|*
name|template
parameter_list|,
name|gpointer
name|insert_data
parameter_list|,
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
if|if
condition|(
name|template
condition|)
name|gimp_template_editor_set_template
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
argument_list|,
name|template
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  the confirm dialog  */
end_comment

begin_function
specifier|static
name|void
DECL|function|file_new_confirm_dialog_callback (GtkWidget * widget,gboolean create,gpointer data)
name|file_new_confirm_dialog_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|create
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|NewImageInfo
modifier|*
name|info
init|=
operator|(
name|NewImageInfo
operator|*
operator|)
name|data
decl_stmt|;
name|info
operator|->
name|confirm_dialog
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|create
condition|)
name|file_new_create_image
argument_list|(
name|info
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_set_sensitive
argument_list|(
name|info
operator|->
name|dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_confirm_dialog (NewImageInfo * info)
name|file_new_confirm_dialog
parameter_list|(
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
name|gchar
modifier|*
name|size_str
decl_stmt|;
name|gchar
modifier|*
name|max_size_str
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|size_str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|info
operator|->
name|memsize
argument_list|)
expr_stmt|;
name|max_size_str
operator|=
name|gimp_memsize_to_string
argument_list|(
name|GIMP_GUI_CONFIG
argument_list|(
name|info
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|max_new_image_size
argument_list|)
expr_stmt|;
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"You are trying to create an image with\n"
literal|"an initial size of %s.\n\n"
literal|"Choose OK to create this image anyway.\n"
literal|"Choose Cancel if you did not intend to\n"
literal|"create such a large image.\n\n"
literal|"To prevent this dialog from appearing,\n"
literal|"increase the \"Maximum Image Size\"\n"
literal|"setting (currently %s) in the\n"
literal|"Preferences dialog."
argument_list|)
argument_list|,
name|size_str
argument_list|,
name|max_size_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|size_str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|max_size_str
argument_list|)
expr_stmt|;
name|info
operator|->
name|confirm_dialog
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Confirm Image Size"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/file_new.html#confirm_size"
argument_list|,
name|GIMP_STOCK_INFO
argument_list|,
name|text
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|file_new_confirm_dialog_callback
argument_list|,
name|info
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|info
operator|->
name|confirm_dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|info
operator|->
name|dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|info
operator|->
name|confirm_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_new_create_image (NewImageInfo * info)
name|file_new_create_image
parameter_list|(
name|NewImageInfo
modifier|*
name|info
parameter_list|)
block|{
name|GimpTemplate
modifier|*
name|template
decl_stmt|;
name|template
operator|=
name|gimp_template_editor_get_template
argument_list|(
name|GIMP_TEMPLATE_EDITOR
argument_list|(
name|info
operator|->
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|info
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|gimp_template_create_image
argument_list|(
name|info
operator|->
name|gimp
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|gimp_image_new_set_last_template
argument_list|(
name|info
operator|->
name|gimp
argument_list|,
name|template
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|template
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|info
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

