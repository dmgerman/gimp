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
file|"base/color-balance.h"
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
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorbalancetool.h"
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
DECL|macro|CYAN_RED
define|#
directive|define
name|CYAN_RED
value|(1<< 0)
end_define

begin_define
DECL|macro|MAGENTA_GREEN
define|#
directive|define
name|MAGENTA_GREEN
value|(1<< 1)
end_define

begin_define
DECL|macro|YELLOW_BLUE
define|#
directive|define
name|YELLOW_BLUE
value|(1<< 2)
end_define

begin_define
DECL|macro|PRESERVE
define|#
directive|define
name|PRESERVE
value|(1<< 3)
end_define

begin_define
DECL|macro|ALL
define|#
directive|define
name|ALL
value|(CYAN_RED | MAGENTA_GREEN | YELLOW_BLUE | PRESERVE)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_tool_class_init
parameter_list|(
name|GimpColorBalanceToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_tool_init
parameter_list|(
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_tool_finalize
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
name|gimp_color_balance_tool_initialize
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
name|gimp_color_balance_tool_map
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
name|gimp_color_balance_tool_dialog
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
name|gimp_color_balance_tool_reset
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
name|color_balance_update
parameter_list|(
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|,
name|gint
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_range_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_range_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_preserve_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_cr_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_mg_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|color_balance_yb_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
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
DECL|function|gimp_color_balance_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_color_balance_tool_register
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
name|GIMP_TYPE_COLOR_BALANCE_TOOL
argument_list|,
name|GIMP_TYPE_IMAGE_MAP_OPTIONS
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|"gimp-color-balance-tool"
argument_list|,
name|_
argument_list|(
literal|"Color Balance"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Adjust color balance"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Color Tools/Color _Balance..."
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_COLOR_BALANCE
argument_list|,
name|GIMP_STOCK_TOOL_COLOR_BALANCE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_color_balance_tool_get_type (void)
name|gimp_color_balance_tool_get_type
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
name|GimpColorBalanceToolClass
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
name|gimp_color_balance_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpColorBalanceTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_color_balance_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_IMAGE_MAP_TOOL
argument_list|,
literal|"GimpColorBalanceTool"
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
DECL|function|gimp_color_balance_tool_class_init (GimpColorBalanceToolClass * klass)
name|gimp_color_balance_tool_class_init
parameter_list|(
name|GimpColorBalanceToolClass
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
name|gimp_color_balance_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_color_balance_tool_initialize
expr_stmt|;
name|image_map_tool_class
operator|->
name|shell_desc
operator|=
name|_
argument_list|(
literal|"Adjust Color Balance"
argument_list|)
expr_stmt|;
name|image_map_tool_class
operator|->
name|map
operator|=
name|gimp_color_balance_tool_map
expr_stmt|;
name|image_map_tool_class
operator|->
name|dialog
operator|=
name|gimp_color_balance_tool_dialog
expr_stmt|;
name|image_map_tool_class
operator|->
name|reset
operator|=
name|gimp_color_balance_tool_reset
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_init (GimpColorBalanceTool * cb_tool)
name|gimp_color_balance_tool_init
parameter_list|(
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|cb_tool
operator|->
name|color_balance
operator|=
name|g_new0
argument_list|(
name|ColorBalance
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|transfer_mode
operator|=
name|GIMP_MIDTONES
expr_stmt|;
name|color_balance_init
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_finalize (GObject * object)
name|gimp_color_balance_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|cb_tool
operator|->
name|color_balance
condition|)
block|{
name|g_free
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|color_balance
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
DECL|function|gimp_color_balance_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_color_balance_tool_initialize
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
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
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
literal|"Color balance operates only on RGB color layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|color_balance_init
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|transfer_mode
operator|=
name|GIMP_MIDTONES
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
name|color_balance_update
argument_list|(
name|cb_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_color_balance_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|color_balance_create_lookup_tables
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
name|gimp_image_map_apply
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|,
name|color_balance
argument_list|,
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**************************/
end_comment

begin_comment
comment|/*  Color Balance dialog  */
end_comment

begin_comment
comment|/**************************/
end_comment

begin_function
specifier|static
name|GtkAdjustment
modifier|*
DECL|function|create_levels_scale (const gchar * left,const gchar * right,GtkWidget * table,gint col)
name|create_levels_scale
parameter_list|(
specifier|const
name|gchar
modifier|*
name|left
parameter_list|,
specifier|const
name|gchar
modifier|*
name|right
parameter_list|,
name|GtkWidget
modifier|*
name|table
parameter_list|,
name|gint
name|col
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkAdjustment
modifier|*
name|adj
decl_stmt|;
name|adj
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|0
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
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|left
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
literal|0.5
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
name|col
argument_list|,
name|col
operator|+
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
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|adj
argument_list|)
expr_stmt|;
name|gtk_scale_set_draw_value
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|FALSE
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
name|gtk_widget_set_size_request
argument_list|(
name|slider
argument_list|,
literal|100
argument_list|,
operator|-
literal|1
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
name|col
argument_list|,
name|col
operator|+
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|slider
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|right
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
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
literal|2
argument_list|,
literal|3
argument_list|,
name|col
argument_list|,
name|col
operator|+
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
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|adj
argument_list|,
literal|1.0
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
name|spinbutton
argument_list|,
literal|3
argument_list|,
literal|4
argument_list|,
name|col
argument_list|,
name|col
operator|+
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
name|gtk_widget_show
argument_list|(
name|spinbutton
argument_list|)
expr_stmt|;
return|return
name|adj
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_color_balance_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
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
name|toggle
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Select Range to Modify"
argument_list|)
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_balance_range_callback
argument_list|)
argument_list|,
name|cb_tool
argument_list|,
operator|&
name|toggle
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
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Modify Selected Range's Color Levels"
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
comment|/*  The table containing sliders  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|4
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
name|cb_tool
operator|->
name|cyan_red_adj
operator|=
name|create_levels_scale
argument_list|(
name|_
argument_list|(
literal|"Cyan"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Red"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|cb_tool
operator|->
name|cyan_red_adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_balance_cr_adjustment_update
argument_list|)
argument_list|,
name|cb_tool
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|magenta_green_adj
operator|=
name|create_levels_scale
argument_list|(
name|_
argument_list|(
literal|"Magenta"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Green"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|cb_tool
operator|->
name|magenta_green_adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_balance_mg_adjustment_update
argument_list|)
argument_list|,
name|cb_tool
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|yellow_blue_adj
operator|=
name|create_levels_scale
argument_list|(
name|_
argument_list|(
literal|"Yellow"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Blue"
argument_list|)
argument_list|,
name|table
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|cb_tool
operator|->
name|yellow_blue_adj
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_balance_yb_adjustment_update
argument_list|)
argument_list|,
name|cb_tool
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
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
name|button
operator|=
name|gtk_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"R_eset Range"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|color_balance_range_reset_callback
argument_list|)
argument_list|,
name|cb_tool
argument_list|)
expr_stmt|;
name|cb_tool
operator|->
name|preserve_toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"Preserve _Luminosity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|cb_tool
operator|->
name|preserve_toggle
argument_list|)
argument_list|,
name|cb_tool
operator|->
name|color_balance
operator|->
name|preserve_luminosity
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|image_map_tool
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|cb_tool
operator|->
name|preserve_toggle
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
name|cb_tool
operator|->
name|preserve_toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|cb_tool
operator|->
name|preserve_toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|color_balance_preserve_update
argument_list|)
argument_list|,
name|cb_tool
argument_list|)
expr_stmt|;
comment|/*  set range after everything is in place  */
name|gimp_int_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|cb_tool
operator|->
name|transfer_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_color_balance_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|color_balance_init
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|)
expr_stmt|;
name|color_balance_update
argument_list|(
name|cb_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_update (GimpColorBalanceTool * cb_tool,gint update)
name|color_balance_update
parameter_list|(
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|,
name|gint
name|update
parameter_list|)
block|{
name|GimpTransferMode
name|tm
decl_stmt|;
name|tm
operator|=
name|cb_tool
operator|->
name|transfer_mode
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|CYAN_RED
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|cb_tool
operator|->
name|cyan_red_adj
argument_list|,
name|cb_tool
operator|->
name|color_balance
operator|->
name|cyan_red
index|[
name|tm
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|MAGENTA_GREEN
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|cb_tool
operator|->
name|magenta_green_adj
argument_list|,
name|cb_tool
operator|->
name|color_balance
operator|->
name|magenta_green
index|[
name|tm
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|YELLOW_BLUE
condition|)
name|gtk_adjustment_set_value
argument_list|(
name|cb_tool
operator|->
name|yellow_blue_adj
argument_list|,
name|cb_tool
operator|->
name|color_balance
operator|->
name|yellow_blue
index|[
name|tm
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|update
operator|&
name|PRESERVE
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|cb_tool
operator|->
name|preserve_toggle
argument_list|)
argument_list|,
name|cb_tool
operator|->
name|color_balance
operator|->
name|preserve_luminosity
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_range_callback (GtkWidget * widget,GimpColorBalanceTool * cb_tool)
name|color_balance_range_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|gimp_radio_button_update
argument_list|(
name|widget
argument_list|,
operator|&
name|cb_tool
operator|->
name|transfer_mode
argument_list|)
expr_stmt|;
name|color_balance_update
argument_list|(
name|cb_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_range_reset_callback (GtkWidget * widget,GimpColorBalanceTool * cb_tool)
name|color_balance_range_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|color_balance_range_reset
argument_list|(
name|cb_tool
operator|->
name|color_balance
argument_list|,
name|cb_tool
operator|->
name|transfer_mode
argument_list|)
expr_stmt|;
name|color_balance_update
argument_list|(
name|cb_tool
argument_list|,
name|ALL
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|cb_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_preserve_update (GtkWidget * widget,GimpColorBalanceTool * cb_tool)
name|color_balance_preserve_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|gboolean
name|active
decl_stmt|;
name|active
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
if|if
condition|(
name|cb_tool
operator|->
name|color_balance
operator|->
name|preserve_luminosity
operator|!=
name|active
condition|)
block|{
name|cb_tool
operator|->
name|color_balance
operator|->
name|preserve_luminosity
operator|=
name|active
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|cb_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_cr_adjustment_update (GtkAdjustment * adjustment,GimpColorBalanceTool * cb_tool)
name|color_balance_cr_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|GimpTransferMode
name|tm
decl_stmt|;
name|tm
operator|=
name|cb_tool
operator|->
name|transfer_mode
expr_stmt|;
if|if
condition|(
name|cb_tool
operator|->
name|color_balance
operator|->
name|cyan_red
index|[
name|tm
index|]
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|cb_tool
operator|->
name|color_balance
operator|->
name|cyan_red
index|[
name|tm
index|]
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|cb_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_mg_adjustment_update (GtkAdjustment * adjustment,GimpColorBalanceTool * cb_tool)
name|color_balance_mg_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|GimpTransferMode
name|tm
decl_stmt|;
name|tm
operator|=
name|cb_tool
operator|->
name|transfer_mode
expr_stmt|;
if|if
condition|(
name|cb_tool
operator|->
name|color_balance
operator|->
name|magenta_green
index|[
name|tm
index|]
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|cb_tool
operator|->
name|color_balance
operator|->
name|magenta_green
index|[
name|tm
index|]
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|cb_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_yb_adjustment_update (GtkAdjustment * adjustment,GimpColorBalanceTool * cb_tool)
name|color_balance_yb_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpColorBalanceTool
modifier|*
name|cb_tool
parameter_list|)
block|{
name|GimpTransferMode
name|tm
decl_stmt|;
name|tm
operator|=
name|cb_tool
operator|->
name|transfer_mode
expr_stmt|;
if|if
condition|(
name|cb_tool
operator|->
name|color_balance
operator|->
name|yellow_blue
index|[
name|tm
index|]
operator|!=
name|adjustment
operator|->
name|value
condition|)
block|{
name|cb_tool
operator|->
name|color_balance
operator|->
name|yellow_blue
index|[
name|tm
index|]
operator|=
name|adjustment
operator|->
name|value
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|cb_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

