begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_UTILS_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_UTILS_H__
define|#
directive|define
name|__APP_GIMP_UTILS_H__
end_define

begin_define
DECL|macro|GIMP_TIMER_START ()
define|#
directive|define
name|GIMP_TIMER_START
parameter_list|()
define|\
value|{ GTimer *_timer = g_timer_new ();
end_define

begin_define
DECL|macro|GIMP_TIMER_END (message)
define|#
directive|define
name|GIMP_TIMER_END
parameter_list|(
name|message
parameter_list|)
define|\
value|g_printerr ("%s: " message " took %0.2f seconds\n", \               G_STRFUNC, g_timer_elapsed (_timer, NULL)); \   g_timer_destroy (_timer); }
end_define

begin_function_decl
name|gint64
name|gimp_g_type_instance_get_memsize
parameter_list|(
name|GTypeInstance
modifier|*
name|instance
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_object_get_memsize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_hash_table_get_memsize
parameter_list|(
name|GHashTable
modifier|*
name|hash
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_hash_table_get_memsize_foreach
parameter_list|(
name|GHashTable
modifier|*
name|hash
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_slist_get_memsize
parameter_list|(
name|GSList
modifier|*
name|slist
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_slist_get_memsize_foreach
parameter_list|(
name|GSList
modifier|*
name|slist
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_list_get_memsize
parameter_list|(
name|GList
modifier|*
name|list
parameter_list|,
name|gint64
name|data_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_list_get_memsize_foreach
parameter_list|(
name|GList
modifier|*
name|slist
parameter_list|,
name|GimpMemsizeFunc
name|func
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_value_get_memsize
parameter_list|(
name|GValue
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_g_param_spec_get_memsize
parameter_list|(
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_string_get_memsize
parameter_list|(
specifier|const
name|gchar
modifier|*
name|string
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint64
name|gimp_parasite_get_memsize
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gint64
modifier|*
name|gui_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_default_language
parameter_list|(
specifier|const
name|gchar
modifier|*
name|category
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|gimp_get_default_unit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
name|GParameter
modifier|*
name|gimp_parameters_append
argument_list|(
name|GType
name|object_type
argument_list|,
name|GParameter
operator|*
name|params
argument_list|,
name|gint
operator|*
name|n_params
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GParameter
modifier|*
name|gimp_parameters_append_valist
parameter_list|(
name|GType
name|object_type
parameter_list|,
name|GParameter
modifier|*
name|params
parameter_list|,
name|gint
modifier|*
name|n_params
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_parameters_free
parameter_list|(
name|GParameter
modifier|*
name|params
parameter_list|,
name|gint
name|n_params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_value_array_truncate
parameter_list|(
name|GValueArray
modifier|*
name|args
parameter_list|,
name|gint
name|n_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_temp_filename
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_markup_extract_text
parameter_list|(
specifier|const
name|gchar
modifier|*
name|markup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_enum_get_value_name
parameter_list|(
name|GType
name|enum_type
parameter_list|,
name|gint
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* Common values for the n_snap_lines parameter of  * gimp_constrain_line.  */
end_comment

begin_define
DECL|macro|GIMP_CONSTRAIN_LINE_90_DEGREES
define|#
directive|define
name|GIMP_CONSTRAIN_LINE_90_DEGREES
value|2
end_define

begin_define
DECL|macro|GIMP_CONSTRAIN_LINE_45_DEGREES
define|#
directive|define
name|GIMP_CONSTRAIN_LINE_45_DEGREES
value|4
end_define

begin_define
DECL|macro|GIMP_CONSTRAIN_LINE_15_DEGREES
define|#
directive|define
name|GIMP_CONSTRAIN_LINE_15_DEGREES
value|12
end_define

begin_function_decl
name|void
name|gimp_constrain_line
parameter_list|(
name|gdouble
name|start_x
parameter_list|,
name|gdouble
name|start_y
parameter_list|,
name|gdouble
modifier|*
name|end_x
parameter_list|,
name|gdouble
modifier|*
name|end_y
parameter_list|,
name|gint
name|n_snap_lines
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __APP_GIMP_UTILS_H__ */
end_comment

end_unit

