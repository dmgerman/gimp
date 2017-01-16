begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * operations-types.h  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__OPERATIONS_TYPES_H__
end_ifndef

begin_define
DECL|macro|__OPERATIONS_TYPES_H__
define|#
directive|define
name|__OPERATIONS_TYPES_H__
end_define

begin_include
include|#
directive|include
file|<gegl-types.h>
end_include

begin_include
include|#
directive|include
file|"gegl/gimp-gegl-types.h"
end_include

begin_include
include|#
directive|include
file|"operations-enums.h"
end_include

begin_comment
comment|/*  operations  */
end_comment

begin_typedef
DECL|typedef|GimpOperationPointFilter
typedef|typedef
name|struct
name|_GimpOperationPointFilter
name|GimpOperationPointFilter
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOperationPointLayerMode
typedef|typedef
name|struct
name|_GimpOperationPointLayerMode
name|GimpOperationPointLayerMode
typedef|;
end_typedef

begin_comment
comment|/*  operation config objects  */
end_comment

begin_typedef
DECL|typedef|GimpBrightnessContrastConfig
typedef|typedef
name|struct
name|_GimpBrightnessContrastConfig
name|GimpBrightnessContrastConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCageConfig
typedef|typedef
name|struct
name|_GimpCageConfig
name|GimpCageConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorBalanceConfig
typedef|typedef
name|struct
name|_GimpColorBalanceConfig
name|GimpColorBalanceConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorizeConfig
typedef|typedef
name|struct
name|_GimpColorizeConfig
name|GimpColorizeConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpCurvesConfig
typedef|typedef
name|struct
name|_GimpCurvesConfig
name|GimpCurvesConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDesaturateConfig
typedef|typedef
name|struct
name|_GimpDesaturateConfig
name|GimpDesaturateConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpHueSaturationConfig
typedef|typedef
name|struct
name|_GimpHueSaturationConfig
name|GimpHueSaturationConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpLevelsConfig
typedef|typedef
name|struct
name|_GimpLevelsConfig
name|GimpLevelsConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpPosterizeConfig
typedef|typedef
name|struct
name|_GimpPosterizeConfig
name|GimpPosterizeConfig
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpThresholdConfig
typedef|typedef
name|struct
name|_GimpThresholdConfig
name|GimpThresholdConfig
typedef|;
end_typedef

begin_comment
comment|/*  non-object types  */
end_comment

begin_typedef
DECL|typedef|GimpCagePoint
typedef|typedef
name|struct
name|_GimpCagePoint
name|GimpCagePoint
typedef|;
end_typedef

begin_comment
comment|/*  functions  */
end_comment

begin_typedef
DECL|typedef|GimpLayerModeFunc
typedef|typedef
name|gboolean
function_decl|(
modifier|*
name|GimpLayerModeFunc
function_decl|)
parameter_list|(
name|gfloat
modifier|*
name|in
parameter_list|,
name|gfloat
modifier|*
name|aux
parameter_list|,
name|gfloat
modifier|*
name|mask
parameter_list|,
name|gfloat
modifier|*
name|out
parameter_list|,
name|gfloat
name|opacity
parameter_list|,
name|glong
name|samples
parameter_list|,
specifier|const
name|GeglRectangle
modifier|*
name|roi
parameter_list|,
name|gint
name|level
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpBlendFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpBlendFunc
function_decl|)
parameter_list|(
specifier|const
name|float
modifier|*
name|dest
parameter_list|,
specifier|const
name|float
modifier|*
name|src
parameter_list|,
name|float
modifier|*
name|out
parameter_list|,
name|gint
name|samples
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __OPERATIONS_TYPES_H__ */
end_comment

end_unit

