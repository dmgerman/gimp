begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_ERROR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_ERROR_H__
define|#
directive|define
name|__GIMP_PDB_ERROR_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2af616080103
block|{
DECL|enumerator|GIMP_PDB_ERROR_FAILED
name|GIMP_PDB_ERROR_FAILED
block|,
comment|/* generic error condition */
DECL|enumerator|GIMP_PDB_ERROR_CANCELLED
name|GIMP_PDB_ERROR_CANCELLED
block|,
DECL|enumerator|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
name|GIMP_PDB_ERROR_PROCEDURE_NOT_FOUND
block|,
DECL|enumerator|GIMP_PDB_ERROR_INVALID_ARGUMENT
name|GIMP_PDB_ERROR_INVALID_ARGUMENT
block|,
DECL|enumerator|GIMP_PDB_ERROR_INVALID_RETURN_VALUE
name|GIMP_PDB_ERROR_INVALID_RETURN_VALUE
block|,
DECL|enumerator|GIMP_PDB_ERROR_INTERNAL_ERROR
name|GIMP_PDB_ERROR_INTERNAL_ERROR
DECL|typedef|GimpPdbErrorCode
block|}
name|GimpPdbErrorCode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_PDB_ERROR
define|#
directive|define
name|GIMP_PDB_ERROR
value|(gimp_pdb_error_quark ())
end_define

begin_decl_stmt
name|GQuark
name|gimp_pdb_error_quark
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
comment|/* __GIMP_PDB_ERROR_H__ */
end_comment

end_unit

