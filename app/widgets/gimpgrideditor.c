begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpGridEditor  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpgrideditor.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GRID_EDITOR_DEFAULT_RESOLUTION
define|#
directive|define
name|GRID_EDITOR_DEFAULT_RESOLUTION
value|72.0
end_define

begin_define
DECL|macro|GRID_EDITOR_COLOR_BUTTON_SIZE
define|#
directive|define
name|GRID_EDITOR_COLOR_BUTTON_SIZE
value|20
end_define

begin_enum
enum|enum
DECL|enum|__anon29d089a70103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GRID
name|PROP_GRID
block|,
DECL|enumerator|PROP_XRESOLUTION
name|PROP_XRESOLUTION
block|,
DECL|enumerator|PROP_YRESOLUTION
name|PROP_YRESOLUTION
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_grid_editor_class_init
parameter_list|(
name|GimpGridEditorClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_grid_editor_constructor
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
name|gimp_grid_editor_set_property
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
name|gimp_grid_editor_get_property
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
name|gimp_grid_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GtkVBoxClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_grid_editor_get_type (void)
name|gimp_grid_editor_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|view_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|view_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|view_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpGridEditorClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init      */
name|NULL
block|,
comment|/* base_finalize  */
operator|(
name|GClassInitFunc
operator|)
name|gimp_grid_editor_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpGridEditor
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
name|NULL
comment|/* instance_init  */
block|}
decl_stmt|;
name|view_type
operator|=
name|g_type_register_static
argument_list|(
name|GTK_TYPE_VBOX
argument_list|,
literal|"GimpGridEditor"
argument_list|,
operator|&
name|view_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|view_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_grid_editor_class_init (GimpGridEditorClass * klass)
name|gimp_grid_editor_class_init
parameter_list|(
name|GimpGridEditorClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_grid_editor_constructor
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_grid_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_grid_editor_get_property
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_grid_editor_finalize
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GRID
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"grid"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GRID
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_XRESOLUTION
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"xresolution"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|,
name|GRID_EDITOR_DEFAULT_RESOLUTION
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_YRESOLUTION
argument_list|,
name|g_param_spec_double
argument_list|(
literal|"yresolution"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_RESOLUTION
argument_list|,
name|GIMP_MAX_RESOLUTION
argument_list|,
name|GRID_EDITOR_DEFAULT_RESOLUTION
argument_list|,
name|G_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_grid_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_grid_editor_set_property
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
name|GimpGridEditor
modifier|*
name|editor
init|=
name|GIMP_GRID_EDITOR
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
name|PROP_GRID
case|:
name|editor
operator|->
name|grid
operator|=
name|GIMP_GRID
argument_list|(
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XRESOLUTION
case|:
name|editor
operator|->
name|xresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YRESOLUTION
case|:
name|editor
operator|->
name|yresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
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
DECL|function|gimp_grid_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_grid_editor_get_property
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
name|GimpGridEditor
modifier|*
name|editor
init|=
name|GIMP_GRID_EDITOR
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
name|PROP_GRID
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|grid
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|xresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YRESOLUTION
case|:
name|g_value_set_double
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|yresolution
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
name|GObject
modifier|*
DECL|function|gimp_grid_editor_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_grid_editor_constructor
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
name|GimpGridEditor
modifier|*
name|editor
decl_stmt|;
name|GObject
modifier|*
name|object
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|style
decl_stmt|;
name|GtkWidget
modifier|*
name|color_button
decl_stmt|;
name|GtkWidget
modifier|*
name|sizeentry
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
name|GIMP_GRID_EDITOR
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_assert
argument_list|(
name|editor
operator|->
name|grid
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Appearance"
argument_list|)
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|3
argument_list|,
literal|2
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
literal|4
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
name|style
operator|=
name|gimp_prop_enum_combo_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
argument_list|,
literal|"style"
argument_list|,
name|GIMP_GRID_DOTS
argument_list|,
name|GIMP_GRID_SOLID
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
literal|"Line _Style:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|style
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
argument_list|,
literal|"fgcolor"
argument_list|,
name|_
argument_list|(
literal|"Change Grid Foreground Color"
argument_list|)
argument_list|,
name|GRID_EDITOR_COLOR_BUTTON_SIZE
argument_list|,
name|GRID_EDITOR_COLOR_BUTTON_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
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
literal|"_Foreground Color:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|color_button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|color_button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
argument_list|,
literal|"bgcolor"
argument_list|,
name|_
argument_list|(
literal|"Change Grid Background Color"
argument_list|)
argument_list|,
name|GRID_EDITOR_COLOR_BUTTON_SIZE
argument_list|,
name|GRID_EDITOR_COLOR_BUTTON_SIZE
argument_list|,
name|GIMP_COLOR_AREA_FLAT
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
literal|"_Background Color:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
argument_list|,
name|color_button
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|table
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Spacing"
argument_list|)
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_prop_coordinates_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
argument_list|,
literal|"xspacing"
argument_list|,
literal|"yspacing"
argument_list|,
literal|"spacing-unit"
argument_list|,
literal|"%a"
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|editor
operator|->
name|xresolution
argument_list|,
name|editor
operator|->
name|yresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Width"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Height"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pixels"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Offset"
argument_list|)
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
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|sizeentry
operator|=
name|gimp_prop_coordinates_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
argument_list|,
literal|"xoffset"
argument_list|,
literal|"yoffset"
argument_list|,
literal|"offset-unit"
argument_list|,
literal|"%a"
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|editor
operator|->
name|xresolution
argument_list|,
name|editor
operator|->
name|yresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_table_set_row_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Width"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Height"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|2
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gimp_size_entry_attach_label
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|sizeentry
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Pixels"
argument_list|)
argument_list|,
literal|1
argument_list|,
literal|4
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|sizeentry
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
name|sizeentry
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
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
DECL|function|gimp_grid_editor_finalize (GObject * object)
name|gimp_grid_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpGridEditor
modifier|*
name|editor
init|=
name|GIMP_GRID_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|grid
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|grid
argument_list|)
expr_stmt|;
name|editor
operator|->
name|grid
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_grid_editor_new (GimpGrid * grid,gdouble xresolution,gdouble yresolution)
name|gimp_grid_editor_new
parameter_list|(
name|GimpGrid
modifier|*
name|grid
parameter_list|,
name|gdouble
name|xresolution
parameter_list|,
name|gdouble
name|yresolution
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GRID
argument_list|(
name|grid
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_GRID_EDITOR
argument_list|,
literal|"grid"
argument_list|,
name|grid
argument_list|,
literal|"xresolution"
argument_list|,
name|xresolution
argument_list|,
literal|"yresolution"
argument_list|,
name|yresolution
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

