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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
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
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimptool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_typedef
DECL|typedef|GimpToolManager
typedef|typedef
name|struct
name|_GimpToolManager
name|GimpToolManager
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolManager
struct|struct
name|_GimpToolManager
block|{
DECL|member|active_tool
name|GimpTool
modifier|*
name|active_tool
decl_stmt|;
DECL|member|tool_stack
name|GSList
modifier|*
name|tool_stack
decl_stmt|;
DECL|member|image_clean_handler_id
name|GQuark
name|image_clean_handler_id
decl_stmt|;
DECL|member|image_dirty_handler_id
name|GQuark
name|image_dirty_handler_id
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|GimpToolManager
modifier|*
name|tool_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_manager_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolManager
modifier|*
name|tool_manager
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|tool_manager_image_clean_dirty
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|,
name|GimpToolManager
modifier|*
name|tool_manager
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|tool_manager_init (Gimp * gimp)
name|tool_manager_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|g_slice_new0
argument_list|(
name|GimpToolManager
argument_list|)
expr_stmt|;
name|tool_manager
operator|->
name|active_tool
operator|=
name|NULL
expr_stmt|;
name|tool_manager
operator|->
name|tool_stack
operator|=
name|NULL
expr_stmt|;
name|tool_manager
operator|->
name|image_clean_handler_id
operator|=
literal|0
expr_stmt|;
name|tool_manager
operator|->
name|image_dirty_handler_id
operator|=
literal|0
expr_stmt|;
name|tool_manager_set
argument_list|(
name|gimp
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
name|tool_manager
operator|->
name|image_clean_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"clean"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_manager_image_clean_dirty
argument_list|)
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
name|tool_manager
operator|->
name|image_dirty_handler_id
operator|=
name|gimp_container_add_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
literal|"dirty"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_manager_image_clean_dirty
argument_list|)
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
name|user_context
operator|=
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|user_context
argument_list|,
literal|"tool-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|tool_manager_tool_changed
argument_list|)
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_exit (Gimp * gimp)
name|tool_manager_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
name|tool_manager_set
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|tool_manager
operator|->
name|image_clean_handler_id
argument_list|)
expr_stmt|;
name|gimp_container_remove_handler
argument_list|(
name|gimp
operator|->
name|images
argument_list|,
name|tool_manager
operator|->
name|image_dirty_handler_id
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
name|g_object_unref
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpToolManager
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpTool
modifier|*
DECL|function|tool_manager_get_active (Gimp * gimp)
name|tool_manager_get_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
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
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|tool_manager
operator|->
name|active_tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_select_tool (Gimp * gimp,GimpTool * tool)
name|tool_manager_select_tool
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|GimpTool
modifier|*
name|active_tool
init|=
name|tool_manager
operator|->
name|active_tool
decl_stmt|;
name|GimpDisplay
modifier|*
name|display
decl_stmt|;
comment|/*  NULL image returns any display (if there is any)  */
name|display
operator|=
name|gimp_tool_has_image
argument_list|(
name|active_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|tool_manager_control_active
argument_list|(
name|gimp
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|tool_manager_focus_display_active
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|)
expr_stmt|;
block|}
name|tool_manager
operator|->
name|active_tool
operator|=
name|g_object_ref
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_push_tool (Gimp * gimp,GimpTool * tool)
name|tool_manager_push_tool
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|GimpDisplay
modifier|*
name|focus_display
init|=
name|NULL
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|focus_display
operator|=
name|tool_manager
operator|->
name|active_tool
operator|->
name|focus_display
expr_stmt|;
name|tool_manager
operator|->
name|tool_stack
operator|=
name|g_slist_prepend
argument_list|(
name|tool_manager
operator|->
name|tool_stack
argument_list|,
name|tool_manager
operator|->
name|active_tool
argument_list|)
expr_stmt|;
name|g_object_ref
argument_list|(
name|tool_manager
operator|->
name|tool_stack
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|tool_manager_select_tool
argument_list|(
name|gimp
argument_list|,
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|focus_display
condition|)
name|tool_manager_focus_display_active
argument_list|(
name|gimp
argument_list|,
name|focus_display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_pop_tool (Gimp * gimp)
name|tool_manager_pop_tool
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|tool_stack
condition|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|tool_manager
operator|->
name|tool_stack
operator|->
name|data
decl_stmt|;
name|GimpDisplay
modifier|*
name|focus_display
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
name|focus_display
operator|=
name|tool_manager
operator|->
name|active_tool
operator|->
name|focus_display
expr_stmt|;
name|tool_manager
operator|->
name|tool_stack
operator|=
name|g_slist_remove
argument_list|(
name|tool_manager
operator|->
name|tool_stack
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|tool_manager_select_tool
argument_list|(
name|gimp
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|focus_display
condition|)
name|tool_manager_focus_display_active
argument_list|(
name|gimp
argument_list|,
name|focus_display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|tool_manager_initialize_active (Gimp * gimp,GimpDisplay * display)
name|tool_manager_initialize_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
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
name|GIMP_IS_DISPLAY
argument_list|(
name|display
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|tool_manager
operator|->
name|active_tool
decl_stmt|;
if|if
condition|(
name|gimp_tool_initialize
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
condition|)
block|{
name|GimpImage
modifier|*
name|image
init|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
decl_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
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

begin_function
name|void
DECL|function|tool_manager_control_active (Gimp * gimp,GimpToolAction action,GimpDisplay * display)
name|tool_manager_control_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|tool_manager
operator|->
name|active_tool
decl_stmt|;
if|if
condition|(
name|display
operator|&&
name|gimp_tool_has_display
argument_list|(
name|tool
argument_list|,
name|display
argument_list|)
condition|)
block|{
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|action
operator|==
name|GIMP_TOOL_ACTION_HALT
condition|)
block|{
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_button_press_active (Gimp * gimp,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|tool_manager_button_press_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_button_press
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|press_type
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_button_release_active (Gimp * gimp,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|tool_manager_button_release_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_button_release
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_motion_active (Gimp * gimp,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|tool_manager_motion_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_motion
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|tool_manager_key_press_active (Gimp * gimp,GdkEventKey * kevent,GimpDisplay * display)
name|tool_manager_key_press_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
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
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
return|return
name|gimp_tool_key_press
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|kevent
argument_list|,
name|display
argument_list|)
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_focus_display_active (Gimp * gimp,GimpDisplay * display)
name|tool_manager_focus_display_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_set_focus_display
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_modifier_state_active (Gimp * gimp,GdkModifierType state,GimpDisplay * display)
name|tool_manager_modifier_state_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_set_modifier_state
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_active_modifier_state_active (Gimp * gimp,GdkModifierType state,GimpDisplay * display)
name|tool_manager_active_modifier_state_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_set_active_modifier_state
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_oper_update_active (Gimp * gimp,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|tool_manager_oper_update_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
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
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_oper_update
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|tool_manager_cursor_update_active (Gimp * gimp,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|tool_manager_cursor_update_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
name|gimp_tool_cursor_update
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|GimpUIManager
modifier|*
DECL|function|tool_manager_get_popup_active (Gimp * gimp,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display,const gchar ** ui_path)
name|tool_manager_get_popup_active
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|ui_path
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
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
name|tool_manager
operator|=
name|tool_manager_get
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
condition|)
block|{
return|return
name|gimp_tool_get_popup
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|,
name|ui_path
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_decl_stmt
DECL|variable|tool_manager_quark
specifier|static
name|GQuark
name|tool_manager_quark
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|GimpToolManager
modifier|*
DECL|function|tool_manager_get (Gimp * gimp)
name|tool_manager_get
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tool_manager_quark
condition|)
name|tool_manager_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-tool-manager"
argument_list|)
expr_stmt|;
return|return
name|g_object_get_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|tool_manager_quark
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_manager_set (Gimp * gimp,GimpToolManager * tool_manager)
name|tool_manager_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolManager
modifier|*
name|tool_manager
parameter_list|)
block|{
if|if
condition|(
operator|!
name|tool_manager_quark
condition|)
name|tool_manager_quark
operator|=
name|g_quark_from_static_string
argument_list|(
literal|"gimp-tool-manager"
argument_list|)
expr_stmt|;
name|g_object_set_qdata
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|tool_manager_quark
argument_list|,
name|tool_manager
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_manager_tool_changed (GimpContext * user_context,GimpToolInfo * tool_info,gpointer data)
name|tool_manager_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|user_context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpToolManager
modifier|*
name|tool_manager
init|=
name|data
decl_stmt|;
name|GimpTool
modifier|*
name|new_tool
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|tool_info
condition|)
return|return;
comment|/* FIXME: gimp_busy HACK */
if|if
condition|(
name|user_context
operator|->
name|gimp
operator|->
name|busy
condition|)
block|{
comment|/*  there may be contexts waiting for the user_context's "tool-changed"        *  signal, so stop emitting it.        */
name|g_signal_stop_emission_by_name
argument_list|(
name|user_context
argument_list|,
literal|"tool-changed"
argument_list|)
expr_stmt|;
if|if
condition|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|tool_manager
operator|->
name|active_tool
argument_list|)
operator|!=
name|tool_info
operator|->
name|tool_type
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|user_context
argument_list|,
name|tool_manager_tool_changed
argument_list|,
name|data
argument_list|)
expr_stmt|;
comment|/*  explicitly set the current tool  */
name|gimp_context_set_tool
argument_list|(
name|user_context
argument_list|,
name|tool_manager
operator|->
name|active_tool
operator|->
name|tool_info
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|user_context
argument_list|,
name|tool_manager_tool_changed
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
return|return;
block|}
if|if
condition|(
name|g_type_is_a
argument_list|(
name|tool_info
operator|->
name|tool_type
argument_list|,
name|GIMP_TYPE_TOOL
argument_list|)
condition|)
block|{
name|new_tool
operator|=
name|g_object_new
argument_list|(
name|tool_info
operator|->
name|tool_type
argument_list|,
literal|"tool-info"
argument_list|,
name|tool_info
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|g_warning
argument_list|(
literal|"%s: tool_info->tool_type is no GimpTool subclass"
argument_list|,
name|G_STRFUNC
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/*  disconnect the old tool's context  */
if|if
condition|(
name|tool_manager
operator|->
name|active_tool
operator|&&
name|tool_manager
operator|->
name|active_tool
operator|->
name|tool_info
operator|&&
name|tool_manager
operator|->
name|active_tool
operator|->
name|tool_info
operator|->
name|context_props
condition|)
block|{
name|GimpToolInfo
modifier|*
name|old_tool_info
init|=
name|tool_manager
operator|->
name|active_tool
operator|->
name|tool_info
decl_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|old_tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
comment|/*  connect the new tool's context  */
if|if
condition|(
name|tool_info
operator|->
name|context_props
condition|)
block|{
name|GimpCoreConfig
modifier|*
name|config
init|=
name|user_context
operator|->
name|gimp
operator|->
name|config
decl_stmt|;
name|GimpContextPropMask
name|global_props
init|=
literal|0
decl_stmt|;
comment|/*  FG and BG are always shared between all tools  */
name|global_props
operator||=
name|GIMP_CONTEXT_FOREGROUND_MASK
expr_stmt|;
name|global_props
operator||=
name|GIMP_CONTEXT_BACKGROUND_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_brush
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_BRUSH_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_pattern
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PATTERN_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_palette
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_PALETTE_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_gradient
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_GRADIENT_MASK
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|global_font
condition|)
name|global_props
operator||=
name|GIMP_CONTEXT_FONT_MASK
expr_stmt|;
name|gimp_context_copy_properties
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|user_context
argument_list|,
name|tool_info
operator|->
name|context_props
operator|&
operator|~
name|global_props
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|GIMP_CONTEXT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
name|user_context
argument_list|)
expr_stmt|;
block|}
name|tool_manager_select_tool
argument_list|(
name|user_context
operator|->
name|gimp
argument_list|,
name|new_tool
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|new_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|tool_manager_image_clean_dirty (GimpImage * image,GimpDirtyMask dirty_mask,GimpToolManager * tool_manager)
name|tool_manager_image_clean_dirty
parameter_list|(
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpDirtyMask
name|dirty_mask
parameter_list|,
name|GimpToolManager
modifier|*
name|tool_manager
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|tool_manager
operator|->
name|active_tool
decl_stmt|;
if|if
condition|(
name|tool
operator|&&
operator|!
name|gimp_tool_control_get_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|&&
operator|(
name|gimp_tool_control_get_dirty_mask
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|&
name|dirty_mask
operator|)
condition|)
block|{
name|GimpDisplay
modifier|*
name|display
init|=
name|gimp_tool_has_image
argument_list|(
name|tool
argument_list|,
name|image
argument_list|)
decl_stmt|;
if|if
condition|(
name|display
condition|)
name|tool_manager_control_active
argument_list|(
name|image
operator|->
name|gimp
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

