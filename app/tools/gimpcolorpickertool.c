begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpconfig/gimpconfig.h"
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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcolorframe.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppaletteeditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooldialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
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
name|gimp_color_picker_tool_class_init
parameter_list|(
name|GimpColorPickerToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_picker_tool_init
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_color_picker_tool_constructor
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
name|gimp_color_picker_tool_finalize
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
name|gdisp
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
name|gdisp
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
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
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
name|GimpImageType
name|sample_type
parameter_list|,
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
name|GtkWidget
modifier|*
name|widget
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
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpColorToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_color_picker_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
literal|0
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
literal|"Pick colors from the image"
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
name|GtkType
DECL|function|gimp_color_picker_tool_get_type (void)
name|gimp_color_picker_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpColorPickerToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_color_picker_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorPickerTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_picker_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_COLOR_TOOL
argument_list|,
literal|"GimpColorPickerTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_color_picker_tool_constructor
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_color_picker_tool_finalize
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
DECL|function|gimp_color_picker_tool_init (GimpColorPickerTool * tool)
name|gimp_color_picker_tool_init
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpColorTool
modifier|*
name|color_tool
init|=
name|GIMP_COLOR_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
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
name|GObject
modifier|*
DECL|function|gimp_color_picker_tool_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_color_picker_tool_constructor
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
name|GimpTool
modifier|*
name|tool
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
name|tool
operator|=
name|GIMP_TOOL
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
name|GIMP_COLOR_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
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
DECL|function|gimp_color_picker_tool_finalize (GObject * object)
name|gimp_color_picker_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorPickerTool
modifier|*
name|picker_tool
init|=
name|GIMP_COLOR_PICKER_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|picker_tool
operator|->
name|dialog
condition|)
name|gimp_color_picker_tool_info_response
argument_list|(
name|NULL
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|picker_tool
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
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
name|gdisp
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
name|HALT
case|:
if|if
condition|(
name|picker_tool
operator|->
name|dialog
condition|)
name|gimp_color_picker_tool_info_response
argument_list|(
name|NULL
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|picker_tool
argument_list|)
expr_stmt|;
break|break;
default|default:
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
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
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
name|gdisp
parameter_list|)
block|{
name|GimpColorPickerOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_COLOR_PICKER_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
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
literal|"add-to-palette"
argument_list|,
operator|!
name|options
operator|->
name|add_to_palette
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
name|GDK_CONTROL_MASK
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
name|GIMP_COLOR_PICK_MODE_NONE
case|:
break|break;
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
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_color_picker_tool_oper_update
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
name|gdisp
parameter_list|)
block|{
name|GimpColorPickerOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_COLOR_PICKER_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
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
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_picked (GimpColorTool * color_tool,GimpColorPickState pick_state,GimpImageType sample_type,GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_picked
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|GimpColorPickState
name|pick_state
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
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
name|color_tool
argument_list|)
decl_stmt|;
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
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|options
operator|=
name|GIMP_COLOR_PICKER_OPTIONS
argument_list|(
name|color_tool
operator|->
name|options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|picker_tool
operator|->
name|dialog
condition|)
name|gimp_color_picker_tool_info_create
argument_list|(
name|picker_tool
argument_list|)
expr_stmt|;
name|gimp_color_picker_tool_info_update
argument_list|(
name|picker_tool
argument_list|,
name|sample_type
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|add_to_palette
condition|)
block|{
name|GimpDialogFactory
modifier|*
name|dialog_factory
decl_stmt|;
name|GdkScreen
modifier|*
name|screen
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|GtkWidget
modifier|*
name|palette_editor
decl_stmt|;
name|GimpData
modifier|*
name|data
decl_stmt|;
name|dialog_factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
argument_list|)
expr_stmt|;
name|screen
operator|=
name|gtk_widget_get_screen
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|dialog_factory
argument_list|,
name|screen
argument_list|,
literal|"gimp-palette-editor"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* don't blink like mad when updating */
if|if
condition|(
name|pick_state
operator|==
name|GIMP_COLOR_PICK_STATE_UPDATE
condition|)
name|gimp_dockable_blink_cancel
argument_list|(
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|palette_editor
operator|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|dockable
argument_list|)
argument_list|)
expr_stmt|;
name|data
operator|=
name|gimp_data_editor_get_data
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|palette_editor
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|data
condition|)
block|{
name|data
operator|=
name|GIMP_DATA
argument_list|(
name|gimp_context_get_palette
argument_list|(
name|user_context
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_editor_set_data
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|palette_editor
argument_list|)
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_palette_editor_pick_color
argument_list|(
name|GIMP_PALETTE_EDITOR
argument_list|(
name|palette_editor
argument_list|)
argument_list|,
name|color
argument_list|,
name|pick_state
argument_list|)
expr_stmt|;
block|}
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
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_FOREGROUND
case|:
name|gimp_context_set_foreground
argument_list|(
name|user_context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_COLOR_PICK_MODE_BACKGROUND
case|:
name|gimp_context_set_background
argument_list|(
name|user_context
argument_list|,
name|color
argument_list|)
expr_stmt|;
break|break;
block|}
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
name|dialog
operator|=
name|gimp_tool_dialog_new
argument_list|(
name|tool
operator|->
name|tool_info
argument_list|,
name|NULL
comment|/* tool->gdisp->shell */
argument_list|,
name|_
argument_list|(
literal|"Color Picker Information"
argument_list|)
argument_list|,
name|GTK_STOCK_CLOSE
argument_list|,
name|GTK_RESPONSE_CLOSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|picker_tool
operator|->
name|dialog
argument_list|)
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
name|dialog
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
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|picker_tool
operator|->
name|dialog
argument_list|)
operator|->
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
DECL|function|gimp_color_picker_tool_info_response (GtkWidget * widget,gint response_id,GimpColorPickerTool * picker_tool)
name|gimp_color_picker_tool_info_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|)
block|{
name|gtk_widget_destroy
argument_list|(
name|picker_tool
operator|->
name|dialog
argument_list|)
expr_stmt|;
name|picker_tool
operator|->
name|dialog
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_picker_tool_info_update (GimpColorPickerTool * picker_tool,GimpImageType sample_type,GimpRGB * color,gint color_index)
name|gimp_color_picker_tool_info_update
parameter_list|(
name|GimpColorPickerTool
modifier|*
name|picker_tool
parameter_list|,
name|GimpImageType
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
name|color_index
parameter_list|)
block|{
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
name|sample_type
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
name|sample_type
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|picker_tool
operator|->
name|dialog
argument_list|)
condition|)
name|gdk_window_show
argument_list|(
name|picker_tool
operator|->
name|dialog
operator|->
name|window
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_show
argument_list|(
name|picker_tool
operator|->
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

