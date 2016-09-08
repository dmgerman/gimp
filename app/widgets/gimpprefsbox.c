begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprefsbox.c  * Copyright (C) 2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpprefsbox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon29ab4c860103
block|{
DECL|enumerator|COLUMN_TREE_ICON_NAME
name|COLUMN_TREE_ICON_NAME
block|,
DECL|enumerator|COLUMN_TREE_ICON_SIZE
name|COLUMN_TREE_ICON_SIZE
block|,
DECL|enumerator|COLUMN_TREE_LABEL
name|COLUMN_TREE_LABEL
block|,
DECL|enumerator|COLUMN_NOTEBOOK_ICON_NAME
name|COLUMN_NOTEBOOK_ICON_NAME
block|,
DECL|enumerator|COLUMN_NOTEBOOK_ICON_SIZE
name|COLUMN_NOTEBOOK_ICON_SIZE
block|,
DECL|enumerator|COLUMN_NOTEBOOK_LABEL
name|COLUMN_NOTEBOOK_LABEL
block|,
DECL|enumerator|COLUMN_PAGE_INDEX
name|COLUMN_PAGE_INDEX
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpPrefsBoxPrivate
typedef|typedef
name|struct
name|_GimpPrefsBoxPrivate
name|GimpPrefsBoxPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPrefsBoxPrivate
struct|struct
name|_GimpPrefsBoxPrivate
block|{
DECL|member|store
name|GtkTreeStore
modifier|*
name|store
decl_stmt|;
DECL|member|tree_view
name|GtkWidget
modifier|*
name|tree_view
decl_stmt|;
DECL|member|notebook
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
DECL|member|label
name|GtkWidget
modifier|*
name|label
decl_stmt|;
DECL|member|image
name|GtkWidget
modifier|*
name|image
decl_stmt|;
DECL|member|tree_icon_size
name|gint
name|tree_icon_size
decl_stmt|;
DECL|member|notebook_icon_size
name|gint
name|notebook_icon_size
decl_stmt|;
DECL|member|page_index
name|gint
name|page_index
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (item)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|item
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (item, \                                                        GIMP_TYPE_PREFS_BOX, \                                                        GimpPrefsBoxPrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_prefs_box_tree_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_prefs_box_notebook_page_callback
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpPrefsBox,gimp_prefs_box,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpPrefsBox
argument_list|,
argument|gimp_prefs_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_prefs_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_prefs_box_class_init
parameter_list|(
name|GimpPrefsBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpPrefsBoxPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prefs_box_init (GimpPrefsBox * box)
name|gimp_prefs_box_init
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpPrefsBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkCellRenderer
modifier|*
name|cell
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
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
name|ebox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|private
operator|->
name|tree_icon_size
operator|=
name|GTK_ICON_SIZE_BUTTON
expr_stmt|;
name|private
operator|->
name|notebook_icon_size
operator|=
name|GTK_ICON_SIZE_DIALOG
expr_stmt|;
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
comment|/*  the categories tree  */
name|frame
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
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
argument_list|,
name|GTK_POLICY_AUTOMATIC
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|private
operator|->
name|store
operator|=
name|gtk_tree_store_new
argument_list|(
literal|7
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_STRING
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|private
operator|->
name|tree_view
operator|=
name|gtk_tree_view_new_with_model
argument_list|(
name|GTK_TREE_MODEL
argument_list|(
name|private
operator|->
name|store
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|private
operator|->
name|store
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_pixbuf_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"icon-name"
argument_list|,
name|COLUMN_TREE_ICON_NAME
argument_list|,
literal|"stock-size"
argument_list|,
name|COLUMN_TREE_ICON_SIZE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cell
operator|=
name|gtk_cell_renderer_text_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|column
argument_list|,
name|cell
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_TREE_LABEL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|,
name|column
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|private
operator|->
name|tree_view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
expr_stmt|;
comment|/*  the notebook  */
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
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
name|ebox
operator|=
name|gtk_event_box_new
argument_list|()
expr_stmt|;
name|gtk_widget_set_state
argument_list|(
name|ebox
argument_list|,
name|GTK_STATE_SELECTED
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|ebox
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|ebox
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|ebox
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
name|private
operator|->
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_LARGE
argument_list|,
name|PANGO_ATTR_WEIGHT
argument_list|,
name|PANGO_WEIGHT_BOLD
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|private
operator|->
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
name|private
operator|->
name|label
argument_list|)
expr_stmt|;
name|private
operator|->
name|image
operator|=
name|gtk_image_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|private
operator|->
name|image
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
name|private
operator|->
name|image
argument_list|)
expr_stmt|;
comment|/* The main preferences notebook */
name|private
operator|->
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_notebook_set_show_border
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|private
operator|->
name|notebook
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
name|private
operator|->
name|notebook
argument_list|)
expr_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|sel
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prefs_box_tree_select_callback
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|private
operator|->
name|notebook
argument_list|,
literal|"switch-page"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_prefs_box_notebook_page_callback
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prefs_box_tree_select_callback (GtkTreeSelection * sel,GimpPrefsBox * box)
name|gimp_prefs_box_tree_select_callback
parameter_list|(
name|GtkTreeSelection
modifier|*
name|sel
parameter_list|,
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpPrefsBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gchar
modifier|*
name|notebook_text
decl_stmt|;
name|gchar
modifier|*
name|notebook_icon_name
decl_stmt|;
name|gint
name|notebook_icon_size
decl_stmt|;
name|gint
name|notebook_index
decl_stmt|;
if|if
condition|(
operator|!
name|gtk_tree_selection_get_selected
argument_list|(
name|sel
argument_list|,
operator|&
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
return|return;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_NOTEBOOK_ICON_NAME
argument_list|,
operator|&
name|notebook_icon_name
argument_list|,
name|COLUMN_NOTEBOOK_ICON_SIZE
argument_list|,
operator|&
name|notebook_icon_size
argument_list|,
name|COLUMN_NOTEBOOK_LABEL
argument_list|,
operator|&
name|notebook_text
argument_list|,
name|COLUMN_PAGE_INDEX
argument_list|,
operator|&
name|notebook_index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|private
operator|->
name|label
argument_list|)
argument_list|,
name|notebook_text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|notebook_text
argument_list|)
expr_stmt|;
name|gtk_image_set_from_icon_name
argument_list|(
name|GTK_IMAGE
argument_list|(
name|private
operator|->
name|image
argument_list|)
argument_list|,
name|notebook_icon_name
argument_list|,
name|notebook_icon_size
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|notebook_icon_name
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|private
operator|->
name|notebook
argument_list|,
name|gimp_prefs_box_notebook_page_callback
argument_list|,
name|sel
argument_list|)
expr_stmt|;
name|gtk_notebook_set_current_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|notebook_index
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|private
operator|->
name|notebook
argument_list|,
name|gimp_prefs_box_notebook_page_callback
argument_list|,
name|sel
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_prefs_box_notebook_page_callback (GtkNotebook * notebook,gpointer page,guint page_num,GimpPrefsBox * box)
name|gimp_prefs_box_notebook_page_callback
parameter_list|(
name|GtkNotebook
modifier|*
name|notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpPrefsBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
name|GtkTreeSelection
modifier|*
name|sel
decl_stmt|;
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|sel
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
name|model
operator|=
name|gtk_tree_view_get_model
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
init|;
name|iter_valid
condition|;
name|iter_valid
operator|=
name|gtk_tree_model_iter_next
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|gint
name|index
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_PAGE_INDEX
argument_list|,
operator|&
name|index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
name|page_num
condition|)
block|{
name|gtk_tree_selection_select_iter
argument_list|(
name|sel
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gtk_tree_model_iter_has_child
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gint
name|num_children
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|num_children
operator|=
name|gtk_tree_model_iter_n_children
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_children
condition|;
name|i
operator|++
control|)
block|{
name|GtkTreeIter
name|child_iter
decl_stmt|;
name|gtk_tree_model_iter_nth_child
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
operator|&
name|iter
argument_list|,
name|i
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|,
name|COLUMN_PAGE_INDEX
argument_list|,
operator|&
name|index
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
name|page_num
condition|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|path
operator|=
name|gtk_tree_model_get_path
argument_list|(
name|model
argument_list|,
operator|&
name|child_iter
argument_list|)
expr_stmt|;
name|gtk_tree_view_expand_to_path
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|private
operator|->
name|tree_view
argument_list|)
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_selection_select_iter
argument_list|(
name|sel
argument_list|,
operator|&
name|child_iter
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prefs_box_new (void)
name|gimp_prefs_box_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PREFS_BOX
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prefs_box_add_page (GimpPrefsBox * box,const gchar * icon_name,const gchar * notebook_label,const gchar * tree_label,const gchar * help_id,GtkTreeIter * parent,GtkTreeIter * iter)
name|gimp_prefs_box_add_page
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|notebook_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tree_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|GimpPrefsBoxPrivate
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|GtkWidget
modifier|*
name|viewport
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PREFS_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_scrolled_window_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
argument_list|,
name|GTK_POLICY_NEVER
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|private
operator|->
name|notebook
argument_list|)
argument_list|,
name|scrolled_win
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scrolled_win
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|scrolled_win
argument_list|,
name|NULL
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
name|viewport
operator|=
name|gtk_viewport_new
argument_list|(
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_viewport_set_shadow_type
argument_list|(
name|GTK_VIEWPORT
argument_list|(
name|viewport
argument_list|)
argument_list|,
name|GTK_SHADOW_NONE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|viewport
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|viewport
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|viewport
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
name|gtk_tree_store_append
argument_list|(
name|private
operator|->
name|store
argument_list|,
name|iter
argument_list|,
name|parent
argument_list|)
expr_stmt|;
name|gtk_tree_store_set
argument_list|(
name|private
operator|->
name|store
argument_list|,
name|iter
argument_list|,
name|COLUMN_TREE_ICON_NAME
argument_list|,
name|icon_name
argument_list|,
name|COLUMN_TREE_ICON_SIZE
argument_list|,
name|private
operator|->
name|tree_icon_size
argument_list|,
name|COLUMN_TREE_LABEL
argument_list|,
name|tree_label
argument_list|,
name|COLUMN_NOTEBOOK_ICON_NAME
argument_list|,
name|icon_name
argument_list|,
name|COLUMN_NOTEBOOK_ICON_SIZE
argument_list|,
name|private
operator|->
name|notebook_icon_size
argument_list|,
name|COLUMN_NOTEBOOK_LABEL
argument_list|,
name|notebook_label
argument_list|,
name|COLUMN_PAGE_INDEX
argument_list|,
name|private
operator|->
name|page_index
operator|++
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_prefs_box_set_page_scrollable (GimpPrefsBox * box,GtkWidget * page,gboolean scrollable)
name|gimp_prefs_box_set_page_scrollable
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|page
parameter_list|,
name|gboolean
name|scrollable
parameter_list|)
block|{
name|GimpPrefsBoxPrivate
modifier|*
name|private
decl_stmt|;
name|GtkWidget
modifier|*
name|scrolled_win
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PREFS_BOX
argument_list|(
name|box
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GTK_IS_BOX
argument_list|(
name|page
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gtk_widget_is_ancestor
argument_list|(
name|page
argument_list|,
name|GTK_WIDGET
argument_list|(
name|box
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|scrolled_win
operator|=
name|gtk_widget_get_ancestor
argument_list|(
name|page
argument_list|,
name|GTK_TYPE_SCROLLED_WINDOW
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gtk_widget_get_parent
argument_list|(
name|scrolled_win
argument_list|)
operator|==
name|private
operator|->
name|notebook
argument_list|)
expr_stmt|;
name|gtk_scrolled_window_set_policy
argument_list|(
name|GTK_SCROLLED_WINDOW
argument_list|(
name|scrolled_win
argument_list|)
argument_list|,
name|GTK_POLICY_NEVER
argument_list|,
name|scrollable
condition|?
name|GTK_POLICY_AUTOMATIC
else|:
name|GTK_POLICY_NEVER
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prefs_box_get_tree_view (GimpPrefsBox * box)
name|gimp_prefs_box_get_tree_view
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PREFS_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
operator|->
name|tree_view
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prefs_box_get_notebook (GimpPrefsBox * box)
name|gimp_prefs_box_get_notebook
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PREFS_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
operator|->
name|notebook
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_prefs_box_get_image (GimpPrefsBox * box)
name|gimp_prefs_box_get_image
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PREFS_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GET_PRIVATE
argument_list|(
name|box
argument_list|)
operator|->
name|image
return|;
block|}
end_function

end_unit

