begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__APP_GIMP_UNIT_H__
end_ifndef

begin_define
DECL|macro|__APP_GIMP_UNIT_H__
define|#
directive|define
name|__APP_GIMP_UNIT_H__
end_define

begin_function_decl
name|void
name|gimp_units_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_units_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unitrc_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unitrc_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|_gimp_unit_get_number_of_units
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|_gimp_unit_get_number_of_built_in_units
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpUnit
name|_gimp_unit_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gdouble
name|factor
parameter_list|,
name|gint
name|digits
parameter_list|,
name|gchar
modifier|*
name|symbol
parameter_list|,
name|gchar
modifier|*
name|abbreviation
parameter_list|,
name|gchar
modifier|*
name|singular
parameter_list|,
name|gchar
modifier|*
name|plural
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|_gimp_unit_get_deletion_flag
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|_gimp_unit_set_deletion_flag
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gboolean
name|deletion_flag
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gdouble
name|_gimp_unit_get_factor
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|_gimp_unit_get_digits
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_unit_get_identifier
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_unit_get_symbol
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_unit_get_abbreviation
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_unit_get_singular
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|_gimp_unit_get_plural
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpUnit
name|unit
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __APP_GIMP_UNIT_H__  */
end_comment

end_unit

