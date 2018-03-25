begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpsubprogress.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2bf6ab020103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_PROGRESS
name|PROP_PROGRESS
block|}
enum|;
end_enum

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_finalize
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
name|gimp_sub_progress_set_property
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
name|gimp_sub_progress_get_property
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
name|GimpProgress
modifier|*
name|gimp_sub_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|cancellable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_sub_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_sub_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_sub_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|guint32
name|gimp_sub_progress_get_window_id
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_sub_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpSubProgress,gimp_sub_progress,G_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,gimp_sub_progress_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpSubProgress
argument_list|,
argument|gimp_sub_progress
argument_list|,
argument|G_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,                                                 gimp_sub_progress_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_sub_progress_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_sub_progress_class_init
parameter_list|(
name|GimpSubProgressClass
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
name|gimp_sub_progress_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_sub_progress_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_sub_progress_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PROGRESS
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"progress"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PROGRESS
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
DECL|function|gimp_sub_progress_init (GimpSubProgress * sub)
name|gimp_sub_progress_init
parameter_list|(
name|GimpSubProgress
modifier|*
name|sub
parameter_list|)
block|{
name|sub
operator|->
name|progress
operator|=
name|NULL
expr_stmt|;
name|sub
operator|->
name|start
operator|=
literal|0.0
expr_stmt|;
name|sub
operator|->
name|end
operator|=
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_finalize (GObject * object)
name|gimp_sub_progress_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|sub
operator|->
name|progress
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
DECL|function|gimp_sub_progress_iface_init (GimpProgressInterface * iface)
name|gimp_sub_progress_iface_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|iface
parameter_list|)
block|{
name|iface
operator|->
name|start
operator|=
name|gimp_sub_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_sub_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_sub_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_sub_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_sub_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_sub_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_sub_progress_pulse
expr_stmt|;
name|iface
operator|->
name|get_window_id
operator|=
name|gimp_sub_progress_get_window_id
expr_stmt|;
name|iface
operator|->
name|message
operator|=
name|gimp_sub_progress_message
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_sub_progress_set_property
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
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
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
name|PROP_PROGRESS
case|:
name|g_return_if_fail
argument_list|(
name|sub
operator|->
name|progress
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|sub
operator|->
name|progress
operator|=
name|g_value_dup_object
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
DECL|function|gimp_sub_progress_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_sub_progress_get_property
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
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
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
name|PROP_PROGRESS
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|sub
operator|->
name|progress
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
name|GimpProgress
modifier|*
DECL|function|gimp_sub_progress_start (GimpProgress * progress,gboolean cancellable,const gchar * message)
name|gimp_sub_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gboolean
name|cancellable
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
comment|/* does nothing */
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_end (GimpProgress * progress)
name|gimp_sub_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
comment|/* does nothing */
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_sub_progress_is_active (GimpProgress * progress)
name|gimp_sub_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
return|return
name|gimp_progress_is_active
argument_list|(
name|sub
operator|->
name|progress
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_sub_progress_set_text
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
comment|/* does nothing */
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_sub_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
name|gimp_progress_set_value
argument_list|(
name|sub
operator|->
name|progress
argument_list|,
name|sub
operator|->
name|start
operator|+
name|percentage
operator|*
operator|(
name|sub
operator|->
name|end
operator|-
name|sub
operator|->
name|start
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_sub_progress_get_value (GimpProgress * progress)
name|gimp_sub_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
return|return
name|gimp_progress_get_value
argument_list|(
name|sub
operator|->
name|progress
argument_list|)
return|;
return|return
literal|0.0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_sub_progress_pulse (GimpProgress * progress)
name|gimp_sub_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
name|gimp_progress_pulse
argument_list|(
name|sub
operator|->
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gimp_sub_progress_get_window_id (GimpProgress * progress)
name|gimp_sub_progress_get_window_id
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
return|return
name|gimp_progress_get_window_id
argument_list|(
name|sub
operator|->
name|progress
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_sub_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_sub_progress_message
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpMessageSeverity
name|severity
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
init|=
name|GIMP_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|sub
operator|->
name|progress
condition|)
return|return
name|gimp_progress_message
argument_list|(
name|sub
operator|->
name|progress
argument_list|,
name|gimp
argument_list|,
name|severity
argument_list|,
name|domain
argument_list|,
name|message
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_sub_progress_new:  * @progress: parent progress or %NULL  *  * GimpSubProgress implements the GimpProgress interface and can be  * used wherever a GimpProgress is needed. It maps progress  * information to a sub-range of its parent @progress. This is useful  * when an action breaks down into multiple sub-actions that itself  * need a #GimpProgress pointer. See gimp_image_scale() for an example.  *  * Return value: a new #GimpProgress object  */
end_comment

begin_function
name|GimpProgress
modifier|*
DECL|function|gimp_sub_progress_new (GimpProgress * progress)
name|gimp_sub_progress_new
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpSubProgress
modifier|*
name|sub
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|progress
operator|==
name|NULL
operator|||
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sub
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_SUB_PROGRESS
argument_list|,
literal|"progress"
argument_list|,
name|progress
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|GIMP_PROGRESS
argument_list|(
name|sub
argument_list|)
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_sub_progress_set_range:  * @start: start value of range on the parent process  * @end:   end value of range on the parent process  *  * Sets a range on the parent progress that this @progress should be  * mapped to.  */
end_comment

begin_function
name|void
DECL|function|gimp_sub_progress_set_range (GimpSubProgress * progress,gdouble start,gdouble end)
name|gimp_sub_progress_set_range
parameter_list|(
name|GimpSubProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|start
parameter_list|,
name|gdouble
name|end
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|start
operator|<
name|end
argument_list|)
expr_stmt|;
name|progress
operator|->
name|start
operator|=
name|start
expr_stmt|;
name|progress
operator|->
name|end
operator|=
name|end
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_sub_progress_set_step:  * @index:     step index  * @num_steps: number of steps  *  * A more convenient form of gimp_sub_progress_set_range().  */
end_comment

begin_function
name|void
DECL|function|gimp_sub_progress_set_step (GimpSubProgress * progress,gint index,gint num_steps)
name|gimp_sub_progress_set_step
parameter_list|(
name|GimpSubProgress
modifier|*
name|progress
parameter_list|,
name|gint
name|index
parameter_list|,
name|gint
name|num_steps
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SUB_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|index
operator|<
name|num_steps
operator|&&
name|num_steps
operator|>
literal|0
argument_list|)
expr_stmt|;
name|progress
operator|->
name|start
operator|=
operator|(
name|gdouble
operator|)
name|index
operator|/
name|num_steps
expr_stmt|;
name|progress
operator|->
name|end
operator|=
call|(
name|gdouble
call|)
argument_list|(
name|index
operator|+
literal|1
argument_list|)
operator|/
name|num_steps
expr_stmt|;
block|}
end_function

end_unit

