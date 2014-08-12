begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_MEMSIZE_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_MEMSIZE_H__
define|#
directive|define
name|__APP_GIMP_MEMSIZE_H__
end_define

begin_function_decl
name|gint64
name|gimp_g_type_instance_get_memsize
parameter_list|(
name|GTypeInstance
modifier|*
name|instance
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_object_get_memsize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_hash_table_get_memsize
parameter_list|(
name|GHashTable
modifier|*
name|hash
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_hash_table_get_memsize_foreach
parameter_list|(
name|GHashTable
modifier|*
name|hash
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_slist_get_memsize
parameter_list|(
name|GSList
modifier|*
name|slist
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_slist_get_memsize_foreach
parameter_list|(
name|GSList
modifier|*
name|slist
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_list_get_memsize
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_list_get_memsize_foreach
parameter_list|(
name|GList
modifier|*
name|slist
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_value_get_memsize
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_param_spec_get_memsize
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_gegl_buffer_get_memsize
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_gegl_pyramid_get_memsize
parameter_list|(
name|GeglBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_string_get_memsize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_parasite_get_memsize
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APP_GIMP_MEMSIZE_H__ */
end_comment

end_unit

