begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorConfig class  * Copyright (C) 2004  Stefan DÃ¶hla<stefan@doehla.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_CONFIG_H__
define|#
directive|define
name|__GIMP_COLOR_CONFIG_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_CONFIG
define|#
directive|define
name|GIMP_TYPE_COLOR_CONFIG
value|(gimp_color_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_CONFIG (obj)
define|#
directive|define
name|GIMP_COLOR_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_CONFIG, GimpColorConfig))
end_define

begin_define
DECL|macro|GIMP_COLOR_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_CONFIG, GimpColorConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_COLOR_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpColorConfigClass
typedef|typedef
name|struct
name|_GimpColorConfigClass
name|GimpColorConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorConfig
struct|struct
name|_GimpColorConfig
block|{
DECL|member|parent_instance
name|GObject
name|parent_instance
decl_stmt|;
DECL|member|mode
name|GimpColorManagementMode
name|mode
decl_stmt|;
DECL|member|rgb_profile
name|gchar
modifier|*
name|rgb_profile
decl_stmt|;
DECL|member|cmyk_profile
name|gchar
modifier|*
name|cmyk_profile
decl_stmt|;
DECL|member|display_profile
name|gchar
modifier|*
name|display_profile
decl_stmt|;
DECL|member|display_profile_from_gdk
name|gboolean
name|display_profile_from_gdk
decl_stmt|;
DECL|member|printer_profile
name|gchar
modifier|*
name|printer_profile
decl_stmt|;
DECL|member|display_intent
name|GimpColorRenderingIntent
name|display_intent
decl_stmt|;
DECL|member|simulation_intent
name|GimpColorRenderingIntent
name|simulation_intent
decl_stmt|;
DECL|member|display_module
name|gchar
modifier|*
name|display_module
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorConfigClass
struct|struct
name|_GimpColorConfigClass
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
name|gimp_color_config_get_type
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
comment|/* GIMP_COLOR_CONFIG_H__ */
end_comment

end_unit

