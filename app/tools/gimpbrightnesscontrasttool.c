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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrightnesscontrasttool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"image_map.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
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

begin_comment
comment|/*  the brightness-contrast structures  */
end_comment

begin_typedef
DECL|typedef|BrightnessContrastDialog
typedef|typedef
name|struct
name|_BrightnessContrastDialog
name|BrightnessContrastDialog
typedef|;
end_typedef

begin_struct
DECL|struct|_BrightnessContrastDialog
struct|struct
name|_BrightnessContrastDialog
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|gimage_name
name|GtkWidget
modifier|*
name|gimage_name
decl_stmt|;
DECL|member|brightness_data
name|GtkAdjustment
modifier|*
name|brightness_data
decl_stmt|;
DECL|member|contrast_data
name|GtkAdjustment
modifier|*
name|contrast_data
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|image_map
name|ImageMap
modifier|*
name|image_map
decl_stmt|;
DECL|member|brightness
name|gdouble
name|brightness
decl_stmt|;
DECL|member|contrast
name|gdouble
name|contrast
decl_stmt|;
DECL|member|preview
name|gboolean
name|preview
decl_stmt|;
DECL|member|lut
name|GimpLut
modifier|*
name|lut
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

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
name|gimp_brightness_contrast_tool_control
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
name|BrightnessContrastDialog
modifier|*
name|brightness_contrast_dialog_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_dialog_hide
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_update
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
parameter_list|,
name|gint
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_preview
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brightness_contrast_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
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
DECL|variable|brightness_contrast_dialog
specifier|static
name|BrightnessContrastDialog
modifier|*
name|brightness_contrast_dialog
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
DECL|function|gimp_brightness_contrast_tool_register (Gimp * gimp,GimpToolRegisterCallback callback)
name|gimp_brightness_contrast_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_BRIGHTNESS_CONTRAST_TOOL
argument_list|,
name|NULL
argument_list|,
name|FALSE
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
literal|"/Layer/Colors/Brightness-Contrast..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/brightness_contrast.html"
argument_list|,
name|GIMP_STOCK_TOOL_BRIGHTNESS_CONTRAST
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
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
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
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_brightness_contrast_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_brightness_contrast_tool_control
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
if|if
condition|(
operator|!
name|gdisp
condition|)
block|{
name|brightness_contrast_dialog_hide
argument_list|()
expr_stmt|;
return|return;
block|}
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
comment|/*  The brightness-contrast dialog  */
if|if
condition|(
operator|!
name|brightness_contrast_dialog
condition|)
name|brightness_contrast_dialog
operator|=
name|brightness_contrast_dialog_new
argument_list|()
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|brightness_contrast_dialog
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|brightness_contrast_dialog
operator|->
name|shell
argument_list|)
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|brightness_contrast_dialog
operator|->
name|image_map
operator|=
name|image_map_create
argument_list|(
name|gdisp
argument_list|,
name|brightness_contrast_dialog
operator|->
name|drawable
argument_list|)
expr_stmt|;
name|brightness_contrast_update
argument_list|(
name|brightness_contrast_dialog
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brightness_contrast_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_brightness_contrast_tool_control
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
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
name|brightness_contrast_dialog_hide
argument_list|()
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
name|BrightnessContrastDialog
modifier|*
DECL|function|brightness_contrast_dialog_new (void)
name|brightness_contrast_dialog_new
parameter_list|(
name|void
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
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
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|bcd
operator|=
name|g_new
argument_list|(
name|BrightnessContrastDialog
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|bcd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|bcd
operator|->
name|lut
operator|=
name|gimp_lut_new
argument_list|()
expr_stmt|;
comment|/*  The shell and main vbox  */
name|bcd
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Brightness-Contrast"
argument_list|)
argument_list|,
literal|"brightness_contrast"
argument_list|,
name|tool_manager_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|brightness_contrast_cancel_callback
argument_list|,
name|bcd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|brightness_contrast_reset_callback
argument_list|,
name|bcd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|brightness_contrast_ok_callback
argument_list|,
name|bcd
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|bcd
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
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
comment|/*  Create the brightness scale widget  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Brightness:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
argument_list|,
operator|-
literal|127
argument_list|,
literal|127.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|bcd
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
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|slider
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|bcd
operator|->
name|brightness_data
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|spinbutton
argument_list|,
literal|75
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|abox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|abox
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_brightness_adjustment_update
argument_list|)
argument_list|,
name|bcd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
comment|/*  Create the contrast scale widget  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Contrast:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|label
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|data
operator|=
name|gtk_adjustment_new
argument_list|(
literal|0
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
literal|0.0
argument_list|)
expr_stmt|;
name|bcd
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
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|slider
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_scale_set_digits
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|bcd
operator|->
name|contrast_data
argument_list|,
literal|1.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|spinbutton
argument_list|,
literal|75
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|abox
argument_list|)
argument_list|,
name|spinbutton
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|abox
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
name|GTK_SHRINK
operator||
name|GTK_FILL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_contrast_adjustment_update
argument_list|)
argument_list|,
name|bcd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|abox
argument_list|)
expr_stmt|;
comment|/*  Horizontal box for preview toggle button  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
comment|/*  The preview toggle  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|bcd
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brightness_contrast_preview_update
argument_list|)
argument_list|,
name|bcd
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|bcd
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|bcd
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_dialog_hide (void)
name|brightness_contrast_dialog_hide
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|brightness_contrast_dialog
condition|)
name|brightness_contrast_cancel_callback
argument_list|(
name|NULL
argument_list|,
operator|(
name|gpointer
operator|)
name|brightness_contrast_dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_update (BrightnessContrastDialog * bcd,gint update)
name|brightness_contrast_update
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
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
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bcd
operator|->
name|brightness_data
argument_list|,
name|bcd
operator|->
name|brightness
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|update
operator|&
name|CONTRAST
condition|)
block|{
name|gtk_adjustment_set_value
argument_list|(
name|bcd
operator|->
name|contrast_data
argument_list|,
name|bcd
operator|->
name|contrast
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_preview (BrightnessContrastDialog * bcd)
name|brightness_contrast_preview
parameter_list|(
name|BrightnessContrastDialog
modifier|*
name|bcd
parameter_list|)
block|{
if|if
condition|(
operator|!
name|bcd
operator|->
name|image_map
condition|)
block|{
name|g_message
argument_list|(
literal|"brightness_contrast_preview(): No image map"
argument_list|)
expr_stmt|;
return|return;
block|}
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|brightness_contrast_lut_setup
argument_list|(
name|bcd
operator|->
name|lut
argument_list|,
name|bcd
operator|->
name|brightness
operator|/
literal|255.0
argument_list|,
name|bcd
operator|->
name|contrast
operator|/
literal|127.0
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|bcd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|bcd
operator|->
name|lut
argument_list|)
expr_stmt|;
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_reset_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|bcd
operator|->
name|brightness
operator|=
literal|0.0
expr_stmt|;
name|bcd
operator|->
name|contrast
operator|=
literal|0.0
expr_stmt|;
name|brightness_contrast_update
argument_list|(
name|bcd
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_ok_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|bcd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
operator|!
name|bcd
operator|->
name|preview
condition|)
block|{
name|brightness_contrast_lut_setup
argument_list|(
name|bcd
operator|->
name|lut
argument_list|,
name|bcd
operator|->
name|brightness
operator|/
literal|255.0
argument_list|,
name|bcd
operator|->
name|contrast
operator|/
literal|127.0
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|bcd
operator|->
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_apply
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|,
operator|(
name|ImageMapApplyFunc
operator|)
name|gimp_lut_process_2
argument_list|,
operator|(
name|void
operator|*
operator|)
name|bcd
operator|->
name|lut
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|bcd
operator|->
name|image_map
condition|)
name|image_map_commit
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|bcd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_cancel_callback (GtkWidget * widget,gpointer data)
name|brightness_contrast_cancel_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|bcd
operator|->
name|shell
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_abort
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|bcd
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brightness_contrast_preview_update (GtkWidget * widget,gpointer data)
name|brightness_contrast_preview_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
condition|)
block|{
name|bcd
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bcd
operator|->
name|preview
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|image_map
condition|)
block|{
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|the_gimp
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|TRUE
expr_stmt|;
name|image_map_clear
argument_list|(
name|bcd
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|active_tool
operator|->
name|preserve
operator|=
name|FALSE
expr_stmt|;
name|gdisplays_flush
argument_list|()
expr_stmt|;
block|}
block|}
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
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|brightness
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bcd
operator|->
name|brightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
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
name|BrightnessContrastDialog
modifier|*
name|bcd
decl_stmt|;
name|bcd
operator|=
operator|(
name|BrightnessContrastDialog
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|contrast
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|bcd
operator|->
name|contrast
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|bcd
operator|->
name|preview
condition|)
name|brightness_contrast_preview
argument_list|(
name|bcd
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

