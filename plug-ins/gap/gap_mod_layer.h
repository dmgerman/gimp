begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_mod_layer.h  * 1998.10.14 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  * modify Layer (perform actions (like raise, set visible, apply filter)  *               - foreach selected layer  *               - in each frame of the selected framerange)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 0.98.00   1998.11.27  hof: - use new module gap_pdb_calls.h  * version 0.97.00              hof: - created module (as extract gap_fileter_foreach)  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_MOD_LAYER_H
end_ifndef

begin_define
DECL|macro|_GAP_MOD_LAYER_H
define|#
directive|define
name|_GAP_MOD_LAYER_H
end_define

begin_define
DECL|macro|MAX_LAYERNAME
define|#
directive|define
name|MAX_LAYERNAME
value|128
end_define

begin_comment
comment|/* action_mode values */
end_comment

begin_define
DECL|macro|ACM_SET_VISIBLE
define|#
directive|define
name|ACM_SET_VISIBLE
value|0
end_define

begin_define
DECL|macro|ACM_SET_INVISIBLE
define|#
directive|define
name|ACM_SET_INVISIBLE
value|1
end_define

begin_define
DECL|macro|ACM_SET_LINKED
define|#
directive|define
name|ACM_SET_LINKED
value|2
end_define

begin_define
DECL|macro|ACM_SET_UNLINKED
define|#
directive|define
name|ACM_SET_UNLINKED
value|3
end_define

begin_define
DECL|macro|ACM_RAISE
define|#
directive|define
name|ACM_RAISE
value|4
end_define

begin_define
DECL|macro|ACM_LOWER
define|#
directive|define
name|ACM_LOWER
value|5
end_define

begin_define
DECL|macro|ACM_MERGE_EXPAND
define|#
directive|define
name|ACM_MERGE_EXPAND
value|6
end_define

begin_define
DECL|macro|ACM_MERGE_IMG
define|#
directive|define
name|ACM_MERGE_IMG
value|7
end_define

begin_define
DECL|macro|ACM_MERGE_BG
define|#
directive|define
name|ACM_MERGE_BG
value|8
end_define

begin_define
DECL|macro|ACM_APPLY_FILTER
define|#
directive|define
name|ACM_APPLY_FILTER
value|9
end_define

begin_define
DECL|macro|ACM_DUPLICATE
define|#
directive|define
name|ACM_DUPLICATE
value|10
end_define

begin_define
DECL|macro|ACM_DELETE
define|#
directive|define
name|ACM_DELETE
value|11
end_define

begin_define
DECL|macro|ACM_RENAME
define|#
directive|define
name|ACM_RENAME
value|12
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon2bae542a0108
block|{
DECL|member|layer_id
name|gint32
name|layer_id
decl_stmt|;
DECL|member|visible
name|gint
name|visible
decl_stmt|;
DECL|member|selected
name|gint
name|selected
decl_stmt|;
DECL|typedef|t_LayliElem
block|}
name|t_LayliElem
typedef|;
end_typedef

begin_function_decl
name|t_LayliElem
modifier|*
name|p_alloc_layli
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
modifier|*
name|l_sel_cnt
parameter_list|,
name|gint
modifier|*
name|nlayers
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
name|p_get_1st_selected
parameter_list|(
name|t_LayliElem
modifier|*
name|layli_ptr
parameter_list|,
name|gint
name|nlayers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_prevent_empty_image
parameter_list|(
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gap_mod_layer
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|range_from
parameter_list|,
name|gint32
name|range_to
parameter_list|,
name|gint32
name|action_mode
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
parameter_list|,
name|char
modifier|*
name|new_layername
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

