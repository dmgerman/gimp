begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolwidget.c  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasgroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvashandle.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasline.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvastransformguides.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolwidget.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2a115c840103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_SHELL
name|PROP_SHELL
block|,
DECL|enumerator|PROP_ITEM
name|PROP_ITEM
block|}
enum|;
end_enum

begin_enum
enum|enum
DECL|enum|__anon2a115c840203
block|{
DECL|enumerator|CHANGED
name|CHANGED
block|,
DECL|enumerator|SNAP_OFFSETS
name|SNAP_OFFSETS
block|,
DECL|enumerator|STATUS
name|STATUS
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpToolWidgetPrivate
struct|struct
name|_GimpToolWidgetPrivate
block|{
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|item
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
DECL|member|group_stack
name|GList
modifier|*
name|group_stack
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_tool_widget_finalize
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
name|gimp_tool_widget_constructed
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
name|gimp_tool_widget_set_property
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
name|gimp_tool_widget_get_property
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
name|gimp_tool_widget_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolWidget
argument_list|,
argument|gimp_tool_widget
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_widget_parent_class
end_define

begin_decl_stmt
specifier|static
name|guint
name|widget_signals
index|[
name|LAST_SIGNAL
index|]
init|=
block|{
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|gimp_tool_widget_class_init (GimpToolWidgetClass * klass)
name|gimp_tool_widget_class_init
parameter_list|(
name|GimpToolWidgetClass
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
name|finalize
operator|=
name|gimp_tool_widget_finalize
expr_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_tool_widget_constructed
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_tool_widget_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_tool_widget_get_property
expr_stmt|;
name|object_class
operator|->
name|dispatch_properties_changed
operator|=
name|gimp_tool_widget_properties_changed
expr_stmt|;
name|widget_signals
index|[
name|CHANGED
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"changed"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolWidgetClass
argument_list|,
name|changed
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|widget_signals
index|[
name|SNAP_OFFSETS
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"snap-offsets"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolWidgetClass
argument_list|,
name|snap_offsets
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__INT_INT_INT_INT
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|4
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|,
name|G_TYPE_INT
argument_list|)
expr_stmt|;
name|widget_signals
index|[
name|STATUS
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"status"
argument_list|,
name|G_TYPE_FROM_CLASS
argument_list|(
name|klass
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpToolWidgetClass
argument_list|,
name|status
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|g_cclosure_marshal_VOID__STRING
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|1
argument_list|,
name|G_TYPE_STRING
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_SHELL
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"shell"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_DISPLAY_SHELL
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
name|PROP_ITEM
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"item"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CANVAS_ITEM
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpToolWidgetPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_widget_init (GimpToolWidget * widget)
name|gimp_tool_widget_init
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|widget
operator|->
name|private
operator|=
name|G_TYPE_INSTANCE_GET_PRIVATE
argument_list|(
name|widget
argument_list|,
name|GIMP_TYPE_TOOL_WIDGET
argument_list|,
name|GimpToolWidgetPrivate
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_widget_constructed (GObject * object)
name|gimp_tool_widget_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolWidget
modifier|*
name|widget
init|=
name|GIMP_TOOL_WIDGET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpToolWidgetPrivate
modifier|*
name|private
init|=
name|widget
operator|->
name|private
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
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|private
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|item
operator|=
name|gimp_canvas_group_new
argument_list|(
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_widget_finalize (GObject * object)
name|gimp_tool_widget_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpToolWidget
modifier|*
name|widget
init|=
name|GIMP_TOOL_WIDGET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpToolWidgetPrivate
modifier|*
name|private
init|=
name|widget
operator|->
name|private
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|private
operator|->
name|item
argument_list|)
expr_stmt|;
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
DECL|function|gimp_tool_widget_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_tool_widget_set_property
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
name|GimpToolWidget
modifier|*
name|widget
init|=
name|GIMP_TOOL_WIDGET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpToolWidgetPrivate
modifier|*
name|private
init|=
name|widget
operator|->
name|private
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SHELL
case|:
name|private
operator|->
name|shell
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref */
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
DECL|function|gimp_tool_widget_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_tool_widget_get_property
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
name|GimpToolWidget
modifier|*
name|widget
init|=
name|GIMP_TOOL_WIDGET
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GimpToolWidgetPrivate
modifier|*
name|private
init|=
name|widget
operator|->
name|private
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_SHELL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_ITEM
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|item
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
DECL|function|gimp_tool_widget_properties_changed (GObject * object,guint n_pspecs,GParamSpec ** pspecs)
name|gimp_tool_widget_properties_changed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|n_pspecs
parameter_list|,
name|GParamSpec
modifier|*
modifier|*
name|pspecs
parameter_list|)
block|{
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dispatch_properties_changed
argument_list|(
name|object
argument_list|,
name|n_pspecs
argument_list|,
name|pspecs
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|object
argument_list|,
name|widget_signals
index|[
name|CHANGED
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDisplayShell
modifier|*
DECL|function|gimp_tool_widget_get_shell (GimpToolWidget * widget)
name|gimp_tool_widget_get_shell
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|widget
operator|->
name|private
operator|->
name|shell
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_tool_widget_get_item (GimpToolWidget * widget)
name|gimp_tool_widget_get_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|widget
operator|->
name|private
operator|->
name|item
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_snap_offsets (GimpToolWidget * widget,gint offset_x,gint offset_y,gint width,gint height)
name|gimp_tool_widget_snap_offsets
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|widget_signals
index|[
name|SNAP_OFFSETS
index|]
argument_list|,
literal|0
argument_list|,
name|offset_x
argument_list|,
name|offset_y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_status (GimpToolWidget * widget,const gchar * status)
name|gimp_tool_widget_status
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|gchar
modifier|*
name|status
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|widget
argument_list|,
name|widget_signals
index|[
name|STATUS
index|]
argument_list|,
literal|0
argument_list|,
name|status
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_add_item (GimpToolWidget * widget,GimpCanvasItem * item)
name|gimp_tool_widget_add_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasGroup
modifier|*
name|group
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|GIMP_CANVAS_GROUP
argument_list|(
name|widget
operator|->
name|private
operator|->
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|widget
operator|->
name|private
operator|->
name|group_stack
condition|)
name|group
operator|=
name|widget
operator|->
name|private
operator|->
name|group_stack
operator|->
name|data
expr_stmt|;
name|gimp_canvas_group_add_item
argument_list|(
name|group
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_remove_item (GimpToolWidget * widget,GimpCanvasItem * item)
name|gimp_tool_widget_remove_item
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_ITEM
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_canvas_group_remove_item
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|widget
operator|->
name|private
operator|->
name|item
argument_list|)
argument_list|,
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpCanvasGroup
modifier|*
DECL|function|gimp_tool_widget_add_stroke_group (GimpToolWidget * widget)
name|gimp_tool_widget_add_stroke_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_canvas_group_new
argument_list|(
name|widget
operator|->
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_canvas_group_set_group_stroking
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|item
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_widget_add_item
argument_list|(
name|widget
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|GIMP_CANVAS_GROUP
argument_list|(
name|item
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpCanvasGroup
modifier|*
DECL|function|gimp_tool_widget_add_fill_group (GimpToolWidget * widget)
name|gimp_tool_widget_add_fill_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_canvas_group_new
argument_list|(
name|widget
operator|->
name|private
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_canvas_group_set_group_filling
argument_list|(
name|GIMP_CANVAS_GROUP
argument_list|(
name|item
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_widget_add_item
argument_list|(
name|widget
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|GIMP_CANVAS_GROUP
argument_list|(
name|item
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_push_group (GimpToolWidget * widget,GimpCanvasGroup * group)
name|gimp_tool_widget_push_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|widget
operator|->
name|private
operator|->
name|group_stack
operator|=
name|g_list_prepend
argument_list|(
name|widget
operator|->
name|private
operator|->
name|group_stack
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_pop_group (GimpToolWidget * widget)
name|gimp_tool_widget_pop_group
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|widget
operator|->
name|private
operator|->
name|group_stack
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|widget
operator|->
name|private
operator|->
name|group_stack
operator|=
name|g_list_remove
argument_list|(
name|widget
operator|->
name|private
operator|->
name|group_stack
argument_list|,
name|widget
operator|->
name|private
operator|->
name|group_stack
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_tool_widget_add_line:  * @widget: the #GimpToolWidget  * @x1:     start point X in image coordinates  * @y1:     start point Y in image coordinates  * @x2:     end point X in image coordinates  * @y2:     end point Y in image coordinates  *  * This function adds a #GimpCanvasLine to @widget.  **/
end_comment

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_tool_widget_add_line (GimpToolWidget * widget,gdouble x1,gdouble y1,gdouble x2,gdouble y2)
name|gimp_tool_widget_add_line
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_canvas_line_new
argument_list|(
name|widget
operator|->
name|private
operator|->
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|)
expr_stmt|;
name|gimp_tool_widget_add_item
argument_list|(
name|widget
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_tool_widget_add_handle (GimpToolWidget * widget,GimpHandleType type,gdouble x,gdouble y,gint width,gint height,GimpHandleAnchor anchor)
name|gimp_tool_widget_add_handle
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GimpHandleType
name|type
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpHandleAnchor
name|anchor
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_canvas_handle_new
argument_list|(
name|widget
operator|->
name|private
operator|->
name|shell
argument_list|,
name|type
argument_list|,
name|anchor
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|width
argument_list|,
name|height
argument_list|)
expr_stmt|;
name|gimp_tool_widget_add_item
argument_list|(
name|widget
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_tool_widget_add_transform_guides (GimpToolWidget * widget,const GimpMatrix3 * transform,gdouble x1,gdouble y1,gdouble x2,gdouble y2,GimpGuidesType type,gint n_guides)
name|gimp_tool_widget_add_transform_guides
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpMatrix3
modifier|*
name|transform
parameter_list|,
name|gdouble
name|x1
parameter_list|,
name|gdouble
name|y1
parameter_list|,
name|gdouble
name|x2
parameter_list|,
name|gdouble
name|y2
parameter_list|,
name|GimpGuidesType
name|type
parameter_list|,
name|gint
name|n_guides
parameter_list|)
block|{
name|GimpCanvasItem
modifier|*
name|item
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|item
operator|=
name|gimp_canvas_transform_guides_new
argument_list|(
name|widget
operator|->
name|private
operator|->
name|shell
argument_list|,
name|transform
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
argument_list|,
name|y2
argument_list|,
name|type
argument_list|,
name|n_guides
argument_list|)
expr_stmt|;
name|gimp_tool_widget_add_item
argument_list|(
name|widget
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
return|return
name|item
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_tool_widget_button_press (GimpToolWidget * widget,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type)
name|gimp_tool_widget_button_press
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|button_press
condition|)
return|return
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|button_press
argument_list|(
name|widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|press_type
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_button_release (GimpToolWidget * widget,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type)
name|gimp_tool_widget_button_release
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|button_release
condition|)
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|button_release
argument_list|(
name|widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|release_type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_motion (GimpToolWidget * widget,const GimpCoords * coords,guint32 time,GdkModifierType state)
name|gimp_tool_widget_motion
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion
condition|)
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion
argument_list|(
name|widget
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_hover (GimpToolWidget * widget,const GimpCoords * coords,GdkModifierType state,gboolean proximity)
name|gimp_tool_widget_hover
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|gboolean
name|proximity
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|hover
condition|)
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|hover
argument_list|(
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_widget_key_press (GimpToolWidget * widget,GdkEventKey * kevent)
name|gimp_tool_widget_key_press
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|kevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|key_press
condition|)
return|return
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|key_press
argument_list|(
name|widget
argument_list|,
name|kevent
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_widget_key_release (GimpToolWidget * widget,GdkEventKey * kevent)
name|gimp_tool_widget_key_release
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|kevent
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|key_release
condition|)
return|return
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|key_release
argument_list|(
name|widget
argument_list|,
name|kevent
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_motion_modifier (GimpToolWidget * widget,GdkModifierType key,gboolean press,GdkModifierType state)
name|gimp_tool_widget_motion_modifier
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion_modifier
condition|)
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion_modifier
argument_list|(
name|widget
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_widget_hover_modifier (GimpToolWidget * widget,GdkModifierType key,gboolean press,GdkModifierType state)
name|gimp_tool_widget_hover_modifier
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion_modifier
condition|)
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|motion_modifier
argument_list|(
name|widget
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_widget_get_cursor (GimpToolWidget * widget,const GimpCoords * coords,GdkModifierType state,GimpCursorType * cursor,GimpToolCursorType * tool_cursor,GimpCursorModifier * cursor_modifier)
name|gimp_tool_widget_get_cursor
parameter_list|(
name|GimpToolWidget
modifier|*
name|widget
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpCursorType
modifier|*
name|cursor
parameter_list|,
name|GimpToolCursorType
modifier|*
name|tool_cursor
parameter_list|,
name|GimpCursorModifier
modifier|*
name|cursor_modifier
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_WIDGET
argument_list|(
name|widget
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|coords
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|get_cursor
condition|)
block|{
name|GimpCursorType
name|my_cursor
decl_stmt|;
name|GimpToolCursorType
name|my_tool_cursor
decl_stmt|;
name|GimpCursorModifier
name|my_cursor_modifier
decl_stmt|;
if|if
condition|(
name|cursor
condition|)
name|my_cursor
operator|=
operator|*
name|cursor
expr_stmt|;
if|if
condition|(
name|tool_cursor
condition|)
name|my_tool_cursor
operator|=
operator|*
name|tool_cursor
expr_stmt|;
if|if
condition|(
name|cursor_modifier
condition|)
name|my_cursor_modifier
operator|=
operator|*
name|cursor_modifier
expr_stmt|;
if|if
condition|(
name|GIMP_TOOL_WIDGET_GET_CLASS
argument_list|(
name|widget
argument_list|)
operator|->
name|get_cursor
argument_list|(
name|widget
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
operator|&
name|my_cursor
argument_list|,
operator|&
name|my_tool_cursor
argument_list|,
operator|&
name|my_cursor_modifier
argument_list|)
condition|)
block|{
if|if
condition|(
name|cursor
condition|)
operator|*
name|cursor
operator|=
name|my_cursor
expr_stmt|;
if|if
condition|(
name|tool_cursor
condition|)
operator|*
name|tool_cursor
operator|=
name|my_tool_cursor
expr_stmt|;
if|if
condition|(
name|cursor_modifier
condition|)
operator|*
name|cursor_modifier
operator|=
name|my_cursor_modifier
expr_stmt|;
return|return
name|TRUE
return|;
block|}
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

