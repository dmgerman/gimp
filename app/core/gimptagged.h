begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * gimptagged.h  * Copyright (C) 2008  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TAGGED_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TAGGED_H__
define|#
directive|define
name|__GIMP_TAGGED_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_TAGGED
define|#
directive|define
name|GIMP_TYPE_TAGGED
value|(gimp_tagged_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_IS_TAGGED (obj)
define|#
directive|define
name|GIMP_IS_TAGGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TAGGED))
end_define

begin_define
DECL|macro|GIMP_TAGGED (obj)
define|#
directive|define
name|GIMP_TAGGED
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TAGGED, GimpTagged))
end_define

begin_define
DECL|macro|GIMP_TAGGED_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_TAGGED_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_TAGGED, GimpTaggedInterface))
end_define

begin_typedef
DECL|typedef|GimpTaggedInterface
typedef|typedef
name|struct
name|_GimpTaggedInterface
name|GimpTaggedInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTaggedInterface
struct|struct
name|_GimpTaggedInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  signals            */
DECL|member|tag_added
name|void
function_decl|(
modifier|*
name|tag_added
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
DECL|member|tag_removed
name|void
function_decl|(
modifier|*
name|tag_removed
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|add_tag
name|gboolean
function_decl|(
modifier|*
name|add_tag
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
DECL|member|remove_tag
name|gboolean
function_decl|(
modifier|*
name|remove_tag
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
DECL|member|get_tags
name|GList
modifier|*
function_decl|(
modifier|*
name|get_tags
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
DECL|member|get_identifier
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_identifier
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
DECL|member|get_checksum
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_checksum
function_decl|)
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tagged_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_tagged_add_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tagged_remove_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tagged_set_tags
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GList
modifier|*
name|tags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_tagged_get_tags
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_tagged_get_identifier
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_tagged_get_checksum
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tagged_has_tag
parameter_list|(
name|GimpTagged
modifier|*
name|tagged
parameter_list|,
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TAGGED_H__ */
end_comment

end_unit

