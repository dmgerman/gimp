begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_SYS_PARAM_H
end_ifdef

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

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
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdocuments.h"
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
file|"core/gimpimagefile.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"file/file-open.h"
end_include

begin_include
include|#
directive|include
file|"file/file-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-utils.h"
end_include

begin_include
include|#
directive|include
file|"file-open-dialog.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|file_open_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_open_genbutton_callback
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
name|file_open_selchanged_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_open_ok_callback
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
name|file_open_type_callback
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
name|file_open_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|fileload
specifier|static
name|GtkWidget
modifier|*
name|fileload
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|open_options
specifier|static
name|GtkWidget
modifier|*
name|open_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|open_options_imagefile
specifier|static
name|GimpImagefile
modifier|*
name|open_options_imagefile
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|open_options_label
specifier|static
name|GtkWidget
modifier|*
name|open_options_label
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|open_options_frame
specifier|static
name|GtkWidget
modifier|*
name|open_options_frame
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|load_file_proc
specifier|static
name|PlugInProcDef
modifier|*
name|load_file_proc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_open_dialog_menu_init (Gimp * gimp,GimpItemFactory * item_factory)
name|file_open_dialog_menu_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|)
block|{
name|GimpItemFactoryEntry
name|entry
decl_stmt|;
name|PlugInProcDef
modifier|*
name|file_proc
decl_stmt|;
name|GSList
modifier|*
name|list
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
name|GIMP_IS_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|load_procs
operator|=
name|g_slist_reverse
argument_list|(
name|gimp
operator|->
name|load_procs
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|load_procs
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|lowercase_basename
decl_stmt|;
name|gchar
modifier|*
name|help_page
decl_stmt|;
name|file_proc
operator|=
operator|(
name|PlugInProcDef
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|basename
operator|=
name|g_path_get_basename
argument_list|(
name|file_proc
operator|->
name|prog
argument_list|)
expr_stmt|;
name|lowercase_basename
operator|=
name|g_ascii_strdown
argument_list|(
name|basename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|help_page
operator|=
name|g_strconcat
argument_list|(
literal|"filters/"
argument_list|,
name|lowercase_basename
argument_list|,
literal|".html"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|lowercase_basename
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|strstr
argument_list|(
name|file_proc
operator|->
name|menu_path
argument_list|,
literal|"/"
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|accelerator
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback
operator|=
name|file_open_type_callback
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|callback_action
operator|=
literal|0
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|item_type
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|quark_string
operator|=
name|NULL
expr_stmt|;
name|entry
operator|.
name|help_page
operator|=
name|help_page
expr_stmt|;
name|entry
operator|.
name|description
operator|=
name|NULL
expr_stmt|;
name|gimp_item_factory_create_item
argument_list|(
name|item_factory
argument_list|,
operator|&
name|entry
argument_list|,
name|file_proc
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_open_dialog_menu_reset (void)
name|file_open_dialog_menu_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|load_file_proc
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_open_dialog_show (Gimp * gimp)
name|file_open_dialog_show
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fileload
condition|)
name|file_open_dialog_create
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|fileload
argument_list|)
condition|)
return|return;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Open Image"
argument_list|)
argument_list|)
expr_stmt|;
name|file_dialog_show
argument_list|(
name|fileload
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
DECL|function|file_open_dialog_create (Gimp * gimp)
name|file_open_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|file_sel
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|tree_sel
decl_stmt|;
name|fileload
operator|=
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Open Image"
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|"load_image"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|file_sel
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|file_sel
operator|->
name|button_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect_swapped
argument_list|(
name|G_OBJECT
argument_list|(
name|file_sel
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|fileload
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|file_sel
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_open_ok_callback
argument_list|)
argument_list|,
name|fileload
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_select_multiple
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|tree_sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
operator|->
name|file_list
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Catch file-list clicks so we can update the preview thumbnail */
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|tree_sel
argument_list|)
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_open_selchanged_callback
argument_list|)
argument_list|,
name|fileload
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect
argument_list|(
name|fileload
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"open/dialogs/file_open.html"
argument_list|)
expr_stmt|;
block|{
name|GimpItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|open_options_genbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|open_options
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
comment|/* format-chooser frame */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Determine File Type"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|open_options
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|option_menu
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
name|option_menu
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|gimp_item_factory_from_path
argument_list|(
literal|"<Load>"
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|GTK_ITEM_FACTORY
argument_list|(
name|item_factory
argument_list|)
operator|->
name|widget
argument_list|)
expr_stmt|;
comment|/* Preview frame */
name|open_options_frame
operator|=
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|open_options
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|0
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
name|open_options_genbutton
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|open_options_genbutton
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|open_options_genbutton
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|open_options_genbutton
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_open_genbutton_callback
argument_list|)
argument_list|,
name|fileload
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|open_options_genbutton
argument_list|,
name|_
argument_list|(
literal|"Click to create preview"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|open_options_imagefile
operator|=
name|gimp_imagefile_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|open_options_imagefile
argument_list|)
argument_list|,
literal|128
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|open_options_genbutton
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|open_options_imagefile
argument_list|)
argument_list|,
literal|"info_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_open_imagefile_info_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|open_options_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"No Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|open_options_label
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
name|open_options_label
argument_list|)
expr_stmt|;
comment|/* pack the containing open_options hbox into the open-dialog */
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|open_options
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|open_options_frame
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|open_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_type_callback (GtkWidget * widget,gpointer data)
name|file_open_type_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PlugInProcDef
modifier|*
name|proc
init|=
operator|(
name|PlugInProcDef
operator|*
operator|)
name|data
decl_stmt|;
name|file_dialog_update_name
argument_list|(
name|proc
argument_list|,
name|GTK_FILE_SELECTION
argument_list|(
name|fileload
argument_list|)
argument_list|)
expr_stmt|;
name|load_file_proc
operator|=
name|proc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_imagefile_info_changed (GimpImagefile * imagefile,gpointer data)
name|file_open_imagefile_info_changed
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|uri
decl_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|imagefile
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|uri
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|open_options_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"No Selection"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label
argument_list|(
name|GTK_FRAME
argument_list|(
name|open_options_frame
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|basename
decl_stmt|;
name|basename
operator|=
name|file_utils_uri_to_utf8_basename
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|gtk_frame_set_label
argument_list|(
name|GTK_FRAME
argument_list|(
name|open_options_frame
argument_list|)
argument_list|,
name|basename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
block|}
switch|switch
condition|(
name|imagefile
operator|->
name|thumb_state
condition|)
block|{
case|case
name|GIMP_IMAGEFILE_STATE_UNKNOWN
case|:
case|case
name|GIMP_IMAGEFILE_STATE_REMOTE
case|:
case|case
name|GIMP_IMAGEFILE_STATE_NOT_FOUND
case|:
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|open_options_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"No preview available"
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_IMAGEFILE_STATE_EXISTS
case|:
if|if
condition|(
name|imagefile
operator|->
name|image_mtime
operator|>
name|imagefile
operator|->
name|thumb_mtime
condition|)
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|open_options_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Thumbnail is out of date"
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|gchar
modifier|*
name|size_str
decl_stmt|;
name|gchar
modifier|*
name|type_str
decl_stmt|;
name|size_str
operator|=
name|gimp_image_new_get_memsize_string
argument_list|(
name|imagefile
operator|->
name|size
argument_list|)
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_IMAGE_TYPE
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|imagefile
operator|->
name|type
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
block|{
name|type_str
operator|=
name|gettext
argument_list|(
name|enum_value
operator|->
name|value_name
argument_list|)
expr_stmt|;
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d x %d (%s, %s)"
argument_list|,
name|imagefile
operator|->
name|width
argument_list|,
name|imagefile
operator|->
name|height
argument_list|,
name|size_str
argument_list|,
name|type_str
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|str
operator|=
name|g_strdup_printf
argument_list|(
literal|"%d x %d (%s)"
argument_list|,
name|imagefile
operator|->
name|width
argument_list|,
name|imagefile
operator|->
name|height
argument_list|,
name|size_str
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|size_str
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|open_options_label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|selchanged_foreach (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter,gpointer data)
name|selchanged_foreach
parameter_list|(
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gboolean
modifier|*
name|selected
init|=
name|data
decl_stmt|;
operator|*
name|selected
operator|=
name|TRUE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_selchanged_callback (GtkTreeSelection * sel,gpointer data)
name|file_open_selchanged_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fileload
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|fullfname
decl_stmt|;
name|gboolean
name|selected
init|=
name|FALSE
decl_stmt|;
name|gtk_tree_selection_selected_foreach
argument_list|(
name|sel
argument_list|,
name|selchanged_foreach
argument_list|,
operator|&
name|selected
argument_list|)
expr_stmt|;
if|if
condition|(
name|selected
condition|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|fileload
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|fileload
argument_list|)
argument_list|,
literal|"gimp"
argument_list|)
argument_list|)
expr_stmt|;
name|fullfname
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|fileload
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|open_options_frame
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|uri
operator|=
name|file_utils_filename_to_uri
argument_list|(
name|gimp
operator|->
name|load_procs
argument_list|,
name|fullfname
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|open_options_imagefile
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|open_options_imagefile
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|gimp_imagefile_update
argument_list|(
name|open_options_imagefile
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_genbutton_callback (GtkWidget * widget,gpointer data)
name|file_open_genbutton_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fs
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|selections
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|"gimp"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_set_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|selections
operator|=
name|gtk_file_selection_get_selections
argument_list|(
name|fs
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|selections
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_file_test
argument_list|(
name|selections
index|[
name|i
index|]
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|uri
init|=
name|g_filename_to_uri
argument_list|(
name|selections
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp
operator|->
name|config
operator|->
name|write_thumbnails
condition|)
block|{
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|open_options_imagefile
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
name|gimp_imagefile_create_thumbnail
argument_list|(
name|open_options_imagefile
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
literal|0
block|{               gtk_label_set_text (GTK_LABEL (open_options_label),                                   _("Failed to generate preview."));             }
endif|#
directive|endif
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
name|g_strfreev
argument_list|(
name|selections
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_unset_busy
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_open_ok_callback (GtkWidget * widget,gpointer data)
name|file_open_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fs
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gchar
modifier|*
name|entered_filename
decl_stmt|;
name|GimpPDBStatusType
name|status
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|selections
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|fs
argument_list|)
argument_list|,
literal|"gimp"
argument_list|)
argument_list|)
expr_stmt|;
name|selections
operator|=
name|gtk_file_selection_get_selections
argument_list|(
name|fs
argument_list|)
expr_stmt|;
if|if
condition|(
name|selections
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|g_file_test
argument_list|(
name|selections
index|[
literal|0
index|]
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
condition|)
block|{
if|if
condition|(
name|selections
index|[
literal|0
index|]
index|[
name|strlen
argument_list|(
name|selections
index|[
literal|0
index|]
argument_list|)
operator|-
literal|1
index|]
operator|!=
name|G_DIR_SEPARATOR
condition|)
block|{
name|gchar
modifier|*
name|s
init|=
name|g_strconcat
argument_list|(
name|selections
index|[
literal|0
index|]
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|s
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|selections
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
name|g_strfreev
argument_list|(
name|selections
argument_list|)
expr_stmt|;
return|return;
block|}
name|entered_filename
operator|=
name|g_strdup
argument_list|(
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|fs
operator|->
name|selection_entry
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|g_file_test
argument_list|(
name|selections
index|[
literal|0
index|]
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
comment|/* try with the entered filename in case the user typed an URI */
name|uri
operator|=
name|g_strdup
argument_list|(
name|entered_filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|selections
index|[
literal|0
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|status
operator|=
name|file_open_with_proc_and_display
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|entered_filename
argument_list|,
name|load_file_proc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|entered_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|file_dialog_hide
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
comment|/* Hackery required. Please add error message. --bex */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Opening '%s' failed."
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
block|}
comment|/*    * Now deal with multiple selections from the filesel list    */
for|for
control|(
name|i
operator|=
literal|1
init|;
name|selections
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|g_file_test
argument_list|(
name|selections
index|[
name|i
index|]
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|)
condition|)
block|{
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|selections
index|[
name|i
index|]
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|status
operator|=
name|file_open_with_proc_and_display
argument_list|(
name|gimp
argument_list|,
name|uri
argument_list|,
name|uri
argument_list|,
name|load_file_proc
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|==
name|GIMP_PDB_SUCCESS
condition|)
block|{
name|file_dialog_hide
argument_list|(
name|data
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
comment|/* same as previous. --bex */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Opening '%s' failed."
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
block|}
block|}
name|g_strfreev
argument_list|(
name|selections
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

