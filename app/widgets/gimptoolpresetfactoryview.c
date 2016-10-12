begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolpresetfactoryview.c  * Copyright (C) 2010 Alexia Death  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpresetfactoryview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolPresetFactoryView,gimp_tool_preset_factory_view,GIMP_TYPE_DATA_FACTORY_VIEW)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolPresetFactoryView
argument_list|,
argument|gimp_tool_preset_factory_view
argument_list|,
argument|GIMP_TYPE_DATA_FACTORY_VIEW
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_tool_preset_factory_view_class_init
parameter_list|(
name|GimpToolPresetFactoryViewClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_preset_factory_view_init (GimpToolPresetFactoryView * view)
name|gimp_tool_preset_factory_view_init
parameter_list|(
name|GimpToolPresetFactoryView
modifier|*
name|view
parameter_list|)
block|{ }
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_preset_factory_view_new (GimpViewType view_type,GimpDataFactory * factory,GimpContext * context,gint view_size,gint view_border_width,GimpMenuFactory * menu_factory)
name|gimp_tool_preset_factory_view_new
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
name|GimpToolPresetFactoryView
modifier|*
name|factory_view
decl_stmt|;
name|GimpEditor
modifier|*
name|editor
decl_stmt|;
name|GtkWidget
modifier|*
name|button
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
name|GIMP_TYPE_TOOL_PRESET_FACTORY_VIEW
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
literal|"<ToolPresets>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/tool-presets-popup"
argument_list|,
literal|"action-group"
argument_list|,
literal|"tool-presets"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|gimp_data_factory_view_get_duplicate_button
argument_list|(
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|factory_view
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_EDITOR
argument_list|(
name|GIMP_CONTAINER_EDITOR
argument_list|(
name|factory_view
argument_list|)
operator|->
name|view
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|editor
argument_list|,
literal|"tool-presets"
argument_list|,
literal|"tool-presets-save"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|gimp_editor_get_button_box
argument_list|(
name|editor
argument_list|)
argument_list|,
name|button
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|editor
argument_list|,
literal|"tool-presets"
argument_list|,
literal|"tool-presets-restore"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|gimp_editor_get_button_box
argument_list|(
name|editor
argument_list|)
argument_list|,
name|button
argument_list|,
literal|3
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

end_unit

