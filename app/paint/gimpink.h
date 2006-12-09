begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_INK_H__
end_ifndef

begin_define
DECL|macro|__GIMP_INK_H__
define|#
directive|define
name|__GIMP_INK_H__
end_define

begin_include
include|#
directive|include
file|"gimppaintcore.h"
end_include

begin_include
include|#
directive|include
file|"gimpink-blob.h"
end_include

begin_define
DECL|macro|DIST_SMOOTHER_BUFFER
define|#
directive|define
name|DIST_SMOOTHER_BUFFER
value|10
end_define

begin_define
DECL|macro|TIME_SMOOTHER_BUFFER
define|#
directive|define
name|TIME_SMOOTHER_BUFFER
value|10
end_define

begin_define
DECL|macro|GIMP_TYPE_INK
define|#
directive|define
name|GIMP_TYPE_INK
value|(gimp_ink_get_type ())
end_define

begin_define
DECL|macro|GIMP_INK (obj)
define|#
directive|define
name|GIMP_INK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_INK, GimpInk))
end_define

begin_define
DECL|macro|GIMP_INK_CLASS (klass)
define|#
directive|define
name|GIMP_INK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_INK, GimpInkClass))
end_define

begin_define
DECL|macro|GIMP_IS_INK (obj)
define|#
directive|define
name|GIMP_IS_INK
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_INK))
end_define

begin_define
DECL|macro|GIMP_IS_INK_CLASS (klass)
define|#
directive|define
name|GIMP_IS_INK_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_INK))
end_define

begin_define
DECL|macro|GIMP_INK_GET_CLASS (obj)
define|#
directive|define
name|GIMP_INK_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_INK, GimpInkClass))
end_define

begin_typedef
DECL|typedef|GimpInk
typedef|typedef
name|struct
name|_GimpInk
name|GimpInk
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpInkClass
typedef|typedef
name|struct
name|_GimpInkClass
name|GimpInkClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpInk
struct|struct
name|_GimpInk
block|{
DECL|member|parent_instance
name|GimpPaintCore
name|parent_instance
decl_stmt|;
DECL|member|start_blob
name|Blob
modifier|*
name|start_blob
decl_stmt|;
comment|/*  starting blob (for undo)       */
DECL|member|cur_blob
name|Blob
modifier|*
name|cur_blob
decl_stmt|;
comment|/*  current blob                   */
DECL|member|last_blob
name|Blob
modifier|*
name|last_blob
decl_stmt|;
comment|/*  blob for last cursor position  */
comment|/* circular distance history buffer */
DECL|member|dt_buffer
name|gdouble
name|dt_buffer
index|[
name|DIST_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|dt_index
name|gint
name|dt_index
decl_stmt|;
comment|/* circular timing history buffer */
DECL|member|ts_buffer
name|guint32
name|ts_buffer
index|[
name|TIME_SMOOTHER_BUFFER
index|]
decl_stmt|;
DECL|member|ts_index
name|gint
name|ts_index
decl_stmt|;
DECL|member|last_time
name|guint32
name|last_time
decl_stmt|;
comment|/*  previous time of a motion event  */
DECL|member|init_velocity
name|gboolean
name|init_velocity
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpInkClass
struct|struct
name|_GimpInkClass
block|{
DECL|member|parent_class
name|GimpPaintCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_ink_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
name|callback
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GType
name|gimp_ink_get_type
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
comment|/*  __GIMP_INK_H__  */
end_comment

end_unit

