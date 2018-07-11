begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrushfactoryview.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"gimpbrushfactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpspinscale.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_brush_factory_view_dispose
parameter_list|(
name|GObject
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrushFactoryView,gimp_brush_factory_view,GIMP_TYPE_DATA_FACTORY_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrushFactoryView
argument_list|,
argument|gimp_brush_factory_view
argument_list|,
argument|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brush_factory_view_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_brush_factory_view_class_init
parameter_list|(
name|GimpBrushFactoryViewClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpContainerEditorClass
modifier|*
name|editor_class
init|=
name|GIMP_CONTAINER_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_brush_factory_view_dispose
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
name|view
operator|->
name|spacing_adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|5000.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|view
operator|->
name|spacing_scale
operator|=
name|gimp_spin_scale_new
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|,
name|_
argument_list|(
literal|"Spacing"
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_scale_limits
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|view
operator|->
name|spacing_scale
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|200.0
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|view
operator|->
name|spacing_scale
argument_list|,
name|_
argument_list|(
literal|"Percentage of width of brush"
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|view
operator|->
name|spacing_adjustment
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_factory_view_spacing_update
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_factory_view_dispose (GObject * object)
name|gimp_brush_factory_view_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrushFactoryView
modifier|*
name|view
init|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|view
operator|->
name|spacing_changed_handler_id
condition|)
block|{
name|GimpDataFactory
modifier|*
name|factory
decl_stmt|;
name|GimpContainer
modifier|*
name|container
decl_stmt|;
name|factory
operator|=
name|gimp_data_factory_view_get_data_factory
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|container
operator|=
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
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
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_brush_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpContext * context,gboolean change_brush_spacing,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory)
name|gimp_brush_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|change_brush_spacing
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
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
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|<=
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_border_width
operator|>=
literal|0
operator|&&
name|view_border_width
operator|<=
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|menu_factory
operator|==
name|NULL
operator|||
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
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
literal|"view-type"
argument_list|,
name|view_type
argument_list|,
literal|"data-factory"
argument_list|,
name|factory
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"view-size"
argument_list|,
name|view_size
argument_list|,
literal|"view-border-width"
argument_list|,
name|view_border_width
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<Brushes>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/brushes-popup"
argument_list|,
literal|"action-group"
argument_list|,
literal|"brushes"
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
name|editor
operator|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|factory_view
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|factory_view
operator|->
name|spacing_scale
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
name|factory_view
operator|->
name|spacing_scale
argument_list|)
expr_stmt|;
name|factory_view
operator|->
name|spacing_changed_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp_data_factory_get_container
argument_list|(
name|factory
argument_list|)
argument_list|,
literal|"spacing-changed"
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
init|=
name|GIMP_BRUSH_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpContainer
modifier|*
name|container
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
name|container
operator|=
name|gimp_container_view_get_container
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|viewable
operator|&&
name|gimp_container_have
argument_list|(
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
init|=
name|GIMP_BRUSH
argument_list|(
name|viewable
argument_list|)
decl_stmt|;
name|spacing_sensitive
operator|=
name|TRUE
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|view
operator|->
name|spacing_adjustment
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
name|view
operator|->
name|spacing_adjustment
argument_list|,
name|gimp_brush_factory_view_spacing_update
argument_list|,
name|view
argument_list|)
expr_stmt|;
block|}
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|==
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|view
operator|->
name|spacing_adjustment
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
name|view
operator|->
name|spacing_adjustment
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
name|GimpContainerEditor
modifier|*
name|editor
init|=
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|view
argument_list|)
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|context
operator|=
name|gimp_container_view_get_context
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
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
name|brush
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
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|brush
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

