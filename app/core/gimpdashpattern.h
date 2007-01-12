begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * gimpdashpattern.h  * Copyright (C) 2003 Simon Budig  * Copyright (C) 2005 Sven Neumann  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DASH_PATTERN_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DASH_PATTERN_H__
define|#
directive|define
name|__GIMP_DASH_PATTERN_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_DASH_PATTERN
define|#
directive|define
name|GIMP_TYPE_DASH_PATTERN
value|(gimp_dash_pattern_get_type ())
end_define

begin_define
DECL|macro|GIMP_VALUE_HOLDS_DASH_PATTERN (value)
define|#
directive|define
name|GIMP_VALUE_HOLDS_DASH_PATTERN
parameter_list|(
name|value
parameter_list|)
value|(G_TYPE_CHECK_VALUE_TYPE ((value), GIMP_TYPE_DASH_PATTERN))
end_define

begin_decl_stmt
name|GType
name|gimp_dash_pattern_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GArray
modifier|*
name|gimp_dash_pattern_new_from_preset
parameter_list|(
name|GimpDashPreset
name|preset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GArray
modifier|*
name|gimp_dash_pattern_new_from_segments
parameter_list|(
specifier|const
name|gboolean
modifier|*
name|segments
parameter_list|,
name|gint
name|n_segments
parameter_list|,
name|gdouble
name|dash_length
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dash_pattern_fill_segments
parameter_list|(
name|GArray
modifier|*
name|pattern
parameter_list|,
name|gboolean
modifier|*
name|segments
parameter_list|,
name|gint
name|n_segments
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GArray
modifier|*
name|gimp_dash_pattern_from_value_array
parameter_list|(
name|GValueArray
modifier|*
name|value_array
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GValueArray
modifier|*
name|gimp_dash_pattern_to_value_array
parameter_list|(
name|GArray
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GArray
modifier|*
name|gimp_dash_pattern_copy
parameter_list|(
name|GArray
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dash_pattern_free
parameter_list|(
name|GArray
modifier|*
name|pattern
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DASH_PATTERN_H__  */
end_comment

end_unit

