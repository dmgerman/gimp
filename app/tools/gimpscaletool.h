begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SCALE_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SCALE_TOOL_H__
define|#
directive|define
name|__GIMP_SCALE_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimptransformtool.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SCALE_TOOL
define|#
directive|define
name|GIMP_TYPE_SCALE_TOOL
value|(gimp_scale_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_SCALE_TOOL (obj)
define|#
directive|define
name|GIMP_SCALE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SCALE_TOOL, GimpScaleTool))
end_define

begin_define
DECL|macro|GIMP_SCALE_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_SCALE_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SCALE_TOOL, GimpScaleToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_SCALE_TOOL (obj)
define|#
directive|define
name|GIMP_IS_SCALE_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SCALE_TOOL))
end_define

begin_define
DECL|macro|GIMP_SCALE_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SCALE_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SCALE_TOOL, GimpScaleToolClass))
end_define

begin_typedef
DECL|typedef|GimpScaleTool
typedef|typedef
name|struct
name|_GimpScaleTool
name|GimpScaleTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpScaleToolClass
typedef|typedef
name|struct
name|_GimpScaleToolClass
name|GimpScaleToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpScaleTool
struct|struct
name|_GimpScaleTool
block|{
DECL|member|parent_instance
name|GimpTransformTool
name|parent_instance
decl_stmt|;
comment|/*  scale dialog  */
DECL|member|orig_width_buf
name|gchar
name|orig_width_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
DECL|member|orig_height_buf
name|gchar
name|orig_height_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
DECL|member|size_vals
name|gdouble
name|size_vals
index|[
literal|2
index|]
decl_stmt|;
DECL|member|x_ratio_buf
name|gchar
name|x_ratio_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
DECL|member|y_ratio_buf
name|gchar
name|y_ratio_buf
index|[
name|MAX_INFO_BUF
index|]
decl_stmt|;
DECL|member|aspect_ratio_val
name|gdouble
name|aspect_ratio_val
decl_stmt|;
DECL|member|sizeentry
name|GtkWidget
modifier|*
name|sizeentry
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpScaleToolClass
struct|struct
name|_GimpScaleToolClass
block|{
DECL|member|parent_class
name|GimpTransformToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_scale_tool_register
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
name|gimp_scale_tool_get_type
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
comment|/*  __GIMP_SCALE_TOOL_H__  */
end_comment

end_unit

