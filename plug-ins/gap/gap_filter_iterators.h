begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gap_filter_iterators.h  *  * 1997.12.18 hof (Wolfgang Hofer)  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  * - Headers for XXX_Iterator_ALT Procedures   *  * for now i made some Iterator Plugins using the ending _ALT,  * If New plugins were added to the gimp, or existing ones were updated,  * the Authors should supply original _Iterator Procedures  * (without the _ALT ending)  * This Procedures are then used instead of my (Hacked _ALT) versions.  * to modify the settings for the plugin when called step by step  * on animated multilayer Images.  * without name conflicts.  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_FILTER_ITERATORS_H
end_ifndef

begin_define
DECL|macro|_GAP_FILTER_ITERATORS_H
define|#
directive|define
name|_GAP_FILTER_ITERATORS_H
end_define

begin_typedef
DECL|typedef|t_iter_ALT_func
typedef|typedef
name|gint
function_decl|(
modifier|*
name|t_iter_ALT_func
function_decl|)
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|total_steps
parameter_list|,
name|gdouble
name|current_step
parameter_list|,
name|gint32
name|len_struct
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|t_iter_ALT_tab
typedef|typedef
struct|struct
name|t_iter_ALT_tab
block|{
DECL|member|proc_name
name|char
modifier|*
name|proc_name
decl_stmt|;
DECL|member|proc_func
name|t_iter_ALT_func
name|proc_func
decl_stmt|;
DECL|typedef|t_iter_ALT_tab
block|}
name|t_iter_ALT_tab
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

end_unit

