begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATTERN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATTERN_H__
define|#
directive|define
name|__GIMP_PATTERN_H__
end_define

begin_include
include|#
directive|include
file|"gimpdata.h"
end_include

begin_define
DECL|macro|GIMP_PATTERN_FILE_EXTENSION
define|#
directive|define
name|GIMP_PATTERN_FILE_EXTENSION
value|".pat"
end_define

begin_define
DECL|macro|GIMP_TYPE_PATTERN
define|#
directive|define
name|GIMP_TYPE_PATTERN
value|(gimp_pattern_get_type ())
end_define

begin_define
DECL|macro|GIMP_PATTERN (obj)
define|#
directive|define
name|GIMP_PATTERN
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_PATTERN, GimpPattern))
end_define

begin_define
DECL|macro|GIMP_PATTERN_CLASS (klass)
define|#
directive|define
name|GIMP_PATTERN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PATTERN, GimpPatternClass))
end_define

begin_define
DECL|macro|GIMP_IS_PATTERN (obj)
define|#
directive|define
name|GIMP_IS_PATTERN
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_PATTERN))
end_define

begin_define
DECL|macro|GIMP_IS_PATTERN_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PATTERN_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PATTERN))
end_define

begin_typedef
DECL|typedef|GimpPatternClass
typedef|typedef
name|struct
name|_GimpPatternClass
name|GimpPatternClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPattern
struct|struct
name|_GimpPattern
block|{
DECL|member|parent_instance
name|GimpData
name|parent_instance
decl_stmt|;
DECL|member|mask
name|TempBuf
modifier|*
name|mask
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPatternClass
struct|struct
name|_GimpPatternClass
block|{
DECL|member|parent_class
name|GimpDataClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_pattern_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPattern
modifier|*
name|gimp_pattern_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPattern
modifier|*
name|gimp_pattern_get_standard
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPattern
modifier|*
name|gimp_pattern_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|TempBuf
modifier|*
name|gimp_pattern_get_mask
parameter_list|(
specifier|const
name|GimpPattern
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PATTERN_H__ */
end_comment

end_unit

