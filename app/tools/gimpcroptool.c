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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-crop.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangletool.h"
end_include

begin_include
include|#
directive|include
file|"gimpcropoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcroptool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_rectangle_tool_iface_init
parameter_list|(
name|GimpRectangleToolInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_constructed
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
name|gimp_crop_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_crop_tool_execute
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_update_option_defaults
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|,
name|gboolean
name|ignore_pending
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpRectangleConstraint
name|gimp_crop_tool_get_constraint
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_options_notify
parameter_list|(
name|GimpCropOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_image_changed
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_image_size_changed
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_cancel
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_crop_tool_rectangle_change_complete
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|)
function_decl|;
end_function_decl

begin_expr_stmt
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
name|GimpCropTool
argument_list|,
name|gimp_crop_tool
argument_list|,
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
name|G_IMPLEMENT_INTERFACE
argument_list|(
name|GIMP_TYPE_RECTANGLE_TOOL
argument_list|,
name|gimp_crop_tool_rectangle_tool_iface_init
argument_list|)
argument_list|)
expr_stmt|;
end_expr_stmt

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_crop_tool_parent_class
end_define

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_crop_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_crop_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_CROP_TOOL
argument_list|,
name|GIMP_TYPE_CROP_OPTIONS
argument_list|,
name|gimp_crop_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-crop-tool"
argument_list|,
name|_
argument_list|(
literal|"Crop"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Crop Tool: Remove edge areas from image or layer"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Crop"
argument_list|)
argument_list|,
literal|"<shift>C"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_CROP
argument_list|,
name|GIMP_STOCK_TOOL_CROP
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_class_init (GimpCropToolClass * klass)
name|gimp_crop_tool_class_init
parameter_list|(
name|GimpCropToolClass
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
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_crop_tool_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_rectangle_tool_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_rectangle_tool_get_property
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_crop_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_crop_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_crop_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_rectangle_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_rectangle_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|active_modifier_key
operator|=
name|gimp_crop_tool_active_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_rectangle_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_crop_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_crop_tool_draw
expr_stmt|;
name|gimp_rectangle_tool_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_rectangle_tool_iface_init (GimpRectangleToolInterface * iface)
name|gimp_crop_tool_rectangle_tool_iface_init
parameter_list|(
name|GimpRectangleToolInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|execute
operator|=
name|gimp_crop_tool_execute
expr_stmt|;
name|iface
operator|->
name|cancel
operator|=
name|gimp_crop_tool_cancel
expr_stmt|;
name|iface
operator|->
name|rectangle_change_complete
operator|=
name|gimp_crop_tool_rectangle_change_complete
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_init (GimpCropTool * crop_tool)
name|gimp_crop_tool_init
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_wants_click
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_precision
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_CROP
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_init
argument_list|(
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|crop_tool
argument_list|)
argument_list|)
expr_stmt|;
name|crop_tool
operator|->
name|current_image
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_constructed (GObject * object)
name|gimp_crop_tool_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpCropOptions
modifier|*
name|options
decl_stmt|;
name|GimpContext
modifier|*
name|gimp_context
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
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
name|gimp_rectangle_tool_constructor
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
operator|->
name|tool_info
expr_stmt|;
name|gimp_context
operator|=
name|gimp_get_user_context
argument_list|(
name|tool_info
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|gimp_context
argument_list|,
literal|"image-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_image_changed
argument_list|)
argument_list|,
name|crop_tool
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
comment|/* Make sure we are connected to "size-changed" for the initial    * image.    */
name|gimp_crop_tool_image_changed
argument_list|(
name|crop_tool
argument_list|,
name|gimp_context_get_image
argument_list|(
name|gimp_context
argument_list|)
argument_list|,
name|gimp_context
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_CROP_TOOL_GET_OPTIONS
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|options
argument_list|,
literal|"notify::layer-only"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_options_notify
argument_list|)
argument_list|,
name|object
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|options
argument_list|,
literal|"notify::allow-growing"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_options_notify
argument_list|)
argument_list|,
name|object
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|object
argument_list|)
argument_list|,
name|gimp_crop_tool_get_constraint
argument_list|(
name|crop_tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_crop_tool_update_option_defaults
argument_list|(
name|crop_tool
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_crop_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_rectangle_tool_control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_crop_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
if|if
condition|(
name|tool
operator|->
name|display
operator|&&
name|display
operator|!=
name|tool
operator|->
name|display
condition|)
name|gimp_rectangle_tool_cancel
argument_list|(
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_button_press
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_crop_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|_
argument_list|(
literal|"Click or press Enter to crop"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_button_release
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|release_type
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_active_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_crop_tool_active_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|active_modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_active_modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_crop_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_rectangle_tool_cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_draw (GimpDrawTool * draw_tool)
name|gimp_crop_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|gimp_rectangle_tool_draw
argument_list|(
name|draw_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_crop_tool_execute (GimpRectangleTool * rectangle,gint x,gint y,gint w,gint h)
name|gimp_crop_tool_execute
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|rectangle
argument_list|)
decl_stmt|;
name|GimpCropOptions
modifier|*
name|options
init|=
name|GIMP_CROP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
comment|/* if rectangle exists, crop it */
if|if
condition|(
name|w
operator|>
literal|0
operator|&&
name|h
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|layer_only
condition|)
block|{
name|GimpLayer
modifier|*
name|layer
init|=
name|gimp_image_get_active_layer
argument_list|(
name|image
argument_list|)
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
if|if
condition|(
operator|!
name|layer
condition|)
block|{
name|gimp_tool_message_literal
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|,
name|_
argument_list|(
literal|"There is no active layer to crop."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_item_is_content_locked
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_tool_message_literal
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|display
argument_list|,
name|_
argument_list|(
literal|"The active layer's pixels are locked."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|gimp_item_get_offset
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
name|off_x
operator|-=
name|x
expr_stmt|;
name|off_y
operator|-=
name|y
expr_stmt|;
name|gimp_item_resize
argument_list|(
name|GIMP_ITEM
argument_list|(
name|layer
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|off_x
argument_list|,
name|off_y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_crop
argument_list|(
name|image
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|options
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
name|gimp_image_flush
argument_list|(
name|image
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_crop_tool_rectangle_change_complete:  * @rectangle:  *  * Returns:  **/
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_crop_tool_rectangle_change_complete (GimpRectangleTool * rectangle)
name|gimp_crop_tool_rectangle_change_complete
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|)
block|{
name|gimp_crop_tool_update_option_defaults
argument_list|(
name|GIMP_CROP_TOOL
argument_list|(
name|rectangle
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_crop_tool_update_option_defaults:  * @crop_tool:  * @ignore_pending: %TRUE to ignore any pending crop rectangle.  *  * Sets the default Fixed: Aspect ratio and Fixed: Size option  * properties.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_update_option_defaults (GimpCropTool * crop_tool,gboolean ignore_pending)
name|gimp_crop_tool_update_option_defaults
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|,
name|gboolean
name|ignore_pending
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpRectangleTool
modifier|*
name|rectangle_tool
decl_stmt|;
name|GimpRectangleOptions
modifier|*
name|rectangle_options
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
expr_stmt|;
name|rectangle_tool
operator|=
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|rectangle_options
operator|=
name|GIMP_RECTANGLE_TOOL_GET_OPTIONS
argument_list|(
name|rectangle_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
operator|!=
name|NULL
operator|&&
operator|!
name|ignore_pending
condition|)
block|{
comment|/* There is a pending rectangle and we should not ignore it, so        * set default Fixed: Aspect ratio to the same as the current        * pending rectangle width/height.        */
name|gimp_rectangle_tool_pending_size_set
argument_list|(
name|rectangle_tool
argument_list|,
name|G_OBJECT
argument_list|(
name|rectangle_options
argument_list|)
argument_list|,
literal|"default-aspect-numerator"
argument_list|,
literal|"default-aspect-denominator"
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|rectangle_options
argument_list|)
argument_list|,
literal|"use-string-current"
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* There is no pending rectangle, set default Fixed: Aspect        * ratio to that of the current image/layer.        */
name|gimp_rectangle_tool_constraint_size_set
argument_list|(
name|rectangle_tool
argument_list|,
name|G_OBJECT
argument_list|(
name|rectangle_options
argument_list|)
argument_list|,
literal|"default-aspect-numerator"
argument_list|,
literal|"default-aspect-denominator"
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|G_OBJECT
argument_list|(
name|rectangle_options
argument_list|)
argument_list|,
literal|"use-string-current"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|GimpRectangleConstraint
DECL|function|gimp_crop_tool_get_constraint (GimpCropTool * crop_tool)
name|gimp_crop_tool_get_constraint
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{
name|GimpCropOptions
modifier|*
name|crop_options
init|=
name|GIMP_CROP_TOOL_GET_OPTIONS
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|crop_options
operator|->
name|allow_growing
condition|)
block|{
return|return
name|GIMP_RECTANGLE_CONSTRAIN_NONE
return|;
block|}
else|else
block|{
return|return
name|crop_options
operator|->
name|layer_only
condition|?
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
else|:
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_options_notify (GimpCropOptions * options,GParamSpec * pspec,GimpCropTool * crop_tool)
name|gimp_crop_tool_options_notify
parameter_list|(
name|GimpCropOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|crop_tool
argument_list|)
argument_list|,
name|gimp_crop_tool_get_constraint
argument_list|(
name|crop_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_image_changed (GimpCropTool * crop_tool,GimpImage * image,GimpContext * context)
name|gimp_crop_tool_image_changed
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
if|if
condition|(
name|crop_tool
operator|->
name|current_image
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|crop_tool
operator|->
name|current_image
argument_list|,
name|gimp_crop_tool_image_size_changed
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|image
argument_list|,
literal|"size-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_image_size_changed
argument_list|)
argument_list|,
name|crop_tool
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
name|crop_tool
operator|->
name|current_image
operator|=
name|image
expr_stmt|;
name|gimp_crop_tool_update_option_defaults
argument_list|(
name|GIMP_CROP_TOOL
argument_list|(
name|crop_tool
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
DECL|function|gimp_crop_tool_image_size_changed (GimpCropTool * crop_tool)
name|gimp_crop_tool_image_size_changed
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{
name|gimp_crop_tool_update_option_defaults
argument_list|(
name|crop_tool
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_cancel (GimpRectangleTool * rect_tool)
name|gimp_crop_tool_cancel
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|)
block|{
name|gimp_crop_tool_update_option_defaults
argument_list|(
name|GIMP_CROP_TOOL
argument_list|(
name|rect_tool
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

