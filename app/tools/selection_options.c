begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimpbase.h"
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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimpellipseselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpfuzzyselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpiscissorstool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbycolorselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_include
include|#
directive|include
file|"selection_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function
name|void
DECL|function|selection_options_init (SelectionOptions * options,GtkType tool_type,ToolOptionsResetFunc reset_func)
name|selection_options_init
parameter_list|(
name|SelectionOptions
modifier|*
name|options
parameter_list|,
name|GtkType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|abox
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
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
comment|/*  initialize the tool options structure  */
name|tool_options_init
argument_list|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
argument_list|,
name|reset_func
argument_list|)
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
expr_stmt|;
comment|/*  initialize the selection options structure  */
name|options
operator|->
name|feather
operator|=
name|options
operator|->
name|feather_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|feather_radius
operator|=
name|options
operator|->
name|feather_radius_d
operator|=
literal|10.0
expr_stmt|;
name|options
operator|->
name|antialias
operator|=
name|options
operator|->
name|antialias_d
operator|=
name|TRUE
expr_stmt|;
name|options
operator|->
name|sample_merged
operator|=
name|options
operator|->
name|sample_merged_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|threshold
operator|=
name|default_threshold
expr_stmt|;
name|options
operator|->
name|fixed_size
operator|=
name|options
operator|->
name|fixed_size_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|fixed_height
operator|=
name|options
operator|->
name|fixed_height_d
operator|=
literal|1
expr_stmt|;
name|options
operator|->
name|fixed_width
operator|=
name|options
operator|->
name|fixed_width_d
operator|=
literal|1
expr_stmt|;
name|options
operator|->
name|fixed_unit
operator|=
name|options
operator|->
name|fixed_unit_d
operator|=
name|GIMP_UNIT_PIXEL
expr_stmt|;
name|options
operator|->
name|interactive
operator|=
name|options
operator|->
name|interactive_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|feather_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|feather_radius_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|antialias_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|sample_merged_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|threshold_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|fixed_size_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|fixed_height_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|fixed_width_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|fixed_unit_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|interactive_w
operator|=
name|NULL
expr_stmt|;
comment|/*  the feather toggle button  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
name|table
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|options
operator|->
name|feather_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Feather"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|options
operator|->
name|feather_w
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
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|feather_w
argument_list|)
argument_list|,
name|options
operator|->
name|feather_d
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|feather_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|feather
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|feather_w
argument_list|)
expr_stmt|;
comment|/*  the feather radius scale  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Radius:"
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
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|abox
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
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
literal|1
argument_list|,
literal|2
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|GTK_EXPAND
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
name|abox
argument_list|)
expr_stmt|;
name|options
operator|->
name|feather_radius_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|feather_radius_d
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|feather_radius_w
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|abox
argument_list|)
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|feather_radius_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/*  grey out label& scale if feather is off  */
name|gtk_widget_set_sensitive
argument_list|(
name|scale
argument_list|,
name|options
operator|->
name|feather_d
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|label
argument_list|,
name|options
operator|->
name|feather_d
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|feather_w
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|scale
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  the antialias toggle button  */
if|if
condition|(
name|tool_type
operator|!=
name|GIMP_TYPE_RECT_SELECT_TOOL
condition|)
block|{
name|options
operator|->
name|antialias_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Antialiasing"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|antialias_w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|antialias_w
argument_list|)
argument_list|,
name|options
operator|->
name|antialias_d
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|antialias_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|antialias
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|antialias_w
argument_list|)
expr_stmt|;
block|}
comment|/*  a separator between the common and tool-specific selection options  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_ISCISSORS_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_RECT_SELECT_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ELLIPSE_SELECT_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_FUZZY_SELECT_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_BY_COLOR_SELECT_TOOL
condition|)
block|{
name|separator
operator|=
name|gtk_hseparator_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|separator
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
name|separator
argument_list|)
expr_stmt|;
block|}
comment|/* selection tool with an interactive boundary that can be toggled */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_ISCISSORS_TOOL
condition|)
block|{
name|options
operator|->
name|interactive_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Show Interactive Boundary"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|interactive_w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|interactive_w
argument_list|)
argument_list|,
name|options
operator|->
name|interactive_d
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|interactive_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|interactive
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|interactive_w
argument_list|)
expr_stmt|;
block|}
comment|/*  selection tools which operate on contiguous regions  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_FUZZY_SELECT_TOOL
condition|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
comment|/*  the sample merged toggle  */
name|options
operator|->
name|sample_merged_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Sample Merged"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|sample_merged_w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
argument_list|,
name|options
operator|->
name|sample_merged_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
expr_stmt|;
comment|/*  the threshold scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Threshold:"
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|options
operator|->
name|threshold_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|default_threshold
argument_list|,
literal|0.0
argument_list|,
literal|255.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|threshold_w
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scale
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|threshold_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|threshold
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
block|}
comment|/*  widgets for fixed size select  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_RECT_SELECT_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ELLIPSE_SELECT_TOOL
condition|)
block|{
name|GtkWidget
modifier|*
name|alignment
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|width_spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|height_spinbutton
decl_stmt|;
name|options
operator|->
name|fixed_size_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Fixed Size / Aspect Ratio"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_size_w
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_size_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fixed_size
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|fixed_size_w
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_size_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|fixed_size_w
argument_list|)
expr_stmt|;
name|alignment
operator|=
name|gtk_alignment_new
argument_list|(
literal|0.5
argument_list|,
literal|0.5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|alignment
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
name|alignment
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|alignment
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
comment|/*  grey out the table if fixed size is off  */
name|gtk_widget_set_sensitive
argument_list|(
name|table
argument_list|,
name|options
operator|->
name|fixed_size_d
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_size_w
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|table
argument_list|)
expr_stmt|;
name|options
operator|->
name|fixed_width_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|fixed_width_d
argument_list|,
literal|1e-5
argument_list|,
literal|32767.0
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|width_spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|fixed_width_w
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_shadow_type
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|width_spinbutton
argument_list|)
argument_list|,
name|GTK_SHADOW_NONE
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|width_spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|width_spinbutton
argument_list|,
literal|75
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_width_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fixed_width
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"Width:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|width_spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|options
operator|->
name|fixed_height_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|fixed_height_d
argument_list|,
literal|1e-5
argument_list|,
literal|32767.0
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|height_spinbutton
operator|=
name|gtk_spin_button_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|fixed_height_w
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_shadow_type
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|height_spinbutton
argument_list|)
argument_list|,
name|GTK_SHADOW_NONE
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_numeric
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|height_spinbutton
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_usize
argument_list|(
name|height_spinbutton
argument_list|,
literal|75
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_height_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fixed_height
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"Height:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|height_spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|options
operator|->
name|fixed_unit_w
operator|=
name|gimp_unit_menu_new
argument_list|(
literal|"%a"
argument_list|,
name|options
operator|->
name|fixed_unit_d
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_unit_w
argument_list|)
argument_list|,
literal|"unit_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_unit_menu_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|fixed_unit
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_unit_w
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|width_spinbutton
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|width_spinbutton
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|height_spinbutton
argument_list|)
expr_stmt|;
name|gimp_table_attach_aligned
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
literal|"Unit:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|fixed_unit_w
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|SelectionOptions
modifier|*
DECL|function|selection_options_new (GtkType tool_type,ToolOptionsResetFunc reset_func)
name|selection_options_new
parameter_list|(
name|GtkType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
block|{
name|SelectionOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|g_new
argument_list|(
name|SelectionOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|selection_options_init
argument_list|(
name|options
argument_list|,
name|tool_type
argument_list|,
name|reset_func
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|void
DECL|function|selection_options_reset (ToolOptions * tool_options)
name|selection_options_reset
parameter_list|(
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|SelectionOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|SelectionOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|feather_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|feather_w
argument_list|)
argument_list|,
name|options
operator|->
name|feather_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|feather_radius_w
argument_list|)
argument_list|,
name|options
operator|->
name|feather_radius_d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|antialias_w
condition|)
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|antialias_w
argument_list|)
argument_list|,
name|options
operator|->
name|antialias_d
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|sample_merged_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|sample_merged_w
argument_list|)
argument_list|,
name|options
operator|->
name|sample_merged_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|threshold_w
argument_list|)
argument_list|,
name|default_threshold
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|fixed_size_w
condition|)
block|{
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|gint
name|digits
decl_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|fixed_size_w
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_size_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|fixed_width_w
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_width_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|fixed_height_w
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_height_d
argument_list|)
expr_stmt|;
name|options
operator|->
name|fixed_unit
operator|=
name|options
operator|->
name|fixed_unit_d
expr_stmt|;
name|gimp_unit_menu_set_unit
argument_list|(
name|GIMP_UNIT_MENU
argument_list|(
name|options
operator|->
name|fixed_unit_w
argument_list|)
argument_list|,
name|options
operator|->
name|fixed_unit_d
argument_list|)
expr_stmt|;
name|digits
operator|=
operator|(
operator|(
name|options
operator|->
name|fixed_unit_d
operator|==
name|GIMP_UNIT_PIXEL
operator|)
condition|?
literal|0
else|:
operator|(
operator|(
name|options
operator|->
name|fixed_unit_d
operator|==
name|GIMP_UNIT_PERCENT
operator|)
condition|?
literal|2
else|:
operator|(
name|MIN
argument_list|(
literal|6
argument_list|,
name|MAX
argument_list|(
literal|3
argument_list|,
name|gimp_unit_get_digits
argument_list|(
name|options
operator|->
name|fixed_unit_d
argument_list|)
argument_list|)
argument_list|)
operator|)
operator|)
operator|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|fixed_unit_w
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
while|while
condition|(
name|spinbutton
condition|)
block|{
name|gtk_spin_button_set_digits
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
name|digits
argument_list|)
expr_stmt|;
name|spinbutton
operator|=
name|gtk_object_get_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|options
operator|->
name|interactive_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|interactive_w
argument_list|)
argument_list|,
name|options
operator|->
name|interactive_d
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

