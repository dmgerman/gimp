begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpfilleditor.c  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpfilloptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorpanel.h"
end_include

begin_include
include|#
directive|include
file|"gimpfilleditor.h"
end_include

begin_include
include|#
directive|include
file|"gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewablebox.h"
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
DECL|enum|__anon29217a9f0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_OPTIONS
name|PROP_OPTIONS
block|,
DECL|enumerator|PROP_EDIT_CONTEXT
name|PROP_EDIT_CONTEXT
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_fill_editor_constructed
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
name|gimp_fill_editor_finalize
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
name|gimp_fill_editor_set_property
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
name|gimp_fill_editor_get_property
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpFillEditor,gimp_fill_editor,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpFillEditor
argument_list|,
argument|gimp_fill_editor
argument_list|,
argument|GTK_TYPE_BOX
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_fill_editor_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_fill_editor_class_init
parameter_list|(
name|GimpFillEditorClass
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
name|gimp_fill_editor_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_fill_editor_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_fill_editor_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_fill_editor_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_OPTIONS
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"options"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_FILL_OPTIONS
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_EDIT_CONTEXT
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"edit-context"
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
DECL|function|gimp_fill_editor_init (GimpFillEditor * editor)
name|gimp_fill_editor_init
parameter_list|(
name|GimpFillEditor
modifier|*
name|editor
parameter_list|)
block|{
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|editor
argument_list|)
argument_list|,
name|GTK_ORIENTATION_VERTICAL
argument_list|)
expr_stmt|;
name|gtk_box_set_spacing
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fill_editor_constructed (GObject * object)
name|gimp_fill_editor_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFillEditor
modifier|*
name|editor
init|=
name|GIMP_FILL_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|box
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
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
name|g_assert
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|box
operator|=
name|gimp_prop_enum_radio_box_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"style"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|editor
argument_list|)
argument_list|,
name|box
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
name|box
argument_list|)
expr_stmt|;
if|if
condition|(
name|editor
operator|->
name|edit_context
condition|)
block|{
name|GtkWidget
modifier|*
name|color_button
decl_stmt|;
name|GtkWidget
modifier|*
name|pattern_box
decl_stmt|;
name|color_button
operator|=
name|gimp_prop_color_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"foreground"
argument_list|,
name|_
argument_list|(
literal|"Fill Color"
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
literal|24
argument_list|,
name|GIMP_COLOR_AREA_SMALL_CHECKS
argument_list|)
expr_stmt|;
name|gimp_color_panel_set_context
argument_list|(
name|GIMP_COLOR_PANEL
argument_list|(
name|color_button
argument_list|)
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_enum_radio_box_add
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|color_button
argument_list|,
name|GIMP_FILL_STYLE_SOLID
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pattern_box
operator|=
name|gimp_prop_pattern_box_new
argument_list|(
name|NULL
argument_list|,
name|GIMP_CONTEXT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|2
argument_list|,
literal|"pattern-view-type"
argument_list|,
literal|"pattern-view-size"
argument_list|)
expr_stmt|;
name|gimp_enum_radio_box_add
argument_list|(
name|GTK_BOX
argument_list|(
name|box
argument_list|)
argument_list|,
name|pattern_box
argument_list|,
name|GIMP_FILL_STYLE_PATTERN
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|editor
operator|->
name|options
argument_list|)
argument_list|,
literal|"antialias"
argument_list|,
name|_
argument_list|(
literal|"_Antialiasing"
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
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_fill_editor_finalize (GObject * object)
name|gimp_fill_editor_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpFillEditor
modifier|*
name|editor
init|=
name|GIMP_FILL_EDITOR
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|editor
operator|->
name|options
condition|)
block|{
name|g_object_unref
argument_list|(
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
name|editor
operator|->
name|options
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
specifier|static
name|void
DECL|function|gimp_fill_editor_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_fill_editor_set_property
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
name|GimpFillEditor
modifier|*
name|editor
init|=
name|GIMP_FILL_EDITOR
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
name|PROP_OPTIONS
case|:
if|if
condition|(
name|editor
operator|->
name|options
condition|)
name|g_object_unref
argument_list|(
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
name|editor
operator|->
name|options
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDIT_CONTEXT
case|:
name|editor
operator|->
name|edit_context
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
DECL|function|gimp_fill_editor_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_fill_editor_get_property
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
name|GimpFillEditor
modifier|*
name|editor
init|=
name|GIMP_FILL_EDITOR
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
name|PROP_OPTIONS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|options
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_EDIT_CONTEXT
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|editor
operator|->
name|edit_context
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
name|GtkWidget
modifier|*
DECL|function|gimp_fill_editor_new (GimpFillOptions * options,gboolean edit_context)
name|gimp_fill_editor_new
parameter_list|(
name|GimpFillOptions
modifier|*
name|options
parameter_list|,
name|gboolean
name|edit_context
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_FILL_OPTIONS
argument_list|(
name|options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_FILL_EDITOR
argument_list|,
literal|"options"
argument_list|,
name|options
argument_list|,
literal|"edit-context"
argument_list|,
name|edit_context
condition|?
name|TRUE
else|:
name|FALSE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

