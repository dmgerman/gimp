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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gtkhwrapbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"tool.h"
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

begin_function_decl
specifier|static
name|PaintPressureOptions
modifier|*
name|paint_pressure_options_new
parameter_list|(
name|GtkType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|paint_pressure_options_reset
parameter_list|(
name|PaintPressureOptions
modifier|*
name|pressure_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|paint_options_opacity_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|paint_options_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|paint_options_paint_mode_update
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
name|paint_options_paint_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  declared extern in paint_options.h  */
end_comment

begin_decl_stmt
DECL|variable|non_gui_pressure_options
name|PaintPressureOptions
name|non_gui_pressure_options
init|=
block|{
name|NULL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|NULL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|NULL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|NULL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|NULL
block|,
name|FALSE
block|,
name|FALSE
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  a list of all PaintOptions  */
end_comment

begin_decl_stmt
DECL|variable|paint_options_list
specifier|static
name|GSList
modifier|*
name|paint_options_list
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|paint_options_init (PaintOptions * options,GtkType tool_type,ToolOptionsResetFunc reset_func)
name|paint_options_init
parameter_list|(
name|PaintOptions
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
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
name|tool_info
operator|=
name|tool_manager_get_info_by_type
argument_list|(
name|tool_type
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
block|{
name|g_warning
argument_list|(
literal|"%s(): no tool info registered for %s"
argument_list|,
name|G_GNUC_FUNCTION
argument_list|,
name|gtk_type_name
argument_list|(
name|tool_type
argument_list|)
argument_list|)
expr_stmt|;
block|}
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
comment|/*  initialize the paint options structure  */
name|options
operator|->
name|global
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|opacity_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|paint_mode_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|context
operator|=
name|tool_info
operator|->
name|context
expr_stmt|;
name|options
operator|->
name|incremental_w
operator|=
name|NULL
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
name|pressure_options
operator|=
name|NULL
expr_stmt|;
comment|/*  the main vbox  */
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
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
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
name|options
operator|->
name|paint_vbox
operator|=
name|vbox
expr_stmt|;
comment|/*  the main table  */
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
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the opacity scale  */
name|options
operator|->
name|opacity_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|gimp_context_get_opacity
argument_list|(
name|tool_info
operator|->
name|context
argument_list|)
operator|*
literal|100
argument_list|,
literal|0.0
argument_list|,
literal|100.0
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
name|opacity_w
argument_list|)
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
name|opacity_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|paint_options_opacity_adjustment_update
argument_list|)
argument_list|,
name|tool_info
operator|->
name|context
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
literal|"Opacity:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|scale
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_info
operator|->
name|context
argument_list|)
argument_list|,
literal|"opacity_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|paint_options_opacity_changed
argument_list|)
argument_list|,
name|options
operator|->
name|opacity_w
argument_list|)
expr_stmt|;
comment|/*  the paint mode menu  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_BUCKET_FILL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_BLEND_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_INK_TOOL
condition|)
block|{
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
name|options
operator|->
name|paint_mode_w
operator|=
name|paint_mode_menu_new
argument_list|(
name|paint_options_paint_mode_update
argument_list|,
name|options
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|tool_info
operator|->
name|context
argument_list|)
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
literal|"Mode:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|options
operator|->
name|paint_mode_w
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|tool_info
operator|->
name|context
argument_list|)
argument_list|,
literal|"paint_mode_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|paint_options_paint_mode_changed
argument_list|)
argument_list|,
name|options
operator|->
name|paint_mode_w
argument_list|)
expr_stmt|;
block|}
comment|/*  show the main table  */
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
comment|/*  a separator after the common paint options which can be global  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_BUCKET_FILL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_BLEND_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_INK_TOOL
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
if|if
condition|(
operator|!
name|global_paint_options
condition|)
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
comment|/*  the "incremental" toggle  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
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
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
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
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_toggle_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|incremental
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
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|incremental_w
argument_list|)
expr_stmt|;
block|}
name|options
operator|->
name|pressure_options
operator|=
name|paint_pressure_options_new
argument_list|(
name|tool_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|pressure_options
operator|->
name|frame
condition|)
block|{
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
name|options
operator|->
name|pressure_options
operator|->
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
name|options
operator|->
name|pressure_options
operator|->
name|frame
argument_list|)
expr_stmt|;
block|}
comment|/*  register this Paintoptions structure  */
name|paint_options_list
operator|=
name|g_slist_prepend
argument_list|(
name|paint_options_list
argument_list|,
name|options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|PaintOptions
modifier|*
DECL|function|paint_options_new (GtkType tool_type,ToolOptionsResetFunc reset_func)
name|paint_options_new
parameter_list|(
name|GtkType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
block|{
name|PaintOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|g_new
argument_list|(
name|PaintOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
name|options
argument_list|,
name|tool_type
argument_list|,
name|reset_func
argument_list|)
expr_stmt|;
if|if
condition|(
name|global_paint_options
operator|&&
name|options
operator|->
name|global
condition|)
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|global
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|void
DECL|function|paint_options_reset (PaintOptions * options)
name|paint_options_reset
parameter_list|(
name|PaintOptions
modifier|*
name|options
parameter_list|)
block|{
name|GimpContext
modifier|*
name|default_context
decl_stmt|;
name|default_context
operator|=
name|gimp_context_get_default
argument_list|()
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|opacity_w
condition|)
block|{
name|gimp_context_set_opacity
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
operator|->
name|context
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|default_context
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|paint_mode_w
condition|)
block|{
name|gimp_context_set_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
operator|->
name|context
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|default_context
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|options
operator|->
name|incremental_w
condition|)
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
name|options
operator|->
name|incremental_d
argument_list|)
expr_stmt|;
block|}
name|paint_pressure_options_reset
argument_list|(
name|options
operator|->
name|pressure_options
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|paint_options_set_global (gboolean global)
name|paint_options_set_global
parameter_list|(
name|gboolean
name|global
parameter_list|)
block|{
name|PaintOptions
modifier|*
name|options
decl_stmt|;
name|GSList
modifier|*
name|list
decl_stmt|;
name|global
operator|=
name|global
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|global_paint_options
operator|==
name|global
condition|)
return|return;
name|global_paint_options
operator|=
name|global
expr_stmt|;
for|for
control|(
name|list
operator|=
name|paint_options_list
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|options
operator|=
operator|(
name|PaintOptions
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|global
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|paint_vbox
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options
operator|->
name|paint_vbox
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|options
operator|->
name|paint_vbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|global
operator|&&
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options
operator|->
name|global
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|global
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|options
operator|->
name|paint_vbox
operator|&&
operator|!
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options
operator|->
name|paint_vbox
argument_list|)
condition|)
name|gtk_widget_show
argument_list|(
name|options
operator|->
name|paint_vbox
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|global
operator|&&
name|GTK_WIDGET_VISIBLE
argument_list|(
name|options
operator|->
name|global
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|options
operator|->
name|global
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|paint_mode_menu_new (GtkSignalFunc callback,gpointer data,LayerModeEffects initial)
name|paint_mode_menu_new
parameter_list|(
name|GtkSignalFunc
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|LayerModeEffects
name|initial
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|menu
operator|=
name|gimp_option_menu_new2
argument_list|(
name|FALSE
argument_list|,
name|callback
argument_list|,
name|data
argument_list|,
operator|(
name|gpointer
operator|)
name|initial
argument_list|,
name|_
argument_list|(
literal|"Normal"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|NORMAL_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dissolve"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|DISSOLVE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Behind"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|BEHIND_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Multiply"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|MULTIPLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Divide"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|DIVIDE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Screen"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|SCREEN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Overlay"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|OVERLAY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Dodge"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|DODGE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Burn"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|BURN_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hard Light"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|HARDLIGHT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Difference"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|DIFFERENCE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Addition"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|ADDITION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Subtract"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|SUBTRACT_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Darken Only"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|DARKEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Lighten Only"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|LIGHTEN_ONLY_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Hue"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|HUE_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Saturation"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|SATURATION_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|COLOR_MODE
argument_list|,
name|NULL
argument_list|,
name|_
argument_list|(
literal|"Value"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|VALUE_MODE
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|menu
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|PaintPressureOptions
modifier|*
DECL|function|paint_pressure_options_new (GtkType tool_type)
name|paint_pressure_options_new
parameter_list|(
name|GtkType
name|tool_type
parameter_list|)
block|{
name|PaintPressureOptions
modifier|*
name|pressure
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|wbox
init|=
name|NULL
decl_stmt|;
name|pressure
operator|=
name|g_new
argument_list|(
name|PaintPressureOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pressure
operator|->
name|opacity
operator|=
name|pressure
operator|->
name|opacity_d
operator|=
name|TRUE
expr_stmt|;
name|pressure
operator|->
name|pressure
operator|=
name|pressure
operator|->
name|pressure_d
operator|=
name|TRUE
expr_stmt|;
name|pressure
operator|->
name|rate
operator|=
name|pressure
operator|->
name|rate_d
operator|=
name|FALSE
expr_stmt|;
name|pressure
operator|->
name|size
operator|=
name|pressure
operator|->
name|size_d
operator|=
name|FALSE
expr_stmt|;
name|pressure
operator|->
name|color
operator|=
name|pressure
operator|->
name|color_d
operator|=
name|FALSE
expr_stmt|;
name|pressure
operator|->
name|opacity_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|pressure_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|rate_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|size_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|color_w
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|_
argument_list|(
literal|"Pressure Sensitivity"
argument_list|)
argument_list|)
expr_stmt|;
name|wbox
operator|=
name|gtk_hwrap_box_new
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_wrap_box_set_aspect_ratio
argument_list|(
name|GTK_WRAP_BOX
argument_list|(
name|wbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|wbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|wbox
argument_list|)
expr_stmt|;
block|}
comment|/*  the opacity toggle  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGEBURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
name|pressure
operator|->
name|opacity_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Opacity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|pressure
operator|->
name|opacity_w
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure
operator|->
name|opacity_w
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
name|pressure
operator|->
name|opacity
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|opacity_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|opacity_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure
operator|->
name|opacity_w
argument_list|)
expr_stmt|;
block|}
comment|/*  the pressure toggle  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGEBURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|pressure
operator|->
name|pressure_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Hardness"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|pressure
operator|->
name|pressure_w
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure
operator|->
name|pressure_w
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
name|pressure
operator|->
name|pressure
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|pressure_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|pressure_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure
operator|->
name|pressure_w
argument_list|)
expr_stmt|;
block|}
comment|/*  the rate toggle */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|pressure
operator|->
name|rate_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Rate"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|pressure
operator|->
name|rate_w
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure
operator|->
name|rate_w
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
name|pressure
operator|->
name|rate
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|rate_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|rate_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure
operator|->
name|rate_w
argument_list|)
expr_stmt|;
block|}
comment|/*  the size toggle  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGEBURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
name|pressure
operator|->
name|size_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Size"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|pressure
operator|->
name|size_w
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure
operator|->
name|size_w
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
name|pressure
operator|->
name|size
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|size_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|size_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure
operator|->
name|size_w
argument_list|)
expr_stmt|;
block|}
comment|/*  the color toggle  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
name|pressure
operator|->
name|color_w
operator|=
name|gtk_check_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Color"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|wbox
argument_list|)
argument_list|,
name|pressure
operator|->
name|color_w
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|pressure
operator|->
name|color_w
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
name|pressure
operator|->
name|color
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|color_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|color_d
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|pressure
operator|->
name|color_w
argument_list|)
expr_stmt|;
block|}
name|pressure
operator|->
name|frame
operator|=
name|frame
expr_stmt|;
return|return
name|pressure
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_pressure_options_reset (PaintPressureOptions * pressure)
name|paint_pressure_options_reset
parameter_list|(
name|PaintPressureOptions
modifier|*
name|pressure
parameter_list|)
block|{
if|if
condition|(
name|pressure
operator|->
name|opacity_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|opacity_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|opacity_d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pressure
operator|->
name|pressure_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|pressure_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|pressure_d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pressure
operator|->
name|rate_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|rate_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|rate_d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pressure
operator|->
name|size_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|size_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|size_d
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|pressure
operator|->
name|color_w
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|pressure
operator|->
name|color_w
argument_list|)
argument_list|,
name|pressure
operator|->
name|color_d
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_options_opacity_adjustment_update (GtkAdjustment * adjustment,gpointer data)
name|paint_options_opacity_adjustment_update
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|adjustment
argument_list|)
expr_stmt|;
name|gimp_context_set_opacity
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
argument_list|,
name|adjustment
operator|->
name|value
operator|/
literal|100
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|adjustment
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_options_opacity_changed (GimpContext * context,gdouble opacity,gpointer data)
name|paint_options_opacity_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|data
argument_list|)
argument_list|,
name|opacity
operator|*
literal|100
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|data
argument_list|)
argument_list|,
name|context
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_options_paint_mode_update (GtkWidget * widget,gpointer data)
name|paint_options_paint_mode_update
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|LayerModeEffects
name|paint_mode
decl_stmt|;
name|PaintOptions
modifier|*
name|options
decl_stmt|;
name|paint_mode
operator|=
operator|(
name|LayerModeEffects
operator|)
name|gtk_object_get_user_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|=
operator|(
name|PaintOptions
operator|*
operator|)
name|data
expr_stmt|;
name|gtk_signal_handler_block_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|paint_mode_w
argument_list|)
expr_stmt|;
name|gimp_context_set_paint_mode
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|options
operator|->
name|context
argument_list|)
argument_list|,
name|paint_mode
argument_list|)
expr_stmt|;
name|gtk_signal_handler_unblock_by_data
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|context
argument_list|)
argument_list|,
name|options
operator|->
name|paint_mode_w
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|paint_options_paint_mode_changed (GimpContext * context,LayerModeEffects paint_mode,gpointer data)
name|paint_options_paint_mode_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|LayerModeEffects
name|paint_mode
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_option_menu_set_history
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|data
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|paint_mode
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

