begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__TOOLS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__TOOLS_TYPES_H__
define|#
directive|define
name|__TOOLS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_comment
comment|/*  tools  */
end_comment

begin_typedef
DECL|typedef|GimpTool
typedef|typedef
name|struct
name|_GimpTool
name|GimpTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPaintTool
typedef|typedef
name|struct
name|_GimpPaintTool
name|GimpPaintTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawTool
typedef|typedef
name|struct
name|_GimpDrawTool
name|GimpDrawTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPathTool
typedef|typedef
name|struct
name|_GimpPathTool
name|GimpPathTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTransformTool
typedef|typedef
name|struct
name|_GimpTransformTool
name|GimpTransformTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBezierSelectPoint
typedef|typedef
name|struct
name|_GimpBezierSelectPoint
name|GimpBezierSelectPoint
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBezierSelectTool
typedef|typedef
name|struct
name|_GimpBezierSelectTool
name|GimpBezierSelectTool
typedef|;
end_typedef

begin_comment
comment|/*  stuff  */
end_comment

begin_typedef
DECL|typedef|ToolOptions
typedef|typedef
name|struct
name|_ToolOptions
name|ToolOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|SelectionOptions
typedef|typedef
name|struct
name|_SelectionOptions
name|SelectionOptions
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|ToolOptionsResetFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|ToolOptionsResetFunc
function_decl|)
parameter_list|(
name|ToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_typedef

begin_comment
comment|/*  EEK  */
end_comment

begin_typedef
DECL|typedef|Tool
typedef|typedef
name|struct
name|_Tool
name|Tool
typedef|;
end_typedef

begin_comment
comment|/*  enums  */
end_comment

begin_comment
comment|/*  The possible states for tools  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28e4a7960103
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
comment|/*  Tool control actions  */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28e4a7960203
block|{
DECL|enumerator|PAUSE
name|PAUSE
block|,
DECL|enumerator|RESUME
name|RESUME
block|,
DECL|enumerator|HALT
name|HALT
block|,
DECL|enumerator|DESTROY
name|DESTROY
block|,
DECL|enumerator|RECREATE
name|RECREATE
DECL|typedef|ToolAction
block|}
name|ToolAction
typedef|;
end_typedef

begin_comment
comment|/* possible transform functions */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28e4a7960303
block|{
DECL|enumerator|TRANSFORM_CREATING
name|TRANSFORM_CREATING
block|,
DECL|enumerator|TRANSFORM_HANDLE_1
name|TRANSFORM_HANDLE_1
block|,
DECL|enumerator|TRANSFORM_HANDLE_2
name|TRANSFORM_HANDLE_2
block|,
DECL|enumerator|TRANSFORM_HANDLE_3
name|TRANSFORM_HANDLE_3
block|,
DECL|enumerator|TRANSFORM_HANDLE_4
name|TRANSFORM_HANDLE_4
block|,
DECL|enumerator|TRANSFORM_HANDLE_CENTER
name|TRANSFORM_HANDLE_CENTER
DECL|typedef|TransformAction
block|}
name|TransformAction
typedef|;
end_typedef

begin_comment
comment|/* the different states that the transformation function can be called with */
end_comment

begin_typedef
typedef|typedef
enum|enum
comment|/*< skip>*/
DECL|enum|__anon28e4a7960403
block|{
DECL|enumerator|TRANSFORM_INIT
name|TRANSFORM_INIT
block|,
DECL|enumerator|TRANSFORM_MOTION
name|TRANSFORM_MOTION
block|,
DECL|enumerator|TRANSFORM_RECALC
name|TRANSFORM_RECALC
block|,
DECL|enumerator|TRANSFORM_FINISH
name|TRANSFORM_FINISH
DECL|typedef|TransformState
block|}
name|TransformState
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __TOOLS_TYPES_H__ */
end_comment

end_unit

