begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BUFFER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BUFFER_H__
define|#
directive|define
name|__GIMP_BUFFER_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BUFFER
define|#
directive|define
name|GIMP_TYPE_BUFFER
value|(gimp_buffer_get_type ())
end_define

begin_define
DECL|macro|GIMP_BUFFER (obj)
define|#
directive|define
name|GIMP_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BUFFER, GimpBuffer))
end_define

begin_define
DECL|macro|GIMP_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BUFFER, GimpBufferClass))
end_define

begin_define
DECL|macro|GIMP_IS_BUFFER (obj)
define|#
directive|define
name|GIMP_IS_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_BUFFER))
end_define

begin_define
DECL|macro|GIMP_IS_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BUFFER))
end_define

begin_typedef
DECL|typedef|GimpBufferClass
typedef|typedef
name|struct
name|_GimpBufferClass
name|GimpBufferClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBuffer
struct|struct
name|_GimpBuffer
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|tiles
name|TileManager
modifier|*
name|tiles
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBufferClass
struct|struct
name|_GimpBufferClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_buffer_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpBuffer
modifier|*
name|gimp_buffer_new
parameter_list|(
name|TileManager
modifier|*
name|tiles
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_BUFFER_H__ */
end_comment

end_unit

