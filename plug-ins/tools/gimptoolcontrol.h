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
file|"libgimptool/gimptooltypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpobject.h"
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
if|#
directive|if
literal|0
comment|/* eventually, we might want to cache this stuff on the plug-in side */
block|GimpToolState  state;
comment|/*  state of tool activity                     */
block|gint           paused_count;
comment|/*  paused control count                       */
block|gboolean       scroll_lock;
comment|/*  allow scrolling or not               */
block|gboolean       auto_snap_to;
comment|/*  snap to guides automatically         */
block|gboolean       preserve;
comment|/*  Preserve this tool across drawable   *                                       *  changes                              */
block|gboolean       handle_empty_image;
comment|/*  invoke the tool on images without    *                                       *  active drawable                      */
block|gboolean       perfectmouse;
comment|/*  tool is affected by gimprc's         *                                       *  "prefectmouse" setting               */
block|GdkCursorType      cursor;   GimpToolCursorType tool_cursor;   GimpCursorModifier cursor_modifier;    GdkCursorType      toggle_cursor;   GimpToolCursorType toggle_tool_cursor;   GimpCursorModifier toggle_cursor_modifier;    gboolean           toggled;
endif|#
directive|endif
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

