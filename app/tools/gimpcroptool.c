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
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolrectangle.h"
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
file|"gimprectangleoptions.h"
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
name|gimp_crop_tool_motion
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
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_crop_tool_rectangle_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|rectangle
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
name|gimp_crop_tool_rectangle_response
parameter_list|(
name|GimpToolWidget
modifier|*
name|rectangle
parameter_list|,
name|gint
name|response_id
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
name|gimp_crop_tool_rectangle_change_complete
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
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
name|gimp_crop_tool_start
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
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
name|gimp_crop_tool_commit
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
name|gimp_crop_tool_halt
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
name|gimp_crop_tool_auto_shrink
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCropTool,gimp_crop_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCropTool
argument_list|,
argument|gimp_crop_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

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
name|GIMP_ICON_TOOL_CROP
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_crop_tool_constructed
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
name|gimp_crop_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|options_notify
operator|=
name|gimp_crop_tool_options_notify
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
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_CROSSHAIR_SMALL
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
name|GimpContext
modifier|*
name|context
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
name|tool_info
operator|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
operator|->
name|tool_info
expr_stmt|;
name|context
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
name|context
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
name|context
argument_list|)
argument_list|,
name|context
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
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|GIMP_TOOL_ACTION_PAUSE
case|:
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|gimp_crop_tool_halt
argument_list|(
name|crop_tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TOOL_ACTION_COMMIT
case|:
name|gimp_crop_tool_commit
argument_list|(
name|crop_tool
argument_list|)
expr_stmt|;
break|break;
block|}
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
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
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
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_COMMIT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_crop_tool_start
argument_list|(
name|crop_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_tool_widget_hover
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* HACK: force CREATING on a newly created rectangle; otherwise,        * the above binding of properties would cause the rectangle to        * start with the size from tool options.        */
name|gimp_tool_rectangle_set_function
argument_list|(
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|)
argument_list|,
name|GIMP_TOOL_RECTANGLE_CREATING
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_tool_widget_button_press
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|press_type
argument_list|)
condition|)
block|{
name|crop_tool
operator|->
name|grab_widget
operator|=
name|crop_tool
operator|->
name|widget
expr_stmt|;
block|}
name|gimp_tool_control_activate
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
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|crop_tool
operator|->
name|grab_widget
condition|)
block|{
name|gimp_tool_widget_button_release
argument_list|(
name|crop_tool
operator|->
name|grab_widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|release_type
argument_list|)
expr_stmt|;
name|crop_tool
operator|->
name|grab_widget
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_crop_tool_motion
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
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|crop_tool
operator|->
name|grab_widget
condition|)
block|{
name|gimp_tool_widget_motion
argument_list|(
name|crop_tool
operator|->
name|grab_widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_options_notify (GimpTool * tool,GimpToolOptions * options,const GParamSpec * pspec)
name|gimp_crop_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpCropTool
modifier|*
name|crop_tool
init|=
name|GIMP_CROP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|crop_tool
operator|->
name|widget
condition|)
block|{
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"layer-only"
argument_list|)
operator|||
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"allow-growing"
argument_list|)
condition|)
block|{
name|gimp_tool_rectangle_set_constraint
argument_list|(
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|)
argument_list|,
name|gimp_crop_tool_get_constraint
argument_list|(
name|crop_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_rectangle_changed (GimpToolWidget * rectangle,GimpCropTool * crop_tool)
name|gimp_crop_tool_rectangle_changed
parameter_list|(
name|GimpToolWidget
modifier|*
name|rectangle
parameter_list|,
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_rectangle_response (GimpToolWidget * rectangle,gint response_id,GimpCropTool * crop_tool)
name|gimp_crop_tool_rectangle_response
parameter_list|(
name|GimpToolWidget
modifier|*
name|rectangle
parameter_list|,
name|gint
name|response_id
parameter_list|,
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
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GIMP_TOOL_WIDGET_RESPONSE_CONFIRM
case|:
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_COMMIT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_TOOL_WIDGET_RESPONSE_CANCEL
case|:
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|tool
operator|->
name|display
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_rectangle_change_complete (GimpToolRectangle * rectangle,GimpCropTool * crop_tool)
name|gimp_crop_tool_rectangle_change_complete
parameter_list|(
name|GimpToolRectangle
modifier|*
name|rectangle
parameter_list|,
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
DECL|function|gimp_crop_tool_start (GimpCropTool * crop_tool,GimpDisplay * display)
name|gimp_crop_tool_start
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
specifier|static
specifier|const
name|gchar
modifier|*
name|properties
index|[]
init|=
block|{
literal|"highlight"
block|,
literal|"guide"
block|,
literal|"x"
block|,
literal|"y"
block|,
literal|"width"
block|,
literal|"height"
block|,
literal|"fixed-rule-active"
block|,
literal|"fixed-rule"
block|,
literal|"desired-fixed-width"
block|,
literal|"desired-fixed-height"
block|,
literal|"desired-fixed-size-width"
block|,
literal|"desired-fixed-size-height"
block|,
literal|"aspect-numerator"
block|,
literal|"aspect-denominator"
block|,
literal|"fixed-center"
block|}
decl_stmt|;
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|GimpCropOptions
modifier|*
name|options
init|=
name|GIMP_CROP_TOOL_GET_OPTIONS
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
name|GimpToolWidget
modifier|*
name|widget
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|crop_tool
operator|->
name|widget
operator|=
name|widget
operator|=
name|gimp_tool_rectangle_new
argument_list|(
name|shell
argument_list|)
expr_stmt|;
name|gimp_draw_tool_set_widget
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|widget
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
name|G_N_ELEMENTS
argument_list|(
name|properties
argument_list|)
condition|;
name|i
operator|++
control|)
name|g_object_bind_property
argument_list|(
name|G_OBJECT
argument_list|(
name|options
argument_list|)
argument_list|,
name|properties
index|[
name|i
index|]
argument_list|,
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|properties
index|[
name|i
index|]
argument_list|,
name|G_BINDING_SYNC_CREATE
operator||
name|G_BINDING_BIDIRECTIONAL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_rectangle_changed
argument_list|)
argument_list|,
name|crop_tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_rectangle_response
argument_list|)
argument_list|,
name|crop_tool
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|widget
argument_list|,
literal|"change-complete"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_rectangle_change_complete
argument_list|)
argument_list|,
name|crop_tool
argument_list|)
expr_stmt|;
name|gimp_rectangle_options_connect
argument_list|(
name|GIMP_RECTANGLE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|gimp_display_get_image
argument_list|(
name|shell
operator|->
name|display
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_auto_shrink
argument_list|)
argument_list|,
name|crop_tool
argument_list|)
expr_stmt|;
name|gimp_tool_rectangle_set_constraint
argument_list|(
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|widget
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
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_commit (GimpCropTool * crop_tool)
name|gimp_crop_tool_commit
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
name|gdouble
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gdouble
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gimp_tool_rectangle_get_public_rect
argument_list|(
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
expr_stmt|;
name|w
operator|=
name|x2
operator|-
name|x
expr_stmt|;
name|h
operator|=
name|y2
operator|-
name|y
expr_stmt|;
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
return|return;
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
return|return;
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
name|options
operator|->
name|fill_type
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
name|GIMP_FILL_TRANSPARENT
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
block|}
name|gimp_crop_tool_halt
argument_list|(
name|crop_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_crop_tool_halt (GimpCropTool * crop_tool)
name|gimp_crop_tool_halt
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
name|GimpCropOptions
modifier|*
name|options
init|=
name|GIMP_CROP_TOOL_GET_OPTIONS
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool
operator|->
name|display
condition|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
decl_stmt|;
name|gimp_display_shell_set_highlight
argument_list|(
name|shell
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_rectangle_options_disconnect
argument_list|(
name|GIMP_RECTANGLE_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_crop_tool_auto_shrink
argument_list|)
argument_list|,
name|crop_tool
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_draw_tool_is_active
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
condition|)
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_draw_tool_set_widget
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|crop_tool
operator|->
name|widget
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
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
init|=
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
decl_stmt|;
name|GimpToolRectangle
modifier|*
name|rectangle
init|=
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|)
decl_stmt|;
name|GimpRectangleOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_RECTANGLE_OPTIONS
argument_list|(
name|GIMP_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|rectangle
condition|)
return|return;
if|if
condition|(
name|tool
operator|->
name|display
operator|&&
operator|!
name|ignore_pending
condition|)
block|{
comment|/* There is a pending rectangle and we should not ignore it, so        * set default Fixed: Aspect ratio to the same as the current        * pending rectangle width/height.        */
name|gimp_tool_rectangle_pending_size_set
argument_list|(
name|rectangle
argument_list|,
name|G_OBJECT
argument_list|(
name|options
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
name|options
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
name|gimp_tool_rectangle_constraint_size_set
argument_list|(
name|rectangle
argument_list|,
name|G_OBJECT
argument_list|(
name|options
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
name|options
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
name|crop_tool
operator|->
name|current_image
operator|=
name|image
expr_stmt|;
if|if
condition|(
name|crop_tool
operator|->
name|current_image
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|crop_tool
operator|->
name|current_image
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
DECL|function|gimp_crop_tool_auto_shrink (GimpCropTool * crop_tool)
name|gimp_crop_tool_auto_shrink
parameter_list|(
name|GimpCropTool
modifier|*
name|crop_tool
parameter_list|)
block|{
name|gboolean
name|shrink_merged
decl_stmt|;
name|g_object_get
argument_list|(
name|gimp_tool_get_options
argument_list|(
name|GIMP_TOOL
argument_list|(
name|crop_tool
argument_list|)
argument_list|)
argument_list|,
literal|"shrink-merged"
argument_list|,
operator|&
name|shrink_merged
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_tool_rectangle_auto_shrink
argument_list|(
name|GIMP_TOOL_RECTANGLE
argument_list|(
name|crop_tool
operator|->
name|widget
argument_list|)
argument_list|,
name|shrink_merged
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

