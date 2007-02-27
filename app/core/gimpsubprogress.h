begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SUB_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SUB_PROGRESS_H__
define|#
directive|define
name|__GIMP_SUB_PROGRESS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_SUB_PROGRESS
define|#
directive|define
name|GIMP_TYPE_SUB_PROGRESS
value|(gimp_sub_progress_get_type ())
end_define

begin_define
DECL|macro|GIMP_SUB_PROGRESS (obj)
define|#
directive|define
name|GIMP_SUB_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SUB_PROGRESS, GimpSubProgress))
end_define

begin_define
DECL|macro|GIMP_SUB_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_SUB_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SUB_PROGRESS, GimpSubProgressClass))
end_define

begin_define
DECL|macro|GIMP_IS_SUB_PROGRESS (obj)
define|#
directive|define
name|GIMP_IS_SUB_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SUB_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_IS_SUB_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SUB_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SUB_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_SUB_PROGRESS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SUB_PROGRESS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SUB_PROGRESS, GimpSubProgressClass))
end_define

begin_typedef
DECL|typedef|GimpSubProgressClass
typedef|typedef
name|struct
name|_GimpSubProgressClass
name|GimpSubProgressClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSubProgress
struct|struct
name|_GimpSubProgress
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|progress
name|GimpProgress
modifier|*
name|progress
decl_stmt|;
DECL|member|start
name|gdouble
name|start
decl_stmt|;
DECL|member|end
name|gdouble
name|end
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSubProgressClass
struct|struct
name|_GimpSubProgressClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_sub_progress_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProgress
modifier|*
name|gimp_sub_progress_new
parameter_list|(
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_sub_progress_set_range
parameter_list|(
name|GimpSubProgress
modifier|*
name|progress
parameter_list|,
name|gdouble
name|start
parameter_list|,
name|gdouble
name|end
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_sub_progress_set_steps
parameter_list|(
name|GimpSubProgress
modifier|*
name|progress
parameter_list|,
name|gint
name|num
parameter_list|,
name|gint
name|steps
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SUB_PROGRESS_H__ */
end_comment

end_unit

