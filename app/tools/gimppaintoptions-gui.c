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
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
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
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreviewrenderergradient.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gtkhwrapbox.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewablebutton.h"
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

begin_function_decl
specifier|static
name|void
name|gradient_options_reverse_notify
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

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
name|button
decl_stmt|;
name|GimpDialogFactory
modifier|*
name|dialog_factory
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
name|gimp_tool_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|dialog_factory
operator|=
name|gimp_dialog_factory_from_name
argument_list|(
literal|"dock"
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
name|table_row
operator|++
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
name|gimp_viewable_button_new
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|context
argument_list|,
name|GIMP_PREVIEW_SIZE_SMALL
argument_list|,
literal|1
argument_list|,
name|dialog_factory
argument_list|,
literal|"gimp-brush-grid|gimp-brush-list"
argument_list|,
name|GIMP_STOCK_BRUSH
argument_list|,
name|_
argument_list|(
literal|"Open the brush selection dialog"
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
name|table_row
operator|++
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
block|}
comment|/*  the pattern preview  */
if|if
condition|(
name|tool_type
operator|==
name|GIMP_TYPE_BUCKET_FILL_TOOL
operator|||
name|tool_type
operator|==
name|GIMP_TYPE_CLONE_TOOL
condition|)
block|{
name|button
operator|=
name|gimp_viewable_button_new
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|,
name|context
argument_list|,
name|GIMP_PREVIEW_SIZE_SMALL
argument_list|,
literal|1
argument_list|,
name|dialog_factory
argument_list|,
literal|"gimp-pattern-grid|gimp-pattern-list"
argument_list|,
name|GIMP_STOCK_PATTERN
argument_list|,
name|_
argument_list|(
literal|"Open the pattern selection dialog"
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
name|table_row
operator|++
argument_list|,
name|_
argument_list|(
literal|"Pattern:"
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
block|}
comment|/*  the gradient preview  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
operator|||
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
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|gradient_button
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gradient_button
operator|=
name|gimp_viewable_button_new
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|,
name|context
argument_list|,
name|GIMP_PREVIEW_SIZE_LARGE
argument_list|,
literal|1
argument_list|,
name|dialog_factory
argument_list|,
literal|"gimp-gradient-list|gimp-gradient-grid"
argument_list|,
name|GIMP_STOCK_GRADIENT
argument_list|,
name|_
argument_list|(
literal|"Open the gradient selection dialog"
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  use smaller previews for the popup  */
name|GIMP_VIEWABLE_BUTTON
argument_list|(
name|gradient_button
argument_list|)
operator|->
name|preview_size
operator|=
name|GIMP_PREVIEW_SIZE_SMALL
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|gradient_button
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
name|gradient_button
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"gradient-reverse"
argument_list|,
name|_
argument_list|(
literal|"Reverse"
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
name|button
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|button
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
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|hbox
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|preview
operator|=
name|GTK_BIN
argument_list|(
name|gradient_button
argument_list|)
operator|->
name|child
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|config
argument_list|,
literal|"notify::gradient-reverse"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradient_options_reverse_notify
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gradient_options_reverse_notify
argument_list|(
name|GIMP_PAINT_OPTIONS
argument_list|(
name|config
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|GIMP_PREVIEW
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/*  the "incremental" toggle  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
operator|||
name|tool_options
operator|->
name|tool_info
operator|->
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
literal|"Hard Edge"
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
name|gtk_expander_new
argument_list|(
name|_
argument_list|(
literal|"Pressure Sensitivity"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_expander_set_expanded
argument_list|(
name|GTK_EXPANDER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|FALSE
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
literal|"pressure-pressure"
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
name|fade
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
name|combo
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
literal|1
argument_list|,
name|_
argument_list|(
literal|"Repeat:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|combo
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
DECL|function|gradient_options_reverse_notify (GimpPaintOptions * paint_options,GParamSpec * pspec,GimpPreview * preview)
name|gradient_options_reverse_notify
parameter_list|(
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpPreview
modifier|*
name|preview
parameter_list|)
block|{
name|GimpPreviewRendererGradient
modifier|*
name|rendergrad
decl_stmt|;
name|rendergrad
operator|=
name|GIMP_PREVIEW_RENDERER_GRADIENT
argument_list|(
name|preview
operator|->
name|renderer
argument_list|)
expr_stmt|;
name|gimp_preview_renderer_gradient_set_reverse
argument_list|(
name|rendergrad
argument_list|,
name|paint_options
operator|->
name|gradient_options
operator|->
name|gradient_reverse
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

