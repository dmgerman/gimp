begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  xpdb_calls.h  *  */
end_comment

begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* revision history:  * version 1.02.00; 1999/02/01  hof: PDB-calls to load/save resolution tattoos and parasites  *                                   (needs GIMP 1.1.1)-- UNDER CONSTRUCTION ---  * version 1.01.00; 1998/11/22  hof: PDB-calls to load/save guides under GIMP 1.1  * version 1.00.00; 1998/10/26  hof: 1.st (pre) release  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_XPDB_CALLS_H
end_ifndef

begin_define
DECL|macro|_XPDB_CALLS_H
define|#
directive|define
name|_XPDB_CALLS_H
end_define

begin_include
include|#
directive|include
file|"libgimp/gimp.h"
end_include

begin_function_decl
name|gint
name|p_procedure_available
parameter_list|(
name|char
modifier|*
name|proc_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_get_gimp_selection_bounds
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
modifier|*
name|x1
parameter_list|,
name|gint32
modifier|*
name|y1
parameter_list|,
name|gint32
modifier|*
name|x2
parameter_list|,
name|gint32
modifier|*
name|y2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_selection_load
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|channel_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|p_layer_set_linked
parameter_list|(
name|gint32
name|layer_id
parameter_list|,
name|gint32
name|new_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_layer_get_linked
parameter_list|(
name|gint32
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_image_floating_sel_attached_to
parameter_list|(
name|gint32
name|image_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_floating_sel_attach
parameter_list|(
name|gint32
name|layer_id
parameter_list|,
name|gint32
name|drawable_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_floating_sel_rigor
parameter_list|(
name|gint32
name|layer_id
parameter_list|,
name|gint32
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_floating_sel_relax
parameter_list|(
name|gint32
name|layer_id
parameter_list|,
name|gint32
name|undo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_image_add_guide
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|position
parameter_list|,
name|gint32
name|orientation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_image_findnext_guide
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|guide_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_image_get_guide_position
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|guide_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_image_get_guide_orientation
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|gint32
name|guide_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_gimp_add_busy_cursors
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|p_gimp_remove_busy_cursors
parameter_list|(
name|void
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_image_get_resolution
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|float
modifier|*
name|xresolution
parameter_list|,
name|float
modifier|*
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|p_gimp_image_set_resolution
parameter_list|(
name|gint32
name|image_id
parameter_list|,
name|float
name|xresolution
parameter_list|,
name|float
name|yresolution
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_layer_get_tattoo
parameter_list|(
name|gint32
name|layer_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint32
name|p_gimp_channel_get_tattoo
parameter_list|(
name|gint32
name|channel_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|Parasite
modifier|*
name|gimp_image_find_parasite
parameter_list|(
name|gint32
name|image_id
parameter_list|,
specifier|const
name|char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

