begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995, 1996, 1997 Spencer Kimball and Peter Mattis  * Copyright (C) 1997 Josh MacDonald  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"file-dialog-utils.h"
end_include

begin_include
include|#
directive|include
file|"file-save-dialog.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"docindex.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"file-save.h"
end_include

begin_include
include|#
directive|include
file|"file-utils.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
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

begin_typedef
DECL|typedef|OverwriteData
typedef|typedef
name|struct
name|_OverwriteData
name|OverwriteData
typedef|;
end_typedef

begin_struct
DECL|struct|_OverwriteData
struct|struct
name|_OverwriteData
block|{
DECL|member|full_filename
name|gchar
modifier|*
name|full_filename
decl_stmt|;
DECL|member|raw_filename
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|file_save_dialog_create
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_overwrite
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gchar
modifier|*
name|raw_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_overwrite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|overwrite
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_ok_callback
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
name|file_save_type_callback
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

begin_decl_stmt
DECL|variable|filesave
specifier|static
name|GtkWidget
modifier|*
name|filesave
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|save_options
specifier|static
name|GtkWidget
modifier|*
name|save_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|save_file_proc
specifier|static
name|PlugInProcDef
modifier|*
name|save_file_proc
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|the_gimage
specifier|static
name|GimpImage
modifier|*
name|the_gimage
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|set_filename
specifier|static
name|gboolean
name|set_filename
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_save_dialog_menu_init (void)
name|file_save_dialog_menu_init
parameter_list|(
name|void
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
name|save_procs
operator|=
name|g_slist_reverse
argument_list|(
name|save_procs
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|save_procs
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
name|help_page
operator|=
name|g_strconcat
argument_list|(
literal|"filters/"
argument_list|,
name|g_basename
argument_list|(
name|file_proc
operator|->
name|prog
argument_list|)
argument_list|,
literal|".html"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_strdown
argument_list|(
name|help_page
argument_list|)
expr_stmt|;
name|entry
operator|.
name|entry
operator|.
name|path
operator|=
name|file_proc
operator|->
name|menu_path
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
name|file_save_type_callback
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
name|menus_create_item_from_full_path
argument_list|(
operator|&
name|entry
argument_list|,
name|NULL
argument_list|,
name|file_proc
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|file_save_dialog_menu_reset (void)
name|file_save_dialog_menu_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|save_file_proc
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_dialog_show (GimpImage * gimage)
name|file_save_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
condition|)
return|return;
name|the_gimage
operator|=
name|gimage
expr_stmt|;
name|set_filename
operator|=
name|TRUE
expr_stmt|;
name|filename
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|the_gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filesave
condition|)
name|file_save_dialog_create
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|filesave
argument_list|)
condition|)
return|return;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_RGB_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|RGBA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_RGBA_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_GRAY_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GRAYA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_GRAYA_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_INDEXED_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|INDEXEDA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_INDEXEDA_IMAGE
argument_list|)
expr_stmt|;
break|break;
block|}
name|file_dialog_show
argument_list|(
name|filesave
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|file_save_a_copy_dialog_show (GimpImage * gimage)
name|file_save_a_copy_dialog_show
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
if|if
condition|(
operator|!
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
condition|)
return|return;
name|the_gimage
operator|=
name|gimage
expr_stmt|;
name|set_filename
operator|=
name|FALSE
expr_stmt|;
name|filename
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|the_gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filesave
condition|)
name|file_save_dialog_create
argument_list|()
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|filesave
argument_list|)
condition|)
return|return;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Save a Copy of the Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|filename
condition|?
name|filename
else|:
literal|"."
name|G_DIR_SEPARATOR_S
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|gimp_drawable_type
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
case|case
name|RGB_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_RGB_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|RGBA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_RGBA_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GRAY_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_GRAY_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|GRAYA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_GRAYA_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|INDEXED_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_INDEXED_IMAGE
argument_list|)
expr_stmt|;
break|break;
case|case
name|INDEXEDA_GIMAGE
case|:
name|file_dialog_update_menus
argument_list|(
name|save_procs
argument_list|,
name|PLUG_IN_INDEXEDA_IMAGE
argument_list|)
expr_stmt|;
break|break;
block|}
name|file_dialog_show
argument_list|(
name|filesave
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
DECL|function|file_save_dialog_create (void)
name|file_save_dialog_create
parameter_list|(
name|void
parameter_list|)
block|{
name|filesave
operator|=
name|gtk_file_selection_new
argument_list|(
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_wmclass
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
literal|"save_image"
argument_list|,
literal|"Gimp"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|filesave
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
name|filesave
argument_list|)
operator|->
name|button_area
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
operator|->
name|cancel_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|filesave
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|filesave
argument_list|)
argument_list|,
literal|"delete_event"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|file_dialog_hide
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
operator|->
name|ok_button
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|file_save_ok_callback
argument_list|)
argument_list|,
name|filesave
argument_list|)
expr_stmt|;
name|gtk_quit_add_destroy
argument_list|(
literal|1
argument_list|,
name|GTK_OBJECT
argument_list|(
name|filesave
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Connect the "F1" help key  */
name|gimp_help_connect_help_accel
argument_list|(
name|filesave
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"save/dialogs/file_save.html"
argument_list|)
expr_stmt|;
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|option_menu
decl_stmt|;
name|GtkWidget
modifier|*
name|save_menu
decl_stmt|;
name|save_options
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Save Options"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_ETCHED_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|save_options
argument_list|)
argument_list|,
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
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
name|hbox
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
name|hbox
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
literal|"Determine File Type:"
argument_list|)
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|option_menu
argument_list|)
expr_stmt|;
name|save_menu
operator|=
name|menus_get_save_factory
argument_list|()
operator|->
name|widget
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|option_menu
argument_list|)
argument_list|,
name|save_menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/* pack the containing save_options hbox into the save-dialog */
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|save_options
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|save_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_type_callback (GtkWidget * widget,gpointer data)
name|file_save_type_callback
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
name|filesave
argument_list|)
expr_stmt|;
name|save_file_proc
operator|=
name|proc
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_ok_callback (GtkWidget * widget,gpointer data)
name|file_save_ok_callback
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
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
name|gchar
modifier|*
name|dot
decl_stmt|;
name|gint
name|x
decl_stmt|;
name|struct
name|stat
name|buf
decl_stmt|;
name|gint
name|err
decl_stmt|;
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|fs
argument_list|)
expr_stmt|;
name|raw_filename
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|fs
operator|->
name|selection_entry
argument_list|)
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|filename
operator|&&
name|raw_filename
argument_list|)
expr_stmt|;
for|for
control|(
name|dot
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
literal|'.'
argument_list|)
operator|,
name|x
operator|=
literal|0
init|;
name|dot
operator|&&
operator|*
operator|(
operator|++
name|dot
operator|)
condition|;
control|)
block|{
if|if
condition|(
operator|*
name|dot
operator|!=
literal|'e'
operator|||
operator|++
name|x
operator|<
literal|0
condition|)
break|break;
elseif|else
if|if
condition|(
name|x
operator|>
literal|3
operator|&&
operator|!
name|strcmp
argument_list|(
name|dot
operator|+
literal|1
argument_list|,
literal|"k"
argument_list|)
condition|)
block|{
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
name|Argument
modifier|*
name|args
decl_stmt|;
name|GimpDrawable
modifier|*
name|the_drawable
decl_stmt|;
name|the_drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|the_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|the_drawable
condition|)
return|return;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|the_gimp
argument_list|,
literal|"plug_in_the_slimy_egg"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
break|break;
name|file_dialog_hide
argument_list|(
name|filesave
argument_list|)
expr_stmt|;
name|args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_INT32
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|RUN_INTERACTIVE
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_IMAGE
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_image_get_ID
argument_list|(
name|the_gimage
argument_list|)
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_DRAWABLE
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|gimp_drawable_get_ID
argument_list|(
name|the_drawable
argument_list|)
expr_stmt|;
name|plug_in_run
argument_list|(
name|proc_rec
argument_list|,
name|args
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|err
operator|=
name|stat
argument_list|(
name|filename
argument_list|,
operator|&
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|buf
operator|.
name|st_mode
operator|&
name|S_IFDIR
condition|)
block|{
if|if
condition|(
name|filename
index|[
name|strlen
argument_list|(
name|filename
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
name|filename
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
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
name|file_overwrite
argument_list|(
name|g_strdup
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strdup
argument_list|(
name|raw_filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
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
name|file_save_with_proc
argument_list|(
name|the_gimage
argument_list|,
name|filename
argument_list|,
name|raw_filename
argument_list|,
name|save_file_proc
argument_list|,
name|set_filename
argument_list|)
condition|)
block|{
name|file_dialog_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|fs
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_overwrite (gchar * filename,gchar * raw_filename)
name|file_overwrite
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|,
name|gchar
modifier|*
name|raw_filename
parameter_list|)
block|{
name|OverwriteData
modifier|*
name|overwrite_data
decl_stmt|;
name|GtkWidget
modifier|*
name|query_box
decl_stmt|;
name|gchar
modifier|*
name|overwrite_text
decl_stmt|;
name|overwrite_data
operator|=
name|g_new
argument_list|(
name|OverwriteData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|overwrite_data
operator|->
name|full_filename
operator|=
name|filename
expr_stmt|;
name|overwrite_data
operator|->
name|raw_filename
operator|=
name|raw_filename
expr_stmt|;
name|overwrite_text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%s exists, overwrite?"
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|query_box
operator|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"File Exists!"
argument_list|)
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"save/file_exists.html"
argument_list|,
name|FALSE
argument_list|,
name|overwrite_text
argument_list|,
name|_
argument_list|(
literal|"Yes"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"No"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|file_overwrite_callback
argument_list|,
name|overwrite_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_text
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|query_box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_overwrite_callback (GtkWidget * widget,gboolean overwrite,gpointer data)
name|file_overwrite_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|overwrite
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|OverwriteData
modifier|*
name|overwrite_data
decl_stmt|;
name|overwrite_data
operator|=
operator|(
name|OverwriteData
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|overwrite
condition|)
block|{
if|if
condition|(
name|file_save_with_proc
argument_list|(
name|the_gimage
argument_list|,
name|overwrite_data
operator|->
name|full_filename
argument_list|,
name|overwrite_data
operator|->
name|raw_filename
argument_list|,
name|save_file_proc
argument_list|,
name|set_filename
argument_list|)
condition|)
block|{
name|file_dialog_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* always make file save dialog sensitive */
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|filesave
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
operator|->
name|full_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
operator|->
name|raw_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

