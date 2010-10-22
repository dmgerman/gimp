begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

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
name|GimpBlob
modifier|*
name|start_blob
decl_stmt|;
comment|/*  starting blob (for undo)       */
DECL|member|cur_blob
name|GimpBlob
modifier|*
name|cur_blob
decl_stmt|;
comment|/*  current blob                   */
DECL|member|last_blob
name|GimpBlob
modifier|*
name|last_blob
decl_stmt|;
comment|/*  blob for last cursor position  */
DECL|member|queue
name|GimpCircularQueue
modifier|*
name|queue
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

