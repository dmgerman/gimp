begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcomponenteditor.c  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrenderertoggle.h"
end_include

begin_include
include|#
directive|include
file|"gimpcellrendererviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcomponenteditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimppreviewrendererimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b7c7cbe0103
block|{
DECL|enumerator|COLUMN_CHANNEL
name|COLUMN_CHANNEL
block|,
DECL|enumerator|COLUMN_VISIBLE
name|COLUMN_VISIBLE
block|,
DECL|enumerator|COLUMN_RENDERER
name|COLUMN_RENDERER
block|,
DECL|enumerator|COLUMN_NAME
name|COLUMN_NAME
block|,
DECL|enumerator|NUM_COLUMNS
name|NUM_COLUMNS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_class_init
parameter_list|(
name|GimpComponentEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_init
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_create_components
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_clear_components
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_clicked
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|cellrenderertoggle
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_component_editor_select
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|gboolean
name|path_currently_selected
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_component_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_renderer_update
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_mode_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_alpha_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_visibility_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_component_editor_active_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_component_editor_get_type (void)
name|gimp_component_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|editor_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|editor_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|editor_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpComponentEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_component_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpComponentEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_component_editor_init
block|,       }
decl_stmt|;
name|editor_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
literal|"GimpComponentEditor"
argument_list|,
operator|&
name|editor_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|editor_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_class_init (GimpComponentEditorClass * klass)
name|gimp_component_editor_class_init
parameter_list|(
name|GimpComponentEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpImageEditorClass
modifier|*
name|image_editor_class
decl_stmt|;
name|image_editor_class
operator|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_component_editor_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_init (GimpComponentEditor * editor)
name|gimp_component_editor_init
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkListStore
modifier|*
name|list
decl_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
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
name|list
operator|=
name|gtk_list_store_new
argument_list|(
name|NUM_COLUMNS
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_BOOLEAN
argument_list|,
name|GIMP_TYPE_PREVIEW_RENDERER
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|editor
operator|->
name|model
operator|=
name|GTK_TREE_MODEL
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|editor
operator|->
name|view
operator|=
name|GTK_TREE_VIEW
argument_list|(
name|gtk_tree_view_new_with_model
argument_list|(
name|editor
operator|->
name|model
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|list
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_headers_visible
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|eye_column
operator|=
name|gtk_tree_view_column_new
argument_list|()
expr_stmt|;
name|gtk_tree_view_append_column
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|editor
operator|->
name|eye_column
argument_list|)
expr_stmt|;
name|editor
operator|->
name|eye_cell
operator|=
name|gimp_cell_renderer_toggle_new
argument_list|(
name|GIMP_STOCK_VISIBLE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_pack_start
argument_list|(
name|editor
operator|->
name|eye_column
argument_list|,
name|editor
operator|->
name|eye_cell
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_tree_view_column_set_attributes
argument_list|(
name|editor
operator|->
name|eye_column
argument_list|,
name|editor
operator|->
name|eye_cell
argument_list|,
literal|"active"
argument_list|,
name|COLUMN_VISIBLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|eye_cell
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_clicked
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|editor
operator|->
name|view
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|gimp_cell_renderer_viewable_new
argument_list|()
argument_list|,
literal|"renderer"
argument_list|,
name|COLUMN_RENDERER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tree_view_insert_column_with_attributes
argument_list|(
name|editor
operator|->
name|view
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|gtk_cell_renderer_text_new
argument_list|()
argument_list|,
literal|"text"
argument_list|,
name|COLUMN_NAME
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"button_press_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_button_press
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|editor
operator|->
name|selection
operator|=
name|gtk_tree_view_get_selection
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_tree_selection_set_mode
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
name|GTK_SELECTION_MULTIPLE
argument_list|)
expr_stmt|;
name|gtk_tree_selection_set_select_function
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
name|gimp_component_editor_select
argument_list|,
name|editor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_set_image (GimpImageEditor * editor,GimpImage * gimage)
name|gimp_component_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|GimpComponentEditor
modifier|*
name|component_editor
decl_stmt|;
name|component_editor
operator|=
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_component_editor_clear_components
argument_list|(
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|gimp_component_editor_mode_changed
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|gimp_component_editor_alpha_changed
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|gimp_component_editor_visibility_changed
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
name|gimp_component_editor_active_changed
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
block|}
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|editor
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|gimage
condition|)
block|{
name|gimp_component_editor_create_components
argument_list|(
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
literal|"mode_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_mode_changed
argument_list|)
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
literal|"alpha_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_alpha_changed
argument_list|)
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
literal|"component_visibility_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_visibility_changed
argument_list|)
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|gimage
argument_list|,
literal|"component_active_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_active_changed
argument_list|)
argument_list|,
name|component_editor
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_component_editor_new (gint preview_size,GimpMenuFactory * menu_factory)
name|gimp_component_editor_new
parameter_list|(
name|gint
name|preview_size
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|GimpComponentEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
name|GIMP_PREVIEW_MAX_SIZE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COMPONENT_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_component_editor_set_preview_size
argument_list|(
name|editor
argument_list|,
name|preview_size
argument_list|)
expr_stmt|;
name|gimp_editor_create_menu
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|menu_factory
argument_list|,
literal|"<Channels>"
argument_list|,
name|editor
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_component_editor_set_preview_size (GimpComponentEditor * editor,gint preview_size)
name|gimp_component_editor_set_preview_size
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|tree_widget
decl_stmt|;
name|GtkIconSize
name|icon_size
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gboolean
name|iter_valid
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_COMPONENT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
name|GIMP_PREVIEW_MAX_SIZE
argument_list|)
expr_stmt|;
name|tree_widget
operator|=
name|GTK_WIDGET
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|icon_size
operator|=
name|gimp_get_icon_size
argument_list|(
name|tree_widget
argument_list|,
name|GIMP_STOCK_VISIBLE
argument_list|,
name|GTK_ICON_SIZE_BUTTON
argument_list|,
name|preview_size
operator|-
literal|2
operator|*
name|tree_widget
operator|->
name|style
operator|->
name|xthickness
argument_list|,
name|preview_size
operator|-
literal|2
operator|*
name|tree_widget
operator|->
name|style
operator|->
name|ythickness
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|editor
operator|->
name|eye_cell
argument_list|,
literal|"stock-size"
argument_list|,
name|icon_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|iter_valid
operator|=
name|gtk_tree_model_get_iter_first
argument_list|(
name|editor
operator|->
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
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|)
control|)
block|{
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_RENDERER
argument_list|,
operator|&
name|renderer
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_set_size
argument_list|(
name|renderer
argument_list|,
name|preview_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
block|}
name|editor
operator|->
name|preview_size
operator|=
name|preview_size
expr_stmt|;
name|gtk_tree_view_columns_autosize
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_create_components (GimpComponentEditor * editor)
name|gimp_component_editor_create_components
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint
name|n_components
init|=
literal|0
decl_stmt|;
name|GimpChannelType
name|components
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
switch|switch
condition|(
name|gimp_image_base_type
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
case|case
name|GIMP_RGB
case|:
name|n_components
operator|=
literal|3
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_RED_CHANNEL
expr_stmt|;
name|components
index|[
literal|1
index|]
operator|=
name|GIMP_GREEN_CHANNEL
expr_stmt|;
name|components
index|[
literal|2
index|]
operator|=
name|GIMP_BLUE_CHANNEL
expr_stmt|;
break|break;
case|case
name|GIMP_GRAY
case|:
name|n_components
operator|=
literal|1
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_GRAY_CHANNEL
expr_stmt|;
break|break;
case|case
name|GIMP_INDEXED
case|:
name|n_components
operator|=
literal|1
expr_stmt|;
name|components
index|[
literal|0
index|]
operator|=
name|GIMP_INDEXED_CHANNEL
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|gimp_image_has_alpha
argument_list|(
name|gimage
argument_list|)
condition|)
name|components
index|[
name|n_components
operator|++
index|]
operator|=
name|GIMP_ALPHA_CHANNEL
expr_stmt|;
name|enum_class
operator|=
name|g_type_class_ref
argument_list|(
name|GIMP_TYPE_CHANNEL_TYPE
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
name|n_components
condition|;
name|i
operator|++
control|)
block|{
name|GimpPreviewRenderer
modifier|*
name|renderer
decl_stmt|;
name|gboolean
name|visible
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|visible
operator|=
name|gimp_image_get_component_visible
argument_list|(
name|gimage
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|renderer
operator|=
name|gimp_preview_renderer_new
argument_list|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|editor
operator|->
name|preview_size
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_set_viewable
argument_list|(
name|renderer
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_remove_idle
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
name|GIMP_PREVIEW_RENDERER_IMAGE
argument_list|(
name|renderer
argument_list|)
operator|->
name|channel
operator|=
name|components
index|[
name|i
index|]
expr_stmt|;
name|g_signal_connect
argument_list|(
name|renderer
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_component_editor_renderer_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value
argument_list|(
name|enum_class
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|gtk_list_store_append
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|editor
operator|->
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|editor
operator|->
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_CHANNEL
argument_list|,
name|components
index|[
name|i
index|]
argument_list|,
name|COLUMN_VISIBLE
argument_list|,
name|visible
argument_list|,
name|COLUMN_RENDERER
argument_list|,
name|renderer
argument_list|,
name|COLUMN_NAME
argument_list|,
name|gettext
argument_list|(
name|enum_value
operator|->
name|value_name
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|renderer
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_get_component_active
argument_list|(
name|gimage
argument_list|,
name|components
index|[
name|i
index|]
argument_list|)
condition|)
name|gtk_tree_selection_select_iter
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
name|g_type_class_unref
argument_list|(
name|enum_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_clear_components (GimpComponentEditor * editor)
name|gimp_component_editor_clear_components
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_list_store_clear
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|editor
operator|->
name|model
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_clicked (GtkCellRendererToggle * cellrenderertoggle,gchar * path_str,GdkModifierType state,GimpComponentEditor * editor)
name|gimp_component_editor_clicked
parameter_list|(
name|GtkCellRendererToggle
modifier|*
name|cellrenderertoggle
parameter_list|,
name|gchar
modifier|*
name|path_str
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|path
operator|=
name|gtk_tree_path_new_from_string
argument_list|(
name|path_str
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpChannelType
name|channel
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_CHANNEL
argument_list|,
operator|&
name|channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|cellrenderertoggle
argument_list|,
literal|"active"
argument_list|,
operator|&
name|active
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_image_set_component_visible
argument_list|(
name|gimage
argument_list|,
name|channel
argument_list|,
operator|!
name|active
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_component_editor_select (GtkTreeSelection * selection,GtkTreeModel * model,GtkTreePath * path,gboolean path_currently_selected,gpointer data)
name|gimp_component_editor_select
parameter_list|(
name|GtkTreeSelection
modifier|*
name|selection
parameter_list|,
name|GtkTreeModel
modifier|*
name|model
parameter_list|,
name|GtkTreePath
modifier|*
name|path
parameter_list|,
name|gboolean
name|path_currently_selected
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpComponentEditor
modifier|*
name|editor
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|GimpChannelType
name|channel
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|editor
operator|=
name|GIMP_COMPONENT_EDITOR
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_CHANNEL
argument_list|,
operator|&
name|channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|active
operator|=
name|gimp_image_get_component_active
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
argument_list|,
name|channel
argument_list|)
expr_stmt|;
return|return
name|active
operator|!=
name|path_currently_selected
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_component_editor_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpComponentEditor * editor)
name|gimp_component_editor_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreeViewColumn
modifier|*
name|column
decl_stmt|;
name|GtkTreePath
modifier|*
name|path
decl_stmt|;
name|editor
operator|->
name|clicked_component
operator|=
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|gtk_tree_view_get_path_at_pos
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|widget
argument_list|)
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|column
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|GimpChannelType
name|channel
decl_stmt|;
name|gboolean
name|active
decl_stmt|;
name|active
operator|=
name|gtk_tree_selection_path_is_selected
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get_iter
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
name|gtk_tree_model_get
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_CHANNEL
argument_list|,
operator|&
name|channel
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|editor
operator|->
name|clicked_component
operator|=
name|channel
expr_stmt|;
switch|switch
condition|(
name|bevent
operator|->
name|button
condition|)
block|{
case|case
literal|1
case|:
if|if
condition|(
name|column
operator|!=
name|editor
operator|->
name|eye_column
operator|&&
name|bevent
operator|->
name|type
operator|==
name|GDK_BUTTON_PRESS
condition|)
name|gimp_image_set_component_active
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
argument_list|,
name|channel
argument_list|,
operator|!
name|active
argument_list|)
expr_stmt|;
break|break;
case|case
literal|2
case|:
break|break;
case|case
literal|3
case|:
name|gimp_item_factory_popup_with_data
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|item_factory
argument_list|,
name|editor
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_component_editor_get_iter (GimpComponentEditor * editor,GimpChannelType channel,GtkTreeIter * iter)
name|gimp_component_editor_get_iter
parameter_list|(
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
block|{
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gimp_image_get_component_index
argument_list|(
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|gimage
argument_list|,
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|!=
operator|-
literal|1
condition|)
return|return
name|gtk_tree_model_iter_nth_child
argument_list|(
name|editor
operator|->
name|model
argument_list|,
name|iter
argument_list|,
name|NULL
argument_list|,
name|index
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_renderer_update (GimpPreviewRenderer * renderer,GimpComponentEditor * editor)
name|gimp_component_editor_renderer_update
parameter_list|(
name|GimpPreviewRenderer
modifier|*
name|renderer
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|index
decl_stmt|;
name|index
operator|=
name|gimp_image_get_component_index
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|renderer
operator|->
name|viewable
argument_list|)
argument_list|,
name|GIMP_PREVIEW_RENDERER_IMAGE
argument_list|(
name|renderer
argument_list|)
operator|->
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_iter_nth_child
argument_list|(
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|,
name|NULL
argument_list|,
name|index
argument_list|)
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
name|editor
operator|->
name|model
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_model_row_changed
argument_list|(
name|editor
operator|->
name|model
argument_list|,
name|path
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
name|gtk_tree_path_free
argument_list|(
name|path
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_mode_changed (GimpImage * gimage,GimpComponentEditor * editor)
name|gimp_component_editor_mode_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_component_editor_clear_components
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_component_editor_create_components
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_alpha_changed (GimpImage * gimage,GimpComponentEditor * editor)
name|gimp_component_editor_alpha_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_component_editor_clear_components
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|gimp_component_editor_create_components
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_visibility_changed (GimpImage * gimage,GimpChannelType channel,GimpComponentEditor * editor)
name|gimp_component_editor_visibility_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gimp_component_editor_get_iter
argument_list|(
name|editor
argument_list|,
name|channel
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gboolean
name|visible
decl_stmt|;
name|visible
operator|=
name|gimp_image_get_component_visible
argument_list|(
name|gimage
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|gtk_list_store_set
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|editor
operator|->
name|model
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|,
name|COLUMN_VISIBLE
argument_list|,
name|visible
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_component_editor_active_changed (GimpImage * gimage,GimpChannelType channel,GimpComponentEditor * editor)
name|gimp_component_editor_active_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpChannelType
name|channel
parameter_list|,
name|GimpComponentEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkTreeIter
name|iter
decl_stmt|;
if|if
condition|(
name|gimp_component_editor_get_iter
argument_list|(
name|editor
argument_list|,
name|channel
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
block|{
name|gboolean
name|active
decl_stmt|;
name|active
operator|=
name|gimp_image_get_component_active
argument_list|(
name|gimage
argument_list|,
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_selection_iter_is_selected
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
operator|!=
name|active
condition|)
block|{
if|if
condition|(
name|active
condition|)
name|gtk_tree_selection_select_iter
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
else|else
name|gtk_tree_selection_unselect_iter
argument_list|(
name|editor
operator|->
name|selection
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

