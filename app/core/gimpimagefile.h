begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagefile.h  *  * Thumbnail handling according to the Thumbnail Managing Standard.  * http://triq.net/~pearl/thumbnail-spec/  *  * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *                          Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_IMAGEFILE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_IMAGEFILE_H__
define|#
directive|define
name|__GIMP_IMAGEFILE_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_IMAGEFILE
define|#
directive|define
name|GIMP_TYPE_IMAGEFILE
value|(gimp_imagefile_get_type ())
end_define

begin_define
DECL|macro|GIMP_IMAGEFILE (obj)
define|#
directive|define
name|GIMP_IMAGEFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_IMAGEFILE, GimpImagefile))
end_define

begin_define
DECL|macro|GIMP_IMAGEFILE_CLASS (klass)
define|#
directive|define
name|GIMP_IMAGEFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_IMAGEFILE, GimpImagefileClass))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGEFILE (obj)
define|#
directive|define
name|GIMP_IS_IMAGEFILE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_IMAGEFILE))
end_define

begin_define
DECL|macro|GIMP_IS_IMAGEFILE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_IMAGEFILE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_IMAGEFILE))
end_define

begin_define
DECL|macro|GIMP_IMAGEFILE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_IMAGEFILE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_IMAGEFILE, GimpImagefileClass))
end_define

begin_typedef
DECL|typedef|GimpImagefileClass
typedef|typedef
name|struct
name|_GimpImagefileClass
name|GimpImagefileClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpImagefile
struct|struct
name|_GimpImagefile
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpImagefileClass
struct|struct
name|_GimpImagefileClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|info_changed
name|void
function_decl|(
modifier|*
name|info_changed
function_decl|)
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_imagefile_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpImagefile
modifier|*
name|gimp_imagefile_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpThumbnail
modifier|*
name|gimp_imagefile_get_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_imagefile_set_mime_type
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_imagefile_update
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_imagefile_create_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|replace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_imagefile_create_thumbnail_weak
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|gint
name|size
parameter_list|,
name|gboolean
name|replace
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_imagefile_check_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_imagefile_save_thumbnail
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|,
specifier|const
name|gchar
modifier|*
name|mime_type
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_imagefile_get_desc_string
parameter_list|(
name|GimpImagefile
modifier|*
name|imagefile
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_IMAGEFILE_H__ */
end_comment

end_unit

