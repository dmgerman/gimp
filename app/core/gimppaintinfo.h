begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_INFO_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_INFO_H__
define|#
directive|define
name|__GIMP_PAINT_INFO_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PAINT_INFO
define|#
directive|define
name|GIMP_TYPE_PAINT_INFO
value|(gimp_paint_info_get_type ())
end_define

begin_define
DECL|macro|GIMP_PAINT_INFO (obj)
define|#
directive|define
name|GIMP_PAINT_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PAINT_INFO, GimpPaintInfo))
end_define

begin_define
DECL|macro|GIMP_PAINT_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_PAINT_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PAINT_INFO, GimpPaintInfoClass))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_INFO (obj)
define|#
directive|define
name|GIMP_IS_PAINT_INFO
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PAINT_INFO))
end_define

begin_define
DECL|macro|GIMP_IS_PAINT_INFO_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PAINT_INFO_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PAINT_INFO))
end_define

begin_define
DECL|macro|GIMP_PAINT_INFO_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PAINT_INFO_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PAINT_INFO, GimpPaintInfoClass))
end_define

begin_typedef
DECL|typedef|GimpPaintInfoClass
typedef|typedef
name|struct
name|_GimpPaintInfoClass
name|GimpPaintInfoClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPaintInfo
struct|struct
name|_GimpPaintInfo
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|paint_type
name|GType
name|paint_type
decl_stmt|;
DECL|member|paint_options_type
name|GType
name|paint_options_type
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
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
DECL|struct|_GimpPaintInfoClass
struct|struct
name|_GimpPaintInfoClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_paint_info_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPaintInfo
modifier|*
name|gimp_paint_info_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|paint_type
parameter_list|,
name|GType
name|paint_options_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_info_set_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintInfo
modifier|*
name|paint_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPaintInfo
modifier|*
name|gimp_paint_info_get_standard
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_INFO_H__  */
end_comment

end_unit

