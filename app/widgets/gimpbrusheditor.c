begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpbrusheditor.c  * Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrusheditor.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|BRUSH_PREVIEW_WIDTH
define|#
directive|define
name|BRUSH_PREVIEW_WIDTH
value|128
end_define

begin_define
DECL|macro|BRUSH_PREVIEW_HEIGHT
define|#
directive|define
name|BRUSH_PREVIEW_HEIGHT
value|96
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_brush_editor_class_init
parameter_list|(
name|GimpBrushEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_editor_init
parameter_list|(
name|GimpBrushEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_editor_update_brush
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDataEditorClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_brush_editor_get_type (void)
name|gimp_brush_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpBrushEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_brush_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpBrushEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_brush_editor_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DATA_EDITOR
argument_list|,
literal|"GimpBrushEditor"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_editor_class_init (GimpBrushEditorClass * klass)
name|gimp_brush_editor_class_init
parameter_list|(
name|GimpBrushEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpDataEditorClass
modifier|*
name|editor_class
decl_stmt|;
name|editor_class
operator|=
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|editor_class
operator|->
name|set_data
operator|=
name|gimp_brush_editor_set_data
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_editor_init (GimpBrushEditor * editor)
name|gimp_brush_editor_init
parameter_list|(
name|GimpBrushEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
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
name|editor
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
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|editor
operator|->
name|preview
operator|=
name|gimp_preview_new_full_by_types
argument_list|(
name|GIMP_TYPE_PREVIEW
argument_list|,
name|GIMP_TYPE_BRUSH
argument_list|,
name|BRUSH_PREVIEW_WIDTH
argument_list|,
name|BRUSH_PREVIEW_HEIGHT
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|editor
operator|->
name|preview
argument_list|,
name|BRUSH_PREVIEW_WIDTH
argument_list|,
name|BRUSH_PREVIEW_HEIGHT
argument_list|)
expr_stmt|;
name|gimp_preview_set_expand
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|editor
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
name|frame
argument_list|)
argument_list|,
name|editor
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
operator|->
name|preview
argument_list|)
expr_stmt|;
comment|/* table for sliders/labels */
name|editor
operator|->
name|options_table
operator|=
name|gtk_table_new
argument_list|(
literal|4
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|editor
operator|->
name|options_table
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
name|editor
operator|->
name|options_table
argument_list|)
expr_stmt|;
comment|/*  brush radius scale  */
name|editor
operator|->
name|radius_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
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
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|1000.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|radius_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_editor_update_brush
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  brush hardness scale  */
name|editor
operator|->
name|hardness_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
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
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|1.0
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
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|hardness_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_editor_update_brush
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  brush aspect ratio scale  */
name|editor
operator|->
name|aspect_ratio_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
name|_
argument_list|(
literal|"Aspect Ratio:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|,
literal|20.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|aspect_ratio_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_editor_update_brush
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
comment|/*  brush angle scale  */
name|editor
operator|->
name|angle_data
operator|=
name|GTK_ADJUSTMENT
argument_list|(
name|gimp_scale_entry_new
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|options_table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|3
argument_list|,
name|_
argument_list|(
literal|"Angle:"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|5
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
literal|180.0
argument_list|,
literal|0.1
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|editor
operator|->
name|angle_data
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_brush_editor_update_brush
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_editor_set_data (GimpDataEditor * editor,GimpData * data)
name|gimp_brush_editor_set_data
parameter_list|(
name|GimpDataEditor
modifier|*
name|editor
parameter_list|,
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpBrushEditor
modifier|*
name|brush_editor
decl_stmt|;
name|gdouble
name|radius
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|hardness
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|ratio
init|=
literal|0.0
decl_stmt|;
name|gdouble
name|angle
init|=
literal|0.0
decl_stmt|;
name|brush_editor
operator|=
name|GIMP_BRUSH_EDITOR
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|GIMP_DATA_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_data
argument_list|(
name|editor
argument_list|,
name|data
argument_list|)
expr_stmt|;
name|gimp_preview_set_viewable
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|brush_editor
operator|->
name|preview
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|data
operator|&&
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|editor
operator|->
name|data
argument_list|)
condition|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|editor
operator|->
name|data
argument_list|)
expr_stmt|;
name|radius
operator|=
name|gimp_brush_generated_get_radius
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|hardness
operator|=
name|gimp_brush_generated_get_hardness
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|ratio
operator|=
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|angle
operator|=
name|gimp_brush_generated_get_angle
argument_list|(
name|brush
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_set_sensitive
argument_list|(
name|brush_editor
operator|->
name|options_table
argument_list|,
name|editor
operator|->
name|data_editable
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|brush_editor
operator|->
name|radius_data
argument_list|,
name|radius
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|brush_editor
operator|->
name|hardness_data
argument_list|,
name|hardness
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|brush_editor
operator|->
name|aspect_ratio_data
argument_list|,
name|ratio
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|brush_editor
operator|->
name|angle_data
argument_list|,
name|angle
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDataEditor
modifier|*
DECL|function|gimp_brush_editor_new (Gimp * gimp)
name|gimp_brush_editor_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpBrushEditor
modifier|*
name|brush_editor
decl_stmt|;
name|brush_editor
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_BRUSH_EDITOR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_data_editor_construct
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|brush_editor
argument_list|)
argument_list|,
name|gimp
operator|->
name|brush_factory
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|g_object_unref
argument_list|(
name|brush_editor
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|GIMP_DATA_EDITOR
argument_list|(
name|brush_editor
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_brush_editor_update_brush (GtkAdjustment * adjustment,GimpBrushEditor * editor)
name|gimp_brush_editor_update_brush
parameter_list|(
name|GtkAdjustment
modifier|*
name|adjustment
parameter_list|,
name|GimpBrushEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|gdouble
name|radius
decl_stmt|;
name|gdouble
name|hardness
decl_stmt|;
name|gdouble
name|ratio
decl_stmt|;
name|gdouble
name|angle
decl_stmt|;
if|if
condition|(
operator|!
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|data
argument_list|)
condition|)
return|return;
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|GIMP_DATA_EDITOR
argument_list|(
name|editor
argument_list|)
operator|->
name|data
argument_list|)
expr_stmt|;
name|radius
operator|=
name|editor
operator|->
name|radius_data
operator|->
name|value
expr_stmt|;
name|hardness
operator|=
name|editor
operator|->
name|hardness_data
operator|->
name|value
expr_stmt|;
name|ratio
operator|=
name|editor
operator|->
name|aspect_ratio_data
operator|->
name|value
expr_stmt|;
name|angle
operator|=
name|editor
operator|->
name|angle_data
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|angle
operator|!=
name|gimp_brush_generated_get_radius
argument_list|(
name|brush
argument_list|)
operator|||
name|hardness
operator|!=
name|gimp_brush_generated_get_hardness
argument_list|(
name|brush
argument_list|)
operator|||
name|ratio
operator|!=
name|gimp_brush_generated_get_aspect_ratio
argument_list|(
name|brush
argument_list|)
operator|||
name|angle
operator|!=
name|gimp_brush_generated_get_angle
argument_list|(
name|brush
argument_list|)
condition|)
block|{
name|gimp_data_freeze
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_radius
argument_list|(
name|brush
argument_list|,
name|radius
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_hardness
argument_list|(
name|brush
argument_list|,
name|hardness
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_aspect_ratio
argument_list|(
name|brush
argument_list|,
name|ratio
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_angle
argument_list|(
name|brush
argument_list|,
name|angle
argument_list|)
expr_stmt|;
name|gimp_data_thaw
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

