begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdata.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<time.h>
end_include

begin_comment
comment|/* time_t */
end_comment

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c6b5e8b0103
block|{
DECL|enumerator|GIMP_DATA_ERROR_OPEN
name|GIMP_DATA_ERROR_OPEN
block|,
comment|/*  opening data file failed   */
DECL|enumerator|GIMP_DATA_ERROR_READ
name|GIMP_DATA_ERROR_READ
block|,
comment|/*  reading data file failed   */
DECL|enumerator|GIMP_DATA_ERROR_WRITE
name|GIMP_DATA_ERROR_WRITE
block|,
comment|/*  writing data file failed   */
DECL|enumerator|GIMP_DATA_ERROR_DELETE
name|GIMP_DATA_ERROR_DELETE
comment|/*  deleting data file failed  */
DECL|typedef|GimpDataError
block|}
name|GimpDataError
typedef|;
end_typedef

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
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DATA, GimpData))
end_define

begin_define
DECL|macro|GIMP_DATA_CLASS (klass)
define|#
directive|define
name|GIMP_DATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DATA, GimpDataClass))
end_define

begin_define
DECL|macro|GIMP_IS_DATA (obj)
define|#
directive|define
name|GIMP_IS_DATA
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DATA))
end_define

begin_define
DECL|macro|GIMP_IS_DATA_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DATA_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DATA))
end_define

begin_define
DECL|macro|GIMP_DATA_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DATA_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DATA, GimpDataClass))
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
comment|/*  signals  */
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
comment|/*  virtual functions  */
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
DECL|member|get_extension
specifier|const
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

begin_decl_stmt
name|GType
name|gimp_data_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gboolean
name|gimp_data_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
name|void
name|gimp_data_clean
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_is_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_freeze
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_thaw
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_is_frozen
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
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
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
parameter_list|,
name|gboolean
name|writable
parameter_list|,
name|gboolean
name|deletable
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
name|dest_dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_data_get_filename
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
name|gimp_data_get_mime_type
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_is_writable
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_is_deletable
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_data_set_mtime
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
name|time_t
name|mtime
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|gimp_data_get_mtime
parameter_list|(
name|GimpData
modifier|*
name|data
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

begin_function_decl
name|void
name|gimp_data_make_internal
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_data_is_internal
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_data_compare
parameter_list|(
name|GimpData
modifier|*
name|data1
parameter_list|,
name|GimpData
modifier|*
name|data2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_data_name_compare
parameter_list|(
name|GimpData
modifier|*
name|data1
parameter_list|,
name|GimpData
modifier|*
name|data2
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|GIMP_DATA_ERROR
define|#
directive|define
name|GIMP_DATA_ERROR
value|(gimp_data_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_data_error_quark
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DATA_H__ */
end_comment

end_unit

