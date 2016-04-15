begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-babl.h  * Copyright (C) 2012 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BABL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BABL_H__
define|#
directive|define
name|__GIMP_BABL_H__
end_define

begin_function_decl
name|void
name|gimp_babl_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_babl_format_get_description
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpColorProfile
modifier|*
name|gimp_babl_format_get_color_profile
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImageBaseType
name|gimp_babl_format_get_base_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpComponentType
name|gimp_babl_format_get_component_type
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPrecision
name|gimp_babl_format_get_precision
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_babl_format_get_linear
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpComponentType
name|gimp_babl_component_type
parameter_list|(
name|GimpPrecision
name|precision
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPrecision
name|gimp_babl_precision
parameter_list|(
name|GimpComponentType
name|component
parameter_list|,
name|gboolean
name|linear
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_babl_format
parameter_list|(
name|GimpImageBaseType
name|base_type
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|gboolean
name|with_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_babl_mask_format
parameter_list|(
name|GimpPrecision
name|precision
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_babl_component_format
parameter_list|(
name|GimpImageBaseType
name|base_type
parameter_list|,
name|GimpPrecision
name|precision
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_babl_print_pixel
parameter_list|(
specifier|const
name|Babl
modifier|*
name|format
parameter_list|,
name|gpointer
name|pixel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BABL_H__ */
end_comment

end_unit

