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
file|"core/gimp.h"
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
file|"widgets/gtkhwrapbox.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpblendtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpbucketfilltool.h"
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
file|"gimpinktool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintbrushtool.h"
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
name|pressure_options_gui
parameter_list|(
name|GimpPressureOptions
modifier|*
name|pressure
parameter_list|,
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
name|fade_options_gui
parameter_list|(
name|GimpFadeOptions
modifier|*
name|fade
parameter_list|,
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
name|GimpGradientOptions
modifier|*
name|gradient
parameter_list|,
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
name|vbox
operator|=
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|tool_type
operator|!=
name|GIMP_TYPE_BUCKET_FILL_TOOL
operator|&&
name|tool_type
operator|!=
name|GIMP_TYPE_BLEND_TOOL
operator|&&
name|tool_type
operator|!=
name|GIMP_TYPE_INK_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_brush_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|2
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
block|}
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_BLEND_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_gradient_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
argument_list|,
literal|"gradient-reverse"
argument_list|,
literal|2
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
block|}
name|frame
operator|=
name|pressure_options_gui
argument_list|(
name|options
operator|->
name|pressure_options
argument_list|,
name|options
argument_list|,
name|tool_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
condition|)
block|{
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
name|frame
operator|=
name|fade_options_gui
argument_list|(
name|options
operator|->
name|fade_options
argument_list|,
name|options
argument_list|,
name|tool_type
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
condition|)
block|{
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
name|frame
operator|=
name|gradient_options_gui
argument_list|(
name|options
operator|->
name|gradient_options
argument_list|,
name|options
argument_list|,
name|tool_type
argument_list|,
name|incremental_toggle
argument_list|)
expr_stmt|;
if|if
condition|(
name|frame
condition|)
block|{
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
DECL|function|pressure_options_gui (GimpPressureOptions * pressure,GimpPaintOptions * paint_options,GType tool_type)
name|pressure_options_gui
parameter_list|(
name|GimpPressureOptions
modifier|*
name|pressure
parameter_list|,
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
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|wbox
init|=
name|NULL
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
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
name|GIMP_TYPE_DODGE_BURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|GtkWidget
modifier|*
name|inner_frame
decl_stmt|;
name|frame
operator|=
name|gimp_prop_expander_new
argument_list|(
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
argument_list|,
literal|"pressure-expanded"
argument_list|,
name|_
argument_list|(
literal|"Pressure sensitivity"
argument_list|)
argument_list|)
expr_stmt|;
name|inner_frame
operator|=
name|gimp_frame_new
argument_list|(
literal|"<expander>"
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|inner_frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|inner_frame
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
literal|7
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|inner_frame
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
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_DODGE_BURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-opacity"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
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
name|GIMP_TYPE_DODGE_BURN_TOOL
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-hardness"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-rate"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
comment|/*  the size toggle  */
if|if
condition|(
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
name|GIMP_TYPE_DODGE_BURN_TOOL
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-size"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
comment|/* the inverse size toggle */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-inverse-size"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
comment|/*  the color toggle  */
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-color"
argument_list|,
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
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
block|}
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|fade_options_gui (GimpFadeOptions * fade,GimpPaintOptions * paint_options,GType tool_type)
name|fade_options_gui
parameter_list|(
name|GimpFadeOptions
modifier|*
name|fade
parameter_list|,
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
init|=
name|NULL
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
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
name|GIMP_TYPE_DODGE_BURN_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"use-fade"
argument_list|,
name|_
argument_list|(
literal|"Fade out"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
argument_list|)
expr_stmt|;
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
if|if
condition|(
name|fade
operator|->
name|use_fade
condition|)
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_set_visible
argument_list|)
argument_list|,
name|table
argument_list|,
literal|0
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
block|}
return|return
name|frame
return|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gradient_options_gui (GimpGradientOptions * gradient,GimpPaintOptions * paint_options,GType tool_type,GtkWidget * incremental_toggle)
name|gradient_options_gui
parameter_list|(
name|GimpGradientOptions
modifier|*
name|gradient
parameter_list|,
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
init|=
name|NULL
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|menu
decl_stmt|;
name|GtkWidget
modifier|*
name|combo
decl_stmt|;
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
name|gimp_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"use-gradient"
argument_list|,
name|_
argument_list|(
literal|"Use color from gradient"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_frame_set_label_widget
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|button
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
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
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|table
argument_list|)
expr_stmt|;
if|if
condition|(
name|gradient
operator|->
name|use_gradient
condition|)
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|button
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_toggle_button_set_visible
argument_list|)
argument_list|,
name|table
argument_list|,
literal|0
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
name|gradient
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
name|gimp_gradient_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|config
argument_list|)
argument_list|,
literal|"gradient-reverse"
argument_list|,
literal|2
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
comment|/*  the gradient length scale  */
name|spinbutton
operator|=
name|gimp_prop_spin_button_new
argument_list|(
name|config
argument_list|,
literal|"gradient-length"
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
literal|1
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
comment|/*  the gradient unitmenu  */
name|menu
operator|=
name|gimp_prop_unit_menu_new
argument_list|(
name|config
argument_list|,
literal|"gradient-unit"
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
literal|"gradient-repeat"
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
block|}
return|return
name|frame
return|;
block|}
end_function

end_unit

