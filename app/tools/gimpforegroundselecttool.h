begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FOREGROUND_SELECT_TOOL_H__
end_ifndef

begin_define
define|#
directive|define
name|__GIMP_FOREGROUND_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_define
define|#
directive|define
name|GIMP_TYPE_FOREGROUND_SELECT_TOOL
value|(gimp_foreground_select_tool_get_type ())
end_define

begin_define
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectTool))
end_define

begin_define
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectToolClass))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_FOREGROUND_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_FOREGROUND_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FOREGROUND_SELECT_TOOL))
end_define

begin_define
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectToolClass))
end_define

begin_define
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_FOREGROUND_SELECT_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_endif
unit|typedef struct _GimpForegroundSelectTool      GimpForegroundSelectTool; typedef struct _GimpForegroundSelectToolClass GimpForegroundSelectToolClass;  struct _GimpForegroundSelectTool {   GimpFreeSelectTool  parent_instance;    GimpCoords          last_coords;   guint               idle_id;   GArray             *stroke;   GList              *strokes;   GimpChannel        *mask;   SioxState          *state;   SioxRefinementType  refinement; };  struct _GimpForegroundSelectToolClass {   GimpFreeSelectToolClass  parent_class; };   void    gimp_foreground_select_tool_register (GimpToolRegisterCallback  callback,                                               gpointer                  data);  GType   gimp_foreground_select_tool_get_type (void) G_GNUC_CONST;
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_FOREGROUND_SELECT_TOOL_H__  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

