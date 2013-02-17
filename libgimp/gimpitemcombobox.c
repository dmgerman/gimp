begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpitemcombobox.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  * Copyright (C) 2006 Simon Budig<simon@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
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
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpitemcombobox.h"
end_include

begin_include
include|#
directive|include
file|"gimppixbuf.h"
end_include

begin_comment
comment|/**  * SECTION: gimpitemcombobox  * @title: GimpItemComboBox  * @short_description: Widgets providing popup menus of items.  *  * Widgets providing popup menus of items (layers, channels,  * drawables, vectors).  **/
end_comment

begin_define
DECL|macro|THUMBNAIL_SIZE
define|#
directive|define
name|THUMBNAIL_SIZE
value|24
end_define

begin_define
DECL|macro|WIDTH_REQUEST
define|#
directive|define
name|WIDTH_REQUEST
value|200
end_define

begin_define
DECL|macro|GET_PRIVATE (obj)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(g_object_get_data (G_OBJECT (obj), "gimp-item-combo-box-private"))
end_define

begin_typedef
DECL|typedef|GimpItemComboBoxPrivate
typedef|typedef
name|struct
name|_GimpItemComboBoxPrivate
name|GimpItemComboBoxPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemComboBoxPrivate
struct|struct
name|_GimpItemComboBoxPrivate
block|{
DECL|member|constraint
name|GimpItemConstraintFunc
name|constraint
decl_stmt|;
DECL|member|data
name|gpointer
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpDrawableComboBoxClass
typedef|typedef
name|struct
name|_GimpDrawableComboBoxClass
name|GimpDrawableComboBoxClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpChannelComboBoxClass
typedef|typedef
name|struct
name|_GimpChannelComboBoxClass
name|GimpChannelComboBoxClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLayerComboBoxClass
typedef|typedef
name|struct
name|_GimpLayerComboBoxClass
name|GimpLayerComboBoxClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpVectorsComboBoxClass
typedef|typedef
name|struct
name|_GimpVectorsComboBoxClass
name|GimpVectorsComboBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDrawableComboBox
struct|struct
name|_GimpDrawableComboBox
block|{
DECL|member|parent_instance
name|GimpIntComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDrawableComboBoxClass
struct|struct
name|_GimpDrawableComboBoxClass
block|{
DECL|member|parent_class
name|GimpIntComboBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpChannelComboBox
struct|struct
name|_GimpChannelComboBox
block|{
DECL|member|parent_instance
name|GimpIntComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpChannelComboBoxClass
struct|struct
name|_GimpChannelComboBoxClass
block|{
DECL|member|parent_class
name|GimpIntComboBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerComboBox
struct|struct
name|_GimpLayerComboBox
block|{
DECL|member|parent_instance
name|GimpIntComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLayerComboBoxClass
struct|struct
name|_GimpLayerComboBoxClass
block|{
DECL|member|parent_class
name|GimpIntComboBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorsComboBox
struct|struct
name|_GimpVectorsComboBox
block|{
DECL|member|parent_instance
name|GimpIntComboBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpVectorsComboBoxClass
struct|struct
name|_GimpVectorsComboBoxClass
block|{
DECL|member|parent_class
name|GimpIntComboBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_item_combo_box_new
parameter_list|(
name|GType
name|type
parameter_list|,
name|GimpItemConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_combo_box_populate
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_combo_box_model_add
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint
name|num_items
parameter_list|,
name|gint32
modifier|*
name|items
parameter_list|,
name|gint
name|tree_level
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_combo_box_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_item_combo_box_changed
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|targets
specifier|static
specifier|const
name|GtkTargetEntry
name|targets
index|[]
init|=
block|{
block|{
literal|"application/x-gimp-channel-id"
block|,
literal|0
block|}
block|,
block|{
literal|"application/x-gimp-layer-id"
block|,
literal|0
block|}
block|,
block|{
literal|"application/x-gimp-vectors-id"
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDrawableComboBox,gimp_drawable_combo_box,GIMP_TYPE_INT_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDrawableComboBox
argument_list|,
argument|gimp_drawable_combo_box
argument_list|,
argument|GIMP_TYPE_INT_COMBO_BOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_drawable_combo_box_class_init
parameter_list|(
name|GimpDrawableComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|drag_data_received
operator|=
name|gimp_item_combo_box_drag_data_received
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_drawable_combo_box_init (GimpDrawableComboBox * combo_box)
name|gimp_drawable_combo_box_init
parameter_list|(
name|GimpDrawableComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|targets
argument_list|,
literal|2
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|"gimp-item-combo-box-private"
argument_list|,
name|g_new0
argument_list|(
name|GimpItemComboBoxPrivate
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_drawable_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * drawables. If a @constraint function is specified, it is called for  * each drawable and only if the function returns %TRUE, the drawable  * is added to the combobox.  *  * You should use gimp_int_combo_box_connect() to initialize and connect  * the combo.  Use gimp_int_combo_box_set_active() to get the active  * drawable ID and gimp_int_combo_box_get_active() to retrieve the ID  * of the selected drawable.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_drawable_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_drawable_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_item_combo_box_new
argument_list|(
name|GIMP_TYPE_DRAWABLE_COMBO_BOX
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_macro
DECL|function|G_DEFINE_TYPE (GimpChannelComboBox,gimp_channel_combo_box,GIMP_TYPE_INT_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpChannelComboBox
argument_list|,
argument|gimp_channel_combo_box
argument_list|,
argument|GIMP_TYPE_INT_COMBO_BOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_channel_combo_box_class_init
parameter_list|(
name|GimpChannelComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|drag_data_received
operator|=
name|gimp_item_combo_box_drag_data_received
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_channel_combo_box_init (GimpChannelComboBox * combo_box)
name|gimp_channel_combo_box_init
parameter_list|(
name|GimpChannelComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|targets
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|"gimp-item-combo-box-private"
argument_list|,
name|g_new0
argument_list|(
name|GimpItemComboBoxPrivate
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_channel_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * channels. See gimp_drawable_combo_box_new() for more information.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_channel_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_channel_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_item_combo_box_new
argument_list|(
name|GIMP_TYPE_CHANNEL_COMBO_BOX
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_macro
DECL|function|G_DEFINE_TYPE (GimpLayerComboBox,gimp_layer_combo_box,GIMP_TYPE_INT_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpLayerComboBox
argument_list|,
argument|gimp_layer_combo_box
argument_list|,
argument|GIMP_TYPE_INT_COMBO_BOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_layer_combo_box_class_init
parameter_list|(
name|GimpLayerComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|drag_data_received
operator|=
name|gimp_item_combo_box_drag_data_received
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_layer_combo_box_init (GimpLayerComboBox * combo_box)
name|gimp_layer_combo_box_init
parameter_list|(
name|GimpLayerComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|targets
operator|+
literal|1
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|"gimp-item-combo-box-private"
argument_list|,
name|g_new0
argument_list|(
name|GimpItemComboBoxPrivate
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_layer_combo_box_new:  * @constraint: a #GimpDrawableConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * layers. See gimp_drawable_combo_box_new() for more information.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.2  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_layer_combo_box_new (GimpDrawableConstraintFunc constraint,gpointer data)
name|gimp_layer_combo_box_new
parameter_list|(
name|GimpDrawableConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_item_combo_box_new
argument_list|(
name|GIMP_TYPE_LAYER_COMBO_BOX
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_macro
DECL|function|G_DEFINE_TYPE (GimpVectorsComboBox,gimp_vectors_combo_box,GIMP_TYPE_INT_COMBO_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpVectorsComboBox
argument_list|,
argument|gimp_vectors_combo_box
argument_list|,
argument|GIMP_TYPE_INT_COMBO_BOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_vectors_combo_box_class_init
parameter_list|(
name|GimpVectorsComboBoxClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|drag_data_received
operator|=
name|gimp_item_combo_box_drag_data_received
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vectors_combo_box_init (GimpVectorsComboBox * combo_box)
name|gimp_vectors_combo_box_init
parameter_list|(
name|GimpVectorsComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gtk_drag_dest_set
argument_list|(
name|GTK_WIDGET
argument_list|(
name|combo_box
argument_list|)
argument_list|,
name|GTK_DEST_DEFAULT_HIGHLIGHT
operator||
name|GTK_DEST_DEFAULT_MOTION
operator||
name|GTK_DEST_DEFAULT_DROP
argument_list|,
name|targets
operator|+
literal|2
argument_list|,
literal|1
argument_list|,
name|GDK_ACTION_COPY
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|combo_box
argument_list|)
argument_list|,
literal|"gimp-item-combo-box-private"
argument_list|,
name|g_new0
argument_list|(
name|GimpItemComboBoxPrivate
argument_list|,
literal|1
argument_list|)
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_vectors_combo_box_new:  * @constraint: a #GimpVectorsConstraintFunc or %NULL  * @data:       a pointer that is passed to @constraint  *  * Creates a new #GimpIntComboBox filled with all currently opened  * vectors objects. If a @constraint function is specified, it is called for  * each vectors object and only if the function returns %TRUE, the vectors  * object is added to the combobox.  *  * You should use gimp_int_combo_box_connect() to initialize and connect  * the combo.  Use gimp_int_combo_box_set_active() to set the active  * vectors ID and gimp_int_combo_box_get_active() to retrieve the ID  * of the selected vectors object.  *  * Return value: a new #GimpIntComboBox.  *  * Since: GIMP 2.4  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_vectors_combo_box_new (GimpVectorsConstraintFunc constraint,gpointer data)
name|gimp_vectors_combo_box_new
parameter_list|(
name|GimpVectorsConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
return|return
name|gimp_item_combo_box_new
argument_list|(
name|GIMP_TYPE_VECTORS_COMBO_BOX
argument_list|,
name|constraint
argument_list|,
name|data
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_item_combo_box_new (GType type,GimpItemConstraintFunc constraint,gpointer data)
name|gimp_item_combo_box_new
parameter_list|(
name|GType
name|type
parameter_list|,
name|GimpItemConstraintFunc
name|constraint
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpIntComboBox
modifier|*
name|combo_box
decl_stmt|;
name|GimpItemComboBoxPrivate
modifier|*
name|private
decl_stmt|;
name|combo_box
operator|=
name|g_object_new
argument_list|(
name|type
argument_list|,
literal|"width-request"
argument_list|,
name|WIDTH_REQUEST
argument_list|,
literal|"ellipsize"
argument_list|,
name|PANGO_ELLIPSIZE_MIDDLE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|private
operator|->
name|constraint
operator|=
name|constraint
expr_stmt|;
name|private
operator|->
name|data
operator|=
name|data
expr_stmt|;
name|gimp_item_combo_box_populate
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_item_combo_box_changed
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|combo_box
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_combo_box_populate (GimpIntComboBox * combo_box)
name|gimp_item_combo_box_populate
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint32
modifier|*
name|images
decl_stmt|;
name|gint
name|num_images
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|images
operator|=
name|gimp_image_list
argument_list|(
operator|&
name|num_images
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
name|num_images
condition|;
name|i
operator|++
control|)
block|{
name|gint32
modifier|*
name|items
decl_stmt|;
name|gint
name|num_items
decl_stmt|;
if|if
condition|(
name|GIMP_IS_DRAWABLE_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
operator|||
name|GIMP_IS_LAYER_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
condition|)
block|{
name|items
operator|=
name|gimp_image_get_layers
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_items
argument_list|)
expr_stmt|;
name|gimp_item_combo_box_model_add
argument_list|(
name|combo_box
argument_list|,
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_items
argument_list|,
name|items
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|items
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_DRAWABLE_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
operator|||
name|GIMP_IS_CHANNEL_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
condition|)
block|{
name|items
operator|=
name|gimp_image_get_channels
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_items
argument_list|)
expr_stmt|;
name|gimp_item_combo_box_model_add
argument_list|(
name|combo_box
argument_list|,
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_items
argument_list|,
name|items
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|items
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|GIMP_IS_VECTORS_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
condition|)
block|{
name|items
operator|=
name|gimp_image_get_vectors
argument_list|(
name|images
index|[
name|i
index|]
argument_list|,
operator|&
name|num_items
argument_list|)
expr_stmt|;
name|gimp_item_combo_box_model_add
argument_list|(
name|combo_box
argument_list|,
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|images
index|[
name|i
index|]
argument_list|,
name|num_items
argument_list|,
name|items
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|items
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|images
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_tree_model_get_iter_first
argument_list|(
name|model
argument_list|,
operator|&
name|iter
argument_list|)
condition|)
name|gtk_combo_box_set_active_iter
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|,
operator|&
name|iter
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_combo_box_model_add (GimpIntComboBox * combo_box,GtkListStore * store,gint32 image,gint num_items,gint32 * items,gint tree_level)
name|gimp_item_combo_box_model_add
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|,
name|GtkListStore
modifier|*
name|store
parameter_list|,
name|gint32
name|image
parameter_list|,
name|gint
name|num_items
parameter_list|,
name|gint32
modifier|*
name|items
parameter_list|,
name|gint
name|tree_level
parameter_list|)
block|{
name|GimpItemComboBoxPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|combo_box
argument_list|)
decl_stmt|;
name|GtkTreeIter
name|iter
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gchar
modifier|*
name|indent
decl_stmt|;
if|if
condition|(
name|tree_level
operator|>
literal|0
condition|)
block|{
name|indent
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|tree_level
operator|+
literal|2
argument_list|)
expr_stmt|;
name|memset
argument_list|(
name|indent
argument_list|,
literal|'-'
argument_list|,
name|tree_level
argument_list|)
expr_stmt|;
name|indent
index|[
name|tree_level
index|]
operator|=
literal|' '
expr_stmt|;
name|indent
index|[
name|tree_level
operator|+
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
else|else
block|{
name|indent
operator|=
name|g_strdup
argument_list|(
literal|""
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_items
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|private
operator|->
name|constraint
operator|||
call|(
modifier|*
name|private
operator|->
name|constraint
call|)
argument_list|(
name|image
argument_list|,
name|items
index|[
name|i
index|]
argument_list|,
name|private
operator|->
name|data
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|image_name
init|=
name|gimp_image_get_name
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|item_name
init|=
name|gimp_item_get_name
argument_list|(
name|items
index|[
name|i
index|]
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|label
decl_stmt|;
name|GdkPixbuf
modifier|*
name|thumb
decl_stmt|;
name|label
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s%s-%d / %s-%d"
argument_list|,
name|indent
argument_list|,
name|image_name
argument_list|,
name|image
argument_list|,
name|item_name
argument_list|,
name|items
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|item_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|image_name
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_VECTORS_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
condition|)
name|thumb
operator|=
name|NULL
expr_stmt|;
else|else
name|thumb
operator|=
name|gimp_drawable_get_thumbnail
argument_list|(
name|items
index|[
name|i
index|]
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|THUMBNAIL_SIZE
argument_list|,
name|GIMP_PIXBUF_SMALL_CHECKS
argument_list|)
expr_stmt|;
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
name|GIMP_INT_STORE_VALUE
argument_list|,
name|items
index|[
name|i
index|]
argument_list|,
name|GIMP_INT_STORE_LABEL
argument_list|,
name|label
argument_list|,
name|GIMP_INT_STORE_PIXBUF
argument_list|,
name|thumb
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|thumb
condition|)
name|g_object_unref
argument_list|(
name|thumb
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|label
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_item_is_group
argument_list|(
name|items
index|[
name|i
index|]
argument_list|)
condition|)
block|{
name|gint32
modifier|*
name|children
decl_stmt|;
name|gint
name|n_children
decl_stmt|;
name|children
operator|=
name|gimp_item_get_children
argument_list|(
name|items
index|[
name|i
index|]
argument_list|,
operator|&
name|n_children
argument_list|)
expr_stmt|;
name|gimp_item_combo_box_model_add
argument_list|(
name|combo_box
argument_list|,
name|store
argument_list|,
name|image
argument_list|,
name|n_children
argument_list|,
name|children
argument_list|,
name|tree_level
operator|+
literal|1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|g_free
argument_list|(
name|indent
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_combo_box_drag_data_received (GtkWidget * widget,GdkDragContext * context,gint x,gint y,GtkSelectionData * selection,guint info,guint time)
name|gimp_item_combo_box_drag_data_received
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkDragContext
modifier|*
name|context
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GtkSelectionData
modifier|*
name|selection
parameter_list|,
name|guint
name|info
parameter_list|,
name|guint
name|time
parameter_list|)
block|{
name|gint
name|length
init|=
name|gtk_selection_data_get_length
argument_list|(
name|selection
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
if|if
condition|(
name|gtk_selection_data_get_format
argument_list|(
name|selection
argument_list|)
operator|!=
literal|8
operator|||
name|length
operator|<
literal|1
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s: received invalid item ID data"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
name|str
operator|=
name|g_strndup
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|gtk_selection_data_get_data
argument_list|(
name|selection
argument_list|)
argument_list|,
name|length
argument_list|)
expr_stmt|;
if|if
condition|(
name|g_utf8_validate
argument_list|(
name|str
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gint
name|pid
decl_stmt|;
name|gint
name|ID
decl_stmt|;
if|if
condition|(
name|sscanf
argument_list|(
name|str
argument_list|,
literal|"%i:%i"
argument_list|,
operator|&
name|pid
argument_list|,
operator|&
name|ID
argument_list|)
operator|==
literal|2
operator|&&
name|pid
operator|==
name|gimp_getpid
argument_list|()
condition|)
block|{
name|gimp_int_combo_box_set_active
argument_list|(
name|GIMP_INT_COMBO_BOX
argument_list|(
name|widget
argument_list|)
argument_list|,
name|ID
argument_list|)
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_item_combo_box_remove_items (GtkTreeModel * model,GtkTreePath * path,GtkTreeIter * iter,gpointer data)
name|gimp_item_combo_box_remove_items
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
name|gint
name|item_ID
decl_stmt|;
name|GList
modifier|*
modifier|*
name|remove
init|=
name|data
decl_stmt|;
name|gtk_tree_model_get
argument_list|(
name|model
argument_list|,
name|iter
argument_list|,
name|GIMP_INT_STORE_VALUE
argument_list|,
operator|&
name|item_ID
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|item_ID
operator|>
literal|0
condition|)
operator|*
name|remove
operator|=
name|g_list_prepend
argument_list|(
operator|*
name|remove
argument_list|,
name|g_memdup
argument_list|(
name|iter
argument_list|,
sizeof|sizeof
argument_list|(
name|GtkTreeIter
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_item_combo_box_changed (GimpIntComboBox * combo_box)
name|gimp_item_combo_box_changed
parameter_list|(
name|GimpIntComboBox
modifier|*
name|combo_box
parameter_list|)
block|{
name|gint
name|item_ID
decl_stmt|;
if|if
condition|(
name|gimp_int_combo_box_get_active
argument_list|(
name|combo_box
argument_list|,
operator|&
name|item_ID
argument_list|)
condition|)
block|{
if|if
condition|(
name|item_ID
operator|>
literal|0
operator|&&
operator|!
name|gimp_item_is_valid
argument_list|(
name|item_ID
argument_list|)
condition|)
block|{
name|GtkTreeModel
modifier|*
name|model
decl_stmt|;
name|GList
modifier|*
name|remove
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|model
operator|=
name|gtk_combo_box_get_model
argument_list|(
name|GTK_COMBO_BOX
argument_list|(
name|combo_box
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_stop_emission_by_name
argument_list|(
name|combo_box
argument_list|,
literal|"changed"
argument_list|)
expr_stmt|;
name|gtk_tree_model_foreach
argument_list|(
name|model
argument_list|,
name|gimp_item_combo_box_remove_items
argument_list|,
operator|&
name|remove
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|remove
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
name|gtk_list_store_remove
argument_list|(
name|GTK_LIST_STORE
argument_list|(
name|model
argument_list|)
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free_full
argument_list|(
name|remove
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_free
argument_list|)
expr_stmt|;
name|gimp_item_combo_box_populate
argument_list|(
name|combo_box
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

