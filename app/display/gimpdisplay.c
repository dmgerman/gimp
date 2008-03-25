begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpdisplayconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimparea.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprogress.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplay-handlers.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-handlers.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-icon.h"
end_include

begin_include
include|#
directive|include
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28ec5f1d0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_ID
name|PROP_ID
block|,
DECL|enumerator|PROP_GIMP
name|PROP_GIMP
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|,
DECL|enumerator|PROP_SHELL
name|PROP_SHELL
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_progress_iface_init
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
name|gimp_display_set_property
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
name|gimp_display_get_property
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
name|gimp_display_progress_start
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_progress_end
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
name|gimp_display_progress_is_active
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
name|gimp_display_progress_set_text
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
name|gimp_display_progress_set_value
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
name|gimp_display_progress_get_value
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
name|gimp_display_progress_pulse
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
name|gimp_display_progress_get_window
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
name|gimp_display_progress_message
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

begin_function_decl
specifier|static
name|void
name|gimp_display_progress_canceled
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_flush_whenever
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|now
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_paint_area
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_CODE (GimpDisplay,gimp_display,GIMP_TYPE_OBJECT,G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,gimp_display_progress_iface_init))
name|G_DEFINE_TYPE_WITH_CODE
argument_list|(
argument|GimpDisplay
argument_list|,
argument|gimp_display
argument_list|,
argument|GIMP_TYPE_OBJECT
argument_list|,
argument|G_IMPLEMENT_INTERFACE (GIMP_TYPE_PROGRESS,                                                 gimp_display_progress_iface_init)
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_display_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_display_class_init
parameter_list|(
name|GimpDisplayClass
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
name|set_property
operator|=
name|gimp_display_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_display_get_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_ID
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"id"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
literal|0
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
name|PROP_GIMP
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"gimp"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_GIMP
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
name|PROP_IMAGE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"image"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
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
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_init (GimpDisplay * display)
name|gimp_display_init
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|display
operator|->
name|ID
operator|=
literal|0
expr_stmt|;
name|display
operator|->
name|gimp
operator|=
name|NULL
expr_stmt|;
name|display
operator|->
name|image
operator|=
name|NULL
expr_stmt|;
name|display
operator|->
name|instance
operator|=
literal|0
expr_stmt|;
name|display
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|display
operator|->
name|update_areas
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_progress_iface_init (GimpProgressInterface * iface)
name|gimp_display_progress_iface_init
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
name|gimp_display_progress_start
expr_stmt|;
name|iface
operator|->
name|end
operator|=
name|gimp_display_progress_end
expr_stmt|;
name|iface
operator|->
name|is_active
operator|=
name|gimp_display_progress_is_active
expr_stmt|;
name|iface
operator|->
name|set_text
operator|=
name|gimp_display_progress_set_text
expr_stmt|;
name|iface
operator|->
name|set_value
operator|=
name|gimp_display_progress_set_value
expr_stmt|;
name|iface
operator|->
name|get_value
operator|=
name|gimp_display_progress_get_value
expr_stmt|;
name|iface
operator|->
name|pulse
operator|=
name|gimp_display_progress_pulse
expr_stmt|;
name|iface
operator|->
name|get_window
operator|=
name|gimp_display_progress_get_window
expr_stmt|;
name|iface
operator|->
name|message
operator|=
name|gimp_display_progress_message
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_display_set_property
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
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
name|PROP_ID
case|:
name|display
operator|->
name|ID
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMP
case|:
name|display
operator|->
name|gimp
operator|=
name|g_value_get_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
comment|/* don't ref the gimp */
name|display
operator|->
name|config
operator|=
name|GIMP_DISPLAY_CONFIG
argument_list|(
name|display
operator|->
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
case|case
name|PROP_SHELL
case|:
name|g_assert_not_reached
argument_list|()
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
DECL|function|gimp_display_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_display_get_property
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
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
name|PROP_ID
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|ID
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_GIMP
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_SHELL
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|display
operator|->
name|shell
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
DECL|function|gimp_display_progress_start (GimpProgress * progress,const gchar * message,gboolean cancelable)
name|gimp_display_progress_start
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
return|return
name|gimp_progress_start
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
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
specifier|static
name|void
DECL|function|gimp_display_progress_end (GimpProgress * progress)
name|gimp_display_progress_end
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
name|gimp_progress_end
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_progress_is_active (GimpProgress * progress)
name|gimp_display_progress_is_active
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
return|return
name|gimp_progress_is_active
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
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
DECL|function|gimp_display_progress_set_text (GimpProgress * progress,const gchar * message)
name|gimp_display_progress_set_text
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
name|gimp_progress_set_text
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|,
name|message
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_progress_set_value (GimpProgress * progress,gdouble percentage)
name|gimp_display_progress_set_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|percentage
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
name|gimp_progress_set_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|,
name|percentage
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gdouble
DECL|function|gimp_display_progress_get_value (GimpProgress * progress)
name|gimp_display_progress_get_value
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
return|return
name|gimp_progress_get_value
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
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
DECL|function|gimp_display_progress_pulse (GimpProgress * progress)
name|gimp_display_progress_pulse
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
name|gimp_progress_pulse
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|guint32
DECL|function|gimp_display_progress_get_window (GimpProgress * progress)
name|gimp_display_progress_get_window
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
return|return
name|gimp_progress_get_window
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
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
DECL|function|gimp_display_progress_message (GimpProgress * progress,Gimp * gimp,GimpMessageSeverity severity,const gchar * domain,const gchar * message)
name|gimp_display_progress_message
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
name|GimpDisplay
modifier|*
name|display
init|=
name|GIMP_DISPLAY
argument_list|(
name|progress
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
return|return
name|gimp_progress_message
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
operator|->
name|shell
argument_list|)
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
specifier|static
name|void
DECL|function|gimp_display_progress_canceled (GimpProgress * progress,GimpDisplay * display)
name|gimp_display_progress_canceled
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|gimp_progress_cancel
argument_list|(
name|GIMP_PROGRESS
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpDisplay
modifier|*
DECL|function|gimp_display_new (Gimp * gimp,GimpImage * image,GimpUnit unit,gdouble scale,GimpMenuFactory * menu_factory,GimpUIManager * popup_manager,GimpDialogFactory * display_factory)
name|gimp_display_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GimpUIManager
modifier|*
name|popup_manager
parameter_list|,
name|GimpDialogFactory
modifier|*
name|display_factory
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
name|gint
name|ID
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  If there isn't an interface, never create a display  */
if|if
condition|(
name|gimp
operator|->
name|no_interface
condition|)
return|return
name|NULL
return|;
do|do
block|{
name|ID
operator|=
name|gimp
operator|->
name|next_display_ID
operator|++
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|next_display_ID
operator|==
name|G_MAXINT
condition|)
name|gimp
operator|->
name|next_display_ID
operator|=
literal|1
expr_stmt|;
block|}
do|while
condition|(
name|gimp_display_get_by_ID
argument_list|(
name|gimp
argument_list|,
name|ID
argument_list|)
condition|)
do|;
name|display
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DISPLAY
argument_list|,
literal|"id"
argument_list|,
name|ID
argument_list|,
literal|"gimp"
argument_list|,
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  refs the image  */
if|if
condition|(
name|image
condition|)
name|gimp_display_connect
argument_list|(
name|display
argument_list|,
name|image
argument_list|)
expr_stmt|;
comment|/*  create the shell for the image  */
name|display
operator|->
name|shell
operator|=
name|gimp_display_shell_new
argument_list|(
name|display
argument_list|,
name|unit
argument_list|,
name|scale
argument_list|,
name|menu_factory
argument_list|,
name|popup_manager
argument_list|,
name|display_factory
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|display
operator|->
name|shell
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
operator|->
name|statusbar
argument_list|,
literal|"cancel"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_display_progress_canceled
argument_list|)
argument_list|,
name|display
argument_list|)
expr_stmt|;
comment|/* add the display to the list */
name|gimp_container_add
argument_list|(
name|gimp
operator|->
name|displays
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|display
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_delete (GimpDisplay * display)
name|gimp_display_delete
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
comment|/* remove the display from the list */
name|gimp_container_remove
argument_list|(
name|display
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  unrefs the image  */
name|gimp_display_set_image
argument_list|(
name|display
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|active_tool
operator|&&
name|active_tool
operator|->
name|focus_display
operator|==
name|display
condition|)
name|tool_manager_focus_display_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  free the update area lists  */
name|gimp_area_list_free
argument_list|(
name|display
operator|->
name|update_areas
argument_list|)
expr_stmt|;
name|display
operator|->
name|update_areas
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|display
operator|->
name|shell
condition|)
block|{
name|GtkWidget
modifier|*
name|shell
init|=
name|display
operator|->
name|shell
decl_stmt|;
comment|/*  set display->shell to NULL *before* destroying the shell.        *  all callbacks in gimpdisplayshell-callbacks.c will check        *  this pointer and do nothing if the shell is in destruction.        */
name|display
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|shell
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_display_get_ID (GimpDisplay * display)
name|gimp_display_get_ID
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|display
operator|->
name|ID
return|;
block|}
end_function

begin_function
name|GimpDisplay
modifier|*
DECL|function|gimp_display_get_by_ID (Gimp * gimp,gint ID)
name|gimp_display_get_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
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
name|GimpDisplay
modifier|*
name|display
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|display
operator|->
name|ID
operator|==
name|ID
condition|)
return|return
name|display
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_set_image (GimpDisplay * display,GimpImage * image)
name|gimp_display_set_image
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
block|{
name|GimpImage
modifier|*
name|old_image
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|image
operator|==
name|NULL
operator|||
name|GIMP_IS_IMAGE
argument_list|(
name|image
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|display
operator|->
name|image
condition|)
block|{
comment|/*  stop any active tool  */
name|tool_manager_control_active
argument_list|(
name|display
operator|->
name|gimp
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|gimp_display_shell_disconnect
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|old_image
operator|=
name|g_object_ref
argument_list|(
name|display
operator|->
name|image
argument_list|)
expr_stmt|;
name|gimp_display_disconnect
argument_list|(
name|display
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image
condition|)
name|gimp_display_connect
argument_list|(
name|display
argument_list|,
name|image
argument_list|)
expr_stmt|;
if|if
condition|(
name|old_image
condition|)
name|g_object_unref
argument_list|(
name|old_image
argument_list|)
expr_stmt|;
if|if
condition|(
name|image
condition|)
name|gimp_display_shell_reconnect
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
else|else
name|gimp_display_shell_icon_update
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_empty (GimpDisplay * display)
name|gimp_display_empty
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|display
operator|->
name|image
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_set_image
argument_list|(
name|display
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_display_shell_empty
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_fill (GimpDisplay * display,GimpImage * image,GimpUnit unit,gdouble scale)
name|gimp_display_fill
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
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
name|gimp_display_set_image
argument_list|(
name|display
argument_list|,
name|image
argument_list|)
expr_stmt|;
name|gimp_display_shell_fill
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|,
name|image
argument_list|,
name|unit
argument_list|,
name|scale
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_update_area (GimpDisplay * display,gboolean now,gint x,gint y,gint w,gint h)
name|gimp_display_update_area
parameter_list|(
name|GimpDisplay
modifier|*
name|display
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
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|now
condition|)
block|{
name|gimp_display_paint_area
argument_list|(
name|display
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpArea
modifier|*
name|area
decl_stmt|;
name|gint
name|image_width
init|=
name|gimp_image_get_width
argument_list|(
name|display
operator|->
name|image
argument_list|)
decl_stmt|;
name|gint
name|image_height
init|=
name|gimp_image_get_height
argument_list|(
name|display
operator|->
name|image
argument_list|)
decl_stmt|;
name|area
operator|=
name|gimp_area_new
argument_list|(
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|image_height
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|x
operator|+
name|w
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|y
operator|+
name|h
argument_list|,
literal|0
argument_list|,
name|image_height
argument_list|)
argument_list|)
expr_stmt|;
name|display
operator|->
name|update_areas
operator|=
name|gimp_area_list_process
argument_list|(
name|display
operator|->
name|update_areas
argument_list|,
name|area
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_flush (GimpDisplay * display)
name|gimp_display_flush
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_flush_whenever
argument_list|(
name|display
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_flush_now (GimpDisplay * display)
name|gimp_display_flush_now
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_flush_whenever
argument_list|(
name|display
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_flush_whenever (GimpDisplay * display,gboolean now)
name|gimp_display_flush_whenever
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gboolean
name|now
parameter_list|)
block|{
if|if
condition|(
name|display
operator|->
name|update_areas
condition|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|display
operator|->
name|update_areas
init|;
name|list
condition|;
name|list
operator|=
name|g_slist_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpArea
modifier|*
name|area
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
operator|(
name|area
operator|->
name|x1
operator|!=
name|area
operator|->
name|x2
operator|)
operator|&&
operator|(
name|area
operator|->
name|y1
operator|!=
name|area
operator|->
name|y2
operator|)
condition|)
block|{
name|gimp_display_paint_area
argument_list|(
name|display
argument_list|,
name|area
operator|->
name|x1
argument_list|,
name|area
operator|->
name|y1
argument_list|,
operator|(
name|area
operator|->
name|x2
operator|-
name|area
operator|->
name|x1
operator|)
argument_list|,
operator|(
name|area
operator|->
name|y2
operator|-
name|area
operator|->
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_area_list_free
argument_list|(
name|display
operator|->
name|update_areas
argument_list|)
expr_stmt|;
name|display
operator|->
name|update_areas
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_display_shell_flush
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
argument_list|,
name|now
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_paint_area (GimpDisplay * display,gint x,gint y,gint w,gint h)
name|gimp_display_paint_area
parameter_list|(
name|GimpDisplay
modifier|*
name|display
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|display
operator|->
name|shell
argument_list|)
decl_stmt|;
name|gint
name|image_width
init|=
name|gimp_image_get_width
argument_list|(
name|display
operator|->
name|image
argument_list|)
decl_stmt|;
name|gint
name|image_height
init|=
name|gimp_image_get_height
argument_list|(
name|display
operator|->
name|image
argument_list|)
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|,
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|gdouble
name|x1_f
decl_stmt|,
name|y1_f
decl_stmt|,
name|x2_f
decl_stmt|,
name|y2_f
decl_stmt|;
comment|/*  Bounds check  */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
name|y1
operator|=
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|x2
operator|=
name|CLAMP
argument_list|(
name|x
operator|+
name|w
argument_list|,
literal|0
argument_list|,
name|image_width
argument_list|)
expr_stmt|;
name|y2
operator|=
name|CLAMP
argument_list|(
name|y
operator|+
name|h
argument_list|,
literal|0
argument_list|,
name|image_height
argument_list|)
expr_stmt|;
name|x
operator|=
name|x1
expr_stmt|;
name|y
operator|=
name|y1
expr_stmt|;
name|w
operator|=
operator|(
name|x2
operator|-
name|x1
operator|)
expr_stmt|;
name|h
operator|=
operator|(
name|y2
operator|-
name|y1
operator|)
expr_stmt|;
comment|/*  display the area  */
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x1_f
argument_list|,
operator|&
name|y1_f
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy_f
argument_list|(
name|shell
argument_list|,
name|x
operator|+
name|w
argument_list|,
name|y
operator|+
name|h
argument_list|,
operator|&
name|x2_f
argument_list|,
operator|&
name|y2_f
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/*  make sure to expose a superset of the transformed sub-pixel expose    *  area, not a subset. bug #126942. --mitch    *    *  also acommodate for spill introduced by potential box filtering.    *  (bug #474509). --simon    */
name|x1
operator|=
name|floor
argument_list|(
name|x1_f
operator|-
literal|0.5
argument_list|)
expr_stmt|;
name|y1
operator|=
name|floor
argument_list|(
name|y1_f
operator|-
literal|0.5
argument_list|)
expr_stmt|;
name|x2
operator|=
name|ceil
argument_list|(
name|x2_f
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|y2
operator|=
name|ceil
argument_list|(
name|y2_f
operator|+
literal|0.5
argument_list|)
expr_stmt|;
name|gimp_display_shell_expose_area
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
name|x2
operator|-
name|x1
argument_list|,
name|y2
operator|-
name|y1
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

