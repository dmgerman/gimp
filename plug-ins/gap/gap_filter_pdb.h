begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  gap_filter_pdb.h  *  * GAP ... Gimp Animation Plugins  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_GAP_FILTER_PDB_H
end_ifndef

begin_define
DECL|macro|_GAP_FILTER_PDB_H
define|#
directive|define
name|_GAP_FILTER_PDB_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27d704660103
DECL|enumerator|PTYP_ANY
block|{
name|PTYP_ANY
init|=
literal|0
block|,
DECL|enumerator|PTYP_ITERATOR
name|PTYP_ITERATOR
init|=
literal|1
block|,
DECL|enumerator|PTYP_CAN_OPERATE_ON_DRAWABLE
name|PTYP_CAN_OPERATE_ON_DRAWABLE
init|=
literal|2
DECL|typedef|t_proc_type
block|}
name|t_proc_type
typedef|;
end_typedef

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon27d704660203
DECL|enumerator|PAPP_CONSTANT
block|{
name|PAPP_CONSTANT
init|=
literal|0
block|,
DECL|enumerator|PTYP_VARYING_LINEAR
name|PTYP_VARYING_LINEAR
init|=
literal|1
DECL|typedef|t_apply_mode
block|}
name|t_apply_mode
typedef|;
end_typedef

begin_comment
comment|/* ------------------------  * gap_filter_pdb.h  * ------------------------  */
end_comment

begin_function_decl
name|gint
name|p_call_plugin
parameter_list|(
name|char
modifier|*
name|plugin_name
parameter_list|,
name|gint32
name|image_id
parameter_list|,
name|gint32
name|layer_id
parameter_list|,
name|GimpRunModeType
name|run_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_save_xcf
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|char
modifier|*
name|sav_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_get_data
parameter_list|(
name|char
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_set_data
parameter_list|(
name|char
modifier|*
name|key
parameter_list|,
name|gint
name|plugin_data_len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_procedure_available
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|,
name|t_proc_type
name|ptype
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|p_get_iterator_proc
parameter_list|(
name|char
modifier|*
name|plugin_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_constraint_proc_sel1
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_constraint_proc_sel2
parameter_list|(
name|gchar
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_constraint_proc
parameter_list|(
name|gchar
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

