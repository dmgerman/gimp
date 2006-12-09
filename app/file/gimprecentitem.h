begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Recent File Storage,  * see http://freedesktop.org/Standards/recent-file-spec/  *  * This code is taken from libegg and has been adapted to the GIMP needs.  * The original author is James Willcox<jwillcox@cs.indiana.edu>,  * responsible for bugs in this version is Sven Neumann<sven@gimp.org>.  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_RECENT_ITEM_H__
end_ifndef

begin_define
DECL|macro|__GIMP_RECENT_ITEM_H__
define|#
directive|define
name|__GIMP_RECENT_ITEM_H__
end_define

begin_typedef
DECL|typedef|GimpRecentItem
typedef|typedef
name|struct
name|_GimpRecentItem
name|GimpRecentItem
typedef|;
end_typedef

begin_function_decl
name|GimpRecentItem
modifier|*
name|gimp_recent_item_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRecentItem
modifier|*
name|gimp_recent_item_ref
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRecentItem
modifier|*
name|gimp_recent_item_unref
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpRecentItem
modifier|*
name|gimp_recent_item_new_from_uri
parameter_list|(
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_recent_item_set_uri
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_recent_item_get_uri
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_recent_item_get_uri_utf8
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_item_set_mime_type
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_recent_item_get_mime_type
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_item_set_timestamp
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
name|time_t
name|timestamp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|gimp_recent_item_get_timestamp
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* groups */
end_comment

begin_function_decl
specifier|const
name|GList
modifier|*
name|gimp_recent_item_get_groups
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_recent_item_in_group
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|group_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_item_add_group
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|group_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_item_remove_group
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
specifier|const
name|gchar
modifier|*
name|group_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_recent_item_set_private
parameter_list|(
name|GimpRecentItem
modifier|*
name|item
parameter_list|,
name|gboolean
name|priv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_recent_item_get_private
parameter_list|(
specifier|const
name|GimpRecentItem
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_RECENT_ITEM_H__ */
end_comment

end_unit

