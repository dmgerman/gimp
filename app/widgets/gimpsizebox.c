begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsizebox.c  * Copyright (C) 2004 Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpsizebox.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SB_WIDTH
define|#
directive|define
name|SB_WIDTH
value|8
end_define

begin_enum
enum|enum
DECL|enum|__anon2b0191160103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_WIDTH
name|PROP_WIDTH
block|,
DECL|enumerator|PROP_HEIGHT
name|PROP_HEIGHT
block|,
DECL|enumerator|PROP_UNIT
name|PROP_UNIT
block|,
DECL|enumerator|PROP_XRESOLUTION
name|PROP_XRESOLUTION
block|,
DECL|enumerator|PROP_YRESOLUTION
name|PROP_YRESOLUTION
block|,
DECL|enumerator|PROP_RESOLUTION_UNIT
name|PROP_RESOLUTION_UNIT
block|,
DECL|enumerator|PROP_KEEP_ASPECT
name|PROP_KEEP_ASPECT
block|,
DECL|enumerator|PROP_EDIT_RESOLUTION
name|PROP_EDIT_RESOLUTION
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_SIZE_BOX_GET_PRIVATE (obj)
define|#
directive|define
name|GIMP_SIZE_BOX_GET_PRIVATE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_PRIVATE ((obj), \                                         GIMP_TYPE_SIZE_BOX, GimpSizeBoxPrivate))
end_define

begin_typedef
DECL|typedef|GimpSizeBoxPrivate
typedef|typedef
name|struct
name|_GimpSizeBoxPrivate
name|GimpSizeBoxPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSizeBoxPrivate
struct|struct
name|_GimpSizeBoxPrivate
block|{
DECL|member|size_entry
name|GimpSizeEntry
modifier|*
name|size_entry
decl_stmt|;
DECL|member|size_chain
name|GimpChainButton
modifier|*
name|size_chain
decl_stmt|;
DECL|member|pixel_label
name|GtkWidget
modifier|*
name|pixel_label
decl_stmt|;
DECL|member|res_label
name|GtkWidget
modifier|*
name|res_label
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_size_box_constructed
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
name|gimp_size_box_dispose
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
name|gimp_size_box_set_property
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
name|gimp_size_box_get_property
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
name|gimp_size_box_update_size
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_size_box_update_resolution
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_size_box_chain_toggled
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|,
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSizeBox,gimp_size_box,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSizeBox
argument_list|,
argument|gimp_size_box
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_size_box_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_size_box_class_init
parameter_list|(
name|GimpSizeBoxClass
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
name|object_class
operator|->
name|constructed
operator|=
name|gimp_size_box_constructed
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_size_box_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_size_box_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_size_box_get_property
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|object_class
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpSizeBoxPrivate
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|256
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_HEIGHT
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"height"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|256
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_UNIT
argument_list|,
name|gimp_param_spec_unit
argument_list|(
literal|"unit"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|GIMP_UNIT_PIXEL
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
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
literal|72.0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
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
literal|72.0
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_RESOLUTION_UNIT
argument_list|,
name|gimp_param_spec_unit
argument_list|(
literal|"resolution-unit"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GIMP_UNIT_INCH
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_KEEP_ASPECT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"keep-aspect"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_EDIT_RESOLUTION
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"edit-resolution"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
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
DECL|function|gimp_size_box_init (GimpSizeBox * box)
name|gimp_size_box_init
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|box
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|box
operator|->
name|size_group
operator|=
name|gtk_size_group_new
argument_list|(
name|GTK_SIZE_GROUP_HORIZONTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_size_box_constructed (GObject * object)
name|gimp_size_box_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpSizeBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_SIZE_BOX_GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|entry
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GList
modifier|*
name|children
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
if|if
condition|(
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
condition|)
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_coordinates_new
argument_list|(
name|box
operator|->
name|unit
argument_list|,
literal|"%p"
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"_Width:"
argument_list|)
argument_list|,
name|box
operator|->
name|width
argument_list|,
name|box
operator|->
name|xresolution
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|box
operator|->
name|width
argument_list|,
name|_
argument_list|(
literal|"H_eight:"
argument_list|)
argument_list|,
name|box
operator|->
name|height
argument_list|,
name|box
operator|->
name|yresolution
argument_list|,
name|GIMP_MIN_IMAGE_SIZE
argument_list|,
name|GIMP_MAX_IMAGE_SIZE
argument_list|,
literal|0
argument_list|,
name|box
operator|->
name|height
argument_list|)
expr_stmt|;
name|priv
operator|->
name|size_entry
operator|=
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
expr_stmt|;
name|priv
operator|->
name|size_chain
operator|=
name|GIMP_COORDINATES_CHAINBUTTON
argument_list|(
name|GIMP_SIZE_ENTRY
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
comment|/*    * let gimp_prop_coordinates_callback know how to interpret the chainbutton    */
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|priv
operator|->
name|size_chain
argument_list|)
argument_list|,
literal|"constrains-ratio"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|TRUE
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_prop_coordinates_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"width"
argument_list|,
literal|"height"
argument_list|,
literal|"unit"
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|,
name|box
operator|->
name|xresolution
argument_list|,
name|box
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|priv
operator|->
name|size_chain
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_size_box_chain_toggled
argument_list|)
argument_list|,
name|box
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
name|gtk_size_group_add_widget
argument_list|(
name|box
operator|->
name|size_group
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
literal|2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_attach_defaults
argument_list|(
name|GTK_TABLE
argument_list|(
name|entry
argument_list|)
argument_list|,
name|vbox
argument_list|,
literal|1
argument_list|,
literal|3
argument_list|,
literal|2
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|priv
operator|->
name|pixel_label
operator|=
name|label
expr_stmt|;
if|if
condition|(
name|box
operator|->
name|edit_resolution
condition|)
block|{
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|hbox
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
name|hbox
argument_list|)
expr_stmt|;
name|entry
operator|=
name|gimp_coordinates_new
argument_list|(
name|box
operator|->
name|resolution_unit
argument_list|,
name|_
argument_list|(
literal|"pixels/%a"
argument_list|)
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|SB_WIDTH
argument_list|,
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"_X resolution:"
argument_list|)
argument_list|,
name|box
operator|->
name|xresolution
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|,
name|_
argument_list|(
literal|"_Y resolution:"
argument_list|)
argument_list|,
name|box
operator|->
name|yresolution
argument_list|,
literal|1.0
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|1
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|entry
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
name|entry
argument_list|)
expr_stmt|;
name|children
operator|=
name|gtk_container_get_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|entry
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|children
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
if|if
condition|(
name|GTK_IS_LABEL
argument_list|(
name|list
operator|->
name|data
argument_list|)
condition|)
name|gtk_size_group_add_widget
argument_list|(
name|box
operator|->
name|size_group
argument_list|,
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_list_free
argument_list|(
name|children
argument_list|)
expr_stmt|;
name|gimp_prop_coordinates_connect
argument_list|(
name|G_OBJECT
argument_list|(
name|box
argument_list|)
argument_list|,
literal|"xresolution"
argument_list|,
literal|"yresolution"
argument_list|,
literal|"resolution-unit"
argument_list|,
name|entry
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|label
operator|=
name|gtk_label_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gimp_label_set_attributes
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ATTR_SCALE
argument_list|,
name|PANGO_SCALE_SMALL
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|priv
operator|->
name|res_label
operator|=
name|label
expr_stmt|;
block|}
name|gimp_size_box_update_size
argument_list|(
name|box
argument_list|)
expr_stmt|;
name|gimp_size_box_update_resolution
argument_list|(
name|box
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_size_box_dispose (GObject * object)
name|gimp_size_box_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|box
operator|->
name|size_group
condition|)
block|{
name|g_object_unref
argument_list|(
name|box
operator|->
name|size_group
argument_list|)
expr_stmt|;
name|box
operator|->
name|size_group
operator|=
name|NULL
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
DECL|function|gimp_size_box_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_size_box_set_property
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
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpSizeBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_SIZE_BOX_GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_WIDTH
case|:
name|box
operator|->
name|width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gimp_size_box_update_size
argument_list|(
name|box
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|box
operator|->
name|height
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
name|gimp_size_box_update_size
argument_list|(
name|box
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|box
operator|->
name|unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_XRESOLUTION
case|:
name|box
operator|->
name|xresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|size_entry
condition|)
name|gimp_size_entry_set_resolution
argument_list|(
name|priv
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|box
operator|->
name|xresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_box_update_resolution
argument_list|(
name|box
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_YRESOLUTION
case|:
name|box
operator|->
name|yresolution
operator|=
name|g_value_get_double
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|priv
operator|->
name|size_entry
condition|)
name|gimp_size_entry_set_resolution
argument_list|(
name|priv
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
name|box
operator|->
name|yresolution
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_size_box_update_resolution
argument_list|(
name|box
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION_UNIT
case|:
name|box
operator|->
name|resolution_unit
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_KEEP_ASPECT
case|:
if|if
condition|(
name|priv
operator|->
name|size_chain
condition|)
name|gimp_chain_button_set_active
argument_list|(
name|priv
operator|->
name|size_chain
argument_list|,
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDIT_RESOLUTION
case|:
name|box
operator|->
name|edit_resolution
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
DECL|function|gimp_size_box_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_size_box_get_property
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
name|GimpSizeBox
modifier|*
name|box
init|=
name|GIMP_SIZE_BOX
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpSizeBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_SIZE_BOX_GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|width
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_HEIGHT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|height
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|unit
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
name|box
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
name|box
operator|->
name|yresolution
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_RESOLUTION_UNIT
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|resolution_unit
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_KEEP_ASPECT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|gimp_chain_button_get_active
argument_list|(
name|priv
operator|->
name|size_chain
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDIT_RESOLUTION
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|box
operator|->
name|edit_resolution
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
DECL|function|gimp_size_box_update_size (GimpSizeBox * box)
name|gimp_size_box_update_size
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpSizeBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_SIZE_BOX_GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|pixel_label
condition|)
block|{
name|gchar
modifier|*
name|text
init|=
name|g_strdup_printf
argument_list|(
name|ngettext
argument_list|(
literal|"%d Ã %d pixel"
argument_list|,
literal|"%d Ã %d pixels"
argument_list|,
name|box
operator|->
name|height
argument_list|)
argument_list|,
name|box
operator|->
name|width
argument_list|,
name|box
operator|->
name|height
argument_list|)
decl_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|priv
operator|->
name|pixel_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_size_box_update_resolution (GimpSizeBox * box)
name|gimp_size_box_update_resolution
parameter_list|(
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
block|{
name|GimpSizeBoxPrivate
modifier|*
name|priv
init|=
name|GIMP_SIZE_BOX_GET_PRIVATE
argument_list|(
name|box
argument_list|)
decl_stmt|;
if|if
condition|(
name|priv
operator|->
name|size_entry
condition|)
block|{
name|gimp_size_entry_set_refval
argument_list|(
name|priv
operator|->
name|size_entry
argument_list|,
literal|0
argument_list|,
name|box
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_size_entry_set_refval
argument_list|(
name|priv
operator|->
name|size_entry
argument_list|,
literal|1
argument_list|,
name|box
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|priv
operator|->
name|res_label
condition|)
block|{
name|gchar
modifier|*
name|text
decl_stmt|;
name|gint
name|xres
init|=
name|ROUND
argument_list|(
name|box
operator|->
name|xresolution
argument_list|)
decl_stmt|;
name|gint
name|yres
init|=
name|ROUND
argument_list|(
name|box
operator|->
name|yresolution
argument_list|)
decl_stmt|;
if|if
condition|(
name|xres
operator|!=
name|yres
condition|)
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d Ã %d ppi"
argument_list|)
argument_list|,
name|xres
argument_list|,
name|yres
argument_list|)
expr_stmt|;
else|else
name|text
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"%d ppi"
argument_list|)
argument_list|,
name|yres
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|priv
operator|->
name|res_label
argument_list|)
argument_list|,
name|text
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|text
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_size_box_chain_toggled (GimpChainButton * button,GimpSizeBox * box)
name|gimp_size_box_chain_toggled
parameter_list|(
name|GimpChainButton
modifier|*
name|button
parameter_list|,
name|GimpSizeBox
modifier|*
name|box
parameter_list|)
block|{
name|g_object_set
argument_list|(
name|box
argument_list|,
literal|"keep-aspect"
argument_list|,
name|gimp_chain_button_get_active
argument_list|(
name|button
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

