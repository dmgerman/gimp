begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_H__
define|#
directive|define
name|__GIMP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RECT_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_RECT_SELECT_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_ISCISSORS_TOOL
define|#
directive|define
name|GIMP_TYPE_ISCISSORS_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_ELLIPSE_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_ELLIPSE_SELECT_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_FUZZY_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_FUZZY_SELECT_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_BY_COLOR_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_BY_COLOR_SELECT_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_BUCKET_FILL_TOOL
define|#
directive|define
name|GIMP_TYPE_BUCKET_FILL_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_BLEND_TOOL
define|#
directive|define
name|GIMP_TYPE_BLEND_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_PENCIL_TOOL
define|#
directive|define
name|GIMP_TYPE_PENCIL_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_ERASER_TOOL
define|#
directive|define
name|GIMP_TYPE_ERASER_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_AIRBRUSH_TOOL
define|#
directive|define
name|GIMP_TYPE_AIRBRUSH_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_CLONE_TOOL
define|#
directive|define
name|GIMP_TYPE_CLONE_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_CONVOLVE_TOOL
define|#
directive|define
name|GIMP_TYPE_CONVOLVE_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_DODGEBURN_TOOL
define|#
directive|define
name|GIMP_TYPE_DODGEBURN_TOOL
value|GTK_TYPE_NONE
end_define

begin_define
DECL|macro|GIMP_TYPE_SMUDGE_TOOL
define|#
directive|define
name|GIMP_TYPE_SMUDGE_TOOL
value|GTK_TYPE_NONE
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

begin_typedef
DECL|typedef|GimpToolClass
typedef|typedef
name|struct
name|_GimpToolClass
name|GimpToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTool
struct|struct
name|_GimpTool
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
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
DECL|member|tool_cursor
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
DECL|member|toggle_cursor
name|GimpToolCursorType
name|toggle_cursor
decl_stmt|;
comment|/* one of these or both will go 				      * away once all cursor_update 				      * functions are properly 				      * virtualized 				      */
DECL|member|toggled
name|gboolean
name|toggled
decl_stmt|;
comment|/*  Bad hack to let the paint_core show the 			       *  right toggle cursors 			       */
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
comment|/* FIXME: most of this stuff must go away */
DECL|member|pdb_string
name|gchar
modifier|*
name|pdb_string
decl_stmt|;
DECL|member|initialize
name|void
function_decl|(
modifier|*
name|initialize
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
DECL|member|control
name|void
function_decl|(
modifier|*
name|control
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
DECL|member|button_press
name|void
function_decl|(
modifier|*
name|button_press
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
DECL|member|button_release
name|void
function_decl|(
modifier|*
name|button_release
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
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
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
DECL|member|arrow_key
name|void
function_decl|(
modifier|*
name|arrow_key
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
DECL|member|modifier_key
name|void
function_decl|(
modifier|*
name|modifier_key
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
DECL|member|cursor_update
name|void
function_decl|(
modifier|*
name|cursor_update
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
DECL|member|oper_update
name|void
function_decl|(
modifier|*
name|oper_update
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
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_tool_get_type
parameter_list|(
name|void
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
parameter_list|,
name|GDisplay
modifier|*
name|gdisplay
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
name|gimp_tool_button_press
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_button_release
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_motion
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_arrow_key
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_modifier_key
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_cursor_update
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
end_function_decl

begin_function_decl
name|void
name|gimp_tool_oper_update
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
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tool_get_PDB_string
parameter_list|(
name|GimpTool
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
comment|/*  __GIMP_TOOL_H__  */
end_comment

end_unit

