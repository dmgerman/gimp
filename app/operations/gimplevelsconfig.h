begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimplevelsconfig.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LEVELS_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LEVELS_CONFIG_H__
define|#
directive|define
name|__GIMP_LEVELS_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_LEVELS_CONFIG
define|#
directive|define
name|GIMP_TYPE_LEVELS_CONFIG
value|(gimp_levels_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_LEVELS_CONFIG (obj)
define|#
directive|define
name|GIMP_LEVELS_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfig))
end_define

begin_define
DECL|macro|GIMP_LEVELS_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_LEVELS_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_LEVELS_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_LEVELS_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LEVELS_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_LEVELS_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_LEVELS_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_LEVELS_CONFIG))
end_define

begin_define
DECL|macro|GIMP_LEVELS_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_LEVELS_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfigClass))
end_define

begin_typedef
DECL|typedef|GimpLevelsConfigClass
typedef|typedef
name|struct
name|_GimpLevelsConfigClass
name|GimpLevelsConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpLevelsConfig
struct|struct
name|_GimpLevelsConfig
block|{
DECL|member|parent_instance
name|GimpSettings
name|parent_instance
decl_stmt|;
DECL|member|linear
name|gboolean
name|linear
decl_stmt|;
DECL|member|channel
name|GimpHistogramChannel
name|channel
decl_stmt|;
DECL|member|low_input
name|gdouble
name|low_input
index|[
literal|5
index|]
decl_stmt|;
DECL|member|high_input
name|gdouble
name|high_input
index|[
literal|5
index|]
decl_stmt|;
DECL|member|clamp_input
name|gboolean
name|clamp_input
decl_stmt|;
DECL|member|gamma
name|gdouble
name|gamma
index|[
literal|5
index|]
decl_stmt|;
DECL|member|low_output
name|gdouble
name|low_output
index|[
literal|5
index|]
decl_stmt|;
DECL|member|high_output
name|gdouble
name|high_output
index|[
literal|5
index|]
decl_stmt|;
DECL|member|clamp_output
name|gboolean
name|clamp_output
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpLevelsConfigClass
struct|struct
name|_GimpLevelsConfigClass
block|{
DECL|member|parent_class
name|GimpSettingsClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_levels_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_levels_config_reset_channel
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_levels_config_stretch
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|gboolean
name|is_color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_levels_config_stretch_channel
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogram
modifier|*
name|histogram
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_levels_config_adjust_by_colors
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GimpHistogramChannel
name|channel
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|black
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|gray
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|white
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpCurvesConfig
modifier|*
name|gimp_levels_config_to_curves_config
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_levels_config_load_cruft
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GInputStream
modifier|*
name|input
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_levels_config_save_cruft
parameter_list|(
name|GimpLevelsConfig
modifier|*
name|config
parameter_list|,
name|GOutputStream
modifier|*
name|output
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LEVELS_CONFIG_H__ */
end_comment

end_unit

