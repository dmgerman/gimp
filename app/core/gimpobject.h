begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OBJECT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OBJECT_H__
define|#
directive|define
name|__GIMP_OBJECT_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_OBJECT
define|#
directive|define
name|GIMP_TYPE_OBJECT
value|(gimp_object_get_type ())
end_define

begin_define
DECL|macro|GIMP_OBJECT (obj)
define|#
directive|define
name|GIMP_OBJECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OBJECT, GimpObject))
end_define

begin_define
DECL|macro|GIMP_OBJECT_CLASS (klass)
define|#
directive|define
name|GIMP_OBJECT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_OBJECT, GimpObjectClass))
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT (obj)
define|#
directive|define
name|GIMP_IS_OBJECT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OBJECT))
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OBJECT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_OBJECT))
end_define

begin_define
DECL|macro|GIMP_OBJECT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OBJECT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_OBJECT, GimpObjectClass))
end_define

begin_typedef
DECL|typedef|GimpObjectPrivate
typedef|typedef
name|struct
name|_GimpObjectPrivate
name|GimpObjectPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpObjectClass
typedef|typedef
name|struct
name|_GimpObjectClass
name|GimpObjectClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpObject
struct|struct
name|_GimpObject
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpObjectPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpObjectClass
struct|struct
name|_GimpObjectClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
comment|/*  signals  */
DECL|member|disconnect
name|void
function_decl|(
modifier|*
name|disconnect
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
DECL|member|name_changed
name|void
function_decl|(
modifier|*
name|name_changed
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|get_memsize
name|gint64
function_decl|(
modifier|*
name|get_memsize
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_object_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_object_set_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_set_name_safe
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_set_static_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_take_name
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gchar
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_object_get_name
parameter_list|(
name|gconstpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_name_changed
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_name_free
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_object_name_collate
parameter_list|(
name|GimpObject
modifier|*
name|object1
parameter_list|,
name|GimpObject
modifier|*
name|object2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_object_get_memsize
parameter_list|(
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OBJECT_H__ */
end_comment

end_unit

