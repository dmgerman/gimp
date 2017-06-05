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
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpspinscale.h"
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
file|"gimpfilteroptions.h"
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
name|gchar
modifier|*
name|gimp_brightness_contrast_tool_get_operation
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gchar
modifier|*
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|description
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|icon_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help_id
parameter_list|,
name|gboolean
modifier|*
name|has_settings
parameter_list|,
name|gchar
modifier|*
modifier|*
name|import_dialog_title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|export_dialog_title
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_tool_dialog
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
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
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpBrightnessContrastTool,gimp_brightness_contrast_tool,GIMP_TYPE_FILTER_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpBrightnessContrastTool
argument_list|,
argument|gimp_brightness_contrast_tool
argument_list|,
argument|GIMP_TYPE_FILTER_TOOL
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
name|GIMP_TYPE_FILTER_OPTIONS
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
name|GIMP_ICON_TOOL_BRIGHTNESS_CONTRAST
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
name|GimpFilterToolClass
modifier|*
name|filter_tool_class
init|=
name|GIMP_FILTER_TOOL_CLASS
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
name|filter_tool_class
operator|->
name|get_operation
operator|=
name|gimp_brightness_contrast_tool_get_operation
expr_stmt|;
name|filter_tool_class
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
condition|)
block|{
return|return
name|FALSE
return|;
block|}
if|if
condition|(
name|gimp_drawable_get_component_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|GIMP_COMPONENT_TYPE_U8
condition|)
block|{
name|gimp_prop_widget_set_factor
argument_list|(
name|bc_tool
operator|->
name|brightness_scale
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|8.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|bc_tool
operator|->
name|contrast_scale
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|8.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_prop_widget_set_factor
argument_list|(
name|bc_tool
operator|->
name|brightness_scale
argument_list|,
literal|0.5
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|bc_tool
operator|->
name|contrast_scale
argument_list|,
literal|0.5
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|3
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
name|gchar
modifier|*
DECL|function|gimp_brightness_contrast_tool_get_operation (GimpFilterTool * filter_tool,gchar ** title,gchar ** description,gchar ** undo_desc,gchar ** icon_name,gchar ** help_id,gboolean * has_settings,gchar ** import_dialog_title,gchar ** export_dialog_title)
name|gimp_brightness_contrast_tool_get_operation
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|,
name|gchar
modifier|*
modifier|*
name|title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|description
parameter_list|,
name|gchar
modifier|*
modifier|*
name|undo_desc
parameter_list|,
name|gchar
modifier|*
modifier|*
name|icon_name
parameter_list|,
name|gchar
modifier|*
modifier|*
name|help_id
parameter_list|,
name|gboolean
modifier|*
name|has_settings
parameter_list|,
name|gchar
modifier|*
modifier|*
name|import_dialog_title
parameter_list|,
name|gchar
modifier|*
modifier|*
name|export_dialog_title
parameter_list|)
block|{
operator|*
name|description
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Adjust Brightness and Contrast"
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|has_settings
operator|=
name|TRUE
expr_stmt|;
operator|*
name|import_dialog_title
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Import Brightness-Contrast settings"
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|export_dialog_title
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Export Brightness-Contrast settings"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
literal|"gimp:brightness-contrast"
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
name|dragging
operator|=
operator|!
name|gimp_filter_tool_on_guide
argument_list|(
name|GIMP_FILTER_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|coords
argument_list|,
name|display
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|bc_tool
operator|->
name|dragging
condition|)
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_press
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|press_type
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gdouble
name|brightness
decl_stmt|;
name|gdouble
name|contrast
decl_stmt|;
name|g_object_get
argument_list|(
name|GIMP_FILTER_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|config
argument_list|,
literal|"brightness"
argument_list|,
operator|&
name|brightness
argument_list|,
literal|"contrast"
argument_list|,
operator|&
name|contrast
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|x
operator|=
name|coords
operator|->
name|x
operator|-
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
name|brightness
operator|*
literal|127.0
expr_stmt|;
name|bc_tool
operator|->
name|dx
operator|=
name|contrast
operator|*
literal|127.0
expr_stmt|;
name|bc_tool
operator|->
name|dy
operator|=
operator|-
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
if|if
condition|(
operator|!
name|bc_tool
operator|->
name|dragging
condition|)
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|button_release
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
else|else
block|{
name|bc_tool
operator|->
name|dragging
operator|=
name|FALSE
expr_stmt|;
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
name|GIMP_FILTER_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
if|if
condition|(
operator|!
name|bc_tool
operator|->
name|dragging
condition|)
block|{
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|motion
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
else|else
block|{
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
name|GIMP_FILTER_TOOL
argument_list|(
name|tool
argument_list|)
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
DECL|function|gimp_brightness_contrast_tool_dialog (GimpFilterTool * filter_tool)
name|gimp_brightness_contrast_tool_dialog
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
init|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|filter_tool
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|main_vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|main_vbox
operator|=
name|gimp_filter_tool_dialog_get_vbox
argument_list|(
name|filter_tool
argument_list|)
expr_stmt|;
comment|/*  Create the brightness scale widget  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"brightness"
argument_list|,
name|_
argument_list|(
literal|"_Brightness"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|brightness_scale
operator|=
name|scale
expr_stmt|;
comment|/*  Create the contrast scale widget  */
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"contrast"
argument_list|,
name|_
argument_list|(
literal|"_Contrast"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|bc_tool
operator|->
name|contrast_scale
operator|=
name|scale
expr_stmt|;
name|button
operator|=
name|gimp_icon_button_new
argument_list|(
name|GIMP_ICON_TOOL_LEVELS
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
name|filter_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_to_levels_callback (GtkWidget * widget,GimpFilterTool * filter_tool)
name|brightness_contrast_to_levels_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpFilterTool
modifier|*
name|filter_tool
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
name|GIMP_BRIGHTNESS_CONTRAST_CONFIG
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_filter_tool_edit_as
argument_list|(
name|filter_tool
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

