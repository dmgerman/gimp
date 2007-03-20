begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcursorview.c  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
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
file|"core/gimpitem.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpunit.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorframe.h"
end_include

begin_include
include|#
directive|include
file|"gimpcursorview.h"
end_include

begin_include
include|#
directive|include
file|"gimpdocked.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenufactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpsessioninfo.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bd04c350103
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
name|void
name|gimp_cursor_view_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_cursor_view_set_property
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
name|gimp_cursor_view_get_property
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
name|gimp_cursor_view_style_set
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
name|gimp_cursor_view_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GList
modifier|*
name|gimp_cursor_view_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpCursorView
argument_list|,
argument|gimp_cursor_view
argument_list|,
argument|GIMP_TYPE_EDITOR
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_DOCKED,                                                 gimp_cursor_view_docked_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_cursor_view_parent_class
end_define

begin_decl_stmt
specifier|static
name|GimpDockedInterface
modifier|*
name|parent_docked_iface
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_cursor_view_class_init (GimpCursorViewClass * klass)
name|gimp_cursor_view_class_init
parameter_list|(
name|GimpCursorViewClass
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
name|object_class
operator|->
name|get_property
operator|=
name|gimp_cursor_view_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_cursor_view_set_property
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_cursor_view_style_set
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
DECL|function|gimp_cursor_view_init (GimpCursorView * view)
name|gimp_cursor_view_init
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|)
block|{
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
name|toggle
decl_stmt|;
name|gint
name|content_spacing
decl_stmt|;
name|view
operator|->
name|sample_merged
operator|=
name|TRUE
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
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
comment|/* cursor information */
name|view
operator|->
name|coord_hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|coord_hbox
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
name|view
operator|->
name|coord_hbox
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Pixels"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|coord_hbox
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
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|6
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
name|view
operator|->
name|pixel_x_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|view
operator|->
name|pixel_x_label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|"X"
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|view
operator|->
name|pixel_x_label
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|view
operator|->
name|pixel_y_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|view
operator|->
name|pixel_y_label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|"Y"
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|view
operator|->
name|pixel_y_label
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_frame_new
argument_list|(
name|_
argument_list|(
literal|"Units"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|coord_hbox
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
name|view
operator|->
name|unit_x_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|view
operator|->
name|unit_x_label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|"X"
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|view
operator|->
name|unit_x_label
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|view
operator|->
name|unit_y_label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|view
operator|->
name|unit_y_label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|0.5
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
literal|"Y"
argument_list|)
argument_list|,
literal|0.5
argument_list|,
literal|0.5
argument_list|,
name|view
operator|->
name|unit_y_label
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* color information */
name|view
operator|->
name|color_hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|TRUE
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|view
operator|->
name|color_hbox
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
name|view
operator|->
name|color_hbox
argument_list|)
expr_stmt|;
name|view
operator|->
name|color_frame_1
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_1
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_PIXEL
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|color_hbox
argument_list|)
argument_list|,
name|view
operator|->
name|color_frame_1
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
name|view
operator|->
name|color_frame_1
argument_list|)
expr_stmt|;
name|view
operator|->
name|color_frame_2
operator|=
name|gimp_color_frame_new
argument_list|()
expr_stmt|;
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_2
argument_list|)
argument_list|,
name|GIMP_COLOR_FRAME_MODE_RGB
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|color_hbox
argument_list|)
argument_list|,
name|view
operator|->
name|color_frame_2
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
name|view
operator|->
name|color_frame_2
argument_list|)
expr_stmt|;
comment|/* sample merged toggle */
name|toggle
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|view
argument_list|)
argument_list|,
literal|"sample-merged"
argument_list|,
name|_
argument_list|(
literal|"_Sample Merged"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|view
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cursor_view_docked_iface_init (GimpDockedInterface * iface)
name|gimp_cursor_view_docked_iface_init
parameter_list|(
name|GimpDockedInterface
modifier|*
name|iface
parameter_list|)
block|{
name|parent_docked_iface
operator|=
name|g_type_interface_peek_parent
argument_list|(
name|iface
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|parent_docked_iface
condition|)
name|parent_docked_iface
operator|=
name|g_type_default_interface_peek
argument_list|(
name|GIMP_TYPE_DOCKED
argument_list|)
expr_stmt|;
name|iface
operator|->
name|set_aux_info
operator|=
name|gimp_cursor_view_set_aux_info
expr_stmt|;
name|iface
operator|->
name|get_aux_info
operator|=
name|gimp_cursor_view_get_aux_info
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cursor_view_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_cursor_view_set_property
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
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
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
name|view
operator|->
name|sample_merged
operator|=
name|g_value_get_boolean
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
DECL|function|gimp_cursor_view_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_cursor_view_get_property
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
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
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
name|view
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

begin_define
DECL|macro|AUX_INFO_FRAME_1_MODE
define|#
directive|define
name|AUX_INFO_FRAME_1_MODE
value|"frame-1-mode"
end_define

begin_define
DECL|macro|AUX_INFO_FRAME_2_MODE
define|#
directive|define
name|AUX_INFO_FRAME_2_MODE
value|"frame-2-mode"
end_define

begin_function
specifier|static
name|void
DECL|function|gimp_cursor_view_set_aux_info (GimpDocked * docked,GList * aux_info)
name|gimp_cursor_view_set_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|,
name|GList
modifier|*
name|aux_info
parameter_list|)
block|{
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|parent_docked_iface
operator|->
name|set_aux_info
argument_list|(
name|docked
argument_list|,
name|aux_info
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|aux_info
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpSessionInfoAux
modifier|*
name|aux
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|AUX_INFO_FRAME_1_MODE
argument_list|)
condition|)
name|frame
operator|=
name|view
operator|->
name|color_frame_1
expr_stmt|;
elseif|else
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|aux
operator|->
name|name
argument_list|,
name|AUX_INFO_FRAME_2_MODE
argument_list|)
condition|)
name|frame
operator|=
name|view
operator|->
name|color_frame_2
expr_stmt|;
if|if
condition|(
name|frame
condition|)
block|{
name|GEnumClass
modifier|*
name|enum_class
decl_stmt|;
name|GEnumValue
modifier|*
name|enum_value
decl_stmt|;
name|enum_class
operator|=
name|g_type_class_peek
argument_list|(
name|GIMP_TYPE_COLOR_FRAME_MODE
argument_list|)
expr_stmt|;
name|enum_value
operator|=
name|g_enum_get_value_by_nick
argument_list|(
name|enum_class
argument_list|,
name|aux
operator|->
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|enum_value
condition|)
name|gimp_color_frame_set_mode
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|enum_value
operator|->
name|value
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|GList
modifier|*
DECL|function|gimp_cursor_view_get_aux_info (GimpDocked * docked)
name|gimp_cursor_view_get_aux_info
parameter_list|(
name|GimpDocked
modifier|*
name|docked
parameter_list|)
block|{
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
argument_list|(
name|docked
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|aux_info
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|nick
decl_stmt|;
name|GimpSessionInfoAux
modifier|*
name|aux
decl_stmt|;
name|aux_info
operator|=
name|parent_docked_iface
operator|->
name|get_aux_info
argument_list|(
name|docked
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_COLOR_FRAME_MODE
argument_list|,
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_1
argument_list|)
operator|->
name|frame_mode
argument_list|,
name|NULL
argument_list|,
operator|&
name|nick
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|aux
operator|=
name|gimp_session_info_aux_new
argument_list|(
name|AUX_INFO_FRAME_1_MODE
argument_list|,
name|nick
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|aux_info
argument_list|,
name|aux
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|gimp_enum_get_value
argument_list|(
name|GIMP_TYPE_COLOR_FRAME_MODE
argument_list|,
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_2
argument_list|)
operator|->
name|frame_mode
argument_list|,
name|NULL
argument_list|,
operator|&
name|nick
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|aux
operator|=
name|gimp_session_info_aux_new
argument_list|(
name|AUX_INFO_FRAME_2_MODE
argument_list|,
name|nick
argument_list|)
expr_stmt|;
name|aux_info
operator|=
name|g_list_append
argument_list|(
name|aux_info
argument_list|,
name|aux
argument_list|)
expr_stmt|;
block|}
return|return
name|aux_info
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_cursor_view_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_cursor_view_style_set
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
name|GimpCursorView
modifier|*
name|view
init|=
name|GIMP_CURSOR_VIEW
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
name|GTK_WIDGET
argument_list|(
name|view
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
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|coord_hbox
argument_list|)
argument_list|,
name|content_spacing
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|view
operator|->
name|color_hbox
argument_list|)
argument_list|,
name|content_spacing
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
DECL|function|gimp_cursor_view_new (GimpMenuFactory * menu_factory)
name|gimp_cursor_view_new
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
name|GIMP_TYPE_CURSOR_VIEW
argument_list|,
literal|"menu-factory"
argument_list|,
name|menu_factory
argument_list|,
literal|"menu-identifier"
argument_list|,
literal|"<CursorInfo>"
argument_list|,
literal|"ui-path"
argument_list|,
literal|"/cursor-info-popup"
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cursor_view_set_sample_merged (GimpCursorView * view,gboolean sample_merged)
name|gimp_cursor_view_set_sample_merged
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURSOR_VIEW
argument_list|(
name|view
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
name|view
operator|->
name|sample_merged
operator|!=
name|sample_merged
condition|)
block|{
name|view
operator|->
name|sample_merged
operator|=
name|sample_merged
expr_stmt|;
name|g_object_notify
argument_list|(
name|G_OBJECT
argument_list|(
name|view
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
DECL|function|gimp_cursor_view_get_sample_merged (GimpCursorView * view)
name|gimp_cursor_view_get_sample_merged
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CURSOR_VIEW
argument_list|(
name|view
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|view
operator|->
name|sample_merged
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_cursor_view_update_cursor (GimpCursorView * view,GimpImage * image,GimpUnit unit,gdouble x,gdouble y)
name|gimp_cursor_view_update_cursor
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|gboolean
name|in_image
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gint
name|unit_digits
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|unit_str
decl_stmt|;
name|gchar
name|format_buf
index|[
literal|32
index|]
decl_stmt|;
name|gchar
name|buf
index|[
literal|32
index|]
decl_stmt|;
name|GimpImageType
name|sample_type
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|color_index
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURSOR_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|unit
operator|==
name|GIMP_UNIT_PIXEL
condition|)
name|unit
operator|=
name|gimp_image_get_unit
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|in_image
operator|=
operator|(
name|x
operator|>=
literal|0.0
operator|&&
name|x
operator|<
name|gimp_image_get_width
argument_list|(
name|image
argument_list|)
operator|&&
name|y
operator|>=
literal|0.0
operator|&&
name|y
operator|<
name|gimp_image_get_height
argument_list|(
name|image
argument_list|)
operator|)
expr_stmt|;
name|unit_factor
operator|=
name|_gimp_unit_get_factor
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|unit_digits
operator|=
name|_gimp_unit_get_digits
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
name|unit_str
operator|=
name|_gimp_unit_get_abbreviation
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|unit
argument_list|)
expr_stmt|;
DECL|macro|FORMAT_STRING (s)
define|#
directive|define
name|FORMAT_STRING
parameter_list|(
name|s
parameter_list|)
value|(in_image ? (s) : "("s")")
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|FORMAT_STRING
argument_list|(
literal|"%d"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|x
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixel_x_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|FORMAT_STRING
argument_list|(
literal|"%d"
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|y
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixel_y_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|format_buf
argument_list|,
sizeof|sizeof
argument_list|(
name|format_buf
argument_list|)
argument_list|,
name|FORMAT_STRING
argument_list|(
literal|"%%.%df %s"
argument_list|)
argument_list|,
name|unit_digits
argument_list|,
name|unit_str
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|format_buf
argument_list|,
name|x
operator|*
name|unit_factor
operator|/
name|image
operator|->
name|xresolution
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|unit_x_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
name|g_snprintf
argument_list|(
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|buf
argument_list|)
argument_list|,
name|format_buf
argument_list|,
name|y
operator|*
name|unit_factor
operator|/
name|image
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|unit_y_label
argument_list|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_image_pick_color
argument_list|(
name|image
argument_list|,
name|NULL
argument_list|,
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|x
argument_list|)
argument_list|,
operator|(
name|gint
operator|)
name|floor
argument_list|(
name|y
argument_list|)
argument_list|,
name|view
operator|->
name|sample_merged
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
operator|&
name|sample_type
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
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_1
argument_list|)
argument_list|,
name|sample_type
argument_list|,
operator|&
name|color
argument_list|,
name|color_index
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_color
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_2
argument_list|)
argument_list|,
name|sample_type
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
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_2
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_cursor_view_clear_cursor (GimpCursorView * view)
name|gimp_cursor_view_clear_cursor
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CURSOR_VIEW
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixel_x_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|pixel_y_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|unit_x_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|view
operator|->
name|unit_y_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"n/a"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_1
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_color_frame_set_invalid
argument_list|(
name|GIMP_COLOR_FRAME
argument_list|(
name|view
operator|->
name|color_frame_2
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

