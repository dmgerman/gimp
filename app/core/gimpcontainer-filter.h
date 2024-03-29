begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimpcontainer-filter.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_FILTER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_FILTER_H__
define|#
directive|define
name|__GIMP_CONTAINER_FILTER_H__
end_define

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_container_filter
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpObjectFilterFunc
name|filter
parameter_list|,
name|gpointer
name|user_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_container_filter_by_name
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|regexp
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
modifier|*
name|gimp_container_get_filtered_name_array
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|regexp
parameter_list|,
name|gint
modifier|*
name|length
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CONTAINER_FILTER_H__ */
end_comment

end_unit

