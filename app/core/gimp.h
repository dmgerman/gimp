begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_H__
end_ifndef

begin_define
DECL|macro|__GIMP_H__
define|#
directive|define
name|__GIMP_H__
end_define

begin_include
include|#
directive|include
file|"gimpobject.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage-new.h"
end_include

begin_typedef
DECL|typedef|GimpCreateDisplayFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpCreateDisplayFunc
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpSetBusyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpSetBusyFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpUnsetBusyFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpUnsetBusyFunc
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_GIMP
define|#
directive|define
name|GIMP_TYPE_GIMP
value|(gimp_get_type ())
end_define

begin_define
DECL|macro|GIMP (obj)
define|#
directive|define
name|GIMP
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_GIMP, Gimp))
end_define

begin_define
DECL|macro|GIMP_CLASS (klass)
define|#
directive|define
name|GIMP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_GIMP, GimpClass))
end_define

begin_define
DECL|macro|GIMP_IS_GIMP (obj)
define|#
directive|define
name|GIMP_IS_GIMP
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_GIMP))
end_define

begin_define
DECL|macro|GIMP_IS_GIMP_CLASS (klass)
define|#
directive|define
name|GIMP_IS_GIMP_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_GIMP))
end_define

begin_typedef
DECL|typedef|GimpClass
typedef|typedef
name|struct
name|_GimpClass
name|GimpClass
typedef|;
end_typedef

begin_struct
DECL|struct|_Gimp
struct|struct
name|_Gimp
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|create_display_func
name|GimpCreateDisplayFunc
name|create_display_func
decl_stmt|;
DECL|member|gui_set_busy_func
name|GimpSetBusyFunc
name|gui_set_busy_func
decl_stmt|;
DECL|member|gui_unset_busy_func
name|GimpUnsetBusyFunc
name|gui_unset_busy_func
decl_stmt|;
DECL|member|busy
name|gboolean
name|busy
decl_stmt|;
DECL|member|busy_idle_id
name|guint
name|busy_idle_id
decl_stmt|;
DECL|member|user_units
name|GList
modifier|*
name|user_units
decl_stmt|;
DECL|member|n_user_units
name|gint
name|n_user_units
decl_stmt|;
DECL|member|images
name|GimpContainer
modifier|*
name|images
decl_stmt|;
DECL|member|global_buffer
name|TileManager
modifier|*
name|global_buffer
decl_stmt|;
DECL|member|named_buffers
name|GimpContainer
modifier|*
name|named_buffers
decl_stmt|;
DECL|member|parasites
name|GimpParasiteList
modifier|*
name|parasites
decl_stmt|;
DECL|member|brush_factory
name|GimpDataFactory
modifier|*
name|brush_factory
decl_stmt|;
DECL|member|pattern_factory
name|GimpDataFactory
modifier|*
name|pattern_factory
decl_stmt|;
DECL|member|gradient_factory
name|GimpDataFactory
modifier|*
name|gradient_factory
decl_stmt|;
DECL|member|palette_factory
name|GimpDataFactory
modifier|*
name|palette_factory
decl_stmt|;
DECL|member|procedural_ht
name|GHashTable
modifier|*
name|procedural_ht
decl_stmt|;
DECL|member|tool_info_list
name|GimpContainer
modifier|*
name|tool_info_list
decl_stmt|;
comment|/*  image_new values  */
DECL|member|image_base_type_names
name|GList
modifier|*
name|image_base_type_names
decl_stmt|;
DECL|member|fill_type_names
name|GList
modifier|*
name|fill_type_names
decl_stmt|;
DECL|member|image_new_last_values
name|GimpImageNewValues
name|image_new_last_values
decl_stmt|;
DECL|member|have_current_cut_buffer
name|gboolean
name|have_current_cut_buffer
decl_stmt|;
comment|/*  the list of all contexts  */
DECL|member|context_list
name|GList
modifier|*
name|context_list
decl_stmt|;
comment|/*  the hardcoded standard context  */
DECL|member|standard_context
name|GimpContext
modifier|*
name|standard_context
decl_stmt|;
comment|/*  the default context which is initialized from gimprc  */
DECL|member|default_context
name|GimpContext
modifier|*
name|default_context
decl_stmt|;
comment|/*  the context used by the interface  */
DECL|member|user_context
name|GimpContext
modifier|*
name|user_context
decl_stmt|;
comment|/*  the currently active context  */
DECL|member|current_context
name|GimpContext
modifier|*
name|current_context
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpClass
struct|struct
name|_GimpClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
name|gimp_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Gimp
modifier|*
name|gimp_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_initialize
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_restore
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gboolean
name|no_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_shutdown
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy_until_idle
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpImage
modifier|*
name|gimp_create_image
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|,
name|GimpImageBaseType
name|type
parameter_list|,
name|gboolean
name|attach_comment
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* void          gimp_open_file            (Gimp              *gimp, 					 const gchar       *filename, 					 gboolean           with_display); */
end_comment

begin_function_decl
name|GimpContext
modifier|*
name|gimp_create_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|template
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_standard_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_default_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_default_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_user_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_user_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_current_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_get_current_context
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_H__ */
end_comment

end_unit

