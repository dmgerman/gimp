begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsamplepointeditor.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-pick-color.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-sample-points.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorframe.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpsamplepointeditor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon279f7eb30103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SAMPLE_MERGED
name|PROP_SAMPLE_MERGED
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_sample_point_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_point_added
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_point_removed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_point_update
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_proj_update
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|now
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_points_changed
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sample_point_editor_dirty
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_sample_point_editor_update
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSamplePointEditor,gimp_sample_point_editor,GIMP_TYPE_IMAGE_EDITOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSamplePointEditor
argument_list|,
argument|gimp_sample_point_editor
argument_list|,
argument|GIMP_TYPE_IMAGE_EDITOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_sample_point_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_sample_point_editor_class_init
parameter_list|(
name|GimpSamplePointEditorClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpImageEditorClass
modifier|*
name|image_editor_class
init|=
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_sample_point_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_sample_point_editor_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_sample_point_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_sample_point_editor_dispose
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_sample_point_editor_style_set
expr_stmt|;
name|image_editor_class
operator|->
name|set_image
operator|=
name|gimp_sample_point_editor_set_image
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SAMPLE_MERGED
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"sample-merged"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_init (GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_init
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gint
name|content_spacing
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|row
init|=
literal|0
decl_stmt|;
name|gint
name|column
init|=
literal|0
decl_stmt|;
name|editor
operator|->
name|sample_merged
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"content-spacing"
argument_list|,
operator|&
name|content_spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|editor
operator|->
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|content_spacing
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
name|editor
operator|->
name|table
argument_list|)
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
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|frame
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_FRAME
argument_list|,
literal|"mode"
argument_list|,
name|GIMP_COLOR_FRAME_MODE_PIXEL
argument_list|,
literal|"has-number"
argument_list|,
name|TRUE
argument_list|,
literal|"number"
argument_list|,
name|i
operator|+
literal|1
argument_list|,
literal|"has-color-area"
argument_list|,
name|TRUE
argument_list|,
literal|"sensitive"
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_attach
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|table
argument_list|)
argument_list|,
name|frame
argument_list|,
name|column
argument_list|,
name|column
operator|+
literal|1
argument_list|,
name|row
argument_list|,
name|row
operator|+
literal|1
argument_list|,
name|GTK_EXPAND
operator||
name|GTK_FILL
argument_list|,
name|GTK_EXPAND
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
name|frame
argument_list|)
expr_stmt|;
name|editor
operator|->
name|color_frames
index|[
name|i
index|]
operator|=
name|frame
expr_stmt|;
name|column
operator|++
expr_stmt|;
if|if
condition|(
name|column
operator|>
literal|1
condition|)
block|{
name|column
operator|=
literal|0
expr_stmt|;
name|row
operator|++
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_sample_point_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_sample_point_editor_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|GimpSamplePointEditor
modifier|*
name|editor
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|editor
operator|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_sample_point_editor_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SAMPLE_MERGED
case|:
name|gimp_sample_point_editor_set_sample_merged
argument_list|(
name|editor
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_sample_point_editor_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SAMPLE_MERGED
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|sample_merged
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_dispose (GObject * object)
name|gimp_sample_point_editor_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|dirty_idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|editor
operator|->
name|dirty_idle_id
argument_list|)
expr_stmt|;
name|editor
operator|->
name|dirty_idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_sample_point_editor_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|content_spacing
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"content-spacing"
argument_list|,
operator|&
name|content_spacing
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|editor
operator|->
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_set_image (GimpImageEditor * image_editor,GimpImage * image)
name|gimp_sample_point_editor_set_image
parameter_list|(
name|GimpImageEditor
modifier|*
name|image_editor
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpSamplePointEditor
modifier|*
name|editor
init|=
name|GIMP_SAMPLE_POINT_EDITOR
argument_list|(
name|image_editor
argument_list|)
decl_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|image
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|gimp_sample_point_editor_point_added
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|gimp_sample_point_editor_point_removed
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|gimp_sample_point_editor_point_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|image_editor
operator|->
name|image
operator|->
name|projection
argument_list|,
name|gimp_sample_point_editor_proj_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|GIMP_IMAGE_EDITOR_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|set_image
argument_list|(
name|image_editor
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"sample-point-added"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_sample_point_editor_point_added
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"sample-point-removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_sample_point_editor_point_removed
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
argument_list|,
literal|"update-sample-point"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_sample_point_editor_point_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image
operator|->
name|projection
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_sample_point_editor_proj_update
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
name|gimp_sample_point_editor_points_changed
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_sample_point_editor_new (GimpMenuFactory * menu_factory)
name|gimp_sample_point_editor_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_MENU_FACTORY
argument_list|(
name|menu_factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_SAMPLE_POINT_EDITOR
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<SamplePointEditor>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/sample-point-editor-popup"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_sample_point_editor_set_sample_merged (GimpSamplePointEditor * editor,gboolean sample_merged)
name|gimp_sample_point_editor_set_sample_merged
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SAMPLE_POINT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|)
expr_stmt|;
name|sample_merged
operator|=
name|sample_merged
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|sample_merged
operator|!=
name|sample_merged
condition|)
block|{
name|gint
name|i
decl_stmt|;
name|editor
operator|->
name|sample_merged
operator|=
name|sample_merged
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
name|editor
operator|->
name|dirty
index|[
name|i
index|]
operator|=
name|TRUE
expr_stmt|;
name|gimp_sample_point_editor_dirty
argument_list|(
name|editor
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|"sample-merged"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_sample_point_editor_get_sample_merged (GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_get_sample_merged
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_SAMPLE_POINT_EDITOR
argument_list|(
name|editor
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|editor
operator|->
name|sample_merged
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_point_added (GimpImage * image,GimpSamplePoint * sample_point,GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_point_added
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_sample_point_editor_points_changed
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_point_removed (GimpImage * image,GimpSamplePoint * sample_point,GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_point_removed
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gimp_sample_point_editor_points_changed
argument_list|(
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_point_update (GimpImage * image,GimpSamplePoint * sample_point,GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_point_update
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gint
name|i
init|=
name|g_list_index
argument_list|(
name|image
operator|->
name|sample_points
argument_list|,
name|sample_point
argument_list|)
decl_stmt|;
if|if
condition|(
name|i
operator|<
literal|4
condition|)
name|gimp_sample_point_editor_dirty
argument_list|(
name|editor
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_proj_update (GimpImage * image,gboolean now,gint x,gint y,gint width,gint height,GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_proj_update
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|gboolean
name|now
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gint
name|n_points
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|n_points
operator|=
name|MIN
argument_list|(
literal|4
argument_list|,
name|g_list_length
argument_list|(
name|image_editor
operator|->
name|image
operator|->
name|sample_points
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|list
operator|=
name|image_editor
operator|->
name|image
operator|->
name|sample_points
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
operator|,
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|sample_point
operator|->
name|x
operator|>=
name|x
operator|&&
name|sample_point
operator|->
name|x
operator|<
operator|(
name|x
operator|+
name|width
operator|)
operator|&&
name|sample_point
operator|->
name|y
operator|>=
name|y
operator|&&
name|sample_point
operator|->
name|y
operator|<
operator|(
name|y
operator|+
name|height
operator|)
condition|)
block|{
name|gimp_sample_point_editor_dirty
argument_list|(
name|editor
argument_list|,
name|i
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_points_changed (GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_points_changed
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gint
name|n_points
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|image_editor
operator|->
name|image
condition|)
name|n_points
operator|=
name|MIN
argument_list|(
literal|4
argument_list|,
name|g_list_length
argument_list|(
name|image_editor
operator|->
name|image
operator|->
name|sample_points
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
control|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|color_frames
index|[
name|i
index|]
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|editor
operator|->
name|dirty
index|[
name|i
index|]
operator|=
name|TRUE
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
name|n_points
init|;
name|i
operator|<
literal|4
condition|;
name|i
operator|++
control|)
block|{
name|gtk_widget_set_sensitive
argument_list|(
name|editor
operator|->
name|color_frames
index|[
name|i
index|]
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|editor
operator|->
name|color_frames
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|editor
operator|->
name|dirty
index|[
name|i
index|]
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|n_points
operator|>
literal|0
condition|)
name|gimp_sample_point_editor_dirty
argument_list|(
name|editor
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sample_point_editor_dirty (GimpSamplePointEditor * editor,gint index)
name|gimp_sample_point_editor_dirty
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|,
name|gint
name|index
parameter_list|)
block|{
if|if
condition|(
name|index
operator|>=
literal|0
condition|)
name|editor
operator|->
name|dirty
index|[
name|index
index|]
operator|=
name|TRUE
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|dirty_idle_id
condition|)
name|g_source_remove
argument_list|(
name|editor
operator|->
name|dirty_idle_id
argument_list|)
expr_stmt|;
name|editor
operator|->
name|dirty_idle_id
operator|=
name|g_idle_add
argument_list|(
operator|(
name|GSourceFunc
operator|)
name|gimp_sample_point_editor_update
argument_list|,
name|editor
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_sample_point_editor_update (GimpSamplePointEditor * editor)
name|gimp_sample_point_editor_update
parameter_list|(
name|GimpSamplePointEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpImageEditor
modifier|*
name|image_editor
init|=
name|GIMP_IMAGE_EDITOR
argument_list|(
name|editor
argument_list|)
decl_stmt|;
name|gint
name|n_points
init|=
literal|0
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|editor
operator|->
name|dirty_idle_id
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
name|image_editor
operator|->
name|image
condition|)
return|return
name|FALSE
return|;
name|n_points
operator|=
name|MIN
argument_list|(
literal|4
argument_list|,
name|g_list_length
argument_list|(
name|image_editor
operator|->
name|image
operator|->
name|sample_points
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|list
operator|=
name|image_editor
operator|->
name|image
operator|->
name|sample_points
init|;
name|i
operator|<
name|n_points
condition|;
name|i
operator|++
operator|,
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
name|editor
operator|->
name|dirty
index|[
name|i
index|]
condition|)
block|{
name|GimpSamplePoint
modifier|*
name|sample_point
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GimpColorFrame
modifier|*
name|color_frame
decl_stmt|;
name|GimpImageType
name|image_type
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|color_index
decl_stmt|;
name|editor
operator|->
name|dirty
index|[
name|i
index|]
operator|=
name|FALSE
expr_stmt|;
name|color_frame
operator|=
name|GIMP_COLOR_FRAME
argument_list|(
name|editor
operator|->
name|color_frames
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_pick_color
argument_list|(
name|image_editor
operator|->
name|image
argument_list|,
name|NULL
argument_list|,
name|sample_point
operator|->
name|x
argument_list|,
name|sample_point
operator|->
name|y
argument_list|,
name|editor
operator|->
name|sample_merged
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
operator|&
name|image_type
argument_list|,
operator|&
name|color
argument_list|,
operator|&
name|color_index
argument_list|)
condition|)
block|{
name|gimp_color_frame_set_color
argument_list|(
name|color_frame
argument_list|,
name|image_type
argument_list|,
operator|&
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_color_frame_set_invalid
argument_list|(
name|color_frame
argument_list|)
expr_stmt|;
block|}
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

