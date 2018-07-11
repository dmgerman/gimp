begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__PLUG_IN_ENUMS_H__
end_ifndef

begin_define
DECL|macro|__PLUG_IN_ENUMS_H__
define|#
directive|define
name|__PLUG_IN_ENUMS_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PLUG_IN_IMAGE_TYPE
define|#
directive|define
name|GIMP_TYPE_PLUG_IN_IMAGE_TYPE
value|(gimp_plug_in_image_type_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_plug_in_image_type_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c2a48770103
block|{
DECL|enumerator|GIMP_PLUG_IN_RGB_IMAGE
name|GIMP_PLUG_IN_RGB_IMAGE
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_PLUG_IN_GRAY_IMAGE
name|GIMP_PLUG_IN_GRAY_IMAGE
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_PLUG_IN_INDEXED_IMAGE
name|GIMP_PLUG_IN_INDEXED_IMAGE
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_PLUG_IN_RGBA_IMAGE
name|GIMP_PLUG_IN_RGBA_IMAGE
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_PLUG_IN_GRAYA_IMAGE
name|GIMP_PLUG_IN_GRAYA_IMAGE
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_PLUG_IN_INDEXEDA_IMAGE
name|GIMP_PLUG_IN_INDEXEDA_IMAGE
init|=
literal|1
operator|<<
literal|5
DECL|typedef|GimpPlugInImageType
block|}
name|GimpPlugInImageType
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_PLUG_CALL_MODE
define|#
directive|define
name|GIMP_TYPE_PLUG_CALL_MODE
value|(gimp_plug_in_call_mode_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_plug_in_call_mode_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c2a48770203
block|{
DECL|enumerator|GIMP_PLUG_IN_CALL_NONE
name|GIMP_PLUG_IN_CALL_NONE
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_RUN
name|GIMP_PLUG_IN_CALL_RUN
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_QUERY
name|GIMP_PLUG_IN_CALL_QUERY
block|,
DECL|enumerator|GIMP_PLUG_IN_CALL_INIT
name|GIMP_PLUG_IN_CALL_INIT
DECL|typedef|GimpPlugInCallMode
block|}
name|GimpPlugInCallMode
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_FILE_PROCEDURE_GROUP
define|#
directive|define
name|GIMP_TYPE_FILE_PROCEDURE_GROUP
value|(gimp_file_procedure_group_get_type ())
end_define

begin_decl_stmt
name|GType
name|gimp_file_procedure_group_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2c2a48770303
block|{
DECL|enumerator|GIMP_FILE_PROCEDURE_GROUP_NONE
name|GIMP_FILE_PROCEDURE_GROUP_NONE
block|,
DECL|enumerator|GIMP_FILE_PROCEDURE_GROUP_ANY
name|GIMP_FILE_PROCEDURE_GROUP_ANY
block|,
DECL|enumerator|GIMP_FILE_PROCEDURE_GROUP_OPEN
name|GIMP_FILE_PROCEDURE_GROUP_OPEN
block|,
DECL|enumerator|GIMP_FILE_PROCEDURE_GROUP_SAVE
name|GIMP_FILE_PROCEDURE_GROUP_SAVE
block|,
DECL|enumerator|GIMP_FILE_PROCEDURE_GROUP_EXPORT
name|GIMP_FILE_PROCEDURE_GROUP_EXPORT
DECL|typedef|GimpFileProcedureGroup
block|}
name|GimpFileProcedureGroup
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __PLUG_IN_ENUMS_H__ */
end_comment

end_unit

