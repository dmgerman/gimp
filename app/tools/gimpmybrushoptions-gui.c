begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_LIBMYPAINT
end_ifdef

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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpmybrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpmybrushoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_load_brush (const GimpDatafileData * file_data,gpointer user_data)
name|gimp_mybrush_options_load_brush
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
if|if
condition|(
name|gimp_datafiles_check_extension
argument_list|(
name|file_data
operator|->
name|basename
argument_list|,
literal|".myb"
argument_list|)
condition|)
block|{
name|GtkListStore
modifier|*
name|store
init|=
name|user_data
decl_stmt|;
name|GtkTreeIter
name|iter
init|=
block|{
literal|0
block|, }
decl_stmt|;
name|GdkPixbuf
modifier|*
name|pixbuf
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|gchar
modifier|*
name|basename
decl_stmt|;
name|gchar
modifier|*
name|preview_filename
decl_stmt|;
name|filename
operator|=
name|g_strdup
argument_list|(
name|file_data
operator|->
name|filename
argument_list|)
expr_stmt|;
name|g_object_weak_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|store
argument_list|)
argument_list|,
operator|(
name|GWeakNotify
operator|)
name|g_free
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|basename
operator|=
name|g_strndup
argument_list|(
name|filename
argument_list|,
name|strlen
argument_list|(
name|filename
argument_list|)
operator|-
literal|4
argument_list|)
expr_stmt|;
name|preview_filename
operator|=
name|g_strconcat
argument_list|(
name|basename
argument_list|,
literal|"_prev.png"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|basename
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|gdk_pixbuf_new_from_file
argument_list|(
name|preview_filename
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|preview_filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
block|{
name|GdkPixbuf
modifier|*
name|scaled
decl_stmt|;
name|gint
name|width
init|=
name|gdk_pixbuf_get_width
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gint
name|height
init|=
name|gdk_pixbuf_get_height
argument_list|(
name|pixbuf
argument_list|)
decl_stmt|;
name|gdouble
name|factor
init|=
literal|48.0
operator|/
name|height
decl_stmt|;
name|scaled
operator|=
name|gdk_pixbuf_scale_simple
argument_list|(
name|pixbuf
argument_list|,
name|width
operator|*
name|factor
argument_list|,
name|height
operator|*
name|factor
argument_list|,
name|GDK_INTERP_NEAREST
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
name|pixbuf
operator|=
name|scaled
expr_stmt|;
block|}
name|gtk_list_store_append
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|store
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|file_data
operator|->
name|basename
argument_list|,
name|GIMP_INT_STORE_PIXBUF
argument_list|,
name|pixbuf
argument_list|,
name|GIMP_INT_STORE_USER_DATA
argument_list|,
name|filename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|pixbuf
condition|)
name|g_object_unref
argument_list|(
name|pixbuf
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_load_recursive (const GimpDatafileData * file_data,gpointer user_data)
name|gimp_mybrush_options_load_recursive
parameter_list|(
specifier|const
name|GimpDatafileData
modifier|*
name|file_data
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
block|{
name|gimp_datafiles_read_directories
argument_list|(
name|file_data
operator|->
name|filename
argument_list|,
name|G_FILE_TEST_IS_REGULAR
argument_list|,
name|gimp_mybrush_options_load_brush
argument_list|,
name|user_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_mybrush_options_brush_changed (GtkComboBox * combo,GObject * config)
name|gimp_mybrush_options_brush_changed
parameter_list|(
name|GtkComboBox
modifier|*
name|combo
parameter_list|,
name|GObject
modifier|*
name|config
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gtk_combo_box_get_active_iter
argument_list|(
name|combo
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
init|=
name|gtk_combo_box_get_model
argument_list|(
name|combo
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|brush
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|GIMP_INT_STORE_USER_DATA
argument_list|,
operator|&
name|brush
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
condition|)
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"mybrush"
argument_list|,
name|brush
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_mybrush_options_gui (GimpToolOptions * tool_options)
name|gimp_mybrush_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
comment|/* radius */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"radius"
argument_list|,
name|_
argument_list|(
literal|"Radius"
argument_list|)
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
comment|/* hardness */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"hardness"
argument_list|,
name|_
argument_list|(
literal|"Hardness"
argument_list|)
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
comment|/* brushes */
name|combo
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_INT_COMBO_BOX
argument_list|,
literal|"label"
argument_list|,
name|_
argument_list|(
literal|"Brush"
argument_list|)
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|combo
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
name|combo
argument_list|)
expr_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_datafiles_read_directories
argument_list|(
literal|"/usr/share/mypaint/brushes"
argument_list|,
name|G_FILE_TEST_IS_DIR
argument_list|,
name|gimp_mybrush_options_load_recursive
argument_list|,
name|model
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_mybrush_options_brush_changed
argument_list|)
argument_list|,
name|config
argument_list|)
expr_stmt|;
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|combo
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

