begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpCoreConfig class  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CORE_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CORE_CONFIG_H__
define|#
directive|define
name|__GIMP_CORE_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/core-enums.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpbaseconfig.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CORE_CONFIG
define|#
directive|define
name|GIMP_TYPE_CORE_CONFIG
value|(gimp_core_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_CORE_CONFIG (obj)
define|#
directive|define
name|GIMP_CORE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CORE_CONFIG, GimpCoreConfig))
end_define

begin_define
DECL|macro|GIMP_CORE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_CORE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CORE_CONFIG, GimpCoreConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_CORE_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_CORE_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CORE_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_CORE_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CORE_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CORE_CONFIG))
end_define

begin_typedef
DECL|typedef|GimpCoreConfig
typedef|typedef
name|struct
name|_GimpCoreConfig
name|GimpCoreConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCoreConfigClass
typedef|typedef
name|struct
name|_GimpCoreConfigClass
name|GimpCoreConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCoreConfig
struct|struct
name|_GimpCoreConfig
block|{
DECL|member|parent_instance
name|GimpBaseConfig
name|parent_instance
decl_stmt|;
DECL|member|plug_in_path
name|gchar
modifier|*
name|plug_in_path
decl_stmt|;
DECL|member|module_path
name|gchar
modifier|*
name|module_path
decl_stmt|;
DECL|member|brush_path
name|gchar
modifier|*
name|brush_path
decl_stmt|;
DECL|member|pattern_path
name|gchar
modifier|*
name|pattern_path
decl_stmt|;
DECL|member|palette_path
name|gchar
modifier|*
name|palette_path
decl_stmt|;
DECL|member|gradient_path
name|gchar
modifier|*
name|gradient_path
decl_stmt|;
DECL|member|default_brush
name|gchar
modifier|*
name|default_brush
decl_stmt|;
DECL|member|default_pattern
name|gchar
modifier|*
name|default_pattern
decl_stmt|;
DECL|member|default_palette
name|gchar
modifier|*
name|default_palette
decl_stmt|;
DECL|member|default_gradient
name|gchar
modifier|*
name|default_gradient
decl_stmt|;
DECL|member|default_comment
name|gchar
modifier|*
name|default_comment
decl_stmt|;
DECL|member|default_image_type
name|GimpImageBaseType
name|default_image_type
decl_stmt|;
DECL|member|default_image_width
name|gint
name|default_image_width
decl_stmt|;
DECL|member|default_image_height
name|gint
name|default_image_height
decl_stmt|;
DECL|member|default_unit
name|GimpUnit
name|default_unit
decl_stmt|;
DECL|member|default_xresolution
name|gdouble
name|default_xresolution
decl_stmt|;
DECL|member|default_yresolution
name|gdouble
name|default_yresolution
decl_stmt|;
DECL|member|default_resolution_unit
name|GimpUnit
name|default_resolution_unit
decl_stmt|;
DECL|member|levels_of_undo
name|gint
name|levels_of_undo
decl_stmt|;
DECL|member|plug_in_rc_path
name|gchar
modifier|*
name|plug_in_rc_path
decl_stmt|;
DECL|member|module_load_inhibit
name|gchar
modifier|*
name|module_load_inhibit
decl_stmt|;
DECL|member|preview_size
name|GimpPreviewSize
name|preview_size
decl_stmt|;
DECL|member|write_thumbnails
name|gboolean
name|write_thumbnails
decl_stmt|;
DECL|member|gamma_val
name|gdouble
name|gamma_val
decl_stmt|;
DECL|member|install_cmap
name|gboolean
name|install_cmap
decl_stmt|;
DECL|member|min_colors
name|gint
name|min_colors
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCoreConfigClass
struct|struct
name|_GimpCoreConfigClass
block|{
DECL|member|parent_class
name|GimpBaseConfigClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_core_config_get_type
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
comment|/* GIMP_CORE_CONFIG_H__ */
end_comment

end_unit

