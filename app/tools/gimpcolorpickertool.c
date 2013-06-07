begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorframe.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimptoolgui.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickeroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpickertool.h"
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

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_constructed
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
name|gimp_color_picker_tool_control
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
name|gimp_color_picker_tool_modifier_key
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
name|gimp_color_picker_tool_oper_update
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
name|gboolean
name|proximity
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
name|gimp_color_picker_tool_picked
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_info_create
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_info_response
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_info_update
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorPickerTool,gimp_color_picker_tool,GIMP_TYPE_COLOR_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorPickerTool
argument_list|,
argument|gimp_color_picker_tool
argument_list|,
argument|GIMP_TYPE_COLOR_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_picker_tool_parent_class
end_define

begin_function
name|void
name|gimp_color_picker_tool_register
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
name|GIMP_TYPE_COLOR_PICKER_TOOL
argument_list|,
name|GIMP_TYPE_COLOR_PICKER_OPTIONS
argument_list|,
name|gimp_color_picker_options_gui
argument_list|,
name|GIMP_CONTEXT_FOREGROUND_MASK
operator||
name|GIMP_CONTEXT_BACKGROUND_MASK
argument_list|,
literal|"gimp-color-picker-tool"
argument_list|,
name|_
argument_list|(
literal|"Color Picker"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Color Picker Tool: Set colors from image pixels"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"C_olor Picker"
argument_list|)
argument_list|,
literal|"O"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_COLOR_PICKER
argument_list|,
name|GIMP_STOCK_TOOL_COLOR_PICKER
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_class_init (GimpColorPickerToolClass * klass)
name|gimp_color_picker_tool_class_init
parameter_list|(
name|GimpColorPickerToolClass
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
name|GimpColorToolClass
modifier|*
name|color_tool_class
init|=
name|GIMP_COLOR_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_color_picker_tool_constructed
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_color_picker_tool_control
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_color_picker_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_color_picker_tool_oper_update
expr_stmt|;
name|color_tool_class
operator|->
name|picked
operator|=
name|gimp_color_picker_tool_picked
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_init (GimpColorPickerTool * picker_tool)
name|gimp_color_picker_tool_init
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|picker_tool
argument_list|)
decl_stmt|;
name|GimpColorTool
modifier|*
name|color_tool
init|=
name|GIMP_COLOR_TOOL
argument_list|(
name|picker_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_motion_mode
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_MOTION_MODE_COMPRESS
argument_list|)
expr_stmt|;
name|color_tool
operator|->
name|pick_mode
operator|=
name|GIMP_COLOR_PICK_MODE_FOREGROUND
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_constructed (GObject * object)
name|gimp_color_picker_tool_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
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
name|gimp_color_tool_enable
argument_list|(
name|GIMP_COLOR_TOOL
argument_list|(
name|object
argument_list|)
argument_list|,
name|GIMP_COLOR_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_color_picker_tool_control
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
name|GimpColorPickerTool
modifier|*
name|picker_tool
init|=
name|GIMP_COLOR_PICKER_TOOL
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
if|if
condition|(
name|picker_tool
operator|->
name|gui
condition|)
block|{
name|g_object_unref
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|)
expr_stmt|;
name|picker_tool
operator|->
name|gui
operator|=
name|NULL
expr_stmt|;
name|picker_tool
operator|->
name|color_area
operator|=
name|NULL
expr_stmt|;
name|picker_tool
operator|->
name|color_frame1
operator|=
name|NULL
expr_stmt|;
name|picker_tool
operator|->
name|color_frame2
operator|=
name|NULL
expr_stmt|;
block|}
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
DECL|function|gimp_color_picker_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_color_picker_tool_modifier_key
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
name|GimpColorPickerOptions
modifier|*
name|options
init|=
name|GIMP_COLOR_PICKER_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_SHIFT_MASK
condition|)
block|{
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"use-info-window"
argument_list|,
operator|!
name|options
operator|->
name|use_info_window
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|key
operator|==
name|gimp_get_toggle_behavior_mask
argument_list|()
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|pick_mode
condition|)
block|{
case|case
name|GIMP_COLOR_PICK_MODE_FOREGROUND
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"pick-mode"
argument_list|,
name|GIMP_COLOR_PICK_MODE_BACKGROUND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_BACKGROUND
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"pick-mode"
argument_list|,
name|GIMP_COLOR_PICK_MODE_FOREGROUND
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_color_picker_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpColorPickerTool
modifier|*
name|picker_tool
init|=
name|GIMP_COLOR_PICKER_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpColorPickerOptions
modifier|*
name|options
init|=
name|GIMP_COLOR_PICKER_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GdkModifierType
name|toggle_mask
decl_stmt|;
name|toggle_mask
operator|=
name|gimp_get_toggle_behavior_mask
argument_list|()
expr_stmt|;
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|pick_mode
operator|=
name|options
operator|->
name|pick_mode
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
name|proximity
condition|)
block|{
name|gchar
modifier|*
name|status_help
init|=
name|NULL
decl_stmt|;
name|GdkModifierType
name|shift_mod
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|picker_tool
operator|->
name|gui
condition|)
name|shift_mod
operator|=
name|GDK_SHIFT_MASK
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|pick_mode
condition|)
block|{
case|case
name|GIMP_COLOR_PICK_MODE_NONE
case|:
name|status_help
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click in any image to view"
literal|" its color"
argument_list|)
argument_list|,
name|shift_mod
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_FOREGROUND
case|:
name|status_help
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click in any image to pick"
literal|" the foreground color"
argument_list|)
argument_list|,
operator|(
name|shift_mod
operator||
name|toggle_mask
operator|)
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_BACKGROUND
case|:
name|status_help
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click in any image to pick"
literal|" the background color"
argument_list|)
argument_list|,
operator|(
name|shift_mod
operator||
name|toggle_mask
operator|)
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_PALETTE
case|:
name|status_help
operator|=
name|gimp_suggest_modifiers
argument_list|(
name|_
argument_list|(
literal|"Click in any image to add"
literal|" the color to the palette"
argument_list|)
argument_list|,
name|shift_mod
operator|&
operator|~
name|state
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|status_help
operator|!=
name|NULL
condition|)
block|{
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
literal|"%s"
argument_list|,
name|status_help
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|status_help
argument_list|)
expr_stmt|;
block|}
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|oper_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_picked (GimpColorTool * color_tool,GimpColorPickState pick_state,gdouble x,gdouble y,const Babl * sample_format,const GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_picked
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
name|GimpColorPickerTool
modifier|*
name|picker_tool
init|=
name|GIMP_COLOR_PICKER_TOOL
argument_list|(
name|color_tool
argument_list|)
decl_stmt|;
name|GimpColorPickerOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_COLOR_PICKER_TOOL_GET_OPTIONS
argument_list|(
name|color_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|use_info_window
operator|&&
operator|!
name|picker_tool
operator|->
name|gui
condition|)
name|gimp_color_picker_tool_info_create
argument_list|(
name|picker_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|picker_tool
operator|->
name|gui
condition|)
name|gimp_color_picker_tool_info_update
argument_list|(
name|picker_tool
argument_list|,
name|sample_format
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|GIMP_COLOR_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|picked
argument_list|(
name|color_tool
argument_list|,
name|pick_state
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|sample_format
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_create (GimpColorPickerTool * picker_tool)
name|gimp_color_picker_tool_info_create
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|picker_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|tool
operator|->
name|drawable
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|picker_tool
operator|->
name|gui
operator|=
name|gimp_tool_gui_new
argument_list|(
name|tool
operator|->
name|tool_info
argument_list|,
name|_
argument_list|(
literal|"Color Picker Information"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_tool_gui_get_dialog
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_tool_gui_get_vbox
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_IS_DIALOG
argument_list|(
name|dialog
argument_list|)
condition|)
name|gtk_window_set_focus_on_map
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_gui_set_viewable
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_picker_tool_info_response
argument_list|)
argument_list|,
name|picker_tool
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|picker_tool
operator|->
name|color_frame1
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|picker_tool
operator|->
name|color_frame1
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_PIXEL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|picker_tool
operator|->
name|color_frame1
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
name|picker_tool
operator|->
name|color_frame1
argument_list|)
expr_stmt|;
name|picker_tool
operator|->
name|color_frame2
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|picker_tool
operator|->
name|color_frame2
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_RGB
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|picker_tool
operator|->
name|color_frame2
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
name|picker_tool
operator|->
name|color_frame2
argument_list|)
expr_stmt|;
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
name|hbox
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
name|gimp_rgba_set
argument_list|(
operator|&
name|color
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|picker_tool
operator|->
name|color_area
operator|=
name|gimp_color_area_new
argument_list|(
operator|&
name|color
argument_list|,
name|gimp_drawable_has_alpha
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
condition|?
name|GIMP_COLOR_AREA_LARGE_CHECKS
else|:
name|GIMP_COLOR_AREA_FLAT
argument_list|,
name|GDK_BUTTON1_MASK
operator||
name|GDK_BUTTON2_MASK
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|picker_tool
operator|->
name|color_area
argument_list|,
literal|48
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_drag_dest_unset
argument_list|(
name|picker_tool
operator|->
name|color_area
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|picker_tool
operator|->
name|color_area
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|picker_tool
operator|->
name|color_area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_response (GimpToolGui * gui,gint response_id,GimpColorPickerTool * picker_tool)
name|gimp_color_picker_tool_info_response
parameter_list|(
name|GimpToolGui
modifier|*
name|gui
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|picker_tool
argument_list|)
decl_stmt|;
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_update (GimpColorPickerTool * picker_tool,const Babl * sample_format,const GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_info_update
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|,
specifier|const
name|Babl
modifier|*
name|sample_format
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|picker_tool
argument_list|)
decl_stmt|;
name|gimp_tool_gui_set_shell
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|,
name|gimp_display_get_shell
argument_list|(
name|tool
operator|->
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_gui_set_viewable
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_area_set_color
argument_list|(
name|GIMP_COLOR_AREA
argument_list|(
name|picker_tool
operator|->
name|color_area
argument_list|)
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_color
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|picker_tool
operator|->
name|color_frame1
argument_list|)
argument_list|,
name|sample_format
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_color
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|picker_tool
operator|->
name|color_frame2
argument_list|)
argument_list|,
name|sample_format
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|gimp_tool_gui_show
argument_list|(
name|picker_tool
operator|->
name|gui
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

