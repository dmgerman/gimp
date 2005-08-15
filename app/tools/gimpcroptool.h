begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CROP_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CROP_TOOL_H__
define|#
directive|define
name|__GIMP_CROP_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CROP_TOOL
define|#
directive|define
name|GIMP_TYPE_CROP_TOOL
value|(gimp_crop_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_CROP_TOOL (obj)
define|#
directive|define
name|GIMP_CROP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CROP_TOOL, GimpCropTool))
end_define

begin_define
DECL|macro|GIMP_CROP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CROP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CROP_TOOL, GimpCropToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_CROP_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CROP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CROP_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_CROP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CROP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CROP_TOOL))
end_define

begin_define
DECL|macro|GIMP_CROP_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CROP_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CROP_TOOL, GimpCropToolClass))
end_define

begin_typedef
DECL|typedef|GimpCropTool
typedef|typedef
name|struct
name|_GimpCropTool
name|GimpCropTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCropToolClass
typedef|typedef
name|struct
name|_GimpCropToolClass
name|GimpCropToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCropTool
struct|struct
name|_GimpCropTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|controls
name|GtkWidget
modifier|*
name|controls
decl_stmt|;
DECL|member|dimensions_entry
name|GtkWidget
modifier|*
name|dimensions_entry
decl_stmt|;
DECL|member|startx
name|gint
name|startx
decl_stmt|;
comment|/*  starting x coord            */
DECL|member|starty
name|gint
name|starty
decl_stmt|;
comment|/*  starting y coord            */
DECL|member|lastx
name|gint
name|lastx
decl_stmt|;
comment|/*  previous x coord            */
DECL|member|lasty
name|gint
name|lasty
decl_stmt|;
comment|/*  previous y coord            */
DECL|member|pressx
name|gint
name|pressx
decl_stmt|;
comment|/*  x where button pressed      */
DECL|member|pressy
name|gint
name|pressy
decl_stmt|;
comment|/*  y where button pressed      */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  upper left hand coordinate  */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  lower right hand coords     */
DECL|member|function
name|guint
name|function
decl_stmt|;
comment|/*  moving or resizing          */
DECL|member|dx1
DECL|member|dy1
name|gint
name|dx1
decl_stmt|,
name|dy1
decl_stmt|;
comment|/*  display coords              */
DECL|member|dx2
DECL|member|dy2
name|gint
name|dx2
decl_stmt|,
name|dy2
decl_stmt|;
comment|/*                              */
DECL|member|dcw
DECL|member|dch
name|gint
name|dcw
decl_stmt|,
name|dch
decl_stmt|;
comment|/*  width and height of edges   */
DECL|member|origx
DECL|member|origy
name|gdouble
name|origx
decl_stmt|,
name|origy
decl_stmt|;
DECL|member|sizew
DECL|member|sizeh
name|gdouble
name|sizew
decl_stmt|,
name|sizeh
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCropToolClass
struct|struct
name|_GimpCropToolClass
block|{
DECL|member|parent_class
name|GimpDrawToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_crop_tool_register
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
name|gimp_crop_tool_get_type
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
comment|/*  __GIMP_CROP_TOOL_H__  */
end_comment

end_unit

