begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplayerlistview.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimplayerlistview.h"
end_include

begin_include
include|#
directive|include
file|"gimplistitem.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_class_init
parameter_list|(
name|GimpLayerListViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_init
parameter_list|(
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_anchor_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_paint_mode_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_preserve_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_opacity_scale_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_layer_signal_handler
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_layer_list_view_update_options
parameter_list|(
name|GimpLayerListView
modifier|*
name|view
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDrawableListViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_layer_list_view_get_type (void)
name|gimp_layer_list_view_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
name|GtkTypeInfo
name|view_info
init|=
block|{
literal|"GimpLayerListView"
block|,
sizeof|sizeof
argument_list|(
name|GimpLayerListView
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpLayerListViewClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_layer_list_view_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_layer_list_view_init
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
name|view_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_DRAWABLE_LIST_VIEW
argument_list|,
operator|&
name|view_info
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_class_init (GimpLayerListViewClass * klass)
name|gimp_layer_list_view_class_init
parameter_list|(
name|GimpLayerListViewClass
modifier|*
name|klass
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
name|GimpContainerViewClass
modifier|*
name|container_view_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|widget_class
operator|=
operator|(
name|GtkWidgetClass
operator|*
operator|)
name|klass
expr_stmt|;
name|container_view_class
operator|=
operator|(
name|GimpContainerViewClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_layer_list_view_destroy
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_layer_list_view_style_set
expr_stmt|;
name|container_view_class
operator|->
name|set_container
operator|=
name|gimp_layer_list_view_set_container
expr_stmt|;
name|container_view_class
operator|->
name|select_item
operator|=
name|gimp_layer_list_view_select_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_init (GimpLayerListView * view)
name|gimp_layer_list_view_init
parameter_list|(
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|view
operator|->
name|options_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|options_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|options_box
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
operator|->
name|options_box
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|options_box
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
comment|/*  Paint mode menu  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Mode:"
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
name|view
operator|->
name|paint_mode_menu
operator|=
name|gimp_paint_mode_menu_new
argument_list|(
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_paint_mode_menu_callback
argument_list|)
argument_list|,
name|view
argument_list|,
name|FALSE
argument_list|,
name|NORMAL_MODE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|view
operator|->
name|paint_mode_menu
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
name|view
operator|->
name|paint_mode_menu
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|view
operator|->
name|paint_mode_menu
argument_list|,
name|NULL
argument_list|,
literal|"#paint_mode_menu"
argument_list|)
expr_stmt|;
comment|/*  Preserve transparency toggle  */
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|abox
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
name|abox
argument_list|)
expr_stmt|;
name|view
operator|->
name|preserve_trans_toggle
operator|=
name|gtk_toggle_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Keep Trans."
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|view
operator|->
name|preserve_trans_toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_preserve_button_toggled
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|,
name|_
argument_list|(
literal|"Keep Transparency"
argument_list|)
argument_list|,
literal|"#keep_trans_button"
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|options_box
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
comment|/*  Opacity scale  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Opacity:"
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
name|view
operator|->
name|opacity_adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|opacity_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_opacity_scale_changed
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|view
operator|->
name|opacity_adjustment
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_RIGHT
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|slider
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
name|slider
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|slider
argument_list|,
name|NULL
argument_list|,
literal|"#opacity_scale"
argument_list|)
expr_stmt|;
comment|/*  Anchor button  */
name|view
operator|->
name|anchor_button
operator|=
name|gimp_container_view_add_button
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|GIMP_STOCK_ANCHOR
argument_list|,
name|_
argument_list|(
literal|"Anchor"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_anchor_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|button_box
argument_list|)
argument_list|,
name|view
operator|->
name|anchor_button
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|gimp_container_view_enable_dnd
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|GTK_BUTTON
argument_list|(
name|view
operator|->
name|anchor_button
argument_list|)
argument_list|,
name|GIMP_TYPE_LAYER
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|options_box
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|anchor_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|view
operator|->
name|mode_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|opacity_changed_handler_id
operator|=
literal|0
expr_stmt|;
name|view
operator|->
name|preserve_trans_changed_handler_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_destroy (GtkObject * object)
name|gimp_layer_list_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpLayerListView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_LAYER_LIST_VIEW
argument_list|(
name|object
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
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_layer_list_view_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpLayerListView
modifier|*
name|layer_view
decl_stmt|;
name|gint
name|content_spacing
decl_stmt|;
name|gint
name|button_spacing
decl_stmt|;
name|layer_view
operator|=
name|GIMP_LAYER_LIST_VIEW
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"content_spacing"
argument_list|,
operator|&
name|content_spacing
argument_list|,
literal|"button_spacing"
argument_list|,
operator|&
name|button_spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|layer_view
operator|->
name|options_box
argument_list|)
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  GimpContainerView methods  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_set_container (GimpContainerView * view,GimpContainer * container)
name|gimp_layer_list_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
block|{
name|GimpLayerListView
modifier|*
name|layer_view
decl_stmt|;
name|layer_view
operator|=
name|GIMP_LAYER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|layer_view
operator|->
name|mode_changed_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|layer_view
operator|->
name|opacity_changed_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|layer_view
operator|->
name|preserve_trans_changed_handler_id
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_container
condition|)
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_container
argument_list|(
name|view
argument_list|,
name|container
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|container
condition|)
block|{
name|layer_view
operator|->
name|mode_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
literal|"mode_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_layer_signal_handler
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|layer_view
operator|->
name|opacity_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
literal|"opacity_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_layer_signal_handler
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|layer_view
operator|->
name|preserve_trans_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|view
operator|->
name|container
argument_list|,
literal|"preserve_trans_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_layer_list_view_layer_signal_handler
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_select_item (GimpContainerView * view,GimpViewable * item,gpointer insert_data)
name|gimp_layer_list_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpLayerListView
modifier|*
name|list_view
decl_stmt|;
name|gboolean
name|options_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|anchor_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|raise_sensitive
init|=
name|FALSE
decl_stmt|;
name|list_view
operator|=
name|GIMP_LAYER_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_VIEW_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
argument_list|(
name|view
argument_list|,
name|item
argument_list|,
name|insert_data
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
condition|)
block|{
name|gimp_layer_list_view_update_options
argument_list|(
name|list_view
argument_list|,
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|options_sensitive
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|gimp_layer_is_floating_sel
argument_list|(
name|GIMP_LAYER
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
block|{
name|anchor_sensitive
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|drawable_view
operator|->
name|lower_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|drawable_view
operator|->
name|duplicate_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|drawable_view
operator|->
name|edit_button
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gimp_drawable_has_alpha
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|item
argument_list|)
argument_list|)
operator|&&
name|gimp_container_get_child_index
argument_list|(
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|)
condition|)
block|{
name|raise_sensitive
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|options_box
argument_list|,
name|options_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|drawable_view
operator|->
name|raise_button
argument_list|,
name|raise_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|list_view
operator|->
name|anchor_button
argument_list|,
name|anchor_sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  "Anchor" functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_anchor_clicked (GtkWidget * widget,GimpLayerListView * view)
name|gimp_layer_list_view_anchor_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
condition|)
name|g_print
argument_list|(
literal|"anchor \"%s\"\n"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|drawable
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  Paint Mode, Opacity and Preserve trans. callbacks  */
end_comment

begin_define
DECL|macro|BLOCK ()
define|#
directive|define
name|BLOCK
parameter_list|()
define|\
value|g_signal_handlers_block_by_func (G_OBJECT (layer), \ 	gimp_layer_list_view_layer_signal_handler, view)
end_define

begin_define
DECL|macro|UNBLOCK ()
define|#
directive|define
name|UNBLOCK
parameter_list|()
define|\
value|g_signal_handlers_unblock_by_func (G_OBJECT (layer), \ 	gimp_layer_list_view_layer_signal_handler, view)
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_paint_mode_menu_callback (GtkWidget * widget,GimpLayerListView * view)
name|gimp_layer_list_view_paint_mode_menu_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|LayerModeEffects
name|mode
decl_stmt|;
name|mode
operator|=
operator|(
name|LayerModeEffects
operator|)
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"user_data"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_mode
argument_list|(
name|layer
argument_list|)
operator|!=
name|mode
condition|)
block|{
name|BLOCK
argument_list|()
expr_stmt|;
name|gimp_layer_set_mode
argument_list|(
name|layer
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|UNBLOCK
argument_list|()
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_preserve_button_toggled (GtkWidget * widget,GimpLayerListView * view)
name|gimp_layer_list_view_preserve_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|gboolean
name|preserve_trans
decl_stmt|;
name|preserve_trans
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_preserve_trans
argument_list|(
name|layer
argument_list|)
operator|!=
name|preserve_trans
condition|)
block|{
name|BLOCK
argument_list|()
expr_stmt|;
name|gimp_layer_set_preserve_trans
argument_list|(
name|layer
argument_list|,
name|preserve_trans
argument_list|)
expr_stmt|;
name|UNBLOCK
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_opacity_scale_changed (GtkAdjustment * adjustment,GimpLayerListView * view)
name|gimp_layer_list_view_opacity_scale_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|GimpLayer
modifier|*
name|layer
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|layer
operator|=
operator|(
name|GimpLayer
operator|*
operator|)
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
condition|)
block|{
name|gdouble
name|opacity
decl_stmt|;
name|opacity
operator|=
name|adjustment
operator|->
name|value
operator|/
literal|100.0
expr_stmt|;
if|if
condition|(
name|gimp_layer_get_opacity
argument_list|(
name|layer
argument_list|)
operator|!=
name|opacity
condition|)
block|{
name|BLOCK
argument_list|()
expr_stmt|;
name|gimp_layer_set_opacity
argument_list|(
name|layer
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|UNBLOCK
argument_list|()
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
block|}
end_function

begin_undef
undef|#
directive|undef
name|BLOCK
end_undef

begin_undef
undef|#
directive|undef
name|UNBLOCK
end_undef

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_layer_signal_handler (GimpLayer * layer,GimpLayerListView * view)
name|gimp_layer_list_view_layer_signal_handler
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpLayerListView
modifier|*
name|view
parameter_list|)
block|{
name|GimpDrawableListView
modifier|*
name|drawable_view
decl_stmt|;
name|drawable_view
operator|=
name|GIMP_DRAWABLE_LIST_VIEW
argument_list|(
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable_view
operator|->
name|get_drawable_func
argument_list|(
name|drawable_view
operator|->
name|gimage
argument_list|)
operator|==
operator|(
name|GimpDrawable
operator|*
operator|)
name|layer
condition|)
block|{
name|gimp_layer_list_view_update_options
argument_list|(
name|view
argument_list|,
name|layer
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|BLOCK (object,function)
define|#
directive|define
name|BLOCK
parameter_list|(
name|object
parameter_list|,
name|function
parameter_list|)
define|\
value|g_signal_handlers_block_by_func (G_OBJECT (object), \ 	                                 (function), view)
end_define

begin_define
DECL|macro|UNBLOCK (object,function)
define|#
directive|define
name|UNBLOCK
parameter_list|(
name|object
parameter_list|,
name|function
parameter_list|)
define|\
value|g_signal_handlers_unblock_by_func (G_OBJECT (object), \ 	                                   (function), view)
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_layer_list_view_update_options (GimpLayerListView * view,GimpLayer * layer)
name|gimp_layer_list_view_update_options
parameter_list|(
name|GimpLayerListView
modifier|*
name|view
parameter_list|,
name|GimpLayer
modifier|*
name|layer
parameter_list|)
block|{
name|gimp_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|view
operator|->
name|paint_mode_menu
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|layer
operator|->
name|mode
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer
operator|->
name|preserve_trans
operator|!=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|)
operator|->
name|active
condition|)
block|{
name|BLOCK
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|,
name|gimp_layer_list_view_preserve_button_toggled
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|)
argument_list|,
name|layer
operator|->
name|preserve_trans
argument_list|)
expr_stmt|;
name|UNBLOCK
argument_list|(
name|view
operator|->
name|preserve_trans_toggle
argument_list|,
name|gimp_layer_list_view_preserve_button_toggled
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|gdouble
operator|)
name|layer
operator|->
name|opacity
operator|/
literal|2.55
operator|!=
name|view
operator|->
name|opacity_adjustment
operator|->
name|value
condition|)
block|{
name|BLOCK
argument_list|(
name|view
operator|->
name|opacity_adjustment
argument_list|,
name|gimp_layer_list_view_opacity_scale_changed
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|view
operator|->
name|opacity_adjustment
argument_list|,
name|layer
operator|->
name|opacity
operator|/
literal|2.55
argument_list|)
expr_stmt|;
name|UNBLOCK
argument_list|(
name|view
operator|->
name|opacity_adjustment
argument_list|,
name|gimp_layer_list_view_opacity_scale_changed
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_undef
undef|#
directive|undef
name|BLOCK
end_undef

begin_undef
undef|#
directive|undef
name|UNBLOCK
end_undef

end_unit

