begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-projection.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"libgimptool/gimptool.h"
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
file|"gimpdisplay-area.h"
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
file|"gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon28d16be80103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_IMAGE
name|PROP_IMAGE
block|}
enum|;
end_enum

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_display_class_init
parameter_list|(
name|GimpDisplayClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_init
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_finalize
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
name|void
name|gimp_display_flush_whenever
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|now
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_display_idlerender_init
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_idlerender_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_display_idle_render_next_area
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
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
name|gdisp
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

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpObjectClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_display_get_type (void)
name|gimp_display_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|display_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|display_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|display_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpDisplayClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_display_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDisplay
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_display_init
block|,       }
decl_stmt|;
name|display_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_OBJECT
argument_list|,
literal|"GimpDisplay"
argument_list|,
operator|&
name|display_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|display_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_class_init (GimpDisplayClass * klass)
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
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_display_finalize
expr_stmt|;
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
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_init (GimpDisplay * gdisp)
name|gimp_display_init
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|gdisp
operator|->
name|ID
operator|=
literal|0
expr_stmt|;
name|gdisp
operator|->
name|gimage
operator|=
name|NULL
expr_stmt|;
name|gdisp
operator|->
name|instance
operator|=
literal|0
expr_stmt|;
name|gdisp
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|gdisp
operator|->
name|draw_guides
operator|=
name|TRUE
expr_stmt|;
name|gdisp
operator|->
name|snap_to_guides
operator|=
name|TRUE
expr_stmt|;
name|gdisp
operator|->
name|update_areas
operator|=
name|NULL
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
literal|0
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_finalize (GObject * object)
name|gimp_display_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY
argument_list|(
name|object
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
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
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
name|gdisp
decl_stmt|;
name|gdisp
operator|=
name|GIMP_DISPLAY
argument_list|(
name|object
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_IMAGE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|gdisp
operator|->
name|gimage
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
name|GimpDisplay
modifier|*
DECL|function|gimp_display_new (GimpImage * gimage,guint scale,GimpMenuFactory * menu_factory,GimpItemFactory * popup_factory)
name|gimp_display_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|guint
name|scale
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|,
name|GimpItemFactory
modifier|*
name|popup_factory
parameter_list|)
block|{
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  If there isn't an interface, never create a gdisplay  */
if|if
condition|(
name|gimage
operator|->
name|gimp
operator|->
name|no_interface
condition|)
return|return
name|NULL
return|;
name|gdisp
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DISPLAY
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|ID
operator|=
name|gimage
operator|->
name|gimp
operator|->
name|next_display_ID
operator|++
expr_stmt|;
comment|/*  refs the image  */
name|gimp_display_connect
argument_list|(
name|gdisp
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
comment|/*  create the shell for the image  */
name|gdisp
operator|->
name|shell
operator|=
name|gimp_display_shell_new
argument_list|(
name|gdisp
argument_list|,
name|scale
argument_list|,
name|menu_factory
argument_list|,
name|popup_factory
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
return|return
name|gdisp
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_delete (GimpDisplay * gdisp)
name|gimp_display_delete
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
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
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* remove the display from the list */
name|gimp_container_remove
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|displays
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  stop any active tool  */
name|tool_manager_control_active
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|,
name|HALT
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|active_tool
operator|=
name|tool_manager_get_active
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
comment|/*  clear out the pointer to this gdisp from the active tool  */
if|if
condition|(
name|active_tool
operator|&&
name|active_tool
operator|->
name|gdisp
operator|==
name|gdisp
condition|)
block|{
name|active_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
name|active_tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
block|}
comment|/* If this gdisplay was idlerendering at the time when it was deleted,    * deactivate the idlerendering thread before deletion!    */
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
comment|/*  free the update area lists  */
name|gimp_display_area_list_free
argument_list|(
name|gdisp
operator|->
name|update_areas
argument_list|)
expr_stmt|;
name|gimp_display_area_list_free
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|shell
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
block|}
comment|/*  unrefs the gimage  */
name|gimp_display_disconnect
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_display_get_ID (GimpDisplay * gdisp)
name|gimp_display_get_ID
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
return|return
name|gdisp
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
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
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
name|gdisp
operator|=
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|ID
operator|==
name|ID
condition|)
return|return
name|gdisp
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_reconnect (GimpDisplay * gdisp,GimpImage * gimage)
name|gimp_display_reconnect
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
literal|0
expr_stmt|;
block|}
name|gimp_display_shell_disconnect
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_display_disconnect
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_display_connect
argument_list|(
name|gdisp
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|gimp_display_add_update_area
argument_list|(
name|gdisp
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
name|gimp_display_shell_reconnect
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_add_update_area (GimpDisplay * gdisp,gint x,gint y,gint w,gint h)
name|gimp_display_add_update_area
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
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
name|GimpArea
modifier|*
name|area
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
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
name|gdisp
operator|->
name|gimage
operator|->
name|width
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
name|y
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|height
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
name|gdisp
operator|->
name|gimage
operator|->
name|width
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
name|gdisp
operator|->
name|gimage
operator|->
name|height
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|update_areas
operator|=
name|gimp_display_area_list_process
argument_list|(
name|gdisp
operator|->
name|update_areas
argument_list|,
name|area
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_flush (GimpDisplay * gdisp)
name|gimp_display_flush
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Redraw on idle time */
name|gimp_display_flush_whenever
argument_list|(
name|gdisp
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_display_flush_now (GimpDisplay * gdisp)
name|gimp_display_flush_now
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
comment|/* Redraw NOW */
name|gimp_display_flush_whenever
argument_list|(
name|gdisp
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* Force all gdisplays to finish their idlerender projection */
end_comment

begin_function
name|void
DECL|function|gimp_display_finish_draw (GimpDisplay * gdisp)
name|gimp_display_finish_draw
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|gimp_display_idlerender_callback
argument_list|(
name|gdisp
argument_list|)
condition|)
empty_stmt|;
block|}
block|}
end_function

begin_comment
comment|/* utility function to check if the cursor is inside the active drawable */
end_comment

begin_function
name|gboolean
DECL|function|gimp_display_coords_in_active_drawable (GimpDisplay * gdisp,const GimpCoords * coords)
name|gimp_display_coords_in_active_drawable
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
block|{
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DISPLAY
argument_list|(
name|gdisp
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gdisp
operator|->
name|gimage
condition|)
return|return
name|FALSE
return|;
if|if
condition|(
operator|!
operator|(
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|x
operator|=
name|ROUND
argument_list|(
name|coords
operator|->
name|x
argument_list|)
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
operator|||
name|x
operator|>
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|FALSE
return|;
name|y
operator|=
name|ROUND
argument_list|(
name|coords
operator|->
name|y
argument_list|)
operator|-
name|y
expr_stmt|;
if|if
condition|(
name|y
operator|<
literal|0
operator|||
name|y
operator|>
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
condition|)
return|return
name|FALSE
return|;
return|return
name|TRUE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_display_flush_whenever (GimpDisplay * gdisp,gboolean now)
name|gimp_display_flush_whenever
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|gboolean
name|now
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/*  Flush the items in the displays and updates lists -    *  but only if gdisplay has been mapped and exposed    */
if|if
condition|(
operator|!
name|shell
operator|->
name|select
condition|)
block|{
name|g_warning
argument_list|(
literal|"gimp_display_flush_whenever(): called unrealized"
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  First the updates...  */
if|if
condition|(
name|now
condition|)
block|{
comment|/* Synchronous */
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpArea
modifier|*
name|area
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gdisp
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
comment|/*  Paint the area specified by the GimpArea  */
name|area
operator|=
operator|(
name|GimpArea
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
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
name|gdisp
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
block|}
else|else
block|{
comment|/* Asynchronous */
if|if
condition|(
name|gdisp
operator|->
name|update_areas
condition|)
name|gimp_display_idlerender_init
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
comment|/*  Free the update lists  */
name|gdisp
operator|->
name|update_areas
operator|=
name|gimp_display_area_list_free
argument_list|(
name|gdisp
operator|->
name|update_areas
argument_list|)
expr_stmt|;
comment|/*  Next the displays...  */
name|gimp_display_shell_flush
argument_list|(
name|shell
argument_list|)
expr_stmt|;
comment|/*  ensure the consistency of the menus  */
if|if
condition|(
operator|!
name|now
condition|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
operator|==
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
condition|)
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_idlerender_init (GimpDisplay * gdisp)
name|gimp_display_idlerender_init
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GimpArea
modifier|*
name|area
decl_stmt|,
modifier|*
name|new_area
decl_stmt|;
comment|/* We need to merge the IdleRender's and the GimpDisplay's update_areas list    * to keep track of which of the updates have been flushed and hence need    * to be drawn.     */
for|for
control|(
name|list
operator|=
name|gdisp
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
name|area
operator|=
operator|(
name|GimpArea
operator|*
operator|)
name|list
operator|->
name|data
expr_stmt|;
name|new_area
operator|=
name|g_new
argument_list|(
name|GimpArea
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|memcpy
argument_list|(
name|new_area
argument_list|,
name|area
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpArea
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|=
name|gimp_display_area_list_process
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
argument_list|,
name|new_area
argument_list|)
expr_stmt|;
block|}
comment|/* If an idlerender was already running, merge the remainder of its    * unrendered area with the update_areas list, and make it start work    * on the next unrendered area in the list.    */
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
condition|)
block|{
name|new_area
operator|=
name|gimp_area_new
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
argument_list|,
name|gdisp
operator|->
name|idle_render
operator|.
name|y
argument_list|,
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|width
argument_list|,
name|gdisp
operator|->
name|idle_render
operator|.
name|y
operator|+
operator|(
name|gdisp
operator|->
name|idle_render
operator|.
name|height
operator|-
operator|(
name|gdisp
operator|->
name|idle_render
operator|.
name|y
operator|-
name|gdisp
operator|->
name|idle_render
operator|.
name|basey
operator|)
operator|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|=
name|gimp_display_area_list_process
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
argument_list|,
name|new_area
argument_list|)
expr_stmt|;
name|gimp_display_idle_render_next_area
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"Wanted to start idlerender thread with no update_areas. (+memleak)"
argument_list|)
expr_stmt|;
return|return;
block|}
name|gimp_display_idle_render_next_area
argument_list|(
name|gdisp
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
name|g_idle_add_full
argument_list|(
name|G_PRIORITY_LOW
argument_list|,
name|gimp_display_idlerender_callback
argument_list|,
name|gdisp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/* Caller frees gdisp->update_areas */
block|}
end_function

begin_comment
comment|/* Unless specified otherwise, display re-rendering is organised by  * IdleRender, which amalgamates areas to be re-rendered and breaks  * them into bite-sized chunks which are chewed on in a low- priority  * idle thread.  This greatly improves responsiveness for many GIMP  * operations.  -- Adam  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_idlerender_callback (gpointer data)
name|gimp_display_idlerender_callback
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
specifier|const
name|gint
name|CHUNK_WIDTH
init|=
literal|256
decl_stmt|;
specifier|const
name|gint
name|CHUNK_HEIGHT
init|=
literal|128
decl_stmt|;
name|gint
name|workx
decl_stmt|,
name|worky
decl_stmt|,
name|workw
decl_stmt|,
name|workh
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
init|=
name|data
decl_stmt|;
name|workw
operator|=
name|CHUNK_WIDTH
expr_stmt|;
name|workh
operator|=
name|CHUNK_HEIGHT
expr_stmt|;
name|workx
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|x
expr_stmt|;
name|worky
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|y
expr_stmt|;
if|if
condition|(
name|workx
operator|+
name|workw
operator|>
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|width
condition|)
block|{
name|workw
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|width
operator|-
name|workx
expr_stmt|;
block|}
if|if
condition|(
name|worky
operator|+
name|workh
operator|>
name|gdisp
operator|->
name|idle_render
operator|.
name|basey
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|height
condition|)
block|{
name|workh
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|basey
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|height
operator|-
name|worky
expr_stmt|;
block|}
name|gimp_display_paint_area
argument_list|(
name|gdisp
argument_list|,
name|workx
argument_list|,
name|worky
argument_list|,
name|workw
argument_list|,
name|workh
argument_list|)
expr_stmt|;
name|gimp_display_shell_flush
argument_list|(
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|x
operator|+=
name|CHUNK_WIDTH
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|x
operator|>=
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|width
condition|)
block|{
name|gdisp
operator|->
name|idle_render
operator|.
name|x
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|y
operator|+=
name|CHUNK_HEIGHT
expr_stmt|;
if|if
condition|(
name|gdisp
operator|->
name|idle_render
operator|.
name|y
operator|>=
name|gdisp
operator|->
name|idle_render
operator|.
name|basey
operator|+
name|gdisp
operator|->
name|idle_render
operator|.
name|height
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_display_idle_render_next_area
argument_list|(
name|gdisp
argument_list|)
condition|)
block|{
comment|/* FINISHED */
name|gdisp
operator|->
name|idle_render
operator|.
name|idle_id
operator|=
literal|0
expr_stmt|;
return|return
name|FALSE
return|;
block|}
block|}
block|}
comment|/* Still work to do. */
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_display_idle_render_next_area (GimpDisplay * gdisp)
name|gimp_display_idle_render_next_area
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpArea
modifier|*
name|area
decl_stmt|;
if|if
condition|(
operator|!
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
condition|)
return|return
name|FALSE
return|;
name|area
operator|=
operator|(
name|GimpArea
operator|*
operator|)
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|->
name|data
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
operator|=
name|g_slist_remove
argument_list|(
name|gdisp
operator|->
name|idle_render
operator|.
name|update_areas
argument_list|,
name|area
argument_list|)
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|x
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|basex
operator|=
name|area
operator|->
name|x1
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|y
operator|=
name|gdisp
operator|->
name|idle_render
operator|.
name|basey
operator|=
name|area
operator|->
name|y1
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|width
operator|=
name|area
operator|->
name|x2
operator|-
name|area
operator|->
name|x1
expr_stmt|;
name|gdisp
operator|->
name|idle_render
operator|.
name|height
operator|=
name|area
operator|->
name|y2
operator|-
name|area
operator|->
name|y1
expr_stmt|;
name|g_free
argument_list|(
name|area
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_display_paint_area (GimpDisplay * gdisp,gint x,gint y,gint w,gint h)
name|gimp_display_paint_area
parameter_list|(
name|GimpDisplay
modifier|*
name|gdisp
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
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
comment|/*  Bounds check  */
name|x1
operator|=
name|CLAMP
argument_list|(
name|x
argument_list|,
literal|0
argument_list|,
name|gdisp
operator|->
name|gimage
operator|->
name|width
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
name|gdisp
operator|->
name|gimage
operator|->
name|height
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
name|gdisp
operator|->
name|gimage
operator|->
name|width
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
name|gdisp
operator|->
name|gimage
operator|->
name|height
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
comment|/*  calculate the extents of the update as limited by what's visible  */
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_untransform_xy
argument_list|(
name|shell
argument_list|,
name|shell
operator|->
name|disp_width
argument_list|,
name|shell
operator|->
name|disp_height
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_invalidate
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
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
comment|/*  display the area  */
name|gimp_display_shell_transform_xy
argument_list|(
name|shell
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_transform_xy
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
name|x2
argument_list|,
operator|&
name|y2
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_display_shell_add_expose_area
argument_list|(
name|shell
argument_list|,
name|x1
argument_list|,
name|y1
argument_list|,
operator|(
name|x2
operator|-
name|x1
operator|)
argument_list|,
operator|(
name|y2
operator|-
name|y1
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

