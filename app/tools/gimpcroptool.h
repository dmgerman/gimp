begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__CROP_H__
end_ifndef

begin_define
DECL|macro|__CROP_H__
define|#
directive|define
name|__CROP_H__
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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_CROP_TOOL, GimpCropTool))
end_define

begin_define
DECL|macro|GIMP_IS_CROP_TOOL (obj)
define|#
directive|define
name|GIMP_IS_CROP_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_CROP_TOOL))
end_define

begin_define
DECL|macro|GIMP_CROP_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_CROP_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CROP_TOOL, GimpCropToolClass))
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

begin_comment
comment|/* XXX Used? */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2b38f20d0103
block|{
DECL|enumerator|CROP_CROP
name|CROP_CROP
block|,
DECL|enumerator|RESIZE_CROP
name|RESIZE_CROP
DECL|typedef|CropType
block|}
name|CropType
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
comment|/*  DrawCore *core; */
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
DECL|member|srw
DECL|member|srh
name|gint
name|srw
decl_stmt|,
name|srh
decl_stmt|;
comment|/*  width and height of corners */
DECL|member|tx1
DECL|member|ty1
name|gint
name|tx1
decl_stmt|,
name|ty1
decl_stmt|;
comment|/*  transformed coords          */
DECL|member|tx2
DECL|member|ty2
name|gint
name|tx2
decl_stmt|,
name|ty2
decl_stmt|;
comment|/*                              */
DECL|member|function
name|guint
name|function
decl_stmt|;
comment|/*  moving or resizing          */
DECL|member|context_id
name|guint
name|context_id
decl_stmt|;
comment|/*  for the statusbar           */
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
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_crop_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Keep around for the PDB, temporarily */
end_comment

begin_function_decl
name|void
name|crop_image
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gboolean
name|layer_only
parameter_list|,
name|gboolean
name|crop_layers
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __CROP_H__  */
end_comment

end_unit

