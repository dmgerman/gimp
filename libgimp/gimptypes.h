begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimptypes.h  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TYPES_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TYPES_H__
define|#
directive|define
name|__GIMP_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<libgimpbase/gimpbasetypes.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the html documentation */
end_comment

begin_typedef
DECL|typedef|GimpPlugInInfo
typedef|typedef
name|struct
name|_GimpPlugInInfo
name|GimpPlugInInfo
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpTile
typedef|typedef
name|struct
name|_GimpTile
name|GimpTile
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDrawable
typedef|typedef
name|struct
name|_GimpDrawable
name|GimpDrawable
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPixelRgn
typedef|typedef
name|struct
name|_GimpPixelRgn
name|GimpPixelRgn
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParamDef
typedef|typedef
name|struct
name|_GimpParamDef
name|GimpParamDef
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParamRegion
typedef|typedef
name|struct
name|_GimpParamRegion
name|GimpParamRegion
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParamData
typedef|typedef
name|union
name|_GimpParamData
name|GimpParamData
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpParam
typedef|typedef
name|struct
name|_GimpParam
name|GimpParam
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|GIMP_DISABLE_DEPRECATED
end_ifndef

begin_comment
comment|/*  This is so ugly it hurts. C++ won't let us have enum GimpLayerMode  *  in the API where we used to have enum GimpLayerModeEffects, so  *  typedef and define around to make it happy:  */
end_comment

begin_typedef
DECL|typedef|GimpLayerModeEffects
typedef|typedef
name|GimpLayerMode
name|GimpLayerModeEffects
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_NORMAL_MODE
define|#
directive|define
name|GIMP_NORMAL_MODE
value|GIMP_LAYER_MODE_NORMAL_LEGACY
end_define

begin_define
DECL|macro|GIMP_DISSOLVE_MODE
define|#
directive|define
name|GIMP_DISSOLVE_MODE
value|GIMP_LAYER_MODE_DISSOLVE
end_define

begin_define
DECL|macro|GIMP_BEHIND_MODE
define|#
directive|define
name|GIMP_BEHIND_MODE
value|GIMP_LAYER_MODE_BEHIND_LEGACY
end_define

begin_define
DECL|macro|GIMP_MULTIPLY_MODE
define|#
directive|define
name|GIMP_MULTIPLY_MODE
value|GIMP_LAYER_MODE_MULTIPLY_LEGACY
end_define

begin_define
DECL|macro|GIMP_SCREEN_MODE
define|#
directive|define
name|GIMP_SCREEN_MODE
value|GIMP_LAYER_MODE_SCREEN_LEGACY
end_define

begin_define
DECL|macro|GIMP_OVERLAY_MODE
define|#
directive|define
name|GIMP_OVERLAY_MODE
value|GIMP_LAYER_MODE_OVERLAY_LEGACY
end_define

begin_define
DECL|macro|GIMP_DIFFERENCE_MODE
define|#
directive|define
name|GIMP_DIFFERENCE_MODE
value|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
end_define

begin_define
DECL|macro|GIMP_ADDITION_MODE
define|#
directive|define
name|GIMP_ADDITION_MODE
value|GIMP_LAYER_MODE_ADDITION_LEGACY
end_define

begin_define
DECL|macro|GIMP_SUBTRACT_MODE
define|#
directive|define
name|GIMP_SUBTRACT_MODE
value|GIMP_LAYER_MODE_SUBTRACT_LEGACY
end_define

begin_define
DECL|macro|GIMP_DARKEN_ONLY_MODE
define|#
directive|define
name|GIMP_DARKEN_ONLY_MODE
value|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
end_define

begin_define
DECL|macro|GIMP_LIGHTEN_ONLY_MODE
define|#
directive|define
name|GIMP_LIGHTEN_ONLY_MODE
value|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
end_define

begin_define
DECL|macro|GIMP_HUE_MODE
define|#
directive|define
name|GIMP_HUE_MODE
value|GIMP_LAYER_MODE_HSV_HUE_LEGACY
end_define

begin_define
DECL|macro|GIMP_SATURATION_MODE
define|#
directive|define
name|GIMP_SATURATION_MODE
value|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
end_define

begin_define
DECL|macro|GIMP_COLOR_MODE
define|#
directive|define
name|GIMP_COLOR_MODE
value|GIMP_LAYER_MODE_HSV_COLOR_LEGACY
end_define

begin_define
DECL|macro|GIMP_VALUE_MODE
define|#
directive|define
name|GIMP_VALUE_MODE
value|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
end_define

begin_define
DECL|macro|GIMP_DIVIDE_MODE
define|#
directive|define
name|GIMP_DIVIDE_MODE
value|GIMP_LAYER_MODE_DIVIDE_LEGACY
end_define

begin_define
DECL|macro|GIMP_DODGE_MODE
define|#
directive|define
name|GIMP_DODGE_MODE
value|GIMP_LAYER_MODE_DODGE_LEGACY
end_define

begin_define
DECL|macro|GIMP_BURN_MODE
define|#
directive|define
name|GIMP_BURN_MODE
value|GIMP_LAYER_MODE_BURN_LEGACY
end_define

begin_define
DECL|macro|GIMP_HARDLIGHT_MODE
define|#
directive|define
name|GIMP_HARDLIGHT_MODE
value|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
end_define

begin_define
DECL|macro|GIMP_SOFTLIGHT_MODE
define|#
directive|define
name|GIMP_SOFTLIGHT_MODE
value|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
end_define

begin_define
DECL|macro|GIMP_GRAIN_EXTRACT_MODE
define|#
directive|define
name|GIMP_GRAIN_EXTRACT_MODE
value|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
end_define

begin_define
DECL|macro|GIMP_GRAIN_MERGE_MODE
define|#
directive|define
name|GIMP_GRAIN_MERGE_MODE
value|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
end_define

begin_define
DECL|macro|GIMP_COLOR_ERASE_MODE
define|#
directive|define
name|GIMP_COLOR_ERASE_MODE
value|GIMP_LAYER_MODE_COLOR_ERASE
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ! GIMP_DISABLE_DEPRECATED */
end_comment

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TYPES_H__ */
end_comment

end_unit

