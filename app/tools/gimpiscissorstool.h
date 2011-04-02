begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ISCISSORS_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ISCISSORS_TOOL_H__
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

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2877bfaf0103
block|{
DECL|enumerator|NO_ACTION
name|NO_ACTION
block|,
DECL|enumerator|SEED_PLACEMENT
name|SEED_PLACEMENT
block|,
DECL|enumerator|SEED_ADJUSTMENT
name|SEED_ADJUSTMENT
block|,
DECL|enumerator|WAITING
name|WAITING
DECL|typedef|IscissorsState
block|}
name|IscissorsState
typedef|;
end_typedef

begin_comment
comment|/*  For oper_update& cursor_update  */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2877bfaf0203
block|{
DECL|enumerator|ISCISSORS_OP_NONE
name|ISCISSORS_OP_NONE
block|,
DECL|enumerator|ISCISSORS_OP_SELECT
name|ISCISSORS_OP_SELECT
block|,
DECL|enumerator|ISCISSORS_OP_MOVE_POINT
name|ISCISSORS_OP_MOVE_POINT
block|,
DECL|enumerator|ISCISSORS_OP_ADD_POINT
name|ISCISSORS_OP_ADD_POINT
block|,
DECL|enumerator|ISCISSORS_OP_CONNECT
name|ISCISSORS_OP_CONNECT
block|,
DECL|enumerator|ISCISSORS_OP_IMPOSSIBLE
name|ISCISSORS_OP_IMPOSSIBLE
DECL|typedef|IscissorsOps
block|}
name|IscissorsOps
typedef|;
end_typedef

begin_typedef
DECL|typedef|ICurve
typedef|typedef
name|struct
name|_ICurve
name|ICurve
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_ISCISSORS_TOOL
define|#
directive|define
name|GIMP_TYPE_ISCISSORS_TOOL
value|(gimp_iscissors_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_ISCISSORS_TOOL (obj)
define|#
directive|define
name|GIMP_ISCISSORS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsTool))
end_define

begin_define
DECL|macro|GIMP_ISCISSORS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_ISCISSORS_TOOL (obj)
define|#
directive|define
name|GIMP_IS_ISCISSORS_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ISCISSORS_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_ISCISSORS_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ISCISSORS_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ISCISSORS_TOOL))
end_define

begin_define
DECL|macro|GIMP_ISCISSORS_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ISCISSORS_TOOL, GimpIscissorsToolClass))
end_define

begin_define
DECL|macro|GIMP_ISCISSORS_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_ISCISSORS_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_ISCISSORS_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpIscissorsTool
typedef|typedef
name|struct
name|_GimpIscissorsTool
name|GimpIscissorsTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpIscissorsToolClass
typedef|typedef
name|struct
name|_GimpIscissorsToolClass
name|GimpIscissorsToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIscissorsTool
struct|struct
name|_GimpIscissorsTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|op
name|IscissorsOps
name|op
decl_stmt|;
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left hand coordinate            */
DECL|member|ix
DECL|member|iy
name|gint
name|ix
decl_stmt|,
name|iy
decl_stmt|;
comment|/*  initial coordinates                   */
DECL|member|nx
DECL|member|ny
name|gint
name|nx
decl_stmt|,
name|ny
decl_stmt|;
comment|/*  new coordinates                       */
DECL|member|dp_buf
name|TempBuf
modifier|*
name|dp_buf
decl_stmt|;
comment|/*  dynamic programming buffer            */
DECL|member|livewire
name|ICurve
modifier|*
name|livewire
decl_stmt|;
comment|/*  livewire boundary curve               */
DECL|member|curve1
name|ICurve
modifier|*
name|curve1
decl_stmt|;
comment|/*  1st curve connected to current point  */
DECL|member|curve2
name|ICurve
modifier|*
name|curve2
decl_stmt|;
comment|/*  2nd curve connected to current point  */
DECL|member|curves
name|GQueue
modifier|*
name|curves
decl_stmt|;
comment|/*  the list of curves                    */
DECL|member|first_point
name|gboolean
name|first_point
decl_stmt|;
comment|/*  is this the first point?              */
DECL|member|connected
name|gboolean
name|connected
decl_stmt|;
comment|/*  is the region closed?                 */
DECL|member|state
name|IscissorsState
name|state
decl_stmt|;
comment|/*  state of iscissors                    */
comment|/* XXX might be useful */
DECL|member|mask
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
comment|/*  selection mask                        */
DECL|member|gradient_map
name|TileManager
modifier|*
name|gradient_map
decl_stmt|;
comment|/*  lazily filled gradient map            */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpIscissorsToolClass
struct|struct
name|_GimpIscissorsToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_iscissors_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_iscissors_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_ISCISSORS_TOOL_H__  */
end_comment

end_unit

