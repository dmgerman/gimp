begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdata.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DATA_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DATA_H__
define|#
directive|define
name|__GIMP_DATA_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DATA
define|#
directive|define
name|GIMP_TYPE_DATA
value|(gimp_data_get_type ())
end_define

begin_define
DECL|macro|GIMP_DATA (obj)
define|#
directive|define
name|GIMP_DATA
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DATA, GimpData))
end_define

begin_define
DECL|macro|GIMP_DATA_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA, GimpDataClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA (obj)
define|#
directive|define
name|GIMP_IS_DATA
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DATA))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA))
end_define

begin_typedef
DECL|typedef|GimpDataClass
typedef|typedef
name|struct
name|_GimpDataClass
name|GimpDataClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpData
struct|struct
name|_GimpData
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|filename
name|gchar
modifier|*
name|filename
decl_stmt|;
DECL|member|dirty
name|gboolean
name|dirty
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDataClass
struct|struct
name|_GimpDataClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
DECL|member|dirty
name|void
function_decl|(
modifier|*
name|dirty
function_decl|)
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|save
name|gboolean
function_decl|(
modifier|*
name|save
function_decl|)
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|get_extension
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_extension
function_decl|)
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|duplicate
name|GimpData
modifier|*
function_decl|(
modifier|*
name|duplicate
function_decl|)
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_data_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_delete_from_disk
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_data_get_extension
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_set_filename
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_create_filename
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|,
specifier|const
name|gchar
modifier|*
name|data_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpData
modifier|*
name|gimp_data_duplicate
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DATA_H__ */
end_comment

end_unit

