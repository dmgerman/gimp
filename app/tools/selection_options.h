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
file|"tool_options.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_SELECTION_OPTIONS
define|#
directive|define
name|GIMP_TYPE_SELECTION_OPTIONS
value|(gimp_selection_options_get_type ())
end_define

begin_define
DECL|macro|GIMP_SELECTION_OPTIONS (obj)
define|#
directive|define
name|GIMP_SELECTION_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SELECTION_OPTIONS, GimpSelectionOptions))
end_define

begin_define
DECL|macro|GIMP_SELECTION_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_SELECTION_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SELECTION_OPTIONS, GimpSelectionOptionsClass))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_OPTIONS (obj)
define|#
directive|define
name|GIMP_IS_SELECTION_OPTIONS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SELECTION_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_IS_SELECTION_OPTIONS_CLASS (klass)
define|#
directive|define
name|GIMP_IS_SELECTION_OPTIONS_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SELECTION_OPTIONS))
end_define

begin_define
DECL|macro|GIMP_SELECTION_OPTIONS_GET_CLASS (obj)
define|#
directive|define
name|GIMP_SELECTION_OPTIONS_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SELECTION_OPTIONS, GimpSelectionOptionsClass))
end_define

begin_typedef
DECL|typedef|GimpSelectionOptions
typedef|typedef
name|struct
name|_GimpSelectionOptions
name|GimpSelectionOptions
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSelectionOptionsClass
typedef|typedef
name|struct
name|_GimpToolOptionsClass
name|GimpSelectionOptionsClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpSelectionOptions
struct|struct
name|_GimpSelectionOptions
block|{
DECL|member|parent_instance
name|GimpToolOptions
name|parent_instance
decl_stmt|;
comment|/*  options used by all selection tools  */
DECL|member|op
name|SelectOps
name|op
decl_stmt|;
DECL|member|op_d
name|SelectOps
name|op_d
decl_stmt|;
DECL|member|op_w
name|GtkWidget
modifier|*
name|op_w
index|[
literal|4
index|]
decl_stmt|;
comment|/*  4 radio buttons  */
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
comment|/*  used by fuzzy, by-color selection  */
DECL|member|select_transparent
name|gboolean
name|select_transparent
decl_stmt|;
DECL|member|select_transparent_d
name|gboolean
name|select_transparent_d
decl_stmt|;
DECL|member|select_transparent_w
name|GtkWidget
modifier|*
name|select_transparent_w
decl_stmt|;
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
DECL|member|threshold
name|gdouble
name|threshold
decl_stmt|;
comment|/* gdouble          threshold_d; (from gimprc) */
DECL|member|threshold_w
name|GtkObject
modifier|*
name|threshold_w
decl_stmt|;
comment|/*  used by rect., ellipse selection  */
DECL|member|auto_shrink
name|gboolean
name|auto_shrink
decl_stmt|;
DECL|member|auto_shrink_d
name|gboolean
name|auto_shrink_d
decl_stmt|;
DECL|member|auto_shrink_w
name|GtkWidget
modifier|*
name|auto_shrink_w
decl_stmt|;
DECL|member|shrink_merged
name|gboolean
name|shrink_merged
decl_stmt|;
DECL|member|shrink_merged_d
name|gboolean
name|shrink_merged_d
decl_stmt|;
DECL|member|shrink_merged_w
name|GtkWidget
modifier|*
name|shrink_merged_w
decl_stmt|;
DECL|member|fixed_mode
name|GimpRectSelectMode
name|fixed_mode
decl_stmt|;
DECL|member|fixed_mode_d
name|gboolean
name|fixed_mode_d
decl_stmt|;
DECL|member|fixed_mode_w
name|GtkWidget
modifier|*
name|fixed_mode_w
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
name|GimpUnit
name|fixed_unit
decl_stmt|;
DECL|member|fixed_unit_d
name|GimpUnit
name|fixed_unit_d
decl_stmt|;
DECL|member|fixed_unit_w
name|GtkWidget
modifier|*
name|fixed_unit_w
decl_stmt|;
comment|/*  used by iscissors */
DECL|member|interactive
name|gboolean
name|interactive
decl_stmt|;
DECL|member|interactive_d
name|gboolean
name|interactive_d
decl_stmt|;
DECL|member|interactive_w
name|GtkWidget
modifier|*
name|interactive_w
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_selection_options_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_selection_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_selection_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
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

