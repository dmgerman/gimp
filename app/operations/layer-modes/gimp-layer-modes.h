begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp-layer-modes.h  * Copyright (C) 2017 Michael Natterer<mitch@gimp.org>  *                    Ãyvind KolÃ¥s<pippin@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_LAYER_MODES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_LAYER_MODES_H__
define|#
directive|define
name|__GIMP_LAYER_MODES_H__
end_define

begin_function_decl
name|void
name|gimp_layer_modes_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_is_legacy
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_is_blend_space_mutable
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_is_composite_space_mutable
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_is_composite_mode_mutable
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_is_subtractive
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_mode_get_blend_space
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerColorSpace
name|gimp_layer_mode_get_composite_space
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|gimp_layer_mode_get_composite_mode
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeMode
name|gimp_layer_mode_get_paint_composite_mode
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_layer_mode_get_operation
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerModeFunc
name|gimp_layer_mode_get_function
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerModeContext
name|gimp_layer_mode_get_context
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerMode
modifier|*
name|gimp_layer_mode_get_context_array
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerModeContext
name|context
parameter_list|,
name|gint
modifier|*
name|n_modes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerModeGroup
name|gimp_layer_mode_get_group
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|GimpLayerMode
modifier|*
name|gimp_layer_mode_get_group_array
parameter_list|(
name|GimpLayerModeGroup
name|group
parameter_list|,
name|gint
modifier|*
name|n_modes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_layer_mode_get_for_group
parameter_list|(
name|GimpLayerMode
name|old_mode
parameter_list|,
name|GimpLayerModeGroup
name|new_group
parameter_list|,
name|GimpLayerMode
modifier|*
name|new_mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|Babl
modifier|*
name|gimp_layer_mode_get_format
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerColorSpace
name|composite_space
parameter_list|,
name|GimpLayerColorSpace
name|blend_space
parameter_list|,
specifier|const
name|Babl
modifier|*
name|preferred_format
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpLayerCompositeRegion
name|gimp_layer_mode_get_included_region
parameter_list|(
name|GimpLayerMode
name|mode
parameter_list|,
name|GimpLayerCompositeMode
name|composite_mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_LAYER_MODES_H__ */
end_comment

end_unit

