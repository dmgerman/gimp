begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FOREGROUND_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FOREGROUND_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_FOREGROUND_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpfreeselecttool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
comment|/*< pdb-skip, skip>*/
DECL|enum|__anon2898ff620103
block|{
DECL|enumerator|SIOX_REFINEMENT_NO_CHANGE
name|SIOX_REFINEMENT_NO_CHANGE
init|=
literal|0
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_FOREGROUND
name|SIOX_REFINEMENT_ADD_FOREGROUND
init|=
operator|(
literal|1
operator|<<
literal|0
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_ADD_BACKGROUND
name|SIOX_REFINEMENT_ADD_BACKGROUND
init|=
operator|(
literal|1
operator|<<
literal|1
operator|)
block|,
DECL|enumerator|SIOX_REFINEMENT_RECALCULATE
name|SIOX_REFINEMENT_RECALCULATE
init|=
literal|0xFF
DECL|typedef|SioxRefinementType
block|}
name|SioxRefinementType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FOREGROUND_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_FOREGROUND_SELECT_TOOL
value|(gimp_foreground_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_FOREGROUND_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectTool))
end_define

begin_define
DECL|macro|GIMP_FOREGROUND_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_FOREGROUND_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_FOREGROUND_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_FOREGROUND_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FOREGROUND_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FOREGROUND_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_FOREGROUND_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FOREGROUND_SELECT_TOOL, GimpForegroundSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_FOREGROUND_SELECT_TOOL_GET_OPTIONS (t)
define|#
directive|define
name|GIMP_FOREGROUND_SELECT_TOOL_GET_OPTIONS
parameter_list|(
name|t
parameter_list|)
value|(GIMP_FOREGROUND_SELECT_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))
end_define

begin_typedef
DECL|typedef|GimpForegroundSelectTool
typedef|typedef
name|struct
name|_GimpForegroundSelectTool
name|GimpForegroundSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpForegroundSelectToolClass
typedef|typedef
name|struct
name|_GimpForegroundSelectToolClass
name|GimpForegroundSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpForegroundSelectTool
struct|struct
name|_GimpForegroundSelectTool
block|{
DECL|member|parent_instance
name|GimpFreeSelectTool
name|parent_instance
decl_stmt|;
DECL|member|last_coords
name|GimpCoords
name|last_coords
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
DECL|member|stroke
name|GArray
modifier|*
name|stroke
decl_stmt|;
DECL|member|strokes
name|GList
modifier|*
name|strokes
decl_stmt|;
DECL|member|mask
name|GimpChannel
modifier|*
name|mask
decl_stmt|;
if|#
directive|if
literal|0
block|SioxState          *state;
endif|#
directive|endif
DECL|member|refinement
name|SioxRefinementType
name|refinement
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpForegroundSelectToolClass
struct|struct
name|_GimpForegroundSelectToolClass
block|{
DECL|member|parent_class
name|GimpFreeSelectToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_foreground_select_tool_register
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
name|gimp_foreground_select_tool_get_type
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
comment|/*  __GIMP_FOREGROUND_SELECT_TOOL_H__  */
end_comment

end_unit

