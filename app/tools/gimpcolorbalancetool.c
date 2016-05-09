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
file|"operations/gimpcolorbalanceconfig.h"
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
file|"gimpfilteroptions.h"
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
name|gboolean
name|gimp_color_balance_tool_initialize
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
name|gchar
modifier|*
name|gimp_color_balance_tool_get_operation
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_balance_tool_dialog
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
name|gimp_color_balance_tool_reset
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
name|color_balance_range_reset_callback
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
DECL|function|G_DEFINE_TYPE (GimpColorBalanceTool,gimp_color_balance_tool,GIMP_TYPE_FILTER_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorBalanceTool
argument_list|,
argument|gimp_color_balance_tool
argument_list|,
argument|GIMP_TYPE_FILTER_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_balance_tool_parent_class
end_define

begin_function
name|void
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
name|GIMP_TYPE_FILTER_OPTIONS
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
literal|"Color Balance Tool: Adjust color distribution"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Color _Balance..."
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
name|gimp_color_balance_tool_initialize
expr_stmt|;
name|filter_tool_class
operator|->
name|settings_name
operator|=
literal|"color-balance"
expr_stmt|;
name|filter_tool_class
operator|->
name|import_dialog_title
operator|=
name|_
argument_list|(
literal|"Import Color Balance Settings"
argument_list|)
expr_stmt|;
name|filter_tool_class
operator|->
name|export_dialog_title
operator|=
name|_
argument_list|(
literal|"Export Color Balance Settings"
argument_list|)
expr_stmt|;
name|filter_tool_class
operator|->
name|get_operation
operator|=
name|gimp_color_balance_tool_get_operation
expr_stmt|;
name|filter_tool_class
operator|->
name|dialog
operator|=
name|gimp_color_balance_tool_dialog
expr_stmt|;
name|filter_tool_class
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
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_color_balance_tool_initialize (GimpTool * tool,GimpDisplay * display,GError ** error)
name|gimp_color_balance_tool_initialize
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
if|if
condition|(
operator|!
name|gimp_drawable_is_rgb
argument_list|(
name|drawable
argument_list|)
condition|)
block|{
name|g_set_error_literal
argument_list|(
name|error
argument_list|,
name|GIMP_ERROR
argument_list|,
name|GIMP_FAILED
argument_list|,
name|_
argument_list|(
literal|"Color Balance operates only on RGB color layers."
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
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
name|gchar
modifier|*
DECL|function|gimp_color_balance_tool_get_operation (GimpFilterTool * filter_tool,gchar ** title,gchar ** description,gchar ** undo_desc,gchar ** icon_name,gchar ** help_id)
name|gimp_color_balance_tool_get_operation
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
parameter_list|)
block|{
operator|*
name|description
operator|=
name|g_strdup
argument_list|(
name|_
argument_list|(
literal|"Adjust Color Balance"
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|g_strdup
argument_list|(
literal|"gimp:color-balance"
argument_list|)
return|;
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
name|void
DECL|function|create_levels_scale (GObject * config,const gchar * property_name,const gchar * left,const gchar * right,GtkWidget * table,gint col)
name|create_levels_scale
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
specifier|const
name|gchar
modifier|*
name|property_name
parameter_list|,
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
name|scale
decl_stmt|;
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
name|property_name
argument_list|,
name|NULL
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_spin_scale_set_label
argument_list|(
name|GIMP_SPIN_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_prop_widget_set_factor
argument_list|(
name|scale
argument_list|,
literal|100.0
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
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
name|scale
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
name|scale
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_dialog (GimpFilterTool * filter_tool)
name|gimp_color_balance_tool_dialog
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
block|{
name|GimpColorBalanceTool
modifier|*
name|cb_tool
init|=
name|GIMP_COLOR_BALANCE_TOOL
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|main_vbox
operator|=
name|gimp_filter_tool_dialog_get_vbox
argument_list|(
name|filter_tool
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"range"
argument_list|,
name|_
argument_list|(
literal|"Select Range to Adjust"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
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
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Adjust Color Levels"
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
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
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
name|create_levels_scale
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"cyan-red"
argument_list|,
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
name|create_levels_scale
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"magenta-green"
argument_list|,
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
name|create_levels_scale
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"yellow-blue"
argument_list|,
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"preserve-luminosity"
argument_list|,
name|_
argument_list|(
literal|"Preserve _luminosity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_balance_tool_reset (GimpFilterTool * filter_tool)
name|gimp_color_balance_tool_reset
parameter_list|(
name|GimpFilterTool
modifier|*
name|filter_tool
parameter_list|)
block|{
name|GimpTransferMode
name|range
decl_stmt|;
name|g_object_get
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"range"
argument_list|,
operator|&
name|range
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|GIMP_FILTER_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|reset
argument_list|(
name|filter_tool
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|,
literal|"range"
argument_list|,
name|range
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|color_balance_range_reset_callback (GtkWidget * widget,GimpFilterTool * filter_tool)
name|color_balance_range_reset_callback
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
name|gimp_color_balance_config_reset_range
argument_list|(
name|GIMP_COLOR_BALANCE_CONFIG
argument_list|(
name|filter_tool
operator|->
name|config
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

