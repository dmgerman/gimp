begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"perspective_tool.h"
end_include

begin_include
include|#
directive|include
file|"rotate_tool.h"
end_include

begin_include
include|#
directive|include
file|"scale_tool.h"
end_include

begin_include
include|#
directive|include
file|"shear_tool.h"
end_include

begin_include
include|#
directive|include
file|"transform_core.h"
end_include

begin_include
include|#
directive|include
file|"transform_tool.h"
end_include

begin_typedef
DECL|typedef|TransformOptions
typedef|typedef
name|struct
name|_TransformOptions
name|TransformOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_TransformOptions
struct|struct
name|_TransformOptions
block|{
DECL|member|direction
name|int
name|direction
decl_stmt|;
DECL|member|smoothing
name|int
name|smoothing
decl_stmt|;
DECL|member|clip
name|int
name|clip
decl_stmt|;
DECL|member|grid_size
name|int
name|grid_size
decl_stmt|;
DECL|member|show_grid
name|int
name|show_grid
decl_stmt|;
DECL|member|type
name|ToolType
name|type
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|transform_change_type
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Static variables  */
end_comment

begin_decl_stmt
DECL|variable|transform_options
specifier|static
name|TransformOptions
modifier|*
name|transform_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|transform_toggle_update (GtkWidget * w,gpointer data)
name|transform_toggle_update
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|int
modifier|*
name|toggle_val
decl_stmt|;
name|toggle_val
operator|=
operator|(
name|int
operator|*
operator|)
name|data
expr_stmt|;
if|if
condition|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|w
argument_list|)
operator|->
name|active
condition|)
operator|*
name|toggle_val
operator|=
name|TRUE
expr_stmt|;
else|else
operator|*
name|toggle_val
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_show_grid_update (GtkWidget * w,gpointer data)
name|transform_show_grid_update
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|transform_toggle_update
argument_list|(
name|w
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|transform_core_grid_density_changed
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_type_callback (GtkWidget * w,gpointer client_data)
name|transform_type_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|transform_change_type
argument_list|(
operator|(
name|long
operator|)
name|client_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_direction_callback (GtkWidget * w,gpointer client_data)
name|transform_direction_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|long
name|dir
init|=
operator|(
name|long
operator|)
name|client_data
decl_stmt|;
if|if
condition|(
name|dir
operator|==
name|TRANSFORM_TRADITIONAL
condition|)
name|transform_options
operator|->
name|direction
operator|=
name|TRANSFORM_TRADITIONAL
expr_stmt|;
else|else
name|transform_options
operator|->
name|direction
operator|=
name|TRANSFORM_CORRECTIVE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_grid_density_callback (GtkWidget * w,GtkSpinButton * spin)
name|transform_grid_density_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|GtkSpinButton
modifier|*
name|spin
parameter_list|)
block|{
name|transform_options
operator|->
name|grid_size
operator|=
operator|(
name|int
operator|)
name|pow
argument_list|(
literal|2.0
argument_list|,
literal|7.0
operator|-
name|gtk_spin_button_get_value_as_int
argument_list|(
name|spin
argument_list|)
argument_list|)
expr_stmt|;
name|transform_core_grid_density_changed
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TransformOptions
modifier|*
DECL|function|create_transform_options (void)
name|create_transform_options
parameter_list|(
name|void
parameter_list|)
block|{
name|TransformOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|main_box
decl_stmt|,
modifier|*
name|box
decl_stmt|,
modifier|*
name|vbox
decl_stmt|,
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_frame
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_button
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|GtkAdjustment
modifier|*
name|grid_adj
decl_stmt|;
name|GtkWidget
modifier|*
name|grid_density
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|int
name|i
decl_stmt|;
name|char
modifier|*
name|transform_button_names
index|[
literal|4
index|]
init|=
block|{
literal|"Rotation"
block|,
literal|"Scaling"
block|,
literal|"Shearing"
block|,
literal|"Perspective"
block|}
decl_stmt|;
name|char
modifier|*
name|direction_button_names
index|[
literal|2
index|]
init|=
block|{
literal|"Traditional"
block|,
literal|"Corrective"
block|}
decl_stmt|;
comment|/*  the new options structure  */
name|options
operator|=
operator|(
name|TransformOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|TransformOptions
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|type
operator|=
name|ROTATE
expr_stmt|;
name|options
operator|->
name|smoothing
operator|=
literal|1
expr_stmt|;
name|options
operator|->
name|clip
operator|=
literal|1
expr_stmt|;
name|options
operator|->
name|direction
operator|=
name|TRANSFORM_TRADITIONAL
expr_stmt|;
name|options
operator|->
name|grid_size
operator|=
literal|32
expr_stmt|;
name|options
operator|->
name|show_grid
operator|=
name|TRUE
expr_stmt|;
comment|/* the main vbox */
name|main_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  the main label  */
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Transform Tool Options"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_box
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
comment|/*  the hbox holding the left and right vboxes*/
name|box
operator|=
name|gtk_hbox_new
argument_list|(
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|main_box
argument_list|)
argument_list|,
name|box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the left vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the first radio frame and box, for transform type  */
name|radio_frame
operator|=
name|gtk_frame_new
argument_list|(
literal|"Transform"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|radio_frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|radio_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_frame
argument_list|)
argument_list|,
name|radio_box
argument_list|)
expr_stmt|;
comment|/*  the radio buttons  */
name|group
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|radio_button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|transform_button_names
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio_button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|radio_button
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
name|radio_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_type_callback
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|ROTATE
operator|+
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_button
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_frame
argument_list|)
expr_stmt|;
comment|/*  the smoothing toggle button  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Smoothing"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_toggle_update
argument_list|,
operator|&
name|options
operator|->
name|smoothing
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|options
operator|->
name|smoothing
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  the right vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|vbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the second radio frame and box, for transform direction  */
name|radio_frame
operator|=
name|gtk_frame_new
argument_list|(
literal|"Tool paradigm"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|radio_frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|radio_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_frame
argument_list|)
argument_list|,
name|radio_box
argument_list|)
expr_stmt|;
comment|/*  the radio buttons  */
name|group
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|radio_button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|direction_button_names
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio_button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|radio_button
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
name|radio_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_direction_callback
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
operator|(
name|long
operator|)
name|i
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_button
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_frame
argument_list|)
expr_stmt|;
comment|/* the show grid toggle button */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Show grid"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|options
operator|->
name|show_grid
argument_list|)
expr_stmt|;
comment|/* important: connect the signal after setting the state, because calling      transform_show_grid_update before the tool is created will fail */
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_show_grid_update
argument_list|,
operator|&
name|options
operator|->
name|show_grid
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
comment|/*  the grid density entry  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
name|label
operator|=
name|gtk_label_new
argument_list|(
literal|"Grid density: "
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
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|grid_adj
operator|=
operator|(
name|GtkAdjustment
operator|*
operator|)
name|gtk_adjustment_new
argument_list|(
literal|2.0
argument_list|,
literal|0.0
argument_list|,
literal|5.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|grid_density
operator|=
name|gtk_spin_button_new
argument_list|(
name|grid_adj
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_spin_button_set_wrap
argument_list|(
name|GTK_SPIN_BUTTON
argument_list|(
name|grid_density
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|grid_adj
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_grid_density_callback
argument_list|,
name|grid_density
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|grid_density
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
name|grid_density
argument_list|)
expr_stmt|;
comment|/*  the clip resulting image toggle button  */
name|toggle
operator|=
name|gtk_check_button_new_with_label
argument_list|(
literal|"Clip perspective"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_toggle_update
argument_list|,
operator|&
name|options
operator|->
name|clip
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_state
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|options
operator|->
name|clip
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|toggle
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|box
argument_list|)
expr_stmt|;
comment|/*  Register this selection options widget with the main tools options dialog  */
name|tools_register_options
argument_list|(
name|ROTATE
argument_list|,
name|main_box
argument_list|)
expr_stmt|;
name|tools_register_options
argument_list|(
name|SCALE
argument_list|,
name|main_box
argument_list|)
expr_stmt|;
name|tools_register_options
argument_list|(
name|SHEAR
argument_list|,
name|main_box
argument_list|)
expr_stmt|;
name|tools_register_options
argument_list|(
name|PERSPECTIVE
argument_list|,
name|main_box
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_transform_tool ()
name|tools_new_transform_tool
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
name|transform_options
operator|=
name|create_transform_options
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|transform_options
operator|->
name|type
condition|)
block|{
case|case
name|ROTATE
case|:
return|return
name|tools_new_rotate_tool
argument_list|()
return|;
break|break;
case|case
name|SCALE
case|:
return|return
name|tools_new_scale_tool
argument_list|()
return|;
break|break;
case|case
name|SHEAR
case|:
return|return
name|tools_new_shear_tool
argument_list|()
return|;
break|break;
case|case
name|PERSPECTIVE
case|:
return|return
name|tools_new_perspective_tool
argument_list|()
return|;
break|break;
default|default :
return|return
name|NULL
return|;
break|break;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tools_free_transform_tool (Tool * tool)
name|tools_free_transform_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
switch|switch
condition|(
name|transform_options
operator|->
name|type
condition|)
block|{
case|case
name|ROTATE
case|:
name|tools_free_rotate_tool
argument_list|(
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|SCALE
case|:
name|tools_free_scale_tool
argument_list|(
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|SHEAR
case|:
name|tools_free_shear_tool
argument_list|(
name|tool
argument_list|)
expr_stmt|;
break|break;
case|case
name|PERSPECTIVE
case|:
name|tools_free_perspective_tool
argument_list|(
name|tool
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_change_type (int new_type)
name|transform_change_type
parameter_list|(
name|int
name|new_type
parameter_list|)
block|{
if|if
condition|(
name|transform_options
operator|->
name|type
operator|!=
name|new_type
condition|)
block|{
comment|/*  change the type, free the old tool, create the new tool  */
name|transform_options
operator|->
name|type
operator|=
name|new_type
expr_stmt|;
name|tools_select
argument_list|(
name|transform_options
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|int
DECL|function|transform_tool_smoothing ()
name|transform_tool_smoothing
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
return|return
literal|1
return|;
else|else
return|return
name|transform_options
operator|->
name|smoothing
return|;
block|}
end_function

begin_function
name|int
DECL|function|transform_tool_clip ()
name|transform_tool_clip
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
return|return
literal|1
return|;
else|else
return|return
name|transform_options
operator|->
name|clip
return|;
block|}
end_function

begin_function
name|int
DECL|function|transform_tool_direction ()
name|transform_tool_direction
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
return|return
name|TRANSFORM_TRADITIONAL
return|;
else|else
return|return
name|transform_options
operator|->
name|direction
return|;
block|}
end_function

begin_function
name|int
DECL|function|transform_tool_grid_size ()
name|transform_tool_grid_size
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
return|return
literal|32
return|;
else|else
return|return
name|transform_options
operator|->
name|grid_size
return|;
block|}
end_function

begin_function
name|int
DECL|function|transform_tool_show_grid ()
name|transform_tool_show_grid
parameter_list|()
block|{
if|if
condition|(
operator|!
name|transform_options
condition|)
return|return
name|TRUE
return|;
else|else
return|return
name|transform_options
operator|->
name|show_grid
return|;
block|}
end_function

end_unit

