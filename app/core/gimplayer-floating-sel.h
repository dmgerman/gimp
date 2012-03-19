begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_FLOATING_SEL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_FLOATING_SEL_H__
define|#
directive|define
name|__GIMP_LAYER_FLOATING_SEL_H__
end_define

begin_function_decl
name|void
name|floating_sel_attach
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|floating_sel_anchor
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|floating_sel_to_layer
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|floating_sel_activate_drawable
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpBoundSeg
modifier|*
name|floating_sel_boundary
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|,
name|gint
modifier|*
name|n_segs
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|floating_sel_invalidate
parameter_list|(
name|GimpLayer
modifier|*
name|layer
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_FLOATING_SEL_H__ */
end_comment

end_unit

