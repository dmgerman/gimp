begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CHANNEL_SELECT_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CHANNEL_SELECT_H__
define|#
directive|define
name|__GIMP_CHANNEL_SELECT_H__
end_define

begin_comment
comment|/*  basic selection functions  */
end_comment

begin_function_decl
name|void
name|gimp_channel_select_rectangle
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_ellipse
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_round_rect
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gdouble
name|corner_radius_y
parameter_list|,
name|gdouble
name|corner_radius_x
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  select by GimpScanConvert functions  */
end_comment

begin_function_decl
name|void
name|gimp_channel_select_scan_convert
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GimpScanConvert
modifier|*
name|scan_convert
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_polygon
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|gint
name|n_points
parameter_list|,
specifier|const
name|GimpVector2
modifier|*
name|points
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_vectors
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|,
name|gboolean
name|push_undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_buffer
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GeglBuffer
modifier|*
name|add_on
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  select by GimpChannel functions  */
end_comment

begin_function_decl
name|void
name|gimp_channel_select_channel
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
specifier|const
name|gchar
modifier|*
name|undo_desc
parameter_list|,
name|GimpChannel
modifier|*
name|add_on
parameter_list|,
name|gint
name|offset_x
parameter_list|,
name|gint
name|offset_y
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_alpha
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_component
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpChannelType
name|component
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_fuzzy
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|gboolean
name|diagonal_neighbors
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_by_color
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gfloat
name|threshold
parameter_list|,
name|gboolean
name|select_transparent
parameter_list|,
name|GimpSelectCriterion
name|select_criterion
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|antialias
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_channel_select_by_index
parameter_list|(
name|GimpChannel
modifier|*
name|channel
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|index
parameter_list|,
name|GimpChannelOps
name|op
parameter_list|,
name|gboolean
name|feather
parameter_list|,
name|gdouble
name|feather_radius_x
parameter_list|,
name|gdouble
name|feather_radius_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CHANNEL_SELECT_H__  */
end_comment

end_unit

