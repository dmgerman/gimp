begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmotionbuffer.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_MOTION_BUFFER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_MOTION_BUFFER_H__
define|#
directive|define
name|__GIMP_MOTION_BUFFER_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_MOTION_BUFFER
define|#
directive|define
name|GIMP_TYPE_MOTION_BUFFER
value|(gimp_motion_buffer_get_type ())
end_define

begin_define
DECL|macro|GIMP_MOTION_BUFFER (obj)
define|#
directive|define
name|GIMP_MOTION_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_MOTION_BUFFER, GimpMotionBuffer))
end_define

begin_define
DECL|macro|GIMP_MOTION_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_MOTION_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_MOTION_BUFFER, GimpMotionBufferClass))
end_define

begin_define
DECL|macro|GIMP_IS_MOTION_BUFFER (obj)
define|#
directive|define
name|GIMP_IS_MOTION_BUFFER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_MOTION_BUFFER))
end_define

begin_define
DECL|macro|GIMP_IS_MOTION_BUFFER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_MOTION_BUFFER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_MOTION_BUFFER))
end_define

begin_define
DECL|macro|GIMP_MOTION_BUFFER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_MOTION_BUFFER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_MOTION_BUFFER, GimpMotionBufferClass))
end_define

begin_typedef
DECL|typedef|GimpMotionBufferClass
typedef|typedef
name|struct
name|_GimpMotionBufferClass
name|GimpMotionBufferClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMotionBuffer
struct|struct
name|_GimpMotionBuffer
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|last_read_motion_time
name|guint32
name|last_read_motion_time
decl_stmt|;
DECL|member|last_motion_time
name|guint32
name|last_motion_time
decl_stmt|;
comment|/*  previous time of a forwarded motion event  */
DECL|member|last_motion_delta_time
name|gdouble
name|last_motion_delta_time
decl_stmt|;
DECL|member|last_motion_delta_x
name|gdouble
name|last_motion_delta_x
decl_stmt|;
DECL|member|last_motion_delta_y
name|gdouble
name|last_motion_delta_y
decl_stmt|;
DECL|member|last_motion_distance
name|gdouble
name|last_motion_distance
decl_stmt|;
DECL|member|last_coords
name|GimpCoords
name|last_coords
decl_stmt|;
comment|/* last motion event                   */
DECL|member|event_history
name|GArray
modifier|*
name|event_history
decl_stmt|;
DECL|member|event_queue
name|GArray
modifier|*
name|event_queue
decl_stmt|;
DECL|member|event_delay
name|gboolean
name|event_delay
decl_stmt|;
comment|/* TRUE if theres an unsent event in                                  *  the history buffer                                  */
DECL|member|event_delay_timeout
name|gint
name|event_delay_timeout
decl_stmt|;
DECL|member|last_active_state
name|GdkModifierType
name|last_active_state
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMotionBufferClass
struct|struct
name|_GimpMotionBufferClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
DECL|member|motion
name|void
function_decl|(
modifier|*
name|motion
function_decl|)
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_motion_buffer_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpMotionBuffer
modifier|*
name|gimp_motion_buffer_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_motion_buffer_start_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|guint32
name|time
parameter_list|,
name|GimpCoords
modifier|*
name|last_motion
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_motion_buffer_finish_stroke
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_motion_buffer_eval_event
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|gdouble
name|scale_x
parameter_list|,
name|gdouble
name|scale_y
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gboolean
name|event_fill
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_motion_buffer_push_event_history
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_motion_buffer_pop_event_queue
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_motion_buffer_process_event_queue
parameter_list|(
name|GimpMotionBuffer
modifier|*
name|buffer
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|guint32
name|time
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_MOTION_BUFFER_H__ */
end_comment

end_unit

