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
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
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
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in-proc.h"
end_include

begin_include
include|#
directive|include
file|"file/file-save.h"
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
file|"gimprc.h"
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
name|GtkWidget
modifier|*
name|file_save_dialog_create
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

begin_function_decl
specifier|static
name|void
name|file_save_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_overwrite
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|file_save_overwrite_callback
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
name|file_save_dialog_save_image
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_uri
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
DECL|variable|set_uri
specifier|static
name|gboolean
name|set_uri
init|=
name|TRUE
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|file_save_dialog_menu_init (Gimp * gimp,GimpItemFactory * item_factory)
name|file_save_dialog_menu_init
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
name|save_procs
operator|=
name|g_slist_reverse
argument_list|(
name|gimp
operator|->
name|save_procs
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
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
comment|/*  NOT g_build_filename() because this is a relative URI */
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
name|gimp_item_factory_create_item
argument_list|(
name|item_factory
argument_list|,
operator|&
name|entry
argument_list|,
name|NULL
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
name|g_free
argument_list|(
name|help_page
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
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
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
name|set_uri
operator|=
name|TRUE
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filesave
condition|)
name|filesave
operator|=
name|file_save_dialog_create
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
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
name|file_dialog_update_menus
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|save_procs
argument_list|,
name|gimp_drawable_type
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
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
name|uri
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
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
name|set_uri
operator|=
name|FALSE
expr_stmt|;
name|uri
operator|=
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
condition|)
name|filename
operator|=
name|g_filename_from_uri
argument_list|(
name|uri
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|filesave
condition|)
name|filesave
operator|=
name|file_save_dialog_create
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
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
name|file_dialog_update_menus
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|save_procs
argument_list|,
name|gimp_drawable_type
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
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
name|GtkWidget
modifier|*
DECL|function|file_save_dialog_create (Gimp * gimp)
name|file_save_dialog_create
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
return|return
name|file_dialog_new
argument_list|(
name|gimp
argument_list|,
name|gimp_item_factory_from_path
argument_list|(
literal|"<Save>"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Save Image"
argument_list|)
argument_list|,
literal|"save_image"
argument_list|,
literal|"save/dialogs/file_save.html"
argument_list|,
name|G_CALLBACK
argument_list|(
name|file_save_ok_callback
argument_list|)
argument_list|)
return|;
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
name|GTK_FILE_SELECTION
argument_list|(
name|filesave
argument_list|)
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
DECL|function|file_save_ok_callback (GtkWidget * widget,GtkWidget * save_dialog)
name|file_save_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|)
block|{
name|GtkFileSelection
modifier|*
name|fs
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
name|gchar
modifier|*
name|uri
decl_stmt|;
name|fs
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|save_dialog
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
name|uri
operator|=
name|g_filename_to_uri
argument_list|(
name|filename
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|{
name|gchar
modifier|*
name|dot
decl_stmt|;
name|gint
name|x
decl_stmt|;
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
block|{
break|break;
block|}
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
name|drawable
decl_stmt|;
name|file_dialog_hide
argument_list|(
name|save_dialog
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|the_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|the_gimage
operator|->
name|gimp
argument_list|,
literal|"plug_in_the_slimy_egg"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
return|return;
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
name|GIMP_RUN_INTERACTIVE
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
name|gimp_item_get_ID
argument_list|(
name|GIMP_ITEM
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|plug_in_run
argument_list|(
name|the_gimage
operator|->
name|gimp
argument_list|,
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
block|}
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_EXISTS
argument_list|)
condition|)
block|{
if|if
condition|(
name|g_file_test
argument_list|(
name|filename
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|)
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
block|{
name|gtk_file_selection_set_filename
argument_list|(
name|fs
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|file_save_overwrite
argument_list|(
name|save_dialog
argument_list|,
name|uri
argument_list|,
name|raw_filename
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
name|file_save_dialog_save_image
argument_list|(
name|save_dialog
argument_list|,
name|the_gimage
argument_list|,
name|uri
argument_list|,
name|raw_filename
argument_list|,
name|save_file_proc
argument_list|,
name|set_uri
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
block|}
end_function

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
DECL|member|save_dialog
name|GtkWidget
modifier|*
name|save_dialog
decl_stmt|;
DECL|member|uri
name|gchar
modifier|*
name|uri
decl_stmt|;
DECL|member|raw_filename
name|gchar
modifier|*
name|raw_filename
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|void
DECL|function|file_save_overwrite (GtkWidget * save_dialog,const gchar * uri,const gchar * raw_filename)
name|file_save_overwrite
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
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
name|g_new0
argument_list|(
name|OverwriteData
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|overwrite_data
operator|->
name|save_dialog
operator|=
name|save_dialog
expr_stmt|;
name|overwrite_data
operator|->
name|uri
operator|=
name|g_strdup
argument_list|(
name|uri
argument_list|)
expr_stmt|;
name|overwrite_data
operator|->
name|raw_filename
operator|=
name|g_strdup
argument_list|(
name|raw_filename
argument_list|)
expr_stmt|;
name|overwrite_text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"File '%s' exists.\n"
literal|"Overwrite it?"
argument_list|)
argument_list|,
name|uri
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
name|GTK_STOCK_DIALOG_QUESTION
argument_list|,
name|overwrite_text
argument_list|,
name|GTK_STOCK_YES
argument_list|,
name|GTK_STOCK_NO
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|file_save_overwrite_callback
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
name|gtk_widget_set_sensitive
argument_list|(
name|save_dialog
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|file_save_overwrite_callback (GtkWidget * widget,gboolean overwrite,gpointer data)
name|file_save_overwrite_callback
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
name|file_save_dialog_save_image
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
argument_list|,
name|the_gimage
argument_list|,
name|overwrite_data
operator|->
name|uri
argument_list|,
name|overwrite_data
operator|->
name|raw_filename
argument_list|,
name|save_file_proc
argument_list|,
name|set_uri
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|overwrite_data
operator|->
name|save_dialog
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|overwrite_data
operator|->
name|uri
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

begin_function
specifier|static
name|void
DECL|function|file_save_dialog_save_image (GtkWidget * save_dialog,GimpImage * gimage,const gchar * uri,const gchar * raw_filename,PlugInProcDef * save_proc,gboolean set_uri)
name|file_save_dialog_save_image
parameter_list|(
name|GtkWidget
modifier|*
name|save_dialog
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|,
specifier|const
name|gchar
modifier|*
name|raw_filename
parameter_list|,
name|PlugInProcDef
modifier|*
name|save_proc
parameter_list|,
name|gboolean
name|set_uri
parameter_list|)
block|{
name|GimpPDBStatusType
name|status
decl_stmt|;
name|status
operator|=
name|file_save
argument_list|(
name|gimage
argument_list|,
name|uri
argument_list|,
name|raw_filename
argument_list|,
name|save_proc
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|,
name|set_uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|status
operator|!=
name|GIMP_PDB_SUCCESS
operator|&&
name|status
operator|!=
name|GIMP_PDB_CANCEL
condition|)
block|{
comment|/* Another error required. --bex */
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Saving '%s' failed."
argument_list|)
argument_list|,
name|uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|file_dialog_hide
argument_list|(
name|save_dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

