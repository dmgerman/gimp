begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__SELECTION_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__SELECTION_OPTIONS_H__
define|#
directive|define
name|__SELECTION_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpunit.h"
end_include

begin_comment
comment|/*  the selection options structures  */
end_comment

begin_typedef
DECL|typedef|SelectionOptions
typedef|typedef
name|struct
name|_SelectionOptions
name|SelectionOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_SelectionOptions
struct|struct
name|_SelectionOptions
block|{
DECL|member|tool_options
name|ToolOptions
name|tool_options
decl_stmt|;
comment|/*  options used by all selection tools  */
DECL|member|feather
name|gboolean
name|feather
decl_stmt|;
DECL|member|feather_d
name|gboolean
name|feather_d
decl_stmt|;
DECL|member|feather_w
name|GtkWidget
modifier|*
name|feather_w
decl_stmt|;
DECL|member|feather_radius
name|gdouble
name|feather_radius
decl_stmt|;
DECL|member|feather_radius_d
name|gdouble
name|feather_radius_d
decl_stmt|;
DECL|member|feather_radius_w
name|GtkObject
modifier|*
name|feather_radius_w
decl_stmt|;
comment|/*  used by all selection tools except rect. select  */
DECL|member|antialias
name|gboolean
name|antialias
decl_stmt|;
DECL|member|antialias_d
name|gboolean
name|antialias_d
decl_stmt|;
DECL|member|antialias_w
name|GtkWidget
modifier|*
name|antialias_w
decl_stmt|;
comment|/*  used by fuzzy, by-color selection  */
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
DECL|member|sample_merged_d
name|gboolean
name|sample_merged_d
decl_stmt|;
DECL|member|sample_merged_w
name|GtkWidget
modifier|*
name|sample_merged_w
decl_stmt|;
comment|/*  used by rect., ellipse selection  */
DECL|member|fixed_size
name|gboolean
name|fixed_size
decl_stmt|;
DECL|member|fixed_size_d
name|gboolean
name|fixed_size_d
decl_stmt|;
DECL|member|fixed_size_w
name|GtkWidget
modifier|*
name|fixed_size_w
decl_stmt|;
DECL|member|fixed_width
name|gdouble
name|fixed_width
decl_stmt|;
DECL|member|fixed_width_d
name|gdouble
name|fixed_width_d
decl_stmt|;
DECL|member|fixed_width_w
name|GtkObject
modifier|*
name|fixed_width_w
decl_stmt|;
DECL|member|fixed_height
name|gdouble
name|fixed_height
decl_stmt|;
DECL|member|fixed_height_d
name|gdouble
name|fixed_height_d
decl_stmt|;
DECL|member|fixed_height_w
name|GtkObject
modifier|*
name|fixed_height_w
decl_stmt|;
DECL|member|fixed_unit
name|GUnit
name|fixed_unit
decl_stmt|;
DECL|member|fixed_unit_d
name|GUnit
name|fixed_unit_d
decl_stmt|;
DECL|member|fixed_unit_w
name|GtkWidget
modifier|*
name|fixed_unit_w
decl_stmt|;
comment|/*  used by bezier selection  */
DECL|member|extend
name|gint
name|extend
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  selection tool options functions  */
end_comment

begin_function_decl
name|SelectionOptions
modifier|*
name|selection_options_new
parameter_list|(
name|ToolType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|selection_options_reset
parameter_list|(
name|SelectionOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  to be used by "derived selection options only  */
end_comment

begin_function_decl
name|void
name|selection_options_init
parameter_list|(
name|SelectionOptions
modifier|*
name|options
parameter_list|,
name|ToolType
name|tool_type
parameter_list|,
name|ToolOptionsResetFunc
name|reset_func
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __SELCTION_OPTIONS_H__  */
end_comment

end_unit

