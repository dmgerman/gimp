begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpfuzzyselecttool.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_FUZZY_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_FUZZY_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_FUZZY_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpregionselecttool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_FUZZY_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_FUZZY_SELECT_TOOL
value|(gimp_fuzzy_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_FUZZY_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_FUZZY_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_FUZZY_SELECT_TOOL, GimpFuzzySelectTool))
end_define

begin_define
DECL|macro|GIMP_FUZZY_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_FUZZY_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_FUZZY_SELECT_TOOL, GimpFuzzySelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_FUZZY_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_FUZZY_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_FUZZY_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_FUZZY_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_FUZZY_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_FUZZY_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_FUZZY_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_FUZZY_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_FUZZY_SELECT_TOOL, GimpFuzzySelectToolClass))
end_define

begin_typedef
DECL|typedef|GimpFuzzySelectTool
typedef|typedef
name|struct
name|_GimpFuzzySelectTool
name|GimpFuzzySelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpFuzzySelectToolClass
typedef|typedef
name|struct
name|_GimpFuzzySelectToolClass
name|GimpFuzzySelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpFuzzySelectTool
struct|struct
name|_GimpFuzzySelectTool
block|{
DECL|member|parent_instance
name|GimpRegionSelectTool
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpFuzzySelectToolClass
struct|struct
name|_GimpFuzzySelectToolClass
block|{
DECL|member|parent_class
name|GimpRegionSelectToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_fuzzy_select_tool_register
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
name|gimp_fuzzy_select_tool_get_type
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
comment|/* __GIMP_FUZZY_SELECT_TOOL_H__ */
end_comment

end_unit

