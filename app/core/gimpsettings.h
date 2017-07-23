begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpsettings.h  * Copyright (C) 2008 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_SETTINGS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_SETTINGS_H__
define|#
directive|define
name|__GIMP_SETTINGS_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewable.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SETTINGS
define|#
directive|define
name|GIMP_TYPE_SETTINGS
value|(gimp_settings_get_type ())
end_define

begin_define
DECL|macro|GIMP_SETTINGS (obj)
define|#
directive|define
name|GIMP_SETTINGS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SETTINGS, GimpSettings))
end_define

begin_define
DECL|macro|GIMP_SETTINGS_CLASS (klass)
define|#
directive|define
name|GIMP_SETTINGS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_SETTINGS, GimpSettingsClass))
end_define

begin_define
DECL|macro|GIMP_IS_SETTINGS (obj)
define|#
directive|define
name|GIMP_IS_SETTINGS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SETTINGS))
end_define

begin_define
DECL|macro|GIMP_IS_SETTINGS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SETTINGS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_SETTINGS))
end_define

begin_define
DECL|macro|GIMP_SETTINGS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SETTINGS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_SETTINGS, GimpSettingsClass))
end_define

begin_typedef
DECL|typedef|GimpSettingsClass
typedef|typedef
name|struct
name|_GimpSettingsClass
name|GimpSettingsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSettings
struct|struct
name|_GimpSettings
block|{
DECL|member|parent_instance
name|GimpViewable
name|parent_instance
decl_stmt|;
DECL|member|time
name|gint64
name|time
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSettingsClass
struct|struct
name|_GimpSettingsClass
block|{
DECL|member|parent_class
name|GimpViewableClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_settings_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gint
name|gimp_settings_compare
parameter_list|(
name|GimpSettings
modifier|*
name|a
parameter_list|,
name|GimpSettings
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_SETTINGS_H__ */
end_comment

end_unit

