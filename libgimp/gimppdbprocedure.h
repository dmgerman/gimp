begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdbprocedure.h  * Copyright (C) 2019 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_PROCEDURE_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_PROCEDURE_H__
define|#
directive|define
name|__GIMP_PDB_PROCEDURE_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PDB_PROCEDURE
define|#
directive|define
name|GIMP_TYPE_PDB_PROCEDURE
value|(_gimp_pdb_procedure_get_type ())
end_define

begin_define
DECL|macro|GIMP_PDB_PROCEDURE (obj)
define|#
directive|define
name|GIMP_PDB_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PDB_PROCEDURE, GimpPDBProcedure))
end_define

begin_define
DECL|macro|GIMP_PDB_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_PDB_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PDB_PROCEDURE, GimpPDBProcedureClass))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_PROCEDURE (obj)
define|#
directive|define
name|GIMP_IS_PDB_PROCEDURE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PDB_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_PROCEDURE_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PDB_PROCEDURE_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PDB_PROCEDURE))
end_define

begin_define
DECL|macro|GIMP_PDB_PROCEDURE_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PDB_PROCEDURE_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PDB_PROCEDURE, GimpPDBProcedureClass))
end_define

begin_typedef
DECL|typedef|GimpPDBProcedure
typedef|typedef
name|struct
name|_GimpPDBProcedure
name|GimpPDBProcedure
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPDBProcedureClass
typedef|typedef
name|struct
name|_GimpPDBProcedureClass
name|GimpPDBProcedureClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPDBProcedurePrivate
typedef|typedef
name|struct
name|_GimpPDBProcedurePrivate
name|GimpPDBProcedurePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPDBProcedure
struct|struct
name|_GimpPDBProcedure
block|{
DECL|member|parent_instance
name|GimpProcedure
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpPDBProcedurePrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPDBProcedureClass
struct|struct
name|_GimpPDBProcedureClass
block|{
DECL|member|parent_class
name|GimpProcedureClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|_gimp_pdb_procedure_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpProcedure
modifier|*
name|_gimp_pdb_procedure_new
parameter_list|(
name|GimpPDB
modifier|*
name|pdb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
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
comment|/*  __GIMP_PDB_PROCEDURE_H__  */
end_comment

end_unit

