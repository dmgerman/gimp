begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpstrokedesc.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_STROKE_DESC_H__
end_ifndef

begin_define
DECL|macro|__GIMP_STROKE_DESC_H__
define|#
directive|define
name|__GIMP_STROKE_DESC_H__
end_define

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_STROKE_DESC
define|#
directive|define
name|GIMP_TYPE_STROKE_DESC
value|(gimp_stroke_desc_get_type ())
end_define

begin_define
DECL|macro|GIMP_STROKE_DESC (obj)
define|#
directive|define
name|GIMP_STROKE_DESC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_STROKE_DESC, GimpStrokeDesc))
end_define

begin_define
DECL|macro|GIMP_STROKE_DESC_CLASS (klass)
define|#
directive|define
name|GIMP_STROKE_DESC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_STROKE_DESC, GimpStrokeDescClass))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE_DESC (obj)
define|#
directive|define
name|GIMP_IS_STROKE_DESC
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_STROKE_DESC))
end_define

begin_define
DECL|macro|GIMP_IS_STROKE_DESC_CLASS (klass)
define|#
directive|define
name|GIMP_IS_STROKE_DESC_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_STROKE_DESC))
end_define

begin_define
DECL|macro|GIMP_STROKE_DESC_GET_CLASS (obj)
define|#
directive|define
name|GIMP_STROKE_DESC_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_STROKE_DESC, GimpStrokeDescClass))
end_define

begin_typedef
DECL|typedef|GimpStrokeDescClass
typedef|typedef
name|struct
name|_GimpStrokeDescClass
name|GimpStrokeDescClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpStrokeDesc
struct|struct
name|_GimpStrokeDesc
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|method
name|GimpStrokeMethod
name|method
decl_stmt|;
DECL|member|stroke_options
name|GimpStrokeOptions
modifier|*
name|stroke_options
decl_stmt|;
DECL|member|paint_info
name|GimpPaintInfo
modifier|*
name|paint_info
decl_stmt|;
DECL|member|paint_options
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpStrokeDescClass
struct|struct
name|_GimpStrokeDescClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_stroke_desc_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpStrokeDesc
modifier|*
name|gimp_stroke_desc_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpStrokeDesc
modifier|*
name|gimp_stroke_desc_duplicate
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_desc_prepare
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gboolean
name|use_default_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_stroke_desc_finish
parameter_list|(
name|GimpStrokeDesc
modifier|*
name|desc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_STROKE_DESC_H__  */
end_comment

end_unit

