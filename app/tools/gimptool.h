begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOL_H__
end_ifndef

begin_define
DECL|macro|__TOOL_H__
define|#
directive|define
name|__TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL
define|#
directive|define
name|GIMP_TYPE_TOOL
value|(gimp_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL (obj)
define|#
directive|define
name|GIMP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_TOOL, GimpTool))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL (obj)
define|#
directive|define
name|GIMP_IS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_TOOL))
end_define

begin_define
DECL|macro|GIMP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL, GimpToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL))
end_define

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

begin_typedef
DECL|typedef|GimpTool
typedef|typedef
name|struct
name|_GimpTool
name|GimpTool
typedef|;
end_typedef

begin_comment
comment|/*  Tool action function declarations  */
end_comment

begin_typedef
DECL|typedef|ButtonPressFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ButtonPressFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ButtonReleaseFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ButtonReleaseFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|MotionFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|MotionFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ArrowKeysFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ArrowKeysFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ModifierKeyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ModifierKeyFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|CursorUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|CursorUpdateFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|OperUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|OperUpdateFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ToolCtlFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolCtlFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpToolNewFunc
typedef|typedef
name|GimpTool
modifier|*
function_decl|(
modifier|*
name|GimpToolNewFunc
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpToolUnrefFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpToolUnrefFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpToolInitFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpToolInitFunc
function_decl|)
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpToolClass
typedef|typedef
name|struct
name|_GimpToolClass
name|GimpToolClass
typedef|;
end_typedef

begin_comment
comment|/*  The types of tools...  */
end_comment

begin_struct
DECL|struct|_GimpTool
struct|struct
name|_GimpTool
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
comment|/*  Data  */
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
DECL|member|gdisp
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
comment|/*  pointer to currently active gdisp           */
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
comment|/*  pointer to the tool's current drawable      */
DECL|member|toggled
name|gboolean
name|toggled
decl_stmt|;
comment|/*  Bad hack to let the paint_core show the 			       *  right toggle cursors 			       */
DECL|member|paintcore
name|PaintCore
modifier|*
name|paintcore
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolClass
struct|struct
name|_GimpToolClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
comment|/* stuff to be filled in by child classes */
DECL|member|tool_options
name|ToolOptions
modifier|*
name|tool_options
decl_stmt|;
DECL|member|pdb_string
name|gchar
modifier|*
name|pdb_string
decl_stmt|;
DECL|member|tool_name
name|gchar
modifier|*
name|tool_name
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
DECL|member|icon_pixmap
name|GdkPixmap
modifier|*
name|icon_pixmap
decl_stmt|;
DECL|member|icon_mask
name|GdkBitmap
modifier|*
name|icon_mask
decl_stmt|;
DECL|member|tool_desc
name|gchar
modifier|*
name|tool_desc
decl_stmt|;
DECL|member|help_data
specifier|const
name|gchar
modifier|*
name|help_data
decl_stmt|;
DECL|member|tool_id
name|ToolType
name|tool_id
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
DECL|member|tool_cursor
name|BitmapCursor
modifier|*
name|tool_cursor
decl_stmt|;
DECL|member|toggle_cursor
name|BitmapCursor
modifier|*
name|toggle_cursor
decl_stmt|;
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
DECL|member|oper_update_func
name|OperUpdateFunc
name|oper_update_func
decl_stmt|;
DECL|member|control_func
name|ToolCtlFunc
name|control_func
decl_stmt|;
comment|/* put lots of interesting signals here */
DECL|member|reserved1
name|ToolCtlFunc
name|reserved1
decl_stmt|;
DECL|member|reserved2
name|ToolCtlFunc
name|reserved2
decl_stmt|;
DECL|member|reserved3
name|ToolCtlFunc
name|reserved3
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  Function declarations  */
end_comment

begin_function_decl
name|GtkType
name|gimp_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTool
modifier|*
name|gimp_tool_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|ToolAction
name|action
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_old_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisplay
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_tool_get_help_data
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_help_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tool_show_options
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|tool_get_PDB_string
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  don't unref these pixmaps, they are static!  */
end_comment

begin_function_decl
name|GdkPixmap
modifier|*
name|gimp_tool_get_pixmap
parameter_list|(
name|GimpToolClass
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GdkBitmap
modifier|*
name|gimp_tool_get_mask
parameter_list|(
name|GimpToolClass
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __TOOL_H__  */
end_comment

end_unit

