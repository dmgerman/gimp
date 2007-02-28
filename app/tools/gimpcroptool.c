begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"tools-types.h"
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
name|GObject
modifier|*
name|gimp_crop_tool_constructor
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
name|gimp_crop_tool_notify_layer_only
parameter_list|(
name|GimpCropOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpTool
modifier|*
name|tool
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
name|constructor
operator|=
name|gimp_crop_tool_constructor
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
name|gimp_rectangle_tool_install_properties
argument_list|(
name|object_class
argument_list|)
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
name|gimp_rectangle_tool_draw
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
name|GimpRectangleTool
modifier|*
name|rect_tool
init|=
name|GIMP_RECTANGLE_TOOL
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
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_CROP
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|rect_tool
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_crop_tool_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_crop_tool_constructor
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
name|GimpRectangleTool
modifier|*
name|rectangle
decl_stmt|;
name|GimpRectangleOptions
modifier|*
name|options
decl_stmt|;
name|gboolean
name|layer_only
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
name|gimp_rectangle_tool_constructor
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|rectangle
operator|=
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_RECTANGLE_TOOL_GET_OPTIONS
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
name|gimp_crop_tool_notify_layer_only
argument_list|)
argument_list|,
name|object
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|options
argument_list|,
literal|"layer-only"
argument_list|,
operator|&
name|layer_only
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_only
condition|)
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|rectangle
argument_list|,
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
argument_list|)
expr_stmt|;
else|else
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|rectangle
argument_list|,
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
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
DECL|function|gimp_crop_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_crop_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
DECL|function|gimp_crop_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_crop_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
DECL|function|gimp_crop_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_crop_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_CROP
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
decl_stmt|;
name|gint
name|max_x
decl_stmt|,
name|max_y
decl_stmt|;
name|gboolean
name|rectangle_exists
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
name|image
operator|=
name|tool
operator|->
name|display
operator|->
name|image
expr_stmt|;
name|max_x
operator|=
name|image
operator|->
name|width
expr_stmt|;
name|max_y
operator|=
name|image
operator|->
name|height
expr_stmt|;
name|rectangle_exists
operator|=
operator|(
name|x
operator|<=
name|max_x
operator|&&
name|y
operator|<=
name|max_y
operator|&&
name|x
operator|+
name|w
operator|>=
literal|0
operator|&&
name|y
operator|+
name|h
operator|>=
literal|0
operator|&&
name|w
operator|>
literal|0
operator|&&
name|h
operator|>
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
block|{
name|w
operator|+=
name|x
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|<
literal|0
condition|)
block|{
name|h
operator|+=
name|y
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|+
name|w
operator|>
name|max_x
condition|)
name|w
operator|=
name|max_x
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|+
name|h
operator|>
name|max_y
condition|)
name|h
operator|=
name|max_y
operator|-
name|y
expr_stmt|;
comment|/* if rectangle exists, crop it */
if|if
condition|(
name|rectangle_exists
condition|)
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
operator|+
name|x
argument_list|,
name|h
operator|+
name|y
argument_list|,
name|options
operator|->
name|layer_only
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
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

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_notify_layer_only (GimpCropOptions * options,GParamSpec * pspec,GimpTool * tool)
name|gimp_crop_tool_notify_layer_only
parameter_list|(
name|GimpCropOptions
modifier|*
name|options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpRectangleTool
modifier|*
name|rectangle
init|=
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gboolean
name|layer_only
decl_stmt|;
name|g_object_get
argument_list|(
name|options
argument_list|,
literal|"layer-only"
argument_list|,
operator|&
name|layer_only
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|layer_only
condition|)
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|rectangle
argument_list|,
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
argument_list|)
expr_stmt|;
else|else
name|gimp_rectangle_tool_set_constraint
argument_list|(
name|rectangle
argument_list|,
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

