begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2002 Spencer Kimball, Peter Mattis and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_CONTROL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_CONTROL_H__
define|#
directive|define
name|__GIMP_TOOL_CONTROL_H__
end_define

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_CONTROL
define|#
directive|define
name|GIMP_TYPE_TOOL_CONTROL
value|(gimp_tool_control_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL (obj)
define|#
directive|define
name|GIMP_TOOL_CONTROL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_CONTROL, GimpToolControl))
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_CONTROL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_CONTROL, GimpToolControlClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CONTROL (obj)
define|#
directive|define
name|GIMP_IS_TOOL_CONTROL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_CONTROL))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_CONTROL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_CONTROL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_CONTROL))
end_define

begin_define
DECL|macro|GIMP_TOOL_CONTROL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_CONTROL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_CONTROL, GimpToolControlClass))
end_define

begin_typedef
DECL|typedef|GimpToolControlClass
typedef|typedef
name|struct
name|_GimpToolControlClass
name|GimpToolControlClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolControlClass
struct|struct
name|_GimpToolControlClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpToolControl
struct|struct
name|_GimpToolControl
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|state
name|GimpToolState
name|state
decl_stmt|;
comment|/*  state of tool activity                     */
DECL|member|paused_count
name|gint
name|paused_count
decl_stmt|;
comment|/*  paused control count                       */
DECL|member|scroll_lock
name|gboolean
name|scroll_lock
decl_stmt|;
comment|/*  allow scrolling or not               */
DECL|member|auto_snap_to
name|gboolean
name|auto_snap_to
decl_stmt|;
comment|/*  snap to guides automatically         */
DECL|member|preserve
name|gboolean
name|preserve
decl_stmt|;
comment|/*  Preserve this tool across drawable   *                                       *  changes                              */
DECL|member|handle_empty_image
name|gboolean
name|handle_empty_image
decl_stmt|;
comment|/*  invoke the tool on images without    *                                       *  active drawable                      */
DECL|member|perfectmouse
name|gboolean
name|perfectmouse
decl_stmt|;
comment|/*  tool is affected by gimprc's         *                                       *  "prefectmouse" setting               */
DECL|member|cursor
name|GdkCursorType
name|cursor
decl_stmt|;
DECL|member|tool_cursor
name|GimpToolCursorType
name|tool_cursor
decl_stmt|;
DECL|member|cursor_modifier
name|GimpCursorModifier
name|cursor_modifier
decl_stmt|;
DECL|member|toggle_cursor
name|GdkCursorType
name|toggle_cursor
decl_stmt|;
DECL|member|toggle_tool_cursor
name|GimpToolCursorType
name|toggle_tool_cursor
decl_stmt|;
DECL|member|toggle_cursor_modifier
name|GimpCursorModifier
name|toggle_cursor_modifier
decl_stmt|;
DECL|member|toggled
name|gboolean
name|toggled
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_CONTROL_H__ */
end_comment

end_unit

