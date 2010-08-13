begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpoperationcagepreview.h  * Copyright (C) 2010 Michael MurÃ©<batolettre@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OPERATION_CAGE_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OPERATION_CAGE_PREVIEW_H__
define|#
directive|define
name|__GIMP_OPERATION_CAGE_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|<gegl-plugin.h>
end_include

begin_include
include|#
directive|include
file|<operation/gegl-operation-composer.h>
end_include

begin_enum
enum|enum
DECL|enum|__anon2c52b6260103
block|{
DECL|enumerator|GIMP_OPERATION_CAGE_PREVIEW_PROP_0
name|GIMP_OPERATION_CAGE_PREVIEW_PROP_0
block|,
DECL|enumerator|GIMP_OPERATION_CAGE_PREVIEW_PROP_CONFIG
name|GIMP_OPERATION_CAGE_PREVIEW_PROP_CONFIG
block|}
enum|;
end_enum

begin_define
DECL|macro|GIMP_TYPE_OPERATION_CAGE_PREVIEW
define|#
directive|define
name|GIMP_TYPE_OPERATION_CAGE_PREVIEW
value|(gimp_operation_cage_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_PREVIEW (obj)
define|#
directive|define
name|GIMP_OPERATION_CAGE_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OPERATION_CAGE_PREVIEW, GimpOperationCagePreview))
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_OPERATION_CAGE_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_OPERATION_CAGE_PREVIEW, GimpOperationCagePreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_CAGE_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_OPERATION_CAGE_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OPERATION_CAGE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_OPERATION_CAGE_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OPERATION_CAGE_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_OPERATION_CAGE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_OPERATION_CAGE_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OPERATION_CAGE_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_OPERATION_CAGE_PREVIEW, GimpOperationCagePreviewClass))
end_define

begin_typedef
DECL|typedef|GimpOperationCagePreviewClass
typedef|typedef
name|struct
name|_GimpOperationCagePreviewClass
name|GimpOperationCagePreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOperationCagePreview
struct|struct
name|_GimpOperationCagePreview
block|{
DECL|member|parent_instance
name|GeglOperationComposer
name|parent_instance
decl_stmt|;
DECL|member|config
name|GimpCageConfig
modifier|*
name|config
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOperationCagePreviewClass
struct|struct
name|_GimpOperationCagePreviewClass
block|{
DECL|member|parent_class
name|GeglOperationComposerClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_operation_cage_preview_get_type
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
comment|/* __GIMP_OPERATION_CAGE_PREVIEW_H__ */
end_comment

end_unit

