begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECT_SELECT_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECT_SELECT_TOOL_H__
define|#
directive|define
name|__GIMP_RECT_SELECT_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_RECT_SELECT_TOOL
define|#
directive|define
name|GIMP_TYPE_RECT_SELECT_TOOL
value|(gimp_rect_select_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_RECT_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_RECT_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_RECT_SELECT_TOOL, GimpRectSelectTool))
end_define

begin_define
DECL|macro|GIMP_RECT_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_RECT_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_RECT_SELECT_TOOL, GimpRectSelectToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_RECT_SELECT_TOOL (obj)
define|#
directive|define
name|GIMP_IS_RECT_SELECT_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_RECT_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_RECT_SELECT_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_RECT_SELECT_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_RECT_SELECT_TOOL))
end_define

begin_define
DECL|macro|GIMP_RECT_SELECT_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_RECT_SELECT_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_RECT_SELECT_TOOL, GimpRectSelectToolClass))
end_define

begin_typedef
DECL|typedef|GimpRectSelectTool
typedef|typedef
name|struct
name|_GimpRectSelectTool
name|GimpRectSelectTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpRectSelectToolClass
typedef|typedef
name|struct
name|_GimpRectSelectToolClass
name|GimpRectSelectToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpRectSelectTool
struct|struct
name|_GimpRectSelectTool
block|{
DECL|member|parent_instance
name|GimpSelectionTool
name|parent_instance
decl_stmt|;
DECL|member|sx
DECL|member|sy
name|gint
name|sx
decl_stmt|,
name|sy
decl_stmt|;
comment|/*  start coordinate where the button is                                    *  first pressed  */
DECL|member|x
DECL|member|y
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
comment|/*  upper left coordinate of selection  */
DECL|member|w
DECL|member|h
name|gint
name|w
decl_stmt|,
name|h
decl_stmt|;
comment|/*  width, height of selection always>=0  */
DECL|member|lx
DECL|member|ly
name|gint
name|lx
decl_stmt|,
name|ly
decl_stmt|;
comment|/*  last coordinate of mouse cursor  */
DECL|member|center
name|gboolean
name|center
decl_stmt|;
comment|/*  is the selection being created from the                                    *  center out?  */
DECL|member|fixed_mode
name|GimpRectSelectMode
name|fixed_mode
decl_stmt|;
DECL|member|fixed_width
name|gdouble
name|fixed_width
decl_stmt|;
DECL|member|fixed_height
name|gdouble
name|fixed_height
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpRectSelectToolClass
struct|struct
name|_GimpRectSelectToolClass
block|{
DECL|member|parent_class
name|GimpSelectionToolClass
name|parent_class
decl_stmt|;
comment|/*  virtual function  */
DECL|member|rect_select
name|void
function_decl|(
modifier|*
name|rect_select
function_decl|)
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_rect_select_tool_register
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
name|gimp_rect_select_tool_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_rect_select_tool_rect_select
parameter_list|(
name|GimpRectSelectTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_RECT_SELECT_TOOL_H__  */
end_comment

end_unit

