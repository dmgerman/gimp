begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BLEND_TOOL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BLEND_TOOL_H__
define|#
directive|define
name|__GIMP_BLEND_TOOL_H__
end_define

begin_include
include|#
directive|include
file|"gimpdrawtool.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bbe9b7d0103
block|{
DECL|enumerator|LINEAR
name|LINEAR
block|,
DECL|enumerator|BILINEAR
name|BILINEAR
block|,
DECL|enumerator|RADIAL
name|RADIAL
block|,
DECL|enumerator|SQUARE
name|SQUARE
block|,
DECL|enumerator|CONICAL_SYMMETRIC
name|CONICAL_SYMMETRIC
block|,
DECL|enumerator|CONICAL_ASYMMETRIC
name|CONICAL_ASYMMETRIC
block|,
DECL|enumerator|SHAPEBURST_ANGULAR
name|SHAPEBURST_ANGULAR
block|,
DECL|enumerator|SHAPEBURST_SPHERICAL
name|SHAPEBURST_SPHERICAL
block|,
DECL|enumerator|SHAPEBURST_DIMPLED
name|SHAPEBURST_DIMPLED
block|,
DECL|enumerator|SPIRAL_CLOCKWISE
name|SPIRAL_CLOCKWISE
block|,
DECL|enumerator|SPIRAL_ANTICLOCKWISE
name|SPIRAL_ANTICLOCKWISE
block|,
DECL|enumerator|GRADIENT_TYPE_LAST
name|GRADIENT_TYPE_LAST
comment|/*< skip>*/
DECL|typedef|GradientType
block|}
name|GradientType
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
comment|/*< chop=_MODE>*/
DECL|enum|__anon2bbe9b7d0203
block|{
DECL|enumerator|FG_BG_RGB_MODE
name|FG_BG_RGB_MODE
block|,
DECL|enumerator|FG_BG_HSV_MODE
name|FG_BG_HSV_MODE
block|,
DECL|enumerator|FG_TRANS_MODE
name|FG_TRANS_MODE
block|,
DECL|enumerator|CUSTOM_MODE
name|CUSTOM_MODE
block|,
DECL|enumerator|BLEND_MODE_LAST
name|BLEND_MODE_LAST
comment|/*< skip>*/
DECL|typedef|BlendMode
block|}
name|BlendMode
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2bbe9b7d0303
block|{
DECL|enumerator|REPEAT_NONE
name|REPEAT_NONE
block|,
DECL|enumerator|REPEAT_SAWTOOTH
name|REPEAT_SAWTOOTH
block|,
DECL|enumerator|REPEAT_TRIANGULAR
name|REPEAT_TRIANGULAR
block|,
DECL|enumerator|REPEAT_LAST
name|REPEAT_LAST
comment|/*< skip>*/
DECL|typedef|RepeatMode
block|}
name|RepeatMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_BLEND_TOOL
define|#
directive|define
name|GIMP_TYPE_BLEND_TOOL
value|(gimp_blend_tool_get_type ())
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL (obj)
define|#
directive|define
name|GIMP_BLEND_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BLEND_TOOL, GimpBlendTool))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_TOOL (obj)
define|#
directive|define
name|GIMP_IS_BLEND_TOOL
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BLEND_TOOL))
end_define

begin_define
DECL|macro|GIMP_BLEND_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_BLEND_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BLEND_TOOL, GimpBlendToolClass))
end_define

begin_define
DECL|macro|GIMP_IS_BLEND_TOOL_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BLEND_TOOL_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BLEND_TOOL))
end_define

begin_typedef
DECL|typedef|GimpBlendTool
typedef|typedef
name|struct
name|_GimpBlendTool
name|GimpBlendTool
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpBlendToolClass
typedef|typedef
name|struct
name|_GimpBlendToolClass
name|GimpBlendToolClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBlendTool
struct|struct
name|_GimpBlendTool
block|{
DECL|member|parent_instance
name|GimpDrawTool
name|parent_instance
decl_stmt|;
DECL|member|startx
name|gint
name|startx
decl_stmt|;
comment|/*  starting x coord     */
DECL|member|starty
name|gint
name|starty
decl_stmt|;
comment|/*  starting y coord     */
DECL|member|endx
name|gint
name|endx
decl_stmt|;
comment|/*  ending x coord       */
DECL|member|endy
name|gint
name|endy
decl_stmt|;
comment|/*  ending y coord       */
DECL|member|context_id
name|guint
name|context_id
decl_stmt|;
comment|/*  for the statusbar    */
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBlendToolClass
struct|struct
name|_GimpBlendToolClass
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
name|gimp_blend_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|gimp_blend_tool_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|blend
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|BlendMode
name|blend_mode
parameter_list|,
name|gint
name|paint_mode
parameter_list|,
name|GradientType
name|gradient_type
parameter_list|,
name|gdouble
name|opacity
parameter_list|,
name|gdouble
name|offset
parameter_list|,
name|RepeatMode
name|repeat
parameter_list|,
name|gint
name|supersample
parameter_list|,
name|gint
name|max_depth
parameter_list|,
name|gdouble
name|threshold
parameter_list|,
name|gdouble
name|startx
parameter_list|,
name|gdouble
name|starty
parameter_list|,
name|gdouble
name|endx
parameter_list|,
name|gdouble
name|endy
parameter_list|,
name|GimpProgressFunc
name|progress_callback
parameter_list|,
name|gpointer
name|progress_data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BLEND_TOOL_H__  */
end_comment

end_unit

