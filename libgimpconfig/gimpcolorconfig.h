begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorConfig class  * Copyright (C) 2004  Stefan DÃ¶hla<stefan@doehla.de>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_CONFIG_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_CONFIG_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimpconfig/gimpconfig.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

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
comment|/*< public>*/
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
DECL|member|simulation_gamut_check
name|gboolean
name|simulation_gamut_check
decl_stmt|;
DECL|member|out_of_gamut_color
name|GimpRGB
name|out_of_gamut_color
decl_stmt|;
comment|/*< private>*/
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved5
name|void
function_decl|(
modifier|*
name|_gimp_reserved5
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved6
name|void
function_decl|(
modifier|*
name|_gimp_reserved6
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved7
name|void
function_decl|(
modifier|*
name|_gimp_reserved7
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved8
name|void
function_decl|(
modifier|*
name|_gimp_reserved8
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
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

