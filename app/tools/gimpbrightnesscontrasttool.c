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
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SLIDER_WIDTH
define|#
directive|define
name|SLIDER_WIDTH
value|200
end_define

begin_define
DECL|macro|BRIGHTNESS
define|#
directive|define
name|BRIGHTNESS
value|0x1
end_define

begin_define
DECL|macro|CONTRAST
define|#
directive|define
name|CONTRAST
value|0x2
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|(BRIGHTNESS | CONTRAST)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_tool_class_init
parameter_list|(
name|GimpBrightnessContrastToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brightness_contrast_tool_init
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
name|void
name|gimp_brightness_contrast_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
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
name|brightness_contrast_update
parameter_list|(
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|,
name|gint
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_brightness_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_contrast_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpImageMapToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|void
DECL|function|gimp_brightness_contrast_tool_register (GimpToolRegisterCallback callback,gpointer data)
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
name|G_TYPE_NONE
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
literal|"Adjust brightness and contrast"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Color Tools/Brightness-Contrast..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/brightness_contrast.html"
argument_list|,
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_brightness_contrast_tool_get_type (void)
name|gimp_brightness_contrast_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
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
name|GimpBrightnessContrastToolClass
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
name|gimp_brightness_contrast_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpBrightnessContrastTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_brightness_contrast_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpBrightnessContrastTool"
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
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpImageMapToolClass
modifier|*
name|image_map_tool_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|image_map_tool_class
operator|=
name|GIMP_IMAGE_MAP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
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
name|image_map_tool_class
operator|->
name|map
operator|=
name|gimp_brightness_contrast_tool_map
expr_stmt|;
name|image_map_tool_class
operator|->
name|dialog
operator|=
name|gimp_brightness_contrast_tool_dialog
expr_stmt|;
name|image_map_tool_class
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
name|image_map_tool
decl_stmt|;
name|image_map_tool
operator|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|bc_tool
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|shell_identifier
operator|=
literal|"gimp-brightness-contrast-tool-dialog"
expr_stmt|;
name|image_map_tool
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Adjust Brightness and Contrast"
argument_list|)
expr_stmt|;
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
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
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
name|void
DECL|function|gimp_brightness_contrast_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_brightness_contrast_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_drawable_is_indexed
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Brightness-Contrast does not operate on indexed drawables."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
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
name|gdisp
argument_list|)
expr_stmt|;
name|brightness_contrast_update
argument_list|(
name|bc_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_brightness_contrast_tool_map
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
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
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
name|image_map_tool
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_map_apply
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|,
operator|(
name|GimpImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
name|bc_tool
operator|->
name|lut
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
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
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
name|image_map_tool
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
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_brightness_adjustment_update
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
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_contrast_adjustment_update
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
DECL|function|gimp_brightness_contrast_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_brightness_contrast_tool_reset
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
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
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
name|brightness_contrast_update
argument_list|(
name|bc_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_update (GimpBrightnessContrastTool * bc_tool,gint update)
name|brightness_contrast_update
parameter_list|(
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
parameter_list|,
name|gint
name|update
parameter_list|)
block|{
if|if
condition|(
name|update
operator|&
name|BRIGHTNESS
condition|)
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
if|if
condition|(
name|update
operator|&
name|CONTRAST
condition|)
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
DECL|function|brightness_contrast_brightness_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|brightness_contrast_brightness_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
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
DECL|function|brightness_contrast_contrast_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|brightness_contrast_contrast_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpBrightnessContrastTool
modifier|*
name|bc_tool
decl_stmt|;
name|bc_tool
operator|=
name|GIMP_BRIGHTNESS_CONTRAST_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
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

