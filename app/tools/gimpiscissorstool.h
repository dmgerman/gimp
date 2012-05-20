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
name|__GIMP_ISCISSORS_TOOL_H__
end_ifndef

begin_define
define|#
directive|define
name|__GIMP_ISCISSORS_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_comment
comment|/*  The possible states...  */
end_comment

begin_comment
unit|typedef enum {   NO_ACTION,   SEED_PLACEMENT,   SEED_ADJUSTMENT,   WAITING } IscissorsState;
comment|/*  For oper_update& cursor_update  */
end_comment

begin_define
unit|typedef enum {   ISCISSORS_OP_NONE,   ISCISSORS_OP_SELECT,   ISCISSORS_OP_MOVE_POINT,   ISCISSORS_OP_ADD_POINT,   ISCISSORS_OP_CONNECT,   ISCISSORS_OP_IMPOSSIBLE } IscissorsOps;  typedef struct _ICurve ICurve;
define|#
directive|define
name|GIMP_TYPE_ISCISSORS_TOOL
value|(gimp_iscissors_tool_get_type ())
end_define

begin_define
define|#
directive|define
name|GIMP_ISCISSORS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsTool))
end_define

begin_define
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsToolClass))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_ISCISSORS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ISCISSORS_TOOL))
end_define

begin_define
define|#
directive|define
name|GIMP_IS_ISCISSORS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ISCISSORS_TOOL))
end_define

begin_define
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsToolClass))
end_define

begin_define
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_ISCISSORS_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_comment
unit|typedef struct _GimpIscissorsTool      GimpIscissorsTool; typedef struct _GimpIscissorsToolClass GimpIscissorsToolClass;  struct _GimpIscissorsTool {   GimpSelectionTool  parent_instance;    IscissorsOps    op;    gint            x, y;
comment|/*  upper left hand coordinate            */
end_comment

begin_comment
unit|gint            ix, iy;
comment|/*  initial coordinates                   */
end_comment

begin_comment
unit|gint            nx, ny;
comment|/*  new coordinates                       */
end_comment

begin_comment
unit|GimpTempBuf    *dp_buf;
comment|/*  dynamic programming buffer            */
end_comment

begin_comment
unit|ICurve         *livewire;
comment|/*  livewire boundary curve               */
end_comment

begin_comment
unit|ICurve         *curve1;
comment|/*  1st curve connected to current point  */
end_comment

begin_comment
unit|ICurve         *curve2;
comment|/*  2nd curve connected to current point  */
end_comment

begin_comment
unit|GQueue         *curves;
comment|/*  the list of curves                    */
end_comment

begin_comment
unit|gboolean        first_point;
comment|/*  is this the first point?              */
end_comment

begin_comment
unit|gboolean        connected;
comment|/*  is the region closed?                 */
end_comment

begin_comment
unit|IscissorsState  state;
comment|/*  state of iscissors                    */
end_comment

begin_comment
comment|/* XXX might be useful */
end_comment

begin_comment
unit|GimpChannel    *mask;
comment|/*  selection mask                        */
end_comment

begin_comment
unit|TileManager    *gradient_map;
comment|/*  lazily filled gradient map            */
end_comment

begin_endif
unit|};  struct _GimpIscissorsToolClass {   GimpSelectionToolClass parent_class; };   void    gimp_iscissors_tool_register (GimpToolRegisterCallback  callback,                                       gpointer                  data);  GType   gimp_iscissors_tool_get_type (void) G_GNUC_CONST;
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ISCISSORS_TOOL_H__  */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

