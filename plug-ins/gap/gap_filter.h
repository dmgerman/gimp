begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  gap_filter.h  *  * GAP ... Gimp Animation Plugins  *  * This Module contains:  *   Headers for gap_filter_*.c (animated filter apply to all imagelayers)  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_FILTER_H
end_ifndef

begin_define
DECL|macro|_GAP_FILTER_H
define|#
directive|define
name|_GAP_FILTER_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_comment
comment|/* ------------------------  * gap_filter_foreach.h  * ------------------------  */
end_comment

begin_function_decl
name|gint
name|gap_proc_anim_apply
parameter_list|(
name|GRunModeType
name|run_mode
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|l_plugin_name
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* ------------------------  * gap_filter_iterators.h  * ------------------------  */
end_comment

begin_comment
comment|/* Hacked Iterators for some existing Plugins */
end_comment

begin_function_decl
name|gint
name|gap_run_iterators_ALT
parameter_list|(
name|char
modifier|*
name|name
parameter_list|,
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
end_function_decl

begin_function_decl
name|void
name|gap_query_iterators_ALT
parameter_list|()
function_decl|;
end_function_decl

begin_comment
comment|/* ------------------------  * gap_dbbrowser.h  * ------------------------  */
end_comment

begin_typedef
DECL|struct|__anon278b4d070108
typedef|typedef
struct|struct
block|{
DECL|member|selected_proc_name
name|char
name|selected_proc_name
index|[
literal|256
index|]
decl_stmt|;
DECL|member|button_nr
name|int
name|button_nr
decl_stmt|;
comment|/* -1 on cancel, 0 .. n */
DECL|typedef|t_gap_db_browse_result
block|}
name|t_gap_db_browse_result
typedef|;
end_typedef

begin_comment
comment|/* proc to check if to add or not to add the procedure to the browsers listbox  * retcode:  * 0 ... do not add  * 1 ... add the procedure to the browsers listbox  */
end_comment

begin_typedef
DECL|typedef|t_constraint_func
typedef|typedef
name|int
function_decl|(
modifier|*
name|t_constraint_func
function_decl|)
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|int
name|gap_db_browser_dialog
parameter_list|(
name|char
modifier|*
name|title_txt
parameter_list|,
name|char
modifier|*
name|button_1_txt
parameter_list|,
name|char
modifier|*
name|button_2_txt
parameter_list|,
name|t_constraint_func
name|constraint_func
parameter_list|,
name|t_constraint_func
name|constraint_func_sel1
parameter_list|,
name|t_constraint_func
name|constraint_func_sel2
parameter_list|,
name|t_gap_db_browse_result
modifier|*
name|result
parameter_list|,
name|gint
name|init_gtk_flag
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* ------------------------  * gap_filter_codegen.h  * ------------------------  */
end_comment

begin_function_decl
name|void
name|p_remove_codegen_files
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gen_code_iter_ALT
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gen_forward_iter_ALT
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gen_tab_iter_ALT
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gen_code_iter
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

