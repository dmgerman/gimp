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
file|"base/gimplut.h"
end_include

begin_include
include|#
directive|include
file|"base/lut-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
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
file|"core/gimpimagemap.h"
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
name|void
name|gimp_brightness_contrast_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

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
name|gimp_brightness_contrast_tool_button_release
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
name|gimp_brightness_contrast_tool_motion
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
name|GeglNode
modifier|*
name|gimp_brightness_contrast_tool_get_operation
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
name|gimp_brightness_contrast_tool_map
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
name|gimp_brightness_contrast_tool_reset
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
name|brightness_contrast_update_sliders
parameter_list|(
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
name|GimpImageMapToolClass
modifier|*
name|im_tool_class
init|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_brightness_contrast_tool_finalize
expr_stmt|;
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
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Adjust Brightness and Contrast"
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
name|map
operator|=
name|gimp_brightness_contrast_tool_map
expr_stmt|;
name|im_tool_class
operator|->
name|dialog
operator|=
name|gimp_brightness_contrast_tool_dialog
expr_stmt|;
name|im_tool_class
operator|->
name|reset
operator|=
name|gimp_brightness_contrast_tool_reset
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
block|{
name|GimpImageMapTool
modifier|*
name|im_tool
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|bc_tool
argument_list|)
decl_stmt|;
name|bc_tool
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|bc_tool
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|bc_tool
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
name|im_tool
operator|->
name|apply_func
operator|=
operator|(
name|GimpImageMapApplyFunc
operator|)
name|gimp_lut_process
expr_stmt|;
name|im_tool
operator|->
name|apply_data
operator|=
name|bc_tool
operator|->
name|lut
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_finalize (GObject * object)
name|gimp_brightness_contrast_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|bc_tool
operator|->
name|lut
condition|)
block|{
name|gimp_lut_free
argument_list|(
name|bc_tool
operator|->
name|lut
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|lut
operator|=
name|NULL
expr_stmt|;
block|}
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
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|display
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
name|FALSE
return|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Brightness-Contrast does not operate on indexed layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|bc_tool
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|bc_tool
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
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
expr_stmt|;
name|brightness_contrast_update_sliders
argument_list|(
name|bc_tool
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|GeglNode
modifier|*
DECL|function|gimp_brightness_contrast_tool_get_operation (GimpImageMapTool * im_tool)
name|gimp_brightness_contrast_tool_get_operation
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GEGL_TYPE_NODE
argument_list|,
literal|"operation"
argument_list|,
literal|"brightness-contrast"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_map (GimpImageMapTool * im_tool)
name|gimp_brightness_contrast_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
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
name|gdouble
name|brightness
decl_stmt|;
name|gdouble
name|contrast
decl_stmt|;
name|brightness
operator|=
name|bc_tool
operator|->
name|brightness
operator|/
literal|256.0
expr_stmt|;
name|contrast
operator|=
operator|(
name|bc_tool
operator|->
name|contrast
operator|<
literal|0
condition|?
operator|(
name|bc_tool
operator|->
name|contrast
operator|+
literal|127.0
operator|)
operator|/
literal|127.0
else|:
name|bc_tool
operator|->
name|contrast
operator|*
literal|4.0
operator|/
literal|127.0
operator|+
literal|1
operator|)
expr_stmt|;
name|gegl_node_set
argument_list|(
name|im_tool
operator|->
name|operation
argument_list|,
literal|"brightness"
argument_list|,
name|brightness
argument_list|,
literal|"contrast"
argument_list|,
name|contrast
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|brightness_contrast_lut_setup
argument_list|(
name|bc_tool
operator|->
name|lut
argument_list|,
name|bc_tool
operator|->
name|brightness
operator|/
literal|255.0
argument_list|,
name|bc_tool
operator|->
name|contrast
operator|/
literal|127.0
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|im_tool
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_brightness_contrast_tool_button_press
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
name|contrast
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
name|brightness
expr_stmt|;
name|bc_tool
operator|->
name|dx
operator|=
name|bc_tool
operator|->
name|contrast
expr_stmt|;
name|bc_tool
operator|->
name|dy
operator|=
operator|-
name|bc_tool
operator|->
name|brightness
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
DECL|function|gimp_brightness_contrast_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_brightness_contrast_tool_button_release
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
name|gimp_brightness_contrast_tool_reset
argument_list|(
name|im_tool
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
DECL|function|gimp_brightness_contrast_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_brightness_contrast_tool_motion
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
name|gimp_tool_control_pause
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
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
name|bc_tool
operator|->
name|brightness
operator|=
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
expr_stmt|;
name|bc_tool
operator|->
name|contrast
operator|=
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
expr_stmt|;
name|brightness_contrast_update_sliders
argument_list|(
name|bc_tool
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|im_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_resume
argument_list|(
name|tool
operator|->
name|control
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
DECL|function|gimp_brightness_contrast_tool_dialog (GimpImageMapTool * im_tool)
name|gimp_brightness_contrast_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
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
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
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
name|im_tool
operator|->
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
name|bc_tool
operator|->
name|brightness
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
name|slider
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
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
name|bc_tool
operator|->
name|contrast
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
name|slider
operator|=
name|GIMP_SCALE_ENTRY_SCALE
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_CONTINUOUS
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_reset (GimpImageMapTool * im_tool)
name|gimp_brightness_contrast_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|im_tool
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
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|bc_tool
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_update_sliders
argument_list|(
name|bc_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_update_sliders (GimpBrightnessContrastTool * bc_tool)
name|brightness_contrast_update_sliders
parameter_list|(
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bc_tool
operator|->
name|brightness_data
argument_list|,
name|bc_tool
operator|->
name|brightness
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|bc_tool
operator|->
name|contrast_data
argument_list|,
name|bc_tool
operator|->
name|contrast
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|bc_tool
operator|->
name|brightness
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bc_tool
operator|->
name|brightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|bc_tool
argument_list|)
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
if|if
condition|(
name|bc_tool
operator|->
name|contrast
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bc_tool
operator|->
name|contrast
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|bc_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

