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
file|"config/gimpconfig.h"
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
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-constructors.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gtkhwrapbox.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
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
file|"gimppenciltool.h"
end_include

begin_include
include|#
directive|include
file|"gimpdodgeburntool.h"
end_include

begin_include
include|#
directive|include
file|"gimpsmudgetool.h"
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
file|"libgimp/gimpintl.h"
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

begin_function_decl
specifier|static
name|void
name|paint_options_brush_clicked
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

begin_function
name|void
DECL|function|gimp_paint_options_gui (GimpToolOptions * tool_options)
name|gimp_paint_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GObject
modifier|*
name|config
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
name|optionmenu
decl_stmt|;
name|GtkWidget
modifier|*
name|mode_label
decl_stmt|;
name|GtkWidget
modifier|*
name|incremental_toggle
init|=
name|NULL
decl_stmt|;
name|options
operator|=
name|GIMP_PAINT_OPTIONS
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_CONTEXT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|tool_options
operator|->
name|main_vbox
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
comment|/*  the opacity scale  */
name|gimp_prop_scale_entry_new
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"Opacity:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
comment|/*  the paint mode menu  */
name|optionmenu
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
name|mode_label
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
name|optionmenu
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_CONVOLVE_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_DODGEBURN_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_SMUDGE_TOOL
condition|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|optionmenu
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_set_sensitive
argument_list|(
name|mode_label
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
comment|/*  the brush preview  */
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|!=
name|GIMP_TYPE_BUCKET_FILL_TOOL
operator|&&
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|!=
name|GIMP_TYPE_BLEND_TOOL
operator|&&
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|!=
name|GIMP_TYPE_INK_TOOL
condition|)
block|{
name|GimpBrush
modifier|*
name|brush
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|brush
operator|=
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
expr_stmt|;
name|button
operator|=
name|gtk_button_new
argument_list|()
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|24
argument_list|,
literal|24
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|button
argument_list|)
argument_list|,
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
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
literal|"Brush:"
argument_list|)
argument_list|,
literal|1.0
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
name|g_signal_connect_object
argument_list|(
name|options
argument_list|,
literal|"brush_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|preview
argument_list|,
name|G_CONNECT_SWAPPED
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
name|paint_options_brush_clicked
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/*  a separator after the common paint options  */
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_BLEND_TOOL
condition|)
block|{
name|GtkWidget
modifier|*
name|separator
decl_stmt|;
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
comment|/*  the "incremental" toggle  */
if|if
condition|(
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_AIRBRUSH_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_ERASER_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
name|tool_type
operator|==
name|GIMP_TYPE_PENCIL_TOOL
condition|)
block|{
name|incremental_toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"incremental"
argument_list|,
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
name|tool_options
operator|->
name|tool_info
operator|->
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
name|gradient_options
argument_list|,
name|options
argument_list|,
name|tool_options
operator|->
name|tool_info
operator|->
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
name|gradient_options_gui
argument_list|(
name|options
operator|->
name|gradient_options
argument_list|,
name|options
argument_list|,
name|tool_options
operator|->
name|tool_info
operator|->
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
name|config
operator|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
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
empty_stmt|;
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
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"pressure-pressure"
argument_list|,
name|_
argument_list|(
literal|"Hardness"
argument_list|)
argument_list|)
expr_stmt|;
empty_stmt|;
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
empty_stmt|;
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
empty_stmt|;
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
literal|"Size"
argument_list|)
argument_list|)
expr_stmt|;
empty_stmt|;
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
DECL|function|fade_options_gui (GimpGradientOptions * gradient,GimpPaintOptions * paint_options,GType tool_type)
name|fade_options_gui
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
parameter_list|)
block|{
name|GObject
modifier|*
name|config
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
name|unitmenu
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
condition|)
block|{
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
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
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
name|gtk_widget_show
argument_list|(
name|table
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
literal|"Fade Out"
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
name|gtk_widget_set_sensitive
argument_list|(
name|table
argument_list|,
name|gradient
operator|->
name|use_fade
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|button
argument_list|)
argument_list|,
literal|"set_sensitive"
argument_list|,
name|table
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
literal|1.0
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
name|unitmenu
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
name|unitmenu
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
name|unitmenu
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|unitmenu
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|spinbutton
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
name|unitmenu
decl_stmt|;
name|GtkWidget
modifier|*
name|enummenu
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_PAINTBRUSH_TOOL
condition|)
block|{
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
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
name|gtk_widget_show
argument_list|(
name|table
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
literal|"Use Color from Gradient"
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
name|gtk_widget_set_sensitive
argument_list|(
name|table
argument_list|,
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
literal|"set_sensitive"
argument_list|,
name|table
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
literal|0
argument_list|,
name|_
argument_list|(
literal|"Length:"
argument_list|)
argument_list|,
literal|1.0
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
name|unitmenu
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
name|unitmenu
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
name|unitmenu
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|unitmenu
argument_list|)
argument_list|,
literal|"set_digits"
argument_list|,
name|spinbutton
argument_list|)
expr_stmt|;
comment|/*  the gradient type  */
name|enummenu
operator|=
name|gimp_prop_enum_option_menu_new
argument_list|(
name|config
argument_list|,
literal|"gradient-type"
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
literal|1
argument_list|,
name|_
argument_list|(
literal|"Type:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|enummenu
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
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
name|void
DECL|function|paint_options_brush_clicked (GtkWidget * widget,gpointer data)
name|paint_options_brush_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|toplevel
decl_stmt|;
name|toplevel
operator|=
name|gtk_widget_get_toplevel
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_IS_DOCK
argument_list|(
name|toplevel
argument_list|)
condition|)
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toplevel
argument_list|)
operator|->
name|dialog_factory
argument_list|,
literal|"gimp-brush-grid"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

