begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2013 Daniel Sabo  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_function_decl
name|void
name|combine_paint_mask_to_canvas_mask
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|paint_mask
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|GeglBuffer
modifier|*
name|canvas_buffer
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gboolean
name|stipple
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|canvas_buffer_to_paint_buf_alpha
parameter_list|(
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|canvas_buffer
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|paint_mask_to_paint_buffer
parameter_list|(
specifier|const
name|GimpTempBuf
modifier|*
name|paint_mask
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|gfloat
name|paint_opacity
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|do_layer_blend
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|dst_buffer
parameter_list|,
name|GimpTempBuf
modifier|*
name|paint_buf
parameter_list|,
name|GeglBuffer
modifier|*
name|mask_buffer
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|gint
name|x_offset
parameter_list|,
name|gint
name|y_offset
parameter_list|,
name|gint
name|mask_x_offset
parameter_list|,
name|gint
name|mask_y_offset
parameter_list|,
name|gboolean
name|linear_mode
parameter_list|,
name|GimpLayerModeEffects
name|paint_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|mask_components_onto
parameter_list|(
name|GeglBuffer
modifier|*
name|src_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|aux_buffer
parameter_list|,
name|GeglBuffer
modifier|*
name|dst_buffer
parameter_list|,
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|GimpComponentMask
name|mask
parameter_list|,
name|gboolean
name|linear_mode
parameter_list|)
function_decl|;
end_function_decl

end_unit

