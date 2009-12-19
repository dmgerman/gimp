begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimppaintoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewablebox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolvetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburntool.h"
end_include

begin_include
include|#
directive|include
file|"gimperasertool.h"
end_include

begin_include
include|#
directive|include
file|"gimphealtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpinktool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpperspectiveclonetool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgetool.h"
end_include

begin_include
include|#
directive|include
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|fade_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gradient_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|GtkWidget
modifier|*
name|incremental_toggle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|jitter_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_paint_options_gui (GimpToolOptions * tool_options)
name|gimp_paint_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GimpPaintOptions
modifier|*
name|options
init|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|incremental_toggle
init|=
name|NULL
decl_stmt|;
name|gint
name|table_row
init|=
literal|0
decl_stmt|;
name|GType
name|tool_type
decl_stmt|;
name|tool_type
operator|=
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
expr_stmt|;
comment|/*  the main table  */
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
literal|2
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
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|GIMP_PAINT_OPTIONS_TABLE_KEY
argument_list|,
name|table
argument_list|)
expr_stmt|;
comment|/*  the paint mode menu  */
name|menu
operator|=
name|gimp_prop_paint_mode_menu_new
argument_list|(
name|config
argument_list|,
literal|"paint-mode"
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|label
operator|=
name|gimp_table_attach_aligned
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Mode:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|menu
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGE_BURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|menu
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|label
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  the opacity scale  */
name|gimp_prop_opacity_entry_new
argument_list|(
name|config
argument_list|,
literal|"opacity"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Opacity:"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  the brush  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_BRUSH_TOOL
argument_list|)
condition|)
block|{
name|GtkObject
modifier|*
name|adj_scale
decl_stmt|;
name|GtkObject
modifier|*
name|adj_angle
decl_stmt|;
name|GtkObject
modifier|*
name|adj_aspect_ratio
decl_stmt|;
name|button
operator|=
name|gimp_prop_brush_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|"brush-view-type"
argument_list|,
literal|"brush-view-size"
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
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Brush:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|adj_scale
operator|=
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"brush-scale"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Scale:"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_scale_entry_set_logarithmic
argument_list|(
name|adj_scale
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|adj_aspect_ratio
operator|=
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"brush-aspect-ratio"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Aspect Ratio:"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_scale_entry_set_logarithmic
argument_list|(
name|adj_aspect_ratio
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|adj_angle
operator|=
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"brush-angle"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Angle:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|5.0
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_BRUSH_TOOL
argument_list|)
condition|)
block|{
name|frame
operator|=
name|fade_options_gui
argument_list|(
name|options
argument_list|,
name|tool_type
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|frame
operator|=
name|jitter_options_gui
argument_list|(
name|options
argument_list|,
name|tool_type
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
comment|/*  the "incremental" toggle  */
if|if
condition|(
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
name|GIMP_TYPE_ERASER_TOOL
condition|)
block|{
name|incremental_toggle
operator|=
name|gimp_prop_enum_check_button_new
argument_list|(
name|config
argument_list|,
literal|"application-mode"
argument_list|,
name|_
argument_list|(
literal|"Incremental"
argument_list|)
argument_list|,
name|GIMP_PAINT_CONSTANT
argument_list|,
name|GIMP_PAINT_INCREMENTAL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|incremental_toggle
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
name|incremental_toggle
argument_list|)
expr_stmt|;
block|}
comment|/* the "hard edge" toggle */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_HEAL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_PERSPECTIVE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGE_BURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"hard"
argument_list|,
name|_
argument_list|(
literal|"Hard edge"
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
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
condition|)
block|{
name|frame
operator|=
name|gradient_options_gui
argument_list|(
name|options
argument_list|,
name|tool_type
argument_list|,
name|incremental_toggle
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
block|}
return|return
name|vbox
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|fade_options_gui (GimpPaintOptions * paint_options,GType tool_type)
name|fade_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|spinbutton
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
name|GtkWidget
modifier|*
name|checkbox
decl_stmt|;
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
literal|2
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"use-fade"
argument_list|,
name|_
argument_list|(
literal|"Fade out"
argument_list|)
argument_list|,
name|table
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  the fade-out sizeentry  */
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"fade-length"
argument_list|,
literal|1.0
argument_list|,
literal|50.0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_entry_set_width_chars
argument_list|(
name|GTK_ENTRY
argument_list|(
name|spinbutton
argument_list|)
argument_list|,
literal|6
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
literal|"Length:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|spinbutton
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  the fade-out unitmenu  */
name|menu
operator|=
name|gimp_prop_unit_menu_new
argument_list|(
name|config
argument_list|,
literal|"fade-unit"
argument_list|,
literal|"%a"
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
name|menu
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
name|gtk_widget_show
argument_list|(
name|menu
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
name|gimp_unit_menu_set_pixel_digits
argument_list|(
name|GIMP_UNIT_MENU
argument_list|(
name|menu
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the repeat type  */
name|combo
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|config
argument_list|,
literal|"fade-repeat"
argument_list|,
literal|0
argument_list|,
literal|0
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
literal|"Repeat:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|combo
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|checkbox
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"fade-reverse"
argument_list|,
name|_
argument_list|(
literal|"Reverse"
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
name|checkbox
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|,
literal|4
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
name|checkbox
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|jitter_options_gui (GimpPaintOptions * paint_options,GType tool_type)
name|jitter_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
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
literal|2
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"use-jitter"
argument_list|,
name|_
argument_list|(
literal|"Apply Jitter"
argument_list|)
argument_list|,
name|table
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"jitter-amount"
argument_list|,
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
literal|"Amount:"
argument_list|)
argument_list|,
literal|0.01
argument_list|,
literal|0.1
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|5.0
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gradient_options_gui (GimpPaintOptions * paint_options,GType tool_type,GtkWidget * incremental_toggle)
name|gradient_options_gui
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GType
name|tool_type
parameter_list|,
name|GtkWidget
modifier|*
name|incremental_toggle
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
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
literal|2
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
name|frame
operator|=
name|gimp_prop_expanding_frame_new
argument_list|(
name|config
argument_list|,
literal|"use-gradient"
argument_list|,
name|_
argument_list|(
literal|"Use color from gradient"
argument_list|)
argument_list|,
name|table
argument_list|,
operator|&
name|button
argument_list|)
expr_stmt|;
if|if
condition|(
name|incremental_toggle
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|incremental_toggle
argument_list|,
operator|!
name|paint_options
operator|->
name|gradient_options
operator|->
name|use_gradient
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"inverse_sensitive"
argument_list|,
name|incremental_toggle
argument_list|)
expr_stmt|;
block|}
comment|/*  the gradient view  */
name|button
operator|=
name|gimp_prop_gradient_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|2
argument_list|,
literal|"gradient-view-type"
argument_list|,
literal|"gradient-view-size"
argument_list|,
literal|"gradient-reverse"
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
literal|"Gradient:"
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.5
argument_list|,
name|button
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|frame
return|;
block|}
end_function

end_unit

