begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprogress.c  * Copyright (C) 2004  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimpmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2c000d830103
block|{
DECL|enumerator|CANCEL
name|CANCEL
block|,
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_progress_iface_base_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|progress_iface
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|progress_signals
specifier|static
name|guint
name|progress_signals
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
name|GType
DECL|function|gimp_progress_interface_get_type (void)
name|gimp_progress_interface_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|progress_iface_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|progress_iface_type
condition|)
block|{
specifier|const
name|GTypeInfo
name|progress_iface_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpProgressInterface
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|gimp_progress_iface_base_init
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|progress_iface_type
operator|=
name|g_type_register_static
argument_list|(
name|G_TYPE_INTERFACE
argument_list|,
literal|"GimpProgressInterface"
argument_list|,
operator|&
name|progress_iface_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_interface_add_prerequisite
argument_list|(
name|progress_iface_type
argument_list|,
name|G_TYPE_OBJECT
argument_list|)
expr_stmt|;
block|}
return|return
name|progress_iface_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_progress_iface_base_init (GimpProgressInterface * progress_iface)
name|gimp_progress_iface_base_init
parameter_list|(
name|GimpProgressInterface
modifier|*
name|progress_iface
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
if|if
condition|(
operator|!
name|initialized
condition|)
block|{
name|progress_signals
index|[
name|CANCEL
index|]
operator|=
name|g_signal_new
argument_list|(
literal|"cancel"
argument_list|,
name|G_TYPE_FROM_INTERFACE
argument_list|(
name|progress_iface
argument_list|)
argument_list|,
name|G_SIGNAL_RUN_FIRST
argument_list|,
name|G_STRUCT_OFFSET
argument_list|(
name|GimpProgressInterface
argument_list|,
name|cancel
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_marshal_VOID__VOID
argument_list|,
name|G_TYPE_NONE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|TRUE
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpProgress
modifier|*
DECL|function|gimp_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_progress_start
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
name|gboolean
name|cancelable
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|message
condition|)
name|message
operator|=
name|_
argument_list|(
literal|"Please wait"
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|start
condition|)
return|return
name|progress_iface
operator|->
name|start
argument_list|(
name|progress
argument_list|,
name|message
argument_list|,
name|cancelable
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_end (GimpProgress * progress)
name|gimp_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|end
condition|)
name|progress_iface
operator|->
name|end
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_progress_is_active (GimpProgress * progress)
name|gimp_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|is_active
condition|)
return|return
name|progress_iface
operator|->
name|is_active
argument_list|(
name|progress
argument_list|)
return|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_progress_set_text
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
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|message
operator|||
operator|!
name|strlen
argument_list|(
name|message
argument_list|)
condition|)
name|message
operator|=
name|_
argument_list|(
literal|"Please wait"
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|set_text
condition|)
name|progress_iface
operator|->
name|set_text
argument_list|(
name|progress
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|percentage
operator|=
name|CLAMP
argument_list|(
name|percentage
argument_list|,
literal|0.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|set_value
condition|)
name|progress_iface
operator|->
name|set_value
argument_list|(
name|progress
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gdouble
DECL|function|gimp_progress_get_value (GimpProgress * progress)
name|gimp_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|get_value
condition|)
return|return
name|progress_iface
operator|->
name|get_value
argument_list|(
name|progress
argument_list|)
return|;
return|return
literal|0.0
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_pulse (GimpProgress * progress)
name|gimp_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|pulse
condition|)
name|progress_iface
operator|->
name|pulse
argument_list|(
name|progress
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|guint32
DECL|function|gimp_progress_get_window_id (GimpProgress * progress)
name|gimp_progress_get_window_id
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|get_window_id
condition|)
return|return
name|progress_iface
operator|->
name|get_window_id
argument_list|(
name|progress
argument_list|)
return|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_progress_message
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
name|GimpProgressInterface
modifier|*
name|progress_iface
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|message
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|progress_iface
operator|=
name|GIMP_PROGRESS_GET_INTERFACE
argument_list|(
name|progress
argument_list|)
expr_stmt|;
if|if
condition|(
name|progress_iface
operator|->
name|message
condition|)
return|return
name|progress_iface
operator|->
name|message
argument_list|(
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

begin_function
name|void
DECL|function|gimp_progress_cancel (GimpProgress * progress)
name|gimp_progress_cancel
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PROGRESS
argument_list|(
name|progress
argument_list|)
argument_list|)
expr_stmt|;
name|g_signal_emit
argument_list|(
name|progress
argument_list|,
name|progress_signals
index|[
name|CANCEL
index|]
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_progress_update_and_flush (gint min,gint max,gint current,gpointer data)
name|gimp_progress_update_and_flush
parameter_list|(
name|gint
name|min
parameter_list|,
name|gint
name|max
parameter_list|,
name|gint
name|current
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|gimp_progress_set_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|data
argument_list|)
argument_list|,
call|(
name|gdouble
call|)
argument_list|(
name|current
operator|-
name|min
argument_list|)
operator|/
call|(
name|gdouble
call|)
argument_list|(
name|max
operator|-
name|min
argument_list|)
argument_list|)
expr_stmt|;
while|while
condition|(
name|g_main_context_pending
argument_list|(
name|NULL
argument_list|)
condition|)
name|g_main_context_iteration
argument_list|(
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

