begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpDialogConfig class  * Copyright (C) 2016  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DIALOG_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DIALOG_CONFIG_H__
define|#
directive|define
name|__GIMP_DIALOG_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_DIALOG_CONFIG
define|#
directive|define
name|GIMP_TYPE_DIALOG_CONFIG
value|(gimp_dialog_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_DIALOG_CONFIG (obj)
define|#
directive|define
name|GIMP_DIALOG_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DIALOG_CONFIG, GimpDialogConfig))
end_define

begin_define
DECL|macro|GIMP_DIALOG_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_DIALOG_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DIALOG_CONFIG, GimpDialogConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_DIALOG_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DIALOG_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DIALOG_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DIALOG_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpDialogConfigClass
typedef|typedef
name|struct
name|_GimpDialogConfigClass
name|GimpDialogConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDialogConfig
struct|struct
name|_GimpDialogConfig
block|{
DECL|member|parent_instance
name|GimpGuiConfig
name|parent_instance
decl_stmt|;
DECL|member|color_profile_policy
name|GimpColorProfilePolicy
name|color_profile_policy
decl_stmt|;
DECL|member|layer_add_mask_type
name|GimpAddMaskType
name|layer_add_mask_type
decl_stmt|;
DECL|member|layer_add_mask_invert
name|gboolean
name|layer_add_mask_invert
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDialogConfigClass
struct|struct
name|_GimpDialogConfigClass
block|{
DECL|member|parent_class
name|GimpGuiConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dialog_config_get_type
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
comment|/* GIMP_DIALOG_CONFIG_H__ */
end_comment

end_unit

