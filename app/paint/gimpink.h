begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INK_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INK_TOOL_H__
define|#
directive|define
name|__GIMP_INK_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"libgimptool/gimptool.h"
end_include

begin_include
include|#
directive|include
file|"gimpinktool-blob.h"
end_include

begin_comment
comment|/* only used by ink */
end_comment

begin_define
DECL|macro|DIST_SMOOTHER_BUFFER
define|#
directive|define
name|DIST_SMOOTHER_BUFFER
value|10
end_define

begin_define
DECL|macro|TIME_SMOOTHER_BUFFER
define|#
directive|define
name|TIME_SMOOTHER_BUFFER
value|10
end_define

begin_define
DECL|macro|GIMP_TYPE_INK_TOOL
define|#
directive|define
name|GIMP_TYPE_INK_TOOL
value|(gimp_ink_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_INK_TOOL (obj)
define|#
directive|define
name|GIMP_INK_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INK_TOOL, GimpInkTool))
end_define

begin_define
DECL|macro|GIMP_INK_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_INK_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_INK_TOOL, GimpInkToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_INK_TOOL (obj)
define|#
directive|define
name|GIMP_IS_INK_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INK_TOOL))
end_define

begin_define
DECL|macro|GIMP_IS_INK_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_INK_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_INK_TOOL))
end_define

begin_define
DECL|macro|GIMP_INK_TOOL_GET_CLASS (obj)
define|#
directive|define
name|GIMP_INK_TOOL_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_INK_TOOL, GimpInkToolClass))
end_define

begin_typedef
DECL|typedef|GimpInkTool
typedef|typedef
name|struct
name|_GimpInkTool
name|GimpInkTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInkToolClass
typedef|typedef
name|struct
name|_GimpInkToolClass
name|GimpInkToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpInkTool
struct|struct
name|_GimpInkTool
block|{
DECL|member|parent_instance
name|GimpTool
name|parent_instance
decl_stmt|;
DECL|member|last_blob
name|Blob
modifier|*
name|last_blob
decl_stmt|;
comment|/*  blob for last cursor position  */
DECL|member|x1
DECL|member|y1
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
comment|/*  image space coordinate         */
DECL|member|x2
DECL|member|y2
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
comment|/*  image space coords             */
comment|/* circular distance history buffer */
DECL|member|dt_buffer
name|gdouble
name|dt_buffer
index|[
name|DIST_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|dt_index
name|gint
name|dt_index
decl_stmt|;
comment|/* circular timing history buffer */
DECL|member|ts_buffer
name|guint32
name|ts_buffer
index|[
name|TIME_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|ts_index
name|gint
name|ts_index
decl_stmt|;
DECL|member|last_time
name|gdouble
name|last_time
decl_stmt|;
comment|/*  previous time of a motion event      */
DECL|member|lastx
DECL|member|lasty
name|gdouble
name|lastx
decl_stmt|,
name|lasty
decl_stmt|;
comment|/*  previous position of a motion event  */
DECL|member|init_velocity
name|gboolean
name|init_velocity
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpInkToolClass
struct|struct
name|_GimpInkToolClass
block|{
DECL|member|parent_class
name|GimpToolClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_ink_tool_register
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
name|gimp_ink_tool_get_type
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
comment|/*  __GIMP_INK_TOOL_H__  */
end_comment

end_unit

