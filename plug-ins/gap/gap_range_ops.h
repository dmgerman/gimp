begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_range_ops.h  * 1998.07.03 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * GAP operations on frame Ranges (from - to)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * 0.97.00; 1998/10/19   hof: extended gap_range_to_multilayer layer seletion  * 0.96.03; 1998/08/31   hof: gap_range_to_multilayer: all params available  *                            in non-interactive runmode  * 0.96.00; 1998/07/02   hof: (extracted from gap_lib.h)  * 0.94.01; 1998/04/27   hof: added flatten_mode to plugin: gap_range_to_multilayer  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_RANGE_OPS_H
end_ifndef

begin_define
DECL|macro|_GAP_RANGE_OPS_H
define|#
directive|define
name|_GAP_RANGE_OPS_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* flatten mode bits used in gap_range_to_multilayer */
end_comment

begin_define
DECL|macro|FLAM_MERG_EXPAND
define|#
directive|define
name|FLAM_MERG_EXPAND
value|0
end_define

begin_define
DECL|macro|FLAM_MERG_CLIP_IMG
define|#
directive|define
name|FLAM_MERG_CLIP_IMG
value|1
end_define

begin_define
DECL|macro|FLAM_MERG_CLIP_BG
define|#
directive|define
name|FLAM_MERG_CLIP_BG
value|2
end_define

begin_define
DECL|macro|FLAM_MERG_FLAT
define|#
directive|define
name|FLAM_MERG_FLAT
value|3
end_define

begin_comment
comment|/* Animation sizechange modes */
end_comment

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon2974a5240103
block|{
DECL|enumerator|ASIZ_SCALE
name|ASIZ_SCALE
DECL|enumerator|ASIZ_RESIZE
block|,
name|ASIZ_RESIZE
DECL|enumerator|ASIZ_CROP
block|,
name|ASIZ_CROP
DECL|typedef|t_gap_asiz
block|}
name|t_gap_asiz
typedef|;
end_typedef

begin_function_decl
name|gint32
name|gap_range_to_multilayer
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|,
name|long
name|flatten_mode
parameter_list|,
name|long
name|bg_visible
parameter_list|,
name|long
name|framerate
parameter_list|,
name|char
modifier|*
name|frame_basename
parameter_list|,
name|int
name|frame_basename_len
parameter_list|,
name|gint32
name|sel_mode
parameter_list|,
name|gint32
name|sel_case
parameter_list|,
name|gint32
name|sel_invert
parameter_list|,
name|char
modifier|*
name|sel_pattern
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_range_flatten
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_range_layer_del
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|,
name|long
name|position
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_range_conv
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|long
name|range_from
parameter_list|,
name|long
name|range_to
parameter_list|,
name|long
name|flatten
parameter_list|,
name|GImageType
name|dest_type
parameter_list|,
name|gint32
name|dest_colors
parameter_list|,
name|gint32
name|dest_dither
parameter_list|,
name|char
modifier|*
name|basename
parameter_list|,
name|char
modifier|*
name|extension
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|gap_anim_sizechange
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|t_gap_asiz
name|asiz_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|long
name|size_x
parameter_list|,
name|long
name|size_y
parameter_list|,
name|long
name|offs_x
parameter_list|,
name|long
name|offs_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

