begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushfactoryview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushfactoryview.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_class_init
parameter_list|(
name|GimpBrushFactoryViewClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_init
parameter_list|(
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_destroy
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
name|gimp_brush_factory_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_spacing_changed
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_spacing_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataFactoryViewClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_brush_factory_view_get_type (void)
name|gimp_brush_factory_view_get_type
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
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBrushFactoryViewClass
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
name|gimp_brush_factory_view_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpBrushFactoryView
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_brush_factory_view_init
block|,       }
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|,
literal|"GimpBrushFactoryView"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
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
DECL|function|gimp_brush_factory_view_class_init (GimpBrushFactoryViewClass * klass)
name|gimp_brush_factory_view_class_init
parameter_list|(
name|GimpBrushFactoryViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpContainerEditorClass
modifier|*
name|editor_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|editor_class
operator|=
name|GIMP_CONTAINER_EDITOR_CLASS
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
name|object_class
operator|->
name|destroy
operator|=
name|gimp_brush_factory_view_destroy
expr_stmt|;
name|editor_class
operator|->
name|select_item
operator|=
name|gimp_brush_factory_view_select_item
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_factory_view_init (GimpBrushFactoryView * view)
name|gimp_brush_factory_view_init
parameter_list|(
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|table
decl_stmt|;
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
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|view
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
name|view
operator|->
name|spacing_adjustment
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1000.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|view
operator|->
name|spacing_scale
operator|=
name|gtk_hscale_new
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|view
operator|->
name|spacing_scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|view
operator|->
name|spacing_scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
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
literal|"Spacing:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|view
operator|->
name|spacing_scale
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_factory_view_spacing_update
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|view
operator|->
name|spacing_changed_handler_id
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_factory_view_destroy (GtkObject * object)
name|gimp_brush_factory_view_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushFactoryView
modifier|*
name|view
decl_stmt|;
name|view
operator|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|view
operator|->
name|spacing_changed_handler_id
condition|)
block|{
name|gimp_container_remove_handler
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
name|container
argument_list|,
name|view
operator|->
name|spacing_changed_handler_id
argument_list|)
expr_stmt|;
name|view
operator|->
name|spacing_changed_handler_id
operator|=
literal|0
expr_stmt|;
block|}
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
name|GtkWidget
modifier|*
DECL|function|gimp_brush_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gboolean change_brush_spacing,gint preview_size,gint min_items_x,gint min_items_y,GimpContainerContextFunc context_func)
name|gimp_brush_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpDataEditFunc
name|edit_func
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|change_brush_spacing
parameter_list|,
name|gint
name|preview_size
parameter_list|,
name|gint
name|min_items_x
parameter_list|,
name|gint
name|min_items_y
parameter_list|,
name|GimpContainerContextFunc
name|context_func
parameter_list|)
block|{
name|GimpBrushFactoryView
modifier|*
name|factory_view
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DATA_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|preview_size
operator|>
literal|0
operator|&&
name|preview_size
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_x
operator|>
literal|0
operator|&&
name|min_items_x
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|min_items_y
operator|>
literal|0
operator|&&
name|min_items_y
operator|<=
literal|64
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory_view
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH_FACTORY_VIEW
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|change_brush_spacing
operator|=
name|change_brush_spacing
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_data_factory_view_construct
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|,
name|view_type
argument_list|,
name|factory
argument_list|,
name|edit_func
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|min_items_x
argument_list|,
name|min_items_y
argument_list|,
name|context_func
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|factory_view
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|factory_view
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|spacing_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|editor
operator|->
name|view
operator|->
name|container
argument_list|,
literal|"spacing_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_factory_view_spacing_changed
argument_list|)
argument_list|,
name|factory_view
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|factory_view
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_factory_view_select_item (GimpContainerEditor * editor,GimpViewable * viewable)
name|gimp_brush_factory_view_select_item
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
block|{
name|GimpBrushFactoryView
modifier|*
name|view
decl_stmt|;
name|gboolean
name|edit_sensitive
init|=
name|FALSE
decl_stmt|;
name|gboolean
name|spacing_sensitive
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
condition|)
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|select_item
argument_list|(
name|editor
argument_list|,
name|viewable
argument_list|)
expr_stmt|;
name|view
operator|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
name|container
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|viewable
argument_list|)
argument_list|)
condition|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
name|edit_sensitive
operator|=
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|spacing_sensitive
operator|=
name|TRUE
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_update
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|,
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_update
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|view
argument_list|)
operator|->
name|edit_button
argument_list|,
name|edit_sensitive
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|view
operator|->
name|spacing_scale
argument_list|,
name|spacing_sensitive
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_factory_view_spacing_changed (GimpBrush * brush,GimpBrushFactoryView * view)
name|gimp_brush_factory_view_spacing_changed
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
block|{
if|if
condition|(
name|brush
operator|==
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
name|context
operator|->
name|brush
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_update
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|,
name|gimp_brush_get_spacing
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_update
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
DECL|function|gimp_brush_factory_view_spacing_update (GtkAdjustment * adjustment,GimpBrushFactoryView * view)
name|gimp_brush_factory_view_spacing_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushFactoryView
modifier|*
name|view
parameter_list|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
operator|->
name|view
operator|->
name|context
operator|->
name|brush
expr_stmt|;
if|if
condition|(
name|brush
operator|&&
name|view
operator|->
name|change_brush_spacing
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gimp_brush_set_spacing
argument_list|(
name|brush
argument_list|,
name|adjustment
operator|->
name|value
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|gimp_brush_factory_view_spacing_changed
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

