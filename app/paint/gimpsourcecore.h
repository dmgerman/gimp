begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CLONE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CLONE_H__
define|#
directive|define
name|__GIMP_CLONE_H__
end_define

begin_include
include|#
directive|include
file|"gimpbrushcore.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CLONE
define|#
directive|define
name|GIMP_TYPE_CLONE
value|(gimp_clone_get_type ())
end_define

begin_define
DECL|macro|GIMP_CLONE (obj)
define|#
directive|define
name|GIMP_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CLONE, GimpClone))
end_define

begin_define
DECL|macro|GIMP_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CLONE, GimpCloneClass))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE (obj)
define|#
directive|define
name|GIMP_IS_CLONE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CLONE))
end_define

begin_define
DECL|macro|GIMP_IS_CLONE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CLONE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CLONE))
end_define

begin_define
DECL|macro|GIMP_CLONE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CLONE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CLONE, GimpCloneClass))
end_define

begin_typedef
DECL|typedef|GimpClone
typedef|typedef
name|struct
name|_GimpClone
name|GimpClone
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCloneClass
typedef|typedef
name|struct
name|_GimpCloneClass
name|GimpCloneClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpClone
struct|struct
name|_GimpClone
block|{
DECL|member|parent_instance
name|GimpBrushCore
name|parent_instance
decl_stmt|;
DECL|member|set_source
name|gboolean
name|set_source
decl_stmt|;
DECL|member|src_pickable
name|GimpPickable
modifier|*
name|src_pickable
decl_stmt|;
DECL|member|src_x
name|gint
name|src_x
decl_stmt|;
DECL|member|src_y
name|gint
name|src_y
decl_stmt|;
DECL|member|orig_src_x
name|gint
name|orig_src_x
decl_stmt|;
DECL|member|orig_src_y
name|gint
name|orig_src_y
decl_stmt|;
DECL|member|offset_x
name|gint
name|offset_x
decl_stmt|;
DECL|member|offset_y
name|gint
name|offset_y
decl_stmt|;
DECL|member|first_stroke
name|gboolean
name|first_stroke
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCloneClass
struct|struct
name|_GimpCloneClass
block|{
DECL|member|parent_class
name|GimpBrushCoreClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_clone_register
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
name|gimp_clone_get_type
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
comment|/*  __GIMP_CLONE_H__  */
end_comment

end_unit

