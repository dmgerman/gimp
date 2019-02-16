begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 2013 Daniel Sabo  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_CORE_LOOPS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_CORE_LOOPS_H__
define|#
directive|define
name|__GIMP_PAINT_CORE_LOOPS_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon277465440103
block|{
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_NONE
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_NONE
init|=
literal|0
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_COMBINE_PAINT_MASK_TO_CANVAS_BUFFER
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_COMBINE_PAINT_MASK_TO_CANVAS_BUFFER
init|=
literal|1
operator|<<
literal|0
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_CANVAS_BUFFER_TO_PAINT_BUF_ALPHA
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_CANVAS_BUFFER_TO_PAINT_BUF_ALPHA
init|=
literal|1
operator|<<
literal|1
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_PAINT_MASK_TO_PAINT_BUF_ALPHA
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_PAINT_MASK_TO_PAINT_BUF_ALPHA
init|=
literal|1
operator|<<
literal|2
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_CANVAS_BUFFER_TO_COMP_MASK
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_CANVAS_BUFFER_TO_COMP_MASK
init|=
literal|1
operator|<<
literal|3
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_PAINT_MASK_TO_COMP_MASK
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_PAINT_MASK_TO_COMP_MASK
init|=
literal|1
operator|<<
literal|4
block|,
DECL|enumerator|GIMP_PAINT_CORE_LOOPS_ALGORITHM_DO_LAYER_BLEND
name|GIMP_PAINT_CORE_LOOPS_ALGORITHM_DO_LAYER_BLEND
init|=
literal|1
operator|<<
literal|5
DECL|typedef|GimpPaintCoreLoopsAlgorithm
block|}
name|GimpPaintCoreLoopsAlgorithm
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon277465440208
block|{
DECL|member|canvas_buffer
name|GeglBuffer
modifier|*
name|canvas_buffer
decl_stmt|;
DECL|member|paint_buf
name|GimpTempBuf
modifier|*
name|paint_buf
decl_stmt|;
DECL|member|paint_buf_offset_x
name|gint
name|paint_buf_offset_x
decl_stmt|;
DECL|member|paint_buf_offset_y
name|gint
name|paint_buf_offset_y
decl_stmt|;
DECL|member|paint_mask
specifier|const
name|GimpTempBuf
modifier|*
name|paint_mask
decl_stmt|;
DECL|member|paint_mask_offset_x
name|gint
name|paint_mask_offset_x
decl_stmt|;
DECL|member|paint_mask_offset_y
name|gint
name|paint_mask_offset_y
decl_stmt|;
DECL|member|stipple
name|gboolean
name|stipple
decl_stmt|;
DECL|member|src_buffer
name|GeglBuffer
modifier|*
name|src_buffer
decl_stmt|;
DECL|member|dest_buffer
name|GeglBuffer
modifier|*
name|dest_buffer
decl_stmt|;
DECL|member|mask_buffer
name|GeglBuffer
modifier|*
name|mask_buffer
decl_stmt|;
DECL|member|mask_offset_x
name|gint
name|mask_offset_x
decl_stmt|;
DECL|member|mask_offset_y
name|gint
name|mask_offset_y
decl_stmt|;
DECL|member|paint_opacity
name|gdouble
name|paint_opacity
decl_stmt|;
DECL|member|image_opacity
name|gdouble
name|image_opacity
decl_stmt|;
DECL|member|paint_mode
name|GimpLayerMode
name|paint_mode
decl_stmt|;
DECL|typedef|GimpPaintCoreLoopsParams
block|}
name|GimpPaintCoreLoopsParams
typedef|;
end_typedef

begin_function_decl
name|void
name|gimp_paint_core_loops_process
parameter_list|(
specifier|const
name|GimpPaintCoreLoopsParams
modifier|*
name|params
parameter_list|,
name|GimpPaintCoreLoopsAlgorithm
name|algorithms
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
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|GimpComponentMask
name|mask
parameter_list|,
name|GimpTRCType
name|trc
parameter_list|,
specifier|const
name|Babl
modifier|*
name|space
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PAINT_CORE_LOOPS_H__ */
end_comment

end_unit

