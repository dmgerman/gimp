begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpmeter.h  * Copyright (C) 2017 Ell  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_METER_H__
end_ifndef

begin_define
DECL|macro|__GIMP_METER_H__
define|#
directive|define
name|__GIMP_METER_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_METER
define|#
directive|define
name|GIMP_TYPE_METER
value|(gimp_meter_get_type ())
end_define

begin_define
DECL|macro|GIMP_METER (obj)
define|#
directive|define
name|GIMP_METER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_METER, GimpMeter))
end_define

begin_define
DECL|macro|GIMP_METER_CLASS (klass)
define|#
directive|define
name|GIMP_METER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_METER, GimpMeterClass))
end_define

begin_define
DECL|macro|GIMP_IS_METER (obj)
define|#
directive|define
name|GIMP_IS_METER
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE (obj, GIMP_TYPE_METER))
end_define

begin_define
DECL|macro|GIMP_IS_METER_CLASS (klass)
define|#
directive|define
name|GIMP_IS_METER_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_METER))
end_define

begin_define
DECL|macro|GIMP_METER_GET_CLASS (obj)
define|#
directive|define
name|GIMP_METER_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_METER, GimpMeterClass))
end_define

begin_typedef
DECL|typedef|GimpMeterPrivate
typedef|typedef
name|struct
name|_GimpMeterPrivate
name|GimpMeterPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpMeterClass
typedef|typedef
name|struct
name|_GimpMeterClass
name|GimpMeterClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpMeter
struct|struct
name|_GimpMeter
block|{
DECL|member|parent_instance
name|GtkWidget
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpMeterPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpMeterClass
struct|struct
name|_GimpMeterClass
block|{
DECL|member|parent_class
name|GtkWidgetClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_meter_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_meter_new
parameter_list|(
name|gint
name|n_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_size
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_meter_get_size
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_refresh_rate
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gdouble
name|rate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_meter_get_refresh_rate
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_range
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gdouble
name|min
parameter_list|,
name|gdouble
name|max
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_meter_get_range_min
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_meter_get_range_max
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_n_values
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|n_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_meter_get_n_values
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_value_active
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_meter_get_value_active
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_value_show_in_gauge
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_meter_get_value_show_in_gauge
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_value_show_in_history
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|,
name|gboolean
name|show
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_meter_get_value_show_in_history
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_value_color
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpRGB
modifier|*
name|gimp_meter_get_value_color
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_value_interpolation
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|,
name|GimpInterpolationType
name|interpolation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpInterpolationType
name|gimp_meter_get_value_interpolation
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_history_visible
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_meter_get_history_visible
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_history_duration
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gdouble
name|duration
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_meter_get_history_duration
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_history_resolution
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gdouble
name|resolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|gimp_meter_get_history_resolution
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_clear_history
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_add_sample
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
specifier|const
name|gdouble
modifier|*
name|sample
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_led_active
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
name|gboolean
name|active
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_meter_get_led_active
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_meter_set_led_color
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpRGB
modifier|*
name|gimp_meter_get_led_color
parameter_list|(
name|GimpMeter
modifier|*
name|meter
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_METER_H__ */
end_comment

end_unit

