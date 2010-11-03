begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SAMPLE_POINT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SAMPLE_POINT_H__
define|#
directive|define
name|__GIMP_SAMPLE_POINT_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SAMPLE_POINT
define|#
directive|define
name|GIMP_TYPE_SAMPLE_POINT
value|(gimp_sample_point_get_type ())
end_define

begin_struct
DECL|struct|_GimpSamplePoint
struct|struct
name|_GimpSamplePoint
block|{
DECL|member|ref_count
name|gint
name|ref_count
decl_stmt|;
DECL|member|sample_point_ID
name|guint32
name|sample_point_ID
decl_stmt|;
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_sample_point_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpSamplePoint
modifier|*
name|gimp_sample_point_new
parameter_list|(
name|guint32
name|sample_point_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSamplePoint
modifier|*
name|gimp_sample_point_ref
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_sample_point_unref
parameter_list|(
name|GimpSamplePoint
modifier|*
name|sample_point
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SAMPLE_POINT_H__ */
end_comment

end_unit

