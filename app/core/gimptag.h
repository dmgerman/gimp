begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptag.h  * Copyright (C) 2008 Aurimas JuÅ¡ka<aurisj@svn.gnome.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TAG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TAG_H__
define|#
directive|define
name|__GIMP_TAG_H__
end_define

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_TAG
define|#
directive|define
name|GIMP_TYPE_TAG
value|(gimp_tag_get_type ())
end_define

begin_define
DECL|macro|GIMP_TAG (obj)
define|#
directive|define
name|GIMP_TAG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TAG, GimpTag))
end_define

begin_define
DECL|macro|GIMP_TAG_CLASS (klass)
define|#
directive|define
name|GIMP_TAG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TAG, GimpTagClass))
end_define

begin_define
DECL|macro|GIMP_IS_TAG (obj)
define|#
directive|define
name|GIMP_IS_TAG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TAG))
end_define

begin_define
DECL|macro|GIMP_IS_TAG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TAG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TAG))
end_define

begin_define
DECL|macro|GIMP_TAG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TAG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TAG, GimpTagClass))
end_define

begin_typedef
DECL|typedef|GimpTagClass
typedef|typedef
name|struct
name|_GimpTagClass
name|GimpTagClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpTag
struct|struct
name|_GimpTag
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|tag
name|GQuark
name|tag
decl_stmt|;
DECL|member|collate_key
name|GQuark
name|collate_key
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpTagClass
struct|struct
name|_GimpTagClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tag_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpTag
modifier|*
name|gimp_tag_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpTag
modifier|*
name|gimp_tag_try_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_tag_get_name
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|guint
name|gimp_tag_get_hash
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tag_equals
parameter_list|(
specifier|const
name|GimpTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|GimpTag
modifier|*
name|other
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_tag_compare_func
parameter_list|(
specifier|const
name|void
modifier|*
name|p1
parameter_list|,
specifier|const
name|void
modifier|*
name|p2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_tag_compare_with_string
parameter_list|(
name|GimpTag
modifier|*
name|tag
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_tag_string_make_valid
parameter_list|(
specifier|const
name|gchar
modifier|*
name|tag_string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_tag_is_tag_separator
parameter_list|(
name|gunichar
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tag_or_null_ref
parameter_list|(
name|GimpTag
modifier|*
name|tag_or_null
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_tag_or_null_unref
parameter_list|(
name|GimpTag
modifier|*
name|tag_or_null
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TAG_H__ */
end_comment

end_unit

