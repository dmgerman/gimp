begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SMUDGE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SMUDGE_TOOL_H__
define|#
directive|define
name|__GIMP_SMUDGE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimppainttool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bdf38aa0103
block|{
DECL|enumerator|SMUDGE_TYPE_SMUDGE
name|SMUDGE_TYPE_SMUDGE
block|,
DECL|enumerator|SMUDGE_TYPE_STREAK
name|SMUDGE_TYPE_STREAK
DECL|typedef|SmudgeType
block|}
name|SmudgeType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bdf38aa0203
block|{
DECL|enumerator|SMUDGE_MODE_HIGHLIGHTS
name|SMUDGE_MODE_HIGHLIGHTS
block|,
DECL|enumerator|SMUDGE_MODE_MIDTONES
name|SMUDGE_MODE_MIDTONES
block|,
DECL|enumerator|SMUDGE_MODE_SHADOWS
name|SMUDGE_MODE_SHADOWS
DECL|typedef|SmudgeMode
block|}
name|SmudgeMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_SMUDGE_TOOL
define|#
directive|define
name|GIMP_TYPE_SMUDGE_TOOL
value|(gimp_smudge_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_SMUDGE_TOOL (obj)
define|#
directive|define
name|GIMP_SMUDGE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SMUDGE_TOOL, GimpSmudgeTool))
end_define

begin_define
DECL|macro|GIMP_IS_SMUDGE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_SMUDGE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SMUDGE_TOOL))
end_define

begin_define
DECL|macro|GIMP_SMUDGE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_SMUDGE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SMUDGE_TOOL, GimpSmudgeToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_SMUDGE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SMUDGE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SMUDGE_TOOL))
end_define

begin_typedef
DECL|typedef|GimpSmudgeTool
typedef|typedef
name|struct
name|_GimpSmudgeTool
name|GimpSmudgeTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSmudgeToolClass
typedef|typedef
name|struct
name|_GimpSmudgeToolClass
name|GimpSmudgeToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSmudgeTool
struct|struct
name|_GimpSmudgeTool
block|{
DECL|member|parent_instance
name|GimpPaintTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSmudgeToolClass
struct|struct
name|_GimpSmudgeToolClass
block|{
DECL|member|parent_class
name|GimpPaintToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_smudge_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_smudge_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* FIXME: this antique code doesn't follow the coding style */
end_comment

begin_function_decl
name|gboolean
name|gimp_smudge_tool_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|rate
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_smudge_tool_non_gui_default
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_SMUDGE_TOOL_H__  */
end_comment

end_unit

