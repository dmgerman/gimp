begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_UTILS_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_UTILS_H__
define|#
directive|define
name|__APP_GIMP_UTILS_H__
end_define

begin_function_decl
name|gboolean
name|gimp_rectangle_intersect
parameter_list|(
name|gint
name|x1
parameter_list|,
name|gint
name|y1
parameter_list|,
name|gint
name|width1
parameter_list|,
name|gint
name|height1
parameter_list|,
name|gint
name|x2
parameter_list|,
name|gint
name|y2
parameter_list|,
name|gint
name|width2
parameter_list|,
name|gint
name|height2
parameter_list|,
name|gint
modifier|*
name|dest_x
parameter_list|,
name|gint
modifier|*
name|dest_y
parameter_list|,
name|gint
modifier|*
name|dest_width
parameter_list|,
name|gint
modifier|*
name|dest_height
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
name|gchar
modifier|*
name|gimp_get_default_language
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APP_GIMP_UTILS_H__ */
end_comment

end_unit

