begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__IMAGE_NEW_H__
end_ifndef

begin_define
DECL|macro|__IMAGE_NEW_H__
define|#
directive|define
name|__IMAGE_NEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdrawable.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
typedef|typedef
struct|struct
DECL|struct|__anon2c6f0eac0108
block|{
DECL|member|type
name|GimpImageBaseType
name|type
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|typedef|GimpImageBaseTypeName
block|}
name|GimpImageBaseTypeName
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2c6f0eac0208
block|{
DECL|member|type
name|GimpFillType
name|type
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|typedef|GimpFillTypeName
block|}
name|GimpFillTypeName
typedef|;
typedef|typedef
struct|struct
DECL|struct|__anon2c6f0eac0308
block|{
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|unit
name|GimpUnit
name|unit
decl_stmt|;
DECL|member|xresolution
name|gdouble
name|xresolution
decl_stmt|;
DECL|member|yresolution
name|gdouble
name|yresolution
decl_stmt|;
DECL|member|res_unit
name|GimpUnit
name|res_unit
decl_stmt|;
DECL|member|type
name|GimpImageBaseType
name|type
decl_stmt|;
DECL|member|fill_type
name|GimpFillType
name|fill_type
decl_stmt|;
DECL|typedef|GimpImageNewValues
block|}
name|GimpImageNewValues
typedef|;
name|GList
modifier|*
name|image_new_get_fill_type_names
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|GList
modifier|*
name|image_new_get_image_base_type_names
parameter_list|(
name|void
parameter_list|)
function_decl|;
name|void
name|image_new_create_window
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|values
parameter_list|,
specifier|const
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
name|void
name|image_new_set_default_values
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
function_decl|;
name|GimpImageNewValues
modifier|*
name|image_new_values_new
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|src_vals
parameter_list|)
function_decl|;
name|void
name|image_new_values_free
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
function_decl|;
name|void
name|image_new_create_image
parameter_list|(
specifier|const
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
function_decl|;
name|gdouble
name|image_new_calculate_size
parameter_list|(
name|GimpImageNewValues
modifier|*
name|values
parameter_list|)
function_decl|;
name|gchar
modifier|*
name|image_new_get_size_string
parameter_list|(
name|gdouble
name|size
parameter_list|)
function_decl|;
name|void
name|image_new_reset_current_cut_buffer
parameter_list|(
name|void
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __IMAGE_NEW__ */
end_comment

end_unit

