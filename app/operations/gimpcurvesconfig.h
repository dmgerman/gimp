begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcurvesconfig.h  * Copyright (C) 2007 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURVES_CONFIG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURVES_CONFIG_H__
define|#
directive|define
name|__GIMP_CURVES_CONFIG_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpsettings.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURVES_CONFIG
define|#
directive|define
name|GIMP_TYPE_CURVES_CONFIG
value|(gimp_curves_config_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURVES_CONFIG (obj)
define|#
directive|define
name|GIMP_CURVES_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURVES_CONFIG, GimpCurvesConfig))
end_define

begin_define
DECL|macro|GIMP_CURVES_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_CURVES_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_CURVES_CONFIG, GimpCurvesConfigClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_CONFIG (obj)
define|#
directive|define
name|GIMP_IS_CURVES_CONFIG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURVES_CONFIG))
end_define

begin_define
DECL|macro|GIMP_IS_CURVES_CONFIG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURVES_CONFIG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_CURVES_CONFIG))
end_define

begin_define
DECL|macro|GIMP_CURVES_CONFIG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CURVES_CONFIG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_CURVES_CONFIG, GimpCurvesConfigClass))
end_define

begin_typedef
DECL|typedef|GimpCurvesConfigClass
typedef|typedef
name|struct
name|_GimpCurvesConfigClass
name|GimpCurvesConfigClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCurvesConfig
struct|struct
name|_GimpCurvesConfig
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
DECL|member|curve
name|GimpCurve
modifier|*
name|curve
index|[
literal|5
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCurvesConfigClass
struct|struct
name|_GimpCurvesConfigClass
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
name|gimp_curves_config_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GObject
modifier|*
name|gimp_curves_config_new_spline
parameter_list|(
name|gint32
name|channel
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GObject
modifier|*
name|gimp_curves_config_new_explicit
parameter_list|(
name|gint32
name|channel
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|samples
parameter_list|,
name|gint
name|n_samples
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GObject
modifier|*
name|gimp_curves_config_new_spline_cruft
parameter_list|(
name|gint32
name|channel
parameter_list|,
specifier|const
name|guint8
modifier|*
name|points
parameter_list|,
name|gint
name|n_points
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GObject
modifier|*
name|gimp_curves_config_new_explicit_cruft
parameter_list|(
name|gint32
name|channel
parameter_list|,
specifier|const
name|guint8
modifier|*
name|samples
parameter_list|,
name|gint
name|n_samples
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_curves_config_reset_channel
parameter_list|(
name|GimpCurvesConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_curves_config_load_cruft
parameter_list|(
name|GimpCurvesConfig
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
name|gimp_curves_config_save_cruft
parameter_list|(
name|GimpCurvesConfig
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
comment|/* __GIMP_CURVES_CONFIG_H__ */
end_comment

end_unit

