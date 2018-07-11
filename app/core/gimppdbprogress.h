begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdbprogress.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_PROGRESS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_PROGRESS_H__
define|#
directive|define
name|__GIMP_PDB_PROGRESS_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PDB_PROGRESS
define|#
directive|define
name|GIMP_TYPE_PDB_PROGRESS
value|(gimp_pdb_progress_get_type ())
end_define

begin_define
DECL|macro|GIMP_PDB_PROGRESS (obj)
define|#
directive|define
name|GIMP_PDB_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PDB_PROGRESS, GimpPdbProgress))
end_define

begin_define
DECL|macro|GIMP_PDB_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_PDB_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PDB_PROGRESS, GimpPdbProgressClass))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_PROGRESS (obj)
define|#
directive|define
name|GIMP_IS_PDB_PROGRESS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PDB_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_PROGRESS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PDB_PROGRESS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PDB_PROGRESS))
end_define

begin_define
DECL|macro|GIMP_PDB_PROGRESS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PDB_PROGRESS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PDB_PROGRESS, GimpPdbProgressClass))
end_define

begin_typedef
DECL|typedef|GimpPdbProgressClass
typedef|typedef
name|struct
name|_GimpPdbProgressClass
name|GimpPdbProgressClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPdbProgress
struct|struct
name|_GimpPdbProgress
block|{
DECL|member|object
name|GObject
name|object
decl_stmt|;
DECL|member|active
name|gboolean
name|active
decl_stmt|;
DECL|member|value
name|gdouble
name|value
decl_stmt|;
DECL|member|pdb
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
DECL|member|callback_busy
name|gboolean
name|callback_busy
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPdbProgressClass
struct|struct
name|_GimpPdbProgressClass
block|{
DECL|member|parent_class
name|GObjectClass
name|parent_class
decl_stmt|;
DECL|member|progresses
name|GList
modifier|*
name|progresses
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pdb_progress_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpPdbProgress
modifier|*
name|gimp_pdb_progress_get_by_callback
parameter_list|(
name|GimpPdbProgressClass
modifier|*
name|klass
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PDB_PROGRESS_H__ */
end_comment

end_unit

