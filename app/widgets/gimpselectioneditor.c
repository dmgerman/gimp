begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpcolor/gimpcolor.h"
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
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-color.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpselection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_comment
comment|/* FIXME: #include "tools/tools-types.h" */
end_comment

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpregionselectoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectioneditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_constructed
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
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_selection_view_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_selection_editor_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSelectionEditor
argument_list|,
argument|gimp_selection_editor
argument_list|,
argument|GIMP_TYPE_IMAGE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_selection_editor_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_selection_editor_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_class_init (GimpSelectionEditorClass * klass)
name|gimp_selection_editor_class_init
parameter_list|(
name|GimpSelectionEditorClass
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
name|GimpImageEditorClass
modifier|*
name|image_editor_class
init|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_selection_editor_constructed
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_selection_editor_set_image
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_docked_iface_init (GimpDockedInterface * iface)
name|gimp_selection_editor_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_context
operator|=
name|gimp_selection_editor_set_context
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_init (GimpSelectionEditor * editor)
name|gimp_selection_editor_init
parameter_list|(
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|editor
operator|->
name|view
operator|=
name|gimp_view_new_by_types
argument_list|(
name|NULL
argument_list|,
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_SELECTION
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_background
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|GIMP_STOCK_TEXTURE
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|,
name|GIMP_VIEW_SIZE_HUGE
argument_list|)
expr_stmt|;
name|gimp_view_set_expand
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|view
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_view_button_press
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_dnd_color_dest_add
argument_list|(
name|editor
operator|->
name|view
argument_list|,
name|gimp_selection_editor_drop_color
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_constructed (GObject * object)
name|gimp_selection_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSelectionEditor
modifier|*
name|editor
init|=
name|GIMP_SELECTION_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|editor
operator|->
name|all_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"select"
argument_list|,
literal|"select-all"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|none_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"select"
argument_list|,
literal|"select-none"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|invert_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"select"
argument_list|,
literal|"select-invert"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|save_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"select"
argument_list|,
literal|"select-save"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|path_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"vectors"
argument_list|,
literal|"vectors-selection-to-vectors"
argument_list|,
literal|"vectors-selection-to-vectors-advanced"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|stroke_button
operator|=
name|gimp_editor_add_action_button
argument_list|(
name|GIMP_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"select"
argument_list|,
literal|"select-stroke"
argument_list|,
literal|"select-stroke-last-values"
argument_list|,
name|GDK_SHIFT_MASK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_set_image (GimpImageEditor * image_editor,GimpImage * image)
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpSelectionEditor
modifier|*
name|editor
init|=
name|GIMP_SELECTION_EDITOR
argument_list|(
name|image_editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|image
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|gimp_selection_editor_mask_changed
argument_list|,
name|editor
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
name|image_editor
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"mask-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_selection_editor_mask_changed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_set_context (GimpDocked * docked,GimpContext * context)
name|gimp_selection_editor_set_context
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpSelectionEditor
modifier|*
name|editor
init|=
name|GIMP_SELECTION_EDITOR
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_context
argument_list|(
name|docked
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_view_renderer_set_context
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|renderer
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_selection_editor_new (GimpMenuFactory * menu_factory)
name|gimp_selection_editor_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
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
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SELECTION_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<Selection>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/selection-popup"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_selection_view_button_press (GtkWidget * widget,GdkEventButton * bevent,GimpSelectionEditor * editor)
name|gimp_selection_view_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|GimpViewRenderer
modifier|*
name|renderer
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|sel_options
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GimpChannelOps
name|operation
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
if|if
condition|(
operator|!
name|image_editor
operator|->
name|image
condition|)
return|return
name|TRUE
return|;
name|renderer
operator|=
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|renderer
expr_stmt|;
name|tool_info
operator|=
name|gimp_get_tool_info
argument_list|(
name|image_editor
operator|->
name|image
operator|->
name|gimp
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return
name|TRUE
return|;
name|sel_options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_REGION_SELECT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|TRUE
return|;
name|operation
operator|=
name|gimp_modifiers_to_channel_op
argument_list|(
name|bevent
operator|->
name|state
argument_list|)
expr_stmt|;
name|x
operator|=
name|gimp_image_get_width
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
operator|*
name|bevent
operator|->
name|x
operator|/
name|renderer
operator|->
name|width
expr_stmt|;
name|y
operator|=
name|gimp_image_get_height
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
operator|*
name|bevent
operator|->
name|y
operator|/
name|renderer
operator|->
name|height
expr_stmt|;
if|if
condition|(
name|gimp_image_pick_color
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|drawable
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|color
argument_list|)
condition|)
block|{
name|gimp_channel_select_by_color
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
operator|&
name|color
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|,
name|options
operator|->
name|select_criterion
argument_list|,
name|operation
argument_list|,
name|sel_options
operator|->
name|antialias
argument_list|,
name|sel_options
operator|->
name|feather
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image_editor
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_drop_color (GtkWidget * widget,gint x,gint y,const GimpRGB * color,gpointer data)
name|gimp_selection_editor_drop_color
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|sel_options
decl_stmt|;
name|GimpRegionSelectOptions
modifier|*
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
if|if
condition|(
operator|!
name|editor
operator|->
name|image
condition|)
return|return;
name|tool_info
operator|=
name|gimp_get_tool_info
argument_list|(
name|editor
operator|->
name|image
operator|->
name|gimp
argument_list|,
literal|"gimp-by-color-select-tool"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
name|sel_options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_REGION_SELECT_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|editor
operator|->
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return;
name|gimp_channel_select_by_color
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|editor
operator|->
name|image
argument_list|)
argument_list|,
name|drawable
argument_list|,
name|options
operator|->
name|sample_merged
argument_list|,
name|color
argument_list|,
name|options
operator|->
name|threshold
argument_list|,
name|options
operator|->
name|select_transparent
argument_list|,
name|options
operator|->
name|select_criterion
argument_list|,
name|sel_options
operator|->
name|operation
argument_list|,
name|sel_options
operator|->
name|antialias
argument_list|,
name|sel_options
operator|->
name|feather
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|,
name|sel_options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|image
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_mask_changed (GimpImage * image,GimpSelectionEditor * editor)
name|gimp_selection_editor_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_view_renderer_invalidate
argument_list|(
name|GIMP_VIEW
argument_list|(
name|editor
operator|->
name|view
argument_list|)
operator|->
name|renderer
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

