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
file|<stdio.h>
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
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"paintbrush.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  defines  */
end_comment

begin_define
DECL|macro|PAINT_LEFT_THRESHOLD
define|#
directive|define
name|PAINT_LEFT_THRESHOLD
value|0.05
end_define

begin_comment
comment|/*  the paintbrush structures  */
end_comment

begin_typedef
DECL|typedef|PaintbrushOptions
typedef|typedef
name|struct
name|_PaintbrushOptions
name|PaintbrushOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_PaintbrushOptions
struct|struct
name|_PaintbrushOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|fade_out
name|double
name|fade_out
decl_stmt|;
DECL|member|fade_out_d
name|double
name|fade_out_d
decl_stmt|;
DECL|member|fade_out_w
name|GtkObject
modifier|*
name|fade_out_w
decl_stmt|;
DECL|member|use_gradient
name|int
name|use_gradient
decl_stmt|;
DECL|member|use_gradient_d
name|int
name|use_gradient_d
decl_stmt|;
DECL|member|use_gradient_w
name|GtkWidget
modifier|*
name|use_gradient_w
decl_stmt|;
DECL|member|gradient_length
name|double
name|gradient_length
decl_stmt|;
DECL|member|gradient_length_d
name|double
name|gradient_length_d
decl_stmt|;
DECL|member|gradient_length_w
name|GtkObject
modifier|*
name|gradient_length_w
decl_stmt|;
DECL|member|gradient_type
name|int
name|gradient_type
decl_stmt|;
DECL|member|gradient_type_d
name|int
name|gradient_type_d
decl_stmt|;
DECL|member|gradient_type_w
name|GtkWidget
modifier|*
name|gradient_type_w
index|[
literal|4
index|]
decl_stmt|;
comment|/* 4 radio buttons */
DECL|member|incremental
name|gboolean
name|incremental
decl_stmt|;
DECL|member|incremental_d
name|gboolean
name|incremental_d
decl_stmt|;
DECL|member|incremental_w
name|GtkWidget
modifier|*
name|incremental_w
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the paint brush tool options  */
end_comment

begin_decl_stmt
DECL|variable|paintbrush_options
specifier|static
name|PaintbrushOptions
modifier|*
name|paintbrush_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|non_gui_fade_out
specifier|static
name|double
name|non_gui_fade_out
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_gradient_length
specifier|static
name|double
name|non_gui_gradient_length
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_gradient_type
specifier|static
name|int
name|non_gui_gradient_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|non_gui_incremental
specifier|static
name|double
name|non_gui_incremental
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|paintbrush_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|,
name|gboolean
parameter_list|,
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
DECL|function|paintbrush_gradient_toggle_callback (GtkWidget * widget,gpointer data)
name|paintbrush_gradient_toggle_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|PaintbrushOptions
modifier|*
name|options
init|=
name|paintbrush_options
decl_stmt|;
specifier|static
name|int
name|incremental_save
init|=
name|FALSE
decl_stmt|;
name|tool_options_toggle_update
argument_list|(
name|widget
argument_list|,
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|paintbrush_options
operator|->
name|use_gradient
condition|)
block|{
name|incremental_save
operator|=
name|options
operator|->
name|incremental
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|incremental_w
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|incremental_w
argument_list|)
argument_list|,
name|incremental_save
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paintbrush_gradient_type_callback (GtkWidget * widget,gpointer data)
name|paintbrush_gradient_type_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
if|if
condition|(
name|paintbrush_options
condition|)
name|paintbrush_options
operator|->
name|gradient_type
operator|=
operator|(
name|int
operator|)
name|data
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paintbrush_options_reset (void)
name|paintbrush_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|PaintbrushOptions
modifier|*
name|options
init|=
name|paintbrush_options
decl_stmt|;
name|paint_options_reset
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|fade_out_w
argument_list|)
argument_list|,
name|options
operator|->
name|fade_out_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|use_gradient_w
argument_list|)
argument_list|,
name|options
operator|->
name|use_gradient_d
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|gradient_length_w
argument_list|)
argument_list|,
name|options
operator|->
name|gradient_length_d
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|gradient_type_w
index|[
name|options
operator|->
name|gradient_type_d
index|]
argument_list|)
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
name|incremental_w
argument_list|)
argument_list|,
name|options
operator|->
name|incremental_d
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|PaintbrushOptions
modifier|*
DECL|function|paintbrush_options_new (void)
name|paintbrush_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|PaintbrushOptions
modifier|*
name|options
decl_stmt|;
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
name|GSList
modifier|*
name|group
init|=
name|NULL
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
name|int
name|i
decl_stmt|;
name|char
modifier|*
name|gradient_types
index|[
literal|4
index|]
init|=
block|{
name|N_
argument_list|(
literal|"Once Forward"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Once Backward"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Loop Sawtooth"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Loop Triangle"
argument_list|)
block|}
decl_stmt|;
comment|/*  the new paint tool options structure  */
name|options
operator|=
operator|(
name|PaintbrushOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|PaintbrushOptions
argument_list|)
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|,
name|PAINTBRUSH
argument_list|,
name|paintbrush_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|fade_out
operator|=
name|options
operator|->
name|fade_out_d
operator|=
literal|0.0
expr_stmt|;
name|options
operator|->
name|incremental
operator|=
name|options
operator|->
name|incremental_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|use_gradient
operator|=
name|options
operator|->
name|use_gradient_d
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|gradient_length
operator|=
name|options
operator|->
name|gradient_length_d
operator|=
literal|10.0
expr_stmt|;
name|options
operator|->
name|gradient_type
operator|=
name|options
operator|->
name|gradient_type_d
operator|=
name|LOOP_TRIANGLE
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
comment|/*  the fade-out scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|4
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
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|3
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
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Fade Out:"
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
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|options
operator|->
name|fade_out_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|fade_out_d
argument_list|,
literal|0.0
argument_list|,
literal|1000.0
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
name|fade_out_w
argument_list|)
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
literal|0
argument_list|,
literal|1
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
name|fade_out_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_double_adjustment_update
argument_list|,
operator|&
name|options
operator|->
name|fade_out
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
comment|/*  the use gradient toggle  */
name|options
operator|->
name|use_gradient_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Gradient"
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
name|use_gradient_w
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
argument_list|,
literal|0
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
name|use_gradient_w
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|paintbrush_gradient_toggle_callback
argument_list|,
operator|&
name|options
operator|->
name|use_gradient
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|use_gradient_w
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Length:"
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
literal|2
argument_list|,
literal|3
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
comment|/*  the gradient length scale  */
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
literal|1
argument_list|,
literal|3
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
name|gradient_length_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|gradient_length_d
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|1.1
argument_list|,
literal|0.1
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
name|gradient_length_w
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
name|gradient_length_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|tool_options_double_adjustment_update
argument_list|,
operator|&
name|options
operator|->
name|gradient_length
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  the radio frame and box  */
name|radio_frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Gradient Type"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|radio_frame
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|4
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|radio_box
argument_list|)
argument_list|,
literal|2
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
name|gradient_types
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
name|paintbrush_gradient_type_callback
argument_list|,
operator|(
name|void
operator|*
operator|)
operator|(
operator|(
name|long
operator|)
name|i
operator|)
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
name|gtk_widget_show
argument_list|(
name|radio_button
argument_list|)
expr_stmt|;
name|options
operator|->
name|gradient_type_w
index|[
name|i
index|]
operator|=
name|radio_button
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
comment|/* the incremental toggle */
name|options
operator|->
name|incremental_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Incremental"
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
name|incremental_w
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
name|incremental_w
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
name|incremental
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|incremental_w
argument_list|)
expr_stmt|;
comment|/*  automatically set the sensitive state of the gradient stuff  */
name|gtk_widget_set_sensitive
argument_list|(
name|scale
argument_list|,
name|options
operator|->
name|use_gradient_d
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|label
argument_list|,
name|options
operator|->
name|use_gradient_d
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|radio_frame
argument_list|,
name|options
operator|->
name|use_gradient_d
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|options
operator|->
name|incremental_w
argument_list|,
operator|!
name|options
operator|->
name|use_gradient_d
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|use_gradient_w
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
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|label
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|radio_frame
argument_list|)
expr_stmt|;
name|gtk_object_set_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|use_gradient_w
argument_list|)
argument_list|,
literal|"inverse_sensitive"
argument_list|,
name|options
operator|->
name|incremental_w
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_define
DECL|macro|USE_SPEEDSHOP_CALIPERS
define|#
directive|define
name|USE_SPEEDSHOP_CALIPERS
value|0
end_define

begin_define
DECL|macro|TIMED_BRUSH
define|#
directive|define
name|TIMED_BRUSH
value|0
end_define

begin_if
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
end_if

begin_include
include|#
directive|include
file|<SpeedShop/api.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
modifier|*
DECL|function|paintbrush_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|paintbrush_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
if|#
directive|if
name|TIMED_BRUSH
specifier|static
name|GTimer
modifier|*
name|timer
decl_stmt|;
endif|#
directive|endif
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
if|#
directive|if
name|TIMED_BRUSH
name|timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
name|g_timer_start
argument_list|(
name|timer
argument_list|)
expr_stmt|;
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
name|ssrt_caliper_point
argument_list|(
literal|0
argument_list|,
literal|"Painting"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SPEEDSHOP_CALIPERS */
endif|#
directive|endif
comment|/* TIMED_BRUSH */
break|break;
case|case
name|MOTION_PAINT
case|:
name|paintbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paintbrush_options
operator|->
name|fade_out
argument_list|,
name|paintbrush_options
operator|->
name|use_gradient
condition|?
name|exp
argument_list|(
name|paintbrush_options
operator|->
name|gradient_length
operator|/
literal|10
argument_list|)
else|:
literal|0
argument_list|,
name|paintbrush_options
operator|->
name|incremental
argument_list|,
name|paintbrush_options
operator|->
name|gradient_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
if|#
directive|if
name|TIMED_BRUSH
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
name|ssrt_caliper_point
argument_list|(
literal|0
argument_list|,
literal|"Not Painting Anymore"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SPEEDSHOP_CALIPERS */
name|g_timer_stop
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"painting took %f:\n"
argument_list|,
name|g_timer_elapsed
argument_list|(
name|timer
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_timer_destroy
argument_list|(
name|timer
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* TIMED_BRUSH */
break|break;
default|default :
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_paintbrush ()
name|tools_new_paintbrush
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|PaintCore
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|paintbrush_options
condition|)
block|{
name|paintbrush_options
operator|=
name|paintbrush_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|PAINTBRUSH
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|paintbrush_options
argument_list|)
expr_stmt|;
comment|/*  press all default buttons  */
name|paintbrush_options_reset
argument_list|()
expr_stmt|;
block|}
name|tool
operator|=
name|paint_core_new
argument_list|(
name|PAINTBRUSH
argument_list|)
expr_stmt|;
name|private
operator|=
operator|(
name|PaintCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|paint_func
operator|=
name|paintbrush_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_paintbrush (Tool * tool)
name|tools_free_paintbrush
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|paint_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paintbrush_motion (PaintCore * paint_core,GimpDrawable * drawable,double fade_out,double gradient_length,gboolean incremental,int gradient_type)
name|paintbrush_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|double
name|fade_out
parameter_list|,
name|double
name|gradient_length
parameter_list|,
name|gboolean
name|incremental
parameter_list|,
name|int
name|gradient_type
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|double
name|x
decl_stmt|,
name|paint_left
decl_stmt|;
name|double
name|position
decl_stmt|;
name|unsigned
name|char
name|local_blend
init|=
name|OPAQUE_OPACITY
decl_stmt|;
name|unsigned
name|char
name|temp_blend
init|=
name|OPAQUE_OPACITY
decl_stmt|;
name|unsigned
name|char
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|double
name|r
decl_stmt|,
name|g
decl_stmt|,
name|b
decl_stmt|,
name|a
decl_stmt|;
name|int
name|mode
decl_stmt|;
name|position
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
name|gimage_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
comment|/*  Get a region which can be used to p\\aint to  */
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  factor in the fade out value  */
if|if
condition|(
name|fade_out
condition|)
block|{
comment|/*  Model the amount of paint left as a gaussian curve  */
name|x
operator|=
operator|(
operator|(
name|double
operator|)
name|paint_core
operator|->
name|distance
operator|/
name|fade_out
operator|)
expr_stmt|;
name|paint_left
operator|=
name|exp
argument_list|(
operator|-
name|x
operator|*
name|x
operator|*
literal|0.5
argument_list|)
expr_stmt|;
name|local_blend
operator|=
call|(
name|int
call|)
argument_list|(
literal|255
operator|*
name|paint_left
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|local_blend
condition|)
block|{
comment|/*  set the alpha channel  */
name|col
index|[
name|area
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|temp_blend
operator|=
name|local_blend
expr_stmt|;
comment|/* hard core to mode LOOP_TRIANGLE */
comment|/* need to maek a gui to handle this */
name|mode
operator|=
name|gradient_type
expr_stmt|;
if|if
condition|(
name|gradient_length
condition|)
block|{
name|paint_core_get_color_from_gradient
argument_list|(
name|paint_core
argument_list|,
name|gradient_length
argument_list|,
operator|&
name|r
argument_list|,
operator|&
name|g
argument_list|,
operator|&
name|b
argument_list|,
operator|&
name|a
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|r
operator|=
name|r
operator|*
literal|255.0
expr_stmt|;
name|g
operator|=
name|g
operator|*
literal|255.0
expr_stmt|;
name|b
operator|=
name|b
operator|*
literal|255.0
expr_stmt|;
name|a
operator|=
name|a
operator|*
literal|255.0
expr_stmt|;
name|temp_blend
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|a
operator|*
name|local_blend
operator|)
operator|/
literal|255
argument_list|)
expr_stmt|;
name|col
index|[
literal|0
index|]
operator|=
operator|(
name|gint
operator|)
name|r
expr_stmt|;
name|col
index|[
literal|1
index|]
operator|=
operator|(
name|gint
operator|)
name|g
expr_stmt|;
name|col
index|[
literal|2
index|]
operator|=
operator|(
name|gint
operator|)
name|b
expr_stmt|;
comment|/* always use incremental mode with gradients */
comment|/* make the gui cool later */
name|incremental
operator|=
name|INCREMENTAL
expr_stmt|;
block|}
comment|/* just leave this because I know as soon as i delete it i'll find a bug */
comment|/*          printf("temp_blend: %u grad_len: %f distance: %f \n",temp_blend, gradient_length, distance); */
comment|/*  color the pixels  */
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
comment|/*  paste the newly painted canvas to the gimage which is being worked on  */
name|paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|temp_blend
argument_list|,
call|(
name|int
call|)
argument_list|(
name|PAINT_OPTIONS_GET_OPACITY
argument_list|(
name|paintbrush_options
argument_list|)
operator|*
literal|255
argument_list|)
argument_list|,
name|PAINT_OPTIONS_GET_PAINT_MODE
argument_list|(
name|paintbrush_options
argument_list|)
argument_list|,
name|PRESSURE
argument_list|,
name|incremental
condition|?
name|INCREMENTAL
else|:
name|CONSTANT
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|paintbrush_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|paintbrush_non_gui_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
name|paintbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|non_gui_fade_out
argument_list|,
name|non_gui_gradient_length
argument_list|,
name|non_gui_incremental
argument_list|,
name|non_gui_gradient_type
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|paintbrush_non_gui (GimpDrawable * drawable,int num_strokes,double * stroke_array,double fade_out,int method,double gradient_length)
name|paintbrush_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|,
name|double
name|fade_out
parameter_list|,
name|int
name|method
parameter_list|,
name|double
name|gradient_length
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
if|if
condition|(
name|paint_core_init
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
name|stroke_array
index|[
literal|0
index|]
argument_list|,
name|stroke_array
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
name|non_gui_fade_out
operator|=
name|fade_out
expr_stmt|;
name|non_gui_gradient_length
operator|=
name|gradient_length
expr_stmt|;
name|non_gui_gradient_type
operator|=
name|LOOP_TRIANGLE
expr_stmt|;
name|non_gui_incremental
operator|=
name|method
expr_stmt|;
comment|/* Set the paint core's paint func */
name|non_gui_paint_core
operator|.
name|paint_func
operator|=
name|paintbrush_non_gui_paint_func
expr_stmt|;
name|non_gui_paint_core
operator|.
name|startx
operator|=
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|stroke_array
index|[
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|starty
operator|=
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|stroke_array
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|num_strokes
operator|==
literal|1
condition|)
name|paintbrush_non_gui_paint_func
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|num_strokes
condition|;
name|i
operator|++
control|)
block|{
name|non_gui_paint_core
operator|.
name|curx
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|cury
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
expr_stmt|;
name|paint_core_interpolate
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|non_gui_paint_core
operator|.
name|curx
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|non_gui_paint_core
operator|.
name|cury
expr_stmt|;
block|}
comment|/* Finish the painting */
name|paint_core_finish
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Cleanup */
name|paint_core_cleanup
argument_list|()
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
return|return
name|FALSE
return|;
block|}
end_function

end_unit

