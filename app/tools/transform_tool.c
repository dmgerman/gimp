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
file|"tool_options_ui.h"
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

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  the transform structures  */
end_comment

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
DECL|member|tool_options
name|ToolOptions
name|tool_options
decl_stmt|;
DECL|member|type
name|ToolType
name|type
decl_stmt|;
DECL|member|type_d
name|ToolType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|4
index|]
decl_stmt|;
comment|/* 4 radio buttons */
DECL|member|smoothing
name|gboolean
name|smoothing
decl_stmt|;
DECL|member|smoothing_d
name|gboolean
name|smoothing_d
decl_stmt|;
DECL|member|smoothing_w
name|GtkWidget
modifier|*
name|smoothing_w
decl_stmt|;
DECL|member|direction
name|gint
name|direction
decl_stmt|;
DECL|member|direction_d
name|gint
name|direction_d
decl_stmt|;
DECL|member|direction_w
name|GtkWidget
modifier|*
name|direction_w
index|[
literal|2
index|]
decl_stmt|;
comment|/* 2 radio buttons */
DECL|member|show_grid
name|gboolean
name|show_grid
decl_stmt|;
DECL|member|show_grid_d
name|gboolean
name|show_grid_d
decl_stmt|;
DECL|member|show_grid_w
name|GtkWidget
modifier|*
name|show_grid_w
decl_stmt|;
DECL|member|grid_size
name|gint
name|grid_size
decl_stmt|;
DECL|member|grid_size_d
name|gint
name|grid_size_d
decl_stmt|;
DECL|member|grid_size_w
name|GtkObject
modifier|*
name|grid_size_w
decl_stmt|;
DECL|member|clip
name|gint
name|clip
decl_stmt|;
DECL|member|clip_d
name|gint
name|clip_d
decl_stmt|;
DECL|member|clip_w
name|GtkWidget
modifier|*
name|clip_w
decl_stmt|;
DECL|member|showpath
name|gboolean
name|showpath
decl_stmt|;
DECL|member|showpath_d
name|gboolean
name|showpath_d
decl_stmt|;
DECL|member|showpath_w
name|GtkWidget
modifier|*
name|showpath_w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the transform tool options  */
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
comment|/*  functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|transform_show_grid_update (GtkWidget * widget,gpointer data)
name|transform_show_grid_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
comment|/* eek, this hack avoids a segfult */
if|if
condition|(
name|first_call
condition|)
block|{
name|first_call
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|tool_options_toggle_update
argument_list|(
name|widget
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
DECL|function|transform_show_path_update (GtkWidget * widget,gpointer data)
name|transform_show_path_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
specifier|static
name|gboolean
name|first_call
init|=
name|TRUE
decl_stmt|;
comment|/* eek, this hack avoids a segfult */
if|if
condition|(
name|first_call
condition|)
block|{
name|first_call
operator|=
name|FALSE
expr_stmt|;
return|return;
block|}
name|transform_core_showpath_changed
argument_list|(
literal|1
argument_list|)
expr_stmt|;
comment|/* pause */
name|tool_options_toggle_update
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|transform_core_showpath_changed
argument_list|(
literal|0
argument_list|)
expr_stmt|;
comment|/* resume */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_type_callback (GtkWidget * widget,gpointer client_data)
name|transform_type_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
DECL|function|transform_direction_callback (GtkWidget * widget,gpointer client_data)
name|transform_direction_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
DECL|function|transform_grid_density_callback (GtkWidget * w,gpointer client_data)
name|transform_grid_density_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|transform_options
operator|->
name|grid_size
operator|=
call|(
name|int
call|)
argument_list|(
name|pow
argument_list|(
literal|2.0
argument_list|,
literal|7.0
operator|-
name|GTK_ADJUSTMENT
argument_list|(
name|w
argument_list|)
operator|->
name|value
argument_list|)
operator|+
literal|0.5
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
DECL|function|transform_options_reset (void)
name|transform_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|TransformOptions
modifier|*
name|options
init|=
name|transform_options
decl_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
operator|(
operator|(
name|options
operator|->
name|type_d
operator|==
name|ROTATE
operator|)
condition|?
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|0
index|]
argument_list|)
else|:
operator|(
operator|(
name|options
operator|->
name|type_d
operator|==
name|SCALE
operator|)
condition|?
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|1
index|]
argument_list|)
else|:
operator|(
operator|(
name|options
operator|->
name|type_d
operator|==
name|SHEAR
operator|)
condition|?
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|2
index|]
argument_list|)
else|:
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|3
index|]
argument_list|)
operator|)
operator|)
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|smoothing_w
argument_list|)
argument_list|,
name|options
operator|->
name|smoothing_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|showpath_w
argument_list|)
argument_list|,
name|options
operator|->
name|showpath_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
operator|(
operator|(
name|options
operator|->
name|direction_d
operator|==
name|TRANSFORM_TRADITIONAL
operator|)
condition|?
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|direction_w
index|[
literal|0
index|]
argument_list|)
else|:
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|direction_w
index|[
literal|1
index|]
argument_list|)
operator|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|show_grid_w
argument_list|)
argument_list|,
name|options
operator|->
name|show_grid_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|grid_size_w
argument_list|)
argument_list|,
literal|7.0
operator|-
name|log
argument_list|(
name|options
operator|->
name|grid_size_d
argument_list|)
operator|/
name|log
argument_list|(
literal|2.0
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|clip_w
argument_list|)
argument_list|,
name|options
operator|->
name|clip_d
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TransformOptions
modifier|*
DECL|function|transform_options_new (void)
name|transform_options_new
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
name|table
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
name|label
decl_stmt|;
name|GSList
modifier|*
name|group
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|fbox
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_button
decl_stmt|;
name|GtkWidget
modifier|*
name|grid_density
decl_stmt|;
name|int
name|i
decl_stmt|;
specifier|static
specifier|const
name|char
modifier|*
name|transform_button_names
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Rotation"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Scaling"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Shearing"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Perspective"
argument_list|)
block|}
decl_stmt|;
specifier|static
specifier|const
name|char
modifier|*
name|direction_button_names
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Traditional"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Corrective"
argument_list|)
block|}
decl_stmt|;
comment|/*  the new transform tool options structure  */
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
name|tool_options_init
argument_list|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
argument_list|,
name|_
argument_list|(
literal|"Transform Tool Options"
argument_list|)
argument_list|,
name|transform_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|type
operator|=
name|options
operator|->
name|type_d
operator|=
name|ROTATE
expr_stmt|;
name|options
operator|->
name|smoothing
operator|=
name|options
operator|->
name|smoothing_d
operator|=
name|TRUE
expr_stmt|;
name|options
operator|->
name|showpath
operator|=
name|options
operator|->
name|showpath_d
operator|=
name|TRUE
expr_stmt|;
name|options
operator|->
name|clip
operator|=
name|options
operator|->
name|clip_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|direction
operator|=
name|options
operator|->
name|direction_d
operator|=
name|TRANSFORM_TRADITIONAL
expr_stmt|;
name|options
operator|->
name|grid_size
operator|=
name|options
operator|->
name|grid_size_d
operator|=
literal|32
expr_stmt|;
name|options
operator|->
name|show_grid
operator|=
name|options
operator|->
name|show_grid_d
operator|=
name|TRUE
expr_stmt|;
comment|/* the main table */
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|options
operator|->
name|tool_options
operator|.
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vbox
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  the first radio frame and box, for transform type  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Transform"
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
name|frame
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|fbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fbox
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
name|fbox
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
name|gettext
argument_list|(
name|transform_button_names
index|[
name|i
index|]
argument_list|)
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
name|fbox
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
name|options
operator|->
name|type_w
index|[
name|i
index|]
operator|=
name|radio_button
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|fbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vbox
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
comment|/*  the second radio frame and box, for transform direction  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Tool Paradigm"
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
name|frame
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|fbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fbox
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
name|fbox
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
name|gettext
argument_list|(
name|direction_button_names
index|[
name|i
index|]
argument_list|)
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
name|fbox
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
name|options
operator|->
name|direction_w
index|[
name|i
index|]
operator|=
name|radio_button
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|fbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
comment|/*  the grid frame  */
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
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
name|fbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|fbox
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
name|fbox
argument_list|)
expr_stmt|;
comment|/*  the show grid toggle button  */
name|options
operator|->
name|show_grid_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Show Grid"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|show_grid_w
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
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|fbox
argument_list|)
argument_list|,
name|options
operator|->
name|show_grid_w
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
name|options
operator|->
name|show_grid_w
argument_list|)
expr_stmt|;
comment|/*  the grid density entry  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|6
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
name|fbox
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
name|_
argument_list|(
literal|"Density:"
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
name|options
operator|->
name|grid_size_w
operator|=
name|gtk_adjustment_new
argument_list|(
literal|7.0
operator|-
name|log
argument_list|(
name|options
operator|->
name|grid_size_d
argument_list|)
operator|/
name|log
argument_list|(
literal|2.0
argument_list|)
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
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|grid_size_w
argument_list|)
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
name|options
operator|->
name|grid_size_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_grid_density_callback
argument_list|,
operator|&
name|options
operator|->
name|grid_size
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
name|gtk_widget_set_sensitive
argument_list|(
name|label
argument_list|,
name|options
operator|->
name|show_grid_d
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|grid_density
argument_list|,
name|options
operator|->
name|show_grid_d
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|show_grid_w
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|grid_density
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|grid_density
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|label
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|fbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vbox
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
comment|/*  the smoothing toggle button  */
name|options
operator|->
name|smoothing_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Smoothing"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|smoothing_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_toggle_update
argument_list|,
operator|&
name|options
operator|->
name|smoothing
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
name|smoothing_w
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
name|options
operator|->
name|smoothing_w
argument_list|)
expr_stmt|;
comment|/*  the clip resulting image toggle button  */
name|options
operator|->
name|clip_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Clip Result"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|clip_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_toggle_update
argument_list|,
operator|&
name|options
operator|->
name|clip
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
name|clip_w
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
name|options
operator|->
name|clip_w
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
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|vbox
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
comment|/*  the show_path toggle button  */
name|options
operator|->
name|showpath_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Show Path"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|showpath_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|transform_show_path_update
argument_list|,
operator|&
name|options
operator|->
name|showpath
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
name|showpath_w
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
name|options
operator|->
name|showpath_w
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
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
DECL|function|tools_new_transform_tool (void)
name|tools_new_transform_tool
parameter_list|(
name|void
parameter_list|)
block|{
comment|/* The tool options */
if|if
condition|(
operator|!
name|transform_options
condition|)
block|{
name|transform_options
operator|=
name|transform_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|ROTATE
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|transform_options
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|SCALE
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|transform_options
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|SHEAR
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|transform_options
argument_list|)
expr_stmt|;
name|tools_register
argument_list|(
name|PERSPECTIVE
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|transform_options
argument_list|)
expr_stmt|;
comment|/*  press all default buttons  */
name|transform_options_reset
argument_list|()
expr_stmt|;
block|}
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
name|gimp_context_set_tool
argument_list|(
name|gimp_context_get_user
argument_list|()
argument_list|,
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
name|TRUE
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
DECL|function|transform_tool_showpath ()
name|transform_tool_showpath
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
name|showpath
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
name|FALSE
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

