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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"base/colorize.h"
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
file|"gimpcolorizetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemapoptions.h"
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
DECL|macro|DA_WIDTH
define|#
directive|define
name|DA_WIDTH
value|40
end_define

begin_define
DECL|macro|DA_HEIGHT
define|#
directive|define
name|DA_HEIGHT
value|20
end_define

begin_define
DECL|macro|HUE_SLIDER
define|#
directive|define
name|HUE_SLIDER
value|(1<< 0)
end_define

begin_define
DECL|macro|SATURATION_SLIDER
define|#
directive|define
name|SATURATION_SLIDER
value|(1<< 1)
end_define

begin_define
DECL|macro|LIGHTNESS_SLIDER
define|#
directive|define
name|LIGHTNESS_SLIDER
value|(1<< 2)
end_define

begin_define
DECL|macro|DRAW
define|#
directive|define
name|DRAW
value|(1<< 3)
end_define

begin_define
DECL|macro|SLIDERS
define|#
directive|define
name|SLIDERS
value|(HUE_SLIDER | LIGHTNESS_SLIDER | SATURATION_SLIDER)
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|(SLIDERS | DRAW)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_class_init
parameter_list|(
name|GimpColorizeToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_init
parameter_list|(
name|GimpColorizeTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_colorize_tool_finalize
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
name|gimp_colorize_tool_initialize
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
name|gimp_colorize_tool_map
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
name|gimp_colorize_tool_dialog
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
name|gimp_colorize_tool_reset
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
name|colorize_update
parameter_list|(
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|,
name|gint
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_hue_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_saturation_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|colorize_lightness_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  private variables  */
end_comment

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
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_colorize_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_colorize_tool_register
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
name|GIMP_TYPE_COLORIZE_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-colorize-tool"
argument_list|,
name|_
argument_list|(
literal|"Colorize"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Colorize the image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Color Tools/Colori_ze..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_COLORIZE
argument_list|,
name|GIMP_STOCK_TOOL_COLORIZE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_colorize_tool_get_type (void)
name|gimp_colorize_tool_get_type
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
name|GimpColorizeToolClass
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
name|gimp_colorize_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorizeTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_colorize_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpColorizeTool"
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_class_init (GimpColorizeToolClass * klass)
name|gimp_colorize_tool_class_init
parameter_list|(
name|GimpColorizeToolClass
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
name|gimp_colorize_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_colorize_tool_initialize
expr_stmt|;
name|image_map_tool_class
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Colorize the Image"
argument_list|)
expr_stmt|;
name|image_map_tool_class
operator|->
name|map
operator|=
name|gimp_colorize_tool_map
expr_stmt|;
name|image_map_tool_class
operator|->
name|dialog
operator|=
name|gimp_colorize_tool_dialog
expr_stmt|;
name|image_map_tool_class
operator|->
name|reset
operator|=
name|gimp_colorize_tool_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_init (GimpColorizeTool * col_tool)
name|gimp_colorize_tool_init
parameter_list|(
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
name|col_tool
operator|->
name|colorize
operator|=
name|g_new0
argument_list|(
name|Colorize
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|colorize_init
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_finalize (GObject * object)
name|gimp_colorize_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|col_tool
operator|->
name|colorize
condition|)
block|{
name|g_free
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
name|col_tool
operator|->
name|colorize
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
DECL|function|gimp_colorize_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_colorize_tool_initialize
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
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
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
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
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
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Colorize operates only on RGB color layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|colorize_init
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
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
name|colorize_update
argument_list|(
name|col_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_colorize_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|gimp_image_map_apply
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|,
operator|(
name|GimpImageMapApplyFunc
operator|)
name|colorize
argument_list|,
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/***************************/
end_comment

begin_comment
comment|/*  Hue-Saturation dialog  */
end_comment

begin_comment
comment|/***************************/
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_colorize_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|image_map_tool
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
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkObject
modifier|*
name|data
decl_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Select Color"
argument_list|)
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
name|frame
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
name|frame
argument_list|)
expr_stmt|;
comment|/*  The table containing sliders  */
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
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
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
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  Create the hue scale widget  */
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
literal|"_Hue:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|360.0
argument_list|,
literal|1.0
argument_list|,
literal|15.0
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
name|col_tool
operator|->
name|hue_data
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
name|colorize_hue_adj_update
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
comment|/*  Create the saturation scale widget  */
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
literal|"_Saturation:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
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
name|col_tool
operator|->
name|saturation_data
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
name|col_tool
operator|->
name|saturation_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|colorize_saturation_adj_update
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
comment|/*  Create the lightness scale widget  */
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
literal|2
argument_list|,
name|_
argument_list|(
literal|"_Lightness:"
argument_list|)
argument_list|,
name|SLIDER_WIDTH
argument_list|,
operator|-
literal|1
argument_list|,
literal|0.0
argument_list|,
operator|-
literal|100.0
argument_list|,
literal|100.0
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
name|col_tool
operator|->
name|lightness_data
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
name|colorize_lightness_adj_update
argument_list|)
argument_list|,
name|col_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_colorize_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_colorize_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorizeTool
modifier|*
name|col_tool
init|=
name|GIMP_COLORIZE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|colorize_init
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
name|colorize_update
argument_list|(
name|col_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_update (GimpColorizeTool * col_tool,gint update)
name|colorize_update
parameter_list|(
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|,
name|gint
name|update
parameter_list|)
block|{
name|colorize_calculate
argument_list|(
name|col_tool
operator|->
name|colorize
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|HUE_SLIDER
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|col_tool
operator|->
name|hue_data
argument_list|)
argument_list|,
name|col_tool
operator|->
name|colorize
operator|->
name|hue
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|SATURATION_SLIDER
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|col_tool
operator|->
name|saturation_data
argument_list|)
argument_list|,
name|col_tool
operator|->
name|colorize
operator|->
name|saturation
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|LIGHTNESS_SLIDER
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|col_tool
operator|->
name|lightness_data
argument_list|)
argument_list|,
name|col_tool
operator|->
name|colorize
operator|->
name|lightness
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_hue_adj_update (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_hue_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
if|if
condition|(
name|col_tool
operator|->
name|colorize
operator|->
name|hue
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|col_tool
operator|->
name|colorize
operator|->
name|hue
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|colorize_update
argument_list|(
name|col_tool
argument_list|,
name|DRAW
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|col_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_saturation_adj_update (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_saturation_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
if|if
condition|(
name|col_tool
operator|->
name|colorize
operator|->
name|saturation
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|col_tool
operator|->
name|colorize
operator|->
name|saturation
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|colorize_update
argument_list|(
name|col_tool
argument_list|,
name|DRAW
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|col_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|colorize_lightness_adj_update (GtkAdjustment * adjustment,GimpColorizeTool * col_tool)
name|colorize_lightness_adj_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorizeTool
modifier|*
name|col_tool
parameter_list|)
block|{
if|if
condition|(
name|col_tool
operator|->
name|colorize
operator|->
name|lightness
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|col_tool
operator|->
name|colorize
operator|->
name|lightness
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|colorize_update
argument_list|(
name|col_tool
argument_list|,
name|DRAW
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|col_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

