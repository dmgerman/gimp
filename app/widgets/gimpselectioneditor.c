begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|#include "tools/tools-types.h"
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimpselectionoptions.h"
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
name|GObject
modifier|*
name|gimp_selection_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
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
name|gimage
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
name|gimage
parameter_list|,
name|GimpSelectionEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE
argument_list|(
name|GimpSelectionEditor
argument_list|,
name|gimp_selection_editor
argument_list|,
name|GIMP_TYPE_IMAGE_EDITOR
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_selection_editor_parent_class
end_define

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
name|constructor
operator|=
name|gimp_selection_editor_constructor
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
name|GObject
modifier|*
DECL|function|gimp_selection_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_selection_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpSelectionEditor
modifier|*
name|editor
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_SELECTION_EDITOR
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
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_set_image (GimpImageEditor * image_editor,GimpImage * gimage)
name|gimp_selection_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|gimage
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
name|gimage
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|gimage
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
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
name|g_signal_connect
argument_list|(
name|gimage
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
name|gimage
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
literal|"<SelectionEditor>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/selection-editor-popup"
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
name|options
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|SelectOps
name|operation
init|=
name|SELECTION_REPLACE
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
name|gimage
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
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|image_editor
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
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
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|image_editor
operator|->
name|gimage
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
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
condition|)
block|{
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|SELECTION_INTERSECT
expr_stmt|;
block|}
else|else
block|{
name|operation
operator|=
name|SELECTION_ADD
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|bevent
operator|->
name|state
operator|&
name|GDK_CONTROL_MASK
condition|)
block|{
name|operation
operator|=
name|SELECTION_SUBTRACT
expr_stmt|;
block|}
name|x
operator|=
name|image_editor
operator|->
name|gimage
operator|->
name|width
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
name|image_editor
operator|->
name|gimage
operator|->
name|height
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
name|gimage
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
operator|&
name|color
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|gimp_channel_select_by_color
argument_list|(
name|gimp_image_get_mask
argument_list|(
name|image_editor
operator|->
name|gimage
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
name|operation
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|image_editor
operator|->
name|gimage
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
name|gimage
condition|)
return|return;
name|tool_info
operator|=
operator|(
name|GimpToolInfo
operator|*
operator|)
name|gimp_container_get_child_by_name
argument_list|(
name|editor
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|tool_info_list
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
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|editor
operator|->
name|gimage
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
name|gimage
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
name|operation
argument_list|,
name|options
operator|->
name|antialias
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|editor
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_selection_editor_mask_changed (GimpImage * gimage,GimpSelectionEditor * editor)
name|gimp_selection_editor_mask_changed
parameter_list|(
name|GimpImage
modifier|*
name|gimage
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

