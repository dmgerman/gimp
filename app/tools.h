begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_H__
define|#
directive|define
name|__TOOLS_H__
end_define

begin_include
include|#
directive|include
file|"layerF.h"
end_include

begin_include
include|#
directive|include
file|"gdisplayF.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"toolsF.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_comment
comment|/*  The possible states for tools  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27d7c1250103
block|{
DECL|enumerator|INACTIVE
name|INACTIVE
block|,
DECL|enumerator|ACTIVE
name|ACTIVE
block|,
DECL|enumerator|PAUSED
name|PAUSED
DECL|typedef|ToolState
block|}
name|ToolState
typedef|;
end_typedef

begin_comment
comment|/*  The possibilities for where the cursor lies  */
end_comment

begin_define
DECL|macro|ACTIVE_LAYER
define|#
directive|define
name|ACTIVE_LAYER
value|(1<< 0)
end_define

begin_define
DECL|macro|SELECTION
define|#
directive|define
name|SELECTION
value|(1<< 1)
end_define

begin_define
DECL|macro|NON_ACTIVE_LAYER
define|#
directive|define
name|NON_ACTIVE_LAYER
value|(1<< 2)
end_define

begin_comment
comment|/*  The types of tools...  */
end_comment

begin_struct
DECL|struct|_Tool
struct|struct
name|_Tool
block|{
comment|/*  Data  */
DECL|member|type
name|ToolType
name|type
decl_stmt|;
comment|/*  Tool type                                   */
DECL|member|ID
name|gint
name|ID
decl_stmt|;
comment|/*  unique tool ID                              */
DECL|member|state
name|ToolState
name|state
decl_stmt|;
comment|/*  state of tool activity                      */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  paused control count                        */
DECL|member|scroll_lock
name|gboolean
name|scroll_lock
decl_stmt|;
comment|/*  allow scrolling or not                      */
DECL|member|auto_snap_to
name|gboolean
name|auto_snap_to
decl_stmt|;
comment|/*  snap to guides automatically                */
DECL|member|preserve
name|gboolean
name|preserve
decl_stmt|;
comment|/*  Preserve this tool across drawable changes  */
DECL|member|gdisp_ptr
name|void
modifier|*
name|gdisp_ptr
decl_stmt|;
comment|/*  pointer to currently active gdisp           */
DECL|member|drawable
name|void
modifier|*
name|drawable
decl_stmt|;
comment|/*  pointer to the tool's current drawable      */
DECL|member|private
name|void
modifier|*
name|private
decl_stmt|;
comment|/*  Tool-specific information                   */
comment|/*  Action functions  */
DECL|member|button_press_func
name|ButtonPressFunc
name|button_press_func
decl_stmt|;
DECL|member|button_release_func
name|ButtonReleaseFunc
name|button_release_func
decl_stmt|;
DECL|member|motion_func
name|MotionFunc
name|motion_func
decl_stmt|;
DECL|member|arrow_keys_func
name|ArrowKeysFunc
name|arrow_keys_func
decl_stmt|;
DECL|member|modifier_key_func
name|ModifierKeyFunc
name|modifier_key_func
decl_stmt|;
DECL|member|cursor_update_func
name|CursorUpdateFunc
name|cursor_update_func
decl_stmt|;
DECL|member|control_func
name|ToolCtlFunc
name|control_func
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_ToolInfo
struct|struct
name|_ToolInfo
block|{
DECL|member|tool_options
name|ToolOptions
modifier|*
name|tool_options
decl_stmt|;
DECL|member|tool_name
name|gchar
modifier|*
name|tool_name
decl_stmt|;
DECL|member|toolbar_position
name|gint
name|toolbar_position
decl_stmt|;
DECL|member|menu_path
name|gchar
modifier|*
name|menu_path
decl_stmt|;
DECL|member|menu_accel
name|gchar
modifier|*
name|menu_accel
decl_stmt|;
DECL|member|icon_data
name|gchar
modifier|*
modifier|*
name|icon_data
decl_stmt|;
DECL|member|tool_desc
name|gchar
modifier|*
name|tool_desc
decl_stmt|;
DECL|member|private_tip
name|gchar
modifier|*
name|private_tip
decl_stmt|;
DECL|member|tool_id
name|ToolType
name|tool_id
decl_stmt|;
DECL|member|new_func
name|ToolInfoNewFunc
name|new_func
decl_stmt|;
DECL|member|free_func
name|ToolInfoFreeFunc
name|free_func
decl_stmt|;
DECL|member|init_func
name|ToolInfoInitFunc
name|init_func
decl_stmt|;
DECL|member|tool_widget
name|GtkWidget
modifier|*
name|tool_widget
decl_stmt|;
DECL|member|tool_context
name|GimpContext
modifier|*
name|tool_context
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Global Data Structures  */
end_comment

begin_decl_stmt
specifier|extern
name|Tool
modifier|*
name|active_tool
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ToolInfo
name|tool_info
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|gint
name|num_tools
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  Function declarations  */
end_comment

begin_function_decl
name|Tool
modifier|*
name|tools_new_tool
parameter_list|(
name|ToolType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_select
parameter_list|(
name|ToolType
name|tool_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_initialize
parameter_list|(
name|ToolType
name|tool_type
parameter_list|,
name|GDisplay
modifier|*
name|gdisplay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|active_tool_control
parameter_list|(
name|ToolAction
name|action
parameter_list|,
name|void
modifier|*
name|gdisp_ptr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_help_func
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tools_register
parameter_list|(
name|ToolType
name|tool_type
parameter_list|,
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_options_dialog_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_options_dialog_show
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|tool_options_dialog_free
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guchar
modifier|*
name|tool_active_PDB_string
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TOOLS_H__  */
end_comment

end_unit

