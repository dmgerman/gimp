begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * brush-editor.c  * Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__GNUC__
end_ifdef

begin_warning
warning|#
directive|warning
warning|GTK_DISABLE_DEPRECATED
end_warning

begin_endif
endif|#
directive|endif
end_endif

begin_undef
undef|#
directive|undef
name|GTK_DISABLE_DEPRECATED
end_undef

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"brush-editor.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_struct
DECL|struct|_BrushEditor
struct|struct
name|_BrushEditor
block|{
DECL|member|shell
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|scale_label
name|GtkWidget
modifier|*
name|scale_label
decl_stmt|;
DECL|member|options_box
name|GtkWidget
modifier|*
name|options_box
decl_stmt|;
DECL|member|name
name|GtkWidget
modifier|*
name|name
decl_stmt|;
DECL|member|radius_data
name|GtkAdjustment
modifier|*
name|radius_data
decl_stmt|;
DECL|member|hardness_data
name|GtkAdjustment
modifier|*
name|hardness_data
decl_stmt|;
DECL|member|angle_data
name|GtkAdjustment
modifier|*
name|angle_data
decl_stmt|;
DECL|member|aspect_ratio_data
name|GtkAdjustment
modifier|*
name|aspect_ratio_data
decl_stmt|;
comment|/*  Brush preview  */
DECL|member|brush_preview
name|GtkWidget
modifier|*
name|brush_preview
decl_stmt|;
DECL|member|brush
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
DECL|member|scale
name|gint
name|scale
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|brush_editor_close_callback
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
name|brush_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|brush_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|fevent
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_editor_update_brush
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_editor_preview_resize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_editor_clear_preview
parameter_list|(
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_editor_brush_dirty
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|brush_editor_brush_name_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|BrushEditor
modifier|*
DECL|function|brush_editor_new (Gimp * gimp)
name|brush_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|BrushEditor
modifier|*
name|brush_editor
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|slider
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|brush_editor
operator|=
name|g_new0
argument_list|(
name|BrushEditor
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|brush_editor
operator|->
name|shell
operator|=
name|gimp_dialog_new
argument_list|(
name|_
argument_list|(
literal|"Brush Editor"
argument_list|)
argument_list|,
literal|"generated_brush_editor"
argument_list|,
name|gimp_standard_help_func
argument_list|,
literal|"dialogs/brush_editor.html"
argument_list|,
name|GTK_WIN_POS_NONE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
literal|"_delete_event_"
argument_list|,
name|brush_editor_close_callback
argument_list|,
name|brush_editor
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_dialog_set_has_separator
argument_list|(
name|GTK_DIALOG
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
operator|->
name|action_area
argument_list|)
expr_stmt|;
name|vbox
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
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
comment|/* Brush's name */
name|brush_editor
operator|->
name|name
operator|=
name|gtk_entry_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|brush_editor
operator|->
name|name
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
name|brush_editor
operator|->
name|name
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|name
argument_list|)
argument_list|,
literal|"activate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_name_activate
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|name
argument_list|)
argument_list|,
literal|"focus_out_event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_name_focus_out
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
comment|/* brush's preview widget w/frame  */
name|brush_editor
operator|->
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|brush_editor
operator|->
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_IN
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|brush_editor
operator|->
name|frame
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
name|brush_editor
operator|->
name|frame
argument_list|)
expr_stmt|;
name|brush_editor
operator|->
name|preview
operator|=
name|gtk_preview_new
argument_list|(
name|GTK_PREVIEW_GRAYSCALE
argument_list|)
expr_stmt|;
name|gtk_preview_size
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
argument_list|,
literal|125
argument_list|,
literal|100
argument_list|)
expr_stmt|;
comment|/*  Enable auto-resizing of the preview but ensure a minimal size  */
name|gtk_widget_set_size_request
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|,
literal|125
argument_list|,
literal|100
argument_list|)
expr_stmt|;
name|gtk_preview_set_expand
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|brush_editor
operator|->
name|frame
argument_list|)
argument_list|,
name|brush_editor
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect_after
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|frame
argument_list|)
argument_list|,
literal|"size_allocate"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_preview_resize
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
comment|/* table for sliders/labels */
name|brush_editor
operator|->
name|scale_label
operator|=
name|gtk_label_new
argument_list|(
literal|"-1:1"
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|brush_editor
operator|->
name|scale_label
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
name|brush_editor
operator|->
name|scale_label
argument_list|)
expr_stmt|;
name|brush_editor
operator|->
name|scale
operator|=
operator|-
literal|1
expr_stmt|;
comment|/* table for sliders/labels */
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
comment|/*  brush radius scale  */
name|brush_editor
operator|->
name|radius_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|10.0
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|brush_editor
operator|->
name|radius_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|radius_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_update_brush
argument_list|)
argument_list|,
name|brush_editor
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
literal|"Radius:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  brush hardness scale  */
name|brush_editor
operator|->
name|hardness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|0.01
argument_list|,
literal|0.01
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|brush_editor
operator|->
name|hardness_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|hardness_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_update_brush
argument_list|)
argument_list|,
name|brush_editor
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
literal|"Hardness:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  brush aspect ratio scale  */
name|brush_editor
operator|->
name|aspect_ratio_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|20.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|brush_editor
operator|->
name|aspect_ratio_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|aspect_ratio_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_update_brush
argument_list|)
argument_list|,
name|brush_editor
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
literal|3
argument_list|,
name|_
argument_list|(
literal|"Aspect Ratio:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  brush angle scale  */
name|brush_editor
operator|->
name|angle_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gtk_adjustment_new
argument_list|(
literal|00.0
argument_list|,
literal|0.0
argument_list|,
literal|180.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
argument_list|)
expr_stmt|;
name|slider
operator|=
name|gtk_hscale_new
argument_list|(
name|brush_editor
operator|->
name|angle_data
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|slider
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|angle_data
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_update_brush
argument_list|)
argument_list|,
name|brush_editor
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
literal|"Angle:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
name|slider
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|3
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
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|brush_editor
return|;
block|}
end_function

begin_function
name|void
DECL|function|brush_editor_set_brush (BrushEditor * brush_editor,GimpBrush * gbrush)
name|brush_editor_set_brush
parameter_list|(
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|,
name|GimpBrush
modifier|*
name|gbrush
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|brush_editor
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|gbrush
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_editor
operator|->
name|brush
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|,
name|brush_editor_brush_dirty
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|,
name|brush_editor_brush_name_changed
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|brush_editor
operator|->
name|brush
operator|=
name|NULL
expr_stmt|;
block|}
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|gbrush
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"invalidate_preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_brush_dirty
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"name_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brush_editor_brush_name_changed
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brush_editor
operator|->
name|radius_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_radius
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brush_editor
operator|->
name|hardness_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_hardness
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brush_editor
operator|->
name|angle_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_angle
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|brush_editor
operator|->
name|aspect_ratio_data
argument_list|)
argument_list|,
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|brush_editor
operator|->
name|name
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|gbrush
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|brush_editor
operator|->
name|brush
operator|=
name|brush
expr_stmt|;
name|g_object_ref
argument_list|(
name|G_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|brush_editor_brush_dirty
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|brush_editor_close_callback (GtkWidget * widget,gpointer data)
name|brush_editor_close_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|BrushEditor
modifier|*
name|brush_editor
init|=
operator|(
name|BrushEditor
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_VISIBLE
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
condition|)
name|gtk_widget_hide
argument_list|(
name|brush_editor
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_name_activate (GtkWidget * widget,BrushEditor * brush_editor)
name|brush_editor_name_activate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|entry_text
decl_stmt|;
name|entry_text
operator|=
name|gtk_entry_get_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|,
name|entry_text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|brush_editor_name_focus_out (GtkWidget * widget,GdkEventFocus * fevent,BrushEditor * brush_editor)
name|brush_editor_name_focus_out
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventFocus
modifier|*
name|fevent
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
name|brush_editor_name_activate
argument_list|(
name|widget
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_update_brush (GtkAdjustment * adjustment,BrushEditor * brush_editor)
name|brush_editor_update_brush
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
if|if
condition|(
name|brush_editor
operator|->
name|brush
operator|&&
operator|(
operator|(
name|brush_editor
operator|->
name|radius_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_radius
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|brush_editor
operator|->
name|hardness_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_hardness
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|brush_editor
operator|->
name|aspect_ratio_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
operator|)
operator|||
operator|(
name|brush_editor
operator|->
name|angle_data
operator|->
name|value
operator|!=
name|gimp_brush_generated_get_angle
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
operator|)
operator|)
condition|)
block|{
name|gimp_brush_generated_freeze
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_radius
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|,
name|brush_editor
operator|->
name|radius_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_hardness
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|,
name|brush_editor
operator|->
name|hardness_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_aspect_ratio
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|,
name|brush_editor
operator|->
name|aspect_ratio_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_angle
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|,
name|brush_editor
operator|->
name|angle_data
operator|->
name|value
argument_list|)
expr_stmt|;
name|gimp_brush_generated_thaw
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_preview_resize (GtkWidget * widget,GtkAllocation * allocation,BrushEditor * brush_editor)
name|brush_editor_preview_resize
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
if|if
condition|(
name|brush_editor
operator|->
name|brush
condition|)
name|brush_editor_brush_dirty
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|,
name|brush_editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_clear_preview (BrushEditor * brush_editor)
name|brush_editor_clear_preview
parameter_list|(
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
name|guchar
modifier|*
name|buf
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
expr_stmt|;
comment|/*  Set the buffer to white  */
name|memset
argument_list|(
name|buf
argument_list|,
literal|255
argument_list|,
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
expr_stmt|;
comment|/*  Set the image buffer to white  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|height
condition|;
name|i
operator|++
control|)
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
argument_list|,
name|buf
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_brush_dirty (GimpBrush * brush,BrushEditor * brush_editor)
name|brush_editor_brush_dirty
parameter_list|(
name|GimpBrush
modifier|*
name|brush
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|width
decl_stmt|,
name|yend
decl_stmt|,
name|ystart
decl_stmt|,
name|xo
decl_stmt|;
name|gint
name|scale
decl_stmt|;
name|guchar
modifier|*
name|src
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
name|brush_editor_clear_preview
argument_list|(
name|brush_editor
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|==
name|NULL
operator|||
name|brush
operator|->
name|mask
operator|==
name|NULL
condition|)
return|return;
name|scale
operator|=
name|MAX
argument_list|(
name|ceil
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
operator|(
name|float
operator|)
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
argument_list|,
name|ceil
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
operator|(
name|float
operator|)
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|ystart
operator|=
literal|0
expr_stmt|;
name|xo
operator|=
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
operator|/
literal|2
operator|-
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
operator|(
literal|2
operator|*
name|scale
operator|)
expr_stmt|;
name|ystart
operator|=
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|height
operator|/
literal|2
operator|-
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
operator|(
literal|2
operator|*
name|scale
operator|)
expr_stmt|;
name|yend
operator|=
name|ystart
operator|+
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
name|scale
expr_stmt|;
name|width
operator|=
name|CLAMP
argument_list|(
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
name|scale
argument_list|,
literal|0
argument_list|,
name|brush_editor
operator|->
name|preview
operator|->
name|allocation
operator|.
name|width
argument_list|)
expr_stmt|;
name|buf
operator|=
name|g_new
argument_list|(
name|guchar
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|=
operator|(
name|guchar
operator|*
operator|)
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|mask
argument_list|)
expr_stmt|;
for|for
control|(
name|y
operator|=
name|ystart
init|;
name|y
operator|<
name|yend
condition|;
name|y
operator|++
control|)
block|{
comment|/*  Invert the mask for display.        */
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|width
condition|;
name|x
operator|++
control|)
name|buf
index|[
name|x
index|]
operator|=
literal|255
operator|-
name|src
index|[
name|x
operator|*
name|scale
index|]
expr_stmt|;
name|gtk_preview_draw_row
argument_list|(
name|GTK_PREVIEW
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
argument_list|,
name|buf
argument_list|,
name|xo
argument_list|,
name|y
argument_list|,
name|width
argument_list|)
expr_stmt|;
name|src
operator|+=
name|brush
operator|->
name|mask
operator|->
name|width
operator|*
name|scale
expr_stmt|;
block|}
name|g_free
argument_list|(
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush_editor
operator|->
name|scale
operator|!=
name|scale
condition|)
block|{
name|gchar
name|str
index|[
literal|255
index|]
decl_stmt|;
name|brush_editor
operator|->
name|scale
operator|=
name|scale
expr_stmt|;
name|g_snprintf
argument_list|(
name|str
argument_list|,
sizeof|sizeof
argument_list|(
name|str
argument_list|)
argument_list|,
literal|"%d:1"
argument_list|,
name|scale
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|brush_editor
operator|->
name|scale_label
argument_list|)
argument_list|,
name|str
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_queue_draw
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brush_editor_brush_name_changed (GtkWidget * widget,BrushEditor * brush_editor)
name|brush_editor_brush_name_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|BrushEditor
modifier|*
name|brush_editor
parameter_list|)
block|{
name|gtk_entry_set_text
argument_list|(
name|GTK_ENTRY
argument_list|(
name|brush_editor
operator|->
name|name
argument_list|)
argument_list|,
name|gimp_object_get_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush_editor
operator|->
name|brush
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

