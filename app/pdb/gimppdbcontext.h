begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimppdbcontext.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_CONTEXT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_CONTEXT_H__
define|#
directive|define
name|__GIMP_PDB_CONTEXT_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_PDB_CONTEXT
define|#
directive|define
name|GIMP_TYPE_PDB_CONTEXT
value|(gimp_pdb_context_get_type ())
end_define

begin_define
DECL|macro|GIMP_PDB_CONTEXT (obj)
define|#
directive|define
name|GIMP_PDB_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PDB_CONTEXT, GimpPDBContext))
end_define

begin_define
DECL|macro|GIMP_PDB_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_PDB_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PDB_CONTEXT, GimpPDBContextClass))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_CONTEXT (obj)
define|#
directive|define
name|GIMP_IS_PDB_CONTEXT
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PDB_CONTEXT))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_CONTEXT_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PDB_CONTEXT_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PDB_CONTEXT))
end_define

begin_define
DECL|macro|GIMP_PDB_CONTEXT_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PDB_CONTEXT_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PDB_CONTEXT, GimpPDBContextClass))
end_define

begin_typedef
DECL|typedef|GimpPDBContext
typedef|typedef
name|struct
name|_GimpPDBContext
name|GimpPDBContext
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPDBContextClass
typedef|typedef
name|struct
name|_GimpPDBContextClass
name|GimpPDBContextClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPDBContext
struct|struct
name|_GimpPDBContext
block|{
DECL|member|parent_instance
name|GimpContext
name|parent_instance
decl_stmt|;
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|feather
name|gboolean
name|feather
decl_stmt|;
DECL|member|feather_radius_x
name|gdouble
name|feather_radius_x
decl_stmt|;
DECL|member|feather_radius_y
name|gdouble
name|feather_radius_y
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|sample_criterion
name|GimpSelectCriterion
name|sample_criterion
decl_stmt|;
DECL|member|sample_threshold
name|gdouble
name|sample_threshold
decl_stmt|;
DECL|member|interpolation
name|GimpInterpolationType
name|interpolation
decl_stmt|;
DECL|member|transform_direction
name|GimpTransformDirection
name|transform_direction
decl_stmt|;
DECL|member|transform_resize
name|GimpTransformResize
name|transform_resize
decl_stmt|;
DECL|member|transform_recursion
name|gint
name|transform_recursion
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPDBContextClass
struct|struct
name|_GimpPDBContextClass
block|{
DECL|member|parent_class
name|GimpContextClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pdb_context_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContext
modifier|*
name|gimp_pdb_context_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|parent
parameter_list|,
name|gboolean
name|set_parent
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PDB_CONTEXT_H__  */
end_comment

end_unit

