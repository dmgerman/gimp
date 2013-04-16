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
file|<string.h>
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
file|"operations/gimpbrightnesscontrastconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimperror.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrasttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemapoptions.h"
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

begin_define
DECL|macro|SLIDER_WIDTH
define|#
directive|define
name|SLIDER_WIDTH
value|200
end_define

begin_function_decl
specifier|static
name|gboolean
name|gimp_brightness_contrast_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_tool_button_press
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
name|gimp_brightness_contrast_tool_button_release
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
name|gimp_brightness_contrast_tool_motion
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
name|GeglNode
modifier|*
name|gimp_brightness_contrast_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_brightness_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_contrast_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_to_levels_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrightnessContrastTool,gimp_brightness_contrast_tool,GIMP_TYPE_IMAGE_MAP_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrightnessContrastTool
argument_list|,
argument|gimp_brightness_contrast_tool
argument_list|,
argument|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_brightness_contrast_tool_parent_class
end_define

begin_function
name|void
name|gimp_brightness_contrast_tool_register
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
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-brightness-contrast-tool"
argument_list|,
name|_
argument_list|(
literal|"Brightness-Contrast"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Brightness/Contrast Tool: Adjust brightness and contrast"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"B_rightness-Contrast..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_BRIGHTNESS_CONTRAST
argument_list|,
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_class_init (GimpBrightnessContrastToolClass * klass)
name|gimp_brightness_contrast_tool_class_init
parameter_list|(
name|GimpBrightnessContrastToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_brightness_contrast_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_brightness_contrast_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_brightness_contrast_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_brightness_contrast_tool_motion
expr_stmt|;
name|im_tool_class
operator|->
name|dialog_desc
operator|=
name|_
argument_list|(
literal|"Adjust Brightness and Contrast"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|settings_name
operator|=
literal|"brightness-contrast"
expr_stmt|;
name|im_tool_class
operator|->
name|import_dialog_title
operator|=
name|_
argument_list|(
literal|"Import Brightness-Contrast settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|export_dialog_title
operator|=
name|_
argument_list|(
literal|"Export Brightness-Contrast settings"
argument_list|)
expr_stmt|;
name|im_tool_class
operator|->
name|get_operation
operator|=
name|gimp_brightness_contrast_tool_get_operation
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_brightness_contrast_tool_dialog
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_init (GimpBrightnessContrastTool * bc_tool)
name|gimp_brightness_contrast_tool_init
parameter_list|(
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brightness_contrast_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_brightness_contrast_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
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
name|display
argument_list|)
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
init|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|drawable
condition|)
return|return
name|FALSE
return|;
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_brightness_contrast_tool_get_operation (GimpImageMapTool * im_tool,GObject ** config,gchar ** undo_desc)
name|gimp_brightness_contrast_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|,
name|GObject
modifier|*
modifier|*
name|config
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|im_tool
argument_list|)
decl_stmt|;
name|bc_tool
operator|->
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|,
literal|"notify"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_config_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|bc_tool
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
operator|*
name|config
operator|=
name|G_OBJECT
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|)
expr_stmt|;
return|return
name|gegl_node_new_child
argument_list|(
name|NULL
argument_list|,
literal|"operation"
argument_list|,
literal|"gimp:brightness-contrast"
argument_list|,
literal|"config"
argument_list|,
name|bc_tool
operator|->
name|config
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_brightness_contrast_tool_button_press
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
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|bc_tool
operator|->
name|x
operator|=
name|coords
operator|->
name|x
operator|-
name|bc_tool
operator|->
name|config
operator|->
name|contrast
operator|*
literal|127.0
expr_stmt|;
name|bc_tool
operator|->
name|y
operator|=
name|coords
operator|->
name|y
operator|+
name|bc_tool
operator|->
name|config
operator|->
name|brightness
operator|*
literal|127.0
expr_stmt|;
name|bc_tool
operator|->
name|dx
operator|=
name|bc_tool
operator|->
name|config
operator|->
name|contrast
operator|*
literal|127.0
expr_stmt|;
name|bc_tool
operator|->
name|dy
operator|=
operator|-
name|bc_tool
operator|->
name|config
operator|->
name|brightness
operator|*
literal|127.0
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_brightness_contrast_tool_button_release
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
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpImageMapTool
modifier|*
name|im_tool
init|=
name|GIMP_IMAGE_MAP_TOOL
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
if|if
condition|(
name|bc_tool
operator|->
name|dx
operator|==
literal|0
operator|&&
name|bc_tool
operator|->
name|dy
operator|==
literal|0
condition|)
return|return;
if|if
condition|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
name|gimp_config_reset
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|im_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_brightness_contrast_tool_motion
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
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|bc_tool
operator|->
name|dx
operator|=
operator|(
name|coords
operator|->
name|x
operator|-
name|bc_tool
operator|->
name|x
operator|)
expr_stmt|;
name|bc_tool
operator|->
name|dy
operator|=
operator|-
operator|(
name|coords
operator|->
name|y
operator|-
name|bc_tool
operator|->
name|y
operator|)
expr_stmt|;
name|g_object_set
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|,
literal|"brightness"
argument_list|,
name|CLAMP
argument_list|(
name|bc_tool
operator|->
name|dy
argument_list|,
operator|-
literal|127.0
argument_list|,
literal|127.0
argument_list|)
operator|/
literal|127.0
argument_list|,
literal|"contrast"
argument_list|,
name|CLAMP
argument_list|(
name|bc_tool
operator|->
name|dx
argument_list|,
operator|-
literal|127.0
argument_list|,
literal|127.0
argument_list|)
operator|/
literal|127.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/********************************/
end_comment

begin_comment
comment|/*  Brightness Contrast dialog  */
end_comment

begin_comment
comment|/********************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_brightness_contrast_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
decl_stmt|;
name|GimpBrightnessContrastConfig
modifier|*
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|config
operator|=
name|bc_tool
operator|->
name|config
expr_stmt|;
name|main_vbox
operator|=
name|gimp_image_map_tool_dialog_get_vbox
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  The table containing sliders  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
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
comment|/*  Create the brightness scale widget  */
name|data
operator|=
name|gimp_scale_entry_new
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
literal|"_Brightness:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
name|config
operator|->
name|brightness
operator|*
literal|127.0
argument_list|,
operator|-
literal|127.0
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|brightness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_brightness_changed
argument_list|)
argument_list|,
name|bc_tool
argument_list|)
expr_stmt|;
comment|/*  Create the contrast scale widget  */
name|data
operator|=
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Con_trast:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
name|config
operator|->
name|contrast
operator|*
literal|127.0
argument_list|,
operator|-
literal|127.0
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|contrast_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_contrast_changed
argument_list|)
argument_list|,
name|bc_tool
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_stock_button_new
argument_list|(
name|GIMP_STOCK_TOOL_LEVELS
argument_list|,
name|_
argument_list|(
literal|"Edit these Settings as Levels"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_to_levels_callback
argument_list|)
argument_list|,
name|bc_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_config_notify (GObject * object,GParamSpec * pspec,GimpBrightnessContrastTool * bc_tool)
name|brightness_contrast_config_notify
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{
name|GimpBrightnessContrastConfig
modifier|*
name|config
decl_stmt|;
name|config
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|bc_tool
operator|->
name|brightness_data
condition|)
return|return;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"brightness"
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bc_tool
operator|->
name|brightness_data
argument_list|,
name|config
operator|->
name|brightness
operator|*
literal|127.0
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|pspec
operator|->
name|name
argument_list|,
literal|"contrast"
argument_list|)
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bc_tool
operator|->
name|contrast_data
argument_list|,
name|config
operator|->
name|contrast
operator|*
literal|127.0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_brightness_changed (GtkAdjustment * adjustment,GimpBrightnessContrastTool * bc_tool)
name|brightness_contrast_brightness_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{
name|GimpBrightnessContrastConfig
modifier|*
name|config
init|=
name|bc_tool
operator|->
name|config
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|value
operator|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|127.0
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|brightness
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"brightness"
argument_list|,
name|value
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
DECL|function|brightness_contrast_contrast_changed (GtkAdjustment * adjustment,GimpBrightnessContrastTool * bc_tool)
name|brightness_contrast_contrast_changed
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{
name|GimpBrightnessContrastConfig
modifier|*
name|config
init|=
name|bc_tool
operator|->
name|config
decl_stmt|;
name|gdouble
name|value
decl_stmt|;
name|value
operator|=
name|gtk_adjustment_get_value
argument_list|(
name|adjustment
argument_list|)
operator|/
literal|127.0
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|contrast
operator|!=
name|value
condition|)
block|{
name|g_object_set
argument_list|(
name|config
argument_list|,
literal|"contrast"
argument_list|,
name|value
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
DECL|function|brightness_contrast_to_levels_callback (GtkWidget * widget,GimpBrightnessContrastTool * bc_tool)
name|brightness_contrast_to_levels_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{
name|GimpLevelsConfig
modifier|*
name|levels
decl_stmt|;
name|levels
operator|=
name|gimp_brightness_contrast_config_to_levels_config
argument_list|(
name|bc_tool
operator|->
name|config
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_edit_as
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|bc_tool
argument_list|)
argument_list|,
literal|"gimp-levels-tool"
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|levels
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|levels
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

