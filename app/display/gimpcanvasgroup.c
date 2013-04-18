begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcanvasgroup.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"display-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpcanvasgroup.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon27e7fd380103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_GROUP_STROKING
name|PROP_GROUP_STROKING
block|,
DECL|enumerator|PROP_GROUP_FILLING
name|PROP_GROUP_FILLING
block|}
enum|;
end_enum

begin_typedef
DECL|typedef|GimpCanvasGroupPrivate
typedef|typedef
name|struct
name|_GimpCanvasGroupPrivate
name|GimpCanvasGroupPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCanvasGroupPrivate
struct|struct
name|_GimpCanvasGroupPrivate
block|{
DECL|member|items
name|GList
modifier|*
name|items
decl_stmt|;
DECL|member|group_stroking
name|gboolean
name|group_stroking
decl_stmt|;
DECL|member|group_filling
name|gboolean
name|group_filling
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (group)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|group
parameter_list|)
define|\
value|G_TYPE_INSTANCE_GET_PRIVATE (group, \                                      GIMP_TYPE_CANVAS_GROUP, \                                      GimpCanvasGroupPrivate)
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_canvas_group_dispose
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
name|gimp_canvas_group_set_property
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
name|gimp_canvas_group_get_property
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
name|gimp_canvas_group_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|cairo_region_t
modifier|*
name|gimp_canvas_group_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_canvas_group_hit
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_canvas_group_child_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpCanvasGroup,gimp_canvas_group,GIMP_TYPE_CANVAS_ITEM)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpCanvasGroup
argument_list|,
argument|gimp_canvas_group
argument_list|,
argument|GIMP_TYPE_CANVAS_ITEM
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_canvas_group_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_canvas_group_class_init
parameter_list|(
name|GimpCanvasGroupClass
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
name|GimpCanvasItemClass
modifier|*
name|item_class
init|=
name|GIMP_CANVAS_ITEM_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_canvas_group_dispose
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_canvas_group_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_canvas_group_get_property
expr_stmt|;
name|item_class
operator|->
name|draw
operator|=
name|gimp_canvas_group_draw
expr_stmt|;
name|item_class
operator|->
name|get_extents
operator|=
name|gimp_canvas_group_get_extents
expr_stmt|;
name|item_class
operator|->
name|hit
operator|=
name|gimp_canvas_group_hit
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GROUP_STROKING
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"group-stroking"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_GROUP_FILLING
argument_list|,
name|g_param_spec_boolean
argument_list|(
literal|"group-filling"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PARAM_READWRITE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpCanvasGroupPrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_group_init (GimpCanvasGroup * group)
name|gimp_canvas_group_init
parameter_list|(
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_group_dispose (GObject * object)
name|gimp_canvas_group_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|private
operator|->
name|items
condition|)
block|{
name|g_list_free_full
argument_list|(
name|private
operator|->
name|items
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
name|private
operator|->
name|items
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
DECL|function|gimp_canvas_group_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_canvas_group_set_property
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
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_GROUP_STROKING
case|:
name|private
operator|->
name|group_stroking
operator|=
name|g_value_get_boolean
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GROUP_FILLING
case|:
name|private
operator|->
name|group_filling
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
DECL|function|gimp_canvas_group_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_canvas_group_get_property
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
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
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
name|PROP_GROUP_STROKING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|group_stroking
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GROUP_FILLING
case|:
name|g_value_set_boolean
argument_list|(
name|value
argument_list|,
name|private
operator|->
name|group_filling
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
DECL|function|gimp_canvas_group_draw (GimpCanvasItem * item,cairo_t * cr)
name|gimp_canvas_group_draw
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|items
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
name|GimpCanvasItem
modifier|*
name|sub_item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_canvas_item_draw
argument_list|(
name|sub_item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|private
operator|->
name|group_stroking
condition|)
name|_gimp_canvas_item_stroke
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_filling
condition|)
name|_gimp_canvas_item_fill
argument_list|(
name|item
argument_list|,
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|cairo_region_t
modifier|*
DECL|function|gimp_canvas_group_get_extents (GimpCanvasItem * item)
name|gimp_canvas_group_get_extents
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|cairo_region_t
modifier|*
name|region
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|items
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
name|GimpCanvasItem
modifier|*
name|sub_item
init|=
name|list
operator|->
name|data
decl_stmt|;
name|cairo_region_t
modifier|*
name|sub_region
init|=
name|gimp_canvas_item_get_extents
argument_list|(
name|sub_item
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|region
condition|)
block|{
name|region
operator|=
name|sub_region
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|sub_region
condition|)
block|{
name|cairo_region_union
argument_list|(
name|region
argument_list|,
name|sub_region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|sub_region
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|region
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_canvas_group_hit (GimpCanvasItem * item,gdouble x,gdouble y)
name|gimp_canvas_group_hit
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|item
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|items
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
if|if
condition|(
name|gimp_canvas_item_hit
argument_list|(
name|list
operator|->
name|data
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
condition|)
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_canvas_group_child_update (GimpCanvasItem * item,cairo_region_t * region,GimpCanvasGroup * group)
name|gimp_canvas_group_child_update
parameter_list|(
name|GimpCanvasItem
modifier|*
name|item
parameter_list|,
name|cairo_region_t
modifier|*
name|region
parameter_list|,
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|)
block|{
if|if
condition|(
name|_gimp_canvas_item_needs_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
condition|)
name|_gimp_canvas_item_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|,
name|region
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpCanvasItem
modifier|*
DECL|function|gimp_canvas_group_new (GimpDisplayShell * shell)
name|gimp_canvas_group_new
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY_SHELL
argument_list|(
name|shell
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_CANVAS_GROUP
argument_list|,
literal|"shell"
argument_list|,
name|shell
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_group_add_item (GimpCanvasGroup * group,GimpCanvasItem * item)
name|gimp_canvas_group_add_item
parameter_list|(
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_GROUP
argument_list|(
name|group
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
name|g_return_if_fail
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
operator|!=
name|item
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|group
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_stroking
condition|)
name|gimp_canvas_item_suspend_stroking
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_filling
condition|)
name|gimp_canvas_item_suspend_filling
argument_list|(
name|item
argument_list|)
expr_stmt|;
name|private
operator|->
name|items
operator|=
name|g_list_append
argument_list|(
name|private
operator|->
name|items
argument_list|,
name|g_object_ref
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|_gimp_canvas_item_needs_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
condition|)
block|{
name|cairo_region_t
modifier|*
name|region
init|=
name|gimp_canvas_item_get_extents
argument_list|(
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|region
condition|)
block|{
name|_gimp_canvas_item_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_connect
argument_list|(
name|item
argument_list|,
literal|"update"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_canvas_group_child_update
argument_list|)
argument_list|,
name|group
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_group_remove_item (GimpCanvasGroup * group,GimpCanvasItem * item)
name|gimp_canvas_group_remove_item
parameter_list|(
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|,
name|GimpCanvasItem
modifier|*
name|item
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_GROUP
argument_list|(
name|group
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
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|group
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|g_list_find
argument_list|(
name|private
operator|->
name|items
argument_list|,
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|->
name|items
operator|=
name|g_list_remove
argument_list|(
name|private
operator|->
name|items
argument_list|,
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_stroking
condition|)
name|gimp_canvas_item_resume_stroking
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_filling
condition|)
name|gimp_canvas_item_resume_filling
argument_list|(
name|item
argument_list|)
expr_stmt|;
if|if
condition|(
name|_gimp_canvas_item_needs_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
condition|)
block|{
name|cairo_region_t
modifier|*
name|region
init|=
name|gimp_canvas_item_get_extents
argument_list|(
name|item
argument_list|)
decl_stmt|;
if|if
condition|(
name|region
condition|)
block|{
name|_gimp_canvas_item_update
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|,
name|region
argument_list|)
expr_stmt|;
name|cairo_region_destroy
argument_list|(
name|region
argument_list|)
expr_stmt|;
block|}
block|}
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|item
argument_list|,
name|gimp_canvas_group_child_update
argument_list|,
name|group
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|item
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_group_set_group_stroking (GimpCanvasGroup * group,gboolean group_stroking)
name|gimp_canvas_group_set_group_stroking
parameter_list|(
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|,
name|gboolean
name|group_stroking
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|group
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_stroking
operator|!=
name|group_stroking
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|group
argument_list|,
literal|"group-stroking"
argument_list|,
name|group_stroking
condition|?
name|TRUE
else|:
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|items
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
if|if
condition|(
name|private
operator|->
name|group_stroking
condition|)
name|gimp_canvas_item_suspend_stroking
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
else|else
name|gimp_canvas_item_resume_stroking
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_canvas_item_end_change
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_canvas_group_set_group_filling (GimpCanvasGroup * group,gboolean group_filling)
name|gimp_canvas_group_set_group_filling
parameter_list|(
name|GimpCanvasGroup
modifier|*
name|group
parameter_list|,
name|gboolean
name|group_filling
parameter_list|)
block|{
name|GimpCanvasGroupPrivate
modifier|*
name|private
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CANVAS_GROUP
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|group
argument_list|)
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|group_filling
operator|!=
name|group_filling
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gimp_canvas_item_begin_change
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|group
argument_list|,
literal|"group-filling"
argument_list|,
name|group_filling
condition|?
name|TRUE
else|:
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|private
operator|->
name|items
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
if|if
condition|(
name|private
operator|->
name|group_filling
condition|)
name|gimp_canvas_item_suspend_filling
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
else|else
name|gimp_canvas_item_resume_filling
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|gimp_canvas_item_end_change
argument_list|(
name|GIMP_CANVAS_ITEM
argument_list|(
name|group
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

