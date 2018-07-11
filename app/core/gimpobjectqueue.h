begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OBJECT_QUEUE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OBJECT_QUEUE_H__
define|#
directive|define
name|__GIMP_OBJECT_QUEUE_H__
end_define

begin_include
include|#
directive|include
file|"gimpsubprogress.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OBJECT_QUEUE
define|#
directive|define
name|GIMP_TYPE_OBJECT_QUEUE
value|(gimp_object_queue_get_type ())
end_define

begin_define
DECL|macro|GIMP_OBJECT_QUEUE (obj)
define|#
directive|define
name|GIMP_OBJECT_QUEUE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OBJECT_QUEUE, GimpObjectQueue))
end_define

begin_define
DECL|macro|GIMP_OBJECT_QUEUE_CLASS (klass)
define|#
directive|define
name|GIMP_OBJECT_QUEUE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_OBJECT_QUEUE, GimpObjectQueueClass))
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT_QUEUE (obj)
define|#
directive|define
name|GIMP_IS_OBJECT_QUEUE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OBJECT_QUEUE))
end_define

begin_define
DECL|macro|GIMP_IS_OBJECT_QUEUE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OBJECT_QUEUE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_OBJECT_QUEUE))
end_define

begin_define
DECL|macro|GIMP_OBJECT_QUEUE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OBJECT_QUEUE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_OBJECT_QUEUE, GimpObjectQueueClass))
end_define

begin_typedef
DECL|typedef|GimpObjectQueueClass
typedef|typedef
name|struct
name|_GimpObjectQueueClass
name|GimpObjectQueueClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpObjectQueue
struct|struct
name|_GimpObjectQueue
block|{
DECL|member|parent_instance
name|GimpSubProgress
name|parent_instance
decl_stmt|;
DECL|member|items
name|GQueue
name|items
decl_stmt|;
DECL|member|processed_memsize
name|gint64
name|processed_memsize
decl_stmt|;
DECL|member|total_memsize
name|gint64
name|total_memsize
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpObjectQueueClass
struct|struct
name|_GimpObjectQueueClass
block|{
DECL|member|parent_class
name|GimpSubProgressClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_object_queue_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpObjectQueue
modifier|*
name|gimp_object_queue_new
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_queue_clear
parameter_list|(
name|GimpObjectQueue
modifier|*
name|queue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_queue_push
parameter_list|(
name|GimpObjectQueue
modifier|*
name|queue
parameter_list|,
name|gpointer
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_queue_push_container
parameter_list|(
name|GimpObjectQueue
modifier|*
name|queue
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_object_queue_push_list
parameter_list|(
name|GimpObjectQueue
modifier|*
name|queue
parameter_list|,
name|GList
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gpointer
name|gimp_object_queue_pop
parameter_list|(
name|GimpObjectQueue
modifier|*
name|queue
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OBJECT_QUEUE_H__ */
end_comment

end_unit

